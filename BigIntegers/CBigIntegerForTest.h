#include "Constants.h"
class CBigIntegerForTest : public CBigInteger
{
public: // functions
    // Sets the integer to a new, nonnegative random value of the size (in bits) given.
    // If the seed is passed and non-NULL, it is used to reseed the random
    // number generator.
    // returns false on failure (out of memory)
    bool SetRandom(size_t nNumBits, unsigned int nSeed=0)
    {
        size_t nLeadingBits;
        DIGIT  nVal;
        bool   bWorked      = false;
        m_nSize = (nNumBits+_DIGIT_SIZE_IN_BITS-1)/_DIGIT_SIZE_IN_BITS;
        if(Reserve(m_nSize))
        {
            nLeadingBits = nNumBits%_DIGIT_SIZE_IN_BITS;
            if(0!=nSeed)
            {
                srand(nSeed);
            }
            for(size_t i = 0;i<m_nSize;i++)
            {
                nVal = 0;
                for(size_t j=0;j<sizeof(DIGIT);j++)
                {
                    nVal |= ((DIGIT) ((rand()&(255<<4))>>4))<<(j<<3);
                }
                m_pnValue[i] = nVal;
            }
            if(0<nLeadingBits)
            {
                // pare down leading digit to appropriate size
                DIGIT nFOO = ((((DIGIT) 1)<<nLeadingBits)-1);
                nVal &= nFOO;
                m_pnValue[m_nSize-1] &= ((((DIGIT) 1)<<nLeadingBits)-1);
            }
            // prune leading 0s, if any
            if(0<m_nSize && 0==m_pnValue[m_nSize-1])
            {
                do
                {
                    m_nSize--;
                }
                while(0<m_nSize && 0==m_pnValue[m_nSize-1]);
            }
            m_bNegative = false;
            bWorked     = true;
        }
        return bWorked;
    }
};