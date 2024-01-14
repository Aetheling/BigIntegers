#pragma once
#include "..\RSA\RSAEncryptor.h"
const unsigned int c_nOneMillion = 1024*1024;
class CRSATest
{
public:  // functions
	CRSATest();
	~CRSATest();
	bool TestProbablyPrime();
	bool TestRSA(bool bProtectAgainstTimingAttacks);

	void PerfTestDivisibleBySmallPrime();
	void PerfTestGetPrime();
	void PerfTestProbablyPrime();
	bool PerfTestRSA();
private: // functions
	bool BruteForcePrimeCheck(CBigInteger &nNumber, bool bShowFactors=false);
public:  // data
private: // data
	char         *m_cPrimeSieve;
	unsigned int *m_pnKnownOddPrimes;
	unsigned int m_nNumKnownOddPrimes;
};