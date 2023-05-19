// class used for functional tests of big integer arithmetic
#include "CUnsignedArithmeticHelper.h"
#include "Timer.h"
#include "CBigIntegerForTest.h"

class CArithmeticTestHelper : public CUnsignedArithmeticHelper
{
public:  // functions
    // creates a new big integer with value 1+2^n, where n is given in DIGITs.
    // Used extensively for testing TestModBy2NPlus1
    CBigInteger *NewBigIntegerOnePlus2ToN(size_t n);
    void ResetThresholdsForTest(bool bForceNo2NByN=false);  // correctness testing
	void ResetThresholdsForOptimization(); // good parameter values for performance
	// wrappers for the basic multiply for the 6 allowed register block sizes
    static void BasicMultiplyReg1(size_t       nXSize,
                                  size_t       nYSize,
                                  const DIGIT  *pX,
                                  const DIGIT  *pY,
                                  DIGIT        *pZ,
                                  bool         bAddInitialZValueToProduct);
    static void BasicMultiplyReg2(size_t       nXSize,
                                  size_t       nYSize,
                                  const DIGIT  *pX,
                                  const DIGIT  *pY,
                                  DIGIT        *pZ,
                                  bool         bAddInitialZValueToProduct);
    static void BasicMultiplyReg3(size_t       nXSize,
                                  size_t       nYSize,
                                  const DIGIT  *pX,
                                  const DIGIT  *pY,
                                  DIGIT        *pZ,
                                  bool         bAddInitialZValueToProduct);
    static void BasicMultiplyReg4(size_t       nXSize,
                                  size_t       nYSize,
                                  const DIGIT  *pX,
                                  const DIGIT  *pY,
                                  DIGIT        *pZ,
                                  bool         bAddInitialZValueToProduct);
    static void BasicMultiplyReg5(size_t       nXSize,
                                  size_t       nYSize,
                                  const DIGIT  *pX,
                                  const DIGIT  *pY,
                                  DIGIT        *pZ,
                                  bool         bAddInitialZValueToProduct);
    static void BasicMultiplyReg6(size_t       nXSize,
                                  size_t       nYSize,
                                  const DIGIT  *pX,
                                  const DIGIT  *pY,
                                  DIGIT        *pZ,
                                  bool         bAddInitialZValueToProduct);
	bool TestBasicMultiplyReg1(bool bVerbose);
	bool TestBasicMultiplyReg2(bool bVerbose);
	bool TestBasicMultiplyReg3(bool bVerbose);
	bool TestBasicMultiplyReg4(bool bVerbose);
	bool TestBasicMultiplyReg5(bool bVerbose);
	bool TestBasicMultiplyReg6(bool bVerbose);
};

class CArithmeticCorrectnessTester : public CArithmeticTestHelper
{
public:  // functions
    // Tests basic BigInteger functionality, plus "Compare" from the ArithmeticBox
    bool TestBigInteger(bool bVerbose = false);
    bool TestAddSubtract(bool bVerbose = false);
    bool TestShortLongMultiply(bool bVerbose = false);
    bool TestBasicMultiply(bool bVerbose = false);
    bool TestRecursiveMultiply(bool bVerbose = false);
    bool TestMultiplyAdd(bool bVerbose = false);
    bool TestDivide(bool bVerbose = false);
    bool TestBigVector(bool bVerbose = false);
    bool TestBigGCD(bool bVerbose = false);
    bool TestBigMatrix(bool bVerbose = false);
    bool Test2NByNMultiply(bool bVerbose = false);
    bool TestModBy2NPlus1(bool bVerbose = false);
    bool TestMult2toMmodOnePlus2toN(bool bVerbose = false);
    bool TestFFT(bool bVerbose = false);
    bool TestFFTMult(bool bVerbose = false); // VERY long test!!!
    bool TestSquare();
    bool TestPowerModulus(bool bVerbose = false); // Another LONG test.  Should run using 16-bit DIGITs as
	                                              // well as 32-bit DIGITs if you plan to use 32-bit DIGITs
	                                              // to make sure multi-digit powers function.  (Just too
	                                              // slow to validate multi-DIGIT powers with 32-bit DIGITs!)
    bool TestModularBox();
    bool TestMontgomeryFormat();
    bool TestMontgomeryMultiply();
    bool TestMontgomeryPowerModulus();
    bool TestSquareRoot();
};

// class to determine where the various threshholds and parameters should be
// set for best performance.  Should only be used in retail builds!
class CArithmeticTuner : public CArithmeticTestHelper
{
public:  // functions
	void FindBestThresholds(); // growth parameters, break points between various algorithms
	void Test2NByNBlockSizes(); // should only run in release.  VERY long test -- get proper cache parameter values
	                            // Really SHOULD do this as part of FindBestThresholds(), but it just takes too long
	                            // to run that many times
    void FindBestDivideThresholds(); // best switch points between recursive and basic divide algorithms
    //void FindBestStrassenThreshold();
private: // functions
	void Compute2NByNGrowthParameters();
	void GetSimpleThreshold(EMultiplyAlgorithm eThresholdToTest, CWorkspace &Work, FILE *pOutput);
	void GetFFTThreshold(); // find threshold above which to use FFT algorithm
};

// Take the package for a test drive -- how long do various operations take?
// Should only be used in retail builds!
class CArithmeticPerformanceTester : public CArithmeticTestHelper
{
public:  // functions
	void SpeedCheckBasicMultiply();
	void TestMultiplyTimes();
	void CompareMultiplicationAlgorithms();
    void CompareBaseMultiplicationToFFT();
    void CompareDivideTimes();
    void GCDTimes();
    void PowerModulusMontgomeryVsStandard();
    void SquareRootTimes();
    void MatrixMultiplyTimes();
};