#include "AVXMultiply.h"

#if _USEAVX
void CAVXMultiply::PushAVXToDigitWithCarry(__m256i &val, DOUBLEDIGIT &nCarry, DIGIT *&pDest)
{
    // store the results.  Note just carryLow is complete.
    DOUBLEDIGIT nY0 = val.m256i_u64[0];
    DOUBLEDIGIT nY1 = val.m256i_u64[1];
    DOUBLEDIGIT nY2 = val.m256i_u64[2];
    DOUBLEDIGIT nY3 = val.m256i_u64[3];
    nCarry   += nY0;
    *pDest++ =  nCarry;
    nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS) + nY1;
    *pDest++ =  nCarry;
    nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS) + nY2;
    *pDest++ =  nCarry;
    nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS) + nY3;
    *pDest++ =  nCarry;
    nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS);
}

void CAVXMultiply::PushAddAVXToDigitWithCarry(__m256i &val, DOUBLEDIGIT &nCarry, DIGIT *&pDest)
{
    // store the results.  Note just carryLow is complete.
    // Note that by the way val is computed, val.m256i_u64[i] can be at most 12*0xFFFFFFFF (doing at most 12 DIGITs at a time)
    // so we don't need to worry about overflow
    DOUBLEDIGIT nY0 = val.m256i_u64[0];
    DOUBLEDIGIT nY1 = val.m256i_u64[1];
    DOUBLEDIGIT nY2 = val.m256i_u64[2];
    DOUBLEDIGIT nY3 = val.m256i_u64[3];
    nCarry   += (nY0 + *pDest);
    *pDest++ =  nCarry;
    nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS) + (nY1 + *pDest);
    *pDest++ =  nCarry;
    nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS) + (nY2 + *pDest);
    *pDest++ =  nCarry;
    nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS) + (nY3 + *pDest);
    *pDest++ =  nCarry;
    nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS);
}

void CAVXMultiply::PushAVXToDigitWithCarry(__m256i &val, DOUBLEDIGIT nCarry, DIGIT *pDest, DIGIT *pDestLim)
{
    // store the results.  Note just carryLow is complete.
    DOUBLEDIGIT nY0 = val.m256i_u64[0];
    DOUBLEDIGIT nY1 = val.m256i_u64[1];
    DOUBLEDIGIT nY2 = val.m256i_u64[2];
    DOUBLEDIGIT nY3 = val.m256i_u64[3];
    nCarry   += nY0;
    *pDest++ =  nCarry;
    if(pDest<pDestLim)
    {
        nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS) + nY1;
        *pDest++ =  nCarry;
        if(pDest<pDestLim)
        {
            nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS) + nY2;
            *pDest++ =  nCarry;
            if(pDest<pDestLim)
            {
                nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS) + nY3;
                *pDest++ =  nCarry;
            }
        }
    }
}

void CAVXMultiply::PushAddAVXToDigitWithCarry(__m256i &val, DOUBLEDIGIT &nCarry, DIGIT *&pDest, DIGIT *pDestLim)
{
    // store the results.  Note just carryLow is complete.
    // Note that by the way val is computed, val.m256i_u64[i] can be at most 12*0xFFFFFFFF (doing at most 12 DIGITs at a time)
    // so we don't need to worry about overflow
    DOUBLEDIGIT nY0 = val.m256i_u64[0];
    DOUBLEDIGIT nY1 = val.m256i_u64[1];
    DOUBLEDIGIT nY2 = val.m256i_u64[2];
    DOUBLEDIGIT nY3 = val.m256i_u64[3];
    nCarry   += (nY0 + *pDest);
    *pDest++ =  nCarry;
    if(pDest<pDestLim)
    {
        nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS) + (nY1 + *pDest);
        *pDest++ =  nCarry;
        if(pDest<pDestLim)
        {
            nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS) + (nY2 + *pDest);
            *pDest++ =  nCarry;
            if(pDest<pDestLim)
            {
                nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS) + (nY3 + *pDest);
                if(pDest<pDestLim) *pDest++ =  nCarry;
            }
        }
    }
    nCarry = (nCarry>>_DIGIT_SIZE_IN_BITS);
    while (nCarry)
    {
        nCarry   += *pDest;
        *pDest++ =  nCarry;
        nCarry   =  (nCarry>>_DIGIT_SIZE_IN_BITS);
    }
}

void CAVXMultiply::Mult4Cols(DIGIT y0, DIGIT y1, DIGIT y2, DIGIT y3,
                             __m256i &x,
                             __m256i &mult0, __m256i &mult1, __m256i &mult2, __m256i &mult3,
                             __m256i &carry, DOUBLEDIGIT &nCarry,
                             DIGIT *&pDest,
                             bool bAddToDest)
{
    const __m256i mask = _mm256_set1_epi64x(0xFFFFFFFF);
    __m256i acc;
    // cols 0-3
    acc   = _mm256_add_epi64(carry, _mm256_and_si256(mult0, mask)); // mult0, low order: cols 0-3
    // cols 1-4
    mult0 = _mm256_add_epi64(_mm256_srli_epi64(mult0, 32), _mm256_and_si256(mult1, mask));
    mult0 = _mm256_permute4x64_epi64(mult0, 147); // slot 0: 11, slot 1: 00, slot 2: 01, slot 3: 10 -> 10010011 = 147
    // add first digit of mult0 to carry; last 3 to acc
    acc   = _mm256_add_epi64(acc, _mm256_blend_epi32(mult0, _mm256_setzero_si256(), 3)); // a5 = 00000011: slots 0, 1 from mult1; rest are 0
    carry = _mm256_blend_epi32(_mm256_setzero_si256(), mult0, 3);
    // done wth mult0.  Set it up for the next iteration
    mult0 = _mm256_mul_epu32(x, _mm256_set1_epi64x(y0));

    // cols 2-5
    mult1 = _mm256_add_epi64(_mm256_srli_epi64(mult1, 32), _mm256_and_si256(mult2, mask)); // mult2: cols 2-5
    mult1 = _mm256_permute4x64_epi64(mult1, 78);  // slot 0: 10, slot 1: 11, slot 2: 00, slot 3: 01 -> 1001110 = 78
    // add first 2 digits of mult1 to carry; last 2 to acc
    acc   = _mm256_add_epi64(acc, _mm256_blend_epi32(mult1, _mm256_setzero_si256(), 15)); // a5 = 00001111: slots 0, 1, 2, 3 from mult2; rest are 0
    carry = _mm256_add_epi64(carry, _mm256_blend_epi32(_mm256_setzero_si256(), mult1, 15));
    // done with mult1.  Set it up for the next iteration
    mult1 = _mm256_mul_epu32(x, _mm256_set1_epi64x(y1));

    // cols 3-6
    mult2 = _mm256_add_epi64(_mm256_srli_epi64(mult2, 32), _mm256_and_si256(mult3, mask)); // mult3: cols 3-6
    mult2 = _mm256_permute4x64_epi64(mult2, 57);  // slot 0: 01, slot 1: 10, slot 2: 11, slot 3: 0 -> 111001 = 57
    // add first 3 digits of mult3 to carry; last digit to acc
    acc   = _mm256_add_epi64(acc, _mm256_blend_epi32(mult2, _mm256_setzero_si256(), 63)); // a5 = 00111111: slots 0, 1, 2, 3, 4, 5 from mult3; rest are 0
    carry = _mm256_add_epi64(carry, _mm256_blend_epi32(_mm256_setzero_si256(), mult2, 63));
    // done with mult2.  Set it up for the next iteration
    mult2 = _mm256_mul_epu32(x, _mm256_set1_epi64x(y2));

    // cols 4-7
    carry = _mm256_add_epi64(carry, _mm256_srli_epi64(mult3, 32));
    // done with mult3.  Set it up for the next iteration
    mult3 = _mm256_mul_epu32(x, _mm256_set1_epi64x(y3));

    // store the results
    if(bAddToDest) PushAddAVXToDigitWithCarry(acc, nCarry, pDest);
    else           PushAVXToDigitWithCarry(acc, nCarry, pDest);
}

