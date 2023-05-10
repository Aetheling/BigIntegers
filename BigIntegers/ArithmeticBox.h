#pragma once
#include "CWorkspace.h"
#include "Timer.h"

// forward declarations
class CBigInteger;

__declspec(dllexport) enum EArithmeticOperationResult
{
    eOperationSucceeded,
    eBadArgument, // e.g., passing a NULL as one of the operands
    eBadOperand,  // e.g., divide by 0
    eOutOfMemory
};

// The ArithmeticBox does the various arithmetic operations on integers we've come to know
// and love -- multiplication, division, addition, etc.  Note that the box is NOT thread-safe:
// using the box to do two different multiplications (say) at the same time in different
// threads can cause Problems.  Having multiple boxes in use simultaneously is fine, but
// boxes should be reused as possible.  Note that using the same box simultaneously on
// two operations is NOT advised -- each box has a workspace it uses for calculations.

// If the numbers passed to the box do not have any leading zeros, the result(s) will also
// not have any leading zeros (aside from 0 itself, which has size 0).  While most operations
// will be fine with leading zeros, trying to divide by such a number most certainly will
// NOT.  If your data source might have leading zeros, calling FixSize() on the integer
// (CBigInteger function) is advised.
class __declspec(dllexport) CArithmeticBox
{
    friend class CArithmeticCorrectnessTester;
    friend class CArithmeticPerformanceTester;
public:
    CArithmeticBox();
    ~CArithmeticBox();
    // assigns the value of X+Y to XPlusY.  XPlusY can be either
    // X or Y.
    EArithmeticOperationResult Add(const CBigInteger &nX,
                                   const CBigInteger &nY,
                                   CBigInteger       &nXPlusY);
    // returns X+Y in a new integer (or NULL on failure)
    CBigInteger *Add(const CBigInteger &nX, const CBigInteger &nY);
    // assigns the value of X-Y to XMinusY.
    EArithmeticOperationResult Subtract(const CBigInteger &nX,
                                        const CBigInteger &nY,
                                        CBigInteger       &nXMinusY);
    // returns X-Y in a new integer (or NULL on failure)
    CBigInteger *Subtract(const CBigInteger &nX, const CBigInteger &nY);
    // assigns the value of X*Y to XTimesY.  XTimesY can be neither
    // X nor Y.
    EArithmeticOperationResult Multiply(const CBigInteger &nX,
                                        const CBigInteger &nY,
                                        CBigInteger       &nXTimesY);
    // returns X*Y in a new integer (or NULL on failure)
    CBigInteger *Multiply(const CBigInteger &nX, const CBigInteger &nY);
    // Square is slightly more efficient than Multiply
    // sets Square to X*X.  Cannot use X for the destination
    EArithmeticOperationResult Square(const CBigInteger &nX,
                                      CBigInteger       &nSquare);
    // returns X*X in a new integer (or NULL on failure)
    CBigInteger *Square(const CBigInteger &nX);
    // computes RunningSum = X*Y + RunningSum.  RunningSum
    // canot be either X or Y.
    EArithmeticOperationResult MultiplyAdd(const CBigInteger &nX,
                                           const CBigInteger &nY,
                                           CBigInteger       &nRunningSum);
    // Computes both X/Y (assigned to XDivY) and the remainder (assigned to Remainder).
    // NOTE: the remainder is in fact |X| mod |Y| with sign set to negative iff X and Y
    // have opposite signs (and X != 0)
    EArithmeticOperationResult Divide(const CBigInteger &nX,
                                      const CBigInteger &nY,
                                      CBigInteger       &nXDivY,
                                      CBigInteger       &nRemainder);
    // Synopsis:	Computes the greatest common divisor of the numbers
    //              passed.  It returns true if it can complete (the workspace
    //              passed is adequate, or can be resized to be); otherwise,
    //              it returns false.  It also sets the values of [a] and
    //              [b] (see algorithm) if they are passed.
    //              Note that it is assumed throughout that the space
    //              provided for [a] and [b] is adequate.
    // Algorithm:   Euler's method: if d is the gcd of u and v, then
    //              a'v + b'(u mod v) = d <=> b'u + (a' - (u/v)b')v = d.
    //              So solving ax + by = d reduces to solving
    //              a'y + b'(x mod y) = d (recall that d is the gcd of
    //              x and y iff 0<d<=x,y and there exists a, b s.t.
    //              ax + by = d)
    //              Then, a = b' and b = a' - (x/y)b'.
    // GCD just computes the greatest common divisor; GCDExtended computes the coefficients a nd b as well:
    // x*x_coef + y*y_coef = GCD
    // Note that computing the coefficients requires significantly more memory!
    EArithmeticOperationResult GCD(const CBigInteger &nX,
                                   const CBigInteger &nY,
                                   CBigInteger       &nGCD);
    // GCD, XCoef, and YCoef must be distinct values
    EArithmeticOperationResult GCDExtended(const CBigInteger &nX,
                                           const CBigInteger &nY,
                                           CBigInteger       &nGCD,
                                           CBigInteger       &nXCoef,
                                           CBigInteger       &nYCoef);

