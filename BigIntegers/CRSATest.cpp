#include "CRSATest.h"
#include "..\BigIntegers\CRandomGenerator.h"
#include "..\RSA\RSAEncryptor.h"

CRSATest::CRSATest()
{
	m_cPrimeSieve             = (char *) malloc(c_nOneMillion);
	m_pnKnownOddPrimes        = (unsigned int *) malloc(sizeof(unsigned int)*82025); // actually 82024
	m_nNumKnownOddPrimes      = 0;
	m_pnKnownOddPrimes[82024] = 0;
	// compute the primes to 1,000,000 -- makes validating ProbablyPrime easier
	// know about 2; just check odd numbers
	for(int i=1;i<c_nOneMillion;i+=2) m_cPrimeSieve[i] = 1;
	for(int i=3;i<c_nOneMillion;i+=2)
	{
		if(1==m_cPrimeSieve[i])
		{
			m_pnKnownOddPrimes[m_nNumKnownOddPrimes++] = i;
			for(int j=3*i; j<c_nOneMillion; j+=2*i) m_cPrimeSieve[j] = 0;
		}
	}
	if(0!=m_pnKnownOddPrimes[82024]) printf("miscount!\n");
}

bool CRSATest::BruteForcePrimeCheck(CBigInteger &nNumber, bool bShowFactors)
{
	CArithmeticBox cBox;
	CBigInteger    nDivisor, nXDivY, nRemainder;
	// first, check the known primes
	nDivisor.Reserve(2);
	for(int i=0; i<m_nNumKnownOddPrimes; i++)
	{
		((DOUBLEDIGIT *) nDivisor.GetValue())[0] = m_pnKnownOddPrimes[i];
		nDivisor.SetSize((nDivisor.GetValue()[1]==0) ? 1 : 2);
		cBox.Divide(nNumber, nDivisor, nXDivY, nRemainder);
		if (0 == nRemainder.GetSize())
		{
			cBox.Multiply(nDivisor, nXDivY, nRemainder);
			if (nRemainder != nNumber)
			{
				printf("major OOPs\n");
				printf("factors:\n");
				nXDivY.PrintDecimalToFile();
				nDivisor.PrintDecimalToFile();
				printf("Product:\n");
				nRemainder.PrintDecimalToFile();
				printf("original:\n");
				nNumber.PrintDecimalToFile();
			}
			else if (bShowFactors)
			{
				printf("factors:\n");
				nXDivY.PrintDecimalToFile();
				nDivisor.PrintDecimalToFile();
			}
			return false;
		}
		if (nXDivY < nDivisor)         return true;
	}
	// ran out of known primes; check more odd numbers until we find a divisor or know it's prime
	do
	{
		nDivisor += 2;
		cBox.Divide(nNumber, nDivisor, nXDivY, nRemainder);
		if(0==nRemainder.GetSize())
		{
			cBox.Multiply(nDivisor, nXDivY, nRemainder);
			if (nRemainder != nNumber)
			{
				printf("major OOPs\n");
				printf("factors:\n");
				nXDivY.PrintDecimalToFile();
				nDivisor.PrintDecimalToFile();
				printf("Product:\n");
				nRemainder.PrintDecimalToFile();
				printf("original:\n");
				nNumber.PrintDecimalToFile();
			}
			else if (bShowFactors)
			{
				printf("factors:\n");
				nXDivY.PrintDecimalToFile();
				nDivisor.PrintDecimalToFile();
			}
			return false;
		}
		if(nXDivY<nDivisor)
		{
			return true;
		}
	}
	while(true);
}

