#include "BigIntegers.h"
#include "Constants.h"
#include "stdlib.h"
#include "stdio.h"
#include "..\BigIntegersBase\CBigIntegerHelper.h"
#include "CUnsignedArithmeticHelper.h"

const unsigned _int32 c_nNibblesPerDigit = 2*sizeof(DIGIT);

// Internal use helper functions
// returns the carry-out (usually 0...)
DIGIT AddSmallUnsigned(DIGIT *pnLarge, size_t nLargeSize, DIGIT nAdd)
{
    if(0<nLargeSize)
    {
        DOUBLEDIGIT nSum;
        size_t      i = 0;
        do
        {
            nSum       = nAdd+((DOUBLEDIGIT) pnLarge[i]);
            pnLarge[i] = (DIGIT) nSum;
            nAdd       = (DIGIT) (nSum>>_DIGIT_SIZE_IN_BITS);
        }
        while(0<nAdd && ++i<nLargeSize);
    }
    return nAdd;
}
// helper function for SubtractSmall.  Returns the number of
// non-zero digits after the subtraction.  Assumes the large number
// is at least the size of the small, and that the small is nonzero!
size_t SubtractSmallUnsigned(DIGIT *pnLarge, size_t nLargeSize, DIGIT nSub)
{
    size_t i = 0;
    do
    {
        DIGIT nBase  = pnLarge[i];
        pnLarge[i++] = nBase - nSub;
        nSub         = (nBase >= nSub) ? 0 : 1;
    }
    while(0!=nSub);
    // check to see if the high-order digit is 0 -- the size is then smaller!
    // note the i==nLargeSize check: most of the time, we expect this to fail,
    // and this test is faster than doing the indirection to see if the high-order
    // digit is 0
    if(i==nLargeSize && 0==pnLarge[nLargeSize-1])
    {
        nLargeSize--;
    }
    return nLargeSize;
}

// assumes a digit value between 0 and 15, inclusive -- not checked
char DigitToHex(DIGIT n)
{
    if(n<10)
    {
        return '0'+n;
    }
    else
    {
        return 'A'+(n-10);
    }
}

// returns a value between 0 and 15, inclusive, if the characted passed is a legal
// hexadecimal value; otherwise, it returns something greater than 15
DIGIT HexToDigit(char cHex)
{
    if('0' <= cHex && cHex <= '9')
    {
        return (DIGIT) (cHex-'0');
    }
    else if('A' <= cHex && cHex <= 'F')
    {
        return (DIGIT) (10+(cHex-'A'));
    }
    else
    {
        return 20;
    }
}

bool PrintHexToFileHelper(FILE *pFile, bool bIsNegative, size_t nDigits, DIGIT *pDigits, bool bAestheticSpaces = true)
{
    bool bAllOkay = false;
    if(NULL == pFile)
    {
        // write to stdout instead
        pFile = stdout;
    }
    if(0==nDigits)
    {
        bAllOkay = (0<fprintf(pFile,"%c\0",'0'));
    }
    else
    {
        DIGIT nVal;
        char  cVal;
        DIGIT nMask = 15;
        size_t j;
        if(bIsNegative)
        {
            if(fprintf(pFile,"%c",'-')<=0)
            {
                goto exit;
            }
        }
        j = c_nNibblesPerDigit-1;
        nDigits--;
        while(0==(pDigits[nDigits]&(nMask<<(j<<2))) && j!=0)
        {
            j--;
        }
        do
        {
            do
            {
                nVal = (pDigits[nDigits]&(nMask<<(j<<2)))>>(j<<2);
                cVal = DigitToHex(nVal);
                if(fprintf(pFile,"%c",cVal)<=0)
                {
                    goto exit;
                }
                j--;
            }
            while(j!=(size_t)-1);
            if(bAestheticSpaces) fprintf(pFile, " ");
            j = c_nNibblesPerDigit-1;
            nDigits--;
        }
        while(nDigits != (size_t) -1);
        if(fprintf(pFile,"%c",'\0')<=0)
        {
            bAllOkay = false;
            goto exit;
        }
        bAllOkay = true;
    }
exit:
    fprintf(pFile,"\n");
    return bAllOkay;
}

