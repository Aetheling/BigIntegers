#pragma once
#include "TestConstants.h"
#include "ArithmeticBox.h"
#include "CUnsignedArithmeticHelper.h"
#include "CArithmeticTestHelper.h"
#include "CBigIntegerVectors.h"
#include "CBigIntegerMatrix.h"
#include "SSystemData.h"
#include "math.h"
#include "CRandomGenerator.h"
#pragma warning(disable:4267)    // conversion from 'size_t' to 'unsigned int' -- possible loss of data

const char *c_szMultiplicationAlgorithmNames[eNumMultiplyAlgorithms] = { "eBasicMultiply",
																		 "e3By2",
																		 "e5By3",
																		 "e7By4",
#ifndef _USESMALLDIGITS
																		 "e9By5",
#endif
																		 "e2NByN",
																		 "eFFTMult" };
/*
This test takes LOTS of time to do, since only very big problems are helped by the cache optimizations.
Sample run:
Cache Size: 1   Subpiece size: 50000006 Time: 3200207959
Cache Size: 2   Subpiece size: 50000006 Time: 1735538658
Cache Size: 4   Subpiece size: 50000006 Time: 1067551877
Cache Size: 8   Subpiece size: 50000006 Time: 758558404
Cache Size: 16  Subpiece size: 50000006 Time: 614248792
Cache Size: 32  Subpiece size: 50000006 Time: 546682628
Cache Size: 64  Subpiece size: 50000006 Time: 525824718
Cache Size: 128 Subpiece size: 50000006 Time: 495525051
Cache Size: 256 Subpiece size: 50000006 Time: 485366342
Cache Size: 512 Subpiece size: 50000006 Time: 481579920
Cache Size: 1024        Subpiece size: 50000006 Time: 475714181
Cache Size: 2048        Subpiece size: 50000006 Time: 473925936
Cache Size: 4096        Subpiece size: 50000006 Time: 474037775
Cache Size: 8192        Subpiece size: 50000006 Time: 472765539
Cache Size: 16384       Subpiece size: 50000006 Time: 476819071
Cache Size: 32768       Subpiece size: 50000006 Time: 475936087
Cache Size: 65536       Subpiece size: 50000006 Time: 476187481
Cache Size: 131072      Subpiece size: 50000006 Time: 479145438
Cache Size: 262144      Subpiece size: 50000006 Time: 479288704
Cache Size: 524288      Subpiece size: 50000006 Time: 479770613
Cache Size: 1048576     Subpiece size: 50000006 Time: 489575842
Cache Size: 2097152     Subpiece size: 50000006 Time: 493030939
Cache Size: 4194304     Subpiece size: 50000006 Time: 495299297
Cache Size: 8388608     Subpiece size: 50000006 Time: 493912041
Cache Size: 16777216    Subpiece size: 50000006 Time: 495976916
Cache Size: 33554432    Subpiece size: 50000006 Time: 489010447
Cache Size: 67108864    Subpiece size: 50000006 Time: 485758698
Cache Size: 1   Subpiece size: 100000012        Time: 84637420896
Cache Size: 2   Subpiece size: 100000012        Time: 7130446025
Cache Size: 4   Subpiece size: 100000012        Time: 4571390426
Cache Size: 8   Subpiece size: 100000012        Time: 3342836365
Cache Size: 16  Subpiece size: 100000012        Time: 2658231935
Cache Size: 32  Subpiece size: 100000012        Time: 2276174170
Cache Size: 64  Subpiece size: 100000012        Time: 2084909059
Cache Size: 128 Subpiece size: 100000012        Time: 1980835995
Cache Size: 256 Subpiece size: 100000012        Time: 1928166510
Cache Size: 512 Subpiece size: 100000012        Time: 1876511694
Cache Size: 1024        Subpiece size: 100000012        Time: 1839170516
Cache Size: 2048        Subpiece size: 100000012        Time: 1846623314
Cache Size: 4096        Subpiece size: 100000012        Time: 1832961513
Cache Size: 8192        Subpiece size: 100000012        Time: 1832572060
Cache Size: 16384       Subpiece size: 100000012        Time: 1826193708
Cache Size: 32768       Subpiece size: 100000012        Time: 1822001072
Cache Size: 65536       Subpiece size: 100000012        Time: 1834448979
Cache Size: 131072      Subpiece size: 100000012        Time: 1858016662
Cache Size: 262144      Subpiece size: 100000012        Time: 1854792939
Cache Size: 524288      Subpiece size: 100000012        Time: 1861740392
Cache Size: 1048576     Subpiece size: 100000012        Time: 1868720403
Cache Size: 2097152     Subpiece size: 100000012        Time: 1887328986
Cache Size: 4194304     Subpiece size: 100000012        Time: 1889861525
Cache Size: 8388608     Subpiece size: 100000012        Time: 1896306366
Cache Size: 16777216    Subpiece size: 100000012        Time: 1894885145
Cache Size: 33554432    Subpiece size: 100000012        Time: 1896594026
Cache Size: 67108864    Subpiece size: 100000012        Time: 1900356477
Cache Size: 134217728   Subpiece size: 100000012        Time: 1900971121
Chosen sizes: Pre: 8192 Time: 472765539 Post: 32768 Time: 1822001072
*/
void CArithmeticTuner::Test2NByNBlockSizes()
{
	FILE         *pOutput;
	fopen_s(&pOutput, "2NByNBlockSizes", "w");
	const size_t c_nMaxSize = 100000000;//1000000000; // my computer can't handle this bigger memory size
	DIGIT        *pnX,*pnY,*pnZ, *pnWorkspace, **ppnRi, *pnOverflowDigits;
	size_t       i,j,nPieces,nIterations,*pnRiSizes,*pnRiOpSizes, nSubproblemSize, nMaxRiOpSize;
	unsigned int *pnCacheBlock;
	SSystemData  *pSystemToUse;
	DWORD64      pdwBestTime[2], nTimestampLow, nTimestampHigh, dwTimestamp;
	size_t       nProblemSize; // cache only helps for big problems
	pnX = new DIGIT[c_nMaxSize];
	pnY = new DIGIT[c_nMaxSize];
	pnZ = new DIGIT[2*c_nMaxSize];
	pnWorkspace = (DIGIT *) malloc(sizeof(DIGIT)*20*c_nMaxSize);
	for(i=0;i<c_nMaxSize;i++)
	{
		pnX[i] = (DIGIT) -1;
		pnY[i] = (DIGIT) -1;
	}
	// pre-generate systems so we don't count that time in optimizing
	for(size_t nProblemSize = 10000; nProblemSize<= c_nMaxSize; nProblemSize *= 10)
	{
		nPieces      = PiecesByProblemSize(nProblemSize);
		pSystemToUse = GenerateSystem(nPieces);
	}
	nProblemSize      =  c_nMaxSize; // cache only helps for big problems
	nIterations       =  c_nMaxSize/nProblemSize;
	nPieces           =  PiecesByProblemSize(nProblemSize);
	pSystemToUse      =  GenerateSystem(nPieces);
	pnOverflowDigits  =  pnWorkspace;
	pnWorkspace       += 2*(2*nPieces-2)*(pSystemToUse->m_nMaxSizeRI+2);
	ppnRi             =  (DIGIT **) pnWorkspace;
    pnRiSizes         =  (size_t *) (ppnRi + (2*nPieces-1));
    pnWorkspace       =  (DIGIT *)  (pnRiSizes + 2*nPieces-1);
    pnRiOpSizes       =  (size_t *) (pnZ + ((size_t) pnZ)%(sizeof(size_t)/sizeof(DIGIT)));
	nMaxRiOpSize      =  ((nProblemSize+nPieces-1)/nPieces+pSystemToUse->m_nMaxSizeRI+2);
	printf("doing %i x %i multiplication in %i pieces\n", nProblemSize, nProblemSize, nPieces);
    for(i=0;i<2*nPieces-2;i++)
    {
        // this gives more space than is needed to hold r(0) and r(2n-2) --
        // but extra space is needed in the r(i)s, since these are also used
        // to hold the arguments in computing the next up: r(0) is used as space
        // for the args for r(1), r(1) for r(2), etc.
        ppnRi[i]     =  pnWorkspace;
        pnWorkspace  += (nProblemSize+nPieces-1)/nPieces+pSystemToUse->m_nMaxSizeRI+2;
		pnRiSizes[i] =  nMaxRiOpSize<<1;
    }
	ppnRi[i]     = pnZ;
	pnRiSizes[i] = nMaxRiOpSize<<1;
	for(i=0;i<2*nPieces-1;i++)
	{
		for(j=0;j<pnRiSizes[i];j++)
		{
			ppnRi[i][j] = (DIGIT) (i+1)*(j+1);
		}
	}
	for(i=0;i<1;i++) // stop at 0: cache blocks for post disabled; code not working & tests indicate not useful for problem sizes that matter
	{
		unsigned int nBestSize;
		pdwBestTime[i] = 0xffffffff;
		if(0==i)
		{
			printf("testing pre block sizes:\n");
			pnCacheBlock    = &c_nBuildBlockSizePre;
			nSubproblemSize = ((nProblemSize+nPieces-1)/nPieces+pSystemToUse->m_nMaxSizeRI+2);
		}
		else
		{
			printf("testing post block sizes:\n");
			pnCacheBlock    = &c_nBuildBlockSizePost;
			nSubproblemSize = ((nProblemSize+nPieces-1)/nPieces+pSystemToUse->m_nMaxSizeRI+2)<<1;
		}
		for(size_t nCacheBlockSize = 1; nCacheBlockSize <= nSubproblemSize*2; nCacheBlockSize=nCacheBlockSize<<1)
		{
			if (1 == nCacheBlockSize)
			{
				*pnCacheBlock = 1000000000; // no caching.  Cache block size 1 very definately SLOW.
			}
			else
			{
				*pnCacheBlock = nCacheBlockSize;
			}
			nTimestampLow = s_Timer.GetMicroseconds();
			if(0==i)
			{
				for(j=0;j<nIterations;j++)
				{
#if _CollectDetailedTimingData
					ConstructArgumentsFor2NByNSubproblems((nProblemSize+nPieces-1)/nPieces,
						                                  nPieces,
														  nProblemSize,
														  nProblemSize,
														  nMaxRiOpSize,
														  pSystemToUse->m_nMaxSizeRI+2,
														  ppnRi,
														  pnRiOpSizes,
														  pnX,
														  pnY,
														  pnOverflowDigits,
														  pSystemToUse,
														  dwTimestamp,
														  pnWorkspace);
#else
					ConstructArgumentsFor2NByNSubproblems((nProblemSize+nPieces-1)/nPieces,
						                                  nPieces,
														  nProblemSize,
														  nProblemSize,
														  nMaxRiOpSize,
														  pSystemToUse->m_nMaxSizeRI+2,
														  ppnRi,
														  pnRiOpSizes,
														  pnX,
														  pnY,
														  pnOverflowDigits,
														  pSystemToUse,
														  pnWorkspace);
#endif
				}
			}
			else
			{
				for(j=0;j<nIterations;j++)
				{
#if _CollectDetailedTimingData
					
					ComputeProductFrom2NByNSubproblemResults(nPieces,
						                                     nMaxRiOpSize<<1,
															 (nProblemSize+nPieces-1)/nPieces,
															 nProblemSize,
															 nProblemSize,
															 pnRiSizes,
															 ppnRi,
															 pnZ,
															 pSystemToUse,
															 dwTimestamp,
															 pnWorkspace);
#else
					ComputeProductFrom2NByNSubproblemResults(nPieces,
						                                     nMaxRiOpSize<<1,
															 (nProblemSize+nPieces-1)/nPieces,
															 nProblemSize,
															 nProblemSize,
															 pnRiSizes,
															 ppnRi,
															 pnZ,
															 pSystemToUse,
															 pnWorkspace);
#endif
				}
			}
			nTimestampHigh = s_Timer.GetMicroseconds();
			if(nTimestampHigh-nTimestampLow<pdwBestTime[i])
			{
				pdwBestTime[i] = nTimestampHigh-nTimestampLow;
				nBestSize      = *pnCacheBlock;
			}
			printf( "Cache Size: %i\tSubpiece size: %i\tTime: %I64u\n", *pnCacheBlock, nSubproblemSize, nTimestampHigh - nTimestampLow);
			fprintf(pOutput,"Cache Size: %i\tSubpiece size: %i\tTime: %I64u\n", *pnCacheBlock,nSubproblemSize,nTimestampHigh-nTimestampLow);
		}
		*pnCacheBlock = nBestSize;
	}
	printf("Chosen sizes: Pre: %i Time: %I64u\tPost: %i Time: %I64u\n",c_nBuildBlockSizePre,pdwBestTime[0],c_nBuildBlockSizePost,pdwBestTime[1]);
	delete pnX;
	delete pnY;
	delete pnZ;
	free(pnOverflowDigits); // pnOverflowDigits aligned with original workspace allocation
	fclose(pOutput);
}

// Turns out, the gcd threshld tested here doesn't actually help
#if 0
void CArithmeticTuner::FindBestGCDThreshold()
{
	CArithmeticBox     cBox;
	CRandomGenerator   cGenerator;
	const unsigned int c_nBaseDigitSize = 256, c_nIterations = 8192;// 16384;
	CBigInteger        nX, nY, nXCoef, nYCoef, nGCD, nXExtended, nYExtended;
	// find two numbers which are relatively prime; use these as the base for constructing numbers with the desired size of GCD
	cGenerator.RandomBits(c_nBaseDigitSize, 0, true, nX);
	do
	{
		cGenerator.RandomBits(c_nBaseDigitSize, 0, true, nY);
		cBox.GCD(&nX, &nY, &nGCD, &nXCoef, &nYCoef);
	}
	while(1 != nGCD.GetSize() || 1 != nGCD.GetValue()[0]);
	for(int nNumberSize = 1; nNumberSize<=256; nNumberSize++)
	{
		// find a suitable common factor
		cGenerator.RandomBits(nNumberSize, 0, true, nGCD);
		// construct numbers with that as there greatest common divisor
		cBox.Multiply(&nX, &nGCD, &nXExtended);
		cBox.Multiply(&nY, &nGCD, &nYExtended);
		// time with threshold below the GCD size and above
		s_nGCDThreshold = 0;
		unsigned int nStartTime = ::GetTickCount();
		for(int i=0; i<c_nIterations; i++)
		{
			cBox.GCD(&nXExtended, &nYExtended, &nGCD, &nXCoef, &nYCoef);
		}
		unsigned int nMiddleTime = ::GetTickCount();
		s_nGCDThreshold = 1000000;
		for(int i=0; i<c_nIterations; i++)
		{
			cBox.GCD(&nXExtended, &nYExtended, &nGCD, &nXCoef, &nYCoef);
		}
		unsigned int nEndTime = ::GetTickCount();
		printf("Number size: %i GCD size: %i Time with low threshold: %i ms  Time with high threshold: %i ms\n",
			   c_nBaseDigitSize + nNumberSize,
			   nNumberSize,
			   nMiddleTime - nStartTime,
			   nEndTime - nMiddleTime);
	}
}
#endif

