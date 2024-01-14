#pragma once
//#define _CollectDetailedTimingData 1
/* with detailed timing data turned on, you will get perf results (when requested) that loo like this:
1 calls to multiply
  1032156 calls to Basic multiply:
    Basic multiply time:        816304 microseconds (0.790873 average)
  9 calls to 3 by 2 multiply:
    Construct subproblems time: 1 microseconds (0.111111 average)
    Combine subproblems time:   1 microseconds (0.111111 average)
  147447 calls to 7 by 4 multiply:
    Construct subproblems time: 58464 microseconds (0.396509 average)
    Combine subproblems time:   209420 microseconds (1.420307 average)
  16384 calls to 9 by 5 multiply:
    Construct subproblems time: 55997 microseconds (3.417786 average)
    Combine subproblems time:   154920 microseconds (9.455566 average)
  1 calls to FFT multiply:
    Construct subproblems time: 284072 microseconds (284072.000000 average)
    Combine subproblems time:   235555 microseconds (235555.000000 average)
Total multiply time: 1820531 microseconds (1820531.000000 average)

(this result was for multiplying two 8000000-BYTEs numbers)

or
Total calls to divide: 65536
  Time in recursive divide: 1808351 microseconds (27.593246 average)
  Time in multiplication:   5529082 microseconds (84.367096 average)
  Time in basic divide:     2174885 microseconds (33.186111 average)
  Total divide time:        10109892 microseconds (154.264709 average)

Note that the high performance timer call is an expensive operation; using it notably degrades performance!
*/
#ifdef _DEBUG
#define _BUFFERGUARD_SLOTS 1024
#endif
#define _DIGIT_SIZE_IN_BITS 32 // 16 or 32
#define _AVXInstructionsAvailable 1 // note that further flags for avx512 should be employed.  I don't have 'em on my computer, so can't verify any such code
// it is assumed that there are hardware operations that are used
// for add, multiply, etc on the chosen size
#define _USEAVX 0
#if(32==_DIGIT_SIZE_IN_BITS)
#undef _USEAVX
#define _USEAVX _AVXInstructionsAvailable
typedef unsigned _int64   DOUBLEDIGIT;
typedef unsigned _int32   DIGIT;
const DIGIT               BUFFERGUARD      = 0xABCDDCBA;
const DIGIT               TEST_BUFFERGUARD = 0xDCBAABCD;
#elif(16==_DIGIT_SIZE_IN_BITS)
typedef unsigned _int32   DOUBLEDIGIT;
typedef unsigned _int16   DIGIT;
const DIGIT               BUFFERGUARD      = 0xABCD;
const DIGIT               TEST_BUFFERGUARD = 0xDCBA;
#endif

const DOUBLEDIGIT     c_nClearHigh = ((((DOUBLEDIGIT) 1)<<_DIGIT_SIZE_IN_BITS)-1);  // Mask to clear the
                                                                                    // high-order bits of
                                                                                    // a DOUBLEDIGIT
#ifndef _REGISTER_BLOCK_SIZE
#if(32==_DIGIT_SIZE_IN_BITS)
#define _REGISTER_BLOCK_SIZE 4    // may need to adjust with testing: min 1, max 6.  These sizes are right for my computer
#elif(16==_DIGIT_SIZE_IN_BITS)
#define _REGISTER_BLOCK_SIZE 4
#endif
#endif
