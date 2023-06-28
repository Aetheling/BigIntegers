#pragma once
#include "Constants.h"
#include "CWorkspace.h"
#include "Timer.h"
// forward declarations
struct SSystemData;
//#define _UsingVariableThresholdsForTest 1 // don't want this in general -- make it a compile-time parameter, and separate test out into separate project

enum EMultiplyAlgorithm { eBasicMultiply = 0,
                          e3By2,
                          e5By3,
                          e7By4,
#if(32<=_DIGIT_SIZE_IN_BITS)
                          e9By5,
#endif
                          e2NByN,
                          eFFTMult, // not used as a threshold marker.  Purely here for naming purposes
                          eNumMultiplyAlgorithms };

enum EDivideComponents { eTotalDivideCalls, eDivideProcessTime, eDivideMultCallsTime, eBasicDivideTime, eTotalDivideTime, eNumDivideComponents };

enum ESquareRootComponents { eTotalSquareRootCalls,
                             eSquareRootProcessTime,
                             eSquareRootMultiplyTime,
                             eSquareRootNewtonProcessTime,
                             eSquareRootNewtonMultiplyTime,
                             eSquareRootNewtonDivideTime,
                             eSquareRootPartAProcessTime, // general square root
                             eSquareRootPartAMultiplyTime, // general square root
                             eSquareRootPartBProcessTime, // general square root
                             eSquareRootPartBMultiplyTime, // general square root
                             eSquareRootPartBDivideTime, // general square root
                             eTotalSquareRootTime,
                             eNumSquareRootComponents };

enum EPowerModulusComponents { eTotalPowerModulusCalls,
                               ePowerModulusProcessTime,
                               ePowerModulusMultiplyTime,
                               ePowerModulusDivideTime,
                               ePowerModulusTotalTime,
                               eNumPowerModulusComponents };

enum EGCDComponents { eTotalGCDCalls,
                      eGCDProcessTime,
                      eGCDMultiplyTime,
                      eGCDDivideTime,
                      eGCDTotalTime,
                      eNumGCDComponents };

enum ETimeMeasuredComponents { eMultiplicationMeasured, eDivideMeasured, eSQRTMeasured, ePowerModulusMeasured, eGCDMeasured, eNumMeasuredComponents };

class CUnsignedArithmeticHelper
{
    friend class CBigInteger;
// These functions are intended for internal use only.  They do
// not do any error checking for such things as whether the workspace
// passed is adequate, and they break the paradigm of what the underlying
// objects are, with one goal in mind: speed.  The front-end procedures
// do the necessary error checks.  For algorithm and other comments,
// see the .cpp file

