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
    void FindBestMultiplicationThresholds();
	void Test2NByNBlockSizes(); // should only run in release.  VERY long test -- get proper cache parameter values
	                            // Really SHOULD do this as part of FindBestThresholds(), but it just takes too long
	                            // to run that many times.  Also largely irrelevant -- by the time the multiplication
                                // is big enough for doing it in chunks to help, using FFT is faster still
    void FindBestDivideThresholds(); // best switch points between recursive and basic divide algorithms
    //void FindBestStrassenThreshold();
private: // functions
    // Determines where to set the passed threshold for multiply: starting at the low point, tries larger and larger
    // multiplies until the point where it is faster to be above the threshold than below.  If the limit is passed,
    // it stops there and sets the threshold to limit+1.  If the output file is not NULL, it will print intermediate
    // results to it.
    // If binary search only is set, it skips the refinement step and just sets the threshold at the result of the
    // binary search
    void ComputeThreshold(unsigned int       *pnThreshold,
                          unsigned int       dwSize,
                          bool               bTestingSquare,
                          CBigIntegerForTest &nX,
                          CBigIntegerForTest &nY,
                          CBigIntegerForTest &nZ,
                          CWorkspace         &cWork,
                          DWORD              dwMinMillisecondsPerTest,
                          FILE               *pOutput,
                          bool               bBinarySearchOnly = false)
    {
        ComputeThreshold(pnThreshold, dwSize, bTestingSquare, nX, nY, nZ, cWork, dwMinMillisecondsPerTest, pOutput, bBinarySearchOnly, NULL, 0);
    }
    // pnSecondaryThreshold: When computing the breakpoints within the 2NByN algorithm (e.g. where we should switch between
    // using 7 pieces and 8), we have NOT determined whether using 2NByN is a good idea in the first place: we need to set
    // up its parameters before we can do that.  So we need to make sure that any subproblems generated by the test don't
    // use 2NByN
    void ComputeThreshold(unsigned int       *pnThreshold,
                          unsigned int       dwSize,
                          bool               bTestingSquare,
                          CBigIntegerForTest &nX,
                          CBigIntegerForTest &nY,
                          CBigIntegerForTest &nZ,
                          CWorkspace         &cWork,
                          DWORD              dwMinMillisecondsPerTest,
                          FILE               *pOutput,
                          bool               bBinarySearchOnly,
                          unsigned int       *pnSecondaryThreshold,
                          size_t             nLim);
    void Resize(DWORD dwSize, CWorkspace &cWork, CBigIntegerForTest &nX, CBigIntegerForTest &nY, CBigIntegerForTest &nZ, bool bTestingSquare);
//	void GetSimpleThreshold(EMultiplyAlgorithm eThresholdToTest, CWorkspace &Work, bool bTestingSquare, FILE *pOutput, size_t nLim=0);
//	void GetFFTThreshold(bool bTestingSquare); // find threshold above which to use FFT algorithm
    DWORD64 GetIterations(DWORD dwSize, CWorkspace &cWork, CBigIntegerForTest &nX, CBigIntegerForTest &nY, CBigIntegerForTest &nZ, DWORD dwMinMillisecondsPerTest, bool bTestingSquare);
    void  MultiplyMultipleTimes(DWORD64 dwNumMultiplies, DWORD &dwTimeTaken, CWorkspace &cWork, CBigIntegerForTest &nX, CBigIntegerForTest &nY, CBigIntegerForTest &nZ, bool bTestingSquare);
};

// Take the package for a test drive -- how long do various operations take?
// Should only be used in retail builds!
class CArithmeticPerformanceTester : public CArithmeticTestHelper
{
public:  // functions
	void SpeedCheckBasicMultiply();
    void CompareBasicMultiplicationToLongShortMultiplication();
    void CompareBasicMultiplicationToStripedMultiplication();
	void TestMultiplyTimes();
	void CompareMultiplicationAlgorithms();
    void CompareBaseMultiplicationToFFT();
    void CompareDivideTimes();
    void GCDTimes();
    void PowerModulusMontgomeryVsStandard();
    void SquareRootTimes();
    void MatrixMultiplyTimes();
    void FFTTimes();
private: // functions
    void SaveMultiplicationThresholds();
    void RestoreMultiplicationThresholds();
private: // data
    unsigned int m_pnTemp2NByNBreakpoints[c_n2NBynSizeBreakpoints];
    unsigned int m_pnTemp2NByNSquareBreakpoints[c_n2NBynSizeBreakpoints];
    unsigned int m_pnTempMultiplicationThresholds[eNumMultiplyAlgorithms - 1];
    unsigned int m_pnTempSquareThresholds[eNumMultiplyAlgorithms - 1];
};