#pragma once
#include "TestConstants.h"
#include "ArithmeticBox.h"
#include "CUnsignedArithmeticHelper.h"
#include "CArithmeticTestHelper.h"
#include "CBigIntegerVectors.h"
#include "CBigIntegerMatrix.h"
#include "SSystemData.h"
#include "CRandomGenerator.h"
#include "math.h"
#include "..\BigIntegersBase\SmallPrimes.h"
#pragma warning(disable:4267)    // conversion from 'size_t' to 'unsigned int' -- possible loss of data

void CArithmeticPerformanceTester::SaveMultiplicationThresholds()
{
    for(int i=0; i<CUnsignedArithmeticHelper::c_n2NBynSizeBreakpoints; i++)
    {
        m_pnTemp2NByNBreakpoints[i]       = c_pn2NByNBreakpoints[i];
        m_pnTemp2NByNSquareBreakpoints[i] = c_pn2NByNSquareBreakpoints[i];
    }
    for(int i=0; i<eNumMultiplyAlgorithms-1; i++)
    {
        m_pnTempMultiplicationThresholds[i] = c_pnMultiplicationThresholds[i];
        m_pnTempSquareThresholds[i]         = c_pnSquareThresholds[i];
    }
}

void CArithmeticPerformanceTester::RestoreMultiplicationThresholds()
{
    for(int i=0; i<CUnsignedArithmeticHelper::c_n2NBynSizeBreakpoints; i++)
    {
        c_pn2NByNBreakpoints[i]       = m_pnTemp2NByNBreakpoints[i];
        c_pn2NByNSquareBreakpoints[i] = m_pnTemp2NByNSquareBreakpoints[i];
    }
    for(int i=0; i<eNumMultiplyAlgorithms-1; i++)
    {
        c_pnMultiplicationThresholds[i] = m_pnTempMultiplicationThresholds[i];
        c_pnSquareThresholds[i]         = m_pnTempSquareThresholds[i];
    }
}

void CArithmeticPerformanceTester::SpeedCheckBasicMultiply()
{
#if(_CollectDetailedTimingData)
    DWORD64 dwDummy;
#endif
    size_t       nIterations;
    const size_t c_nMinSize     = 1;
    const size_t c_nMaxSize     = 36; // the cutover point between basic multiply and 3 by 2 multiply seems to be around 32 for both large and small DIGITs
    DWORD64      pnTotalTime[6] = { 0,0,0,0,0,0 };
    DWORD64      pnTotalTimeLarge[6] = { 0,0,0,0,0,0 };
    DIGIT        *nX            = new DIGIT[c_nMaxSize];
    DIGIT        *nY            = new DIGIT[c_nMaxSize];
    DIGIT        *nZ            = new DIGIT[2*c_nMaxSize];
    printf("\nIf you're not doing this in retail, you're not getting good results\n");
    printf("SpeedCheckBasicMultiply\n");
    for(size_t nSize = c_nMinSize; nSize <= c_nMaxSize; nSize++) // *= 10)
    {
        nIterations = 10000;
        nIterations = nIterations*nIterations/10;
        for(int nAlgorithm=0;nAlgorithm<6;nAlgorithm++)
        {
            for(int i=0;i<c_nMaxSize;i++)
            {
                nX[i]        = (DIGIT) -1;
                nY[i]        = (DIGIT) -1;
                nZ[i<<1]     = (DIGIT) -1;
                nZ[1+(i<<1)] = (DIGIT) -1;
            }
            DWORD64 dw64Start = s_Timer.GetMicroseconds();
            for(size_t nIterationCount=0;nIterationCount<nIterations;nIterationCount++)
            {
                switch(nAlgorithm)
                {
                case 0:
                    BasicMultiplyReg1(nSize,nSize,nX,nY,nZ,false);
                    break;
                case 1:
                    BasicMultiplyReg2(nSize,nSize,nX,nY,nZ,false);
                    break;
                case 2:
                    BasicMultiplyReg3(nSize,nSize,nX,nY,nZ,false);
                    break;
                case 3:
                    BasicMultiplyReg4(nSize,nSize,nX,nY,nZ,false);
                    break;
                case 4:
                    BasicMultiplyReg5(nSize,nSize,nX,nY,nZ,false);
                    break;
                case 5:
                    BasicMultiplyReg6(nSize,nSize,nX,nY,nZ,false);
                    break;
                }
            }
            dw64Start = s_Timer.GetMicroseconds() - dw64Start;
            pnTotalTime[nAlgorithm] += dw64Start;
            if(20<=nSize) pnTotalTimeLarge[nAlgorithm] += dw64Start;
            printf("Size (BYTEs): %i Size (DIGITs): %i\tRegister block size: %i\tIterations: %i\tTime: %I64u\n",nSize*sizeof(DIGIT),nSize,nAlgorithm+1,nIterations,dw64Start);
        }
    }
    for (int i=0; i<6; i++)
    {
        printf("Total microseconds for %i registers: %I64u 20+ DIGITS only: %I64u\n", i + 1, pnTotalTime[i], pnTotalTimeLarge[i]);
    }
    delete nX;
    delete nY;
    delete nZ;
}

void CArithmeticPerformanceTester::CompareBasicMultiplicationToLongShortMultiplication()
{
    printf("\nIf you're not doing this in retail, you're not getting good results\n");
    printf("Compare basic to short-long\n");
    DWORD64 dwTimesMult[13],dwTimesMultAdd[13];
    const unsigned int c_nMaxSizeY = 16384;
    DIGIT *pX = (DIGIT *) malloc(sizeof(DIGIT)*(12+c_nMaxSizeY)*2);
    DIGIT *pY = pX + 12;
    DIGIT *pZ = pY + c_nMaxSizeY;
    for(int i=0; i<12+c_nMaxSizeY; i++) pX[i] = (DIGIT) -1;
    for(size_t j=1; j<=c_nMaxSizeY; j*=2)
    {
        for(size_t i=1; i<=12; i++)
        {
            if(j<i) continue;
            size_t  nIterations = ((size_t) 10000)*(12*c_nMaxSizeY)/(i*j);
            DWORD64 dwTimeBasic = s_Timer.GetMicroseconds();
            for(int k=0;k<nIterations;k++)
            {
                MultUBasic(i, j, pX, pY, pZ, false);
            }
            DWORD64 dwTimeShortLong = s_Timer.GetMicroseconds();
            dwTimeBasic = dwTimeShortLong - dwTimeBasic;
            for(int k=0;k<nIterations;k++)
            {
                MultUShortLong(i, j, pX, pY, pZ);
            }
            dwTimeShortLong = s_Timer.GetMicroseconds() - dwTimeShortLong;
            dwTimesMult[i]  = dwTimeShortLong;
            DWORD64 dwTimeBasicMultAdd = s_Timer.GetMicroseconds();
            for(int k=0;k<nIterations;k++)
            {
                MultUBasic(i, j, pX, pY, pZ, true);
            }
            DWORD64 dwTimeShortLongAdd = s_Timer.GetMicroseconds();
            dwTimeBasicMultAdd = dwTimeShortLongAdd - dwTimeBasicMultAdd;
            for(int k=0;k<nIterations;k++)
            {
                MultAddUShortLong(i, j, pX, pY, pZ);
            }
            dwTimeShortLongAdd = s_Timer.GetMicroseconds() - dwTimeShortLongAdd;
            dwTimesMultAdd[i]  = dwTimeShortLongAdd;
            printf("Size: %ux%u\n\tShort/long:          %I64u\n\tMult/add short/long: %I64u\n\tBasic:               %I64u\n\tBasic mult/add:      %I64u\n\n", i, j, dwTimeShortLong, dwTimeShortLongAdd, dwTimeBasic, dwTimeBasicMultAdd);
        }
    }
    free(pX);
}