    // times in microseconds
    // build time: time to construct the arguments for the multiplies
    // process time: time to use the multiplies to get the results
public:  // functions
    static void ReportAllTimingData();
    static void ReportMeasuredComponentTimingData(ETimeMeasuredComponents eComponent);
    /*static void ReportMultiplicationTimingData();
    static void ReportDivisionTimingData();
    static void ReportSquareRootTimingData();
    static void ReportGCDTimingData();
    static void ReportPowerModulusTimingData();*/
    static unsigned long long GetChunkProcessTime(bool bPre);
    static void ResetTimingData();
    // and one further operation on signed values...  *sigh*
    // Also used by Mult2NByN
    static void AddSigned(size_t       nXSize,
                          size_t       nYSize,
                          size_t       &nZSize,
                          const DIGIT  *pXValue,
                          const DIGIT  *pYValue,
                          DIGIT        *pZValue,
                          bool         bXNegative,
                          bool         bYNegative,
                          bool         &bZNegative);
    // returns the number of DIGITs needed in workspace memory
    // to do a multiplication of the given size.  Rounds UP
    // to the nearest multiple of 2.
    // If nSum is passed, it computes the memory needed for z = x*y+z.
    // Note that z is assumed to have the same sign as x*y!
    static size_t MultiplyMemoryNeeds(size_t nXSize, size_t nYSize, size_t nSum = 0);
    static size_t SquareMemoryNeeds(size_t nXSize, size_t nSum = 0);
    // Returns the amount of memory needed, in DIGITs, to divide a number of
    // size nNumeratorSize by one of size nDenominatorSize.  Rounds UP to the
    // nearest multiple of 2.
    static size_t DivisionMemoryNeeds(size_t nNumeratorSize, size_t nDenominatorSize);
    // memory needs for power-modulus: x^y mod z
    static size_t PowerModulusMemoryNeeds(size_t nXSize, size_t nYSize, size_t nZSize);
    // computes the memory needs of the GCD function, expressed in DIGITs and rounded
    // UP to the nearest multiple of 2.
    static size_t GCDMemoryNeeds(size_t n1, size_t n2, bool bComputingCoefficients);
    // Computes memory needed for FFT multiplication.  Seperate from MultiplyMemoryNeeds
    // for now.
    static size_t FFTMultiplyMemoryNeeds(size_t nXSize, size_t nYSize, bool bMultAdd);
    static size_t FFTSquareMemoryNeeds(size_t nXSize, bool bMultAdd);
    static size_t SquareRootMemoryNeeds(size_t nXSize);
    static void Multiply(size_t nXSize,
                         size_t nYSize,
                         DIGIT  *pnXValue,
                         DIGIT  *pnYValue,
                         DIGIT  *pnXTimesYValue,
                         DIGIT  *pnWorkspace);
    static void MultiplyAdd(size_t nXSize,
                            size_t nYSize,
                            size_t &nRunningSumSize,
                            DIGIT  *pnXValue,
                            DIGIT  *pnYValue,
                            DIGIT  *pnRunningSum,
                            DIGIT  *pnWorkspace);
    static void Square(size_t nXSize,
                       DIGIT  *pnXValue,
                       DIGIT  *pnXSquaredValue,
                       DIGIT  *pnWorkspace);
    // computes X/Y (stored in XDivYValue) and the remainder (stored in X) -- yes; this
    // *is* destructive!
    // Y is NOT destroyed, despite not being labeled as const; it is transiently adjusted
    // in some of the work, however.  It's value is restored before return.
    // Algorithm:	If the base and y are close in size, or
    //				the y value is small, it uses the basic algorithm
    //				you learned when you first learned long division.
    //				Otherwise, it uses a divide-and-conquer method:
    //				Consider dividing (w,x,y,z) by (a,b).
    //				We break this down into two parts: first,
    //				compute (w,x,0,0) divided by (a+1,0); call
    //				it (p1,p2,0).  Clearly (p1,p2,0) < (w,x,y,z)/(a,b).
    //				Further,
    //				(w,x,y,z)/(a,b) = (p1,p2,0) + ((w,x,y,z)-(p1,p2,0)*(a,b))/(a,b).
    //				The key here is to note that
    //				(w,x,y,z) - (p1,p2,0)*(a,b)                       =
    //				(w,x,y,z) - (p1,p2,0)*(a,0) - (p1,p2,0)*(0,b)     =
    //				(w,x,y,z) - (p1,p2,0)*(a,0) - (p1,p2,0)*(0,b) +
    //							(p1,p2,0)*(1,0) - (p1,p2,0)*(1,0)     =
    //				(w,x,y,z) - (p1,p2,0)*(a+1,0) - (p1,p2,0)*(0,b) -
    //							(p1,p2,0)*(1,0)                       <
    //				(p1,p2,0)
    //				In general, we can do the division by utilizing
    //				two half-size divisions, a multiplication, and linear
    //				ops; by doing this recursively, the assymptotic
    //				performance is that of the multiplications (which
    //				are superlinear).
    //				More specifically: to divide a (2d+n)-DIGIT number,
    //				let k = min(d,n).  The problem reduces to dividing
    //				a 2k-DIGIT number by a k-DIGIT number and a (2d+n-k)-DIGIT
    //				number by an n-DIGIT number
    static void Divide(size_t  nXSize,
                       size_t  nYSize,
                       size_t  &nXDivYSize,
                       size_t  &nRemainderSize,
                       DIGIT   *pXValue,
                       DIGIT   *pYValue,
                       DIGIT   *pXDivYValue,
                       DIGIT   *pWorkspace);
    // GCD: compute the greatest common divisor of X and Y.
    // Coefs: values a, b such that ax+by = GCD(x,y) (assumes
    // x, y are positive).
    // wrapper for computing the GCD: don't care about coefs
    static size_t GCD(size_t nXSize,
                      size_t nYSize,
                      DIGIT  *pXValue,
                      DIGIT  *pYValue,
                      DIGIT  *pGCDValue,
                      DIGIT  *pWorkspace);
    // wrapper for computing GCD: *do* care about those coefs.
    // note that this uses significantly more memory!
    // In case you only care about one of the coefs, passing
    // NULL for the one not desired will work -- and reduce
    // computation time somewhat (especially for large X, Y
    // values)
    static void GCD(size_t nXSize,
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
                    DIGIT  *pWorkspace);
	// Compute (x^y) mod z, where x, y, and z are all big unsigned integers.  It is assumed that
	// there is sufficient space in the result!  Also that the power Y is nonzero, for simplicity.
	// The prospective use of this function is for RSA encryption, which does a LOT of power-modulus operations.
	// It turns out that by timing the operation, it can be computed how many bits are set in the power, which
	// is supposed to be a private key, hence compromising the security of the encryption.  If the flag
	// bProtectAgainstTimingAttacks is set, a bit of extra work is done such that the total work done is
	// the same, regardless of how many bits in the power are actually set.
	static void PowerModulus(size_t      nXSize,
		                     size_t      nYSize,
							 size_t      nZSize,
							 size_t      &nPowerModulusSize,
							 const DIGIT *pnXValue,
							 const DIGIT *pnYValue,
							 DIGIT       *pnZValue,
							 DIGIT       *pnPowerModulus,
							 DIGIT       *pnWorkspace,
							 bool        bProtectAgainstTimingAttacks = false);
    // gives the position of the first (most significant) bit of the number passed
    static void GetLeadBit(size_t       nValSize,
                           const DIGIT  *pVal,
                           size_t       &nLeadDigit,
                           size_t       &nLeadBit);

    // when the modulus is odd, we use Montgomery form (see https://en.wikipedia.org/wiki/Montgomery_modular_multiplication) to do power modulus
    // N is the modulus; R is implicitly 2^<size in digits of N * bits in a digit> -- division by R just means dropping the last several digits;
    // clearly, N < R and 1 == GCD(R,N) -- R is a power of 2 and N is odd by assumption
    // nPrime in (0, R) chosen s.t. n*nPrime mod(R) == 1

    // pNPrimeValue, pRPrimeValue must have space for nNSize DIGITs
    static void GetMontgomeryParameters(size_t nNSize,
                                        size_t &nNPrimeSize,
                                        size_t &nRPrimeSize,
                                        DIGIT  *pNValue,
                                        DIGIT  *pNPrimeValue,
                                        DIGIT  *pRPrimeValue,
                                        DIGIT  *pWorkspace);
    // Performs  (x^y) mod modulus, putting the result in pnPowerModulus.  It is assumed that pnPowerModulus has enough space for 2*nModulusSize DIGITs.
    // Note modulus takes the place of N in MontgomeryMultiply.  Assumes the power is greater than 0!
    static void MontgomeryPowerModulus(size_t      nXSize,
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
							           bool        bProtectAgainstTimingAttacks = false);
    // same, but with the lead bit of the power precomputed
    static void MontgomeryPowerModulus(size_t      nXSize,
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
							           bool        bProtectAgainstTimingAttacks = false);
    // computes the largest value SquareRoot such that SquareRoot*SquareRoot <= X
    static void SQRT(size_t nXSize, size_t &nRootSize, DIGIT *pnX, DIGIT *pnSquareRoot, DIGIT *pWorkspace);


protected: // functions
    static const char *GetMultiplicationAlgorithmName(EMultiplyAlgorithm eMultAlg);
    // Sets the XPlusY array to contain the sum X+Y -- it assumes that array is big enough;
    // it does NOT check.  Returns the #of digits in XPlusY.
    // XPlusY may be either X or Y; this will not affect correctness (though it will of course
    // mean overwriting the original value!)
    static size_t Add(size_t      nXSize,
                      size_t      nYSize,
                      const DIGIT *pX,
                      const DIGIT *pY,
                      DIGIT       *pXPlusY);