bool CRSATest::TestProbablyPrime()
{
	CRandomGenerator generator;
	CBigInteger      number;
	unsigned int     nNumberSmall;
	bool             bProbablyPrime, bActuallyPrime;
	// small, fast tests
	printf("Testing ProbablyPrime:\n  small tests:\n");
	for(int i=0;i<10000;i++)
	{
		generator.RandomBits(20/_DIGIT_SIZE_IN_BITS, 20%_DIGIT_SIZE_IN_BITS, false, number); // 20-bit number -- one million
		number.GetValue()[0] |= 1; // force odd
		bProbablyPrime = CRSADecrypt::ProbablyPrime(number);
		nNumberSmall   = number.GetValue()[0];
		if(2==number.GetSize()) nNumberSmall |= (number.GetValue()[1]<<(sizeof(DIGIT)<<3));
		bActuallyPrime = (1==m_cPrimeSieve[nNumberSmall]);
		if(bActuallyPrime != bProbablyPrime)
		{
			printf("Value: %u\tPrime: %s Probably prime: %s\n", nNumberSmall, ((bActuallyPrime) ? "yes" : "no"), ((bProbablyPrime) ? "yes" : "no"));
			return false;
		}
	}
	printf("  ...  small tests PASSED!\n");
	// large, slower tests
	printf("  large tests:\n");
	for(int i=0; i<100; i++)
	{
		generator.RandomBits(56/_DIGIT_SIZE_IN_BITS, 56%_DIGIT_SIZE_IN_BITS, false, number); // 56-bit number -- at least 2 digits
		number.GetValue()[0] |= 1; // force odd
		bProbablyPrime = CRSADecrypt::ProbablyPrime(number);
		bActuallyPrime = BruteForcePrimeCheck(number);
		if (bActuallyPrime != bProbablyPrime)
		{
			printf("value (decimal): ");
			number.PrintDecimalToFile();
			printf("value (hex):     ");
			number.PrintHexToFile();
			printf("Probably prime: %s\tActually prime: %s\n", bProbablyPrime ? "yes" : "no", bActuallyPrime ? "yes" : "no");
			if (!bActuallyPrime) BruteForcePrimeCheck(number, true);
			return false;
		}
	}
	printf("  ...  large tests PASSED!\n");
	return true;
}

