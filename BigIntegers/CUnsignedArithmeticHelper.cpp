#include "CUnsignedArithmeticHelper.h"
#include "..\BigIntegersBase\CBigIntegerHelper.h"
#include "Macros.h"
#include "math.h"
#include "SSystemData.h"
#include "AVXMultiply.h"

#pragma warning(disable:4018)    // signed/unsigned mismatch
#pragma warning(disable:4146)    // unary operator applied to signed type
CHighPerfTimer CUnsignedArithmeticHelper::s_Timer;
#if _DEBUG
bool CUnsignedArithmeticHelper::s_bForceBigAddForValidatingNthRoot = false;
#endif
// global declarations
SSystemDataNode *g_pInversionStructures = NULL;
// class variable definitions/initializations
#ifndef _UsingVariableThresholdsForTest
#if(32==_DIGIT_SIZE_IN_BITS)
#if _USEAVX
const unsigned int CUnsignedArithmeticHelper::c_nBuildBlockSizePre                                   = 8192;
const unsigned int CUnsignedArithmeticHelper::c_nBuildBlockSizePost                                  = 32768; // ignored
const unsigned int CUnsignedArithmeticHelper::c_pnMultiplicationThresholds[eNumMultiplyAlgorithms-1] = { 130, 149, 154, 250, 54494, 0 };
const unsigned int CUnsignedArithmeticHelper::c_pnSquareThresholds[eNumMultiplyAlgorithms-1]         = { 53, 211, 217, 337, 14963, 0 };
const unsigned int CUnsignedArithmeticHelper::c_pn2NByNBreakpoints[c_n2NBynSizeBreakpoints]          = { 12093, 12093, 16387, 16387, 230200, 7270576, 7270576 }; // Not really important to get right -- in practice, 2nbyn is never used
const unsigned int CUnsignedArithmeticHelper::c_pn2NByNSquareBreakpoints[c_n2NBynSizeBreakpoints]    = { 16156, 89155, 582464, 582464, 957196, 957196, 8727776 }; // Not really important to get right -- in practice, 2nbyn is never used
const unsigned int CUnsignedArithmeticHelper::c_nDivideThresholdSmall                                = 11;       // at least 4 to insure correctness
const unsigned int CUnsignedArithmeticHelper::c_nDivideThresholdDiff                                 = 4;        // at least 4 to insure correctness
const unsigned int CUnsignedArithmeticHelper::c_nSquareRootThreshold                                 = 3;        // 3 is the minimum for correctness -- and also seems to be the best
#else
const unsigned int CUnsignedArithmeticHelper::c_nBuildBlockSizePre                                   = 16384;         // or whatever is found to be best in testing thresholds -- this is good
const unsigned int CUnsignedArithmeticHelper::c_nBuildBlockSizePost                                  = 65536;         // or whatever is found to be best in testing thresholds -- this is good
// note that the ABSOLUTE MINIMUM for c_pnMultiplicationThresholds[e2NByN] is 2*(2*nPieces-3)*sizeof(size_t)/sizeof(DIGIT) -- that much space is assumed to be present in Z to hold arguments!
const unsigned int CUnsignedArithmeticHelper::c_pnMultiplicationThresholds[eNumMultiplyAlgorithms-1] = { 54, 100, 100, 160, 40789, 0 };     // or whatever values the test deems Worthy
const unsigned int CUnsignedArithmeticHelper::c_pnSquareThresholds[eNumMultiplyAlgorithms-1]         = { 26, 186, 186, 190, 11573, 0 };     // or whatever values the test deems Worthy
// note that the ABSOLUTE MINIMUM for c_pn2NByNBreakpoints[nPieces-5] is 2*(2*nPieces-3)*sizeof(size_t)/sizeof(DIGIT) -- that much space is assumed to be present in Z to hold arguments!
const unsigned int CUnsignedArithmeticHelper::c_pn2NByNBreakpoints[c_n2NBynSizeBreakpoints]          = { 160, 644, 3499, 3500, 13545, 13546, 19471 }; // Not really important to get right -- in practice, 2nbyn is never used
const unsigned int CUnsignedArithmeticHelper::c_pn2NByNSquareBreakpoints[c_n2NBynSizeBreakpoints]    = { 356, 2333, 17964, 23264, 28659, 28660, 28661 }; // Not really important to get right -- in practice, 2nbyn is never used
const unsigned int CUnsignedArithmeticHelper::c_nDivideThresholdSmall                                = 16;       // at least 4 to insure correctness
const unsigned int CUnsignedArithmeticHelper::c_nDivideThresholdDiff                                 =  4;       // at least 4 to insure correctness
const unsigned int CUnsignedArithmeticHelper::c_nSquareRootThreshold                                 =  3;       // 3 is the minimum for correctness -- and also seems to be the best
#endif
#elif(16==_DIGIT_SIZE_IN_BITS)
const unsigned int CUnsignedArithmeticHelper::c_nBuildBlockSizePre                                   = 8192;         // or whatever is found to be best in testing thresholds -- this is good
const unsigned int CUnsignedArithmeticHelper::c_nBuildBlockSizePost                                  = 32768;         // or whatever is found to be best in testing thresholds -- this is good
// note that the ABSOLUTE MINIMUM for c_pnMultiplicationThresholds[e2NByN] is 2*(2*nPieces-3)*sizeof(size_t)/sizeof(DIGIT) -- that much space is assumed to be present in Z to hold arguments!
const unsigned int CUnsignedArithmeticHelper::c_pnMultiplicationThresholds[eNumMultiplyAlgorithms-1] = { 52, 152, 152, 39211, 0 };     // or whatever values the test deems Worthy
const unsigned int CUnsignedArithmeticHelper::c_pnSquareThresholds[eNumMultiplyAlgorithms-1]         = { 34, 154, 154, 18956, 0 };     // or whatever values the test deems Worthy
const unsigned int CUnsignedArithmeticHelper::c_pn2NByNSquareBreakpoints[c_n2NBynSizeBreakpoints]    = { 9947, 12563, 12597, 44304, 89971, 275688, 2000000000 }; // Not really important to get right -- in practice, 2nbyn is never used
// note that the ABSOLUTE MINIMUM for c_pn2NByNBreakpoints[nPieces-5] is 2*(2*nPieces-3)*sizeof(size_t)/sizeof(DIGIT) -- that much space is assumed to be present in Z to hold arguments!
const unsigned int CUnsignedArithmeticHelper::c_pn2NByNBreakpoints[c_n2NBynSizeBreakpoints]          = { 101233, 182042, 201275, 231567, 1692095, 2254277, 33154301 }; // Not really important to get right -- in practice, 2nbyn is never used
const unsigned int CUnsignedArithmeticHelper::c_nDivideThresholdSmall                                = 7;       // at least 4 to insure correctness; 22 is heuristically good
const unsigned int CUnsignedArithmeticHelper::c_nDivideThresholdDiff                                 = 4;       // at least 4 to insure correctness; 22 is heuristically good
const unsigned int CUnsignedArithmeticHelper::c_nSquareRootThreshold                                 = 3;       // 3 is the minimum for correctness -- and also seems to be the best
#endif
#else
#if(16==_DIGIT_SIZE_IN_BITS)
unsigned int CUnsignedArithmeticHelper::c_nBuildBlockSizePre                                   = 16384;         // or whatever is found to be best in testing thresholds -- this is good
unsigned int CUnsignedArithmeticHelper::c_nBuildBlockSizePost                                  = 65536;         // or whatever is found to be best in testing thresholds -- this is good
// note that the ABSOLUTE MINIMUM for c_pnMultiplicationThresholds[e2NByN] is 2*(2*nPieces-3)*sizeof(size_t)/sizeof(DIGIT) -- that much space is assumed to be present in Z to hold arguments!
unsigned int CUnsignedArithmeticHelper::c_pnMultiplicationThresholds[eNumMultiplyAlgorithms-1] = { 52, 152, 152, 39211, 0 };     // or whatever values the test deems Worthy
unsigned int CUnsignedArithmeticHelper::c_pnSquareThresholds[eNumMultiplyAlgorithms-1]         = { 34, 154, 154, 18956, 0 };     // or whatever values the test deems Worthy
// note that the ABSOLUTE MINIMUM for c_pn2NByNBreakpoints[nPieces-5] is 2*(2*nPieces-3)*sizeof(size_t)/sizeof(DIGIT) -- that much space is assumed to be present in Z to hold arguments!
unsigned int CUnsignedArithmeticHelper::c_pn2NByNBreakpoints[c_n2NBynSizeBreakpoints]          = { 101233, 182042, 201275, 231567, 1692095, 2254277, 33154301 }; // Not really important to get right -- in practice, 2nbyn is never used
unsigned int CUnsignedArithmeticHelper::c_pn2NByNSquareBreakpoints[c_n2NBynSizeBreakpoints]    = { 9947, 12563, 12597, 44304, 89971, 275688, 2000000000 }; // Not really important to get right -- in practice, 2nbyn is never used
unsigned int CUnsignedArithmeticHelper::c_nDivideThresholdSmall                                = 7;        // at least 4 to insure correctness; 6 or 7 is heuristically good
unsigned int CUnsignedArithmeticHelper::c_nDivideThresholdDiff                                 = 4;        // at least 4 to insure correctness; 4 is heuristically good
unsigned int CUnsignedArithmeticHelper::c_nSquareRootThreshold                                 = 3;        // 3 is the minimum for correctness -- and also seems to be the best
#elif(32==_DIGIT_SIZE_IN_BITS)
#if _USEAVX
unsigned int CUnsignedArithmeticHelper::c_nBuildBlockSizePre                                   = 8192;
unsigned int CUnsignedArithmeticHelper::c_nBuildBlockSizePost                                  = 32768; // ignored
unsigned int CUnsignedArithmeticHelper::c_pnMultiplicationThresholds[eNumMultiplyAlgorithms-1] = { 130, 149, 154, 250, 54494, 0 };
unsigned int CUnsignedArithmeticHelper::c_pnSquareThresholds[eNumMultiplyAlgorithms-1]         = { 53, 211, 217, 337, 14963, 0 };
unsigned int CUnsignedArithmeticHelper::c_pn2NByNBreakpoints[c_n2NBynSizeBreakpoints]          = { 967257, 1338767, 1338767, 1338767, 1404417, 1404417, 1577792 }; // Not really important to get right -- in practice, 2nbyn is never used
unsigned int CUnsignedArithmeticHelper::c_pn2NByNSquareBreakpoints[c_n2NBynSizeBreakpoints]    = { 16156, 89155, 582464, 582464, 957196, 957196, 8727776 }; // Not really important to get right -- in practice, 2nbyn is never used
unsigned int CUnsignedArithmeticHelper::c_nDivideThresholdSmall                                = 11;       // at least 4 to insure correctness; 6 is heuristically good
unsigned int CUnsignedArithmeticHelper::c_nDivideThresholdDiff                                 = 4;        // at least 4 to insure correctness; 4 is heuristically good
unsigned int CUnsignedArithmeticHelper::c_nSquareRootThreshold                                 = 3;        // 3 is the minimum for correctness -- and also seems to be the best
#else
unsigned int CUnsignedArithmeticHelper::c_nBuildBlockSizePre                                   = 8192;
unsigned int CUnsignedArithmeticHelper::c_nBuildBlockSizePost                                  = 32768; // ignored
unsigned int CUnsignedArithmeticHelper::c_pnMultiplicationThresholds[eNumMultiplyAlgorithms-1] = { 54, 100, 100, 160, 40789, 0 };
unsigned int CUnsignedArithmeticHelper::c_pnSquareThresholds[eNumMultiplyAlgorithms-1]         = { 26, 186, 186, 190, 11573, 0 };
unsigned int CUnsignedArithmeticHelper::c_pn2NByNBreakpoints[c_n2NBynSizeBreakpoints]          = { 160, 644, 3499, 3500, 13545, 13546, 19471 }; // Not really important to get right -- in practice, 2nbyn is never used
unsigned int CUnsignedArithmeticHelper::c_pn2NByNSquareBreakpoints[c_n2NBynSizeBreakpoints]    = { 356, 2333, 17964, 23264, 28659, 28660, 28661 }; // Not really important to get right -- in practice, 2nbyn is never used
unsigned int CUnsignedArithmeticHelper::c_nDivideThresholdSmall                                = 12;       // at least 4 to insure correctness; 6 is heuristically good
unsigned int CUnsignedArithmeticHelper::c_nDivideThresholdDiff                                 = 4;        // at least 4 to insure correctness; 4 is heuristically good
unsigned int CUnsignedArithmeticHelper::c_nSquareRootThreshold                                 = 3;        // 3 is the minimum for correctness -- and also seems to be the best
#endif
#endif
#endif
// note that these values are not used unless the compile flag _CollectDetailedTimingData is set
unsigned long long g_nDivideTime[eNumDivideComponents]             = {0, 0, 0, 0, 0};
unsigned long long g_nSquareRootTime[eNumSquareRootComponents]     = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned long long g_nPowerModulusTime[eNumPowerModulusComponents] = {0, 0, 0, 0, 0};
unsigned long long g_nGCDTime[eNumGCDComponents]                   = {0, 0, 0, 0, 0};
#if(32<=_DIGIT_SIZE_IN_BITS)
unsigned long long g_nBuildTimes[eNumMultiplyAlgorithms]           = {0, 0, 0, 0, 0, 0, 0};
unsigned long long g_nProcessTimes[eNumMultiplyAlgorithms+1]       = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned long      g_nMultiplyCalls[eNumMultiplyAlgorithms+1]      = {0, 0, 0, 0, 0, 0, 0, 0};
#else
unsigned long long g_nBuildTimes[eNumMultiplyAlgorithms]           = {0, 0, 0, 0, 0, 0};
unsigned long long g_nProcessTimes[eNumMultiplyAlgorithms+1]       = {0, 0, 0, 0, 0, 0, 0};
unsigned long      g_nMultiplyCalls[eNumMultiplyAlgorithms+1]      = {0, 0, 0, 0, 0, 0, 0};
#endif

const char *c_szMultiplyFunctionNames[eNumMultiplyAlgorithms] = { "Basic multiply",
                                                                  "3 by 2 multiply",
                                                                  "5 by 3 multiply",
                                                                  "7 by 4 multiply",
#if(32<=_DIGIT_SIZE_IN_BITS)
                                                                  "9 by 5 multiply",
#endif
                                                                  "2n by n multiply",
                                                                  "FFT multiply" };

//enum EDivideComponents { eTotalDivideCalls, eDivideProcessTime, eDivideMultCallsTime, eBasicDivideTime, eTotalDivideTime, eNumDivideComponents };
const char *c_szDivideComponentNames[eNumDivideComponents] = {"Total calls to divide:",
                                                              "Time in recursive divide:",
                                                              "Time in multiplication:  ",
                                                              "Time in basic divide:    ",
                                                              "Total divide time:       " };

const char *c_szSquareRootComponentNames[eNumSquareRootComponents] = {"Total calls to square root:",
                                                                      "Time spent in master function overhead:              ",
                                                                      "Time spent in master function multiplying:           ",
                                                                      "Time spent in Newton function overhead:              ",
                                                                      "Time spent in Newton function multiplying:           ",
                                                                      "Time spent in Newton function dividing:              ",
                                                                      "Time spent in general square root part A overhead:   ",
                                                                      "Time spent in general square root part A multiplying:",
                                                                      "Time spent in general square root part B overhead:   ",
                                                                      "Time spent in general square root part B multiplying:",
                                                                      "Time spent in general square root part B dividing:   ",
                                                                      "Total time spent computing square roots:             "};

const char *c_szPowerModulusComponentNames[eNumPowerModulusComponents] = { "Total calls to power modulus: ",
                                                                           "Time spent in Power Modulus overhead:    ",
                                                                           "Time spent in Power Modulus multiplying: ",
                                                                           "Time spent in Power Modulus dividing:    ",
                                                                           "Total time spent computing Power Modulus:" };

const char *c_szGCDCompoinentNames[eNumGCDComponents] = {"Total calls to GCD:",
                                                         "Time spent in GCD overhead:    ",
                                                         "Time spent in GCD multiplying: ",
                                                         "Time spent in GCD dividing:    ",
                                                         "Total time spent computing GCD:" };

const unsigned int c_nNumMeasuredValuesByComponent[eNumMeasuredComponents] = { 0, eNumDivideComponents, eNumSquareRootComponents, eNumPowerModulusComponents, eNumGCDComponents };

const char **c_szMeasuredComponentNames[eNumMeasuredComponents] = { NULL, c_szDivideComponentNames, c_szSquareRootComponentNames, c_szPowerModulusComponentNames, c_szGCDCompoinentNames };

unsigned long long *c_nMeasuredValues[eNumMeasuredComponents] = { NULL, g_nDivideTime, g_nSquareRootTime, g_nPowerModulusTime, g_nGCDTime };
const char *CUnsignedArithmeticHelper::GetMultiplicationAlgorithmName(EMultiplyAlgorithm eMultAlg)
{
    return c_szMultiplyFunctionNames[eMultAlg];
}

void CUnsignedArithmeticHelper::ReportMeasuredComponentTimingData(ETimeMeasuredComponents eComponent)
{
#if _CollectDetailedTimingData
    if (eMultiplicationMeasured == eComponent)
    {
        printf("%i calls to multiply\n", g_nMultiplyCalls[eNumMultiplyAlgorithms]);
        printf("  %I64u calls to %s:\n", g_nMultiplyCalls[0], c_szMultiplyFunctionNames[0]);
        printf("    Basic multiply time:        %I64u microseconds (%f average)\n", g_nProcessTimes[0], g_nProcessTimes[0]/((float) g_nMultiplyCalls[0]));
        for (int i=1; i<eNumMultiplyAlgorithms; i++)
        {
            if (0 != g_nMultiplyCalls[i])
            {
                printf("  %I64u calls to %s:\n", g_nMultiplyCalls[i], c_szMultiplyFunctionNames[i]);
                printf("    Construct subproblems time: %I64u microseconds (%f average)\n", g_nBuildTimes[i], g_nBuildTimes[i]/((float) g_nMultiplyCalls[i]));
                printf("    Combine subproblems time:   %I64u microseconds (%f average)\n", g_nProcessTimes[i], g_nProcessTimes[i]/((float) g_nMultiplyCalls[i]));
            }
        }
        printf("Total multiply time: %I64u microseconds (%f average)\n", g_nProcessTimes[eNumMultiplyAlgorithms], g_nProcessTimes[eNumMultiplyAlgorithms]/((float) g_nMultiplyCalls[eNumMultiplyAlgorithms]));
    }
    else
    {
        printf("%s %i\n", c_szMeasuredComponentNames[eComponent][0], c_nMeasuredValues[eComponent][0]);
        for (int i=1; i<c_nNumMeasuredValuesByComponent[eComponent]; i++)
        {
            printf("  %s %I64u microseconds (%f average)\n", c_szMeasuredComponentNames[eComponent][i], c_nMeasuredValues[eComponent][i], c_nMeasuredValues[eComponent][i] / ((float)c_nMeasuredValues[eComponent][0]));
        }
    }
    printf("\n");
#endif
}
// timing functions: used for testing
void CUnsignedArithmeticHelper::ReportAllTimingData()
{
    for(int i=0; i<eNumMeasuredComponents; i++)
    {
        ReportMeasuredComponentTimingData((ETimeMeasuredComponents) i);
    }
}

void CUnsignedArithmeticHelper::ResetTimingData()
{
    for(int i=0; i<eNumMultiplyAlgorithms; i++)
    {
        g_nBuildTimes[i]    = 0;
        g_nProcessTimes[i]  = 0;
        g_nMultiplyCalls[i] = 0;
    }
    g_nProcessTimes[eNumMultiplyAlgorithms]  = 0;
    g_nMultiplyCalls[eNumMultiplyAlgorithms] = 0;
    for(int i=0; i<eNumMeasuredComponents; i++)
    {
        if(eMultiplicationMeasured != i)
        {
            for(int j=0; j<c_nNumMeasuredValuesByComponent[i]; j++)
            {
                c_nMeasuredValues[i][j] = 0;
            }
        }
    }
}

unsigned long long CUnsignedArithmeticHelper::GetChunkProcessTime(bool bPre)
{
    if (bPre)
    {
        return g_nBuildTimes[e2NByN];
    }
    else
    {
        return g_nProcessTimes[e2NByN];
    }
}

size_t CUnsignedArithmeticHelper::Add(size_t      nXSize,
                                      size_t      nYSize,
                                      const DIGIT *pX,
                                      const DIGIT *pY,
                                      DIGIT       *pXPlusY)
{
    DOUBLEDIGIT	 nSum, nCarry=0;
    size_t       i, nSmallSize, nLargeSize;
    const DIGIT  *pSmall, *pLarge;

    if(nXSize<nYSize)
    {
        nSmallSize = nXSize;
        nLargeSize = nYSize;
        pSmall     = pX;
        pLarge     = pY;
    }
    else
    {
        nLargeSize = nXSize;
        nSmallSize = nYSize;
        pLarge     = pX;
        pSmall     = pY;
    }
    for(i=0;i<nSmallSize;i++)
    {
        nSum       = (nCarry + pSmall[i]) + pLarge[i];
        nCarry     = nSum>>_DIGIT_SIZE_IN_BITS;
        pXPlusY[i] = (DIGIT) nSum;
    }
    for(;i<nLargeSize;i++)
    {
        nSum       = nCarry + pLarge[i];
        nCarry     = nSum>>_DIGIT_SIZE_IN_BITS;
        pXPlusY[i] = (DIGIT) nSum;
    }
    pXPlusY[i] = (DIGIT) nCarry;
    return (0<nCarry) ? nLargeSize+1 : nLargeSize;
}

void CUnsignedArithmeticHelper::AddXToYInPlace(size_t      nXSize,
                                               size_t      &nYSize,
                                               const DIGIT *pX,
                                               DIGIT       *pY)
{
    DOUBLEDIGIT	 nSum, nCarry = 0;
    size_t       i;

    for(i=0; i<nXSize; i++)
    {
        nSum   = (nCarry + pX[i]) + pY[i];
        nCarry = nSum>>_DIGIT_SIZE_IN_BITS;
        pY[i]  = (DIGIT) nSum;
    }
    while(nCarry)
    {
        nSum    = nCarry + pY[i];
        nCarry  = nSum>>_DIGIT_SIZE_IN_BITS;
        pY[i++] = (DIGIT) nSum;
    }
    if(nYSize<i) nYSize = i;
    if(0==pY[nYSize-1]) nYSize--;
}

size_t CUnsignedArithmeticHelper::Subtract(size_t      nXSize,
                                           size_t      nYSize,
                                           const DIGIT *pX,
                                           const DIGIT *pY,
                                           DIGIT       *pXMinusY)
{
    DOUBLEDIGIT nDiff, nBorrow=0;
    size_t      i;
    for(i=0;i<nYSize;i++)
    {
        nDiff       = pY[i]+nBorrow;
        nBorrow    	= (DOUBLEDIGIT) (pX[i] < nDiff);
        pXMinusY[i] = pX[i] - (DIGIT) nDiff;
    }
    // note by assumption Y<X, so needn't check size
    if(0 != nBorrow)
    {
        do
        {
            nDiff	    = nBorrow;
            nBorrow     = (DOUBLEDIGIT) (pX[i] < nDiff);
            pXMinusY[i] = pX[i] - (DIGIT) nDiff;
            i++;
        }
        while(0!=nBorrow);
    }
    for(;i<nXSize;i++)
    {
        pXMinusY[i] = pX[i];
    }
    // find the size of z
    if(0==pXMinusY[i-1])
    {
        do
        {
            i--;
        }
        while(0<i && 0==pXMinusY[i-1]);
    }
    return i;
}

size_t CUnsignedArithmeticHelper::MultOracle(size_t      nXSize,
                                             size_t      nYSize,
                                             const DIGIT *pX,
                                             const DIGIT *pY,
                                             DIGIT       *pZ)
{
    DOUBLEDIGIT nProduct,nCarry, nSum;
    size_t      i,j;

    if(0==nXSize || 0==nYSize)
    {
        return 0;
    }
    else
    {
        // zero out Z
        for(i=0;i<nXSize+nYSize;i++)
        {
            pZ[i] = 0;
        }
        for(i=0;i<nXSize;i++)
        {
            nCarry = 0;
            DOUBLEDIGIT nX = pX[i];
            for(j=0;j<nYSize;j++)
            {
                nProduct = nX*pY[j];
                nSum     = (nProduct&c_nClearHigh) + nCarry + pZ[i+j];
                nCarry   = (nProduct>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);
                pZ[i+j]  = (DIGIT) nSum;
            }
            pZ[i+j] = (DIGIT) nCarry;
        }
        return ((0<nCarry) ? i+j : i+j-1);
    }
}

size_t CUnsignedArithmeticHelper::MultiplyMemoryNeeds(size_t nXSize, size_t nYSize, size_t nSum)
{
    size_t nSmall, nLarge, nNeeds;
    if(nXSize<nYSize)
    {
        nSmall = nXSize;
        nLarge = nYSize;
    }
    else
    {
        nSmall = nYSize;
        nLarge = nXSize;
    }
    nNeeds = MultiplyMemoryNeedsBackend(nSmall,nLarge);
    return nNeeds + nSum;
}

size_t CUnsignedArithmeticHelper::MultiplyMemoryNeedsBackend(size_t nXSize, size_t nYSize)
{
    size_t i, j, k;
    if(nXSize<c_pnMultiplicationThresholds[eBasicMultiply])
    {
        // Needs to be kept in sync with MultUBasic, MultUShortLong, MultAddUShortLong
        return 0;
    }
    if(nXSize<<1 <= nYSize)
    {
        size_t nNeeds;
        // chunked multiplies: three sizes.  If using FFT mult, the smaller can actually take more memory as it can use a smaller field (witha longer FFT)
        if (nXSize < c_pnMultiplicationThresholds[e2NByN])
        {
            // simple
            nNeeds = MultiplyMemoryNeedsBackend(nXSize, nXSize);
        }
        else
        {
            // FFT -- FFT can be tricky: a slightly smaller multiply might be doable with a longer FFT and a smaller field,
            // actually taking MORE memory: and with the mult/add needed to solve the multiply in chunks, we try more sizes.
            nNeeds = FFTMultiplyMemoryNeeds(nXSize, nYSize, true);
        }
        return nNeeds + (nXSize<<1) + (nYSize%nXSize); // nXSize + nXSize + (nLarge%nXSize) to hold intermediate value for mult/add
    }
#if(32<=_DIGIT_SIZE_IN_BITS)
    else if (nXSize < c_pnMultiplicationThresholds[e9By5])
#else
    else if (nXSize < c_pnMultiplicationThresholds[e7By4])
#endif
    {
        // tighter bounds can be computed, obviously; but this is reasonable
        // and fast.  It also has the advantage of being nondecreasing, which
        // has its advantages.
        return nYSize*6;
    }
    else if (nXSize < c_pnMultiplicationThresholds[e2NByN])
    {
        // tighter bounds can be computed, obviously; but this is reasonable
        // and fast.  It also has the advantage of being nondecreasing, which
        // has its advantages.  Note this assumes the e2NbyN multiply is not passed small numbers with big piece counts!
        // the 2n by n multiply can be made more memory-efficient by putting more of the subproblems in Z: todo
        return nYSize*12;
    }
    else
    {
        return FFTMultiplyMemoryNeeds(nXSize,nYSize,false);
    }
}

size_t CUnsignedArithmeticHelper::SquareMemoryNeeds(size_t nXSize, size_t nSum)
{
    if(nXSize<c_pnSquareThresholds[eBasicMultiply])
    {
        // Needs to be kept in sync with MultUBasic, MultUShortLong, MultAddUShortLong
        return nSum;
    }
#if(32<=_DIGIT_SIZE_IN_BITS)
    else if (nXSize < c_pnSquareThresholds[e9By5])
#else
    else if (nXSize < c_pnSquareThresholds[e7By4])
#endif
    {
        // tighter bounds can be computed, obviously; but this is reasonable
        // and fast.  It also has the advantage of being nondecreasing, which
        // has its advantages.
        // Tighter still -- this uses the general multiplication needs -- not square -- which is larger.  Debug resolve todo!
        return nSum + nXSize*6;
    }
    else if (nXSize < c_pnSquareThresholds[e2NByN])
    {
        // tighter bounds can be computed, obviously; but this is reasonable
        // and fast.  It also has the advantage of being nondecreasing, which
        // has its advantages.  Note this assumes the e2NbyN multiply is not
        // passed small numbers with big piece counts!
        return nSum + nXSize*12;
    }
    else
    {
        return nSum + FFTSquareMemoryNeeds(nXSize,false);
    }
}

size_t CUnsignedArithmeticHelper::DivisionMemoryNeeds(size_t nNumeratorSize, size_t nDenominatorSize)
{
    size_t nNeeds = DivisionMemoryNeedsBackend(nNumeratorSize,nDenominatorSize);
    return nNeeds;
}

// if this changes, may need to change PowerModulusMemoryNeeds
size_t CUnsignedArithmeticHelper::DivisionMemoryNeedsBackend(size_t nNumeratorSize, size_t nDenominatorSize)
{
    size_t nFirstMultNeeds, nSecondMultNeeds;
    if(nDenominatorSize<c_nDivideThresholdSmall || nNumeratorSize-nDenominatorSize<c_nDivideThresholdDiff || nNumeratorSize<nDenominatorSize)
    {
        return 0;
    }
    else
    {
        size_t nOffset; // not needed here
        size_t nBaseSubproblemSize;
        // memory for first subproblem multiplication
        if(2*nDenominatorSize < nNumeratorSize) nNumeratorSize = 2*nDenominatorSize; // largest problem actually need workspace for
        nBaseSubproblemSize = DivideSubproblemSize(nNumeratorSize, nDenominatorSize, nOffset);
        nFirstMultNeeds     = MultiplyMemoryNeeds(nBaseSubproblemSize+1, nDenominatorSize-nBaseSubproblemSize+1);
        // memory for second subproblem multiplication
        nNumeratorSize      = nNumeratorSize - nBaseSubproblemSize + 2;
        nBaseSubproblemSize = DivideSubproblemSize(nNumeratorSize, nDenominatorSize, nOffset);
        nSecondMultNeeds    = MultiplyMemoryNeeds(nBaseSubproblemSize+1, nDenominatorSize-nBaseSubproblemSize+1);
        return 2 + nDenominatorSize*2 + max(nFirstMultNeeds, nSecondMultNeeds)*2; // *2: FFT might be right on the threshold between sizes,
                                                                                // depending on data; smaller size can take twice as much space as larger
                                                                                // for some thresholds (though the general trend is up)
    }
}

size_t CUnsignedArithmeticHelper::GCDMemoryNeeds(size_t n1, size_t n2, bool bComputingCoefficients)
{
    // needs to be kept in sync with GCD function!
    size_t nNeeds;
    if(bComputingCoefficients)
    {
        size_t nSmall, nLarge;
        if (n1<n2)
        {
            nSmall = n1;
            nLarge = n2;
        }
        else
        {
            nSmall = n2;
            nLarge = n1;
        }
        if(sizeof(DIGIT)*nSmall<=c_nMaxBYTESizeForRecursiveGCD)
        {
            // this is an overestimate!  Tighter bounds exist.
            nNeeds = 4*nLarge + nSmall*((1+nSmall)/2)*_DIGIT_SIZE_IN_BITS;
        }
        else
        {
            nNeeds = 2 + 5*nLarge + max(DivisionMemoryNeeds(2*nLarge, nLarge), nLarge + nSmall + MultiplyMemoryNeeds(nLarge,nSmall));
        }
    }
    else
    {
        size_t nWorkspace, nOperandSpace;
        size_t nLarge,nSmall;
        if(n1<n2)
        {
            nLarge = n2;
            nSmall = n1;
        }
        else
        {
            nLarge = n1;
            nSmall = n2;
        }
        // memory needed: room to copy both arguments (since the back-end
        // process is destructive), plus the memory needed to divide the
        // larger operand by the smaller (workspace plus result) or the
        // workspace needed to do the largest subsequent division: whichever
        // is greater.  The largest subsequent division possible is the
        // second, which can be anything in the range of smallsize divided
        // by something between 1 digit and smallsize digits, inclusive
        // (depending on the data, not just the data size!)
        nWorkspace = DivisionMemoryNeeds(nLarge,nSmall);
        // operand space, first division:
        // nLarge (space for large copy) + nSmall (space for small copy) + (nLarge-nSmall+1) (space for division result)
        nOperandSpace = nLarge + 1;
        // operand space, max smaller division:
        // nLarge (space for large copy) + nSmall (space for small copy) + (nSmall-1+1) (space for division result)
        if(nLarge+1 < nSmall+nSmall)
        {
            nOperandSpace = nSmall+nSmall; // take the larger of the two
        }
        nOperandSpace += nLarge;
        nNeeds        =  nOperandSpace + nWorkspace;
    }
    return nNeeds;
}

size_t CUnsignedArithmeticHelper::PowerModulusMemoryNeeds(size_t nXSize, size_t nYSize, size_t nZSize)
{
    // memory needed:
    // 6*nZSize + nXSize + 2 + max(MultiplyMemoryNeedsBackend(nZSize,nZSize) + 2*nZSize + 1, DivisionMemoryNeedsBackend(2*nZSize, nZSize));
    // Now, noting that the division memory needs is at most ((nZSize<<1) + MultiplyMemoryNeeds(nZSize, nZSize))<<1 for a division of 2 nZSize digits
    // by nZSize digits, this simplifies to
    // 6*nZSize + nXSize + 2 + (((nZSize*2) + MultiplyMemoryNeeds(nZSize, nZSize))*2)
    return nXSize + 10*nZSize + 2 + (MultiplyMemoryNeeds(nZSize, nZSize)<<1);
}

size_t CUnsignedArithmeticHelper::SquareRootNewtonMemoryNeeds(size_t nXSize)
{
    return 4*nXSize + 8 + DivisionMemoryNeeds(nXSize, (nXSize+1)>>1);
}

size_t CUnsignedArithmeticHelper::GeneralSquareRootNewtonMemoryNeeds(size_t nX1Size, size_t nX2Size)
{
    size_t nBaseNeeds     = 4*nX2Size + 8;
    size_t nDivisionNeeds = max(DivisionMemoryNeeds(nX2Size+1, max(nX1Size, 1+(nX2Size-nX1Size)/2)),
                                DivisionMemoryNeeds(nX2Size+1, nX2Size-nX1Size));
    size_t nMultiplyNeeds = max(MultiplyMemoryNeeds((nX2Size-nX1Size)/2 + 1, (nX2Size - nX1Size)/2 + 1),
                                MultiplyMemoryNeeds((nX2Size+1)>>1, (nX2Size+1)>>1));
    return nBaseNeeds + max(nDivisionNeeds, nMultiplyNeeds);
}

size_t CUnsignedArithmeticHelper::GeneralSquareRootRecursiveMemoryNeeds(size_t nX1Size, size_t nX2Size)
{
    size_t nBaseNeeds     = 6*nX2Size + 8; // 6: were it not for roundoff (or, in this case, roundUP) only need 4*size.  But round up at each recursive halving)
    size_t nDivisionNeeds = (nX1Size<<1 < nX2Size) ? 0 : DivisionMemoryNeeds(nX1Size, 2*nX1Size - nX2Size);
    return nBaseNeeds + max(nDivisionNeeds, MultiplyMemoryNeeds((1+nX2Size)>>1, (1+nX2Size)>>1));
}

size_t CUnsignedArithmeticHelper::SquareRootMemoryNeeds(size_t nXSize)
{
    return 3*nXSize + 2 + max(MultiplyMemoryNeeds((nXSize+1)>>1,(nXSize+1)>>1), GeneralSquareRootRecursiveMemoryNeeds((3*nXSize)>>2, nXSize));
}

// same for NthRootNewtonFromGuess and NthRootNewton -- though in the former case, we assume the initial guess is close to the actual root in
// size (at most 1 extra DIGIT)
size_t CUnsignedArithmeticHelper::NthRootNewtonMemoryNeeds(size_t nSize, DIGIT nRoot)
{
    // (n+_DIGIT_SIZE_IN_BITS-1)/_DIGIT_SIZE_IN_BITS: using Newton the value being taken to a power can be a bit larger than the actual root
    // (assuming a reasonable initial guess), but not much
    DIGIT pMaxFirst[] = { c_nClearHigh };
    return 2*nSize + 2 + max(PowerMemoryNeeds(pMaxFirst - ((nSize+nRoot-1)/nRoot) + 1, (nSize+nRoot-1)/nRoot, nRoot-1) + (nRoot+_DIGIT_SIZE_IN_BITS-1)/_DIGIT_SIZE_IN_BITS,
                             DivisionMemoryNeeds(nSize, (nSize+nRoot-1)/nRoot));
}

void CUnsignedArithmeticHelper::Multiply(size_t nXSize,
                                         size_t nYSize,
                                         DIGIT  *pnXValue,
                                         DIGIT  *pnYValue,
                                         DIGIT  *pnXTimesYValue,
                                         DIGIT  *pnWorkspace)
{
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
    DWORD64 dwStart     = dwTimestamp;
    MultUBackend(nXSize, nYSize, pnXValue, pnYValue, pnXTimesYValue, pnWorkspace, dwTimestamp);
    g_nProcessTimes[eNumMultiplyAlgorithms] += (dwTimestamp-dwStart);
    g_nMultiplyCalls[eNumMultiplyAlgorithms]++;
#else
    MultUBackend(nXSize, nYSize, pnXValue, pnYValue, pnXTimesYValue, pnWorkspace);
#endif
}

void CUnsignedArithmeticHelper::MultiplyAdd(size_t nXSize,
                                            size_t nYSize,
                                            size_t &nRunningSumSize,
                                            DIGIT  *pnXValue,
                                            DIGIT  *pnYValue,
                                            DIGIT  *pnRunningSum,
                                            DIGIT  *pnWorkspace)
{
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
    DWORD64 dwStart     = dwTimestamp;
    MultAddUBackend(nXSize, nYSize, nRunningSumSize, pnXValue, pnYValue, pnRunningSum, dwTimestamp, pnWorkspace);
    g_nProcessTimes[eNumMultiplyAlgorithms] += (dwTimestamp - dwStart);
    g_nMultiplyCalls[eNumMultiplyAlgorithms]++;
#else
    MultAddUBackend(nXSize, nYSize, nRunningSumSize, pnXValue, pnYValue, pnRunningSum, pnWorkspace);
#endif
}

void CUnsignedArithmeticHelper::Square(size_t      nXSize,
                                       const DIGIT *pnXValue,
                                       DIGIT       *pnXSquaredValue,
                                       DIGIT       *pnWorkspace)
{
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
    DWORD64 dwStart     = dwTimestamp;
    SquareUBackend(nXSize, pnXValue, pnXSquaredValue, pnWorkspace, dwTimestamp);
    g_nProcessTimes[eNumMultiplyAlgorithms] += (dwTimestamp - dwStart);
    g_nMultiplyCalls[eNumMultiplyAlgorithms]++;
#else
    SquareUBackend(nXSize, pnXValue, pnXSquaredValue, pnWorkspace);
#endif
}

EMultiplyAlgorithm CUnsignedArithmeticHelper::MultUBackend(size_t             nXSize,
                                                           size_t             nYSize,
                                                           const DIGIT        *pXValue,
                                                           const DIGIT        *pYValue,
                                                           DIGIT              *pZValue,
                                                           DIGIT              *pnWorkspace,
#if(_CollectDetailedTimingData)
                                                           DWORD64            &dwTimestamp,
#endif
                                                           size_t             *pnZSize)
{
    size_t             nSmallSize, nLargeSize;
    const DIGIT        *pnSmallValue, *pnLargeValue;
    EMultiplyAlgorithm eAlg = eBasicMultiply;
    if(NULL!=pnZSize)
    {
        if(0==pXValue[nXSize-1])
        {
            do
            {
                pZValue[nYSize+--nXSize] = 0;
            }
            while(0<nXSize && 0==pXValue[nXSize-1]);
            if(0==nXSize)
            {
                *pnZSize=0;
                memset(pZValue,0,nYSize*sizeof(DIGIT));
                return eBasicMultiply;
            }
        }
        if(0==pYValue[nYSize-1])
        {
            do
            {
                pZValue[nXSize+--nYSize] = 0;
            }
            while(0<nYSize && 0==pYValue[nYSize-1]);
            if(0==nYSize)
            {
                *pnZSize=0;
                memset(pZValue,0,nXSize*sizeof(DIGIT));
                return eBasicMultiply;
            }
        }
    }
    if(nXSize<=nYSize)
    {
        nSmallSize   = nXSize;
        nLargeSize   = nYSize;
        pnSmallValue = pXValue;
        pnLargeValue = pYValue;
    }
    else
    {
        nSmallSize   = nYSize;
        nLargeSize   = nXSize;
        pnSmallValue = pYValue;
        pnLargeValue = pXValue;
    }
#if(16 ==_DIGIT_SIZE_IN_BITS)
    // in 16 bit, basic multiply is faster than striped for 1 == nSmallSize and 16 <= nLargeSize.  In this case ONLY.  But the difference is significant.
    if(1 == nSmallSize && 32 <= nLargeSize)
    {
#if(_CollectDetailedTimingData)
        DWORD64 dwStart = dwTimestamp;
        MultUBasic(nSmallSize, nLargeSize, pnSmallValue, pnLargeValue, pZValue, false);
        dwTimestamp = s_Timer.GetMicroseconds();
        g_nMultiplyCalls[eBasicMultiply]++;
        g_nProcessTimes[eBasicMultiply] += (dwTimestamp - dwStart);
#else
        MultUBasic(nSmallSize, nLargeSize, pnSmallValue, pnLargeValue, pZValue, false);
#endif
    }
    else if(nSmallSize < c_pnMultiplicationThresholds[eBasicMultiply])
#else
    if(nSmallSize < c_pnMultiplicationThresholds[eBasicMultiply])
#endif
    {
#if(_CollectDetailedTimingData)
        DWORD64 dwStart = dwTimestamp;
        MultUStriped(nSmallSize, nLargeSize, pnSmallValue, pnLargeValue, pZValue, false);
        dwTimestamp = s_Timer.GetMicroseconds();
        g_nMultiplyCalls[eBasicMultiply]++;
        g_nProcessTimes[eBasicMultiply] += (dwTimestamp - dwStart);
#else
        MultUStriped(nSmallSize, nLargeSize, pnSmallValue, pnLargeValue, pZValue, false);
#endif
    }
    else if(nSmallSize<<1 <= nLargeSize)
    {
        // large size disparity: chop larger smaller pieces, but not the smaller
        // "even" pieces in place
        BigShortLongMultiply(nSmallSize,
                             nLargeSize,
                             pnSmallValue,
                             pnLargeValue,
                             pZValue,
#if(_CollectDetailedTimingData)
                             dwTimestamp,
#endif
                             pnWorkspace,
                             pnZSize);
    }
    else if(nSmallSize < c_pnMultiplicationThresholds[e3By2])
    {
#if(_CollectDetailedTimingData)
        MultU3by2(nSmallSize,nLargeSize,pnSmallValue,pnLargeValue,pZValue,pnWorkspace,dwTimestamp);
#else
        MultU3by2(nSmallSize,nLargeSize,pnSmallValue,pnLargeValue,pZValue,pnWorkspace);
#endif
        eAlg = e3By2;
    }
    else if(nSmallSize < c_pnMultiplicationThresholds[e5By3])
    {
#if(_CollectDetailedTimingData)
        MultU5by3(nSmallSize,nLargeSize,pnSmallValue,pnLargeValue,pZValue,pnWorkspace,dwTimestamp);
#else
        MultU5by3(nSmallSize,nLargeSize,pnSmallValue,pnLargeValue,pZValue,pnWorkspace);
#endif
        eAlg = e5By3;
    }
    else if (nSmallSize < c_pnMultiplicationThresholds[e7By4])
    {
#if(_CollectDetailedTimingData)
        MultU7by4(nSmallSize, nLargeSize, pnSmallValue, pnLargeValue, pZValue, pnWorkspace, dwTimestamp);
#else
        MultU7by4(nSmallSize, nLargeSize, pnSmallValue, pnLargeValue, pZValue, pnWorkspace);
#endif
        eAlg = e7By4;
    }
#if(32<=_DIGIT_SIZE_IN_BITS)
    else if (nSmallSize < c_pnMultiplicationThresholds[e9By5])
    {
#if(_CollectDetailedTimingData)
        MultU9by5(nSmallSize, nLargeSize, pnSmallValue, pnLargeValue, pZValue, pnWorkspace, dwTimestamp);
#else
        MultU9by5(nSmallSize, nLargeSize, pnSmallValue, pnLargeValue, pZValue, pnWorkspace);
#endif
        eAlg = e9By5;
    }
#endif
    else if(nSmallSize < c_pnMultiplicationThresholds[e2NByN])
    {
        size_t      nPieces       = PiecesByProblemSize(nSmallSize);
        SSystemData *pSystemToUse = GenerateSystem(nPieces);
        MultU2NByN(nSmallSize,
                   nLargeSize,
                   pnSmallValue,
                   pnLargeValue,
                   pZValue,
                   pSystemToUse,
#if(_CollectDetailedTimingData)
                   pnWorkspace,
                   dwTimestamp);
#else
                   pnWorkspace);
#endif
        eAlg = e2NByN;
    }
    else
    {
        //  FFT mult
#if(_CollectDetailedTimingData)
        MultFFT(nSmallSize,nLargeSize,pnSmallValue,pnLargeValue,pZValue,pnWorkspace,dwTimestamp);
#else
        MultFFT(nSmallSize,nLargeSize,pnSmallValue,pnLargeValue,pZValue,pnWorkspace);
#endif
        eAlg = eFFTMult;
    }
    if(NULL!=pnZSize)
    {
        if(0==pZValue[nSmallSize+nLargeSize-1])
        {
            nLargeSize--;
        }
        *pnZSize = nSmallSize+nLargeSize;
    }
    return eAlg;
}

EMultiplyAlgorithm CUnsignedArithmeticHelper::SquareUBackend(size_t       nXSize,
                                                             const DIGIT  *pXValue,
                                                             DIGIT        *pZValue,
                                                             DIGIT        *pnWorkspace,
#if(_CollectDetailedTimingData)
                                                             DWORD64      &dwTimestamp,
#endif
                                                             size_t       *pnZSize)
{
    EMultiplyAlgorithm eAlg = eBasicMultiply;
    if(NULL!=pnZSize)
    {
        if(0==pXValue[nXSize-1])
        {
            size_t nOldXSize = nXSize;
            do
            {
                nXSize--;
                pZValue[nXSize + nXSize]     = 0;
                pZValue[nXSize + nXSize + 1] = 0;
            }
            while(0<nXSize && 0==pXValue[nXSize-1]);
            if(0==nXSize)
            {
                *pnZSize=0;
                return eBasicMultiply;
            }
        }
    }
    if(nXSize < c_pnSquareThresholds[eBasicMultiply])
    {
#if(_CollectDetailedTimingData)
        DWORD64 dwStart = dwTimestamp;
        MultUStriped(nXSize, nXSize, pXValue, pXValue, pZValue, false);
        dwTimestamp = s_Timer.GetMicroseconds();
        g_nMultiplyCalls[eBasicMultiply]++;
        g_nProcessTimes[eBasicMultiply] += (dwTimestamp - dwStart);
#else
        MultUStriped(nXSize, nXSize, pXValue, pXValue, pZValue, false);
#endif
    }
    else if(nXSize < c_pnSquareThresholds[e3By2])
    {
        SquareU3by2(nXSize,
                    pXValue,
                    pZValue,
#if(_CollectDetailedTimingData)
                    dwTimestamp,
#endif
                    pnWorkspace);
        eAlg = e3By2;
    }
    else if(nXSize < c_pnSquareThresholds[e5By3])
    {
        SquareU5by3(nXSize,
                    pXValue,
                    pZValue,
#if(_CollectDetailedTimingData)
                    dwTimestamp,
#endif
                    pnWorkspace);
        eAlg = e5By3;
    }
    else if (nXSize < c_pnSquareThresholds[e7By4])
    {
        SquareU7by4(nXSize,
                    pXValue,
                    pZValue,
#if(_CollectDetailedTimingData)
                    dwTimestamp,
#endif
                    pnWorkspace);
        eAlg = e7By4;
    }
#if(32<=_DIGIT_SIZE_IN_BITS)
    else if (nXSize < c_pnSquareThresholds[e9By5])
    {
       SquareU9by5(nXSize,
                   pXValue,
                   pZValue,
#if(_CollectDetailedTimingData)
                   dwTimestamp,
#endif
                   pnWorkspace);
       eAlg = e9By5;
    }
#endif
    else if(nXSize < c_pnSquareThresholds[e2NByN])
    {
        size_t      nPieces       = PiecesByProblemSizeSquare(nXSize);
        SSystemData *pSystemToUse = GenerateSystem(nPieces);
        SquareU2NByN(nXSize,
                     pXValue,
                     pZValue,
                     pSystemToUse,
#if(_CollectDetailedTimingData)
                     dwTimestamp,
#endif
                     pnWorkspace);
        eAlg = e2NByN;
    }
    else
    {
        //  FFT mult
#if(_CollectDetailedTimingData)
        SquareFFT(nXSize,pXValue,pZValue,pnWorkspace, dwTimestamp);
#else
        SquareFFT(nXSize,pXValue,pZValue,pnWorkspace);
#endif
        eAlg = eFFTMult;
    }
    if(NULL!=pnZSize)
    {
        int nSize = nXSize<<1;
        if(0==pZValue[nSize - 1])
        {
            nSize--;
        }
        *pnZSize = nSize;
    }
    return eAlg;
}

EMultiplyAlgorithm CUnsignedArithmeticHelper::MultAddUBackend(size_t             nXSize,
                                                              size_t             nYSize,
                                                              size_t             &nZSize,
                                                              const DIGIT        *pXValue,
                                                              const DIGIT        *pYValue,
                                                              DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                                                              DWORD64            &dwTimestamp,
#endif
                                                              DIGIT              *pnWorkspace)
{
    size_t             nSmallSize, nLargeSize;
    const DIGIT        *pnSmallData, *pnLargeData;
    EMultiplyAlgorithm eAlg = eBasicMultiply;
    if(nXSize<=nYSize)
    {
        nSmallSize  = nXSize;
        nLargeSize  = nYSize;
        pnSmallData = pXValue;
        pnLargeData = pYValue;
    }
    else
    {
        nSmallSize  = nYSize;
        nLargeSize  = nXSize;
        pnSmallData = pYValue;
        pnLargeData = pXValue;
    }
#if(16 ==_DIGIT_SIZE_IN_BITS)
    // in 16 bit, basic multiply-add is faster than striped for 1 == nSmallSize and 2 <= nLargeSize.  In this case ONLY.  But the difference is significant.
    if (1 == nSmallSize)// && 2 <= nLargeSize)
    {
#if(_CollectDetailedTimingData)
        DWORD64 dwStart = dwTimestamp;
        MultUBasic(nSmallSize, nLargeSize, pnSmallData, pnLargeData, pZValue, true);
        dwTimestamp = s_Timer.GetMicroseconds();
        g_nMultiplyCalls[eBasicMultiply]++;
        g_nProcessTimes[eBasicMultiply] += (dwTimestamp - dwStart);
#else
        MultUBasic(nSmallSize, nLargeSize, pnSmallData, pnLargeData, pZValue, true);
#endif
        // get the final size
        if (nXSize + nYSize > nZSize)
        {
            if (0 != pZValue[nXSize + nYSize])
            {
                nZSize = nXSize + nYSize + 1;
            }
            else if (0 != pZValue[nXSize + nYSize - 1])
            {
                nZSize = nXSize + nYSize;
            }
            else
            {
                nZSize = nXSize + nYSize - 1;
            }
    }
        else if (0 != pZValue[nZSize])
        {
            nZSize++;
        }
    }
    else if (nSmallSize < c_pnMultiplicationThresholds[eBasicMultiply])
#else
    if (nSmallSize < c_pnMultiplicationThresholds[eBasicMultiply])
#endif
    {
#if(_CollectDetailedTimingData)
        DWORD64 dwStart = dwTimestamp;
        MultUStriped(nSmallSize, nLargeSize, pnSmallData, pnLargeData, pZValue, true);
        dwTimestamp = s_Timer.GetMicroseconds();
        g_nMultiplyCalls[eBasicMultiply]++;
        g_nProcessTimes[eBasicMultiply] += (dwTimestamp - dwStart);
#else
        MultUStriped(nSmallSize, nLargeSize, pnSmallData, pnLargeData, pZValue, true);
#endif
        // get the final size
        if(nXSize+nYSize>nZSize)
        {
            if(0!=pZValue[nXSize+nYSize])
            {
                nZSize = nXSize+nYSize+1;
            }
            else if(0!=pZValue[nXSize+nYSize-1])
            {
                nZSize = nXSize+nYSize;
            }
            else
            {
                nZSize = nXSize+nYSize-1;
            }
        }
        else if(0!=pZValue[nZSize])
        {
            nZSize++;
        }
    }
    else
    {
        size_t nMultSize = nSmallSize + nLargeSize;
        if (nSmallSize < c_pnMultiplicationThresholds[e3By2])
        {
            MultU3by2(nSmallSize,
                      nLargeSize,
                      pnSmallData,
                      pnLargeData,
                      pnWorkspace,
#if(_CollectDetailedTimingData)
                      pnWorkspace + nMultSize,
                      dwTimestamp);
#else
                      pnWorkspace + nMultSize);
#endif
            eAlg = e3By2;
        }
        else if (nSmallSize < c_pnMultiplicationThresholds[e5By3])
        {
            MultU5by3(nSmallSize,
                      nLargeSize,
                      pnSmallData,
                      pnLargeData,
                      pnWorkspace,
#if(_CollectDetailedTimingData)
                      pnWorkspace + nMultSize,
                      dwTimestamp);
#else
                      pnWorkspace + nMultSize);
            eAlg = e5By3;
#endif
        }
#if(32<=_DIGIT_SIZE_IN_BITS)
        else if (nSmallSize < c_pnMultiplicationThresholds[e7By4])
        {
            MultU7by4(nSmallSize,
                      nLargeSize,
                      pnSmallData,
                      pnLargeData,
                      pnWorkspace,
#if(_CollectDetailedTimingData)
                      pnWorkspace + nMultSize,
                      dwTimestamp);
#else
                      pnWorkspace + nMultSize);
#endif
            eAlg = e7By4;
        }
        else if (nSmallSize < c_pnMultiplicationThresholds[e9By5] && nSmallSize < c_pnMultiplicationThresholds[e2NByN])
        {
            MultU9by5(nSmallSize,
                      nLargeSize,
                      pnSmallData,
                      pnLargeData,
                      pnWorkspace,
#if(_CollectDetailedTimingData)
                      pnWorkspace + nMultSize,
                      dwTimestamp);
#else
                      pnWorkspace + nMultSize);
#endif
            eAlg = e9By5;
        }
#else
        else if (nSmallSize < c_pnMultiplicationThresholds[e7By4] && nSmallSize < c_pnMultiplicationThresholds[e2NByN])
        {
#if(_CollectDetailedTimingData)
            MultU7by4(nSmallSize, nLargeSize, pnSmallData, pnLargeData, pnWorkspace, pnWorkspace + nMultSize, dwTimestamp);
#else
            MultU7by4(nSmallSize, nLargeSize, pnSmallData, pnLargeData, pnWorkspace, pnWorkspace + nMultSize);
#endif
            eAlg = e7By4;
        }
#endif
        else if (nSmallSize < c_pnMultiplicationThresholds[e2NByN])
        {
            size_t      nPieces       = PiecesByProblemSize(nSmallSize);
            SSystemData *pSystemToUse = GenerateSystem(nPieces);
            MultU2NByN(nSmallSize,
                       nLargeSize,
                       pnSmallData,
                       pnLargeData,
                       pnWorkspace,
                       pSystemToUse,
#if(_CollectDetailedTimingData)
                       pnWorkspace + nMultSize,
                       dwTimestamp);
#else
                       pnWorkspace + nMultSize);
#endif
            eAlg = e2NByN;
        }
        else
        {
            MultFFT(nSmallSize,
                    nLargeSize,
                    pnSmallData,
                    pnLargeData,
                    pnWorkspace,
#if(_CollectDetailedTimingData)
                    pnWorkspace + nMultSize,
                    dwTimestamp);
#else
                    pnWorkspace + nMultSize);
#endif
            eAlg = eFFTMult;
        }
        if(0 == pnWorkspace[nMultSize-1]) nMultSize--;
        AddXToYInPlace(nMultSize, nZSize, pnWorkspace, pZValue);
#if(_CollectDetailedTimingData)
        DWORD64 dwTimestamp2 = dwTimestamp;
        dwTimestamp           =  s_Timer.GetMicroseconds();
        g_nProcessTimes[eAlg] += (dwTimestamp - dwTimestamp2);
#endif
        return eAlg;
    }
    return eAlg;
}

void CUnsignedArithmeticHelper::BigShortLongMultiply(size_t             nSmallSize,
                                                     size_t             nLargeSize,
                                                     const DIGIT        *pnSmallValue,
                                                     const DIGIT        *pnLargeValue,
                                                     DIGIT              *pnZValue,
#if(_CollectDetailedTimingData)
                                                     DWORD64            &dwTimestamp,
#endif
                                                     DIGIT              *pnWorkspace,
                                                     size_t             *pnZSize)
{
    // large size disparity: chop larger smaller pieces, but not the smaller
    // Do the "even" pieces in place, and then add in the "odd" pieces
    // Get one step ahead with even pieces, so can add odd in in entirety
    size_t  i,j, nZSize, nStep = nSmallSize<<1;
    nZSize = nStep;
    // Even needs to be one step ahead of the odd
#if(_CollectDetailedTimingData)
    MultUBackend(nSmallSize, nSmallSize, pnSmallValue, pnLargeValue, pnZValue, pnWorkspace, dwTimestamp, pnZSize);
#else
    MultUBackend(nSmallSize, nSmallSize, pnSmallValue, pnLargeValue, pnZValue, pnWorkspace, pnZSize);
#endif
    for(i=nStep; i+nStep<=nLargeSize; i += nStep)
    {
        // in-place even piece
#if(_CollectDetailedTimingData)
        MultUBackend(nSmallSize, nSmallSize, pnSmallValue, pnLargeValue+i, pnZValue+i, pnWorkspace, dwTimestamp, pnZSize);
#else
        MultUBackend(nSmallSize, nSmallSize, pnSmallValue, pnLargeValue+i, pnZValue+i, pnWorkspace, pnZSize);
#endif
        DIGIT c = pnZValue[i - 2];
        // in-place odd piece -- mult/add
        nZSize = nStep + nSmallSize;
#if(_CollectDetailedTimingData)
        MultAddUBackend(nSmallSize, nSmallSize, nZSize, pnSmallValue, pnLargeValue + i - nSmallSize, pnZValue + i - nSmallSize, dwTimestamp, pnWorkspace);
#else
        MultAddUBackend(nSmallSize, nSmallSize, nZSize, pnSmallValue, pnLargeValue+i-nSmallSize, pnZValue+i-nSmallSize, pnWorkspace);
#endif
    }
    if(i<nLargeSize)
    {
        // even and odd piece left to do; even piece is smaller than usual
        // in-place even piece
#if(_CollectDetailedTimingData)
        MultUBackend(nSmallSize, nLargeSize-i, pnSmallValue, pnLargeValue + i, pnZValue + i, pnWorkspace, dwTimestamp, pnZSize);
#else
        MultUBackend(nSmallSize, nLargeSize-i, pnSmallValue, pnLargeValue + i, pnZValue + i, pnWorkspace, pnZSize);
#endif
        // in-place odd piece -- mult/add
        nZSize = nStep + nLargeSize - i;
#if(_CollectDetailedTimingData)
        MultAddUBackend(nSmallSize, nSmallSize, nZSize, pnSmallValue, pnLargeValue + i - nSmallSize, pnZValue + i - nSmallSize, dwTimestamp, pnWorkspace);
#else
        MultAddUBackend(nSmallSize, nSmallSize, nZSize, pnSmallValue, pnLargeValue + i - nSmallSize, pnZValue + i - nSmallSize, pnWorkspace);
#endif
    }
    else
    {
        // just the odd piece left -- zero out the leading bits so we can do mult/add safely (alternately, could do the multiply into the workspace then add it in -- more memory; less work)
        for(j=i;j<nSmallSize+nLargeSize; j++)
        {
            pnZValue[j] = 0;
        }
        nZSize = nStep + nLargeSize - i;
#if(_CollectDetailedTimingData)
        MultAddUBackend(nSmallSize, nSmallSize + nLargeSize - i, nZSize, pnSmallValue, pnLargeValue + i - nSmallSize, pnZValue + i - nSmallSize, dwTimestamp, pnWorkspace);
#else
        MultAddUBackend(nSmallSize, nSmallSize + nLargeSize - i, nZSize, pnSmallValue, pnLargeValue + i - nSmallSize, pnZValue + i - nSmallSize, pnWorkspace);
#endif
    }
    nZSize = nSmallSize + nLargeSize - 1;
    if(pnZValue[nZSize]) nZSize++;
}

void CUnsignedArithmeticHelper::FinishUnbalancedMult(size_t             nXSize,
                                                     size_t             nYSize,
                                                     const DIGIT        *pnX,
                                                     const DIGIT        *pnY,
                                                     DIGIT              *pnZ,
#if(_CollectDetailedTimingData)
                                                     DWORD64            &dwTimestamp,
#endif
                                                     DIGIT              *pnWorkspace,
                                                     size_t             *pnZSize)
{
    size_t      i;
    DOUBLEDIGIT nSum, nCarry;
#if(_CollectDetailedTimingData)
    DWORD64 dwProcessTime = dwTimestamp;
    EMultiplyAlgorithm eCaller = MultUBackend(nXSize,nYSize-nXSize,pnX,pnY,pnWorkspace,pnWorkspace+nYSize,dwTimestamp,pnZSize);
#else
    MultUBackend(nXSize,nYSize-nXSize,pnX,pnY,pnWorkspace,pnWorkspace+nYSize,pnZSize);
#endif
    memcpy(pnZ,pnWorkspace,sizeof(DIGIT)*(nYSize-nXSize));
    nCarry = 0;
    for(i=nYSize-nXSize;i<nYSize;i++)
    {
        nSum   = (nCarry + pnZ[i]) + pnWorkspace[i];
        nCarry = (nSum>>_DIGIT_SIZE_IN_BITS);
        pnZ[i] = (DIGIT) nSum;
    }
    if(0<nCarry)
    {
        do
        {
            nSum     = nCarry + pnZ[i];
            nCarry   = (nSum>>_DIGIT_SIZE_IN_BITS);
            pnZ[i++] = (DIGIT) nSum;
        }
        while(0<nCarry);
    }
#if _CollectDetailedTimingData
    dwTimestamp              =  s_Timer.GetMicroseconds();
    g_nProcessTimes[eCaller] += dwTimestamp-dwProcessTime;
#endif
}

void CUnsignedArithmeticHelper::MultUShortLong(size_t      nXSize,
                                               size_t      nYSize,
                                               const DIGIT *pXValue,
                                               const DIGIT *pYValue,
                                               DIGIT       *pZValue)
{
    DOUBLEDIGIT nProd,nSum,nCarry;
    DOUBLEDIGIT nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11;
    DOUBLEDIGIT nY0,nY1,nY2,nY3,nY4,nY5,nY6,nY7,nY8,nY9,nY10,nY11;
    const DIGIT *pTop;
    size_t      i;

    switch(nXSize)
    {
    case 1:
        {
#if(1)
            nX0    = *pXValue;
            nCarry = 0;
#if 0
            // faster for y 1, 2, 0r 4 DIGITs; slower for y 8+ DIGITs
            pTop   = pYValue+nYSize;
            do
            {
                // note that we don't have to clear the high-order
                // bits in this case, as there is guaranteed to
                // be no overflow -- think of each DIGIT being
                // the last: a 1-DIGIT multiplied by an n-DIGIT
                // can have at most n+1 digits, therefore the
                // nCarry can be at most one DIGIT, therefore
                // it cannot overflow a DOUBLEDIGIT
                nY0        = *pYValue++;
                nProd      = nY0*nX0;
                nSum       = nProd+nCarry;
                nCarry     = nSum>>_DIGIT_SIZE_IN_BITS;
                *pZValue++ = (DIGIT) nSum;
            }
            while(pYValue<pTop);
            *pZValue = (DIGIT) nCarry;
#else
            int i=0;
            for(;i<nYSize;i++)
            {
                nY0        = pYValue[i];
                nProd      = nX0*nY0;
                nSum       = nProd+nCarry;
                nCarry     = nSum>>_DIGIT_SIZE_IN_BITS;
                pZValue[i] = nSum;
            }
            pZValue[i] = nCarry;
#endif
#endif
        }
        break;
    case 2:
        {
#if(1)
            pTop       = pYValue+nYSize-1;
            nX0        = *pXValue++;
            nX1        = *pXValue;
            nY1        = *pYValue++;
            nProd      = nX0*nY1;
            *pZValue++ = (DIGIT) nProd;
            nCarry     = nProd>>_DIGIT_SIZE_IN_BITS;
            nY0        = *pYValue++;
            DotMult2(nX0,nX1,nY0,nY1,nCarry,nSum,nProd,pZValue);
            if(nYSize>=4)
            {
                do
                {
                    nY1 = *pYValue++;
                    DotMult2(nX0,nX1,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMult2(nX0,nX1,nY0,nY1,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%2;
            if(i==0)
            {
                nProd      = nX1*nY0;
                nSum       = (nProd&c_nClearHigh)+nCarry;
                *pZValue++ = (DIGIT) nSum;
                *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            }
            else  // i = 1
            {
                nY1        = *pYValue;
                DotMult2(nX0,nX1,nY1,nY0,nCarry,nSum,nProd,pZValue);
                nProd      = nX1*nY1;
                nSum       = (nProd&c_nClearHigh)+nCarry;
                *pZValue++ = (DIGIT) nSum;
                *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            }
#endif
        }
        break;
    case 3:
        {
#if(1)
            pTop       = pYValue+nYSize-2;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue;
            nY2        = *pYValue++;
            nProd      = nX0*nY2;
            *pZValue++ = (DIGIT) nProd;
            nCarry     = nProd>>_DIGIT_SIZE_IN_BITS;
            nY0        = *pYValue++;
            DotMult2(nX0,nX1,nY0,nY2,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMult3(nX0,nX1,nX2,nY1,nY0,nY2,nCarry,nSum,nProd,pZValue);
            if(nYSize>=6)
            {
                do
                {
                    nY2 = *pYValue++;
                    DotMult3(nX0,nX1,nX2,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMult3(nX0,nX1,nX2,nY0,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMult3(nX0,nX1,nX2,nY1,nY0,nY2,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%3;
            if(i<2)
            {
                if(i==0)
                {
                    DotMult2(nX1,nX2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nProd      = nX2*nY1;
                    nSum       = (nProd&c_nClearHigh)+nCarry;
                    *pZValue++ = (DIGIT) nSum;
                    *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
                else  // i = 1
                {
                    nY2        = *pYValue;
                    DotMult3(nX0,nX1,nX2,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMult2(nX1,nX2,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nProd      = nX2*nY2;
                    nSum       = (nProd&c_nClearHigh)+nCarry;
                    *pZValue++ = (DIGIT) nSum;
                    *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
            }
            else // i = 2
            {
                nY2        = *pYValue++;
                DotMult3(nX0,nX1,nX2,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                nY0        = *pYValue;
                DotMult3(nX0,nX1,nX2,nY0,nY2,nY1,nCarry,nSum,nProd,pZValue);
                DotMult2(nX1,nX2,nY0,nY2,nCarry,nSum,nProd,pZValue);
                nProd      = nX2*nY0;
                nSum       = (nProd&c_nClearHigh)+nCarry;
                *pZValue++ = (DIGIT) nSum;
                *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            }
#endif
        }
        break;
    case 4:
        {
#if(1)
            pTop       = pYValue+nYSize-3;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue;
            nY3        = *pYValue++;
            nProd      = nX0*nY3;
            *pZValue++ = (DIGIT) nProd;
            nCarry     = nProd>>_DIGIT_SIZE_IN_BITS;
            nY0        = *pYValue++;
            DotMult2(nX0,nX1,nY0,nY3,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMult3(nX0,nX1,nX2,nY1,nY0,nY3,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMult4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY3,nCarry,nSum,nProd,pZValue);
            if(nYSize>=8)
            {
                do
                {
                    nY3 = *pYValue++;
                    DotMult4(nX0,nX1,nX2,nX3,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMult4(nX0,nX1,nX2,nX3,nY0,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMult4(nX0,nX1,nX2,nX3,nY1,nY0,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2 = *pYValue++;
                    DotMult4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY3,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%4;
            if(i<2)
            {
                if(i==0)
                {
                    DotMult3(nX1,nX2,nX3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMult2(nX2,nX3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nProd      = nX3*nY2;
                    nSum       = (nProd&c_nClearHigh)+nCarry;
                    *pZValue++ = (DIGIT) nSum;
                    *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
                else  // i = 1
                {
                    nY3        = *pYValue;
                    DotMult4(nX0,nX1,nX2,nX3,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMult3(nX1,nX2,nX3,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    DotMult2(nX2,nX3,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nProd      = nX3*nY3;
                    nSum       = (nProd&c_nClearHigh)+nCarry;
                    *pZValue++ = (DIGIT) nSum;
                    *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
            }
            else
            {
                if(i==2)
                {
                    nY3        = *pYValue++;
                    DotMult4(nX0,nX1,nX2,nX3,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue;
                    DotMult4(nX0,nX1,nX2,nX3,nY0,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    DotMult3(nX1,nX2,nX3,nY0,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    DotMult2(nX2,nX3,nY0,nY3,nCarry,nSum,nProd,pZValue);
                    nProd      = nX3*nY0;
                    nSum       = (nProd&c_nClearHigh)+nCarry;
                    *pZValue++ = (DIGIT) nSum;
                    *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
                else  // i = 3
                {
                    nY3        = *pYValue++;
                    DotMult4(nX0,nX1,nX2,nX3,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue++;
                    DotMult4(nX0,nX1,nX2,nX3,nY0,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1        = *pYValue;
                    DotMult4(nX0,nX1,nX2,nX3,nY1,nY0,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    DotMult3(nX1,nX2,nX3,nY1,nY0,nY3,nCarry,nSum,nProd,pZValue);
                    DotMult2(nX2,nX3,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nProd      = nX3*nY1;
                    nSum       = (nProd&c_nClearHigh)+nCarry;
                    *pZValue++ = (DIGIT) nSum;
                    *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
            }
#endif
        }
        break;
    case 5:
        {
#if(1)
            pTop       = pYValue+nYSize-4;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue;
            nY4        = *pYValue++;
            nProd      = nX0*nY4;
            *pZValue++ = (DIGIT) nProd;
            nCarry     = nProd>>_DIGIT_SIZE_IN_BITS;
            nY0        = *pYValue++;
            DotMult2(nX0,nX1,nY0,nY4,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMult3(nX0,nX1,nX2,nY1,nY0,nY4,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMult4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY4,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMult5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY4,nCarry,nSum,nProd,pZValue);
            if(nYSize>=10)
            {
                do
                {
                    nY4 = *pYValue++;
                    DotMult5(nX0,nX1,nX2,nX3,nX4,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMult5(nX0,nX1,nX2,nX3,nX4,nY0,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMult5(nX0,nX1,nX2,nX3,nX4,nY1,nY0,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2 = *pYValue++;
                    DotMult5(nX0,nX1,nX2,nX3,nX4,nY2,nY1,nY0,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3 = *pYValue++;
                    DotMult5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY4,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%5;
            if(i<4)
            {
                if(i<2)
                {
                    if(i==0)
                    {
                        DotMult4(nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX2,nX3,nX4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX3,nX4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nProd      = nX4*nY3;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 1
                    {
                        nY4        = *pYValue;
                        DotMult5(nX0,nX1,nX2,nX3,nX4,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX1,nX2,nX3,nX4,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX2,nX3,nX4,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX3,nX4,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nProd      = nX4*nY4;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else
                {
                    if(i==2)
                    {
                        nY4        = *pYValue++;
                        DotMult5(nX0,nX1,nX2,nX3,nX4,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue;
                        DotMult5(nX0,nX1,nX2,nX3,nX4,nY0,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX1,nX2,nX3,nX4,nY0,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX2,nX3,nX4,nY0,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX3,nX4,nY0,nY4,nCarry,nSum,nProd,pZValue);
                        nProd      = nX4*nY0;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 3
                    {
                        nY4        = *pYValue++;
                        DotMult5(nX0,nX1,nX2,nX3,nX4,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult5(nX0,nX1,nX2,nX3,nX4,nY0,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue;
                        DotMult5(nX0,nX1,nX2,nX3,nX4,nY1,nY0,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX1,nX2,nX3,nX4,nY1,nY0,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX2,nX3,nX4,nY1,nY0,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX3,nX4,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nProd      = nX4*nY1;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
            }
            else // i = 4
            {
                nY4        = *pYValue++;
                DotMult5(nX0,nX1,nX2,nX3,nX4,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                nY0        = *pYValue++;
                DotMult5(nX0,nX1,nX2,nX3,nX4,nY0,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                nY1        = *pYValue++;
                DotMult5(nX0,nX1,nX2,nX3,nX4,nY1,nY0,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                nY2        = *pYValue;
                DotMult5(nX0,nX1,nX2,nX3,nX4,nY2,nY1,nY0,nY4,nY3,nCarry,nSum,nProd,pZValue);
                DotMult4(nX1,nX2,nX3,nX4,nY2,nY1,nY0,nY4,nCarry,nSum,nProd,pZValue);
                DotMult3(nX2,nX3,nX4,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                DotMult2(nX3,nX4,nY2,nY1,nCarry,nSum,nProd,pZValue);
                nProd      = nX4*nY2;
                nSum       = (nProd&c_nClearHigh)+nCarry;
                *pZValue++ = (DIGIT) nSum;
                *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            }

#endif
        }
        break;
    case 6:
        {
#if(1)
            pTop       = pYValue+nYSize-5;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue++;
            nX5        = *pXValue;
            nY5        = *pYValue++;
            nProd      = nX0*nY5;
            *pZValue++ = (DIGIT) nProd;
            nCarry     = nProd>>_DIGIT_SIZE_IN_BITS;
            nY0        = *pYValue++;
            DotMult2(nX0,nX1,nY0,nY5,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMult3(nX0,nX1,nX2,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMult4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMult5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
            nY4        = *pYValue++;
            DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
            if(nYSize>=12)
            {
                do
                {
                    nY5 = *pYValue++;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY0,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY1,nY0,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2 = *pYValue++;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY2,nY1,nY0,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3 = *pYValue++;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY3,nY2,nY1,nY0,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4 = *pYValue++;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%6;
            if(i<4)
            {
                if(i<2)
                {
                    if(i==0)
                    {
                        DotMult5(nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX3,nX4,nX5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX4,nX5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nProd      = nX5*nY4;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 1
                    {
                        nY5        = *pYValue;
                        DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX1,nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX3,nX4,nX5,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX4,nX5,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nProd      = nX5*nY5;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else
                {
                    if(i==2)
                    {
                        nY5        = *pYValue++;
                        DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue;
                        DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY0,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX1,nX2,nX3,nX4,nX5,nY0,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX2,nX3,nX4,nX5,nY0,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX3,nX4,nX5,nY0,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX4,nX5,nY0,nY5,nCarry,nSum,nProd,pZValue);
                        nProd      = nX5*nY0;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 3
                    {
                        nY5        = *pYValue++;
                        DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY0,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue;
                        DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY1,nY0,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX1,nX2,nX3,nX4,nX5,nY1,nY0,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX2,nX3,nX4,nX5,nY1,nY0,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX3,nX4,nX5,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX4,nX5,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nProd      = nX5*nY1;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
            }
            else
            {
                if(i==4)
                {
                    nY5        = *pYValue++;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue++;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY0,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1        = *pYValue++;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY1,nY0,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2        = *pYValue;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY2,nY1,nY0,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    DotMult5(nX1,nX2,nX3,nX4,nX5,nY2,nY1,nY0,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    DotMult4(nX2,nX3,nX4,nX5,nY2,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
                    DotMult3(nX3,nX4,nX5,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMult2(nX4,nX5,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nProd      = nX5*nY2;
                    nSum       = (nProd&c_nClearHigh)+nCarry;
                    *pZValue++ = (DIGIT) nSum;
                    *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
                else // i = 5
                {
                    nY5        = *pYValue++;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue++;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY0,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1        = *pYValue++;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY1,nY0,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2        = *pYValue++;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY2,nY1,nY0,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3        = *pYValue;
                    DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY3,nY2,nY1,nY0,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    DotMult5(nX1,nX2,nX3,nX4,nX5,nY3,nY2,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
                    DotMult4(nX2,nX3,nX4,nX5,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMult3(nX3,nX4,nX5,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    DotMult2(nX4,nX5,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nProd      = nX5*nY3;
                    nSum       = (nProd&c_nClearHigh)+nCarry;
                    *pZValue++ = (DIGIT) nSum;
                    *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                } 
            }

#endif
        }
        break;
    case 7:
        {
#if(1)
            pTop       = pYValue+nYSize-6;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue++;
            nX5        = *pXValue++;
            nX6        = *pXValue;
            nY6        = *pYValue++;
            nProd      = nX0*nY6;
            *pZValue++ = (DIGIT) nProd;
            nCarry     = nProd>>_DIGIT_SIZE_IN_BITS;
            nY0        = *pYValue++;
            DotMult2(nX0,nX1,nY0,nY6,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMult3(nX0,nX1,nX2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMult4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMult5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
            nY4        = *pYValue++;
            DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
            nY5        = *pYValue++;
            DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
            if(nYSize>=14)
            {
                do
                {
                    nY6 = *pYValue++;
                    DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2 = *pYValue++;
                    DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY2,nY1,nY0,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3 = *pYValue++;
                    DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY3,nY2,nY1,nY0,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4 = *pYValue++;
                    DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY4,nY3,nY2,nY1,nY0,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5 = *pYValue++;
                    DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%7;
            if(i<4)
            {
                if(i<2)
                {
                    if(i==0)
                    {
                        DotMult6(nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX4,nX5,nX6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX5,nX6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nProd      = nX6*nY5;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 1
                    {
                        nY6        = *pYValue;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX4,nX5,nX6,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX5,nX6,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nProd      = nX6*nY6;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else
                {
                    if(i==2)
                    {
                        nY6        = *pYValue++;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX1,nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX4,nX5,nX6,nY0,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX5,nX6,nY0,nY6,nCarry,nSum,nProd,pZValue);
                        nProd      = nX6*nY0;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 3
                    {
                        nY6        = *pYValue++;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX1,nX2,nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX2,nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX4,nX5,nX6,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX5,nX6,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nProd      = nX6*nY1;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
            }
            else
            {
                if(i<6)
                {
                    if(i==4)
                    {
                        nY6        = *pYValue++;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY2,nY1,nY0,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX1,nX2,nX3,nX4,nX5,nX6,nY2,nY1,nY0,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX2,nX3,nX4,nX5,nX6,nY2,nY1,nY0,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX3,nX4,nX5,nX6,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX4,nX5,nX6,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX5,nX6,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nProd      = nX6*nY2;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else // i = 5
                    {
                        nY6        = *pYValue++;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY2,nY1,nY0,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue;
                        DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY3,nY2,nY1,nY0,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX1,nX2,nX3,nX4,nX5,nX6,nY3,nY2,nY1,nY0,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX2,nX3,nX4,nX5,nX6,nY3,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX3,nX4,nX5,nX6,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX4,nX5,nX6,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX5,nX6,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nProd      = nX6*nY3;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else // i = 6
                {
                    nY6        = *pYValue++;
                    DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue++;
                    DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1        = *pYValue++;
                    DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2        = *pYValue++;
                    DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY2,nY1,nY0,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3        = *pYValue++;
                    DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY3,nY2,nY1,nY0,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4        = *pYValue;
                    DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY4,nY3,nY2,nY1,nY0,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    DotMult6(nX1,nX2,nX3,nX4,nX5,nX6,nY4,nY3,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
                    DotMult5(nX2,nX3,nX4,nX5,nX6,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMult4(nX3,nX4,nX5,nX6,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    DotMult3(nX4,nX5,nX6,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    DotMult2(nX5,nX6,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nProd      = nX6*nY4;
                    nSum       = (nProd&c_nClearHigh)+nCarry;
                    *pZValue++ = (DIGIT) nSum;
                    *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
            }

#endif
        }
        break;
    case 8:
        {
#if(1)
            pTop       = pYValue+nYSize-7;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue++;
            nX5        = *pXValue++;
            nX6        = *pXValue++;
            nX7        = *pXValue;
            nY7        = *pYValue++;
            nProd      = nX0*nY7;
            *pZValue++ = (DIGIT) nProd;
            nCarry     = nProd>>_DIGIT_SIZE_IN_BITS;
            nY0        = *pYValue++;
            DotMult2(nX0,nX1,nY0,nY7,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMult3(nX0,nX1,nX2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMult4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMult5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
            nY4        = *pYValue++;
            DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
            nY5        = *pYValue++;
            DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
            nY6        = *pYValue++;
            DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
            if(nYSize>=16)
            {
                do
                {
                    nY7 = *pYValue++;
                    DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2 = *pYValue++;
                    DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3 = *pYValue++;
                    DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4 = *pYValue++;
                    DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY4,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5 = *pYValue++;
                    DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY5,nY4,nY3,nY2,nY1,nY0,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6 = *pYValue++;
                    DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%8;
            if(i<4)
            {
                if(i<2)
                {
                    if(i==0)
                    {
                        DotMult7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX5,nX6,nX7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX6,nX7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY6;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 1
                    {
                        nY7        = *pYValue;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX5,nX6,nX7,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX6,nX7,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY7;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else
                {
                    if(i==2)
                    {
                        nY7        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX5,nX6,nX7,nY0,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX6,nX7,nY0,nY7,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY0;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 3
                    {
                        nY7        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX5,nX6,nX7,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX6,nX7,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY1;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
            }
            else
            {
                if(i<6)
                {
                    if(i==4)
                    {
                        nY7        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX2,nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX5,nX6,nX7,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX6,nX7,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY2;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else // i = 5
                    {
                        nY7        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX2,nX3,nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX3,nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX5,nX6,nX7,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX6,nX7,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY3;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else
                {
                    if(i==6)
                    {
                        nY7        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY4,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY4,nY3,nY2,nY1,nY0,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX2,nX3,nX4,nX5,nX6,nX7,nY4,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX3,nX4,nX5,nX6,nX7,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX4,nX5,nX6,nX7,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX5,nX6,nX7,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX6,nX7,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY4;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 7
                    {
                        nY7        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue++;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY4,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nY5        = *pYValue;
                        DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY5,nY4,nY3,nY2,nY1,nY0,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMult7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY5,nY4,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX2,nX3,nX4,nX5,nX6,nX7,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX3,nX4,nX5,nX6,nX7,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX4,nX5,nX6,nX7,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX5,nX6,nX7,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX6,nX7,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY5;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
            }

#endif
        }
        break;
    case 9:
        {
#if(1)
            pTop       = pYValue+nYSize-8;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue++;
            nX5        = *pXValue++;
            nX6        = *pXValue++;
            nX7        = *pXValue++;
            nX8        = *pXValue;
            nY8        = *pYValue++;
            nProd      = nX0*nY8;
            *pZValue++ = (DIGIT) nProd;
            nCarry     = nProd>>_DIGIT_SIZE_IN_BITS;
            nY0        = *pYValue++;
            DotMult2(nX0,nX1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMult3(nX0,nX1,nX2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMult4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMult5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            nY4        = *pYValue++;
            DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            nY5        = *pYValue++;
            DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            nY6        = *pYValue++;
            DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            nY7        = *pYValue++;
            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            if(nYSize>=18)
            {
                do
                {
                    nY8 = *pYValue++;
                    DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2 = *pYValue++;
                    DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3 = *pYValue++;
                    DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4 = *pYValue++;
                    DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5 = *pYValue++;
                    DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6 = *pYValue++;
                    DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    nY7 = *pYValue++;
                    DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%9;
            if(i<8)
            {
                if(i<4)
                {
                    if(i<2)
                    {
                        if(i==0)
                        {
                            DotMult8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX6,nX7,nX8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX7,nX8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY7;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 1
                        {
                            nY8        = *pYValue;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX6,nX7,nX8,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX7,nX8,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY8;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==2)
                        {
                            nY8        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX6,nX7,nX8,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX7,nX8,nY0,nY8,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY0;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 3
                        {
                            nY8        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX6,nX7,nX8,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX7,nX8,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY1;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
                else
                {
                    if(i<6)
                    {
                        if(i==4)
                        {
                            nY8        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX6,nX7,nX8,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX7,nX8,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY2;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else // i = 5
                        {
                            nY8        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX6,nX7,nX8,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX7,nX8,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY3;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==6)
                        {
                            nY8        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX3,nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX6,nX7,nX8,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX7,nX8,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY4;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 7
                        {
                            nY8        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue++;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            nY5        = *pYValue;
                            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX3,nX4,nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX4,nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX6,nX7,nX8,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX7,nX8,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY5;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
            }
            else // i = 8
            {
                nY8        = *pYValue++;
                DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                nY0        = *pYValue++;
                DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                nY1        = *pYValue++;
                DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                nY2        = *pYValue++;
                DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                nY3        = *pYValue++;
                DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                nY4        = *pYValue++;
                DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                nY5        = *pYValue++;
                DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                nY6        = *pYValue;
                DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                DotMult8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
                DotMult7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                DotMult6(nX3,nX4,nX5,nX6,nX7,nX8,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                DotMult5(nX4,nX5,nX6,nX7,nX8,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                DotMult4(nX5,nX6,nX7,nX8,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                DotMult3(nX6,nX7,nX8,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                DotMult2(nX7,nX8,nY6,nY5,nCarry,nSum,nProd,pZValue);
                nProd      = nX8*nY6;
                nSum       = (nProd&c_nClearHigh)+nCarry;
                *pZValue++ = (DIGIT) nSum;
                *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            }
#endif
        }
        break;
    case 10:
        {
#if(1)
            pTop       = pYValue+nYSize-9;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue++;
            nX5        = *pXValue++;
            nX6        = *pXValue++;
            nX7        = *pXValue++;
            nX8        = *pXValue++;
            nX9        = *pXValue;
            nY9        = *pYValue++;
            nProd      = nX0*nY9;
            *pZValue++ = (DIGIT) nProd;
            nCarry     = nProd>>_DIGIT_SIZE_IN_BITS;
            nY0        = *pYValue++;
            DotMult2(nX0,nX1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMult3(nX0,nX1,nX2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMult4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMult5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY4        = *pYValue++;
            DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY5        = *pYValue++;
            DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY6        = *pYValue++;
            DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY7        = *pYValue++;
            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY8        = *pYValue++;
            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            if(nYSize>=20)
            {
                do
                {
                    nY9 = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2 = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3 = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4 = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5 = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6 = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    nY7 = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                    nY8 = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%10;
            if(i<8)
            {
                if(i<4)
                {
                    if(i<2)
                    {
                        if(i==0)
                        {
                            DotMult9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX7,nX8,nX9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX8,nX9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY8;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 1
                        {
                            nY9        = *pYValue;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX7,nX8,nX9,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX8,nX9,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY9;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==2)
                        {
                            nY9        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX7,nX8,nX9,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX8,nX9,nY0,nY9,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY0;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 3
                        {
                            nY9        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX7,nX8,nX9,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX8,nX9,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY1;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
                else
                {
                    if(i<6)
                    {
                        if(i==4)
                        {
                            nY9        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX7,nX8,nX9,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX8,nX9,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY2;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else // i = 5
                        {
                            nY9        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX7,nX8,nX9,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX8,nX9,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY3;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==6)
                        {
                            nY9        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX7,nX8,nX9,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX8,nX9,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY4;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 7
                        {
                            nY9        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue++;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            nY5        = *pYValue;
                            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX7,nX8,nX9,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX8,nX9,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY5;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
            }
            else
            {
                if(i==8)
                {
                    nY9        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6        = *pYValue;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    DotMult9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                    DotMult8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                    DotMult7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMult6(nX4,nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    DotMult5(nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    DotMult4(nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    DotMult3(nX7,nX8,nX9,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    DotMult2(nX8,nX9,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nProd      = nX9*nY6;
                    nSum       = (nProd&c_nClearHigh)+nCarry;
                    *pZValue++ = (DIGIT) nSum;
                    *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
                else // i = 9
                {
                    nY9        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6        = *pYValue++;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    nY7        = *pYValue;
                    DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                    DotMult9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                    DotMult8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMult7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    DotMult6(nX4,nX5,nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    DotMult5(nX5,nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    DotMult4(nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    DotMult3(nX7,nX8,nX9,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    DotMult2(nX8,nX9,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nProd      = nX9*nY7;
                    nSum       = (nProd&c_nClearHigh)+nCarry;
                    *pZValue++ = (DIGIT) nSum;
                    *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
            }
#endif
        }
        break;
    case 11:
        {
#if(1)
            pTop       = pYValue+nYSize-10;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue++;
            nX5        = *pXValue++;
            nX6        = *pXValue++;
            nX7        = *pXValue++;
            nX8        = *pXValue++;
            nX9        = *pXValue++;
            nX10       = *pXValue;
            nY10       = *pYValue++;
            nProd      = nX0*nY10;
            *pZValue++ = (DIGIT) nProd;
            nCarry     = nProd>>_DIGIT_SIZE_IN_BITS;
            nY0        = *pYValue++;
            DotMult2(nX0,nX1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMult3(nX0,nX1,nX2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMult4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMult5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY4        = *pYValue++;
            DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY5        = *pYValue++;
            DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY6        = *pYValue++;
            DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY7        = *pYValue++;
            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY8        = *pYValue++;
            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY9        = *pYValue++;
            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            if(nYSize>=22)
            {
                do
                {
                    nY10 = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0  = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1  = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2  = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3  = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4  = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5  = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6  = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    nY7  = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                    nY8  = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                    nY9  = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%11;
            if(i<8)
            {
                if(i<4)
                {
                    if(i<2)
                    {
                        if(i==0)
                        {
                            DotMult10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX8,nX9,nX10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX9,nX10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY9;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 1
                        {
                            nY10       = *pYValue;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX8,nX9,nX10,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX9,nX10,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY10;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==2)
                        {
                            nY10       = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX8,nX9,nX10,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX9,nX10,nY0,nY10,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY0;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 3
                        {
                            nY10       = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX8,nX9,nX10,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX9,nX10,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY1;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
                else
                {
                    if(i<6)
                    {
                        if(i==4)
                        {
                            nY10       = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX8,nX9,nX10,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX9,nX10,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY2;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else // i = 5
                        {
                            nY10       = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX8,nX9,nX10,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX9,nX10,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY3;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==6)
                        {
                            nY10       = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX8,nX9,nX10,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX9,nX10,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY4;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 7
                        {
                            nY10       = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue++;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            nY5        = *pYValue;
                            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX8,nX9,nX10,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX9,nX10,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY5;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
            }
            else
            {
                if(i<10)
                {
                    if(i==8)
                    {
                        nY10       = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nY5        = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nY6        = *pYValue;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        DotMult10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                        DotMult9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                        DotMult8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                        DotMult7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX8,nX9,nX10,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX9,nX10,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nProd      = nX10*nY6;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else // i = 9
                    {
                        nY10       = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nY5        = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nY6        = *pYValue++;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        nY7        = *pYValue;
                        DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                        DotMult10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                        DotMult9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                        DotMult8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX8,nX9,nX10,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX9,nX10,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nProd      = nX10*nY7;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else // i = 10
                {
                    nY10       = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1        = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2        = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3        = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4        = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5        = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6        = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    nY7        = *pYValue++;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                    nY8        = *pYValue;
                    DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                    DotMult10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                    DotMult9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMult8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    DotMult7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    DotMult6(nX5,nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    DotMult5(nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    DotMult4(nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    DotMult3(nX8,nX9,nX10,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    DotMult2(nX9,nX10,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    nProd      = nX10*nY8;
                    nSum       = (nProd&c_nClearHigh)+nCarry;
                    *pZValue++ = (DIGIT) nSum;
                    *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
            }
#endif
        }
        break;
    case 12:
        {
#if(1)
            pTop       = pYValue+nYSize-11;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue++;
            nX5        = *pXValue++;
            nX6        = *pXValue++;
            nX7        = *pXValue++;
            nX8        = *pXValue++;
            nX9        = *pXValue++;
            nX10       = *pXValue++;
            nX11       = *pXValue;
            nY11       = *pYValue++;
            nProd      = nX0*nY11;
            *pZValue++ = (DIGIT) nProd;
            nCarry     = nProd>>_DIGIT_SIZE_IN_BITS;
            nY0        = *pYValue++;
            DotMult2(nX0,nX1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMult3(nX0,nX1,nX2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMult4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMult5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY4        = *pYValue++;
            DotMult6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY5        = *pYValue++;
            DotMult7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY6        = *pYValue++;
            DotMult8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY7        = *pYValue++;
            DotMult9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY8        = *pYValue++;
            DotMult10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY9        = *pYValue++;
            DotMult11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY10       = *pYValue++;
            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            if(nYSize>=24)
            {
                do
                {
                    nY11 = *pYValue++;
                    DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0  = *pYValue++;
                    DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1  = *pYValue++;
                    DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2  = *pYValue++;
                    DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3  = *pYValue++;
                    DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4  = *pYValue++;
                    DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5  = *pYValue++;
                    DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6  = *pYValue++;
                    DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    nY7  = *pYValue++;
                    DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                    nY8  = *pYValue++;
                    DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                    nY9  = *pYValue++;
                    DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                    nY10 = *pYValue++;
                    DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%12;
            if(i<8)
            {
                if(i<4)
                {
                    if(i<2)
                    {
                        if(i==0)
                        {
                            DotMult11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX9,nX10,nX11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX10,nX11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY10;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 1
                        {
                            nY11 = *pYValue;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX9,nX10,nX11,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX10,nX11,nY11,nY10,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY11;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==2)
                        {
                            nY11       = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX9,nX10,nX11,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX10,nX11,nY0,nY11,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY0;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 3
                        {
                            nY11       = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX9,nX10,nX11,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX10,nX11,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY1;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
                else
                {
                    if(i<6)
                    {
                        if(i==4)
                        {
                            nY11       = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX9,nX10,nX11,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX10,nX11,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY2;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else // i = 5
                        {
                            nY11       = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMult11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX9,nX10,nX11,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX10,nX11,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY3;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==6)
                        {
                            nY11       = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMult11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX9,nX10,nX11,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX10,nX11,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY4;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 7
                        {
                            nY11       = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue++;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            nY5        = *pYValue;
                            DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMult11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMult10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMult9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMult8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                            DotMult7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                            DotMult6(nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMult5(nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMult4(nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMult3(nX9,nX10,nX11,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMult2(nX10,nX11,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY5;
                            nSum       = (nProd&c_nClearHigh)+nCarry;
                            *pZValue++ = (DIGIT) nSum;
                            *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
            }
            else
            {
                if(i<10)
                {
                    if(i==8)
                    {
                        nY11       = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nY5        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nY6        = *pYValue;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        DotMult11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                        DotMult10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                        DotMult9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                        DotMult8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                        DotMult7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX9,nX10,nX11,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX10,nX11,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nProd      = nX11*nY6;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else // i = 9
                    {
                        nY11       = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nY5        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nY6        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        nY7        = *pYValue;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                        DotMult11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                        DotMult10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                        DotMult9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                        DotMult8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX9,nX10,nX11,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX10,nX11,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nProd      = nX11*nY7;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else
                {
                    if(i==10)
                    {
                        nY11       = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nY5        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nY6        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        nY7        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                        nY8        = *pYValue;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                        DotMult11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                        DotMult10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                        DotMult9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX9,nX10,nX11,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX10,nX11,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        nProd      = nX11*nY8;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else // i = 11
                    {
                        nY11       = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nY5        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nY6        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        nY7        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                        nY8        = *pYValue++;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                        nY9        = *pYValue;
                        DotMult12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                        DotMult11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                        DotMult10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMult9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMult8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMult7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMult6(nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMult5(nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMult4(nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMult3(nX9,nX10,nX11,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        DotMult2(nX10,nX11,nY9,nY8,nCarry,nSum,nProd,pZValue);
                        nProd      = nX11*nY9;
                        nSum       = (nProd&c_nClearHigh)+nCarry;
                        *pZValue++ = (DIGIT) nSum;
                        *pZValue   = (DIGIT) ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
            }
#endif
        }
        break;
    }
}


// x 1 to 12 digits in length
void CUnsignedArithmeticHelper::MultAddUShortLong(size_t      nXSize,
                                                  size_t      nYSize,
                                                  const DIGIT *pXValue,
                                                  const DIGIT *pYValue,
                                                  DIGIT       *pZValue)
{
    DOUBLEDIGIT nProd,nSum,nCarry;
    DOUBLEDIGIT nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11;
    DOUBLEDIGIT nY0,nY1,nY2,nY3,nY4,nY5,nY6,nY7,nY8,nY9,nY10,nY11;
    const DIGIT *pTop;
    size_t      i;

    switch(nXSize)
    {
    case 1:
        {
#if(1)
            nX0    = *pXValue;
            nCarry = 0;
            for(i=0; i<nYSize; i++)
            {
                nY0        = pYValue[i];
                nProd      = nX0*nY0;
                nSum       = nCarry + pZValue[i] + (nProd&c_nClearHigh);
                nCarry     = (nProd>>_DIGIT_SIZE_IN_BITS) + (nSum>>_DIGIT_SIZE_IN_BITS);
                pZValue[i] = nSum;
            }
            pZValue += i;
#endif
        }
        break;
    case 2:
        {
#if(1)
            pTop       = pYValue+nYSize-1;
            nX0        = *pXValue++;
            nX1        = *pXValue;
            nY1        = *pYValue++;
            nProd      = nX0*nY1;
            nSum       = (nProd&c_nClearHigh) + *pZValue;
            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            *pZValue++ = (DIGIT) nSum;
            nY0        = *pYValue++;
            DotMultAdd2(nX0,nX1,nY0,nY1,nCarry,nSum,nProd,pZValue);
            if(nYSize>=4)
            {
                do
                {
                    nY1 = *pYValue++;
                    DotMultAdd2(nX0,nX1,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMultAdd2(nX0,nX1,nY0,nY1,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%2;
            if(i==0)
            {
                nProd      = nX1*nY0;
                nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                *pZValue++ = (DIGIT) nSum;
                nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            }
            else  // i = 1
            {
                nY1        = *pYValue;
                DotMultAdd2(nX0,nX1,nY1,nY0,nCarry,nSum,nProd,pZValue);
                nProd      = nX1*nY1;
                nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                *pZValue++ = (DIGIT) nSum;
                nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            }
#endif
        }
        break;
    case 3:
        {
#if(1)
            pTop       = pYValue+nYSize-2;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue;
            nY2        = *pYValue++;
            nProd      = nX0*nY2;
            nSum       = (nProd&c_nClearHigh) + *pZValue;
            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            *pZValue++ = (DIGIT) nSum;
            nY0        = *pYValue++;
            DotMultAdd2(nX0,nX1,nY0,nY2,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMultAdd3(nX0,nX1,nX2,nY1,nY0,nY2,nCarry,nSum,nProd,pZValue);
            if(nYSize>=6)
            {
                do
                {
                    nY2 = *pYValue++;
                    DotMultAdd3(nX0,nX1,nX2,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMultAdd3(nX0,nX1,nX2,nY0,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMultAdd3(nX0,nX1,nX2,nY1,nY0,nY2,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%3;
            if(i<2)
            {
                if(i==0)
                {
                    DotMultAdd2(nX1,nX2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nProd      = nX2*nY1;
                    nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                    *pZValue++ = (DIGIT) nSum;
                    nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
                else  // i = 1
                {
                    nY2        = *pYValue;
                    DotMultAdd3(nX0,nX1,nX2,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMultAdd2(nX1,nX2,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nProd      = nX2*nY2;
                    nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                    *pZValue++ = (DIGIT) nSum;
                    nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
            }
            else // i = 2
            {
                nY2        = *pYValue++;
                DotMultAdd3(nX0,nX1,nX2,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                nY0        = *pYValue;
                DotMultAdd3(nX0,nX1,nX2,nY0,nY2,nY1,nCarry,nSum,nProd,pZValue);
                DotMultAdd2(nX1,nX2,nY0,nY2,nCarry,nSum,nProd,pZValue);
                nProd      = nX2*nY0;
                nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                *pZValue++ = (DIGIT) nSum;
                nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            }
#endif
        }
        break;
    case 4:
        {
#if(1)
            pTop       = pYValue+nYSize-3;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue;
            nY3        = *pYValue++;
            nProd      = nX0*nY3;
            nSum       = (nProd&c_nClearHigh) + *pZValue;
            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            *pZValue++ = (DIGIT) nSum;
            nY0        = *pYValue++;
            DotMultAdd2(nX0,nX1,nY0,nY3,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMultAdd3(nX0,nX1,nX2,nY1,nY0,nY3,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMultAdd4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY3,nCarry,nSum,nProd,pZValue);
            if(nYSize>=8)
            {
                do
                {
                    nY3 = *pYValue++;
                    DotMultAdd4(nX0,nX1,nX2,nX3,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMultAdd4(nX0,nX1,nX2,nX3,nY0,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMultAdd4(nX0,nX1,nX2,nX3,nY1,nY0,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2 = *pYValue++;
                    DotMultAdd4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY3,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%4;
            if(i<2)
            {
                if(i==0)
                {
                    DotMultAdd3(nX1,nX2,nX3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMultAdd2(nX2,nX3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nProd      = nX3*nY2;
                    nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                    *pZValue++ = (DIGIT) nSum;
                    nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
                else  // i = 1
                {
                    nY3        = *pYValue;
                    DotMultAdd4(nX0,nX1,nX2,nX3,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMultAdd3(nX1,nX2,nX3,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    DotMultAdd2(nX2,nX3,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nProd      = nX3*nY3;
                    nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                    *pZValue++ = (DIGIT) nSum;
                    nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
            }
            else
            {
                if(i==2)
                {
                    nY3        = *pYValue++;
                    DotMultAdd4(nX0,nX1,nX2,nX3,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue;
                    DotMultAdd4(nX0,nX1,nX2,nX3,nY0,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    DotMultAdd3(nX1,nX2,nX3,nY0,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    DotMultAdd2(nX2,nX3,nY0,nY3,nCarry,nSum,nProd,pZValue);
                    nProd      = nX3*nY0;
                    nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                    *pZValue++ = (DIGIT) nSum;
                    nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
                else  // i = 3
                {
                    nY3        = *pYValue++;
                    DotMultAdd4(nX0,nX1,nX2,nX3,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue++;
                    DotMultAdd4(nX0,nX1,nX2,nX3,nY0,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1        = *pYValue;
                    DotMultAdd4(nX0,nX1,nX2,nX3,nY1,nY0,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    DotMultAdd3(nX1,nX2,nX3,nY1,nY0,nY3,nCarry,nSum,nProd,pZValue);
                    DotMultAdd2(nX2,nX3,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nProd      = nX3*nY1;
                    nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                    *pZValue++ = (DIGIT) nSum;
                    nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
            }
#endif
        }
        break;
    case 5:
        {
#if(1)
            pTop       = pYValue+nYSize-4;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue;
            nY4        = *pYValue++;
            nProd      = nX0*nY4;
            nSum       = (nProd&c_nClearHigh) + *pZValue;
            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            *pZValue++ = (DIGIT) nSum;
            nY0        = *pYValue++;
            DotMultAdd2(nX0,nX1,nY0,nY4,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMultAdd3(nX0,nX1,nX2,nY1,nY0,nY4,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMultAdd4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY4,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY4,nCarry,nSum,nProd,pZValue);
            if(nYSize>=10)
            {
                do
                {
                    nY4 = *pYValue++;
                    DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY0,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY1,nY0,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2 = *pYValue++;
                    DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY2,nY1,nY0,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3 = *pYValue++;
                    DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY4,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%5;
            if(i<4)
            {
                if(i<2)
                {
                    if(i==0)
                    {
                        DotMultAdd4(nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX2,nX3,nX4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX3,nX4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nProd      = nX4*nY3;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 1
                    {
                        nY4        = *pYValue;
                        DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX1,nX2,nX3,nX4,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX2,nX3,nX4,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX3,nX4,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nProd      = nX4*nY4;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else
                {
                    if(i==2)
                    {
                        nY4        = *pYValue++;
                        DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue;
                        DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY0,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX1,nX2,nX3,nX4,nY0,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX2,nX3,nX4,nY0,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX3,nX4,nY0,nY4,nCarry,nSum,nProd,pZValue);
                        nProd      = nX4*nY0;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 3
                    {
                        nY4        = *pYValue++;
                        DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY0,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue;
                        DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY1,nY0,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX1,nX2,nX3,nX4,nY1,nY0,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX2,nX3,nX4,nY1,nY0,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX3,nX4,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nProd      = nX4*nY1;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
            }
            else // i = 4
            {
                nY4        = *pYValue++;
                DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                nY0        = *pYValue++;
                DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY0,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                nY1        = *pYValue++;
                DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY1,nY0,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                nY2        = *pYValue;
                DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY2,nY1,nY0,nY4,nY3,nCarry,nSum,nProd,pZValue);
                DotMultAdd4(nX1,nX2,nX3,nX4,nY2,nY1,nY0,nY4,nCarry,nSum,nProd,pZValue);
                DotMultAdd3(nX2,nX3,nX4,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                DotMultAdd2(nX3,nX4,nY2,nY1,nCarry,nSum,nProd,pZValue);
                nProd      = nX4*nY2;
                nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                *pZValue++ = (DIGIT) nSum;
                nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            }

#endif
        }
        break;
    case 6:
        {
#if(1)
            pTop       = pYValue+nYSize-5;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue++;
            nX5        = *pXValue;
            nY5        = *pYValue++;
            nProd      = nX0*nY5;
            nSum       = (nProd&c_nClearHigh) + *pZValue;
            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            *pZValue++ = (DIGIT) nSum;
            nY0        = *pYValue++;
            DotMultAdd2(nX0,nX1,nY0,nY5,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMultAdd3(nX0,nX1,nX2,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMultAdd4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
            nY4        = *pYValue++;
            DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
            if(nYSize>=12)
            {
                do
                {
                    nY5 = *pYValue++;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY0,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY1,nY0,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2 = *pYValue++;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY2,nY1,nY0,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3 = *pYValue++;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY3,nY2,nY1,nY0,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4 = *pYValue++;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%6;
            if(i<4)
            {
                if(i<2)
                {
                    if(i==0)
                    {
                        DotMultAdd5(nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX3,nX4,nX5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX4,nX5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nProd      = nX5*nY4;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 1
                    {
                        nY5        = *pYValue;
                        DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX1,nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX3,nX4,nX5,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX4,nX5,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nProd      = nX5*nY5;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else
                {
                    if(i==2)
                    {
                        nY5        = *pYValue++;
                        DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue;
                        DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY0,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX1,nX2,nX3,nX4,nX5,nY0,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX2,nX3,nX4,nX5,nY0,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX3,nX4,nX5,nY0,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX4,nX5,nY0,nY5,nCarry,nSum,nProd,pZValue);
                        nProd      = nX5*nY0;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 3
                    {
                        nY5        = *pYValue++;
                        DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY0,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue;
                        DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY1,nY0,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX1,nX2,nX3,nX4,nX5,nY1,nY0,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX2,nX3,nX4,nX5,nY1,nY0,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX3,nX4,nX5,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX4,nX5,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nProd      = nX5*nY1;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
            }
            else
            {
                if(i==4)
                {
                    nY5        = *pYValue++;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue++;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY0,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1        = *pYValue++;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY1,nY0,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2        = *pYValue;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY2,nY1,nY0,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    DotMultAdd5(nX1,nX2,nX3,nX4,nX5,nY2,nY1,nY0,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    DotMultAdd4(nX2,nX3,nX4,nX5,nY2,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
                    DotMultAdd3(nX3,nX4,nX5,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMultAdd2(nX4,nX5,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nProd      = nX5*nY2;
                    nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                    *pZValue++ = (DIGIT) nSum;
                    nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
                else // i = 5
                {
                    nY5        = *pYValue++;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue++;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY0,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1        = *pYValue++;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY1,nY0,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2        = *pYValue++;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY2,nY1,nY0,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3        = *pYValue;
                    DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY3,nY2,nY1,nY0,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    DotMultAdd5(nX1,nX2,nX3,nX4,nX5,nY3,nY2,nY1,nY0,nY5,nCarry,nSum,nProd,pZValue);
                    DotMultAdd4(nX2,nX3,nX4,nX5,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMultAdd3(nX3,nX4,nX5,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    DotMultAdd2(nX4,nX5,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nProd      = nX5*nY3;
                    nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                    *pZValue++ = (DIGIT) nSum;
                    nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                } 
            }

#endif
        }
        break;
    case 7:
        {
#if(1)
            pTop       = pYValue+nYSize-6;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue++;
            nX5        = *pXValue++;
            nX6        = *pXValue;
            nY6        = *pYValue++;
            nProd      = nX0*nY6;
            nSum       = (nProd&c_nClearHigh) + *pZValue;
            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            *pZValue++ = (DIGIT) nSum;
            nY0        = *pYValue++;
            DotMultAdd2(nX0,nX1,nY0,nY6,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMultAdd3(nX0,nX1,nX2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMultAdd4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
            nY4        = *pYValue++;
            DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
            nY5        = *pYValue++;
            DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
            if(nYSize>=14)
            {
                do
                {
                    nY6 = *pYValue++;
                    DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2 = *pYValue++;
                    DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY2,nY1,nY0,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3 = *pYValue++;
                    DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY3,nY2,nY1,nY0,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4 = *pYValue++;
                    DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY4,nY3,nY2,nY1,nY0,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5 = *pYValue++;
                    DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%7;
            if(i<4)
            {
                if(i<2)
                {
                    if(i==0)
                    {
                        DotMultAdd6(nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX4,nX5,nX6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX5,nX6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nProd      = nX6*nY5;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 1
                    {
                        nY6        = *pYValue;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX4,nX5,nX6,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX5,nX6,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nProd      = nX6*nY6;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else
                {
                    if(i==2)
                    {
                        nY6        = *pYValue++;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX1,nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX4,nX5,nX6,nY0,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX5,nX6,nY0,nY6,nCarry,nSum,nProd,pZValue);
                        nProd      = nX6*nY0;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 3
                    {
                        nY6        = *pYValue++;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX1,nX2,nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX2,nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX4,nX5,nX6,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX5,nX6,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nProd      = nX6*nY1;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
            }
            else
            {
                if(i<6)
                {
                    if(i==4)
                    {
                        nY6        = *pYValue++;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY2,nY1,nY0,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX1,nX2,nX3,nX4,nX5,nX6,nY2,nY1,nY0,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX2,nX3,nX4,nX5,nX6,nY2,nY1,nY0,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX3,nX4,nX5,nX6,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX4,nX5,nX6,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX5,nX6,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nProd      = nX6*nY2;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else // i = 5
                    {
                        nY6        = *pYValue++;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY2,nY1,nY0,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue;
                        DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY3,nY2,nY1,nY0,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX1,nX2,nX3,nX4,nX5,nX6,nY3,nY2,nY1,nY0,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX2,nX3,nX4,nX5,nX6,nY3,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX3,nX4,nX5,nX6,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX4,nX5,nX6,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX5,nX6,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nProd      = nX6*nY3;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else // i = 6
                {
                    nY6        = *pYValue++;
                    DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue++;
                    DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY0,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1        = *pYValue++;
                    DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY1,nY0,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2        = *pYValue++;
                    DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY2,nY1,nY0,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3        = *pYValue++;
                    DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY3,nY2,nY1,nY0,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4        = *pYValue;
                    DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY4,nY3,nY2,nY1,nY0,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    DotMultAdd6(nX1,nX2,nX3,nX4,nX5,nX6,nY4,nY3,nY2,nY1,nY0,nY6,nCarry,nSum,nProd,pZValue);
                    DotMultAdd5(nX2,nX3,nX4,nX5,nX6,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMultAdd4(nX3,nX4,nX5,nX6,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    DotMultAdd3(nX4,nX5,nX6,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    DotMultAdd2(nX5,nX6,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nProd      = nX6*nY4;
                    nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                    *pZValue++ = (DIGIT) nSum;
                    nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
            }

#endif
        }
        break;
    case 8:
        {
#if(1)
            pTop       = pYValue+nYSize-7;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue++;
            nX5        = *pXValue++;
            nX6        = *pXValue++;
            nX7        = *pXValue;
            nY7        = *pYValue++;
            nProd      = nX0*nY7;
            nSum       = (nProd&c_nClearHigh) + *pZValue;
            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            *pZValue++ = (DIGIT) nSum;
            nY0        = *pYValue++;
            DotMultAdd2(nX0,nX1,nY0,nY7,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMultAdd3(nX0,nX1,nX2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMultAdd4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
            nY4        = *pYValue++;
            DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
            nY5        = *pYValue++;
            DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
            nY6        = *pYValue++;
            DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
            if(nYSize>=16)
            {
                do
                {
                    nY7 = *pYValue++;
                    DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2 = *pYValue++;
                    DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3 = *pYValue++;
                    DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4 = *pYValue++;
                    DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY4,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5 = *pYValue++;
                    DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY5,nY4,nY3,nY2,nY1,nY0,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6 = *pYValue++;
                    DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%8;
            if(i<4)
            {
                if(i<2)
                {
                    if(i==0)
                    {
                        DotMultAdd7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX5,nX6,nX7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX6,nX7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY6;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 1
                    {
                        nY7        = *pYValue;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX5,nX6,nX7,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX6,nX7,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY7;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else
                {
                    if(i==2)
                    {
                        nY7        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX5,nX6,nX7,nY0,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX6,nX7,nY0,nY7,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY0;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 3
                    {
                        nY7        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX5,nX6,nX7,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX6,nX7,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY1;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
            }
            else
            {
                if(i<6)
                {
                    if(i==4)
                    {
                        nY7        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX2,nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX5,nX6,nX7,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX6,nX7,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY2;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else // i = 5
                    {
                        nY7        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX2,nX3,nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX3,nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX5,nX6,nX7,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX6,nX7,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY3;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else
                {
                    if(i==6)
                    {
                        nY7        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY4,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY4,nY3,nY2,nY1,nY0,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX2,nX3,nX4,nX5,nX6,nX7,nY4,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX3,nX4,nX5,nX6,nX7,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX4,nX5,nX6,nX7,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX5,nX6,nX7,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX6,nX7,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY4;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else  // i = 7
                    {
                        nY7        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue++;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY4,nY3,nY2,nY1,nY0,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nY5        = *pYValue;
                        DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY5,nY4,nY3,nY2,nY1,nY0,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMultAdd7(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY5,nY4,nY3,nY2,nY1,nY0,nY7,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX2,nX3,nX4,nX5,nX6,nX7,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX3,nX4,nX5,nX6,nX7,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX4,nX5,nX6,nX7,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX5,nX6,nX7,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX6,nX7,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nProd      = nX7*nY5;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
            }

#endif
        }
        break;
    case 9:
        {
#if(1)
            pTop       = pYValue+nYSize-8;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue++;
            nX5        = *pXValue++;
            nX6        = *pXValue++;
            nX7        = *pXValue++;
            nX8        = *pXValue;
            nY8        = *pYValue++;
            nProd      = nX0*nY8;
            nSum       = (nProd&c_nClearHigh) + *pZValue;
            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            *pZValue++ = (DIGIT) nSum;
            nY0        = *pYValue++;
            DotMultAdd2(nX0,nX1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMultAdd3(nX0,nX1,nX2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMultAdd4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            nY4        = *pYValue++;
            DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            nY5        = *pYValue++;
            DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            nY6        = *pYValue++;
            DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            nY7        = *pYValue++;
            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
            if(nYSize>=18)
            {
                do
                {
                    nY8 = *pYValue++;
                    DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2 = *pYValue++;
                    DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3 = *pYValue++;
                    DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4 = *pYValue++;
                    DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5 = *pYValue++;
                    DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6 = *pYValue++;
                    DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    nY7 = *pYValue++;
                    DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%9;
            if(i<8)
            {
                if(i<4)
                {
                    if(i<2)
                    {
                        if(i==0)
                        {
                            DotMultAdd8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX6,nX7,nX8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX7,nX8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY7;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 1
                        {
                            nY8 = *pYValue;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX6,nX7,nX8,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX7,nX8,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY8;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==2)
                        {
                            nY8        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX6,nX7,nX8,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX7,nX8,nY0,nY8,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY0;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 3
                        {
                            nY8        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX6,nX7,nX8,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX7,nX8,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY1;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
                else
                {
                    if(i<6)
                    {
                        if(i==4)
                        {
                            nY8        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX6,nX7,nX8,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX7,nX8,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY2;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else // i = 5
                        {
                            nY8        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX6,nX7,nX8,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX7,nX8,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY3;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==6)
                        {
                            nY8        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX3,nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX6,nX7,nX8,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX7,nX8,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY4;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 7
                        {
                            nY8        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue++;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            nY5        = *pYValue;
                            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX3,nX4,nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX4,nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX6,nX7,nX8,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX7,nX8,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nProd      = nX8*nY5;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
            }
            else // i = 8
            {
                nY8        = *pYValue++;
                DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                nY0        = *pYValue++;
                DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                nY1        = *pYValue++;
                DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                nY2        = *pYValue++;
                DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                nY3        = *pYValue++;
                DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                nY4        = *pYValue++;
                DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                nY5        = *pYValue++;
                DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                nY6        = *pYValue;
                DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nY7,nCarry,nSum,nProd,pZValue);
                DotMultAdd8(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY8,nCarry,nSum,nProd,pZValue);
                DotMultAdd7(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                DotMultAdd6(nX3,nX4,nX5,nX6,nX7,nX8,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                DotMultAdd5(nX4,nX5,nX6,nX7,nX8,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                DotMultAdd4(nX5,nX6,nX7,nX8,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                DotMultAdd3(nX6,nX7,nX8,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                DotMultAdd2(nX7,nX8,nY6,nY5,nCarry,nSum,nProd,pZValue);
                nProd      = nX8*nY6;
                nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                *pZValue++ = (DIGIT) nSum;
                nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            }
#endif
        }
        break;
    case 10:
        {
#if(1)
            pTop       = pYValue+nYSize-9;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue++;
            nX5        = *pXValue++;
            nX6        = *pXValue++;
            nX7        = *pXValue++;
            nX8        = *pXValue++;
            nX9        = *pXValue;
            nY9        = *pYValue++;
            nProd      = nX0*nY9;
            nSum       = (nProd&c_nClearHigh) + *pZValue;
            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            *pZValue++ = (DIGIT) nSum;
            nY0        = *pYValue++;
            DotMultAdd2(nX0,nX1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMultAdd3(nX0,nX1,nX2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMultAdd4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY4        = *pYValue++;
            DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY5        = *pYValue++;
            DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY6        = *pYValue++;
            DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY7        = *pYValue++;
            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            nY8        = *pYValue++;
            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
            if(nYSize>=20)
            {
                do
                {
                    nY9 = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0 = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1 = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2 = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3 = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4 = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5 = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6 = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    nY7 = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                    nY8 = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%10;
            if(i<8)
            {
                if(i<4)
                {
                    if(i<2)
                    {
                        if(i==0)
                        {
                            DotMultAdd9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX7,nX8,nX9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX8,nX9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY8;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 1
                        {
                            nY9        = *pYValue;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX7,nX8,nX9,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX8,nX9,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY9;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==2)
                        {
                            nY9        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX7,nX8,nX9,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX8,nX9,nY0,nY9,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY0;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 3
                        {
                            nY9        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX7,nX8,nX9,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX8,nX9,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY1;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
                else
                {
                    if(i<6)
                    {
                        if(i==4)
                        {
                            nY9        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX7,nX8,nX9,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX8,nX9,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY2;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else // i = 5
                        {
                            nY9        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX7,nX8,nX9,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX8,nX9,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY3;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==6)
                        {
                            nY9        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX7,nX8,nX9,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX8,nX9,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY4;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 7
                        {
                            nY9        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue++;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            nY5        = *pYValue;
                            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX7,nX8,nX9,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX8,nX9,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nProd      = nX9*nY5;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
            }
            else
            {
                if(i==8)
                {
                    nY9        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6        = *pYValue;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    DotMultAdd9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                    DotMultAdd8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                    DotMultAdd7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMultAdd6(nX4,nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    DotMultAdd5(nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    DotMultAdd4(nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    DotMultAdd3(nX7,nX8,nX9,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    DotMultAdd2(nX8,nX9,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nProd      = nX9*nY6;
                    nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                    *pZValue++ = (DIGIT) nSum;
                    nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
                else // i = 9
                {
                    nY9        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6        = *pYValue++;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    nY7        = *pYValue;
                    DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nY8,nCarry,nSum,nProd,pZValue);
                    DotMultAdd9(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY9,nCarry,nSum,nProd,pZValue);
                    DotMultAdd8(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMultAdd7(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    DotMultAdd6(nX4,nX5,nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    DotMultAdd5(nX5,nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    DotMultAdd4(nX6,nX7,nX8,nX9,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    DotMultAdd3(nX7,nX8,nX9,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    DotMultAdd2(nX8,nX9,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nProd      = nX9*nY7;
                    nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                    *pZValue++ = (DIGIT) nSum;
                    nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
            }
#endif
        }
        break;
    case 11:
        {
#if(1)
            pTop       = pYValue+nYSize-10;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue++;
            nX5        = *pXValue++;
            nX6        = *pXValue++;
            nX7        = *pXValue++;
            nX8        = *pXValue++;
            nX9        = *pXValue++;
            nX10       = *pXValue;
            nY10       = *pYValue++;
            nProd      = nX0*nY10;
            nSum       = (nProd&c_nClearHigh) + *pZValue;
            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            *pZValue++ = (DIGIT) nSum;
            nY0        = *pYValue++;
            DotMultAdd2(nX0,nX1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMultAdd3(nX0,nX1,nX2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMultAdd4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY4        = *pYValue++;
            DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY5        = *pYValue++;
            DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY6        = *pYValue++;
            DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY7        = *pYValue++;
            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY8        = *pYValue++;
            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            nY9        = *pYValue++;
            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
            if(nYSize>=22)
            {
                do
                {
                    nY10 = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0  = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1  = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2  = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3  = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4  = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5  = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6  = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    nY7  = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                    nY8  = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                    nY9  = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%11;
            if(i<8)
            {
                if(i<4)
                {
                    if(i<2)
                    {
                        if(i==0)
                        {
                            DotMultAdd10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX8,nX9,nX10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX9,nX10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY9;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 1
                        {
                            nY10       = *pYValue;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX8,nX9,nX10,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX9,nX10,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY10;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==2)
                        {
                            nY10       = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX8,nX9,nX10,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX9,nX10,nY0,nY10,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY0;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 3
                        {
                            nY10       = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX8,nX9,nX10,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX9,nX10,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY1;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
                else
                {
                    if(i<6)
                    {
                        if(i==4)
                        {
                            nY10       = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX8,nX9,nX10,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX9,nX10,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY2;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else // i = 5
                        {
                            nY10       = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX8,nX9,nX10,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX9,nX10,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY3;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==6)
                        {
                            nY10       = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX8,nX9,nX10,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX9,nX10,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY4;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 7
                        {
                            nY10       = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue++;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            nY5        = *pYValue;
                            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX8,nX9,nX10,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX9,nX10,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nProd      = nX10*nY5;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
            }
            else
            {
                if(i<10)
                {
                    if(i==8)
                    {
                        nY10       = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nY5        = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nY6        = *pYValue;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        DotMultAdd10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                        DotMultAdd9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                        DotMultAdd8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                        DotMultAdd7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX8,nX9,nX10,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX9,nX10,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nProd      = nX10*nY6;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else // i = 9
                    {
                        nY10       = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nY5        = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nY6        = *pYValue++;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        nY7        = *pYValue;
                        DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                        DotMultAdd10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                        DotMultAdd9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                        DotMultAdd8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX8,nX9,nX10,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX9,nX10,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nProd      = nX10*nY7;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else // i = 10
                {
                    nY10       = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0        = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1        = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2        = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3        = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4        = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5        = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6        = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    nY7        = *pYValue++;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                    nY8        = *pYValue;
                    DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nY9,nCarry,nSum,nProd,pZValue);
                    DotMultAdd10(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY10,nCarry,nSum,nProd,pZValue);
                    DotMultAdd9(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    DotMultAdd8(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    DotMultAdd7(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    DotMultAdd6(nX5,nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    DotMultAdd5(nX6,nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    DotMultAdd4(nX7,nX8,nX9,nX10,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    DotMultAdd3(nX8,nX9,nX10,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    DotMultAdd2(nX9,nX10,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    nProd      = nX10*nY8;
                    nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                    *pZValue++ = (DIGIT) nSum;
                    nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                }
            }
#endif
        }
        break;
    case 12:
        {
#if(1)
            pTop       = pYValue+nYSize-11;
            nX0        = *pXValue++;
            nX1        = *pXValue++;
            nX2        = *pXValue++;
            nX3        = *pXValue++;
            nX4        = *pXValue++;
            nX5        = *pXValue++;
            nX6        = *pXValue++;
            nX7        = *pXValue++;
            nX8        = *pXValue++;
            nX9        = *pXValue++;
            nX10       = *pXValue++;
            nX11       = *pXValue;
            nY11       = *pYValue++;
            nProd      = nX0*nY11;
            nSum       = (nProd&c_nClearHigh) + *pZValue;
            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
            *pZValue++ = (DIGIT) nSum;
            nY0        = *pYValue++;
            DotMultAdd2(nX0,nX1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY1        = *pYValue++;
            DotMultAdd3(nX0,nX1,nX2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY2        = *pYValue++;
            DotMultAdd4(nX0,nX1,nX2,nX3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY3        = *pYValue++;
            DotMultAdd5(nX0,nX1,nX2,nX3,nX4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY4        = *pYValue++;
            DotMultAdd6(nX0,nX1,nX2,nX3,nX4,nX5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY5        = *pYValue++;
            DotMultAdd7(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY6        = *pYValue++;
            DotMultAdd8(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY7        = *pYValue++;
            DotMultAdd9(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY8        = *pYValue++;
            DotMultAdd10(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY9        = *pYValue++;
            DotMultAdd11(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            nY10       = *pYValue++;
            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
            if(nYSize>=24)
            {
                do
                {
                    nY11 = *pYValue++;
                    DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                    nY0  = *pYValue++;
                    DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                    nY1  = *pYValue++;
                    DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                    nY2  = *pYValue++;
                    DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                    nY3  = *pYValue++;
                    DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                    nY4  = *pYValue++;
                    DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                    nY5  = *pYValue++;
                    DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                    nY6  = *pYValue++;
                    DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                    nY7  = *pYValue++;
                    DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                    nY8  = *pYValue++;
                    DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                    nY9  = *pYValue++;
                    DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                    nY10 = *pYValue++;
                    DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                }
                while(pYValue<pTop);
            }
            i = nYSize%12;
            if(i<8)
            {
                if(i<4)
                {
                    if(i<2)
                    {
                        if(i==0)
                        {
                            DotMultAdd11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX6,nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX7,nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX8,nX9,nX10,nX11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX9,nX10,nX11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX10,nX11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY10;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 1
                        {
                            nY11       = *pYValue;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX9,nX10,nX11,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX10,nX11,nY11,nY10,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY11;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==2)
                        {
                            nY11       = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX9,nX10,nX11,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX10,nX11,nY0,nY11,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY0;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 3
                        {
                            nY11       = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX9,nX10,nX11,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX10,nX11,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY1;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
                else
                {
                    if(i<6)
                    {
                        if(i==4)
                        {
                            nY11       = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX9,nX10,nX11,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX10,nX11,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY2;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else // i = 5
                        {
                            nY11       = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            DotMultAdd11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX9,nX10,nX11,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX10,nX11,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY3;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                    else
                    {
                        if(i==6)
                        {
                            nY11       = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            DotMultAdd11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX9,nX10,nX11,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX10,nX11,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY4;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                        else  // i = 7
                        {
                            nY11       = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            nY0        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            nY1        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            nY2        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            nY3        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nY4        = *pYValue++;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                            nY5        = *pYValue;
                            DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                            DotMultAdd11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                            DotMultAdd10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                            DotMultAdd9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                            DotMultAdd8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                            DotMultAdd7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                            DotMultAdd6(nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                            DotMultAdd5(nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                            DotMultAdd4(nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                            DotMultAdd3(nX9,nX10,nX11,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                            DotMultAdd2(nX10,nX11,nY5,nY4,nCarry,nSum,nProd,pZValue);
                            nProd      = nX11*nY5;
                            nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                            *pZValue++ = (DIGIT) nSum;
                            nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                        }
                    }
                }
            }
            else
            {
                if(i<10)
                {
                    if(i==8)
                    {
                        nY11       = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nY5        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nY6        = *pYValue;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        DotMultAdd11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                        DotMultAdd10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                        DotMultAdd9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                        DotMultAdd8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                        DotMultAdd7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX9,nX10,nX11,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX10,nX11,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nProd      = nX11*nY6;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else // i = 9
                    {
                        nY11       = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nY5        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nY6        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        nY7        = *pYValue;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                        DotMultAdd11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                        DotMultAdd10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                        DotMultAdd9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                        DotMultAdd8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX9,nX10,nX11,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX10,nX11,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nProd      = nX11*nY7;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
                else
                {
                    if(i==10)
                    {
                        nY11       = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nY5        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nY6        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        nY7        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                        nY8        = *pYValue;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                        DotMultAdd11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                        DotMultAdd10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                        DotMultAdd9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX9,nX10,nX11,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX10,nX11,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        nProd      = nX11*nY8;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                    else // i = 11
                    {
                        nY11       = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        nY0        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        nY1        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        nY2        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        nY3        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        nY4        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        nY5        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        nY6        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        nY7        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nY8,nCarry,nSum,nProd,pZValue);
                        nY8        = *pYValue++;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nY9,nCarry,nSum,nProd,pZValue);
                        nY9        = *pYValue;
                        DotMultAdd12(nX0,nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nY10,nCarry,nSum,nProd,pZValue);
                        DotMultAdd11(nX1,nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nY11,nCarry,nSum,nProd,pZValue);
                        DotMultAdd10(nX2,nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nY0,nCarry,nSum,nProd,pZValue);
                        DotMultAdd9(nX3,nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nY1,nCarry,nSum,nProd,pZValue);
                        DotMultAdd8(nX4,nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nY2,nCarry,nSum,nProd,pZValue);
                        DotMultAdd7(nX5,nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nY3,nCarry,nSum,nProd,pZValue);
                        DotMultAdd6(nX6,nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nY4,nCarry,nSum,nProd,pZValue);
                        DotMultAdd5(nX7,nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nY5,nCarry,nSum,nProd,pZValue);
                        DotMultAdd4(nX8,nX9,nX10,nX11,nY9,nY8,nY7,nY6,nCarry,nSum,nProd,pZValue);
                        DotMultAdd3(nX9,nX10,nX11,nY9,nY8,nY7,nCarry,nSum,nProd,pZValue);
                        DotMultAdd2(nX10,nX11,nY9,nY8,nCarry,nSum,nProd,pZValue);
                        nProd      = nX11*nY9;
                        nSum       = (nProd&c_nClearHigh)+nCarry+*pZValue;
                        *pZValue++ = (DIGIT) nSum;
                        nCarry     = ((nSum>>_DIGIT_SIZE_IN_BITS) + (nProd>>_DIGIT_SIZE_IN_BITS));
                    }
                }
            }
#endif
        }
        break;
    }
    // final nCarry out
    if(nCarry)
    {
        do
        {
            nSum       = *pZValue+nCarry;
            nCarry     = nSum>>_DIGIT_SIZE_IN_BITS;
            *pZValue++ = (DIGIT) nSum;
        }
        while(nCarry);
    }
}

void CUnsignedArithmeticHelper::MultUStriped(size_t       nXSize,
                                             size_t       nYSize,
                                             const DIGIT  *pX,
                                             const DIGIT  *pY,
                                             DIGIT        *pZ,
                                             bool         bAddInitialZValueToProduct)
{
    size_t i, nXPieceSize;
#if _USEAVX
    nXPieceSize = nXSize%12;
    if(0==nXPieceSize) nXPieceSize = 12;
    switch (nXPieceSize)
    {
    case 4:
        CAVXMultiply::Mult4DigitX(pX, pY, nYSize, pZ, bAddInitialZValueToProduct);
        break;
    case 8:
        CAVXMultiply::Mult8DigitX(pX, pY, nYSize, pZ, bAddInitialZValueToProduct);
        break;
    case 12:
        CAVXMultiply::Mult12DigitX(pX, pY, nYSize, pZ, bAddInitialZValueToProduct);
        break;
    default:
        (bAddInitialZValueToProduct) ? MultAddUShortLong(nXPieceSize, nYSize, pX, pY, pZ) :
                                       MultUShortLong(nXPieceSize, nYSize, pX, pY, pZ);
    }
    if(!bAddInitialZValueToProduct)
    {
        for(i=nXPieceSize+nYSize; i<nXSize+nYSize; i++) pZ[i] = 0; // zero out the rest of Z
    }
    nXSize -= nXPieceSize;
    pX     += nXPieceSize;
    pZ     += nXPieceSize;
    for(i=0; i<nXSize; i += 12)
    {
        CAVXMultiply::Mult12DigitX(pX, pY, nYSize, pZ, true);
        pX += 12;
        pZ += 12;
    }
#else
    // if adding initial value, all calls are to multaddushortlong.  If not, the first
    // call is to multushortlong and the rest to multaddushortlong.  Perf testing shows that
    // multushortlong is faster than multaddushortlong (no surprise there) and that the fewer
    // rows, the bigger the advantage -- so we do the residual rows FIRST.
    nXPieceSize = nXSize%12;
    if(0==nXPieceSize) nXPieceSize = 12;
    if(!bAddInitialZValueToProduct)
    {
        MultUShortLong(nXPieceSize, nYSize, pX, pY, pZ);
        for(i=nXPieceSize+nYSize; i<nXSize+nYSize; i++) pZ[i] = 0; // zero out the rest of Z
    }
    else
    {
        MultAddUShortLong(nXPieceSize, nYSize, pX, pY, pZ);
    }
    nXSize -= nXPieceSize;
    pX     += nXPieceSize;
    pZ     += nXPieceSize;
    for(i=0; i<nXSize; i += 12)
    {
        MultAddUShortLong(12, nYSize, pX, pY, pZ);
        pX += 12;
        pZ += 12;
    }
#endif
}

// Synopsis:	Sets the value of the third operand to
//              the product of the first two operands.  It
//				assumes all the space it needs is properly
//				allocated; it does no error checking.
//				This is an unsigned multiply.  Note that
//				it doesn't check whether the pnWorkspace passed
//				is adequate; it just assumes that is is.
//				(A pnWorkspace at which is four times the size
//				of the larger operand is adequate.)
//
// Arguments:	[pXValue], [pYValue]: numbers to be multiplied
//				[pZValue]: destination of the multiply.
//              [nXSize], [nYSize]: size of x and y, respectively,
//              in DIGITs
//				[pnWorkspace]: pointer to an array of DIGITs;
//				   used as pnWorkspace.  Need not be initialized;
//				   should not contain any data which needs to
//				   persist!
//				Note that unlike the linear ops (addition, subtraction)
//				[]data CANNOT be either of the operands: it starts writing
//				the answer before it is finished reading either operand.
//
// Algorithm:	Consider multiplying 2 2-DOUBLEDIGIT numbers:
//				(a,b)*(y,z) = ay<<2 + by<<1 + az<<1 + bz
//				= ay<<2 + ((a+b)*(y+z)-(ay+bz))<<1 + bz
//				Thus, the large multiply can be done with
//				3 (roughly) half-sized multiplies, plus
//				some linear ops.  Done recursively, this
//				gives assymptotic performance of
//				Theta(n^lg_2(3)), which is substantially
//				better than n^2.
//				In general, for any integer i>0, the
//				problem can be reduced to solving 2i-1
//				subproblems each of 1/i the original size;
//				assymptotically, this gives performance
//				of Theta(n^lg_i(2i-1)).
//				Note that it is also assumed that the first
//				is the smaller operand.  (The check is done
//				in the MultUBackend method.)
//              If the smaller number is much smaller than the
//              larger, the divide-and-conquer doesn't work: in
//              this case, if the larger is at least twice as
//              large as the smaller.  In that case, we do something
//              Different.  Assume that x (the smaller) has n DIGITs.  The
//              problem is broken up as follows:
//              (1) Multiply x by DIGITs 0 to n-1 of y in place (DIGITs 0 to
//                  2n-1 of the answer)
//              (2) Multiply x by DIGITs 2n to 3n-1 of y in place (DIGITs 2n to
//                  4n-1 of the answer)
//              (3) Multiply x by DIGITs n to 2n-1 of y, and add the product
//                  into the answer (DIGITs n through 3n-1)
//              (4) Repeat (2) and (3) with DIGITs 4n to 5n-1 and 3n to 4n-1,
//                  6n to 7n-1 and 5n to 6n-1, etc.
//              (This pattern saves space, and minimizes the amount of carrying
//              necessary.)
//
// History:		Created Feb. 22, 2006
//				Apparently working: June 6, 2006
//				Verified all is well with the procedure: June 13-14, 2006
//              Another glitch repaired: July 27, 2006
//              Rewrote for new calling convention: Aug 22, 2006
//              Converted algorithm for short/long multiply from recursive
//              to iterative: Sept. 6, 2006 (while the recursive code
//              was somewhat simpler, the iterative code takes better
//              advantage of allocated memory -- and the recursive version
//              was getting stack overflows when a 100x20000000 multiply
//              was attempted: too great a call depth)
//
//----------------------------------------------------------

void CUnsignedArithmeticHelper::MultU3by2(size_t             nXSize,
                                          size_t             nYSize,
                                          const DIGIT        *pXValue,
                                          const DIGIT        *pYValue,
                                          DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                                          DIGIT              *pnWorkspace,
                                          DWORD64            &dwTimestamp)
#else
                                          DIGIT              *pnWorkspace)
#endif
{
    size_t      nHalf,i,nUpper;
    DOUBLEDIGIT nSum1,nSum2,nCarry1,nCarry2,nBorrow;
    DIGIT       *pD1,*pD2;
#if(_CollectDetailedTimingData)
    DWORD64     dwBuildTime = dwTimestamp;
    DWORD64     dwProcessTime;
#endif

    nHalf = (nYSize+1)>>1;
    if(nXSize<=nHalf)
    {
        // unbalanced -- can't use this algorithm on the given full problem size
#if(_CollectDetailedTimingData)
        UNBALANCED_MULT(MultU3by2,nXSize,nYSize,pXValue,pYValue,pZValue,pnWorkspace,dwTimestamp,NULL)
#else
        UNBALANCED_MULT(MultU3by2,nXSize,nYSize,pXValue,pYValue,pZValue,pnWorkspace,NULL)
#endif
    }
    else
    {	// compute a+b, y+z (see algorithm notes, above)
        // use the destination(target) to hold these interim
        // values to save space
        nCarry1 = 0;
        nCarry2 = 0;
        pD1     = pZValue;
        pD2     = pZValue+nHalf+1;
        for(i=0;i<nXSize-nHalf;i++)
        {
            nSum1   = nCarry1 + pXValue[i] + pXValue[nHalf+i];
            nSum2   = nCarry2 + pYValue[i] + pYValue[nHalf+i];
            pD1[i]  = (DIGIT) nSum1;
            pD2[i]  = (DIGIT) nSum2;
            nCarry1 = nSum1>>_DIGIT_SIZE_IN_BITS;
            nCarry2 = nSum2>>_DIGIT_SIZE_IN_BITS;
        }
        for(;i<nYSize-nHalf;i++)
        {
            nSum1    = nCarry1 + pXValue[i];
            nSum2    = nCarry2 + pYValue[i] + pYValue[nHalf+i];
            pD1[i]   = (DIGIT) nSum1;
            pD2[i]   = (DIGIT) nSum2;
            nCarry1  = nSum1>>_DIGIT_SIZE_IN_BITS;
            nCarry2  = nSum2>>_DIGIT_SIZE_IN_BITS;
        }
        if(i<nHalf)  // one more DIGIT to take care of
        {
            nSum1    = nCarry1 + pXValue[i];
            nSum2    = nCarry2 + pYValue[i];
            pD1[i]   = (DIGIT) nSum1;
            pD2[i]   = (DIGIT) nSum2;
            nCarry1  = nSum1>>_DIGIT_SIZE_IN_BITS;
            nCarry2  = nSum2>>_DIGIT_SIZE_IN_BITS;
            i++;
        }
        // final carry-out
        pD1[i] = (DIGIT) nCarry1;
        pD2[i] = (DIGIT) nCarry2;
        nUpper = (nHalf+1)<<1;
#if(_CollectDetailedTimingData)
        dwTimestamp          =  s_Timer.GetMicroseconds();
        g_nBuildTimes[e3By2] += dwTimestamp-dwBuildTime;
        g_nMultiplyCalls[e3By2]++;
        // (a+b)*(y+z)
        MultUBackend(nHalf+1, nHalf+1, pD1, pD2, pnWorkspace, pnWorkspace+nUpper, dwTimestamp);
        // a*y
        MultUBackend(nHalf, nHalf, pXValue, pYValue, pZValue, pnWorkspace+nUpper, dwTimestamp);
        // b*z
        MultUBackend(nXSize-nHalf, nYSize-nHalf, pXValue+nHalf, pYValue+nHalf, pZValue+nHalf+nHalf, pnWorkspace+nUpper, dwTimestamp);
#else
        // (a+b)*(y+z)
        MultUBackend(nHalf+1,
                     nHalf+1,
                     pD1,
                     pD2,
                     pnWorkspace,
                     pnWorkspace+nUpper);
        // a*y
        MultUBackend(nHalf,nHalf,pXValue,pYValue,pZValue,pnWorkspace+nUpper);
        // b*z
        MultUBackend(nXSize-nHalf,
                     nYSize-nHalf,
                     pXValue+nHalf,
                     pYValue+nHalf,
                     pZValue+nHalf+nHalf,
                     pnWorkspace+nUpper);
#endif

        // Now: the first "nHalf" of z contains ay; the second,
        // bz; and pnWorkspace contains (a+b)(y+z)
        // Replace (a+b)(y+z) with (a+b)(y+z) - ay - bz

        nBorrow = 0;
        pD1     = pZValue;
        pD2     = pZValue+nHalf+nHalf;
        nUpper  = nXSize+nYSize-(nHalf+nHalf);
        for(i=0;i<nUpper;i++)
        {
            nSum1          =  (nBorrow+pD1[i])+pD2[i];
            nBorrow        =  nSum1>>_DIGIT_SIZE_IN_BITS;
            nSum1          =  nSum1&c_nClearHigh;
            nCarry1        =  pnWorkspace[i];
            nBorrow        += (nSum1>nCarry1);
            pnWorkspace[i] =  (DIGIT) (nCarry1 - nSum1);
        }
        for(;i<nHalf+nHalf;i++)
        {
            nSum1          =  nBorrow+pD1[i];
            nBorrow        =  nSum1>>_DIGIT_SIZE_IN_BITS;
            nSum1          =  nSum1&c_nClearHigh;
            nCarry1        =  pnWorkspace[i];
            nBorrow        += (nSum1>nCarry1);
            pnWorkspace[i] =  (DIGIT) (nCarry1 - nSum1);
        }
        pnWorkspace[i] -= (DIGIT) nBorrow;
        // Finally, add the (a+b)*(y+z)-(ay+bz) piece into the product,
        // with the appropriate shift of course!
        nCarry1 = 0;
        pD1     = pZValue+nHalf;
        nUpper  = nHalf+nHalf+1;  // maximum size of the (a+b)*(y+z)-(ay+bz) piece
        for(i=0;i<nUpper;i++)
        {
            nSum1   = nCarry1 + pnWorkspace[i] + pD1[i];
            nCarry1 = nSum1>>_DIGIT_SIZE_IN_BITS;
            pD1[i]  = (DIGIT) nSum1;
        }
        if(nCarry1)
        {
            do
            {
                nSum1    = nCarry1 + pD1[i];
                nCarry1  = nSum1>>_DIGIT_SIZE_IN_BITS;
                pD1[i++] = (DIGIT) nSum1;
            }
            while(nCarry1);
        }
#if(_CollectDetailedTimingData)
        dwProcessTime          = dwTimestamp;
        dwTimestamp            =  s_Timer.GetMicroseconds();
        g_nProcessTimes[e3By2] += dwTimestamp-dwProcessTime;
#endif
    }
}

// Two choices here: we can compute (a+b)*(a+b) and subtract off a*a and b*b to get 2ab, or
// we can just compute ab directly.  The former is obviously more work up front -- but does
// a square for the subproblem, whereas the latter needs a full multiply.
// If the subproblem is solved using basic multiply, square or multiply -- all the same.
// If 3by2 is called, however, multiply uses 3 half-sized linear ops -- a+b, y+z, and
// (a+b)(y+z) - ay - bz.  Further it calls multiply 3 times on quarter-sized multiplies, etc.
// So:
// Immediate subproblem uses basic:
//    square subproblem: 3 linear ops
//    multiply subproblem: 0 linear ops  <- take this one!
// One level of 3by2:
//    square subproblem: 3 linear ops + 0 linear ops
//    multiply subproblem: 0 linear ops + 3/2 linear ops <- take this one!
// Two levels of 3by2:
//    square subproblem: 3 linear ops + 3/2 linear ops = 18/4 linear ops
//    multiply subproblem: 0 linear ops + 3/2 linear ops + 9/4 linear ops = 15/4 linear ops <- take this one!
// Three levels of 3by2:
//    square subproblem: 3 linear ops + 15/8 linear ops = 39/8 linear ops <- take this one!
//    multiply subproblem: 0 linear ops + 3/2 linear ops + 9/4 linear ops + 27/8 linear ops = 57 linear ops
// So: if the next 3 levels will ALSO use 3By2, we should compute ab using (a+b)^2; otherwise, compute it directly
//
// Practically speaking, the band in which 3by2 is optimal is not wide enough to get that deep a call stack on 3by2
// alone, so I haven't bothered to code up the (a+b)*(a+b) option.
void CUnsignedArithmeticHelper::SquareU3by2(size_t             nXSize,
                                            const DIGIT        *pXValue,
                                            DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                                            DWORD64            &dwTimestamp,
#endif
                                            DIGIT              *pnWorkspace)
{
#if(_CollectDetailedTimingData)
    DWORD64      dwProcessTime;
#endif
    size_t       nHalf,i,nUpper;
    DOUBLEDIGIT  nSum,nCarry,nBorrow;
    DIGIT        *pD1, *pD2;
    nHalf = (nXSize+1)>>1;
#if(_CollectDetailedTimingData)
    // a*b
    MultUBackend(nXSize - nHalf, nHalf, pXValue + nHalf, pXValue, pnWorkspace, pnWorkspace + nXSize, dwTimestamp);
    // a*a
    SquareUBackend(nHalf, pXValue, pZValue, pnWorkspace + nHalf + nHalf + 2, dwTimestamp);
    // b*b
    SquareUBackend(nXSize - nHalf, pXValue + nHalf, pZValue + nHalf + nHalf, pnWorkspace + nHalf + nHalf + 2, dwTimestamp);
#else
    // a*b
    MultUBackend(nXSize-nHalf, nHalf, pXValue+nHalf, pXValue, pnWorkspace, pnWorkspace + nXSize);
    // a*a
    SquareUBackend(nHalf, pXValue, pZValue, pnWorkspace+nHalf+nHalf+2);
    // b*b
    SquareUBackend(nXSize-nHalf, pXValue+nHalf, pZValue+nHalf+nHalf, pnWorkspace+nHalf+nHalf+2);
#endif
    nCarry = 0;
    pD1    = pZValue+nHalf;
    for(i=0;i<nXSize;i++)
    {
        nSum   = nCarry + (((DOUBLEDIGIT) pnWorkspace[i])<<1) + pD1[i];
        nCarry = nSum>>_DIGIT_SIZE_IN_BITS;
        pD1[i] = (DIGIT) nSum;
    }
    if(nCarry)
    {
        do
        {
            nSum     = nCarry + pD1[i];
            nCarry   = nSum>>_DIGIT_SIZE_IN_BITS;
            pD1[i++] = (DIGIT) nSum;
        }
        while(nCarry);
    }
#if(_CollectDetailedTimingData)
    g_nMultiplyCalls[e3By2]++;
    dwProcessTime          =  dwTimestamp;
    dwTimestamp            =  s_Timer.GetMicroseconds();
    g_nProcessTimes[e3By2] += dwTimestamp-dwProcessTime;
#endif
}

// Synopsis:	Performs extended-precision unsigned multiplication
//
// Arguments:	[pXValue], [pYValue]: Numbers to be multiplied
//              [pZValue]: destination for the multiply
//              [nXSize], [nYSize]: The size of x and y, respectively,
//              in Digits
//              [pnWorkspace]: Pointer to pnWorkspace for the multiply
//
// Algorithm:   Suppose we wish to multiply (a,b,c) and (x,y,z)
//              The "digits" of the result are (ignoring some carrying)
//              (ax,ay+bx,az+by+cx,bz+cy,cz) = (p0,p1,p2,pP3,pP4)
//              Let:  r0 = ax
//                    r1 = (a+b+c)(x+y+z)
//                    r2 = (a+2b+4c)(x+2y+4z)
//                    r3 = (a+4b+16c)(x+4y+16z)
//                    r4 = cz
//              Then: p0 = pR0
//                    p1 = (-42r0 + 64r1 - 24r2 + 2r3 - 192r4)/24
//                    p2 = (7r0 - 16r1 + 10r2 - r3 + 112r4)/8
//                    pP3 = (-3r0 + 8r1 - 6r2 + r3 - 168r4)/24
//                    pP4 = r4
//              For comments on the case where the larger operand is "much"
//              larger than the smaller (in this case, at least 3/2 as large),
//              see the 3 by 2 header.
//
//----------------------------------------------------------
//
// 0000
//   1111
//     2222
//       3333
//         4444
// Construct R(0) = P(0), R(4) = P(4) in place
// Construct R(2) in P(2) -- being careful of the (single-digit) overlap with P(0)
// R(1), R(3) in the workspace
// args:
// R(1) args in R(3)
// R(2) args in R(1)
// R(3) args in R(0) (offset 2 digits so as not to be overwritten by R(2) computations) and R(4)
// Compute order: R(2), R(1), R(3), R(0)/R(4)
// Note: Must have P(0) has at least 3 digits above and beyond <third> for argument space:
// must have 2 <= (xSize+ySize) - 5*<third>
// or 3 + 5*third <= xSize+ySize

void CUnsignedArithmeticHelper::MultU5by3(size_t             nXSize,
                                          size_t             nYSize,
                                          const DIGIT        *pXValue,
                                          const DIGIT        *pYValue,
                                          DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                                          DIGIT              *pnWorkspace,
                                          DWORD64            &dwTimestamp)
#else
                                          DIGIT              *pnWorkspace)
#endif
{
    size_t                    nThird;
    int                       i;
    const DIGIT               *pX0,*pX1,*pX2,*pY0,*pY1,*pY2;
    DIGIT                     *pR0,*pR1,*pR2,*pR3,*pR4;
    DOUBLEDIGIT               nSum0,nSum1,nSum2,nSum3,nSum4;
    DOUBLEDIGIT               nBorrow1,nBorrow2,nBorrow3;
    DOUBLEDIGIT               nCarry1,nCarry2,nCarry3;
    DOUBLEDIGIT               nE0,nE1,nE2,nE3,nE4;
    DOUBLEDIGIT               nR0_R2_Overlap;
#if(_CollectDetailedTimingData)
    DWORD64                   dwBuildTime = dwTimestamp;
    DWORD64                   dwProcessTime;
#endif
    nThird = (nYSize+2)/3;
    i      = (nThird<<1);
    if (nXSize <= i || nXSize + nYSize < 3 + 5*nThird)
    {
        if (nXSize == nYSize)
        {
            // too small to be done with this algorithm
#if(_CollectDetailedTimingData)
            MultU3by2(nXSize, nYSize, pXValue, pYValue, pZValue, pnWorkspace, dwTimestamp);
#else
            MultU3by2(nXSize, nYSize, pXValue, pYValue, pZValue, pnWorkspace);
#endif
        }
        else
        {
            // unbalanced -- can't use this algorithm on the given full problem size
#if(_CollectDetailedTimingData)
            UNBALANCED_MULT(MultU5by3, nXSize, nYSize, pXValue, pYValue, pZValue, pnWorkspace, dwTimestamp, NULL)
#else
            UNBALANCED_MULT(MultU5by3, nXSize, nYSize, pXValue, pYValue, pZValue, pnWorkspace, NULL)
#endif
        }
    }
    else
    {
        pX2 = pXValue;
        pX1 = pX2+nThird;
        pX0 = pX1+nThird;
        pY2 = pYValue;
        pY1 = pY2+nThird;
        pY0 = pY1+nThird;
        // Construct operands for the multiplies.  Use z as pnWorkspace
        // to save on memory where possible
        pR0         = pZValue + (nThird<<2) + 2; // +2: temp offset to make R(i) argument construction simpler
        pR1         = pnWorkspace;
        pR2         = pZValue + i;
        pR3         = pR1 + i + 2;
        pR4         = pZValue;
        pnWorkspace = pR3 + i + 2;
        nCarry1     = 0;
        nCarry2     = 0;
        nCarry3     = 0;
        // args:
        // R(1) args in R(3)
        // R(2) args in R(1)
        // R(3) args in R(0) and R(4)
        // Compute order: R(2), R(1), R(3), R(0)/R(4)
        for(i=0;i<nXSize-nThird-nThird;i++)
        {
            nE0     = pX0[i];
            nE1     = pX1[i];
            nE2     = pX2[i];
            nSum1   = nE0+nE1+nE2+nCarry1; // R(1) arg
            pR3[i]  = (DIGIT) nSum1;
            nCarry1 = nSum1>>_DIGIT_SIZE_IN_BITS;
            nSum2   = nE0+(nE1<<1)+(nE2<<2)+nCarry2; // R(2) arg
            pR1[i]  = (DIGIT) nSum2;
            nCarry2 = nSum2>>_DIGIT_SIZE_IN_BITS;
            nSum3   = nE0+(nE1<<2)+(nE2<<4)+nCarry3; // R(3) arg
            pR0[i]  = (DIGIT) nSum3;
            nCarry3 = nSum3>>_DIGIT_SIZE_IN_BITS;
        }
        for(;i<nThird;i++)
        {
            nE1     = pX1[i];
            nE2     = pX2[i];
            nSum1   = nE1+nE2+nCarry1;
            pR3[i]  = (DIGIT) nSum1;
            nCarry1 = nSum1>>_DIGIT_SIZE_IN_BITS;
            nSum2   = (nE1<<1)+(nE2<<2)+nCarry2;
            pR1[i]  = (DIGIT) nSum2;
            nCarry2 = nSum2>>_DIGIT_SIZE_IN_BITS;
            nSum3   = (nE1<<2)+(nE2<<4)+nCarry3;
            pR0[i]  = (DIGIT) nSum3;
            nCarry3 = nSum3>>_DIGIT_SIZE_IN_BITS;
        }
        pR3[i]   =  (DIGIT) nCarry1;
        pR1[i]   =  (DIGIT) nCarry2;
        pR0[i++] =  (DIGIT) nCarry3;
        nCarry1  =  0;
        nCarry2  =  0;
        nCarry3  =  0;
        pR1      += i;
        pR3      += i;
        for(i=0;i<nYSize-(nThird+nThird);i++)
        {
            nE0     = pY0[i];
            nE1     = pY1[i];
            nE2     = pY2[i];
            nSum1   = nE0+nE1+nE2+nCarry1;
            pR3[i]  = (DIGIT) nSum1;
            nCarry1 = nSum1>>_DIGIT_SIZE_IN_BITS;
            nSum2   = nE0+(nE1<<1)+(nE2<<2)+nCarry2;
            pR1[i]  = (DIGIT) nSum2;
            nCarry2 = nSum2>>_DIGIT_SIZE_IN_BITS;
            nSum3   = nE0+(nE1<<2)+(nE2<<4)+nCarry3;
            pR4[i]  = (DIGIT) nSum3;
            nCarry3 = nSum3>>_DIGIT_SIZE_IN_BITS;
        }
        for(;i<nThird;i++)
        {
            nE1     = pY1[i];
            nE2     = pY2[i];
            nSum1   = nE1+nE2+nCarry1;
            pR3[i]  = (DIGIT) nSum1;
            nCarry1 = nSum1>>_DIGIT_SIZE_IN_BITS;
            nSum2   = (nE1<<1)+(nE2<<2)+nCarry2;
            pR1[i]  = (DIGIT) nSum2;
            nCarry2 = nSum2>>_DIGIT_SIZE_IN_BITS;
            nSum3   = (nE1<<2)+(nE2<<4)+nCarry3;
            pR4[i]  = (DIGIT) nSum3;
            nCarry3 = nSum3>>_DIGIT_SIZE_IN_BITS;
        }
        // R(1) args in R(3)
        // R(2) args in R(1)
        // R(3) args in R(0) and R(4)
        // Compute order: R(2), R(1), R(3), R(0)/R(4)
        pR3[i] =  (DIGIT) nCarry1;
        pR1[i] =  (DIGIT) nCarry2;
        pR4[i] =  (DIGIT) nCarry3;
        pR1    -= ++i; // undo twiddle used to make arg computation faster
        pR3    -= i;   // undo twiddle used to make arg computation faster
        i      =  nThird + 1;
#if(_CollectDetailedTimingData)
        dwTimestamp          =  s_Timer.GetMicroseconds();
        g_nBuildTimes[e5By3] += (dwTimestamp-dwBuildTime);
        MultUBackend(i,i,pR1,pR1+i,pR2,pnWorkspace,dwTimestamp);
        nR0_R2_Overlap = pR2[i + i - 2];
        MultUBackend(i,i,pR3,pR3+i,pR1,pnWorkspace,dwTimestamp);
        MultUBackend(i,i,pR0,pR4,pR3,pnWorkspace,dwTimestamp);
        pR0 -= 2; // undo twiddle
        MultUBackend(nXSize-(nThird<<1),nYSize-(nThird<<1),pX0,pY0,pR0,pnWorkspace,dwTimestamp);
        MultUBackend(nThird,nThird,pX2,pY2,pR4,pnWorkspace,dwTimestamp);
        dwProcessTime = dwTimestamp;
#else
        MultUBackend(i, i, pR1, pR1 + i, pR2, pnWorkspace);
        nR0_R2_Overlap = pR2[i + i - 2];
        MultUBackend(i, i, pR3, pR3 + i, pR1, pnWorkspace);
        MultUBackend(i, i, pR0, pR4, pR3, pnWorkspace);
        pR0 -= 2; // undo twiddle
        MultUBackend(nXSize - (nThird<<1), nYSize - (nThird<<1), pX0, pY0, pR0, pnWorkspace);
        MultUBackend(nThird, nThird, pX2, pY2, pR4, pnWorkspace);
#endif
        // At this point, all the multiplies are done.  We just
        // need to combine the results into the final product.
        // Note that P0, P2 and P4 are already in place in the result, and P0 and P2 are complete
        // combine the pRi's to get pP1, pP2, pP3
        nCarry1  = 0;
        nCarry2  = 0;
        nCarry3  = 0;
        nBorrow1 = 0;
        nBorrow2 = 0;
        nBorrow3 = 0;
        for(i=0;i<nXSize+nYSize-(nThird<<2);i++)
        {
            nE0      = pR0[i];
            nE1      = pR1[i];
            nE2      = pR2[i];
            nE3      = pR3[i];
            nE4      = pR4[i];
            nSum0    = (nE1<<6) + (nE3<<1) + nCarry1;
            nSum4    = 42*nE0 + 24*nE2 + 192*nE4 + nBorrow1;
            nBorrow1 = nSum4>>_DIGIT_SIZE_IN_BITS;
            nSum4    = nSum4&c_nClearHigh;
            nCarry1  = nSum0>>_DIGIT_SIZE_IN_BITS;
            nSum0    = nSum0&c_nClearHigh;
            if(nSum4>nSum0)
            {
                nBorrow1++;
                nSum0 += ((DOUBLEDIGIT) 1)<<_DIGIT_SIZE_IN_BITS;
            }
            nSum1    = nSum0-nSum4;
            nSum0    = 7*nE0 + 10*nE2 + 112*nE4 + nCarry2;
            nSum4    = (nE1<<4) + nE3 + nBorrow2;
            nBorrow2 = nSum4>>_DIGIT_SIZE_IN_BITS;
            nSum4    = nSum4&c_nClearHigh;
            nCarry2  = nSum0>>_DIGIT_SIZE_IN_BITS;
            nSum0    = nSum0&c_nClearHigh;
            if(nSum4>nSum0)
            {
                nBorrow2++;
                nSum0 += ((DOUBLEDIGIT) 1)<<_DIGIT_SIZE_IN_BITS;
            }
            nSum2    = nSum0-nSum4;
            nSum0    = (nE1<<3) + nE3 + nCarry3;
            nSum4    = 3*nE0 + 6*nE2 + 168*nE4 + nBorrow3;
            nBorrow3 = nSum4>>_DIGIT_SIZE_IN_BITS;
            nSum4    = nSum4&c_nClearHigh;
            nCarry3  = nSum0>>_DIGIT_SIZE_IN_BITS;
            nSum0    = nSum0&c_nClearHigh;
            if(nSum4>nSum0)
            {
                nBorrow3++;
                nSum0 += ((DOUBLEDIGIT) 1)<<_DIGIT_SIZE_IN_BITS;
            }
            nSum3    = nSum0-nSum4;
            pR1[i]   = (DIGIT) nSum1;
            pR2[i]   = (DIGIT) nSum2;
            pR3[i]   = (DIGIT) nSum3;
        }
        for(;i<nThird<<1;i++)
        {
            nE1      = pR1[i];
            nE2      = pR2[i];
            nE3      = pR3[i];
            nE4      = pR4[i];
            nSum0    = (nE1<<6) + (nE3<<1) + nCarry1;
            nSum4    = 24*nE2 + 192*nE4 + nBorrow1;
            nBorrow1 = nSum4>>_DIGIT_SIZE_IN_BITS;
            nSum4    = nSum4&c_nClearHigh;
            nCarry1  = nSum0>>_DIGIT_SIZE_IN_BITS;
            nSum0    = nSum0&c_nClearHigh;
            if(nSum4>nSum0)
            {
                nBorrow1++;
                nSum0 += ((DOUBLEDIGIT) 1)<<_DIGIT_SIZE_IN_BITS;
            }
            nSum1    = nSum0-nSum4;
            nSum0    = 10*nE2 + 112*nE4 + nCarry2;
            nSum4    = (nE1<<4) + nE3 + nBorrow2;
            nBorrow2 = nSum4>>_DIGIT_SIZE_IN_BITS;
            nSum4    = nSum4&c_nClearHigh;
            nCarry2  = nSum0>>_DIGIT_SIZE_IN_BITS;
            nSum0    = nSum0&c_nClearHigh;
            if(nSum4>nSum0)
            {
                nBorrow2++;
                nSum0 += ((DOUBLEDIGIT) 1)<<_DIGIT_SIZE_IN_BITS;
            }
            nSum2    = nSum0-nSum4;
            nSum0    = (nE1<<3) + nE3 + nCarry3;
            nSum4    = 6*nE2 + 168*nE4 + nBorrow3;
            nBorrow3 = nSum4>>_DIGIT_SIZE_IN_BITS;
            nSum4    = nSum4&c_nClearHigh;
            nCarry3  = nSum0>>_DIGIT_SIZE_IN_BITS;
            nSum0    = nSum0&c_nClearHigh;
            if(nSum4>nSum0)
            {
                nBorrow3++;
                nSum0 += ((DOUBLEDIGIT) 1)<<_DIGIT_SIZE_IN_BITS;
            }
            nSum3    = nSum0-nSum4;
            pR1[i]   = (DIGIT) nSum1;
            pR2[i]   = (DIGIT) nSum2;
            pR3[i]   = (DIGIT) nSum3;
        }
        // last digit, and start division
        nE1            = pR1[i];
        nE3            = pR3[i];
        nSum0          = (nE1<<6) + (nE3<<1) + nCarry1;
        nSum4          = 24*nR0_R2_Overlap + nBorrow1;
        nSum1          = nSum0 - nSum4;
        nSum0          = 10*nR0_R2_Overlap + nCarry2;
        nSum4          = (nE1<<4) + nE3 + nBorrow2;
        nSum2          = nSum0 - nSum4;
        nSum0          = (nE1<<3) + nE3 + nCarry3;
        nSum4          = 6*nR0_R2_Overlap + nBorrow3;
        nSum3          = nSum0 - nSum4;
        // Divisions to get pP1, pP2, pP3 in final form
        nCarry1        = nSum1%24;
        nCarry2        = nSum2&7; // remainder of div by 8
        nCarry3        = nSum3%24;
        pR1[i]         = nSum1/24;
        nR0_R2_Overlap = nSum2>>3;
        pR3[i--]       = nSum3/24;
        for(; 0<=i; i--)
        {
            nSum1    = pR1[i] + (nCarry1<<_DIGIT_SIZE_IN_BITS);
            nSum2    = pR2[i] + (nCarry2<<_DIGIT_SIZE_IN_BITS);
            nSum3    = pR3[i] + (nCarry3<<_DIGIT_SIZE_IN_BITS);
            nE1      = nSum1/24;
            nE2      = nSum2>>3;
            nE3      = nSum3/24;
            nCarry1  = nSum1%24;
            nCarry2  = nSum2&7;
            nCarry3  = nSum3%24;
            pR1[i]   = (DIGIT) nE1;
            pR2[i]   = (DIGIT) nE2;
            pR3[i]   = (DIGIT) nE3;
        }
        // Add P1, P3 into the final product.  Note that
        // P0, P2, and P4 are already in place, with the exception of the P0/P2 overlap digit
        nCarry1 = 0;
        pZValue += nThird; // convenience for master placement
        // add in P3 -- currently in R3
        for(i=0;i<(nThird<<1);i++)
        {
            nSum1      = (nCarry1 + pZValue[i]) + pR3[i];
            nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
            pZValue[i] = (DIGIT) nSum1;
        }
        nCarry1 += pR3[i];
        pZValue += i;
        // add in P1 -- careful about the P0/P2 overlap!
        for(i=0;i<nThird;i++)
        {
            nSum1      = (nCarry1 + pZValue[i]) + pR1[i];
            nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
            pZValue[i] = (DIGIT) nSum1;
        }
        nCarry1 += nR0_R2_Overlap;
        for(;i<=(nThird<<1);i++)
        {
            nSum1      = (nCarry1 + pZValue[i]) + pR1[i];
            nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
            pZValue[i] = (DIGIT) nSum1;
        }
        // note we are guaranteed carry-out won't go past the end of Z, so no need to enforce
        if(nCarry1)
        {
            do
            {
                nSum1        = nCarry1 + pZValue[i];
                nCarry1      = nSum1>>_DIGIT_SIZE_IN_BITS;
                pZValue[i++] = (DIGIT) nSum1;
            }
            while(nCarry1);
        }
#if(_CollectDetailedTimingData)
        g_nMultiplyCalls[e5By3]++;
        dwTimestamp            =  s_Timer.GetMicroseconds();
        g_nProcessTimes[e5By3] += dwTimestamp - dwProcessTime;
#endif
    }
}

void CUnsignedArithmeticHelper::SquareU5by3(size_t             nXSize,
                                            const DIGIT        *pXValue,
                                            DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                                            DWORD64            &dwTimestamp,
#endif
                                            DIGIT              *pnWorkspace)
{
    size_t                    nThird;
    int                       i;
    const DIGIT               *pX0,*pX1,*pX2;
    DIGIT                     *pR0,*pR1,*pR2,*pR3,*pR4;
    DOUBLEDIGIT               nSum0,nSum1,nSum2,nSum3,nSum4;
    DOUBLEDIGIT               nBorrow1,nBorrow2,nBorrow3;
    DOUBLEDIGIT               nCarry1,nCarry2,nCarry3;
    DOUBLEDIGIT               nE0,nE1,nE2,nE3,nE4;
    DOUBLEDIGIT               nR0_R2_Overlap;
#if(_CollectDetailedTimingData)
    DWORD64                   dwBuildTime = dwTimestamp;
    DWORD64                   dwProcessTime;
#endif
    nThird      = (nXSize+2)/3;
    i           = (nThird<<1);
    pX2         = pXValue;
    pX1         = pX2+nThird;
    pX0         = pX1+nThird;
    // Construct operands for the multiplies.  Use z as pnWorkspace
    // to save on memory where possible
    pR0         = pZValue + (nThird<<2);
    pR1         = pnWorkspace;
    pR2         = pZValue + i;
    pR3         = pR1 + i + 2;
    pR4         = pZValue;
    pnWorkspace = pR3 + i + 2;
    nCarry1     = 0;
    nCarry2     = 0;
    nCarry3     = 0;
    // args:
    // R(1) arg in R(3)
    // R(2) arg in R(1)
    // R(3) arg in R(4)
    // Compute order: R(2), R(1), R(3), R(0)/R(4)
    for(i=0;i<nXSize-(nThird<<1);i++)
    {
        nE0     = pX0[i];
        nE1     = pX1[i];
        nE2     = pX2[i];
        nSum1   = nE0+nE1+nE2+nCarry1; // R(1) arg
        pR3[i]  = (DIGIT) nSum1;
        nCarry1 = nSum1>>_DIGIT_SIZE_IN_BITS;
        nSum2   = nE0+(nE1<<1)+(nE2<<2)+nCarry2; // R(2) arg
        pR1[i]  = (DIGIT) nSum2;
        nCarry2 = nSum2>>_DIGIT_SIZE_IN_BITS;
        nSum3   = nE0+(nE1<<2)+(nE2<<4)+nCarry3; // R(3) arg
        pR4[i]  = (DIGIT) nSum3;
        nCarry3 = nSum3>>_DIGIT_SIZE_IN_BITS;
    }
    for(;i<nThird;i++)
    {
        nE1     = pX1[i];
        nE2     = pX2[i];
        nSum1   = nE1+nE2+nCarry1;
        pR3[i]  = (DIGIT) nSum1;
        nCarry1 = nSum1>>_DIGIT_SIZE_IN_BITS;
        nSum2   = (nE1<<1)+(nE2<<2)+nCarry2;
        pR1[i]  = (DIGIT) nSum2;
        nCarry2 = nSum2>>_DIGIT_SIZE_IN_BITS;
        nSum3   = (nE1<<2)+(nE2<<4)+nCarry3;
        pR4[i]  = (DIGIT) nSum3;
        nCarry3 = nSum3>>_DIGIT_SIZE_IN_BITS;
    }
    pR3[i]   =  (DIGIT) nCarry1;
    pR1[i]   =  (DIGIT) nCarry2;
    pR4[i++] =  (DIGIT) nCarry3;
    // R(1) args in R(3)
    // R(2) args in R(1)
    // R(3) args in R(4)
    // Compute order: R(2), R(1), R(3), R(0)/R(4)
#if(_CollectDetailedTimingData)
    dwTimestamp          =  s_Timer.GetMicroseconds();
    g_nBuildTimes[e5By3] += (dwTimestamp-dwBuildTime);
    SquareUBackend(i,pR1,pR2,pnWorkspace,dwTimestamp);
    nR0_R2_Overlap = pR2[i + i - 2];
    SquareUBackend(i,pR3,pR1,pnWorkspace,dwTimestamp);
    SquareUBackend(i,pR4,pR3,pnWorkspace,dwTimestamp);
    SquareUBackend(nXSize-(nThird<<1),pX0,pR0,pnWorkspace,dwTimestamp);
    SquareUBackend(nThird,pX2,pR4,pnWorkspace,dwTimestamp);
    dwProcessTime =  dwTimestamp;
#else
    SquareUBackend(i, pR1, pR2, pnWorkspace);
    nR0_R2_Overlap = pR2[nThird<<1];
    SquareUBackend(i, pR3, pR1, pnWorkspace);
    SquareUBackend(i, pR4, pR3, pnWorkspace);
    SquareUBackend(nXSize - (nThird<<1), pX0, pR0, pnWorkspace);
    SquareUBackend(nThird, pX2, pR4, pnWorkspace);
#endif
    // At this point, all the multiplies are done.  We just
    // need to combine the results into the final product.
    // Note that P0, P2 and P4 are already in place in the result, and P0 and P2 are complete
    // combine the pRi's to get pP1, pP2, pP3
    nCarry1  = 0;
    nCarry2  = 0;
    nCarry3  = 0;
    nBorrow1 = 0;
    nBorrow2 = 0;
    nBorrow3 = 0;
    for(i=0;i<nXSize+nXSize-(nThird<<2);i++)
    {
        nE0      = pR0[i];
        nE1      = pR1[i];
        nE2      = pR2[i];
        nE3      = pR3[i];
        nE4      = pR4[i];
        nSum0    = (nE1<<6) + (nE3<<1) + nCarry1;
        nSum4    = 42*nE0 + 24*nE2 + 192*nE4 + nBorrow1;
        nBorrow1 = nSum4>>_DIGIT_SIZE_IN_BITS;
        nSum4    = nSum4&c_nClearHigh;
        nCarry1  = nSum0>>_DIGIT_SIZE_IN_BITS;
        nSum0    = nSum0&c_nClearHigh;
        if(nSum4>nSum0)
        {
            nBorrow1++;
            nSum0 += ((DOUBLEDIGIT) 1)<<_DIGIT_SIZE_IN_BITS;
        }
        nSum1    = nSum0-nSum4;
        nSum0    = 7*nE0 + 10*nE2 + 112*nE4 + nCarry2;
        nSum4    = (nE1<<4) + nE3 + nBorrow2;
        nBorrow2 = nSum4>>_DIGIT_SIZE_IN_BITS;
        nSum4    = nSum4&c_nClearHigh;
        nCarry2  = nSum0>>_DIGIT_SIZE_IN_BITS;
        nSum0    = nSum0&c_nClearHigh;
        if(nSum4>nSum0)
        {
            nBorrow2++;
            nSum0 += ((DOUBLEDIGIT) 1)<<_DIGIT_SIZE_IN_BITS;
        }
        nSum2    = nSum0-nSum4;
        nSum0    = (nE1<<3) + nE3 + nCarry3;
        nSum4    = 3*nE0 + 6*nE2 + 168*nE4 + nBorrow3;
        nBorrow3 = nSum4>>_DIGIT_SIZE_IN_BITS;
        nSum4    = nSum4&c_nClearHigh;
        nCarry3  = nSum0>>_DIGIT_SIZE_IN_BITS;
        nSum0    = nSum0&c_nClearHigh;
        if(nSum4>nSum0)
        {
            nBorrow3++;
            nSum0 += ((DOUBLEDIGIT) 1)<<_DIGIT_SIZE_IN_BITS;
        }
        nSum3    = nSum0-nSum4;
        pR1[i]   = (DIGIT) nSum1;
        pR2[i]   = (DIGIT) nSum2;
        pR3[i]   = (DIGIT) nSum3;
    }
    for(;i<nThird<<1;i++)
    {
        nE1      = pR1[i];
        nE2      = pR2[i];
        nE3      = pR3[i];
        nE4      = pR4[i];
        nSum0    = (nE1<<6) + (nE3<<1) + nCarry1;
        nSum4    = 24*nE2 + 192*nE4 + nBorrow1;
        nBorrow1 = nSum4>>_DIGIT_SIZE_IN_BITS;
        nSum4    = nSum4&c_nClearHigh;
        nCarry1  = nSum0>>_DIGIT_SIZE_IN_BITS;
        nSum0    = nSum0&c_nClearHigh;
        if(nSum4>nSum0)
        {
            nBorrow1++;
            nSum0 += ((DOUBLEDIGIT) 1)<<_DIGIT_SIZE_IN_BITS;
        }
        nSum1    = nSum0-nSum4;
        nSum0    = 10*nE2 + 112*nE4 + nCarry2;
        nSum4    = (nE1<<4) + nE3 + nBorrow2;
        nBorrow2 = nSum4>>_DIGIT_SIZE_IN_BITS;
        nSum4    = nSum4&c_nClearHigh;
        nCarry2  = nSum0>>_DIGIT_SIZE_IN_BITS;
        nSum0    = nSum0&c_nClearHigh;
        if(nSum4>nSum0)
        {
            nBorrow2++;
            nSum0 += ((DOUBLEDIGIT) 1)<<_DIGIT_SIZE_IN_BITS;
        }
        nSum2    = nSum0-nSum4;
        nSum0    = (nE1<<3) + nE3 + nCarry3;
        nSum4    = 6*nE2 + 168*nE4 + nBorrow3;
        nBorrow3 = nSum4>>_DIGIT_SIZE_IN_BITS;
        nSum4    = nSum4&c_nClearHigh;
        nCarry3  = nSum0>>_DIGIT_SIZE_IN_BITS;
        nSum0    = nSum0&c_nClearHigh;
        if(nSum4>nSum0)
        {
            nBorrow3++;
            nSum0 += ((DOUBLEDIGIT) 1)<<_DIGIT_SIZE_IN_BITS;
        }
        nSum3    = nSum0-nSum4;
        pR1[i]   = (DIGIT) nSum1;
        pR2[i]   = (DIGIT) nSum2;
        pR3[i]   = (DIGIT) nSum3;
    }
    // last digit, and start division
    nE1            = pR1[i];
    nE3            = pR3[i];
    nSum0          = (nE1<<6) + (nE3<<1) + nCarry1;
    nSum4          = 24*nR0_R2_Overlap + nBorrow1;
    nSum1          = nSum0 - nSum4;
    nSum0          = 10*nR0_R2_Overlap + nCarry2;
    nSum4          = (nE1<<4) + nE3 + nBorrow2;
    nSum2          = nSum0 - nSum4;
    nSum0          = (nE1<<3) + nE3 + nCarry3;
    nSum4          = 6*nR0_R2_Overlap + nBorrow3;
    nSum3          = nSum0 - nSum4;
    // Divisions to get pP1, pP2, pP3 in final form
    nCarry1        = nSum1%24;
    nCarry2        = nSum2&7; // remainder of div by 8
    nCarry3        = nSum3%24;
    pR1[i]         = nSum1/24;
    nR0_R2_Overlap = nSum2>>3;
    pR3[i--]       = nSum3/24;
    for(; 0<=i; i--)
    {
        nSum1    = pR1[i] + (nCarry1<<_DIGIT_SIZE_IN_BITS);
        nSum2    = pR2[i] + (nCarry2<<_DIGIT_SIZE_IN_BITS);
        nSum3    = pR3[i] + (nCarry3<<_DIGIT_SIZE_IN_BITS);
        nE1      = nSum1/24;
        nE2      = nSum2>>3;
        nE3      = nSum3/24;
        nCarry1  = nSum1%24;
        nCarry2  = nSum2&7;
        nCarry3  = nSum3%24;
        pR1[i]   = (DIGIT) nE1;
        pR2[i]   = (DIGIT) nE2;
        pR3[i]   = (DIGIT) nE3;
    }
    // Add P1, P3 into the final product.  Note that
    // P0, P2, and P4 are already in place, with the exception of the P0/P2 overlap digit
    nCarry1 = 0;
    pZValue += nThird; // convenience for master placement
    // add in P3 -- currently in R3
    for(i=0;i<(nThird<<1);i++)
    {
        nSum1      = (nCarry1 + pZValue[i]) + pR3[i];
        nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
        pZValue[i] = (DIGIT) nSum1;
    }
    nCarry1 += pR3[i];
    pZValue += i;
    // add in P1 -- careful about the P0/P2 overlap!
    for(i=0;i<nThird;i++)
    {
        nSum1      = (nCarry1 + pZValue[i]) + pR1[i];
        nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
        pZValue[i] = (DIGIT) nSum1;
    }
    nCarry1 += nR0_R2_Overlap;
    for(;i<=(nThird<<1);i++)
    {
        nSum1      = (nCarry1 + pZValue[i]) + pR1[i];
        nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
        pZValue[i] = (DIGIT) nSum1;
    }
    // note we are guaranteed carry-out won't go past the end of Z, so no need to enforce
    if(nCarry1)
    {
        do
        {
            nSum1        = nCarry1 + pZValue[i];
            nCarry1      = nSum1>>_DIGIT_SIZE_IN_BITS;
            pZValue[i++] = (DIGIT) nSum1;
        }
        while(nCarry1);
    }
#if(_CollectDetailedTimingData)
    g_nMultiplyCalls[e5By3]++;
    dwTimestamp            =  s_Timer.GetMicroseconds();
    g_nProcessTimes[e5By3] += dwTimestamp - dwProcessTime;
#endif
}

//+--------------------------------------------------------
//
// Member:		CExtendedPrecisionInteger::MultU7by4, protected
//
// Synopsis:	Performs extended-precision unsigned multiplication
//
// Arguments:	[pY]: amount [this] is to be multiplied by
//              [pz]: destination for the multiply
//              [pworkspace]: Pointer to pnWorkspace for the multiply
//
// Algorithm:   Suppose we wish to multiply (a,b,c,d) and (w,x,y,z)
//              The "digits" of the result are (ignoring some carrying)
//              (ax,ay+bx,az+by+cx,bz+cy,cz) = (pP0,pP1,pP2,pP3,pP4)
//              Let:
//					P0 = aw
//					P1 = ax + bw
//					P2 = ay + bx + cw
//					P3 = az + by + cx + dw
//					P4 =      bz + cy + dx
//					P5 =           cz + dy
//					P6 =                dz
//				The final product is then
//					P6    + P5<<1 + P4<<2 + P3<<3 + P2<<4 + P1<<5 + P0<<6
//				Here, we compute
//					R0 = aw                             = P0
//					R1 = (a+b+c+d)(w+x+y+z)             = P0 + P1  + P2   + P3    + P4    + P5     + pP6
//					R2 = (a+2b+4c+8d)(w+2x+4y+8z)       = P0 + 2P1 + 4P2  + 8P3   + 16P4  + 32P5   + 64P6
//					R3 = (a+3b+9c+27d)(w+3x+9y+27z)     = P0 + 3P1 + 9P2  + 27P3  + 81P4  + 243P5  + 729P6
//					R4 = (a+4b+16c+64d)(w+4x+16y+64z)   = P0 + 4P1 + 16P2 + 64P3  + 256P4 + 1024P5 + 4096P6
//					R5 = (a+5b+25c+125d)(w+5x+25y+125z) = P0 + 5P1 + 25P2 + 125P3 + 625P4 + 3125P5 + 15625P6
//					R6 = dz                             = P6
//				This is a simple system of 7 equations in 7 unknowns; its solution is
//					P0 = R0
//					P1 = (-137R0 + 300R1 - 300R2 + 200R3 - 75R4 + 12R5 -7200R6)/60
//					P2 = (45R0 - 154R1 + 214R2 - 156R3 + 61R4 - 10R5 + 6576R6)/24
//					P3 = (-17R0 + 71R1 - 118R2 + 98R3 - 41R4 + 7R5 - 5400R6)/24
//					P4 = (3R0 - 14R1 + 26R2 - 24R3 + 11R4 - 2R5 + 2040R6)/24
//					P5 = (-R0 + 5R1 - 10R2 + 10R3 - 5R4 + R5 - 1800R6)/120
//					P6 = R6
//              For comments on the case where the larger operand is "much"
//              larger than the smaller (in this case, at least 4/3 as large),
//              see the 3 by 2 header.
//
//----------------------------------------------------------

// 0000
//   1111
//     2222
//       3333
//         4444
//           5555
//             6666
// Compute R0 in P0, R2 in P2, R4 in P4, and R6 in P6.  Need to be careful: P4 overflows into P2 by a digit; P2 overflows into P0 by a like amount
// Note that it is ONLY a digit; while the args are of size (fourth + 1), guaranteed by construction their product is at most (2*fourth +1) digits
// R1, R3, and R5 in the workspace
// args for computing the R(i)s:
// R1 holds args for R2
// R2 (offset 2 digits so not overwritten by R4 computations) holds args for R3
// R3 holds args for R4
// R4 doesn't hold any args
// R5 holds args for R1
// R0 (offset 4 digits so as not to interfere with R2 calculations) and R6 hold args for R5
// Compute order: R4, R3, R2, R1, R5, R0/R6

void CUnsignedArithmeticHelper::MultU7by4(size_t             nXSize,
                                          size_t             nYSize,
                                          const DIGIT        *pXValue,
                                          const DIGIT        *pYValue,
                                          DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                                          DIGIT              *pnWorkspace,
                                          DWORD64            &dwTimestamp) // on entry, time called.  On exit, time completed
#else
                                          DIGIT              *pnWorkspace)
#endif
{
    DIGIT                      *pR0,*pR1,*pR2,*pR3,*pR4,*pR5,*pR6;
    DOUBLEDIGIT                nCarry1,nCarry2,nCarry3,nCarry4,nCarry5;
    DOUBLEDIGIT                nP0_P2_Overlap,nP2_P4_Overlap;
    DOUBLEDIGIT                nSum1,nSum2,nSum3,nSum4,nSum5;
    DOUBLEDIGIT                nBorrow1,nBorrow2,nBorrow3,nBorrow4,nBorrow5;
    DOUBLEDIGIT                nS0,nS1,nS2,nS3,nS4,nS5,nS6;
    size_t                     nFourth,i,j;
#if(_CollectDetailedTimingData)
    DWORD64                    dwProcess;
    DWORD64                    dwBuild = dwTimestamp;
#endif

    nFourth = (nYSize+3)>>2;
    i       = (nFourth<<1);
    if (nXSize <= i || nXSize + nYSize < 5 + 7*nFourth)
    {
        if (nXSize == nYSize)
        {
            // too small to be done with this algorithm
#if(_CollectDetailedTimingData)
            MultU5by3(nXSize, nYSize, pXValue, pYValue, pZValue, pnWorkspace, dwTimestamp);
#else
            MultU5by3(nXSize, nYSize, pXValue, pYValue, pZValue, pnWorkspace);
#endif
        }
        else
        {
            // unbalanced -- can't use this algorithm on the given full problem size
#if(_CollectDetailedTimingData)
            UNBALANCED_MULT(MultU7by4, nXSize, nYSize, pXValue, pYValue, pZValue, pnWorkspace, dwTimestamp, NULL)
#else
            UNBALANCED_MULT(MultU7by4, nXSize, nYSize, pXValue, pYValue, pZValue, pnWorkspace, NULL)
#endif
        }
        return;
    }
    // The full divide-and-conquer method is justified if we get
    // to here
    pR6         =  pZValue;
    pR4         =  pR6 + i;
    i           += 2;
    pR2         =  pR4 + i; // extra offset of 2 to avoid conflict with R4 computations
    pR0         =  pR2 + i; // extra offset of 4 to avoid conflict with R2 computations
    pR5         =  pnWorkspace;
    pR3         =  pR5 + i;
    pR1         =  pR3 + i;
    pnWorkspace =  pR1 + i;
    // Compute the arguments for the sub-multiplications
    nCarry1     = 0;
    nCarry2     = 0;
    nCarry3     = 0;
    nCarry4     = 0;
    nCarry5     = 0;
    nSum1       = 0;
    nSum2       = 0;
    nSum3       = 0;
    nSum4       = 0;
    nSum5       = 0;
    // R1 holds args for R2
    // R2 (offset 2 digits so not overwritten by R4 computations) holds args for R3
    // R3 holds args for R4
    // R4 doesn't hold any args
    // R5 holds args for R1
    // R0 (offset 4 digits so as not to interfere with R2 calculations) and R6 hold args for R5
    // Compute order: R4, R3, R2, R1, R5, R0/R6
    for(i=0;i<nXSize-(nFourth*3);i++)
    {
        nS3      =  pXValue[i];
        nS2      =  pXValue[nFourth+i];
        nS1      =  pXValue[(nFourth<<1)+i];
        nS0      =  pXValue[nFourth*3+i];
        nCarry1  += nS0 + nS1 + nS2 + nS3;
        nCarry2  += nS0 + (nS1<<1) + (nS2<<2) + (nS3<<3);
        nCarry3  += nS0 + 3*nS1 + 9*nS2 + 27*nS3;
        nCarry4  += nS0 + (nS1<<2) + (nS2<<4) + (nS3<<6);
        nCarry5  += nS0 + 5*nS1 + 25*nS2 + 125*nS3;
        pR5[i]   =  (DIGIT) nCarry1;
        pR1[i]   =  (DIGIT) nCarry2;
        pR2[i]   =  (DIGIT) nCarry3;
        pR3[i]   =  (DIGIT) nCarry4;
        pR0[i]   =  (DIGIT) nCarry5;
        nCarry1  =  nCarry1>>_DIGIT_SIZE_IN_BITS;
        nCarry2  =  nCarry2>>_DIGIT_SIZE_IN_BITS;
        nCarry3  =  nCarry3>>_DIGIT_SIZE_IN_BITS;
        nCarry4  =  nCarry4>>_DIGIT_SIZE_IN_BITS;
        nCarry5  =  nCarry5>>_DIGIT_SIZE_IN_BITS;
    }
    for(;i<nFourth;i++)
    {
        nS3      =  pXValue[i];
        nS2      =  pXValue[nFourth+i];
        nS1      =  pXValue[(nFourth<<1)+i];
        nCarry1  += nS1 + nS2 + nS3;
        nCarry2  += (nS1<<1) + (nS2<<2) + (nS3<<3);
        nCarry3  += 3*nS1 + 9*nS2 + 27*nS3;
        nCarry4  += (nS1<<2) + (nS2<<4) + (nS3<<6);
        nCarry5  += 5*nS1 + 25*nS2 + 125*nS3;
        pR5[i]   =  (DIGIT) nCarry1;
        pR1[i]   =  (DIGIT) nCarry2;
        pR2[i]   =  (DIGIT) nCarry3;
        pR3[i]   =  (DIGIT) nCarry4;
        pR0[i]   =  (DIGIT) nCarry5;
        nCarry1  =  nCarry1>>_DIGIT_SIZE_IN_BITS;
        nCarry2  =  nCarry2>>_DIGIT_SIZE_IN_BITS;
        nCarry3  =  nCarry3>>_DIGIT_SIZE_IN_BITS;
        nCarry4  =  nCarry4>>_DIGIT_SIZE_IN_BITS;
        nCarry5  =  nCarry5>>_DIGIT_SIZE_IN_BITS;
    }
    pR5[i]   =  (DIGIT) nCarry1;
    pR1[i]   =  (DIGIT) nCarry2;
    pR2[i]   =  (DIGIT) nCarry3;
    pR3[i]   =  (DIGIT) nCarry4;
    pR0[i++] =  (DIGIT) nCarry5;
    pR5      += i;
    pR1      += i;
    pR2      += i;
    pR3      += i;
    for(i=0;i<nYSize-(nFourth*3);i++)
    {
        nS3    =  pYValue[i];
        nS2    =  pYValue[nFourth+i];
        nS1    =  pYValue[(nFourth<<1)+i];
        nS0    =  pYValue[nFourth*3+i];
        nSum1  += nS0 + nS1 + nS2 + nS3;
        nSum2  += nS0 + (nS1<<1) + (nS2<<2) + (nS3<<3);
        nSum3  += nS0 + 3*nS1 + 9*nS2 + 27*nS3;
        nSum4  += nS0 + (nS1<<2) + (nS2<<4) + (nS3<<6);
        nSum5  += nS0 + 5*nS1 + 25*nS2 + 125*nS3;
        pR5[i] =  (DIGIT) nSum1;
        pR1[i] =  (DIGIT) nSum2;
        pR2[i] =  (DIGIT) nSum3;
        pR3[i] =  (DIGIT) nSum4;
        pR6[i] =  (DIGIT) nSum5;
        nSum1  =  nSum1>>_DIGIT_SIZE_IN_BITS;
        nSum2  =  nSum2>>_DIGIT_SIZE_IN_BITS;
        nSum3  =  nSum3>>_DIGIT_SIZE_IN_BITS;
        nSum4  =  nSum4>>_DIGIT_SIZE_IN_BITS;
        nSum5  =  nSum5>>_DIGIT_SIZE_IN_BITS;
    }
    for(;i<nFourth;i++)
    {
        nS3    =  pYValue[i];
        nS2    =  pYValue[nFourth+i];
        nS1    =  pYValue[(nFourth<<1)+i];
        nSum1  += nS1 + nS2 + nS3;
        nSum2  += (nS1<<1) + (nS2<<2) + (nS3<<3);
        nSum3  += 3*nS1 + 9*nS2 + 27*nS3;
        nSum4  += (nS1<<2) + (nS2<<4) + (nS3<<6);
        nSum5  += 5*nS1 + 25*nS2 + 125*nS3;
        pR5[i] =  (DIGIT) nSum1;
        pR1[i] =  (DIGIT) nSum2;
        pR2[i] =  (DIGIT) nSum3;
        pR3[i] =  (DIGIT) nSum4;
        pR6[i] =  (DIGIT) nSum5;
        nSum1  =  nSum1>>_DIGIT_SIZE_IN_BITS;
        nSum2  =  nSum2>>_DIGIT_SIZE_IN_BITS;
        nSum3  =  nSum3>>_DIGIT_SIZE_IN_BITS;
        nSum4  =  nSum4>>_DIGIT_SIZE_IN_BITS;
        nSum5  =  nSum5>>_DIGIT_SIZE_IN_BITS;
    }
    pR5[i]   =  (DIGIT) nSum1;
    pR1[i]   =  (DIGIT) nSum2;
    pR2[i]   =  (DIGIT) nSum3;
    pR3[i]   =  (DIGIT) nSum4;
    pR6[i++] =  (DIGIT) nSum5;
    pR5      -= i;
    pR1      -= i;
    pR2      -= i;
    pR3      -= i;
    // At this point, we have the operands ready for the sub-multiplies.
    // Care must be taken to do them in the proper order!
    // R1 holds args for R2
    // R2 (offset 2 digits so not overwritten by R4 computations) holds args for R3
    // R3 holds args for R4
    // R4 doesn't hold any args
    // R5 holds args for R1
    // R0 (offset 4 digits so as not to interfere with R2 calculations) and R6 hold args for R5
    // Compute order: R4, R3, R2, R1, R5, R0/R6
#if(_CollectDetailedTimingData)
    dwTimestamp          =  s_Timer.GetMicroseconds();
    g_nBuildTimes[e7By4] += (dwTimestamp - dwBuild);
    MultUBackend(i,i,pR3,pR3+i,pR4,pnWorkspace,dwTimestamp);
    nP2_P4_Overlap = pR4[nFourth<<1]; // save value that will be overwritten when R2 is computed
    MultUBackend(i,i,pR2,pR2+i,pR3,pnWorkspace,dwTimestamp);
    pR2 -= 2; // undo offset
    MultUBackend(i,i,pR1,pR1+i,pR2,pnWorkspace,dwTimestamp);
    nP0_P2_Overlap = pR2[nFourth<<1]; // save value that will be overwritten when R0 is computed
    MultUBackend(i,i,pR5,pR5+i,pR1,pnWorkspace,dwTimestamp);
    MultUBackend(i,i,pR0,pR6,pR5,pnWorkspace,dwTimestamp);
    pR0 -= 4; // undo offset
    MultUBackend(nFourth,nFourth,pXValue,pYValue,pR6,pnWorkspace,dwTimestamp);
    MultUBackend(nXSize-3*nFourth,nYSize-3*nFourth,pXValue+3*nFourth,pYValue+3*nFourth,pR0,pnWorkspace,dwTimestamp);
    dwProcess   = s_Timer.GetMicroseconds();
    dwTimestamp = dwProcess;
#else
    MultUBackend(i,i,pR3,pR3+i,pR4,pnWorkspace);
    nP2_P4_Overlap = pR4[nFourth<<1]; // save value that will be overwritten when R2 is computed
    MultUBackend(i,i,pR2,pR2+i,pR3,pnWorkspace);
    pR2 -= 2; // undo offset
    MultUBackend(i,i,pR1,pR1+i,pR2,pnWorkspace);
    nP0_P2_Overlap = pR2[nFourth<<1]; // save value that will be overwritten when R0 is computed
    MultUBackend(i,i,pR5,pR5+i,pR1,pnWorkspace);
    MultUBackend(i,i,pR0,pR6,pR5,pnWorkspace);
    pR0 -= 4; // undo offset
    MultUBackend(nFourth,nFourth,pXValue,pYValue,pR6,pnWorkspace);
    MultUBackend(nXSize-3*nFourth,
                 nYSize-3*nFourth,
                 pXValue+3*nFourth,
                 pYValue+3*nFourth,
                 pR0,
                 pnWorkspace);
#endif
    // At this point, we have all the r's computed.  Now is the
    // time to use these values to compute the remaining p's.
    // Recall:
    // pP0 = pR0
    // pP1 = (-137R0 + 300R1 - 300R2 + 200R3 - 75R4 + 12R5 -7200R6)/60
    // pP2 = (45R0 - 154R1 + 214R2 - 156R3 + 61R4 - 10R5 + 6576R6)/24
    // pP3 = (-17R0 + 71R1 - 118R2 + 98R3 - 41R4 + 7R5 - 5400R6)/24
    // pP4 = (3R0 - 14R1 + 26R2 - 24R3 + 11R4 - 2R5 + 2040R6)/24
    // pP5 = (-pR0 + 5R1 - 10R2 + 10R3 - 5R4 + pR5 - 1800R6)/120
    // pP6 = pR6
    nBorrow1 = 0;
    nBorrow2 = 0;
    nBorrow3 = 0;
    nBorrow4 = 0;
    nBorrow5 = 0;
    nCarry1  = 0;
    nCarry2  = 0;
    nCarry3  = 0;
    nCarry4  = 0;
    nCarry5  = 0;
    for(i=0;i<nXSize+nYSize-(nFourth*6);i++)
    {
        // pP1 = (-137R0 + 300R1 - 300R2 + 200R3 - 75R4 + 12R5 -7200R6)/60
        // pP2 = (45R0 - 154R1 + 214R2 - 156R3 + 61R4 - 10R5 + 6576R6)/24
        // pP3 = (-17R0 + 71R1 - 118R2 + 98R3 - 41R4 + 7R5 - 5400R6)/24
        // pP4 = (3R0 - 14R1 + 26R2 - 24R3 + 11R4 - 2R5 + 2040R6)/24
        // pP5 = (-pR0 + 5R1 - 10R2 + 10R3 - 5R4 + pR5 - 1800R6)/120
        nS0      =  pR0[i];
        nS1      =  pR1[i];
        nS2      =  pR2[i];
        nS3      =  pR3[i];
        nS4      =  pR4[i];
        nS5      =  pR5[i];
        nS6      =  pR6[i];
        nSum1    =  nCarry1  + 300*nS1 + 200*nS3 + 12*nS5;
        nBorrow1 =  nBorrow1 + 137*nS0 + 300*nS2 + 75*nS4 + 7200*nS6;
        nSum2    =  nCarry2  + 45*nS0  + 214*nS2 + 61*nS4 + 6576*nS6;
        nBorrow2 =  nBorrow2 + 154*nS1 + 156*nS3 + 10*nS5;
        nSum3    =  nCarry3  + 71*nS1  + 98*nS3  + 7*nS5;
        nBorrow3 =  nBorrow3 + 17*nS0  + 118*nS2 + 41*nS4 + 5400*nS6;
        nSum4    =  nCarry4  + 3*nS0   + 26*nS2  + 11*nS4 + 2040*nS6;
        nBorrow4 =  nBorrow4 + 14*nS1  + 24*nS3  + 2*nS5;
        nSum5    =  nCarry5  + 5*nS1   + 10*nS3  + nS5;
        nBorrow5 =  nBorrow5 + nS0     + 10*nS2  + 5*nS4  + 1800*nS6;
        nS0      =  nSum1&c_nClearHigh;
        nCarry1  =  nSum1>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow1&c_nClearHigh;
        nBorrow1 =  nBorrow1>>_DIGIT_SIZE_IN_BITS;
        nBorrow1 += (nS0<nS1);
        pR1[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum2&c_nClearHigh;
        nCarry2  =  nSum2>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow2&c_nClearHigh;
        nBorrow2 =  nBorrow2>>_DIGIT_SIZE_IN_BITS;
        nBorrow2 += (nS0 < nS1);
        pR2[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum3&c_nClearHigh;
        nCarry3  =  nSum3>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow3&c_nClearHigh;
        nBorrow3 =  nBorrow3>>_DIGIT_SIZE_IN_BITS;
        nBorrow3 += (nS0 < nS1);
        pR3[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum4&c_nClearHigh;
        nCarry4  =  nSum4>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow4&c_nClearHigh;
        nBorrow4 =  nBorrow4>>_DIGIT_SIZE_IN_BITS;
        nBorrow4 += (nS0 < nS1);
        pR4[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum5&c_nClearHigh;
        nCarry5  =  nSum5>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow5&c_nClearHigh;
        nBorrow5 =  nBorrow5>>_DIGIT_SIZE_IN_BITS;
        nBorrow5 += (nS0 < nS1);
        pR5[i]   =  (DIGIT) (nS0-nS1);
    }
    for(;i<(nFourth<<1);i++)
    {
        // pP1 = (-137R0 + 300R1 - 300R2 + 200R3 - 75R4 + 12R5 -7200R6)/60
        // pP2 = (45R0 - 154R1 + 214R2 - 156R3 + 61R4 - 10R5 + 6576R6)/24
        // pP3 = (-17R0 + 71R1 - 118R2 + 98R3 - 41R4 + 7R5 - 5400R6)/24
        // pP4 = (3R0 - 14R1 + 26R2 - 24R3 + 11R4 - 2R5 + 2040R6)/24
        // pP5 = (-pR0 + 5R1 - 10R2 + 10R3 - 5R4 + pR5 - 1800R6)/120
        nS1      =  pR1[i];
        nS2      =  pR2[i];
        nS3      =  pR3[i];
        nS4      =  pR4[i];
        nS5      =  pR5[i];
        nS6      =  pR6[i];
        nSum1    =  nCarry1  + 300*nS1 + 200*nS3 + 12*nS5;
        nBorrow1 =  nBorrow1 + 300*nS2 + 75*nS4  + 7200*nS6;
        nSum2    =  nCarry2  + 214*nS2 + 61*nS4  + 6576*nS6;
        nBorrow2 =  nBorrow2 + 154*nS1 + 156*nS3 + 10*nS5;
        nSum3    =  nCarry3  + 71*nS1  + 98*nS3  + 7*nS5;
        nBorrow3 =  nBorrow3 + 118*nS2 + 41*nS4  + 5400*nS6;
        nSum4    =  nCarry4  + 26*nS2  + 11*nS4  + 2040*nS6;
        nBorrow4 =  nBorrow4 + 14*nS1  + 24*nS3  + 2*nS5;
        nSum5    =  nCarry5  + 5*nS1   + 10*nS3  + nS5;
        nBorrow5 =  nBorrow5 + 10*nS2  + 5*nS4   + 1800*nS6;
        nS0      =  nSum1&c_nClearHigh;
        nCarry1  =  nSum1>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow1&c_nClearHigh;
        nBorrow1 =  nBorrow1>>_DIGIT_SIZE_IN_BITS;
        nBorrow1 += (nS0 < nS1);
        pR1[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum2&c_nClearHigh;
        nCarry2  =  nSum2>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow2&c_nClearHigh;
        nBorrow2 =  nBorrow2>>_DIGIT_SIZE_IN_BITS;
        nBorrow2 += (nS0 < nS1);
        pR2[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum3&c_nClearHigh;
        nCarry3  =  nSum3>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow3&c_nClearHigh;
        nBorrow3 =  nBorrow3>>_DIGIT_SIZE_IN_BITS;
        nBorrow3 += (nS0 < nS1);
        pR3[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum4&c_nClearHigh;
        nCarry4  =  nSum4>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow4&c_nClearHigh;
        nBorrow4 =  nBorrow4>>_DIGIT_SIZE_IN_BITS;
        nBorrow4 += (nS0 < nS1);
        pR4[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum5&c_nClearHigh;
        nCarry5  =  nSum5>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow5&c_nClearHigh;
        nBorrow5 =  nBorrow5>>_DIGIT_SIZE_IN_BITS;
        nBorrow5 += (nS0 < nS1);
        pR5[i]   =  (DIGIT) (nS0-nS1);
    }
    // final digit; combine with start the division
    // pP1 = (-137R0 + 300R1 - 300R2 + 200R3 - 75R4 + 12R5 -7200R6)/60
    // pP2 = (45R0 - 154R1 + 214R2 - 156R3 + 61R4 - 10R5 + 6576R6)/24
    // pP3 = (-17R0 + 71R1 - 118R2 + 98R3 - 41R4 + 7R5 - 5400R6)/24
    // pP4 = (3R0 - 14R1 + 26R2 - 24R3 + 11R4 - 2R5 + 2040R6)/24
    // pP5 = (-pR0 + 5R1 - 10R2 + 10R3 - 5R4 + pR5 - 1800R6)/120
    nS1            =  pR1[i];
    nS3            =  pR3[i];
    nS5            =  pR5[i];
    nSum1          =  nCarry1  + 300*nS1 + 200*nS3 + 12*nS5;
    nBorrow1       =  nBorrow1 + 300*nP0_P2_Overlap + 75*nP2_P4_Overlap;
    nSum2          =  nCarry2  + 214*nP0_P2_Overlap + 61*nP2_P4_Overlap;
    nBorrow2       =  nBorrow2 + 154*nS1 + 156*nS3 + 10*nS5;
    nSum3          =  nCarry3  + 71*nS1  + 98*nS3  + 7*nS5;
    nBorrow3       =  nBorrow3 + 118*nP0_P2_Overlap + 41*nP2_P4_Overlap;
    nSum4          =  nCarry4  + 26*nP0_P2_Overlap  + 11*nP2_P4_Overlap;
    nBorrow4       =  nBorrow4 + 14*nS1  + 24*nS3  + 2*nS5;
    nSum5          =  nCarry5  + 5*nS1   + 10*nS3  + nS5;
    nBorrow5       =  nBorrow5 + 10*nP0_P2_Overlap  + 5*nP2_P4_Overlap;
    nS0            = nSum1 - nBorrow1;
    pR1[i]         = nS0/60;
    nCarry1        = nS0%60;
    nS0            = nSum2 - nBorrow2;
    nP0_P2_Overlap = nS0/24;
    nCarry2        = nS0%24;
    nS0            = nSum3 - nBorrow3;
    pR3[i]         = nS0/24;
    nCarry3        = nS0%24;
    nS0            = nSum4 - nBorrow4;
    nP2_P4_Overlap = nS0/24;
    nCarry4        = nS0%24;
    nS0            = nSum5 - nBorrow5;
    pR5[i--]       = nS0/120;
    nCarry5        = nS0%120;

    // Now: do the final divides, and we will have all the p's
    do
    {
        nS0     = pR1[i] + (nCarry1<<_DIGIT_SIZE_IN_BITS);
        pR1[i]  = nS0/60;
        nCarry1 = nS0%60;
        nS0     = pR2[i] + (nCarry2<<_DIGIT_SIZE_IN_BITS);
        pR2[i]  = nS0/24;
        nCarry2 = nS0%24;
        nS0     = pR3[i] + (nCarry3<<_DIGIT_SIZE_IN_BITS);
        pR3[i]  = nS0/24;
        nCarry3 = nS0%24;
        nS0     = pR4[i] + (nCarry4<<_DIGIT_SIZE_IN_BITS);
        pR4[i]  = nS0/24;
        nCarry4 = nS0%24;
        nS0     = pR5[i] + (nCarry5<<_DIGIT_SIZE_IN_BITS);
        pR5[i]  = nS0/120;
        nCarry5 = nS0%120;
    }
    while(i-- != 0);
    // Now, add the p's into place.  Note that P6, P4, P2, and P0
    // are already where they belong (with the caveat of the overlap digits for P2 and P4)
    nCarry1 =  0;
    // add in P5
    pZValue += nFourth; // align with P5
    for(i=0;i<(nFourth<<1);i++)
    {
        nSum1      = pZValue[i] + (pR5[i] + nCarry1);
        pZValue[i] = (DIGIT) nSum1;
        nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
    }
    nCarry1 += pR5[i];
    pZValue += i;
    // add in P3
    for(i=0;i<nFourth;i++)
    {
        nSum1      = pZValue[i] + (pR3[i] + nCarry1);
        pZValue[i] = (DIGIT) nSum1;
        nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
    }
    nCarry1 += nP2_P4_Overlap;
    for(;i<(nFourth<<1);i++)
    {
        nSum1      = pZValue[i] + (pR3[i] + nCarry1);
        pZValue[i] = (DIGIT) nSum1;
        nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
    }
    nCarry1 += pR3[i];
    pZValue += i;
    // add in P1
    for(i=0;i<nFourth;i++)
    {
        nSum1      = pZValue[i] + (pR1[i] + nCarry1);
        pZValue[i] = (DIGIT) nSum1;
        nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
    }
    nCarry1 += nP0_P2_Overlap;
    for(;i<(nFourth<<1)+1;i++)
    {
        nSum1      = pZValue[i] + (pR1[i] + nCarry1);
        pZValue[i] = (DIGIT) nSum1;
        nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
    }
    // note we are guaranteed no carry past Z, so no need to check
    if(nCarry1)
    {
        do
        {
            nSum1        = nCarry1 + pZValue[i];
            pZValue[i++] = (DIGIT) nSum1;
            nCarry1      = nSum1>>_DIGIT_SIZE_IN_BITS;
        }
        while(nCarry1);
    }
#if(_CollectDetailedTimingData)
    dwTimestamp            =  s_Timer.GetMicroseconds();
    g_nProcessTimes[e7By4] += dwTimestamp-dwProcess;
    g_nMultiplyCalls[e7By4]++;
#endif
}

void CUnsignedArithmeticHelper::SquareU7by4(size_t             nXSize,
                                            const DIGIT        *pXValue,
                                            DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                                            DWORD64            &dwTimestamp, // on entry, time called.  On exit, time completed
#endif
                                            DIGIT              *pnWorkspace)
{
    DIGIT                      *pR0,*pR1,*pR2,*pR3,*pR4,*pR5,*pR6;
    DOUBLEDIGIT                nCarry1,nCarry2,nCarry3,nCarry4,nCarry5;
    DOUBLEDIGIT                nP0_P2_Overlap,nP2_P4_Overlap;
    DOUBLEDIGIT                nSum1,nSum2,nSum3,nSum4,nSum5;
    DOUBLEDIGIT                nBorrow1,nBorrow2,nBorrow3,nBorrow4,nBorrow5;
    DOUBLEDIGIT                nS0,nS1,nS2,nS3,nS4,nS5,nS6;
    size_t                     nFourth,i,j;
#if(_CollectDetailedTimingData)
    DWORD64                    dwProcess;
    DWORD64                    dwBuild = dwTimestamp;
#endif

    nFourth     = (nXSize+3)>>2;
    i           = (nFourth<<1);
    pR6         =  pZValue;
    pR4         =  pR6 + i;
    pR2         =  pR4 + i;
    pR0         =  pR2 + i;
    i           += 2;
    pR5         =  pnWorkspace;
    pR3         =  pR5 + i;
    pR1         =  pR3 + i;
    pnWorkspace =  pR1 + i;
    // Compute the arguments for the sub-multiplications
    nCarry1     = 0;
    nCarry2     = 0;
    nCarry3     = 0;
    nCarry4     = 0;
    nCarry5     = 0;
    nSum1       = 0;
    nSum2       = 0;
    nSum3       = 0;
    nSum4       = 0;
    nSum5       = 0;
    // R1 holds arg for R2
    // R2 (offset 2 digits so as not to be twiddled by R4 computations) holds arg for R3
    // R3 holds arg for R4
    // R4 doesn't hold any args
    // R5 holds arg for R1
    // R6 holds arg for R5
    // Compute order: R4, R3, R2, R1, R5, R0/R6
    pR2 += 2;
    for(i=0;i<nXSize-(nFourth*3);i++)
    {
        nS3      =  pXValue[i];
        nS2      =  pXValue[nFourth+i];
        nS1      =  pXValue[(nFourth<<1)+i];
        nS0      =  pXValue[nFourth*3+i];
        nCarry1  += nS0 + nS1 + nS2 + nS3;
        nCarry2  += nS0 + (nS1<<1) + (nS2<<2) + (nS3<<3);
        nCarry3  += nS0 + 3*nS1 + 9*nS2 + 27*nS3;
        nCarry4  += nS0 + (nS1<<2) + (nS2<<4) + (nS3<<6);
        nCarry5  += nS0 + 5*nS1 + 25*nS2 + 125*nS3;
        pR5[i]   =  (DIGIT) nCarry1;
        pR1[i]   =  (DIGIT) nCarry2;
        pR2[i]   =  (DIGIT) nCarry3;
        pR3[i]   =  (DIGIT) nCarry4;
        pR6[i]   =  (DIGIT) nCarry5;
        nCarry1  =  nCarry1>>_DIGIT_SIZE_IN_BITS;
        nCarry2  =  nCarry2>>_DIGIT_SIZE_IN_BITS;
        nCarry3  =  nCarry3>>_DIGIT_SIZE_IN_BITS;
        nCarry4  =  nCarry4>>_DIGIT_SIZE_IN_BITS;
        nCarry5  =  nCarry5>>_DIGIT_SIZE_IN_BITS;
    }
    for(;i<nFourth;i++)
    {
        nS3      =  pXValue[i];
        nS2      =  pXValue[nFourth+i];
        nS1      =  pXValue[(nFourth<<1)+i];
        nCarry1  += nS1 + nS2 + nS3;
        nCarry2  += (nS1<<1) + (nS2<<2) + (nS3<<3);
        nCarry3  += 3*nS1 + 9*nS2 + 27*nS3;
        nCarry4  += (nS1<<2) + (nS2<<4) + (nS3<<6);
        nCarry5  += 5*nS1 + 25*nS2 + 125*nS3;
        pR5[i]   =  (DIGIT) nCarry1;
        pR1[i]   =  (DIGIT) nCarry2;
        pR2[i]   =  (DIGIT) nCarry3;
        pR3[i]   =  (DIGIT) nCarry4;
        pR6[i]   =  (DIGIT) nCarry5;
        nCarry1  =  nCarry1>>_DIGIT_SIZE_IN_BITS;
        nCarry2  =  nCarry2>>_DIGIT_SIZE_IN_BITS;
        nCarry3  =  nCarry3>>_DIGIT_SIZE_IN_BITS;
        nCarry4  =  nCarry4>>_DIGIT_SIZE_IN_BITS;
        nCarry5  =  nCarry5>>_DIGIT_SIZE_IN_BITS;
    }
    pR5[i]   =  (DIGIT) nCarry1;
    pR1[i]   =  (DIGIT) nCarry2;
    pR2[i]   =  (DIGIT) nCarry3;
    pR3[i]   =  (DIGIT) nCarry4;
    pR6[i++] =  (DIGIT) nCarry5;
    // At this point, we have the operands ready for the sub-multiplies.
    // Care must be taken to do them in the proper order!
    // R1 holds args for R2
    // R2 (offset 2 digits so not overwritten by R4 computations) holds args for R3
    // R3 holds args for R4
    // R4 doesn't hold any args
    // R5 holds args for R1
    // R0 (offset 4 digits so as not to interfere with R2 calculations) and R6 hold args for R5
    // Compute order: R4, R3, R2, R1, R5, R0/R6
#if(_CollectDetailedTimingData)
    dwTimestamp          =  s_Timer.GetMicroseconds();
    g_nBuildTimes[e7By4] += (dwTimestamp - dwBuild);
    SquareUBackend(i,pR3,pR4,pnWorkspace,dwTimestamp);
    nP2_P4_Overlap = pR4[nFourth<<1]; // save value that will be overwritten when R2 is computed
    SquareUBackend(i,pR2,pR3,pnWorkspace,dwTimestamp);
    pR2 -= 2; // undo twiddle
    SquareUBackend(i,pR1,pR2,pnWorkspace,dwTimestamp);
    nP0_P2_Overlap = pR2[nFourth<<1]; // save value that will be overwritten when R0 is computed
    SquareUBackend(i,pR5,pR1,pnWorkspace,dwTimestamp);
    SquareUBackend(i,pR6,pR5,pnWorkspace,dwTimestamp);
    SquareUBackend(nFourth,pXValue,pR6,pnWorkspace,dwTimestamp);
    SquareUBackend(nXSize-3*nFourth,pXValue+3*nFourth,pR0,pnWorkspace,dwTimestamp);
    dwProcess   = s_Timer.GetMicroseconds();
    dwTimestamp = dwProcess;
#else
    SquareUBackend(i,pR3,pR4,pnWorkspace);
    nP2_P4_Overlap = pR4[nFourth<<1]; // save value that will be overwritten when R2 is computed
    SquareUBackend(i,pR2,pR3,pnWorkspace);
    pR2 -= 2; // undo twiddle
    SquareUBackend(i,pR1,pR2,pnWorkspace);
    nP0_P2_Overlap = pR2[nFourth<<1]; // save value that will be overwritten when R0 is computed
    SquareUBackend(i,pR5,pR1,pnWorkspace);
    SquareUBackend(i,pR6,pR5,pnWorkspace);
    SquareUBackend(nFourth,pXValue,pR6,pnWorkspace);
    SquareUBackend(nXSize-3*nFourth,
                   pXValue+3*nFourth,
                   pR0,
                   pnWorkspace);
#endif
    // At this point, we have all the r's computed.  Now is the
    // time to use these values to compute the remaining p's.
    // Recall:
    // pP0 = pR0
    // pP1 = (-137R0 + 300R1 - 300R2 + 200R3 - 75R4 + 12R5 -7200R6)/60
    // pP2 = (45R0 - 154R1 + 214R2 - 156R3 + 61R4 - 10R5 + 6576R6)/24
    // pP3 = (-17R0 + 71R1 - 118R2 + 98R3 - 41R4 + 7R5 - 5400R6)/24
    // pP4 = (3R0 - 14R1 + 26R2 - 24R3 + 11R4 - 2R5 + 2040R6)/24
    // pP5 = (-pR0 + 5R1 - 10R2 + 10R3 - 5R4 + pR5 - 1800R6)/120
    // pP6 = pR6
    nBorrow1 = 0;
    nBorrow2 = 0;
    nBorrow3 = 0;
    nBorrow4 = 0;
    nBorrow5 = 0;
    nCarry1  = 0;
    nCarry2  = 0;
    nCarry3  = 0;
    nCarry4  = 0;
    nCarry5  = 0;
    for(i=0;i<nXSize+nXSize-(nFourth*6);i++)
    {
        // pP1 = (-137R0 + 300R1 - 300R2 + 200R3 - 75R4 + 12R5 -7200R6)/60
        // pP2 = (45R0 - 154R1 + 214R2 - 156R3 + 61R4 - 10R5 + 6576R6)/24
        // pP3 = (-17R0 + 71R1 - 118R2 + 98R3 - 41R4 + 7R5 - 5400R6)/24
        // pP4 = (3R0 - 14R1 + 26R2 - 24R3 + 11R4 - 2R5 + 2040R6)/24
        // pP5 = (-pR0 + 5R1 - 10R2 + 10R3 - 5R4 + pR5 - 1800R6)/120
        nS0      =  pR0[i];
        nS1      =  pR1[i];
        nS2      =  pR2[i];
        nS3      =  pR3[i];
        nS4      =  pR4[i];
        nS5      =  pR5[i];
        nS6      =  pR6[i];
        nSum1    =  nCarry1  + 300*nS1 + 200*nS3 + 12*nS5;
        nBorrow1 =  nBorrow1 + 137*nS0 + 300*nS2 + 75*nS4 + 7200*nS6;
        nSum2    =  nCarry2  + 45*nS0  + 214*nS2 + 61*nS4 + 6576*nS6;
        nBorrow2 =  nBorrow2 + 154*nS1 + 156*nS3 + 10*nS5;
        nSum3    =  nCarry3  + 71*nS1  + 98*nS3  + 7*nS5;
        nBorrow3 =  nBorrow3 + 17*nS0  + 118*nS2 + 41*nS4 + 5400*nS6;
        nSum4    =  nCarry4  + 3*nS0   + 26*nS2  + 11*nS4 + 2040*nS6;
        nBorrow4 =  nBorrow4 + 14*nS1  + 24*nS3  + 2*nS5;
        nSum5    =  nCarry5  + 5*nS1   + 10*nS3  + nS5;
        nBorrow5 =  nBorrow5 + nS0     + 10*nS2  + 5*nS4  + 1800*nS6;
        nS0      =  nSum1&c_nClearHigh;
        nCarry1  =  nSum1>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow1&c_nClearHigh;
        nBorrow1 =  nBorrow1>>_DIGIT_SIZE_IN_BITS;
        nBorrow1 += (nS0<nS1);
        pR1[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum2&c_nClearHigh;
        nCarry2  =  nSum2>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow2&c_nClearHigh;
        nBorrow2 =  nBorrow2>>_DIGIT_SIZE_IN_BITS;
        nBorrow2 += (nS0 < nS1);
        pR2[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum3&c_nClearHigh;
        nCarry3  =  nSum3>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow3&c_nClearHigh;
        nBorrow3 =  nBorrow3>>_DIGIT_SIZE_IN_BITS;
        nBorrow3 += (nS0 < nS1);
        pR3[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum4&c_nClearHigh;
        nCarry4  =  nSum4>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow4&c_nClearHigh;
        nBorrow4 =  nBorrow4>>_DIGIT_SIZE_IN_BITS;
        nBorrow4 += (nS0 < nS1);
        pR4[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum5&c_nClearHigh;
        nCarry5  =  nSum5>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow5&c_nClearHigh;
        nBorrow5 =  nBorrow5>>_DIGIT_SIZE_IN_BITS;
        nBorrow5 += (nS0 < nS1);
        pR5[i]   =  (DIGIT) (nS0-nS1);
    }
    for(;i<(nFourth<<1);i++)
    {
        // pP1 = (-137R0 + 300R1 - 300R2 + 200R3 - 75R4 + 12R5 -7200R6)/60
        // pP2 = (45R0 - 154R1 + 214R2 - 156R3 + 61R4 - 10R5 + 6576R6)/24
        // pP3 = (-17R0 + 71R1 - 118R2 + 98R3 - 41R4 + 7R5 - 5400R6)/24
        // pP4 = (3R0 - 14R1 + 26R2 - 24R3 + 11R4 - 2R5 + 2040R6)/24
        // pP5 = (-pR0 + 5R1 - 10R2 + 10R3 - 5R4 + pR5 - 1800R6)/120
        nS1      =  pR1[i];
        nS2      =  pR2[i];
        nS3      =  pR3[i];
        nS4      =  pR4[i];
        nS5      =  pR5[i];
        nS6      =  pR6[i];
        nSum1    =  nCarry1  + 300*nS1 + 200*nS3 + 12*nS5;
        nBorrow1 =  nBorrow1 + 300*nS2 + 75*nS4  + 7200*nS6;
        nSum2    =  nCarry2  + 214*nS2 + 61*nS4  + 6576*nS6;
        nBorrow2 =  nBorrow2 + 154*nS1 + 156*nS3 + 10*nS5;
        nSum3    =  nCarry3  + 71*nS1  + 98*nS3  + 7*nS5;
        nBorrow3 =  nBorrow3 + 118*nS2 + 41*nS4  + 5400*nS6;
        nSum4    =  nCarry4  + 26*nS2  + 11*nS4  + 2040*nS6;
        nBorrow4 =  nBorrow4 + 14*nS1  + 24*nS3  + 2*nS5;
        nSum5    =  nCarry5  + 5*nS1   + 10*nS3  + nS5;
        nBorrow5 =  nBorrow5 + 10*nS2  + 5*nS4   + 1800*nS6;
        nS0      =  nSum1&c_nClearHigh;
        nCarry1  =  nSum1>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow1&c_nClearHigh;
        nBorrow1 =  nBorrow1>>_DIGIT_SIZE_IN_BITS;
        nBorrow1 += (nS0 < nS1);
        pR1[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum2&c_nClearHigh;
        nCarry2  =  nSum2>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow2&c_nClearHigh;
        nBorrow2 =  nBorrow2>>_DIGIT_SIZE_IN_BITS;
        nBorrow2 += (nS0 < nS1);
        pR2[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum3&c_nClearHigh;
        nCarry3  =  nSum3>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow3&c_nClearHigh;
        nBorrow3 =  nBorrow3>>_DIGIT_SIZE_IN_BITS;
        nBorrow3 += (nS0 < nS1);
        pR3[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum4&c_nClearHigh;
        nCarry4  =  nSum4>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow4&c_nClearHigh;
        nBorrow4 =  nBorrow4>>_DIGIT_SIZE_IN_BITS;
        nBorrow4 += (nS0 < nS1);
        pR4[i]   =  (DIGIT) (nS0-nS1);
        nS0      =  nSum5&c_nClearHigh;
        nCarry5  =  nSum5>>_DIGIT_SIZE_IN_BITS;
        nS1      =  nBorrow5&c_nClearHigh;
        nBorrow5 =  nBorrow5>>_DIGIT_SIZE_IN_BITS;
        nBorrow5 += (nS0 < nS1);
        pR5[i]   =  (DIGIT) (nS0-nS1);
    }
    // final digit; combine with start the division
    // pP1 = (-137R0 + 300R1 - 300R2 + 200R3 - 75R4 + 12R5 -7200R6)/60
    // pP2 = (45R0 - 154R1 + 214R2 - 156R3 + 61R4 - 10R5 + 6576R6)/24
    // pP3 = (-17R0 + 71R1 - 118R2 + 98R3 - 41R4 + 7R5 - 5400R6)/24
    // pP4 = (3R0 - 14R1 + 26R2 - 24R3 + 11R4 - 2R5 + 2040R6)/24
    // pP5 = (-pR0 + 5R1 - 10R2 + 10R3 - 5R4 + pR5 - 1800R6)/120
    nS1            =  pR1[i];
    nS3            =  pR3[i];
    nS5            =  pR5[i];
    nSum1          =  nCarry1  + 300*nS1 + 200*nS3 + 12*nS5;
    nBorrow1       =  nBorrow1 + 300*nP0_P2_Overlap + 75*nP2_P4_Overlap;
    nSum2          =  nCarry2  + 214*nP0_P2_Overlap + 61*nP2_P4_Overlap;
    nBorrow2       =  nBorrow2 + 154*nS1 + 156*nS3 + 10*nS5;
    nSum3          =  nCarry3  + 71*nS1  + 98*nS3  + 7*nS5;
    nBorrow3       =  nBorrow3 + 118*nP0_P2_Overlap + 41*nP2_P4_Overlap;
    nSum4          =  nCarry4  + 26*nP0_P2_Overlap  + 11*nP2_P4_Overlap;
    nBorrow4       =  nBorrow4 + 14*nS1  + 24*nS3  + 2*nS5;
    nSum5          =  nCarry5  + 5*nS1   + 10*nS3  + nS5;
    nBorrow5       =  nBorrow5 + 10*nP0_P2_Overlap  + 5*nP2_P4_Overlap;
    nS0            = nSum1 - nBorrow1;
    pR1[i]         = nS0/60;
    nCarry1        = nS0%60;
    nS0            = nSum2 - nBorrow2;
    nP0_P2_Overlap = nS0/24;
    nCarry2        = nS0%24;
    nS0            = nSum3 - nBorrow3;
    pR3[i]         = nS0/24;
    nCarry3        = nS0%24;
    nS0            = nSum4 - nBorrow4;
    nP2_P4_Overlap = nS0/24;
    nCarry4        = nS0%24;
    nS0            = nSum5 - nBorrow5;
    pR5[i--]       = nS0/120;
    nCarry5        = nS0%120;

    // Now: do the final divides, and we will have all the p's
    do
    {
        nS0     = pR1[i] + (nCarry1<<_DIGIT_SIZE_IN_BITS);
        pR1[i]  = nS0/60;
        nCarry1 = nS0%60;
        nS0     = pR2[i] + (nCarry2<<_DIGIT_SIZE_IN_BITS);
        pR2[i]  = nS0/24;
        nCarry2 = nS0%24;
        nS0     = pR3[i] + (nCarry3<<_DIGIT_SIZE_IN_BITS);
        pR3[i]  = nS0/24;
        nCarry3 = nS0%24;
        nS0     = pR4[i] + (nCarry4<<_DIGIT_SIZE_IN_BITS);
        pR4[i]  = nS0/24;
        nCarry4 = nS0%24;
        nS0     = pR5[i] + (nCarry5<<_DIGIT_SIZE_IN_BITS);
        pR5[i]  = nS0/120;
        nCarry5 = nS0%120;
    }
    while(i-- != 0);
    // Now, add the p's into place.  Note that P6, P4, P2, and P0
    // are already where they belong (with the caveat of the overlap digits for P2 and P4)
    nCarry1 =  0;
    // add in P5
    pZValue += nFourth; // align with P5
    for(i=0;i<(nFourth<<1);i++)
    {
        nSum1      = pZValue[i] + (pR5[i] + nCarry1);
        pZValue[i] = (DIGIT) nSum1;
        nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
    }
    nCarry1 += pR5[i];
    pZValue += i;
    // add in P3
    for(i=0;i<nFourth;i++)
    {
        nSum1      = pZValue[i] + (pR3[i] + nCarry1);
        pZValue[i] = (DIGIT) nSum1;
        nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
    }
    nCarry1 += nP2_P4_Overlap;
    for(;i<(nFourth<<1);i++)
    {
        nSum1      = pZValue[i] + (pR3[i] + nCarry1);
        pZValue[i] = (DIGIT) nSum1;
        nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
    }
    nCarry1 += pR3[i];
    pZValue += i;
    // add in P1
    for(i=0;i<nFourth;i++)
    {
        nSum1      = pZValue[i] + (pR1[i] + nCarry1);
        pZValue[i] = (DIGIT) nSum1;
        nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
    }
    nCarry1 += nP0_P2_Overlap;
    for(;i<(nFourth<<1)+1;i++)
    {
        nSum1      = pZValue[i] + (pR1[i] + nCarry1);
        pZValue[i] = (DIGIT) nSum1;
        nCarry1    = nSum1>>_DIGIT_SIZE_IN_BITS;
    }
    // note we are guaranteed no carry past Z, so no need to check
    if(nCarry1)
    {
        do
        {
            nSum1        = nCarry1 + pZValue[i];
            pZValue[i++] = (DIGIT) nSum1;
            nCarry1      = nSum1>>_DIGIT_SIZE_IN_BITS;
        }
        while(nCarry1);
    }
#if(_CollectDetailedTimingData)
    dwTimestamp            =  s_Timer.GetMicroseconds();
    g_nProcessTimes[e7By4] += dwTimestamp-dwProcess;
    g_nMultiplyCalls[e7By4]++;
#endif
}

#if(32<=_DIGIT_SIZE_IN_BITS)
// For 9 by 5, the system of equations for multiplying (x0, x1, x2, x3, x4) by (y0, y1, y2, y3, y4) is
// R0 =  x0                               * y0
// R1 = (x0 +  x1 +   x2 +    x3 +     x4)*(y0 +  y1 +   y2 +    y3 +     y4)
// R2 = (x0 + 2x1 +  4x2 +   8x3 +   16x4)*(y0 + 2y1 +  4y2 +   8y3 +   16y4)
// R3 = (x0 + 3x1 +  9x2 +  27x3 +   81x4)*(y0 + 3y1 +  9y2 +  27y3 +   81y4)
// R4 = (x0 + 4x1 + 16x2 +  64x3 +  256x4)*(y0 + 4y1 + 16y2 +  64y3 +  256y4)
// R5 = (x0 + 5x1 + 25x2 + 125x3 +  625x4)*(y0 + 5y1 + 25y2 + 125y3 +  625y4)
// R6 = (x0 + 6x1 + 36x2 + 216x3 + 1296x4)*(y0 + 6y1 + 36y2 + 216y3 + 1296y4)
// R7 = (x0 + 7x1 + 49x2 + 343x3 + 2401x4)*(y0 + 7y1 + 49y2 + 343y3 + 2401y4)
// R8 =                                x4 *                               y4
// and the P(i)s are
// P0 = R0
// P1 = (-1089R0 + 2940R1 -  4410R2 +  4900R3 -  3675R4 + 1764R5 -  490R6 +  60R7 - 2116800R8)/420
// P2 = (  938R0 - 4014R1 +  7911R2 -  9490R3 +  7380R4 - 3618R5 + 1019R6 - 126R7 + 4704480R8)/360
// P3 = ( -967R0 + 5104R1 - 11787R2 + 15560R3 - 12725R4 + 6432R5 - 1849R6 + 232R7 - 9455040R8)/720
// P4 = (   56R0 -  333R1 +   852R2 -  1219R3 +  1056R4 -  555R5 +  164R6 -  21R7 +  974736R8)/144
// P5 = (  -46R0 +  295R1 -   810R2 +  1235R3 -  1130R4 +  621R5 -  190R6 +  25R7 - 1411200R8)/720
// P6 = (    4R0 -   27R1 +    78R2 -   125R3 +   120R4 -   69R5 +   22R6 -   3R7 +  231840R8)/720
// P7 = (    -R0 +    7R1 -    21R2 +    35R3 -    35R4 +   21R5 -    7R6 +    R7 -  141120R8)/5040
// P8 = R8
// Now, it is obvious some of these coefficients won't fit in a 16-bit value.  So the 9 by 5 is
// only defined with larger DIGIT size.
// assume Y has at least as many digits as X (not checked)
// overlap for 9 by 5 multiply:
// 0000
//   1111
//     2222
//       3333
//         4444
//           5555
//             6666
//               7777
//                 8888
// To save on memory: compute P0, P2, P4, P6, and P8 in place.  Others on the stack.  Note that P2, P4, and P6 might have 1 extra digit of carry past their
// alotted slots; need to keep track of the digit of overlap when computing.
// For further memory optimization: don't need the arguments for the recursive multiplies after the multiply, so can store these operands
// in the P(i) space -- just need to be careful of the order the multiplies are done in.
// Store R(i) in the space allocated for P(i)
// P0, P8: hold arguments for computing R(5)
// P1: holds arguments for P6
// P2 (offset to leave space for arguments not-quite-held in P4) holds arguments for P3
// P3 holds arguments for P4
// P4 (offset to leave space for arguments not-quite-held in P6) holds arguments for P1
// P5 holds arguments for P2
// P6 holds arguments for P7
//
// P0 and P8 read their arguments directly from X and Y: no need to store them separately
// So: compute P7, then P6, then P1, then P4 (being careful to save the overlap digit of P6), then P3, then P2 (saving overlap
// digit with P4), then P5, the P8 and P0
//
// Memory needed: 8*(1 + (ysize+4)/5) to store P1, P3, P5, and P7 on the stack, plus whatever workspace needed for the recursive multiplies: 2*ysize plenty
// Since we need to fit in (1 + (ysize+4)/5) starting 6 digits in to the P0 slot, we must have xsize + ysize - 8*((ysize+4)/5) is at least (7 + (ysize+4)/5)
// So 7 + 9*((ysize+4)/5) <= xsize + ysize
//
void CUnsignedArithmeticHelper::MultU9by5(size_t             nXSize,
                                          size_t             nYSize,
                                          const DIGIT        *pXValue,
                                          const DIGIT        *pYValue,
                                          DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                                          DIGIT              *pnWorkspace,
                                          DWORD64            &dwTimestamp) // on entry, time called.  On exit, time completed
#else
                                          DIGIT              *pnWorkspace)
#endif
{
    DOUBLEDIGIT  x0, x1, x2, x3, x4, y0, y1, y2, y3, y4, nAdd, nSub, nCarry1, nCarry2, nCarry3, nCarry4, nCarry5, nCarry6, nCarry7, nBorrow1, nBorrow2, nBorrow3, nBorrow4, nBorrow5, nBorrow6, nBorrow7;
    DOUBLEDIGIT  nP0_P2_overlap, nP2_P4_overlap, nP4_P6_overlap, nR0, nR1, nR2, nR3, nR4, nR5, nR6, nR7, nR8;
    unsigned int i, nResidual;
    size_t       nFifth = (nYSize + 4)/5;
#if(_CollectDetailedTimingData)
    DWORD64 dwProcessTime, dwBuildTime = dwTimestamp;
#endif
    // check to make sure x, y big enough for the method!
    if((nFifth<<2)>=nXSize || nXSize + nYSize < 7 + 9*nFifth)  // Too few digits in the smaller number to use the normal technique
    {
        if(nXSize == nYSize)
        {
            // too small to do with this algorithm
#if(_CollectDetailedTimingData)
            MultU7by4(nXSize, nYSize, pXValue, pYValue, pZValue, pnWorkspace, dwTimestamp);
#else
            MultU7by4(nXSize, nYSize, pXValue, pYValue, pZValue, pnWorkspace);
#endif
        }
        else
        {
            // unbalanced -- can't use this algorithm on the given full problem size
#if(_CollectDetailedTimingData)
            UNBALANCED_MULT(MultU9by5, nXSize, nYSize, pXValue, pYValue, pZValue, pnWorkspace, dwTimestamp, NULL)
#else
            UNBALANCED_MULT(MultU9by5, nXSize, nYSize, pXValue, pYValue, pZValue, pnWorkspace, NULL)
#endif
        }
        return;
    }
    DIGIT       *pR0    = pZValue + (nFifth<<3);
    DIGIT       *pR1    = pnWorkspace;
    DIGIT       *pR2    = pZValue + (nFifth*6);
    DIGIT       *pR3    = pR1     + ((nFifth+1)<<1);
    DIGIT       *pR4    = pZValue + (nFifth<<2);
    DIGIT       *pR5    = pR3     + ((nFifth+1)<<1);
    DIGIT       *pR6    = pZValue + (nFifth<<1);
    DIGIT       *pR7    = pR5     + ((nFifth+1)<<1);
    DIGIT       *pR8    = pZValue;
    const DIGIT *pX4    = pXValue;
    const DIGIT *pX3    = pX4 + nFifth;
    const DIGIT *pX2    = pX3 + nFifth;
    const DIGIT *pX1    = pX2 + nFifth;
    const DIGIT *pX0    = pX1 + nFifth;
    const DIGIT *pY4    = pYValue;
    const DIGIT *pY3    = pY4 + nFifth;
    const DIGIT *pY2    = pY3 + nFifth;
    const DIGIT *pY1    = pY2 + nFifth;
    const DIGIT *pY0    = pY1 + nFifth;
    // P0, P8: hold arguments for computing R(5)
    // P1: holds arguments for P6
    // P2 (offset to leave space for arguments not-quite-held in P4) holds arguments for P3
    // P3 holds arguments for P4
    // P4 (offset to leave space for arguments not-quite-held in P6) holds arguments for P1
    // P5 holds arguments for P2
    // P6 holds arguments for P7
    DIGIT       *pArgR1 = pR4 + 2;
    DIGIT       *pArgR2 = pR5;
    DIGIT       *pArgR3 = pR2 + 4;
    DIGIT       *pArgR4 = pR3;
    DIGIT       *pArgR5 = pR0 + 6;
    DIGIT       *pArgR6 = pR1;
    DIGIT       *pArgR7 = pR6;
    pnWorkspace = pR7 + ((nFifth+1)<<1);
    // arguments for R1 - R7.  Recall
    // R1 = (x0 +  x1 +   x2 +    x3 +     x4)*(y0 +  y1 +   y2 +    y3 +     y4)
    // R2 = (x0 + 2x1 +  4x2 +   8x3 +   16x4)*(y0 + 2y1 +  4y2 +   8y3 +   16y4)
    // R3 = (x0 + 3x1 +  9x2 +  27x3 +   81x4)*(y0 + 3y1 +  9y2 +  27y3 +   81y4)
    // R4 = (x0 + 4x1 + 16x2 +  64x3 +  256x4)*(y0 + 4y1 + 16y2 +  64y3 +  256y4)
    // R5 = (x0 + 5x1 + 25x2 + 125x3 +  625x4)*(y0 + 5y1 + 25y2 + 125y3 +  625y4)
    // R6 = (x0 + 6x1 + 36x2 + 216x3 + 1296x4)*(y0 + 6y1 + 36y2 + 216y3 + 1296y4)
    // R7 = (x0 + 7x1 + 49x2 + 343x3 + 2401x4)*(y0 + 7y1 + 49y2 + 343y3 + 2401y4)
    nCarry1   = 0;
    nCarry2   = 0;
    nCarry3   = 0;
    nCarry4   = 0;
    nCarry5   = 0;
    nCarry6   = 0;
    nCarry7   = 0;
    nResidual = nXSize - (nFifth<<2);
    for(i=0; i<nResidual; i++)
    {
        DOUBLEDIGIT n0   = pX0[i];
        DOUBLEDIGIT n1   = pX1[i];
        DOUBLEDIGIT n2   = pX2[i];
        DOUBLEDIGIT n3   = pX3[i];
        DOUBLEDIGIT n4   = pX4[i];
        DOUBLEDIGIT nAdd = n0 + n1 + n2 + n3 + n4 + nCarry1; // R1
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
        nAdd      = n0 + (n1<<1) + (n2<<2) + (n3<<3) + (n4<<4) + nCarry2; // R2
        nCarry2   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR2[i] = (DIGIT) nAdd;
        nAdd      = n0 + 3*n1 + 9*n2 + 27*n3 + 81*n4 + nCarry3; // R3
        nCarry3   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR3[i] = (DIGIT) nAdd;
        nAdd      = n0 + (n1<<2) + (n2<<4) + (n3<<6) + (n4<<8) + nCarry4; // R4
        nCarry4   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR4[i] = (DIGIT) nAdd;
        nAdd      = n0 + 5*n1 + 25*n2 + 125*n3 + 625*n4 + nCarry5; // R5
        nCarry5   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR5[i] = (DIGIT) nAdd;
        nAdd      = n0 + 6*n1 + 36*n2 + 216*n3 + 1296*n4 + nCarry6; // R6
        nCarry6   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR6[i] = (DIGIT) nAdd;
        nAdd      = n0 + 7*n1 + 49*n2 + 343*n3 + 2401*n4 + nCarry7; // R7
        nCarry7   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR7[i] = (DIGIT) nAdd;
    }
    for(; i<nFifth; i++)
    {
        DOUBLEDIGIT n1   = pX1[i];
        DOUBLEDIGIT n2   = pX2[i];
        DOUBLEDIGIT n3   = pX3[i];
        DOUBLEDIGIT n4   = pX4[i];
        DOUBLEDIGIT nAdd = n1 + n2 + n3 + n4 + nCarry1; // R1
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
        nAdd      = (n1<<1) + (n2<<2) + (n3<<3) + (n4<<4) + nCarry2; // R2
        nCarry2   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR2[i] = (DIGIT) nAdd;
        nAdd      = 3*n1 + 9*n2 + 27*n3 + 81*n4 + nCarry3; // R3
        nCarry3   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR3[i] = (DIGIT) nAdd;
        nAdd      = (n1<<2) + (n2<<4) + (n3<<6) + (n4<<8) + nCarry4; // R4
        nCarry4   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR4[i] = (DIGIT) nAdd;
        nAdd      = 5*n1 + 25*n2 + 125*n3 + 625*n4 + nCarry5; // R5
        nCarry5   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR5[i] = (DIGIT) nAdd;
        nAdd      = 6*n1 + 36*n2 + 216*n3 + 1296*n4 + nCarry6; // R6
        nCarry6   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR6[i] = (DIGIT) nAdd;
        nAdd      = 7*n1 + 49*n2 + 343*n3 + 2401*n4 + nCarry7; // R7
        nCarry7   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR7[i] = (DIGIT) nAdd;
    }
    pArgR1[i] =  nCarry1;
    pArgR2[i] =  nCarry2;
    pArgR3[i] =  nCarry3;
    pArgR4[i] =  nCarry4;
    pArgR5[i] =  nCarry5;
    pArgR6[i] =  nCarry6;
    pArgR7[i] =  nCarry7;
    pArgR1    += ++i;
    pArgR2    += i;
    pArgR3    += i;
    pArgR4    += i;
    pArgR5    =  pR8;
    pArgR6    += i;
    pArgR7    += i;
    nCarry1   =  0;
    nCarry2   =  0;
    nCarry3   =  0;
    nCarry4   =  0;
    nCarry5   =  0;
    nCarry6   =  0;
    nCarry7   =  0;
    nResidual =  nYSize - (nFifth<<2);
    for(i=0; i<nResidual; i++)
    {
        DOUBLEDIGIT n0   = pY0[i];
        DOUBLEDIGIT n1   = pY1[i];
        DOUBLEDIGIT n2   = pY2[i];
        DOUBLEDIGIT n3   = pY3[i];
        DOUBLEDIGIT n4   = pY4[i];
        DOUBLEDIGIT nAdd = n0 + n1 + n2 + n3 + n4 + nCarry1; // R1
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
        nAdd      = n0 + (n1<<1) + (n2<<2) + (n3<<3) + (n4<<4) + nCarry2; // R2
        nCarry2   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR2[i] = (DIGIT) nAdd;
        nAdd      = n0 + 3*n1 + 9*n2 + 27*n3 + 81*n4 + nCarry3; // R3
        nCarry3   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR3[i] = (DIGIT) nAdd;
        nAdd      = n0 + (n1<<2) + (n2<<4) + (n3<<6) + (n4<<8) + nCarry4; // R4
        nCarry4   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR4[i] = (DIGIT) nAdd;
        nAdd      = n0 + 5*n1 + 25*n2 + 125*n3 + 625*n4 + nCarry5; // R5
        nCarry5   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR5[i] = (DIGIT) nAdd;
        nAdd      = n0 + 6*n1 + 36*n2 + 216*n3 + 1296*n4 + nCarry6; // R6
        nCarry6   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR6[i] = (DIGIT) nAdd;
        nAdd      = n0 + 7*n1 + 49*n2 + 343*n3 + 2401*n4 + nCarry7; // R7
        nCarry7   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR7[i] = (DIGIT) nAdd;
    }
    for(; i<nFifth; i++)
    {
        DOUBLEDIGIT n1   = pY1[i];
        DOUBLEDIGIT n2   = pY2[i];
        DOUBLEDIGIT n3   = pY3[i];
        DOUBLEDIGIT n4   = pY4[i];
        DOUBLEDIGIT nAdd = n1 + n2 + n3 + n4 + nCarry1; // R1
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
        nAdd      = (n1<<1) + (n2<<2) + (n3<<3) + (n4<<4) + nCarry2; // R2
        nCarry2   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR2[i] = (DIGIT) nAdd;
        nAdd      = 3*n1 + 9*n2 + 27*n3 + 81*n4 + nCarry3; // R3
        nCarry3   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR3[i] = (DIGIT) nAdd;
        nAdd      = (n1<<2) + (n2<<4) + (n3<<6) + (n4<<8) + nCarry4; // R4
        nCarry4   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR4[i] = (DIGIT) nAdd;
        nAdd      = 5*n1 + 25*n2 + 125*n3 + 625*n4 + nCarry5; // R5
        nCarry5   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR5[i] = (DIGIT) nAdd;
        nAdd      = 6*n1 + 36*n2 + 216*n3 + 1296*n4 + nCarry6; // R6
        nCarry6   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR6[i] = (DIGIT) nAdd;
        nAdd      = 7*n1 + 49*n2 + 343*n3 + 2401*n4 + nCarry7; // R7
        nCarry7   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR7[i] = (DIGIT) nAdd;
    }
    pArgR1[i]   = nCarry1;
    pArgR2[i]   = nCarry2;
    pArgR3[i]   = nCarry3;
    pArgR4[i]   = nCarry4;
    pArgR5[i]   = nCarry5;
    pArgR6[i]   = nCarry6;
    pArgR7[i++] = nCarry7;
    // have the args for the multiplies: do them.  Make sure order right -- R(0) after R(2); for the rest, R(i) before R(i+1)
    // So: compute P7, then P6, then P1, then P4 (being careful to save the overlap digit of P6), then P3, then P2 (saving overlap
    // digit with P4), then P5, the P8 and P0
#if(_CollectDetailedTimingData)
    dwTimestamp          =  s_Timer.GetMicroseconds();
    g_nBuildTimes[e9By5] += (dwTimestamp-dwBuildTime);
    MultUBackend(i, i, pArgR7 - i, pArgR7, pR7, pnWorkspace, dwTimestamp);
    MultUBackend(i, i, pArgR6 - i, pArgR6, pR6, pnWorkspace, dwTimestamp);
    nP4_P6_overlap = pR6[nFifth<<1];
    MultUBackend(i, i, pArgR1 - i, pArgR1, pR1, pnWorkspace, dwTimestamp);
    MultUBackend(i, i, pArgR4 - i, pArgR4, pR4, pnWorkspace, dwTimestamp);
    nP2_P4_overlap = pR4[nFifth<<1];
    MultUBackend(i, i, pArgR3 - i, pArgR3, pR3, pnWorkspace, dwTimestamp);
    MultUBackend(i, i, pArgR2 - i, pArgR2, pR2, pnWorkspace, dwTimestamp);
    nP0_P2_overlap = pR2[nFifth<<1];
    MultUBackend(i, i, pR0+6, pR8, pR5, pnWorkspace, dwTimestamp);
    MultUBackend(i-1, i-1, pXValue, pYValue, pR8, pnWorkspace, dwTimestamp);
    MultUBackend(nXSize - (nFifth<<2), nYSize - (nFifth<<2), pXValue + (nFifth<<2), pYValue + (nFifth<<2), pR0, pnWorkspace, dwTimestamp);
    dwProcessTime = dwTimestamp;
#else
    MultUBackend(i, i, pArgR7 - i, pArgR7, pR7, pnWorkspace);
    MultUBackend(i, i, pArgR6 - i, pArgR6, pR6, pnWorkspace);
    nP4_P6_overlap = pR6[nFifth << 1];
    MultUBackend(i, i, pArgR1 - i, pArgR1, pR1, pnWorkspace);
    MultUBackend(i, i, pArgR4 - i, pArgR4, pR4, pnWorkspace);
    nP2_P4_overlap = pR4[nFifth << 1];
    MultUBackend(i, i, pArgR3 - i, pArgR3, pR3, pnWorkspace);
    MultUBackend(i, i, pArgR2 - i, pArgR2, pR2, pnWorkspace);
    nP0_P2_overlap = pR2[nFifth << 1];
    MultUBackend(i, i, pR0 + 6, pR8, pR5, pnWorkspace);
    MultUBackend(i - 1, i - 1, pXValue, pYValue, pR8, pnWorkspace);
    MultUBackend(nXSize - (nFifth << 2), nYSize - (nFifth << 2), pXValue + (nFifth << 2), pYValue + (nFifth << 2), pR0, pnWorkspace);
#endif
    nCarry1  = 0;
    nCarry2  = 0;
    nCarry3  = 0;
    nCarry4  = 0;
    nCarry5  = 0;
    nCarry6  = 0;
    nCarry7  = 0;
    nBorrow1 = 0;
    nBorrow2 = 0;
    nBorrow3 = 0;
    nBorrow4 = 0;
    nBorrow5 = 0;
    nBorrow6 = 0;
    nBorrow7 = 0;
    // now, construct the p(i)s -- first pass, pre-division.  Store p(i) in r(i).  Recall
    // P0 = R0
    // P1 = (-1089R0 + 2940R1 -  4410R2 +  4900R3 -  3675R4 + 1764R5 -  490R6 +  60R7 - 2116800R8)/420
    // P2 = (  938R0 - 4014R1 +  7911R2 -  9490R3 +  7380R4 - 3618R5 + 1019R6 - 126R7 + 4704480R8)/360
    // P3 = ( -967R0 + 5104R1 - 11787R2 + 15560R3 - 12725R4 + 6432R5 - 1849R6 + 232R7 - 9455040R8)/720
    // P4 = (   56R0 -  333R1 +   852R2 -  1219R3 +  1056R4 -  555R5 +  164R6 -  21R7 +  974736R8)/144
    // P5 = (  -46R0 +  295R1 -   810R2 +  1235R3 -  1130R4 +  621R5 -  190R6 +  25R7 - 1411200R8)/720
    // P6 = (    4R0 -   27R1 +    78R2 -   125R3 +   120R4 -   69R5 +   22R6 -   3R7 +  231840R8)/720
    // P7 = (    -R0 +    7R1 -    21R2 +    35R3 -    35R4 +   21R5 -    7R6 +    R7 -  141120R8)/5040
    // P8 = R8
    nResidual = nXSize + nYSize - (nFifth<<3);
    for(i=0; i<nResidual; i++)
    {
        nR0      =  pR0[i];
        nR1      =  pR1[i];
        nR2      =  pR2[i];
        nR3      =  pR3[i];
        nR4      =  pR4[i];
        nR5      =  pR5[i];
        nR6      =  pR6[i];
        nR7      =  pR7[i];
        nR8      =  pR8[i];
        // P1 = (-1089R0 + 2940R1 -  4410R2 +  4900R3 -  3675R4 + 1764R5 -  490R6 +  60R7 - 2116800R8)/420
        nAdd     =  2940*nR1 + 4900*nR3 + 1764*nR5 + 60*nR7 + nCarry1;
        nSub     =  1089*nR0 + 4410*nR2 + 3675*nR4 + 490*nR6 + 2116800*nR8 + nBorrow1;
        nCarry1  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow1 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow1 += (nAdd < nSub);
        pR1[i]   =  (DIGIT) (nAdd - nSub);
        // P2 = (  938R0 - 4014R1 +  7911R2 -  9490R3 +  7380R4 - 3618R5 + 1019R6 - 126R7 + 4704480R8)/360
        nAdd     =  938*nR0 + 7911*nR2 + 7380*nR4 + 1019*nR6 + 4704480*nR8 + nCarry2;
        nSub     =  4014*nR1 + 9490*nR3 + 3618*nR5 + 126*nR7 + nBorrow2;
        nCarry2  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow2 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow2 += (nAdd < nSub);
        pR2[i]   =  (DIGIT) (nAdd - nSub);
        // P3 = ( -967R0 + 5104R1 - 11787R2 + 15560R3 - 12725R4 + 6432R5 - 1849R6 + 232R7 - 9455040R8)/720
        nAdd     =  5104*nR1 + 15560*nR3 + 6432*nR5 + 232*nR7 + nCarry3;
        nSub     =  967*nR0 + 11787*nR2 + 12725*nR4 + 1849*nR6 + 9455040*nR8 + nBorrow3;
        nCarry3  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow3 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow3 += (nAdd < nSub);
        pR3[i]   =  (DIGIT) (nAdd - nSub);
        // P4 = (   56R0 -  333R1 +   852R2 -  1219R3 +  1056R4 -  555R5 +  164R6 -  21R7 +  974736R8)/144
        nAdd     =  56*nR0 + 852*nR2 + 1056*nR4 + 164*nR6 + 974736*nR8 + nCarry4;
        nSub     =  333*nR1 + 1219*nR3 + 555*nR5 + 21*nR7 + nBorrow4;
        nCarry4  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow4 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow4 += (nAdd < nSub);
        pR4[i]   =  (DIGIT) (nAdd - nSub);
        // P5 = (  -46R0 +  295R1 -   810R2 +  1235R3 -  1130R4 +  621R5 -  190R6 +  25R7 - 1411200R8)/720
        nAdd     =  295*nR1 + 1235*nR3 + 621*nR5 + 25*nR7 + nCarry5;
        nSub     =  46*nR0 + 810*nR2 + 1130*nR4 + 190*nR6 + 1411200*nR8 + nBorrow5;
        nCarry5  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow5 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow5 += (nAdd < nSub);
        pR5[i]   =  (DIGIT) (nAdd - nSub);
        // P6 = (    4R0 -   27R1 +    78R2 -   125R3 +   120R4 -   69R5 +   22R6 -   3R7 +  231840R8)/720
        nAdd     =  4*nR0 + 78*nR2 + 120*nR4 + 22*nR6 + 231840*nR8 + nCarry6;
        nSub     =  27*nR1 + 125*nR3 + 69*nR5 + 3*nR7 + nBorrow6;
        nCarry6  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow6 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow6 += (nAdd < nSub);
        pR6[i]   =  (DIGIT) (nAdd - nSub);
        // P7 = (    -R0 +    7R1 -    21R2 +    35R3 -    35R4 +   21R5 -    7R6 +    R7 -  141120R8)/5040
        nAdd     =  7*nR1 + 35*nR3 + 21*nR5 + nR7 + nCarry7;
        nSub     =  nR0 + 21*nR2 + 35*nR4 + 7*nR6 + 141120*nR8 + nBorrow7;
        nCarry7  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow7 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow7 += (nAdd < nSub);
        pR7[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
    }
    for(; i<(nFifth<<1); i++)
    {
        // no more of R(0)
        nR1      = pR1[i];
        nR2      = pR2[i];
        nR3      = pR3[i];
        nR4      = pR4[i];
        nR5      = pR5[i];
        nR6      = pR6[i];
        nR7      = pR7[i];
        nR8      = pR8[i];
        // P1 = (-1089R0 + 2940R1 -  4410R2 +  4900R3 -  3675R4 + 1764R5 -  490R6 +  60R7 - 2116800R8)/420
        nAdd     = 2940*nR1 + 4900*nR3 + 1764*nR5 + 60*nR7 + nCarry1;
        nSub     = 4410*nR2 + 3675*nR4 + 490*nR6 + 2116800*nR8 + nBorrow1;
        nCarry1  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow1 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow1 += (nAdd < nSub);
        pR1[i]   =  (DIGIT) (nAdd - nSub);
        // P2 = (  938R0 - 4014R1 +  7911R2 -  9490R3 +  7380R4 - 3618R5 + 1019R6 - 126R7 + 4704480R8)/360
        nAdd     =  7911*nR2 + 7380*nR4 + 1019*nR6 + 4704480*nR8 + nCarry2;
        nSub     =  4014*nR1 + 9490*nR3 + 3618*nR5 + 126*nR7 + nBorrow2;
        nCarry2  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow2 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow2 += (nAdd < nSub);
        pR2[i]   =  (DIGIT) (nAdd - nSub);
        // P3 = ( -967R0 + 5104R1 - 11787R2 + 15560R3 - 12725R4 + 6432R5 - 1849R6 + 232R7 - 9455040R8)/720
        nAdd     =  5104*nR1 + 15560*nR3 + 6432*nR5 + 232*nR7 + nCarry3;
        nSub     =  11787*nR2 + 12725*nR4 + 1849*nR6 + 9455040*nR8 + nBorrow3;
        nCarry3  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow3 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow3 += (nAdd < nSub);
        pR3[i]   =  (DIGIT) (nAdd - nSub);
        // P4 = (   56R0 -  333R1 +   852R2 -  1219R3 +  1056R4 -  555R5 +  164R6 -  21R7 +  974736R8)/144
        nAdd     =  852*nR2 + 1056*nR4 + 164*nR6 + 974736*nR8 + nCarry4;
        nSub     =  333*nR1 + 1219*nR3 + 555*nR5 + 21*nR7 + nBorrow4;
        nCarry4  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow4 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow4 += (nAdd < nSub);
        pR4[i]   =  (DIGIT) (nAdd - nSub);
        // P5 = (  -46R0 +  295R1 -   810R2 +  1235R3 -  1130R4 +  621R5 -  190R6 +  25R7 - 1411200R8)/720
        nAdd     =  295*nR1 + 1235*nR3 + 621*nR5 + 25*nR7 + nCarry5;
        nSub     =  810*nR2 + 1130*nR4 + 190*nR6 + 1411200*nR8 + nBorrow5;
        nCarry5  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow5 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow5 += (nAdd < nSub);
        pR5[i]   =  (DIGIT) (nAdd - nSub);
        // P6 = (    4R0 -   27R1 +    78R2 -   125R3 +   120R4 -   69R5 +   22R6 -   3R7 +  231840R8)/720
        nAdd     =  78*nR2 + 120*nR4 + 22*nR6 + 231840*nR8 + nCarry6;
        nSub     =  27*nR1 + 125*nR3 + 69*nR5 + 3*nR7 + nBorrow6;
        nCarry6  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow6 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow6 += (nAdd < nSub);
        pR6[i]   =  (DIGIT) (nAdd - nSub);
        // P7 = (    -R0 +    7R1 -    21R2 +    35R3 -    35R4 +   21R5 -    7R6 +    R7 -  141120R8)/5040
        nAdd     =  7*nR1 + 35*nR3 + 21*nR5 + nR7 + nCarry7;
        nSub     =  21*nR2 + 35*nR4 + 7*nR6 + 141120*nR8 + nBorrow7;
        nCarry7  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow7 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow7 += (nAdd < nSub);
        pR7[i]   =  (DIGIT) (nAdd - nSub);
    }
    // These are the products of two (nFifth+1)-digit numbers; from that alone, might have
    // 2 more digits.  But from what they are (P(i) is the sum of the digit multiplies for the ith column, in this case
    // multiplied by the divisor -- not yet done), we know that the first digit is 0 from the size of the divisors.
    // Also know that it is positive.
    nR1            = pR1[i];
    nR2            = nP0_P2_overlap;
    nR3            = pR3[i];
    nR4            = nP2_P4_overlap;
    nR5            = pR5[i];
    nR6            = nP4_P6_overlap;
    nR7            = pR7[i];
    // P1 = (-1089R0 + 2940R1 -  4410R2 +  4900R3 -  3675R4 + 1764R5 -  490R6 +  60R7 - 2116800R8)/420
    nAdd           = 2940*nR1 + 4900*nR3 + 1764*nR5 + 60*nR7 + nCarry1;
    nSub           = 4410*nR2 + 3675*nR4 + 490*nR6 + nBorrow1;
    pR1[i]         = (DIGIT) (nAdd - nSub);
    // P2 = (  938R0 - 4014R1 +  7911R2 -  9490R3 +  7380R4 - 3618R5 + 1019R6 - 126R7 + 4704480R8)/360
    nAdd           = 7911*nR2 + 7380*nR4 + 1019*nR6 + nCarry2;
    nSub           = 4014*nR1 + 9490*nR3 + 3618*nR5 + 126*nR7 + nBorrow2;
    nP0_P2_overlap = (DIGIT) (nAdd - nSub);
    // P3 = ( -967R0 + 5104R1 - 11787R2 + 15560R3 - 12725R4 + 6432R5 - 1849R6 + 232R7 - 9455040R8)/720
    nAdd           = 5104*nR1 + 15560*nR3 + 6432*nR5 + 232*nR7 + nCarry3;
    nSub           = 11787*nR2 + 12725*nR4 + 1849*nR6 + nBorrow3;
    pR3[i]         = (DIGIT) (nAdd - nSub);
    // P4 = (   56R0 -  333R1 +   852R2 -  1219R3 +  1056R4 -  555R5 +  164R6 -  21R7 +  974736R8)/144
    nAdd           = 852*nR2 + 1056*nR4 + 164*nR6 + nCarry4;
    nSub           = 333*nR1 + 1219*nR3 + 555*nR5 + 21*nR7 + nBorrow4;
    nP2_P4_overlap = (DIGIT) (nAdd - nSub);
    // P5 = (  -46R0 +  295R1 -   810R2 +  1235R3 -  1130R4 +  621R5 -  190R6 +  25R7 - 1411200R8)/720
    nAdd           = 295*nR1 + 1235*nR3 + 621*nR5 + 25*nR7 + nCarry5;
    nSub           = 810*nR2 + 1130*nR4 + 190*nR6 + nBorrow5;
    pR5[i]         = (DIGIT) (nAdd - nSub);
    // P6 = (    4R0 -   27R1 +    78R2 -   125R3 +   120R4 -   69R5 +   22R6 -   3R7 +  231840R8)/720
    nAdd   = 78*nR2 + 120*nR4 + 22*nR6 + nCarry6;
    nSub           = 27*nR1 + 125*nR3 + 69*nR5 + 3*nR7 + nBorrow6;
    nP4_P6_overlap = (DIGIT) (nAdd - nSub);
    // P7 = (    -R0 +    7R1 -    21R2 +    35R3 -    35R4 +   21R5 -    7R6 +    R7 -  141120R8)/5040
    nAdd           = 7*nR1 + 35*nR3 + 21*nR5 + nR7 + nCarry7;
    nSub           = 21*nR2 + 35*nR4 + 7*nR6 + nBorrow7;
    pR7[i]         = (DIGIT) (nAdd - nSub);
    // finally, apply the divisors and get the P(i)s in place in Z.  Note that P(0), P(2), P(4), P(6), and P(8) are already in place
    // but for any needed division and noting that the first digit is stored locally
    // P6
    i              = nFifth<<1;
    nAdd           = pR1[i];
    pR1[i]         = nAdd/420;
    nCarry1        = (nAdd%420)<<_DIGIT_SIZE_IN_BITS;
    nCarry2        = (nP0_P2_overlap%360)<<_DIGIT_SIZE_IN_BITS;
    nP0_P2_overlap = nP0_P2_overlap/360;
    nAdd           = pR3[i];
    pR3[i]         = nAdd/720;
    nCarry3        = (nAdd%720)<<_DIGIT_SIZE_IN_BITS;
    nCarry4        = (nP2_P4_overlap%144)<<_DIGIT_SIZE_IN_BITS;
    nP2_P4_overlap = nP2_P4_overlap/144;
    nAdd           = pR5[i];
    pR5[i]         = nAdd/720;
    nCarry5        = (nAdd%720)<<_DIGIT_SIZE_IN_BITS;
    nCarry6        = (nP4_P6_overlap%720)<<_DIGIT_SIZE_IN_BITS;
    nP4_P6_overlap = nP4_P6_overlap /720;
    nAdd           = pR7[i];
    pR7[i--]       = nAdd/5040;
    nCarry7        = (nAdd%5040)<<_DIGIT_SIZE_IN_BITS;
    do
    {
        nAdd    = pR1[i] | nCarry1;
        pR1[i]  = nAdd/420;
        nCarry1 = (nAdd%420)<<_DIGIT_SIZE_IN_BITS;
        nAdd    = pR2[i] | nCarry2;
        pR2[i]  = nAdd/360;
        nCarry2 = (nAdd%360)<<_DIGIT_SIZE_IN_BITS;
        nAdd    = pR3[i] | nCarry3;
        pR3[i]  = nAdd/720;
        nCarry3 = (nAdd%720)<<_DIGIT_SIZE_IN_BITS;
        nAdd    = pR4[i] | nCarry4;
        pR4[i]  = nAdd/144;
        nCarry4 = (nAdd%144)<<_DIGIT_SIZE_IN_BITS;
        nAdd    = pR5[i] | nCarry5;
        pR5[i]  = nAdd/720;
        nCarry5 = (nAdd%720)<<_DIGIT_SIZE_IN_BITS;
        nAdd    = pR6[i] | nCarry6;
        pR6[i]  = nAdd/720;
        nCarry6 = (nAdd%720)<<_DIGIT_SIZE_IN_BITS;
        nAdd    = pR7[i] | nCarry7;
        pR7[i]  = nAdd/5040;
        nCarry7 = (nAdd%5040)<<_DIGIT_SIZE_IN_BITS;
    }
    while(0 != i--);
    // at this point, P0, P2, P4, P6, and P8 are (mostly) in place; add in the odd Ps (and the overlap digits for the even)
    pArgR1  = pZValue + nFifth;
    nCarry1 = 0;
    // P7
    for(i=0; i<(nFifth<<1); i++)
    {
        nAdd      = (nCarry1 + pArgR1[i]) + pR7[i];
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
    }
    nCarry1 += pR7[i];
    pArgR1  += (nFifth<<1);
    // P5
    for(i=0; i<nFifth; i++)
    {
        nAdd      = (nCarry1 + pArgR1[i]) + pR5[i];
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
    }
    nCarry1 += nP4_P6_overlap;
    for(; i<(nFifth<<1); i++)
    {
        nAdd      = (nCarry1 + pArgR1[i]) + pR5[i];
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
    }
    nCarry1 += pR5[i];
    pArgR1  += (nFifth<<1);
    // P3
    for(i=0; i<nFifth; i++)
    {
        nAdd      = (nCarry1 + pArgR1[i]) + pR3[i];
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
    }
    nCarry1 += nP2_P4_overlap;
    for(; i<(nFifth<<1); i++)
    {
        nAdd      = (nCarry1 + pArgR1[i]) + pR3[i];
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
    }
    nCarry1 += pR3[i];
    pArgR1  += (nFifth<<1);
    // P1
    for(i=0; i<nFifth; i++)
    {
        nAdd      = (nCarry1 + pArgR1[i]) + pR1[i];
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
    }
    nCarry1 += nP0_P2_overlap;
    for(; i<1+(nFifth<<1); i++)
    {
        nAdd      = (nCarry1 + pArgR1[i]) + pR1[i];
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
    }
    // note we are guaranteed no carry past the end of Z
    if(nCarry1)
    {
        do
        {
            nAdd        = nCarry1 + pArgR1[i];
            nCarry1     = (nAdd>>_DIGIT_SIZE_IN_BITS);
            pArgR1[i++] = (DIGIT) nAdd;
        }
        while(nCarry1);
    }
#if(_CollectDetailedTimingData)
    dwTimestamp            =  s_Timer.GetMicroseconds();
    g_nProcessTimes[e9By5] += (dwTimestamp-dwProcessTime);
    g_nMultiplyCalls[e9By5]++;
#endif
    // and that's it -- we're done!
}

void CUnsignedArithmeticHelper::SquareU9by5(size_t             nXSize,
                                            const DIGIT        *pXValue,
                                            DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                                            DWORD64            &dwTimestamp,
#endif
                                            DIGIT              *pnWorkspace)
{
    DOUBLEDIGIT x0, x1, x2, x3, x4, nAdd, nSub, nCarry1, nCarry2, nCarry3, nCarry4, nCarry5, nCarry6, nCarry7, nBorrow1, nBorrow2, nBorrow3, nBorrow4, nBorrow5, nBorrow6, nBorrow7;
    DOUBLEDIGIT nP0_P2_overlap, nP2_P4_overlap, nP4_P6_overlap, nR0, nR1, nR2, nR3, nR4, nR5, nR6, nR7, nR8;
    unsigned int i, nResidual;
#if(_CollectDetailedTimingData)
    DWORD64 dwProcessTime, dwBuildTime = dwTimestamp;
#endif
    size_t      nFifth = (nXSize + 4)/5;
    DIGIT       *pR0   = pZValue + (nFifth<<3);
    DIGIT       *pR1   = pnWorkspace;
    DIGIT       *pR2   = pZValue + (nFifth*6);
    DIGIT       *pR3   = pR1     + ((nFifth+1)<<1);
    DIGIT       *pR4   = pZValue + (nFifth<<2);
    DIGIT       *pR5   = pR3     + ((nFifth+1)<<1);
    DIGIT       *pR6   = pZValue + (nFifth<<1);
    DIGIT       *pR7   = pR5     + ((nFifth+1)<<1);
    DIGIT       *pR8   = pZValue;
    const DIGIT *pX4   = pXValue;
    const DIGIT *pX3   = pX4 + nFifth;
    const DIGIT *pX2   = pX3 + nFifth;
    const DIGIT *pX1   = pX2 + nFifth;
    const DIGIT *pX0   = pX1 + nFifth;
    // P0, P8: hold arguments for computing R(5)
    // P1: holds arguments for P6
    // P2 (offset to leave space for arguments not-quite-held in P4) holds arguments for P3
    // P3 holds arguments for P4
    // P4 (offset to leave space for arguments not-quite-held in P6) holds arguments for P1
    // P5 holds arguments for P2
    // P6 holds arguments for P7
    DIGIT       *pArgR1 = pR4 + 2;
    DIGIT       *pArgR2 = pR5;
    DIGIT       *pArgR3 = pR2 + 4;
    DIGIT       *pArgR4 = pR3;
    DIGIT       *pArgR5 = pR8;
    DIGIT       *pArgR6 = pR1;
    DIGIT       *pArgR7 = pR6;
    pnWorkspace = pR7 + ((nFifth+1)<<1);
    // arguments for R1 - R7.  Recall
    // R1 = (x0 +  x1 +   x2 +    x3 +     x4)*(y0 +  y1 +   y2 +    y3 +     y4)
    // R2 = (x0 + 2x1 +  4x2 +   8x3 +   16x4)*(y0 + 2y1 +  4y2 +   8y3 +   16y4)
    // R3 = (x0 + 3x1 +  9x2 +  27x3 +   81x4)*(y0 + 3y1 +  9y2 +  27y3 +   81y4)
    // R4 = (x0 + 4x1 + 16x2 +  64x3 +  256x4)*(y0 + 4y1 + 16y2 +  64y3 +  256y4)
    // R5 = (x0 + 5x1 + 25x2 + 125x3 +  625x4)*(y0 + 5y1 + 25y2 + 125y3 +  625y4)
    // R6 = (x0 + 6x1 + 36x2 + 216x3 + 1296x4)*(y0 + 6y1 + 36y2 + 216y3 + 1296y4)
    // R7 = (x0 + 7x1 + 49x2 + 343x3 + 2401x4)*(y0 + 7y1 + 49y2 + 343y3 + 2401y4)
    nCarry1   = 0;
    nCarry2   = 0;
    nCarry3   = 0;
    nCarry4   = 0;
    nCarry5   = 0;
    nCarry6   = 0;
    nCarry7   = 0;
    nResidual = nXSize - (nFifth<<2);
    for(i=0; i<nResidual; i++)
    {
        DOUBLEDIGIT n0   = pX0[i];
        DOUBLEDIGIT n1   = pX1[i];
        DOUBLEDIGIT n2   = pX2[i];
        DOUBLEDIGIT n3   = pX3[i];
        DOUBLEDIGIT n4   = pX4[i];
        DOUBLEDIGIT nAdd = n0 + n1 + n2 + n3 + n4 + nCarry1; // R1
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
        nAdd      = n0 + (n1<<1) + (n2<<2) + (n3<<3) + (n4<<4) + nCarry2; // R2
        nCarry2   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR2[i] = (DIGIT) nAdd;
        nAdd      = n0 + 3*n1 + 9*n2 + 27*n3 + 81*n4 + nCarry3; // R3
        nCarry3   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR3[i] = (DIGIT) nAdd;
        nAdd      = n0 + (n1<<2) + (n2<<4) + (n3<<6) + (n4<<8) + nCarry4; // R4
        nCarry4   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR4[i] = (DIGIT) nAdd;
        nAdd      = n0 + 5*n1 + 25*n2 + 125*n3 + 625*n4 + nCarry5; // R5
        nCarry5   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR5[i] = (DIGIT) nAdd;
        nAdd      = n0 + 6*n1 + 36*n2 + 216*n3 + 1296*n4 + nCarry6; // R6
        nCarry6   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR6[i] = (DIGIT) nAdd;
        nAdd      = n0 + 7*n1 + 49*n2 + 343*n3 + 2401*n4 + nCarry7; // R7
        nCarry7   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR7[i] = (DIGIT) nAdd;
    }
    for(; i<nFifth; i++)
    {
        DOUBLEDIGIT n1   = pX1[i];
        DOUBLEDIGIT n2   = pX2[i];
        DOUBLEDIGIT n3   = pX3[i];
        DOUBLEDIGIT n4   = pX4[i];
        DOUBLEDIGIT nAdd = n1 + n2 + n3 + n4 + nCarry1; // R1
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
        nAdd      = (n1<<1) + (n2<<2) + (n3<<3) + (n4<<4) + nCarry2; // R2
        nCarry2   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR2[i] = (DIGIT) nAdd;
        nAdd      = 3*n1 + 9*n2 + 27*n3 + 81*n4 + nCarry3; // R3
        nCarry3   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR3[i] = (DIGIT) nAdd;
        nAdd      = (n1<<2) + (n2<<4) + (n3<<6) + (n4<<8) + nCarry4; // R4
        nCarry4   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR4[i] = (DIGIT) nAdd;
        nAdd      = 5*n1 + 25*n2 + 125*n3 + 625*n4 + nCarry5; // R5
        nCarry5   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR5[i] = (DIGIT) nAdd;
        nAdd      = 6*n1 + 36*n2 + 216*n3 + 1296*n4 + nCarry6; // R6
        nCarry6   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR6[i] = (DIGIT) nAdd;
        nAdd      = 7*n1 + 49*n2 + 343*n3 + 2401*n4 + nCarry7; // R7
        nCarry7   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR7[i] = (DIGIT) nAdd;
    }
    pArgR1[i]   = nCarry1;
    pArgR2[i]   = nCarry2;
    pArgR3[i]   = nCarry3;
    pArgR4[i]   = nCarry4;
    pArgR5[i]   = nCarry5;
    pArgR6[i]   = nCarry6;
    pArgR7[i++] = nCarry7;
    // have the args for the multiplies: do them.  Make sure order right -- R(0) after R(2); for the rest, R(i) before R(i+1)
    // So: compute P7, then P6, then P1, then P4 (being careful to save the overlap digit of P6), then P3, then P2 (saving overlap
    // digit with P4), then P5, the P8 and P0
#if(_CollectDetailedTimingData)
    dwTimestamp          =  s_Timer.GetMicroseconds();
    g_nBuildTimes[e9By5] += (dwTimestamp-dwBuildTime);
    SquareUBackend(i, pArgR7, pR7, pnWorkspace, dwTimestamp);
    SquareUBackend(i, pArgR6, pR6, pnWorkspace, dwTimestamp);
    nP4_P6_overlap = pR6[nFifth<<1];
    SquareUBackend(i, pArgR1, pR1, pnWorkspace, dwTimestamp);
    SquareUBackend(i,pArgR4, pR4, pnWorkspace, dwTimestamp);
    nP2_P4_overlap = pR4[nFifth<<1];
    SquareUBackend(i, pArgR3, pR3, pnWorkspace, dwTimestamp);
    SquareUBackend(i, pArgR2, pR2, pnWorkspace, dwTimestamp);
    nP0_P2_overlap = pR2[nFifth<<1];
    SquareUBackend(i, pR8, pR5, pnWorkspace, dwTimestamp);
    SquareUBackend(i-1, pXValue, pR8, pnWorkspace, dwTimestamp);
    SquareUBackend(nXSize - (nFifth<<2), pXValue + (nFifth<<2), pR0, pnWorkspace, dwTimestamp);
    dwProcessTime = dwTimestamp;
#else
    SquareUBackend(i, pArgR7, pR7, pnWorkspace);
    SquareUBackend(i, pArgR6, pR6, pnWorkspace);
    nP4_P6_overlap = pR6[nFifth << 1];
    SquareUBackend(i, pArgR1, pR1, pnWorkspace);
    SquareUBackend(i, pArgR4, pR4, pnWorkspace);
    nP2_P4_overlap = pR4[nFifth << 1];
    SquareUBackend(i, pArgR3, pR3, pnWorkspace);
    SquareUBackend(i, pArgR2, pR2, pnWorkspace);
    nP0_P2_overlap = pR2[nFifth << 1];
    SquareUBackend(i, pArgR5, pR5, pnWorkspace);
    SquareUBackend(i - 1, pXValue, pR8, pnWorkspace);
    SquareUBackend(nXSize - (nFifth << 2), pXValue + (nFifth << 2), pR0, pnWorkspace);
#endif
    nCarry1  = 0;
    nCarry2  = 0;
    nCarry3  = 0;
    nCarry4  = 0;
    nCarry5  = 0;
    nCarry6  = 0;
    nCarry7  = 0;
    nBorrow1 = 0;
    nBorrow2 = 0;
    nBorrow3 = 0;
    nBorrow4 = 0;
    nBorrow5 = 0;
    nBorrow6 = 0;
    nBorrow7 = 0;
    // now, construct the p(i)s -- first pass, pre-division.  Store p(i) in r(i).  Recall
    // P0 = R0
    // P1 = (-1089R0 + 2940R1 -  4410R2 +  4900R3 -  3675R4 + 1764R5 -  490R6 +  60R7 - 2116800R8)/420
    // P2 = (  938R0 - 4014R1 +  7911R2 -  9490R3 +  7380R4 - 3618R5 + 1019R6 - 126R7 + 4704480R8)/360
    // P3 = ( -967R0 + 5104R1 - 11787R2 + 15560R3 - 12725R4 + 6432R5 - 1849R6 + 232R7 - 9455040R8)/720
    // P4 = (   56R0 -  333R1 +   852R2 -  1219R3 +  1056R4 -  555R5 +  164R6 -  21R7 +  974736R8)/144
    // P5 = (  -46R0 +  295R1 -   810R2 +  1235R3 -  1130R4 +  621R5 -  190R6 +  25R7 - 1411200R8)/720
    // P6 = (    4R0 -   27R1 +    78R2 -   125R3 +   120R4 -   69R5 +   22R6 -   3R7 +  231840R8)/720
    // P7 = (    -R0 +    7R1 -    21R2 +    35R3 -    35R4 +   21R5 -    7R6 +    R7 -  141120R8)/5040
    // P8 = R8
    nResidual = nXSize + nXSize - (nFifth<<3);
    for(i=0; i<nResidual; i++)
    {
        nR0      =  pR0[i];
        nR1      =  pR1[i];
        nR2      =  pR2[i];
        nR3      =  pR3[i];
        nR4      =  pR4[i];
        nR5      =  pR5[i];
        nR6      =  pR6[i];
        nR7      =  pR7[i];
        nR8      =  pR8[i];
        // P1 = (-1089R0 + 2940R1 -  4410R2 +  4900R3 -  3675R4 + 1764R5 -  490R6 +  60R7 - 2116800R8)/420
        nAdd     =  2940*nR1 + 4900*nR3 + 1764*nR5 + 60*nR7 + nCarry1;
        nSub     =  1089*nR0 + 4410*nR2 + 3675*nR4 + 490*nR6 + 2116800*nR8 + nBorrow1;
        nCarry1  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow1 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow1 += (nAdd < nSub);
        pR1[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
        // P2 = (  938R0 - 4014R1 +  7911R2 -  9490R3 +  7380R4 - 3618R5 + 1019R6 - 126R7 + 4704480R8)/360
        nAdd     =  938*nR0 + 7911*nR2 + 7380*nR4 + 1019*nR6 + 4704480*nR8 + nCarry2;
        nSub     =  4014*nR1 + 9490*nR3 + 3618*nR5 + 126*nR7 + nBorrow2;
        nCarry2  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow2 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow2 += (nAdd < nSub);
        pR2[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
        // P3 = ( -967R0 + 5104R1 - 11787R2 + 15560R3 - 12725R4 + 6432R5 - 1849R6 + 232R7 - 9455040R8)/720
        nAdd     =  5104*nR1 + 15560*nR3 + 6432*nR5 + 232*nR7 + nCarry3;
        nSub     =  967*nR0 + 11787*nR2 + 12725*nR4 + 1849*nR6 + 9455040*nR8 + nBorrow3;
        nCarry3  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow3 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow3 += (nAdd < nSub);
        pR3[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
        // P4 = (   56R0 -  333R1 +   852R2 -  1219R3 +  1056R4 -  555R5 +  164R6 -  21R7 +  974736R8)/144
        nAdd     =  56*nR0 + 852*nR2 + 1056*nR4 + 164*nR6 + 974736*nR8 + nCarry4;
        nSub     =  333*nR1 + 1219*nR3 + 555*nR5 + 21*nR7 + nBorrow4;
        nCarry4  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow4 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow4 += (nAdd < nSub);
        pR4[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
        // P5 = (  -46R0 +  295R1 -   810R2 +  1235R3 -  1130R4 +  621R5 -  190R6 +  25R7 - 1411200R8)/720
        nAdd     =  295*nR1 + 1235*nR3 + 621*nR5 + 25*nR7 + nCarry5;
        nSub     =  46*nR0 + 810*nR2 + 1130*nR4 + 190*nR6 + 1411200*nR8 + nBorrow5;
        nCarry5  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow5 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow5 += (nAdd < nSub);
        pR5[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
        // P6 = (    4R0 -   27R1 +    78R2 -   125R3 +   120R4 -   69R5 +   22R6 -   3R7 +  231840R8)/720
        nAdd     =  4*nR0 + 78*nR2 + 120*nR4 + 22*nR6 + 231840*nR8 + nCarry6;
        nSub     =  27*nR1 + 125*nR3 + 69*nR5 + 3*nR7 + nBorrow6;
        nCarry6  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow6 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow6 += (nAdd < nSub);
        pR6[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
        // P7 = (    -R0 +    7R1 -    21R2 +    35R3 -    35R4 +   21R5 -    7R6 +    R7 -  141120R8)/5040
        nAdd     =  7*nR1 + 35*nR3 + 21*nR5 + nR7 + nCarry7;
        nSub     =  nR0 + 21*nR2 + 35*nR4 + 7*nR6 + 141120*nR8 + nBorrow7;
        nCarry7  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow7 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow7 += (nAdd < nSub);
        pR7[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
    }
    for(; i<(nFifth<<1); i++)
    {
        // no more of R(0)
        nR1      = pR1[i];
        nR2      = pR2[i];
        nR3      = pR3[i];
        nR4      = pR4[i];
        nR5      = pR5[i];
        nR6      = pR6[i];
        nR7      = pR7[i];
        nR8      = pR8[i];
        // P1 = (-1089R0 + 2940R1 -  4410R2 +  4900R3 -  3675R4 + 1764R5 -  490R6 +  60R7 - 2116800R8)/420
        nAdd     = 2940*nR1 + 4900*nR3 + 1764*nR5 + 60*nR7 + nCarry1;
        nSub     = 4410*nR2 + 3675*nR4 + 490*nR6 + 2116800*nR8 + nBorrow1;
        nCarry1  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow1 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow1 += (nAdd < nSub);
        pR1[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
        // P2 = (  938R0 - 4014R1 +  7911R2 -  9490R3 +  7380R4 - 3618R5 + 1019R6 - 126R7 + 4704480R8)/360
        nAdd     =  7911*nR2 + 7380*nR4 + 1019*nR6 + 4704480*nR8 + nCarry2;
        nSub     =  4014*nR1 + 9490*nR3 + 3618*nR5 + 126*nR7 + nBorrow2;
        nCarry2  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow2 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow2 += (nAdd < nSub);
        pR2[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
        // P3 = ( -967R0 + 5104R1 - 11787R2 + 15560R3 - 12725R4 + 6432R5 - 1849R6 + 232R7 - 9455040R8)/720
        nAdd     =  5104*nR1 + 15560*nR3 + 6432*nR5 + 232*nR7 + nCarry3;
        nSub     =  11787*nR2 + 12725*nR4 + 1849*nR6 + 9455040*nR8 + nBorrow3;
        nCarry3  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow3 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow3 += (nAdd < nSub);
        pR3[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
        // P4 = (   56R0 -  333R1 +   852R2 -  1219R3 +  1056R4 -  555R5 +  164R6 -  21R7 +  974736R8)/144
        nAdd     =  852*nR2 + 1056*nR4 + 164*nR6 + 974736*nR8 + nCarry4;
        nSub     =  333*nR1 + 1219*nR3 + 555*nR5 + 21*nR7 + nBorrow4;
        nCarry4  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow4 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow4 += (nAdd < nSub);
        pR4[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
        // P5 = (  -46R0 +  295R1 -   810R2 +  1235R3 -  1130R4 +  621R5 -  190R6 +  25R7 - 1411200R8)/720
        nAdd     =  295*nR1 + 1235*nR3 + 621*nR5 + 25*nR7 + nCarry5;
        nSub     =  810*nR2 + 1130*nR4 + 190*nR6 + 1411200*nR8 + nBorrow5;
        nCarry5  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow5 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow5 += (nAdd < nSub);
        pR5[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
        // P6 = (    4R0 -   27R1 +    78R2 -   125R3 +   120R4 -   69R5 +   22R6 -   3R7 +  231840R8)/720
        nAdd     =  78*nR2 + 120*nR4 + 22*nR6 + 231840*nR8 + nCarry6;
        nSub     =  27*nR1 + 125*nR3 + 69*nR5 + 3*nR7 + nBorrow6;
        nCarry6  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow6 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow6 += (nAdd < nSub);
        pR6[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
        // P7 = (    -R0 +    7R1 -    21R2 +    35R3 -    35R4 +   21R5 -    7R6 +    R7 -  141120R8)/5040
        nAdd     =  7*nR1 + 35*nR3 + 21*nR5 + nR7 + nCarry7;
        nSub     =  21*nR2 + 35*nR4 + 7*nR6 + 141120*nR8 + nBorrow7;
        nCarry7  =  nAdd>>_DIGIT_SIZE_IN_BITS;
        nBorrow7 =  nSub>>_DIGIT_SIZE_IN_BITS;
        nAdd     &= c_nClearHigh;
        nSub     &= c_nClearHigh;
        nBorrow7 += (nAdd < nSub);
        pR7[i]   =  ((DIGIT) nAdd) - ((DIGIT) nSub);
    }
    // These are the products of two (nFifth+1)-digit numbers; from that alone, might have
    // 2 more digits.  But from what they are (P(i) is the sum of the digit multiplies for the ith column, in this case
    // multiplied by the divisor -- not yet done), we know that the first digit is 0 from the size of the divisors.
    // Also know that it is positive.
    nR1            = pR1[i];
    nR2            = nP0_P2_overlap;
    nR3            = pR3[i];
    nR4            = nP2_P4_overlap;
    nR5            = pR5[i];
    nR6            = nP4_P6_overlap;
    nR7            = pR7[i];
    // P1 = (-1089R0 + 2940R1 -  4410R2 +  4900R3 -  3675R4 + 1764R5 -  490R6 +  60R7 - 2116800R8)/420
    nAdd           = 2940*nR1 + 4900*nR3 + 1764*nR5 + 60*nR7 + nCarry1;
    nSub           = 4410*nR2 + 3675*nR4 + 490*nR6 + nBorrow1;
    pR1[i]         = (DIGIT) (nAdd - nSub);
    // P2 = (  938R0 - 4014R1 +  7911R2 -  9490R3 +  7380R4 - 3618R5 + 1019R6 - 126R7 + 4704480R8)/360
    nAdd           = 7911*nR2 + 7380*nR4 + 1019*nR6 + nCarry2;
    nSub           = 4014*nR1 + 9490*nR3 + 3618*nR5 + 126*nR7 + nBorrow2;
    nP0_P2_overlap = (DIGIT) (nAdd - nSub);
    // P3 = ( -967R0 + 5104R1 - 11787R2 + 15560R3 - 12725R4 + 6432R5 - 1849R6 + 232R7 - 9455040R8)/720
    nAdd           = 5104*nR1 + 15560*nR3 + 6432*nR5 + 232*nR7 + nCarry3;
    nSub           = 11787*nR2 + 12725*nR4 + 1849*nR6 + nBorrow3;
    pR3[i]         = (DIGIT) (nAdd - nSub);
    // P4 = (   56R0 -  333R1 +   852R2 -  1219R3 +  1056R4 -  555R5 +  164R6 -  21R7 +  974736R8)/144
    nAdd           = 852*nR2 + 1056*nR4 + 164*nR6 + nCarry4;
    nSub           = 333*nR1 + 1219*nR3 + 555*nR5 + 21*nR7 + nBorrow4;
    nP2_P4_overlap = (DIGIT) (nAdd - nSub);
    // P5 = (  -46R0 +  295R1 -   810R2 +  1235R3 -  1130R4 +  621R5 -  190R6 +  25R7 - 1411200R8)/720
    nAdd           = 295*nR1 + 1235*nR3 + 621*nR5 + 25*nR7 + nCarry5;
    nSub           = 810*nR2 + 1130*nR4 + 190*nR6 + nBorrow5;
    pR5[i]         = (DIGIT) (nAdd - nSub);
    // P6 = (    4R0 -   27R1 +    78R2 -   125R3 +   120R4 -   69R5 +   22R6 -   3R7 +  231840R8)/720
    nAdd   = 78*nR2 + 120*nR4 + 22*nR6 + nCarry6;
    nSub           = 27*nR1 + 125*nR3 + 69*nR5 + 3*nR7 + nBorrow6;
    nP4_P6_overlap = (DIGIT) (nAdd - nSub);
    // P7 = (    -R0 +    7R1 -    21R2 +    35R3 -    35R4 +   21R5 -    7R6 +    R7 -  141120R8)/5040
    nAdd           = 7*nR1 + 35*nR3 + 21*nR5 + nR7 + nCarry7;
    nSub           = 21*nR2 + 35*nR4 + 7*nR6 + nBorrow7;
    pR7[i]         = (DIGIT) (nAdd - nSub);
    // finally, apply the divisors and get the P(i)s in place in Z.  Note that P(0), P(2), P(4), P(6), and P(8) are already in place
    // but for any needed division and noting that the first digit is stored locally
    // P6
    i              = nFifth<<1;
    nAdd           = pR1[i];
    pR1[i]         = nAdd/420;
    nCarry1        = (nAdd%420)<<_DIGIT_SIZE_IN_BITS;
    nCarry2        = (nP0_P2_overlap%360)<<_DIGIT_SIZE_IN_BITS;
    nP0_P2_overlap = nP0_P2_overlap/360;
    nAdd           = pR3[i];
    pR3[i]         = nAdd/720;
    nCarry3        = (nAdd%720)<<_DIGIT_SIZE_IN_BITS;
    nCarry4        = (nP2_P4_overlap%144)<<_DIGIT_SIZE_IN_BITS;
    nP2_P4_overlap = nP2_P4_overlap/144;
    nAdd           = pR5[i];
    pR5[i]         = nAdd/720;
    nCarry5        = (nAdd%720)<<_DIGIT_SIZE_IN_BITS;
    nCarry6        = (nP4_P6_overlap%720)<<_DIGIT_SIZE_IN_BITS;
    nP4_P6_overlap = nP4_P6_overlap /720;
    nAdd           = pR7[i];
    pR7[i--]       = nAdd/5040;
    nCarry7        = (nAdd%5040)<<_DIGIT_SIZE_IN_BITS;
    do
    {
        nAdd    = pR1[i] | nCarry1;
        pR1[i]  = nAdd/420;
        nCarry1 = (nAdd%420)<<_DIGIT_SIZE_IN_BITS;
        nAdd    = pR2[i] | nCarry2;
        pR2[i]  = nAdd/360;
        nCarry2 = (nAdd%360)<<_DIGIT_SIZE_IN_BITS;
        nAdd    = pR3[i] | nCarry3;
        pR3[i]  = nAdd/720;
        nCarry3 = (nAdd%720)<<_DIGIT_SIZE_IN_BITS;
        nAdd    = pR4[i] | nCarry4;
        pR4[i]  = nAdd/144;
        nCarry4 = (nAdd%144)<<_DIGIT_SIZE_IN_BITS;
        nAdd    = pR5[i] | nCarry5;
        pR5[i]  = nAdd/720;
        nCarry5 = (nAdd%720)<<_DIGIT_SIZE_IN_BITS;
        nAdd    = pR6[i] | nCarry6;
        pR6[i]  = nAdd/720;
        nCarry6 = (nAdd%720)<<_DIGIT_SIZE_IN_BITS;
        nAdd    = pR7[i] | nCarry7;
        pR7[i]  = nAdd/5040;
        nCarry7 = (nAdd%5040)<<_DIGIT_SIZE_IN_BITS;
    }
    while(0 != i--);
    // at this point, P0, P2, P4, P6, and P8 are (mostly) in place; add in the odd Ps (and the overlap digits for the even)
    pArgR1  = pZValue + nFifth;
    nCarry1 = 0;
    // P7
    for(i=0; i<(nFifth<<1); i++)
    {
        nAdd      = nCarry1 + pArgR1[i] + pR7[i];
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
    }
    nCarry1 += pR7[i];
    pArgR1  += (nFifth<<1);
    // P5
    for(i=0; i<nFifth; i++)
    {
        nAdd      = nCarry1 + pArgR1[i] + pR5[i];
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
    }
    nCarry1 += nP4_P6_overlap;
    for(; i<(nFifth<<1); i++)
    {
        nAdd      = nCarry1 + pArgR1[i] + pR5[i];
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
    }
    nCarry1 += pR5[i];
    pArgR1  += (nFifth<<1);
    // P3
    for(i=0; i<nFifth; i++)
    {
        nAdd      = nCarry1 + pArgR1[i] + pR3[i];
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
    }
    nCarry1 += nP2_P4_overlap;
    for(; i<(nFifth<<1); i++)
    {
        nAdd      = nCarry1 + pArgR1[i] + pR3[i];
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
    }
    nCarry1 += pR3[i];
    pArgR1  += (nFifth<<1);
    // P1
    for(i=0; i<nFifth; i++)
    {
        nAdd      = nCarry1 + pArgR1[i] + pR1[i];
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
    }
    nCarry1 += nP0_P2_overlap;
    for(; i<1+(nFifth<<1); i++)
    {
        nAdd      = nCarry1 + pArgR1[i] + pR1[i];
        nCarry1   = (nAdd>>_DIGIT_SIZE_IN_BITS);
        pArgR1[i] = (DIGIT) nAdd;
    }
    // note we are guaranteed no carry past the end of Z
    if(nCarry1)
    {
        do
        {
            nAdd        = nCarry1 + pArgR1[i];
            nCarry1     = (nAdd>>_DIGIT_SIZE_IN_BITS);
            pArgR1[i++] = (DIGIT) nAdd;
        }
        while(nCarry1);
    }
#if(_CollectDetailedTimingData)
    dwTimestamp            =  s_Timer.GetMicroseconds();
    g_nProcessTimes[e9By5] += (dwTimestamp-dwProcessTime);
    g_nMultiplyCalls[e9By5]++;
#endif
    // and that's it -- we're done!
}
#endif

void CUnsignedArithmeticHelper::Divide(size_t  nXSize,
                                       size_t  nYSize,
                                       size_t  &nXDivYSize,
                                       size_t  &nRemainderSize,
                                       DIGIT   *pXValue,
                                       DIGIT   *pYValue,
                                       DIGIT   *pXDivYValue,
                                       DIGIT   *pWorkspace)
{
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp  = s_Timer.GetMicroseconds();
    DWORD64 dwTimestamp2 = dwTimestamp;
    DivideBackend(nXSize, nYSize, nXDivYSize, nRemainderSize, pXValue, pYValue, pXDivYValue, dwTimestamp, pWorkspace);
    g_nDivideTime[eTotalDivideCalls]++;
    g_nDivideTime[eTotalDivideTime] += dwTimestamp - dwTimestamp2;
#else
    DivideBackend(nXSize, nYSize, nXDivYSize, nRemainderSize, pXValue, pYValue, pXDivYValue, pWorkspace);
#endif
}

void CUnsignedArithmeticHelper::DivideBackend(size_t  nXSize,
                                              size_t  nYSize,
                                              size_t  &nXDivYSize,
                                              size_t  &nRemainderSize,
                                              DIGIT   *pXValue,
                                              DIGIT   *pYValue,
                                              DIGIT   *pXDivYValue,
#if(_CollectDetailedTimingData)
                                              DWORD64 &dwTimestamp,
#endif
                                              DIGIT   *pWorkspace)
{
#if _CollectDetailedTimingData
    DWORD64 dwTimestamp2 = dwTimestamp;
#endif
    int nCompare = CBigInteger::CompareUnsigned(nXSize,nYSize,pXValue,pYValue);
    if(nCompare<0)
    {
        // X is smaller than Y
        nXDivYSize     = 0;
        nRemainderSize = nXSize;
        *pXDivYValue = 0;
    }
    else
    {
        // first estimate of the division size (done here, because the size of x might
        // change in internal usage)
        nXDivYSize = nXSize-nYSize;
        DIGIT nLast = 0; // used as we will overwrite a digit of the result when we do the
                         // divide in multiple chunks
        // X is at least as large as Y
        if(nYSize<<1 < nXSize)
        {
            // If X is *much* bigger than Y, do in base-sized chunks iteratively, to
            // avoid using recursion (which can blow out the stack if, say, Y is millions
            // of digits and X only hundreds)
            do
            {
                // in doing this division in pieces, we will overwrite the first computed
                // digit: dividing an m digit number by an n digit number yields an (m-n+1)
                // digit number; there is overlap in this first digit.  But for all but
                // the first iteration, this digit will be 0: the first m digits of the
                // number to be divided are the remainder of the last division, and so
                // less than the number to be divided by.  Fastest way to restore it
                // is to just add the value in: this avoids any conditionals, and atomic
                // adds are fast.
#if _CollectDetailedTimingData
                DivideRecursive(nYSize<<1,
                                nYSize,
                                pXValue+nXSize-(nYSize<<1),
                                pYValue,
                                pXDivYValue+nXSize-(nYSize<<1),
                                dwTimestamp,
                                pWorkspace);
#else
                DivideRecursive(nYSize<<1,
                                nYSize,
                                pXValue+nXSize-(nYSize<<1),
                                pYValue,
                                pXDivYValue+nXSize-(nYSize<<1),
                                pWorkspace);
#endif
                // restore value overwritten
                pXDivYValue[nXSize-nYSize] += nLast;
                nXSize                     -= nYSize;
                nLast                      =  pXDivYValue[nXSize-nYSize];
            }
            while(nYSize<<1 < nXSize);
        }
        // final (possibly first) division
#if _CollectDetailedTimingData
        DivideRecursive(nXSize,nYSize,pXValue,pYValue,pXDivYValue,dwTimestamp,pWorkspace);
#else
        DivideRecursive(nXSize,nYSize,pXValue,pYValue,pXDivYValue,pWorkspace);
#endif
        // restore value overwritten
        pXDivYValue[nXSize-nYSize] += nLast;
        // compute the actual size of XDivY
        if(0!=pXDivYValue[nXDivYSize])
        {
            nXDivYSize++;
        }
        // compute the size of XModY
        nRemainderSize = nYSize;
        if(0==pXValue[nRemainderSize-1])
        {
            do
            {
                nRemainderSize--;
            }
            while(0<nRemainderSize && 0==pXValue[nRemainderSize-1]);
        }
    }
};

void CUnsignedArithmeticHelper::DivideBasic(size_t      nXSize,
                                            size_t      nYSize,
                                            DIGIT       *pXValue,
                                            const DIGIT *pYValue,
#if(_CollectDetailedTimingData)
                                            DWORD64     &dwTimestamp,
#endif
                                            DIGIT       *pXDivYValue)
{
    DOUBLEDIGIT  nD1,nD2,nD3,nD4;
    size_t       i,ii;
    DOUBLEDIGIT	 nCarry, nBorrow, nProd, nMult;
    if(1==nYSize)
    {
        // special case
        nD1    = pYValue[0];
        nCarry = 0;
        do
        {
            nProd               = pXValue[--nXSize] | (nCarry<<_DIGIT_SIZE_IN_BITS);
            pXDivYValue[nXSize] = (DIGIT) (nProd/nD1);
            nCarry              = nProd%nD1;
        }
        while(0 != nXSize);
        pXValue[0] = (DIGIT) nCarry; // put the remainder back into X
    }
    else
    {
        for(i=0;i<=nXSize-nYSize;i++)  // zero out the result
        {
            pXDivYValue[i] = 0;
        }
        nD1 = pYValue[nYSize-1];
        nD2 = ((nD1<<_DIGIT_SIZE_IN_BITS) + pYValue[nYSize-2]) + (2<nYSize); // if nYSize==2, do exact divide -- no need to estimate
        nD1++;
        while(nYSize < nXSize)
        {
            ii = 0;
            nD3 = pXValue[nXSize - 1];
            if(nD1 <= nD3)
            {
                nMult = nD3/nD1;
            }
            else
            {
                nMult = ((nD3<<_DIGIT_SIZE_IN_BITS) + pXValue[nXSize-2])/nD1;
                ii    = 1;
            }
            // add divide into place
            nProd                         = pXDivYValue[nXSize-nYSize-ii] + nMult;
            nCarry                        = nProd>>_DIGIT_SIZE_IN_BITS;
            pXDivYValue[nXSize-nYSize-ii] = nProd;
            if(nCarry)
            {
                i = 1;
                do
                {
                    nProd                             = pXDivYValue[nXSize-nYSize-ii+i] + nCarry;
                    pXDivYValue[nXSize-nYSize-ii+i++] = nProd;
                    nCarry                            = (nProd>>_DIGIT_SIZE_IN_BITS);
                }
                while(nCarry);
            }
            // subtract multiple of Y from X
            nCarry = 0;
            for(i=0;i<nYSize;i++)
            {
                nProd                    =  nMult*pYValue[i];
                nBorrow                  =  (nProd&c_nClearHigh) + nCarry;
                nCarry                   =  (nProd>>_DIGIT_SIZE_IN_BITS) + (nBorrow>>_DIGIT_SIZE_IN_BITS);
                nBorrow                  =  nBorrow&c_nClearHigh;
                if(nBorrow>pXValue[nXSize-nYSize+i-ii])
                {
                    nCarry++;
                }
                pXValue[nXSize-nYSize+i-ii] -= (DIGIT) nBorrow;
            }
            pXValue[nXSize-ii] -= (DIGIT) nCarry;
            while(0<nXSize && 0==pXValue[nXSize-1])
            {
                nXSize--;
            }
        }
        if(nXSize==nYSize)
        {
            // might be able to extract a little bit more
            // if 0 == nD2, first 2 DIGITS of Y are FFF...: know can get at most one more Y in
            if(0!=nD2)
            {
                nD3   = *((DOUBLEDIGIT *) (pXValue+nXSize-2));
                nMult = nD3/nD2;
                if(nMult)
                {
                    // yup
                    nCarry = 0;
                    for(i=0;i<nYSize;i++)
                    {
                        nProd                    =  nMult*pYValue[i];
                        nBorrow                  =  (nProd&c_nClearHigh) + nCarry;
                        nCarry                   =  (nProd>>_DIGIT_SIZE_IN_BITS) + (nBorrow>>_DIGIT_SIZE_IN_BITS);
                        nBorrow                  =  nBorrow&c_nClearHigh;
                        if(nBorrow>pXValue[i])
                        {
                            nCarry++;
                        }
                        pXValue[i] -= (DIGIT) nBorrow;
                    }
                    pXValue[i] -= (DIGIT) nCarry;
                    while(0<nXSize && 0==pXValue[nXSize-1])
                    {
                        nXSize--;
                    }
                    nCarry         = nMult + pXDivYValue[0];
                    pXDivYValue[0] = nCarry;
                    nCarry         = nCarry>>_DIGIT_SIZE_IN_BITS;
                    if(nCarry)
                    {
                        i = 1;
                        while(c_nClearHigh==pXDivYValue[i]) pXDivYValue[i++] = 0;
                        pXDivYValue[i]++;
                    }
                }
            }
            if(nXSize==nYSize)
            {
                // *might* be able to fit in just one more
                bool bXGreater = false;
                for(i=1;i<=nXSize;i++)
                {
                    if(pXValue[nXSize-i]<pYValue[nXSize-i])
                    {
                        break;
                    }
                    else if(pYValue[nXSize-i]<pXValue[nXSize-i])
                    {
                        bXGreater = true;
                        break;
                    }
                }
                bXGreater |= (i==nXSize+1);
                if(bXGreater)
                {
                    // in fact, we can
                    nXSize = Subtract(nXSize, nYSize, pXValue, pYValue, pXValue);
                    i = 0;
                    while(c_nClearHigh==pXDivYValue[i]) pXDivYValue[i++] = 0;
                    pXDivYValue[i]++;
                }
                while(0<nXSize && 0==pXValue[nXSize-1])
                {
                    nXSize--;
                }
            }
        }
    }
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp2            =  s_Timer.GetMicroseconds();
    g_nDivideTime[eBasicDivideTime] += dwTimestamp2 - dwTimestamp;
    dwTimestamp                     =  dwTimestamp2;
#endif
}

// returns the new x size
size_t AddDivBackIn(size_t nXSize, size_t nYSize, DIGIT *pX, DIGIT *pDiv)
{
    size_t      i;
    DOUBLEDIGIT nCarry = 0;
    for(i=0; i<=nXSize-nYSize; i++)
    {
        nCarry = (nCarry + pX[i]) + pDiv[i];
        pX[i]  = nCarry;
        nCarry = nCarry>>_DIGIT_SIZE_IN_BITS;
    }
    pX[i] = nCarry;
    while ((size_t) -1 != i && 0 == pX[i]) i--;
    return i+1;
}

size_t CUnsignedArithmeticHelper::DivideSubproblemSize(size_t nXSize, size_t nYSize, size_t &nDivOffset)
{
    size_t nSmallY;
    if (nXSize - nYSize < ((nYSize + 1)>>1) + 2)
    {
        // few enough DIGITs of difference left to do the remainder in one half-sized divide and a cleanup divide
        nDivOffset = 0;
        nSmallY    = nXSize - nYSize;
    }
    else
    {
        // do a half-sized divide to get the upper digits, then a second divide to get the rest -- which should be small
        // enough for the previous case.  Thus, break problem into two half-sized divides and a linear (cleanup) divide
        // Pick as our estimate that given by the first (xSize-ySize)/2 DIGITs of y -- that should knock out half the difference
        nSmallY    = (nXSize - nYSize + 1)>>1;
        nDivOffset = nXSize - nYSize - nSmallY;
    }
    return nSmallY;
}

// Break the division into two pieces.  First, find div1 s.t. y*div1 <= x; then solve the problem
// (x - y*div1)/y and combine the results: x mod y is (x - y*div1) mod y and (x/y) is div1 + (x - y*div1)/y
// Now, it's easy to find such a div1 -- 1 will do, for instance.  The key is to find a div1 such that the
// problem is significantly easier, and find it quickly.  Wish to knock out as many digits of x as possible
// (thus getting closer to a solution) without too much work.
// If we use the first few bits of y as the divisor for finding div1, we knock that many bits off of x (roughly)
// since x is not *too* much bigger than y.
// To find div1, let y1 = (y>>bitshift) + 1.
// Then (x>>bitshift)/y1 <= x/y, so we have a candidate for div1
// Further (x>>bitshift) mod y1 == (x>>bitshift) mod ((y>>bitshift) + 1)
//                              == (x>>bitshift) - div1*((y>>bitshift) + 1)
//                              == x>>bitshift - div1*(y>>bitshift) - div1
//                              == yy
// What we want for the second half is x - div1*y -- which is clearly easy to compute from the above:
// x = (x>>bitshift)<<bitshift + x mod(1<<bitshift)
// so x - div1*y == (x>>bitshift)<<bitshift + x mod(1<<bitshift) - div1*((y>>bitshift)<<bitshift + y mod (1<<bitshift)) + div1<<bitshift - div1<<bitshift
//               == (x>>bitshift - div1*(y>>bitshift) - div1 + div1)<<bitshift + x mod(1<<bitshift) -  div1*(y mod (1<<bitshift))
//               == (yy + div1)<<bitshift + x mod(1<<bitshift) - div1*(y mod (1<<bitshift))
// Given what we have from the division giving div1, this at worst requires some linear operations, plus the single
// multiplication div1*(y mod (1<<bitshift))
// Here, it's clear that the local work is the multiplication, plus the recursive work of the two divides.  Lower bitshift
// gives less local work -- but makes the subproblems larger.
// NEVER call this function when X has twice as many digits as y or more!
void CUnsignedArithmeticHelper::DivideRecursive(size_t  nXSize,
                                                size_t  nYSize,
                                                DIGIT   *pXValue,
                                                DIGIT   *pYValue,
                                                DIGIT   *pXDivYValue,
#if(_CollectDetailedTimingData)
                                                DWORD64 &dwTimestamp,
#endif
                                                DIGIT   *pWorkspace)
{
    size_t       i,j,nXDivYSize,nXModYSize,nSmallY,nDivOffset,nLowestAdded,nNumDIGITsDivOverlap;
    DOUBLEDIGIT	 nCarry, nValX, nValProd;
    DIGIT        *pDivSmall,*pXSmall,*pYSmall;
#if(_CollectDetailedTimingData)
    DWORD64 dwProcessTime = 0, dwMultTime, dwTimestamp2;
    dwTimestamp = s_Timer.GetMicroseconds();
#endif
    // if the problem is "small," use the basic algorithm
    if (nYSize < c_nDivideThresholdSmall || nXSize-nYSize < c_nDivideThresholdDiff)
    {
#if(_CollectDetailedTimingData)
        DivideBasic(nXSize, nYSize, pXValue, pYValue, dwTimestamp, pXDivYValue);
#else
        DivideBasic(nXSize, nYSize, pXValue, pYValue, pXDivYValue);
#endif
        return;
    }
    // Break problem down recursively: want to use at most half of y for subproblem
    nSmallY = DivideSubproblemSize(nXSize, nYSize, nDivOffset);
    // y shift: nYSize - nSmallY
    // x shift: nXSize - 2*nSmallY
    // div shift: nXShift-nYShift = nXSize - 2*nSmallY - (nYSize - nSmallY) = nXSize - nYSize - nSmallY
    i          = nYSize      - nSmallY;
    pDivSmall  = pXDivYValue + nDivOffset;                  // section of XDivY used for upper half of division
    pXSmall    = pXValue     + nXSize - 2*nSmallY;          // section of x used for upper half of division
    pYSmall    = pYValue     + i;                           // section of y used for upper half of division
    while(i<nYSize && c_nClearHigh==pYValue[i]) pYValue[i++] = 0;
    bool bSpecialCase = (i == nYSize);
    if (bSpecialCase)
    {
        // Divide by (1<<nSmallYSize).  Can do THAT directly
        for(i=0; i<nSmallY; i++)
        {
            pDivSmall[i]         = pXSmall[nSmallY + i];
            pXSmall[nSmallY + i] = 0;
            pYSmall[i]           = c_nClearHigh; // don't need twiddled y
        }
        pDivSmall[i] =  0;
        nXDivYSize   =  nSmallY;
    }
    else
    {
        pYValue[i]++;
#if(_CollectDetailedTimingData)
        dwTimestamp2                      =  s_Timer.GetMicroseconds();
        g_nDivideTime[eDivideProcessTime] += dwTimestamp2 - dwTimestamp;
        DivideRecursive(nSmallY<<1, nSmallY, pXSmall, pYSmall, pDivSmall, dwTimestamp2, pWorkspace);
        dwTimestamp = dwTimestamp2;
#else
        DivideRecursive(nSmallY<<1, nSmallY, pXSmall, pYSmall, pDivSmall, pWorkspace);
#endif
        nXDivYSize = nSmallY + (0 < pDivSmall[nSmallY]);
    }
    nLowestAdded =  nXSize - nYSize - nSmallY; // index in pXDivY of lowest entry added
    // add Div back into x
    nXSize       = nXSize - (nSmallY<<1) + AddDivBackIn(nSmallY<<1, nSmallY, pXSmall, pDivSmall);
#if(_CollectDetailedTimingData)
    dwMultTime                          =  s_Timer.GetMicroseconds();
    g_nDivideTime[eDivideProcessTime]   += dwMultTime - dwTimestamp;
    dwTimestamp                         =  dwMultTime;
    MultUBackend(nXDivYSize, nYSize-nSmallY, pDivSmall, pYValue, pWorkspace, pWorkspace+nXDivYSize+nYSize-nSmallY, dwTimestamp);
    g_nDivideTime[eDivideMultCallsTime] += dwTimestamp - dwMultTime;
#else
    MultUBackend(nXDivYSize, nYSize-nSmallY, pDivSmall, pYValue, pWorkspace, pWorkspace+nXDivYSize+nYSize-nSmallY);
#endif
    i = nXDivYSize + nYSize-nSmallY;
    if(0==pWorkspace[i-1]) i--;
    nXSize = Subtract(nXSize-nDivOffset, i, pXValue+nDivOffset, pWorkspace, pXValue+nDivOffset) + nDivOffset;
    // restore y to its original state if need be
    if (!bSpecialCase)
    {
        i = nYSize - nSmallY;
        // undo addition of 1 to y
        while (0 == pYValue[i]) pYValue[i++] = c_nClearHigh;
        pYValue[i]--;
    }
    if(nXSize<nYSize)
    {
        // knocked out so much with first half that the problem is done.  Cleanup.
        for(i=0; i<nDivOffset; i++)
        {
            pXDivYValue[i] = 0;
        }
    }
    else
    {
        // if we knocked out LOTS of digits, we skip over parts of the div.  Fill those digits with the appropriate 0s
        for(i=nXSize-nYSize+1; i<nDivOffset; i++) pXDivYValue[i] = 0;
        // solve for the rest of the digits.  The new problem is of size xsize-ysize; we might
        // have a couple DIGITs of overlap.  Save those DIGITs and add them back in afterwards
        nSmallY              = nXSize-nYSize;
        nNumDIGITsDivOverlap = (nLowestAdded <= nSmallY) ? (nSmallY-nLowestAdded+1) : 0;
        for(i=0; i<nNumDIGITsDivOverlap; i++)
        {
            pWorkspace[i]                 = pXDivYValue[nLowestAdded+i];
            pXDivYValue[nLowestAdded + i] = 0;
        }
#if(_CollectDetailedTimingData)
        dwTimestamp2                      =  s_Timer.GetMicroseconds();
        g_nDivideTime[eDivideProcessTime] += dwTimestamp2 - dwTimestamp;
        DivideBackend(nXSize, nYSize, nXDivYSize, j, pXValue, pYValue, pXDivYValue, dwTimestamp2, pWorkspace+nNumDIGITsDivOverlap);
        dwTimestamp = dwTimestamp2;
#else
        DivideBackend(nXSize, nYSize, nXDivYSize, j, pXValue, pYValue, pXDivYValue, pWorkspace+nNumDIGITsDivOverlap);
#endif
        // add overlap digits back into place
        nCarry = 0;
        for(i=0; i<nNumDIGITsDivOverlap; i++)
        {
            nCarry                      = (nCarry + pXDivYValue[nLowestAdded+i]) + pWorkspace[i];
            pXDivYValue[nLowestAdded+i] = nCarry;
            nCarry                      = nCarry>>_DIGIT_SIZE_IN_BITS;
        }
        while(nCarry)
        {
            nCarry                        = nCarry + pXDivYValue[nLowestAdded+i];
            pXDivYValue[nLowestAdded+i++] = nCarry;
            nCarry                        = nCarry>>_DIGIT_SIZE_IN_BITS;
        }
    }
#if(_CollectDetailedTimingData)
    dwTimestamp2                      =  s_Timer.GetMicroseconds();
    g_nDivideTime[eDivideProcessTime] += dwTimestamp2 - dwTimestamp;
    dwTimestamp                       =  dwTimestamp2;
#endif
}

// MUST return a #of pieces that is at least 5 if the size passed is
// at least CExtendedPrecisionInteger::c_pnMultiplicationThresholds[e7By4]
// Note that if this changes in form, we need to change
// ThresholdTestObject::GetParamsForBigProblemDetermination
// in the LongIntegerArithmetic test suite as well!
size_t CUnsignedArithmeticHelper::PiecesByProblemSize(size_t nSize)
{
    size_t nPieces;
    if(nSize<c_pn2NByNBreakpoints[0])
    {
        nPieces = 5;
    }
    else if(nSize<c_pn2NByNBreakpoints[1])
    {
        nPieces = 6;
    }
    else if(nSize<c_pn2NByNBreakpoints[2])
    {
        nPieces = 7;
    }
    else if(nSize<c_pn2NByNBreakpoints[3])
    {
        nPieces = 8;
    }
    else if(nSize<c_pn2NByNBreakpoints[4])
    {
        nPieces = 9;
    }
    else if(nSize<c_pn2NByNBreakpoints[5])
    {
        nPieces = 10;
    }
    else if(nSize<c_pn2NByNBreakpoints[6])
    {
        nPieces = 11;
    }
    else
    {
        // more than 10 pieces will doubtless not be used -- used FFT mult for such large problems!
        nPieces = 12;
    }
    return nPieces;
}

size_t CUnsignedArithmeticHelper::PiecesByProblemSizeSquare(size_t nSize)
{
    size_t nPieces;
    if(nSize<c_pn2NByNSquareBreakpoints[0])
    {
        nPieces = 5;
    }
    else if(nSize<c_pn2NByNSquareBreakpoints[1])
    {
        nPieces = 6;
    }
    else if(nSize<c_pn2NByNSquareBreakpoints[2])
    {
        nPieces = 7;
    }
    else if(nSize<c_pn2NByNSquareBreakpoints[3])
    {
        nPieces = 8;
    }
    else if(nSize<c_pn2NByNSquareBreakpoints[4])
    {
        nPieces = 9;
    }
    else if(nSize<c_pn2NByNSquareBreakpoints[5])
    {
        nPieces = 10;
    }
    else if(nSize<c_pn2NByNSquareBreakpoints[6])
    {
        nPieces = 11;
    }
    else
    {
        // more than 10 pieces will doubtless not be used -- used FFT mult for such large problems!
        nPieces = 10;
    }
    return nPieces;
}

size_t CUnsignedArithmeticHelper::GCD(size_t nXSize,
                                      size_t nYSize,
                                      DIGIT  *pXValue,
                                      DIGIT  *pYValue,
                                      DIGIT  *pGCDValue,
                                      DIGIT  *pWorkspace)
{
    size_t  nGCDSize;
#if _CollectDetailedTimingData
    DWORD64 dwTimestamp  = s_Timer.GetMicroseconds();
    DWORD64 dwTimestamp2 = dwTimestamp;
    g_nGCDTime[eTotalGCDCalls]++;
#endif
    // copy the base values into the workspace -- GCDBase is destructive!
    memcpy(pWorkspace,pXValue,nXSize*sizeof(DIGIT));
    memcpy(pWorkspace+nXSize,pYValue,nYSize*sizeof(DIGIT));
    // chose order for operands -- GCDBase assumes the larger
    // of (x, y) is the first given.
#if _CollectDetailedTimingData
    dwTimestamp                 =  s_Timer.GetMicroseconds();
    g_nGCDTime[eGCDProcessTime] += (dwTimestamp - dwTimestamp2);
#endif
    if(0<=CBigInteger::CompareUnsigned(nXSize,nYSize,pXValue,pYValue))
    {
        // x is the larger
        nGCDSize = GCDBase(nXSize,
                           nYSize,
                           pWorkspace,
                           pWorkspace+nXSize,
                           pGCDValue,
#if _CollectDetailedTimingData
                           dwTimestamp,
#endif
                           pWorkspace+nXSize+nYSize);
    }
    else
    {
        // Y is the larger
        nGCDSize = GCDBase(nYSize,
                           nXSize,
                           pWorkspace+nXSize,
                           pWorkspace,
                           pGCDValue,
#if _CollectDetailedTimingData
                           dwTimestamp,
#endif
                           pWorkspace+nXSize+nYSize);
    }
#if _CollectDetailedTimingData
    g_nGCDTime[eGCDTotalTime] += (dwTimestamp - dwTimestamp2);
#endif
    return nGCDSize;
}

void CUnsignedArithmeticHelper::GCD(size_t nXSize,
                                    size_t nYSize,
                                    size_t &nGCDSize,
                                    size_t &nXCoefSize,
                                    size_t &nYCoefSize,
                                    DIGIT  *pXValue,
                                    DIGIT  *pYValue,
                                    DIGIT  *pGCDValue,
                                    DIGIT  *pXCoefValue,
                                    DIGIT  *pYCoefValue,
                                    bool   &bXCoefNegative,
                                    DIGIT  *pWorkspace)
{
#if _CollectDetailedTimingData
    DWORD64 dwTimestamp  = s_Timer.GetMicroseconds();
    DWORD64 dwTimestamp2 = dwTimestamp;
    g_nGCDTime[eTotalGCDCalls]++;
#endif
    // if either X or Y is 0, do directly -- back-end functions don't deal with 0 operand well.
    // (If BOTH are 0, we end up with a GCD of 0.)
    if(0==nXSize)
    {
        nXCoefSize     = 0;
        bXCoefNegative = true; // or, in this case, the y coefficient is NOT negative
        if (NULL != pYCoefValue)
        {
            nYCoefSize   = 1;
            *pYCoefValue = 1;
        }
    }
    else if(0==nYSize)
    {
        nYCoefSize     = 0;
        bXCoefNegative = false;
        if (NULL != pXCoefValue)
        {
            nXCoefSize   = 1;
            *pXCoefValue = 1;
        }
    }
    else
    {
        // chose order for operands -- GCDBase assumes the larger
        // of (x, y) is the first given.
        if(0<=CBigInteger::CompareUnsigned(nXSize,nYSize,pXValue,pYValue))
        {
            // x is the larger
            GCDCoef(nXSize,
                    nYSize,
                    nGCDSize,
                    nXCoefSize,
                    nYCoefSize,
                    pXValue,
                    pYValue,
                    pGCDValue,
                    pXCoefValue,
                    pYCoefValue,
                    bXCoefNegative,
#if _CollectDetailedTimingData
                    dwTimestamp,
#endif
                    pWorkspace);
        }
        else
        {
            // Y is the larger
            GCDCoef(nYSize,
                    nXSize,
                    nGCDSize,
                    nYCoefSize,
                    nXCoefSize,
                    pYValue,
                    pXValue,
                    pGCDValue,
                    pYCoefValue,
                    pXCoefValue,
                    bXCoefNegative,
#if _CollectDetailedTimingData
                    dwTimestamp,
#endif
                    pWorkspace);
            // swap xcoef sign -- doing in reverse expected order!
            bXCoefNegative = !bXCoefNegative;
        }
    }
#ifdef _DEBUG
    // validate correctly computed coefficients in debug build if both were asked for (and we didn't
    // overwrite x or y -- CAN compute the GCD using either as an output destination):
    // should be the case that x*xcoef + y*ycoef = gcd
    if (pYCoefValue && pXCoefValue && pXCoefValue != pXValue && pXCoefValue != pYValue && pYCoefValue != pXValue && pYCoefValue != pYValue && pGCDValue != pXValue && pGCDValue != pYValue)
    {
        bool   bSumNeg;
        size_t nXXcoefSize   = nXSize + nXCoefSize, nYYcoefSize = nYSize + nYCoefSize, nSumSize;
        DIGIT  *pXTimesXCoef = pWorkspace;
        DIGIT  *pYTimesYCoef = pXTimesXCoef + nXXcoefSize;
        pWorkspace = pYTimesYCoef + nYYcoefSize;
        // x*xcoef
        if (nXCoefSize)
        {
#if _CollectDetailedTimingData
            MultUBackend(nXSize, nXCoefSize, pXValue, pXCoefValue, pXTimesXCoef, pWorkspace, dwTimestamp);
#else
            MultUBackend(nXSize, nXCoefSize, pXValue, pXCoefValue, pXTimesXCoef, pWorkspace);
#endif
            if (0 == pXTimesXCoef[nXXcoefSize - 1]) nXXcoefSize--;
        }
        else
        {
            nXXcoefSize = 0;
        }
        // y*ycoef
        if (nYCoefSize)
        {
#if _CollectDetailedTimingData
            MultUBackend(nYSize, nYCoefSize, pYValue, pYCoefValue, pYTimesYCoef, pWorkspace, dwTimestamp);
#else
            MultUBackend(nYSize, nYCoefSize, pYValue, pYCoefValue, pYTimesYCoef, pWorkspace);
#endif
            if (0 == pYTimesYCoef[nYYcoefSize - 1]) nYYcoefSize--;
        }
        else
        {
            nYYcoefSize = 0;
        }
        // x*xcoef + y*ycoef
        AddSigned(nXXcoefSize, nYYcoefSize, nSumSize, pXTimesXCoef, pYTimesYCoef, pWorkspace, bXCoefNegative, !bXCoefNegative, bSumNeg);
        if (bSumNeg || 0 != CBigInteger::CompareUnsigned(nSumSize, nGCDSize, pWorkspace, pGCDValue))
        {
            printf("Problems: coefs (or GCD) not correctly computed\n");
        }
    }
#endif
#if _CollectDetailedTimingData
    g_nGCDTime[eGCDTotalTime] += (dwTimestamp - dwTimestamp2);
#endif
}

size_t CUnsignedArithmeticHelper::GCDBase(size_t  nXSize,
                                          size_t  nYSize,
                                          DIGIT   *pXValue,
                                          DIGIT   *pYValue,
                                          DIGIT   *pGCDValue,
#if(_CollectDetailedTimingData)
                                          DWORD64 &dwTimestamp,
#endif
                                          DIGIT   *pWorkspace)
{
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp2;
#endif
    DIGIT   *pHold;
    size_t  nDivSize, nModSize;
    do
    {
#if(_CollectDetailedTimingData)
        dwTimestamp2 = dwTimestamp;
        DivideBackend(nXSize,
                      nYSize,
                      nDivSize, // actually don't care about this value
                      nModSize,
                      pXValue,
                      pYValue,
                      pWorkspace,
                      dwTimestamp,
                      pWorkspace+nXSize-nYSize+1);
        g_nGCDTime[eGCDDivideTime] += (dwTimestamp - dwTimestamp2);
#else
        DivideBackend(nXSize,
                      nYSize,
                      nDivSize, // actually don't care about this value
                      nModSize,
                      pXValue,
                      pYValue,
                      pWorkspace,
                      pWorkspace+nXSize-nYSize+1);
#endif
        if(0==nModSize)
        {
            break;
        }
        nXSize  = nYSize;
        nYSize  = nModSize;
        pHold   = pXValue;
        pXValue = pYValue;
        pYValue = pHold;
    }
    while(1);
    for(size_t i=0; i<nYSize; i++)
    {
        pGCDValue[i] = pYValue[i];
    }
#if(_CollectDetailedTimingData)
    dwTimestamp2               =  dwTimestamp;
    dwTimestamp                =  s_Timer.GetMicroseconds();
    g_nGCDTime[eGCDDivideTime] += (dwTimestamp - dwTimestamp2);
#endif
    return nYSize;
}

// Algorithm:
// function extended_gcd(a, b)
//     s <- 0;    old_s <- 1
//     t <- 1;    old_t <- 0
//     r <- b;    old_r <- a
//     while r ? 0
//         quotient <- old_r div r
//         (old_r, r) <- (r, old_r - quotient * r) <-> (old_r, r) <- (r, old_r%r)
//         (old_s, s) <- (s, old_s - quotient * s)
//         (old_t, t) <- (t, old_t - quotient * t)
//         output "Bézout coefficients:", (old_s, old_t)
//         output "greatest common divisor:", old_r
//         output "quotients by the gcd:", (t, s)
// old_r <-> GCD
// old_s <-> coef for x
// old_t <-> coef for y
//
// Now, this computes both coefficients as we go -- so at each step, 2 multiply/adds.
// But note that the computations are independent -- we don't need the x coefficient to
// get the y, for example.  So we could just compute one of the two coefficients
// as we go along, then note that if g = gcd(x, y) and ax + by = g then
// b = (g-ax)/y -- so we need only do a single add/divide at the end and t, old_t are not needed
// And if the y coef is not asked for (NULL passed) need not even do that
void CUnsignedArithmeticHelper::GCDCoef(size_t  nXSize,
                                        size_t  nYSize,
                                        size_t  &nGCDSize,
                                        size_t  &nXCoefSize,
                                        size_t  &nYCoefSize,
                                        DIGIT   *pXValue,
                                        DIGIT   *pYValue,
                                        DIGIT   *pGCDValue,
                                        DIGIT   *pXCoefValue,
                                        DIGIT   *pYCoefValue,
                                        bool    &bXCoefNegative,
#if(_CollectDetailedTimingData)
                                        DWORD64 &dwTimestamp,
#endif
                                        DIGIT   *pWorkspace)
{
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp2;
#endif
    if(nYSize*sizeof(DIGIT) <= c_nMaxBYTESizeForRecursiveGCD && NULL != pXCoefValue && NULL != pYCoefValue)
    {
        // use recursive version.  It's faster when we want both coefficients, but blows out the stack for large x, y
        // Note that it also destroys the X, Y values so we need to make copies first
        // copy the base values into the workspace -- GCDBase is destructive!
        memcpy(pWorkspace,pXValue,nXSize*sizeof(DIGIT));
        memcpy(pWorkspace+nXSize,pYValue,nYSize*sizeof(DIGIT));
#if(_CollectDetailedTimingData)
        dwTimestamp2                =  s_Timer.GetMicroseconds();
        g_nGCDTime[eGCDProcessTime] += (dwTimestamp2 - dwTimestamp);
        dwTimestamp                 =  dwTimestamp2;
        GCDCoef_recursive(nXSize, nYSize, nGCDSize, nXCoefSize, nYCoefSize, pWorkspace, pWorkspace+nXSize, pGCDValue, pXCoefValue, pYCoefValue, bXCoefNegative, dwTimestamp, pWorkspace+nXSize+nYSize);
#else
        GCDCoef_recursive(nXSize, nYSize, nGCDSize, nXCoefSize, nYCoefSize, pWorkspace, pWorkspace+nXSize, pGCDValue, pXCoefValue, pYCoefValue, bXCoefNegative, pWorkspace+nXSize+nYSize);
#endif
        return;
    }
    size_t nQuotientSize, nRemainderSize, nProductSize, nSSize, nSSize_old;
    DIGIT  *pHold;
    bool   bHold, bSumNeg;
    size_t nNumberSpace = max(nXSize, nYSize);
    size_t nOrigXSize   = nXSize;
    size_t nOrigYSize   = nYSize;
    bool   bSNeg        = false;
    bool   bSNeg_old    = false;
    DIGIT  *pR          = pGCDValue;
    DIGIT  *pR_old      = pWorkspace;
    DIGIT  *pS          = (pXCoefValue) ? pXCoefValue : pYCoefValue;
    DIGIT  *pS_old      = pR_old    + nNumberSpace + 1; // one extra DIGIT for overflow protection
    DIGIT  *pQuotient   = pS_old    + nNumberSpace + 1;
    DIGIT  *pProduct    = pQuotient + nNumberSpace;
    if(NULL==pXCoefValue)
    {
        // compute y coef directly instead of the usual x coef
        nSSize     = 1;
        nSSize_old = 0;
        *pS        = 1;
    }
    else
    {
        nSSize     = 0;
        nSSize_old = 1;
        *pS_old    = 1;
    }
    pWorkspace = pProduct + (nNumberSpace<<1);
    // Divides are destructive!  Copy x, y
    memcpy(pR_old, pXValue, nOrigXSize*sizeof(DIGIT));
    memcpy(pR, pYValue, nOrigYSize*sizeof(DIGIT));
    do
    {
        // R, R_old: (old_r, r) <- (r, old_r - quotient * r) <-> (old_r, r) <- (r, old_r%r)
#if(_CollectDetailedTimingData)
        dwTimestamp2                =  s_Timer.GetMicroseconds();
        g_nGCDTime[eGCDProcessTime] += (dwTimestamp2 - dwTimestamp);
        DivideBackend(nXSize,
                      nYSize,
                      nQuotientSize,
                      nRemainderSize,
                      pR_old,
                      pR,
                      pQuotient,
                      dwTimestamp,
                      pWorkspace);
        g_nGCDTime[eGCDDivideTime] += (dwTimestamp - dwTimestamp2);
#else
        DivideBackend(nXSize,
                      nYSize,
                      nQuotientSize,
                      nRemainderSize,
                      pR_old,
                      pR,
                      pQuotient,
                      pWorkspace);
#endif
        if (0 == nRemainderSize) break;
        nXSize = nYSize;
        nYSize = nRemainderSize;
        pHold  = pR;
        pR     = pR_old;
        pR_old = pHold;
        if (0 == nQuotientSize)
        {
            // S, S_old just swap
            pHold         = pS;
            pS            = pS_old;
            pS_old        = pHold;
            nQuotientSize = nSSize;
            nSSize        = nSSize_old;
            nSSize_old    = nQuotientSize;
            bHold         = bSNeg;
            bSNeg         = bSNeg_old;
            bSNeg_old     = bHold;
        }
        else
        {
            // S: (old_s, s) <- (s, old_s - quotient * s)
            if(0==nSSize)
            {
                // again, just swap
                pHold         = pS;
                pS            = pS_old;
                pS_old        = pHold;
                nSSize        = nSSize_old;
                nSSize_old    = 0;
                bSNeg         = bSNeg_old;
                bSNeg_old     = false; // size 0 -> not negative
            }
            else
            {
#if _CollectDetailedTimingData
                dwTimestamp2 = dwTimestamp;
                dwTimestamp  = s_Timer.GetMicroseconds();
                MultUBackend(nSSize, nQuotientSize, pS, pQuotient, pProduct, pWorkspace, dwTimestamp);
                g_nGCDTime[eGCDMultiplyTime] += (dwTimestamp - dwTimestamp2);
#else
                MultUBackend(nSSize, nQuotientSize, pS, pQuotient, pProduct, pWorkspace);
#endif
                pProduct[nSSize + nQuotientSize] = 0;
                nProductSize = nSSize + nQuotientSize;
                if(0 == pProduct[nProductSize-1]) nProductSize--;
                AddSigned(nSSize_old, nProductSize, nProductSize, pS_old, pProduct, pS_old, bSNeg_old, !bSNeg, bSumNeg);
                // now:
                // pS_old contains old_s - quotient*s
                // pS contains s
                // both have same allocated space
                // -> swap pointers around rather than copy
                pHold      = pS;
                bSNeg_old  = bSNeg;
                nSSize_old = nSSize;
                pS         = pS_old;
                bSNeg      = bSumNeg;
                nSSize     = nProductSize;
                pS_old     = pHold;
            }
        }
    }
    while (1);
    nGCDSize = nYSize;
    if (pGCDValue != pR)
    {
        // didn't put GCD in the right place; copy it over
        memcpy(pGCDValue, pR, nGCDSize*sizeof(DIGIT));
    }
    if(NULL==pXCoefValue)
    {
        // actually computed y coef and CALLED it x
        bXCoefNegative = !bSNeg;
        nYCoefSize     = nSSize;
        if(pS != pYCoefValue)
        {
            // happens half the time -- pS in "wrong" slot; copy it into right one (guessed wrong initially)
            memcpy(pYCoefValue, pS, nYCoefSize*sizeof(DIGIT));
        }
    }
    else
    {
        bXCoefNegative = bSNeg;
        nXCoefSize     = nSSize;
        if(pS != pXCoefValue)
        {
            // happens half the time -- pS in "wrong" slot; copy it into right one (guessed wrong initially)
            memcpy(pXCoefValue, pS, nXCoefSize*sizeof(DIGIT));
        }
#if _CollectDetailedTimingData
        dwTimestamp2                =  dwTimestamp;
        dwTimestamp                 =  s_Timer.GetMicroseconds();
        g_nGCDTime[eGCDProcessTime] += (dwTimestamp - dwTimestamp2);
#endif
        if (NULL != pYCoefValue)
        {
            // want y coef, too
            // have the GCD and x coefficient at this point.  Compute the y coefficient:
            // <y coef> = (gcd - <x coef>x)/y
#if 0 // nice idea; doesn't help
            if (s_nGCDThreshold < nGCDSize)
            {
                // compute with extra small operations
                // Note that <y coef> = (gcd - <x coef>x)/y
                // is equivalent to
                // (1 - <x-coef><x/gcd>)/(y/gcd)
                // If the GCD is large, the extra ops to pull it out will be justified by the reduced size of the ops needed
                // Use pR_old, pS_old as workspace -- don't need the values contained there anymore
                DIGIT *pSlot1 = (pXCoefValue) ? ((pXCoefValue==pS) ? pS_old : pS) : ((pYCoefValue == pS) ? pS_old : pS);
                DIGIT *pSlot2 = (pR==pGCDValue) ? pR_old : pR;
                // Compute x/gcd.  Note that the divide destroys the x value, so copy it.
                memcpy(pSlot1, pXValue, nOrigXSize * sizeof(DIGIT));
                Divide(nOrigXSize,
                       nGCDSize,
                       nQuotientSize,
                       nRemainderSize,
                       pSlot1,
                       pGCDValue,
                       pSlot2,
                       pWorkspace);
                // Compute xCoef*(x/gcd)
                nProductSize = nQuotientSize + nXCoefSize;
#if _CollectDetailedTimingData
                DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
                MultUBackend(nQuotientSize, nXCoefSize, pSlot2, pXCoefValue, pWorkspace, pWorkspace + nProductSize, dwTimestamp);
#else
                MultUBackend(nQuotientSize, nXCoefSize, pSlot2, pXCoefValue, pWorkspace, pWorkspace + nProductSize);
#endif
                if (0 == pWorkspace[nProductSize - 1]) nProductSize--;
                // Compute xCoef*(x/gcd) - 1
                size_t i = 0; // note this has troubles if x == 0 -- but should never be in this function in that case in the first place
                if (bXCoefNegative)
                {
                    pWorkspace[nProductSize] = 0; // on the off chance have DIGITS that are all FFFF
                    while (c_nClearHigh == pWorkspace[i])
                    {
                        pWorkspace[i++] = 0;
                    }
                    pWorkspace[i]++;
                    if (i == nProductSize) nProductSize++;
                }
                else
                {
                    while (0 == pWorkspace[i])
                    {
                        pWorkspace[i++] = c_nClearHigh;
                    }
                    pWorkspace[i]--;
                    if (0 == pWorkspace[nProductSize - 1]) nProductSize--;
                }
                // Compute y/gcd.  Note that the divide destroys the y value, so copy it.
                memcpy(pSlot1, pYValue, nOrigYSize*sizeof(DIGIT));
                Divide(nOrigYSize, nGCDSize, nQuotientSize, nRemainderSize, pSlot1, pGCDValue, pSlot2, pWorkspace + nProductSize);
                // Compute (1 - <x-coef><x/gcd>)/(y/gcd)
                Divide(nProductSize, nQuotientSize, nYCoefSize, nRemainderSize, pWorkspace, pSlot2, pYCoefValue, pWorkspace + nProductSize);
            }
            else
#endif
            {
                // GCD isn't big enough to make it worthwhile to divide out by it
                nProductSize = nXCoefSize + nOrigXSize;
#if _CollectDetailedTimingData
                dwTimestamp2 = dwTimestamp;
                MultUBackend(nXCoefSize, nOrigXSize, pXCoefValue, pXValue, pWorkspace, pWorkspace + nProductSize, dwTimestamp);
                g_nGCDTime[eGCDMultiplyTime] += (dwTimestamp - dwTimestamp2);
#else
                MultUBackend(nXCoefSize, nOrigXSize, pXCoefValue, pXValue, pWorkspace, pWorkspace + nProductSize);
#endif
                pWorkspace[nProductSize] = 0; // prevent overflow
                if (0 == pWorkspace[nProductSize - 1]) nProductSize--;
#if _CollectDetailedTimingData
                AddSigned(nProductSize, nGCDSize, nQuotientSize, pWorkspace, pGCDValue, pWorkspace, !bXCoefNegative, false, bSumNeg);
                dwTimestamp2                =  dwTimestamp;
                dwTimestamp                 =  s_Timer.GetMicroseconds();
                g_nGCDTime[eGCDProcessTime] += (dwTimestamp - dwTimestamp2);
                DivideBackend(nQuotientSize, nOrigYSize, nYCoefSize, nRemainderSize, pWorkspace, pYValue, pYCoefValue, dwTimestamp2, pWorkspace + nQuotientSize);
                g_nGCDTime[eGCDDivideTime]  += (dwTimestamp2 - dwTimestamp);
                dwTimestamp                 =  dwTimestamp2;
#else
                AddSigned(nProductSize, nGCDSize, nQuotientSize, pWorkspace, pGCDValue, pWorkspace, !bXCoefNegative, false, bSumNeg);
                DivideBackend(nQuotientSize, nOrigYSize, nYCoefSize, nRemainderSize, pWorkspace, pYValue, pYCoefValue, pWorkspace + nQuotientSize);
#endif
            }
        }
    }
}

// old version.  Works, but blows out the stack for X, Y in the low 100s of digits.  But faster for small  X, Y -- so use it there (only)
void CUnsignedArithmeticHelper::GCDCoef_recursive(size_t  nXSize,
                                                  size_t  nYSize,
                                                  size_t  &nGCDSize,
                                                  size_t  &nXCoefSize,
                                                  size_t  &nYCoefSize,
                                                  DIGIT   *pXValue,
                                                  DIGIT   *pYValue,
                                                  DIGIT   *pGCDValue,
                                                  DIGIT   *pXCoefValue,
                                                  DIGIT   *pYCoefValue,
                                                  bool    &bXCoefNegative,
#if(_CollectDetailedTimingData)
                                                  DWORD64 &dwTimestamp,
#endif
                                                  DIGIT   *pWorkspace)
{
    size_t  i,j,nXDivYSize,nXModYSize;
    size_t  nXDivYSpace=nXSize-nYSize+1;
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp2 = dwTimestamp;
    DivideBackend(nXSize, nYSize, nXDivYSize, nXModYSize, pXValue, pYValue, pWorkspace, dwTimestamp, pWorkspace + nXDivYSpace);
    g_nGCDTime[eGCDDivideTime] += (dwTimestamp - dwTimestamp2);
#else
    DivideBackend(nXSize,nYSize,nXDivYSize,nXModYSize,pXValue,pYValue,pWorkspace,pWorkspace+nXDivYSpace);
#endif
    // set the size of X to that of the computed X mod Y (remainder)
    if(0==nXModYSize)  // found the GCD: y
    {
        for(i=0;i<nYSize;i++)
        {
            pGCDValue[i] = pYValue[i];
        }
        nGCDSize       = nYSize;
        nXCoefSize     = 0;
        nYCoefSize     = 1;
        pYCoefValue[0] = 1;
        bXCoefNegative = true; // to force the y coef to be positive; in fact, 0 *should* be positive, too
    }
    else
    {
        // Now, a bit of care must be taken.  We know that if
        // y does not evenly divide x, the XCoefValue and YCoefValue coeficients
        // must have opposite signs; we need to keep track of
        // which is which.
        // Suppose YCoefValue' is positive in solving a'y + YCoefValue'(x mod y)
        // Then a = YCoefValue' is positive, and YCoefValue = a' - (x/y)YCoefValue' is
        // negative.  So the signs of XCoefValue and YCoefValue flip with each
        // recursive call
        // at this point x contains the remainder of x/y -- x mod y --
        // and pWorkspace contains x/y.
        GCDCoef_recursive(nYSize,
                          nXModYSize,
                          nGCDSize,
                          nYCoefSize,
                          nXCoefSize,
                          pYValue,
                          pXValue,
                          pGCDValue,
                          pYCoefValue,
                          pXCoefValue,
                          bXCoefNegative,
#if(_CollectDetailedTimingData)
                          dwTimestamp,
#endif
                          pWorkspace+nXDivYSpace);
        bXCoefNegative = !bXCoefNegative; // sign flips with each step
        // Algorithm:   Euler's method: if d is the gcd of u and v, then
        //              a'v + b'(u mod v) = d <=> b'u + (a' - (u/v)b')v = d.
        //              So solving ax + by = d reduces to solving
        //              a'y + b'(x mod y) = d (recall that d is the gcd of
        //              x and y iff 0<d<=x,y and there exists a, b s.t.
        //              ax + by = d)
        //              Then, a = b' and b = a' - (x/y)b'.
#if _CollectDetailedTimingData
        dwTimestamp2 = dwTimestamp;
        MultUBackend(nXDivYSize,
                     nXCoefSize,
                     pWorkspace,
                     pXCoefValue,
                     pWorkspace+nXDivYSpace,
                     pWorkspace+nXDivYSpace+nXDivYSize+nXCoefSize,
                     dwTimestamp);
        g_nGCDTime[eGCDMultiplyTime] += (dwTimestamp - dwTimestamp2);
#else
        MultUBackend(nXDivYSize,
                     nXCoefSize,
                     pWorkspace,
                     pXCoefValue,
                     pWorkspace+nXDivYSpace,
                     pWorkspace+nXDivYSpace+nXDivYSize+nXCoefSize);
#endif
        j = nXDivYSize+nXCoefSize;
        if(0 == pWorkspace[nXDivYSpace+j-1])
        {
            j--;
        }
        // Note that a' and pYCoefValue' always have opposite signs (since x, y assumed positive),
        // and x/y is always positive, so |a' - (x/y)pYCoefValue'|
        // can always be computed by addition.
        nYCoefSize = Add(nYCoefSize,
                         j,
                         pYCoefValue,
                         pWorkspace+nXDivYSpace,
                         pYCoefValue);
    }
#if _CollectDetailedTimingData
    dwTimestamp2                =  dwTimestamp;
    dwTimestamp                 =  s_Timer.GetMicroseconds();
    g_nGCDTime[eGCDProcessTime] += (dwTimestamp - dwTimestamp2);
#endif
}

// Synopsis:	The idea of divide-and-conquer multiplication, using
//              the same method of problem reduction, taken to its logical
//              conclusion: breaking it into (2n-1) multiplications of
//              (roughly) one nth the size (e.g. 9 multiplications of
//              one fifth the size, eleven of one sixth, etc.).
//              This procedure generates the "rules" needed for the
//              multiplication: given n, it returns how to perform
//              the multiplication using 2n-1 smaller multiplications
//              of one nth the size.
//              Note: this should NOT be called for n less than 5 --
//              for those sizes, use the hardwired procedures.
//
// Algorithm:   Consider multiplying the integers (written as vectors
//              of "digits")
//              (x(0),x(1),x(2),...,x(n)) and (y(0),y(1),y(2),...,y(n))
//              Let p(m) = sum(x(i)*y(j), i+j = m)
//              Then (ignoring carrying) x*y = (p(0),p(1),...,p(2n))
//              For the smaller multiplications, let
//              r(0)  = x(0)*y(0)
//              r(2n) = x(n)*y(n)
//              r(m)  = (x(0) + mx(1) + m^2x(2) + ... + m^nx(n))*
//                      (y(0) + my(1) + m^2y(2) + ... + m^ny(n)), 0<m<2n
//              It is clear that r(0) = p(0), r(2n) = p(2n), and
//              r(m) = p(0) + mp(1) + m^2p(2) + ... + m^(2n)p(2n)
//              This gives a system of 2n+1 equations in 2n+1 unknowns,
//              from which we can get the p(m)s (unknown) from the r(i)s
//              (known).
//              Note: there are many other systems of equations that can
//              be used in place of the one described: in general, r(m)
//              can take the form
//              (a^nx(0) + a^(n-1)bx(1) + a^(n-2)b^2x(2) + ... + b^nx(n)) *
//              (a^ny(0) + a^(n-1)by(1) + a^(n-2)b^2y(2) + ... + b^ny(n))
//              giving
//              r(m) = a^(2n)p(0) + a^(2n-1)bp(1) + ... + b^(2n)p(2n)
//              The system chosen has two advantages: first, it is simple.
//              Second, it seems to give the best balance between the size
//              of the coefficients needed to compute the r(i)s and the
//              size of the coeficients in the inversion matrix (which grow
//              with the size of the system).  It is desirable (but not
//              necessary) to avoid negative coefficients in the computation
//              of the r(i)s, so that sign can be ignored.  (In the inversion
//              matrix, it will appear.  However it can still be ignored to
//              some degree, as each p(i) is clearly nonnegative.)
//              Assymptotically, breaking the system into 2n-1 pieces of
//              one nth the size gives Theta(n^(log_n(2n-1))); this goes
//              to linear as n goes to infinity.  Since the coefficients
//              *also* grow, however, you can't simply split an n-digit
//              number into n pieces and expect good results.  Assuming
//              I'm right about the growth rate of the coefficients, the
//              correct number of pieces to split an n-digit number into
//              grows as exp(log(sqrt(n))), for overall performance of
//              n*exp(log(sqrt(n))) -- better than n^(1+r) for all r>0,
//              but worse than nln(n)^r for all r>0.  (The coefficients
//              need to be arrived at heuristically; they will vary
//              somewhat based on the computer, compiler, etc.)
//
//----------------------------------------------------------

SSystemData *CUnsignedArithmeticHelper::GenerateSystem(size_t n)
{
    SSystemDataNode *pSystemDataNode;
    if(n<5)
    {
        // should only happen in testing for getting the right parameter values
        // for 2N bu N multiplication
        SSystemData *pData = new SSystemData();
        pData->Init(n);
        return pData;
    }
    if(NULL == g_pInversionStructures)
    {
        g_pInversionStructures = new SSystemDataNode();
    }
    pSystemDataNode = g_pInversionStructures;
    size_t nIndex = n - 5;
    if(nIndex>4)
    {
        do
        {
            if(pSystemDataNode->m_pNext==NULL)
            {
                pSystemDataNode->m_pNext = new SSystemDataNode();
            }
            nIndex -= 5;
            pSystemDataNode = pSystemDataNode->m_pNext;
        }
        while(nIndex>4);
    }
    if(NULL == pSystemDataNode->m_pData[nIndex].m_pppCoefficientsPi)
    {
        pSystemDataNode->m_pData[nIndex].Init(n);
    }
    return (pSystemDataNode->m_pData)+nIndex;
}

void CUnsignedArithmeticHelper::ConstructArgumentsFor2NByNSubproblems(size_t             nSubproblemSize,
                                                                      size_t             nNumPieces,
                                                                      size_t             nXSize,
                                                                      size_t             nYSize,
                                                                      size_t             nMaxRIOpSize,
                                                                      size_t             nOverflowSize,
                                                                      DIGIT              **ppnRi,
                                                                      size_t             *pnRiOpSizes,
                                                                      const DIGIT        *pnX,
                                                                      const DIGIT        *pnY,
                                                                      DIGIT              *pnOverflowDigits,
                                                                      SSystemData        *pSystemToUse,
#if(_CollectDetailedTimingData)
                                                                      DWORD64            &dwTimestamp, // on entry, time called.  On exit, time completed
#endif
                                                                      DIGIT              *pnWorkspace)
{
    size_t       i, j, nOffset, nCoefSize, nMultSize, nChunkOffset, nPieceSize, nSmallXSize, nSmallYSize;
    nPieceSize = c_nBuildBlockSizePre;
    for(nChunkOffset = 0; nChunkOffset<nSubproblemSize; nChunkOffset += c_nBuildBlockSizePre)
    {
        if(nChunkOffset+nPieceSize>nSubproblemSize)
        {
            nPieceSize = nSubproblemSize-nChunkOffset;
        }
        // Compute the operands for the r(i)s
        // Note that for each, the zeroth piece is 1*x(0) and 1*y(0)
        // nNumPieces-1 chunk: x(nNumPieces-1) and y(nNumPieces-1) for r(0); coef*(same) for rest
        // todo: try splitting into separate loops for x & y
        memcpy(ppnRi[0]+nChunkOffset,pnX+nChunkOffset,nPieceSize*sizeof(DIGIT));
        memcpy(ppnRi[0]+nChunkOffset+nMaxRIOpSize,pnY+nChunkOffset,nPieceSize*sizeof(DIGIT));
        ppnRi[0][nChunkOffset+nPieceSize]                = 0;
        ppnRi[0][nChunkOffset+nPieceSize+nMaxRIOpSize]   = 0;
        ppnRi[0][nChunkOffset+nPieceSize+1]              = 0;  // needed?
        ppnRi[0][nChunkOffset+nPieceSize+nMaxRIOpSize+1] = 0;  // needed?
        nOffset                                          = nSubproblemSize;
        if(0<nChunkOffset)
        {
            // may have overflow from previous pass
            nSmallXSize = nOverflowSize;
            if(0==pnOverflowDigits[nSmallXSize-1])
            {
                do
                {
                    nSmallXSize--;
                }
                while(0<nSmallXSize && 0==pnOverflowDigits[nSmallXSize-1]);
            }
            nSmallYSize = nPieceSize;
            if(0==ppnRi[0][nChunkOffset+nSmallYSize-1])
            {
                do
                {
                    nSmallYSize--;
                }
                while(0<nSmallYSize && 0==ppnRi[0][nChunkOffset+nSmallYSize-1]);
            }
            // AddU expects smaller operand second
            if(nSmallYSize>nSmallXSize)
            {
                pnRiOpSizes[0] = Add(nSmallYSize,
                                     nSmallXSize,
                                     ppnRi[0]+nChunkOffset,
                                     pnOverflowDigits,
                                     ppnRi[0]+nChunkOffset);
            }
            else
            {
                pnRiOpSizes[0] = Add(nSmallXSize,
                                     nSmallYSize,
                                     pnOverflowDigits,
                                     ppnRi[0]+nChunkOffset,
                                     ppnRi[0]+nChunkOffset);
            }
            nSmallXSize = nOverflowSize;
            if(0==pnOverflowDigits[nOverflowSize+nSmallXSize-1])
            {
                do
                {
                    nSmallXSize--;
                }
                while(0<nSmallXSize && 0==pnOverflowDigits[nOverflowSize+nSmallXSize-1]);
            }
            nSmallYSize = nPieceSize;
            if(0==ppnRi[0][nChunkOffset+nMaxRIOpSize+nSmallYSize-1])
            {
                do
                {
                    nSmallYSize--;
                }
                while(0<nSmallYSize && 0==ppnRi[0][nChunkOffset+nMaxRIOpSize+nSmallYSize-1]);
            }
            // AddU expectes smaller operand second
            if(nSmallYSize>nSmallXSize)
            {
                pnRiOpSizes[1] = Add(nSmallYSize,
                                     nSmallXSize,
                                     ppnRi[0]+nChunkOffset+nMaxRIOpSize,
                                     pnOverflowDigits+nOverflowSize,
                                     ppnRi[0]+nChunkOffset+nMaxRIOpSize);
            }
            else
            {
                pnRiOpSizes[1] = Add(nSmallYSize,
                                     nSmallXSize,
                                     ppnRi[0]+nChunkOffset+nMaxRIOpSize,
                                     pnOverflowDigits+nOverflowSize,
                                     ppnRi[0]+nChunkOffset+nMaxRIOpSize);
            }
        }
        else
        {
            pnRiOpSizes[0] = nPieceSize;
            pnRiOpSizes[1] = nPieceSize;
        }
        for(i=1;i<2*nNumPieces-3;i++) // loop over the rest of the r(i)
        {
            nCoefSize = pSystemToUse->m_ppnSizesRi[i][nNumPieces-2];
#if _CollectDetailedTimingData
            MultUBackend(nCoefSize,
                         nPieceSize,
                         pSystemToUse->m_pppCoefficientsRi[i][nNumPieces-2],
                         pnX+nChunkOffset,
                         ppnRi[i]+nChunkOffset,
                         pnWorkspace,
                         dwTimestamp);
            MultUBackend(nCoefSize,
                         nPieceSize,
                         pSystemToUse->m_pppCoefficientsRi[i][nNumPieces-2],
                         pnY+nChunkOffset,
                         ppnRi[i]+nChunkOffset+nMaxRIOpSize,
                         pnWorkspace,
                         dwTimestamp);
#else
            MultUBackend(nCoefSize,
                         nPieceSize,
                         pSystemToUse->m_pppCoefficientsRi[i][nNumPieces-2],
                         pnX+nChunkOffset,
                         ppnRi[i]+nChunkOffset,
                         pnWorkspace);
            MultUBackend(nCoefSize,
                         nPieceSize,
                         pSystemToUse->m_pppCoefficientsRi[i][nNumPieces-2],
                         pnY+nChunkOffset,
                         ppnRi[i]+nChunkOffset+nMaxRIOpSize,
                         pnWorkspace);
#endif
            nMultSize = nCoefSize+nPieceSize;
            // zero out overflow region
            ppnRi[i][nChunkOffset+nMultSize]                = 0;
            ppnRi[i][nChunkOffset+nMultSize+1]              = 0;
            ppnRi[i][nChunkOffset+nMaxRIOpSize+nMultSize]   = 0;
            ppnRi[i][nChunkOffset+nMaxRIOpSize+nMultSize+1] = 0;
            if(0<nChunkOffset)
            {
                // might have carry-out from previous iteration
                // AddU wants smaller operand second
                if(nMultSize>=nOverflowSize)
                {
                    pnRiOpSizes[i<<1] = Add(nMultSize,
                                            nOverflowSize,
                                            ppnRi[i]+nChunkOffset,
                                            pnOverflowDigits+2*i*nOverflowSize,
                                            ppnRi[i]+nChunkOffset);
                }
                else
                {
                    pnRiOpSizes[i<<1] = Add(nOverflowSize,
                                            nMultSize,
                                            pnOverflowDigits+2*i*nOverflowSize,
                                            ppnRi[i]+nChunkOffset,
                                            ppnRi[i]+nChunkOffset);
                }
                // AddU wants smaller operand second
                if(nMultSize>nOverflowSize)
                {
                    pnRiOpSizes[1+(i<<1)] = Add(nMultSize,
                                                nOverflowSize,
                                                ppnRi[i]+nChunkOffset+nMaxRIOpSize,
                                                pnOverflowDigits+(2*i+1)*nOverflowSize,
                                                ppnRi[i]+nChunkOffset+nMaxRIOpSize);
                }
                else
                {
                    pnRiOpSizes[1+(i<<1)] = Add(nOverflowSize,
                                                nMultSize,
                                                pnOverflowDigits+(2*i+1)*nOverflowSize,
                                                ppnRi[i]+nChunkOffset+nMaxRIOpSize,
                                                ppnRi[i]+nChunkOffset+nMaxRIOpSize);
                }
            }
            else // nChunkOffset==0
            {
                if(0==ppnRi[i][nMultSize-1])
                {
                    pnRiOpSizes[i<<1] = nMultSize-1;
                }
                else
                {
                    pnRiOpSizes[i<<1] = nMultSize;
                }
                if(0==ppnRi[i][nMaxRIOpSize+nMultSize-1])
                {
                    pnRiOpSizes[1+(i<<1)] = nMultSize-1;
                }
                else
                {
                    pnRiOpSizes[1+(i<<1)] = nMultSize;
                }
            }
        }
        for(j=nNumPieces-2;j>0;j--) // loop over rest of the pieces
        {
            // r(0): just x(0)*y(0)
            // r(2n-2): just x(nNumPieces-1)*y(nNumPieces-1)
            // r(1): all coefs are 1
            // Recall: AddU expects smaller operand second
            if(nPieceSize<pnRiOpSizes[0])
            {
                pnRiOpSizes[0] = Add(pnRiOpSizes[0],
                                     nPieceSize,
                                     ppnRi[0]+nChunkOffset,
                                     pnX+nChunkOffset+nOffset,
                                     ppnRi[0]+nChunkOffset);
            }
            else
            {
                pnRiOpSizes[0] = Add(nPieceSize,
                                     pnRiOpSizes[0],
                                     pnX+nChunkOffset+nOffset,
                                     ppnRi[0]+nChunkOffset,
                                     ppnRi[0]+nChunkOffset);
            }
            if(nPieceSize<pnRiOpSizes[1])
            {
                pnRiOpSizes[1] = Add(pnRiOpSizes[1],
                                     nPieceSize,
                                     ppnRi[0]+nChunkOffset+nMaxRIOpSize,
                                     pnY+nChunkOffset+nOffset,
                                     ppnRi[0]+nChunkOffset+nMaxRIOpSize);
            }
            else
            {
                pnRiOpSizes[1] = Add(nPieceSize,
                                     pnRiOpSizes[1],
                                     pnY+nChunkOffset+nOffset,
                                     ppnRi[0]+nChunkOffset+nMaxRIOpSize,
                                     ppnRi[0]+nChunkOffset+nMaxRIOpSize);
            }
            for(i=1;i<2*nNumPieces-3;i++) // loop over the rest of the r(i)
            {
                nCoefSize = pSystemToUse->m_ppnSizesRi[i][j-1];
                MultAddUBackend(nCoefSize,
                                nPieceSize,
                                pnRiOpSizes[i<<1],
                                pSystemToUse->m_pppCoefficientsRi[i][j-1],
                                pnX+nChunkOffset+nOffset,
                                ppnRi[i]+nChunkOffset,
#if(_CollectDetailedTimingData)
                                dwTimestamp,
#endif
                                pnWorkspace);
                MultAddUBackend(nCoefSize,
                                nPieceSize,
                                pnRiOpSizes[1+(i<<1)],
                                pSystemToUse->m_pppCoefficientsRi[i][j-1],
                                pnY+nChunkOffset+nOffset,
                                ppnRi[i]+nChunkOffset+nMaxRIOpSize,
#if(_CollectDetailedTimingData)
                                dwTimestamp,
#endif
                                pnWorkspace);
            }
            nOffset += nSubproblemSize;
        }
        // add in the last piece: coef == 1 all for all RIs
        for(i=0;i<2*nNumPieces-3;i++)
        {
            // note that this last piece -- that of x/y -- is guaranteed to be nonzero:
            // it is the most significant chunk
            // AddU expects smaller operand second!
            // Note that by construction nXSize-nOffset, nYSize-nOffset <= nSubproblemSize
            // and nSubproblemSize <= pnRiOpSizes[(i<<1)], pnRiOpSizes[1+(i<<1)]
            // so we don't need to check for order here
            nMultSize = nChunkOffset+nOffset;
            if(nMultSize<nXSize)
            {
                nSmallXSize = nPieceSize;
                if(nMultSize+nPieceSize>nXSize)
                {
                    nSmallXSize = nXSize-nMultSize;
                }
                pnRiOpSizes[i<<1] = Add(pnRiOpSizes[i<<1],
                                        nSmallXSize,
                                        ppnRi[i]+nChunkOffset,
                                        pnX+nChunkOffset+nOffset,
                                        ppnRi[i]+nChunkOffset);
            }
            if(nMultSize<nYSize)
            {
                nSmallYSize = nPieceSize;
                if(nMultSize+nPieceSize>nYSize)
                {
                    nSmallYSize = nYSize-nMultSize;
                }
                pnRiOpSizes[1+(i<<1)] = Add(pnRiOpSizes[1+(i<<1)],
                                            nSmallYSize,
                                            ppnRi[i]+nChunkOffset+nMaxRIOpSize,
                                            pnY+nChunkOffset+nOffset,
                                            ppnRi[i]+nChunkOffset+nMaxRIOpSize);
            }
            if(nChunkOffset+c_nBuildBlockSizePre<nSubproblemSize)
            {
                for(nMultSize=0;nMultSize<pnRiOpSizes[i<<1]-nPieceSize;nMultSize++)
                {
                    pnOverflowDigits[(i<<1)*nOverflowSize+nMultSize] = ppnRi[i][nChunkOffset+nPieceSize+nMultSize];
                }
                for(;nMultSize<nOverflowSize;nMultSize++)
                {
                    pnOverflowDigits[(i<<1)*nOverflowSize+nMultSize] = 0;
                }
                for(nMultSize=0;nMultSize<pnRiOpSizes[1+(i<<1)]-nPieceSize;nMultSize++)
                {
                    pnOverflowDigits[((i<<1)+1)*nOverflowSize+nMultSize] = ppnRi[i][nMaxRIOpSize+nChunkOffset+nPieceSize+nMultSize];
                }
                for(;nMultSize<nOverflowSize;nMultSize++)
                {
                    pnOverflowDigits[((i<<1)+1)*nOverflowSize+nMultSize] = 0;
                }
            }
            else
            {
                // figure the final ppnRi operator sizes
                pnRiOpSizes[i<<1]     += nChunkOffset;
                pnRiOpSizes[1+(i<<1)] += nChunkOffset;
            }
        }
    }
}

// Construct the operands for the r(i)s.
// Store that for r(i) in r(i-1).
// (recall r(1) = (1*x(1) + 1*x(2) + ... + 1*x(n))*(y(1)+...+y(n)),
// r(2) = (1*x(1)+2*x(2)+4*x(3) + ... + (2^(n-1))*x(n))*(y), etc.
// Except for the leading 1 for each, these coefs are stored in
// the CoefficientRi portion of the system data.)
void CUnsignedArithmeticHelper::ConstructArgumentsFor2NByNSubproblems(size_t             nSubproblemSize,
                                                                      size_t             nNumPieces,
                                                                      size_t             nXSize,
                                                                      size_t             nMaxRIOpSize,
                                                                      DIGIT              **ppnRi,
                                                                      size_t             *pnRiOpSizes,
                                                                      const DIGIT        *pnX,
                                                                      SSystemData        *pSystemToUse,
#if(_CollectDetailedTimingData)
                                                                      DWORD64            &dwTimestamp, // on entry, time called.  On exit, time completed
#endif
                                                                      DIGIT              *pnWorkspace)
{
    int nOffset;
    // first, initial piece: coef of last chunk*coef (except for r(1) -- for that, just add last TWO chunks to initialize)
    for(int i=1; i<2*nNumPieces-3; i++)
    {
        nOffset = pSystemToUse->m_ppnSizesRi[i][nNumPieces - 2] + nSubproblemSize;
        MultUBackend(pSystemToUse->m_ppnSizesRi[i][nNumPieces-2],
                     nSubproblemSize,
                     pSystemToUse->m_pppCoefficientsRi[i][nNumPieces-2],
                     pnX,
                     ppnRi[i],
                     pnWorkspace,
#if(_CollectDetailedTimingData)
                     dwTimestamp,
                     pnRiOpSizes + i);
#else
            pnRiOpSizes + i);
#endif
        memset(ppnRi[i] + nOffset, 0, (nMaxRIOpSize-nOffset)*sizeof(DIGIT));
    }
    pnRiOpSizes[0] = Add(nSubproblemSize, nSubproblemSize, pnX, pnX + nSubproblemSize, ppnRi[0]);
    memset(ppnRi[0] + nOffset, 0, (nMaxRIOpSize-(nSubproblemSize + 1))*sizeof(DIGIT));
    // add in the rest of the pieces -- except the short high-order piece
    pnX += nSubproblemSize;
    for (int nPiece = nNumPieces - 2; 1 <= nPiece; nPiece--)
    {
        for(int i=1; i<2*nNumPieces-3; i++)
        {
            MultAddUBackend(pSystemToUse->m_ppnSizesRi[i][nPiece - 1],
                            nSubproblemSize,
                            pnRiOpSizes[i],
                            pSystemToUse->m_pppCoefficientsRi[i][nPiece - 1],
                            pnX,
                            ppnRi[i],
#if(_CollectDetailedTimingData)
                            dwTimestamp,
                            pnWorkspace);
#else
                            pnWorkspace);
#endif
        }
        if(nPiece != nNumPieces - 2)
        {
            pnRiOpSizes[0] = Add(pnRiOpSizes[0],
                                 nSubproblemSize,
                                 ppnRi[0],
                                 pnX,
                                 ppnRi[0]);
        }
        pnX += nSubproblemSize;
    }
    // add in the final (short) piece -- coef == 1 for all r(i)
    int nFinalPieceSize = nXSize - (nNumPieces - 1)*nSubproblemSize;
    for(int i=0; i<2*nNumPieces-3; i++)
    {
        pnRiOpSizes[i] = Add(pnRiOpSizes[i],
                             nFinalPieceSize,
                             ppnRi[i],
                             pnX,
                             ppnRi[i]);
    }
}

/*
To compute the final product, we need to compute several linear combinations of the RIs, and divide each by
its divisor.  (These are the PIs.)  The coefficients and the divisors are very small relative to the size of the RIs
(assuming we are using a reasonable number of pieces!), so there is scope for ordering computations for better use of
cache.
Basic idea 1:
Note that (a+b)/c = a/c + (a%c+b)/c -- you do this all the time with long division, if you think of "a" as the hundreds digit
and "b" as the tens digit, for instance.
Thus, we can construct the PIs in chunks, starting from the high-order bits and working our way back, and thus need read
through the RIs only once, keeping the chunk of the RI we need in cache.
Basic idea 2:
We don't actually need the PIs once they have been added into the final product; if we add them in place as we go, we
only need to keep around the chunks of the PIs we are currently working on, thus saving a bit of memory.  But we need
to be careful here, naturally.  Recalling P0 is the most-significant of the PIs, each PI starts <subproblem size> digits
further back in the final product; there is overlap.  Now, we KNOW that the total sum cannot extend past <xsize+ysize>.
But an individual PI could in theory be as long as (<subproblem size>+<max RI coef size>+<max PI coef size>)*2+2 (assuming
we have a reasonable number of pieces, and all the summations do not cause more than 1 DIGIT of carry).  Except for the
first and last PI, the PIs *could* be negative, though the total sum is positive.  In particular, therefore, P1 and P2
could extend past <xsize>+<ysize> -- P1 by <subproblem size>+2*<max RI coef size>+2*<max PI coef size> (lose +2: P0
is at least 2 DIGITs long), P2 by 2*<max RI coef size>+2*<max PI coef size>.  HOWEVER if P1 extends further
than P2 does, it cannot be canceled out by P2, and we know that any DIGITs past <xsize>+<ysize> MUST be canceled
out.  But we cannot rule out that P0 might extend past the end of P0 (and thus the final product) by
2*<max RI coef size>+2*<max PI coef size> DIGITs; this extension could have either sign.  So we need to make
a little extra space available for this temporary overflow.
*/

// UNfortunately, there is a bug somewhere in the code -- constructing the pieces in chunks isn't working.
// BUT: perf testing indicates the block size should be set larger than the basic multiply size that would
// use this algorithm in the first place -- multiplis of such a size that chunking helps are better done
// with the FFT multiply.  So: skip chunking; do directly
void CUnsignedArithmeticHelper::ComputeProductFrom2NByNSubproblemResults(size_t              nNumPieces,
                                                                         size_t              nMaxRISize,
                                                                         size_t              nSubproblemSize,
                                                                         size_t              nXSize,
                                                                         size_t              nYSize,
                                                                         size_t              *pnRiSizes,
                                                                         DIGIT               **ppnRi,
                                                                         DIGIT               *pnZValue,
                                                                         SSystemData         *pSystemToUse,
#if(_CollectDetailedTimingData)
                                                                         DWORD64             &dwTimestamp, // on entry, time called.  On exit, time completed
#endif
                                                                         DIGIT               *pnWorkspace)
{
    size_t      nOffset, nCoefSize, nRISize, i, j, k;
    DOUBLEDIGIT nSum, nCarry;
#if _CollectDetailedTimingData
    DWORD64     dwProcess = dwTimestamp;
#endif
    // Using the r(i)s and the quasi-inverse matrix, construct the p(i)s
    // Recall p(i) = <quasi-inverse matrix>*r(i)/Diag(i)
    // Set aside space for remainders from division
    pSystemToUse->m_nMaxSizeRI;
    size_t nMaxDivisorSize = pSystemToUse->m_nMaxDivisorSize;
    size_t nMaxCoefSize    = pSystemToUse->m_nMaxSizePI;  // max coef. size for the second part
    size_t nMaxPIsize      = ((pSystemToUse->m_nMaxSizeRI+nSubproblemSize)<<1) + nMaxCoefSize + 2; // really, +1.  +2 so we don't have to
                                                                                                   // worry about an "overflow" (guaranteed 0)
                                                                                                   // being carried out
    // Note that pi(2*nNumPieces-2) == ppnRi(2*nNumPieces-2) done in place
    nOffset                       = (2*nNumPieces - 2)*nSubproblemSize;
    // initialize Z between p(0) and p(2n-2) to 0.  (Note: p(2n-2) done in place)
    memset(pnZValue + nSubproblemSize + nSubproblemSize, 0, sizeof(DIGIT)*(nOffset - (nSubproblemSize<<1)));
    // copy pi(0) == ppnRi(0) into place.
    memcpy(pnZValue + nOffset, ppnRi[0], pnRiSizes[0]*sizeof(DIGIT));
    // zero out above pi(0) -- can be empty for internal multiplication, where leading 0s are possible (and high-order DIGIT can always be 0)
    for(i=nOffset+pnRiSizes[0]; i<nXSize+nYSize; i++) pnZValue[i] = 0;
    DIGIT *pDiv = NULL;
    DIGIT *pOp1 = pnWorkspace;
    DIGIT *pOp2 = pOp1 + nMaxPIsize;
    pnWorkspace = pOp2 + nMaxPIsize;
    // Compute the rest of the Pi's in chunks, and add those chunks into
    // place as we go.
    nOffset = (2*nNumPieces - 3)*nSubproblemSize;
    for (i=0; i<2*nNumPieces - 3; i++)
    {
        size_t nPiComponentSize = 0;
        bool   bSign            = false;
        bool   bHasComponent    = false;
        for (j=0; j<2*nNumPieces - 1; j++)  // loop over the r(j)s
        {
            nCoefSize = pSystemToUse->m_ppnSizesPi[i][j];
            nRISize   = pnRiSizes[j];
            while (0<nRISize && 0==ppnRi[j][nRISize - 1]) nRISize--; // internal piece might have leading 0s
            if (nRISize)
            {
                if (!bHasComponent)
                {
                    // first component
                    MultUBackend(nCoefSize,
                                 nRISize,
                                 pSystemToUse->m_pppCoefficientsPi[i][j],
                                 ppnRi[j],
                                 pOp1,
#if(_CollectDetailedTimingData)
                                 pnWorkspace,
                                 dwTimestamp);
#else
                                 pnWorkspace);
#endif
                    nPiComponentSize       = nCoefSize + nRISize;
                    pOp1[nPiComponentSize] = 0; // guard against overflow
                    bHasComponent          = true;
                    bSign                  = pSystemToUse->m_ppbSigns[i][j];
                    if (0 == pOp1[nPiComponentSize - 1]) nPiComponentSize--;
                }
                else
                {
                    // second or succeeding component
                    MultUBackend(nCoefSize,
                                 nRISize,
                                 pSystemToUse->m_pppCoefficientsPi[i][j],
                                 ppnRi[j],
                                 pOp2,
#if(_CollectDetailedTimingData)
                                 pnWorkspace,
                                 dwTimestamp);
#else
                                 pnWorkspace);
#endif
                    size_t nIntermediateSize = nCoefSize + nRISize;
                    pOp2[nIntermediateSize] = 0; // guard against overflow
                    if (0 == pOp2[nIntermediateSize - 1]) nIntermediateSize--;
                    AddSigned(nPiComponentSize, nIntermediateSize, nPiComponentSize, pOp1, pOp2, pOp1, bSign, pSystemToUse->m_ppbSigns[i][j], bSign);
                }
            }
        }
        if (0<nPiComponentSize)
        {
            // do division
            size_t nRemainderSize; // always 0: dummy variable here
            DivideBackend(nPiComponentSize,
                          pSystemToUse->m_ppnSizesPi[i][j],
                          nPiComponentSize,
                          nRemainderSize,
                          pOp1,
                          pSystemToUse->m_pppCoefficientsPi[i][j],
                          pOp2,
#if(_CollectDetailedTimingData)
                          dwTimestamp,
#endif
                          pnWorkspace);
            // add (or subtract) P(i) into place
            DIGIT *pDest = pnZValue + nOffset;
            nCarry = 0;
            // note that P(i) is the sum of the ith column of "digit" products -- it is guaranteed to be non-negative
            // add
            for (k=0; k<nPiComponentSize; k++)
            {
                nSum     = (pOp2[k] + nCarry) + pDest[k];
                nCarry   = nSum>>_DIGIT_SIZE_IN_BITS;
                pDest[k] = (DIGIT) nSum;
            }
            while (nCarry && k < nXSize + nYSize - nOffset)
            {
                nCarry = ((DIGIT)-1 == pDest[k++]++);
            }
        }
        nOffset -= nSubproblemSize;
    }
}

void CUnsignedArithmeticHelper::MultU2NByN(size_t             nXSize,
                                           size_t             nYSize,
                                           const DIGIT        *pXValue,
                                           const DIGIT        *pYValue,
                                           DIGIT              *pZValue,
                                           SSystemData        *pSystemToUse,
#if(_CollectDetailedTimingData)
                                           DIGIT              *pWorkspace,
                                           DWORD64            &dwTimestamp)
#else
                                           DIGIT              *pWorkspace)
#endif
{
    DIGIT        **pRi, *pnOverflowDigits;
    size_t       nSubproblemSize, nMaxRIOpSize, nMaxCoefSize, i,
                 *pnRiSizes, *pnRiOpSizes, nSmallXSize, nSmallYSize, n,
                 nMaxRISize = 0, nOverflowSize, nMaxRiSize;
#if(_CollectDetailedTimingData)
    DWORD64      dwBuildTime = dwTimestamp;
    DWORD64      dwProcessTime;
#endif
    n               = pSystemToUse->m_nSystemSize;
    nSubproblemSize = (nYSize+(n-1))/n;
    if(nXSize <= pSystemToUse->m_nMaxSizePI + 2 + (n - 1)*nSubproblemSize)
    {
        // size discrepency too great to use the 2n-by-n algorithm on the full problem; break it down
        // need the first chunk/piece to be large enough that the next piece doesn't fully overlap with it
        // if the size of the numbers is x, and there are n pieces, the smallest r(i) will be a product of two numbers of size
        // x - ((x+n-1)/n)n
        // to avoid dangerous overlap in computation, this must be at least 2 + <max coef for computing the p(i)s>
        // which boils down to the size must be greater than (<max coef> + nPieces)*nPieces + 1
        if(nXSize == nYSize)
        {
            // can't use this algorithm at all
#if(32<=_DIGIT_SIZE_IN_BITS)
#if(_CollectDetailedTimingData)
            MultU9by5(nXSize, nYSize, pXValue, pYValue, pZValue, pWorkspace, dwTimestamp);
#else
            MultU9by5(nXSize, nYSize, pXValue, pYValue, pZValue, pWorkspace);
#endif
#else
#if(_CollectDetailedTimingData)
            MultU7by4(nXSize, nYSize, pXValue, pYValue, pZValue, pWorkspace, dwTimestamp);
#else
            MultU7by4(nXSize, nYSize, pXValue, pYValue, pZValue, pWorkspace);
#endif
#endif
        }
        else
        {
            // try with equal sizes
            size_t nProdSize;
#if _CollectDetailedTimingData
            MultU2NByN(nXSize, nXSize, pXValue, pYValue + nYSize - nXSize, pZValue + nYSize - nXSize, pSystemToUse, pWorkspace, dwTimestamp);
            FinishUnbalancedMult(nXSize, nYSize, pXValue, pYValue, pZValue, dwTimestamp, pWorkspace, &nProdSize);
#else
            MultU2NByN(nXSize, nXSize, pXValue, pYValue + nYSize - nXSize, pZValue + nYSize - nXSize, pSystemToUse, pWorkspace);
            FinishUnbalancedMult(nXSize, nYSize, pXValue, pYValue, pZValue, pWorkspace, &nProdSize);
#endif
        }
        return;
    }
    // Align pWorkspace with size_t boundaries, so efficient
    // for holding pointers; set up the various pointers used in construction
    size_t nOffset =  ((size_t) pWorkspace)%(sizeof(size_t)/sizeof(DIGIT));
    pWorkspace       += nOffset;
    // should actually be able to store this in Z, too, for real problem
    // sizes TODO
    pnOverflowDigits =  pWorkspace;
    nMaxCoefSize     =  pSystemToUse->m_nMaxSizeRI;
    nOverflowSize    =  nMaxCoefSize + 2; // just for convenience
    pWorkspace       += 2*(2*n-2)*nOverflowSize;
    // The vectors holding the various r(i) and p(i) values
    pRi              =  (DIGIT **) pWorkspace;
    // the sizes of the Ris, once computed
    pnRiSizes        =  (size_t *) (pRi + (2*n-1));
    pWorkspace       =  (DIGIT *)  (pnRiSizes + 2*n-1);
    // Use pZValue to hold the sizes for the operands for computing the pRi's: by the time we're
    // ready to write into Z, won't need these.  Just make sure to make them properly aligned
    // for the size!
    nOffset          = sizeof(size_t)/sizeof(DIGIT) - ((size_t) pZValue)%(sizeof(size_t)/sizeof(DIGIT));
    pnRiOpSizes      = (size_t *) (pZValue + nOffset);
    // Generate the r(i)s
    // r(0): most significant
    // Determine how much space the largest of the rest of the r(i)s will
    // need, and block off that much space for each of the rest.  Note:
    // this assumes a limit on the number of pieces, as noted above!
    nMaxCoefSize =  pSystemToUse->m_nMaxSizeRI;
    nMaxRIOpSize =  (nSubproblemSize + nMaxCoefSize + 2); // a little extra space for carry, so needn't check
                                                          // carry-out for overflow when we know the "overflow"
                                                          // (if any) will be 0
    nMaxRiSize   =  nMaxRIOpSize<<1;
    for(i=0;i<2*n-2;i++)
    {
        // this gives more space than is needed to hold r(0) and r(2n-2) --
        // but extra space is needed in the r(i)s, since these are also used
        // to hold the arguments in computing the next up: r(0) is used as space
        // for the args for r(1), r(1) for r(2), etc.
        pRi[i]     =  pWorkspace;
        pWorkspace += nMaxRiSize;
    }
    pRi[i] = pZValue;  // last piece done in place
    // Construct the operands for the r(i)s.
    // Store that for r(i) in r(i-1).
    // (recall r(1) = (1*x(1) + 1*x(2) + ... + 1*x(n))*(y(1)+...+y(n)),
    // r(2) = (1*x(1)+2*x(2)+4*x(3) + ... + (2^(n-1))*x(n))*(y), etc.
    // Except for the leading 1 for each, these coefs are stored in
    // the CoefficientRi portion of the system data.)
    ConstructArgumentsFor2NByNSubproblems(nSubproblemSize,
                                          n,
                                          nXSize,
                                          nYSize,
                                          nMaxRIOpSize,
                                          nOverflowSize,
                                          pRi,
                                          pnRiOpSizes,
                                          pXValue,
                                          pYValue,
                                          pnOverflowDigits,
                                          pSystemToUse,
#if(_CollectDetailedTimingData)
                                          dwTimestamp,
#endif
                                          pWorkspace);
    // The operands for the r(i)s have now been computed
    // Perform the (primary) multiplications, generating the r(i)s
#if(_CollectDetailedTimingData)
    dwTimestamp           =  s_Timer.GetMicroseconds();
    g_nBuildTimes[e2NByN] += dwTimestamp-dwBuildTime;
#endif
    for(i=2*n-3;i>=1;i--)
    {
#if(_CollectDetailedTimingData)
        MultUBackend(pnRiOpSizes[(i-1)<<1],pnRiOpSizes[1+((i-1)<<1)],pRi[i-1],pRi[i-1]+nMaxRIOpSize,pRi[i],pWorkspace,dwTimestamp,pnRiSizes+i);
#else
        MultUBackend(pnRiOpSizes[(i-1)<<1],pnRiOpSizes[1+((i-1)<<1)],pRi[i-1],pRi[i-1]+nMaxRIOpSize,pRi[i],pWorkspace,pnRiSizes+i);
#endif
        if(nMaxRISize<pnRiSizes[i])
        {
            nMaxRISize = pnRiSizes[i];
        }
    }
    i = 2*n-2;
#if(_CollectDetailedTimingData)
    MultUBackend(nSubproblemSize,nSubproblemSize,pXValue,pYValue,pRi[i],pWorkspace,dwTimestamp,pnRiSizes+i);
#else
    MultUBackend(nSubproblemSize,nSubproblemSize,pXValue,pYValue,pRi[i],pWorkspace,pnRiSizes+i);
#endif
    if(nMaxRISize<pnRiSizes[i])
    {
        nMaxRISize = pnRiSizes[i];
    }
    nSmallXSize = nXSize-(n-1)*nSubproblemSize;
    nSmallYSize = nYSize-(n-1)*nSubproblemSize;
#if _CollectDetailedTimingData
    MultUBackend(nSmallXSize,
                 nSmallYSize,
                 pXValue+(n-1)*nSubproblemSize,
                 pYValue+(n-1)*nSubproblemSize,
                 pRi[0],
                 pWorkspace,
                 dwTimestamp,
                 pnRiSizes);
    dwProcessTime = dwTimestamp;
#else
    MultUBackend(nSmallXSize,
                 nSmallYSize,
                 pXValue+(n-1)*nSubproblemSize,
                 pYValue+(n-1)*nSubproblemSize,
                 pRi[0],
                 pWorkspace,
                 pnRiSizes);
#endif
    if(nMaxRISize<pnRiSizes[0])
    {
        nMaxRISize = pnRiSizes[0];
    }
    if(0==nMaxRISize)
    {
        // product is 0.  Unlikely to happen, but ComputeProductFrom2NByNSubproblemResults gets stuck in an endless
        // loop if it does.  So pull it out as a special case
        for(int i=0; i<nXSize+nYSize; i++)
        {
            pZValue[i] = 0;
        }
    }
    else
    {
        ComputeProductFrom2NByNSubproblemResults(n,
                                                 nMaxRISize,
                                                 nSubproblemSize,
                                                 nXSize,
                                                 nYSize,
                                                 pnRiSizes,
                                                 pRi,
                                                 pZValue,
                                                 pSystemToUse,
#if(_CollectDetailedTimingData)
                                                 dwTimestamp,
#endif
                                                 pWorkspace);
    }
#if(_CollectDetailedTimingData)
    dwTimestamp             =  s_Timer.GetMicroseconds();
    g_nProcessTimes[e2NByN] += (dwTimestamp-dwProcessTime);
    g_nMultiplyCalls[e2NByN]++;
#endif
}

void CUnsignedArithmeticHelper::SquareU2NByN(size_t             nXSize,
                                             const DIGIT        *pXValue,
                                             DIGIT              *pZValue,
                                             SSystemData        *pSystemToUse,
#if(_CollectDetailedTimingData)
                                             DWORD64            &dwTimestamp,
#endif
                                             DIGIT              *pWorkspace)
{
    DIGIT        **pRi;
    size_t       nSubproblemSize, nMaxRIOpSize, nMaxCoefSize, i,
                 *pnRiSizes, *pnRiOpSizes, nSmallXSize, nSmallYSize, n,
                 nMaxRiSize;
#if(_CollectDetailedTimingData)
    DWORD64      dwBuildTime = dwTimestamp;
    DWORD64      dwProcessTime;
#endif
    n               = pSystemToUse->m_nSystemSize;
    nSubproblemSize = (nXSize+(n-1))/n;
    // might not need this size check?  TODO
    if(nXSize <= pSystemToUse->m_nMaxSizePI + 2 + (n - 1)*nSubproblemSize)
    {
        // size discrepency too great to use the 2n-by-n algorithm on the full problem; break it down
        // need the first chunk/piece to be large enough that the next piece doesn't fully overlap with it
        // if the size of the numbers is x, and there are n pieces, the smallest r(i) will be a product of two numbers of size
        // x - ((x+n-1)/n)n
        // to avoid dangerous overlap in computation, this must be at least 2 + <max coef for computing the p(i)s>
        // which boils down to the size must be greater than (<max coef> + nPieces)*nPieces + 1
#if(32<=_DIGIT_SIZE_IN_BITS)
#if(_CollectDetailedTimingData)
        SquareU9by5(nXSize, pXValue, pZValue, dwTimestamp, pWorkspace);
#else
        SquareU9by5(nXSize, pXValue, pZValue, pWorkspace);
#endif
#else
#if(_CollectDetailedTimingData)
        SquareU7by4(nXSize, pXValue, pZValue, dwTimestamp, pWorkspace);
#else
        SquareU7by4(nXSize, pXValue, pZValue, pWorkspace);
#endif
#endif
        return;
    }
    // Align pWorkspace with size_t boundaries, so efficient
    // for holding pointers; set up the various pointers used in construction
    size_t nOffset =  ((size_t) pWorkspace)%(sizeof(size_t)/sizeof(DIGIT));
    pWorkspace       += nOffset;
    // should actually be able to store this in Z, too, for real problem
    // sizes TODO
   // pnOverflowDigits =  pWorkspace;
    nMaxCoefSize     =  pSystemToUse->m_nMaxSizeRI;
    // The vectors holding the various r(i) and p(i) values
    pRi              =  (DIGIT **) pWorkspace;
    // the sizes of the Ris, once computed
    pnRiSizes        =  (size_t *) (pRi + (2*n-1));
    pWorkspace       =  (DIGIT *)  (pnRiSizes + 2*n-1);
    // Use pZValue to hold the sizes for the operands for computing the pRi's: by the time we're
    // ready to write into Z, won't need these.  Just make sure to make them properly aligned
    // for the size!
    nOffset          = sizeof(size_t)/sizeof(DIGIT) - ((size_t) pZValue)%(sizeof(size_t)/sizeof(DIGIT));
    pnRiOpSizes      = (size_t *) (pZValue + nOffset);
    // Generate the r(i)s
    // r(0): most significant
    // Determine how much space the largest of the rest of the r(i)s will
    // need, and block off that much space for each of the rest.  Note:
    // this assumes a limit on the number of pieces, as noted above!
    nMaxCoefSize =  pSystemToUse->m_nMaxSizeRI;
    nMaxRIOpSize =  (nSubproblemSize + nMaxCoefSize + 2); // a little extra space for carry, so needn't check
                                                          // carry-out for overflow when we know the "overflow"
                                                          // (if any) will be 0
    nMaxRiSize   =  nMaxRIOpSize<<1;
    for(i=0;i<2*n-2;i++)
    {
        // this gives more space than is needed to hold r(0) and r(2n-2) --
        // but extra space is needed in the r(i)s, since these are also used
        // to hold the arguments in computing the next up: r(0) is used as space
        // for the args for r(1), r(1) for r(2), etc.
        pRi[i]     =  pWorkspace;
        pWorkspace += nMaxRiSize;
    }
    pRi[i] = pZValue;  // last piece done in place
    // Construct the operands for the r(i)s.
    // Store that for r(i) in r(i-1).
    // (recall r(1) = (1*x(1) + 1*x(2) + ... + 1*x(n))*(y(1)+...+y(n)),
    // r(2) = (1*x(1)+2*x(2)+4*x(3) + ... + (2^(n-1))*x(n))*(y), etc.
    // Except for the leading 1 for each, these coefs are stored in
    // the CoefficientRi portion of the system data.)
    ConstructArgumentsFor2NByNSubproblems(nSubproblemSize,
                                          n,
                                          nXSize,
                                          nMaxRIOpSize,
                                          pRi,
                                          pnRiOpSizes,
                                          pXValue,
                                          pSystemToUse,
#if(_CollectDetailedTimingData)
                                          dwTimestamp,
#endif
                                          pWorkspace);
#if(_CollectDetailedTimingData)
    dwTimestamp           =  s_Timer.GetMicroseconds();
    g_nBuildTimes[e2NByN] += dwTimestamp-dwBuildTime;
#endif
    // The operands for the r(i)s have now been computed
    // Perform the (primary) multiplications, generating the r(i)s
    nMaxRiSize = 0;
    for(i=2*n-3;i>=1;i--)
    {
#if(_CollectDetailedTimingData)
        SquareUBackend(pnRiOpSizes[i-1],pRi[i-1],pRi[i],pWorkspace,dwTimestamp,pnRiSizes+i);
#else
        SquareUBackend(pnRiOpSizes[i-1],pRi[i-1],pRi[i],pWorkspace,pnRiSizes+i);
#endif
        if(nMaxRiSize<pnRiSizes[i])
        {
            nMaxRiSize = pnRiSizes[i];
        }
    }
    i = 2*n-2;
#if(_CollectDetailedTimingData)
    SquareUBackend(nSubproblemSize,pXValue,pRi[i],pWorkspace,dwTimestamp,pnRiSizes+i);
#else
    SquareUBackend(nSubproblemSize,pXValue,pRi[i],pWorkspace,pnRiSizes+i);
#endif
    if(nMaxRiSize<pnRiSizes[i])
    {
        nMaxRiSize = pnRiSizes[i];
    }
    nSmallXSize = nXSize-(n-1)*nSubproblemSize;
#if(_CollectDetailedTimingData)
    SquareUBackend(nSmallXSize, pXValue+(n-1)*nSubproblemSize, pRi[0], pWorkspace, dwTimestamp, pnRiSizes);
    dwProcessTime = dwTimestamp;
#else
    SquareUBackend(nSmallXSize, pXValue + (n - 1) * nSubproblemSize, pRi[0], pWorkspace, pnRiSizes);
#endif
    if(nMaxRiSize<pnRiSizes[0])
    {
        nMaxRiSize = pnRiSizes[0];
    }
    if(0==nMaxRiSize)
    {
        // product is 0.  Unlikely to happen, but ComputeProductFrom2NByNSubproblemResults gets stuck in an endless
        // loop if it does.  So pull it out as a special case
        for(int i=0; i<nXSize+nXSize; i++)
        {
            pZValue[i] = 0;
        }
    }
    else
    {
        ComputeProductFrom2NByNSubproblemResults(n,
                                                 nMaxRiSize,
                                                 nSubproblemSize,
                                                 nXSize,
                                                 nXSize,
                                                 pnRiSizes,
                                                 pRi,
                                                 pZValue,
                                                 pSystemToUse,
#if(_CollectDetailedTimingData)
                                                 dwTimestamp,
#endif
                                                 pWorkspace);
    }
#if(_CollectDetailedTimingData)
    dwTimestamp             =  s_Timer.GetMicroseconds();
    g_nProcessTimes[e2NByN] += (dwTimestamp-dwProcessTime);
    g_nMultiplyCalls[e2NByN]++;
#endif
}

// Adds two signed values.  The buffers are assumed to be accurate.
// Sets z to the sum of x and y, with sign
void CUnsignedArithmeticHelper::AddSigned(size_t       nXSize,
                                          size_t       nYSize,
                                          size_t       &nZSize,
                                          const DIGIT  *pXValue,
                                          const DIGIT  *pYValue,
                                          DIGIT        *pZValue,
                                          bool         bXNegative,
                                          bool         bYNegative,
                                          bool         &bZNegative)
{
    if(bXNegative==bYNegative)
    {
        // really is addition
        bZNegative = bYNegative;
        // AddU expects smaller operand second!
        if(nXSize>nYSize)
        {
            nZSize = Add(nXSize,nYSize,pXValue,pYValue,pZValue);
        }
        else
        {
            nZSize = Add(nYSize,nXSize,pYValue,pXValue,pZValue);
        }
    }
    else
    {
        // subtraction
        if(nXSize>nYSize)
        {
            bZNegative = bXNegative;
            nZSize     = Subtract(nXSize,nYSize,pXValue,pYValue,pZValue);
        }
        else if(nYSize>nXSize)
        {
            bZNegative = bYNegative;
            nZSize     = Subtract(nYSize,nXSize,pYValue,pXValue,pZValue);
        }
        else
        {
            // x and y have the same number of digits
            nZSize = nXSize-1;
            if(pXValue[nZSize]==pYValue[nZSize] && 0!=nZSize)
            {
                do
                {
                    nZSize--;
                }
                while(pXValue[nZSize]==pYValue[nZSize] && 0 != nZSize);
            }
            if(pXValue[nZSize]>pYValue[nZSize])
            {
                bZNegative = bXNegative;
                nZSize     = Subtract(nZSize+1,nZSize+1,pXValue,pYValue,pZValue);
            }
            else if(pXValue[nZSize]<pYValue[nZSize])
            {
                bZNegative = bYNegative;
                nZSize     = Subtract(nZSize+1,nZSize+1,pYValue,pXValue,pZValue);
            }
            else
            {
                // x and y are equal.  The sign of 0 is by convention positive
                bZNegative = false;
            }
        }
    }
}

// Mod x by 1+2^n.  Assumes x is at most 2^(2n), and has
// exactly 2n+1 digits (with leading 0s, if need be).  Yup;
// specialized function.
// Note that x mod (1+2^n) for x a number of m bits the result is
// (least significant n bits) - (next least significant n bits) + (next least
// sigificant n bits) - ... + (most significant m mod n) bits, + (1+2^n) if the
// final result is negative.
// We have a version of this of known (short) size.
// It is safe for pDestination to be X.
void CUnsignedArithmeticHelper::ModBy2nPlus1(const DIGIT *pXData,
                                             DIGIT       *pDestination,
                                             size_t      n)
{
    DOUBLEDIGIT nAdd,nSub;
    size_t      i;
    const DIGIT *pHigh  = pXData + n;
    DOUBLEDIGIT nBorrow = 0;

    nAdd            = ((DOUBLEDIGIT) pXData[0])+pHigh[n];
    nSub            = pHigh[0];
    nBorrow         = (nAdd<nSub) ? 1 : 0;
    pDestination[0] = (DIGIT) (nAdd-nSub); //((nBorrow<<_DIGIT_SIZE_IN_BITS) + nAdd - nSub);
    // Note that while it might LOOK like we might have a carry -- the sum of two digits, minus
    // a third digit, could overflow in general -- we can't in this case due to the range
    // assumption: the only number in the range with non-zero most-significant digit is 2^(2n);
    // the rest of its digits are 0 -- and hence, no overflow.
    for(i=1;i<n;i++)
    {
        nAdd            = pXData[i];
        nSub            = pHigh[i]+nBorrow;
        nBorrow         = (nAdd<nSub) ? 1 : 0;
        pDestination[i] = (DIGIT) (nAdd-nSub); //((nBorrow<<DigitSize) + nAdd - nSub);
    }
    pDestination[i] = 0;
    // add back 1+2^n if necessary
    if(0<nBorrow)
    {
        // need to add 1+2^n.  Note that the add of 2^n was implicitly
        // done by allowing the "borrow" from nowhere
        nAdd            =  ((DOUBLEDIGIT) 1)+pDestination[0];
        pDestination[0] =  (DIGIT) nAdd;
        nBorrow         =  (nAdd>>_DIGIT_SIZE_IN_BITS);
        if(0<nBorrow)
        {
            i = 1;
            do
            {
                nAdd              = ((DOUBLEDIGIT) pDestination[i])+nBorrow;
                pDestination[i++] = (DIGIT) nAdd;
                nBorrow           = (nAdd>>_DIGIT_SIZE_IN_BITS);
            }
            while(0<nBorrow);
        }
    }
}

// specialized!  X is assumed to be an n+1 digit number at most 2^n
void CUnsignedArithmeticHelper::Mult2toMmodOnePlus2toN(const DIGIT *pXData,
                                                       size_t      n,
                                                       SBitShift   &nShift,
                                                       DIGIT       *pDestination)
{
    size_t       i;
    DOUBLEDIGIT  nAdd, nSub, nBorrow, nHold;
    DIGIT        nShiftAdd, nShiftSub;
    const DIGIT  *pHigh;
    size_t       nShiftDigits = nShift.m_nDigitShift;
    DIGIT        nShiftBits   = nShift.m_nBitShift;
    if((nShiftDigits/n)&1)
    {
        // subtract least-significant digits; add most-significant
        nShiftDigits =  nShiftDigits%n;
        pXData       -= nShiftDigits; // for easier addressing
        pHigh        =  pXData+n;
        if(0==nShiftBits)
        {
            for(i=0;i<nShiftDigits;i++)
            {
                pDestination[i] = pHigh[i];
            }
            nAdd              = pHigh[i];
            nSub              = pXData[i];
            nBorrow           = (nAdd<nSub) ? 1 : 0;
            pDestination[i++] = (DIGIT) (nAdd-nSub);
            for(;i<n;i++)
            {
                nSub            = nBorrow + pXData[i];
                nBorrow         = (0<nSub) ? 1 : 0;
                pDestination[i] = (DIGIT) -nSub;
            }
            pDestination[i] = 0;
        }
        else
        {
            int nRightBitShift = _DIGIT_SIZE_IN_BITS - nShiftBits;
            // a bit more complicated -- have a bit-shift as well as a digit-shift to
            // deal with
            // need to deal with bit shift as well as digit shift
            nShiftAdd = pHigh[-1]>>nRightBitShift;
            for(i=0;i<nShiftDigits;i++)
            {
                nHold           = pHigh[i];
                nAdd            = (nHold<<nShiftBits) | nShiftAdd;
                nShiftAdd       = (DIGIT) (nHold>>nRightBitShift);
                pDestination[i] = (DIGIT) nAdd;
            }
            nHold             =  pHigh[i];
            nAdd              =  (nHold<<nShiftBits) | nShiftAdd;
            nShiftAdd         =  (DIGIT) (nHold>>nRightBitShift);
            nAdd              &= c_nClearHigh;
            nHold             =  pXData[i];
            nSub              =  nHold<<nShiftBits;
            nShiftSub         =  (DIGIT) (nHold>>nRightBitShift);
            nSub              &= c_nClearHigh;
            nBorrow           =  (nAdd<nSub) ? 1 : 0;
            pDestination[i++] =  (DIGIT) (nAdd-nSub);
            for(;i<n;i++)
            {
                nHold           =  pXData[i];
                nSub            =  ((nHold<<nShiftBits) | nShiftSub);
                nShiftSub       =  (DIGIT) (nHold>>nRightBitShift);
                nSub            &= c_nClearHigh;
                nSub            += nBorrow;
                nBorrow         =  (0<nSub) ? 1 : 0;
                pDestination[i] =  (DIGIT) -nSub;
            }
            pDestination[i] = 0;
        }
    }
    else
    {
        // subtract most-significant digits; add least-significant
        nShiftDigits =  nShiftDigits%n;
        pHigh        =  pXData+n-nShiftDigits;
        pXData       -= nShiftDigits; // for easier addressing
        if(0==nShiftBits)
        {
            nBorrow = 0;
            for(i=0;i<nShiftDigits;i++)
            {
                nSub            = pHigh[i]+nBorrow;
                nBorrow         = (0<nSub);
                pDestination[i] = (DIGIT) -nSub;
            }
            nSub              = pHigh[i]+nBorrow;
            nAdd              = pXData[i];
            nBorrow           = (nAdd<nSub) ? 1 : 0;
            pDestination[i++] = (DIGIT) (nAdd-nSub);
            for(;i<n;i++)
            {
                nSub            = nBorrow;
                nAdd            = pXData[i];
                nBorrow         = (nAdd<nSub) ? 1 : 0;
                pDestination[i] = (DIGIT) (nAdd-nSub);
            }
            pDestination[i] = 0;
        }
        else
        {
            // need to deal with bit shift as well as digit shift
            int nRightBitShift = _DIGIT_SIZE_IN_BITS - nShiftBits;
            nBorrow   = 0;
            nShiftSub = pHigh[-1]>>nRightBitShift;
            for(i=0;i<nShiftDigits;i++)
            {
                nHold           =  pHigh[i];
                nSub            =  ((nHold<<nShiftBits) | nShiftSub);
                nShiftSub       =  (DIGIT) (nHold>>nRightBitShift);
                nSub            &= c_nClearHigh;
                nSub            += nBorrow;
                nBorrow         =  (0<nSub) ? 1 : 0;
                pDestination[i] =  (DIGIT) -nSub;
            }
            nHold             =  pHigh[i]; // shift out of last "low" digit
            nSub              =  ((nHold<<nShiftBits) | nShiftSub);
            nShiftSub         =  (DIGIT) (nHold>>nRightBitShift);
            nSub              &= c_nClearHigh;
            nSub              += nBorrow;
            nHold             =  pXData[i];
            nAdd              =  (nHold<<nShiftBits);
            nShiftAdd         =  (DIGIT) (nHold>>nRightBitShift);
            nAdd              &= c_nClearHigh;
            nBorrow           =  (nAdd<nSub) ? 1 : 0;
            pDestination[i++] =  (DIGIT) (nAdd-nSub);
            for(;i<n;i++)
            {
                nSub            =  nBorrow;
                nHold           =  pXData[i];
                nAdd            =  (nHold<<nShiftBits) | nShiftAdd;
                nShiftAdd       =  (DIGIT) (nHold>>nRightBitShift);
                nAdd            &= c_nClearHigh;
                nBorrow         =  (nAdd<nSub) ? 1 : 0;
                pDestination[i] =  (DIGIT) (nAdd-nSub);
            }
            pDestination[i] = 0;
        }
    }
    // add back 1+2^n if necessary
    if(0<nBorrow)
    {
        // need to add 1+2^n.  Note that the add of 2^n was implicitly
        // done by allowing the "borrow" from nowhere
        nAdd            =  ((DOUBLEDIGIT) 1)+pDestination[0];
        pDestination[0] =  (DIGIT) nAdd;
        nBorrow         =  (nAdd>>_DIGIT_SIZE_IN_BITS);
        if(0<nBorrow)
        {
            i = 1;
            do
            {
                nAdd              = pDestination[i]+nBorrow;
                pDestination[i++] = (DIGIT) nAdd;
                nBorrow           = (nAdd>>_DIGIT_SIZE_IN_BITS);
            }
            while(0<nBorrow);
        }
    }
}

CUnsignedArithmeticHelper::SBitShift::SBitShift()
{
    m_nBitShift   = 0;
    m_nDigitShift = 0;
}

bool CUnsignedArithmeticHelper::SBitShift::Halve()
{
    if(0!=(m_nBitShift&1))
    {
        return false;
    }
    if(0!=(m_nDigitShift&1))
    {
        m_nBitShift += _DIGIT_SIZE_IN_BITS;
    }
    m_nBitShift   = m_nBitShift>>1;
    m_nDigitShift = m_nDigitShift>>1;
    return true;
}

void CUnsignedArithmeticHelper::SBitShift::Double()
{
    m_nBitShift   = m_nBitShift<<1;
    m_nDigitShift = m_nDigitShift<<1;
    if(_DIGIT_SIZE_IN_BITS<=m_nBitShift)
    {
        m_nBitShift -= _DIGIT_SIZE_IN_BITS;
        m_nDigitShift++;
    }
}

void CUnsignedArithmeticHelper::SBitShift::Add(SBitShift &nAddend)
{
    m_nBitShift   += nAddend.m_nBitShift;
    m_nDigitShift += nAddend.m_nDigitShift;
    if(_DIGIT_SIZE_IN_BITS<=m_nBitShift)
    {
        m_nBitShift -= _DIGIT_SIZE_IN_BITS;
        m_nDigitShift++;
    }
}

bool CUnsignedArithmeticHelper::SBitShift::Sub(SBitShift &nSub)
{
    if((m_nDigitShift<nSub.m_nDigitShift)                                     ||
       (m_nDigitShift==nSub.m_nDigitShift && m_nBitShift<nSub.m_nBitShift))
    {
        return false;
    }
    m_nDigitShift -= nSub.m_nDigitShift;
    if(m_nBitShift<nSub.m_nBitShift)
    {
        m_nBitShift += _DIGIT_SIZE_IN_BITS;
        m_nDigitShift--;
    }
    m_nBitShift -= nSub.m_nBitShift;
    return true;
}

void CUnsignedArithmeticHelper::ExpandBaseNumberForFFT(const DIGIT *pnToExpand,
                                                       size_t      nToExpandLength,
                                                       size_t      nChunkSize,
                                                       size_t      nFieldSize,
                                                       size_t      nFFTLength,
                                                       DIGIT       *pnExpanded)
{
    size_t i,j,k;
    // martial the data for the FFT
    // Note that this is specialized for FFT multiply -- at most half the slots in the FFT should be
    // used, and less than half the size of each slot, so the product is unique mod the field size
    // ALSO: this can be done more efficiently!  First pass.
    k = 0;
    for(i=0;i<nToExpandLength/nChunkSize;i++)
    {
        for(j=i*nChunkSize;j<i*nChunkSize+(nFieldSize>>1)-1;j++)
        {
            pnExpanded[k++] = pnToExpand[j];
        }
        for(;j<i*((nFieldSize>>1)-1)+nFieldSize+1;j++)
        {
            pnExpanded[k++] = 0;
        }
    }
    for(j=i*nChunkSize;j<nToExpandLength;j++)
    {
        pnExpanded[k++] = pnToExpand[j];
    }
    if(k<(nFieldSize+1)*nFFTLength)
    {
        do
        {
            pnExpanded[k++] = 0;
        }
        while(k<(nFieldSize+1)*nFFTLength);
    }
}

// THE FFT ALGORITHM
// =================
// Here is the general algorithm in pseudo-C:

// Let A be array of length m, w be primitive mth root of unity.
// Goal: produce DFT F(A): evaluation of A at 1, w, w^2,...,w^{m-1}.
// FFT(A, m, w)
// {
//   if (m==1)
//   {
//     return vector (a_0)
//   }
//   else
//   {
//     A_even = (a_0, a_2, ..., a_{m-2})
//     A_odd  = (a_1, a_3, ..., a_{m-1})
//     V_even = FFT(A_even, m/2, w^2)    //w^2 is a primitive m/2-th root of unity
//     V_odd  = FFT(A_odd, m/2, w^2)
//     V      = new vector of length m
//     for (j=0; j < m/2; ++j)
//     {
//       V[j]     = V_even[j] + w^j*V_odd[j]
//       V[j+m/2] = V_even[j] - w^j*V_odd[j]
//     }
//   }
//   return V
// }
void CUnsignedArithmeticHelper::FFT_basic(const DIGIT *pBase,
                                          DIGIT       *pFFT,
                                          size_t      nLength,
                                          size_t      nFieldSize,
                                          SBitShift   nRoot,
                                          size_t      nStep, // base skip size in the FFT.  Should start at nFieldSize+1
                                          DIGIT       *pnWorkspace)
{
    DOUBLEDIGIT nSum, nDifference, nCarry, nBorrow, nEven, nOdd;
    bool        bOpEndedOutsideField;
    size_t      i, j;
    if(1==nLength)
    {
        // base case
        memcpy(pFFT,pBase,sizeof(DIGIT)*(nFieldSize+1));
    }
    else
    {
        SBitShift nRootIterator;
        SBitShift nRootSquared;
        size_t    nSubFFTSize;
        DIGIT     *pFFT_Even, *pFFT_Odd;
        nLength                    = nLength>>1;
        nSubFFTSize                = nLength*(nFieldSize+1); // used repeatedly
        pFFT_Even                  = pnWorkspace;
        pFFT_Odd                   = pnWorkspace + nSubFFTSize;
        pnWorkspace                = pFFT_Odd    + nSubFFTSize;
        nRootSquared.m_nBitShift   = nRoot.m_nBitShift;
        nRootSquared.m_nDigitShift = nRoot.m_nDigitShift;
        nRootSquared.Double();
        FFT_basic(pBase,pFFT_Even,nLength,nFieldSize,nRootSquared,nStep<<1,pnWorkspace);
        FFT_basic(pBase+nStep,pFFT_Odd,nLength,nFieldSize,nRootSquared,nStep<<1,pnWorkspace);
        for(j=0;j<nSubFFTSize;j+=(nFieldSize+1))
        {
            // mult each odd element by w^j
            Mult2toMmodOnePlus2toN(pFFT_Odd+j,nFieldSize,nRootIterator,pnWorkspace);
            nRootIterator.Add(nRoot); // move iterator to the next power of the root of unity
            nCarry  = 0;
            nBorrow = 0;
            // V[j]     = V_even[j] + w^j*V_odd[j] and
            // V[j+m/2] = V_even[j] - w^j*V_odd[j]
            for(i=0;i<nFieldSize+1;i++)
            {
                nEven                 = pFFT_Even[j+i];
                nOdd                  = pnWorkspace[i];
                nSum                  = nCarry+nEven+nOdd;
                pFFT[j+i]             = (DIGIT) nSum;
                nDifference           = nOdd+nBorrow;
                pFFT[nSubFFTSize+j+i] = (DIGIT) (nEven-nDifference);
                nCarry                = nSum>>_DIGIT_SIZE_IN_BITS;
                nBorrow               = (nEven<nDifference) ? 1 : 0;
            }
            // check for overflow on the add
            if(0<pFFT[j+nFieldSize])
            {
                bOpEndedOutsideField = false;
                if(1<pFFT[j+nFieldSize])
                {
                    bOpEndedOutsideField = true;
                }
                else
                {
                    for(i=0;i<nFieldSize;i++)
                    {
                        if(0<pFFT[j+i])
                        {
                            bOpEndedOutsideField = true;
                            break;
                        }
                    }
                }
                if(bOpEndedOutsideField)
                {
                    // need to subtract off (1+2^nFieldSize)
                    pFFT[j+nFieldSize]--;
                    i = 0;
                    do
                    {
                        ;
                    }
                    while(0==pFFT[j+i++]--);
                }
            }
            // check for overflow on the subtract
            if(0<nBorrow)
            {
                // need to add in (1+2^nFieldSize)
                pFFT[nSubFFTSize+j+nFieldSize] = 0; // note that if we had borrow out, the value for the first digit MUST be -1 -- the largest
                                                    // value we can subtract is 10000...  from 0.  (If the first digit started as 1, it was the
                                                    // largest possible number in the field -> no borrowing necessary!)
                i                              = 0;
                do
                {
                    ;
                }
                while(0==++pFFT[nSubFFTSize+j+i++]);
            }
        }
    }
}

void CUnsignedArithmeticHelper::FFT(const DIGIT *pBase,    // the number whose FFT is to be computed
                                    DIGIT       *pFFT,
                                    size_t      nBaseSize, // the size of the number whose FFT is to be computed
                                    size_t      nChunkSize,
                                    size_t      nBaseStep, // should start at nChunkSize+1
                                    size_t      nLength,
                                    size_t      nFieldSize,
                                    SBitShift   nRootUnity,
                                    DIGIT       *pnWorkspace)
{
    DOUBLEDIGIT nSum, nDifference, nCarry, nBorrow, nEven, nOdd;
    bool        bOpEndedOutsideField;
    DIGIT       *pFFT_Even, *pFFT_Odd;
    size_t      i, j;
    nLength = nLength>>1; // length of subproblems for this stage
    size_t nSubFFTSize = nLength*(nFieldSize+1); // used repeatedly
    if(1==nLength)
    {
        size_t nOddSize,nEvenSize;
        if(nBaseStep<nBaseSize)
        {
            if(nBaseStep+nChunkSize<=nBaseSize)
            {
                nOddSize = nChunkSize;
            }
            else
            {
                nOddSize = nBaseSize-nBaseStep;
            }
            nEvenSize = nChunkSize;
        }
        else
        {
            nOddSize  = 0;
            nEvenSize = (nBaseSize<nChunkSize) ? nBaseSize : nChunkSize;
        }
        // note that nOddSize <= nEvenSize in all cases
        nCarry  = 0;
        nBorrow = 0;
        // V[0]   = V_even[0] + V_odd[0] and
        // V[m/2] = V_even[0] - V_odd[0]
        pFFT_Even = (DIGIT *) pBase;
        pFFT_Odd  = (DIGIT *) (pBase+nBaseStep);
        for(i=0;i<nOddSize;i++)
        {
            nEven               = pFFT_Even[i];
            nOdd                = pFFT_Odd[i];
            nSum                = nCarry+nEven+nOdd;
            pFFT[i]             = (DIGIT) nSum;
            nDifference         = nOdd+nBorrow;
            pFFT[nSubFFTSize+i] = (DIGIT) (nEven-nDifference);
            nCarry              = nSum>>_DIGIT_SIZE_IN_BITS;
            nBorrow             = (nEven<nDifference) ? 1 : 0;
        }
        for(;i<nEvenSize;i++)
        {
            nEven               = pFFT_Even[i];
            nSum                = nCarry+nEven;
            pFFT[i]             = (DIGIT) nSum;
            nDifference         = nBorrow;
            pFFT[nSubFFTSize+i] = (DIGIT) (nEven-nDifference);
            nCarry              = nSum>>_DIGIT_SIZE_IN_BITS;
            nBorrow             = (nEven<nDifference) ? 1 : 0;
        }
        // check for overflow on the subtract
        if(0<nBorrow)
        {
            memset(pFFT+nSubFFTSize+i,-1,(nFieldSize+1-i)*sizeof(DIGIT));
            // need to add in (1+2^nFieldSize)
            pFFT[nSubFFTSize+nFieldSize] = 0; // note that if we had borrow out, the value for the first digit MUST be -1 -- the largest
                                              // value we can subtract is 10000...  from 0.  (If the first digit started as 1, it was the
                                              // largest possible number in the field -> no borrowing necessary!)
            j                            = 0;
            do
            {
                ;
            }
            while(0==++pFFT[nSubFFTSize+j++]);
        }
        else
        {
            memset(pFFT+nSubFFTSize+i,0,(nFieldSize+1-i)*sizeof(DIGIT));
        }
        // note that we CANNOT have overflow on the add -- nOddSize<=nEvenSize<=nChunkSize<nFieldSize
        pFFT[i++] = (DIGIT) nCarry;
        if(i<nFieldSize + 1) memset(pFFT+i,0,(nFieldSize+1-i)*sizeof(DIGIT));
    }
    else
    {
        SBitShift nRootIterator;
        SBitShift nRootSquared;
        pFFT_Even                  = pFFT;
        pFFT_Odd                   = pFFT_Even + nSubFFTSize;
        nRootSquared.m_nBitShift   = nRootUnity.m_nBitShift;
        nRootSquared.m_nDigitShift = nRootUnity.m_nDigitShift;
        nRootSquared.Double();
        FFT(pBase,pFFT_Even,nBaseSize,nChunkSize,nBaseStep<<1,nLength,nFieldSize,nRootSquared,pnWorkspace);
        if(nBaseStep<nBaseSize)
        {
            FFT(pBase+nBaseStep,pFFT_Odd,nBaseSize-nBaseStep,nChunkSize,nBaseStep<<1,nLength,nFieldSize,nRootSquared,pnWorkspace);
        }
        else
        {
            memset(pFFT_Odd,0,nSubFFTSize*sizeof(DIGIT));
        }
        for(j=0;j<nSubFFTSize;j+=(nFieldSize+1))
        {
            // mult each odd element by w^j
            Mult2toMmodOnePlus2toN(pFFT_Odd+j,nFieldSize,nRootIterator,pnWorkspace);
            nRootIterator.Add(nRootUnity); // move iterator to the next power of the root of unity
            nCarry  = 0;
            nBorrow = 0;
            // V[j]     = V_even[j] + w^j*V_odd[j] and
            // V[j+m/2] = V_even[j] - w^j*V_odd[j]
            for(i=0;i<nFieldSize+1;i++)
            {
                nEven                 = pFFT_Even[j+i];
                nOdd                  = pnWorkspace[i];
                nSum                  = nCarry+nEven+nOdd;
                pFFT[j+i]             = (DIGIT) nSum;
                nDifference           = nOdd+nBorrow;
                pFFT[nSubFFTSize+j+i] = (DIGIT) (nEven-nDifference);
                nCarry                = nSum>>_DIGIT_SIZE_IN_BITS;
                nBorrow               = (nEven<nDifference) ? 1 : 0;
            }
            // check for overflow on the add
            if(0<pFFT[j+nFieldSize])
            {
                bOpEndedOutsideField = false;
                if(1<pFFT[j+nFieldSize])
                {
                    bOpEndedOutsideField = true;
                }
                else
                {
                    for(i=0;i<nFieldSize;i++)
                    {
                        if(0<pFFT[j+i])
                        {
                            bOpEndedOutsideField = true;
                            break;
                        }
                    }
                }
                if(bOpEndedOutsideField)
                {
                    // need to subtract off (1+2^nFieldSize)
                    pFFT[j+nFieldSize]--;
                    i = 0;
                    do
                    {
                        ;
                    }
                    while(0==pFFT[j+i++]--);
                }
            }
            // check for overflow on the subtract
            if(0<nBorrow)
            {
                // need to add in (1+2^nFieldSize)
                pFFT[nSubFFTSize+j+nFieldSize] = 0; // note that if we had borrow out, the value for the first digit MUST be -1 -- the largest
                                                    // value we can subtract is 10000...  from 0.  (If the first digit started as 1, it was the
                                                    // largest possible number in the field -> no borrowing necessary!)
                i                              = 0;
                do
                {
                    ;
                }
                while(0==++pFFT[nSubFFTSize+j+i++]);
            }
        }
    }
}

void CUnsignedArithmeticHelper::FFTInverse(const DIGIT *pFFT,
                                           DIGIT       *pFFTInverse,
                                           size_t      nBaseStep, // should start at nFieldSize+1
                                           size_t      nLength,
                                           size_t      nFieldSize,
                                           SBitShift   nRootUnity,
                                           DIGIT       *pnWorkspace)
{
    DOUBLEDIGIT nSum, nDifference, nCarry, nBorrow, nEven, nOdd;
    bool        bOpEndedOutsideField;
    DIGIT       *pFFT_Even, *pFFT_Odd;
    SBitShift   nRootIterator;
    size_t      i, j, nSubFFTSize;
    nLength     = nLength>>1; // length of subproblems for this stage
    nSubFFTSize = nLength*(nFieldSize+1); // used repeatedly
    if(1 != nLength)
    {
        SBitShift nRootSquared;
        pFFT_Even                  = pFFTInverse;
        pFFT_Odd                   = pFFT_Even + nSubFFTSize;
        nRootSquared.m_nBitShift   = nRootUnity.m_nBitShift;
        nRootSquared.m_nDigitShift = nRootUnity.m_nDigitShift;
        nRootSquared.Double();
        FFTInverse(pFFT,pFFT_Even,nBaseStep<<1,nLength,nFieldSize,nRootSquared,pnWorkspace);
        FFTInverse(pFFT+nBaseStep,pFFT_Odd,nBaseStep<<1,nLength,nFieldSize,nRootSquared,pnWorkspace);
    }
    else
    {
        pFFT_Even = (DIGIT *) pFFT;
        pFFT_Odd  = pFFT_Even + nBaseStep;
    }
    for(j=0;j<nSubFFTSize;j+=(nFieldSize+1))
    {
        // mult each odd element by w^j
        Mult2toMmodOnePlus2toN(pFFT_Odd+j,nFieldSize,nRootIterator,pnWorkspace);
        nRootIterator.Add(nRootUnity); // move iterator to the next power of the root of unity
        nCarry  = 0;
        nBorrow = 0;
        // V[j]     = V_even[j] + w^j*V_odd[j] and
        // V[j+m/2] = V_even[j] - w^j*V_odd[j]
        for(i=0;i<nFieldSize+1;i++)
        {
            nEven                        = pFFT_Even[j+i];
            nOdd                         = pnWorkspace[i];
            nSum                         = nCarry+nEven+nOdd;
            pFFTInverse[j+i]             = (DIGIT) nSum;
            nDifference                  = nOdd+nBorrow;
            pFFTInverse[nSubFFTSize+j+i] = (DIGIT) (nEven-nDifference);
            nCarry                       = nSum>>_DIGIT_SIZE_IN_BITS;
            nBorrow                      = (nEven<nDifference) ? 1 : 0;
        }
        // check for overflow on the add
        if(0<pFFTInverse[j+nFieldSize])
        {
            bOpEndedOutsideField = false;
            if(1<pFFTInverse[j+nFieldSize])
            {
                bOpEndedOutsideField = true;
            }
            else
            {
                for(i=0;i<nFieldSize;i++)
                {
                    if(0<pFFTInverse[j+i])
                    {
                        bOpEndedOutsideField = true;
                        break;
                    }
                }
            }
            if(bOpEndedOutsideField)
            {
                // need to subtract off (1+2^nFieldSize)
                pFFTInverse[j+nFieldSize]--;
                i = 0;
                do
                {
                    ;
                }
                while(0==pFFTInverse[j+i++]--);
            }
        }
        // check for overflow on the subtract
        if(0<nBorrow)
        {
            // need to add in (1+2^nFieldSize)
            pFFTInverse[nSubFFTSize+j+nFieldSize] = 0; // note that if we had borrow out, the value for the first digit MUST be -1 -- the largest
                                                       // value we can subtract is 10000...  from 0.  (If the first digit started as 1, it was the
                                                       // largest possible number in the field -> no borrowing necessary!)
            i                                     = 0;
            do
            {
                ;
            }
            while(0==++pFFTInverse[nSubFFTSize+j+i++]);
        }
    }
}

void CUnsignedArithmeticHelper::FFT_Inverse_basic(const DIGIT *pToCompute,
                                                  size_t      nLength,
                                                  SBitShift   nRootUnity,
                                                  size_t      nFieldSize,
                                                  DIGIT       *pFFTInverse,
                                                  DIGIT       *pnWorkspace)
{
    SBitShift nTwoNMinusM,nRootUnityForInverse;
    nRootUnityForInverse.m_nBitShift   = 0;
    nRootUnityForInverse.m_nDigitShift = 2*nFieldSize;
    nRootUnityForInverse.Sub(nRootUnity);
    FFT_basic(pToCompute,pFFTInverse,nLength,nFieldSize,nRootUnityForInverse,nFieldSize+1,pnWorkspace);
    // divide each element by nLength.  Note that we assume nLength is a power of 2 and at least 2!
    size_t m=1;
    if(2 != nLength)
    {
        do
        {
            m++;
        }
        while(1 != (nLength>>m));
    }
    nTwoNMinusM.m_nBitShift   = m%_DIGIT_SIZE_IN_BITS;
    nTwoNMinusM.m_nDigitShift = m/_DIGIT_SIZE_IN_BITS;
    nTwoNMinusM.m_nDigitShift = (nFieldSize-nTwoNMinusM.m_nDigitShift)+nFieldSize;
    if(0 != nTwoNMinusM.m_nBitShift)
    {
        nTwoNMinusM.m_nBitShift = _DIGIT_SIZE_IN_BITS-nTwoNMinusM.m_nBitShift;
        nTwoNMinusM.m_nDigitShift--;
    }
    for(size_t i=0;i<nLength;i++)
    {
        Mult2toMmodOnePlus2toN(pFFTInverse,nFieldSize,nTwoNMinusM,pnWorkspace);
        memcpy(pFFTInverse,pnWorkspace,(nFieldSize+1)*sizeof(DIGIT));
        pFFTInverse += (nFieldSize+1);
    }
}

void CUnsignedArithmeticHelper::FFT_Inverse(const DIGIT *pFFT,
                                            DIGIT       *pFFT_FFTInverse,
                                            size_t      nLength,
                                            SBitShift   nRootUnity,
                                            size_t      nFieldSize,
                                            DIGIT       *pnWorkspace)
{
    SBitShift nTwoNMinusM,nRootUnityForInverse;
    nRootUnityForInverse.m_nBitShift   = 0;
    nRootUnityForInverse.m_nDigitShift = 2*nFieldSize;
    nRootUnityForInverse.Sub(nRootUnity);
    FFTInverse(pFFT,pFFT_FFTInverse,nFieldSize+1,nLength,nFieldSize,nRootUnityForInverse,pnWorkspace);
    // divide each element by nLength.  Note that we assume nLength is a power of 2 and at least 2!
    size_t m=1;
    if(2 != nLength)
    {
        do
        {
            m++;
        }
        while(1 != (nLength>>m));
    }
    nTwoNMinusM.m_nBitShift   = m%_DIGIT_SIZE_IN_BITS;
    nTwoNMinusM.m_nDigitShift = m/_DIGIT_SIZE_IN_BITS;
    nTwoNMinusM.m_nDigitShift = (nFieldSize-nTwoNMinusM.m_nDigitShift)+nFieldSize;
    if(0 != nTwoNMinusM.m_nBitShift)
    {
        nTwoNMinusM.m_nBitShift = _DIGIT_SIZE_IN_BITS-nTwoNMinusM.m_nBitShift;
        nTwoNMinusM.m_nDigitShift--;
    }
    for(size_t i=0;i<nLength;i++)
    {
        Mult2toMmodOnePlus2toN(pFFT_FFTInverse,nFieldSize,nTwoNMinusM,pnWorkspace);
        memcpy(pFFT_FFTInverse,pnWorkspace,(nFieldSize+1)*sizeof(DIGIT));
        pFFT_FFTInverse += (nFieldSize+1);
    }
}

// FFT, FFT inverse compute the values at the lowest (length 0) level in a "strange" order, giving poor performance.  Instead:
// do the input at the lowest level sequentially, and the OUTPUT in the strange order.  Might be faster (check) -- don't have
// to wait on writes; need to wait on reads
// this function takes as parameters the top bit in the index (e.g. for a length 16 FFT, the top bit is (1<<3) -- 8) and the
// index.  It replaces the index with the next in the sequence.  NOTE: it will reset to 0 if passed the last value in the sequence!
__forceinline void NextInSequence(size_t &nIndex, size_t nTopBit)
{
    while(nIndex&nTopBit)
    {
        nIndex &= ~nTopBit;
        nTopBit = nTopBit>>1;
    }
    nIndex |= nTopBit;
}

void CUnsignedArithmeticHelper::GetFFTSize(size_t nXSize, size_t nYSize, size_t &nFFTLength, size_t &nFieldSize, size_t &nChunkSize, BYTE &byMaxOverflowSize, SBitShift &nRootUnity)
{
    size_t nXPieces, nYPieces, nShift;
    BYTE   byRoundoffSpace   = 1;
    nFieldSize               = 2;
    nFFTLength               = sizeof(DIGIT)<<5; // max length for the field size
    nRootUnity.m_nBitShift   = 1;
    nRootUnity.m_nDigitShift = 0;
    // First pass: get the minimum field size necessary for the multiply.  Note that the field size determines the maximum
    // length of the FFT that can be done!
    do
    {
        nFieldSize = nFieldSize<<1;
        nFFTLength = nFFTLength<<1;
        nChunkSize = (nFieldSize>>1)-byRoundoffSpace;
        nXPieces   = (nXSize+nChunkSize-1)/nChunkSize;
        nYPieces   = (nYSize+nChunkSize-1)/nChunkSize;
        nShift     = sizeof(DOUBLEDIGIT)<<(3*byRoundoffSpace);
        if(nShift               <  (sizeof(size_t)<<3) &&
           ((size_t) 1)<<nShift <= nXSize+nYSize)
        {
            do
            {
                byRoundoffSpace++;
                nChunkSize = (nFieldSize>>1)-byRoundoffSpace;
                nXPieces   = (nXSize+nChunkSize-1)/nChunkSize;
                nYPieces   = (nYSize+nChunkSize-1)/nChunkSize;
                nShift     = sizeof(DOUBLEDIGIT)<<(3*byRoundoffSpace);
            }
            while(nShift               <  (sizeof(size_t)<<3) &&
                  ((size_t) 1)<<nShift <= nXPieces+nYPieces);
        }
    }
    while(nFFTLength<nXPieces+nYPieces);
    // if the FFT is longer than it needs to be, prune it back to the minimum length needed
    while(nXPieces+nYPieces<=(nFFTLength>>1))
    {
        nFFTLength = nFFTLength>>1;
        nRootUnity.Double();
    }
    // the FFT/FFT_inverse involve adding n numbers, where 2^n is the length of the FFT.  The maximum number of DIGITs of the carry-out
    // is (n + <size of a DIGIT in bits> - 1)/<size of DIGIT in bits)
    byMaxOverflowSize = 1;
    while (((size_t) 1)<<(_DIGIT_SIZE_IN_BITS*byMaxOverflowSize) < nFFTLength) byMaxOverflowSize++;
}

void CUnsignedArithmeticHelper::Convolve(DIGIT       *pnFFT_a,
                                         const DIGIT *pnFFT_b,
                                         size_t      nLength,
                                         size_t      nFieldSize,
#if(_CollectDetailedTimingData)
                                         DIGIT       *pnWorkspace,
                                         DWORD64     &dwTimestamp)
#else
                                         DIGIT       *pnWorkspace)
#endif
{
    size_t nASize,nBSize,nProdSize;
    for(size_t i=0;i<nLength;i++)
    {
        // note that it is HIGHLY likely that the most significant digits of pnFFT_a
        // and pnFFT_b are 0 -- else, they are just 2^<size> (-1 in the field).  Profitable to check
        // against this.  TODO: do case of -1 as special case, rather than use normal
        // mult/mod
        if(0==pnFFT_a[nFieldSize])
        {
            nASize                           = nFieldSize;
            pnWorkspace[nASize+nFieldSize+1] = 0;
        }
        else
        {
            nASize = nFieldSize+1;
        }
        if(0==pnFFT_b[nFieldSize])
        {
            nBSize                     = nFieldSize;
            pnWorkspace[nASize+nBSize] = 0;
        }
        else
        {
            nBSize = nFieldSize+1;
        }
#if(_CollectDetailedTimingData)
        MultUBackend(nASize,
                     nBSize,
                     pnFFT_a,
                     pnFFT_b,
                     pnWorkspace,
                     pnWorkspace+((nFieldSize+1)<<1),
                     dwTimestamp,
                     &nProdSize);
#else
        MultUBackend(nASize,
                     nBSize,
                     pnFFT_a,
                     pnFFT_b,
                     pnWorkspace,
                     pnWorkspace+((nFieldSize+1)<<1),
                     &nProdSize);
#endif
        ModBy2nPlus1(pnWorkspace,pnFFT_a,nFieldSize);
        pnFFT_a += nFieldSize+1;
        pnFFT_b += nFieldSize+1;
    }
}

void CUnsignedArithmeticHelper::ConvolveSquare(DIGIT   *pnFFT_a,
                                               size_t  nLength,
                                               size_t  nFieldSize,
#if(_CollectDetailedTimingData)
                                               DWORD64 &dwTimestamp,
#endif
                                               DIGIT   *pnWorkspace)
{
    size_t nASize,nBSize,nProdSize;
    for(size_t i=0;i<nLength;i++)
    {
        // note that it is HIGHLY likely that the most significant digits of pnFFT_a is 0 -- else,
        // it is just 2^<size> (-1 in the field).  Profitable to check against this?  TODO: do case of -1
        // as special case, rather than use normal mult/mod -- since we already test it, might as well do
        // a faster mult
        if(0==pnFFT_a[nFieldSize])
        {
            nASize                               = nFieldSize;
            pnWorkspace[nFieldSize+nFieldSize]   = 0;
            pnWorkspace[nFieldSize+nFieldSize+1] = 0;
        }
        else
        {
            nASize = nFieldSize+1;
        }
        SquareUBackend(nASize,
                       pnFFT_a,
                       pnWorkspace,
                       pnWorkspace+((nFieldSize+1)<<1),
#if(_CollectDetailedTimingData)
                       dwTimestamp,
#endif
                       &nProdSize);
        ModBy2nPlus1(pnWorkspace, pnFFT_a, nFieldSize);
        pnFFT_a += nFieldSize + 1;
    }
}

size_t CUnsignedArithmeticHelper::FFTMultiplyMemoryNeeds(size_t nXSize, size_t nYSize, bool bMultAdd)
{
    size_t      nFFTLength,nFieldSize;
    size_t      nChunkSize;
    SBitShift   nRootUnity;
    BYTE        byMaxOverflowSize;
    GetFFTSize(nXSize,nYSize,nFFTLength,nFieldSize,nChunkSize,byMaxOverflowSize,nRootUnity);
    if(bMultAdd)
    {
        return 4*((nFieldSize>>1) + 1)*nFFTLength;
    }
    else
    {
        return 2*(nFieldSize + 1)*nFFTLength;
    }
}

size_t CUnsignedArithmeticHelper::FFTSquareMemoryNeeds(size_t nXSize, bool bMultAdd)
{
    size_t      nFFTLength,nFieldSize;
    size_t      nChunkSize;
    SBitShift   nRootUnity;
    BYTE        byMaxOverflowSize;
    GetFFTSize(nXSize,nXSize,nFFTLength,nFieldSize,nChunkSize,byMaxOverflowSize,nRootUnity);
    if(bMultAdd)
    {
        return 4*((nFieldSize>>1) + 1)*nFFTLength;
    }
    else
    {
        return 2*(nFieldSize + 1)*nFFTLength;
    }
}

void CUnsignedArithmeticHelper::MultFFT(size_t             nXSize,
                                        size_t             nYSize,
                                        const DIGIT        *pnXValue,
                                        const DIGIT        *pnYValue,
                                        DIGIT              *pnZValue,
#if(_CollectDetailedTimingData)
                                        DIGIT              *pnWorkspace,
                                        DWORD64            &dwTimestamp)
#else
                                        DIGIT              *pnWorkspace)
#endif
{
    size_t      nFFTLength,nFieldSize;
    size_t      nChunkSize;
    SBitShift   nRootUnity;
    DIGIT       *pnFFT_x,*pnFFT_y;
    BYTE        byMaxOverflowSize;
#if(_CollectDetailedTimingData)
    DWORD64     dwBuild = dwTimestamp;
    DWORD64     dwRecursiveTime;
    DWORD64     dwProcess;
#endif
    GetFFTSize(nXSize,nYSize,nFFTLength,nFieldSize,nChunkSize,byMaxOverflowSize,nRootUnity);
    pnFFT_x     = pnWorkspace;
    pnFFT_y     = pnWorkspace+(nFieldSize+1)*nFFTLength;
    FFT(pnXValue,pnFFT_x,nXSize,nChunkSize,nChunkSize,nFFTLength,nFieldSize,nRootUnity,pnZValue); // use Z as workspace -- far more space than actually needed
    FFT(pnYValue,pnFFT_y,nYSize,nChunkSize,nChunkSize,nFFTLength,nFieldSize,nRootUnity,pnZValue); // use Z as workspace -- far more space than actually needed
#if(_CollectDetailedTimingData)
    dwRecursiveTime         =  s_Timer.GetMicroseconds();
    dwTimestamp             =  dwRecursiveTime;
    g_nBuildTimes[eFFTMult] += (dwRecursiveTime - dwBuild);
    Convolve(pnFFT_y,pnFFT_x,nFFTLength,nFieldSize,pnZValue,dwTimestamp); // use Z as workspace -- less memory needed
    dwProcess = dwTimestamp;
#else
    // convolve workspace needs is 2*(field size + 1) + multiply needs(field size+1, field size +1) -- which is less than the size of Z.  Use Z as the workspace to save memory
    Convolve(pnFFT_y,pnFFT_x,nFFTLength,nFieldSize,pnZValue);
#endif
    // put the result of the inverse FFT into the FFT_x space, as there is enough room
    FFT_Inverse(pnFFT_y,pnFFT_x,nFFTLength,nRootUnity,nFieldSize,pnZValue); // use Z as workspace -- far more space than actually needed
    // Pull the result out of the inverse FFT vector and massage it into Z.
    // Note that we expect anything beyond nXSize+nYSize in the inverse FFT to be 0 (not checked!)
    // first piece of Z -- no overlap
    GetProductFromInverseFFT(pnFFT_x,pnZValue,nChunkSize,nFieldSize,nXSize+nYSize,byMaxOverflowSize);
#if(_CollectDetailedTimingData)
    dwTimestamp               =  s_Timer.GetMicroseconds();
    g_nProcessTimes[eFFTMult] += dwTimestamp-dwProcess;
    g_nMultiplyCalls[eFFTMult]++;
#endif
}

void CUnsignedArithmeticHelper::GetProductFromInverseFFT(const DIGIT *pnFFT_Inverse,
                                                         DIGIT       *pnZValue,
                                                         size_t      nChunkSize,
                                                         size_t      nFieldSize,
                                                         size_t      nProductSize,
                                                         BYTE        byMaxOverflowSize)
{
    DIGIT       pnOverflowDigits[256]; // VASTLY more space than needed!
    size_t      i,j,nPieces;
    DOUBLEDIGIT nSum,nCarry;
    DIGIT       *pnProductTop = pnZValue+nProductSize;
    // Pull the result out of the inverse FFT vector and massage it into Z.
    // Note that we expect anything beyond nXSize+nYSize in the inverse FFT to be 0 (not checked!)
    // first piece of Z -- no overlap
    memcpy(pnZValue,pnFFT_Inverse,sizeof(DIGIT)*nChunkSize);
    nCarry         =  0;
    nPieces        =  (nProductSize+nChunkSize-1)/nChunkSize;
    pnZValue       += nChunkSize;
    memset(pnOverflowDigits,0,sizeof(DIGIT)*byMaxOverflowSize);
    for(i=1;i<nPieces-2;i++)
    {
        for(j=0;j<byMaxOverflowSize;j++)
        {
            nSum        = ((nCarry+pnFFT_Inverse[nChunkSize+j])+pnFFT_Inverse[nFieldSize+1+j])+pnOverflowDigits[j];
            nCarry      = (nSum>>_DIGIT_SIZE_IN_BITS);
            pnZValue[j] = (DIGIT) nSum;
        }
        for(;j<nChunkSize;j++)
        {
            nSum        = (nCarry+pnFFT_Inverse[nChunkSize+j])+pnFFT_Inverse[nFieldSize+1+j];
            nCarry      = (nSum>>_DIGIT_SIZE_IN_BITS);
            pnZValue[j] = (DIGIT) nSum;
        }
        for(;j<nChunkSize+byMaxOverflowSize;j++)
        {
            pnOverflowDigits[j-nChunkSize] = pnFFT_Inverse[nChunkSize+j];
        }
        pnFFT_Inverse += nFieldSize+1;
        pnZValue      += nChunkSize;
    }
    // last piece or two of Z can be "short", so check for completion
    do
    {
        j = 0;
        do
        {
            nSum          = ((nCarry+pnFFT_Inverse[nChunkSize+j])+pnFFT_Inverse[nFieldSize+1+j])+pnOverflowDigits[j];
            nCarry        = (nSum>>_DIGIT_SIZE_IN_BITS);
            pnZValue[j++] = (DIGIT) nSum;
        }
        while(j<byMaxOverflowSize && pnZValue+j<pnProductTop);
        if(pnZValue+j<pnProductTop)
        {
            if(j<nChunkSize)
            {
                do
                {
                    nSum          = (nCarry+pnFFT_Inverse[nChunkSize+j])+pnFFT_Inverse[nFieldSize+1+j];
                    nCarry        = (nSum>>_DIGIT_SIZE_IN_BITS);
                    pnZValue[j++] = (DIGIT) nSum;
                }
                while(j<nChunkSize && pnZValue+j<pnProductTop);
            }
            if(pnZValue+j<pnProductTop)
            {
                for(i=0;i<byMaxOverflowSize;i++)
                {
                    pnOverflowDigits[i] = pnFFT_Inverse[nChunkSize+j+i];
                }
            }
        }
        pnFFT_Inverse  += nFieldSize+1;
        pnZValue       += nChunkSize;
    }
    while(pnZValue<pnProductTop);
}

void CUnsignedArithmeticHelper::SquareFFT(size_t             nXSize,
                                          const DIGIT        *pnXValue,
                                          DIGIT              *pnZValue,
#if _CollectDetailedTimingData
                                          DIGIT              *pnWorkspace,
                                          DWORD64            &dwTimestamp)
#else
                                          DIGIT              *pnWorkspace)
#endif
{
    size_t      nFFTLength,nFieldSize;
    size_t      nChunkSize;
    SBitShift   nRootUnity;
    DIGIT       *pnFFT, *pnFFT_inv;
    BYTE        byMaxOverflowSize;
#if(_CollectDetailedTimingData)
    DWORD64     dwBuild = dwTimestamp;
    DWORD64     dwRecursiveTime;
    DWORD64     dwProcess;
#endif
    GetFFTSize(nXSize,nXSize,nFFTLength,nFieldSize,nChunkSize,byMaxOverflowSize,nRootUnity);
    pnFFT     = pnWorkspace;
    pnFFT_inv = pnFFT + (nFieldSize+1)*nFFTLength;
    FFT(pnXValue,pnFFT,nXSize,nChunkSize,nChunkSize,nFFTLength,nFieldSize,nRootUnity,pnZValue);
#if(_CollectDetailedTimingData)
    dwRecursiveTime         =  s_Timer.GetMicroseconds();
    dwTimestamp             =  dwRecursiveTime;
    g_nBuildTimes[eFFTMult] += (dwRecursiveTime - dwBuild);
    ConvolveSquare(pnFFT,nFFTLength,nFieldSize,dwTimestamp,pnZValue);
    dwProcess = dwTimestamp;
#else
    ConvolveSquare(pnFFT,nFFTLength,nFieldSize,pnZValue);
#endif
    FFT_Inverse(pnFFT,pnFFT_inv,nFFTLength,nRootUnity,nFieldSize,pnZValue);
    // Pull the result out of the inverse FFT vector and massage it into Z.
    // Note that we expect anything beyond nXSize+nYSize in the inverse FFT to be 0 (not checked!)
    // first piece of Z -- no overlap
    GetProductFromInverseFFT(pnFFT_inv,pnZValue,nChunkSize,nFieldSize,nXSize+nXSize,byMaxOverflowSize);
#if(_CollectDetailedTimingData)
    dwTimestamp               =  s_Timer.GetMicroseconds();
    g_nProcessTimes[eFFTMult] += dwTimestamp-dwProcess;
    g_nMultiplyCalls[eFFTMult]++;
#endif
}

void CUnsignedArithmeticHelper::GetLeadBit(size_t       nValSize,
                                           const DIGIT  *pVal,
                                           size_t       &nLeadDigit,
                                           size_t       &nLeadBit)
{
    nLeadBit   = ((size_t) 1)<<_DIGIT_SIZE_IN_BITS;
    nLeadDigit = nValSize-1;
    // find the most-significant bit of Y
    do
    {
        nLeadBit = nLeadBit >>1;
    }
    while(0==(nLeadBit&(pVal[nLeadDigit])));
}

// Algorithm to compute x^y:
// Initialize the power modulus to 1.
// Start a pointer "above" the most-significant bit of Y.
// Loop:
// While(pointer is not pointing at the least-significant bit of ny)
//   Square the power modulus
//   Move the pointer one to the "right" -- to the next-most-significant bit
//   If the bit pointed to is a 1, multiply the power modulus by X.
// E.g., if Y is 7 (bits: 111), we compute x^4 * x^2 * x == x^7
//       if Y is 5 (bits: 101), we compute x^4 * x       == x^7.
// Now, for X and Y extended-precision integers, this will get to be VERY BIG, VERY FAST.
// So we don't want to compute x^y fully, then mod by z.
// Fortunately, we don't have to: a*b mod c == ((a mod c) * (b mod c)) mod c.
// So the final answer is the same if we wait to take the mod until after computing x^y,
// or if we take the mod after every multiply -- and the latter will keep the sizes
// manageable, and so be MUCH faster (and much more memory-friendly).
void CUnsignedArithmeticHelper::PowerModulus(size_t      nXSize,
                                             size_t      nYSize,
                                             size_t      nZSize,
                                             size_t      &nPowerModulusSize,
                                             const DIGIT *pnXValue,
                                             const DIGIT *pnYValue,
                                             DIGIT       *pnZValue,
                                             DIGIT       *pnPowerModulus,
                                             DIGIT       *pnWorkspace,
                                             bool        bProtectAgainstTimingAttacks)
{
#if(_CollectDetailedTimingData)
    DWORD64     dwTimestamp  = s_Timer.GetMicroseconds();
    DWORD64     dwTimestamp2 = dwTimestamp, dwTimestamp3;
    g_nPowerModulusTime[eTotalPowerModulusCalls]++;
#endif
    size_t      nPowerBit, nPowerDigit;
    const DIGIT *pX;
    GetLeadBit(nYSize, pnYValue, nPowerDigit, nPowerBit);
    if (nXSize > nZSize || (1==nYSize && 1==*pnYValue && -1!=CBigInteger::CompareUnsigned(nXSize,nYSize,pnXValue,pnYValue)))
    {
        // first "multiply" -- just compute X mod Z and copy into place
        pX          =  pnWorkspace;
        memcpy(pnWorkspace, pnXValue, sizeof(DIGIT)*nXSize);
#if(_CollectDetailedTimingData)
        dwTimestamp3                                  =  s_Timer.GetMicroseconds();
        dwTimestamp2                                  =  dwTimestamp3;
        g_nPowerModulusTime[ePowerModulusProcessTime] += (dwTimestamp3 - dwTimestamp);
        DivideBackend(nXSize, nZSize, nXSize, nPowerModulusSize, pnWorkspace, pnZValue, pnWorkspace + nXSize, dwTimestamp2, pnWorkspace + nXSize + nXSize - nZSize + 1);
        g_nPowerModulusTime[ePowerModulusDivideTime]  += (dwTimestamp2 - dwTimestamp3);
#else
        DivideBackend(nXSize, nZSize, nXSize, nPowerModulusSize, pnWorkspace, pnZValue, pnWorkspace+nXSize, pnWorkspace+nXSize+nXSize-nZSize+1);
#endif
        nXSize = nPowerModulusSize;
        memcpy(pnPowerModulus, pX, sizeof(DIGIT)*nXSize);
        pnWorkspace += nZSize;
    }
    else
    {
        // use x directly rather than x mod z
        // first "multiply" -- just copy x into place
        pX = pnXValue;
        memcpy(pnPowerModulus, pnXValue, sizeof(DIGIT)*nXSize);
        nPowerModulusSize = nXSize;
    }
    if(0<nPowerDigit || 1<nPowerBit)
    {
        size_t nDivSize; // dummy variable; don't care about it
        size_t nNewModulusSize;
        size_t nProdSize;
        do
        {
            // update power bit "pointer" to the next bit
            nPowerBit = nPowerBit>>1;
            if(0==nPowerBit)
            {
                if(0==nPowerDigit)
                {
                    // done
                    break;
                }
                nPowerDigit--;
                nPowerBit = ((size_t) 1)<<(_DIGIT_SIZE_IN_BITS-1);
            }
            // square
            if (0 == nPowerModulusSize)
            {
                // end of the line -- number has 0 as its power modulus -- e.g. 4 with modulus 16: (4*4)%16 = 0, so (4^n)%16 = 0 for 1<n
                break;
            }
#if(_CollectDetailedTimingData)
            dwTimestamp3                                   =  s_Timer.GetMicroseconds();
            g_nPowerModulusTime[ePowerModulusProcessTime]  += (dwTimestamp3 - dwTimestamp2);
            dwTimestamp2                                   =  dwTimestamp3;
            SquareUBackend(nPowerModulusSize,
                           pnPowerModulus,
                           pnWorkspace,
                           pnWorkspace+(nZSize<<1),
                           dwTimestamp2,
                           &nProdSize);
            g_nPowerModulusTime[ePowerModulusMultiplyTime] += (dwTimestamp2 - dwTimestamp3);
            dwTimestamp3                                   =  dwTimestamp2;
            // take modulus
            DivideBackend(nProdSize,
                          nZSize,
                          nDivSize,
                          nPowerModulusSize,
                          pnWorkspace,
                          pnZValue,
                          pnWorkspace+(nZSize<<1),         // div value -- don't care what it is, actually
                          dwTimestamp2,
                          pnWorkspace+(nZSize<<1)+nProdSize-nZSize+1);
            g_nPowerModulusTime[ePowerModulusDivideTime]  += (dwTimestamp2 - dwTimestamp3);
#else
            SquareUBackend(nPowerModulusSize,
                           pnPowerModulus,
                           pnWorkspace,
                           pnWorkspace+(nZSize<<1),
                           &nProdSize);
            // take modulus
            DivideBackend(nProdSize,
                          nZSize,
                          nDivSize,
                          nPowerModulusSize,
                          pnWorkspace,
                          pnZValue,
                          pnWorkspace+(nZSize<<1),         // div value -- don't care what it is, actually
                          pnWorkspace+(nZSize<<1)+nProdSize-nZSize+1);
#endif
            if(0 != (nPowerBit&(pnYValue[nPowerDigit])) || bProtectAgainstTimingAttacks)
            {
#if(_CollectDetailedTimingData)
                // multiply by x
                dwTimestamp3 = dwTimestamp2;
                MultUBackend(nPowerModulusSize,
                             nXSize,
                             pnWorkspace,
                             pX,
                             pnWorkspace+(nZSize<<1), // KNOW that nPowerModulusSize <= nZSize; this way, don't need to save old power modulus size, too
                             pnWorkspace+(nZSize<<1)+nPowerModulusSize+nXSize,
                             dwTimestamp2,
                             &nProdSize);
                g_nPowerModulusTime[ePowerModulusMultiplyTime] += (dwTimestamp2 - dwTimestamp3);
                dwTimestamp3                                   =  dwTimestamp2;
                // take modulus
                DivideBackend(nProdSize,
                              nZSize,
                              nDivSize,
                              nNewModulusSize,
                              pnWorkspace+(nZSize<<1),
                              pnZValue,
                              pnWorkspace+(nZSize<<1)+nProdSize,
                              dwTimestamp2,
                              pnWorkspace+(nZSize<<1)+nProdSize+nProdSize-nZSize+1);
                g_nPowerModulusTime[ePowerModulusDivideTime] += (dwTimestamp2 - dwTimestamp3);
#else
                // multiply by x
                MultUBackend(nPowerModulusSize,
                             nXSize,
                             pnWorkspace,
                             pX,
                             pnWorkspace+(nZSize<<1), // KNOW that nPowerModulusSize <= nZSize; this way, don't need to save old power modulus size, too
                             pnWorkspace+(nZSize<<1)+nPowerModulusSize+nXSize,
                             &nProdSize);
                // take modulus
                DivideBackend(nProdSize,
                              nZSize,
                              nDivSize,
                              nNewModulusSize,
                              pnWorkspace+(nZSize<<1),
                              pnZValue,
                              pnWorkspace+(nZSize<<1)+nProdSize,
                              pnWorkspace+(nZSize<<1)+nProdSize+nProdSize-nZSize+1);
#endif
                if(0 != (nPowerBit&(pnYValue[nPowerDigit])))
                {
                    // copy result back into power modulus
                    memcpy(pnPowerModulus,pnWorkspace+(nZSize<<1),sizeof(DIGIT)*nNewModulusSize);
                    nPowerModulusSize = nNewModulusSize;
                }
                else
                {
                    // copy result of original divide back into power modulus -- protection against timing attacks path
                    memcpy(pnPowerModulus,pnWorkspace,sizeof(DIGIT)*nPowerModulusSize);
                }
            }
            else
            {
                // copy the mod result back into the power modulus
                memcpy(pnPowerModulus,pnWorkspace,sizeof(DIGIT)*nPowerModulusSize);
            }
        }
        while(1);
    }
#if(_CollectDetailedTimingData)
    dwTimestamp3 = s_Timer.GetMicroseconds();
    g_nPowerModulusTime[ePowerModulusProcessTime] += (dwTimestamp3 - dwTimestamp2);
    g_nPowerModulusTime[ePowerModulusTotalTime]   += (dwTimestamp3 - dwTimestamp);
    dwTimestamp                                   =  dwTimestamp3;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                    //
//                                               Montgomery Stuff                                                     //
//                       see https://en.wikipedia.org/wiki/Montgomery_modular_multiplication                          //
//                                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CUnsignedArithmeticHelper::GetMontgomeryParameters(size_t nNSize,
                                                        size_t &nNPrimeSize,
                                                        size_t &nRPrimeSize,
                                                        DIGIT  *pNValue,
                                                        DIGIT  *pNPrimeValue,
                                                        DIGIT  *pRPrimeValue,
                                                        DIGIT  *pWorkspace)
{
    // construct R -- in this one instance, we need it
    size_t nDummySize; // where function wants to set a size value we don't care about
    bool   bRCoefNeg;
    DIGIT  *pR = pWorkspace;
    pWorkspace += nNSize+1;
    memset(pR, 0, sizeof(DIGIT)*nNSize);
    pR[nNSize] = 1;
    GCD(nNSize+1, nNSize, nDummySize, nRPrimeSize, nNPrimeSize, pR, pNValue, pWorkspace, pRPrimeValue, pNPrimeValue, bRCoefNeg, pWorkspace + nNSize);
    // Now, we have R*R' + N*N' = gcd = 1.
    // Either R' or N' is negative depending on bRCoefNeg
    // What we want is R*R' - N*N' = 1, with both R' and N' positive.
    // If not bRCoefNeg, we're good.
    // Otherwise, note that |R'| < N and |N'| < R
    // Then R*R' + N*N' == -R*|R'| + N*|N'|
    //                  == R*|N-R'| + N*|R-N'|
    // So if we replace R' with N-R' and N' with R-N' (ignoring signs in both cases) we're done
    if (bRCoefNeg)
    {
        size_t      i;
        DOUBLEDIGIT nSub = 0;
        // N - R'
        nRPrimeSize = Subtract(nNSize, nRPrimeSize, pNValue, pRPrimeValue, pRPrimeValue);
        // R - N'.  Recall R is 1<<nNSize
        for(i=0; i<nNPrimeSize; i++)
        {
            nSub            += pNPrimeValue[i];
            pNPrimeValue[i] =  -nSub;
            nSub            =  (0<nSub);
        }
        for(; i<nNSize; i++)
        {
            // note that we know N' is not zero
            pNPrimeValue[i] = c_nClearHigh;
        }
        nNPrimeSize = nNSize;
        while(0== pNPrimeValue[nNPrimeSize-1]) nNPrimeSize--;
    }
}

// "Recall:"  The Montgomery form of the residue class a with respect to R is aR mod N
void CUnsignedArithmeticHelper::ToMontgomeryForm(size_t      nXSize,
                                                 size_t      nNSize,
                                                 size_t      &nXMontgomerySize,
                                                 const DIGIT *pXValue,
                                                 DIGIT       *pNValue,
                                                 DIGIT       *pXMontgomeryValue,
#if(_CollectDetailedTimingData)
                                                 DWORD64     &dwTimestamp,
#endif
                                                 DIGIT       *pWorkspace)
{
    size_t nDummy; // used to hold the size of aR/N -- a value we don't care about
    memset(pXMontgomeryValue, 0, sizeof(DIGIT)*nNSize);
    for(size_t i=0;i<nXSize; i++)
    {
        pXMontgomeryValue[nNSize+i] = pXValue[i];
    }
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp2 = s_Timer.GetMicroseconds();
    g_nPowerModulusTime[ePowerModulusProcessTime] += (dwTimestamp2 - dwTimestamp);
    dwTimestamp                                   =  dwTimestamp2;
    DivideBackend(nXSize+nNSize, nNSize, nDummy, nXMontgomerySize, pXMontgomeryValue, pNValue, pWorkspace, dwTimestamp, pWorkspace+nXSize+1);
    g_nPowerModulusTime[ePowerModulusDivideTime]  += (dwTimestamp - dwTimestamp2);
#else
    DivideBackend(nXSize+nNSize, nNSize, nDummy, nXMontgomerySize, pXMontgomeryValue, pNValue, pWorkspace, pWorkspace+nXSize+1);
#endif
}

// x == (xMontgomery*R') mod N
void CUnsignedArithmeticHelper::FromMontgomeryForm(size_t      nMontgomerySize,
                                                   size_t      nNSize,
                                                   size_t      nRPrimeSize,
                                                   size_t      &nXSize,
                                                   const DIGIT *pXMontgomeryValue,
                                                   DIGIT       *pNValue,
                                                   const DIGIT *pRPrimeValue,
                                                   DIGIT       *pXValue,
#if(_CollectDetailedTimingData)
                                                   DWORD64     &dwTimestamp,
#endif
                                                   DIGIT       *pWorkspace)
{
    size_t nDummy; // used to hold the size of aR'/N -- a value we don't care about
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp2 = dwTimestamp;
    MultUBackend(nMontgomerySize, nRPrimeSize, pXMontgomeryValue, pRPrimeValue, pWorkspace, pWorkspace+nMontgomerySize+nRPrimeSize, dwTimestamp2);
    g_nPowerModulusTime[ePowerModulusMultiplyTime] += (dwTimestamp - dwTimestamp2);
#else
    MultUBackend(nMontgomerySize, nRPrimeSize, pXMontgomeryValue, pRPrimeValue, pWorkspace, pWorkspace+nMontgomerySize+nRPrimeSize);
#endif
    nXSize = nMontgomerySize + nRPrimeSize;
    if(0==pWorkspace[nXSize-1]) nXSize--;
#if(_CollectDetailedTimingData)
    dwTimestamp2 = dwTimestamp;
    DivideBackend(nXSize, nNSize, nDummy, nXSize, pWorkspace, pNValue, pWorkspace+nMontgomerySize+nRPrimeSize, dwTimestamp, pWorkspace+nMontgomerySize+nRPrimeSize+nXSize-nNSize+1);
    g_nPowerModulusTime[ePowerModulusMultiplyTime] += (dwTimestamp - dwTimestamp2);
#else
    DivideBackend(nXSize, nNSize, nDummy, nXSize, pWorkspace, pNValue, pWorkspace+nMontgomerySize+nRPrimeSize, pWorkspace+nMontgomerySize+nRPrimeSize+nXSize-nNSize+1);
#endif
    memcpy(pXValue, pWorkspace, nXSize*sizeof(DIGIT));
}

/*
function REDC is
input: Integers R and N with gcd(R, N) = 1,
       Integer N' in [0, R - 1] such that NN? ? ?1 mod R,
       Integer T in the range [0, RN - 1].
output: Integer S in the range [0, N - 1] such that S = TR^(-1) mod N

m <- ((T mod R)N') mod R
s <- (T + mN)/R
if s >= N then
    return s - N
else
    return s
end if
end function
*/
void CUnsignedArithmeticHelper::REDC(size_t       nNSize,
                                     size_t       nNPrimeSize,
                                     size_t       &nSTSize,
                                     const DIGIT  *pNValue,
                                     const DIGIT  *pNPrimeValue,
                                     const DIGIT  *pTValue,
                                     DIGIT        *pSValue,
#if(_CollectDetailedTimingData)
                                     DWORD64      &dwTimestamp,
#endif
                                     DIGIT        *pWorkspace)
{
    DOUBLEDIGIT nCarry, nSum;
    size_t      i, nMSize;
    DIGIT       *pM = pWorkspace;
    nMSize = min(nSTSize, nNSize);
    // note that mod R is accomplished by just returning the last (at most) nNSize digits
    //           divide by R skipping the last nNSize digits
    // m = ((T mod R)*N') mod R
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp2 = dwTimestamp;
    MultUBackend(nMSize, // taking size min gives T mod R
                 nNPrimeSize,
                 pTValue,
                 pNPrimeValue,
                 pM,
                 pWorkspace + nNPrimeSize + nNSize,
                 dwTimestamp);
    g_nPowerModulusTime[ePowerModulusMultiplyTime] += (dwTimestamp - dwTimestamp2);
#else
    MultUBackend(nMSize, // taking size min gives T mod R
                 nNPrimeSize,
                 pTValue,
                 pNPrimeValue,
                 pM,
                 pWorkspace + nNPrimeSize + nNSize);
#endif
    nMSize = min(nMSize+nNPrimeSize, nNSize);
    while(0<nMSize && 0==pWorkspace[nMSize-1])
    {
        nMSize--;
    }
    pWorkspace += nMSize;
    // s <- (T + mN)/R
    if (0 != nMSize)
    {
        // mN
        size_t nMultSize = nMSize + nNSize;
#if _CollectDetailedTimingData
        dwTimestamp2 = dwTimestamp;
        MultUBackend(nMSize, nNSize, pM, pNValue, pWorkspace, pWorkspace+nMultSize, dwTimestamp);
        g_nPowerModulusTime[ePowerModulusMultiplyTime] += (dwTimestamp - dwTimestamp2);
#else
        MultUBackend(nMSize, nNSize, pM, pNValue, pWorkspace, pWorkspace+nMultSize);
#endif
        if(0==pWorkspace[nMultSize-1]) nMultSize--;
        // Note that by construction (and how N' was chosen), (T+mN) is evenly divisible by R.
        // Further we don't care about the last nNSize digits (dividing by R!).
        // So we don't actually need to add the last nNSize digits, except to see if there will
        // be a carry-out.  If  either digit (nNSize-1) of T or mN is nonzero, there will be
        // a carry out of 1 when we add T to mN; otherwise, no carry-out.
        nCarry = (0!= pWorkspace[nNSize-1] || (nNSize<=nSTSize && 0!= pTValue[nNSize-1]));
        for(i=nNSize; i<min(nSTSize, nMultSize); i++)
        {
            nSum                = (nCarry + pTValue[i]) + pWorkspace[i];
            nCarry              = nSum>>_DIGIT_SIZE_IN_BITS;
            pSValue[i - nNSize] = (DIGIT) nSum;
        }
        for(; i<nMultSize; i++)
        {
            nSum                = nCarry + pWorkspace[i];
            nCarry              = nSum>>_DIGIT_SIZE_IN_BITS;
            pSValue[i - nNSize] = (DIGIT) nSum;
        }
        for(; i<nSTSize; i++)
        {
            nSum                = nCarry + pTValue[i];
            nCarry              = nSum>>_DIGIT_SIZE_IN_BITS;
            pSValue[i - nNSize] = (DIGIT) nSum;
        }
        nSTSize = i - nNSize;
        if (nCarry) pSValue[nSTSize++] = nCarry;
        if (-1 != CBigInteger::CompareUnsigned(nSTSize, nNSize, pSValue, pNValue))
        {
            // need to subtract off the modulus
            nSTSize = Subtract(nSTSize, nNSize, pSValue, pNValue, pSValue);
        }
    }
    else
    {
        nSTSize = max(0,nSTSize-nNSize);
        for(size_t i=0; i<nSTSize; i++)
        {
            pSValue[i] = pTValue[i+nNSize];
        }
    }
#if _CollectDetailedTimingData
    dwTimestamp2                                  =  dwTimestamp;
    dwTimestamp                                   =  s_Timer.GetMicroseconds();
    g_nPowerModulusTime[ePowerModulusProcessTime] += (dwTimestamp - dwTimestamp2);
#endif
}

void CUnsignedArithmeticHelper::MontgomeryMultiply(size_t       nXSize,
                                                   size_t       nYSize,
                                                   size_t       nNSize,
                                                   size_t       nNPrimeSize,
                                                   size_t       &nZSize,
                                                   const DIGIT  *pXValue,
                                                   const DIGIT  *pYValue,
                                                   const DIGIT  *pNValue,
                                                   const DIGIT  *pNPrimeValue,
                                                   DIGIT        *pZValue,
#if(_CollectDetailedTimingData)
                                                   DWORD64      &dwTimestamp,
#endif
                                                   DIGIT        *pWorkspace)
{
    DIGIT *pIntermediateValue = pWorkspace;
    pWorkspace += nXSize + nYSize;
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp2 = dwTimestamp;
    MultUBackend(nXSize,
                 nYSize,
                 pXValue,
                 pYValue,
                 pIntermediateValue,
                 pWorkspace,
                 dwTimestamp);
    g_nPowerModulusTime[ePowerModulusMultiplyTime] += (dwTimestamp - dwTimestamp2);
#else
    MultUBackend(nXSize,
                 nYSize,
                 pXValue,
                 pYValue,
                 pIntermediateValue,
                 pWorkspace);
#endif
    nZSize = nXSize + nYSize;
    if(0==pIntermediateValue[nZSize-1]) nZSize--;
#if(_CollectDetailedTimingData)
    REDC(nNSize, nNPrimeSize, nZSize, pNValue, pNPrimeValue, pIntermediateValue, pZValue, dwTimestamp, pWorkspace);
#else
    REDC(nNSize, nNPrimeSize, nZSize, pNValue, pNPrimeValue, pIntermediateValue, pZValue, pWorkspace);
#endif
}

void CUnsignedArithmeticHelper::MontgomerySquare(size_t       nXSize,
                                                 size_t       nNSize,
                                                 size_t       nNPrimeSize,
                                                 size_t       &nZSize,
                                                 const DIGIT  *pXValue,
                                                 const DIGIT  *pNValue,
                                                 const DIGIT  *pNPrimeValue,
                                                 DIGIT        *pZValue,
#if(_CollectDetailedTimingData)
                                                 DWORD64      &dwTimestamp,
#endif
                                                 DIGIT        *pWorkspace)
{
    DIGIT *pIntermediateValue = pWorkspace;
    pWorkspace += (nXSize<<1);
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp2 = dwTimestamp;
    SquareUBackend(nXSize,
                   pXValue,
                   pIntermediateValue,
                   pWorkspace,
                   dwTimestamp);
    g_nPowerModulusTime[ePowerModulusMultiplyTime] += (dwTimestamp - dwTimestamp2);
#else
    SquareUBackend(nXSize,
                   pXValue,
                   pIntermediateValue,
                   pWorkspace);
#endif
    nZSize = nXSize<<1;
    if(0==pIntermediateValue[nZSize-1]) nZSize--;
#if(_CollectDetailedTimingData)
    REDC(nNSize, nNPrimeSize, nZSize, pNValue, pNPrimeValue, pIntermediateValue, pZValue, dwTimestamp, pWorkspace);
#else
    REDC(nNSize, nNPrimeSize, nZSize, pNValue, pNPrimeValue, pIntermediateValue, pZValue, pWorkspace);
#endif
}

void CUnsignedArithmeticHelper::MontgomeryPowerModulus(size_t      nXSize,
                                                       size_t      nYSize,
                                                       size_t      nModulusSize,
                                                       size_t      nModulusPrimeSize,
                                                       size_t      nRPrimeSize,
                                                       size_t      &nPowerModulusSize,
                                                       const DIGIT *pnXValue,
                                                       const DIGIT *pnYValue,
                                                       const DIGIT *pnRPrimeValue,
                                                       DIGIT       *pnModulusValue,
                                                       const DIGIT *pnModulusPrimeValue,
                                                       DIGIT       *pnPowerModulus,
                                                       DIGIT       *pnWorkspace,
                                                       bool        bProtectAgainstTimingAttacks)
{
    size_t nLeadPowerBit, nLeadPowerDigit, nPowerModulusSizeMontgomery;
    DIGIT  *pnPowerModulusMontgomery;
    GetLeadBit(nYSize, pnYValue, nLeadPowerDigit, nLeadPowerBit);
    MontgomeryPowerModulus(nXSize,
                           nYSize,
                           nModulusSize,
                           nModulusPrimeSize,
                           nRPrimeSize,
                           nLeadPowerDigit,
                           nLeadPowerBit,
                           nPowerModulusSize,
                           pnXValue,
                           pnYValue,
                           pnRPrimeValue,
                           pnModulusValue,
                           pnModulusPrimeValue,
                           pnPowerModulus,
                           pnWorkspace,
                           bProtectAgainstTimingAttacks);
}

void CUnsignedArithmeticHelper::MontgomeryPowerModulus(size_t      nXSize,
                                                       size_t      nYSize,
                                                       size_t      nModulusSize,
                                                       size_t      nModulusPrimeSize,
                                                       size_t      nRPrimeSize,
                                                       size_t      nPowerDigit,
                                                       size_t      nPowerBit,
                                                       size_t      &nPowerModulusSize,
                                                       const DIGIT *pnXValue,
                                                       const DIGIT *pnYValue,
                                                       const DIGIT *pnRPrimeValue,
                                                       DIGIT       *pnModulusValue,
                                                       const DIGIT *pnModulusPrimeValue,
                                                       DIGIT       *pnPowerModulus,
                                                       DIGIT       *pnWorkspace,
                                                       bool        bProtectAgainstTimingAttacks)
{
    size_t nLeadPowerBit, nLeadPowerDigit, nPowerModulusSizeMontgomery;
    DIGIT  *pXMontgomery, *pnPowerModulusMontgomery;
    // convert X to Montgomery form
    pXMontgomery             = pnWorkspace;
    pnPowerModulusMontgomery = pXMontgomery             + nXSize + nModulusSize; // pX needs nXSize + nModulusSize space (initial copy for divide)
    pnWorkspace              = pnPowerModulusMontgomery + nModulusSize + 1; // needs modulus space, +1 extra digit for overflow
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp  = s_Timer.GetMicroseconds();
    DWORD64 dwTimestamp2 = dwTimestamp;
    g_nPowerModulusTime[eTotalPowerModulusCalls]++;
    ToMontgomeryForm(nXSize, nModulusSize, nXSize, pnXValue, pnModulusValue, pXMontgomery, dwTimestamp, pnWorkspace);
#else
    ToMontgomeryForm(nXSize, nModulusSize, nXSize, pnXValue, pnModulusValue, pXMontgomery, pnWorkspace);
#endif
    if (0 != nXSize)
    {
        MontgomeryPowerModulus(nXSize,
                               nYSize,
                               nModulusSize,
                               nModulusPrimeSize,
                               nPowerDigit,
                               nPowerBit,
                               nPowerModulusSizeMontgomery,
                               pXMontgomery,
                               pnYValue,
                               pnModulusValue,
                               pnModulusPrimeValue,
                               pnPowerModulusMontgomery,
#if(_CollectDetailedTimingData)
                               dwTimestamp,
#endif
                               pnWorkspace,
                               bProtectAgainstTimingAttacks);
        // convert back to standard form and store the result in pnPowerModulus
        FromMontgomeryForm(nPowerModulusSizeMontgomery,
                           nModulusSize,
                           nRPrimeSize,
                           nPowerModulusSize,
                           pnPowerModulusMontgomery,
                           pnModulusValue,
                           pnRPrimeValue,
                           pnPowerModulus,
#if(_CollectDetailedTimingData)
                           dwTimestamp,
#endif
                           pnWorkspace);
    }
    else
    {
        // zero in, zero out
        nPowerModulusSize = 0;
    }
#if(_CollectDetailedTimingData)
    g_nPowerModulusTime[ePowerModulusTotalTime] += (dwTimestamp - dwTimestamp2);
#endif
}

void CUnsignedArithmeticHelper::MontgomeryPowerModulus(size_t      nXSize,
                                                       size_t      nYSize,
                                                       size_t      nModulusSize,
                                                       size_t      nModulusPrimeSize,
                                                       size_t      nPowerDigit,
                                                       size_t      nPowerBit,
                                                       size_t      &nPowerModulusSize,
                                                       const DIGIT *pnXValue,
                                                       const DIGIT *pnYValue,
                                                       const DIGIT *pnModulusValue,
                                                       const DIGIT *pModulusPrimeValue,
                                                       DIGIT       *pnPowerModulus,
#if(_CollectDetailedTimingData)
                                                       DWORD64     &dwTimestamp,
#endif
                                                       DIGIT       *pnWorkspace,
                                                       bool        bProtectAgainstTimingAttacks)
{
    bool  bMultAndSquare;
    // first "multiply" -- just copy x into place
    memcpy(pnPowerModulus, pnXValue, sizeof(DIGIT)*nXSize);
    nPowerModulusSize = nXSize;
    if(0<nPowerDigit || 1<nPowerBit)
    {
        do
        {
            // update power bit "pointer" to the next bit
            nPowerBit = nPowerBit>>1;
            if(0==nPowerBit)
            {
                if(0==nPowerDigit)
                {
                    // done
                    break;
                }
                nPowerDigit--;
                nPowerBit = ((size_t) 1)<<(_DIGIT_SIZE_IN_BITS-1);
            }
            if (0 == nPowerModulusSize)
            {
                // end of the line -- number has 0 as its power modulus -- e.g. 4 with modulus 16: (4*4)%16 = 0, so (4^n)%16 = 0 for 1<n
                break;
            }
            bMultAndSquare = (0 != (nPowerBit&(pnYValue[nPowerDigit])));
            // square
            MontgomerySquare(nPowerModulusSize,
                             nModulusSize,
                             nModulusPrimeSize,
                             nPowerModulusSize,
                             pnPowerModulus,
                             pnModulusValue,
                             pModulusPrimeValue,
                             bMultAndSquare ? pnWorkspace : pnPowerModulus,
#if(_CollectDetailedTimingData)
                             dwTimestamp,
#endif
                             pnWorkspace+(nModulusSize<<1)+1);
            if(bMultAndSquare)
            {
                // multiply by x
                MontgomeryMultiply(nPowerModulusSize,
                                   nXSize,
                                   nModulusSize,
                                   nModulusPrimeSize,
                                   nPowerModulusSize,
                                   pnWorkspace,
                                   pnXValue,
                                   pnModulusValue,
                                   pModulusPrimeValue,
                                   pnPowerModulus,
#if(_CollectDetailedTimingData)
                                   dwTimestamp,
#endif
                                   pnWorkspace + (nModulusSize<<1)+1);
            }
            else if(bProtectAgainstTimingAttacks)
            {
                // do the multiply by x anyway; just throw away the result;
                size_t nProductSize;
                MontgomeryMultiply(nPowerModulusSize,
                                   nXSize,
                                   nModulusSize,
                                   nModulusPrimeSize,
                                   nProductSize,
                                   pnPowerModulus,
                                   pnXValue,
                                   pnModulusValue,
                                   pModulusPrimeValue,
                                   pnWorkspace,
#if(_CollectDetailedTimingData)
                                   dwTimestamp,
#endif
                                   pnWorkspace + (nModulusSize<<1)+1);
            }
        }
        while(1);
    }
}

// Note that the size of the square root of a number X, in DIGITs, is ALWAYS (size of X)/2, round UP.
void CUnsignedArithmeticHelper::SQRT(size_t nXSize, size_t &nRootSize, DIGIT *pnX, DIGIT *pnSquareRoot, DIGIT *pWorkspace)
{
    if (0 == nXSize)
    {
        // back end doesn't deal well with 0
        nRootSize = 0;
    }
    else
    {
#if(_CollectDetailedTimingData)
        DWORD64 dwTimestamp  = s_Timer.GetMicroseconds();
        DWORD64 dwTimestamp2 = dwTimestamp;
        SquareRootRecursive(nXSize, nRootSize, pnX, pnSquareRoot, dwTimestamp, pWorkspace);
        g_nSquareRootTime[eTotalSquareRootTime] += (dwTimestamp - dwTimestamp2);
        g_nSquareRootTime[eTotalSquareRootCalls]++;
#else
        SquareRootRecursive(nXSize, nRootSize, pnX, pnSquareRoot, pWorkspace);
#endif
    }
}

/*
  Consider taking the square root of the number x = {x0, x1, x2, x3} -- or, rather, the largest number y = {y0, y1} such that y^2 <= x.
  Suppose we have that y' is the largest number s.t. y'^2 <= 10*x0 + x1.
  Let Ya be y' shifted over by half the size of {x2, x3}.
  Then { x0, x1, x2, x3 } - {y', y1}^2  is 1000x0 + 100x1 + 10x2 + x3 - 100y'^2 - 20y'y1 - y1^2
  <-> {x0, ..., x3} - Ya^2 - 2Yay1 - y1^2
  Ya is known, so we want the largest y1 s.t. (2Ya + y1)*y1 <= {x0, ..., x3} - Ya^2
  We then solve this latter (smaller) problem with GeneralSquareRootRecursive
*/
void CUnsignedArithmeticHelper::SquareRootRecursive(size_t  nXSize,
                                                    size_t  &nRootSize,
                                                    DIGIT   *pnX,
                                                    DIGIT   *pnRoot,
#if(_CollectDetailedTimingData)
                                                    DWORD64 &dwTimestamp,
#endif
                                                    DIGIT   *pnWorkspace)
{
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp2;
#endif
    DIGIT   *pnX1, *pnX2, *pnYPrime, *pnY1;
    size_t  nOffset, nX1Size, nX2Size, nYPrimeSize, nYPrimeSquaredSize, nY1Size, i;
    if (nXSize < c_nSquareRootThreshold)
    {
        SquareRootNewton(nXSize,
                         nRootSize,
                         pnX,
                         pnRoot,
#if(_CollectDetailedTimingData)
                         dwTimestamp,
#endif
                         pnWorkspace);
    }
    else
    {
        DOUBLEDIGIT nCarry, nVal;
        nOffset     = ((nXSize+3)>>2)<<1;      // offset needs to be even, and at least half x size
        pnX1        = pnWorkspace;
        pnYPrime    = pnX1     + (nOffset>>1); // NOTE: we use that y' immediately follows x1 in memory!
        pnWorkspace = pnYPrime + ((nXSize + 1)>>1) + 1;
        SquareRootRecursive(nXSize - nOffset,
                            nYPrimeSize,
                            pnX + nOffset,
                            pnYPrime,
#if(_CollectDetailedTimingData)
                            dwTimestamp,
#endif
                            pnWorkspace);
        // x2 is X - y'^2
        pnX2        =  pnWorkspace;
        pnWorkspace += nXSize + 1; // +1: needs a little extra space for intermediate results
#if(_CollectDetailedTimingData)
        dwTimestamp2 = dwTimestamp;
        SquareUBackend(nYPrimeSize, pnYPrime, pnWorkspace, pnWorkspace + (nYPrimeSize<<1), dwTimestamp);
        g_nSquareRootTime[eSquareRootMultiplyTime] += (dwTimestamp - dwTimestamp2);
#else
        SquareUBackend(nYPrimeSize, pnYPrime, pnWorkspace, pnWorkspace + (nYPrimeSize<<1));
#endif
        nYPrimeSquaredSize = (0 == pnWorkspace[(nYPrimeSize<<1) - 1]) ? (nYPrimeSize<<1) - 1 : (nYPrimeSize<<1);
        nX2Size            = Subtract(nXSize - nOffset, nYPrimeSquaredSize, pnX + nOffset, pnWorkspace, pnX2 + nOffset) + nOffset;
        for (i=0; i<nOffset; i++)
        {
            pnX2[i] = pnX[i];
        }
        // x1 = Y' shifted left half of nOffset and multiplied by 2.  Note we don't need y' after computing x1; use the same space
        for(i=0; i<(nOffset>>1); i++)
        {
            pnX1[i] = 0;
        }
        nCarry = 0;
        for(i=0;i<nYPrimeSize;i++)
        {
            nCarry      += (((DOUBLEDIGIT) pnYPrime[i])<<1);
            pnYPrime[i] =  nCarry;
            nCarry      =  nCarry>>_DIGIT_SIZE_IN_BITS;
        }
        pnYPrime[i] =  nCarry;
        nX1Size     =  nYPrimeSize + (nOffset>>1) + nCarry; // note: nCarry is at most 1
        pnY1        =  pnWorkspace;
        pnWorkspace += nX2Size+1; // max size Y1 can be, with one extra DIGIT for overflow
        // solve for y1, the largest value satisfying (x1 + y1)*y1 <= x2
#if(_CollectDetailedTimingData)
        dwTimestamp2                              =  s_Timer.GetMicroseconds();
        g_nSquareRootTime[eSquareRootProcessTime] += (dwTimestamp2 - dwTimestamp);
        GeneralSquareRootRecursive(nX1Size, nX2Size, nY1Size, pnX1, pnX2, pnY1, dwTimestamp, pnWorkspace);
#else
        GeneralSquareRootRecursive(nX1Size, nX2Size, nY1Size, pnX1, pnX2, pnY1, pnWorkspace);
#endif
        // splice the two parts together into the root
        nRootSize = (nXSize+1)>>1;
        for(i=0; i<nY1Size; i++)
        {
            pnRoot[i] = pnY1[i];
        }
        for(; i<(nOffset>>1); i++)
        {
            pnRoot[i] = 0;
        }
        pnRoot += (nOffset>>1);
        if(nY1Size<=(nOffset>>1))
        {
            i      = nYPrimeSize;
            nCarry = (pnYPrime[i]<<(_DIGIT_SIZE_IN_BITS-1)); // note: pnYPrime[i] can only be 0 or 1
            do
            {
                nVal      = pnYPrime[--i];
                nCarry    = nCarry | (nVal>>1);
                pnRoot[i] = nCarry;
                nCarry    = (nVal&1)<<(_DIGIT_SIZE_IN_BITS-1); // &1 likely redundant -- ret get dropped anyway when cast to DIGIT
            }
            while(i);
        }
        else
        {
            // some overlap between the two pieces
            for(i=0; i<nY1Size-(nOffset>>1); i++)
            {
                nCarry    = (((DOUBLEDIGIT) pnRoot[i]) + (pnYPrime[i]>>1)) + (pnYPrime[i+1]<<(_DIGIT_SIZE_IN_BITS-1));
                pnRoot[i] = nCarry;
                nCarry    = (nCarry>>_DIGIT_SIZE_IN_BITS);
            }
            for(; i<nYPrimeSize; i++)
            {
                nCarry    = ((DOUBLEDIGIT) + (pnYPrime[i]>>1)) + (pnYPrime[i+1]<<(_DIGIT_SIZE_IN_BITS-1));
                pnRoot[i] = nCarry;
                nCarry    = (nCarry>>_DIGIT_SIZE_IN_BITS);
            }
        }
#if(_CollectDetailedTimingData)
        dwTimestamp2                              =  dwTimestamp;
        dwTimestamp                               =  s_Timer.GetMicroseconds();
        g_nSquareRootTime[eSquareRootProcessTime] += (dwTimestamp - dwTimestamp2);
#endif
    }
}

// gives the size in bits of the DIGIT passed.  Assumed to NOT be zero!
unsigned int DigitBitSize(DIGIT n)
{
    unsigned int nSize = _DIGIT_SIZE_IN_BITS;
    unsigned int nBit  = 1<<(_DIGIT_SIZE_IN_BITS-1);
    while(0==(n&nBit))
    {
        nSize--;
        nBit = nBit>>1;
    }
    return nSize;
}

// gives the size in bits of the DOUBLEDIGIT passed.  Assumed to NOT be zero!
unsigned int DigitBitSize(DOUBLEDIGIT n)
{
    unsigned int nSize = _DIGIT_SIZE_IN_BITS*2;
    DOUBLEDIGIT  nBit  = ((DOUBLEDIGIT) 1)<<(_DIGIT_SIZE_IN_BITS*2 - 1);
    while (0 == (n&nBit))
    {
        nSize--;
        nBit = nBit>>1;
    }
    return nSize;
}

// gives the size in BITs of the number passed
size_t CUnsignedArithmeticHelper::BitSize(size_t nXSize, const DIGIT *pnX)
{
    if (0 == nXSize) return 0;
    DIGIT       nFirstDigit = pnX[nXSize - 1];
    DOUBLEDIGIT nMask       = ((DOUBLEDIGIT) 1)<<(_DIGIT_SIZE_IN_BITS - 1);
    size_t      nBits       = nXSize*_DIGIT_SIZE_IN_BITS; // BITs in nX
    while (0 == (nFirstDigit&nMask))
    {
        nBits--;
        nMask = nMask>>1;
    }
    return nBits;
}

// Find: largest y s.t. (x1 + y)y <= x2.  Note that with x1 positive, it is clear that y < sqrt(x2)
// Write y = ya + yb.  Suppose ya is chosen to satisfy 0<ya and (x1 + ya)ya <= x2.  The it is clear to satisfy
// y is the largest value s.t. (x1 + y)y <= x2, we just need to choose yb appropriately:
// yb is the largest value s.t. (x1 + ya + yb)(ya + yb) <= x2
// <->
// (x1 + ya + yb)yb + (x1 + ya + yb)ya <= x2
// <->
// (x1 + 2ya + yb)yb + (x1 + ya)ya <= x2
// <->
// (x1a + yb)yb <= x2a
// where x1a = (x1 + 2ya) and x2a = x2 - (x1 + ya)ya
// We just need a simple way to pick ya s.t. picking yb is likewise made simpler
// write x2 = {xa, xb}
// Solve ya is the largest value with (x1 + ya)ya <= xa
// Write y = ya' + yb where ya' is ya shifted to line up with xa in {xa, xb}: shifted half the size of xb
// Then we wish to find the largest yb s.t.
// (x1 + ya' + yb)(ya' + yb) <= {xa, xb}
// <-> (x1 + ya' + yb)yb + (x1 + ya' + yb)ya' <= {xa,xb}
// <-> (x1 + 2ya' + yb)yb <= {xa, xb} - (x1 + ya')ya'
// If we write x1' = x1 + 2ya' we see that this is the same form as the original problem.  Also we see that the rhs *should*
// be smaller -- roughly half the size in fact -- by the choice of ya'
// So we have reduced the problem to two roughly half-sized problems
// ya:
// Assume x2 has m+2n DIGITs
// Set x2' = x2>>(2n DIGITS)
// Set x1' = 1+(x1>>(n DIGITS))
// Set ya' = largest value s.t. (x1' + ya')ya' <= x2'
// ya = ya'<<(n DIGITs)
// Solving for ya is clearly a smaller problem than solving for y, and the residual problem for finding yb should also be much reduced -- at least for the size of x2
// Note x1 should have an extra DIGIT of space for overflow!  Assumed without checking
void CUnsignedArithmeticHelper::GeneralSquareRootRecursive(size_t  nX1Size,
                                                           size_t  nX2Size,
                                                           size_t  &nRootSize,
                                                           DIGIT   *pnX1,
                                                           DIGIT   *pnX2,
                                                           DIGIT   *pnRoot,
#if(_CollectDetailedTimingData)
                                                           DWORD64 &dwTimestamp,
#endif
                                                           DIGIT   *pnWorkspace)
{
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp2;
#endif
    // if X2 <= X1, do directly
    int nCompare = CBigInteger::CompareUnsigned(nX2Size, nX1Size, pnX2, pnX1);
    if (1 != nCompare)
    {
        // X2 <= X1.  0==y -- obvious
        nRootSize = 0;
    }
    else if (0 == nX1Size)
    {
        // square root function is simpler
        SquareRootRecursive(nX2Size,
                            nRootSize,
                            pnX2,
                            pnRoot,
#if(_CollectDetailedTimingData)
                            dwTimestamp,
#endif
                            pnWorkspace);
    }
    else if(nX2Size<c_nSquareRootThreshold)
    {
        GeneralSquareRootNewton(nX1Size,
                                nX2Size,
                                nRootSize,
                                pnX1,
                                pnX2,
                                pnRoot,
#if(_CollectDetailedTimingData)
                                dwTimestamp,
#endif
                                pnWorkspace);
    }
    else
    {
        DIGIT       *pnYa, *pnYb, *pnX1a, *pnX2a;
        size_t      nOffset, nHalfOffset, nYaSize, nYbSize, nX1aSize, nX2aSize, nBitSizeX1, nBitSizeX2, nBitDiff, i;
        DOUBLEDIGIT nCarry1, nCarry2, nCarry3, nVal1, nVal2;

        nBitSizeX1  = BitSize(nX1Size, pnX1);
        nBitSizeX2  = BitSize(nX2Size, pnX2);

        if(nBitSizeX1<<1 <= nBitSizeX2+1)
        {
            // execute recursively, shrinking X2
            // In this case, X1 is small relative to X2 -- at most half its size.  So the dominant term
            // in the sum for (x1 + y)*y is y: x1 < y
            // Let x1' = x1>>BitShift + 1
            //     x2' = x2>>(2*BitShift)
            // Solve for y' the largest value s.t. (x1' + y')*y' <= x2'
            // Clearly then ((x1' + y')*y')<<(2*BitShift) <= x2'<<(2*BitShift)
            //  <->         (x1'<<BitShift + y'<<BitShift)*(y'<<BitShift) <= x2'<<BitShift
            //  <->         (x1'<<BitShift + x1%(1<<BitShift) - x1%(1<<BitShift) + y'<<BitShift)*(y'<<BitShift) <= x2'<<BitShift + x2%(1<<BitShift) - x2%(1<<BitShift)
            //  <->         (x1'<<BitShift + x1%(1<<BitShift) - 1<<BitShift + 1<<BitShift - x1%(1<<BitShift) + y'<<BitShift)*(y'<<BitShift) <= x2'<<BitShift + x2%(1<<BitShift) - x2%(1<<BitShift)
            // Now for any x, x = (x>>BitShift)<<BitShift + x%(1<<BitShift)
            // so x1 = (x1>>BitShift)<<BitShift + x1%(1<<BitShift)
            //       = (x1>>BitShift)<<BitShift + x1%(1<<BitShift) + 1<<BitShift - 1<<BitShift
            //       = x1'<<BitShift + x1%(1<<BitShift) - 1<<BitShift
            // so (*) gives (x1 + 1<<BitShift - x1%(1<<BitShift) + y'<<BitShift)*(y'<<BitShift) <= x2 - x2%(1<<BitShift)
            // since 0 < 1<<BitShift - x1%(1<<BitShift) this gives us
            //        (x1 + y'<<BitShift)*(y'<<BitShift) <= x2
            // In this branch, x1 is at most half the size of x2, so y will be half the size of x2
            // Now, this path isn't actually hit in computing square roots -- x1 is always at least half the size of x2 in actual square root computations --
            // so while aesthetics dictates this should be efficient, we don't really need to squeeze every last drop of performance out.  Taking BitShift as
            // a multiple of DIGITs instead of bits simplifies the code.
            // To improve efficiency: DIGITs of x2 beyond twice the size of y' don't give us much of anything; don't bother with them for the first guess.
            // Base shift is then (x2 size in DIGITs +3)/4 -- + 3 to round up.  This gives us a problem half the original size
            nHalfOffset = ((nX2Size+3)>>2);
            nOffset     = nHalfOffset<<1;      // offset needs to be even, and at least half x size
            pnYa        = pnRoot + nHalfOffset; // compute Ya directly in place
            nX2aSize    = nX2Size - nOffset;
            // construct x1' if need be
            if (nHalfOffset<nX1Size)
            {
                pnX1a       = pnWorkspace;
                pnWorkspace = pnX1a + nX2aSize + 1; // needs space to expand to x2, with 1 extra DIGIT for overflow
                nCarry1     = 1;
                i           = nHalfOffset;
                for(i=0; i<nX1Size-nHalfOffset; i++)
                {
                    nCarry1  = nCarry1 + pnX1[nHalfOffset + i];
                    pnX1a[i] = nCarry1;
                    nCarry1  = (nCarry1>>_DIGIT_SIZE_IN_BITS);
                }
                pnX1a[i] = nCarry1;
                nX1aSize = i + nCarry1;
            }
            else
            {
                pnX1a = NULL; // just to make the compiler happy -- unitialized variable otherwise
            }
            pnX2a       =  pnWorkspace;
            pnWorkspace += nX2aSize + 1;
            // make a copy of the portion of X2 we need -- recall this is destructive!
            for(i=0; i<nX2aSize; i++)
            {
                pnX2a[i] = pnX2[nOffset+i];
            }
            pnX2a[i] = 0; // buffer guard in case nYbSize < nYaSize+nHalfOffset (see below)
            if(pnX1a)
            {
#if(_CollectDetailedTimingData)
                dwTimestamp2                                   =  dwTimestamp;
                dwTimestamp                                    =  s_Timer.GetMicroseconds();
                g_nSquareRootTime[eSquareRootPartAProcessTime] += (dwTimestamp - dwTimestamp2);
                GeneralSquareRootRecursive(nX1aSize, nX2aSize, nYaSize, pnX1a, pnX2a, pnYa, dwTimestamp, pnWorkspace);
#else
                GeneralSquareRootRecursive(nX1aSize, nX2aSize, nYaSize, pnX1a, pnX2a, pnYa, pnWorkspace);
#endif
                // don't need what remains of X1a, x2a -- reuse the space
                pnWorkspace -= ((nX2aSize + 1)<<1);
            }
            else
            {
                *pnWorkspace = 1;
#if(_CollectDetailedTimingData)
                dwTimestamp2                                   =  dwTimestamp;
                dwTimestamp                                    =  s_Timer.GetMicroseconds();
                g_nSquareRootTime[eSquareRootPartAProcessTime] += (dwTimestamp - dwTimestamp2);
                GeneralSquareRootRecursive(1, nX2aSize, nYaSize, pnWorkspace, pnX2a, pnYa, dwTimestamp, pnWorkspace + nX2aSize + 1);
#else
                GeneralSquareRootRecursive(1, nX2aSize, nYaSize, pnWorkspace, pnX2a, pnYa, pnWorkspace + nX2aSize + 1);
#endif
                // don't need what remains of X2a -- reuse the space
                pnWorkspace -= (nX2aSize + 1);
            }
            if(0==nYaSize)
            {
                // the recursion got us nowhere.  Need to use Newton for the whole thing.  Never seen this happen, but possible in theory
                pnWorkspace = pnYa; // don't need it anymore; reuse space
                GeneralSquareRootNewton(nX1Size,
                                        nX2Size,
                                        nRootSize,
                                        pnX1,
                                        pnX2,
                                        pnRoot,
#if(_CollectDetailedTimingData)
                                        dwTimestamp,
#endif
                                        pnWorkspace);
            }
            else
            {
                pnYa[nYaSize] = 0; // buffer guard -- make sure this value IS 0 in case
                // convert X1 to X1a, X2 to X2a
                DIGIT *pnX1PlusY = pnWorkspace;
                pnWorkspace = pnX1PlusY + nX2Size + 1;
                // convert Ya' to Ya -- purely to align with pnX1, pnX2.  Note trailing 0s are virtual
                pnYa    -= nHalfOffset;
                nYaSize += nHalfOffset;
                nCarry1 =  0;
                nCarry2 =  0;
                // x1a = (x1 + 2ya); also compute x1+ya and store in pnX1PlusY
                // Low-order nHalfOffset digits: Ya is 0 here
                for(i=0; i<min(nHalfOffset,nX1Size); i++)
                {
                    pnX1PlusY[i] = pnX1[i];
                }
                for(; i<nHalfOffset; i++)
                {
                    pnX1PlusY[i] = 0;
                    pnX1[i]      = 0;
                }
                if(nYaSize <= nX1Size)
                {
                    for(; i<nYaSize; i++)
                    {
                        nVal1        = pnYa[i];
                        nVal2        = (DOUBLEDIGIT) pnX1[i] + nVal1;
                        nCarry1      = nCarry1 + nVal1 + nVal2;
                        nCarry2      = nCarry2 + nVal2;
                        pnX1[i]      = nCarry1;
                        pnX1PlusY[i] = nCarry2;
                        nCarry1      = (nCarry1>>_DIGIT_SIZE_IN_BITS);
                        nCarry2      = (nCarry2>>_DIGIT_SIZE_IN_BITS);
                    }
                    for(; i<nX1Size; i++)
                    {
                        nVal2        = pnX1[i];
                        nCarry1      = nCarry1 + nVal2;
                        nCarry2      = nCarry2 + nVal2;
                        pnX1[i]      = nCarry1;
                        pnX1PlusY[i] = nCarry2;
                        nCarry1      = (nCarry1>>_DIGIT_SIZE_IN_BITS);
                        nCarry2      = (nCarry2>>_DIGIT_SIZE_IN_BITS);
                    }
                    pnX1[i]      = nCarry1;
                    pnX1PlusY[i] = nCarry2;
                }
                else
                {
                    for(; i<nX1Size; i++)
                    {
                        nVal1        = pnYa[i];
                        nVal2        = pnX1[i] + nVal1;
                        nCarry1      = nCarry1 + nVal1 + nVal2;
                        nCarry2      = nCarry2 + nVal2;
                        pnX1[i]      = nCarry1;
                        pnX1PlusY[i] = nCarry2;
                        nCarry1      = (nCarry1>>_DIGIT_SIZE_IN_BITS);
                        nCarry2      = (nCarry2>>_DIGIT_SIZE_IN_BITS);
                    }
                    for(; i<nYaSize; i++)
                    {
                        nVal1        = pnYa[i];
                        nCarry1      = nCarry1 + (nVal1<<1);
                        nCarry2      = nCarry2 + nVal1;
                        pnX1[i]      = nCarry1;
                        pnX1PlusY[i] = nCarry2;
                        nCarry1      = (nCarry1>>_DIGIT_SIZE_IN_BITS);
                        nCarry2      = (nCarry2>>_DIGIT_SIZE_IN_BITS);
                    }
                    pnX1[i]      = nCarry1;
                    pnX1PlusY[i] = nCarry2;
                }
                nX1aSize = i + (0<nCarry1);
                nX2aSize = i + (0<nCarry2);
                // x2a = x2 - (x1 + ya)ya.  Note (x1 + ya) is stored in x2a at this point
                // (x1 + ya)ya
                // skip over virtual 0s
                pnYa    += nHalfOffset;
                nYaSize -= nHalfOffset;
#if _CollectDetailedTimingData
                dwTimestamp2                                    =  dwTimestamp;
                dwTimestamp                                     =  s_Timer.GetMicroseconds();
                g_nSquareRootTime[eSquareRootPartAProcessTime]  += (dwTimestamp - dwTimestamp2);
                dwTimestamp2                                    =  dwTimestamp;
                MultUBackend(nX2aSize, nYaSize, pnX1PlusY, pnYa, pnWorkspace, pnWorkspace+nX2aSize+nYaSize, dwTimestamp);
                g_nSquareRootTime[eSquareRootPartAMultiplyTime] += (dwTimestamp - dwTimestamp2);
#else
                MultUBackend(nX2aSize, nYaSize, pnX1PlusY, pnYa, pnWorkspace, pnWorkspace+nX2aSize+nYaSize);
#endif
                nX2aSize = nX2aSize + nYaSize;
                if(0==pnWorkspace[nX2aSize-1]) nX2aSize--;
                // x2 - (x1 + ya)ya
                nX2aSize = Subtract(nX2Size-nHalfOffset, nX2aSize, pnX2+nHalfOffset, pnWorkspace, pnX2+nHalfOffset) + nHalfOffset;
                // note we don't need pnX1PlusY anymore
                pnWorkspace = pnX1PlusY;
                // compute Yb
                pnYb        =  pnWorkspace;
                pnWorkspace += nX2Size;
#if _CollectDetailedTimingData
                dwTimestamp2                                    =  dwTimestamp;
                dwTimestamp                                     =  s_Timer.GetMicroseconds();
                g_nSquareRootTime[eSquareRootPartAProcessTime]  += (dwTimestamp - dwTimestamp2);
                GeneralSquareRootRecursive(nX1aSize, nX2aSize, nYbSize, pnX1, pnX2, pnYb, dwTimestamp, pnWorkspace);
#else
                GeneralSquareRootRecursive(nX1aSize, nX2aSize, nYbSize, pnX1, pnX2, pnYb, pnWorkspace);
#endif
                // splice the two parts together into the root.  Note the root is (Ya << <half offset>) + Yb,
                // and Ya is already in place.
                // Copy Yb into place.
                if(0==nYaSize)
                {
                    // JUST the Yb component
                    nRootSize = nYbSize;
                    for(i=0; i<nYbSize; i++)
                    {
                        pnRoot[i] = pnYb[i];
                    }
                }
                else
                {
                    for(i=0; i<min(nYbSize, nHalfOffset); i++)
                    {
                        pnRoot[i] = pnYb[i];
                    }
                    for(; i<nHalfOffset; i++)
                    {
                        pnRoot[i] = 0;
                    }
                    // overlap of Ya and Yb
                    nCarry1 = 0;
                    if(nYaSize+nHalfOffset<=nYbSize)
                    {
                        for(; i<nYaSize+nHalfOffset; i++)
                        {
                            nCarry1   = (nCarry1 + pnRoot[i]) + pnYb[i];
                            pnRoot[i] = nCarry1;
                            nCarry1   = (nCarry1>>_DIGIT_SIZE_IN_BITS);
                        }
                        for(; i<nYbSize; i++)
                        {
                            nCarry1   = nCarry1 + pnYb[i];
                            pnRoot[i] = nCarry1;
                            nCarry1   = (nCarry1>>_DIGIT_SIZE_IN_BITS);
                        }
                        pnRoot[i] = nCarry1;
                        nRootSize = i + nCarry1;
                    }
                    else
                    {
                        for(; i<nYbSize; i++)
                        {
                            nCarry1   = (nCarry1 + pnRoot[i]) + pnYb[i];
                            pnRoot[i] = nCarry1;
                            nCarry1   = (nCarry1>>_DIGIT_SIZE_IN_BITS);
                        }
                        while(nCarry1)
                        {
                            nCarry1     = nCarry1 + pnRoot[i];
                            pnRoot[i++] = nCarry1;
                            nCarry1     = (nCarry1>>_DIGIT_SIZE_IN_BITS);
                        }
                        nRootSize = nYaSize + nHalfOffset;
                        if(0 != pnRoot[nRootSize]) nRootSize++;
                    }
                }
            }
#if _CollectDetailedTimingData
            dwTimestamp2                                    =  dwTimestamp;
            dwTimestamp                                     =  s_Timer.GetMicroseconds();
            g_nSquareRootTime[eSquareRootPartAProcessTime]  += (dwTimestamp - dwTimestamp2);
#endif
        }
        else
        {
            DIGIT  *pnTop, *pnBottom;
            size_t nDigitShift, nBitShift, nTopSize, nBottomSize;
            // Recall: looking to find the largest y s.t. y(y+x1) <= x2
            // Now, x2 in this case is less than twice the size of x1.
            // Clearly sqrt(x2) < x1, so y<x1
            // Further it is clear that y < 1<<(difference in size of x2 and x1)
            // Let x1' = 2 + [x1 right-shifted (x2 size in BITs - x1 size in bits)]
            // Then (x2/x1) left-shifted (x2 size in BITs - x1 size in bits) is smaller than y, though not appallingly so.
            // We use this as our Ya
            // Update x1 as x1+2Ya, update x2 as x2 - (x1+Ya)*Ya, repeat

            // When multiplying an n-bit number by an m-bit number, the result is either an (m+n)-bit number or an (m+n-1)-bit number
            // So Ya can be at most (x2 length in BITs - X1 length in BITs) + 1 BITs in size  (Note X1 is greater than half the length
            // of X2 in this branch, so Ya < X1).  So takinging BitDiff as 2 + (X2 size - X1 size) inthe work below guarantees Ya < (1<<BitDiff)
            // and the rest follows
            // Note that for all X, X = (X>>n)<<n + X mod (1<<n) -- the first few BITs followed byt he last n BITs
            // To get ya, we divide (x2>>BitDiff) by (2 + x1>>BitDiff).
            // This gives Ya = (x2>>BitDiff)/(2 + x1>>BitDiff)
            // and (x2>>BitDiff) mod (2 + x1>>BitDiff) = (x2>>BitDiff) - Ya*(2 + x1>>BitDiff)
            // we wish to replace x2 with x2 - Ya(Ya+x1) and x1 with x1 + 2Ya
            //
            // (x2>>BitDiff) mod (2 + x1>>BitDiff) = (x2>>BitDiff) - Ya*(2 + x1>>BitDiff)
            //  = (x2>>BitDiff) - ya*(x1>>BitDiff) - 2*Ya = YY
            // and
            // x2 - Ya*(Ya + x1)
            //       = (x2>>BitDiff)<<BitDiff + x2 mod(1<<BitDiff) - Ya*(Ya + (x1>>BitDiff)<<BitDiff + x1 mod(1<<BitDiff))
            //       = (x2>>BitDiff)<<BitDiff - Ya*(x1>>BitDiff)<<BitDiff - 2Ya<<BitDiff + 2Ya<<BitDiff + x2 mod(1<<BitDiff) - Ya*(Ya + x1 mod(1<<BitDiff))
            //       = (x2>>BitDiff - Ya*(x1>>BitDiff) - 2Ya)<<BitDiff + 2Ya<<BitDiff + x2 mod(1<<BitDiff) - Ya*(Ya + x1 mod(1<<BitDiff))
            //       = YY<<BitDiff + (2Ya)<<BitDiff + x2 mod(1<<BitDiff) - Ya*(Ya + x1 mod(1<<BitDiff))
            //       = (YY + 2Ya)<<BitDiff + x2 mod(1<<BitDiff) - Ya*(Ya + x1 mod(1<<BitDiff))
            // The only multiplication we need, then, is Ya*(Ya + x1 mod(1<<BitDiff)) which should be considerably smaller
            // than the original Ya*(Ya+x1)
            // The mods and shifts are trivial -- especially if BitDiff is an even multiple of the DIGIT size

            // space for operands
            pnTop       = pnWorkspace;
            pnBottom    = pnTop    + nX2Size + 1;
            pnYb        = pnBottom + nX2Size + 1;
            pnWorkspace = pnYb     + nX1Size;
            pnYa        = pnRoot; // first pass: put directly in root.  Later passes go in Yb, then add to root
            nRootSize   = 0;
            *pnRoot     = 0;
            do
            {
                nBitDiff = nBitSizeX2 - nBitSizeX1;
                if(nBitDiff<2)
                {
                    // do directly: Ya is at most 3
                    if(1==nBitDiff)
                    {
                        // see if we can fit in a 2.  If so, update X1 and X2
                        // 2 fits if (x1+2)*2 <= X2
                        // speculatively twiddle X1
                        i       = 0;
                        nCarry1 = 2;
                        do
                        {
                            nCarry1   += pnX1[i];
                            pnX1[i++] =  nCarry1;
                            nCarry1   =  nCarry1>>_DIGIT_SIZE_IN_BITS;
                        }
                        while(nCarry1);
                        if(nX1Size<i) nX1Size = i;
                        nBottomSize = CBigIntegerHelper::ShiftXLeft(nX1Size, 1, 0, pnX1, pnBottom);
                        if(1 != CBigInteger::CompareUnsigned(nBottomSize, nX2Size, pnBottom, pnX2))
                        {
                            // yup; it fits.
                            // Update X1 to X1 + 2Ya and X2 to X2 - (x1 + Ya)Ya
                            // Here, Ya is 2, and pnBottom already contains (x1 + 2)*2 == (x1 + Ya)Ya
                            // Further X1 actually contains X1 + 2.
                            // Just need to add 2 more to X1, and subtract pnBottom from X2
                            // X1
                            i       = 0;
                            nCarry1 = 2;
                            do
                            {
                                nCarry1   += pnX1[i];
                                pnX1[i++] =  nCarry1;
                                nCarry1   =  nCarry1>>_DIGIT_SIZE_IN_BITS;
                            }
                            while(nCarry1);
                            if(nX1Size<i) nX1Size = i;
                            // X2
                            nX2Size = Subtract(nX1Size, nBottomSize, pnX2, pnBottom, pnX2);
                            // root
                            i       = 0;
                            nCarry1 = 2;
                            do
                            {
                                nCarry1     += pnRoot[i];
                                pnRoot[i++] =  nCarry1;
                                nCarry1     =  nCarry1>>_DIGIT_SIZE_IN_BITS;
                            }
                            while(nCarry1);
                            if(nRootSize<i) nRootSize = i;
                        }
                        else
                        {
                            // didn't work out.  Revert X1 twiddle
                            i       = 0;
                            nCarry1 = 2;
                            do
                            {
                                nVal1     = pnX1[i];
                                pnX1[i++] = nVal1 - nCarry1;
                                nCarry1   = (nVal1<nCarry1);
                            }
                            while(nCarry1);
                            if(0==pnX1[nX1Size-1]) nX1Size--;
                        }
                    }
                    // Can add one more to the root if X1 < X2
                    if(-1 == CBigInteger::CompareUnsigned(nX1Size, nX2Size, pnX1, pnX2))
                    {
                        i       = 0;
                        nCarry1 = 1;
                        do
                        {
                            nCarry1     += pnRoot[i];
                            pnRoot[i++] =  nCarry1;
                            nCarry1     =  nCarry1>>_DIGIT_SIZE_IN_BITS;
                        }
                        while(nCarry1);
                        if(nRootSize<i) nRootSize = i;
                    }
#if _CollectDetailedTimingData
                    dwTimestamp2                                    =  dwTimestamp;
                    dwTimestamp                                     =  s_Timer.GetMicroseconds();
                    g_nSquareRootTime[eSquareRootPartBProcessTime]  += (dwTimestamp - dwTimestamp2);
#endif
                    break; // done
                }
                else
                {
                    nDigitShift   = (nBitDiff+2)/_DIGIT_SIZE_IN_BITS;
                    nBitShift     = (nBitDiff+2)%_DIGIT_SIZE_IN_BITS;
                    pnX1[nX1Size] = 0; // overflow guard
                    if(0==nBitShift)
                    {
                        // do in place.
                        // add 2 to x1 at the appropriate shift
                        nCarry1 = 2;
                        i       = nDigitShift;
                        do
                        {
                            nCarry1   += pnX1[i];
                            pnX1[i++] =  nCarry1;
                            nCarry1   =  (nCarry1>>_DIGIT_SIZE_IN_BITS);
                        }
                        while(nCarry1);
                        nX1aSize = nX1Size;
                        if(nX1aSize<i) nX1aSize = i;
#if _CollectDetailedTimingData
                        dwTimestamp2                                    =  dwTimestamp;
                        dwTimestamp                                     =  s_Timer.GetMicroseconds();
                        g_nSquareRootTime[eSquareRootPartBProcessTime]  += (dwTimestamp - dwTimestamp2);
                        dwTimestamp2                                    =  dwTimestamp;
                        DivideBackend(nX2Size-nDigitShift, nX1aSize-nDigitShift, nYaSize, nX2aSize, pnX2+nDigitShift, pnX1+nDigitShift, pnYa, dwTimestamp, pnWorkspace);
                        g_nSquareRootTime[eSquareRootPartBDivideTime]   += (dwTimestamp - dwTimestamp2);
#else
                        DivideBackend(nX2Size-nDigitShift, nX1aSize-nDigitShift, nYaSize, nX2aSize, pnX2+nDigitShift, pnX1+nDigitShift, pnYa, pnWorkspace);
#endif
                        nX2Size = nX2aSize + nDigitShift;
                        // undo the twiddle of x1
                        nCarry1 = 2;
                        i       = nDigitShift;
                        do
                        {
                            nVal1     = pnX1[i];
                            pnX1[i++] = nVal1-nCarry1;
                            nCarry1   = (nVal1<nCarry1);
                        }
                        while(nCarry1);
                        // Ya + x1 mod <>; x1 <- x1 + 2Ya; (YY + 2Ya)<<BitDiff
                        // Note that Ya < x1 mod <>
                        // already guaranteed nCarry1 is 0 from previous loop
                        nCarry2 = 0;
                        for(i=0; i<nYaSize; i++)
                        {
                            nVal1    =  pnYa[i];
                            nVal2    =  nVal1 + pnX1[i];
                            nCarry1  += nVal1 + nVal2; // x1 + 2Ya
                            nCarry2  += nVal2;         // x1 mod <nDigitShift> + Ya
                            pnX1[i]  =  nCarry1;
                            pnTop[i] =  nCarry2;
                            nCarry1  =  nCarry1>>_DIGIT_SIZE_IN_BITS;
                            nCarry2  =  nCarry2>>_DIGIT_SIZE_IN_BITS;
                        }
                        pnTop[i] = nCarry2;
                        nTopSize = nDigitShift + nCarry2; // note Carry2 is 0 or 1 ONLY
                        while (0 == pnTop[nTopSize - 1]) nTopSize--; // chunk of X1 of interest might have leading 0s
                        if (nCarry1)
                        {
                            // recall we made sure x1 had a leading 0 so we are safe from overflow!
                            do
                            {
                                nCarry1   += pnX1[i];   // x1 + 2Ya
                                pnX1[i++] =  nCarry1;
                                nCarry1   =  nCarry1>>_DIGIT_SIZE_IN_BITS;
                            }
                            while(nCarry1);
                            if(nX1Size<i) nX1Size = i;
                        }
                        // (YY + 2Ya)<<BitDiff
                        nCarry3 = 0;
                        if(nX2Size-nDigitShift<=nYaSize)
                        {
                            for(i=0; i<nX2Size-nDigitShift; i++)
                            {
                                nVal1               =  pnYa[i];
                                nCarry3             += pnX2[nDigitShift+i] + (nVal1<<1); // (YY + 2Ya)<<BitDiff
                                pnX2[nDigitShift+i] =  nCarry3;
                                nCarry3             =  nCarry3>>_DIGIT_SIZE_IN_BITS;
                            }
                            for(; i<nYaSize; i++)
                            {
                                nVal1               =  pnYa[i];
                                nCarry3             += (nVal1<<1); // (YY + 2Ya)<<BitDiff
                                pnX2[nDigitShift+i] =  nCarry3;
                                nCarry3             =  nCarry3>>_DIGIT_SIZE_IN_BITS;
                            }
                            if(nCarry3) pnX2[nDigitShift+i] = nCarry3;
                            nX2Size = nYaSize + nDigitShift + (0<nCarry3);
                        }
                        else
                        {
                            for(i=0; i<nYaSize; i++)
                            {
                                nVal1               =  pnYa[i];
                                nCarry3             += pnX2[nDigitShift+i] + (nVal1<<1); // (YY + 2Ya)<<BitDiff
                                pnX2[nDigitShift+i] =  nCarry3;
                                nCarry3             =  nCarry3>>_DIGIT_SIZE_IN_BITS;
                            }
                            if(nCarry3)
                            {
                                i = nYaSize + nDigitShift;
                                do
                                {
                                    nCarry3   += pnX2[i];
                                    pnX2[i++] =  nCarry3;
                                    nCarry3   =  nCarry3>>_DIGIT_SIZE_IN_BITS;
                                }
                                while(nCarry3);
                                if(nX2Size<i) nX2Size++;
                            }
                        }
                        // Ya*(Ya + x1 mod(1<<BitDiff))
#if _CollectDetailedTimingData
                        dwTimestamp2                                    =  dwTimestamp;
                        dwTimestamp                                     =  s_Timer.GetMicroseconds();
                        g_nSquareRootTime[eSquareRootPartBProcessTime]  += (dwTimestamp - dwTimestamp2);
                        dwTimestamp2                                    =  dwTimestamp;
                        MultUBackend(nYaSize, nTopSize, pnYa, pnTop, pnBottom, pnWorkspace, dwTimestamp);
                        g_nSquareRootTime[eSquareRootPartBMultiplyTime] += (dwTimestamp - dwTimestamp2);
#else
                        MultUBackend(nYaSize, nTopSize, pnYa, pnTop, pnBottom, pnWorkspace);
#endif
                        nBottomSize = nYaSize + nTopSize;
                        if(0==pnBottom[nBottomSize-1]) nBottomSize--;
                        // YY<<BitDiff + (2Ya)<<BitDiff + x2 mod(1<<BitDiff) - Ya*(Ya + x1 mod(1<<BitDiff))
                        nX2Size = Subtract(nX2Size, nBottomSize, pnX2, pnBottom, pnX2);
                    }
                    else
                    {
                        DIGIT nPartialDigitX1, nPartialDigitX2, nMask;
                        // save the "overlap" bits -- bits of the lower half in the upper half's final DIGIT
                        nMask                 = ~((-1)<<nBitShift);
                        nPartialDigitX1       = pnX1[nDigitShift]&nMask;
                        nPartialDigitX2       = pnX2[nDigitShift]&nMask;
                        // add 2 to x1 at the appropriate shift
                        nBottomSize           = CBigIntegerHelper::ShiftXRight(nX1Size, nBitShift, nDigitShift, pnX1, pnBottom);
                        pnBottom[nBottomSize] = 0; // overflow guard
                        nCarry1               = 2;
                        i                     = 0;
                        do
                        {
                            nCarry1       += pnBottom[i];
                            pnBottom[i++] =  nCarry1;
                            nCarry1       =  (nCarry1>>_DIGIT_SIZE_IN_BITS);
                        }
                        while(nCarry1);
                        if(nBottomSize<i) nBottomSize = i;
                        // get shift of upper bits of x2
                        pnX2a    = pnX2+nDigitShift;
                        nTopSize = CBigIntegerHelper::ShiftRightInPlace(nX2Size-nDigitShift, nBitShift, 0, pnX2a);
#if _CollectDetailedTimingData
                        dwTimestamp2                                    =  dwTimestamp;
                        dwTimestamp                                     =  s_Timer.GetMicroseconds();
                        g_nSquareRootTime[eSquareRootPartBProcessTime]  += (dwTimestamp - dwTimestamp2);
                        dwTimestamp2                                    =  dwTimestamp;
                        DivideBackend(nTopSize, nBottomSize, nYaSize, nX2aSize, pnX2a, pnBottom, pnYa, dwTimestamp, pnWorkspace);
                        g_nSquareRootTime[eSquareRootPartBDivideTime]   += (dwTimestamp - dwTimestamp2);
#else
                        DivideBackend(nTopSize, nBottomSize, nYaSize, nX2aSize, pnX2a, pnBottom, pnYa, pnWorkspace);
#endif
                        // Now, the upper bits of X2 contains YY (and we don't care about the value in pnBottom anymore)
                        // X1[nDigitShift] is the DIGIT of X1 that is "partial" in X1 mod(1<<BitDiff)
                        // Likewise in X2 mod(1<<BitDiff)
                        nCarry1         = 0;
                        // Compute Ya + X1 mod<>; put it in pnBottom.  The partial DIGIT for x1 is at nDigitShift
                        if(nDigitShift<nYaSize)
                        {
                            for(i=0; i<nDigitShift; i++)
                            {
                                nCarry1     += ((DOUBLEDIGIT) pnYa[i]) + pnX1[i];
                                pnBottom[i] =  nCarry1;
                                nCarry1     =  (nCarry1>>_DIGIT_SIZE_IN_BITS);
                            }
                            nCarry1       = (nCarry1 + nPartialDigitX1) + pnYa[i];
                            pnBottom[i++] = nCarry1;
                            nCarry1       = (nCarry1>>_DIGIT_SIZE_IN_BITS);
                            for(; i<nYaSize; i++)
                            {
                                nCarry1     += pnYa[i];
                                pnBottom[i] =  nCarry1;
                                nCarry1     =  (nCarry1>>_DIGIT_SIZE_IN_BITS);
                            }
                            pnBottom[i] = nCarry1;
                            nBottomSize = i + nCarry1; // note nCarry1 is at most 1
                        }
                        else
                        {
                            for(i=0; i<nYaSize; i++)
                            {
                                nCarry1     += ((DOUBLEDIGIT) pnYa[i]) + pnX1[i];
                                pnBottom[i] =  nCarry1;
                                nCarry1     =  (nCarry1>>_DIGIT_SIZE_IN_BITS);
                            }
                            for(; i<nDigitShift-1; i++)
                            {
                                nCarry1     += pnX1[i];
                                pnBottom[i] =  nCarry1;
                                nCarry1     =  (nCarry1>>_DIGIT_SIZE_IN_BITS);
                            }
                            nCarry1     += nPartialDigitX1;
                            pnBottom[i] =  nCarry1;
                            nBottomSize =  nDigitShift + (0<nCarry1);
                            while(0==pnBottom[nBottomSize-1]) nBottomSize--; // x1 mod<shift> might have leading 0s
                        }
                        // YY <- YY + 2Ya
                        // X1 <- X1 + 2Ya (note we've already computed X1 + Ya and stored elsewhere; don't need old X1 anymore).
                        nCarry1 = 0;
                        nCarry2 = 0;
                        if(nX2aSize<nYaSize) // nX2aSize is size of YY, present in pnTop
                        {
                            for(i=0; i<nX2aSize; i++)
                            {
                                nVal1    =  ((DOUBLEDIGIT) pnYa[i])<<1;
                                nCarry1  += pnX2a[i] + nVal1;
                                nCarry2  += nVal1 + pnX1[i];
                                pnX2a[i] =  nCarry1;
                                pnX1[i]  =  nCarry2;
                                nCarry1  =  nCarry1>>_DIGIT_SIZE_IN_BITS;
                                nCarry2  =  nCarry2>>_DIGIT_SIZE_IN_BITS;
                            }
                            for(; i<nYaSize; i++)
                            {
                                nVal1    =  ((DOUBLEDIGIT) pnYa[i])<<1;
                                nCarry1  += nVal1;
                                nCarry2  += nVal1 + pnX1[i];
                                pnX2a[i] =  nCarry1;
                                pnX1[i]  =  nCarry2;
                                nCarry1  =  nCarry1>>_DIGIT_SIZE_IN_BITS;
                                nCarry2  =  nCarry2>>_DIGIT_SIZE_IN_BITS;
                            }
                        }
                        else
                        {
                            for(i=0; i<nYaSize; i++)
                            {
                                nVal1    =  ((DOUBLEDIGIT) pnYa[i])<<1;
                                nCarry1  += pnX2a[i] + nVal1;
                                nCarry2  += nVal1 + pnX1[i];
                                pnX2a[i] =  nCarry1;
                                pnX1[i]  =  nCarry2;
                                nCarry1  =  nCarry1>>_DIGIT_SIZE_IN_BITS;
                                nCarry2  =  nCarry2>>_DIGIT_SIZE_IN_BITS;
                            }
                            for(; i<nX2aSize; i++)
                            {
                                nCarry1  += pnX2a[i];
                                pnX2a[i] =  nCarry1;
                                nCarry1  =  nCarry1>>_DIGIT_SIZE_IN_BITS;
                            }
                        }
                        pnX2a[i] = nCarry1;
                        nX2aSize = i + (0<nCarry1);
                        if(nCarry2)
                        {
                            i = nYaSize;
                            do
                            {
                                nCarry2   += pnX1[i];
                                pnX1[i++] =  nCarry2;
                                nCarry2   =  (nCarry2>>_DIGIT_SIZE_IN_BITS);
                            }
                            while(nCarry2);
                            if (nX1Size<i) nX1Size = i;
                        }
                        // Compute (YY + 2Ya)<<BitDiff and put it in place
                        nX2Size           =  CBigIntegerHelper::ShiftLeftInPlace(nX2aSize,nBitShift,0, pnX2a) + nDigitShift;
                        pnX2[nDigitShift] += nPartialDigitX2; // restore overwritten partial digit
                        // Now: x1 updated; YY<<BitDiff + (2Ya)<<BitDiff + x2 mod(1<<BitDiff) is in X2
                        // Just need YY<<BitDiff + (2Ya)<<BitDiff + x2 mod(1<<BitDiff) - Ya*(Ya + x1 mod(1<<BitDiff)) in X2,
                        // and we're done
                        // Ya + x1 mod(1<<BitDiff) is in pnBottom
                        // Ya*(Ya + x1 mod(1<<BitDiff))
#if _CollectDetailedTimingData
                        dwTimestamp2                                    =  dwTimestamp;
                        dwTimestamp                                     =  s_Timer.GetMicroseconds();
                        g_nSquareRootTime[eSquareRootPartBProcessTime]  += (dwTimestamp - dwTimestamp2);
                        dwTimestamp2                                    =  dwTimestamp;
                        MultUBackend(nYaSize, nBottomSize, pnYa, pnBottom, pnTop, pnWorkspace, dwTimestamp);
                        g_nSquareRootTime[eSquareRootPartBMultiplyTime] += (dwTimestamp - dwTimestamp2);
#else
                        MultUBackend(nYaSize, nBottomSize, pnYa, pnBottom, pnTop, pnWorkspace);
#endif
                        nTopSize = nYaSize + nBottomSize;
                        if(0==pnTop[nTopSize-1]) nTopSize--;
                        // YY<<BitDiff + (2Ya)<<BitDiff + x2 mod(1<<BitDiff) - Ya*(Ya + x1 mod(1<<BitDiff))
                        nX2Size = Subtract(nX2Size, nTopSize, pnX2, pnTop, pnX2);
                    }
                    if (pnRoot == pnYa)
                    {
                        // first pass: Ya slotted directly into root
                        nRootSize     = nYaSize;
                        pnYa[nYaSize] = 0;    // buffer guard
                        pnYa          = pnYb; // use space reserved for subsequent computations for Ya hereafter
                    }
                    else
                    {
                        // add Ya into root.  Note each subsequent Ya guaranteed to be at most as large as the previous
                        nCarry1 = 0;
                        for(i=0; i<nYaSize; i++)
                        {
                            nCarry1   = (nCarry1 + pnYa[i]) + pnRoot[i];
                            pnRoot[i] = nCarry1;
                            nCarry1   = nCarry1>>_DIGIT_SIZE_IN_BITS;
                        }
                        while(nCarry1)
                        {
                            nCarry1     += pnRoot[i];
                            pnRoot[i++] =  nCarry1;
                            nCarry1     =  nCarry1>>_DIGIT_SIZE_IN_BITS;
                        }
                        if(nRootSize<i) nRootSize = i;
                    }
                }
                nBitSizeX1 = BitSize(nX1Size, pnX1);
                nBitSizeX2 = BitSize(nX2Size, pnX2);
            }
            while(nBitSizeX1 <= nBitSizeX2);
#if _CollectDetailedTimingData
            dwTimestamp2                                   =  dwTimestamp;
            dwTimestamp                                    =  s_Timer.GetMicroseconds();
            g_nSquareRootTime[eSquareRootPartBProcessTime] += (dwTimestamp - dwTimestamp2);
#endif
        }
    }
}

// Use Newton's method: x(i+1) = x(i) - F(x(i))/F'(x(i))
//      F(X)  = X^2 - nX
//      F'(X) = 2X
// So:
//     X(i+1) = X(i) - (X(i)^2 - nX)/(2X(i))
// <-> X(i+1) = 2X(i)^2/(2X(i)) - (X(i)^2 - nX)/(2X(i))
// <-> X(i+1) = (2X(i)^2 - X(i)^2 + nX)/(2X(i))
// <-> X(i+1) = (X(i)^2 + nX)/(2X(i))
// <-> X(i+1) = (X(i)/2 + nX/(2X(i)))
// <-> X(i+1) = (X(i) + nX/X(i))/2
// As our initial guess, pick the smallest power of 2 such that nX <= X(0)^2 -- that saves us the multiplication
// for the first step
// Note that we start with a value known to be ABOVE the actual square root.  Newton's method -- barring roundoff --
// will always overestimate.  But integer truncation is a given here.  When we get below the actual square root,
// Newton will move up again, or stay the same.  That is our signal to quit; no need to square our value to validate.
void CUnsignedArithmeticHelper::SquareRootNewton(size_t  nXSize,
                                                 size_t  &nRootSize,
                                                 DIGIT   *pnX,
                                                 DIGIT   *pnRoot,
#if(_CollectDetailedTimingData)
                                                 DWORD64 &dwTimestamp,
#endif
                                                 DIGIT   *pnWorkspace)
{
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp2 = dwTimestamp;
#endif
    if (nXSize <= 2)
    {
        // can do the problem directly with sqrt from math.h -- roughly 20x as fast as Newton, with the note that it doesn't
        // always do the rounding the way we want so we need to correct for that
        if(2==nXSize)
        {
            DOUBLEDIGIT x, s;
            x = *((DOUBLEDIGIT *) pnX);
            s = sqrt(x);
            if(x < s*s) s--;
            *pnRoot = s;
        }
        else
        {
            DIGIT x, s;
            x = *pnX;
            s = sqrt(x);
            if(x < s*s) s--;
            *pnRoot = s;
        }
        nRootSize = 1;
#if(_CollectDetailedTimingData)
        dwTimestamp2                                    =  s_Timer.GetMicroseconds();
        g_nSquareRootTime[eSquareRootNewtonProcessTime] += dwTimestamp2 - dwTimestamp;
        dwTimestamp                                     =  dwTimestamp2;
#endif
    }
    else
    {
        // use Newton
        size_t      i, nDigitShift, nBitShift, nInverseShift, nDivSize, nRemainderSize;
        DOUBLEDIGIT nCarry;
        DIGIT       *pYPrev, *pYCurr, *pNum1, *pNum2, *pNum3, *pSwap, nMask;//, nFirstDigit;
        i             = nXSize + 2; // space needed for intermediate values
        pYPrev        = pnRoot;
        pYCurr        = pnWorkspace;
        pNum1         = pYCurr + i;
        pNum2         = pNum1  + i;
        pNum3         = pNum2  + i;
        pnWorkspace   = pNum3  + i;
        nBitShift     = BitSize(nXSize, pnX);
        nBitShift     = ((nBitShift + 1)>>1); // y = 1<<nBitShift
        nDigitShift   = nBitShift/(sizeof(DIGIT)<<3);
        nBitShift     = nBitShift%(sizeof(DIGIT)<<3);
        nInverseShift = _DIGIT_SIZE_IN_BITS - nBitShift;
        nMask         = (DIGIT) (c_nClearHigh<<nInverseShift);
        // pYPrev <- (y + x/y)/2
        // note nDigitShift <= nXSize/2 < nXSize for nXSize != 1
        // Note that by choice of y, x/y <= y (y chosen to be at least the square root of x)
        // Also y has at most one digit more than x/y
        if(0==nDigitShift)
        {
            nCarry    =  (pnX[0]>>nBitShift);
            if(1<nXSize) nCarry |= ((pnX[1]<<nInverseShift)&nMask);
            nCarry    += (((DOUBLEDIGIT) 1)<<nBitShift);
            pYPrev[0] =  ((nCarry&c_nClearHigh)>>1);
            nRootSize =  1;
        }
        else
        {
            pYPrev[0] = (((pnX[nDigitShift]>>nBitShift) | ((pnX[nDigitShift+1]<<nInverseShift)&nMask))>>1);
            for (i=1; i<nDigitShift; i++)
            {
                nCarry      =  ((pnX[nDigitShift+i]>>nBitShift) | ((pnX[nDigitShift+i+1]<<nInverseShift)&nMask));
                pYPrev[i-1] |= (nCarry&1)<<(_DIGIT_SIZE_IN_BITS-1);
                pYPrev[i]   =  ((nCarry&c_nClearHigh)>>1);
            }
            if(nDigitShift + i<nXSize)
            {
                nCarry = (pnX[nDigitShift+i]>>nBitShift);
                if(nDigitShift + i<nXSize) nCarry |= ((pnX[nDigitShift+i+1]<<nInverseShift)&nMask);
            }
            else
            {
                nCarry = 0;
            }
            nCarry      += (((DOUBLEDIGIT) 1)<<nBitShift);
            pYPrev[i-1] |= (nCarry&1)<<(_DIGIT_SIZE_IN_BITS-1);
            nCarry      =  ((nCarry&c_nClearHigh)>>1);
            pYPrev[i]   =  nCarry;
            nRootSize   =  (nCarry) ? i+1 : i;
        }
        // Newton proper
        nInverseShift = _DIGIT_SIZE_IN_BITS - 1;
        do
        {
            // pYCurr = x -- make a copy: divide is destructive
            memcpy(pYCurr, pnX, nXSize*sizeof(DIGIT));
            // pNum1 <- x/y
#if(_CollectDetailedTimingData)
            dwTimestamp2                                     =  s_Timer.GetMicroseconds();
            g_nSquareRootTime[eSquareRootNewtonProcessTime]  += (dwTimestamp2 - dwTimestamp);
            dwTimestamp2                                     =  dwTimestamp;
            DivideBackend(nXSize, nRootSize, nDivSize, nRemainderSize, pYCurr, pYPrev, pNum1, dwTimestamp, pnWorkspace);
            g_nSquareRootTime[eSquareRootNewtonDivideTime]   += (dwTimestamp2 - dwTimestamp);
#else
            DivideBackend(nXSize, nRootSize, nDivSize, nRemainderSize, pYCurr, pYPrev, pNum1, pnWorkspace);
#endif
            // pYCurr <- (y + x/y)/2
            // can speed this up a trifle by doing 2 digits at a time, thus saving a load/store for each digit -- todo xxx
            nCarry    = ((DOUBLEDIGIT) pYPrev[0]) + pNum1[0];
            pYCurr[0] = ((nCarry&c_nClearHigh)>>1);
            nCarry    = nCarry>>_DIGIT_SIZE_IN_BITS;
            for(i=1; i<nDivSize; i++)
            {
                nCarry      = (nCarry + pYPrev[i]) + pNum1[i];
                pYCurr[i]   = ((nCarry&c_nClearHigh)>>1);
                pYCurr[i-1] = pYCurr[i-1] | ((nCarry&1)<<nInverseShift);
                nCarry      = nCarry>>_DIGIT_SIZE_IN_BITS;
            }
            for(; i<nRootSize; i++)
            {
                nCarry      = nCarry + pYPrev[i];
                pYCurr[i]   = ((nCarry&c_nClearHigh)>>1);;
                pYCurr[i-1] = pYCurr[i-1] | ((nCarry&1)<<nInverseShift);
                nCarry      = nCarry>>_DIGIT_SIZE_IN_BITS;
            }
            pYCurr[i-1] |= ((nCarry&1)<<nInverseShift);
            nDivSize    =  nRootSize; // size of previous guess
            nRootSize   =  (pYCurr[nRootSize-1]) ? nRootSize : nRootSize - 1;
            pSwap       =  pYCurr;
            pYCurr      =  pYPrev;
            pYPrev      =  pSwap;
        }
        while(-1 == CBigInteger::CompareUnsigned(nRootSize, nDivSize, pYPrev, pYCurr));
        if (pYCurr != pnRoot)
        {
            // ended in the wrong slot.  Copy over.
            for(i=0; i<nRootSize; i++)
            {
                pnRoot[i] = pYCurr[i];
            }
        }
#if(_CollectDetailedTimingData)
        dwTimestamp2                                     =  s_Timer.GetMicroseconds();
        g_nSquareRootTime[eSquareRootNewtonProcessTime]  += (dwTimestamp2 - dwTimestamp);
        dwTimestamp                                      =  dwTimestamp2;
#endif
    }
}

/*
  Find: largest y s.t. (x1 + y)y <= x2.  Note that with x1 positive, it is clear that y < sqrt(x2)
  f(y)  = (x1 + y)y - x2 = 0
  f'(y) = x1 + 2y
  y1    = y - f(y)/f'(y) -- Newton
        = y - ((x1y + y^2) - x2)/(x1 + 2y)
        = (y(x1 + 2y) - y(x1 + y) + x2)/(x1 + 2y)
        = (y^2 + x2)/(x1 + 2y)
  Start with y a power of 2 (because that's easy to multiply) bigger than the square root of x2.  Then we know that y will be decreasing
  with each step -- until it overshoots the target due to roundoff.  When y stops decreasing, we've reached bottom
  Note that a power of 2 bigger than x2/x1 is ALSO an upper bound for y -- so if this is smaller, pick it as a starting point instead.
  Assumes X2 is at least as large as X1
*/
void CUnsignedArithmeticHelper::GeneralSquareRootNewton(size_t  nX1Size,
                                                        size_t  nX2Size,
                                                        size_t  &nRootSize,
                                                        DIGIT   *pnX1,
                                                        DIGIT   *pnX2,
                                                        DIGIT   *pnRoot,
#if(_CollectDetailedTimingData)
                                                        DWORD64 &dwTimestamp,
#endif
                                                        DIGIT   *pnWorkspace)
{
#if(_CollectDetailedTimingData)
    DWORD64     dwTimestamp2 = dwTimestamp;
#endif
    size_t      i, nDigitShift, nBitShift, nTopSize, nBottomSize;
    DOUBLEDIGIT nCarry;
    DIGIT       *pYPrev, *pYCurr, *pNum1, *pNum2, *pNum3, *pSwap;
    i           = nX2Size + 2; // space needed for intermediate values
    pYPrev      = pnRoot;
    pYCurr      = pnWorkspace;
    pNum1       = pYCurr + i;
    pNum2       = pNum1  + i;
    pNum3       = pNum2  + i;
    pnWorkspace = pNum3  + i;
    // first guess y: power of 2.  Smallest power of 2 guaranteed larger than the square root of x2 or X2/x1 -- whichever is smaller.
    nTopSize    = BitSize(nX2Size, pnX2);
    nBottomSize = BitSize(nX1Size, pnX1);
    nBitShift   = min((nTopSize+1)>>1, nTopSize-nBottomSize+1);
    nDigitShift = nBitShift/_DIGIT_SIZE_IN_BITS;
    nBitShift   = 1 + (nBitShift%_DIGIT_SIZE_IN_BITS); // +1: note we actually use 2y, not y, in Newton
    if(_DIGIT_SIZE_IN_BITS==nBitShift)
    {
        nDigitShift++;
        nBitShift = 0;
    }
    // x1 + 2y
    if(nDigitShift < nX1Size)
    {
        for(i=0; i<nDigitShift; i++)
        {
            pYCurr[i] = pnX1[i];
        }
        nCarry      = pnX1[i] + (((DOUBLEDIGIT) 1)<<nBitShift);
        pYCurr[i++] = nCarry;
        nCarry      = nCarry>>_DIGIT_SIZE_IN_BITS;
        for(; i<nX1Size; i++)
        {
            nCarry    += pnX1[i];
            pYCurr[i] =  nCarry;
            nCarry    =  nCarry>>_DIGIT_SIZE_IN_BITS;
        }
        pYCurr[i]   = nCarry;
        nBottomSize = (0==nCarry) ? i : i+1;
    }
    else
    {
        for(i=0; i<nX1Size; i++)
        {
            pYCurr[i] = pnX1[i];
        }
        for(; i<nDigitShift; i++)
        {
            pYCurr[i] = 0;
        }
        pYCurr[i]   = (1<<nBitShift);
        nBottomSize = i+1;
    }
    // y^2 + x2
    for(i=0;i<nX2Size;i++)
    {
        pNum1[i] = pnX2[i];
    }
    pNum1[i] = 1;
    nTopSize = i+1;
    // (y^2 + x2)/(x1 + 2y)
#if(_CollectDetailedTimingData)
    dwTimestamp2                                     =  s_Timer.GetMicroseconds();
    g_nSquareRootTime[eSquareRootNewtonProcessTime]  += (dwTimestamp2 - dwTimestamp);
    dwTimestamp                                      =  dwTimestamp2;
    DivideBackend(nTopSize, nBottomSize, nRootSize, nBottomSize, pNum1, pYCurr, pYPrev, dwTimestamp, pnWorkspace);
    g_nSquareRootTime[eSquareRootNewtonMultiplyTime] += (dwTimestamp2 - dwTimestamp);
#else
    DivideBackend(nTopSize, nBottomSize, nRootSize, nBottomSize, pNum1, pYCurr, pYPrev, pnWorkspace);
#endif
    do
    {
        // Newton proper
        // pNum3 <- y^2
#if(_CollectDetailedTimingData)
        dwTimestamp2                                     =  dwTimestamp;
        SquareUBackend(nRootSize, pYPrev, pNum3, pnWorkspace, dwTimestamp, &nBottomSize);
        g_nSquareRootTime[eSquareRootNewtonMultiplyTime] += (dwTimestamp - dwTimestamp2);
#else
        SquareUBackend(nRootSize, pYPrev, pNum3, pnWorkspace, &nBottomSize);
#endif
        // pNum1 <- y^2 + x2.
        nCarry = 0;
        if(nX2Size <= nBottomSize)
        {
            for(i=0; i<nX2Size; i++)
            {
                nCarry   = (nCarry + pnX2[i]) + pNum3[i];
                pNum1[i] = nCarry;
                nCarry   = (nCarry>>_DIGIT_SIZE_IN_BITS);
            }
            for(; i<nBottomSize; i++)
            {
                nCarry   = nCarry + pNum3[i];
                pNum1[i] = nCarry;
                nCarry   = (nCarry>>_DIGIT_SIZE_IN_BITS);
            }
        }
        else
        {
            for(i=0; i<nBottomSize; i++)
            {
                nCarry   = (nCarry + pnX2[i]) + pNum3[i];
                pNum1[i] = nCarry;
                nCarry   = (nCarry>>_DIGIT_SIZE_IN_BITS);
            }
            for(; i<nX2Size; i++)
            {
                nCarry   = nCarry + pnX2[i];
                pNum1[i] = nCarry;
                nCarry   = (nCarry>>_DIGIT_SIZE_IN_BITS);
            }
        }
        pNum1[i] = nCarry;
        nTopSize = i + nCarry; // note adding two numbers: carry is 0 or 1 ONLY
        // pNum2 <- x1 + 2y
        nCarry = 0;
        if (nRootSize < nX1Size)
        {
            for(i=0; i<nRootSize; i++)
            {
                nCarry   += (((DOUBLEDIGIT) pYPrev[i])<<1) + pnX1[i];
                pNum2[i] =  nCarry;
                nCarry   =  nCarry>>_DIGIT_SIZE_IN_BITS;
            }
            for(; i<nX1Size; i++)
            {
                nCarry   += pnX1[i];
                pNum2[i] =  nCarry;
                nCarry   =  nCarry>>_DIGIT_SIZE_IN_BITS;
            }
        }
        else
        {
            for(i=0; i<nX1Size; i++)
            {
                nCarry   += (((DOUBLEDIGIT) pYPrev[i])<<1) + pnX1[i];
                pNum2[i] =  nCarry;
                nCarry   =  nCarry>>_DIGIT_SIZE_IN_BITS;
            }
            for(; i<nRootSize; i++)
            {
                nCarry   += (((DOUBLEDIGIT) pYPrev[i])<<1);
                pNum2[i] =  nCarry;
                nCarry   =  nCarry>>_DIGIT_SIZE_IN_BITS;
            }
        }
        pNum2[i]    = nCarry;
        nBottomSize = (nCarry) ? i+1 : i;
        // set i to hold old root size temporarily
        i = nRootSize;
#if(_CollectDetailedTimingData)
        dwTimestamp2                                     =  s_Timer.GetMicroseconds();
        g_nSquareRootTime[eSquareRootNewtonProcessTime]  += (dwTimestamp2 - dwTimestamp);
        dwTimestamp                                      =  dwTimestamp2;
        DivideBackend(nTopSize, nBottomSize, nRootSize, nTopSize, pNum1, pNum2, pYCurr, dwTimestamp, pnWorkspace);
        g_nSquareRootTime[eSquareRootNewtonDivideTime]   += (dwTimestamp - dwTimestamp2);
#else
        DivideBackend(nTopSize, nBottomSize, nRootSize, nTopSize, pNum1, pNum2, pYCurr, pnWorkspace);
#endif
        pSwap  = pYCurr;
        pYCurr = pYPrev;
        pYPrev = pSwap;
    }
    while(-1 == CBigInteger::CompareUnsigned(nRootSize, i, pYPrev, pYCurr));
    if (pYCurr != pnRoot)
    {
        // ended in the wrong slot.  Copy over.
        for(i=0; i<nRootSize; i++)
        {
            pnRoot[i] = pYCurr[i];
        }
    }
#if(_CollectDetailedTimingData)
    dwTimestamp2                                     =  s_Timer.GetMicroseconds();
    g_nSquareRootTime[eSquareRootNewtonProcessTime]  += (dwTimestamp2 - dwTimestamp);
    dwTimestamp                                      =  dwTimestamp2;
#endif
}

// if power memory needs changes, update NthRootMemoryNeeds accordingly
size_t CUnsignedArithmeticHelper::PowerMemoryNeeds(DIGIT *pX, size_t nXSize, size_t nPower)
{
    size_t nXSizeInBits = BitSize(nXSize, pX);
    nXSize = (nXSizeInBits*nPower + 1)/2;  // bitsize of the square
    nXSize = (nXSize + _DIGIT_SIZE_IN_BITS - 1)/_DIGIT_SIZE_IN_BITS; // digit size of the square
    return (nXSizeInBits*nPower + 1 + _DIGIT_SIZE_IN_BITS - 1)/_DIGIT_SIZE_IN_BITS + SquareMemoryNeeds(nXSize) + 1;
}

// needs to be kept in sync with power memory needs
size_t CUnsignedArithmeticHelper::NthRootMemoryNeeds(size_t nXSize, DIGIT nRoot)
{
    if(nXSize*_DIGIT_SIZE_IN_BITS < nRoot)
    {
        // root IS 1; no need to compute
        return 0;
    }
    else
    {
        DIGIT  pThree[] = { 3 };
        size_t nPower3Needs = (2 * nRoot + _DIGIT_SIZE_IN_BITS) / _DIGIT_SIZE_IN_BITS + PowerMemoryNeeds(pThree, 1, nRoot);
        if(nXSize*_DIGIT_SIZE_IN_BITS < 2*((size_t) nRoot))
        {
            // root can be at most 3
            return nPower3Needs;
        }
        else
        {
            // general case
            size_t nMemoryNeeds;
            size_t nRootSize            = (nXSize+nRoot-1)/nRoot;
            size_t nPowerMemoryNeeds    = nXSize + 1 + SquareMemoryNeeds((nXSize + 1)/2);  // room for the root to the power, plus room for squaring
            size_t nDivisionMemoryNeeds = DivisionMemoryNeeds(nXSize, nRootSize);
            nMemoryNeeds =  max(nPowerMemoryNeeds, nDivisionMemoryNeeds) + nXSize;
            nMemoryNeeds += 2*(nXSize + NthRootPowerOverflow(nRoot)) + nPower3Needs; // last bit: may need to take 3^<root> in final step; room for that
            return nMemoryNeeds;
        }
    }
}

void CUnsignedArithmeticHelper::Power(size_t nXSize, size_t &nPowerSize, unsigned int nPower, const DIGIT *pnX, DIGIT *pnPowerOfX, DIGIT *pnWorkspace)
{
    // compute the size of the power and x in bits.  This gives a reasonably tight upper bound on the size of x^n
    DIGIT  *pnXa, *pnXb, *pnHold;
    size_t nXSizeInBits     = BitSize(nXSize, pnX);
    int    nPowerSizeInBits = 31, n;
    int    nFurtherSetBits  = 0;
    while(0==((1<<nPowerSizeInBits)&nPower)) nPowerSizeInBits--;
    // start x^n at x.  For every bit in the power after the first: square x^n.  Then if the bit is set multiply by x.
    // Each of these operations means moving the value of x^n.  We have nPowerSizeInBits square operations.  Thus if we know how many bits in the power
    // are set (ignoring the first), we know how many operations we need to compute x^n -- and thus whether we should start with x^n in pnPowerOfX or
    // in the workspace
    n = nPowerSizeInBits;
    while(n)
    {
        n--;
        nFurtherSetBits += (0<((1<<n)&nPower));
    }
    nPowerSize  =  (nXSizeInBits*nPower + _DIGIT_SIZE_IN_BITS - 1)/_DIGIT_SIZE_IN_BITS; // might actually be smaller, but might be this large -- and no larger
    pnXa        =  ((nPowerSizeInBits+nFurtherSetBits)&1) ? pnWorkspace : pnPowerOfX;
    pnXb        =  ((nPowerSizeInBits+nFurtherSetBits)&1) ? pnPowerOfX : pnWorkspace;
    pnWorkspace += nPowerSize + 1; // +1: need one extra DIGIT for overflow
    // data starts in pnXa; ends in pnPowerOfX
    memcpy(pnXa, pnX, sizeof(DIGIT)*nXSize);
    nPowerSize = nXSize;
    while (nPowerSizeInBits--)
    {
        Square(nPowerSize, pnXa, pnXb, pnWorkspace);
        nPowerSize = nPowerSize<<1;
        if(0==pnXb[nPowerSize-1]) nPowerSize--;
        if((1<<nPowerSizeInBits)&nPower)
        {
            // need to multiply by x
#if _CollectDetailedTimingData
            DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
            MultUBackend(nXSize, nPowerSize, pnX, pnXb, pnXa, pnWorkspace, dwTimestamp);
#else
            MultUBackend(nXSize, nPowerSize, pnX, pnXb, pnXa, pnWorkspace);
#endif
            nPowerSize += nXSize;
            if(0==pnXa[nPowerSize-1]) nPowerSize--;
        }
        else
        {
            // get value back in pnXa
            pnHold = pnXa;
            pnXa   = pnXb;
            pnXb   = pnHold;
        }
    }
}

void CUnsignedArithmeticHelper::NthRootNewton(size_t nASize, unsigned int n, size_t &nNthRootSize, const DIGIT *pA, DIGIT *pnRoot, DIGIT *pnWorkspace)
{
    long long   i;
    DOUBLEDIGIT nSum, nCarry, nPow = n-1; // nPow: power take guess to
    size_t      nRightSize, nRemainderSize, nNewSize, nOldSize;
    DIGIT       *pnGuess  = pnWorkspace;
    DIGIT       *pOld     = pnGuess;
    DIGIT       *pNew     = pnRoot;
    DIGIT       *pRight   = pnGuess + nASize + 1;
    DIGIT       *pACopy   = pRight  + nASize + 1;
    pnWorkspace = pACopy + nASize;
    // actually do Newton
    // Recall: x(i+1) = x(i) - f(x(i))/f'(x(i))
    // f(x)  = x^n - a
    // f'(x) = nx^(n-1)
    // -> x - f(x)/f'(x) = x - (x^n - a)/(nx^(n-1))
    //                   = (nx^n - (x^n - a))/(nx^(n-1))
    //                   = ((n-1)x^n + a)/(nx^(n-1))
    //                   = ((n-1)x + a/x^(n-1))/n
    // If we start with a guess above the root, at each step the guess will decrease until roundoff causes us to either reach it or we overshoot and
    // bounce back.  In any case the moment the guess is NOT less than the previous guess, we've found our solution -- the previous guess
    // Good initial guess: 
    // size_t nBitsizeX = BitSize(nXSize, pnX);
    // initial guess: 2^((bitsize + n - 1)/n)
    // Then  x^(n-1) is 1<<(nBitShiftInitialGuess*(n-1)) and x^n is 1<<(nBitShiftInitialGuess*n)
    // so ((n-1)x^n + a)/(nx^(n-1)) is ((n-1)*(1<<nBitShiftInitialGuess) + a>>(1<<(nBitShiftInitialGuess*n)))/n
    // But I'm feeling lazy, so I'm not going through the optimizations.
    size_t nBitsizeX = BitSize(nASize, pA);
    nBitsizeX = (nBitsizeX+n-1)/n;
    nNewSize = nBitsizeX/_DIGIT_SIZE_IN_BITS;
    for(i=0; i<nNewSize; i++) pOld[i] = c_nClearHigh; // certainly bigger than the root -- but not by more than 1 DIGIT
    pOld[i] = ((DIGIT) -1)>>(32 - nBitsizeX%_DIGIT_SIZE_IN_BITS);
    nNewSize += (0 < pOld[i]);
    do
    {
        nOldSize = nNewSize;
        // x^(n-1)
        Power(nOldSize, nNewSize, nPow, pOld, pNew, pnWorkspace); // pNew <- pOld^(n-1)
        memcpy(pACopy, pA, sizeof(DIGIT)*nASize);
        Divide(nASize, nNewSize, nRightSize, nRemainderSize, pACopy, pNew, pRight, pnWorkspace); // pRight <- a/(pOld^(n-1))
        // Note that x >= (nth root of a) -> a/x^(n-1)) <= (nth root of a)
        // -> a/x^(n-1)) <= (n-1)x
        // and if x <= a/(x^(n-1)) we have reached our stopping point
        if (-1 != CBigInteger::CompareUnsigned(nRightSize, nOldSize, pRight, pOld))
        {
            break; // end of the line
        }
        // pRight <- (n-1)*pOld + a/(pOld^(n-1))
        nCarry = 0;
        for(i=0; i<nRightSize; i++)
        {
            nCarry    += pRight[i];
            nSum      =  nPow*pOld[i];
            pRight[i] =  nCarry + nSum;
            nCarry    =  (((nCarry&c_nClearHigh) + (nSum&c_nClearHigh))>>_DIGIT_SIZE_IN_BITS) + (nCarry>>_DIGIT_SIZE_IN_BITS) + (nSum>>_DIGIT_SIZE_IN_BITS);
        }
        for(; i<nOldSize; i++)
        {
            nSum      =  nPow*pOld[i];
            pRight[i] =  nCarry + nSum;
            nCarry    =  (((nCarry&c_nClearHigh) + (nSum&c_nClearHigh))>>_DIGIT_SIZE_IN_BITS) + (nCarry>>_DIGIT_SIZE_IN_BITS) + (nSum>>_DIGIT_SIZE_IN_BITS);
        }
        pRight[i]  = nCarry;
        nRightSize = nOldSize + (0<nCarry);
        // pNew = ((n-1)*pOld + a/(pOld^(n-1)))/n
        nCarry   = 0;
        nNewSize = nRightSize-1;
        for(i=nRightSize-1; 0<=i; i--)
        {
            nSum    = nCarry | pRight[i];
            pNew[i] = nSum/n;
            nCarry  = (nSum%n)<<_DIGIT_SIZE_IN_BITS;
        }
        if (pNew[nNewSize]) nNewSize++;
        DIGIT *pHold = pOld;
        pOld = pNew;
        pNew = pHold;
    }
    while(true);
    if (pnRoot != pOld)
    {
        // final result in the wrong slot; copy over
        memcpy(pnRoot, pOld, nOldSize*sizeof(DIGIT));
    }
    nNthRootSize = nOldSize;
}

void CUnsignedArithmeticHelper::NthRootNewtonFromGuess(size_t nASize, unsigned int n, size_t &nNthRootSize, const DIGIT *pA, DIGIT *pnRoot, DIGIT *pnWorkspace)
{
    long long   i;
    DOUBLEDIGIT nSum, nCarry, nPow = n-1; // nPow: power take guess to
    size_t      nRightSize, nRemainderSize, nNewSize, nOldSize;
    DIGIT       *pnGuess  = pnWorkspace;
    DIGIT       *pOld     = pnRoot;
    DIGIT       *pNew     = pnGuess;
    DIGIT       *pRight   = pnGuess + nASize + NthRootPowerOverflow(n);
    DIGIT       *pACopy   = pRight  + nASize + NthRootPowerOverflow(n);
    pnWorkspace = pACopy + nASize;
    // actually do Newton
    // Recall: x(i+1) = x(i) - f(x(i))/f'(x(i))
    // f(x)  = x^n - a
    // f'(x) = nx^(n-1)
    // -> x - f(x)/f'(x) = x - (x^n - a)/(nx^(n-1))
    //                   = (nx^n - (x^n - a))/(nx^(n-1))
    //                   = ((n-1)x^n + a)/(nx^(n-1))
    //                   = ((n-1)x + a/x^(n-1))/n
    // If we start with a guess above the root, at each step the guess will decrease until roundoff causes us to either reach it or we overshoot and
    // bounce back.  In any case the moment the guess is NOT less than the previous guess, we've found our solution -- the previous guess
    nNewSize = nNthRootSize;
    do
    {
        nOldSize = nNewSize;
        // x^(n-1)
        Power(nOldSize, nNewSize, nPow, pOld, pNew, pnWorkspace); // pNew <- pOld^(n-1)
        memcpy(pACopy, pA, sizeof(DIGIT)*nASize);
        Divide(nASize, nNewSize, nRightSize, nRemainderSize, pACopy, pNew, pRight, pnWorkspace); // pRight <- a/(pOld^(n-1))
        // Note that x >= (nth root of a) -> a/x^(n-1)) <= (nth root of a)
        // -> a/x^(n-1)) <= (n-1)x
        // and if x <= a/(x^(n-1)) we have reached our stopping point
        if (-1 != CBigInteger::CompareUnsigned(nRightSize, nOldSize, pRight, pOld))
        {
            break; // end of the line
        }
        // pRight <- (n-1)*pOld + a/(pOld^(n-1))
        nCarry = 0;
        for(i=0; i<nRightSize; i++)
        {
            nCarry    += pRight[i];
            nSum      =  nPow*pOld[i];
            pRight[i] =  nCarry + nSum;
            nCarry    =  (((nCarry&c_nClearHigh) + (nSum&c_nClearHigh))>>_DIGIT_SIZE_IN_BITS) + (nCarry>>_DIGIT_SIZE_IN_BITS) + (nSum>>_DIGIT_SIZE_IN_BITS);
        }
        for(; i<nOldSize; i++)
        {
            nSum      =  nPow*pOld[i];
            pRight[i] =  nCarry + nSum;
            nCarry    =  (((nCarry&c_nClearHigh) + (nSum&c_nClearHigh))>>_DIGIT_SIZE_IN_BITS) + (nCarry>>_DIGIT_SIZE_IN_BITS) + (nSum>>_DIGIT_SIZE_IN_BITS);
        }
        pRight[i]  = nCarry;
        nRightSize = nOldSize + (0<nCarry);
        // pNew = ((n-1)*pOld + a/(pOld^(n-1)))/n
        nCarry   = 0;
        nNewSize = nRightSize-1;
        for(i=nRightSize-1; 0<=i; i--)
        {
            nSum    = nCarry | pRight[i];
            pNew[i] = nSum/n;
            nCarry  = (nSum%n)<<_DIGIT_SIZE_IN_BITS;
        }
        if (pNew[nNewSize]) nNewSize++;
        DIGIT *pHold = pOld;
        pOld = pNew;
        pNew = pHold;
    }
    while(true);
    if (pnRoot != pOld)
    {
        // final result in the wrong slot; copy over
        memcpy(pnRoot, pOld, nOldSize*sizeof(DIGIT));
    }
    nNthRootSize = nOldSize;
}

/*
  nth root of y: the largest number x s.t. x^n <= y
  Consider taking the nth root of an n-bit number.  2^n is an n+1 bit number.  So the root is 1.
  Likewise 4^n is a 2n+1 bit number.  So the nth root of a 2n bit number is either 2 or 3.
  Consider taking the nth root of a number y with 2jn bits, 2 <= j.
  First, solve the problem of finding the nth root of the first jn bits; call this root a'.  (2^j)^n is 2^(jn) and
  has jn+1, so a'<2^j -> the root has at most j bits
  Similarly (2^(j-1))^n has jn-n+1 bits < jn since 2 <= n.  So the root has at least j bits.
  Ergo, the root has exactly j bits.

  Now consider solving our original problem.  Note that a'^n <= y>>(jn) by construction
  so (a'<<j)^n <= y.  Let a = a'<<j.
  We wish to find the largest b s.t. (a+b)^n <= y
  Suppose b has at least j+1 bits
  Then a+b <= a + 1<<j
            = (a'<<j) + (1<<j)
            = (a' + 1)<<j
  But we know from the way a' was chosen that y < ((a'+1)<<j)^n
  So b has at most j bits

  (a+b)^n <= y
  <-> a^n + (n choose 1) a^(n-1)b + (n choose 2)a^(n-2)b^2 + (n choose 3)a^(n-3)b*3 + ... + (n choose n-1) ab^(n-1) + b^n <= y
  <-> ((n choose 1) a^(n-1) + (n choose 2)a^(n-2)b + ... + b^(n-1))b <= y - a^n = y'
  Now from the above a is a 2j-bit number and b is a j-bit number.  Ignoring the "choose" coefficients, this is a geometric
  series -- each term is ~j bits larger than the next.
  Suppose n has k bits.  Note the "choose" coefficients grow by at most n and k<j-1, we have
  (n choose 2)a^(n-2)b + ... + b^(n-1))b < (1<<k)na^(n-2)
  Let a' = (a>>k).  We then have that
  ((n choose 1) a^(n-1) + (n choose 2)a^(n-2)b + ... + b^(n-1))b <= b((a' + 1)<<k)^n
  so if b satisfies (n choose 1)((a' + 1)<<k)^(n-1)b <= y - a^n it also satisfies
  ((n choose 1) a^(n-1) + (n choose 2)a^(n-2)b + ... + b^(n-1))b <= y - a^n
  With this b in hand, replace a with a+b and repeat -- a will be larger, so the convergence assumptions still hold
  And when to stop?  The inequality gives a lower bound for the maximum b we can add.
  Now it is clear that (n choose 1)(a'<<k)^(n-1)b <= ((n choose 1) a^(n-1) + (n choose 2)a^(n-2)b + ... + b^(n-1))b
  so if b satisfies ((n choose 1) a^(n-1) + (n choose 2)a^(n-2)b + ... + b^(n-1))b <= y - a^n it also satisfies
  (n choose 1)(a'<<k)^(n-1)b <= y - a^n
  So the maximum b satisfying (n choose 1)(a'<<k)^(n-1)b <= y - a^n is an upper bound for the maximum b satisfying
  ((n choose 1) a^(n-1) + (n choose 2)a^(n-2)b + ... + b^(n-1))b <= y - a^n (note that this holds regardless of the size of n)

  Now suppose 0 is the largest value b s.t. (n choose 1)((a' + 1)<<k)^(n-1)b <= y - a^n
  How big can the largest b' satisfying (n choose 1)(a'<<k)^(n-1)b' <= y - a^n be?

  Well; (n choose 1)((a' + 1)<<k)^(n-1)/2 <= (n choose 1)(a'<<k)^(n-1)b' is clear
  So since the solution to (n choose 1)((a' + 1)<<k)^(n-1)b <= y - a^n rounds down to 0,
  the solution to (n choose 1)(a'<<k)^(n-1)b' <= y - a^n can be at most 1 (twice as large, rounded down)

  So once our process reachea solution of b = 0, see if we can replace a with a+1.  And that really IS
  the end of the line.

  ======================================================================================================================

  Now: what about the case where the difference in the size of a and b is j bits, whereas the size of the root is k bits
  with j-1 <= k?  The inequality we used to get a lower bound for the maximum value of b does not necessarily hold.
  
  By construction, a is either 2j or 2j-1 bits (depending on whether y is a multiple of n or not) and b is a j bit number.
  Since n is at most 32 bits, we must have k <= 32 so j is at most 33.

  And I still don't see a way better than Newton to solve this.

  So: with y a 2jn-m bit number, m < 2n
  if j-1<k, use Newton
  Otherwise solve for the nth root of the high-order jn bits recursively, then use the method outlined above to get the lower order bits
*/

void CUnsignedArithmeticHelper::NthRoot(size_t nXSize, unsigned int n, size_t &nRootSize, DIGIT *pnX, DIGIT *pnRoot, DIGIT *pnWorkspace)
{
    unsigned int nBitSizeN       = 32;
    size_t       nXBitsLeadDigit = _DIGIT_SIZE_IN_BITS;
    DIGIT        nLeadDigitX     = pnX[nXSize - 1];
    while(0==((1<<(nBitSizeN-1))&n))                 nBitSizeN--;
    while(0==((1<<(nXBitsLeadDigit-1))&nLeadDigitX)) nXBitsLeadDigit--;
    NthRootRecursive(nXSize, n, nBitSizeN, nXBitsLeadDigit, nRootSize, pnX, pnRoot, pnWorkspace);
}

void CUnsignedArithmeticHelper::NthRootRecursive(size_t nYSize, DIGIT n, size_t nRootBits, size_t nXBitsLeadDigit, size_t &nRootSize, DIGIT *pnY, DIGIT *pnRoot, DIGIT *pnWorkspace)
{
    if(1==nYSize)
    {
        // small.  Do with math.h's power function
        DIGIT d  = pow(*pnY, 1.0/n);
        DIGIT d2 = pow(d, n);
        // might be rounding other than we desire -- a little over X instead of a little under
        if (*pnY < d2)
        {
            d--;
            d2 = pow(d, n);
        }
        nRootSize = 1;
        *pnRoot   = d;
    }
    else
    {
        size_t       j;
        DOUBLEDIGIT  nCarry;
        DIGIT        *pB, *pAPrime, *pAPrimePow;
        size_t       nBSize, nAPrimeSize, i, nBitshiftJ, nDigitShiftJ, nDigitShiftUpper, nBitShiftK, nDigitShiftK, nYTwiddleSize, nRemainderSize;
        size_t       nBitSizeY = BitSize(nYSize, pnY);
  //      size_t       nBitSizeLeadDigit = _DIGIT_SIZE_IN_BITS;
    //    DIGIT        lead              = pnY[nYSize-1];
      //  while(0==((1<<(nBitSizeLeadDigit-1))&lead)) nBitSizeLeadDigit--;
        //nBitSizeY = nBitSizeLeadDigit + (nYSize-1)*_DIGIT_SIZE_IN_BITS;
        if(nBitSizeY <= n)
        {
            // too small for anything but 1
            nRootSize = 1;
            *pnRoot   = 1;
        }
        else if(nBitSizeY <= 2*((size_t) n))
        {
            // root is either 2 or 3
            // see if 3 works.  If not, can only be 2
            size_t nPowerSize = (2*n+_DIGIT_SIZE_IN_BITS)/_DIGIT_SIZE_IN_BITS;
            *pnRoot = 3;
            Power(1,nRootSize,n,pnRoot,pnWorkspace,pnWorkspace+nPowerSize);
            if(-1==CBigInteger::CompareUnsigned(nYSize,nRootSize,pnY,pnWorkspace))
            {
                // too big
                *pnRoot = 2;
            }
            nRootSize = 1;
        }
        else
        {
            // Use recursive descent to get the upper half+ of the root, and recursive with hint to finish it
            // Suppose Y is m bits long.
            // Find the largest 0<j s.t. nj < m/2.  (Note that if we get here this is guaranteed to exist, as 2*n < m)
            // Compute the root of Y ignoring the last jn bits recursively.
            // Use that "guess" as the seed to NthRootRecursiveWithHint to finish it
            j            = nBitSizeY/(2*n);
            nDigitShiftJ = j/_DIGIT_SIZE_IN_BITS;
            if(0<nDigitShiftJ)
            {
                // JUST cut off trailing DIGITs -- simpler, and most of the work is in the "with hint" stage so making the recursive step larger
                // at the expense of the "hint" stage is not ALL bad
                for(size_t i=0; i<nDigitShiftJ; i++)
                {
                    pnRoot[i] = 0;
                }
                nDigitShiftK = n*nDigitShiftJ;
                NthRootRecursive(nYSize - nDigitShiftK, n, nRootBits, nXBitsLeadDigit, nRootSize, pnY + nDigitShiftK, pnRoot + nDigitShiftJ, pnWorkspace);
                nRootSize += nDigitShiftJ;
                j         =  j - (j%_DIGIT_SIZE_IN_BITS); // reduce j to actual shift used
            }
            else
            {
                DIGIT hold;
                // use a bit shift instead of a digit shift
                nBitshiftJ   =  j;
                nBitShiftK   =  n*j;
                nDigitShiftK =  nBitShiftK/_DIGIT_SIZE_IN_BITS;
                nBitShiftK   =  nBitShiftK%_DIGIT_SIZE_IN_BITS;
                pnY          += nDigitShiftK; // for convenience -- just looking at the top section
                hold         =  pnY[0];
                nYSize       =  CBigIntegerHelper::ShiftRightInPlace(nYSize - nDigitShiftK, nBitShiftK, 0, pnY);
                NthRootRecursive(nYSize, n, nRootBits, nXBitsLeadDigit, nRootSize, pnY, pnRoot, pnWorkspace);
                nYSize       =  CBigIntegerHelper::ShiftLeftInPlace(nYSize, nBitShiftK, 0, pnY)+nDigitShiftK;
                nRootSize    =  CBigIntegerHelper::ShiftLeftInPlace(nRootSize, nBitshiftJ, 0, pnRoot);
                pnY[0]       =  hold;
                pnY          -= nDigitShiftK;
            }
            // finish it
            NthRootRecursiveWithHint(n, nRootSize, nYSize, j, pnRoot, pnY, pnWorkspace);
        }
    }
}

DOUBLEDIGIT GetTopDigitsizeBits(DIGIT *pNumber, size_t nNumberSize)
{
    DOUBLEDIGIT nTop;
    if(nNumberSize <= 1)
    {
        nTop = *pNumber;
    }
    else
    {
        int nExcess = 0;
        nTop = *((DOUBLEDIGIT *) (pNumber+nNumberSize-2));
        // find out how many bits nTop is in excess of _DIGIT_SIZE_IN_BITS, and shift right by that amount
        DOUBLEDIGIT nBit = ((DOUBLEDIGIT) 1)<<(2*_DIGIT_SIZE_IN_BITS-1);
        while(0==(nBit&nTop))
        {
            nExcess++;
            nBit = nBit>>1;
        }
        nTop = nTop>>(_DIGIT_SIZE_IN_BITS - nExcess);
    }
    return nTop;
}

//
// Suppose we have big integers a and y and integer n, where a^n <= y.  We wish to find the largest big integer b s.t (a+b)^n <= y.
// <-> a^n + nba^(n-1) + (n choose 2) b^2a^(n-2) + (n choose 3) b^3a^(n-3) + ... + b^n <= y
// <-> b(na^(n-1) + (n choose 2)ba^(n-2) + ... + b^(n-1)) <= y - a^n
// Now suppose e is chosen s.t. b <= e.
// Then if b is the largest integer s.t. b(na^(n-1) + (n choose 2)ea^(n-2) + ... + e^(n-1)) <= y - a^n
// then b(na^(n-1) + (n choose 2)ba^(n-2) + ... + b^(n-1)) <= y - a^n (though it might not be the largest such b)
//
// Now consider na^(n-1) + (n choose 2)a^(n-2)e + ... + e^(n-1)
//
// (a+e)^(n-1)  = a^(n-1) + (n-1)a^(n-2)e + ((n-1) choose 2)a^(n-3)e^2 + ... + e^(n-1)
// n(a+e)^(n-1) = na^(n-1) + n(n-1)a^(n-2)e + n((n-1) choose 2)a^(n-3)e^2 + ... + ne^(n-1)
// compare with   na^(n-1) + (n choose 2)a^(n-2)e + ... + e^(n-1)
//
// the ith component of n(a+e)^(n-1)  is n((n-1) choose i)a^(n-1-i)e^i
// the ith component of the latter is    (n choose (i+1))a^(n-1-i)e^i
//
// n((n-1) choose i) = n(n-1)!/((n-1-i)!i!) = n!/((n-1-i)!i!)
// n choose(i+1)     =                        n!/((n-i-1)!(i+1)!)
//
// The former is clearly larger.  So if b is chosen such that bn(a+e)^(n-1) <= (y - a^n), we must have that
//                                                            b(na^(n-1) + (n choose 2)a^(n-2)e + ... + e^(n-1)) <= (y - a^n)
// and hence                                                  b(na^(n-1) + (n choose 2)ba^(n-2) + b^(n-1)) <= y - a^n  since b <= e
// Finally, to get the best possible b for bn(a+e)^(n-1) <= (y - a^n) we just set
// b = (y - a^n)/(n(a+e)^(n-1))
//
// To get e: well; clearly b <= (y - a^n)/(na^(n-1)).  We can limit this with a power of 2 to get a fast estimate for e.
// Also: when first called, A contains the nth root for the first few bits -- all but the final jn, where j is an integer greater than 0.
// With this, we know that b can be at most j bits in length (otherwise it would overlap with the computed best root, forcing the first
// part to be larger -- and thus exceeed the computed root).

void CUnsignedArithmeticHelper::NthRootRecursiveWithHint(DIGIT n, size_t &nASize, size_t nYSize, size_t nMaxBSizeInBits, DIGIT *pA, const DIGIT *pY, DIGIT *pWorkspace)
{
    DOUBLEDIGIT nBottom, nTop;
    size_t      nPowerSizeSmall, nPowerSizeLarge, nBottomBitsize, nTopBitSize, nPowerBitsize, i, nBottomSize, nTopSize, nBitSizeBUpperBound;
    size_t      nMaxOverflow = NthRootPowerOverflow(n); // max overflow might get from computing power, in DIGITS
    DIGIT       *pTop        = pWorkspace;                    // space for a^n, y-a^n.  nYSize+nMaxOverflow is enough, including overflow space
    DIGIT       *pBottom     = pTop + nYSize + nMaxOverflow;  // space for a^(n-1), n(a+e)^(n-1).  Again nYSize+nMaxOverflow is enough, including overflow space
    pWorkspace = pBottom + nYSize + nMaxOverflow;
    pA[nASize] = 0; // overflow guard
    do
    {
        // a^(n-1), a^n
        Power(nASize, nPowerSizeSmall, n - 1, pA, pBottom, pWorkspace);
#if _CollectDetailedTimingData
        DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
        MultUBackend(nASize, nPowerSizeSmall, pA, pBottom, pTop, pWorkspace, dwTimestamp);
#else
        MultUBackend(nASize, nPowerSizeSmall, pA, pBottom, pTop, pWorkspace);
#endif
        nPowerSizeLarge = nPowerSizeSmall + nASize;
        if(0==pTop[nPowerSizeLarge-1]) nPowerSizeLarge--;
        // y - a^n.  Note that we don't need a^n after this is computed; put in pTop (overwriting a^n)
        nPowerSizeLarge = Subtract(nYSize, nPowerSizeLarge, pY, pTop, pTop);
        if(0==nPowerSizeLarge)
        {
            // b is at most 0 -> done
            break;
        }
        // find the maximum bitsize of b: (y - a^n)/(na^(n-1)) is an upper bound for b -- what is the (maximum) bitsize of THAT?
        // pull first _DIGIT_SIZE_IN_BITS bits out of a^(n-1), multiply by n, and subtract 1.  Use the bitsize of the result to
        // get a lower bound for the bitsize of n*a^(n-1): <result bitsize> - _DIGIT_SIZE_IN_BITS + <bitsize of a^(n-1)>
        // This digit also gives an upper bound for the size in bits of (y-a^n)/(na^(n-1)) -- compare first _DIGIT_SIZE_IN_BITS
        // of top and bottom+1; if top is greater, size<top>-size<bottom>+1; else, size<top>-size<bottom>
        nTopBitSize         =  BitSize(nPowerSizeLarge, pTop); // bitsize of y - a^n
        nPowerBitsize       =  BitSize(nPowerSizeSmall, pBottom); // bitsize of a^(n-1).  Note that we don't need a^(n-1) after this
        nTop                =  GetTopDigitsizeBits(pTop, nPowerSizeLarge);
        nBottom             =  GetTopDigitsizeBits(pBottom, nPowerSizeSmall);
        nBottomBitsize      =  DigitBitSize(nBottom);
        nBottom             *= n;
        nBottom             -= 1;
        nBottomBitsize      =  DigitBitSize(nBottom) - nBottomBitsize;
        nBottom             =  nBottom>>nBottomBitsize; // just want the leading _DIGIT_SIZE_IN_BITS) for comparison
        nBitSizeBUpperBound =  nTopBitSize + (nBottom<=nTop);
        nBottomBitsize      =  nPowerBitsize + nBottomBitsize;
        if (nBitSizeBUpperBound <= nBottomBitsize) break; // max size 0 bits -> done
        nBitSizeBUpperBound -= nBottomBitsize;
        // for large roots and small values of A, this upper bound may be bigger than A.  But the updates will always be getting smaller
        // by the way they are done -- refining by pulling in a piece of what's left.  If we get into such a state, use the size of A as
        // a limit on the update e.
        if (nMaxBSizeInBits < nBitSizeBUpperBound)
        {
            nBitSizeBUpperBound = nMaxBSizeInBits;
        }
        if(nBitSizeBUpperBound<=2)
        {
            // Note we don't need the computed values nBottom, nTop anymore
            // b can be 0, 1, 2, or 3.
            if(2==nBitSizeBUpperBound)
            {
                // 2 or 3 is possible (if 1 == nBitSizeBUpperBound, only 0 or 1 is possible for b)
                // See if 2 fits.
                // use nTop for carry
                nTop = 2;
                i    = 0;
                do
                {
                    nTop    += pA[i];
                    pA[i++] =  nTop;
                    nTop    =  nTop>>_DIGIT_SIZE_IN_BITS;
                }
                while(nTop);
                if (pA[nASize]) // certainly too large
                {
                    nASize++;
                    nPowerSizeLarge = nYSize + 1; // flag for compare to undo
                }
                else
                {
                    Power(nASize, nPowerSizeLarge, n, pA, pTop, pWorkspace);
                }
                if (1 == CBigInteger::CompareUnsigned(nPowerSizeLarge, nYSize, pTop, pY))
                {
                    // nope; doesn't fit.  Subtract 2 off again
                    if(2<=pA[0]) pA[0] -= 2;
                    else
                    {
                        pA[0] -= 2;
                        i     =  1;
                        while(0==pA[i]) pA[i++] = c_nClearHigh;
                        pA[i]--;
                        if(0==pA[nASize-1]) nASize--;
                    }
                }
            }
            // see if we can add 1 more to b
            nTop = 1;
            i    = 0;
            do
            {
                nTop    += pA[i];
                pA[i++] =  nTop;
                nTop    = nTop>>_DIGIT_SIZE_IN_BITS;
            }
            while(nTop);
            if (pA[nASize]) // shouldn't ever happen
            {
                nASize++;
            }
            Power(nASize, nPowerSizeLarge, n, pA, pTop, pWorkspace);
            if(1==CBigInteger::CompareUnsigned(nPowerSizeLarge, nYSize, pTop, pY))
            {
                // nope; doesn't fit.  Subtract 1 off again
                i = 0;
                while(0==pA[i]) pA[i++] = c_nClearHigh;
                pA[i]--;
                if(0==pA[nASize-1]) nASize--;
            }
            break;
        }
        // use a + 1<<shift rounded up to the shift bit and truncated  as a+e
        // compute the minimum bits of our update using the basic scheme and this upper bound.
        // a + e: Truncate a to the <e size> bit, rounding up, thyen add 1.  Note rather than check we round 0 up
        // Compute x = (a + 1<<(nBitSizeBUpperBound + 1))>>(nBitSizeBUpperBound+1)
        //           = (a>>(nBitSizeBUpperBound + 1)) + 1
        //         z = (y - a^n)>>((nBitSizeBUpperBound+1)*(n-1))
        // Approximate (y - a^n)/(n*(a+e)^n-1) with z/(nx^(n-1))
        // put (y - a^n)>>(nBitSizeBUpperBound)*(n-1)) in pTop (note we don't need y-a^n after this)
        nTopSize                                  = CBigIntegerHelper::ShiftRightInPlace(nPowerSizeLarge, ((n-1)*nBitSizeBUpperBound)%_DIGIT_SIZE_IN_BITS, ((n-1)*nBitSizeBUpperBound)/_DIGIT_SIZE_IN_BITS, pTop);
        // put a>>nBitSizeBUpperBound in pWorkspace -- a+e
        nBottomSize                               = CBigIntegerHelper::ShiftXRight(nASize, nBitSizeBUpperBound%_DIGIT_SIZE_IN_BITS, nBitSizeBUpperBound/_DIGIT_SIZE_IN_BITS, pA, pWorkspace);
        pWorkspace[nBottomSize]                   = 0; // overflow guard
        // put a>>nBitSizeBUpperBound + 2 in pWorkspace -- the "x" value (+1 for round up)
        i                                         = 0;
        nTop                                      = 2;
        do
        {
            nTop            += pWorkspace[i];
            pWorkspace[i++] =  nTop;
            nTop            =  nTop>>_DIGIT_SIZE_IN_BITS;
        }
        while(nTop);
        if (pWorkspace[nBottomSize]) nBottomSize++;
        // put (a+e)^(n-1) (x^(n-1)) in pBottom
        Power(nBottomSize, nPowerSizeSmall, n-1, pWorkspace, pBottom, pWorkspace+nBottomSize);
        // n*(a+e)^(n-1) in place
        nBottom = 0; // use for carry
        for(i=0; i<nPowerSizeSmall; i++)
        {
            nBottom    += ((DOUBLEDIGIT) n)*pBottom[i];
            pBottom[i] =  nBottom;
            nBottom    =  nBottom>>_DIGIT_SIZE_IN_BITS;
        }
        pBottom[i]      =  nBottom;
        nPowerSizeSmall += (0<nBottom);
        // (y - a^n)/(n*(a+e)^n-1)
        // No need to use extreme precision -- a 44 bit number divided by a 40 bit number can likely be pruned down to a 10 bit divided by a 6
        // bit without affecting the final result, since division truncates anyway.  DEBUG RESOLVE TODO!
#if _CollectDetailedTimingData
        dwTimestamp = s_Timer.GetMicroseconds();
        DivideBackend(nTopSize, nPowerSizeSmall, nPowerSizeSmall, nBottomSize, pTop, pBottom, pWorkspace, dwTimestamp, pWorkspace + nTopSize - nPowerSizeSmall + 1);
#else
        DivideBackend(nTopSize, nPowerSizeSmall, nPowerSizeSmall, nBottomSize, pTop, pBottom, pWorkspace, pWorkspace+nTopSize-nPowerSizeSmall+1);
#endif
        if(0==nPowerSizeSmall)
        {
            // end of the line -- this approximation scheme has reached its limit
            // BUT: value might still be too small!
            // At this point, the possible addition B is pretty small -- on the order of 8 bits or less (in all cases I've noticed).
            // One way to finish would be to use Newton.  Another to just do a bit-by-bit add -- can we add 2^7?  2^6?  Etc.
            // Turns out, the latter method is faster -- a lot faster.
            // We know that the amount to add has AT MOST nBitSizeBUpperBound bits, so that gives us our starting point
            // try binary search
#if _DEBUG
            if(nBitSizeBUpperBound <= _DIGIT_SIZE_IN_BITS && !s_bForceBigAddForValidatingNthRoot)
#else
            if(nBitSizeBUpperBound <= _DIGIT_SIZE_IN_BITS)
#endif
            {
                // The biggest nBitSizeBUpperBound value I've seen is 15 (using 32-bit DIGITs; haven't looked at 16-bit ones)
                // so this will likely always hold -- but it might not
                DOUBLEDIGIT nAdd = 1<<(nBitSizeBUpperBound-1);
                do
                {
                    // check if we can add nAdd to the root
                    nTop = nAdd;
                    i    = 0;
                    do
                    {
                        nTop    += pA[i];
                        pA[i++] =  nTop;
                        nTop    =  nTop>>_DIGIT_SIZE_IN_BITS;
                    }
                    while(nTop);
                    if (pA[nASize]) nASize++;
                    // validate
                    Power(nASize, nPowerSizeLarge, n, pA, pTop, pWorkspace);
                    int nCompare = CBigInteger::CompareUnsigned(nPowerSizeLarge, nYSize, pTop, pY);
                    if (1 == nCompare)
                    {
                        // doesn't fit; take it off again
                        nTop = nAdd;
                        i    = 0;
                        do
                        {
                            nBottom = pA[i];
                            pA[i]   = nBottom - nTop;
                            nTop    = (nBottom<nTop);
                        }
                        while(nTop);
                        if(0 == pA[nASize-1]) nASize--;
                    }
                    else if (0 == nCompare)
                    {
                        // exact fit
                        break;
                    }
                    nAdd = nAdd>>1;
                }
                while(nAdd);
            }
            else
            {
                // well who'd'a thunk it -- a whopping big uper bound on B!
                CBigInteger nAdd("1");
                nAdd.ShiftLeft(nBitSizeBUpperBound - 1);
                do
                {
                    // check if we can add nAdd to the root
                    nASize = Add(nASize, nAdd.GetSize(), pA, nAdd.GetValue(), pA);
                    // validate
                    Power(nASize, nPowerSizeLarge, n, pA, pTop, pWorkspace);
                    int nCompare = CBigInteger::CompareUnsigned(nPowerSizeLarge, nYSize, pTop, pY);
                    if (1 == nCompare)
                    {
                        // doesn't fit; take it off again
                        nASize = Subtract(nASize, nAdd.GetSize(), pA, nAdd.GetValue(), pA);
                    }
                    else if (0 == nCompare)
                    {
                        // exact fit
                        break;
                    }
                    nAdd.ShiftRight(1);
                }
                while(!nAdd.IsZero());
            }
            break;
        }
        // update a: a += b
        nTop = 0;
        for(i=0; i<nPowerSizeSmall; i++)
        {
            nTop  = (nTop + pA[i]) + pWorkspace[i];
            pA[i] = nTop;
            nTop  = nTop>>_DIGIT_SIZE_IN_BITS;
        }
        while (nTop)
        {
            nTop    = nTop + pA[i];
            pA[i++] = nTop;
            nTop    = nTop>>_DIGIT_SIZE_IN_BITS;
        }
        //if (0 < pA[nASize]) // shouldn't ever happen
        //{
        //    printf("oops\n");
        //}
        nASize += (0<pA[nASize]);
    }
    while(true);
}

#if(16==_DIGIT_SIZE_IN_BITS)
const unsigned int c_nBaseNumberSize = 5;
const DIGIT        c_nBaseNumber     = 10000;      // ten thousand -- largest power of 10 that fits in 16 bits
#else
const unsigned int c_nBaseNumberSize = 10;
const DIGIT        c_nBaseNumber     = 1000000000; // one BILLION -- largest power of 10 that fits in 32 bits
#endif

// helper function: print a single DIGIT.  Assumed to be at most c_nBaseNumber
void PrintBase10ToString(DIGIT n, char *&s)
{
    *--s = (n%10) + '0';
    n /= 10;
    *--s = (n%10) + '0';
    n /= 10;
    *--s = (n%10) + '0';
    n /= 10;
    *--s = (n%10) + '0';
#if(32==_DIGIT_SIZE_IN_BITS)
    n /= 10;
    *--s = (n%10) + '0';
    n /= 10;
    *--s = (n%10) + '0';
    n /= 10;
    *--s = (n%10) + '0';
    n /= 10;
    *--s = (n%10) + '0';
    n /= 10;
    *--s = (n%10) + '0';
#endif
}

// to convert to base 10:
// find the smallest squaring of c_nBaseNumber that is at least as large as half the size of the number passed
// divide by that number.  Mod contains right "half" to print; div contains "left"
// Repeat on left and right halves.  Note that this is a destructive function! -- destroys original number
void CUnsignedArithmeticHelper::PrintPiecesBase10(DIGIT **ppnPowersOfBase, size_t *pnPowerSizes, int nDepth, size_t nNumberDigits, DIGIT *pNum, char *&s, DIGIT *pWork)
{
    size_t nRemainderSize;
    if(-1==nDepth)
    {
        if (0 < nNumberDigits)
        {
            // base case
            if (1 == nNumberDigits)
            {
                PrintBase10ToString((*pNum)%c_nBaseNumber, s);
                PrintBase10ToString((*pNum)/c_nBaseNumber, s);
            }
            else
            {
                // 2 DIGITs, and the number is less than c_nBaseNumber*c_nBaseNumber
                DOUBLEDIGIT x = *((DOUBLEDIGIT*)pNum);
                PrintBase10ToString(x%c_nBaseNumber, s);
                PrintBase10ToString(x/c_nBaseNumber, s);
            }
        }
    }
    else if(nNumberDigits < pnPowerSizes[nDepth])
    {
        // power too small for the number -- can happen if the number is just a little larger than the power size
        PrintPiecesBase10(ppnPowersOfBase, pnPowerSizes, nDepth-1, nNumberDigits, pNum, s, pWork);
    }
    else
    {
        // main path.  Divide by power; print the two halves
        CUnsignedArithmeticHelper::Divide(nNumberDigits, pnPowerSizes[nDepth], nNumberDigits, nRemainderSize, pNum, ppnPowersOfBase[nDepth], pWork, pWork+nNumberDigits-pnPowerSizes[nDepth]+1);
        nDepth--;
        PrintPiecesBase10(ppnPowersOfBase, pnPowerSizes, nDepth, nRemainderSize, pNum, s, pWork+nNumberDigits);
        PrintPiecesBase10(ppnPowersOfBase, pnPowerSizes, nDepth, nNumberDigits, pWork, s, pWork+nNumberDigits);
    }
}

void CUnsignedArithmeticHelper::PrintNumberToBase10(const CBigInteger &nX, char *&s, DIGIT *pWork)
{
    DIGIT *pnPowersOf10[sizeof(size_t)*8]; // certainly more than needed
    size_t pnPowerSizes[sizeof(size_t)*8];
    *--s = '\0';
    if(1==nX.GetSize())
    {
        PrintBase10ToString(nX.m_pnValue[0]%c_nBaseNumber, s);
        PrintBase10ToString(nX.m_pnValue[0]/c_nBaseNumber, s);
    }
    else
    {
        // set up the powers of 10 needed
        size_t      nSize     = 1;
        const DIGIT *pCurrent = &c_nBaseNumber;
        DIGIT       *pNext    = pWork;
        int         nDepth    = -1;
        do
        {
            Square(nSize, pCurrent, pNext, pNext+nSize+nSize);
            nSize = nSize + nSize;
            if(0==pNext[nSize-1]) nSize--;
            pnPowersOf10[++nDepth] = pNext;
            pnPowerSizes[nDepth]   = nSize;
            pCurrent               = pNext;
            pNext                  = pNext + nSize;
        }
        while(nSize <= nX.GetSize()/2);
        PrintPiecesBase10(pnPowersOf10, pnPowerSizes, nDepth, nX.GetSize(), nX.GetValue(), s, pNext);
    }
    // get rid of leading 0s.  Note that we are guaranteed that the number is not ALL 0s, so no further checks needed
    while ('0' == *s) s++;
    // sign, if necessary
    if (nX.IsNegative()) *--s = '-';
}

void CUnsignedArithmeticHelper::PrintNumberToBase10(const CBigInteger &nX, DIGIT *pWork, FILE *f)
{
    char *s;
    if (nX.IsZero())
    {
        // special case
        fprintf(f, "0\n");
        return;
    }
    // set up the string to print.  Note we know that there WILL be at least one nonzero digit!
    s     = ((char *) pWork) + (nX.GetSize()+2)*c_nBaseNumberSize + 2; // s points to the END of the string to print.  Give enough space for all the digits (including lead overflow 0s), plus sign and trailing null character
    pWork = (DIGIT *) (s+1);
    // convert to a base-10 representation; put in a string
    PrintNumberToBase10(nX, s, pWork);
    // print to file
    fprintf_s(f, "%s\n", s);
}

size_t CUnsignedArithmeticHelper::PrintToBase10StringLength(size_t nDigits)
{
    return (nDigits + 2)*c_nBaseNumberSize + 2; // +2: - sign, if any, plus closing '\0' character
}

size_t CUnsignedArithmeticHelper::PrintToBase10MemoryNeeds(size_t nDigits)
{
    size_t nMemory;
    nMemory =  PrintToBase10StringLength(nDigits + sizeof(DIGIT) -1)/sizeof(DIGIT); // memory needed for the intermediate string
    nMemory += 4*nDigits; // for the powers of 10 -- overestimate!
    nMemory += nDigits + DivisionMemoryNeeds(2*nDigits, nDigits);
    return nMemory;
}