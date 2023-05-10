#pragma once
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "Constants.h"

class __declspec(dllexport) CBigInteger
{
    friend class CUnsignedArithmeticHelper;
    friend class CArithmeticCorrectnessTester;
public:    // functions
    // constructors
    CBigInteger(); // the value will be 0
    // copy constructor
    CBigInteger(const CBigInteger &base);
    // create big integer with value given by a hexidecimal string (no spaces) -- e.g. "AA3271D"  Note: A-F must be capitals -- "aa3271d" doesn't work
    CBigInteger(const char *szHexadecimalValue, bool bKeepLeadingZeroes = false);
    ~CBigInteger();

    // All operations in the library make sure that there are no leading zeros.  But what if a value is imported from
    // somewhere without such a guarantee?  This function fixes up the size if such might occur
    void FixLeadingZeros();

    // comparitors
    bool operator==(const CBigInteger &toCompare);
    bool operator!=(const CBigInteger &toCompare);
    bool operator<(const CBigInteger &toCompare);
    bool operator<=(const CBigInteger &toCompare);
    bool operator>=(const CBigInteger &toCompare);
    bool operator>(const CBigInteger &toCompare);
    // assignment.  Does deep copy.  Returns true on success (failure means out of memory)
    bool operator=(const CBigInteger &nBase);
    // add in place
    bool operator+=(DIGIT nAdd); // BOOLEAN return value!  (true on success: might run out of memory).  Also DIGIT is unsigned, so can't do (say) x += -7 -- use x -= 7 instead
    bool operator+=(const CBigInteger &nToAdd); // BOOLEAN return value!  (true on success; might run out of memory).
    // subtract in place
    bool operator-=(DIGIT nAdd); // BOOLEAN return value!  (true on success; might run out of memory).  Also DIGIT is unsigned, so can't do (say) x -= -7 -- use x += 7 instead
    bool operator-=(const CBigInteger &nToSubtract); // BOOLEAN return value!  (true on success; might run out of memory).
    // Note that we do NOT overload +, -, *, /, or %.  For these, use the arithmetic box.  (*, /, and % need a workspace, and for all
    // overloading would mean computing the value, then copying it in to the destination rather than computing it in the destination
    // in the first place as the box does)

    // returns -1 if x<y, 0 if x==y, and 1 if y<x
    static int Compare(const CBigInteger &x, const CBigInteger &y);

    // swaps the values of x and y
    static void Swap(CBigInteger &nX, CBigInteger &nY);

    // accessors
    DIGIT *GetValue() const
    {
        return m_pnValue;
    }

    size_t GetSize() const
    {
        return m_nSize;
    }

    bool SetSize(size_t nNewSize)
    {
        if (m_nAllocatedSize < nNewSize) return false;
        m_nSize = nNewSize;
        if (0 == m_nSize) m_bNegative = false;
        return true;
    }

    bool IsOdd() const
    {
        return ((0<m_nSize) && (0 != (m_pnValue[0]&1)));
    }

    bool IsNegative() const
    {
        return m_bNegative;
    }

    bool IsZero() const
    {
        return (0 == m_nSize);
    }

    void Invert()
    {
        if(0<m_nSize) m_bNegative = !m_bNegative;
    }

    void SetNegative(bool bNegative)
    {
        if(0<m_nSize) m_bNegative = bNegative;
    }

    // General utility
    // Prints the number, in hexadecimal, to the file passed (or to stdout if
    // the file is NULL).  Adds some spacing to make the result more readable
    bool PrintHexToFile(FILE *pFile = NULL) const;
    bool PrintHexToScreen(); // prints to screen without spacing for aesthetics
    // Same, but prints to base 10.  Slower.  NOTE: allows for at most ~2 billion DIGITs
    bool PrintDecimalToFile(FILE *pFile = NULL) const;
    // Makes sure the integer has space for at least as many digits as needed.  If bPreserveData is false and more space is needed,
    // the original data is discarded.  The data is copied if bPreserveData is true
    bool Reserve(size_t nDigitsNeeded, bool bPreserveData = false);

    // Sets the value to that represented by the null-terminated
    // hexadecimal string passed.  The string may not have whitespace:
    // only digits (0-9, A-F), with an optional leading -.  It must
    // have at least 1 digit!
    bool SetFromHexString(const char *szHexadecimalValue, bool bKeepLeadingZeroes=false);

    // Does the bit shift on the value -- equivalent to replacing it with divide/multiply by 2^nBits
    bool ShiftRight(size_t nBits);
    bool ShiftLeft(size_t nBits);
    // Puts a copy of the base integer, shifted right/left by the passed number of bits, into the passed big integer.
    // returns true on success.  Equivalent to divide/multiply by 2^nBits
    bool CopyShiftRight(CBigInteger &nDestination, size_t nBits) const;
    bool CopyShiftLeft(CBigInteger &nDestination, size_t nBits) const;
    // vaccuous in retail.  Potentially useful in debugging.  Returns true if the buffer does not appear to have been overrun (or it's retail)
    _forceinline void CheckBufferguard() const
    {
#ifdef _DEBUG
        if (0<m_nAllocatedSize)
        {
            for(int j=0; j<_BUFFERGUARD_SLOTS; j++)
            {
                if(BUFFERGUARD != m_pnValue[m_nAllocatedSize+j])
                {
                    printf("Overran allocated memory space for big integer\n");
                }
            }
        }
#endif
    }

protected: // functions
private:   // functions
    // returns -1 if X < Y, 0 if X == Y, and 1 if X > Y.
    static int CompareUnsigned(size_t nXSize, size_t nYSize, const DIGIT *pX, const DIGIT *pY);
public:    // data
    size_t m_nAllocatedSize;
    size_t m_nSize;
    DIGIT  *m_pnValue;
    bool   m_bNegative;
};