bool CRSATest::TestRSA(bool bProtectAgainstTimingAttacks)
{
	int                i;
	size_t             nEncryptedMessageLength, nDecryptedMessageLength, nPadding;
	char               *pBigMessage;
	const unsigned int c_nSpecialCases    = 2;
	const char         *szTextToEncrypt   = "Now is the time for all good men to come to the aid of their party.";
	const char         *pszSpecialPrimes[2*c_nSpecialCases] = {"7FCDF484851267914942EE6C8F101100B6A400FB0282C3675E5C94C6E949117FF84D97", "AA39D49A5E743225035980582F85166127ED78EF1A643DABAEE74AFD9B",
	                                                           "871028845C345F857D82676016744D54F1ED3D03C074F3BDCF098F13920096CC6B3316C034B5","80DA9A842C2BD1DDBB6D09EA0762E1BDEEADD75177BDDD3E6DFF"};
	char               *pEncryptedMessage = NULL, *pDecryptedMessage = NULL;
	size_t             nTextLength        = 68;
	CRSADecrypt        *pDecryptor        = CRSADecrypt::GetDecrypt(13, false, bProtectAgainstTimingAttacks);
	bool               bTestWorked        = false;
	printf("Testing RSA: small\n");
	if(!pDecryptor->Encrypt(szTextToEncrypt, nTextLength, pEncryptedMessage, nEncryptedMessageLength, nPadding))
	{
		printf("Encryption failed\n");
		goto exit;
	}
	if(!pDecryptor->Decrypt(pEncryptedMessage, nEncryptedMessageLength, nPadding, pDecryptedMessage, nDecryptedMessageLength))
	{
		printf("Decryption failed\n");
		goto exit;
	}
	if (nDecryptedMessageLength != nTextLength)
	{
		printf("Botched text length: %i original, %i decrypted\n", nTextLength, nDecryptedMessageLength);
		goto exit;
	}
	for(size_t i=0; i<nTextLength; i++)
	{
		if (szTextToEncrypt[i] != pDecryptedMessage[i])
		{
			printf("Botched encrypt/decrypt: %i vs %i\n", szTextToEncrypt[i], pDecryptedMessage[i]);
			goto exit;
		}
	}
	printf("    passed!\n");
	delete pDecryptor;
	free(pEncryptedMessage);
	free(pDecryptedMessage);
	pEncryptedMessage = NULL;
	pDecryptedMessage = NULL;
	// and a larger test
	printf("Testing RSA: large\n");
	pDecryptor  = CRSADecrypt::GetDecrypt(512, false, bProtectAgainstTimingAttacks);
	nTextLength = 64000;
	pBigMessage = (char *) malloc(nTextLength);
	// try a leading 0
	pBigMessage[0] = 0;
	for(i=1; i<nTextLength/3; i++)
	{
		pBigMessage[i] = 'a' + i%26;
    }
	// put some 0s in the middle
	for(; i<2*nTextLength/3; i++)
	{
		pBigMessage[i] = 0;
	}
	for(; i<nTextLength; i++)
	{
		pBigMessage[i] = 'a' + i%26;
    }
	if (!pDecryptor->Encrypt(pBigMessage, nTextLength, pEncryptedMessage, nEncryptedMessageLength, nPadding))
	{
		printf("Encryption failed\n");
		goto exit;
	}
	if (!pDecryptor->Decrypt(pEncryptedMessage, nEncryptedMessageLength, nPadding, pDecryptedMessage, nDecryptedMessageLength))
	{
		printf("Decryption failed\n");
		goto exit;
	}
	if (nDecryptedMessageLength != nTextLength)
	{
		printf("Botched text length: %i original, %i decrypted\n", nTextLength, nDecryptedMessageLength);
		goto exit;
	}
	for (size_t i = 0; i < nTextLength; i++)
	{
		if (pBigMessage[i] != pDecryptedMessage[i])
		{
			printf("Botched encrypt/decrypt: %i vs %i\n", pBigMessage[i], pDecryptedMessage[i]);
			goto exit;
		}
	}
	// large encryptor, small message
	free(pEncryptedMessage);
	free(pDecryptedMessage);
	pEncryptedMessage = NULL;
	pDecryptedMessage = NULL;
	nTextLength = 1;
	if (!pDecryptor->Encrypt(pBigMessage, nTextLength, pEncryptedMessage, nEncryptedMessageLength, nPadding))
	{
		printf("Encryption failed\n");
		goto exit;
	}
	if (!pDecryptor->Decrypt(pEncryptedMessage, nEncryptedMessageLength, nPadding, pDecryptedMessage, nDecryptedMessageLength))
	{
		printf("Decryption failed\n");
		goto exit;
	}
	if (nDecryptedMessageLength != nTextLength)
	{
		printf("Botched text length: %i original, %i decrypted\n", nTextLength, nDecryptedMessageLength);
		goto exit;
	}
	for (size_t i = 0; i < nTextLength; i++)
	{
		if (pBigMessage[i] != pDecryptedMessage[i])
		{
			printf("Botched encrypt/decrypt: %i vs %i\n", pBigMessage[i], pDecryptedMessage[i]);
			goto exit;
		}
	}
	printf("    passed!\n");
	free(pBigMessage);
	// Some specific decryptors that have caused Troubles in the past
	for(int i=0; i<c_nSpecialCases; i++)
	{
		CBigInteger nPrimeP(pszSpecialPrimes[2*i]), nPrimeQ(pszSpecialPrimes[2*i + 1]);
		delete pDecryptor;
		free(pEncryptedMessage);
		free(pDecryptedMessage);
		pEncryptedMessage = NULL;
		pDecryptedMessage = NULL;
		pDecryptor = CRSADecrypt::GetDecrypt(nPrimeP, nPrimeQ, bProtectAgainstTimingAttacks);
		if (!pDecryptor->Encrypt(szTextToEncrypt, nTextLength, pEncryptedMessage, nEncryptedMessageLength, nPadding))
		{
			printf("Encryption failed\n");
			goto exit;
		}
		if (!pDecryptor->Decrypt(pEncryptedMessage, nEncryptedMessageLength, nPadding, pDecryptedMessage, nDecryptedMessageLength))
		{
			printf("Decryption failed\n");
			goto exit;
		}
		if (nDecryptedMessageLength != nTextLength)
		{
			printf("Botched text length: %i original, %i decrypted\n", nTextLength, nDecryptedMessageLength);
			goto exit;
		}
		for (size_t j = 0; j < nTextLength; j++)
		{
			if (szTextToEncrypt[j] != pDecryptedMessage[j])
			{
				printf("Botched encrypt/decrypt: %i vs %i\n", szTextToEncrypt[j], pDecryptedMessage[j]);
			//	goto exit;
			}
		}
    }
	bTestWorked = true;
exit:
	delete pDecryptor;
	free(pEncryptedMessage);
	free(pDecryptedMessage);
	pEncryptedMessage = NULL;
	pDecryptedMessage = NULL;
	return bTestWorked;
}
/*
16-bit DIGITs
Finding 128 BYTE prime:
  Use get next: 859 milliseconds (tried 141 numbers) -- 6.092198 ms/try
  Use uniform:  469 milliseconds (tried 51 numbers) -- 9.196078 ms/try
Finding 256 BYTE prime:
  Use get next: 9641 milliseconds (tried 330 numbers) -- 29.215151 ms/try
  Use uniform:  4734 milliseconds (tried 144 numbers) -- 32.875000 ms/try
Finding 512 BYTE prime:
  Use get next: 342328 milliseconds (tried 2212 numbers) -- 154.759491 ms/try
  Use uniform:  78828 milliseconds (tried 432 numbers) -- 182.472229 ms/try
Finding 1024 BYTE prime:
  Use get next: 4607141 milliseconds (tried 5216 numbers) -- 883.270874 ms/try
  Use uniform:  2919078 milliseconds (tried 3700 numbers) -- 788.940002 ms/try

32-bit DIGITs:
Finding 128 BYTE prime:
  Use get next: 1047 milliseconds (tried 660 numbers) -- 1.586364 ms/try
  Use uniform:  281 milliseconds (tried 164 numbers) -- 1.713415 ms/try
Finding 256 BYTE prime:
  Use get next: 6562 milliseconds (tried 767 numbers) -- 8.555410 ms/try
  Use uniform:  2516 milliseconds (tried 266 numbers) -- 9.458647 ms/try
Finding 512 BYTE prime:
  Use get next: 36141 milliseconds (tried 646 numbers) -- 55.945820 ms/try
  Use uniform:  11187 milliseconds (tried 218 numbers) -- 51.316513 ms/try
Finding 1024 BYTE prime:
  Use get next: 226172 milliseconds (tried 747 numbers) -- 302.773773 ms/try
  Use uniform:  29703 milliseconds (tried 61 numbers) -- 486.934418 ms/try
*/
void CRSATest::PerfTestGetPrime()
{
	unsigned int c_nPrimeSizeInBYTEsBase = 128;
	unsigned int c_nPrimeSizeInBYTEsMax  = 1024;
	CBigInteger  nPrimeStartingPoint, nPrimeStartingPointCopy;
	unsigned int nTime;
	size_t       nCount;
	for (size_t nBYTEs = c_nPrimeSizeInBYTEsBase; nBYTEs <= c_nPrimeSizeInBYTEsMax; nBYTEs *= 2)
	{
		printf("Finding %i BYTE prime:\n", nBYTEs);
		CRSADecrypt::GetOddMultipleOf15Plus2(nBYTEs, nPrimeStartingPoint);
		nPrimeStartingPointCopy = nPrimeStartingPoint;
		nTime  = ::GetTickCount();
		nCount = CRSADecrypt::GetNextOddPrime(nPrimeStartingPoint);
		nTime  = ::GetTickCount() - nTime;
		printf("  Use get next: %u milliseconds (tried %i numbers) -- %f ms/try\n", nTime, nCount, ((float) nTime)/nCount);
		nTime  = ::GetTickCount();
		nCount = CRSADecrypt::GetOddPrime(nPrimeStartingPoint, nBYTEs, true);
		nTime  = ::GetTickCount() - nTime;
		printf("  Use uniform:  %u milliseconds (tried %i numbers) -- %f ms/try\n", nTime, nCount, ((float)nTime)/nCount);
	}
	// shows the count of Miller-Rabin primality tests needed to reject each prospect that was rejected.  Overwhelmingly the answer is "1"
	CRSADecrypt::PrintTestsToReject();
}