void CAVXMultiply::Mult4Cols(__m256i &x, __m256i &mult0, __m256i &mult1, __m256i &mult2, __m256i &mult3, __m256i &carry, DOUBLEDIGIT &nCarry, DIGIT *&pDest, bool bAddToDest)
{
    const __m256i mask = _mm256_set1_epi64x(0xFFFFFFFF);
    __m256i acc;
    // cols 0-3
    acc   = _mm256_add_epi64(carry, _mm256_and_si256(mult0, mask)); // mult0, low order: cols 0-3
    // cols 1-4
    mult0 = _mm256_add_epi64(_mm256_srli_epi64(mult0, 32), _mm256_and_si256(mult1, mask));
    mult0 = _mm256_permute4x64_epi64(mult0, 147); // slot 0: 11, slot 1: 00, slot 2: 01, slot 3: 10 -> 10010011 = 147
    // add first digit of mult0 to carry; last 3 to acc
    acc   = _mm256_add_epi64(acc, _mm256_blend_epi32(mult0, _mm256_setzero_si256(), 3)); // a5 = 00000011: slots 0, 1 from mult1; rest are 0
    carry = _mm256_blend_epi32(_mm256_setzero_si256(), mult0, 3);

    // cols 2-5
    mult1 = _mm256_add_epi64(_mm256_srli_epi64(mult1, 32), _mm256_and_si256(mult2, mask)); // mult2: cols 2-5
    mult1 = _mm256_permute4x64_epi64(mult1, 78);  // slot 0: 10, slot 1: 11, slot 2: 00, slot 3: 01 -> 1001110 = 78
    // add first 2 digits of mult1 to carry; last 2 to acc
    acc   = _mm256_add_epi64(acc, _mm256_blend_epi32(mult1, _mm256_setzero_si256(), 15)); // a5 = 00001111: slots 0, 1, 2, 3 from mult2; rest are 0
    carry = _mm256_add_epi64(carry, _mm256_blend_epi32(_mm256_setzero_si256(), mult1, 15));

    // cols 3-6
    mult2 = _mm256_add_epi64(_mm256_srli_epi64(mult2, 32), _mm256_and_si256(mult3, mask)); // mult3: cols 3-6
    mult2 = _mm256_permute4x64_epi64(mult2, 57);  // slot 0: 01, slot 1: 10, slot 2: 11, slot 3: 0 -> 111001 = 57
    // add first 3 digits of mult3 to carry; last digit to acc
    acc   = _mm256_add_epi64(acc, _mm256_blend_epi32(mult2, _mm256_setzero_si256(), 63)); // a5 = 00111111: slots 0, 1, 2, 3, 4, 5 from mult3; rest are 0
    carry = _mm256_add_epi64(carry, _mm256_blend_epi32(_mm256_setzero_si256(), mult2, 63));

    // cols 4-7
    carry = _mm256_add_epi64(carry, _mm256_srli_epi64(mult3, 32));

    // store the results
    if(bAddToDest) PushAddAVXToDigitWithCarry(acc, nCarry, pDest);
    else           PushAVXToDigitWithCarry(acc, nCarry, pDest);
}

