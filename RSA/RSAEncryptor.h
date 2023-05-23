#pragma once
#include "..\BigIntegers\BigIntegers.h"
#include "..\BigIntegers\ArithmeticBox.h"
#include "Encryptor.h"

// Implements RSA encryption/decryption
class __declspec(dllexport) CRSAEncrypt : IEncrypt
{
public:    // functions
	// If pEncryptedMessage is NULL, it will be allocated with sufficient memory for the encryption.  Uses malloc(); caller's resposibility to
	// free it when it is no longer needed.
	// If pEncryptedMessage is NOT null, it is assumed to have adequate space.  That can be found using SpaceNeededForEncryptedMessage, below
	virtual bool Encrypt(const char *pMessage, size_t nMessageLength, char *&pEncryptedMessage, size_t &nEncryptedMessageLength, size_t &nPadding);
	virtual size_t SpaceNeededForEncryptedMessage(size_t nMessageLength);
	// makes its own copy of the arguments; they can be reused without affecting the encryptor
	CRSAEncrypt(CBigInteger &nPublicPower, CBigInteger &nModulus );
public:    // variables
protected: // variables
	size_t                          m_nModulusBYTESize;
	int                             m_nLeadByteBitMask; // lead BYTE of each chunk topped off with random bits for greater security; mask makes
	                                                    // sure we don't set too many
	CFixedPowerModularArithmeticBox m_Box;
};

class __declspec(dllexport) CRSADecrypt : CRSAEncrypt, IDecrypt
{
	friend class CRSATest;
public:  // functions
	// messages will be encrypted in chunks (nDesiredModulusSizeInBYTEs-1) BYTEs long
	static CRSADecrypt *GetDecrypt(size_t nDesiredModulusSizeInBYTEs, bool bForceUniformPrimeDistribution, bool bProtectAgainstTimingAttacks);
	// get a decryptor constructed using the two passed primes (product -> modulus).  Primality NOT checked!
	// makes its own copy of the arguments; they can be reused without affecting the decryptor
	static CRSADecrypt *GetDecrypt(CBigInteger &primeP, CBigInteger &primeQ, bool bProtectAgainstTimingAttacks);
	~CRSADecrypt();
	// sets power, modulus to copies of the public keys.  Returns false in the (highly unusual) case of failure -- out of memory?
	bool GetPublicKeys(CBigInteger &nPublicPower, CBigInteger &nModulus);
	// prints the primes used to construct the object.  Used for debugging.
	// hexidecimal if bHex set; decimal otherwise
	void PrintPrimes(bool bHex);
	// If pDecryptedMessage is NULL, it will be allocated with sufficient memory for the decryption.  Uses malloc(); caller's resposibility to
	// free it when it is no longer needed.
	// If pDecryptedMessage is NOT null, it is assumed to have adequate space.  That can be found using SpaceNeededForDecryptedMessage, below
	virtual bool Decrypt(const char *pMessage, size_t nEncryptedMessageLength, size_t nPaddingBYTEs, char *&pDecryptedMessage, size_t &nMessageLength);
	virtual size_t SpaceNeededForDecryptedMessage(size_t nEncryptedMessageLength);
private: // functions
	CRSADecrypt(CBigInteger &nPowerP,
				CBigInteger &nPowerQ,
				CBigInteger &nP,
				CBigInteger &nQ,
				CBigInteger &nInverseQ,
				CBigInteger &nPublicPower,
				CBigInteger &nModulus,
		        bool        bProtectAgainstTimingAttacks);
	// gets a random number of the requested size whis is 2 more than an odd multiple of 15 (a reasonable prospect
	// for primality)
	static void GetOddMultipleOf15Plus2(size_t nSizeInBYTEs, CBigInteger &nMultipleOf15Plus2);
	// uses Miller-Rabine primality testing.  Note that it assumes -- without checking -- that the number passed is odd.
	// Not likely to be an issue: if the number's size in bits does not fit in a size_t, we may fail
	static bool ProbablyPrime(CBigInteger &nNumber);
	// sets nNumber to an odd (probably) prime number of the desired size in BITs.  Returns the offset from the starting point of the test --
	// useful for perf testing: gives an indication of how much ground was searched to find the prime
	static size_t GetOddPrime(CBigInteger &nNumber, size_t nBYTEsDesired, bool bForceUniformDistribution, bool bPrintPrimeToScreen = false);
	// GetNextOddPrime replaces the passed starting point with the first (probably) prime odd number at or after it
	// returns count of numbers checked.  By assumption the number pass is 2 more than an odd multiple of 15 -- not checked!
	static size_t GetNextOddPrime(CBigInteger &nNumber);
	// checks whether some small prime (hardwired) is a factor of the number passed.
	// NOTE: doesn't bother with 2, 3, or 5 -- the GetOddPrime function already avoids any multiple of THOSE
	static bool DivisibleBySmallPrime(const CBigInteger &nNumber);
	static CRSADecrypt *GetDecrypt(CBigInteger &nP, CBigInteger &nQ, CBigInteger &nPublicPower, CArithmeticBox &cBox, bool bProtectAgainstTimingAttacks);
	// if the primes p, q are too close to each other, the encryption is weak.  Get a new prime pair.
	static bool TooClose(CBigInteger &p, CBigInteger &q, CArithmeticBox &cBox);
	// whether number oinly has small prime factors -- in this case, just prime factors that can fit into 2 BYTEs.
	// Sufficient?
	static bool AllSmallPrimeFactors(CBigInteger &nNumber);
	// sets nFactor to nNumber divided by the largest possible power of 2, and returns that power
	static size_t StripPowerOf2(CBigInteger &nNumber, CBigInteger &nFactor);
	static void PrintTestsToReject()
	{
		for(int i=0;i<c_nMaxMillerRabinTests;i++)
		{
			printf("%i took %i Miller-Rabin tests to reject\n",s_nTestsToReject[i],i+1);
		}
	}
public:  // variables
private: // variables;
	static const unsigned int       c_nMaxMillerRabinTests = 20;
	// rather than use the base private power, use split private power from p, q (the factors of the modulus) and Chinese remainder
	// theorem to speed up decryption
	CBigInteger                     m_q, m_qInverse;
	CFixedPowerModularArithmeticBox m_BoxP, m_BoxQ;
	// counts how many Miller-Rabin tests were performed for each number deemed NOT to be prime
	static unsigned int             s_nTestsToReject[c_nMaxMillerRabinTests];
};