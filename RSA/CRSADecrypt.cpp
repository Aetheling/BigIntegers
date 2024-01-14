#include "RSAEncryptor.h"
#include "..\BigIntegers\CRandomGenerator.h"
#include "..\BigIntegersBase\SmallPrimes.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                              //
//                                      Public functions                                        //
//                                                                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////

bool CRSADecrypt::GetPublicKeys(CBigInteger &nPublicPower, CBigInteger &nModulus)
{
	if (!(nPublicPower = *m_Box.GetPower()))                                            return false;
	if (EArithmeticOperationResult::eOperationSucceeded != m_Box.GetModulus(&nModulus)) return false;
	return true;
}

size_t CRSADecrypt::SpaceNeededForDecryptedMessage(size_t nEncryptedMessageLength)
{
	size_t nSpace = (nEncryptedMessageLength/m_nModulusBYTESize)*m_nModulusBYTESize;
	if(nSpace<m_nModulusBYTESize) nSpace = m_nModulusBYTESize; // for really small messages
#ifdef _DEBUG
	nSpace++; // space for buffer guard
#endif
	return nSpace;
}

/*
Using the Chinese remainder algorithm

For efficiency, many popular crypto libraries (such as OpenSSL, Java and .NET) use for decryption and signing the following optimization based on the Chinese remainder theorem. The following values are precomputed and stored as part of the private key:

	p and q q – the primes from the key generation,
	dP    = d ( mod (p - 1) ) 
	dQ    = d ( mod (q - 1) ) 
	q_inv = q^(-1) ( mod p ) 

These values allow the recipient to compute the exponentiation m = c^d (mod pq) more efficiently as follows:
  ?   m1 = c^(dP) ( mod p )
  ?   m2 = c^(dQ) ( mod q ),
  ?   h = q_inv ( m1 - m2 ) ( mod p )
  ?   m = (m2 + hq) ( mod pq )

This is more efficient than computing exponentiation by squaring, even though two modular exponentiations have to be computed. The reason is that these two modular exponentiations both use a smaller exponent and a smaller modulus.

dP <-> powerP
dQ <-> powerQ
pq <-> public modulus
*/
bool CRSADecrypt::Decrypt(const char *pMessage, size_t nEncryptedMessageLength, size_t nPaddingBYTEs, char *&pDecryptedMessage, size_t &nMessageLength)
{
	CBigInteger m1, m2, messageChunk;
	char        *pDecryptChunk;
	const char  *pEncryptChunk;
	size_t      nChunks, nSize;
	// check message size -- should be multiple of the modulus size
	if(0 != nEncryptedMessageLength%m_nModulusBYTESize)   return false;
	// get space for the decryption (if necessary)
	if(NULL == pDecryptedMessage)
	{
		nSize             = SpaceNeededForDecryptedMessage(nEncryptedMessageLength);
		pDecryptedMessage = (char *) malloc(nSize);
	}
	if(NULL == pDecryptedMessage) return false;
#ifdef _DEBUG
	pDecryptedMessage[nSize-1] = 'X';
#endif
	nChunks        = nEncryptedMessageLength/m_nModulusBYTESize;
	pEncryptChunk  = pMessage;
	pDecryptChunk  = pDecryptedMessage;
	nMessageLength = nChunks*(m_nModulusBYTESize - 1) - nPaddingBYTEs;
	messageChunk.Reserve(m_Box.GetModulusSize());
	m2.Reserve(m_Box.GetModulusSize()); // make sure has enough space for 0 padding in case of small messages
	for(size_t i=0; i<nChunks; i++)
	{
		messageChunk.SetSize(m_Box.GetModulusSize());
		messageChunk.m_pnValue[m_Box.GetModulusSize() - 1] = 0;
		memcpy(messageChunk.m_pnValue, pEncryptChunk, m_nModulusBYTESize);
		messageChunk.FixLeadingZeros(); // in case the data has leading 0s
		// m1 = c^(dP) ( mod p )
		m_BoxP.Import(&messageChunk, &m2);
		m_BoxP.Power(messageChunk, m1);
		messageChunk.SetSize(m_Box.GetModulusSize());
		messageChunk.m_pnValue[m_Box.GetModulusSize() - 1] = 0;
		memcpy(messageChunk.m_pnValue, pEncryptChunk, m_nModulusBYTESize);
		messageChunk.FixLeadingZeros(); // in case the data has leading 0s
		// m2 = c^(dQ) ( mod q )
		m_BoxQ.Import(&messageChunk, &m2);
		m_BoxQ.Power(messageChunk, m2);
		// h = (q_inv*( m1 - m2 )) ( mod p )
		if(eOperationSucceeded != m_BoxP.Subtract(&m1, &m2, &messageChunk)) return false; // don't need messageChunk anymore; use its space
		if(eOperationSucceeded != m_BoxP.Multiply(&m_qInverse, &messageChunk, &m1)) return false; // don't need m1 anymore; use ITS space
		// m = m2 + hq ( mod pq )
		// note h is < p, so hq <= (p-1)q -- so don't need to worry about taking modulus for multiply
		// m2 is at most q-1. so m2+hq < q + hq <= q + (p-1)q = pq, so don't need to worry about the mod for the full sum
		if(eOperationSucceeded != m_Box.MultiplyAdd(&m1, &m_q, &m2)) return false;
		for(int j=m2.GetSize(); j<m_Box.GetModulusSize(); j++)
		{
			// in case of pesky 0s in the message
			m2.m_pnValue[j] = 0;
		}
		memcpy(pDecryptChunk, m2.GetValue(), m_nModulusBYTESize - 1);
		pDecryptChunk += (m_nModulusBYTESize - 1);
		pEncryptChunk += m_nModulusBYTESize;
	}
#ifdef _DEBUG
	if('X' != pDecryptedMessage[nSize - 1])
	{
		printf("Buffer overrun in decrypted message\n");
    }
#endif
	return true;
}