    // sets nSqrt to the largest integer with nSqrt^2 <= nX on success.
    EArithmeticOperationResult SQRT(const CBigInteger &nX, CBigInteger &nSqrt);

protected: // functions
public:    // variables
protected: // variables
    CWorkspace            m_Workspace;
	static CHighPerfTimer s_Timer;
};

// As ArithmeticBox, but performs all operations in the ring of the integers mod n, where n
// is the integer passed to the constructor.
// Note that certain operations don't make sense in the ring!  For example, in the integers
// mod 8, 2*6 = 6*6 = 4.  Multiplication is not invertible, so divide doesn't make
// sense.  Compare doesn't make sense, either.
// Except for Import(), the box assumes all numbers were either already imported,
// or were generated by operations within the box.
// Import() takes a general big integer, and converts it to a number in the
// integers mod n.
class __declspec(dllexport) CModularArithmeticBox
{
public:
    // If you want to take the power modulus of numbers larger than those in the field,
    // import it -- THEN take power modulus!  Recall (x^n) mod y == (x mod y)^n mod y
    CModularArithmeticBox(const CBigInteger &nModulus, bool bProtectAgainstTimingAttacks);
    CModularArithmeticBox(const char *szModulusExpressedInHexadecimal, bool bProtectAgainstTimingAttacks);
    ~CModularArithmeticBox();
    EArithmeticOperationResult GetModulus(CBigInteger *pnModulusCopy);
    const CBigInteger *GetModulus() { return &m_Modulus;  }
    size_t GetModulusSize();
	// Replaces X with X mod N.  Suitable for use
	// with the ring of integers mod N.  Computes
	// X/N as a side effect.
    void Import(CBigInteger *pX, CBigInteger *pXDivN);
    // X, Y, and XPlusY could be the same
    EArithmeticOperationResult Add(const CBigInteger *pX,
                                   const CBigInteger *pY,
                                   CBigInteger       *pXPlusY);
    // X, Y, could be the same
    CBigInteger *Add(const CBigInteger *pX, const CBigInteger *pY);
    // X, Y, and xMinusY could be the same
    EArithmeticOperationResult Subtract(const CBigInteger *pX,
                                        const CBigInteger *pY,
                                        CBigInteger       *pXMinusY);
    // X, Y, could be the same
    CBigInteger *Subtract(const CBigInteger *pX, const CBigInteger *pY);
    // XTimesY must not be X or Y
    EArithmeticOperationResult Multiply(const CBigInteger *pX,
                                        const CBigInteger *pY,
                                        CBigInteger       *pXTimesY);
    // xSquared must not be X
    EArithmeticOperationResult Square(const CBigInteger *pX,
                                      CBigInteger       *pXSquared);
    CBigInteger *Multiply(const CBigInteger *pX, const CBigInteger *pY);
    // RunningSum must not be X or Y.  Obviously *could* do multiply
    // followed by add -- but a little bit more efficient to do it
    // together
    EArithmeticOperationResult MultiplyAdd(const CBigInteger *pX,
                                           const CBigInteger *pY,
                                           CBigInteger       *pRunningSum);
    // Computes x^y in the ring.  XToY must be neither X nor Y.
    // With odd modulus, we can speed things up considerably by using Montgomery modular multiplication.  We assume the input is NOT
    // already in Montgomery form, and that we wish the output in regular form -- not Montgomery.  This can be overridden.
    EArithmeticOperationResult Power(const CBigInteger *pX,
                                     const CBigInteger *pY,
                                     CBigInteger       *pXToY);
    // computes the multiplicative inverse of X in the ring, if it exists
    EArithmeticOperationResult MultiplicativeInverse(const CBigInteger *pX, CBigInteger *pXInverse);
protected: // functions
    void ReserveMemory();
    EArithmeticOperationResult PowerLeadPowerDigitKnown(const CBigInteger *pX,
                                                        const CBigInteger *pY,
                                                        size_t            nPowerLeadDigit,
                                                        size_t            nPowerLeadBit,
                                                        CBigInteger       *pXToY);
public:    // variables
protected: // variables
#if(_CollectDetailedTimingData)
    static CHighPerfTimer s_Timer;
#endif
    CWorkspace            m_Workspace;
	CBigInteger           m_Modulus;
    // used by Montgomery multiplication  (in turn just used by Power() and PowerToBuffer())
    bool                  m_bSuitableForMontgomery, m_bProtectAgainstTimingAttacks;
    CBigInteger           m_ModulusPrime;
    CBigInteger           m_RPrime;
};

// As ModularBox, but for those times when you will ALWAYS be using the same power in power-modulus (say, a box intended
// for RSA encryption)
class __declspec(dllexport) CFixedPowerModularArithmeticBox : public CModularArithmeticBox
{
public:    // functions
    CFixedPowerModularArithmeticBox(CBigInteger &nPower, CBigInteger &nModulus, bool bProtectAgainstTimingAttacks);
    // If bProtectAgainstTimingAttacks is set, does a little extra work so regardless of
    // the bits of the power the computation takes the same amount of time -- potentially useful for RSA encryption (for which this is, yes, a
    // Useful Function).
    void Power(CBigInteger &nX, CBigInteger &nXToPower);
    const CBigInteger *GetPower() { return &m_nPower;  }
protected: // data
    CBigInteger m_nPower;
    size_t      m_nPowerLeadDigit, m_nPowerLeadBit;
};