void CRSATest::PerfTestDivisibleBySmallPrime()
{
	const unsigned int c_nNumsToCheck = 10000000;
	const unsigned int c_nBaseBitSize = 2048;
	const unsigned int c_nMaxBitSize  = 16384;
	CRandomGenerator   generator;
	CBigInteger        number;
	unsigned int       nTime;
	bool               bAllDivisible = true; // so compiler doesn't optimize out the calls

	for(int nBits=c_nBaseBitSize; nBits<=c_nMaxBitSize; nBits *= 2)
	{
		generator.RandomBits(nBits/_DIGIT_SIZE_IN_BITS, nBits%_DIGIT_SIZE_IN_BITS, false, number);
		number.GetValue()[0] |= 1; // force odd
		nTime = ::GetTickCount();
		for (int i=0; i<c_nNumsToCheck; i++)
		{
			bAllDivisible &= CRSADecrypt::DivisibleBySmallPrime(number);
			number += 2;
		}
		nTime = ::GetTickCount() - nTime;
		printf("Time to check %i consecutive odd numbers of %i bits for divisibility by small primes: %i milliseconds\n", c_nNumsToCheck, nBits, nTime);
	}
	if (bAllDivisible) printf("Well THAT was unexpected\n");
}

/*
16-bit DIGITs
Time to check 1000 nonconsecutive odd numbers of 256 bits each for primality: 188 milliseconds
Time to check 1000 nonconsecutive odd numbers of 512 bits each for primality: 1234 milliseconds
Time to check 1000 nonconsecutive odd numbers of 1024 bits each for primality: 5141 milliseconds
Time to check 1000 nonconsecutive odd numbers of 2048 bits each for primality: 25141 milliseconds
Time to check 1000 nonconsecutive odd numbers of 4096 bits each for primality: 155859 milliseconds
Time to check 1000 nonconsecutive odd numbers of 8192 bits each for primality: 878656 milliseconds

32-bit DIGITs
Time to check 1000 nonconsecutive odd numbers of 256 bits each for primality: 62 milliseconds
Time to check 1000 nonconsecutive odd numbers of 512 bits each for primality: 297 milliseconds
Time to check 1000 nonconsecutive odd numbers of 1024 bits each for primality: 1734 milliseconds
Time to check 1000 nonconsecutive odd numbers of 2048 bits each for primality: 8063 milliseconds
Time to check 1000 nonconsecutive odd numbers of 4096 bits each for primality: 45297 milliseconds
Time to check 1000 nonconsecutive odd numbers of 8192 bits each for primality: 289328 milliseconds
*/
void CRSATest::PerfTestProbablyPrime()
{
	const unsigned int c_nNumsToCheck = 1000;
	CRandomGenerator   generator;
	CBigInteger        number;
	bool               bProbablyPrime, bActuallyPrime;
	unsigned int       nNumberSmall;
	unsigned int       nTime;
	unsigned int       nBaseBitSize = 256;
	unsigned int       nMaxBitSize  = 8192;
	for( ; nBaseBitSize<=nMaxBitSize; nBaseBitSize *= 2)
	{
		nTime = ::GetTickCount();
		for (int i=0; i<c_nNumsToCheck; i++)
		{
			generator.RandomBits(nBaseBitSize/_DIGIT_SIZE_IN_BITS, nBaseBitSize%_DIGIT_SIZE_IN_BITS, false, number);
			number.GetValue()[0] |= 1; // force odd
			bProbablyPrime = CRSADecrypt::ProbablyPrime(number);
		}
		printf("Time to check %i nonconsecutive odd numbers of %i bits each for primality: %i milliseconds\n", c_nNumsToCheck, nBaseBitSize, ::GetTickCount() - nTime);
	}
}