void CAVXMultiply::Mult4Cols(DIGIT y0, DIGIT y1, DIGIT y2, DIGIT y3,
                             __m256i &xLow, __m256i &xHigh,
                             __m256i &mult0Low, __m256i &mult0High, __m256i &mult1Low, __m256i &mult1High,
                             __m256i & carryLow, __m256i &carryMid, __m256i &carryHigh,
                             DOUBLEDIGIT &nCarry,
                             DIGIT *&pDest,
                             bool bAddToDest)
{
    const __m256i mask = _mm256_set1_epi64x(0xFFFFFFFF);
    __m256i tempA, tempB, y;
    // cols 0-7 (low & mid)
    // mult0Low has cols (3, 2, 1, 0) in low-order bits and cols (4, 3, 2, 1) in high-order bits
    // mult0High has cols (7, 6, 5, 4) in low-order bits and cols (8, 7, 6, 5) in high-order bits
    y         = _mm256_set1_epi64x(y2); // set up for next multiply
    carryLow  = _mm256_add_epi64(carryLow, _mm256_and_si256(mult0Low, mask)); // mult0, low order: cols 0-3
    carryMid  = _mm256_add_epi64(carryMid, _mm256_and_si256(mult0High, mask)); // mult0, low order: cols 4-7

    // cols 1-8 (low, mid, high):
    // mult0Low has data for cols 1-4 (high-order bits)
    // mult0High has data for 5-8 (high-order bits)
    // mult1Low has data for cols 1-4 (low-order bits)
    // mult1High has data for cols 5-8 (low-order bits)
    tempA     = _mm256_add_epi64(_mm256_srli_epi64(mult0Low, 32), _mm256_and_si256(mult1Low, mask));
    // note we don't need y0<xLow> any more.  Use mult0Low for y2<xLow>
    mult0Low  = _mm256_mul_epu32(xLow, y);
    tempB     = _mm256_add_epi64(_mm256_srli_epi64(mult0High, 32), _mm256_and_si256(mult1High, mask));
    // note we don't need y0<xHigh> any more.  Use mult0High for y2<xHigh>
    mult0High = _mm256_mul_epu32(xHigh, y);
    y         = _mm256_set1_epi64x(y3); // set up for next mutiply
    // slot 0: 11, slot 1: 00, slot 2: 01, slot 3: 10 -> 10010011 = 147.  So (a,b,c,d) -> (b,c,d,a) with leftmost slot high-order
    tempA     = _mm256_permute4x64_epi64(tempA, 147); // tempA now has data for cols (3, 2, 1 ,4)
    tempB     = _mm256_permute4x64_epi64(tempB, 147); // tempB now has data for cols (7, 6, 5, 8)
    // add cols 3, 2, 1 (from tempA) to carryLow and cols (7, 6, 5, 4) (from tempA and tempB) to carryMid
    carryLow  = _mm256_add_epi64(carryLow, _mm256_blend_epi32(tempA, _mm256_setzero_si256(), 3)); // a5 = 00000011: slots 0, 1 from mult1; rest are 0
    carryMid  = _mm256_add_epi64(carryMid, _mm256_blend_epi32(tempB, tempA, 3));
    // set carryHigh to col 8
    carryHigh = _mm256_blend_epi32(_mm256_setzero_si256(), tempB, 3);

    // cols 2-9
    // mult1Low has data for cols 2-5 (high-order bits)
    // mult1High has data for 6-9 (high-order bits)
    // mult0Low has data for cols 2-5 (low-order bits)
    // mult0High has data for cols 6-9 (low-order bits)
    tempA     = _mm256_add_epi64(_mm256_srli_epi64(mult1Low, 32), _mm256_and_si256(mult0Low, mask));
    // note we don't need y2<xLow> any more.  Use mult1Low for y3<xLow>
    mult1Low  = _mm256_mul_epu32(xLow, y);
    tempB     = _mm256_add_epi64(_mm256_srli_epi64(mult1High, 32), _mm256_and_si256(mult0High, mask));
    // note we don't need y2<xHigh> any more.  Use mult1High for y3<xHigh>
    mult1High = _mm256_mul_epu32(xHigh, y);
    y         = _mm256_set1_epi64x(y0); // set up for next mutiply
    // slot 0: 10, slot 1: 11, slot 2: 00, slot 3: 01 -> 1001110 = 78.  So (a,b,c,d) -> (c,d,a,b)
    tempA     = _mm256_permute4x64_epi64(tempA, 78); // tempA now has data for cols (3, 2, 5, 4)
    tempB     = _mm256_permute4x64_epi64(tempB, 78); // tempB now has data for cols (7, 6, 9, 8)
    // add cols 3, 2 (from tempA) to carryLow and cols 7, 6, 5, 4 (from tempB, tempA) to carryMid and cols 9, 8 (tempB) to carryHigh
    carryLow  = _mm256_add_epi64(carryLow, _mm256_blend_epi32(tempA, _mm256_setzero_si256(), 15)); // a5 = 00001111: slots 0, 1, 2, 3 from mult2; rest are 0
    carryMid  = _mm256_add_epi64(carryMid, _mm256_blend_epi32(tempB, tempA, 15));
    // add cols 9, 8 to carryHigh
    carryHigh = _mm256_add_epi64(carryHigh, _mm256_blend_epi32(_mm256_setzero_si256(), tempB, 15));

    // cols 3-10
    // mult0Low has data for cols 3-6 (high-order bits)
    // mult0High has data for 7-10 (high-order bits)
    // mult1Low has data for cols 3-6 (low-order bits)
    // mult1High has data for cols 7-10 (low-order bits)
    tempA     = _mm256_add_epi64(_mm256_srli_epi64(mult0Low, 32), _mm256_and_si256(mult1Low, mask));
    // note we don't need y3<xLow> any more.  Use mult0Low for y0<xLow>
    mult0Low  = _mm256_mul_epu32(xLow, y);
    tempB     = _mm256_add_epi64(_mm256_srli_epi64(mult0High, 32), _mm256_and_si256(mult1High, mask));
    // note we don't need y3<xHigh> any more.  Use mult0High for y0<xHigh>
    mult0High = _mm256_mul_epu32(xHigh, y);
    y         = _mm256_set1_epi64x(y1); // set up for next mutiply
    // slot 0: 01, slot 1 : 10, slot 2 : 11, slot 3 : 0 -> 111001 = 57  So (a, b, c, d) -> (d, a, b, c)
    tempA     = _mm256_permute4x64_epi64(tempA, 57); // tempA now has data for cols (3, 6, 5, 4)
    tempB     = _mm256_permute4x64_epi64(tempB, 57); // tempB now has data for cols (7, 10, 9, 8)
    // add col 3 (from tempA) to carryLow.  Add cols 7, 6, 5, 4 (from tempA, tempB) to carryMid.  Add cols 10, 9, 8 (from tempB) to carryHigh
    carryLow  = _mm256_add_epi64(carryLow, _mm256_blend_epi32(tempA, _mm256_setzero_si256(), 63)); // a5 = 00111111: slots 0, 1, 2, 3, 4, 5 from mult3; rest are 0
    carryMid  = _mm256_add_epi64(carryMid, _mm256_blend_epi32(tempB, tempA, 63));
    carryHigh = _mm256_add_epi64(carryHigh, _mm256_blend_epi32(_mm256_setzero_si256(), tempB, 63));

    // cols 4-11
    // mult1Low has data for cols 4-7 (high-order bits)
    // mult1High has data for cols 8-11 (high-order bits)
    carryMid  = _mm256_add_epi64(_mm256_srli_epi64(mult1Low, 32), carryMid);
    // note we don't need y0<xLow> any more.  Use mult1Low for y1<xLow>
    mult1Low  = _mm256_mul_epu32(xLow, y);
    carryHigh = _mm256_add_epi64(_mm256_srli_epi64(mult1High, 32), carryHigh);
    // note we don't need y3<xHigh> any more.  Use mult1High for y1<xHigh>
    mult1High = _mm256_mul_epu32(xHigh, y);

    // store the results.  Note just carryLow is complete.
    if(bAddToDest) PushAddAVXToDigitWithCarry(carryLow, nCarry, pDest);
    else           PushAVXToDigitWithCarry(carryLow, nCarry, pDest);
}

