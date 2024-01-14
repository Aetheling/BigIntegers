#pragma once
#include "Constants.h"
#include <immintrin.h>
class CAVXMultiply
{
#if _USEAVX
public: // functions
    // multiply X times Y.  X must have exactly 4 DIGITs, and Y must be at least 4 DIGITs.  XTimesY must have sufficient space
    // None of this is verified, naturally.
    // If bAddToSum is set, it compute z = x*y + z instead of z = x*y.  In this case it is assumed that z has leading zeros to
    // avoid overflow: to its size+1, or to nYDigits+5, whichever is greater.  Again, unchecked.
    static void Mult4DigitX(const DIGIT *pX, const DIGIT *pY, size_t nYDigits, DIGIT *pXTimesY, bool bAddToSum);
    // Same, but X is 8 DIGITs.
    static void Mult8DigitX(const DIGIT *pX, const DIGIT *pY, size_t nYDigits, DIGIT *pXTimesY, bool bAddToSum);
    // Same, but X is 12 DIGITs.
    static void Mult12DigitX(const DIGIT *pX, const DIGIT *pY, size_t nYDigits, DIGIT *pXTimesY, bool bAddToSum);
private: // functions
    // debug check todo: forceinline help?
    // push the values in val (uint64) to pDest (uint32), making sure of the carry.  Note highorder bits of slot 0 in val overlap
    // with low order bits of slot 1, etc
    __forceinline static void PushAVXToDigitWithCarry(__m256i &val, DOUBLEDIGIT &nCarry, DIGIT *&pDest);
    // Same, but adds carry to dest, rather than just assigning.
    __forceinline static void PushAddAVXToDigitWithCarry(__m256i &val, DOUBLEDIGIT &nCarry, DIGIT *&pDest);
    // as PushAVXToDigitWithCarry, but with a size bound on Dest -- for simplicity, at the end of a multiply we will compute some
    // extra zeros when the operands have sizes which are not multiples of 4, and Dest might not have the space to slot them.
    __forceinline static void PushAVXToDigitWithCarry(__m256i &val, DOUBLEDIGIT nCarry, DIGIT *pDest, DIGIT *pDestLim);
    // Same, but adds carry to dest, rather than just assigning.  Assumes Dest has a leading 0 which will prevent carry overflow
    __forceinline static void PushAddAVXToDigitWithCarry(__m256i &val, DOUBLEDIGIT &nCarry, DIGIT *&pDest, DIGIT *pDestLim);
    // Compute 4 columns of the output, where X has exactly 4 DIGITs
    // On entry mult0 - mult3 are y_i * <x> from previous 4 columns.  On exit, they are y_i>*<x> for the Y passed
    // Notation: when x is an __m256i containing 4 64-bit values, write x = (x3, x2, x1, x0) where x0 is x[0], x1 is x[1], etc
    __forceinline static void Mult4Cols(DIGIT y0, DIGIT y1, DIGIT y2, DIGIT y3,
                                        __m256i &x,
                                        __m256i &mult0, __m256i &mult1, __m256i &mult2, __m256i &mult3,
                                        __m256i &carry,
                                        DOUBLEDIGIT &nCarry, DIGIT *&pDest,
                                        bool bAddToDest);
    // final step for 4-DIGIT X -- don't need to set up for next iteration
    __forceinline static void Mult4Cols(__m256i &x, __m256i &mult0, __m256i &mult1, __m256i &mult2, __m256i &mult3, __m256i &carry, DOUBLEDIGIT &nCarry, DIGIT *&pDest, bool bAddToDest);
    // compute 4 columns of the output, where X has exactly 8 DIGITs
    // carryLow has data for cols (3, 2, 1, 0) on entry; carryMid cols (7,6,5,4).  carryHigh has junk
    __forceinline static void Mult4Cols(DIGIT y0, DIGIT y1, DIGIT y2, DIGIT y3,
                                        __m256i &xLow, __m256i &xHigh,
                                        __m256i &mult0Low, __m256i &mult0High, __m256i &mult1Low, __m256i &mult1High,
                                        __m256i &carryLow, __m256i &carryMid, __m256i &carryHigh,
                                        DOUBLEDIGIT &nCarry, DIGIT *&pDest,
                                        bool bAddToDest);
    // same, but don't need to precompute mult0, mult1 for next iteration
    __forceinline static void Mult4Cols(DIGIT y2, DIGIT y3,
                                        __m256i &xLow, __m256i &xHigh,
                                        __m256i &mult0Low, __m256i &mult0High, __m256i &mult1Low, __m256i &mult1High,
                                        __m256i &carryLow, __m256i &carryMid, __m256i &carryHigh,
                                        DOUBLEDIGIT &nCarry,
                                        DIGIT *&pDest,
                                        bool bAddToDest);
    // x has exactly 8 DIGITs; only care about mult0Low, mult0High
    __forceinline static void Mult4ColsTruncated(__m256i &mult0Low, __m256i &mult0High, __m256i &carryLow, __m256i &carryMid, __m256i &carryHigh, DOUBLEDIGIT &nCarry, DIGIT *&pDest, bool bAddToDest);
    // compute 4 columns of the output, where X has exactly 12 DIGITs
    // On entry, carryA contains data for cols 0-3, carryB for cols 4-7, carryC cols 8-11, and carryD garbage
    // mult0Low/Mid/High contains y0*<x>
    // mult1Low/Mid/High
    // on exit, mult0 contains y0*<x> for the NEXT iteration; mult1 for y1*<x>
    __forceinline static void Mult4Cols(DIGIT y2, DIGIT y3, DIGIT y0_next, DIGIT y1_next,
                                        __m256i &xLow,     __m256i &xMid,     __m256i &xHigh,
                                        __m256i &mult0Low, __m256i &mult0Mid, __m256i &mult0High,
                                        __m256i &mult1Low, __m256i &mult1Mid, __m256i &mult1High,
                                        __m256i &carryA,   __m256i &carryB,   __m256i &carryC, __m256i &carryD,
                                        DOUBLEDIGIT &nCarry,
                                        DIGIT *&pDest,
                                        bool bAddToDest);
    // compute the last few residual columns where X has exactly 8 DIGITs
    static void Mult8DigitsFinish(const DIGIT *pY, const DIGIT *yLim,
                                  __m256i &xLow, __m256i &xHigh,
                                  __m256i &mult0, __m256i &mult1, __m256i &mult2, __m256i &mult3,
                                  __m256i &carryLow, __m256i &carryMid, __m256i &carryHigh,
                                  DOUBLEDIGIT nCarry,
                                  DIGIT *pDest, DIGIT *zLim,
                                  bool bAddToDest);
    // compute the last few residual columns where X has exactly 12 DIGITs
    static void Mult12DigitsFinish(const DIGIT *pY, const DIGIT *yLim,
                                   __m256i &xLow, __m256i &xMid, __m256i &xHigh,
                                   __m256i &mult0Low, __m256i &mult0Mid, __m256i &mult0High, __m256i &mult1Low, __m256i &mult1Mid, __m256i &mult1High,
                                   __m256i &carryA, __m256i &carryB, __m256i &carryC, __m256i &carryD,
                                   DOUBLEDIGIT nCarry,
                                   DIGIT *pDest, DIGIT *pDestLim,
                                   bool bAddToDest);
#endif
};