/*

16-bit DIGITs
All encrypt/decrypt tests use the same message of 100000 BYTEs
Using protection against timing attacks: false
Iterations for modulus of 64 BYTEs: 10000
Get encryptor milliseconds:   255318
Encryption milliseconds:      574343
Decryption milliseconds:      6849434

Iterations for modulus of 128 BYTEs: 1000
Get encryptor milliseconds:   273866
Encryption milliseconds:      91175
Decryption milliseconds:      2219366

Iterations for modulus of 256 BYTEs: 100
Get encryptor milliseconds:   278713
Encryption milliseconds:      14622
Decryption milliseconds:      739979

Iterations for modulus of 512 BYTEs: 10
Get encryptor milliseconds:   255141
Encryption milliseconds:      1920
Decryption milliseconds:      235751

Iterations for modulus of 1024 BYTEs: 1
Get encryptor milliseconds:   73625
Encryption milliseconds:      281
Decryption milliseconds:      65391

Using protection against timing attacks: true
Iterations for modulus of 64 BYTEs: 10000
Get encryptor milliseconds:   247465
Encryption milliseconds:      575968
Decryption milliseconds:      9114442

Iterations for modulus of 128 BYTEs: 1000
Get encryptor milliseconds:   279553
Encryption milliseconds:      91196
Decryption milliseconds:      2955391

Iterations for modulus of 256 BYTEs: 100
Get encryptor milliseconds:   261238
Encryption milliseconds:      14730
Decryption milliseconds:      997501

Iterations for modulus of 512 BYTEs: 10
Get encryptor milliseconds:   282967
Encryption milliseconds:      1969
Decryption milliseconds:      321079

Iterations for modulus of 1024 BYTEs: 1
Get encryptor milliseconds:   215891
Encryption milliseconds:      297
Decryption milliseconds:      89359

32-bit DIGITs
All encrypt/decrypt tests use the same message of 100000 BYTEs
Using protection against timing attacks: false
Iterations for modulus of 64 BYTEs: 10000
Get encryptor milliseconds:   101524
Encryption milliseconds:      166963
Decryption milliseconds:      2343563

Iterations for modulus of 128 BYTEs: 1000
Get encryptor milliseconds:   124218
Encryption milliseconds:      26754
Decryption milliseconds:      651513

Iterations for modulus of 256 BYTEs: 100
Get encryptor milliseconds:   102089
Encryption milliseconds:      4423
Decryption milliseconds:      215081

Iterations for modulus of 512 BYTEs: 10
Get encryptor milliseconds:   80717
Encryption milliseconds:      640
Decryption milliseconds:      71002

Iterations for modulus of 1024 BYTEs: 1
Get encryptor milliseconds:   89937
Encryption milliseconds:      94
Decryption milliseconds:      20891

Using protection against timing attacks: true
Iterations for modulus of 64 BYTEs: 10000
Get encryptor milliseconds:   94403
Encryption milliseconds:      166924
Decryption milliseconds:      3079408

Iterations for modulus of 128 BYTEs: 1000
Get encryptor milliseconds:   99941
Encryption milliseconds:      26685
Decryption milliseconds:      865483

Iterations for modulus of 256 BYTEs: 100
Get encryptor milliseconds:   107095
Encryption milliseconds:      4267
Decryption milliseconds:      286872

Iterations for modulus of 512 BYTEs: 10
Get encryptor milliseconds:   77391
Encryption milliseconds:      624
Decryption milliseconds:      94110

Iterations for modulus of 1024 BYTEs: 1
Get encryptor milliseconds:   182359
Encryption milliseconds:      94
Decryption milliseconds:      28109
*/
bool CRSATest::PerfTestRSA()
{
	printf("If you're not doing this in a retail build, you're not getting the best numbers\n");
	const unsigned int c_nMinModulusBytes = 64;
	const unsigned int c_nMaxModulusBytes = 1024;
	const unsigned int c_nMessageLength   = 100000;
	char         *pMessage;
	unsigned int nModulusBYTEs;
	CRSADecrypt  *pDecryptor;
	unsigned int nTimeGet, nTimeEncrypt, nTimeDecrypt, nTimeA, nTimeB;
	size_t       nEncryptedLength, nDecryptedLength, nPadding;
	char         *pEncrypted   = NULL, *pDecrypted = NULL;
	bool         bTestJustFine = true;
	int          nIterations   = 10000;
	pMessage = (char *) malloc(c_nMessageLength);
	for (int i=0; i<c_nMessageLength; i++)
	{
		pMessage[i] = 'a' + (i%26);
	}
	printf("All encrypt/decrypt tests use the same message of %i BYTEs\n", c_nMessageLength);
	for (int nTimingProt = 0; nTimingProt < 2; nTimingProt++)
	{
		bool bProtectAgainstTimingAttacks = (1==nTimingProt);
		printf("Using protection against timing attacks: %s\n", bProtectAgainstTimingAttacks ? "true" : "false");
		nIterations = 10000;
		for (nModulusBYTEs = c_nMinModulusBytes; nModulusBYTEs <= c_nMaxModulusBytes && bTestJustFine; nModulusBYTEs *= 2)
		{
			nTimeGet     = 0;
			nTimeEncrypt = 0;
			nTimeDecrypt = 0;
			printf("Iterations for modulus of %i BYTEs: %i\n", nModulusBYTEs, nIterations);
			for (int j = 0; j < nIterations && bTestJustFine; j++)
			{
				nTimeB = ::GetTickCount();
				do
				{
					pDecryptor = CRSADecrypt::GetDecrypt(nModulusBYTEs, true, bProtectAgainstTimingAttacks);
					if (NULL == pDecryptor) printf("Retrying\n");
				}
				while (NULL == pDecryptor);
				nTimeA   =  ::GetTickCount();
				nTimeGet += nTimeA - nTimeB;
				if (!pDecryptor->Encrypt(pMessage, c_nMessageLength, pEncrypted, nEncryptedLength, nPadding))
				{
					printf("Encryption failed\n");
					bTestJustFine = false;
				}
				else
				{
					nTimeB = ::GetTickCount();
					nTimeEncrypt += nTimeB - nTimeA;
					if (!pDecryptor->Decrypt(pEncrypted, nEncryptedLength, nPadding, pDecrypted, nDecryptedLength))
					{
						printf("Decryption failed\n");
						bTestJustFine = false;
					}
					else
					{
						nTimeDecrypt += ::GetTickCount() - nTimeB;
					}
				}
				// validate.  Might as well, though this is really at heart a perf test
				if (c_nMessageLength != nDecryptedLength)
				{
					printf("Bad decryption length\n");
					bTestJustFine = false;
				}
				else
				{
					for (size_t i = 0; i < c_nMessageLength; i++)
					{
						if (pDecrypted[i] != pMessage[i])
						{
							printf("Bad decryption.  %u of %u wrong\n", i, c_nMessageLength);
							bTestJustFine = false;
						}
					}
				}
				if (!bTestJustFine)
				{
					printf("Primes used for decryptor:\n");
					pDecryptor->PrintPrimes(true);
					printf("\n");
				}
				delete pDecryptor;
				free(pEncrypted);
				free(pDecrypted);
				pEncrypted = NULL;
				pDecrypted = NULL;
			}
			if (bTestJustFine)
			{

				printf("Get encryptor milliseconds:   %i\nEncryption milliseconds:      %u\nDecryption milliseconds:      %u\n\n", nTimeGet, nTimeEncrypt, nTimeDecrypt);
			}
			nIterations /= 10;
		}
	}
	free(pMessage);
	return bTestJustFine;
}