void CAVXMultiply::Mult4Cols(DIGIT y2, DIGIT y3,
                             __m256i &xLow, __m256i &xHigh,
                             __m256i &mult0Low, __m256i &mult0High, __m256i &mult1Low, __m256i &mult1High,
                             __m256i &carryLow, __m256i &carryMid, __m256i &carryHigh,
                             DOUBLEDIGIT &nCarry,
                             DIGIT *&pDest,
                             bool bAddToDest)
{
    const __m256i mask = _mm256_set1_epi64x(0xFFFFFFFF);
    __m256i tempA, tempB, y;
    y = _mm256_set1_epi64x(y2); // set up for next multiply
    // cols 0-7 (low & mid)
    // mult0Low has cols (3, 2, 1, 0) in low-order bits and cols (4, 3, 2, 1) in high-order bits
    // mult0High has cols (7, 6, 5, 4) in low-order bits and cols (8, 7, 6, 5) in high-order bits
    carryLow  = _mm256_add_epi64(carryLow, _mm256_and_si256(mult0Low, mask)); // mult0, low order: cols 0-3
    carryMid  = _mm256_add_epi64(carryMid, _mm256_and_si256(mult0High, mask)); // mult0, low order: cols 4-7

    // cols 1-8 (low, mid, high):
    // mult0Low has data for cols 1-4 (high-order bits)
    // mult0High has data for 5-8 (high-order bits)
    // mult1Low has data for cols 1-4 (low-order bits)
    // mult1High has data for cols 5-8 (low-order bits)
    tempA     = _mm256_add_epi64(_mm256_srli_epi64(mult0Low, 32), _mm256_and_si256(mult1Low, mask));
    // note we don't need y0<xLow> any more.  Use mult0Low for y2<xLow>
    mult0Low  = _mm256_mul_epu32(xLow, y);
    tempB     = _mm256_add_epi64(_mm256_srli_epi64(mult0High, 32), _mm256_and_si256(mult1High, mask));
    // note we don't need y0<xHigh> any more.  Use mult0High for y2<xHigh>
    mult0High = _mm256_mul_epu32(xHigh, y);
    y         = _mm256_set1_epi64x(y3); // set up for next mutiply
    // slot 0: 11, slot 1: 00, slot 2: 01, slot 3: 10 -> 10010011 = 147.  So (a,b,c,d) -> (b,c,d,a) with leftmost slot high-order
    tempA     = _mm256_permute4x64_epi64(tempA, 147); // tempA now has data for cols (3, 2, 1 ,4)
    tempB     = _mm256_permute4x64_epi64(tempB, 147); // tempB now has data for cols (7, 6, 5, 8)
    // add cols 3, 2, 1 (from tempA) to carryLow and cols (7, 6, 5, 4) (from tempA and tempB) to carryMid
    carryLow  = _mm256_add_epi64(carryLow, _mm256_blend_epi32(tempA, _mm256_setzero_si256(), 3)); // a5 = 00000011: slots 0, 1 from mult1; rest are 0
    // should be: last from b, first 3 from a\n");
    carryMid  = _mm256_add_epi64(carryMid, _mm256_blend_epi32(tempB, tempA, 3));
    // set carryHigh to col 8
    carryHigh = _mm256_blend_epi32(_mm256_setzero_si256(), tempB, 3);

    // cols 2-9
    // mult1Low has data for cols 2-5 (high-order bits)
    // mult1High has data for 6-9 (high-order bits)
    // mult0Low has data for cols 2-5 (low-order bits)
    // mult0High has data for cols 6-9 (low-order bits)
    tempA     = _mm256_add_epi64(_mm256_srli_epi64(mult1Low, 32), _mm256_and_si256(mult0Low, mask));
    // note we don't need y2<xLow> any more.  Use mult1Low for y3<xLow>
    mult1Low  = _mm256_mul_epu32(xLow, y);
    tempB     = _mm256_add_epi64(_mm256_srli_epi64(mult1High, 32), _mm256_and_si256(mult0High, mask));
    // note we don't need y2<xHigh> any more.  Use mult1High for y3<xHigh>
    mult1High = _mm256_mul_epu32(xHigh, y);
    // slot 0: 10, slot 1: 11, slot 2: 00, slot 3: 01 -> 1001110 = 78.  So (a,b,c,d) -> (c,d,a,b)
    tempA     = _mm256_permute4x64_epi64(tempA, 78); // tempA now has data for cols (3, 2, 5, 4)
    tempB     = _mm256_permute4x64_epi64(tempB, 78); // tempB now has data for cols (7, 6, 9, 8)
    // add cols 3, 2 (from tempA) to carryLow and cols 7, 6, 5, 4 (from tempB, tempA) to carryMid and cols 9, 8 (tempB) to carryHigh
    carryLow  = _mm256_add_epi64(carryLow, _mm256_blend_epi32(tempA, _mm256_setzero_si256(), 15)); // a5 = 00001111: slots 0, 1, 2, 3 from mult2; rest are 0
    carryMid  = _mm256_add_epi64(carryMid, _mm256_blend_epi32(tempB, tempA, 15));
    // add cols 9, 8 to carryHigh
    carryHigh = _mm256_add_epi64(carryHigh, _mm256_blend_epi32(_mm256_setzero_si256(), tempB, 15));

    // cols 3-10
    // mult0Low has data for cols 3-6 (high-order bits)
    // mult0High has data for 7-10 (high-order bits)
    // mult1Low has data for cols 3-6 (low-order bits)
    // mult1High has data for cols 7-10 (low-order bits)
    tempA     = _mm256_add_epi64(_mm256_srli_epi64(mult0Low, 32), _mm256_and_si256(mult1Low, mask));
    tempB     = _mm256_add_epi64(_mm256_srli_epi64(mult0High, 32), _mm256_and_si256(mult1High, mask));
    // slot 0: 01, slot 1 : 10, slot 2 : 11, slot 3 : 0 -> 111001 = 57  So (a, b, c, d) -> (d, a, b, c)
    tempA     = _mm256_permute4x64_epi64(tempA, 57); // tempA now has data for cols (3, 6, 5, 4)
    tempB     = _mm256_permute4x64_epi64(tempB, 57); // tempB now has data for cols (7, 10, 9, 8)
    // add col 3 (from tempA) to carryLow.  Add cols 7, 6, 5, 4 (from tampA, tampB) to carryMid.  Add cols 10, 9, 8 (from tempB) to carryHigh
    carryLow  = _mm256_add_epi64(carryLow, _mm256_blend_epi32(tempA, _mm256_setzero_si256(), 63)); // a5 = 00111111: slots 0, 1, 2, 3, 4, 5 from mult3; rest are 0
    carryMid  = _mm256_add_epi64(carryMid, _mm256_blend_epi32(tempB, tempA, 63));
    carryHigh = _mm256_add_epi64(carryHigh, _mm256_blend_epi32(_mm256_setzero_si256(), tempB, 63));

    // cols 4-11
    // mult1Low has data for cols 4-7 (high-order bits)
    // mult1High has data for cols 8-11 (high-order bits)
    carryMid  = _mm256_add_epi64(_mm256_srli_epi64(mult1Low, 32), carryMid);
    carryHigh = _mm256_add_epi64(_mm256_srli_epi64(mult1High, 32), carryHigh);

    // store the results.  Note just carryLow is complete.
    if(bAddToDest) PushAddAVXToDigitWithCarry(carryLow, nCarry, pDest);
    else           PushAVXToDigitWithCarry(carryLow, nCarry, pDest);
}

void CAVXMultiply::Mult4ColsTruncated(__m256i &mult0Low, __m256i &mult0High, __m256i &carryLow, __m256i &carryMid, __m256i &carryHigh, DOUBLEDIGIT &nCarry, DIGIT *&pDest, bool bAddToDest)
{
    const __m256i mask = _mm256_set1_epi64x(0xFFFFFFFF);
    __m256i tempA, tempB, y;
    // cols 0-7 (low & mid)
    // mult0Low has cols (3, 2, 1, 0) in low-order bits and cols (4, 3, 2, 1) in high-order bits
    // mult0High has cols (7, 6, 5, 4) in low-order bits and cols (8, 7, 6, 5) in high-order bits
    carryLow  = _mm256_add_epi64(carryLow, _mm256_and_si256(mult0Low, mask)); // mult0, low order: cols 0-3
    carryMid  = _mm256_add_epi64(carryMid, _mm256_and_si256(mult0High, mask)); // mult0, low order: cols 4-7

    // cols 1-8 (low, mid, high):
    // mult0Low has data for cols 1-4 (high-order bits)
    // mult0High has data for 5-8 (high-order bits)
    tempA     = _mm256_srli_epi64(mult0Low, 32);
    tempB     = _mm256_srli_epi64(mult0High, 32);
    // slot 0: 11, slot 1: 00, slot 2: 01, slot 3: 10 -> 10010011 = 147.  So (a,b,c,d) -> (b,c,d,a) with leftmost slot high-order
    tempA     = _mm256_permute4x64_epi64(tempA, 147); // tempA now has data for cols (3, 2, 1 ,4)
    tempB     = _mm256_permute4x64_epi64(tempB, 147); // tempB now has data for cols (7, 6, 5, 8)
    // add cols 3, 2, 1 (from tempA) to carryLow and cols (7, 6, 5, 4) (from tempA and tempB) to carryMid
    carryLow  = _mm256_add_epi64(carryLow, _mm256_blend_epi32(tempA, _mm256_setzero_si256(), 3)); // a5 = 00000011: slots 0, 1 from mult1; rest are 0
    carryMid  = _mm256_add_epi64(carryMid, _mm256_blend_epi32(tempB, tempA, 3));
    // set carryHigh to col 8
    carryHigh = _mm256_blend_epi32(_mm256_setzero_si256(), tempB, 3);
    // store the results.  Note just carryLow is complete.
    if(bAddToDest) PushAddAVXToDigitWithCarry(carryLow, nCarry, pDest);
    else           PushAVXToDigitWithCarry(carryLow, nCarry, pDest);
}

