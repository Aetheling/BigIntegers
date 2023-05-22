// some macros which will be used over and over again, to
// cut down on the code size: in effect, the dot-product of
// two vectors.  Used to cut down on the amount of code written
// for large multiplications: one dot-product/DIGIT
// Note that it is assumed that nA0-11 and nB0-b11 are of type DIGIT;
// nCar, nSum, and nProd of type DOUBLEDIGIT; and pDest is a pointer
// to a DIGIT
// nCar:  carry
// nProd: product
// nSum:  sum
// pDest: the "return" value -- the dot product
// DotMultN: dot product of 2 vectors of length N
//              Used by MultUShortLong
// DotMultAddN: dot product of two vectors of length N, added to the destination's initial value.
//              Used by MultAddUShortLong
#ifndef _MACROS
#define _MACROS 1
#define DotMult12(nA0,nA1,nA2,nA3,nA4,nA5,nA6,nA7,nA8,nA9,nA10,nA11,nB0,nB1,nB2,nB3,nB4,nB5,nB6,nB7,nB8,nB9,nB10,nB11,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA11)*nB11;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA10)*nB10;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA9)*nB9;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA8)*nB8;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA7)*nB7;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA6)*nB6;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA5)*nB5;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += nProd&c_nClearHigh;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;

#define DotMult11(nA0,nA1,nA2,nA3,nA4,nA5,nA6,nA7,nA8,nA9,nA10,nB0,nB1,nB2,nB3,nB4,nB5,nB6,nB7,nB8,nB9,nB10,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA10)*nB10;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA9)*nB9;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA8)*nB8;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA7)*nB7;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA6)*nB6;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA5)*nB5;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += nProd&c_nClearHigh;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;

#define DotMult10(nA0,nA1,nA2,nA3,nA4,nA5,nA6,nA7,nA8,nA9,nB0,nB1,nB2,nB3,nB4,nB5,nB6,nB7,nB8,nB9,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA9)*nB9;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA8)*nB8;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA7)*nB7;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA6)*nB6;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA5)*nB5;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += nProd&c_nClearHigh;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;

#define DotMult9(nA0,nA1,nA2,nA3,nA4,nA5,nA6,nA7,nA8,nB0,nB1,nB2,nB3,nB4,nB5,nB6,nB7,nB8,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA8)*nB8;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA7)*nB7;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA6)*nB6;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA5)*nB5;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += nProd&c_nClearHigh;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMult8(nA0,nA1,nA2,nA3,nA4,nA5,nA6,nA7,nB0,nB1,nB2,nB3,nB4,nB5,nB6,nB7,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA7)*nB7;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA6)*nB6;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA5)*nB5;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += nProd&c_nClearHigh;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMult7(nA0,nA1,nA2,nA3,nA4,nA5,nA6,nB0,nB1,nB2,nB3,nB4,nB5,nB6,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA6)*nB6;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA5)*nB5;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += nProd&c_nClearHigh;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMult6(nA0,nA1,nA2,nA3,nA4,nA5,nB0,nB1,nB2,nB3,nB4,nB5,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA5)*nB5;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += nProd&c_nClearHigh;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMult5(nA0,nA1,nA2,nA3,nA4,nB0,nB1,nB2,nB3,nB4,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += nProd&c_nClearHigh;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMult4(nA0,nA1,nA2,nA3,nB0,nB1,nB2,nB3,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += nProd&c_nClearHigh;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMult3(nA0,nA1,nA2,nB0,nB1,nB2,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += nProd&c_nClearHigh;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMult2(nA0,nA1,nB0,nB1,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += nProd&c_nClearHigh;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMultAdd12(nA0,nA1,nA2,nA3,nA4,nA5,nA6,nA7,nA8,nA9,nA10,nA11,nB0,nB1,nB2,nB3,nB4,nB5,nB6,nB7,nB8,nB9,nB10,nB11,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA11)*nB11;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA10)*nB10;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA9)*nB9;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA8)*nB8;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA7)*nB7;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA6)*nB6;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA5)*nB5;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += (nProd&c_nClearHigh) + *pDest;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;

