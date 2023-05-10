#include "CBigIntegerHelper.h"

size_t CBigIntegerHelper::ShiftXRight(size_t nXSize, int nBitShift, size_t nDigitShift, const DIGIT *pnX, DIGIT *pnShiftedValue)
{
    size_t i;
    if(nXSize<=nDigitShift) return 0;
    if(nBitShift)
    {
        for(i=nDigitShift; i<nXSize-1; i++)
        {
            pnShiftedValue[i-nDigitShift] = (pnX[i]>>nBitShift) | (pnX[i+1]<<(c_nDigitSize-nBitShift));
        }
        pnShiftedValue[i-nDigitShift] = (pnX[i]>>nBitShift);
        return (0==pnShiftedValue[i-nDigitShift]) ? nXSize - (nDigitShift + 1) : nXSize - nDigitShift;
    }
    else
    {
        for(i=nDigitShift; i<nXSize; i++)
        {
            pnShiftedValue[i - nDigitShift] = pnX[i];
        }
        return nXSize - nDigitShift;
    }
}

size_t CBigIntegerHelper::ShiftXLeft(size_t nXSize, int nBitShift, size_t nDigitShift, const DIGIT *pnX, DIGIT *pnShiftedValue)
{
    size_t i;
    for(i=0; i<nDigitShift; i++)
    {
        pnShiftedValue[i] = 0;
    }
    if(nBitShift)
    {
        pnShiftedValue[i++] = (pnX[i-nDigitShift]<<nBitShift);
        for(; i<nDigitShift+nXSize; i++)
        {
            pnShiftedValue[i] = (pnX[i - nDigitShift]<<nBitShift) | (pnX[i-(1+nDigitShift)]>>(c_nDigitSize-nBitShift));
        }
        pnShiftedValue[i] = pnX[i-(1+nDigitShift)]>>(c_nDigitSize-nBitShift);
        return (0 == pnShiftedValue[i]) ? i : i+1;
    }
    else
    {
        for(; i<nDigitShift+nXSize; i++)
        {
            pnShiftedValue[i] = pnX[i - nDigitShift];
        }
        return i;
    }
}

size_t CBigIntegerHelper::ShiftLeftInPlace(size_t nXSize, int nBitShift, size_t nDigitShift, DIGIT *pnX)
{
    size_t i;
    int    nReverseShift;
    if(0==nBitShift)
    {
        if(nDigitShift)
        {
            i = nXSize + nDigitShift - 1;
            do
            {
                pnX[i] = pnX[i - nDigitShift];
            }
            while(i-- != nDigitShift);
            do
            {
                pnX[i] = 0;
            }
            while(i-- != 0);
        }
        return nXSize + nDigitShift;
    }
    else
    {
        i             = nXSize + nDigitShift;
        nReverseShift = c_nDigitSize - nBitShift;
        pnX[i--] = pnX[i - (1 + nDigitShift)]>>nReverseShift;
        if (i != nDigitShift)
        {
            do
            {
                pnX[i] = (pnX[i - nDigitShift]<<nBitShift) | (pnX[i-(1+nDigitShift)]>>nReverseShift);
            }
            while (--i != nDigitShift);
        }
        pnX[i] = (pnX[i - nDigitShift]<<nBitShift);
        if(0 != i--)
        {
            do
            {
                pnX[i] = 0;
            }
            while(0 != i--);
        }
        nXSize += nDigitShift;
        return nXSize + (0 < pnX[nXSize]);
    }
}

size_t CBigIntegerHelper::ShiftRightInPlace(size_t nXSize, int nBitShift, size_t nDigitShift, DIGIT *pnX)
{
    size_t i;
    if(nXSize <= nDigitShift) return 0; // entiely shifted away
    if(nBitShift)
    {
        int nReverseShift = c_nDigitSize - nBitShift;
        for (i=nDigitShift; i<nXSize-1; i++)
        {
            pnX[i - nDigitShift] = (pnX[i]>>nBitShift) | (pnX[i + 1]<<nReverseShift);
        }
        pnX[i - nDigitShift] = (pnX[i]>>nBitShift);
        return nXSize - nDigitShift - 1 + (0 < pnX[i - nDigitShift]);
    }
    else
    {
        if(nDigitShift)
        {
            for (i=nDigitShift; i<nXSize; i++)
            {
                pnX[i - nDigitShift] = pnX[i];
            }
        }
        return nXSize - nDigitShift;
    }
}