void CAVXMultiply::Mult4Cols(DIGIT y2, DIGIT y3, DIGIT y0_next, DIGIT y1_next,
                             __m256i &xLow,     __m256i &xMid,     __m256i &xHigh,
                             __m256i &mult0Low, __m256i &mult0Mid, __m256i &mult0High,
                             __m256i &mult1Low, __m256i &mult1Mid, __m256i &mult1High,
                             __m256i &carryA,   __m256i &carryB,   __m256i &carryC, __m256i &carryD,
                             DOUBLEDIGIT &nCarry,
                             DIGIT *&pDest,
                             bool bAddToDest)
{
    const __m256i mask = _mm256_set1_epi64x(0xFFFFFFFF);
    __m256i y, tempA, tempB, tempC;

    // prep y for the next multiplication
    y         = _mm256_set1_epi64x(y2); // latency 3, throughput 1? That's what _mm256_set_m128d is listed at
    // cols 0-11
    carryA    = _mm256_add_epi64(carryA, _mm256_and_si256(mult0Low, mask));
    carryB    = _mm256_add_epi64(carryB, _mm256_and_si256(mult0Mid, mask));
    carryC    = _mm256_add_epi64(carryC, _mm256_and_si256(mult0High, mask));

    // cols 1-12
    tempA     = _mm256_srli_epi64(mult0Low, 32);
    tempB     = _mm256_srli_epi64(mult0Mid, 32);
    tempC     = _mm256_srli_epi64(mult0High, 32);
    // note we don't need y0*<x> anymore.  Use mult0 to hold y2*<x>
    mult0Low  = _mm256_mul_epu32(y, xLow); // latency 5, throughput 0.5
    mult0Mid  = _mm256_mul_epu32(y, xMid);
    mult0High = _mm256_mul_epu32(y, xHigh);
    y         = _mm256_set1_epi64x(y3);
    tempA     = _mm256_add_epi64(tempA, _mm256_and_si256(mult1Low, mask)); // _mm256_add_epi64: latency 1, throughput 0.33
    tempB     = _mm256_add_epi64(tempB, _mm256_and_si256(mult1Mid, mask)); // _mm256_and_si256: latency 1, throughput 0.33
    tempC     = _mm256_add_epi64(tempC, _mm256_and_si256(mult1High, mask));
    // slot 0: 11, slot 1: 00, slot 2: 01, slot 3: 10 -> 10010011 = 147
    // So (a,b,c,d) -> (b,c,d,a)
    tempA     = _mm256_permute4x64_epi64(tempA, 147); // latency 3; throughput 1
    tempB     = _mm256_permute4x64_epi64(tempB, 147);
    tempC     = _mm256_permute4x64_epi64(tempC, 147);
    // add cols 3, 2, 1 (from tempA) to carryA and cols (7, 6, 5, 4) (from tempA and tempB) to carryB and cols (11, 10, 9, 8) (tempB, tempC) to carryC
    carryA    = _mm256_add_epi64(carryA, _mm256_blend_epi32(tempA, _mm256_setzero_si256(), 3)); // a5 = 00000011: slots 0, 1 from are 0; rest from tempA
    carryB    = _mm256_add_epi64(carryB, _mm256_blend_epi32(tempB, tempA, 3)); // _mm256_add_epi64: latency 1, throughput 0.33
    carryC    = _mm256_add_epi64(carryC, _mm256_blend_epi32(tempC, tempB, 3)); // _mm256_blend_epi32: latency 1, throughput 0.33
    // set carryD to col 12
    carryD    = _mm256_blend_epi32(_mm256_setzero_si256(), tempC, 3); // _mm256_setzero_si256: latency 1, throughput 0.33

    // cols 2-13
    tempA     = _mm256_srli_epi64(mult1Low, 32);  // latency 1, throughput 0.5
    tempB     = _mm256_srli_epi64(mult1Mid, 32);
    tempC     = _mm256_srli_epi64(mult1High, 32);
    // note we don't need y1*<x> anymore.  Use mult1 to hold y3*<x>
    mult1Low  = _mm256_mul_epu32(y, xLow);
    mult1Mid  = _mm256_mul_epu32(y, xMid);
    mult1High = _mm256_mul_epu32(y, xHigh);
    y         = _mm256_set1_epi64x(y0_next);
    tempA     = _mm256_add_epi64(tempA, _mm256_and_si256(mult0Low, mask));
    tempB     = _mm256_add_epi64(tempB, _mm256_and_si256(mult0Mid, mask));
    tempC     = _mm256_add_epi64(tempC, _mm256_and_si256(mult0High, mask));
    // slot 0: 10, slot 1: 11, slot 2: 00, slot 3: 01 -> 1001110 = 78.  So (a,b,c,d) -> (c,d,a,b)
    tempA     = _mm256_permute4x64_epi64(tempA, 78);
    tempB     = _mm256_permute4x64_epi64(tempB, 78);
    tempC     = _mm256_permute4x64_epi64(tempC, 78);
    // add cols in to the carry.
    carryA    = _mm256_add_epi64(carryA, _mm256_blend_epi32(tempA, _mm256_setzero_si256(), 15)); // a5 = 00001111: (x3, x2) from tempA; rest are 0
    carryB    = _mm256_add_epi64(carryB, _mm256_blend_epi32(tempB, tempA, 15));
    carryC    = _mm256_add_epi64(carryC, _mm256_blend_epi32(tempC, tempB, 15));
    carryD    = _mm256_add_epi64(carryD, _mm256_blend_epi32(_mm256_setzero_si256(), tempC, 15));

    // cols 3-14
    tempA     = _mm256_srli_epi64(mult0Low, 32);
    tempB     = _mm256_srli_epi64(mult0Mid, 32);
    tempC     = _mm256_srli_epi64(mult0High, 32);
    // note we don't need y2*<x> anymore.  Use mult0 to hold y0_next*<x>
    mult0Low  = _mm256_mul_epu32(y, xLow);
    mult0Mid  = _mm256_mul_epu32(y, xMid);
    mult0High = _mm256_mul_epu32(y, xHigh);
    y         = _mm256_set1_epi64x(y1_next);
    tempA     = _mm256_add_epi64(tempA, _mm256_and_si256(mult1Low, mask));
    tempB     = _mm256_add_epi64(tempB, _mm256_and_si256(mult1Mid, mask));
    tempC     = _mm256_add_epi64(tempC, _mm256_and_si256(mult1High, mask));
    // slot 0: 01, slot 1 : 10, slot 2 : 11, slot 3 : 0 -> 111001 = 57  So (a, b, c, d) -> (d, a, b, c)
    tempA     = _mm256_permute4x64_epi64(tempA, 57);
    tempB     = _mm256_permute4x64_epi64(tempB, 57);
    tempC     = _mm256_permute4x64_epi64(tempC, 57);
    // add cols in to the carry.
    carryA    = _mm256_add_epi64(carryA, _mm256_blend_epi32(tempA, _mm256_setzero_si256(), 63)); // a5 = 00111111: slots 0, 1, 2, 3, 4, 5 from mult3; rest are 0
    carryB    = _mm256_add_epi64(carryB, _mm256_blend_epi32(tempB, tempA, 63));
    carryC    = _mm256_add_epi64(carryC, _mm256_blend_epi32(tempC, tempB, 63));
    carryD    = _mm256_add_epi64(carryD, _mm256_blend_epi32(_mm256_setzero_si256(), tempC, 63));

    // cols 4-15
    carryB    = _mm256_add_epi64(_mm256_srli_epi64(mult1Low, 32), carryB);
    carryC    = _mm256_add_epi64(_mm256_srli_epi64(mult1Mid, 32), carryC);
    carryD    = _mm256_add_epi64(_mm256_srli_epi64(mult1High, 32), carryD);
    // note we don't need y3*<x> anymore.  Use mult1 to hold y1_next*<x>
    mult1Low  = _mm256_mul_epu32(y, xLow);
    mult1Mid  = _mm256_mul_epu32(y, xMid);
    mult1High = _mm256_mul_epu32(y, xHigh);

    // store results.  Note only carryA is complete
    if(bAddToDest) PushAddAVXToDigitWithCarry(carryA, nCarry, pDest);
    else           PushAVXToDigitWithCarry(carryA, nCarry, pDest);
}