    // Adds X to Y, storing the results in Y.  Assumes Y is at least as big as X.  If Y gets bigger due to carry, updates its size
    static void AddXToYInPlace(size_t      nXSize,
                               size_t      &nYSize,
                               const DIGIT *pX,
                               DIGIT       *pY);

    // Sets the Z array to X-Y.  It assumes the Z array is big enough, and that
    // X is, indeed, at least as large as Y.  Returns the size of XMinusY.
    // XMinusY may be either X or Y; this will not affect correctness (though it will of course
    // mean overwriting the original value!)
    static size_t Subtract(size_t      nXSize,
                           size_t      nYSize,
                           const DIGIT *pX,
                           const DIGIT *pY,
                           DIGIT       *pXMinusY);
    // Wrapper for multiplication.  Makes sure the
    // operands are in the right order -- smaller first -- and
    // decides which multiplication routine to use, based on
    // the size of the smaller operand.  Z is assumed to have enough
    // space for the operation (not checked).  It does not handle
    // multiply by 0-DIGIT operands.  Likewise the workspace is assumed to be
    // sufficient.
	// It is up to the user to trim the leading 0 of the product (if any)
	// if desired when pnZSize is not passed.  If pnZSize is passed,
	// it checks for leading 0s in the operands, and zeros out Z accordingly.
	// Useful when leading 0s might exist, and the cost of checking is
	// worth it (either because it is computationally efficient to do
	// so -- smaller mults are cheaper -- or the system might generate
	// errors if they are NOT eliminated.  In particular, it is needed
	// wherever either operand might have leading 0s, and MultU2NByN
	// might be the multiply used!!!
    // returns the multiplication algorithm used
    static EMultiplyAlgorithm MultUBackend(size_t             nXSize,
                                           size_t             nYSize,
                                           const DIGIT        *pXValue,
                                           const DIGIT        *pYValue,
                                           DIGIT              *pZValue,
                                           DIGIT              *pnWorkspace,
#if(_CollectDetailedTimingData)
                                           DWORD64            &dwTimestamp,
#endif
							               size_t             *pnZSize=NULL);
    static EMultiplyAlgorithm SquareUBackend(size_t           nXSize,
                                             const DIGIT      *pXValue,
                                             DIGIT            *pZValue,
                                             DIGIT            *pnWorkspace,
#if(_CollectDetailedTimingData)
                                             DWORD64          &dwTimestamp,
#endif
                                             size_t           *pnZSize=NULL);
    // If the multiply can be done using the basic algorithms (not divide-and-conquer),
    // there is no need to copy the z data.  If not, a copy must be done.  The memory is
    // assumed to be adequate either way.  Note the pZValue needs to be padded with zeroes
    // from nZSize to nZSize+1 or nXSize+nYSize+1, whichever is greater.
    // nZSize is set to the new size on completion.
	// (Keep in sync with MultUBackend)
    static EMultiplyAlgorithm MultAddUBackend(size_t             nXSize,
                                              size_t             nYSize,
                                              size_t             &nZSize,
                                              const DIGIT        *pXValue,
                                              const DIGIT        *pYValue,
                                              DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                                              DWORD64            &dwTimestamp,
#endif
                                              DIGIT              *pnWorkspace);
    static void DivideBackend(size_t  nXSize,
                              size_t  nYSize,
                              size_t  &nXDivYSize,
                              size_t  &nRemainderSize,
                              DIGIT   *pXValue,
                              DIGIT   *pYValue,
                              DIGIT   *pXDivYValue,
#if(_CollectDetailedTimingData)
                              DWORD64 &dwTimestamp,
#endif
                              DIGIT   *pWorkspace);
    // Assumes X is at most as large as Y.
    // Needs to be kept in sync with the multiplication algorithms!
    static size_t MultiplyMemoryNeedsBackend(size_t nXSize, size_t nYSize);
    // Back end for computing division memory needs.  Recursive; doesn't
    // do the rounding.  Needs to be kept in sync with the division algorithm!
    static size_t DivisionMemoryNeedsBackend(size_t nNumeratorSize, size_t nDenominatorSize);
    // memory needed by the various backend functions used in calculating square roots
    static size_t SquareRootNewtonMemoryNeeds(size_t nXSize);
    static size_t GeneralSquareRootNewtonMemoryNeeds(size_t nX1Size, size_t nX2Size);
    static size_t GeneralSquareRootRecursiveMemoryNeeds(size_t nX1Size, size_t nX2Size);
    // This is NOT to be held up as the right way to do multiplication.
    // Rather, it is an easy-to-debug baseline for testing the real
    // functions: something to get the bootstrapping started.
    // Multiples X and Y, and puts their product in Z, and returns Z's
    // size.
    // It is assumed that all the arrays are of the required size (unchecked)
    static size_t MultOracle(size_t      nXSize,
                             size_t      nYSize,
                             const DIGIT *pX,
                             const DIGIT *pY,
                             DIGIT       *pZ);
	// for when the larger value is at least twice the size of the smaller,
	// and the size of the smaller indicates a divide-and-conquer algorithm
	// should be employed
	static void BigShortLongMultiply(size_t             nSmallSize,
								     size_t             nLargeSize,
									 const DIGIT        *pnSmallValue,
									 const DIGIT        *pnLargeValue,
									 DIGIT              *pnZValue,
#if(_CollectDetailedTimingData)
                                     DWORD64            &dwTimestamp,
#endif
									 DIGIT              *pnWorkspace,
									 size_t             *pnZSize=NULL);
	// used for common work in multiplying two numbers far enough apart in size
	// that the algorithm for which their size is appropriate won't work,
	// but where the larger is less than double the size of the smaller.
	// X should be the smaller number; Y, the larger (unchecked, but vital)
	static void FinishUnbalancedMult(size_t             nXSize,
                                     size_t             nYSize,
                                     const DIGIT        *pX,
                                     const DIGIT        *pY,
                                     DIGIT              *pZ,
#if(_CollectDetailedTimingData)
                                     DWORD64            &dwTimestamp,
#endif
									 DIGIT              *pnWorkspace,
									 size_t             *pnZSize=NULL);
    // The basic multiplication algorithm all the other higher-order algorithms
    // eventually call.  This is just the long-multiplication you learned in
    // elementary school, optimized to take advantage of memory and registers.
    // Note that it is assumed that nXSize <= nYSize (unverified).  Also
    // doesn't handle 0-sized numbers!.
    // The caller is responsible for computing the size of the result.
    // If performing z = x*y+z (boolean set to true), it is assumed that
    // the Z array is initialized to nXSize+nYSize+1 (possibly with leading 0s!).
    // And you wondered why this was a private function?  It's for internal
    // use, silly!
    static void MultUBasic(size_t       nXSize,
                           size_t       nYSize,
                           const DIGIT  *pX,
                           const DIGIT  *pY,
                           DIGIT        *pZ,
                           bool         bAddInitialZValueToProduct);
    // same as MultUBasic; just does the work in a different fashion.  Assumes
    // nXSize is at least 13 (else wouldn't be calling this function).  Also
    // assumes z is 0 above nYSize+6 if doing multiply, 0 above <z size> for mult-add
    static void MultUStriped(size_t       nXSize,
                             size_t       nYSize,
                             const DIGIT  *pX,
                             const DIGIT  *pY,
                             DIGIT        *pZ,
                             bool         bAddInitialZValueToProduct);
    // Note that it is assumed that nXSize <= nYSize (unverified).  Also
    // doesn't handle 0-sized numbers!.
    static void MultUShortLong(size_t       nXSize,
                               size_t       nYSize,
                               const DIGIT  *pXValue,
                               const DIGIT  *pYValue,
                               DIGIT        *pZValue);
    // it is assumed that the pZValue array has leading 0s, to prevent
    // excessive carry-out -- going beyond its size is NOT checked!
    // Note that it is assumed that nXSize <= nYSize (unverified).  Also
    // doesn't handle 0-sized numbers!.
    static void MultAddUShortLong(size_t       nXSize,
                                  size_t       nYSize,
                                  const DIGIT  *pXValue,
                                  const DIGIT  *pYValue,
                                  DIGIT        *pZValue);
    static void MultU3by2(size_t              nXSize,
                          size_t              nYSize,
                          const DIGIT         *pXValue,
                          const DIGIT         *pYValue,
                          DIGIT               *pZValue,
#if(_CollectDetailedTimingData)
                          DIGIT               *pnWorkspace,
                          DWORD64             &dwTimestamp); // on entry, time called.  On exit, time completed
#else
                          DIGIT               *pnWorkspace);
