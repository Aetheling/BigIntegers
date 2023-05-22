#pragma once
//#define _CollectDetailedTimingData 1
#ifdef _DEBUG
#define _BUFFERGUARD_SLOTS 1024
#endif
#define _DIGIT_SIZE_IN_BITS 32 // 16 or 32
// it is assumed that there are hardware operations that are used
// for add, multiply, etc on the chosen size
#if(32==_DIGIT_SIZE_IN_BITS)
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