void CAVXMultiply::Mult8DigitsFinish(const DIGIT *pY, const DIGIT *yLim,
                                     __m256i &xLow, __m256i &xHigh,
                                     __m256i &mult0, __m256i &mult1, __m256i &mult2, __m256i &mult3,
                                     __m256i &carryLow, __m256i &carryMid, __m256i &carryHigh,
                                     DOUBLEDIGIT nCarry,
                                     DIGIT *pDest, DIGIT *pDestLim,
                                     bool bAddToDest)
{
    // limited digits to slurp
    DOUBLEDIGIT nY0, nY1, nY2, nY3;
    if (pY == yLim)
    {
        // done reading
        // final: don't need to precompute mult for next iteration
        Mult4Cols(0, 0, xLow, xHigh, mult0, mult1, mult2, mult3, carryLow, carryMid, carryHigh, nCarry, pDest, bAddToDest);
        if (bAddToDest)
        {
            // push the data out left in carryMid
            PushAddAVXToDigitWithCarry(carryMid, nCarry, pDest);
            // and carryHigh
            PushAddAVXToDigitWithCarry(carryHigh, nCarry, pDest, pDestLim);
        }
        else
        {
            // push the data out left in carryMid
            PushAVXToDigitWithCarry(carryMid, nCarry, pDest);
            // and carryHigh
            PushAVXToDigitWithCarry(carryHigh, nCarry, pDest, pDestLim);
        }
    }
    else
    {
        // more DIGITs to read
        DIGIT y0    = 0;
        DIGIT y1    = 0;
        DIGIT y3    = 0;
        DIGIT y2    = *pY++;
        bool  bFull = false;
        if (pY < yLim)
        {
            y3 = *pY++;
            if (pY < yLim)
            {
                y0    = *pY++;
                bFull = true;
            }
        }
        if (bFull)
        {
            // two more multiplies.  Could have an abbreviated version for Mult4Cols; know 0 == y1
            Mult4Cols(y0, y1, y2, y3, xLow, xHigh, mult0, mult1, mult2, mult3, carryLow, carryMid, carryHigh, nCarry, pDest, bAddToDest);
            // final: don't need to precompute mult for next iteration.  In fact, only mult0, mult1 are relevant -- and precomputed
            Mult4ColsTruncated(mult0, mult1, carryMid, carryHigh, carryLow, nCarry, pDest, bAddToDest);
            if (bAddToDest)
            {
                // push the data out left in carryHigh
                PushAddAVXToDigitWithCarry(carryHigh, nCarry, pDest);
                // and carryLow
                PushAddAVXToDigitWithCarry(carryLow, nCarry, pDest, pDestLim);
            }
            else
            {
                // push the data out left in carryHigh
                PushAVXToDigitWithCarry(carryHigh, nCarry, pDest);
                // and carryLow
                PushAVXToDigitWithCarry(carryLow, nCarry, pDest, pDestLim);
            }
        }
        else
        {
            // one more multiply, and we're done.  Don't need to precompute mult for next iteration
            Mult4Cols(y2, y3, xLow, xHigh, mult0, mult1, mult2, mult3, carryLow, carryMid, carryHigh, nCarry, pDest, bAddToDest);
            if (bAddToDest)
            {
                // push the data out left in carryMid
                PushAddAVXToDigitWithCarry(carryMid, nCarry, pDest);
                // and carryHigh
                PushAddAVXToDigitWithCarry(carryHigh, nCarry, pDest, pDestLim);
            }
            else
            {
                // push the data out left in carryMid
                PushAVXToDigitWithCarry(carryMid, nCarry, pDest);
                // and carryHigh
                PushAVXToDigitWithCarry(carryHigh, nCarry, pDest, pDestLim);
            }
        }
    }
}

void CAVXMultiply::Mult12DigitsFinish(const DIGIT *pY, const DIGIT *yLim,
                                      __m256i &xLow, __m256i &xMid, __m256i &xHigh,
                                      __m256i &mult0Low, __m256i &mult0Mid, __m256i &mult0High, __m256i &mult1Low, __m256i &mult1Mid, __m256i &mult1High,
                                      __m256i &carryA, __m256i &carryB, __m256i &carryC, __m256i &carryD,
                                      DOUBLEDIGIT nCarry,
                                      DIGIT *pDest, DIGIT *pDestLim,
                                      bool bAddToDest)
{
    DIGIT y0_next, y1_next, y2, y3, dummy;
    bool  bFull = false;
    y0_next = 0;
    y1_next = 0;
    y2      = 0;
    y3      = 0;
    if (pY < yLim)
    {
        y2 = *pY++;
        if (pY < yLim)
        {
            y3 = *pY++;
            if (pY < yLim)
            {
                y0_next = *pY++;
                bFull   = true;
            }
        }
    }
    Mult4Cols(y2, y3, y0_next, y1_next, xLow, xMid, xHigh, mult0Low, mult0Mid, mult0High, mult1Low, mult1Mid, mult1High, carryA, carryB, carryC, carryD, nCarry, pDest, bAddToDest);
    if (bFull)
    {
        // one more multiply to do
        Mult4Cols(0, 0, 0, 0, xLow, xMid, xHigh, mult0Low, mult0Mid, mult0High, mult1Low, mult1Mid, mult1High, carryB, carryC, carryD, carryA, nCarry, pDest, bAddToDest);
        // push out residual data
        if (bAddToDest)
        {
            PushAddAVXToDigitWithCarry(carryC, nCarry, pDest);
            PushAddAVXToDigitWithCarry(carryD, nCarry, pDest);
            PushAddAVXToDigitWithCarry(carryA, nCarry, pDest, pDestLim);
        }
        else
        {
            PushAVXToDigitWithCarry(carryC, nCarry, pDest);
            PushAVXToDigitWithCarry(carryD, nCarry, pDest);
            PushAVXToDigitWithCarry(carryA, nCarry, pDest, pDestLim);
        }
    }
    else
    {
        // push out residual data
        if (bAddToDest)
        {
            PushAddAVXToDigitWithCarry(carryB, nCarry, pDest);
            PushAddAVXToDigitWithCarry(carryC, nCarry, pDest);
            PushAddAVXToDigitWithCarry(carryD, nCarry, pDest, pDestLim);
        }
        else
        {
            PushAVXToDigitWithCarry(carryB, nCarry, pDest);
            PushAVXToDigitWithCarry(carryC, nCarry, pDest);
            PushAVXToDigitWithCarry(carryD, nCarry, pDest, pDestLim);
        }
    }
}