#endif
    static void SquareU3by2(size_t             nXSize,
                            const DIGIT        *pxValue,
                            DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                            DWORD64            &dwTimestamp,
#endif
                            DIGIT              *pnWorkspace);
    static void MultU5by3(size_t              nXSize,
                          size_t              nYSize,
                          const DIGIT         *pXValue,
                          const DIGIT         *pYValue,
                          DIGIT               *pZValue,
#if(_CollectDetailedTimingData)
                          DIGIT               *pnWorkspace,
                          DWORD64             &dwTimestamp); // on entry, time called.  On exit, time completed
#else
                          DIGIT               *pnWorkspace);
#endif
    static void SquareU5by3(size_t             nXSize,
                            const DIGIT        *pxValue,
                            DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                            DWORD64            &dwTimestamp,
#endif
                            DIGIT              *pnWorkspace);
    static void MultU7by4(size_t              nXSize,
                          size_t              nYSize,
                          const DIGIT         *pXValue,
                          const DIGIT         *pYValue,
                          DIGIT               *pZValue,
#if(_CollectDetailedTimingData)
                          DIGIT               *pnWorkspace,
                          DWORD64             &dwTimestamp); // on entry, time called.  On exit, time completed
#else
                          DIGIT               *pnWorkspace);
#endif
    static void SquareU7by4(size_t             nXSize,
                            const DIGIT        *pxValue,
                            DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                            DWORD64            &dwTimestamp,
#endif
                            DIGIT              *pnWorkspace);
#if(32<=_DIGIT_SIZE_IN_BITS)
    static void MultU9by5(size_t             nXSize,
                          size_t             nYSize,
                          const DIGIT        *pXValue,
                          const DIGIT        *pYValue,
                          DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                          DIGIT              *pnWorkspace,
                          DWORD64            &dwTimestamp); // on entry, time called.  On exit, time completed
#else
                          DIGIT              *pnWorkspace);
#endif
    static void SquareU9by5(size_t             nXSize,
                            const DIGIT        *pxValue,
                            DIGIT              *pZValue,
#if(_CollectDetailedTimingData)
                            DWORD64            &dwTimestamp,
#endif
                            DIGIT              *pnWorkspace);