#define DotMultAdd11(nA0,nA1,nA2,nA3,nA4,nA5,nA6,nA7,nA8,nA9,nA10,nB0,nB1,nB2,nB3,nB4,nB5,nB6,nB7,nB8,nB9,nB10,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA10)*nB10;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA9)*nB9;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA8)*nB8;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA7)*nB7;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA6)*nB6;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA5)*nB5;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += (nProd&c_nClearHigh) + *pDest;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;

#define DotMultAdd10(nA0,nA1,nA2,nA3,nA4,nA5,nA6,nA7,nA8,nA9,nB0,nB1,nB2,nB3,nB4,nB5,nB6,nB7,nB8,nB9,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA9)*nB9;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA8)*nB8;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA7)*nB7;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA6)*nB6;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA5)*nB5;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += (nProd&c_nClearHigh) + *pDest;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;

#define DotMultAdd9(nA0,nA1,nA2,nA3,nA4,nA5,nA6,nA7,nA8,nB0,nB1,nB2,nB3,nB4,nB5,nB6,nB7,nB8,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA8)*nB8;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA7)*nB7;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA6)*nB6;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA5)*nB5;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += (nProd&c_nClearHigh) + *pDest;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMultAdd8(nA0,nA1,nA2,nA3,nA4,nA5,nA6,nA7,nB0,nB1,nB2,nB3,nB4,nB5,nB6,nB7,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA7)*nB7;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA6)*nB6;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA5)*nB5;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += (nProd&c_nClearHigh) + *pDest;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMultAdd7(nA0,nA1,nA2,nA3,nA4,nA5,nA6,nB0,nB1,nB2,nB3,nB4,nB5,nB6,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA6)*nB6;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA5)*nB5;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += (nProd&c_nClearHigh) + *pDest;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMultAdd6(nA0,nA1,nA2,nA3,nA4,nA5,nB0,nB1,nB2,nB3,nB4,nB5,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA5)*nB5;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += (nProd&c_nClearHigh) + *pDest;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMultAdd5(nA0,nA1,nA2,nA3,nA4,nB0,nB1,nB2,nB3,nB4,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA4)*nB4;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += (nProd&c_nClearHigh) + *pDest;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMultAdd4(nA0,nA1,nA2,nA3,nB0,nB1,nB2,nB3,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA3)*nB3;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += (nProd&c_nClearHigh) + *pDest;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMultAdd3(nA0,nA1,nA2,nB0,nB1,nB2,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA2)*nB2;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     += (nProd&c_nClearHigh);\
    nCar     += nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += (nProd&c_nClearHigh) + *pDest;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;


#define DotMultAdd2(nA0,nA1,nB0,nB1,nCar,nSum,nProd,pDest)\
    nProd    =  ((DOUBLEDIGIT) nA1)*nB1;\
    nSum     =  (nProd&c_nClearHigh) + nCar;\
    nCar     =  nProd>>_DIGIT_SIZE_IN_BITS;\
    nProd    =  ((DOUBLEDIGIT) nA0)*nB0;\
    nSum     += (nProd&c_nClearHigh) + *pDest;\
    nCar     += (nProd>>_DIGIT_SIZE_IN_BITS)+(nSum>>_DIGIT_SIZE_IN_BITS);\
    *pDest++ =  (DIGIT) nSum;
#endif

// To multiply two numbers too far apart in size for the given base algorithm,
// but with the larger less than twice the size of the smaller.  X is smaller,
// Y is larger
#if(_CollectDetailedTimingData)
#define UNBALANCED_MULT(fAlgorithm,nXSize,nYSize,pX,pY,pProd,pnWorkspace,dwTimestamp,pnZSize)\
{\
	fAlgorithm(nXSize,nXSize,pX,pY+nYSize-nXSize,pProd+nYSize-nXSize,pnWorkspace,dwTimestamp);\
    FinishUnbalancedMult(nXSize,nYSize,pXValue,pYValue,pProd,dwTimestamp,pnWorkspace,pnZSize);\
}
#else
#define UNBALANCED_MULT(fAlgorithm,nXSize,nYSize,pX,pY,pProd,pnWorkspace,pnZSize)\
{\
	fAlgorithm(nXSize,nXSize,pX,pY+nYSize-nXSize,pProd+nYSize-nXSize,pnWorkspace);\
    FinishUnbalancedMult(nXSize,nYSize,pXValue,pYValue,pProd,pnWorkspace,pnZSize);\
}
#endif