// try to figure out the parameters for deciding how to do Really Big Multiplies
// Need to compute 3 values:
// CExtendedPrecisionInteger::s_7by4Threshold: threshold below which we use 7x4 multiplication
// CExtendedPrecisionInteger::s_2NbyN_addend: constant term in fnc for deciding number of pieces for Big Problems
// CExtendedPrecisionInteger::s_2NbyN_coef: coef (linear) term in fnc for deciding number of pieces for Big Problems
// It should use AT LEAST 5 pieces at the s_7by4Threshold (might use more; the 2NbyN algorithm isn't
// as well-tuned, since it has to be general -- so we might actually skip the first size or three).
// Determine best break points for 4 to 5, 5 to 6, and 6 to 7 to get basic values; repeat and also
    // get break points for 7 to 8, 8 to 9, and 9 to 10 to refine with curve fitting.
void CArithmeticTuner::Compute2NByNGrowthParameters()
{
	CBigIntegerForTest nX, nY, nZ;
	CWorkspace         cWork;
    DWORD              i;
    DWORD64            dwFewPiecesTime, dwMorePiecesTime, dwStartTime, dwTimestamp;
    size_t             nSize, nSizeLow, nSizeHigh, nProdSize;
    DWORD              nIterations, nBaseIterations;
	FILE               *pOutput;
	fopen_s(&pOutput, "2NByNGrowthParameters", "w");
#ifndef _USESMALLDIGITS
	// set the starting size to the 7by4 threshold
	nSize = c_pnMultiplicationThresholds[e7By4];
#else
	// set the starting size to the 5by3 threshold
	nSize = c_pnMultiplicationThresholds[e5By3];
#endif
    // find out how many multiplications (roughly) that it takes to use up at least
    // a second's worth of time
	nX.SetRandom(nSize*sizeof(DIGIT)<<3); // random number on nSize digits
    nY.SetRandom(nSize*sizeof(DIGIT)<<3); // random number on nSize digits
	nZ.Reserve(nSize<<1);
	// find a reasonable number of iterations -- want at least a second of work to
	// get stable times, but not so much as to be slow!
	cWork.Reserve(8*MultiplyMemoryNeeds(nSize,nSize));  // *8: fudge factor; may be using more pieces than memory func designed for
    nIterations = 1;
    do
    {
        dwStartTime = s_Timer.GetMicroseconds();
		dwTimestamp = dwStartTime;
        for(i=0;i<nIterations;i++)
        {
#if _CollectDetailedTimingData
			MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nZ.GetValue(),cWork.GetSpace(),dwTimestamp,&nProdSize);
#else
			MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nZ.GetValue(),cWork.GetSpace(),&nProdSize);
#endif
        }
        dwFewPiecesTime = s_Timer.GetMicroseconds()-dwStartTime;
        if(1000000<dwFewPiecesTime)
        {
            break;
        }
        nIterations = nIterations<<1;
    }
    while(1);
    nBaseIterations = nIterations;
    // find the switch points between nPieces and nPieces+1
    for(size_t nPieces=5; nPieces<5+c_n2NBynSizeBreakpoints; nPieces++)
    {
		printf("Considering %i:%i split for the 2N-1 by N multiplication\n",nPieces,nPieces+1);
        // first, need to find a size for which nPieces+1 is faster than nPieces.
        // Then, we can do a binary search to find the change point.  It is assumed
        // that we start with a size for which nPieces is faster!
        nSizeLow = nSize;
        nSize    = nSize<<1;
        do
        {
			nX.SetRandom(nSize*sizeof(DIGIT)<<3); // random number on nSize digits
			nY.SetRandom(nSize*sizeof(DIGIT)<<3); // random number on nSize digits
			nZ.Reserve(nSize<<1);
			dwStartTime = s_Timer.GetMicroseconds();
			dwTimestamp = dwStartTime;
#ifndef _USESMALLDIGITS
			c_pnMultiplicationThresholds[e9By5]  = nSize-1; // so we only use the 2nbyn algorithm for the top level
#else
			c_pnMultiplicationThresholds[e7By4]  = nSize-1; // so we only use the 2nbyn algorithm for the top level
#endif
			cWork.Reserve(8*MultiplyMemoryNeeds(nSize,nSize));  // *8: fudge factor; may be using more pieces than memory func designed for
            for(i=0;i<nIterations;i++)
            {
#if _CollectDetailedTimingData
				MultU2NByN(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nZ.GetValue(), GenerateSystem(nPieces), cWork.GetSpace(), dwTimestamp);
#else
				MultU2NByN(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nZ.GetValue(), GenerateSystem(nPieces), cWork.GetSpace());
#endif
            }
			dwFewPiecesTime = s_Timer.GetMicroseconds() - dwStartTime;
            fprintf(pOutput,
					"Size: %i Pieces: %i Iterations: %i Microseconds: %I64u\n",
                    nSize,
                    nPieces,
                    nIterations,
                    dwFewPiecesTime);
            dwStartTime = s_Timer.GetMicroseconds();
			dwTimestamp = dwStartTime;
            for(i=0;i<nIterations;i++)
            {
#if _CollectDetailedTimingData
				MultU2NByN(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nZ.GetValue(), GenerateSystem(nPieces+1), cWork.GetSpace(), dwTimestamp);
#else
				MultU2NByN(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nZ.GetValue(), GenerateSystem(nPieces+1), cWork.GetSpace());
#endif
            }
			dwMorePiecesTime = s_Timer.GetMicroseconds() - dwStartTime;
            fprintf(pOutput,
					"Size: %i Pieces: %i Iterations: %i Microseconds: %I64u\n",
                    nSize,
                    nPieces+1,
                    nIterations,
                    dwMorePiecesTime);
            if(dwMorePiecesTime<dwFewPiecesTime)
            {
                nSizeLow  = nSize>>1;
                nSizeHigh = nSize;
                break;
            }
            else if(nIterations>1)
            {
                nIterations = nIterations>>1;
            }
            nSize = nSize<<1;
        }
        while(1);
        // Now, use binary search to find the breakpoint
        do
        {
            nSize       = (nSizeLow+nSizeHigh)>>1;
			dwStartTime = s_Timer.GetMicroseconds();
			dwTimestamp = dwStartTime;
            for(i=0;i<nIterations;i++)
            {
#if _CollectDetailedTimingData
				MultU2NByN(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nZ.GetValue(), GenerateSystem(nPieces), cWork.GetSpace(), dwTimestamp);
#else
				MultU2NByN(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nZ.GetValue(), GenerateSystem(nPieces), cWork.GetSpace());
#endif
            }
			dwFewPiecesTime = s_Timer.GetMicroseconds() - dwStartTime;
            fprintf(pOutput,
					"Size: %i Pieces: %i Iterations: %i Microseconds: %I64u\n",
                    nSize,
                    nPieces,
                    nIterations,
                    dwFewPiecesTime);
            dwStartTime = s_Timer.GetMicroseconds();
            for(i=0;i<nIterations;i++)
            {
#if _CollectDetailedTimingData
				MultU2NByN(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nZ.GetValue(), GenerateSystem(nPieces+1), cWork.GetSpace(), dwTimestamp);
#else
				MultU2NByN(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nZ.GetValue(), GenerateSystem(nPieces+1), cWork.GetSpace());
#endif
            }
            dwMorePiecesTime = s_Timer.GetMicroseconds() - dwStartTime;
            fprintf(pOutput,
					"Size: %i Pieces: %i Iterations: %i Microseconds: %I64u\n",
                    nSize,
                    nPieces+1,
                    nIterations,
                    dwMorePiecesTime);
            if(dwMorePiecesTime<dwFewPiecesTime)
            {
                nSizeHigh = nSize;
                if(2000000<dwMorePiecesTime && 1<nIterations)
                {
                    nIterations = nIterations>>1;
                }
            }
            else
            {
                nSizeLow = nSize;
                if(2000000<dwFewPiecesTime && 1<nIterations)
                {
                    nIterations = nIterations>>1;
                }
            }
        }
        while(nSizeLow < nSizeHigh-1);
		c_pn2NByNBreakpoints[nPieces-5] = nSizeLow;
        printf("%i:%i threshold: %i (c_pn2NByNBreakpoints[%i])\n",nPieces,nPieces+1,nSizeLow,nPieces-5);
    }
	FILE *pThreshold;
#ifndef _USESMALLDIGITS
	// get the threshold for the 7x4/2nxn-1 split -- c_pnMultiplicationThresholds[e9By5]
	c_pnMultiplicationThresholds[e9By5] = c_pnMultiplicationThresholds[e7By4] + 1; // starting point 
	fopen_s(&pThreshold, "e9By5Threshold", "w");
    GetSimpleThreshold(e9By5,cWork,pThreshold);
#else
	// get the threshold for the 7x4/2nxn-1 split -- c_pnMultiplicationThresholds[e7By4]
	c_pnMultiplicationThresholds[e7By4] = c_pnMultiplicationThresholds[e5By3] + 1; // starting point
	fopen_s(&pThreshold, "e7By4Threshold", "w");
	GetSimpleThreshold(e7By4, cWork, pThreshold);
#endif
	fclose(pThreshold);
	fclose(pOutput);
}

// should have LOTS of available digits in pX, pY
void CArithmeticTuner::GetSimpleThreshold(EMultiplyAlgorithm eThresholdToTest, CWorkspace &Work, FILE *pOutput)
{
	DWORD nIterates   = 1;
    DWORD nCnt        = 0;
    bool  bFoundFast  = false;
    bool  bSearchDown = false;
	CBigInteger nX,nY,nZ;
    // low threshold time gives time for the higher-order algorithm (size
    // is above the low threshold).  high threshold time, conversely, gives
    // the time for the low-order algorithm.
    DWORD   i, dwSize, dwHoldSize, dwAllocatedSize=0;
	DWORD64 dwStart, dwLowThresholdTime, dwHighThresholdTime;
    // get the starting size
	dwSize = c_pnMultiplicationThresholds[eThresholdToTest];
    do
	{
        c_pnMultiplicationThresholds[eThresholdToTest] = dwSize;
		if(dwAllocatedSize<dwSize+1)
		{
			dwAllocatedSize = (dwSize+1)<<1;
			nX.Reserve(dwAllocatedSize);
			nY.Reserve(dwAllocatedSize);
			nZ.Reserve(dwAllocatedSize<<1);
			Work.Reserve(MultiplyMemoryNeeds(dwAllocatedSize,dwAllocatedSize));
			for(nCnt=0;nCnt<dwAllocatedSize;nCnt++)
			{
				nX.GetValue()[nCnt] = (DIGIT) -1;
				nY.GetValue()[nCnt] = (DIGIT) -1;
			}
		}
		nX.SetSize(dwSize);
		nY.SetSize(dwSize);
		do
		{
			dwStart = s_Timer.GetMicroseconds();
			for(i=0;i<nIterates;i++)
			{
#if(_CollectDetailedTimingData)
				MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nZ.GetValue(),Work.GetSpace(),dwLowThresholdTime);
#else
				MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nZ.GetValue(),Work.GetSpace());
#endif
			}
			dwLowThresholdTime = s_Timer.GetMicroseconds()-dwStart;
			if(100000<dwLowThresholdTime)
			{
				break;
			}
			nIterates = nIterates<<1;
		}
		while(1);
        c_pnMultiplicationThresholds[eThresholdToTest]++;
		dwStart = s_Timer.GetMicroseconds();
		for(i=0;i<nIterates;i++)
		{
#if(_CollectDetailedTimingData)
				MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nZ.GetValue(),Work.GetSpace(),dwHighThresholdTime);
#else
				MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nZ.GetValue(),Work.GetSpace());
#endif
		}
		dwHighThresholdTime = s_Timer.GetMicroseconds()-dwStart;
		fprintf(pOutput,
			    "Size: %i Iterations: %i\tLow-order alg: %I64u  High-order alg: %I64u\n",
			    dwSize,
                nIterates,
                dwHighThresholdTime,
                dwLowThresholdTime);
		if(dwLowThresholdTime<dwHighThresholdTime)
        {
            nCnt++;
            if(!bFoundFast)
            {
                // fill in gap skipped
                bSearchDown = true;
                bFoundFast  = true;
            }
            if(bSearchDown)
            {
                dwHoldSize = dwSize;
				if(dwSize<100)
				{
					dwSize -= 1;
				}
				else if(dwSize<1000)
				{
					dwSize -= 10;
				}
				else if(dwSize<10000)
				{
					dwSize -= 100;
				}
				else if(dwSize<100000)
				{
					dwSize -= 1000;
				}
				else
				{
					dwSize -= 10000;
				}
            }
            else
            {
				if(dwSize<100)
				{
					dwSize += 1;
				}
				else if(dwSize<1000)
				{
					dwSize += 10;
				}
				else if(dwSize<10000)
				{
					dwSize += 100;
				}
				else if(dwSize<100000)
				{
					dwSize += 1000;
				}
				else
				{
					dwSize += 10000;
				}
            }
        }
		else
        {
            if(bSearchDown)
            {
                // found "bottom" of the array if fast zone
                dwSize      = dwHoldSize+nCnt;
                bSearchDown = false;
            }
            else
            {
                nCnt       =  0;
                bFoundFast =  false;
				if(dwSize<100)
				{
					dwSize += 6;
				}
				else if(dwSize<1000)
				{
					dwSize += 60;
				}
				else if(dwSize<10000)
				{
					dwSize += 600;
				}
				else if(dwSize<100000)
				{
					dwSize += 6000;
				}
				else
				{
					dwSize += 60000;
				}
            }
        }
		if(2000000<dwHighThresholdTime && 1<nIterates)
        {
            nIterates = nIterates>>1;
        }
	}
	while(nCnt<6);
    c_pnMultiplicationThresholds[eThresholdToTest] = dwHoldSize;
	//printf("The compile-time parameter \"c_pnMultiplicationThresholds[%s]\" should be set to %i\n", c_szMultiplicationAlgorithmNames[eThresholdToTest], c_pnMultiplicationThresholds[eThresholdToTest]);
}