#endif
    // Performs division, using simple algorithm: O(nXSize * nYSize).
    // Replaces X with the remainder of the division
    static void DivideBasic(size_t      nXSize,
                            size_t      nYSize,
                            DIGIT       *pXValue,
                            const DIGIT *pYValue,
#if(_CollectDetailedTimingData)
                            DWORD64     &dwTimestamp,
#endif
                            DIGIT       *pXDivYValue);
    // Uses a more complex algorithm to do the division: takes time proportional
    // to multiplication.  Assumptions (and results) as per DivideBasic.
    // Note that Y is *transiently* changed; its original value is restored
    // by the time the divide exits -- but because it is twiddled internally,
    // it cannot be a constant variable
    // by assumption: y<=x, and 2*size<y> <= size<x>
    // by assumption: y<=x, and 2*size<y> <= size<x>
    static void DivideRecursive(size_t  nXSize,
                                size_t  nYSize,
                                DIGIT   *pXValue,
                                DIGIT   *pYValue,
                                DIGIT   *pXDivYValue,
#if(_CollectDetailedTimingData)
                                DWORD64 &dwTimestamp,
#endif
                                DIGIT   *pWorkspace);
    // For breaking a multiplication down into very
    // large numbers of subproblems. If called with pieces (n) < 5,
    // delete the return value when done; otherwise, we keep
    // it for future use.  Should ONLY call it with n < 5 internally!
    static SSystemData *GenerateSystem(size_t n);
    // returns the number of pieces appropriate for using 2NbyN
    // multiplication, below, given the passed size.  There are
    // theoretical reasons that it should grow as log(sqrt(n)),
    // but for now hardwired for testing.
    // Assumes nXsize <= nYsize!
    static size_t PiecesByProblemSize(size_t nSize);
    static size_t PiecesByProblemSizeSquare(size_t nSize);
	static void ConstructArgumentsFor2NByNSubproblems(size_t              nSubproblemSize,
													  size_t              nNumPieces,
													  size_t              nXSize,
													  size_t              nYSize,
													  size_t              nMaxRIOpSize,
													  size_t              nOverflowSize,
													  DIGIT               **ppnRi,
													  size_t              *pnRiOpSizes,
													  const DIGIT         *pnX,
													  const DIGIT         *pnY,
													  DIGIT               *pnOverflowDigits,
													  SSystemData         *pSystemToUse,
#if(_CollectDetailedTimingData)
													  DWORD64             &dwTimestamp, // on entry, time called.  On exit, time completed
#endif
													  DIGIT               *pnWorkspace);
    // same, but constructs the arguments for a square
	static void ConstructArgumentsFor2NByNSubproblems(size_t              nSubproblemSize,
													  size_t              nNumPieces,
													  size_t              nXSize,
													  size_t              nMaxRIOpSize,
													  DIGIT               **ppnRi,
													  size_t              *pnRiOpSizes,
													  const DIGIT         *pnX,
													  SSystemData         *pSystemToUse,
#if(_CollectDetailedTimingData)
													  DWORD64             &dwTimestamp, // on entry, time called.  On exit, time completed
#endif
													  DIGIT               *pnWorkspace);
	static void ComputeProductFrom2NByNSubproblemResults(size_t              nNumPieces,
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
											             DIGIT               *pnWorkspace);
    // Actually, 2N-1 by N, using the normal parlance
    static void MultU2NByN(size_t             nXSize,
                           size_t             nYSize,
                           const DIGIT        *pXValue,
                           const DIGIT        *pYValue,
                           DIGIT              *pZValue,
                           SSystemData        *pSystemToUse,
#if(_CollectDetailedTimingData)
                           DIGIT               *pWorkspace,
                           DWORD64             &dwTimestamp); // on entry, time called.  On exit, time completed
#else
                           DIGIT               *pWorkspace);
