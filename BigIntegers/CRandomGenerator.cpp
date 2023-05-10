#include "CRandomGenerator.h"
#include "BigIntegers.h"
#include "ArithmeticBox.h"

DWORD CRandomGenerator::m_dwCount = 0;

CRandomGenerator::CRandomGenerator(PFnRandomBYTE pfRandomBYTEGenerator)
{
	if(NULL==pfRandomBYTEGenerator)
	{
		pfRandomBYTEGenerator = DefaultRandomBYTE;
	}
	m_pFnRandomBYTE = pfRandomBYTEGenerator;
}

CRandomGenerator::~CRandomGenerator()
{
	// purely for symmetry
	;
}

void CRandomGenerator::RandomBits(size_t nDigits, BYTE nBits, bool bForceLead, CBigInteger &nRandom)
{
	size_t i;
	DIGIT  *pData;
	DIGIT  nMask;
	// convert bits in excess of a DIGIT to more DIGITs
	nDigits += nBits/(sizeof(DIGIT)<<3);
	nBits   =  nBits%(sizeof(DIGIT)<<3);
	nRandom.Reserve(nDigits+1);
	pData = nRandom.GetValue();
	for(i=0;i<nDigits+1;i++)
	{
		pData[i] = 0;
		for(int j=0;j<sizeof(DIGIT);j++)
		{
			pData[i] |= m_pFnRandomBYTE()<<(j<<3);
		}
	}
	nMask = (DIGIT) ((((size_t) 1)<<nBits)-1);
	pData[nDigits] &= nMask;
	if(bForceLead)
	{
		pData[nDigits] |= (((DIGIT) 1)<<(nBits-1));
	}
	if(0==pData[i-1])
	{
		do
		{
			i--;
		}
		while(0<i && 0==pData[i-1]);
	}
	nRandom.SetSize(i);
}

bool CRandomGenerator::RandomInRange(CBigInteger &nLow, CBigInteger &nHigh, CBigInteger &nRandom)
{
	size_t         nDigits;
	CArithmeticBox cBox;
	CBigInteger    nHold;
	DIGIT          i, *pData;
	DIGIT          nMask      = (DIGIT) -1;
	bool           bSucceeded = false;
	if(eOperationSucceeded != cBox.Subtract(nHigh,nLow,nRandom))
	{
		goto exit;
	}
	if(nRandom.IsNegative())
	{
		goto exit;
	}
	nDigits = nRandom.GetSize();
	if(0==nDigits)
	{
		nRandom = nLow;
	}
	else
	{
		nDigits--;
		pData = nRandom.GetValue();
		// get a mask for the first DIGIT
		i = ((DIGIT) 1)<<((sizeof(DIGIT)<<3)-1);
		if(0==(i&(pData[nDigits])))
		{
			do
			{
				i = (i>>1);
				nMask = nMask>>1;
			}
			while(0==(i&(pData[nDigits])));
		}
		do
		{
			RandomBits(1+nDigits,0,false,nHold);
			pData = nHold.GetValue();
			pData[nDigits] &= nMask;
		}
		while(nRandom < nHold);
		cBox.Add(nHold,nLow,nRandom);
	}
	bSucceeded = true;
exit:
	return bSucceeded;
}

DIGIT CRandomGenerator::RandomDigit()
{
	int   nShift = 3;
	DIGIT nRand  = DefaultRandomBYTE();
	for (int i = 1; i < sizeof(DIGIT); i++)
	{
		nRand  |= (DefaultRandomBYTE()<<nShift);
		nShift += 3;
	}
	return nRand;
}

BYTE CRandomGenerator::DefaultRandomBYTE()
{
	if(0==m_dwCount%c_dwMaxRandomsForReseed)
	{
		srand(time(NULL));
	}
	m_dwCount++;
	return rand()&255;
}