void CArithmeticTuner::GetFFTThreshold()
{
	// for simplicity, only look at the smallest sizes for which a given field size is
	// needed
	CBigInteger        nX,nY,nZ;
	CWorkspace         cWork;
	DWORD64            dwStart, dwTime2NByN, dwTimeFFT, dwMin, dwMax, dwTime;
	size_t             nFFTLength,nFieldSize,nChunkSize, nFFTLength_old, nFieldSize_old;
	BYTE               byMaxOverflowSize;
	SBitShift          nRootUnity;
	DWORD              dwSize, dwSizeMiddle;
	DWORD              dwSizePrevious = 5; // FAR smaller than we expect the cuttoff to be!
	const unsigned int c_nIterations  = 18;
#if(_CollectDetailedTimingData)
	DWORD64     dwTimestamp;
#endif
	c_pnMultiplicationThresholds[e2NByN] = (DWORD) -1;
	GetFFTSize(dwSizePrevious,dwSizePrevious,nFFTLength_old,nFieldSize_old,nChunkSize,byMaxOverflowSize,nRootUnity);
	do
	{
		// first, find the next minimum size
		dwSize = dwSizePrevious;
		do
		{
			dwSize++;
			GetFFTSize(dwSize, dwSize, nFFTLength, nFieldSize, nChunkSize, byMaxOverflowSize, nRootUnity);
		}
		while(nFFTLength == nFFTLength_old || nFieldSize == nFieldSize_old);
		// next, determine which is faster: standard recursive multiply, or FFT
		cWork.Reserve(4*MultiplyMemoryNeeds(dwSize,dwSize)); // allocate extra memory -- thresholds in flux -> might not get right memory needs
		nZ.Reserve(((size_t) dwSize)<<1);
		nY.Reserve(dwSize);
		nX.Reserve(dwSize);
		nX.SetSize(dwSize);
		nY.SetSize(dwSize);
		for(DWORD i=0;i<dwSize;i++)
		{
			nX.GetValue()[i] = (DIGIT) -1;
			nY.GetValue()[i] = (DIGIT) -1;
		}
		// time using standard multiply
		dwMin       = (DWORD64)-1;
		dwMax       = 0;
		dwTime2NByN = 0;
		for (int i=0; i<c_nIterations; i++)
		{
			dwStart = s_Timer.GetMicroseconds();
#if(_CollectDetailedTimingData)
			MultUBackend(dwSize, dwSize, nX.GetValue(), nY.GetValue(), nZ.GetValue(), cWork.GetSpace(), dwTimestamp, &nChunkSize);
#else
			MultUBackend(dwSize, dwSize, nX.GetValue(), nY.GetValue(), nZ.GetValue(), cWork.GetSpace(), &nChunkSize);
#endif
			dwTime      =  s_Timer.GetMicroseconds() - dwStart;
			dwTime2NByN += dwTime;
			if(dwMax<dwTime) dwMax = dwTime;
			if(dwMin>dwTime) dwMin = dwTime;
		}
		dwTime2NByN -= (dwMax + dwMin);
		// repeat using FFT multiply
		cWork.Reserve(FFTMultiplyMemoryNeeds(nFFTLength, nFieldSize, false));
		dwMin     = (DWORD64)-1;
		dwMax     = 0;
		dwTimeFFT = 0;
		for (int i=0; i<c_nIterations; i++)
		{
			dwStart = s_Timer.GetMicroseconds();
#if(_CollectDetailedTimingData)
			MultFFT(dwSize, dwSize, nX.GetValue(), nY.GetValue(), nZ.GetValue(), cWork.GetSpace(), dwTimestamp);
#else
			MultFFT(dwSize, dwSize, nX.GetValue(), nY.GetValue(), nZ.GetValue(), cWork.GetSpace());
#endif
			dwTime    =  s_Timer.GetMicroseconds() - dwStart;
			dwTimeFFT += dwTime;
			if (dwMax < dwTime) dwMax = dwTime;
			if (dwMin > dwTime) dwMin = dwTime;
		}
		dwTimeFFT -= (dwMax + dwMin);
		printf("Doubling: Size: %i\tStandard multiply: %I64u\tFFT Multiply: %I64u\n",dwSize,dwTime2NByN,dwTimeFFT);
		if(dwTimeFFT<dwTime2NByN)
		{
			break;
		}
		nFieldSize_old = nFieldSize;
		nFFTLength_old = nFFTLength;
		dwSizePrevious = dwSize;
	}
	while(1);
	// Now: the minimum problem size for a given FFT size is where FFT does worst relative to the basic algorithms.  So,
	// should do better for anything larger.  But FFT is constant time over a large range of problem sizes.  Back up
	// to see where basic catches up
	do
	{
		dwSizeMiddle = (dwSize + dwSizePrevious)>>1;
		GetFFTSize(dwSizeMiddle, dwSizeMiddle, nFFTLength, nFieldSize, nChunkSize, byMaxOverflowSize, nRootUnity);
		cWork.Reserve(FFTMultiplyMemoryNeeds(nFFTLength, nFieldSize, false));
		// time using standard multiply
		dwMin       = (DWORD64)-1;
		dwMax       = 0;
		dwTime2NByN = 0;
		for (int i=0; i<c_nIterations; i++)
		{
			dwStart = s_Timer.GetMicroseconds();
#if(_CollectDetailedTimingData)
			MultUBackend(dwSizeMiddle, dwSizeMiddle, nX.GetValue(), nY.GetValue(), nZ.GetValue(), cWork.GetSpace(), dwTimestamp, &nChunkSize);
#else
			MultUBackend(dwSizeMiddle, dwSizeMiddle, nX.GetValue(), nY.GetValue(), nZ.GetValue(), cWork.GetSpace(), &nChunkSize);
#endif
			dwTime = s_Timer.GetMicroseconds() - dwStart;
			dwTime2NByN += dwTime;
			if (dwMax < dwTime) dwMax = dwTime;
			if (dwMin > dwTime) dwMin = dwTime;
		}
		dwTime2NByN -= (dwMax + dwMin);
		// repeat using FFT multiply
		dwMin     = (DWORD64)-1;
		dwMax     = 0;
		dwTimeFFT = 0;
		for (int i=0; i<c_nIterations; i++)
		{
			dwStart = s_Timer.GetMicroseconds();
#if(_CollectDetailedTimingData)
			MultFFT(dwSizeMiddle, dwSizeMiddle, nX.GetValue(), nY.GetValue(), nZ.GetValue(), cWork.GetSpace(), dwTimestamp);
#else
			MultFFT(dwSizeMiddle, dwSizeMiddle, nX.GetValue(), nY.GetValue(), nZ.GetValue(), cWork.GetSpace());
#endif
			dwTime = s_Timer.GetMicroseconds() - dwStart;
			dwTimeFFT += dwTime;
			if (dwMax < dwTime) dwMax = dwTime;
			if (dwMin > dwTime) dwMin = dwTime;
		}
		dwTimeFFT -= (dwMax + dwMin);
		printf("Binary: Size: %i\tStandard multiply: %I64u\tFFT Multiply: %I64u\n", dwSizeMiddle, dwTime2NByN, dwTimeFFT);
		if (dwTimeFFT < dwTime2NByN) dwSize         = dwSizeMiddle;
		else                         dwSizePrevious = dwSizeMiddle;
	}
	while(dwSize != (dwSize + dwSizePrevious)>>1);
	// this is the spot!
	c_pnMultiplicationThresholds[e2NByN] = dwSize;
}