bool PrintDecimalToFileHelper(FILE *pFile, bool bIsNegative, size_t nDigits, DIGIT *pDigits)
{
    char  *szBase10Rep = NULL;
    DIGIT *pWorkspace  = NULL;
    bool  bAllOkay     = false;
    if (NULL == pFile)
    {
        // write to stdout instead
        pFile = stdout;
    }
    if (0 == nDigits)
    {
        bAllOkay = (0 < fprintf(pFile, "0\n"));
    }
    else
    {
        // space for the answer.  Total bits of the number divided by 3 gives an overestimate of the
        // number of base 10 digits
        size_t nSize = nDigits*_DIGIT_SIZE_IN_BITS/3 + 2;
        szBase10Rep = (char *)  malloc(nSize); // +1 for terminal '\0'; + 1 more for sign
        pWorkspace  = (DIGIT *) malloc(sizeof(DIGIT)*nDigits);
        if (NULL == szBase10Rep || NULL == pWorkspace) goto exit;
        szBase10Rep[--nSize] = '\0';
        for (int i = 0; i < nDigits; i++)
        {
            pWorkspace[i] = pDigits[i];
        }
        do
        {
            DOUBLEDIGIT nVal;
            DOUBLEDIGIT nCarry = 0;
            for(int i = nDigits-1; 0<=i; i--)
            {
                nVal          = pWorkspace[i] | (nCarry<<_DIGIT_SIZE_IN_BITS);
                nCarry        = nVal%10;
                pWorkspace[i] = nVal/10;
            }
            szBase10Rep[--nSize] = nCarry + '0';
            if(0==pWorkspace[nDigits-1]) nDigits--;
        }
        while (0<nDigits);
        if(bIsNegative) szBase10Rep[--nSize] = '-';
        bAllOkay = (0 < fprintf(pFile, "%s\n", szBase10Rep + nSize));
    }
exit:
    free(szBase10Rep); // note freeing  NULL pointer is safe
    free(pWorkspace);
    return bAllOkay;
}

void CBigInteger::FixLeadingZeros()
{
    while (0 < m_nSize && 0 == m_pnValue[m_nSize - 1]) m_nSize--;
}

/////////////////////////////////////////////////////////////////////////////////////
//                                                                                 //
//                      Big integer class functions                                //
//                                                                                 //
/////////////////////////////////////////////////////////////////////////////////////

CBigInteger::CBigInteger()
{
    m_nAllocatedSize = 0;
    m_nSize          = 0;
    m_pnValue        = NULL;
    m_bNegative      = false;
#ifdef _DEBUG
    m_pnValue        = (DIGIT *) malloc(sizeof(DIGIT)*_BUFFERGUARD_SLOTS);
    for(int j=0; j<_BUFFERGUARD_SLOTS; j++)
    {
        m_pnValue[j] = BUFFERGUARD;
    }
#endif
}

CBigInteger::CBigInteger(const CBigInteger &base)
{
    m_nAllocatedSize = base.m_nSize;
    m_nSize          = base.m_nSize;
    m_bNegative      = base.m_bNegative;
#ifdef _DEBUG
    m_pnValue        = (DIGIT *) malloc(sizeof(DIGIT)*(m_nSize+_BUFFERGUARD_SLOTS));
    for(int j=m_nSize; j< m_nSize+_BUFFERGUARD_SLOTS; j++)
    {
        m_pnValue[j] = BUFFERGUARD;
    }
#else
    m_pnValue        = (DIGIT *) malloc(sizeof(DIGIT)*m_nSize);
#endif
    memcpy(m_pnValue, base.m_pnValue, sizeof(DIGIT)*m_nSize);
}