#endif
    static void SquareU2NByN(size_t             nXSize,
                             const DIGIT        *pXValue,
                             DIGIT              *pZValue,
                             SSystemData        *pSystemToUse,
#if(_CollectDetailedTimingData)
                             DWORD64            &dwTimestamp,
#endif
                             DIGIT              *pWorkspace);
    // returns the size (in DIGITs) of the GCD
    // Synopsis:	Computes the greatest common divisor of the numbers
    //              passed.  ASSUMES x, y are positive!
    //              Note that it is assumed throughout that the space
    //              provided for [a] and [b] is adequate.
    // Algorithm:   Euler's method: if d is the gcd of u and v, then
    //              a'v + b'(u mod v) = d <=> b'u + (a' - (u/v)b')v = d.
    //              So solving ax + by = d reduces to solving
    //              a'y + b'(x mod y) = d (recall that d is the gcd of
    //              x and y iff 0<d<=x,y and there exists a, b s.t.
    //              ax + by = d)
    //              Then, a = b' and b = a' - (x/y)b'.
    // This function destroys X and Y in the process!
    // Note that computing the coefficients requires significantly more memory!
    // Assumes X is at least as large as Y
    static size_t GCDBase(size_t  nXSize,
                          size_t  nYSize,
                          DIGIT   *pXValue,
                          DIGIT   *pYValue,
                          DIGIT   *pGCDValue,
#if(_CollectDetailedTimingData)
                          DWORD64 &dwTimestamp,
#endif
                          DIGIT   *pWorkspace);
    // As GCD (except for the return value), but also computes the A and B values.
    // The coef value arrays are assumed to have enough space!  (Bound on needs:
    // the x coef can't be larger than y; the y coef can't be larger than x.)
    // Assumes that X is the larger value.
    // Also: doesn't deal with either x or y being 0.  Frankly doesn't make sense
    // if BOTH are 0.  Treat as special case.
    // In case you only care about one of the coefs, passing
    // NULL for the one not desired will work -- and reduce
    // computation time somewhat (especially for large X, Y
    // values)
    static void GCDCoef(size_t  nXSize,
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
                        DIGIT   *pWorkspace);

    // same, except uses recursion instead of a loop.  Perhaps simpler to
    // code...  but blows out the stack in the low 100s of digits
    static void GCDCoef_recursive(size_t  nXSize,
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
                                  DIGIT   *pWorkspace);
    // the bit shift represents a positive (left) bit shift as bits and digits; used in the FFT multiplication.
    // e.g. a shift of 73 with a 16-bit DIGIT would be [4,9]
    struct SBitShift
    {
    public: // variables
        size_t m_nDigitShift;
        DIGIT  m_nBitShift;
    public: // functions
        SBitShift();
        // returns false if halving the shift would lead to the loss
        // of significant digits; otherwise, halves it
        bool Halve();
        // doubles the value
        void Double();
        // adds the value passed to the base
        void Add(SBitShift &nAddend);
        // subtracts the passed to the base, if it is at most as large
        bool Sub(SBitShift &nSub);
    };
    // Mod x by 1+2^n.  Assumes x is at most 2^(2n), and has
    // exactly 2n+1 digits (with leading 0s, if need be).  Yup;
    // specialized function.
    // Note that x mod (1+2^n) for x a number of m bits the result is
    // (least significant n bits) - (next least significant n bits) + (next least
    // sigificant n bits) - ... + (most significant m mod n) bits, + (1+2^n) if the
    // final result is negative.
    // We have a version of this of known (short) size.
    // It is safe for pDestination to be X.
    static void ModBy2nPlus1(const DIGIT *pXData,
                             DIGIT       *pDestination,
                             size_t      n);
    // In computing the FFT-equivalent, there is much multiplying by powers
    // of 2 and modding by (1+2^n) involved.  It is cost-effective to have a
    // dedicated function for doing this.
    // Note that x mod (1+2^n) for x a number of m bits the result is
    // (least significant n bits) - (next least significant n bits) + (next least
    // sigificant n bits) - ... +/- (most significant m mod n) bits, + (1+2^n) if the
    // final result is negative.
    // This function computes (x*2^m) mod (1+2^n) where x is in [0,2^n].
    // Note that the destination can NOT be the same as the source (pXData).
    // X is assumed to have exactly n+1 digits and to be in the range [0,2^n],
    // with leading 0s to fill it out if need be.
    // Note that n is given in DIGITS, whereas m is given in BITS.
    // Assumes n is at least 4 (for technical reasons -- don't
    // have to do some checks that way)
    static void Mult2toMmodOnePlus2toN(const DIGIT *pXData,
                                       size_t      n,
                                       SBitShift   &nShift,
                                       DIGIT       *pDestination);
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
    // Note that for the inverse, pass a root of -1 instead of a root of unity, so we don't
    // need a separate function, then divide by nLength
    // Here, the field is over the integers mod (1+2^n), where n is expressed in DIGITs -- NOT bits
    // The size of the original number might not be quite right for the FFT length.
    // When this happens, the first few elements of the number to take the FFT are implicitly
    // 0 ("first" being "high order"), and the first nonzero element will in general be smaller
    // than the rest of the pieces
    // Note that this is going to fail if the ToCompute number does not have at least half
    // as many elements as the FFT!

    // converts the base number whose FFT is to be computed into the format desired for the FFT
    // Note the nFFTLength is always a power of 2, and division by 2^m is the same as multiplication by 2^(2n-m) in the field.
    // This function is only used in test, for FFT_basic (which is itself only used in test for validation purposes)
    static void ExpandBaseNumberForFFT(const DIGIT *pnToExpand,
                                       size_t      nToExpandLength,
                                       size_t      nChunkSize,
                                       size_t      nFieldSize,
                                       size_t      nFFTLength,
                                       DIGIT       *pnExpanded);
    static void FFT_basic(const DIGIT *pBase,
                          DIGIT       *pFFT,
                          size_t      nLength,
                          size_t      nFieldSize,
                          SBitShift   nRootUnity,
                          size_t      nStep, // base skip size in the FFT.  Should start at nFieldSize+1
                          DIGIT       *pnWorkspace);
    // same as FFT, but optimized.  The pFFT array should contain the initial value whose FFT is
    // to be computed, which will be replaced by the FFT
    static void FFT(const DIGIT *pBase,    // the number whose FFT is to be computed
                    DIGIT       *pFFT,
                    size_t      nBaseSize, // the size of the number whose FFT is to be computed
                    size_t      nChunkSize,
                    size_t      nBaseStep, // should start at nChunkSize+1
                    size_t      nLength,
                    size_t      nFieldSize,
                    SBitShift   nRootUnity,
                    DIGIT       *pnWorkspace);
    // computes the FFT with a different ordering of the data for better locality of reference
    /*static void FFTReordered(const DIGIT *pBase,    // the number whose FFT is to be computed
                    DIGIT       *pFFT,
                    size_t      nBaseSize, // the size of the number whose FFT is to be computed
                    size_t      nChunkSize,
                    size_t      nLength,
                    size_t      nFieldSize,
                    SBitShift   nRootUnity,
                    DIGIT       *pnWorkspace);
    static void FFTReorderedBackend(DIGIT       *pFFT,
                                    size_t      nLength,
                                    size_t      nFieldSize,
                                    SBitShift   nRootUnity,
                                    DIGIT       *pnWorkspace);*/
    static void FFT_Inverse_basic(const DIGIT *pToCompute,
                                  size_t      nLength,
                                  SBitShift   nRootUnity, // the root of unity used in the forward FFT
                                  size_t      nFieldSize,
                                  DIGIT       *pFFTInverse,
                                  DIGIT       *pnWorkspace);
    static void FFTInverse(const DIGIT *pBase,    // the number whose FFT is to be computed
                           DIGIT       *pFFT,
                           size_t      nBaseStep, // should start at nChunkSize+1
                           size_t      nLength,
                           size_t      nFieldSize,
                           SBitShift   nRootUnity,
                           DIGIT       *pnWorkspace);
	// for use with optimized FFT
    static void FFT_Inverse(const DIGIT *pFFT,
		                    DIGIT       *pFFT_FFTInverse,
                            size_t      nLength,
                            SBitShift   nRootUnity, // the root of unity used in the forward FFT
                            size_t      nFieldSize,
                            DIGIT       *pnWorkspace);
    // GetFFTSize is passed in the size (in DIGITs) of the larger number to multiply, and determines
    // the parameters needed for the FFT multiply
    //
    // Doing: multiply {x0, x1, ... ,xn} by {y0, y1, ... , ym}.
    // In the FFT multiply, the kth element in the vector corresponds to the sum of all xi*yj s.t. i+j=k.
    //
    // The field size for the FFT needs to be at least twice the size of the piece (so it can be inverted uniquely),
    // with at lest one extra digit (for carry ops -- the middle pices of the FFT multiplication are the virtual
    // sums of MANY sub-multiplications).  Also the FFT needs to be at least as long as the sum of the two numbers
    // being multiplied: one for each slot in the vector multiply
    // since there are 
    // The number of pieces can be at most 2^<field size in DIGITs+4> (so 2 is a root of unity of sufficient degree)
    static void GetFFTSize(size_t nXSize, size_t nYSize, size_t &nFFTLength, size_t &nFieldSize, size_t &nChunkSize, BYTE &byMaxOverflowSize, SBitShift &nRootUnity);
    // computes the element-by-element product of two vectors, in the format output by FFT_Basic, and mods by the field.
    // Replaces the first (FFT_a) with the result.
    static void Convolve(DIGIT       *pnFFT_a,
                         const DIGIT *pnFFT_b,
                         size_t      nLength,
                         size_t      nFieldSize,
#if(_CollectDetailedTimingData)
                         DIGIT       *pnWorkspace,
                         DWORD64     &dwTimestamp);