/*
Sample run, 16-bit DIGITs
Considering 5:6 split for the 2N-1 by N multiplication
5:6 threshold: 68096 (c_pn2NByNBreakpoints[0])
Considering 6:7 split for the 2N-1 by N multiplication
6:7 threshold: 68629 (c_pn2NByNBreakpoints[1])
Considering 7:8 split for the 2N-1 by N multiplication
7:8 threshold: 137528 (c_pn2NByNBreakpoints[2])
Considering 8:9 split for the 2N-1 by N multiplication
8:9 threshold: 138875 (c_pn2NByNBreakpoints[3])
Considering 9:10 split for the 2N-1 by N multiplication
9:10 threshold: 4426393 (c_pn2NByNBreakpoints[4])
Considering 10:11 split for the 2N-1 by N multiplication
10:11 threshold: 4426394 (c_pn2NByNBreakpoints[5])
Considering 11:12 split for the 2N-1 by N multiplication
11:12 threshold: 4603929 (c_pn2NByNBreakpoints[6])
Doubling: Size: 65      Standard multiply: 43   FFT Multiply: 396
Doubling: Size: 385     Standard multiply: 624  FFT Multiply: 1571
Doubling: Size: 1793    Standard multiply: 5310 FFT Multiply: 7322
Doubling: Size: 7681    Standard multiply: 43726        FFT Multiply: 36257
Binary: Size: 4737      Standard multiply: 22576        FFT Multiply: 33573
Binary: Size: 6209      Standard multiply: 29880        FFT Multiply: 35747
Binary: Size: 6945      Standard multiply: 38824        FFT Multiply: 36338
Binary: Size: 6577      Standard multiply: 32660        FFT Multiply: 34344
Binary: Size: 6761      Standard multiply: 34811        FFT Multiply: 34161
Binary: Size: 6669      Standard multiply: 35753        FFT Multiply: 34073
Binary: Size: 6623      Standard multiply: 33204        FFT Multiply: 34096
Binary: Size: 6646      Standard multiply: 34549        FFT Multiply: 35047
Binary: Size: 6657      Standard multiply: 34354        FFT Multiply: 34000
Binary: Size: 6651      Standard multiply: 34289        FFT Multiply: 35469
Binary: Size: 6654      Standard multiply: 35154        FFT Multiply: 34816
Binary: Size: 6652      Standard multiply: 34225        FFT Multiply: 34322
Binary: Size: 6653      Standard multiply: 34878        FFT Multiply: 37109
Binary: Size: 6653      Standard multiply: 33938        FFT Multiply: 34361
Binary: Size: 6653      Standard multiply: 34308        FFT Multiply: 35474
Binary: Size: 6653      Standard multiply: 38997        FFT Multiply: 34171
The compile-time parameter "c_pnMultiplicationThresholds[eBasicMultiply]" should be set to 48
The compile-time parameter "c_pnMultiplicationThresholds[e3By2]" should be set to 73
The compile-time parameter "c_pnMultiplicationThresholds[e5By3]" should be set to 76
The compile-time parameter "c_pnMultiplicationThresholds[e7By4]" should be set to 360002
The compile-time parameter "c_pnMultiplicationThresholds[e2NByN]" should be set to 6653

and
Considering 5:6 split for the 2N-1 by N multiplication
5:6 threshold: 32707 (c_pn2NByNBreakpoints[0])
Considering 6:7 split for the 2N-1 by N multiplication
6:7 threshold: 130828 (c_pn2NByNBreakpoints[1])
Considering 7:8 split for the 2N-1 by N multiplication
7:8 threshold: 261977 (c_pn2NByNBreakpoints[2])
Considering 8:9 split for the 2N-1 by N multiplication
8:9 threshold: 523956 (c_pn2NByNBreakpoints[3])
Considering 9:10 split for the 2N-1 by N multiplication
9:10 threshold: 3493044 (c_pn2NByNBreakpoints[4])
Considering 10:11 split for the 2N-1 by N multiplication
10:11 threshold: 3547622 (c_pn2NByNBreakpoints[5])
Considering 11:12 split for the 2N-1 by N multiplication
11:12 threshold: 3873519 (c_pn2NByNBreakpoints[6])
Doubling: Size: 65      Standard multiply: 73   FFT Multiply: 658
Doubling: Size: 385     Standard multiply: 568  FFT Multiply: 1676
Doubling: Size: 1793    Standard multiply: 7189 FFT Multiply: 8913
Doubling: Size: 7681    Standard multiply: 57968        FFT Multiply: 47540
Binary: Size: 4737      Standard multiply: 25078        FFT Multiply: 41111
Binary: Size: 6209      Standard multiply: 35047        FFT Multiply: 44414
Binary: Size: 6945      Standard multiply: 42738        FFT Multiply: 53768
Binary: Size: 7313      Standard multiply: 48581        FFT Multiply: 53025
Binary: Size: 7497      Standard multiply: 47415        FFT Multiply: 47198
Binary: Size: 7405      Standard multiply: 58375        FFT Multiply: 45587
Binary: Size: 7359      Standard multiply: 50209        FFT Multiply: 42622
Binary: Size: 7336      Standard multiply: 48917        FFT Multiply: 40263
Binary: Size: 7324      Standard multiply: 56984        FFT Multiply: 54186
Binary: Size: 7318      Standard multiply: 58113        FFT Multiply: 51544
Binary: Size: 7315      Standard multiply: 48520        FFT Multiply: 54450
Binary: Size: 7316      Standard multiply: 67458        FFT Multiply: 48545
Binary: Size: 7315      Standard multiply: 64941        FFT Multiply: 53586
The compile-time parameter "c_pnMultiplicationThresholds[eBasicMultiply]" should be set to 50
The compile-time parameter "c_pnMultiplicationThresholds[e3By2]" should be set to 51
The compile-time parameter "c_pnMultiplicationThresholds[e5By3]" should be set to 52
The compile-time parameter "c_pnMultiplicationThresholds[e7By4]" should be set to 160001
The compile-time parameter "c_pnMultiplicationThresholds[e2NByN]" should be set to 7315

Sample, 32-bit DIGITs
The compile-time parameter "c_pnMultiplicationThresholds[eBasicMultiply]" should be set to 34
The compile-time parameter "c_pnMultiplicationThresholds[e3By2]" should be set to 68
The compile-time parameter "c_pnMultiplicationThresholds[e5By3]" should be set to 76
The compile-time parameter "c_pnMultiplicationThresholds[e7By4]" should be set to 161
Considering 5:6 split for the 2N-1 by N multiplication
5:6 threshold: 41298 (c_pn2NByNBreakpoints[0])
Considering 6:7 split for the 2N-1 by N multiplication
6:7 threshold: 61888 (c_pn2NByNBreakpoints[1])
Considering 7:8 split for the 2N-1 by N multiplication
7:8 threshold: 64486 (c_pn2NByNBreakpoints[2])
Considering 8:9 split for the 2N-1 by N multiplication
8:9 threshold: 264008 (c_pn2NByNBreakpoints[3])
Considering 9:10 split for the 2N-1 by N multiplication
9:10 threshold: 1055759 (c_pn2NByNBreakpoints[4])
Considering 10:11 split for the 2N-1 by N multiplication
10:11 threshold: 2278560 (c_pn2NByNBreakpoints[5])
Considering 11:12 split for the 2N-1 by N multiplication
11:12 threshold: 2323063 (c_pn2NByNBreakpoints[6])
The compile-time parameter "c_pnMultiplicationThresholds[e9By5]" should be set to 1990006
Doubling: Size: 129     Standard multiply: 96   FFT Multiply: 960
Doubling: Size: 769     Standard multiply: 1409 FFT Multiply: 3478
Doubling: Size: 3585    Standard multiply: 13788        FFT Multiply: 15712
Doubling: Size: 15361   Standard multiply: 92410        FFT Multiply: 78142
Binary: Size: 9473      Standard multiply: 48845        FFT Multiply: 72066
Binary: Size: 12417     Standard multiply: 73113        FFT Multiply: 73015
Binary: Size: 10945     Standard multiply: 58539        FFT Multiply: 73561
Binary: Size: 11681     Standard multiply: 64776        FFT Multiply: 73625
Binary: Size: 12049     Standard multiply: 67980        FFT Multiply: 71975
Binary: Size: 12233     Standard multiply: 72525        FFT Multiply: 72487
Binary: Size: 12141     Standard multiply: 69756        FFT Multiply: 73760
Binary: Size: 12187     Standard multiply: 68474        FFT Multiply: 75102
Binary: Size: 12210     Standard multiply: 66762        FFT Multiply: 72222
Binary: Size: 12221     Standard multiply: 73989        FFT Multiply: 76813
Binary: Size: 12227     Standard multiply: 67916        FFT Multiply: 73030
Binary: Size: 12230     Standard multiply: 67053        FFT Multiply: 74503
Binary: Size: 12231     Standard multiply: 67526        FFT Multiply: 73597
Binary: Size: 12232     Standard multiply: 67032        FFT Multiply: 72524
Binary: Size: 12232     Standard multiply: 68412        FFT Multiply: 72548
Binary: Size: 12232     Standard multiply: 68669        FFT Multiply: 73861
Binary: Size: 12232     Standard multiply: 68721        FFT Multiply: 72680
Binary: Size: 12232     Standard multiply: 67403        FFT Multiply: 73350
Binary: Size: 12232     Standard multiply: 70353        FFT Multiply: 75796
Binary: Size: 12232     Standard multiply: 69917        FFT Multiply: 72485
Binary: Size: 12232     Standard multiply: 67302        FFT Multiply: 73623
Binary: Size: 12232     Standard multiply: 68011        FFT Multiply: 74030
Binary: Size: 12232     Standard multiply: 69387        FFT Multiply: 73212
Binary: Size: 12232     Standard multiply: 68672        FFT Multiply: 71212
Binary: Size: 12232     Standard multiply: 68424        FFT Multiply: 73243
Binary: Size: 12232     Standard multiply: 67679        FFT Multiply: 73647
Binary: Size: 12232     Standard multiply: 67574        FFT Multiply: 72326
Binary: Size: 12232     Standard multiply: 69744        FFT Multiply: 72711
Binary: Size: 12232     Standard multiply: 67861        FFT Multiply: 74973
Binary: Size: 12232     Standard multiply: 66552        FFT Multiply: 75902
Binary: Size: 12232     Standard multiply: 67168        FFT Multiply: 75183
Binary: Size: 12232     Standard multiply: 70191        FFT Multiply: 76744
Binary: Size: 12232     Standard multiply: 69475        FFT Multiply: 72590
Binary: Size: 12232     Standard multiply: 68152        FFT Multiply: 74393
Binary: Size: 12232     Standard multiply: 67058        FFT Multiply: 74530
Binary: Size: 12232     Standard multiply: 68735        FFT Multiply: 72126
Binary: Size: 12232     Standard multiply: 69170        FFT Multiply: 72847
Binary: Size: 12232     Standard multiply: 69952        FFT Multiply: 72488
Binary: Size: 12232     Standard multiply: 67344        FFT Multiply: 74940
Binary: Size: 12232     Standard multiply: 67064        FFT Multiply: 73498
Binary: Size: 12232     Standard multiply: 68657        FFT Multiply: 72620
Binary: Size: 12232     Standard multiply: 71322        FFT Multiply: 72194
Binary: Size: 12232     Standard multiply: 67359        FFT Multiply: 74617
Binary: Size: 12232     Standard multiply: 68127        FFT Multiply: 74973
Binary: Size: 12232     Standard multiply: 67376        FFT Multiply: 73203
Binary: Size: 12232     Standard multiply: 76680        FFT Multiply: 71964
The compile-time parameter "c_pnMultiplicationThresholds[eBasicMultiply]" should be set to 34
The compile-time parameter "c_pnMultiplicationThresholds[e3By2]" should be set to 68
The compile-time parameter "c_pnMultiplicationThresholds[e5By3]" should be set to 76
The compile-time parameter "c_pnMultiplicationThresholds[e7By4]" should be set to 161
The compile-time parameter "c_pnMultiplicationThresholds[e9By5]" should be set to 1990006
The compile-time parameter "c_pnMultiplicationThresholds[e2NByN]" should be set to 12232
*/
void CArithmeticTuner::FindBestThresholds()
{
	FILE *pOutput;
	fopen_s(&pOutput, "BestThresholds", "w");
	CWorkspace cWork;
	c_pnMultiplicationThresholds[eBasicMultiply] = 15; // likely lower than need be
	for(DWORD i=e3By2;i<eNumMultiplyAlgorithms;i++) c_pnMultiplicationThresholds[i] = 1000000000; // make sure only testing expected algorithm
#if _USESMALLDIGITS
	for(DWORD i=eBasicMultiply;i<e7By4;i++)
#else
	for(DWORD i=eBasicMultiply;i<e9By5;i++)
#endif
	{
		if(eBasicMultiply!=i)
		{
			c_pnMultiplicationThresholds[i] = c_pnMultiplicationThresholds[i-1]+1;
		}
		GetSimpleThreshold((EMultiplyAlgorithm) i,cWork,pOutput);
	}
	Compute2NByNGrowthParameters();
	GetFFTThreshold();
	for(int i=0; i<eNumMultiplyAlgorithms-2; i++)
	{
		printf("The compile-time parameter \"c_pnMultiplicationThresholds[%s]\" should be set to %i\n", c_szMultiplicationAlgorithmNames[i], c_pnMultiplicationThresholds[i]);
	}
	fclose(pOutput);
}
/*
32-bit DIGITs
Recursive (lower threshold):
8-DIGIT divided by 4-DIGIT, threshold 4: 21922 milliseconds (100000000 iterations)
8-DIGIT divided by 4-DIGIT, threshold 5: 17094 milliseconds (100000000 iterations)
10-DIGIT divided by 5-DIGIT, threshold 5: 18937 milliseconds (100000000 iterations)
10-DIGIT divided by 5-DIGIT, threshold 6: 15781 milliseconds (100000000 iterations)
12-DIGIT divided by 6-DIGIT, threshold 6: 17922 milliseconds (100000000 iterations)
12-DIGIT divided by 6-DIGIT, threshold 7: 16375 milliseconds (100000000 iterations)
14-DIGIT divided by 7-DIGIT, threshold 7: 23141 milliseconds (100000000 iterations)
14-DIGIT divided by 7-DIGIT, threshold 8: 18031 milliseconds (100000000 iterations)
16-DIGIT divided by 8-DIGIT, threshold 8: 46125 milliseconds (100000000 iterations)
16-DIGIT divided by 8-DIGIT, threshold 9: 44063 milliseconds (100000000 iterations)
18-DIGIT divided by 9-DIGIT, threshold 9: 24234 milliseconds (50000000 iterations)
18-DIGIT divided by 9-DIGIT, threshold 10: 23922 milliseconds (50000000 iterations)
20-DIGIT divided by 10-DIGIT, threshold 10: 25047 milliseconds (50000000 iterations)
20-DIGIT divided by 10-DIGIT, threshold 11: 23328 milliseconds (50000000 iterations)
22-DIGIT divided by 11-DIGIT, threshold 11: 19125 milliseconds (50000000 iterations)
22-DIGIT divided by 11-DIGIT, threshold 12: 17687 milliseconds (50000000 iterations)
24-DIGIT divided by 12-DIGIT, threshold 12: 30172 milliseconds (50000000 iterations)
24-DIGIT divided by 12-DIGIT, threshold 13: 35594 milliseconds (50000000 iterations)
Recursive (upper threshold):
32-DIGIT divided by 16-DIGIT, threshold 4: 91109 milliseconds (100000000 iterations)
32-DIGIT divided by 16-DIGIT, threshold 5: 88782 milliseconds (100000000 iterations)
34-DIGIT divided by 17-DIGIT, threshold 5: 37062 milliseconds (50000000 iterations)
34-DIGIT divided by 17-DIGIT, threshold 6: 36547 milliseconds (50000000 iterations)
36-DIGIT divided by 18-DIGIT, threshold 6: 23656 milliseconds (25000000 iterations)
36-DIGIT divided by 18-DIGIT, threshold 7: 22906 milliseconds (25000000 iterations)
38-DIGIT divided by 19-DIGIT, threshold 7: 29079 milliseconds (25000000 iterations)
38-DIGIT divided by 19-DIGIT, threshold 8: 33187 milliseconds (25000000 iterations)
Recursive (upper threshold):
10004-DIGIT divided by 10000-DIGIT, threshold 4: 48641 milliseconds (1000000 iterations)
10004-DIGIT divided by 10000-DIGIT, threshold 5: 119047 milliseconds (1000000 iterations)

16-bit DIGITs
Recursive (lower threshold):
8-DIGIT divided by 4-DIGIT, threshold 4: 16859 milliseconds (100000000 iterations)
8-DIGIT divided by 4-DIGIT, threshold 5: 11953 milliseconds (100000000 iterations)
10-DIGIT divided by 5-DIGIT, threshold 5: 15938 milliseconds (100000000 iterations)
10-DIGIT divided by 5-DIGIT, threshold 6: 11593 milliseconds (100000000 iterations)
12-DIGIT divided by 6-DIGIT, threshold 6: 31750 milliseconds (100000000 iterations)
12-DIGIT divided by 6-DIGIT, threshold 7: 22922 milliseconds (100000000 iterations)
14-DIGIT divided by 7-DIGIT, threshold 7: 38078 milliseconds (100000000 iterations)
14-DIGIT divided by 7-DIGIT, threshold 8: 32141 milliseconds (100000000 iterations)
16-DIGIT divided by 8-DIGIT, threshold 8: 20859 milliseconds (50000000 iterations)
16-DIGIT divided by 8-DIGIT, threshold 9: 17891 milliseconds (50000000 iterations)
18-DIGIT divided by 9-DIGIT, threshold 9: 21266 milliseconds (50000000 iterations)
18-DIGIT divided by 9-DIGIT, threshold 10: 19656 milliseconds (50000000 iterations)
20-DIGIT divided by 10-DIGIT, threshold 10: 19969 milliseconds (50000000 iterations)
20-DIGIT divided by 10-DIGIT, threshold 11: 18843 milliseconds (50000000 iterations)
22-DIGIT divided by 11-DIGIT, threshold 11: 32797 milliseconds (50000000 iterations)
22-DIGIT divided by 11-DIGIT, threshold 12: 32203 milliseconds (50000000 iterations)
24-DIGIT divided by 12-DIGIT, threshold 12: 17625 milliseconds (25000000 iterations)
24-DIGIT divided by 12-DIGIT, threshold 13: 16219 milliseconds (25000000 iterations)
26-DIGIT divided by 13-DIGIT, threshold 13: 14938 milliseconds (25000000 iterations)
26-DIGIT divided by 13-DIGIT, threshold 14: 15234 milliseconds (25000000 iterations)
Recursive (upper threshold):
34-DIGIT divided by 17-DIGIT, threshold 4: 98734 milliseconds (100000000 iterations)
34-DIGIT divided by 17-DIGIT, threshold 5: 99516 milliseconds (100000000 iterations)
Recursive (upper threshold):
10004-DIGIT divided by 10000-DIGIT, threshold 4: 36219 milliseconds (1000000 iterations)
10004-DIGIT divided by 10000-DIGIT, threshold 5: 92359 milliseconds (1000000 iterations)
*/
void CArithmeticTuner::FindBestDivideThresholds()
{
	CRandomGenerator   cRandom;
	DWORD64            dwTimestamp, dwTimestamp2;
	CBigInteger        nX, nY, nXCopy, nYCopy, nXDivY;
	unsigned int       nTime1, nTime2, nSize, nIterations;
	const unsigned int c_nTenMILLION             = 10000000;
	const unsigned int c_nSmallProblemIterations = 100000000;
	const unsigned int c_nLargeProblemIterations = 1000000;
	DIGIT              *pWorkspace               = (DIGIT *) malloc(sizeof(DIGIT)*c_nTenMILLION);

	ResetThresholdsForOptimization(); // just to makie sure we have the right multiplication thresholds set

	cRandom.RandomBits(1048576, 0, true, nX); // should be big enough to test the thresholds -- a million DIGITs
	cRandom.RandomBits(524288, 0, true, nY);
	nXDivY.Reserve(nX.GetSize() - nY.GetSize() + 1);
	nXCopy = nX;
	nYCopy = nY;

	// find best divide thresholds for recursive
	printf("Recursive (lower threshold):\n");
	c_nDivideThresholdSmall = 4;
	nIterations             = c_nSmallProblemIterations;
#if _CollectDetailedTimingData
	dwTimestamp = s_Timer.GetMicroseconds();
#endif
	do
	{
		nXCopy.SetSize(2*c_nDivideThresholdSmall);
		nYCopy.SetSize(c_nDivideThresholdSmall);
		nTime1 = ::GetTickCount();
		for(int i=0; i<nIterations; i++)
		{
			memcpy(nXCopy.GetValue(), nX.GetValue(), nXCopy.GetSize()*sizeof(DIGIT)*sizeof(DIGIT));
			memcpy(nYCopy.GetValue(), nY.GetValue(), nYCopy.GetSize()*sizeof(DIGIT)*sizeof(DIGIT));
#if _CollectDetailedTimingData
			DivideRecursive(nXCopy.GetSize(), nYCopy.GetSize(), nXCopy.GetValue(), nYCopy.GetValue(), nXDivY.GetValue(), dwTimestamp, pWorkspace);
#else
			DivideRecursive(nXCopy.GetSize(), nYCopy.GetSize(), nXCopy.GetValue(), nYCopy.GetValue(), nXDivY.GetValue(), pWorkspace);
#endif
		}
		nTime1 = ::GetTickCount() - nTime1;
		printf("%i-DIGIT divided by %i-DIGIT, threshold %i: %i milliseconds (%i iterations)\n", nXCopy.GetSize(), nYCopy.GetSize(), c_nDivideThresholdSmall, nTime1, nIterations);
		c_nDivideThresholdSmall++;
		nTime2 = ::GetTickCount();
		for(int i=0; i<nIterations; i++)
		{
			memcpy(nXCopy.GetValue(), nX.GetValue(), nXCopy.GetSize()*sizeof(DIGIT)*sizeof(DIGIT));
			memcpy(nYCopy.GetValue(), nY.GetValue(), nYCopy.GetSize()*sizeof(DIGIT)*sizeof(DIGIT));
#if _CollectDetailedTimingData
			DivideRecursive(nXCopy.GetSize(), nYCopy.GetSize(), nXCopy.GetValue(), nYCopy.GetValue(), nXDivY.GetValue(), dwTimestamp, pWorkspace);
#else
			DivideRecursive(nXCopy.GetSize(), nYCopy.GetSize(), nXCopy.GetValue(), nYCopy.GetValue(), nXDivY.GetValue(), pWorkspace);
#endif
		}
		nTime2 = ::GetTickCount() - nTime2;
		printf("%i-DIGIT divided by %i-DIGIT, threshold %i: %i milliseconds (%i iterations)\n", nXCopy.GetSize(), nYCopy.GetSize(), c_nDivideThresholdSmall, nTime2, nIterations);
		if(30000<nTime2) nIterations = (nIterations+1)/2; // too much time!
	}
	while(nTime1>nTime2);
	printf("Recursive (upper threshold):\n");
	c_nDivideThresholdSmall--; // best lower threshold
	c_nDivideThresholdDiff  = 4;
	nIterations             = c_nSmallProblemIterations;
	do
	{
		nXCopy.SetSize(2*(c_nDivideThresholdSmall+c_nDivideThresholdDiff));
		nYCopy.SetSize(c_nDivideThresholdSmall+c_nDivideThresholdDiff);
		nTime1 = ::GetTickCount();
		for(int i=0; i<nIterations; i++)
		{
			memcpy(nXCopy.GetValue(), nX.GetValue(), nXCopy.GetSize()*sizeof(DIGIT)*sizeof(DIGIT));
			memcpy(nYCopy.GetValue(), nY.GetValue(), nYCopy.GetSize()*sizeof(DIGIT)*sizeof(DIGIT));
#if _CollectDetailedTimingData
			DivideRecursive(nXCopy.GetSize(), nYCopy.GetSize(), nXCopy.GetValue(), nYCopy.GetValue(), nXDivY.GetValue(), dwTimestamp, pWorkspace);
#else
			DivideRecursive(nXCopy.GetSize(), nYCopy.GetSize(), nXCopy.GetValue(), nYCopy.GetValue(), nXDivY.GetValue(), pWorkspace);
#endif
		}
		nTime1 = ::GetTickCount() - nTime1;
		printf("%i-DIGIT divided by %i-DIGIT, threshold %i: %i milliseconds (%i iterations)\n", nXCopy.GetSize(), nYCopy.GetSize(), c_nDivideThresholdDiff, nTime1, nIterations);
		c_nDivideThresholdDiff++;
		nTime2 = ::GetTickCount();
		for(int i=0; i<nIterations; i++)
		{
			memcpy(nXCopy.GetValue(), nX.GetValue(), nXCopy.GetSize()*sizeof(DIGIT)*sizeof(DIGIT));
			memcpy(nYCopy.GetValue(), nY.GetValue(), nYCopy.GetSize()*sizeof(DIGIT)*sizeof(DIGIT));
#if _CollectDetailedTimingData
			DivideRecursive(nXCopy.GetSize(), nYCopy.GetSize(), nXCopy.GetValue(), nYCopy.GetValue(), nXDivY.GetValue(), dwTimestamp, pWorkspace);
#else
			DivideRecursive(nXCopy.GetSize(), nYCopy.GetSize(), nXCopy.GetValue(), nYCopy.GetValue(), nXDivY.GetValue(), pWorkspace);
#endif
		}
		nTime2 = ::GetTickCount() - nTime2;
		printf("%i-DIGIT divided by %i-DIGIT, threshold %i: %i milliseconds (%i iterations)\n", nXCopy.GetSize(), nYCopy.GetSize(), c_nDivideThresholdDiff, nTime2, nIterations);
		if(30000<nTime2) nIterations = (nIterations+1)/2; // too much time!
	}
	while(nTime1>nTime2);
	printf("Recursive (upper threshold):\n");
	c_nDivideThresholdDiff = 4;
	nIterations            = c_nLargeProblemIterations;
	do
	{
		nXCopy.SetSize(10000+c_nDivideThresholdDiff);
		nYCopy.SetSize(10000);
		nTime1 = ::GetTickCount();
		for(int i=0; i<nIterations; i++)
		{
			memcpy(nXCopy.GetValue(), nX.GetValue(), nXCopy.GetSize()*sizeof(DIGIT)*sizeof(DIGIT));
			memcpy(nYCopy.GetValue(), nY.GetValue(), nYCopy.GetSize()*sizeof(DIGIT)*sizeof(DIGIT));
#if _CollectDetailedTimingData
			DivideRecursive(nXCopy.GetSize(), nYCopy.GetSize(), nXCopy.GetValue(), nYCopy.GetValue(), nXDivY.GetValue(), dwTimestamp, pWorkspace);
#else
			DivideRecursive(nXCopy.GetSize(), nYCopy.GetSize(), nXCopy.GetValue(), nYCopy.GetValue(), nXDivY.GetValue(), pWorkspace);
#endif
		}
		nTime1 = ::GetTickCount() - nTime1;
		printf("%i-DIGIT divided by %i-DIGIT, threshold %i: %i milliseconds (%i iterations)\n", nXCopy.GetSize(), nYCopy.GetSize(), c_nDivideThresholdDiff, nTime1, nIterations);
		c_nDivideThresholdDiff++;
		nTime2 = ::GetTickCount();
		for(int i=0; i<nIterations; i++)
		{
			memcpy(nXCopy.GetValue(), nX.GetValue(), nXCopy.GetSize()*sizeof(DIGIT)*sizeof(DIGIT));
			memcpy(nYCopy.GetValue(), nY.GetValue(), nYCopy.GetSize()*sizeof(DIGIT)*sizeof(DIGIT));
#if _CollectDetailedTimingData
			DivideRecursive(nXCopy.GetSize(), nYCopy.GetSize(), nXCopy.GetValue(), nYCopy.GetValue(), nXDivY.GetValue(), dwTimestamp, pWorkspace);
#else
			DivideRecursive(nXCopy.GetSize(), nYCopy.GetSize(), nXCopy.GetValue(), nYCopy.GetValue(), nXDivY.GetValue(), pWorkspace);
#endif
		}
		nTime2 = ::GetTickCount() - nTime2;
		printf("%i-DIGIT divided by %i-DIGIT, threshold %i: %i milliseconds (%i iterations)\n", nXCopy.GetSize(), nYCopy.GetSize(), c_nDivideThresholdDiff, nTime2, nIterations);
		if(30000<nTime2) nIterations = (nIterations+1)/2; // too much time!
	}
	while(nTime1>nTime2);
}