// https://en.wikipedia.org/wiki/RSA_(cryptosystem)
CRSADecrypt *CRSADecrypt::GetDecrypt(size_t nDesiredModulusSizeInBYTEs, bool bForceUniformPrimeDistribution, bool bProtectAgainstTimingAttacks)
{
	CArithmeticBox   cBox;
	CRandomGenerator cGenerator;
	CBigInteger      p, q, publicPower, dummyA, dummyB, primeMinus1;
	size_t           nBYTELengthP, nBYTELengthQ, nDigits;
	BYTE             nBits;
	CRSADecrypt      *pDecryptor;
	// first, we need a couple prime numbers which, when multiplied together, will give the desired
	// modulus size.  Should be roughly the same size: here, choose them to be within (roughly) 10%
	// of each other in length
	do
	{
		nBYTELengthP = (0.5 + ((float) (rand()%100))/1000)*nDesiredModulusSizeInBYTEs;
		nBYTELengthQ = nDesiredModulusSizeInBYTEs - nBYTELengthP;
		// 65537 is a standard choice for the public power: short (but not too short) with few bits set -> fast.  Also
		// prime, so always works (needs to be coprime with lcm(p-1, q-1) -- being prime insures that no matter what
		// choice of p, q is made)
		if (!publicPower.SetFromHexString("10001")) return NULL;
		// If the public power is a factor of p-1 or q-1, the system won't work.  Either need a new p (q), or a new public
		// power.  If we choose to get a new public power, users will know that either p-1 or q-1 is a multiple of the
		// standard public power, leading to security weakness.  Ergo we choose the route of picking a new p (q).
		do
		{
			GetOddPrime(p, nBYTELengthP, bForceUniformPrimeDistribution);
			if (!(primeMinus1 = p)) return NULL;
			primeMinus1 -= 1;
			cBox.Divide(p, publicPower, dummyA , dummyB); // Divide only done to validate publicPower does NOT divide p
		}
		while(AllSmallPrimeFactors(primeMinus1) || 0 == dummyB.GetSize()); // remainder 0?  public power is a divisor -- try again
		do
		{
			GetOddPrime(q, nBYTELengthQ, bForceUniformPrimeDistribution);
			if (!(primeMinus1 = q)) return NULL;
			primeMinus1 -= 1;
			cBox.Divide(q, publicPower, dummyA , dummyB); // Divide only done to validate publicPower does NOT divide q
		}
		while (AllSmallPrimeFactors(primeMinus1) || TooClose(p,q,cBox) || 0 == dummyB.GetSize()); // remainder 0?  public power is a divisor -- try again
		// larger prime needs to be FIRST
		if(p<q)
			pDecryptor = GetDecrypt(q, p, publicPower, cBox, bProtectAgainstTimingAttacks);
		else
			pDecryptor = GetDecrypt(p, q, publicPower, cBox, bProtectAgainstTimingAttacks);
	}
	while(NULL == pDecryptor);
	return pDecryptor;
}

