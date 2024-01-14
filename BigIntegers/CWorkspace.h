#include "BigIntegers.h"
#pragma once
class __declspec(dllexport) CWorkspace
{
public:
    CWorkspace();
    ~CWorkspace();
    size_t GetSize();
    DIGIT *GetSpace();
    // resizes the workspace to the passed size in DIGITs, if it is greater
    // than the current size.  (If it cannot allocate the memory,
    // the workspace ends up with size 0.)
    bool Reserve(size_t i);
    // Frees all memory for the workspace, and sets its size to 0.
    void Empty();
    // vaccuous in retail.  Potentially useful in debugging.  Returns true if the buffer does not appear to have been overrun (or it's retail)
    _forceinline void CheckBufferguard() const
    {
#ifdef _DEBUG
        if (0<m_nSize)
        {
            for(int j=0; j<_BUFFERGUARD_SLOTS; j++)
            {
                if(BUFFERGUARD != m_pSpace[m_nSize+j])
                {
                    printf("Overran allocated memory space for workspace\n");
                    m_pSpace[m_nSize + j] = BUFFERGUARD;
                }
            }
        }
#endif
    }
protected:
    size_t  m_nSize;  // in DIGITs
    DIGIT   *m_pSpace;
};