#else
                         DIGIT       *pnWorkspace);
#endif
    static void ConvolveSquare(DIGIT   *pnFFT_a,
                               size_t  nLength,
                               size_t  nFieldSize,
#if(_CollectDetailedTimingData)
                               DWORD64 &dwTimestamp,
#endif
                               DIGIT   *pnWorkspace);
    // helper function for MultFFT, SquareFFT
    static void GetProductFromInverseFFT(const DIGIT *pnFFT_Inverse,
                                         DIGIT       *pnZValue,
                                         size_t      nChunkSize,
                                         size_t      nFieldSize,
                                         size_t      nProductSize,
                                         BYTE        byMaxOverflowSize);
    // multiplies X and Y, using the FFT multiplication algorithm
    // As ever, it is assumed that nXSize <= nYSize (unverified).
    // It is ALSO assumed that nYSize < 2*nXSize -- likewise unverified
    static void MultFFT(size_t             nXSize,
                        size_t             nYSize,
                        const DIGIT        *pnXValue,
                        const DIGIT        *pnYValue,
                        DIGIT              *pnZValue,
#if(_CollectDetailedTimingData)
                        DIGIT              *pnWorkspace,
                        DWORD64            &dwTimestamp); // on entry, time called.  On exit, time completed
#else
                        DIGIT              *pnWorkspace);
#endif
    // Computes x^2 -- done as a separate function because, unlike the other
    // multiplication algorithms, FFT multiplication can be done faster if
    // we know the two numbers to be multiplied are one and the same!
    static void SquareFFT(size_t             nXSize,
                          const DIGIT        *pnXValue,
                          DIGIT              *pnZValue,
#if(_CollectDetailedTimingData)
                          DIGIT              *pnWorkspace,
                          DWORD64            &dwTimestamp); // on entry, time called.  On exit, time completed
#else 
                          DIGIT              *pnWorkspace);