void CAVXMultiply::Mult4DigitX(const DIGIT *pX, const DIGIT *pY, size_t nYDigits, DIGIT *pZ, bool bAddToSum)
{
    DOUBLEDIGIT         sum, carry, nY0, nY1, nY2, nY3;
    __m256i             xVec, carryVec;// , * pDest = (__m256i*) pWork;
    __m256i             mult0, mult1, mult2, mult3;
    const DIGIT         *yLim = pY + nYDigits;
    DIGIT               *zLim = pZ + 4 + nYDigits;

    xVec     = _mm256_cvtepu32_epi64(_mm_lddqu_si128((__m128i *) pX));
    carryVec = _mm256_setzero_si256();
    mult0    = _mm256_mul_epu32(xVec, _mm256_set1_epi64x(*pY++));
    mult1    = _mm256_mul_epu32(xVec, _mm256_set1_epi64x(*pY++));
    mult2    = _mm256_mul_epu32(xVec, _mm256_set1_epi64x(*pY++));
    mult3    = _mm256_mul_epu32(xVec, _mm256_set1_epi64x(*pY++));
    carry    = 0;
    for(; pY<yLim-4; pY += 4)
    {
        Mult4Cols(pY[0], pY[1], pY[2], pY[3], xVec, mult0, mult1, mult2, mult3, carryVec, carry, pZ, bAddToSum);
    }
    DIGIT y0, y1=0, y2=0, y3=0;
    y0 = *pY++;
    if (pY < yLim)
    {
        y1 = *pY++;
        if (pY < yLim)
        {
            y2 = *pY++;
            if (pY < yLim)
            {
                y3 = *pY;
            }
        }
    }
    Mult4Cols(y0, y1, y2, y3, xVec, mult0, mult1, mult2, mult3, carryVec, carry, pZ, bAddToSum);
    if (4 != nYDigits)
    {
        Mult4Cols(xVec, mult0, mult1, mult2, mult3, carryVec, carry, pZ, bAddToSum);
    }
    // push the data out left in carryVec
    if(bAddToSum) PushAddAVXToDigitWithCarry(carryVec, carry, pZ, zLim);
    else          PushAVXToDigitWithCarry(carryVec, carry, pZ, zLim);
}

void CAVXMultiply::Mult8DigitX(const DIGIT *pX, const DIGIT *pY, size_t nYDigits, DIGIT *pZ, bool bAddToSum)
{
    __m256i     xLow, xHigh, carryLow, carryMid, carryHigh;
    __m256i     mult0, mult1, mult2, mult3;
    const DIGIT *yLim = pY + nYDigits;
    DIGIT       *zLim = pZ + nYDigits + 8;
    DIGIT       y0, y1 = 0, y2 = 0, y3 = 0;
    DOUBLEDIGIT nCarry = 0;

    xLow     = _mm256_cvtepu32_epi64(_mm_lddqu_si128((__m128i *) pX));
    xHigh    = _mm256_cvtepu32_epi64(_mm_lddqu_si128((__m128i *) (pX+4)));
    y0       = *pY++;
    y1       = *pY++;
    mult1    = _mm256_set1_epi64x(y0);
    mult3    = _mm256_set1_epi64x(y1);
    mult0    = _mm256_mul_epu32(xLow, mult1);
    mult1    = _mm256_mul_epu32(xHigh, mult1);
    mult2    = _mm256_mul_epu32(xLow, mult3);
    mult3    = _mm256_mul_epu32(xHigh, mult3);
    carryLow = _mm256_setzero_si256();
    carryMid = _mm256_setzero_si256();
    if (13 < nYDigits)
    {
        // at least 12 more DIGITs of y to read
        yLim -= 11;
        for (; pY<yLim;)
        {
            y2 = *pY++;
            y3 = *pY++;
            y0 = *pY++;
            y1 = *pY++;
            // use digits 0-3, read through digit 5
            Mult4Cols(y0, y1, y2, y3, xLow, xHigh, mult0, mult1, mult2, mult3, carryLow, carryMid, carryHigh, nCarry, pZ, bAddToSum);
            y2 = *pY++;
            y3 = *pY++;
            y0 = *pY++;
            y1 = *pY++;
            // use digits 4-7, read through digit 9
            Mult4Cols(y0, y1, y2, y3, xLow, xHigh, mult0, mult1, mult2, mult3, carryMid, carryHigh, carryLow, nCarry, pZ, bAddToSum);
            y2 = *pY++;
            y3 = *pY++;
            y0 = *pY++;
            y1 = *pY++;
            // use digits 8-11, read through digit 13
            // Okay; compiler...  issues.  If I leave out this empty work, or don't force Mult4ColsTwiddle to NOT inline, the code generates
            // the wrong answer, every time.  With this bit of extra work, or forcing Mult4ColsTwiddle to not inline, it works every time.
            // Looks like the compiler is incorrectly optimizing stuff away? xxx
            for (int i = 0; i < 1; i++)
            {
            }
            Mult4Cols(y0, y1, y2, y3, xLow, xHigh, mult0, mult1, mult2, mult3, carryHigh, carryLow, carryMid, nCarry, pZ, bAddToSum);
        }
        yLim += 11;
    }
    // at this point we have between 0 and 11 more DIGITs of y to read, and 2-13 more DIGITs to compute
    if (pY + 3 < yLim)
    {
        // slurp through another 4 digits
        y2 = *pY++;
        y3 = *pY++;
        y0 = *pY++;
        y1 = *pY++;
        // use digits 0-3, read through digit 5
        Mult4Cols(y0, y1, y2, y3, xLow, xHigh, mult0, mult1, mult2, mult3, carryLow, carryMid, carryHigh, nCarry, pZ, bAddToSum);
        if (pY + 3 < yLim)
        {
            // slurp through ANOTHER 4 digits -- last we can do
            y2 = *pY++;
            y3 = *pY++;
            y0 = *pY++;
            y1 = *pY++;
            // use digits 4-7, read through digit 9
            Mult4Cols(y0, y1, y2, y3, xLow, xHigh, mult0, mult1, mult2, mult3, carryMid, carryHigh, carryLow, nCarry, pZ, bAddToSum);
            Mult8DigitsFinish(pY, yLim, xLow, xHigh, mult0, mult1, mult2, mult3, carryHigh, carryLow, carryMid, nCarry, pZ, zLim, bAddToSum);
        }
        else
        {
            Mult8DigitsFinish(pY, yLim, xLow, xHigh, mult0, mult1, mult2, mult3, carryMid, carryHigh, carryLow, nCarry, pZ, zLim, bAddToSum);
        }
    }
    else
    {
        Mult8DigitsFinish(pY, yLim, xLow, xHigh, mult0, mult1, mult2, mult3, carryLow, carryMid, carryHigh, nCarry, pZ, zLim, bAddToSum);
    }
}

