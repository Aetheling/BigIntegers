#pragma once
#undef _REGISTER_BLOCK_SIZE
#define _REGISTER_BLOCK_SIZE 6
#define _TestingBasicMultiplyDirectly
#include "BasicMultiply.cpp"
#undef _REGISTER_BLOCK_SIZE
#define _REGISTER_BLOCK_SIZE _TEMP
#undef _TEMP
#undef _TestingBasicMultiplyDirectly
#include "ArithmeticBox.h"
#include "CArithmeticTestHelper.h"

#if(_CollectDetailedTimingData)
void CArithmeticTestHelper::BasicMultiplyReg6(size_t       nXSize,
                                              size_t       nYSize,
                                              const DIGIT  *pX,
                                              const DIGIT  *pY,
                                              DIGIT        *pZ,
                                              bool         bAddInitialZValueToProduct,
                                              DWORD64      &dwTimestamp)
{
	BasicUnsignedMultiplyForTest6(nXSize,nYSize,pX,pY,pZ,bAddInitialZValueToProduct,dwTimestamp);
}
#else
void CArithmeticTestHelper::BasicMultiplyReg6(size_t       nXSize,
                                              size_t       nYSize,
                                              const DIGIT  *pX,
                                              const DIGIT  *pY,
                                              DIGIT        *pZ,
                                              bool         bAddInitialZValueToProduct)
{
	BasicUnsignedMultiplyForTest6(nXSize,nYSize,pX,pY,pZ,bAddInitialZValueToProduct);
}
#endif