#endif
    // for efficiency, it is assumed that pXMontgomeryValue has space for nXSize + nNSize DIGITs, even though it is guaranteed to have a value
    // needing at most nNSize: xR mod N
    static void ToMontgomeryForm(size_t      nXSize,
                                 size_t      nNSize,
                                 size_t      &nXMontgomerySize,
                                 const DIGIT *pXValue,
                                 DIGIT       *pNValue,
                                 DIGIT       *pXMontgomeryValue,
#if(_CollectDetailedTimingData)
                                 DWORD64     &dwTimestamp,
#endif
                                 DIGIT       *pWorkspace);
    // xR' mod N.  X should have room for 2*nSize DIGITs, though its value will only have at most nNSize in the end
    static void FromMontgomeryForm(size_t      nMontgomerySize,
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
                                   DIGIT       *pWorkspace);
    // It is assumed that x, y are already in Montgomery form.  Note this implies each has at most 2*nSize DIGITs.  Performs x*y = z
    // z should have space for at least 2*nNSize+1 DIGITs
    static void MontgomeryMultiply(size_t       nXSize,
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
                                   DIGIT        *pWorkspace);
    // Same; just does x*x instead of x*y
    static void MontgomerySquare(size_t       nXSize,
                                 size_t       nNSize,
                                 size_t       nNPrimeSize,
                                 size_t       &nZSize,
                                 const DIGIT  *pXValue,
                                 const DIGIT  *pNValue,
                                 const DIGIT  *pNPrimeValue,
                                 DIGIT        *pZValue,
#if(_CollectDetailedTimingData)
                                 DWORD64     &dwTimestamp,
#endif
                                 DIGIT        *pWorkspace);
    // same, but assumes X is already in Montgomery form, and puts the power modulus -- still in Montgomery form --
    // in pnPowerModulus.  nPowerDigit and nPowerBit from GetLeadBit on the modulus.  pnPowerModulus should have
    // space for at least 2*nModulusSize + 1 DIGITs (those beyond the modulus size as workspace).
    static void MontgomeryPowerModulus(size_t      nXSize,
		                               size_t      nYSize,
					    		       size_t      nModulusSize,
                                       size_t      nModulusPrimeSize,
                                       size_t      nPowerDigit,
                                       size_t      nPowerBit,
                                       size_t      &nPowerModulusSize,
				    			       const DIGIT *pnXValue,
							           const DIGIT *pnYValue,
							           const DIGIT *pnModulusValue,
                                       const DIGIT *pnModulusPrimeValue,
                                       DIGIT       *pnPowerModulus,
#if(_CollectDetailedTimingData)
                                       DWORD64     &dwTimestamp,
#endif
							           DIGIT       *pnWorkspace,
							           bool        bProtectAgainstTimingAttacks = false);
    // REDC does multiplication in Montgomery form cleanup
    // In this implementation of REDC, T is replaced with S on return
    // input: Integers R and N with gcd(R, N) = 1,
    // Integer N? in[0, R ? 1] such that NN? ? ?1 mod R,
    // Integer T in the range[0, RN ? 1].
    // output : Integer S in the range[0, N ? 1] such that S ? TR?1 mod N
    // T is assumed to have space for at least 2*nNSize+1 DIGITs
    static void REDC(size_t       nNSize,
                     size_t       nNPrimeSize,
                     size_t       &nSTSize,
                     const DIGIT  *pNValue,
                     const DIGIT  *pNPrimeValue,
                     const DIGIT  *pTValue,
                     DIGIT        *pSValue,
#if(_CollectDetailedTimingData)
                     DWORD64      &dwTimestamp,
#endif
                     DIGIT        *pWorkspace);
    // Find: largest y s.t. (x1 + y)y <= x2.  Note that with x1 positive, it is clear that y < sqrt(x2).  As the name suggests,
    // uses Newton's method.  Assumes x1 < x2
    static void GeneralSquareRootNewton(size_t  nX1Size,
                                        size_t  nX2Size,
                                        size_t  &nRootSize,
                                        DIGIT   *pnX1,
                                        DIGIT   *pnX2,
                                        DIGIT   *pnRoot,
#if(_CollectDetailedTimingData)
                                        DWORD64 &dwTimestamp,
#endif
                                        DIGIT   *pnWorkspace);
    static void GeneralSquareRootRecursive(size_t  nX1Size,
                                           size_t  nX2Size,
                                           size_t  &nRootSize,
                                           DIGIT   *pnX1,
                                           DIGIT   *pnX2,
                                           DIGIT   *pnRoot,
#if(_CollectDetailedTimingData)
                                           DWORD64 &dwTimestamp,
#endif
                                           DIGIT   *pnWorkspace);
    // Finds the largest y s.t. y^2 <= x using Newton's method.  Assumes 0<x (if 0 == x, get a divide-by-zero)
    static void SquareRootNewton(size_t  nXSize,
                                 size_t  &nRootSize,
                                 DIGIT   *pnX,
                                 DIGIT   *pnRoot,
#if(_CollectDetailedTimingData)
                                 DWORD64 &dwTimestamp,
#endif
                                 DIGIT   *pnWorkspace);
    // Finds the largest y s.t. y^2 <= x
    static void SquareRootRecursive(size_t  nXSize,
                                    size_t  &nRootSize,
                                    DIGIT   *pnX,
                                    DIGIT   *pnRoot,
#if(_CollectDetailedTimingData)
                                    DWORD64 &dwTimestamp,
#endif
                                    DIGIT   *pnWorkspace);

    // returns the subproblem size used in dividing an nXSize-DIGIT number by an nYSize-DIGIT one
    static size_t DivideSubproblemSize(size_t nXSize, size_t nYSize, size_t &nDivOffset);

public:    // variables
protected: // variables
    static const unsigned int c_n2NBynSizeBreakpoints = 7;
#ifdef _UsingVariableThresholdsForTest
    static unsigned int       c_nBuildBlockSizePre;
    static unsigned int       c_nBuildBlockSizePost;
    static unsigned int       c_pnMultiplicationThresholds[eNumMultiplyAlgorithms-1];
    static unsigned int       c_pnSquareThresholds[eNumMultiplyAlgorithms-1];
	static unsigned int       c_pn2NByNBreakpoints[c_n2NBynSizeBreakpoints]; // switch between 5 and 6 pieces, 6 and 7, etc.  By the upper end,
	                                                                         // don't care -- FFT mult is faster, anyway
    static unsigned int       c_pn2NByNSquareBreakpoints[c_n2NBynSizeBreakpoints];
    static unsigned int       c_nDivideThresholdSmall;       // at least 4 for correctness
    static unsigned int       c_nDivideThresholdDiff;        // at least 4 for correctness
    static unsigned int       c_nSquareRootThreshold;
#else
    static const unsigned int c_nBuildBlockSizePre;          // or whatever is found to be best in testing thresholds -- this is good
    static const unsigned int c_nBuildBlockSizePost;         // or whatever is found to be best in testing thresholds -- this is good
    static const unsigned int c_pnMultiplicationThresholds[eNumMultiplyAlgorithms-1];
    static const unsigned int c_pnSquareThresholds[eNumMultiplyAlgorithms-1];
	static const unsigned int c_pn2NByNBreakpoints[c_n2NBynSizeBreakpoints]; // switch between 5 and 6 pieces, 6 and 7, etc.  By the upper end,
	                                                                         // don't care -- FFT mult is faster, anyway
    static const unsigned int c_pn2NByNSquareBreakpoints[c_n2NBynSizeBreakpoints];
    // used by the function deciding how many pieces to use for REALLY BIG multiplications
    static const unsigned int c_nDivideThresholdSmall;       // at least 4 for correctness
    static const unsigned int c_nDivideThresholdDiff;        // at least 4 for correctness
    static const unsigned int c_nSquareRootThreshold;
#endif
    // might want to tune this value -- different machines might have different stack space
    static const unsigned int c_nMaxBYTESizeForRecursiveGCD = 400;
    static CHighPerfTimer     s_Timer;
    CWorkspace                m_Workspace;
};