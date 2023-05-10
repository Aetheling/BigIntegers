// put the basic multiply in a seperate file so we can play with compile options in test more easily
#pragma once
#include "CUnsignedArithmeticHelper.h"
#include "Constants.h"
#include "Macros.h"

// note that we assume nXSize <= nYSize (for the case of _REGISTER_BLOCK_SIZE == 1, at least)
#ifdef _TestingBasicMultiplyDirectly
#if(1==_REGISTER_BLOCK_SIZE)
void BasicUnsignedMultiplyForTest1(size_t nXSize,
#elif(2==_REGISTER_BLOCK_SIZE)
void BasicUnsignedMultiplyForTest2(size_t nXSize,
#elif(3==_REGISTER_BLOCK_SIZE)
void BasicUnsignedMultiplyForTest3(size_t nXSize,
#elif(4==_REGISTER_BLOCK_SIZE)
void BasicUnsignedMultiplyForTest4(size_t nXSize,
#elif(5==_REGISTER_BLOCK_SIZE)
void BasicUnsignedMultiplyForTest5(size_t nXSize,
#elif(6==_REGISTER_BLOCK_SIZE)
void BasicUnsignedMultiplyForTest6(size_t nXSize,
#endif
#else
void CUnsignedArithmeticHelper::MultUBasic(size_t       nXSize,
#endif
                                           size_t       nYSize,
                                           const DIGIT  *pX,
                                           const DIGIT  *pY,
                                           DIGIT        *pZ,
#if(_CollectDetailedTimingData)
                                           bool         bAddInitialZValueToProduct,
                                           DWORD64      &dwTimestamp)
#else
                                           bool         bAddInitialZValueToProduct)
#endif
{
    DOUBLEDIGIT	nProd,nCarry,nSum;
    size_t  	i,j;
    DIGIT       *pLast = pZ+nXSize+nYSize-1;
#if(_CollectDetailedTimingData)
    DWORD64     dwTime = dwTimestamp;
#endif
#if(_REGISTER_BLOCK_SIZE==1)
    DOUBLEDIGIT nX0;
    // special case: not doing any blocking of data
    if(!bAddInitialZValueToProduct)
    {
        for(i=0;i<nXSize+nYSize;i++)
        {
            pZ[i]=0;
        }
        for(i=0;i<nXSize;i++)
        {
            nX0    = pX[i];
            nCarry = 0;
            for(j=0;j<nYSize;j++)
            {
                nProd   = nX0*pY[j];
                nSum    = (nProd&c_nClearHigh)+pZ[i+j]+nCarry;
                pZ[i+j] = (DIGIT) nSum;
                nCarry  = (nProd>>c_nDigitSize)+(nSum>>c_nDigitSize);
            }
            pZ[i+j] = (DIGIT) nCarry;
        }
    }
    else
    {
        DOUBLEDIGIT nCarryOut = 0;
        for(i=0;i<nXSize;i++)
        {
            nX0    = pX[i];
            nCarry = 0;
            for(j=0;j<nYSize;j++)
            {
                nProd   = nX0*pY[j];
                nSum    = (nProd&c_nClearHigh)+pZ[i+j]+nCarry;
                pZ[i+j] = (DIGIT) nSum;
                nCarry  = (nProd>>c_nDigitSize)+(nSum>>c_nDigitSize);
            }
            nSum      = nCarry+nCarryOut+pZ[i+j];
            pZ[i+j]   = (DIGIT) nSum;
            nCarryOut = nSum>>c_nDigitSize;
        }
        if(0 != nCarryOut)
        {
            j = nXSize+nYSize;
            do
            {
                nSum      = nCarryOut + pZ[j];
                nCarryOut = (nSum>>c_nDigitSize);
                pZ[j++]   = (DIGIT) nSum;
            }
            while(0 != nCarryOut);
        }
    }
#else
    DIGIT	    nX0,nY0,nX1,nY1;
#if(2<_REGISTER_BLOCK_SIZE)
    DIGIT       nX2,nY2;
#if(3<_REGISTER_BLOCK_SIZE)
    DIGIT       nX3,nY3;
#if(4<_REGISTER_BLOCK_SIZE)
    DIGIT nX4,nY4;
#if(5<_REGISTER_BLOCK_SIZE)
    DIGIT nX5,nY5;
#endif
#endif
#endif
#endif
#if(_REGISTER_BLOCK_SIZE==2)
#define yTOP         nY1
#define yTOP_MINUS_1 nY0
#elif(_REGISTER_BLOCK_SIZE==3)
#define yTOP         nY2
#define yTOP_MINUS_1 nY1
#define yTOP_MINUS_2 nY0
#elif(_REGISTER_BLOCK_SIZE==4)
#define yTOP         nY3
#define yTOP_MINUS_1 nY2
#define yTOP_MINUS_2 nY1
#define yTOP_MINUS_3 nY0
#elif(_REGISTER_BLOCK_SIZE==5)
#define yTOP         nY4
#define yTOP_MINUS_1 nY3
#define yTOP_MINUS_2 nY2
#define yTOP_MINUS_3 nY1
#define yTOP_MINUS_4 nY0
#elif(_REGISTER_BLOCK_SIZE==6)
#define yTOP         nY5
#define yTOP_MINUS_1 nY4
#define yTOP_MINUS_2 nY3
#define yTOP_MINUS_3 nY2
#define yTOP_MINUS_4 nY1
#define yTOP_MINUS_5 nY0
#else
    C_ASSERT(false);
#endif
    // Since the multiply is to be done in _REGISTER_BLOCK_SIZE-DIGIT chunks,
    // need to do a few "trimming" operations when the
    // numbers don't happen to have sizes in neat multiples
    // of _REGISTER_BLOCK_SIZE.
    j = nXSize%_REGISTER_BLOCK_SIZE;
    if(j==0)
    {
        j = _REGISTER_BLOCK_SIZE;
    }
    if(!bAddInitialZValueToProduct)
    {
        for(i=nYSize+1;i<nXSize+nYSize;i++)  // initialize where needed only
        {
            pZ[i] = 0;
        }
    }
    nXSize -= j;
    nX0    =  pX[0];
    nCarry =  0;
    if(!bAddInitialZValueToProduct)
    {
        for(i=0;i<nYSize;i++)
        {
            nY0    = pY[i];
            nProd  = nX0*((DOUBLEDIGIT) nY0);
            nSum   = (nProd&c_nClearHigh) + nCarry;
            nCarry = (nSum>>c_nDigitSize) + (nProd>>c_nDigitSize);
            pZ[i]  = (DIGIT) nSum;
        }
        pZ[i] = (DIGIT) nCarry;
    }
    else
    {
        for(i=0;i<nYSize;i++)
        {
            nY0    = pY[i];
            nProd  = nX0*((DOUBLEDIGIT) nY0);
            nSum   = (nProd&c_nClearHigh) + nCarry + pZ[i];
            nCarry = (nSum>>c_nDigitSize) + (nProd>>c_nDigitSize);
            pZ[i]  = (DIGIT) nSum;
        }
        if(0 != nCarry)
        {
            do
            {
                nSum    = pZ[i]+nCarry;
                nCarry  = (nSum>>c_nDigitSize);
                pZ[i++] = (DIGIT) nSum;
            }
            while(0 != nCarry);
        }
    }
    j--;
    pZ++;
    pX++;
    for(;j>0;j--)
    {
        nX0    = pX[0];
        nCarry = 0;
        for(i=0;i<nYSize;i++)
        {
            nY0    = pY[i];
            nProd  = nX0*((DOUBLEDIGIT) nY0);
            nSum   = (nProd&c_nClearHigh) + nCarry  + pZ[i];
            nCarry = (nSum>>c_nDigitSize) + (nProd>>c_nDigitSize);
            pZ[i]  = (DIGIT) nSum;
        }
        if(nCarry)
        {
            do
            {
                nCarry  += pZ[i];
                pZ[i++] =  (DIGIT) nCarry;
                nCarry  =  nCarry>>c_nDigitSize;
            }
            while(nCarry);
        }
        pZ++;
        pX++;
    }
    if(nXSize==0)
    {
        // nothing left after trimming the digits in excess of a multiple
        // of the register block size from X.  (Note that we don't need
        // to check Y: by assumption, it has at least as many digits as X.)
        return;
    }
    j      =  nYSize%_REGISTER_BLOCK_SIZE;
    nYSize -= j;
    for(;j>0;j--)
    {
        nY0    = pY[0];
        nCarry = 0;
        for(i=0;i<nXSize;i++)
        {
            nX0    = pX[i];
            nProd  = nX0*((DOUBLEDIGIT) nY0);
            nSum   = (nProd&c_nClearHigh) + nCarry + pZ[i];
            nCarry = (nSum>>c_nDigitSize) + (nProd>>c_nDigitSize);
            pZ[i]  = (DIGIT) nSum;
        }
        if(nCarry)
        {
            do
            {
                nCarry  += pZ[i];
                pZ[i++] =  (DIGIT) nCarry;
                nCarry  =  (nCarry>>c_nDigitSize);
            }
            while(nCarry);
        }
        pZ++;
        pY++;
    }
    // Now, all that remains is to multiply the "core" of the
    // two numbers: two numbers which are both multiples
    // of _REGISTER_BLOCK_SIZE digits in length
    for(j=0;j<nYSize;j+=_REGISTER_BLOCK_SIZE)
    {
        nY0		=  pY[j];
        nX0		=  pX[0];
        nY1		=  pY[j+1];
        nX1		=  pX[1];
#if(_REGISTER_BLOCK_SIZE>2)
        nY2		=  pY[j+2];
        nX2		=  pX[2];
#if(_REGISTER_BLOCK_SIZE>3)
        nY3		=  pY[j+3];
        nX3		=  pX[3];
#if(_REGISTER_BLOCK_SIZE>4)
        nY4		=  pY[j+4];
        nX4		=  pX[4];
#if(_REGISTER_BLOCK_SIZE>5)
        nY5		=  pY[j+5];
        nX5		=  pX[5];
#endif
#endif
#endif
#endif
        nProd	=  nX0*((DOUBLEDIGIT) nY0);
        nSum	=  (nProd&c_nClearHigh) + pZ[j];
        nCarry	=  (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
        pZ[j]   =  (DIGIT) nSum;
#if(_REGISTER_BLOCK_SIZE>2)
        nProd	=  nX0*((DOUBLEDIGIT) nY1);
        nSum	=  (nProd&c_nClearHigh) + pZ[j+1] + nCarry;
        nCarry	=  (nProd>>c_nDigitSize);
        nProd	=  nX1*((DOUBLEDIGIT) nY0);
        nSum	+= (nProd&c_nClearHigh);
        nCarry	+= (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
        pZ[j+1] =  (DIGIT) nSum;
#if(_REGISTER_BLOCK_SIZE>3)
        nProd	=  nX0*((DOUBLEDIGIT) nY2);
        nSum	=  (nProd&c_nClearHigh) + pZ[j+2] + nCarry;
        nCarry	=  (nProd>>c_nDigitSize);
        nProd	=  nX1*((DOUBLEDIGIT) nY1);
        nSum	+= (nProd&c_nClearHigh);
        nCarry	+= (nProd>>c_nDigitSize);
        nProd	=  nX2*((DOUBLEDIGIT) nY0);
        nSum	+= (nProd&c_nClearHigh);
        nCarry	+= (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
        pZ[j+2] =  (DIGIT) nSum;
#if(_REGISTER_BLOCK_SIZE>4)
        nProd	=  nX0*((DOUBLEDIGIT) nY3);
        nSum	=  (nProd&c_nClearHigh) + pZ[j+3] + nCarry;
        nCarry	=  (nProd>>c_nDigitSize);
        nProd	=  nX1*((DOUBLEDIGIT) nY2);
        nSum	+= (nProd&c_nClearHigh);
        nCarry	+= (nProd>>c_nDigitSize);
        nProd	=  nX2*((DOUBLEDIGIT) nY1);
        nSum	+= (nProd&c_nClearHigh);
        nCarry	+= (nProd>>c_nDigitSize);
        nProd	=  nX3*((DOUBLEDIGIT) nY0);
        nSum	+= (nProd&c_nClearHigh);
        nCarry	+= (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
        pZ[j+3] =  (DIGIT) nSum;
#if(_REGISTER_BLOCK_SIZE>5)
        nProd	=  nX0*((DOUBLEDIGIT) nY4);
        nSum	=  (nProd&c_nClearHigh) + pZ[j+4] + nCarry;
        nCarry	=  (nProd>>c_nDigitSize);
        nProd	=  nX1*((DOUBLEDIGIT) nY3);
        nSum	+= (nProd&c_nClearHigh);
        nCarry	+= (nProd>>c_nDigitSize);
        nProd	=  nX2*((DOUBLEDIGIT) nY2);
        nSum	+= (nProd&c_nClearHigh);
        nCarry	+= (nProd>>c_nDigitSize);
        nProd	=  nX3*((DOUBLEDIGIT) nY1);
        nSum	+= (nProd&c_nClearHigh);
        nCarry	+= (nProd>>c_nDigitSize);
        nProd	=  nX4*((DOUBLEDIGIT) nY0);
        nSum	+= (nProd&c_nClearHigh);
        nCarry	+= (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
        pZ[j+4] =  (DIGIT) nSum;
#endif
#endif
#endif
#endif
        for(i=_REGISTER_BLOCK_SIZE-1;i<nXSize-_REGISTER_BLOCK_SIZE;i+=_REGISTER_BLOCK_SIZE)
        {
            nProd   =  nX0*((DOUBLEDIGIT) yTOP);
            nSum    =  (nProd&c_nClearHigh) + pZ[i+j] + nCarry;
            nCarry  =  (nProd>>c_nDigitSize);
            nProd   =  nX1*((DOUBLEDIGIT) yTOP_MINUS_1);
#if(_REGISTER_BLOCK_SIZE>2)
            nSum    += (nProd&c_nClearHigh);
            nCarry  += (nProd>>c_nDigitSize);
            nProd   =  nX2*((DOUBLEDIGIT) yTOP_MINUS_2);
#if(_REGISTER_BLOCK_SIZE>3)
            nSum    += (nProd&c_nClearHigh);
            nCarry  += (nProd>>c_nDigitSize);
            nProd   =  nX3*((DOUBLEDIGIT) yTOP_MINUS_3);
#if(_REGISTER_BLOCK_SIZE>4)
            nSum    += (nProd&c_nClearHigh);
            nCarry  += (nProd>>c_nDigitSize);
            nProd   =  nX4*((DOUBLEDIGIT) yTOP_MINUS_4);
#if(_REGISTER_BLOCK_SIZE>5)
            nSum    += (nProd&c_nClearHigh);
            nCarry  += (nProd>>c_nDigitSize);
            nProd   =  nX5*((DOUBLEDIGIT) yTOP_MINUS_5);
#endif
#endif
#endif
#endif
            nSum    += (nProd&c_nClearHigh);
            nCarry  += (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
            pZ[i+j] =  (DIGIT) nSum;
            nX0		=  pX[i+1];
            nProd	=  nX1*((DOUBLEDIGIT) yTOP);
            nSum	=  (nProd&c_nClearHigh) + pZ[i+j+1] + nCarry;
            nCarry	=  (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==2)
            nProd	=  nX0*((DOUBLEDIGIT) yTOP_MINUS_1);
#else
            nProd	=  nX2*((DOUBLEDIGIT) yTOP_MINUS_1);
            nSum	+= (nProd&c_nClearHigh);
            nCarry	+= (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==3)
            nProd	=  nX0*((DOUBLEDIGIT) yTOP_MINUS_2);
#else
            nProd	=  nX3*((DOUBLEDIGIT) yTOP_MINUS_2);
            nSum	+= (nProd&c_nClearHigh);
            nCarry	+= (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==4)
            nProd	=  nX0*((DOUBLEDIGIT) yTOP_MINUS_3);
#else
            nProd	=  nX4*((DOUBLEDIGIT) yTOP_MINUS_3);
            nSum	+= (nProd&c_nClearHigh);
            nCarry	+= (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==5)
            nProd	=  nX0*((DOUBLEDIGIT) yTOP_MINUS_4);
#else
            nProd	=  nX5*((DOUBLEDIGIT) yTOP_MINUS_4);
            nSum	+= (nProd&c_nClearHigh);
            nCarry	+= (nProd>>c_nDigitSize);
            nProd	=  nX0*((DOUBLEDIGIT) yTOP_MINUS_5);
#endif
#endif
#endif
#endif
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
            pZ[i+j+1] =  (DIGIT) nSum;
            nX1		  =  pX[i+2];
#if(_REGISTER_BLOCK_SIZE>2)
            nProd	  =  nX2*((DOUBLEDIGIT) yTOP);
            nSum	  =  (nProd&c_nClearHigh) + pZ[i+j+2] + nCarry;
            nCarry	  =  (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==3)
            nProd	  =  nX0*((DOUBLEDIGIT) yTOP_MINUS_1);
#else
            nProd	  =  nX3*((DOUBLEDIGIT) yTOP_MINUS_1);
#endif
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==3)
            nProd	  =  nX1*((DOUBLEDIGIT) yTOP_MINUS_2);
#elif(_REGISTER_BLOCK_SIZE==4)
            nProd	  =  nX0*((DOUBLEDIGIT) yTOP_MINUS_2);
#else
            nProd	  =  nX4*((DOUBLEDIGIT) yTOP_MINUS_2);
#endif
#if(_REGISTER_BLOCK_SIZE>3)
            nSum	  += (nProd&c_nClearHigh);
            nCarry    += (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==4)
            nProd	  =  nX1*((DOUBLEDIGIT) yTOP_MINUS_3);
#elif(_REGISTER_BLOCK_SIZE==5)
            nProd	  =  nX0*((DOUBLEDIGIT) yTOP_MINUS_3);
#else
            nProd	  =  nX5*((DOUBLEDIGIT) yTOP_MINUS_3);
#endif
#if(_REGISTER_BLOCK_SIZE>4)
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==5)
            nProd	  =  nX1*((DOUBLEDIGIT) yTOP_MINUS_4);
#else
            nProd	  =  nX0*((DOUBLEDIGIT) yTOP_MINUS_4);
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
            nProd	  =  nX1*((DOUBLEDIGIT) yTOP_MINUS_5);
#endif
#endif
#endif
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
            pZ[i+j+2] =  (DIGIT) nSum;
            nX2		  =  pX[i+3];
#if(_REGISTER_BLOCK_SIZE>3)
            nProd	  =  nX3*((DOUBLEDIGIT) yTOP);
            nSum	  =  (nProd&c_nClearHigh) + pZ[i+j+3] + nCarry;
            nCarry	  =  (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==4)
            nProd	  =  nX0*((DOUBLEDIGIT) yTOP_MINUS_1);
#else
            nProd	  =  nX4*((DOUBLEDIGIT) yTOP_MINUS_1);
#endif
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==4)
            nProd	  =  nX1*((DOUBLEDIGIT) yTOP_MINUS_2);
#elif(_REGISTER_BLOCK_SIZE==5)
            nProd	  =  nX0*((DOUBLEDIGIT) yTOP_MINUS_2);
#else
            nProd	  =  nX5*((DOUBLEDIGIT) yTOP_MINUS_2);
#endif
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==4)
            nProd	  =  nX2*((DOUBLEDIGIT) yTOP_MINUS_3);
#elif(_REGISTER_BLOCK_SIZE==5)
            nProd	  =  nX1*((DOUBLEDIGIT) yTOP_MINUS_3);
#else
            nProd	  =  nX0*((DOUBLEDIGIT) yTOP_MINUS_3);
#endif
#if(_REGISTER_BLOCK_SIZE>4)
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==5)
            nProd	  =  nX2*((DOUBLEDIGIT) yTOP_MINUS_4);
#else
            nProd	  =  nX1*((DOUBLEDIGIT) yTOP_MINUS_4);
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
            nProd	  =  nX2*((DOUBLEDIGIT) yTOP_MINUS_5);
#endif
#endif
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
            pZ[i+j+3] =  (DIGIT) nSum;
            nX3		  =  pX[i+4];
#if(_REGISTER_BLOCK_SIZE>4)
            nProd	  =  nX4*((DOUBLEDIGIT) yTOP);
            nSum	  =  (nProd&c_nClearHigh) + pZ[i+j+4] + nCarry;
            nCarry	  =  (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==5)
            nProd	  =  nX0*((DOUBLEDIGIT) yTOP_MINUS_1);
#else // == 6
            nProd	  =  nX5*((DOUBLEDIGIT) yTOP_MINUS_1);
#endif
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==5)
            nProd	  =  nX1*((DOUBLEDIGIT) yTOP_MINUS_2);
#else // == 6
            nProd	  =  nX0*((DOUBLEDIGIT) yTOP_MINUS_2);
#endif
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==5)
            nProd	  =  nX2*((DOUBLEDIGIT) yTOP_MINUS_3);
#else
            nProd	  =  nX1*((DOUBLEDIGIT) yTOP_MINUS_3);
#endif
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
#if(_REGISTER_BLOCK_SIZE==5)
            nProd	  =  nX3*((DOUBLEDIGIT) yTOP_MINUS_4);
#else
            nProd	  =  nX2*((DOUBLEDIGIT) yTOP_MINUS_4);
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
            nProd	  =  nX3*((DOUBLEDIGIT) yTOP_MINUS_5);
#endif
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
            pZ[i+j+4] =  (DIGIT) nSum;
            nX4		  =  pX[i+5];
#if(_REGISTER_BLOCK_SIZE>5)
            nProd	  =  nX5*((DOUBLEDIGIT) yTOP);
            nSum	  =  (nProd&c_nClearHigh) + pZ[i+j+5] + nCarry;
            nCarry	  =  (nProd>>c_nDigitSize);
            nProd	  =  nX0*((DOUBLEDIGIT) yTOP_MINUS_1);
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
            nProd	  =  nX1*((DOUBLEDIGIT) yTOP_MINUS_2);
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
            nProd	  =  nX2*((DOUBLEDIGIT) yTOP_MINUS_3);
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
            nProd	  =  nX3*((DOUBLEDIGIT) yTOP_MINUS_4);
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize);
            nProd	  =  nX4*((DOUBLEDIGIT) yTOP_MINUS_5);
            nSum	  += (nProd&c_nClearHigh);
            nCarry	  += (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
            pZ[i+j+5] =  (DIGIT) nSum;
            nX5		  =  pX[i+6];
#endif
#endif
#endif
#endif
        }
        nProd	  =  nX0*((DOUBLEDIGIT) yTOP);
        nSum	  =  (nProd&c_nClearHigh) + pZ[i+j] + nCarry;
        nCarry	  =  (nProd>>c_nDigitSize);
        nProd	  =  nX1*((DOUBLEDIGIT) yTOP_MINUS_1);
#if(_REGISTER_BLOCK_SIZE>2)
        nSum	  += (nProd&c_nClearHigh);
        nCarry	  += (nProd>>c_nDigitSize);
        nProd	  =  nX2*((DOUBLEDIGIT) yTOP_MINUS_2);
#if(_REGISTER_BLOCK_SIZE>3)
        nSum	  += (nProd&c_nClearHigh);
        nCarry	  += (nProd>>c_nDigitSize);
        nProd	  =  nX3*((DOUBLEDIGIT) yTOP_MINUS_3);
#if(_REGISTER_BLOCK_SIZE>4)
        nSum	  += (nProd&c_nClearHigh);
        nCarry	  += (nProd>>c_nDigitSize);
        nProd	  =  nX4*((DOUBLEDIGIT) yTOP_MINUS_4);
#if(_REGISTER_BLOCK_SIZE>5)
        nSum	  += (nProd&c_nClearHigh);
        nCarry	  += (nProd>>c_nDigitSize);
        nProd	  =  nX5*((DOUBLEDIGIT) yTOP_MINUS_5);
#endif
#endif
#endif
#endif
        nSum	  += (nProd&c_nClearHigh);
        nCarry	  += (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
        pZ[i+j]	  =  (DIGIT) nSum;
        nProd	  =  nX1*((DOUBLEDIGIT) yTOP);
#if(_REGISTER_BLOCK_SIZE>2)
        nSum	  =  (nProd&c_nClearHigh) + pZ[i+j+1] + nCarry;
        nCarry	  =  (nProd>>c_nDigitSize);
        nProd	  =  nX2*((DOUBLEDIGIT) yTOP_MINUS_1);
#if(_REGISTER_BLOCK_SIZE>3)
        nSum	  += (nProd&c_nClearHigh);
        nCarry    += (nProd>>c_nDigitSize);
        nProd	  =  nX3*((DOUBLEDIGIT) yTOP_MINUS_2);
#if(_REGISTER_BLOCK_SIZE>4)
        nSum	  += (nProd&c_nClearHigh);
        nCarry	  += (nProd>>c_nDigitSize);
        nProd	  =  nX4*((DOUBLEDIGIT) yTOP_MINUS_3);
#if(_REGISTER_BLOCK_SIZE>5)
        nSum	  += (nProd&c_nClearHigh);
        nCarry	  += (nProd>>c_nDigitSize);
        nProd	  =  nX5*((DOUBLEDIGIT) yTOP_MINUS_4);
#endif
#endif
#endif
        nSum	  += (nProd&c_nClearHigh);
        nCarry	  += (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
        pZ[i+j+1] =  (DIGIT) nSum;
        nProd	  =  nX2*((DOUBLEDIGIT) yTOP);
#if(_REGISTER_BLOCK_SIZE>3)
        nSum	  =  (nProd&c_nClearHigh) + pZ[i+j+2] + nCarry;
        nCarry	  =  (nProd>>c_nDigitSize);
        nProd	  =  nX3*((DOUBLEDIGIT) yTOP_MINUS_1);
#if(_REGISTER_BLOCK_SIZE>4)
        nSum	  += (nProd&c_nClearHigh);
        nCarry	  += (nProd>>c_nDigitSize);
        nProd	  =  nX4*((DOUBLEDIGIT) yTOP_MINUS_2);
#if(_REGISTER_BLOCK_SIZE>5)
        nSum	  += (nProd&c_nClearHigh);
        nCarry	  += (nProd>>c_nDigitSize);
        nProd	  =  nX5*((DOUBLEDIGIT) yTOP_MINUS_3);
#endif
#endif
        nSum	  += (nProd&c_nClearHigh);
        nCarry	  += (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
        pZ[i+j+2] =  (DIGIT) (nSum&c_nClearHigh);
        nProd	  =  nX3*((DOUBLEDIGIT) yTOP);
#if(_REGISTER_BLOCK_SIZE>4)
        nSum	  =  (nProd&c_nClearHigh) + pZ[i+j+3] + nCarry;
        nCarry	  =  (nProd>>c_nDigitSize);
        nProd	  =  nX4*((DOUBLEDIGIT) yTOP_MINUS_1);
#if(_REGISTER_BLOCK_SIZE>5)
        nSum	  += (nProd&c_nClearHigh);
        nCarry	  += (nProd>>c_nDigitSize);
        nProd	  =  nX5*((DOUBLEDIGIT) yTOP_MINUS_2);
#endif
        nSum	  += (nProd&c_nClearHigh);
        nCarry	  += (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
        pZ[i+j+3] =  (DIGIT) nSum;
        nProd	  =  nX4*((DOUBLEDIGIT) yTOP);
#if(_REGISTER_BLOCK_SIZE>5)
        nSum	  =  (nProd&c_nClearHigh) + pZ[i+j+4] + nCarry;
        nCarry	  =  (nProd>>c_nDigitSize);
        nProd	  =  nX5*((DOUBLEDIGIT) yTOP_MINUS_1);
        nSum	  += (nProd&c_nClearHigh);
        nCarry	  += (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
        pZ[i+j+4] =  (DIGIT) (nSum&c_nClearHigh);
        nProd	  =  nX5*((DOUBLEDIGIT) yTOP);
#undef yTOP_MINUS_5
#endif
#undef yTOP_MINUS_4
#endif
#undef yTOP_MINUS_3
#endif
#undef yTOP_MINUS_2
#endif
        nSum			               =  (nProd&c_nClearHigh)  + pZ[i+j+_REGISTER_BLOCK_SIZE-1] + nCarry;
        nCarry		                   =  (nProd>>c_nDigitSize) + (nSum>>c_nDigitSize);
        pZ[i+j+_REGISTER_BLOCK_SIZE-1] =  (DIGIT) nSum;
        nCarry		                   =  pZ[i+j+_REGISTER_BLOCK_SIZE] + nCarry;
        pZ[i+j+_REGISTER_BLOCK_SIZE]   =  (DIGIT) nCarry;
        nCarry		                   =  (nCarry>>c_nDigitSize);
        if(nCarry)
        {
            do
            {
                i++;
                nCarry                       += pZ[i+j+_REGISTER_BLOCK_SIZE];
                pZ[i+j+_REGISTER_BLOCK_SIZE] =  (DIGIT) nCarry;
                nCarry                       =  (nCarry>>c_nDigitSize);
            }
            while(nCarry);
        }
    }
#undef yTOP_MINUS_1
#undef yTOP
#endif
#if(_CollectDetailedTimingData)
#ifndef _TestingBasicMultiplyDirectly
    dwTimestamp = s_Timer.GetMicroseconds();
    s_nProcessTimes[eBasicMultiply] += dwTimestamp-dwTime;
    s_nMultiplyCalls[eBasicMultiply]++;
#endif
#endif
}