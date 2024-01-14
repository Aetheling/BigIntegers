#pragma once
#include "TestConstants.h"
#include "ArithmeticBox.h"
#include "CUnsignedArithmeticHelper.h"
#include "CArithmeticTestHelper.h"
#include "CBigIntegerVectors.h"
#include "CBigIntegerMatrix.h"
#include "SSystemData.h"
#include "math.h"
#pragma warning(disable:4267)    // conversion from 'size_t' to 'unsigned int' -- possible loss of data

void CArithmeticTestHelper::ResetThresholdsForOptimization()
{
#ifdef _UsingVariableThresholdsForTest
#if(16==_DIGIT_SIZE_IN_BITS)
    // values found to be reasonable
    c_nBuildBlockSizePre                         = 8388608; // effectively ignored
    c_nBuildBlockSizePost                        = 16777216; // ignored
    c_pnMultiplicationThresholds[eBasicMultiply] = 52;
    c_pnMultiplicationThresholds[e3By2]          = 152;
    c_pnMultiplicationThresholds[e5By3]          = 152;
    c_pnMultiplicationThresholds[e7By4]          = 39211;
    c_pnMultiplicationThresholds[e2NByN]         = 0;
    c_pn2NByNBreakpoints[0]                      = 101233;   // below use 5 pieces; above, 6
    c_pn2NByNBreakpoints[1]                      = 182042;   // below use 6 pieces; above, 7
    c_pn2NByNBreakpoints[2]                      = 201275;   // below use 7 pieces; above, 8
    c_pn2NByNBreakpoints[3]                      = 231567;   // below use 8 pieces; above, 9
    c_pn2NByNBreakpoints[4]                      = 1692095;  // below use 9 pieces; above, 10
    c_pn2NByNBreakpoints[5]                      = 2254277;  // below use 10 pieces; above, 11
    c_pn2NByNBreakpoints[6]                      = 33154301; // below use 11 pieces; above, 12
    c_pnSquareThresholds[eBasicMultiply]         = 34;
    c_pnSquareThresholds[e3By2]                  = 154;
    c_pnSquareThresholds[e5By3]                  = 154;
    c_pnSquareThresholds[e7By4]                  = 18956;
    c_pnSquareThresholds[e2NByN]                 = 0;
    c_pn2NByNSquareBreakpoints[0]                = 9947;
    c_pn2NByNSquareBreakpoints[1]                = 12563;
    c_pn2NByNSquareBreakpoints[2]                = 12597;
    c_pn2NByNSquareBreakpoints[3]                = 44304;
    c_pn2NByNSquareBreakpoints[4]                = 89971;
    c_pn2NByNSquareBreakpoints[5]                = 275688;
    c_pn2NByNSquareBreakpoints[6]                = 2000000000;
    c_nDivideThresholdSmall                      = 7;
    c_nDivideThresholdDiff                       = 4;
#else
    // values found to be reasonable
#if _USEAVX
    c_nBuildBlockSizePre = 8192;
    c_nBuildBlockSizePost = 32768; // ignored
    c_pnMultiplicationThresholds[eBasicMultiply] = 130;
    c_pnMultiplicationThresholds[e3By2]          = 149;
    c_pnMultiplicationThresholds[e5By3]          = 154;
    c_pnMultiplicationThresholds[e7By4]          = 250;
    c_pnMultiplicationThresholds[e9By5]          = 54494;
    c_pnMultiplicationThresholds[e2NByN]         = 0;
    c_pnSquareThresholds[eBasicMultiply]         = 53;
    c_pnSquareThresholds[e3By2]                  = 211;
    c_pnSquareThresholds[e5By3]                  = 217;
    c_pnSquareThresholds[e7By4]                  = 337;
    c_pnSquareThresholds[e9By5]                  = 14963;
    c_pnSquareThresholds[e2NByN]                 = 0;
	c_pn2NByNBreakpoints[0]                      = 967257;    // below use 5 pieces; above, 6
	c_pn2NByNBreakpoints[1]                      = 1338767;    // below use 6 pieces; above, 7
	c_pn2NByNBreakpoints[2]                      = 1338767;   // below use 7 pieces; above, 8
	c_pn2NByNBreakpoints[3]                      = 1338767;   // below use 8 pieces; above, 9
	c_pn2NByNBreakpoints[4]                      = 1404417;   // below use 9 pieces; above, 10
	c_pn2NByNBreakpoints[5]                      = 1404417;  // below use 10 pieces; above, 11
	c_pn2NByNBreakpoints[6]                      = 1577792;  // below use 11 pieces; above, 12
    c_pn2NByNSquareBreakpoints[0]                = 16156;
    c_pn2NByNSquareBreakpoints[1]                = 89155;
    c_pn2NByNSquareBreakpoints[2]                = 582464;
    c_pn2NByNSquareBreakpoints[3]                = 582464;
    c_pn2NByNSquareBreakpoints[4]                = 957196;
    c_pn2NByNSquareBreakpoints[5]                = 957196;
    c_pn2NByNSquareBreakpoints[6]                = 8727776;
    c_nDivideThresholdSmall                      = 11;       // at least 4 to insure correctness; 16 is heuristically good
    c_nDivideThresholdDiff                       = 4;        // at least 4 to insure correctness; 4 is heuristically good
#else
    c_nBuildBlockSizePre                         = 16777216;
    c_nBuildBlockSizePost                        = 16777216; // ignored
    c_pnMultiplicationThresholds[eBasicMultiply] = 54;
    c_pnMultiplicationThresholds[e3By2]          = 100;
    c_pnMultiplicationThresholds[e5By3]          = 100;
    c_pnMultiplicationThresholds[e7By4]          = 160;
    c_pnMultiplicationThresholds[e9By5]          = 40789;
    c_pnMultiplicationThresholds[e2NByN]         = 0;
    c_pnSquareThresholds[eBasicMultiply]         = 26;
    c_pnSquareThresholds[e3By2]                  = 186;
    c_pnSquareThresholds[e5By3]                  = 186;
    c_pnSquareThresholds[e7By4]                  = 190;
    c_pnSquareThresholds[e9By5]                  = 11573;
    c_pnSquareThresholds[e2NByN]                 = 0;
	c_pn2NByNBreakpoints[0]                      = 160;    // below use 5 pieces; above, 6
	c_pn2NByNBreakpoints[1]                      = 644;    // below use 6 pieces; above, 7
	c_pn2NByNBreakpoints[2]                      = 3499;   // below use 7 pieces; above, 8
	c_pn2NByNBreakpoints[3]                      = 3500;   // below use 8 pieces; above, 9
	c_pn2NByNBreakpoints[4]                      = 13545;   // below use 9 pieces; above, 10
	c_pn2NByNBreakpoints[5]                      = 13546;  // below use 10 pieces; above, 11
	c_pn2NByNBreakpoints[6]                      = 19471;  // below use 11 pieces; above, 12
    c_pn2NByNSquareBreakpoints[0]                = 346;
    c_pn2NByNSquareBreakpoints[1]                = 2433;
    c_pn2NByNSquareBreakpoints[2]                = 17964;
    c_pn2NByNSquareBreakpoints[3]                = 23264;
    c_pn2NByNSquareBreakpoints[4]                = 28659;
    c_pn2NByNSquareBreakpoints[5]                = 28660;
    c_pn2NByNSquareBreakpoints[6]                = 28661;
    c_nDivideThresholdSmall                      = 12;
    c_nDivideThresholdDiff                       = 4;
#endif
#endif
#endif
}

