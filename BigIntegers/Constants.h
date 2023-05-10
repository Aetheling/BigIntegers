#pragma once
//#define _USESMALLDIGITS 1
//#define _CollectDetailedTimingData 1
#ifdef _DEBUG
#define _BUFFERGUARD_SLOTS 1024
#endif
#ifndef _USESMALLDIGITS
// it is assumed that there are hardware operations that are used
// for add, multiply, etc on size_t
typedef unsigned _int64   DOUBLEDIGIT;
typedef unsigned _int32   DIGIT;
const DIGIT               BUFFERGUARD      = 0xABCDDCBA;
const DIGIT               TEST_BUFFERGUARD = 0xDCBAABCD;
#else
typedef unsigned _int32   DOUBLEDIGIT;
typedef unsigned _int16   DIGIT;
const DIGIT               BUFFERGUARD      = 0xABCD;
const DIGIT               TEST_BUFFERGUARD = 0xDCBA;
#endif

const unsigned _int32 c_nDigitSize = (sizeof(DIGIT)<<3);                     // size of a DIGIT, in bits
const DOUBLEDIGIT     c_nClearHigh = ((((DOUBLEDIGIT) 1)<<c_nDigitSize)-1);  // Mask to clear the
                                                                             // high-order bits of
                                                                             // a DOUBLEDIGIT
#ifndef _REGISTER_BLOCK_SIZE
#ifndef _USESMALLDIGITS
#define _REGISTER_BLOCK_SIZE 4    // may need to adjust with testing: min 1, max 6.  These sizes are right for my computer
#else
#define _REGISTER_BLOCK_SIZE 4
#endif
#endif
#ifndef _THRESHOLDS
#endif