void CArithmeticPerformanceTester::CompareBasicMultiplicationToStripedMultiplication()
{
    printf("\nIf you're not doing this in retail, you're not getting good results\n");
    printf("Compare basic to striped\n");
    const unsigned int c_nMaxSizeY = 16384;
    DIGIT *pX = (DIGIT *) malloc(sizeof(DIGIT)*(60+c_nMaxSizeY)*2);
    DIGIT *pY = pX + 60;
    DIGIT *pZ = pY + c_nMaxSizeY;
    for(int i=0; i<60+c_nMaxSizeY; i++) pX[i] = (DIGIT) -1;
    for(size_t j=16; j<=c_nMaxSizeY; j*=2)
    {
        for(size_t i=13; i<=60; i++)
        {
            if(j<i) continue;
            size_t  nIterations = ((size_t) 1000)*(12*c_nMaxSizeY)/(i*j);
            DWORD64 dwTimeBasic = s_Timer.GetMicroseconds();
            for(int k=0;k<nIterations;k++)
            {
                MultUBasic(i, j, pX, pY, pZ, false);
            }
            DWORD64 dwTimeShortLong = s_Timer.GetMicroseconds();
            dwTimeBasic = dwTimeShortLong - dwTimeBasic;
            for(int k=0;k<nIterations;k++)
            {
                MultUStriped(i, j, pX, pY, pZ, false);
            }
            dwTimeShortLong = s_Timer.GetMicroseconds() - dwTimeShortLong;
            DWORD64 dwTimeBasicMultAdd = s_Timer.GetMicroseconds();
            for(int k=0;k<nIterations;k++)
            {
                MultUBasic(i, j, pX, pY, pZ, true);
            }
            DWORD64 dwTimeShortLongAdd = s_Timer.GetMicroseconds();
            dwTimeBasicMultAdd = dwTimeShortLongAdd - dwTimeBasicMultAdd;
            for(int k=0;k<nIterations;k++)
            {
                MultUStriped(i, j, pX, pY, pZ, true);
            }
            dwTimeShortLongAdd = s_Timer.GetMicroseconds() - dwTimeShortLongAdd;
            printf("Size: %ux%u\n\tBasic:            %I64u\n\tMult/add basic:   %I64u\n\tStriped:          %I64u\n\tMult/add striped: %I64u\n", i, j, dwTimeBasic, dwTimeBasicMultAdd, dwTimeShortLong, dwTimeShortLongAdd);
        }
    }
    free(pX);
}