void CArithmeticTestHelper::ResetThresholdsForTest(bool bForceNo2NByN)
{
#ifdef _UsingVariableThresholdsForTest
    // values NOT chosen for optimization!  These are values useful for correctness testing
    c_nBuildBlockSizePre                         = 2;
    c_nBuildBlockSizePost                        = 3;
    c_pnMultiplicationThresholds[eBasicMultiply] = 15;
    c_pnMultiplicationThresholds[e3By2]          = 30;
    c_pnMultiplicationThresholds[e5By3]          = 45;
    c_pnMultiplicationThresholds[e7By4]          = (bForceNo2NByN) ? 100000000 : 60;
#if(16==_DIGIT_SIZE_IN_BITS)
    c_pnMultiplicationThresholds[e2NByN]         = (bForceNo2NByN) ? 100000000 : 75;
#else
    c_pnMultiplicationThresholds[e9By5]          = 75;
    c_pnMultiplicationThresholds[e2NByN]         = (bForceNo2NByN) ? 100000000 : 90;
#endif
    c_pnSquareThresholds[eBasicMultiply]         = 15;
    c_pnSquareThresholds[e3By2]                  = 30;
    c_pnSquareThresholds[e5By3]                  = 45;
    c_pnSquareThresholds[e7By4]                  = (bForceNo2NByN) ? 100000000 : 60;
#if(16==_DIGIT_SIZE_IN_BITS)
    c_pnSquareThresholds[e2NByN]                 = (bForceNo2NByN) ? 100000000 : 75;
#else
    c_pnSquareThresholds[e9By5]                  = 75;
    c_pnSquareThresholds[e2NByN]                 = (bForceNo2NByN) ? 100000000 : 90;
#endif
	c_pn2NByNBreakpoints[0]                      = 100; // below use 5 pieces; above, 6
	c_pn2NByNBreakpoints[1]                      = 200; // below use 6 pieces; above, 7
	c_pn2NByNBreakpoints[2]                      = 300; // below use 7 pieces; above, 8
	c_pn2NByNBreakpoints[3]                      = 400; // below use 8 pieces; above, 9
	c_pn2NByNBreakpoints[4]                      = 500; // below use 9 pieces; above, 10
    c_nDivideThresholdSmall                      = 4;
    c_nDivideThresholdDiff                       = 4;
#endif
}

CBigInteger *CArithmeticTestHelper::NewBigIntegerOnePlus2ToN(size_t n)
{
    CBigInteger *pBig = new CBigInteger();
    pBig->Reserve(n+1);
    pBig->GetValue()[0] = 1;
    for(size_t i=1;i<n;i++)
    {
        pBig->GetValue()[i] = 0;
    }
    pBig->GetValue()[n] = 1;
    pBig->SetSize(n+1);
    return pBig;
}