CRSADecrypt *CRSADecrypt::GetDecrypt(CBigInteger &primeP, CBigInteger &primeQ, bool bProtectAgainstTimingAttacks)
{
	CArithmeticBox   cBox;
	CBigInteger      nDummyA, nDummyB; // just used to check that P, Q are not multiples of the standard public power
	CBigInteger      nPublicPower("10001");
	// larger prime needs to be FIRST
	if(primeP<primeQ)
		return GetDecrypt(primeQ, primeP, nPublicPower, cBox, bProtectAgainstTimingAttacks);
	else
	    return GetDecrypt(primeP, primeQ, nPublicPower, cBox, bProtectAgainstTimingAttacks);
}

CRSADecrypt::~CRSADecrypt()
{
	;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                              //
//                                      Private functions                                       //
//                                                                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////

bool CRSADecrypt::DivisibleBySmallPrime(const CBigInteger &nNumber)
{
	DOUBLEDIGIT nVal;
	const DIGIT *pnDigits  = nNumber.GetValue();
	size_t      nDigit     = nNumber.GetSize() - 1;
	size_t      nDigitCopy = nDigit;
	// rough-and-ready -- the more digits in the number, the more expensive the MR tests and hence the more
	// valuable to check small primes on the off chance they divide
	DOUBLEDIGIT nRemainderA = 0;
	DOUBLEDIGIT nRemainderB = 0;
	DOUBLEDIGIT nRemainderC = 0;
	DOUBLEDIGIT nRemainderD = 0;
	DOUBLEDIGIT nRemainderE = 0;
	DOUBLEDIGIT nRemainderF = 0;
	DOUBLEDIGIT nRemainderG = 0;
	DOUBLEDIGIT nRemainderH = 0;
	// check 7, 11, 13, 17, 19, 23, 29, 31
	do
	{
		nVal = pnDigits[nDigit];
		nRemainderA = (((nVal|nRemainderA)% 7)<<_DIGIT_SIZE_IN_BITS);
		nRemainderB = (((nVal|nRemainderB)% 11)<<_DIGIT_SIZE_IN_BITS);
		nRemainderC = (((nVal|nRemainderC)% 13)<<_DIGIT_SIZE_IN_BITS);
		nRemainderD = (((nVal|nRemainderD)% 17)<<_DIGIT_SIZE_IN_BITS);
		nRemainderE = (((nVal|nRemainderE)% 19)<<_DIGIT_SIZE_IN_BITS);
		nRemainderF = (((nVal|nRemainderF)% 23)<<_DIGIT_SIZE_IN_BITS);
		nRemainderG = (((nVal|nRemainderG)% 29)<<_DIGIT_SIZE_IN_BITS);
		nRemainderH = (((nVal|nRemainderH)% 31)<<_DIGIT_SIZE_IN_BITS);
	}
	while (0 != nDigit--);
	if (0 == nRemainderA || 0 == nRemainderB || 0 == nRemainderC || 0 == nRemainderD || 0 == nRemainderE || 0 == nRemainderF || 0 == nRemainderG || 0 == nRemainderH) return true;
	if (nDigitCopy < 32) return false; // for "small" numbers, going on not worth the extra effor
	nDigit = nDigitCopy;
	// check 37, 41, 43, 47, 53, 59, 61
	do
	{
		nVal = pnDigits[nDigit];
		nRemainderA = (((nVal|nRemainderA)%37)<<_DIGIT_SIZE_IN_BITS);
		nRemainderB = (((nVal|nRemainderB)%41)<<_DIGIT_SIZE_IN_BITS);
		nRemainderC = (((nVal|nRemainderC)%43)<<_DIGIT_SIZE_IN_BITS);
		nRemainderD = (((nVal|nRemainderD)%47)<<_DIGIT_SIZE_IN_BITS);
		nRemainderE = (((nVal|nRemainderE)%53)<<_DIGIT_SIZE_IN_BITS);
		nRemainderF = (((nVal|nRemainderF)%59)<<_DIGIT_SIZE_IN_BITS);
		nRemainderG = (((nVal|nRemainderG)%61)<<_DIGIT_SIZE_IN_BITS);
	}
	while (0 != nDigit--);
	if (0 == nRemainderA || 0 == nRemainderB || 0 == nRemainderC || 0 == nRemainderD || 0 == nRemainderE || 0 == nRemainderF || 0 == nRemainderG) return true;
	nDigit = nDigitCopy;
	// check 67, 71, 73, 79, 83, 89, 97
	do
	{
		nVal = pnDigits[nDigit];
		nRemainderA = (((nVal|nRemainderA)%67)<<_DIGIT_SIZE_IN_BITS);
		nRemainderB = (((nVal|nRemainderB)%71)<<_DIGIT_SIZE_IN_BITS);
		nRemainderC = (((nVal|nRemainderC)%73)<<_DIGIT_SIZE_IN_BITS);
		nRemainderD = (((nVal|nRemainderD)%79)<<_DIGIT_SIZE_IN_BITS);
		nRemainderE = (((nVal|nRemainderE)%83)<<_DIGIT_SIZE_IN_BITS);
		nRemainderF = (((nVal|nRemainderF)%89)<<_DIGIT_SIZE_IN_BITS);
		nRemainderG = (((nVal|nRemainderG)%97)<<_DIGIT_SIZE_IN_BITS);
	}
	while (0 != nDigit--);
	return (0 == nRemainderA || 0 == nRemainderB || 0 == nRemainderC || 0 == nRemainderD || 0 == nRemainderE || 0 == nRemainderF || 0 == nRemainderG);
}

// does Miller-Rabin primality testing
// from wikipedia:
/*
Miller–Rabin test

The algorithm can be written in pseudocode as follows. The parameter k determines the accuracy of the test. The greater the number of rounds, the more accurate the result.[6]

Input #1: n > 2, an odd integer to be tested for primality
Input #2: k, the number of rounds of testing to perform
Output: “composite” if n is found to be composite, “probably prime” otherwise

let s > 0 and d odd > 0 such that n-1 = 2*(sd)  # by factoring out powers of 2 from n-1
repeat k times:
	a <- random(2, n - 2)  # n is always a probable prime to base 1 and n ? 1
	x <- a^d mod n
	repeat s times:
		y <- x^2 mod n
		if y = 1 and x != 1 and x != n-1 then  # nontrivial square root of 1 modulo n
			return “composite”
		x <- y
	if y != 1 then
		return “composite”
return “probably prime”

In choosing the number of Miller-Rabin tests to do to accept a number as a prime, 20 is HIGHLY conservative.
On the other hand most numbers tested won't be prime, so the extra work amortizes out well.
Checking 20266 numbers not divisible by 2, 3, or 5 using Miller-Rabin:
20266 took 1 Miller-Rabin tests to reject
0 took 2 Miller-Rabin tests to reject
0 took 3 Miller-Rabin tests to reject
0 took 4 Miller-Rabin tests to reject
0 took 5 Miller-Rabin tests to reject
0 took 6 Miller-Rabin tests to reject
0 took 7 Miller-Rabin tests to reject
0 took 8 Miller-Rabin tests to reject
0 took 9 Miller-Rabin tests to reject
0 took 10 Miller-Rabin tests to reject
0 took 11 Miller-Rabin tests to reject
0 took 12 Miller-Rabin tests to reject
0 took 13 Miller-Rabin tests to reject
0 took 14 Miller-Rabin tests to reject
0 took 15 Miller-Rabin tests to reject
0 took 16 Miller-Rabin tests to reject
0 took 17 Miller-Rabin tests to reject
0 took 18 Miller-Rabin tests to reject
0 took 19 Miller-Rabin tests to reject
0 took 20 Miller-Rabin tests to reject
*/
unsigned int CRSADecrypt::s_nTestsToReject[c_nMaxMillerRabinTests] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
bool CRSADecrypt::ProbablyPrime(CBigInteger &nNumber)
{
	size_t nBitShift, j;
	CRandomGenerator cGenerator;
	CBigInteger      nLowerBound, nUpperBound, nWitness, nPower, nNMinusOne, nOne, nD, *pPower, *pWitness, *pSwap;
	// note we don't call ProbablyPrime with numbers that are small -- under 3 BYTEs in size
	if (DivisibleBySmallPrime(nNumber))
	{
		return false;
	}
	CModularArithmeticBox nBox(nNumber, false);
	nLowerBound.SetFromHexString("2");
	nOne.SetFromHexString("1");
	nNMinusOne = nNumber;
	nNMinusOne -= 1;
	nUpperBound = nNMinusOne;
	nUpperBound -= 1;
	nBitShift = StripPowerOf2(nNMinusOne, nD);
	for (int i=0; i<c_nMaxMillerRabinTests; i++)
	{
		// generate random number in range (2, n-2)
		cGenerator.RandomInRange(nLowerBound, nUpperBound, nWitness);
		pWitness = &nWitness;
		pPower   = &nPower;
		nBox.Power(pWitness, &nD, pPower);
		nWitness = nPower;
		for (j=0; j<nBitShift; j++)
		{
			pSwap    = pPower;
			pPower   = pWitness;
			pWitness = pSwap;
			nBox.Square(pWitness, pPower);
			if (nOne == *pPower && nOne != *pWitness && nNMinusOne != *pWitness)
			{
				s_nTestsToReject[i]++;
				return false;
			}
		}
		if (nOne != *pPower)
		{
			s_nTestsToReject[i]++;
			return false;
		}
	}
	return true;
}

size_t CRSADecrypt::StripPowerOf2(CBigInteger &nNumber, CBigInteger &nFactor)
{
	size_t nBitShift;
	nBitShift = 0;
	for (int i=0; i<nNumber.GetSize(); i++)
	{
		for (int j=0; j<_DIGIT_SIZE_IN_BITS; j++)
		{
			if(0 != (nNumber.GetValue()[i]&(1<<j)))
			{
				// found first set bit
				i = nNumber.GetSize(); // break out of outer loop, too
				break;
			}
			nBitShift++;
		}
	}
	nNumber.CopyShiftRight(nFactor, nBitShift);
	return nBitShift;
}

void CRSADecrypt::GetOddMultipleOf15Plus2(size_t nSizeInBYTEs, CBigInteger &nMultipleOf15Plus2)
{
	// generate an odd number 4 bits smaller than desired and multiply it by 15 as our starting point
	CRandomGenerator cGenerator;
	size_t           nBitsDesired = (nSizeInBYTEs<<3) - 4;
	size_t           nDigits      = nBitsDesired/_DIGIT_SIZE_IN_BITS;
	size_t           nBits        = nBitsDesired%_DIGIT_SIZE_IN_BITS;
	cGenerator.RandomBits(nDigits, nBits, true, nMultipleOf15Plus2);
	nMultipleOf15Plus2.GetValue()[0] = nMultipleOf15Plus2.GetValue()[0]|1; // force odd
	// note guaranteed no overflow when multiply by 15 by way base number was generated
	DOUBLEDIGIT nCarry = 2, nVal; // start with carry of 2 -- want <multiple of 15> + 2
	for (size_t i = 0; i < nMultipleOf15Plus2.GetSize(); i++)
	{
		nVal                            = ((DOUBLEDIGIT) nMultipleOf15Plus2.m_pnValue[i])*15 + nCarry;
		nCarry                          = nVal>>_DIGIT_SIZE_IN_BITS;
		nMultipleOf15Plus2.m_pnValue[i] = nVal;
	}
}

// Note that if a number is a multiple of 15, it is not prime.  Force our
// base number n to be an odd multiple of 15; then we know that
// none of (n+2, n+4, n+8, n+14, n+16, n+22, n+26, n+28) are divisible
// by 2, 3, or 5 -- saving a bit of time checking
// Picking an odd multiple of 15 then checking each number from this base point in turn which is not a multiple of 2, 3, or 5 is
// guaranteed to find a prime eventually, but has the disadvantage that it is more likely to find some primes than others -- e.g,
// the second value in a prime pair will NEVER be found.
// If we just pick a random number which is not a multiple of 2, 3, or 5 until we find a prime we get a more even distribution --
// but the algorithm is not guaranteed to terminate (and in fact might be guaranteed NOT to terminate in some cases if we are
// looking for a really big prime -- cycle through the random number generator's repetoire), and it is a little slower to pick
// a new random number than to just add 2, 4, or 6 to an existing value.
// If bForceUniformDistribution is set, we use the latter method; otherwise, we use the former.
// Function returns the count of numbers tested
const unsigned int c_nOffsets[8] = { 0, 2, 6, 12, 14, 20, 24, 26 };
size_t CRSADecrypt::GetOddPrime(CBigInteger &nNumber, size_t nBYTEsDesired, bool bForceUniformDistribution, bool bPrintPrimeToScreen)
{
	bool   bFirstPass = true;
	size_t nOffset = 0;
	if(nBYTEsDesired<3)
	{
		nNumber.Reserve(1);
		nNumber.SetSize(1);
		if(nBYTEsDesired<2) nNumber.GetValue()[0] = c_pnOneBYTEPrimes[rand()%c_nNumOneBYTEPrimes];
		else                nNumber.GetValue()[0] = c_pnTwoBYTEPrimes[rand()%c_nNumTwoBYTEPrimes];
	}
	else
	{
		// generate an odd number 4 bits smaller than desired and multiply it by 15 as our starting point
		if (bForceUniformDistribution)
		{
			do
			{
				nOffset++;
				GetOddMultipleOf15Plus2(nBYTEsDesired, nNumber);
				nNumber += c_nOffsets[CRandomGenerator::DefaultRandomBYTE()&7];
			}
			while(!ProbablyPrime(nNumber));
		}
		else
		{
			GetOddMultipleOf15Plus2(nBYTEsDesired, nNumber);
			nOffset = GetNextOddPrime(nNumber);
		}
	}
	if(bPrintPrimeToScreen)
	{
		printf("(decimal): ");
		nNumber.PrintDecimalToFile();
		printf("(hex):     ");
		nNumber.PrintHexToFile();
	}
	return nOffset;
}

// Assumes start with an odd multiple of 15.  Cycles through the 60-long stretch
// (2*3*5), checking those numbers that are not multiples of 2, 3, or 5 ONLY
size_t CRSADecrypt::GetNextOddPrime(CBigInteger &nNumber)
{
	unsigned int nTime, nOffset;
	nOffset = 1;
	nTime = ::GetTickCount();
	do
	{
		// base + 2
		if (ProbablyPrime(nNumber)) break;
		// base + 4
		nOffset++;
		nNumber += 2;
		if (ProbablyPrime(nNumber)) break;
		// base + 8
		nOffset++;
		nNumber += 4;
		if (ProbablyPrime(nNumber)) break;
		// base + 14
		nOffset++;
		nNumber += 6;
		if (ProbablyPrime(nNumber)) break;
		// base + 16
		nOffset++;
		nNumber += 2;
		if (ProbablyPrime(nNumber)) break;
		// base + 22
		nOffset++;
		nNumber += 6;
		if (ProbablyPrime(nNumber)) break;
		// base + 26
		nOffset++;
		nNumber += 4;
		if (ProbablyPrime(nNumber)) break;
		// base + 28
		nOffset++;
		nNumber += 2;
		if (ProbablyPrime(nNumber)) break;
		// back to base + 2
		nOffset++;
		nNumber += 4;
	}
	while(true);
	return nOffset;
}

CRSADecrypt::CRSADecrypt(CBigInteger &nPowerP,
		  				 CBigInteger &nPowerQ,
						 CBigInteger &nP,
						 CBigInteger &nQ,
						 CBigInteger &nInverseQ,
						 CBigInteger &nPublicPower,
						 CBigInteger &nModulus,
	                     bool        bProtectAgainstTimingAttacks) : CRSAEncrypt(nPublicPower, nModulus),
	                                                                 m_BoxP(nPowerP, nP, bProtectAgainstTimingAttacks),
	                                                                 m_BoxQ(nPowerQ, nQ, bProtectAgainstTimingAttacks)
{
	m_q        = nQ;
	m_qInverse = nInverseQ;
}

CRSADecrypt *CRSADecrypt::GetDecrypt(CBigInteger &p, CBigInteger &q, CBigInteger &publicPower, CArithmeticBox &cBox, bool bProtectAgainstTimingAttacks)
{
	CBigInteger nModulus, privatePower, powerP, powerQ, inverseQ, pMinus1, qMinus1, gcd, lcm, work;
	// this gives us the modulus...  almost: modulus is product of p and q
	if (eOperationSucceeded != cBox.Multiply(p, q, nModulus)) return NULL;
	// want the first nonzero BYTE of the modulus to be at least 16: want some spare bits to dump junk in for greater security
	// Note that the first DIGIT of nModulus is guaranteed to be nozero
	int nShift = _DIGIT_SIZE_IN_BITS - 8;
	DIGIT nFirstDigit = nModulus.GetValue()[nModulus.GetSize()-1];
	while(0==(nFirstDigit>>nShift)) nShift -=8;
	if((nFirstDigit>>nShift) < 16)
	{
		return NULL;
	}
	// need lcm(p-1, q-1) to get private power from public power
	if (!(pMinus1=p))
	{
		return NULL;
	}
	if (!(qMinus1=q))
	{
		return NULL;
	}
	pMinus1 -= 1;
	qMinus1 -= 1;
	if (eOperationSucceeded != cBox.GCD(pMinus1, qMinus1, gcd))
	{
		return NULL;
	}
	if (eOperationSucceeded != cBox.Divide(pMinus1, gcd, work, lcm))
	{
		return NULL;
	}
	if (eOperationSucceeded != cBox.Multiply(work, qMinus1, lcm))
	{
		return NULL;
	}
	// now that we have the least common multiple of p-1 and q-1, we can compute the private power:
	// the multiplicative inverse of the public power mod LCM
	CModularArithmeticBox cModularBoxLCM(lcm, false);
	CModularArithmeticBox cModularBoxP(p, false);
	if (eOperationSucceeded != cModularBoxLCM.MultiplicativeInverse(&publicPower, &privatePower))
	{
		return NULL;
	}
	// get the smaller keys used for decryption
	if (eOperationSucceeded != cBox.Divide(privatePower, pMinus1, work, powerP)) // note we only care about the remainder of the divide
	{
		return NULL;
	}
	if (eOperationSucceeded != cBox.Divide(privatePower, qMinus1, work, powerQ)) // note we only care about the remainder of the divide
	{
		return NULL;
	}
	if (eOperationSucceeded != cModularBoxP.MultiplicativeInverse(&q, &inverseQ))
	{
		return NULL;
	}
	return new CRSADecrypt(powerP, powerQ, p, q, inverseQ, publicPower, nModulus, bProtectAgainstTimingAttacks);
}

void CRSADecrypt::PrintPrimes(bool bHex)
{
	if (bHex)
	{
		m_BoxP.GetModulus()->PrintHexToFile();
		m_BoxQ.GetModulus()->PrintHexToFile();
	}
	else
	{
		m_BoxP.GetModulus()->PrintDecimalToFile();
		m_BoxQ.GetModulus()->PrintDecimalToFile();
	}
}

/*
From Wikipedia:
"The numbers p and q should not be "too close", lest the Fermat factorization for n be successful. If p ? q is less than 2n^(1/4) (n = p*q, which even for "small"
 1024-bit values of n is 3×10^77), solving for p and q is trivial. Furthermore, if either p ? 1 or q ? 1 has only small prime factors, n can be factored quickly
 by Pollard's p ? 1 algorithm, and hence such values of p or q should be discarded."
 p-1, q-1 only small prime factors: looks like this is obsolete?  https://en.wikipedia.org/wiki/Pollard%27s_p_%E2%88%92_1_algorithm
*/
bool CRSADecrypt::TooClose(CBigInteger &p, CBigInteger &q, CArithmeticBox &cBox)
{
	CBigInteger nDiff;
	cBox.Subtract(p, q, nDiff);
	return (nDiff.GetSize() < 2*(max(p.GetSize(),q.GetSize())>>1)); // slightly conservative
}

bool CRSADecrypt::AllSmallPrimeFactors(CBigInteger &nNumber)
{
	CBigInteger nWorkingVal;
	DOUBLEDIGIT nRemainder, nDiv, nPrime;
	size_t      nDigits, i;
	return false; // obsolete?  https://en.wikipedia.org/wiki/Pollard%27s_p_%E2%88%92_1_algorithm
	DIGIT       *pDiv = (DIGIT *) malloc(sizeof(DIGIT)*nNumber.GetSize()), *pVal, *pHold;

	// first, rip out 2 as a factor
	StripPowerOf2(nNumber, nWorkingVal);
	nDigits = nWorkingVal.GetSize();
	pVal    = nWorkingVal.GetValue();
	// Note we have already stripped out 2 with a bitshift, so start with 3 at index 1
	for(int j=1; j<c_nNumOneBYTEPrimes + c_nNumTwoBYTEPrimes; j++)
	{
		nPrime = (j<c_nNumOneBYTEPrimes) ? c_pnOneBYTEPrimes[j] : c_pnTwoBYTEPrimes[j-c_nNumOneBYTEPrimes];
		// divide by nPrime so long as it is a factor -- i.e, remainder is 0
		do
		{
			nRemainder = 0;
			i          = nDigits-1;
			do
			{
				nDiv       = pVal[i] | nRemainder;
				nRemainder = (nDiv%nPrime)<<_DIGIT_SIZE_IN_BITS;
				pDiv[i]    = nDiv/nPrime;
			}
			while(0 != i--);
			if(0!=nRemainder) break;
			// nPrime divides it evenly if we get to here
			pHold = pDiv;
			pDiv  = pVal;
			pVal  = pHold;
			if(0==pVal[nDigits-1]) nDigits--;
		}
		while(true);
	}
	free(pDiv);
	return ((1==nDigits) && (1==*pVal));
}