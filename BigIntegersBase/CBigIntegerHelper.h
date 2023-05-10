#pragma once
#include "..\BigIntegers\Constants.h"
// Helper functions for CBigInteger -- static functions on unsigned DIGIT arrays
class CBigIntegerHelper
{
public: // functions
	    // returns the size, in DIGITs, of the bit-shifted result.  (Shift nDigitShift DIGITS and nBitShift BITs
    static size_t ShiftXRight(size_t nXSize, int nBitShift, size_t nDigitShift, const DIGIT *pnX, DIGIT *pnShiftedValue);
    static size_t ShiftXLeft(size_t nXSize, int nBitShift, size_t nDigitShift, const DIGIT *pnX, DIGIT *pnShiftedValue);
    // assumes sufficient space is available for the shifted value
    static size_t ShiftLeftInPlace(size_t nXSize, int nBitShift, size_t nDigitShift, DIGIT *pnX);
    static size_t ShiftRightInPlace(size_t nXSize, int nBitShift, size_t nDigitShift, DIGIT *pnX);
};