CBigInteger::CBigInteger(const char *szHexadecimalValue, bool bKeepLeadingZeroes)
{
    m_nAllocatedSize = 0;
    m_nSize          = 0;
    m_pnValue        = NULL;
    m_bNegative      = false;
#ifdef _DEBUG
    m_pnValue        = (DIGIT *) malloc(sizeof(DIGIT)*_BUFFERGUARD_SLOTS);
    for(int j=0; j<_BUFFERGUARD_SLOTS; j++)
    {
        m_pnValue[j] = BUFFERGUARD;
    }
#endif
    SetFromHexString(szHexadecimalValue, bKeepLeadingZeroes);
}

CBigInteger::~CBigInteger()
{
    CheckBufferguard();
    free(m_pnValue); // note that calling free on a NULL pointer is harmless
}

int CBigInteger::CompareUnsigned(size_t      nXSize,
                                 size_t      nYSize,
                                 const DIGIT *pX,
                                 const DIGIT *pY)
{
    if (nXSize < nYSize)
    {
        return -1;
    }
    else if (nXSize > nYSize)
    {
        return 1;
    }
    else if (0 == nXSize)
    {
        return 0;
    }
    else
    {
        do
        {
            nXSize--;
        }
        while (pX[nXSize] == pY[nXSize] && 0 != nXSize);
        if (pX[nXSize] < pY[nXSize])
        {
            return -1;
        }
        else if (pX[nXSize] > pY[nXSize])
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

// comparison functions
int CBigInteger::Compare(const CBigInteger &x, const CBigInteger &y)
{
    if (x.IsNegative())
    {
        if (y.IsNegative())
        {
            return CompareUnsigned(y.m_nSize, x.m_nSize, y.m_pnValue, x.m_pnValue);
        }
        else
        {
            return -1;
        }
    }
    else if (y.IsNegative())
    {
        return 1;
    }
    else
    {
        return CompareUnsigned(x.m_nSize, y.m_nSize, x.m_pnValue, y.m_pnValue);
    }
}
bool CBigInteger::operator==(const CBigInteger &toCompare)
{
    return (0 == Compare(*this, toCompare));
}
bool CBigInteger::operator!=(const CBigInteger &toCompare)
{
    return (0 != Compare(*this, toCompare));
}
bool CBigInteger::operator<(const CBigInteger &toCompare)
{
    return (-1 == Compare(*this, toCompare));
}
bool CBigInteger::operator<=(const CBigInteger &toCompare)
{
    return (1 != Compare(*this, toCompare));
}
bool CBigInteger::operator>=(const CBigInteger &toCompare)
{
    return (-1 != Compare(*this, toCompare));
}
bool CBigInteger::operator>(const CBigInteger& toCompare)
{
    return (1 == Compare(*this, toCompare));
}

void CBigInteger::Swap(CBigInteger &nX, CBigInteger &nY)
{
    size_t nSize     = nX.m_nAllocatedSize;
    DIGIT  *pnDigits = nX.m_pnValue;
    bool   bNegative = nX.m_bNegative;
    nX.m_nAllocatedSize = nY.m_nAllocatedSize;
    nX.m_pnValue        = nY.m_pnValue;
    nX.m_bNegative      = nY.m_bNegative;
    nY.m_nAllocatedSize = nSize;
    nY.m_pnValue        = pnDigits;
    nY.m_bNegative      = bNegative;
    nSize               = nX.m_nSize;
    nX.m_nSize          = nY.m_nSize;
    nY.m_nSize          = nSize;
}

bool CBigInteger::Reserve(size_t nDigitsNeeded, bool bPreserveData)
{
#ifdef _DEBUG
    // check that didn't override buffer guard
    for(int j=0; j<_BUFFERGUARD_SLOTS; j++)
    {
        if(BUFFERGUARD != m_pnValue[m_nAllocatedSize+j])
        {
            printf("Overran big integer allocated size\n");
        }
    }
#endif
    if(m_nAllocatedSize<nDigitsNeeded)
    {
#ifdef _DEBUG
        // extra space for buffer guard in debug
        DIGIT *pTemp = (DIGIT *) malloc(sizeof(DIGIT)*(nDigitsNeeded + _BUFFERGUARD_SLOTS));
#else
        DIGIT *pTemp = (DIGIT *) malloc(sizeof(DIGIT)*nDigitsNeeded);
#endif
        if (NULL == pTemp) return false;
        if(bPreserveData && 0<m_nSize)
        {
            memcpy_s(pTemp,sizeof(DIGIT)*nDigitsNeeded,m_pnValue,sizeof(DIGIT)*m_nSize);
        }
        free(m_pnValue);
        m_pnValue        = pTemp;
        m_nAllocatedSize = nDigitsNeeded;
#ifdef _DEBUG
        // set up bufferguard to detect memory overruns
        for(int j=0; j<_BUFFERGUARD_SLOTS; j++)
        {
            m_pnValue[m_nAllocatedSize+j] = BUFFERGUARD;
        }
#endif
    }
    return true;
}

bool CBigInteger::PrintHexToFile(FILE *pFile) const
{
    return PrintHexToFileHelper(pFile,m_bNegative,m_nSize,m_pnValue);
}

bool CBigInteger::PrintHexToScreen()
{
    return PrintHexToFileHelper(NULL, m_bNegative, m_nSize, m_pnValue, false);
}

bool CBigInteger::PrintDecimalToFile(FILE *pFile) const
{
    return PrintDecimalToFileHelper(pFile, m_bNegative, m_nSize, m_pnValue);
}

bool CBigInteger::operator=(const CBigInteger &nBase)
{
    if (this == &nBase)            return true; // nothing to do
    if (!Reserve(nBase.GetSize())) return false;
    SetSize(nBase.GetSize());
    SetNegative(nBase.IsNegative());
    memcpy(m_pnValue, nBase.m_pnValue, m_nSize*sizeof(DIGIT));
    return true;
}

bool CBigInteger::operator+=(DIGIT nAdd)
{
    bool bAllOkay = false;
    if(0!=nAdd)
    {
        if(m_bNegative)
        {
            // actually amounts to a subtraction
            size_t nDigits = GetSize();
            if(1==nDigits && (m_pnValue[0] < nAdd))
            {
                SetNegative(false);
                m_pnValue[0] = nAdd-m_pnValue[0];
            }
            else
            {
                SetSize(SubtractSmallUnsigned(m_pnValue,m_nSize,nAdd));
            }
        }
        else
        {
            // Really are doing addition
            nAdd = AddSmallUnsigned(m_pnValue,m_nSize,nAdd);
            if(0<nAdd)
            {
                if(!Reserve(m_nSize+1,true))
                {
                    goto exit;
                }
                else
                {
                    m_pnValue[m_nSize++] = nAdd;
                }
            }
        }
    }
    bAllOkay = true;
exit:
    return bAllOkay;
}

bool CBigInteger::operator+=(const CBigInteger &nAdd)
{
    size_t nSizeNeeded = max(m_nSize, nAdd.m_nSize) + 1;
    // make sure we have enough space
    if (!Reserve(nSizeNeeded, true)) return false;
    if(m_bNegative==nAdd.m_bNegative)
    {
        // really is add
        if(m_nSize)
        {
            m_nSize = CUnsignedArithmeticHelper::Add(m_nSize,nAdd.m_nSize,m_pnValue,nAdd.m_pnValue,m_pnValue);
        }
        else
        {
            return(*this = nAdd);
          //  return nAdd.Copy(*this);
        }
    }
    else
    {
        // actually doing subtraction
        switch (CompareUnsigned(m_nSize,nAdd.m_nSize,m_pnValue,nAdd.m_pnValue)) //(Compare(*this, nAdd))
        {
        case -1:
            // this < nAdd
            m_nSize     = CUnsignedArithmeticHelper::Subtract(nAdd.m_nSize,m_nSize,nAdd.m_pnValue,m_pnValue,m_pnValue);
            m_bNegative = !m_bNegative;
            break;
        case 0:
            // this == nAdd
            m_nSize     = 0;
            m_bNegative = false;
            break;
        case 1:
            // this > nAdd
            m_nSize = CUnsignedArithmeticHelper::Subtract(m_nSize,nAdd.m_nSize,m_pnValue,nAdd.m_pnValue,m_pnValue);
            break;
        }
    }
    return true;
}

bool CBigInteger::operator-=(DIGIT nSub)
{
    bool bAllOkay = false;
    if(0!=nSub)
    {
        if(m_bNegative)
        {
            // Really are doing addition
            nSub = AddSmallUnsigned(m_pnValue, m_nSize, nSub);
            if (0<nSub)
            {
                if (!Reserve(m_nSize + 1, true))
                {
                    goto exit;
                }
                else
                {
                    m_pnValue[m_nSize++] = nSub;
                }
            }
        }
        else
        {
            // actually is subtraction
            size_t nDigits = GetSize();
            if(0==nDigits)
            {
                if(!Reserve(1))
                {
                    goto exit;
                }
                else
                {
                    SetSize(1);
                    SetNegative(true);
                    m_pnValue[0] = nSub;
                }
            }
            else if(1==nDigits && (m_pnValue[0]<=nSub))
            {
                m_pnValue[0] = nSub-m_pnValue[0];
                if(m_pnValue[0])
                {
                    SetSize(1);
                    SetNegative(true);
                }
                else
                {
                    SetSize(0);
                }
            }
            else
            {
                SetSize(SubtractSmallUnsigned(m_pnValue,m_nSize,nSub));
            }
        }
    }
    bAllOkay = true;
exit:
    return bAllOkay;
}

bool CBigInteger::operator-=(const CBigInteger &nSub)
{
    size_t nSizeNeeded = max(m_nSize, nSub.m_nSize) + 1;
    // make sure we have enough space
    if (!Reserve(nSizeNeeded, true)) return false;
    if(m_bNegative!=nSub.m_bNegative)
    {
        // Actually is add
        if(m_nSize)
        {
            m_nSize = CUnsignedArithmeticHelper::Add(m_nSize,nSub.m_nSize,m_pnValue,nSub.m_pnValue,m_pnValue);
        }
        else
        {
            if (!(*this = nSub)) return false;
            m_bNegative = (0<m_nSize && !nSub.m_bNegative);
        }
    }
    else
    {
        // doing subtraction
        switch (CompareUnsigned(m_nSize, nSub.m_nSize, m_pnValue, nSub.m_pnValue)) //(Compare(*this, nSub))
        {
        case -1:
            // this < nSub
            m_nSize     = CUnsignedArithmeticHelper::Subtract(nSub.m_nSize,m_nSize,nSub.m_pnValue,m_pnValue,m_pnValue);
            m_bNegative = !m_bNegative;
            break;
        case 0:
            // this == nSub
            SetSize(0);
            break;
        case 1:
            // this > nSub
            m_nSize = CUnsignedArithmeticHelper::Subtract(m_nSize,nSub.m_nSize,m_pnValue,nSub.m_pnValue,m_pnValue);
            break;
        }
    }
    return true;
}

bool CBigInteger::SetFromHexString(const char *szHexadecimalValue, bool bKeepLeadingZeroes)
{
    DIGIT  nVal        = 0;
    size_t i           = 0;
    size_t j           = 0;
    bool   bSetWorked  = false;
    bool   bFoundDigit = false;
    bool   bNegative   = false;
    size_t nHexSize    = strlen(szHexadecimalValue);
    size_t nDigits     = (nHexSize+c_nNibblesPerDigit-1)/c_nNibblesPerDigit;
    if(0==nHexSize || !Reserve(nDigits))
    {
        goto exit;
    }
    if('-'==szHexadecimalValue[0])
    {
        szHexadecimalValue++;
        nHexSize--;
        bNegative = true;
        // with the shorter string, need to re-calculate the number of digits
        nDigits = (nHexSize+c_nNibblesPerDigit-1)/c_nNibblesPerDigit;
    }
    for(i=nHexSize;i!=0;i--)
    {
        // skip over whitespace?
        DIGIT nRead = HexToDigit(szHexadecimalValue[i-1]);
        if(15<nRead)
        {
            goto exit;
        }
        bFoundDigit = true;
        nVal += nRead<<(4*(j%c_nNibblesPerDigit));
        if(2*sizeof(DIGIT)-1==j%c_nNibblesPerDigit)
        {
            // read in full digit; enter it into the value array
            m_pnValue[j/c_nNibblesPerDigit] = nVal;
            nVal = 0;
        }
        j++;
    }
    if(0!=j%c_nNibblesPerDigit)
    {
        // drop in the last (partial) digit
        m_pnValue[j/c_nNibblesPerDigit] = nVal;
        nVal = 0;
    }
    if(!bKeepLeadingZeroes)
    {
        // get rid of any leading 0s
        if(0==m_pnValue[nDigits-1])
        {
            do
            {
                nDigits--;
            }
            while(0<nDigits && 0==m_pnValue[nDigits-1]);
        }
    }
    m_nSize    = nDigits;
    bSetWorked = bFoundDigit;
    SetNegative(bNegative);
exit:
    return bSetWorked;
}

bool CBigInteger::ShiftRight(size_t nBits)
{
    m_nSize = CBigIntegerHelper::ShiftRightInPlace(m_nSize, nBits%_DIGIT_SIZE_IN_BITS, nBits/_DIGIT_SIZE_IN_BITS, m_pnValue);
    if (0 == m_nSize) m_bNegative = false;
    return true;
}

bool CBigInteger::ShiftLeft(size_t nBits)
{
    size_t nDigitShift, nBitShift, i;
    if (0 != nBits)
    {
        nDigitShift = nBits/_DIGIT_SIZE_IN_BITS;
        nBitShift   = nBits%_DIGIT_SIZE_IN_BITS;
        if (!Reserve(nDigitShift+m_nSize+1, true)) return false;
        m_nSize = CBigIntegerHelper::ShiftLeftInPlace(m_nSize, nBitShift, nDigitShift, m_pnValue);
    }
    return true;
}

bool CBigInteger::CopyShiftRight(CBigInteger &nDestination, size_t nBits) const
{
    size_t nDigitShift, nBitShift, i;
    if(0==nBits)
    {
        // simple copy
        return(nDestination = *this);
    }
    nDigitShift = nBits/_DIGIT_SIZE_IN_BITS;
    if(m_nSize <= nDigitShift)
    {
        nDestination.SetSize(0);
        return true;
    }
    nBitShift = nBits%_DIGIT_SIZE_IN_BITS;
    if (!nDestination.Reserve(m_nSize - nDigitShift)) return false; // couldn't get enough memory -- weird!
    nDestination.SetSize(CBigIntegerHelper::ShiftXRight(m_nSize, nBitShift, nDigitShift, m_pnValue, nDestination.GetValue()));
    nDestination.SetNegative(m_bNegative);
    return true;
}

bool CBigInteger::CopyShiftLeft(CBigInteger &nDestination, size_t nBits) const
{
    size_t nDigitShift, nBitShift, i, nSize;
    if (0 == nBits)
    {
        // simple copy
        return(nDestination = *this);
    }
    nDigitShift = nBits/_DIGIT_SIZE_IN_BITS;
    nBitShift   = nBits%_DIGIT_SIZE_IN_BITS;
    if(!nDestination.Reserve(GetSize()+nDigitShift+1))
    {
        return false;
    }
    nDestination.SetSize(CBigIntegerHelper::ShiftXLeft(m_nSize, nBitShift, nDigitShift, m_pnValue, nDestination.GetValue()));
    nDestination.SetNegative(m_bNegative);
    return true;
}