void CArithmeticPerformanceTester::CompareBaseMultiplicationToFFT()
{
    CBigIntegerForTest nX,nY,nXCopy,nYCopy,nProduct,nProductBaseline, nProductBaselineSquare;
    DWORD64            dwStartTime;
    CArithmeticBox     cBox;
    CWorkspace         cWork;
    size_t             nProductSize;
    printf("\nIf you're not doing this with a retail build, you're not getting good numbers\n");
    printf("CompareBseMultiplicationToFFT\n");
    SaveMultiplicationThresholds();
    // note size 5 DIGITs is the smallest size FFTMult will work with; we start with 8 -- smallest power of 2 which is at least 5
    for(size_t i=8*_DIGIT_SIZE_IN_BITS; i<=((size_t) 1)<<31; i=i<<1)
    {
        size_t nFFTLength,nFieldSize,nChunkSize;
        BYTE   byChunkSize;
        SBitShift nRoot;
        nX.SetRandom(i);
        nY.SetRandom(i);
        nXCopy = nX;
        nYCopy = nY;
        GetFFTSize(nX.GetSize(),nY.GetSize(),nFFTLength,nFieldSize,nChunkSize,byChunkSize,nRoot);
        nProduct.Reserve(nX.GetSize()+nY.GetSize()+1);
        nProductBaseline.Reserve(nX.GetSize()+nY.GetSize());
        nProductBaselineSquare.Reserve(nX.GetSize()+nY.GetSize());
        c_pnMultiplicationThresholds[e2NByN] = nX.GetSize()+nY.GetSize(); // so we don't use FFT multiply
        c_pnSquareThresholds[e2NByN]         = nX.GetSize()+nY.GetSize(); // so we don't use FFT multiply
        printf("Size %i x %i bytes\tMemory (basic): %I64u kB FFT: %I64u kB\n",
               nX.GetSize()*sizeof(DIGIT),
               nY.GetSize()*sizeof(DIGIT),
               MultiplyMemoryNeeds(nX.GetSize(),nY.GetSize())*sizeof(DIGIT)/1024,
               FFTMultiplyMemoryNeeds(nX.GetSize(),nY.GetSize(),false)*sizeof(DIGIT)/1024);
        if(!cWork.Reserve(MultiplyMemoryNeeds(nX.GetSize(),nY.GetSize())))
        {
            printf("couldn't allocate workspace -- baseline\n");
            break;
        }
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        Multiply(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProductBaseline.GetValue(),cWork.GetSpace());
        dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        printf("Non-FFT multiply:  %I64u microseconds\n",dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        Square(nX.GetSize(), nX.GetValue(), nProductBaselineSquare.GetValue(), cWork.GetSpace());
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        printf("Non-FFT square:    %I64u microseconds\n", dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        nProductSize = nX.GetSize()+nY.GetSize();
        while(0<nProductSize && 0==nProductBaseline.GetValue()[nProductSize-1])
        {
            nProductSize--;
        }
        nProductBaseline.SetSize(nProductSize);
        nProductSize = nX.GetSize() + nY.GetSize();
        while (0 < nProductSize && 0 == nProductBaselineSquare.GetValue()[nProductSize - 1])
        {
            nProductSize--;
        }
        nProductBaselineSquare.SetSize(nProductSize);
        if(!cWork.Reserve(FFTMultiplyMemoryNeeds(nX.GetSize(),nY.GetSize(),false)))
        {
            printf("couldn't allocate workspace -- FFT\n");
            break;
        }
        ResetTimingData();
        RestoreMultiplicationThresholds(); // so we DO use FFT multiply for subproblems (if appropriate to the size)
        // force top level at least to use FFT
        if (c_pnMultiplicationThresholds[e2NByN] <= nX.GetSize()) c_pnMultiplicationThresholds[e2NByN] = nX.GetSize() - 1;
        if (c_pnMultiplicationThresholds[e2NByN] <= nY.GetSize()) c_pnMultiplicationThresholds[e2NByN] = nY.GetSize() - 1;
        if (c_pnSquareThresholds[e2NByN] <= nX.GetSize())         c_pnSquareThresholds[e2NByN] = nX.GetSize() - 1;
        if (c_pnSquareThresholds[e2NByN] <= nY.GetSize())         c_pnSquareThresholds[e2NByN] = nY.GetSize() - 1;
        dwStartTime = s_Timer.GetMicroseconds();
        Multiply(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProduct.GetValue(),cWork.GetSpace());
        dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        nProductSize = nX.GetSize()+nY.GetSize();
        while(0<nProductSize && 0==nProduct.GetValue()[nProductSize-1])
        {
            nProductSize--;
        }
        nProduct.SetSize(nProductSize);
        printf("FFT multiply:      %I64u microseconds\tField size: %I64u Length: %I64u\n",dwStartTime, nFieldSize, nFFTLength);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        if(nProduct != nProductBaseline)
        {
            printf("Oopsie!  Error found; best investigate\n");
            int nOffDigits = 0;
            for (int i = 0; i < nProductBaseline.GetSize(); i++)
            {
                if (nProduct.GetValue()[i] != nProductBaseline.GetValue()[i])
                {
                    if (0 == nOffDigits++) printf("First bad digit: %i; ", i);
                }
            }
            printf("%i total bad digits (of %i)\n", nOffDigits, nProductBaseline.GetSize());
            cWork.CheckBufferguard(); // note this is vaccuous in retail -- and why would we be doing a perf test in debug?
        }
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        Square(nX.GetSize(),nX.GetValue(),nProduct.GetValue(),cWork.GetSpace());
        dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        nProductSize = nX.GetSize() + nY.GetSize();
        while (0 < nProductSize && 0 == nProduct.GetValue()[nProductSize - 1])
        {
            nProductSize--;
        }
        nProduct.SetSize(nProductSize);
        printf("FFT square:        %I64u microseconds\n",dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        if (nProduct != nProductBaselineSquare)
        {
            cWork.CheckBufferguard(); // note this is vaccuous in retail -- and why would we be doing a perf test in debug?
            printf("Oopsie!  Error found; best investigate\n");
        }
        RestoreMultiplicationThresholds();
    }
}

// checks how long it takes to get the FFT in preparation for a multiplication of 2 numbers of two billion bits each
void CArithmeticPerformanceTester::FFTTimes()
{
    const size_t       c_nTwoBILLION = 2000000000;
    unsigned int       nStartTime;
    size_t             nFFTLength, nFieldSize, nFFTSpace;
    size_t             nChunkSize;
    SBitShift          nRootUnity;
    DIGIT              *pnFFT_x, *pnFFT_XInverse, *pnWorkspace;
    BYTE               byMaxOverflowSize;
    CBigIntegerForTest nX;
    printf("\nIf you're not doing this in retail, you're not getting good results\n");
    printf("FFTTimes\n");
    nX.SetRandom(c_nTwoBILLION);
    GetFFTSize(nX.GetSize(), nX.GetSize(), nFFTLength, nFieldSize, nChunkSize, byMaxOverflowSize, nRootUnity);
    nFFTSpace      = FFTMultiplyMemoryNeeds(nX.GetSize(), nX.GetSize(), false);
    pnFFT_x        = (DIGIT *) malloc(sizeof(DIGIT)*nFFTSpace);
    pnFFT_XInverse = pnFFT_x + (nFFTLength/2);
    pnWorkspace    = (DIGIT *) malloc(sizeof(DIGIT)*1000000); // should be plenty of space
    // do an untimed FFT, so always start with the same memory position
    FFT(nX.GetValue(), pnFFT_x, nX.GetSize(), nChunkSize, nChunkSize, nFFTLength, nFieldSize, nRootUnity, pnWorkspace);
    // and a timed one
    nStartTime = ::GetTickCount();
    FFT(nX.GetValue(), pnFFT_x, nX.GetSize(), nChunkSize, nChunkSize, nFFTLength, nFieldSize, nRootUnity, pnWorkspace);
    printf("Standard FFT took %i milliseconds for a %I64u-bit number\n",::GetTickCount()-nStartTime,c_nTwoBILLION);
    // Repeat for inverse FFT
    FFT_Inverse(pnFFT_x, pnFFT_XInverse, nFFTLength, nRootUnity, nFieldSize, pnWorkspace);
    nStartTime = ::GetTickCount();
    FFT_Inverse(pnFFT_x, pnFFT_XInverse, nFFTLength, nRootUnity, nFieldSize, pnWorkspace);
    printf("Standard FFT inverse took %i milliseconds for a %I64u-bit number\n", ::GetTickCount() - nStartTime, c_nTwoBILLION);
    free(pnFFT_x);
    free(pnWorkspace);
}

void CArithmeticPerformanceTester::TestMultiplyTimes()
{
    CBigIntegerForTest nX,nY,nProduct;
    DWORD64            dwStartTime;
    CWorkspace         cWork;
    size_t             nProductSize;
    printf("\nIf you're not doing this with a retail build, you're not getting good numbers.  All sizes in BYTES, not DIGITs!\n");
    printf("TestMultiplyTimes\n");
    for(size_t i=2;i<=(((size_t) 1)<<28);i=i<<1)
    {
        nX.SetRandom(i<<3);
        nY.SetRandom(i<<3);
        nProduct.Reserve(nX.GetSize()+nY.GetSize());
        size_t nMemoryNeeds = max(MultiplyMemoryNeeds(nX.GetSize(),nY.GetSize()), SquareMemoryNeeds(nX.GetSize(), nY.GetSize()));
        if(!cWork.Reserve(nMemoryNeeds))
        {
            printf("couldn't allocate workspace -- baseline\n");
            break;
        }
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        Multiply(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue(), cWork.GetSpace());
        dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        printf("Multiply two %i BYTE numbers:\t%I64u microseconds\n", nX.GetSize() * sizeof(DIGIT), dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        Square(nX.GetSize(), nX.GetValue(), nProduct.GetValue(), cWork.GetSpace());
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        printf("Square a     %i BYTE numbers:\t%I64u microseconds\n", nX.GetSize() * sizeof(DIGIT), dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
    }
}

void CArithmeticPerformanceTester::CompareMultiplicationAlgorithms()
{
    const unsigned int c_nMinProblemSize = 2000000, c_nMaxProblemSize = 128000000; // number of BYTEs in numbers to multiply
    CBigIntegerForTest nX, nY, nProduct;
    DWORD64            dwStartTime;
#if(_CollectDetailedTimingData)
    DWORD64            dwTimestamp;
#endif
    CWorkspace         cWork;
    size_t             nProductSize;
    SaveMultiplicationThresholds();
    printf("\nIf you're not doing this with a retail build, you're not getting good numbers.  All sizes in BYTES, not DIGITs!\n");
    printf("CompareMultiplicationAlgorithms\n");
    for (int nProblemSize = c_nMinProblemSize; nProblemSize <= c_nMaxProblemSize; nProblemSize *= 2)
    {
        nX.SetRandom(nProblemSize*8);
        nY.SetRandom(nProblemSize*8);
        nProduct.Reserve(nX.GetSize() + nY.GetSize());
        for (int eAlgorithm = eFFTMult; eBasicMultiply < eAlgorithm; eAlgorithm--)
        {
            c_pnMultiplicationThresholds[eAlgorithm] = 2000000000; // to force use of algorithm for any large problem
            c_pnSquareThresholds[eAlgorithm]         = 2000000000; // to force use of algorithm for any large problem
            unsigned int nMemoryNeeds = MultiplyMemoryNeeds(nX.GetSize(), nY.GetSize());
            if (!cWork.Reserve(nMemoryNeeds + 1))
            {
                printf("couldn't allocate workspace\n");
                return;
            }
            cWork.GetSpace()[nMemoryNeeds] = TEST_BUFFERGUARD; // validate not using more memory than expected
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
            Multiply(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue(), cWork.GetSpace());
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Multiply size:    %I64ux%I64u (BYTEs): %I64u microseconds (%s)\n",  nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime, GetMultiplicationAlgorithmName((EMultiplyAlgorithm) eAlgorithm));
            if (TEST_BUFFERGUARD != cWork.GetSpace()[nMemoryNeeds])
            {
                printf("Overran workspace memory bounds for algorithm %i multiply.  Oops.\n", eAlgorithm);
                return;
            }
            ReportMeasuredComponentTimingData(eMultiplicationMeasured);
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
            Square(nX.GetSize(), nX.GetValue(), nProduct.GetValue(), cWork.GetSpace());
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Square size:      %I64ux%I64u (BYTEs): %I64u microseconds (%s)\n", nX.GetSize()*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime, GetMultiplicationAlgorithmName((EMultiplyAlgorithm) eAlgorithm));
            if (TEST_BUFFERGUARD != cWork.GetSpace()[nMemoryNeeds])
            {
                printf("Overran workspace memory bounds for algorithm %i square.  Oops.\n", eAlgorithm);
                return;
            }
            ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        }
        if(nProblemSize<=4000000)
        {
            // only do basic multiply comparison for relatively small problem sizes -- too slow!
            c_pnMultiplicationThresholds[eBasicMultiply] = 10000000000; // to force use of algorithm for any large problem
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
            Multiply(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue(), cWork.GetSpace());
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Multiply size:    %I64ux%I64u (BYTEs): %I64u microseconds (striped)\n", nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime);
            ReportMeasuredComponentTimingData(eMultiplicationMeasured);
            dwStartTime = s_Timer.GetMicroseconds();
            MultUBasic(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue(), false);
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Multiply size:    %I64ux%I64u (BYTEs): %I64u microseconds (basic)\n", nX.GetSize() * sizeof(DIGIT), nY.GetSize() * sizeof(DIGIT), dwStartTime);
            dwStartTime = s_Timer.GetMicroseconds();
            MultOracle(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue());
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Multiply size:    %I64ux%I64u (BYTEs): %I64u microseconds (oracle)\n", nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime);
        }
        printf("\n");
        RestoreMultiplicationThresholds();
    }
}

void CArithmeticPerformanceTester::CompareDivideTimes()
{
    size_t             nWorkspaceMemoryNeeds;
    const unsigned int c_nMinSize = 1000, c_nMaxSize = 100000000; // my system can allocate enough memory for 100,000,000 -- but not 1,000,000,000
    CBigIntegerForTest nX, nXCopy, nY, nProduct1, nProduct2, nDiv;
    DWORD64            dwStartTime, dwMultTime;
    unsigned int       nIterations;
    CWorkspace         cWork;
    size_t             nDivSize, nRemainderSize;
    unsigned int       nDivideThresholdSmallOriginal = c_nDivideThresholdSmall;
    SaveMultiplicationThresholds();
    printf("\nIf you're not doing this with a retail build, you're not getting good numbers.  All sizes in BYTES, not DIGITs!\n");
    printf("CompareDivideTimes\n");
    for (int nSize = c_nMinSize; nSize <= c_nMaxSize; nSize *= 10)
    {
        nX.SetRandom(nSize*8); // want size in BYTEs; set random size bits
        nY.SetRandom(2*nSize*8); // want size in BYTES; set random size bits
        nProduct1.Reserve(nX.GetSize() + nY.GetSize());
        nProduct2.Reserve(nX.GetSize() + nY.GetSize());
        nDiv.Reserve(nY.GetSize()+1);
        cWork.Reserve(MultiplyMemoryNeeds(nX.GetSize(), nY.GetSize()));
        cWork.Reserve(DivisionMemoryNeeds(nX.GetSize() + nY.GetSize(), nX.GetSize()));
        cWork.Reserve(DivisionMemoryNeeds(nX.GetSize() + nY.GetSize(), nY.GetSize()));
        // find out how many iterations needed to take 10+ seconds for the given multiply size
        nIterations = 1;
        do
        {
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
            for (int i=0; i<nIterations; i++)
            {
                Multiply(nX.GetSize(), nX.GetSize(), nX.GetValue(), nY.GetValue(), nProduct1.GetValue(), cWork.GetSpace());
            }
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            if(1000000<dwStartTime) break; // 10 seconds better?  Or 1 second?
            nIterations *= 2;
        }
        while (true);
        printf("Time for %i %ix%i BYTE multiplications: %I64u microseconds\n", nIterations, nX.GetSize()*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        ResetTimingData();
        dwMultTime = dwStartTime;
        if(nX.GetSize()<=1000000)
        {
            c_nDivideThresholdSmall = 2000000000; // force the system to use basic division
            // bigger numbers just too slow!  Works fine.  You have been warned.
            dwStartTime = s_Timer.GetMicroseconds();
            for (int i=0; i<nIterations; i++)
            {
                memcpy(nProduct2.m_pnValue, nProduct1.m_pnValue, (nX.GetSize() + nX.GetSize())*sizeof(DIGIT));
                Divide(nX.GetSize() + nX.GetSize(), nX.GetSize(), nDivSize, nRemainderSize, nProduct2.GetValue(), nX.GetValue(), nDiv.GetValue(), cWork.GetSpace());
            }
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Time for %i divisions of %i BYTE number by %i BYTE number: %I64u microseconds (divide:multiply ratio: %f) -- basic\n", nIterations, 2*nX.GetSize()*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime, (float) dwStartTime/dwMultTime);
            ReportMeasuredComponentTimingData(eDivideMeasured);
            ResetTimingData();
            c_nDivideThresholdSmall = nDivideThresholdSmallOriginal;
        }
        dwStartTime = s_Timer.GetMicroseconds();
        for (int i=0; i<nIterations; i++)
        {
            memcpy(nProduct2.m_pnValue, nProduct1.m_pnValue, (nX.GetSize() + nX.GetSize())*sizeof(DIGIT));
            Divide(nX.GetSize() + nX.GetSize(), nX.GetSize(), nDivSize, nRemainderSize, nProduct2.GetValue(), nX.GetValue(), nDiv.GetValue(), cWork.GetSpace());
        }
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        printf("Time for %i divisions of %i BYTE number by %i BYTE number: %I64u microseconds (divide:multiply ratio: %f)\n", nIterations, 2*nX.GetSize()*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime, (float) dwStartTime/dwMultTime);
        ReportMeasuredComponentTimingData(eDivideMeasured);
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        for (int i=0; i<nIterations; i++)
        {
            Multiply(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct1.GetValue(), cWork.GetSpace());
        }
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        dwMultTime  = dwStartTime;
        printf("Time for %i %ix%i BYTE multiplications: %I64u microseconds\n", nIterations, nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        for(int i=0; i<nIterations; i++)
        {
            memcpy(nProduct2.m_pnValue, nProduct1.m_pnValue, (nX.GetSize() + nY.GetSize())*sizeof(DIGIT));
            Divide(nX.GetSize() + nY.GetSize(), nX.GetSize(), nDivSize, nRemainderSize, nProduct2.GetValue(), nX.GetValue(), nDiv.GetValue(), cWork.GetSpace());
        }
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        printf("Time for %i divisions of %i BYTE number by %i BYTE number: %I64u microseconds (divide:multiply ratio: %f)\n", nIterations, (nX.GetSize() + nY.GetSize())*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime, (float) dwStartTime/dwMultTime);
        ReportMeasuredComponentTimingData(eDivideMeasured);
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        for(int i=0; i<nIterations; i++)
        {
            memcpy(nProduct2.m_pnValue, nProduct1.m_pnValue, (nX.GetSize() + nY.GetSize())*sizeof(DIGIT));
            Divide((nX.GetSize() + nY.GetSize()), nY.GetSize(), nDivSize, nRemainderSize, nProduct2.GetValue(), nY.GetValue(), nDiv.GetValue(), cWork.GetSpace());
        }
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        printf("Time for %i divisions of %i BYTE number by %i BYTE number: %I64u microseconds (divide:multiply ratio: %f)\n", nIterations, (nX.GetSize() + nY.GetSize())*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime, (float) dwStartTime/dwMultTime);
        ReportMeasuredComponentTimingData(eDivideMeasured);
    }
    for(int nSize=100000; nSize<=c_nMaxSize; nSize *= 10)
    {
        nX.SetRandom(16*nSize);
        nY.SetRandom(8*nSize);
        nXCopy = nX;
        nDiv.Reserve(nX.GetSize()-nY.GetSize()+1);
        ResetTimingData();
        nWorkspaceMemoryNeeds = DivisionMemoryNeeds(nX.GetSize(), nY.GetSize());
        cWork.Reserve(nWorkspaceMemoryNeeds);
        dwStartTime = s_Timer.GetMicroseconds();
        Divide(nX.GetSize(), nY.GetSize(), nDivSize, nRemainderSize, nXCopy.GetValue(), nY.GetValue(), nDiv.GetValue(), cWork.GetSpace());
        printf("Dividing a %i-BYTE number by a %i-BYTE one took %I64u microseconds\n", nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), s_Timer.GetMicroseconds() - dwStartTime);
        ReportMeasuredComponentTimingData(eDivideMeasured);
    }
}

void CArithmeticPerformanceTester::GCDTimes()
{
    CArithmeticBox     cBox;
    CRandomGenerator   cRandom;
    CBigInteger        x, y, nGCD, nXCoef, nYCoef;
    bool               bXCoefNeg;
    size_t             nGCDSize, nXCoefSize, nYCoefSize;
    const unsigned int c_nMaxDigits          = 0x1000;
    const unsigned int c_nStartingIterations = 0x1000000;
    unsigned int       nIterations           = c_nStartingIterations;

    printf("\nIf you're not doing this in retail, you're not getting good results\n");
    printf("GCDTimes\n");
    x.Reserve(c_nMaxDigits);
    y.Reserve(c_nMaxDigits);
    for(int nDigits=1; nDigits<=c_nMaxDigits; nDigits=(nDigits<<1))
    {
        ResetTimingData();
        unsigned int nTime = ::GetTickCount();
        for (int i=0; i<nIterations; i++)
        {
            do
            {
                cRandom.RandomBits(nDigits, 0, true, x);
            }
            while(0==x.GetSize());
            do
            {
                cRandom.RandomBits(nDigits, 0, true, y);
            }
            while(0==y.GetSize());
            cBox.GCD(x, y, nGCD);
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to get the GCD of %i pairs of %i-byte numbers:            %i milliseconds\n", nIterations, nDigits*sizeof(DIGIT), nTime);
        ReportMeasuredComponentTimingData(eGCDMeasured);
        ResetTimingData();
        nTime = ::GetTickCount();
        for (int i=0; i<nIterations; i++)
        {
            do
            {
                cRandom.RandomBits(nDigits, 0, true, x);
            }
            while(0==x.GetSize());
            do
            {
                cRandom.RandomBits(nDigits, 0, true, y);
            }
            while(0==y.GetSize());
            cBox.GCDExtended(x, y, nGCD, nXCoef, nYCoef);
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to get the GCD of %i pairs of %i-byte numbers (extended): %i milliseconds\n", nIterations, nDigits*sizeof(DIGIT), nTime);
        ReportMeasuredComponentTimingData(eGCDMeasured);
        nIterations /= 2;
    }
}

void CArithmeticPerformanceTester::PowerModulusMontgomeryVsStandard()
{
    CRandomGenerator   cRandom;
    CBigInteger        nBase, nPower, nModulus, nResult, nNPrime, nRPrime, nPowerModulus;
    size_t             nNPrimeSize, nRPrimeSize, nMontSize, nPowerModSize, nLeadDigit, nLeadBit;
    unsigned int       nTime;
    const unsigned int c_nMinBits   = 16;
    const unsigned int c_nMaxBits   = 65536;
    unsigned int       nIterations  = 0x1000000;
    DIGIT              *pnWorkspace = (DIGIT *) malloc(sizeof(DIGIT)*1000000);
    printf("\nIf you're not doing this in retail, you're not getting good results\n");
    printf("PowerModulusMontgomeryVsStandard\n");
    for(int nBits=c_nMinBits; nBits<=c_nMaxBits; nBits *= 2)
    {
        cRandom.RandomBits(nBits/_DIGIT_SIZE_IN_BITS, nBits%_DIGIT_SIZE_IN_BITS, true, nBase);
        cRandom.RandomBits(nBits/_DIGIT_SIZE_IN_BITS, nBits%_DIGIT_SIZE_IN_BITS, true, nPower);
        cRandom.RandomBits(nBits/_DIGIT_SIZE_IN_BITS, nBits%_DIGIT_SIZE_IN_BITS, true, nModulus);
        nResult.Reserve(2*nModulus.GetSize()+1);
        nModulus.GetValue()[0] |= 1; // force the modulus to be odd, so it is suitable for Montgomery
        // first, standard power modulus
        ResetTimingData();
        nTime = ::GetTickCount();
        for(int i=0;i<nIterations; i++)
        {
            PowerModulus(nBase.GetSize(), nPower.GetSize(), nModulus.GetSize(), nPowerModSize, nBase.GetValue(), nPower.GetValue(), nModulus.GetValue(), nResult.GetValue(), pnWorkspace);
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i  standard  power-modulus operations of size %i bits: %i milliseconds\n", nIterations, nBits, nTime);
        ReportMeasuredComponentTimingData(ePowerModulusMeasured);
        // Then, Montgomery power-modulus
        nNPrime.Reserve(nModulus.GetSize());
        nRPrime.Reserve(nModulus.GetSize());
        GetMontgomeryParameters(nModulus.GetSize(), nNPrimeSize, nRPrimeSize, nModulus.GetValue(), nNPrime.GetValue(), nRPrime.GetValue(), pnWorkspace);
        GetLeadBit(nModulus.GetSize(), nModulus.GetValue(), nLeadDigit, nLeadBit);
        nPowerModulus.Reserve(2*nModulus.GetSize() + 1);
        ResetTimingData();
        nTime = ::GetTickCount();
        for(int i=0;i<nIterations; i++)
        {
            MontgomeryPowerModulus(nBase.GetSize(),
                                   nPower.GetSize(),
                                   nModulus.GetSize(),
                                   nNPrimeSize,
                                   nRPrimeSize,
                                   nPowerModSize,
                                   nBase.GetValue(),
                                   nPower.GetValue(),
                                   nRPrime.GetValue(),
                                   nModulus.GetValue(),
                                   nNPrime.GetValue(),
                                   nPowerModulus.GetValue(),
                                   pnWorkspace);
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i Montgomery power-modulus operations of size %i bits: %i milliseconds\n", nIterations, nBits, nTime);
        ReportMeasuredComponentTimingData(ePowerModulusMeasured);
        nIterations /= 4;
    }
    free(pnWorkspace);
}

void CArithmeticPerformanceTester::SquareRootTimes()
{
#if _CollectDetailedTimingData
    DWORD64            dwTimestamp = s_Timer.GetMicroseconds();
#endif
    CArithmeticBox     cBox;
    size_t             nRootSize;
    CBigIntegerForTest nX1, nX1Copy, nX2, nX2Copy, nSqrtX, nExtra;
    DIGIT              *pWorkspace   = (DIGIT *) malloc(sizeof(DIGIT)*100000000);
    const unsigned int c_nMinBitSize = 16, c_nMaxBitSize = 524288;
    unsigned       int nTests        = c_nMaxBitSize*16, nTime;
    printf("\nIf you're not doing this in retail, you're not getting good results\n");
    printf("SquareRootTimes\n");
    for(int nSize=c_nMinBitSize; nSize<=c_nMaxBitSize; nSize *= 2)
    {
        nX2.SetSize(0);
        // want to make sure we hit 3-DIGIT numbers, too
        if(_DIGIT_SIZE_IN_BITS*4 == nSize) nSize -= _DIGIT_SIZE_IN_BITS;
        else if(_DIGIT_SIZE_IN_BITS*6 == nSize) nSize -= (2*_DIGIT_SIZE_IN_BITS);
        nX1.SetRandom(nSize);
        nSqrtX.Reserve(nX1.GetSize()+1); // extra digit for overflow --  only needed in single-digit case
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
#if _CollectDetailedTimingData
            SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
            SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i square roots of a %i bit number (Newton):                  %i milliseconds (%f average)\n",nTests,nSize,nTime,((float) nTime)/nTests);
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
#if _CollectDetailedTimingData
            GeneralSquareRootNewton(nX2.GetSize(), nX1.GetSize(), nRootSize, nX2.GetValue(), nX1.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
            GeneralSquareRootNewton(nX2.GetSize(), nX1.GetSize(), nRootSize, nX2.GetValue(), nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i square roots of a %i bit number using general Newton:      %i milliseconds (%f average)\n",nTests,nSize,nTime,((float) nTime)/nTests);
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
#if _CollectDetailedTimingData
            SquareRootRecursive(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
            SquareRootRecursive(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
        }
        nTime = ::GetTickCount() - nTime;
        nSqrtX.SetSize(nRootSize);
        printf("Time to do %i square roots of a %i bit number using recursive algorithm: %i milliseconds (%f average)\n",nTests,nSize,nTime,((float) nTime)/nTests);
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
            cBox.Divide(nX1, nSqrtX, nX2, nExtra);
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i divides of a %i bit number by its square root:             %i milliseconds (%f average)\n",nTests,nSize,nTime,((float) nTime)/nTests);
        // Compare general recursive square root vs its Newton equivalent, on sizes roughly in line with what would get from the square root function:
        // x1 ~ 2/3 the size of x2 (or in this case x2 ~ 2/3 the size of x1, since numbers reversed in this test)
        nX2.SetRandom(2*nSize/3);
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
#if _CollectDetailedTimingData
            GeneralSquareRootNewton(nX2.GetSize(), nX1.GetSize(), nRootSize, nX2.GetValue(), nX1.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
            GeneralSquareRootNewton(nX2.GetSize(), nX1.GetSize(), nRootSize, nX2.GetValue(), nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i general roots of a %i, %i bit numbers: Newton:             %i milliseconds (%f average)\n",nTests,2*nSize/3,nSize,nTime,((float) nTime)/nTests);
        nX2Copy.Reserve(nX1.GetSize()+1); // needs a bit of extra space!
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
            // GeneralSquareRootRecursive destructive -- copy data
            nX1Copy = nX1;
            nX2Copy = nX2;
#if _CollectDetailedTimingData
            GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
            GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i general roots of a %i, %i bit numbers: Recursive:          %i milliseconds (%f average)\n\n",nTests,2*nSize/3,nSize,nTime,((float) nTime)/nTests);
        nTests /= 2;
    }
    nX1.SetRandom(c_nMaxBitSize*64);
    nSqrtX.Reserve(nX1.GetSize());
    nX2Copy.Reserve(nX1.GetSize()+1); // needs more working space
    ResetTimingData();
    nTime   = ::GetTickCount();
    cBox.SQRT(nX1, nSqrtX);
    printf("And the time to do a single %i bit square root using the full algorithm: %i milliseconds\n",c_nMaxBitSize*64,::GetTickCount()-nTime);
    ReportMeasuredComponentTimingData(eSQRTMeasured);
    nTime   = ::GetTickCount();
#if _CollectDetailedTimingData
    SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
    SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
    printf("Simple Newton:                                                                 %i milliseconds\n",::GetTickCount()-nTime);
    nX2.SetRandom(nX1.GetSize()*_DIGIT_SIZE_IN_BITS/2);
    nX1Copy = nX1;
    nX2Copy = nX2;
    nTime   = ::GetTickCount();
#if _CollectDetailedTimingData
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
    printf("General recursive (half-size x1):                                              %i milliseconds\n", ::GetTickCount() - nTime);
    nX2.SetRandom(nX1.GetSize()*_DIGIT_SIZE_IN_BITS*2/3);
    nX1Copy = nX1;
    nX2Copy = nX2;
    nTime   = ::GetTickCount();
#if _CollectDetailedTimingData
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
    printf("General recursive (two thirds-size x1):                                        %i milliseconds\n", ::GetTickCount() - nTime);
    nX2.SetRandom(nX1.GetSize()*_DIGIT_SIZE_IN_BITS/3);
    nX1Copy = nX1;
    nX2Copy = nX2;
    nTime   = ::GetTickCount();
#if _CollectDetailedTimingData
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
    printf("General recursive (one third-size x1):                                         %i milliseconds\n", ::GetTickCount() - nTime);
    ResetTimingData();
    nTime = ::GetTickCount();
    if (eOperationSucceeded != cBox.Square(nSqrtX, nX2))
    {
        printf("Square failed\n");
    }
    printf("And, for comparison, squaring that square root again:                          %i milliseconds\n",::GetTickCount()-nTime);
    ReportMeasuredComponentTimingData(eMultiplicationMeasured);
    ResetTimingData();
    nTime   = ::GetTickCount();
    if (eOperationSucceeded != cBox.Divide(nX1, nSqrtX, nX2, nExtra))
    {
        printf("Divide failed\n");
    }
    printf("And to divide that large number by its square root:                            %i milliseconds\n",::GetTickCount()-nTime);
    ReportMeasuredComponentTimingData(eDivideMeasured);
    printf("compute the square root of 2 to 1,000,000 base 10 digits\n");
    nX1.SetFromHexString("64"); // 64 base 16 is 100 base 10
    nTime = ::GetTickCount();
    cBox.Power(nX1, 1000000, nX2); // 100 to 1,000,000 -> multiply root by 10 to the 1,000,000
    nTime = ::GetTickCount() - nTime;
    printf("Time to compute the power: %i ms\n", nTime);
    nX2.ShiftLeft(1); // multiply by 2
    ResetTimingData();
    nTime = ::GetTickCount();
    cBox.SQRT(nX2, nSqrtX);
    nTime = ::GetTickCount() - nTime;
    printf("Time to compute the root: %i ms (%u DIGIT base number)\n", nTime, nX2.GetSize());
    ReportMeasuredComponentTimingData(eSQRTMeasured);
    FILE *f;
    nX2Copy = nSqrtX; // PrintNumberToBase10 is destructive
    nTime = ::GetTickCount();
    fopen_s(&f, "sqrt2_a", "w");
    PrintNumberToBase10(nX2Copy, cBox.m_Workspace.GetSpace(), f);
    fclose(f);
    nTime = ::GetTickCount() - nTime;
    printf("Time to print the square root in base 10 to a file: %u ms\n", nTime);
    // validate
    nTime = ::GetTickCount();
    cBox.Square(nSqrtX, nX1);
    if (nX2 < nX1) printf("square root of 2 too big!\n");
    nSqrtX += 1;
    cBox.Square(nSqrtX, nX1);
    if (nX1 <= nX2)
    {
        printf("square root of 2 too small!\n");
        cBox.Subtract(nX2, nX1, nExtra);
        printf("Computed + 1: ",nSqrtX.PrintDecimalToFile());
    }
    nTime = ::GetTickCount() - nTime;
    printf("Time to validate the root: %i ms\n", nTime);
    printf("And finally: the time to compute the square root of 2 to 20,000,000 base-10 digits\n");
    nX1.SetFromHexString("64"); // 64 base 16 is 100 base 10
    nTime = ::GetTickCount();
    cBox.Power(nX1, 20000000, nX2); // 100 to 20,000 -> multiply root by 10 to the 20000000
    nTime = ::GetTickCount() - nTime;
    printf("Time to compute the power: %i ms\n", nTime);
    nX2.ShiftLeft(1); // multiply by 2
    nTime = ::GetTickCount();
    cBox.SQRT(nX2, nSqrtX);
    nTime = ::GetTickCount() - nTime;
    printf("Time to compute the root: %i ms (%u DIGIT base number)\n", nTime, nX2.GetSize());
    nX2Copy = nSqrtX; // PrintNumberToBase10 is destructive
    nTime = ::GetTickCount();
    fopen_s(&f, "sqrt2_b", "w");
    PrintNumberToBase10(nX2Copy, cBox.m_Workspace.GetSpace(), f);
    fclose(f);
    nTime = ::GetTickCount() - nTime;
    printf("Time to print the square root in base 10 to a file: %u ms\n", nTime);
    // validate
    nTime = ::GetTickCount();
    cBox.Square(nSqrtX, nX1);
    if (nX2 < nX1) printf("square root of 2 too big!\n");
    nSqrtX += 1;
    cBox.Square(nSqrtX, nX1);
    if (nX1 <= nX2)
    {
        printf("square root of 2 too small!\n");
        cBox.Subtract(nX2, nX1, nExtra);
        printf("Computed + 1: ",nSqrtX.PrintDecimalToFile());
    }
    nTime = ::GetTickCount() - nTime;
    printf("Time to validate the root: %i ms\n", nTime);
    free(pWorkspace);
}

void CArithmeticPerformanceTester::GeneralRootTimes()
{
    CArithmeticBox     cBox;
    const unsigned int c_nNumberSizeInBYTEs = 1000000;
    const unsigned int c_nOneBILLION        = 1000000000;
    const unsigned int c_nMaxRoot           = 900;
    unsigned int       nTimeA, nTimeB;
    size_t             nRootSize;
    CBigIntegerForTest nX, nRootX, nXCopy;
    DIGIT              *pWorkspace = (DIGIT *) malloc(sizeof(DIGIT)*c_nNumberSizeInBYTEs*10);
    printf("\nIf you're not doing this in retail, you're not getting good results\n");
    printf("GeneralRootTimes\n");
    // for "large" numbers, compare mth root(sqrt)) vs (2m)th root
    nX.Reserve(c_nNumberSizeInBYTEs); // more than needed
    nXCopy.Reserve(c_nNumberSizeInBYTEs); // more than needed
    nRootX.Reserve(c_nNumberSizeInBYTEs); // more than needed
    // for "large" numbers, compare computing the square root using general root vs square root function
    size_t nSize = 0; // prevent code from being optimized away
    /*for (int i = 0; i<10; i++)
    {
        nX.SetRandom(c_nNumberSizeInBYTEs*8);
        nXCopy = nX;
        nTimeA = ::GetTickCount();
        SQRT(nXCopy.GetSize(), nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
        nSize += nRootSize;
        nTimeA = ::GetTickCount() - nTimeA;
        nXCopy = nX;
        nTimeB = ::GetTickCount();
        NthRoot(nXCopy.GetSize(), 2, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
        nSize += nRootSize;
        nTimeB = ::GetTickCount() - nTimeB;
        printf("Square root of a %u BYTE number: SQRT %u ms; general nth root %u ms\n",c_nNumberSizeInBYTEs, nTimeA, nTimeB);
    };*/
    // for "large" numbers, compare general root vs Newton
    for(DIGIT n=2;n<=c_nMaxRoot;n++)
    {
        nX.SetRandom(c_nNumberSizeInBYTEs*8);
        nXCopy = nX;
        nTimeA = ::GetTickCount();
        NthRootNewton(nXCopy.GetSize(), n, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
        nSize += nRootSize;
        nTimeA = ::GetTickCount() - nTimeA;
        nXCopy = nX;
        nTimeB = ::GetTickCount();
        NthRoot(nXCopy.GetSize(), n, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
        nSize += nRootSize;
        nTimeB = ::GetTickCount() - nTimeB;
        printf("%u root of a %u BYTE number: general newton %u ms; general nth root %u ms\n",n, c_nNumberSizeInBYTEs, nTimeA, nTimeB);
    }
    // for "large" numbers, compare mth root(sqrt)) vs (2m)th root
    for(DIGIT m=2; m<=c_nMaxRoot/2; m++)
    {
        nXCopy = nX;
        nTimeB = ::GetTickCount();
        SQRT(nXCopy.GetSize(), nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
        nSize += nRootSize;
        nTimeB = ::GetTickCount() - nTimeB;
        nTimeA = ::GetTickCount();
        NthRoot(nRootSize, m, nRootSize, nRootX.GetValue(), nXCopy.GetValue(), pWorkspace);
        nSize += nRootSize;
        nTimeA = ::GetTickCount() - nTimeA;
        printf("%u ms to take the square root of a %u BYTE number (%u ms) then take the %u root of THAT (%u ms)\n", nTimeA + nTimeB, c_nNumberSizeInBYTEs, nTimeB, m, nTimeA);
        nXCopy = nX;
        nTimeB = ::GetTickCount();
        NthRoot(nXCopy.GetSize(), m, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
        nSize += nRootSize;
        nTimeB = ::GetTickCount() - nTimeB;
        nTimeA = ::GetTickCount();
        SQRT(nRootSize, nRootSize, nRootX.GetValue(), nXCopy.GetValue(), pWorkspace);
        nSize += nRootSize;
        nTimeA = ::GetTickCount() - nTimeA;
        printf("%u ms to take the %u root of a %u BYTE number (%u ms) then take the square root of THAT: (%u ms)\n", nTimeA + nTimeB, m, c_nNumberSizeInBYTEs, nTimeB, nTimeA);
        nXCopy = nX;
        nTimeB = ::GetTickCount();
        NthRoot(nXCopy.GetSize(), m*2, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
        nSize += nRootSize;
        nTimeB = ::GetTickCount() - nTimeB;
        printf("%u ms to take the %u root of a %u BYTE number\n", nTimeB,m*2, c_nNumberSizeInBYTEs);
    }
    if (0 == nSize) printf("uh-oh\n");
    free(pWorkspace);
    /*
    // try roots of varying powers of 7 for a large number -- how do the times compare?
    for(size_t nSize=c_nNumberSizeInBYTEs; nSize<=c_nOneBILLION; nSize *= 10)
    {
        nX.SetRandom(8*nSize);
        nTimeA = ::GetTickCount();
        cBox.SQRT(nX, nRootX);
        nTimeA = ::GetTickCount() - nTimeA;
        printf("Taking square root of a %u BYTE number took %u milliseconds ",nX.GetSize()*sizeof(DIGIT), nTimeA);
        // validate it, because - why not?
        nTimeA = ::GetTickCount();
        cBox.Power(nRootX, 2, nXCopy);
        if(nX<nXCopy)
        {
            printf("Whoops -- computed root too big\n");
        }
        nRootX += 1;
        cBox.Power(nRootX, 2, nXCopy);
        if(nXCopy<=nX)
        {
            printf("Whoops -- computed root too small\n");
        }
        nTimeA = ::GetTickCount() - nTimeA;
        printf("Validate: %u milliseconds\n", nTimeA);
        for(size_t n=7; n<((size_t) 1<<_DIGIT_SIZE_IN_BITS)-1; n *= 7)
        {
            nTimeA = ::GetTickCount();
            cBox.NthRoot(nX, (DIGIT) n, nRootX);
            nTimeA = ::GetTickCount() - nTimeA;
            printf("Taking root %u of a %u BYTE number took %u milliseconds ",n,nX.GetSize()*sizeof(DIGIT), nTimeA);
            // validate it, because - why not?
            nTimeA = ::GetTickCount();
            cBox.Power(nRootX, n, nXCopy);
            if(nX<nXCopy)
            {
                printf("Whoops -- computed root too big\n");
            }
            nRootX += 1;
            cBox.Power(nRootX, n, nXCopy);
            if(nXCopy<=nX)
            {
                printf("Whoops -- computed root too small\n");
            }
            nTimeA = ::GetTickCount() - nTimeA;
            printf("Validate: %u milliseconds\n", nTimeA);
        }
    }*/
}

void CArithmeticPerformanceTester::CompareNthRootProblemBreakdownTimes()
{
    const unsigned int c_nMinNumberSizeInBYTEs = 100000, c_nMaxNumberSizeInBYTEs = 10000000;
    unsigned int       nTimeA, nTimeB, nTime;
    size_t             nRootSize;
    CBigIntegerForTest nX, nRootX, nXCopy;
    int                nIterations = 100;
    nX.Reserve(c_nMaxNumberSizeInBYTEs + 1);
    nRootX.Reserve(c_nMaxNumberSizeInBYTEs + 1);
    nXCopy.Reserve(c_nMaxNumberSizeInBYTEs + 1);
    printf("\nIf you're not doing this in retail, you're not getting good results\n");
    printf("CompareNthyRootProblemBreakdownTimes\n");
    // comparing problem paritioning for compouting general roots.  Doing this in retail?  If no, your
    // numbers might not be representative
    DIGIT *pWorkspace = (DIGIT *) malloc(sizeof(DIGIT)*NthRootMemoryNeeds(c_nMaxNumberSizeInBYTEs, c_pnOneBYTEPrimes[19])*2);
    for (size_t nSize = c_nMinNumberSizeInBYTEs; nSize <= c_nMaxNumberSizeInBYTEs; nSize *= 10)
    {
        for(int i=0; i<20; i++) // upper bound at most c_nNumOneBYTEPrimes
        {
            DIGIT m = c_pnOneBYTEPrimes[i];
            for(int j=i; j<20; j++)
            {
                DIGIT n = c_pnOneBYTEPrimes[j];
                nTimeA = 0;
                nTimeB = 0;
                for (int k=0; k<nIterations; k++)
                {
                    srand(k);
                    nX.SetRandom(nSize*8);
                    nXCopy = nX;
                    nTime  = ::GetTickCount();
                    if (2 == n)
                    {
                        SQRT(nXCopy.GetSize(), nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
                    }
                    else
                    {
                        NthRoot(nXCopy.GetSize(), n, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
                    }
                    nTimeA += (::GetTickCount() - nTime);
                    nXCopy =  nX;
                    nTime  =  ::GetTickCount();
                    if (2 == m)
                    {
                        SQRT(nRootSize, nRootSize, nRootX.GetValue(), nXCopy.GetValue(), pWorkspace);
                    }
                    else
                    {
                        NthRoot(nRootSize, m, nRootSize, nRootX.GetValue(), nXCopy.GetValue(), pWorkspace);
                    }
                    nTimeB += (::GetTickCount() - nTime);
                }
                printf("%u ms to take the %u root of a %u BYTE number (%u ms) then take the  %u root of THAT (%u ms) %u times\n", nTimeA + nTimeB, n, nX.GetSize()*sizeof(DIGIT), nTimeA, m, nTimeB, nIterations);
                if (n != m)
                {
                    nTimeA = 0;
                    nTimeB = 0;
                    for (int k=0; k<nIterations; k++)
                    {
                        srand(k);
                        nX.SetRandom(nSize*8);
                        nXCopy = nX;
                        nTime  = ::GetTickCount();
                        if (2 == m)
                        {
                            SQRT(nXCopy.GetSize(), nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
                        }
                        else
                        {
                            NthRoot(nXCopy.GetSize(), m, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
                        }
                        nTimeA += (::GetTickCount() - nTime);
                        nXCopy =  nX;
                        nTime  =  ::GetTickCount();
                        if (2 == n)
                        {
                            SQRT(nRootSize, nRootSize, nRootX.GetValue(), nXCopy.GetValue(), pWorkspace);
                        }
                        else
                        {
                            NthRoot(nRootSize, n, nRootSize, nRootX.GetValue(), nXCopy.GetValue(), pWorkspace);
                        }
                        nTimeB += (::GetTickCount() - nTime);
                    }
                    printf("%u ms to take the %u root of a %u BYTE number (%u ms) then take the  %u root of THAT (%u ms) %u times\n", nTimeA + nTimeB, m, nX.GetSize()*sizeof(DIGIT), nTimeA, n, nTimeB, nIterations);
                }
                nTimeA = 0;
                for (int k=0; k<nIterations; k++)
                {
                    srand(k);
                    nX.SetRandom(nSize * 8);
                    nXCopy = nX;
                    nTime = ::GetTickCount();
                    NthRoot(nXCopy.GetSize(), m*n, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
                    nTimeA += (::GetTickCount() - nTime);
                }
                nTimeB = ::GetTickCount() - nTimeB;
                printf("%u ms to take the %u root of a %u BYTE number %u times\n\n", nTimeA, m*n, nX.GetSize()*sizeof(DIGIT), nIterations);
            }
        }
        nIterations /= 10;
    }
    free(pWorkspace);
}

void CArithmeticPerformanceTester::MatrixMultiplyTimes()
{
    CBigIntegerForTest nBigInt;
    CArithmeticBox     cBox;
    const unsigned int c_nMaxMatrixSize = 1536; // up to c_nMaxMatrixSizexc_nMaxMatrixSize matrix multiplication
    const unsigned int c_nMaxNumberSize = 16;   // size in DIGITs
    unsigned int       nTime;
    unsigned int       nIterations = 1, nSize = 12;
    printf("\nIf you're not doing this in retail, you're not getting good results\n");
    printf("MatrixMultiplyTimes\n");
    // find minimum number of iterations for 12x12 basic multiplication with 1-DIGIT numbers to take 1 second
    do
    {
        CBigIntegerMatrix nMat1(nSize, nSize);
        CBigIntegerMatrix nMat2(nSize, nSize);
        CBigIntegerMatrix nProdOracle(nSize, nSize);
        for (int i=0; i<nSize; i++)
        {
            for (int j=0; j<nSize; j++)
            {
                nBigInt.SetRandom(_DIGIT_SIZE_IN_BITS);
                nBigInt.SetNegative(rand()%2);
                nMat1[i][j] = nBigInt;
                nBigInt.SetRandom(_DIGIT_SIZE_IN_BITS);
                nBigInt.SetNegative(rand()%2);
                nMat2[i][j] = nBigInt;
            }
        }
        nTime = ::GetTickCount();
        for(int i=0;i<nIterations; i++)
        {
            CBigIntegerMatrix::MultiplyOracle(nMat1, nMat2, nProdOracle, cBox);
        }
        nTime = ::GetTickCount()-nTime;
        if(1000<nTime) break;
        nIterations *= 2;
    }
    while (true);
    for(;nSize<=c_nMaxMatrixSize;nSize*=2)
    {
        CBigIntegerMatrix nMat1(nSize, nSize);
        CBigIntegerMatrix nMat2(nSize, nSize);
        CBigIntegerMatrix nProdOracle(nSize, nSize);
        CBigIntegerMatrix nProdStrassen(nSize, nSize);
        printf("Using %i iterations\n", nIterations);
        for (int nDigits=1; nDigits<=c_nMaxNumberSize; nDigits++)
        {
            for (int i=0; i<nSize; i++)
            {
                for (int j=0; j<nSize; j++)
                {
                    nBigInt.SetRandom(nDigits*_DIGIT_SIZE_IN_BITS);
                    nBigInt.SetNegative(rand()%2);
                    nMat1[i][j] = nBigInt;
                    nBigInt.SetRandom(nDigits*_DIGIT_SIZE_IN_BITS);
                    nBigInt.SetNegative(rand()%2);
                    nMat2[i][j] = nBigInt;
                }
            }
            nTime = ::GetTickCount();
            for(int i=0;i<nIterations; i++)
            {
                CBigIntegerMatrix::MultiplyOracle(nMat1, nMat2, nProdOracle, cBox);
            }
            nTime = ::GetTickCount() - nTime;
            printf("Basic matrix multiplier took    %u milliseconds for square matrix of size %u with entries of %u DIGITs\n",nTime,nSize,nDigits);
            nTime = ::GetTickCount();
            for(int i=0;i<nIterations; i++)
            {
                CBigIntegerMatrix::Multiply(nMat1, nMat2, nProdStrassen, cBox);
            }
            printf("Strassen matrix multiplier took %u milliseconds for square matrix of size %u with entries of %u DIGITs\n",::GetTickCount()-nTime,nSize,nDigits);
            if (nProdStrassen != nProdOracle) printf("uh-oh -- %u %u\n", nSize, nDigits);
        }
        nIterations = (nIterations+7)/8;
    }
}

void CArithmeticPerformanceTester::AVXMultTimes()
{
#if _USEAVX
    unsigned long nTime1, nTime2;
    CBigIntegerForTest x, y, z;
    DIGIT              *pX, *pY, *pZ;
    size_t             nXSize, nYSize, nZSize;
    const unsigned int c_numSizesToTest                 = 3;
    const unsigned int c_nSizesToTest[c_numSizesToTest] = { 24, 125, 2049 };
    unsigned int nIterations;
    printf("\nIf you're not doing this in retail, you're not getting good results\n");
    printf("AVXMultTimes\n");
    for (int type=0; type<2 && false; type++)
    {
        bool bMultiplyAdd = (type != 0);
        if (bMultiplyAdd) printf("Multiply/add times:\n");
        else              printf("Multiply times:\n");
        for (int n = 0; n < c_numSizesToTest; n++)
        {
            // 4-DIGIT x
            x.SetRandom(4*_DIGIT_SIZE_IN_BITS);
            y.SetRandom(c_nSizesToTest[n]*_DIGIT_SIZE_IN_BITS);
            z.Reserve(x.GetSize() + y.GetSize() + 1);
            nXSize      = x.GetSize();
            nYSize      = y.GetSize();
            nZSize      = nXSize + nYSize;
            pX          = x.GetValue();
            pY          = y.GetValue();
            pZ          = z.GetValue();
            pZ[nZSize]  = 0; // overflow guard
            nIterations = 0;
            // find out how many iterations
            do
            {
                nIterations = 2*nIterations + 1;
                nTime1 = ::GetTickCount();
                for (int i=0; i<nIterations; i++)
                {
                    CUnsignedArithmeticHelper::MultUShortLong(nXSize, nYSize, pX, pY, pZ);
                }
            }
            while (::GetTickCount() - nTime1 < 1000);
            nIterations *= 60;
            nTime1 = ::GetTickCount();
            if (bMultiplyAdd)
            {
                for (int i=0; i<nIterations; i++)
                {
                    CUnsignedArithmeticHelper::MultAddUShortLong(nXSize, nYSize, pX, pY, pZ);
                    pZ[nZSize] = 0;
                }
            }
            else
            {
                for (int i=0; i<nIterations; i++)
                {
                    CUnsignedArithmeticHelper::MultUShortLong(nXSize, nYSize, pX, pY, pZ);
                    pZ[nZSize] = 0;
                }
            }
            nTime1 = ::GetTickCount() - nTime1;
            printf("  %u x %u, %u iterations: short/long: %u milliseconds\n", nXSize, nYSize, nIterations, nTime1);
            nTime2 = ::GetTickCount();
            for (int i=0; i<nIterations; i++)
            {
                CAVXMultiply::Mult4DigitX(pX, pY, nYSize, pZ, bMultiplyAdd);
                pZ[nZSize] = 0;
            }
            nTime2 = ::GetTickCount() - nTime2;
            printf("  %u x %u, %u iterations: AVXMult:    %u milliseconds (%f of short/long)\n", nXSize, nYSize, nIterations, nTime2, ((double) nTime2)/nTime1);

            // 8-DIGIT x
            x.SetRandom(8*_DIGIT_SIZE_IN_BITS);
            z.Reserve(x.GetSize() + y.GetSize() + 1);
            nXSize = x.GetSize();
            nZSize = nXSize + nYSize;
            pX = x.GetValue();
            pZ = z.GetValue();
            // find out how many iterations
            nIterations = 0;
            do
            {
                nIterations = 2*nIterations + 1;
                nTime1 = ::GetTickCount();
                for (int i=0; i<nIterations; i++)
                {
                    CUnsignedArithmeticHelper::MultUShortLong(nXSize, nYSize, pX, pY, pZ);
                }
            }
            while (::GetTickCount() - nTime1 < 1000);
            nIterations *= 60;
            nTime1 = ::GetTickCount();
            if (bMultiplyAdd)
            {
                for (int i=0; i<nIterations; i++)
                {
                    CUnsignedArithmeticHelper::MultAddUShortLong(nXSize, nYSize, pX, pY, pZ);
                    pZ[nZSize] = 0;
                }
            }
            else
            {
                for (int i=0; i<nIterations; i++)
                {
                    CUnsignedArithmeticHelper::MultUShortLong(nXSize, nYSize, pX, pY, pZ);
                    pZ[nZSize] = 0;
                }
            }
            nTime1 = ::GetTickCount() - nTime1;
            printf("  %u x %u, %u iterations: short/long: %u milliseconds\n", nXSize, nYSize, nIterations, nTime1);
            nTime2 = ::GetTickCount();
            for (int i=0; i<nIterations; i++)
            {
                CAVXMultiply::Mult8DigitX(pX, pY, nYSize, pZ, bMultiplyAdd);
                pZ[nZSize] = 0;
            }
            nTime2 = ::GetTickCount() - nTime2;
            printf("  %u x %u, %u iterations: AVXMult:    %u milliseconds (%f of short/long)\n", nXSize, nYSize, nIterations, nTime2, ((double) nTime2)/nTime1);

            // 12-DIGIT x
            x.SetRandom(12*_DIGIT_SIZE_IN_BITS);
            z.Reserve(x.GetSize() + y.GetSize() + 1);
            nXSize = x.GetSize();
            nZSize = nXSize + nYSize;
            pX = x.GetValue();
            pZ = z.GetValue();
            // find out how many iterations
            nIterations = 0;
            do
            {
                nIterations = 2*nIterations + 1;
                nTime1 = ::GetTickCount();
                for (int i=0; i<nIterations; i++)
                {
                    CUnsignedArithmeticHelper::MultUShortLong(nXSize, nYSize, pX, pY, pZ);
                }
            }
            while (::GetTickCount() - nTime1 < 1000);
            nIterations *= 60;
            nTime1 = ::GetTickCount();
            if (bMultiplyAdd)
            {
                for (int i=0; i<nIterations; i++)
                {
                    CUnsignedArithmeticHelper::MultAddUShortLong(nXSize, nYSize, pX, pY, pZ);
                    pZ[nZSize] = 0;
                }
            }
            else
            {
                for (int i=0; i<nIterations; i++)
                {
                    CUnsignedArithmeticHelper::MultUShortLong(nXSize, nYSize, pX, pY, pZ);
                    pZ[nZSize] = 0;
                }
            }
            nTime1 = ::GetTickCount() - nTime1;
            printf("  %u x %u, %u iterations: short/long: %u milliseconds\n", nXSize, nYSize, nIterations, nTime1);
            nTime2 = ::GetTickCount();
            for (int i=0; i<nIterations; i++)
            {
                CAVXMultiply::Mult12DigitX(pX, pY, nYSize, pZ, bMultiplyAdd);
                pZ[nZSize] = 0;
            }
            nTime2 = ::GetTickCount() - nTime2;
            printf("  %u x %u, %u iterations: AVXMult:    %u milliseconds (%f of short/long)\n", nXSize, nYSize, nIterations, nTime2, ((double) nTime2)/nTime1);
        }
    }
#else
    printf("AVX instructions not available.  Test aborted.\n");
#endif
}