void CAVXMultiply::Mult12DigitX(const DIGIT *pX, const DIGIT *pY, size_t nYDigits, DIGIT *pZ, bool bAddToSum)
{
    DOUBLEDIGIT carry;
    __m256i     xLow, xMid, xHigh, carryA, carryB, carryC, carryD;
    __m256i     mult0A, mult0B, mult0C, mult1A, mult1B, mult1C;
    const DIGIT *yLim = pY + nYDigits;
    DIGIT       *pZLim = pZ + 12 +nYDigits;
    DIGIT y0, y1 = 0, y2 = 0, y3 = 0;

    xLow   = _mm256_cvtepu32_epi64(_mm_lddqu_si128((__m128i*) pX));
    xMid   = _mm256_cvtepu32_epi64(_mm_lddqu_si128((__m128i*) (pX + 4)));
    xHigh  = _mm256_cvtepu32_epi64(_mm_lddqu_si128((__m128i*) (pX + 8)));
    y0     = *pY++;
    y1     = *pY++;
    mult0C = _mm256_set1_epi64x(y0);
    mult1C = _mm256_set1_epi64x(y1);
    mult0A = _mm256_mul_epu32(xLow, mult0C);
    mult0B = _mm256_mul_epu32(xMid, mult0C);
    mult0C = _mm256_mul_epu32(xHigh, mult0C);
    mult1A = _mm256_mul_epu32(xLow, mult1C);
    mult1B = _mm256_mul_epu32(xMid, mult1C);
    mult1C = _mm256_mul_epu32(xHigh, mult1C);
    carryA = _mm256_setzero_si256();
    carryB = _mm256_setzero_si256();
    carryC = _mm256_setzero_si256();
    carry  = 0;
    if (17 < nYDigits)
    {
        // at least 12 more DIGITs of y to read
        yLim -= 15;
        for (; pY < yLim;)
        {
            y2 = *pY++;
            y3 = *pY++;
            y0 = *pY++;
            y1 = *pY++;
            Mult4Cols(y2, y3, y0, y1, xLow, xMid, xHigh, mult0A, mult0B, mult0C, mult1A, mult1B, mult1C, carryA, carryB, carryC, carryD, carry, pZ, bAddToSum);
            y2 = *pY++;
            y3 = *pY++;
            y0 = *pY++;
            y1 = *pY++;
            Mult4Cols(y2, y3, y0, y1, xLow, xMid, xHigh, mult0A, mult0B, mult0C, mult1A, mult1B, mult1C, carryB, carryC, carryD, carryA, carry, pZ, bAddToSum);
            y2 = *pY++;
            y3 = *pY++;
            y0 = *pY++;
            y1 = *pY++;
            Mult4Cols(y2, y3, y0, y1, xLow, xMid, xHigh, mult0A, mult0B, mult0C, mult1A, mult1B, mult1C, carryC, carryD, carryA, carryB, carry, pZ, bAddToSum);
            y2 = *pY++;
            y3 = *pY++;
            y0 = *pY++;
            y1 = *pY++;
            // Okay; compiler...  issues.  If I leave out this empty work, or don't force Mult4ColsTwiddle to NOT inline, the code generates
            // the wrong answer, every time.  With this bit of extra work, or forcing Mult4ColsTwiddle to not inline, it works every time.
            // Looks like the compiler is incorrectly optimizing stuff away? xxx
            for(int i=0;i<2;i++) ;
            Mult4Cols(y2, y3, y0, y1, xLow, xMid, xHigh, mult0A, mult0B, mult0C, mult1A, mult1B, mult1C, carryD, carryA, carryB, carryC, carry, pZ, bAddToSum);
        }
        yLim += 15;
    }
    // at this point we have between 0 and 15 more DIGITs of y to read, and 2-15 more DIGITs to compute
    if (pY + 3 < yLim)
    {
        // slurp through another 4 digits
        y2 = *pY++;
        y3 = *pY++;
        y0 = *pY++;
        y1 = *pY++;
        Mult4Cols(y2, y3, y0, y1, xLow, xMid, xHigh, mult0A, mult0B, mult0C, mult1A, mult1B, mult1C, carryA, carryB, carryC, carryD, carry, pZ, bAddToSum);
        if (pY + 3 < yLim)
        {
            // slurp through another 4 digits
            y2 = *pY++;
            y3 = *pY++;
            y0 = *pY++;
            y1 = *pY++;
            Mult4Cols(y2, y3, y0, y1, xLow, xMid, xHigh, mult0A, mult0B, mult0C, mult1A, mult1B, mult1C, carryB, carryC, carryD, carryA, carry, pZ, bAddToSum);
            if (pY + 3 < yLim)
            {
                // slurp through ANOTHER 4 digits -- last full chunk left
                y2 = *pY++;
                y3 = *pY++;
                y0 = *pY++;
                y1 = *pY++;
                Mult4Cols(y2, y3, y0, y1, xLow, xMid, xHigh, mult0A, mult0B, mult0C, mult1A, mult1B, mult1C, carryC, carryD, carryA, carryB, carry, pZ, bAddToSum);
                // residual digits
                Mult12DigitsFinish(pY, yLim, xLow, xMid, xHigh, mult0A, mult0B, mult0C, mult1A, mult1B, mult1C, carryD, carryA, carryB, carryC, carry, pZ, pZLim, bAddToSum);
            }
            else
            {
                // residual digits
                Mult12DigitsFinish(pY, yLim, xLow, xMid, xHigh, mult0A, mult0B, mult0C, mult1A, mult1B, mult1C, carryC, carryD, carryA, carryB, carry, pZ, pZLim, bAddToSum);
            }
        }
        else
        {
            // residual digits
            Mult12DigitsFinish(pY, yLim, xLow, xMid, xHigh, mult0A, mult0B, mult0C, mult1A, mult1B, mult1C, carryB, carryC, carryD, carryA, carry, pZ, pZLim, bAddToSum);
        }
    }
    else
    {
        // residual digits
        Mult12DigitsFinish(pY, yLim, xLow, xMid, xHigh, mult0A, mult0B, mult0C, mult1A, mult1B, mult1C, carryA, carryB, carryC, carryD, carry, pZ, pZLim, bAddToSum);
    }
}
#endif