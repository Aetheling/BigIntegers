#pragma once
#include "CWorkspace.h"
#include "BigIntegers.h"

CWorkspace::CWorkspace()
{
    m_nSize  = 0;
    m_pSpace = NULL;
}

CWorkspace::~CWorkspace()
{
    free(m_pSpace);
}

size_t CWorkspace::GetSize()
{
    return m_nSize;
}

DIGIT *CWorkspace::GetSpace()
{
    return m_pSpace;
}

// resize to the given number of DIGITs
bool CWorkspace::Reserve(size_t i)
{
    size_t nNewSize;
#ifdef _DEBUG
    // validate didn't overrun workspace
    if (0<m_nSize)
    {
        for(int j=0; j<_BUFFERGUARD_SLOTS; j++)
        {
            if(BUFFERGUARD != m_pSpace[m_nSize+j])
            {
                printf("Overran workspace\n");
            }
        }
    }
#endif
    if(i>m_nSize)
    {
        free(m_pSpace);
        m_pSpace = NULL;
#ifdef _DEBUG
        // a little extra space for a buffer guard
        nNewSize = sizeof(DIGIT)*(_BUFFERGUARD_SLOTS+i);
        if(nNewSize/sizeof(DIGIT)==(_BUFFERGUARD_SLOTS+i))  // didn't trigger overflow -- size is okay
#else
        nNewSize = sizeof(DIGIT)*i;
        if(nNewSize/sizeof(DIGIT)==i)  // didn't trigger overflow -- size is okay
#endif
        {
            m_pSpace = (DIGIT *) malloc(nNewSize);
        }
        if(m_pSpace)
        {
            m_nSize           = i;
#ifdef _DEBUG
            for(int j=0;j<_BUFFERGUARD_SLOTS;j++)
            {
                m_pSpace[m_nSize+j] = BUFFERGUARD;
            }
#endif
        }
        else
        {
            m_nSize = 0;
        }
        return (m_nSize>0);
    }
    return true;
}

void CWorkspace::Empty()
{
    free(m_pSpace);
    m_pSpace = NULL;
    m_nSize  = 0;
}
