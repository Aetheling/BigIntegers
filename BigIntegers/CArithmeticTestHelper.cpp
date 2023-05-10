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
#ifdef _USESMALLDIGITS
    // values found to be reasonable
    c_nBuildBlockSizePre                         = 8388608; // effectively ignored
    c_nBuildBlockSizePost                        = 16777216; // ignored
    c_pnMultiplicationThresholds[eBasicMultiply] = 15;
    c_pnMultiplicationThresholds[e3By2]          = 43;
    c_pnMultiplicationThresholds[e5By3]          = 58;
    c_pnMultiplicationThresholds[e7By4]          = 423327;
    c_pnMultiplicationThresholds[e2NByN]         = 5633;
	c_pn2NByNBreakpoints[0]                      = 91; // below use 5 pieces; above, 6
	c_pn2NByNBreakpoints[1]                      = 2639; // below use 6 pieces; above, 7
	c_pn2NByNBreakpoints[2]                      = 4366; // below use 7 pieces; above, 8
	c_pn2NByNBreakpoints[3]                      = 6920; // below use 8 pieces; above, 9
	c_pn2NByNBreakpoints[4]                      = 18377; // below use 9 pieces; above, 10
	c_pn2NByNBreakpoints[5]                      = 26457; // below use 10 pieces; above, 11
	c_pn2NByNBreakpoints[6]                      = 239783; // below use 11 pieces; above, 12
    c_nDivideThresholdSmall                      = 16;
    c_nDivideThresholdDiff                       = 4;
#else
    // values found to be reasonable
    c_nBuildBlockSizePre                         = 16777216;
    c_nBuildBlockSizePost                        = 16777216; // ignored
    c_pnMultiplicationThresholds[eBasicMultiply] = 38;// 15;
    c_pnMultiplicationThresholds[e3By2]          = 83; //35;
    c_pnMultiplicationThresholds[e5By3]          = 84; //43;
    c_pnMultiplicationThresholds[e7By4]          = 115; //111;
    c_pnMultiplicationThresholds[e9By5]          = 1090018; //130143;
    c_pnMultiplicationThresholds[e2NByN]         = 12683; //12356;
	c_pn2NByNBreakpoints[0]                      = 14481; //142; // below use 5 pieces; above, 6
	c_pn2NByNBreakpoints[1]                      = 34001; //211; // below use 6 pieces; above, 7
	c_pn2NByNBreakpoints[2]                      = 135915; //568; // below use 7 pieces; above, 8
	c_pn2NByNBreakpoints[3]                      = 543863; //3564; // below use 8 pieces; above, 9
	c_pn2NByNBreakpoints[4]                      = 779232; //10375; // below use 9 pieces; above, 10
	c_pn2NByNBreakpoints[5]                      = 1765454; //16267; // below use 10 pieces; above, 11
	c_pn2NByNBreakpoints[6]                      = 1917176; //90534; // below use 11 pieces; above, 12
    c_nDivideThresholdSmall                      = 12;
    c_nDivideThresholdDiff                       = 4;
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
    c_pnMultiplicationThresholds[e2NByN]         = (bForceNo2NByN) ? 100000000 : 75;
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