#if 0 // outdated -- simple threshold not appropriate.  Used the below code to determine what IS.
/*
16-bit DIGITs run:
Size: 2  Digits: 1  Iterations: 8388608 Basic: 1531 milliseconds  Strassen: 9266 milliseconds
Size: 2  Digits: 2  Iterations: 8388608 Basic: 1640 milliseconds  Strassen: 9406 milliseconds
Size: 2  Digits: 3  Iterations: 8388608 Basic: 1734 milliseconds  Strassen: 9797 milliseconds
Size: 2  Digits: 4  Iterations: 4194304 Basic: 1094 milliseconds  Strassen: 5125 milliseconds
Size: 2  Digits: 5  Iterations: 4194304 Basic: 1328 milliseconds  Strassen: 5360 milliseconds
Size: 2  Digits: 6  Iterations: 4194304 Basic: 1547 milliseconds  Strassen: 6328 milliseconds
Size: 2  Digits: 7  Iterations: 4194304 Basic: 1843 milliseconds  Strassen: 6422 milliseconds
Size: 2  Digits: 8  Iterations: 2097152 Basic: 1141 milliseconds  Strassen: 3203 milliseconds
Size: 2  Digits: 9  Iterations: 2097152 Basic: 1718 milliseconds  Strassen: 3860 milliseconds
Size: 2  Digits: 10  Iterations: 1048576        Basic: 1031 milliseconds  Strassen: 2141 milliseconds
Size: 2  Digits: 11  Iterations: 1048576        Basic: 1282 milliseconds  Strassen: 2406 milliseconds
Size: 2  Digits: 12  Iterations: 1048576        Basic: 1391 milliseconds  Strassen: 2484 milliseconds
Size: 2  Digits: 13  Iterations: 1048576        Basic: 1437 milliseconds  Strassen: 3125 milliseconds
Size: 2  Digits: 14  Iterations: 1048576        Basic: 1578 milliseconds  Strassen: 3359 milliseconds
Size: 2  Digits: 15  Iterations: 524288 Basic: 1204 milliseconds  Strassen: 1984 milliseconds
Size: 2  Digits: 16  Iterations: 524288 Basic: 1250 milliseconds  Strassen: 2265 milliseconds
Size: 2  Digits: 17  Iterations: 524288 Basic: 1562 milliseconds  Strassen: 2516 milliseconds
Size: 2  Digits: 18  Iterations: 524288 Basic: 1687 milliseconds  Strassen: 2406 milliseconds
Size: 2  Digits: 19  Iterations: 524288 Basic: 1859 milliseconds  Strassen: 2688 milliseconds
Size: 2  Digits: 20  Iterations: 262144 Basic: 1203 milliseconds  Strassen: 1547 milliseconds
Size: 2  Digits: 21  Iterations: 262144 Basic: 1078 milliseconds  Strassen: 1312 milliseconds
Size: 2  Digits: 22  Iterations: 262144 Basic: 1125 milliseconds  Strassen: 1422 milliseconds
Size: 2  Digits: 23  Iterations: 262144 Basic: 1250 milliseconds  Strassen: 1390 milliseconds
Size: 2  Digits: 24  Iterations: 262144 Basic: 1172 milliseconds  Strassen: 1422 milliseconds
Size: 2  Digits: 25  Iterations: 262144 Basic: 1234 milliseconds  Strassen: 1453 milliseconds
Size: 2  Digits: 26  Iterations: 262144 Basic: 1265 milliseconds  Strassen: 1563 milliseconds
Size: 2  Digits: 27  Iterations: 262144 Basic: 1563 milliseconds  Strassen: 1687 milliseconds
Size: 2  Digits: 28  Iterations: 262144 Basic: 1610 milliseconds  Strassen: 1890 milliseconds
Size: 2  Digits: 29  Iterations: 262144 Basic: 1829 milliseconds  Strassen: 1953 milliseconds
Size: 2  Digits: 30  Iterations: 262144 Basic: 1953 milliseconds  Strassen: 2078 milliseconds
Size: 2  Digits: 31  Iterations: 131072 Basic: 1063 milliseconds  Strassen: 1203 milliseconds
Size: 2  Digits: 32  Iterations: 131072 Basic: 1109 milliseconds  Strassen: 1391 milliseconds
Size: 2  Digits: 33  Iterations: 131072 Basic: 1172 milliseconds  Strassen: 1234 milliseconds
Size: 2  Digits: 34  Iterations: 131072 Basic: 1250 milliseconds  Strassen: 1391 milliseconds
Size: 2  Digits: 35  Iterations: 131072 Basic: 1328 milliseconds  Strassen: 1422 milliseconds
Size: 2  Digits: 36  Iterations: 131072 Basic: 1343 milliseconds  Strassen: 1453 milliseconds
Size: 2  Digits: 37  Iterations: 131072 Basic: 1485 milliseconds  Strassen: 1484 milliseconds
Size: 4  Digits: 1  Iterations: 1048576 Basic: 1610 milliseconds  Strassen: 4218 milliseconds
Size: 4  Digits: 2  Iterations: 1048576 Basic: 1860 milliseconds  Strassen: 4500 milliseconds
Size: 4  Digits: 3  Iterations: 524288  Basic: 1094 milliseconds  Strassen: 2406 milliseconds
Size: 4  Digits: 4  Iterations: 524288  Basic: 1203 milliseconds  Strassen: 2547 milliseconds
Size: 4  Digits: 5  Iterations: 524288  Basic: 1454 milliseconds  Strassen: 3000 milliseconds
Size: 4  Digits: 6  Iterations: 524288  Basic: 1828 milliseconds  Strassen: 3343 milliseconds
Size: 4  Digits: 7  Iterations: 262144  Basic: 1047 milliseconds  Strassen: 1844 milliseconds
Size: 4  Digits: 8  Iterations: 262144  Basic: 1359 milliseconds  Strassen: 2094 milliseconds
Size: 4  Digits: 9  Iterations: 262144  Basic: 1766 milliseconds  Strassen: 2515 milliseconds
Size: 4  Digits: 10  Iterations: 131072 Basic: 1109 milliseconds  Strassen: 1406 milliseconds
Size: 4  Digits: 11  Iterations: 131072 Basic: 1313 milliseconds  Strassen: 1718 milliseconds
Size: 4  Digits: 12  Iterations: 131072 Basic: 1391 milliseconds  Strassen: 1843 milliseconds
Size: 4  Digits: 13  Iterations: 131072 Basic: 1406 milliseconds  Strassen: 1672 milliseconds
Size: 4  Digits: 14  Iterations: 131072 Basic: 1641 milliseconds  Strassen: 2078 milliseconds
Size: 4  Digits: 15  Iterations: 65536  Basic: 1328 milliseconds  Strassen: 1391 milliseconds
Size: 4  Digits: 16  Iterations: 65536  Basic: 1312 milliseconds  Strassen: 1469 milliseconds
Size: 4  Digits: 17  Iterations: 65536  Basic: 1547 milliseconds  Strassen: 1672 milliseconds
Size: 4  Digits: 18  Iterations: 65536  Basic: 1813 milliseconds  Strassen: 1844 milliseconds
Size: 4  Digits: 19  Iterations: 65536  Basic: 1907 milliseconds  Strassen: 1922 milliseconds
Size: 4  Digits: 20  Iterations: 65536  Basic: 2031 milliseconds  Strassen: 2047 milliseconds
Size: 4  Digits: 21  Iterations: 32768  Basic: 1250 milliseconds  Strassen: 1203 milliseconds
Size: 8  Digits: 1  Iterations: 65536   Basic: 1063 milliseconds  Strassen: 1515 milliseconds
Size: 8  Digits: 2  Iterations: 65536   Basic: 1109 milliseconds  Strassen: 1875 milliseconds
Size: 8  Digits: 3  Iterations: 65536   Basic: 1219 milliseconds  Strassen: 1703 milliseconds
Size: 8  Digits: 4  Iterations: 65536   Basic: 1344 milliseconds  Strassen: 1828 milliseconds
Size: 8  Digits: 5  Iterations: 65536   Basic: 1640 milliseconds  Strassen: 2203 milliseconds
Size: 8  Digits: 6  Iterations: 65536   Basic: 1844 milliseconds  Strassen: 2328 milliseconds
Size: 8  Digits: 7  Iterations: 32768   Basic: 1109 milliseconds  Strassen: 1329 milliseconds
Size: 8  Digits: 8  Iterations: 32768   Basic: 1360 milliseconds  Strassen: 1765 milliseconds
Size: 8  Digits: 9  Iterations: 32768   Basic: 1922 milliseconds  Strassen: 2109 milliseconds
Size: 8  Digits: 10  Iterations: 16384  Basic: 1234 milliseconds  Strassen: 1313 milliseconds
Size: 8  Digits: 11  Iterations: 16384  Basic: 1406 milliseconds  Strassen: 1422 milliseconds
Size: 8  Digits: 12  Iterations: 16384  Basic: 1500 milliseconds  Strassen: 1578 milliseconds
Size: 8  Digits: 13  Iterations: 16384  Basic: 1437 milliseconds  Strassen: 1719 milliseconds
Size: 8  Digits: 14  Iterations: 16384  Basic: 1750 milliseconds  Strassen: 2000 milliseconds
Size: 8  Digits: 15  Iterations: 8192   Basic: 1453 milliseconds  Strassen: 1391 milliseconds
Size: 16  Digits: 1  Iterations: 8192   Basic: 1078 milliseconds  Strassen: 1500 milliseconds
Size: 16  Digits: 2  Iterations: 8192   Basic: 1328 milliseconds  Strassen: 1672 milliseconds
Size: 16  Digits: 3  Iterations: 8192   Basic: 1297 milliseconds  Strassen: 1750 milliseconds
Size: 16  Digits: 4  Iterations: 8192   Basic: 1563 milliseconds  Strassen: 1891 milliseconds
Size: 16  Digits: 5  Iterations: 8192   Basic: 1703 milliseconds  Strassen: 2203 milliseconds
Size: 16  Digits: 6  Iterations: 4096   Basic: 1047 milliseconds  Strassen: 1297 milliseconds
Size: 16  Digits: 7  Iterations: 4096   Basic: 1281 milliseconds  Strassen: 1375 milliseconds
Size: 16  Digits: 8  Iterations: 4096   Basic: 1328 milliseconds  Strassen: 1485 milliseconds
Size: 16  Digits: 9  Iterations: 4096   Basic: 2000 milliseconds  Strassen: 2172 milliseconds
Size: 16  Digits: 10  Iterations: 2048  Basic: 1391 milliseconds  Strassen: 1343 milliseconds
Size: 32  Digits: 1  Iterations: 1024   Basic: 1219 milliseconds  Strassen: 1375 milliseconds
Size: 32  Digits: 2  Iterations: 1024   Basic: 1329 milliseconds  Strassen: 1546 milliseconds
Size: 32  Digits: 3  Iterations: 1024   Basic: 1437 milliseconds  Strassen: 1610 milliseconds
Size: 32  Digits: 4  Iterations: 1024   Basic: 1734 milliseconds  Strassen: 1938 milliseconds
Size: 32  Digits: 5  Iterations: 512    Basic: 1125 milliseconds  Strassen: 1047 milliseconds
Size: 64  Digits: 1  Iterations: 128    Basic: 1203 milliseconds  Strassen: 1281 milliseconds
Size: 64  Digits: 2  Iterations: 128    Basic: 1468 milliseconds  Strassen: 1453 milliseconds
Size: 128  Digits: 1  Iterations: 16    Basic: 1609 milliseconds  Strassen: 1547 milliseconds

Size: 2  Digits: 1  Iterations: 8388608 Basic: 1610 milliseconds  Strassen: 9640 milliseconds
Size: 2  Digits: 2  Iterations: 8388608 Basic: 1641 milliseconds  Strassen: 10187 milliseconds
Size: 2  Digits: 3  Iterations: 8388608 Basic: 1703 milliseconds  Strassen: 9828 milliseconds
Size: 2  Digits: 4  Iterations: 4194304 Basic: 1078 milliseconds  Strassen: 5219 milliseconds
Size: 2  Digits: 5  Iterations: 4194304 Basic: 1406 milliseconds  Strassen: 5703 milliseconds
Size: 2  Digits: 6  Iterations: 4194304 Basic: 1704 milliseconds  Strassen: 6359 milliseconds
Size: 2  Digits: 7  Iterations: 2097152 Basic: 1203 milliseconds  Strassen: 3454 milliseconds
Size: 2  Digits: 8  Iterations: 2097152 Basic: 1187 milliseconds  Strassen: 3641 milliseconds
Size: 2  Digits: 9  Iterations: 1048576 Basic: 1015 milliseconds  Strassen: 2188 milliseconds
Size: 2  Digits: 10  Iterations: 1048576        Basic: 1312 milliseconds  Strassen: 2547 milliseconds
Size: 2  Digits: 11  Iterations: 1048576        Basic: 1609 milliseconds  Strassen: 2766 milliseconds
Size: 2  Digits: 12  Iterations: 1048576        Basic: 1469 milliseconds  Strassen: 2672 milliseconds
Size: 2  Digits: 13  Iterations: 1048576        Basic: 1547 milliseconds  Strassen: 3500 milliseconds
Size: 2  Digits: 14  Iterations: 1048576        Basic: 1828 milliseconds  Strassen: 3688 milliseconds
Size: 2  Digits: 15  Iterations: 524288 Basic: 1375 milliseconds  Strassen: 2266 milliseconds
Size: 2  Digits: 16  Iterations: 524288 Basic: 1437 milliseconds  Strassen: 2516 milliseconds
Size: 2  Digits: 17  Iterations: 524288 Basic: 1703 milliseconds  Strassen: 2594 milliseconds
Size: 2  Digits: 18  Iterations: 524288 Basic: 1844 milliseconds  Strassen: 2734 milliseconds
Size: 2  Digits: 19  Iterations: 262144 Basic: 1110 milliseconds  Strassen: 1547 milliseconds
Size: 2  Digits: 20  Iterations: 262144 Basic: 1078 milliseconds  Strassen: 1578 milliseconds
Size: 2  Digits: 21  Iterations: 262144 Basic: 1203 milliseconds  Strassen: 1547 milliseconds
Size: 2  Digits: 22  Iterations: 262144 Basic: 1266 milliseconds  Strassen: 1500 milliseconds
Size: 2  Digits: 23  Iterations: 262144 Basic: 1375 milliseconds  Strassen: 1625 milliseconds
Size: 2  Digits: 24  Iterations: 262144 Basic: 1344 milliseconds  Strassen: 1625 milliseconds
Size: 2  Digits: 25  Iterations: 262144 Basic: 1438 milliseconds  Strassen: 1703 milliseconds
Size: 2  Digits: 26  Iterations: 262144 Basic: 1375 milliseconds  Strassen: 1735 milliseconds
Size: 2  Digits: 27  Iterations: 262144 Basic: 1781 milliseconds  Strassen: 1844 milliseconds
Size: 2  Digits: 28  Iterations: 262144 Basic: 1906 milliseconds  Strassen: 2094 milliseconds
Size: 2  Digits: 29  Iterations: 131072 Basic: 1016 milliseconds  Strassen: 1063 milliseconds
Size: 2  Digits: 30  Iterations: 131072 Basic: 1015 milliseconds  Strassen: 1094 milliseconds
Size: 2  Digits: 31  Iterations: 131072 Basic: 1125 milliseconds  Strassen: 1219 milliseconds
Size: 2  Digits: 32  Iterations: 131072 Basic: 1094 milliseconds  Strassen: 1344 milliseconds
Size: 2  Digits: 33  Iterations: 131072 Basic: 1250 milliseconds  Strassen: 1328 milliseconds
Size: 2  Digits: 34  Iterations: 131072 Basic: 1437 milliseconds  Strassen: 1438 milliseconds
Size: 2  Digits: 35  Iterations: 131072 Basic: 1360 milliseconds  Strassen: 1437 milliseconds
Size: 2  Digits: 36  Iterations: 131072 Basic: 1500 milliseconds  Strassen: 1515 milliseconds
Size: 2  Digits: 37  Iterations: 131072 Basic: 1547 milliseconds  Strassen: 1500 milliseconds
Size: 4  Digits: 1  Iterations: 1048576 Basic: 1625 milliseconds  Strassen: 4656 milliseconds
Size: 4  Digits: 2  Iterations: 1048576 Basic: 1875 milliseconds  Strassen: 4547 milliseconds
Size: 4  Digits: 3  Iterations: 524288  Basic: 1093 milliseconds  Strassen: 2407 milliseconds
Size: 4  Digits: 4  Iterations: 524288  Basic: 1250 milliseconds  Strassen: 2531 milliseconds
Size: 4  Digits: 5  Iterations: 524288  Basic: 1484 milliseconds  Strassen: 2937 milliseconds
Size: 4  Digits: 6  Iterations: 524288  Basic: 1672 milliseconds  Strassen: 3078 milliseconds
Size: 4  Digits: 7  Iterations: 262144  Basic: 1031 milliseconds  Strassen: 1672 milliseconds
Size: 4  Digits: 8  Iterations: 262144  Basic: 1250 milliseconds  Strassen: 1953 milliseconds
Size: 4  Digits: 9  Iterations: 262144  Basic: 1797 milliseconds  Strassen: 2578 milliseconds
Size: 4  Digits: 10  Iterations: 131072 Basic: 1125 milliseconds  Strassen: 1438 milliseconds
Size: 4  Digits: 11  Iterations: 131072 Basic: 1344 milliseconds  Strassen: 1656 milliseconds
Size: 4  Digits: 12  Iterations: 131072 Basic: 1422 milliseconds  Strassen: 1859 milliseconds
Size: 4  Digits: 13  Iterations: 131072 Basic: 1422 milliseconds  Strassen: 1734 milliseconds
Size: 4  Digits: 14  Iterations: 131072 Basic: 1828 milliseconds  Strassen: 2094 milliseconds
Size: 4  Digits: 15  Iterations: 65536  Basic: 1266 milliseconds  Strassen: 1359 milliseconds
Size: 4  Digits: 16  Iterations: 65536  Basic: 1297 milliseconds  Strassen: 1500 milliseconds
Size: 4  Digits: 17  Iterations: 65536  Basic: 1562 milliseconds  Strassen: 1657 milliseconds
Size: 4  Digits: 18  Iterations: 65536  Basic: 1735 milliseconds  Strassen: 1859 milliseconds
Size: 4  Digits: 19  Iterations: 65536  Basic: 1906 milliseconds  Strassen: 1969 milliseconds
Size: 4  Digits: 20  Iterations: 32768  Basic: 1031 milliseconds  Strassen: 1047 milliseconds
Size: 4  Digits: 21  Iterations: 32768  Basic: 1094 milliseconds  Strassen: 1140 milliseconds
Size: 4  Digits: 22  Iterations: 32768  Basic: 1188 milliseconds  Strassen: 1172 milliseconds
Size: 8  Digits: 1  Iterations: 131072  Basic: 2031 milliseconds  Strassen: 2859 milliseconds
Size: 8  Digits: 2  Iterations: 65536   Basic: 1078 milliseconds  Strassen: 1500 milliseconds
Size: 8  Digits: 3  Iterations: 65536   Basic: 1234 milliseconds  Strassen: 1719 milliseconds
Size: 8  Digits: 4  Iterations: 65536   Basic: 1391 milliseconds  Strassen: 1875 milliseconds
Size: 8  Digits: 5  Iterations: 65536   Basic: 1625 milliseconds  Strassen: 2094 milliseconds
Size: 8  Digits: 6  Iterations: 32768   Basic: 1109 milliseconds  Strassen: 1329 milliseconds
Size: 8  Digits: 7  Iterations: 32768   Basic: 1343 milliseconds  Strassen: 1610 milliseconds
Size: 8  Digits: 8  Iterations: 32768   Basic: 1344 milliseconds  Strassen: 1609 milliseconds
Size: 8  Digits: 9  Iterations: 16384   Basic: 1062 milliseconds  Strassen: 1157 milliseconds
Size: 8  Digits: 10  Iterations: 16384  Basic: 1406 milliseconds  Strassen: 1454 milliseconds
Size: 8  Digits: 11  Iterations: 16384  Basic: 1750 milliseconds  Strassen: 1703 milliseconds
Size: 16  Digits: 1  Iterations: 8192   Basic: 1266 milliseconds  Strassen: 1750 milliseconds
Size: 16  Digits: 2  Iterations: 8192   Basic: 1328 milliseconds  Strassen: 1765 milliseconds
Size: 16  Digits: 3  Iterations: 8192   Basic: 1500 milliseconds  Strassen: 1906 milliseconds
Size: 16  Digits: 4  Iterations: 8192   Basic: 1578 milliseconds  Strassen: 2000 milliseconds
Size: 16  Digits: 5  Iterations: 8192   Basic: 1922 milliseconds  Strassen: 2485 milliseconds
Size: 16  Digits: 6  Iterations: 4096   Basic: 1156 milliseconds  Strassen: 1281 milliseconds
Size: 16  Digits: 7  Iterations: 4096   Basic: 1313 milliseconds  Strassen: 1515 milliseconds
Size: 16  Digits: 8  Iterations: 4096   Basic: 1453 milliseconds  Strassen: 1656 milliseconds
Size: 16  Digits: 9  Iterations: 2048   Basic: 1109 milliseconds  Strassen: 1204 milliseconds
Size: 16  Digits: 10  Iterations: 2048  Basic: 1531 milliseconds  Strassen: 1516 milliseconds
Size: 32  Digits: 1  Iterations: 1024   Basic: 1359 milliseconds  Strassen: 1531 milliseconds
Size: 32  Digits: 2  Iterations: 1024   Basic: 1390 milliseconds  Strassen: 1516 milliseconds
Size: 32  Digits: 3  Iterations: 1024   Basic: 1516 milliseconds  Strassen: 1718 milliseconds
Size: 32  Digits: 4  Iterations: 1024   Basic: 1688 milliseconds  Strassen: 1953 milliseconds
Size: 32  Digits: 5  Iterations: 512    Basic: 1078 milliseconds  Strassen: 1078 milliseconds
Size: 64  Digits: 1  Iterations: 128    Basic: 1297 milliseconds  Strassen: 1375 milliseconds
Size: 64  Digits: 2  Iterations: 128    Basic: 1453 milliseconds  Strassen: 1469 milliseconds
Size: 64  Digits: 3  Iterations: 128    Basic: 1657 milliseconds  Strassen: 1625 milliseconds
Size: 128  Digits: 1  Iterations: 16    Basic: 1500 milliseconds  Strassen: 1375 milliseconds

32-bit DIGITs
Size: 2  Digits: 1  Iterations: 8388608 Basic: 1438 milliseconds  Strassen: 9031 milliseconds
Size: 2  Digits: 2  Iterations: 8388608 Basic: 1531 milliseconds  Strassen: 9360 milliseconds
Size: 2  Digits: 3  Iterations: 4194304 Basic: 1031 milliseconds  Strassen: 4875 milliseconds
Size: 2  Digits: 4  Iterations: 4194304 Basic: 1141 milliseconds  Strassen: 5437 milliseconds
Size: 2  Digits: 5  Iterations: 4194304 Basic: 1531 milliseconds  Strassen: 7390 milliseconds
Size: 2  Digits: 6  Iterations: 4194304 Basic: 1703 milliseconds  Strassen: 7313 milliseconds
Size: 2  Digits: 7  Iterations: 2097152 Basic: 1094 milliseconds  Strassen: 5484 milliseconds
Size: 2  Digits: 8  Iterations: 2097152 Basic: 1312 milliseconds  Strassen: 6109 milliseconds
Size: 2  Digits: 9  Iterations: 2097152 Basic: 1907 milliseconds  Strassen: 4609 milliseconds
Size: 2  Digits: 10  Iterations: 1048576        Basic: 1204 milliseconds  Strassen: 2640 milliseconds
Size: 2  Digits: 11  Iterations: 1048576        Basic: 1312 milliseconds  Strassen: 2734 milliseconds
Size: 2  Digits: 12  Iterations: 1048576        Basic: 1531 milliseconds  Strassen: 2937 milliseconds
Size: 2  Digits: 13  Iterations: 1048576        Basic: 1578 milliseconds  Strassen: 3125 milliseconds
Size: 2  Digits: 14  Iterations: 524288 Basic: 1063 milliseconds  Strassen: 1594 milliseconds
Size: 2  Digits: 15  Iterations: 524288 Basic: 1110 milliseconds  Strassen: 1687 milliseconds
Size: 2  Digits: 16  Iterations: 524288 Basic: 1125 milliseconds  Strassen: 1781 milliseconds
Size: 2  Digits: 17  Iterations: 524288 Basic: 1141 milliseconds  Strassen: 1781 milliseconds
Size: 2  Digits: 18  Iterations: 524288 Basic: 1391 milliseconds  Strassen: 2062 milliseconds
Size: 2  Digits: 19  Iterations: 524288 Basic: 1531 milliseconds  Strassen: 2204 milliseconds
Size: 2  Digits: 20  Iterations: 524288 Basic: 1625 milliseconds  Strassen: 2281 milliseconds
Size: 2  Digits: 21  Iterations: 524288 Basic: 1578 milliseconds  Strassen: 2297 milliseconds
Size: 2  Digits: 22  Iterations: 524288 Basic: 1859 milliseconds  Strassen: 2484 milliseconds
Size: 2  Digits: 23  Iterations: 262144 Basic: 1078 milliseconds  Strassen: 1360 milliseconds
Size: 2  Digits: 24  Iterations: 524288 Basic: 2094 milliseconds  Strassen: 2812 milliseconds
Size: 2  Digits: 25  Iterations: 262144 Basic: 1109 milliseconds  Strassen: 1516 milliseconds
Size: 2  Digits: 26  Iterations: 262144 Basic: 1219 milliseconds  Strassen: 1516 milliseconds
Size: 2  Digits: 27  Iterations: 262144 Basic: 1407 milliseconds  Strassen: 1859 milliseconds
Size: 2  Digits: 28  Iterations: 262144 Basic: 1547 milliseconds  Strassen: 1782 milliseconds
Size: 2  Digits: 29  Iterations: 262144 Basic: 1407 milliseconds  Strassen: 1703 milliseconds
Size: 2  Digits: 30  Iterations: 262144 Basic: 1578 milliseconds  Strassen: 1938 milliseconds
Size: 2  Digits: 31  Iterations: 262144 Basic: 1813 milliseconds  Strassen: 2015 milliseconds
Size: 2  Digits: 32  Iterations: 262144 Basic: 1782 milliseconds  Strassen: 2171 milliseconds
Size: 2  Digits: 33  Iterations: 262144 Basic: 1812 milliseconds  Strassen: 2125 milliseconds
Size: 2  Digits: 34  Iterations: 131072 Basic: 1016 milliseconds  Strassen: 1187 milliseconds
Size: 2  Digits: 35  Iterations: 131072 Basic: 1235 milliseconds  Strassen: 1218 milliseconds
Size: 4  Digits: 1  Iterations: 524288  Basic: 1015 milliseconds  Strassen: 2688 milliseconds
Size: 4  Digits: 2  Iterations: 524288  Basic: 1063 milliseconds  Strassen: 2843 milliseconds
Size: 4  Digits: 3  Iterations: 524288  Basic: 1422 milliseconds  Strassen: 4000 milliseconds
Size: 4  Digits: 4  Iterations: 524288  Basic: 1969 milliseconds  Strassen: 4094 milliseconds
Size: 4  Digits: 5  Iterations: 262144  Basic: 1235 milliseconds  Strassen: 2296 milliseconds
Size: 4  Digits: 6  Iterations: 262144  Basic: 1156 milliseconds  Strassen: 1922 milliseconds
Size: 4  Digits: 7  Iterations: 262144  Basic: 1328 milliseconds  Strassen: 2188 milliseconds
Size: 4  Digits: 8  Iterations: 262144  Basic: 1344 milliseconds  Strassen: 2344 milliseconds
Size: 4  Digits: 9  Iterations: 131072  Basic: 1031 milliseconds  Strassen: 1531 milliseconds
Size: 4  Digits: 10  Iterations: 131072 Basic: 1297 milliseconds  Strassen: 1766 milliseconds
Size: 4  Digits: 11  Iterations: 131072 Basic: 1625 milliseconds  Strassen: 1938 milliseconds
Size: 4  Digits: 12  Iterations: 131072 Basic: 1703 milliseconds  Strassen: 2204 milliseconds
Size: 4  Digits: 13  Iterations: 131072 Basic: 1672 milliseconds  Strassen: 2172 milliseconds
Size: 4  Digits: 14  Iterations: 65536  Basic: 1016 milliseconds  Strassen: 1188 milliseconds
Size: 4  Digits: 15  Iterations: 65536  Basic: 1172 milliseconds  Strassen: 1312 milliseconds
Size: 4  Digits: 16  Iterations: 65536  Basic: 1250 milliseconds  Strassen: 1765 milliseconds
Size: 4  Digits: 17  Iterations: 65536  Basic: 1110 milliseconds  Strassen: 1219 milliseconds
Size: 4  Digits: 18  Iterations: 65536  Basic: 1218 milliseconds  Strassen: 1360 milliseconds
Size: 4  Digits: 19  Iterations: 65536  Basic: 1375 milliseconds  Strassen: 1500 milliseconds
Size: 4  Digits: 20  Iterations: 65536  Basic: 1531 milliseconds  Strassen: 1719 milliseconds
Size: 4  Digits: 21  Iterations: 65536  Basic: 1453 milliseconds  Strassen: 1547 milliseconds
Size: 4  Digits: 22  Iterations: 65536  Basic: 1640 milliseconds  Strassen: 1735 milliseconds
Size: 4  Digits: 23  Iterations: 65536  Basic: 1891 milliseconds  Strassen: 1922 milliseconds
Size: 4  Digits: 24  Iterations: 65536  Basic: 2031 milliseconds  Strassen: 2063 milliseconds
Size: 4  Digits: 25  Iterations: 65536  Basic: 1937 milliseconds  Strassen: 2000 milliseconds
Size: 4  Digits: 26  Iterations: 32768  Basic: 1078 milliseconds  Strassen: 1109 milliseconds
Size: 4  Digits: 27  Iterations: 32768  Basic: 1203 milliseconds  Strassen: 1204 milliseconds
Size: 4  Digits: 28  Iterations: 32768  Basic: 1250 milliseconds  Strassen: 1266 milliseconds
Size: 4  Digits: 29  Iterations: 32768  Basic: 1234 milliseconds  Strassen: 1250 milliseconds
Size: 4  Digits: 30  Iterations: 32768  Basic: 1406 milliseconds  Strassen: 1407 milliseconds
Size: 4  Digits: 31  Iterations: 32768  Basic: 1546 milliseconds  Strassen: 1469 milliseconds
Size: 8  Digits: 1  Iterations: 131072  Basic: 1875 milliseconds  Strassen: 2765 milliseconds
Size: 8  Digits: 2  Iterations: 131072  Basic: 2078 milliseconds  Strassen: 3360 milliseconds
Size: 8  Digits: 3  Iterations: 65536   Basic: 1219 milliseconds  Strassen: 1672 milliseconds
Size: 8  Digits: 4  Iterations: 65536   Basic: 1359 milliseconds  Strassen: 1969 milliseconds
Size: 8  Digits: 5  Iterations: 65536   Basic: 1578 milliseconds  Strassen: 2204 milliseconds
Size: 8  Digits: 6  Iterations: 65536   Basic: 1828 milliseconds  Strassen: 2359 milliseconds
Size: 8  Digits: 7  Iterations: 32768   Basic: 1062 milliseconds  Strassen: 1360 milliseconds
Size: 8  Digits: 8  Iterations: 32768   Basic: 1203 milliseconds  Strassen: 1469 milliseconds
Size: 8  Digits: 9  Iterations: 32768   Basic: 1765 milliseconds  Strassen: 2063 milliseconds
Size: 8  Digits: 10  Iterations: 16384  Basic: 1125 milliseconds  Strassen: 1219 milliseconds
Size: 8  Digits: 11  Iterations: 16384  Basic: 1359 milliseconds  Strassen: 1406 milliseconds
Size: 8  Digits: 12  Iterations: 16384  Basic: 1422 milliseconds  Strassen: 1531 milliseconds
Size: 8  Digits: 13  Iterations: 16384  Basic: 1406 milliseconds  Strassen: 1532 milliseconds
Size: 8  Digits: 14  Iterations: 16384  Basic: 1688 milliseconds  Strassen: 1766 milliseconds
Size: 8  Digits: 15  Iterations: 8192   Basic: 1047 milliseconds  Strassen: 1015 milliseconds
Size: 16  Digits: 1  Iterations: 8192   Basic: 1031 milliseconds  Strassen: 1391 milliseconds
Size: 16  Digits: 2  Iterations: 8192   Basic: 1172 milliseconds  Strassen: 1812 milliseconds
Size: 16  Digits: 3  Iterations: 8192   Basic: 1344 milliseconds  Strassen: 1719 milliseconds
Size: 16  Digits: 4  Iterations: 8192   Basic: 1407 milliseconds  Strassen: 1828 milliseconds
Size: 16  Digits: 5  Iterations: 8192   Basic: 1688 milliseconds  Strassen: 2078 milliseconds
Size: 16  Digits: 6  Iterations: 8192   Basic: 1906 milliseconds  Strassen: 2281 milliseconds
Size: 16  Digits: 7  Iterations: 4096   Basic: 1093 milliseconds  Strassen: 1282 milliseconds
Size: 16  Digits: 8  Iterations: 4096   Basic: 1313 milliseconds  Strassen: 1437 milliseconds
Size: 16  Digits: 9  Iterations: 4096   Basic: 2000 milliseconds  Strassen: 2234 milliseconds
Size: 16  Digits: 10  Iterations: 2048  Basic: 1266 milliseconds  Strassen: 1234 milliseconds
Size: 32  Digits: 1  Iterations: 1024   Basic: 1109 milliseconds  Strassen: 1266 milliseconds
Size: 32  Digits: 2  Iterations: 1024   Basic: 1156 milliseconds  Strassen: 1329 milliseconds
Size: 32  Digits: 3  Iterations: 1024   Basic: 1344 milliseconds  Strassen: 1500 milliseconds
Size: 32  Digits: 4  Iterations: 1024   Basic: 1640 milliseconds  Strassen: 1938 milliseconds
Size: 32  Digits: 5  Iterations: 512    Basic: 1078 milliseconds  Strassen: 1047 milliseconds
Size: 64  Digits: 1  Iterations: 128    Basic: 1297 milliseconds  Strassen: 1359 milliseconds
Size: 64  Digits: 2  Iterations: 128    Basic: 1281 milliseconds  Strassen: 1438 milliseconds
Size: 64  Digits: 3  Iterations: 128    Basic: 1609 milliseconds  Strassen: 1484 milliseconds
Size: 128  Digits: 1  Iterations: 16    Basic: 1281 milliseconds  Strassen: 1235 milliseconds

Size: 2  Digits: 1  Iterations: 8388608 Basic: 1469 milliseconds  Strassen: 9187 milliseconds
Size: 2  Digits: 2  Iterations: 8388608 Basic: 1578 milliseconds  Strassen: 9437 milliseconds
Size: 2  Digits: 3  Iterations: 4194304 Basic: 1187 milliseconds  Strassen: 5266 milliseconds
Size: 2  Digits: 4  Iterations: 4194304 Basic: 1187 milliseconds  Strassen: 5594 milliseconds
Size: 2  Digits: 5  Iterations: 4194304 Basic: 1343 milliseconds  Strassen: 6016 milliseconds
Size: 2  Digits: 6  Iterations: 4194304 Basic: 1563 milliseconds  Strassen: 6125 milliseconds
Size: 2  Digits: 7  Iterations: 2097152 Basic: 1016 milliseconds  Strassen: 4562 milliseconds
Size: 2  Digits: 8  Iterations: 2097152 Basic: 1109 milliseconds  Strassen: 5203 milliseconds
Size: 2  Digits: 9  Iterations: 2097152 Basic: 1625 milliseconds  Strassen: 5281 milliseconds
Size: 2  Digits: 10  Iterations: 2097152        Basic: 1984 milliseconds  Strassen: 5813 milliseconds
Size: 2  Digits: 11  Iterations: 1048576        Basic: 1297 milliseconds  Strassen: 2406 milliseconds
Size: 2  Digits: 12  Iterations: 1048576        Basic: 1313 milliseconds  Strassen: 2500 milliseconds
Size: 2  Digits: 13  Iterations: 1048576        Basic: 1344 milliseconds  Strassen: 2375 milliseconds
Size: 2  Digits: 14  Iterations: 1048576        Basic: 1688 milliseconds  Strassen: 2609 milliseconds
Size: 2  Digits: 15  Iterations: 1048576        Basic: 1844 milliseconds  Strassen: 2843 milliseconds
Size: 2  Digits: 16  Iterations: 524288 Basic: 1015 milliseconds  Strassen: 1516 milliseconds
Size: 2  Digits: 17  Iterations: 1048576        Basic: 1969 milliseconds  Strassen: 3031 milliseconds
Size: 2  Digits: 18  Iterations: 524288 Basic: 1328 milliseconds  Strassen: 1781 milliseconds
Size: 2  Digits: 19  Iterations: 524288 Basic: 1578 milliseconds  Strassen: 2078 milliseconds
Size: 2  Digits: 20  Iterations: 524288 Basic: 1562 milliseconds  Strassen: 2156 milliseconds
Size: 2  Digits: 21  Iterations: 524288 Basic: 1391 milliseconds  Strassen: 1953 milliseconds
Size: 2  Digits: 22  Iterations: 524288 Basic: 1625 milliseconds  Strassen: 2125 milliseconds
Size: 2  Digits: 23  Iterations: 524288 Basic: 1828 milliseconds  Strassen: 2500 milliseconds
Size: 2  Digits: 24  Iterations: 524288 Basic: 1860 milliseconds  Strassen: 2328 milliseconds
Size: 2  Digits: 25  Iterations: 524288 Basic: 1875 milliseconds  Strassen: 2453 milliseconds
Size: 2  Digits: 26  Iterations: 262144 Basic: 1047 milliseconds  Strassen: 1297 milliseconds
Size: 2  Digits: 27  Iterations: 262144 Basic: 1188 milliseconds  Strassen: 1421 milliseconds
Size: 2  Digits: 28  Iterations: 262144 Basic: 1218 milliseconds  Strassen: 1500 milliseconds
Size: 2  Digits: 29  Iterations: 262144 Basic: 1297 milliseconds  Strassen: 1547 milliseconds
Size: 2  Digits: 30  Iterations: 262144 Basic: 1375 milliseconds  Strassen: 1578 milliseconds
Size: 2  Digits: 31  Iterations: 262144 Basic: 1547 milliseconds  Strassen: 1703 milliseconds
Size: 2  Digits: 32  Iterations: 262144 Basic: 1500 milliseconds  Strassen: 1812 milliseconds
Size: 2  Digits: 33  Iterations: 262144 Basic: 1578 milliseconds  Strassen: 1844 milliseconds
Size: 2  Digits: 34  Iterations: 262144 Basic: 1735 milliseconds  Strassen: 1921 milliseconds
Size: 2  Digits: 35  Iterations: 262144 Basic: 1907 milliseconds  Strassen: 2031 milliseconds
Size: 2  Digits: 36  Iterations: 262144 Basic: 1937 milliseconds  Strassen: 2078 milliseconds
Size: 2  Digits: 37  Iterations: 131072 Basic: 1031 milliseconds  Strassen: 1157 milliseconds
Size: 2  Digits: 38  Iterations: 131072 Basic: 1172 milliseconds  Strassen: 1187 milliseconds
Size: 2  Digits: 39  Iterations: 131072 Basic: 1156 milliseconds  Strassen: 1172 milliseconds
Size: 2  Digits: 40  Iterations: 131072 Basic: 1171 milliseconds  Strassen: 1219 milliseconds
Size: 2  Digits: 41  Iterations: 131072 Basic: 1296 milliseconds  Strassen: 1344 milliseconds
Size: 2  Digits: 42  Iterations: 131072 Basic: 1235 milliseconds  Strassen: 1312 milliseconds
Size: 2  Digits: 43  Iterations: 131072 Basic: 1344 milliseconds  Strassen: 1421 milliseconds
Size: 2  Digits: 44  Iterations: 131072 Basic: 1469 milliseconds  Strassen: 1453 milliseconds
Size: 4  Digits: 1  Iterations: 1048576 Basic: 1688 milliseconds  Strassen: 4375 milliseconds
Size: 4  Digits: 2  Iterations: 1048576 Basic: 1828 milliseconds  Strassen: 4562 milliseconds
Size: 4  Digits: 3  Iterations: 524288  Basic: 1047 milliseconds  Strassen: 2391 milliseconds
Size: 4  Digits: 4  Iterations: 524288  Basic: 1172 milliseconds  Strassen: 2578 milliseconds
Size: 4  Digits: 5  Iterations: 524288  Basic: 1422 milliseconds  Strassen: 3015 milliseconds
Size: 4  Digits: 6  Iterations: 524288  Basic: 1719 milliseconds  Strassen: 3734 milliseconds
Size: 4  Digits: 7  Iterations: 262144  Basic: 1062 milliseconds  Strassen: 1719 milliseconds
Size: 4  Digits: 8  Iterations: 262144  Basic: 1110 milliseconds  Strassen: 1859 milliseconds
Size: 4  Digits: 9  Iterations: 262144  Basic: 1719 milliseconds  Strassen: 2421 milliseconds
Size: 4  Digits: 10  Iterations: 131072 Basic: 1094 milliseconds  Strassen: 1422 milliseconds
Size: 4  Digits: 11  Iterations: 131072 Basic: 1218 milliseconds  Strassen: 1610 milliseconds
Size: 4  Digits: 12  Iterations: 131072 Basic: 1344 milliseconds  Strassen: 1719 milliseconds
Size: 4  Digits: 13  Iterations: 131072 Basic: 1453 milliseconds  Strassen: 1766 milliseconds
Size: 4  Digits: 14  Iterations: 131072 Basic: 1641 milliseconds  Strassen: 1953 milliseconds
Size: 4  Digits: 15  Iterations: 131072 Basic: 1922 milliseconds  Strassen: 2188 milliseconds
Size: 4  Digits: 16  Iterations: 65536  Basic: 1047 milliseconds  Strassen: 1156 milliseconds
Size: 4  Digits: 17  Iterations: 65536  Basic: 1047 milliseconds  Strassen: 1218 milliseconds
Size: 4  Digits: 18  Iterations: 65536  Basic: 1250 milliseconds  Strassen: 1484 milliseconds
Size: 4  Digits: 19  Iterations: 65536  Basic: 1453 milliseconds  Strassen: 1672 milliseconds
Size: 4  Digits: 20  Iterations: 65536  Basic: 1484 milliseconds  Strassen: 1641 milliseconds
Size: 4  Digits: 21  Iterations: 65536  Basic: 1531 milliseconds  Strassen: 2031 milliseconds
Size: 4  Digits: 22  Iterations: 65536  Basic: 2094 milliseconds  Strassen: 2109 milliseconds
Size: 4  Digits: 23  Iterations: 32768  Basic: 1031 milliseconds  Strassen: 984 milliseconds
Size: 8  Digits: 1  Iterations: 131072  Basic: 2047 milliseconds  Strassen: 3219 milliseconds
Size: 8  Digits: 2  Iterations: 65536   Basic: 1078 milliseconds  Strassen: 1547 milliseconds
Size: 8  Digits: 3  Iterations: 65536   Basic: 1250 milliseconds  Strassen: 1750 milliseconds
Size: 8  Digits: 4  Iterations: 65536   Basic: 1359 milliseconds  Strassen: 1828 milliseconds
Size: 8  Digits: 5  Iterations: 65536   Basic: 1547 milliseconds  Strassen: 2203 milliseconds
Size: 8  Digits: 6  Iterations: 65536   Basic: 1859 milliseconds  Strassen: 2391 milliseconds
Size: 8  Digits: 7  Iterations: 32768   Basic: 1109 milliseconds  Strassen: 1391 milliseconds
Size: 8  Digits: 8  Iterations: 32768   Basic: 1234 milliseconds  Strassen: 1579 milliseconds
Size: 8  Digits: 9  Iterations: 16384   Basic: 1156 milliseconds  Strassen: 1281 milliseconds
Size: 8  Digits: 10  Iterations: 16384  Basic: 1218 milliseconds  Strassen: 1360 milliseconds
Size: 8  Digits: 11  Iterations: 16384  Basic: 1406 milliseconds  Strassen: 1672 milliseconds
Size: 8  Digits: 12  Iterations: 16384  Basic: 1531 milliseconds  Strassen: 1734 milliseconds
Size: 8  Digits: 13  Iterations: 16384  Basic: 1594 milliseconds  Strassen: 1766 milliseconds
Size: 8  Digits: 14  Iterations: 16384  Basic: 1797 milliseconds  Strassen: 1906 milliseconds
Size: 8  Digits: 15  Iterations: 8192   Basic: 1172 milliseconds  Strassen: 1047 milliseconds
Size: 16  Digits: 1  Iterations: 8192   Basic: 1047 milliseconds  Strassen: 1469 milliseconds
Size: 16  Digits: 2  Iterations: 8192   Basic: 1110 milliseconds  Strassen: 1500 milliseconds
Size: 16  Digits: 3  Iterations: 8192   Basic: 1282 milliseconds  Strassen: 1687 milliseconds
Size: 16  Digits: 4  Iterations: 8192   Basic: 1469 milliseconds  Strassen: 1813 milliseconds
Size: 16  Digits: 5  Iterations: 8192   Basic: 1688 milliseconds  Strassen: 2062 milliseconds
Size: 16  Digits: 6  Iterations: 8192   Basic: 1906 milliseconds  Strassen: 2359 milliseconds
Size: 16  Digits: 7  Iterations: 4096   Basic: 1109 milliseconds  Strassen: 1281 milliseconds
Size: 16  Digits: 8  Iterations: 4096   Basic: 1250 milliseconds  Strassen: 1422 milliseconds
Size: 16  Digits: 9  Iterations: 4096   Basic: 1875 milliseconds  Strassen: 2032 milliseconds
Size: 16  Digits: 10  Iterations: 2048  Basic: 1281 milliseconds  Strassen: 1234 milliseconds
Size: 32  Digits: 1  Iterations: 1024   Basic: 1094 milliseconds  Strassen: 1313 milliseconds
Size: 32  Digits: 2  Iterations: 1024   Basic: 1156 milliseconds  Strassen: 1485 milliseconds
Size: 32  Digits: 3  Iterations: 1024   Basic: 1406 milliseconds  Strassen: 1609 milliseconds
Size: 32  Digits: 4  Iterations: 1024   Basic: 1516 milliseconds  Strassen: 1688 milliseconds
Size: 32  Digits: 5  Iterations: 1024   Basic: 1735 milliseconds  Strassen: 1968 milliseconds
Size: 32  Digits: 6  Iterations: 1024   Basic: 1953 milliseconds  Strassen: 2109 milliseconds
Size: 32  Digits: 7  Iterations: 512    Basic: 1140 milliseconds  Strassen: 1188 milliseconds
Size: 32  Digits: 8  Iterations: 512    Basic: 1266 milliseconds  Strassen: 1343 milliseconds
Size: 32  Digits: 9  Iterations: 512    Basic: 1906 milliseconds  Strassen: 1938 milliseconds
Size: 32  Digits: 10  Iterations: 256   Basic: 1219 milliseconds  Strassen: 1156 milliseconds
Size: 64  Digits: 1  Iterations: 128    Basic: 1156 milliseconds  Strassen: 1187 milliseconds
Size: 64  Digits: 2  Iterations: 128    Basic: 1250 milliseconds  Strassen: 1266 milliseconds
Size: 64  Digits: 3  Iterations: 128    Basic: 1500 milliseconds  Strassen: 1406 milliseconds
Size: 128  Digits: 1  Iterations: 16    Basic: 1266 milliseconds  Strassen: 1234 milliseconds

16-bit changeovers:
Size: 2  Digits: 37  Iterations: 131072 Basic: 1485 milliseconds  Strassen: 1484 milliseconds
Size: 2  Digits: 37  Iterations: 131072 Basic: 1547 milliseconds  Strassen: 1500 milliseconds
Size: 4  Digits: 21  Iterations: 32768  Basic: 1250 milliseconds  Strassen: 1203 milliseconds
Size: 4  Digits: 22  Iterations: 32768  Basic: 1188 milliseconds  Strassen: 1172 milliseconds
Size: 8  Digits: 15  Iterations: 8192   Basic: 1453 milliseconds  Strassen: 1391 milliseconds
Size: 8  Digits: 11  Iterations: 16384  Basic: 1750 milliseconds  Strassen: 1703 milliseconds
Size: 16  Digits: 10  Iterations: 2048  Basic: 1391 milliseconds  Strassen: 1343 milliseconds
Size: 16  Digits: 10  Iterations: 2048  Basic: 1531 milliseconds  Strassen: 1516 milliseconds
Size: 32  Digits: 5  Iterations: 512    Basic: 1125 milliseconds  Strassen: 1047 milliseconds
Size: 32  Digits: 5  Iterations: 512    Basic: 1078 milliseconds  Strassen: 1078 milliseconds
Size: 64  Digits: 2  Iterations: 128    Basic: 1468 milliseconds  Strassen: 1453 milliseconds
Size: 64  Digits: 3  Iterations: 128    Basic: 1657 milliseconds  Strassen: 1625 milliseconds
Size: 128  Digits: 1  Iterations: 16    Basic: 1609 milliseconds  Strassen: 1547 milliseconds
Size: 128  Digits: 1  Iterations: 16    Basic: 1500 milliseconds  Strassen: 1375 milliseconds

32-bit changeovers:
Size: 2  Digits: 35  Iterations: 131072 Basic: 1235 milliseconds  Strassen: 1218 milliseconds
Size: 2  Digits: 44  Iterations: 131072 Basic: 1469 milliseconds  Strassen: 1453 milliseconds
Size: 4  Digits: 31  Iterations: 32768  Basic: 1546 milliseconds  Strassen: 1469 milliseconds
Size: 4  Digits: 23  Iterations: 32768  Basic: 1031 milliseconds  Strassen: 984 milliseconds
Size: 8  Digits: 15  Iterations: 8192   Basic: 1047 milliseconds  Strassen: 1015 milliseconds
Size: 8  Digits: 15  Iterations: 8192   Basic: 1172 milliseconds  Strassen: 1047 milliseconds
Size: 16  Digits: 10  Iterations: 2048  Basic: 1266 milliseconds  Strassen: 1234 milliseconds
Size: 16  Digits: 10  Iterations: 2048  Basic: 1281 milliseconds  Strassen: 1234 milliseconds
Size: 32  Digits: 5  Iterations: 512    Basic: 1078 milliseconds  Strassen: 1047 milliseconds
Size: 32  Digits: 10  Iterations: 256   Basic: 1219 milliseconds  Strassen: 1156 milliseconds
Size: 64  Digits: 3  Iterations: 128    Basic: 1609 milliseconds  Strassen: 1484 milliseconds
Size: 64  Digits: 3  Iterations: 128    Basic: 1500 milliseconds  Strassen: 1406 milliseconds
Size: 128  Digits: 1  Iterations: 16    Basic: 1281 milliseconds  Strassen: 1235 milliseconds
Size: 128  Digits: 1  Iterations: 16    Basic: 1500 milliseconds  Strassen: 1375 milliseconds
*/
void CArithmeticTuner::FindBestStrassenThreshold()
{
	CArithmeticBox     cBox;
	unsigned int       nTimeBasic, nTimeStrassen;
	CBigIntegerForTest nBigInt;
	size_t             nDigits;
	size_t             nSize = 2;
	// For each matrix size 2, 4, 8, 16, etc. find smallest DIGIT size for which matrix multiplication using Strassen for the
	// first step and basic below that is faster than using basic throughout.  Quite when we reach the point where Strassen is
	// faster for single-DIGIT values in the matrices.
	ResetThresholdsForOptimization();
	do
	{
		CBigIntegerMatrix nMat1(nSize), nMat2(nSize), nProduct(nSize);
		nDigits = 1;
		do
		{
			int nIterations = 1;
			// initialize the matrices to multiply with suitably-sized values
			for (int i=0; i<nSize; i++)
			{
				for(int j=0; j<nSize; j++)
				{
					nBigInt.SetRandom(nDigits*c_nDigitSize);
					nBigInt.SetNegative(rand()%2);
					nBigInt.Copy(nMat1[i][j]);
					nBigInt.SetRandom(nDigits*c_nDigitSize);
					nBigInt.SetNegative(rand()%2);
					nBigInt.Copy(nMat2[i][j]);
				}
			}
			// first, using basic
			CBigIntegerMatrix::SetStrassenThreshold(nSize+1);
			do
			{
				nTimeBasic = ::GetTickCount();
				for (int i=0; i<nIterations; i++)
				{
					CBigIntegerMatrix::Multiply(nMat1, nMat2, nProduct, 0, 0, nSize, nSize, 0, 0, nSize, 0, 0, cBox);
				}
				nTimeBasic = ::GetTickCount() - nTimeBasic;
				if(1000<nTimeBasic) break;
				nIterations *= 2;
			}
			while(true);
			// next, Strassen
			CBigIntegerMatrix::SetStrassenThreshold(nSize);
			nTimeStrassen = ::GetTickCount();
			for (int i=0; i<nIterations; i++)
			{
				CBigIntegerMatrix::Multiply(nMat1, nMat2, nProduct, 0, 0, nSize, nSize, 0, 0, nSize, 0, 0, cBox);
			}
			nTimeStrassen = ::GetTickCount() - nTimeStrassen;
			printf("Size: %u  Digits: %u  Iterations: %u\tBasic: %u milliseconds  Strassen: %u milliseconds\n",nSize,nDigits,nIterations,nTimeBasic,nTimeStrassen);
			if (nTimeStrassen <= nTimeBasic) break;
			nDigits++;
		}
		while(true);
		nSize *= 2;
	}
	while(1 != nDigits);
}
#endif