#if 0
// compare versions of divisible by small prime -- inactive
// Times from last test (largest small prime checked: 97 for all.  Might change; might be worthwhile to try even larger ones)
// Base: 9641 milliseconds
// B : 16453 milliseconds
// C : 14750 milliseconds
//
// DivisibleBySmallPrime_b, DivisibleBySmallPrime_c no longer compiled -- no use case.  Code retained (in inactive block) just in case

void CRSATest::PerfTestDivisibleBySmallPrime()
{
	const unsigned int c_nNumsToCheck = 10000000;
	const unsigned int c_nBaseBitSize = 2048;
	CRandomGenerator   generator;
	CBigInteger        number, nNumberCopy;
	unsigned int       nTimeA, nTimeB, nTimeC, nTimeD;
	bool               bAllDivisible = true; // so don't optimize out calls to DivisibleBySmallPrime

	generator.RandomBits(c_nBaseBitSize / _DIGIT_SIZE_IN_BITS, c_nBaseBitSize % _DIGIT_SIZE_IN_BITS, false, number);
	number.GetValue()[0] |= 1; // force odd
	nTimeA      = ::GetTickCount();
	nNumberCopy = number;
	for (int i = 0; i < c_nNumsToCheck; i++)
	{
		bAllDivisible &= CRSADecrypt::DivisibleBySmallPrime(nNumberCopy);
		nNumberCopy += 2;
	}
	nTimeB      = ::GetTickCount();
	nNumberCopy = number;
	for (int i = 0; i < c_nNumsToCheck; i++)
	{
		bAllDivisible &= CRSADecrypt::DivisibleBySmallPrime_b(nNumberCopy);
		nNumberCopy += 2;
	}
	nTimeC      = ::GetTickCount();
	nNumberCopy = number;
	for (int i = 0; i < c_nNumsToCheck; i++)
	{
		bAllDivisible &= CRSADecrypt::DivisibleBySmallPrime_c(nNumberCopy);
		nNumberCopy += 2;
	}
	nTimeD = ::GetTickCount();
	printf("Base: %i milliseconds\nB:   %i milliseconds\nC:   %i milliseconds\n", nTimeB - nTimeA, nTimeC - nTimeB, nTimeD - nTimeC);
	if (bAllDivisible) printf("Well THAT'S unexpected\n");
}
#endif