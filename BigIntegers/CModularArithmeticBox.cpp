#include "BigIntegers.h"
#include "ArithmeticBox.h"
#include "CUnsignedArithmeticHelper.h"

CModularArithmeticBox::CModularArithmeticBox(const CBigInteger &nModulus, bool bProtectAgainstTimingAttacks)
{
    // copy N into the modulus
    m_Modulus = nModulus;
    m_bProtectAgainstTimingAttacks = bProtectAgainstTimingAttacks;
    ReserveMemory();
};

CModularArithmeticBox::CModularArithmeticBox(const char *szModulusExpressedInHexadecimal, bool bProtectAgainstTimingAttacks) : m_Modulus(szModulusExpressedInHexadecimal)
{
    m_bProtectAgainstTimingAttacks = bProtectAgainstTimingAttacks;
    ReserveMemory();
}

CModularArithmeticBox::~CModularArithmeticBox()
{
    // purely for symmetry
    ;
}

EArithmeticOperationResult CModularArithmeticBox::GetModulus(CBigInteger *pnModulusCopy)
{
    if(!(*pnModulusCopy = m_Modulus)) return eOutOfMemory;
    return eOperationSucceeded;
}

size_t CModularArithmeticBox::GetModulusSize()
{
    return m_Modulus.GetSize();
}

void CModularArithmeticBox::Import(CBigInteger *pX, CBigInteger *pXDivN)
{
    size_t nRemainderSize, nXDivModulusSize;
    if(m_Modulus.GetSize()<=pX->GetSize())
    {
        pXDivN->Reserve(pX->GetSize()-m_Modulus.GetSize()+1);
    }
    CUnsignedArithmeticHelper::Divide(pX->GetSize(),
                                      m_Modulus.GetSize(),
                                      nXDivModulusSize,
                                      nRemainderSize,
                                      pX->GetValue(),
                                      m_Modulus.GetValue(),
                                      pXDivN->GetValue(),
                                      m_Workspace.GetSpace());
    pX->SetSize(nRemainderSize);
    pX->Reserve(m_Modulus.GetSize()+1,true); // give 1 extra DIGIT to make addition easier -- needn't worry about overflow
    pXDivN->SetSize(nXDivModulusSize);
}

EArithmeticOperationResult CModularArithmeticBox::Add(const CBigInteger *pX,
                                                      const CBigInteger *pY,
                                                      CBigInteger       *pXPlusY)
{
    size_t                     nSumSize;
    bool                       bDummySign;
    EArithmeticOperationResult eResult = eOperationSucceeded;
    if(NULL==pX || NULL==pY || NULL == pXPlusY)
    {
        eResult = eBadArgument;
    }
    else
    {
        size_t nXSize = pX->GetSize();
        size_t nYSize = pY->GetSize();
        if (0 == nXSize && 0 == nYSize)
        {
            // special case -- back-end subtract doesn't handle both arguments
            // having size 0
            pXPlusY->SetSize(0);
            goto exit;
        }
        if (!pXPlusY->Reserve(m_Modulus.GetSize() + 1), (pXPlusY == pX) || (pXPlusY == pY))
        {
            eResult = eOutOfMemory;
            goto exit;
        }
        CUnsignedArithmeticHelper::AddSigned(nXSize, nYSize, nSumSize, pX->GetValue(), pY->GetValue(), pXPlusY->GetValue(), false, false, bDummySign);
        pXPlusY->SetSize(nSumSize);
        if(m_Modulus<=*pXPlusY)
        {
            // do modulus!!!
            CUnsignedArithmeticHelper::AddSigned(nSumSize, m_Modulus.GetSize(), nSumSize, pXPlusY->GetValue(), m_Modulus.GetValue(), pXPlusY->GetValue(), false, true, bDummySign);
            pXPlusY->SetSize(nSumSize);
        }
    }
exit:
    return eResult;
}

CBigInteger *CModularArithmeticBox::Add(const CBigInteger *pX, const CBigInteger *pY)
{
    CBigInteger *pXPlusY = new CBigInteger();
    if(eOperationSucceeded != Add(pX,pY,pXPlusY))
    {
        delete pXPlusY;
        pXPlusY = NULL;
    }
    return pXPlusY;
}

EArithmeticOperationResult CModularArithmeticBox::Subtract(const CBigInteger *pX,
                                                           const CBigInteger *pY,
                                                           CBigInteger       *pXMinusY)
{
    size_t                     nDiffSize;
    bool                       bDummySign;
    EArithmeticOperationResult eResult = eOperationSucceeded;
    if(NULL==pX || NULL==pY || NULL == pXMinusY)
    {
        eResult = eBadArgument;
        goto exit;
    }
    {
        size_t nXSize = pX->GetSize();
        size_t nYSize = pY->GetSize();
        if(0==nXSize && 0==nYSize)
        {
            // special case -- back-end subtract doesn't handle both arguments
            // having size 0
            pXMinusY->SetSize(0);
            goto exit;
        }
        // make sure destination has enough room for the result
        if(!pXMinusY->Reserve(m_Modulus.GetSize() + 1), (pXMinusY == pX) || (pXMinusY == pY))
        {
            eResult = eOutOfMemory;
            goto exit;
        }
        CUnsignedArithmeticHelper::AddSigned(nXSize, nYSize, nDiffSize, pX->GetValue(), pY->GetValue(), pXMinusY->GetValue(), false, true, bDummySign);
        if(bDummySign)
        {
            // x was smaller than y; add modulus to result to get it back in the range
            CUnsignedArithmeticHelper::AddSigned(nDiffSize, m_Modulus.GetSize(), nDiffSize, pXMinusY->GetValue(), m_Modulus.GetValue(), pXMinusY->GetValue(), true, false, bDummySign);
        }
        pXMinusY->SetSize(nDiffSize);
    }
exit:
    return eResult;
}

CBigInteger *CModularArithmeticBox::Subtract(const CBigInteger *pX, const CBigInteger *pY)
{
    CBigInteger *pXMinusY = new CBigInteger();
    if(eOperationSucceeded != Subtract(pX,pY,pXMinusY))
    {
        delete pXMinusY;
        pXMinusY = NULL;
    }
    return pXMinusY;
}

EArithmeticOperationResult CModularArithmeticBox::Multiply(const CBigInteger *pX,
                                                           const CBigInteger *pY,
                                                           CBigInteger       *pXTimesY)
{
    size_t nXDivYSize, nMultSize;
    EArithmeticOperationResult eResult = eOperationSucceeded;
    if(NULL==pX || NULL==pY || NULL==pXTimesY || pX==pXTimesY || pY==pXTimesY)
    {
        eResult = eBadArgument;
        goto exit;
    }
    {
        size_t nXSize = pX->GetSize();
        size_t nYSize = pY->GetSize();
        // helper functions assume nonzero operand sizes
        if (0 != nXSize && 0 != nYSize)
        {
            if (!pXTimesY->Reserve(nXSize + nYSize))
            {
                eResult = eOutOfMemory;
                goto exit;
            }
            // multiply
            CUnsignedArithmeticHelper::Multiply(nXSize, nYSize, pX->GetValue(), pY->GetValue(), pXTimesY->GetValue(), m_Workspace.GetSpace());
            // modulus
            nMultSize = nXSize + nYSize;
            if(0 == pXTimesY->GetValue()[nMultSize - 1]) nMultSize--;
            CUnsignedArithmeticHelper::Divide(nMultSize, m_Modulus.GetSize(), nXDivYSize, nMultSize, pXTimesY->GetValue(), m_Modulus.GetValue(), m_Workspace.GetSpace(), m_Workspace.GetSpace() + m_Modulus.GetSize() + 1);
            pXTimesY->SetSize(nMultSize);
        }
        else
        {
            pXTimesY->SetSize(0);
        }
    }
exit:
    return eResult;
}

EArithmeticOperationResult CModularArithmeticBox::Square(const CBigInteger *pX, CBigInteger *pXSquared)
{
    size_t nXDivYSize, nSquareSize;
    EArithmeticOperationResult eResult = eOperationSucceeded;
    if (NULL == pX || NULL == pXSquared || pX == pXSquared)
    {
        eResult = eBadArgument;
        goto exit;
    }
    {
        size_t nXSize = pX->GetSize();
        if (0 != nXSize)
        {
            // backend doesn't handle operands of size 0 gracefully
            if (!pXSquared->Reserve(nXSize << 1))
            {
                eResult = eOutOfMemory;
                goto exit;
            }
            // square
            CUnsignedArithmeticHelper::Square(nXSize, pX->GetValue(), pXSquared->GetValue(), m_Workspace.GetSpace());
            nSquareSize = (nXSize<<1);
            if(0==pXSquared->GetValue()[nSquareSize-1]) nSquareSize--;
            // modulus
            CUnsignedArithmeticHelper::Divide(nSquareSize, m_Modulus.GetSize(), nXDivYSize, nSquareSize, pXSquared->GetValue(), m_Modulus.GetValue(), m_Workspace.GetSpace(), m_Workspace.GetSpace() + m_Modulus.GetSize() + 1);
            pXSquared->SetSize(nSquareSize);
        }
        else
        {
            pXSquared->SetSize(0);
        }
    }
exit:
    return eResult;
}

CBigInteger *CModularArithmeticBox::Multiply(const CBigInteger *pX, const CBigInteger *pY)
{
    CBigInteger *pXTimesY = new CBigInteger();
    if(eOperationSucceeded != Multiply(pX,pY,pXTimesY))
    {
        delete pXTimesY;
        pXTimesY = NULL;
    }
    return pXTimesY;
}

EArithmeticOperationResult CModularArithmeticBox::MultiplyAdd(const CBigInteger *pX,
                                                              const CBigInteger *pY,
                                                              CBigInteger       *pRunningSum)
{
    size_t nXDivYSize,nRemainderSize;
    EArithmeticOperationResult eResult = eOperationSucceeded;
    if(NULL==pX || NULL==pY || NULL==pRunningSum || pX==pRunningSum || pY==pRunningSum)
    {
        eResult = eBadArgument;
        goto exit;
    }
    else
    {
        size_t nXSize = pX->GetSize();
        size_t nYSize = pY->GetSize();
        if (0 != nXSize && 0 != nYSize)
        {
            // back end doesn't handle operands of size 0 gracefully
            size_t nRunning = pRunningSum->GetSize();
            size_t needed   = max(nXSize + nYSize, nRunning) + 1;
            if (!pRunningSum->Reserve(needed, true))
            {
                eResult = eOutOfMemory;
                goto exit;
            }
            // make sure running has leading 0s -- required by mult/add
            for (size_t i = nRunning; i < needed; i++)
            {
                pRunningSum->m_pnValue[i] = 0;
            }
            // multiply/add
            CUnsignedArithmeticHelper::MultiplyAdd(nXSize, nYSize, nRunning, pX->GetValue(), pY->GetValue(), pRunningSum->GetValue(), m_Workspace.GetSpace());
            // modulus
            CUnsignedArithmeticHelper::Divide(nRunning, m_Modulus.GetSize(), nXDivYSize, nRemainderSize, pRunningSum->GetValue(), m_Modulus.GetValue(), m_Workspace.GetSpace(), m_Workspace.GetSpace() + m_Modulus.GetSize() + 2);
            pRunningSum->SetSize(nRemainderSize);
        }
    }
exit:
    return eResult;
}

EArithmeticOperationResult CModularArithmeticBox::Power(const CBigInteger *pX,
                                                        const CBigInteger *pY,
                                                        CBigInteger       *pXToY)
{
    size_t nPowerLeadDigit=0, nPowerLeadBit=0;
    if (m_bSuitableForMontgomery)
    {
        CUnsignedArithmeticHelper::GetLeadBit(pY->GetSize(), pY->GetValue(), nPowerLeadDigit, nPowerLeadBit);
    }
    return PowerLeadPowerDigitKnown(pX, pY, nPowerLeadDigit, nPowerLeadBit, pXToY);
}


EArithmeticOperationResult CModularArithmeticBox::PowerLeadPowerDigitKnown(const CBigInteger *pX,
                                                                           const CBigInteger *pY,
                                                                           size_t            nPowerLeadDigit,
                                                                           size_t            nPowerLeadBit,
                                                                           CBigInteger       *pXToY)
{
    size_t nRemainderSize;
    EArithmeticOperationResult eResult      = eOperationSucceeded;
    size_t                     nResultSpace = m_Modulus.GetSize();
    if(NULL==pX || NULL==pY || NULL==pXToY || pX==pXToY || pY==pXToY)
    {
        eResult = eBadArgument;
        goto exit;
    }
    if (!pXToY->Reserve(nResultSpace)) return eOutOfMemory;
    // some special cases
    if (0 == pY->GetSize())
    {
        // by convention, anything to the 0 is 1
        nRemainderSize      = 1;
        pXToY->m_pnValue[0] = 1;
    }
    else if (0 == pX->GetSize() || (1 == pX->GetSize() && 1 == pX->m_pnValue[0]))
    {
        // 0 or 1 to any power but 0 is unchanged
        if (!(*pXToY = *pX)) return eOutOfMemory;
        nRemainderSize = pX->GetSize();
    }
    else
    {
        // normal path
        if (m_Modulus.GetSize() < pX->GetSize())
        {
            // may need a bigger workspace
            m_Workspace.Reserve(CUnsignedArithmeticHelper::PowerModulusMemoryNeeds(pX->GetSize(), m_Modulus.GetSize(), m_Modulus.GetSize()));
        }
        if (m_bSuitableForMontgomery)
        {
            CUnsignedArithmeticHelper::MontgomeryPowerModulus(pX->GetSize(),
                                                              pY->GetSize(),
                                                              m_Modulus.GetSize(),
                                                              m_ModulusPrime.GetSize(),
                                                              m_RPrime.GetSize(),
                                                              nPowerLeadDigit,
                                                              nPowerLeadBit,
                                                              nRemainderSize,
                                                              pX->GetValue(),
                                                              pY->GetValue(),
                                                              m_RPrime.GetValue(),
                                                              m_Modulus.GetValue(),
                                                              m_ModulusPrime.GetValue(),
                                                              pXToY->GetValue(),
                                                              m_Workspace.GetSpace(),
                                                              m_bProtectAgainstTimingAttacks);
        }
        else
        {
            CUnsignedArithmeticHelper::PowerModulus(pX->GetSize(),
                                                    pY->GetSize(),
                                                    m_Modulus.GetSize(),
                                                    nRemainderSize,
                                                    pX->GetValue(),
                                                    pY->GetValue(),
                                                    m_Modulus.GetValue(),
                                                    pXToY->GetValue(),
                                                    m_Workspace.GetSpace(),
                                                    m_bProtectAgainstTimingAttacks);
        }
    }
    pXToY->SetSize(nRemainderSize);
    // zero out the rest
    for(size_t i=nRemainderSize; i<m_Modulus.GetSize(); i++)
    {
        pXToY->m_pnValue[i] = 0;
    }
exit:
    return eResult;
}

EArithmeticOperationResult CModularArithmeticBox::MultiplicativeInverse(const CBigInteger *pX, CBigInteger *pXInverse)
{
    size_t nXCoefSize, nModulusCoefSize, nGCDSize;
    bool   bXCoefNegative;
    if(NULL == pX || NULL==pXInverse || 0==pX->GetSize()) return eBadArgument;
    if (!pXInverse->Reserve(m_Modulus.GetSize()+1)) return eOutOfMemory; // +1: need extra DIGIT for intermediate results
    CUnsignedArithmeticHelper::GCD(pX->GetSize(),
                                   m_Modulus.GetSize(),
                                   nGCDSize,
                                   nXCoefSize,
                                   nModulusCoefSize,
                                   pX->GetValue(),
                                   m_Modulus.GetValue(),
                                   m_Workspace.GetSpace(),
                                   pXInverse->GetValue(),
                                   m_Workspace.GetSpace() + m_Modulus.GetSize(),
                                   bXCoefNegative,
                                   m_Workspace.GetSpace() + (m_Modulus.GetSize()<<1));
    if(1!=nGCDSize || 1!= m_Workspace.GetSpace()[0]) return eBadArgument; // GCD != 1 -> not invertible
    pXInverse->SetSize(nXCoefSize);
    if(bXCoefNegative)
    {
        CUnsignedArithmeticHelper::AddSigned(pXInverse->GetSize(),
                                             m_Modulus.GetSize(),
                                             nXCoefSize,
                                             pXInverse->GetValue(),
                                             m_Modulus.GetValue(),
                                             pXInverse->GetValue(),
                                             true,
                                             false,
                                             bXCoefNegative);
        pXInverse->SetSize(nXCoefSize);
    }
    return eOperationSucceeded;
}

void CModularArithmeticBox::ReserveMemory()
{
    // Size the workspace for the maximum needed for any operation on the box.
    // Note that we can do this, as the modulus guarantees a max operation size
    // make sure we have enough memory for multiplies, plus one extra value of the size of the modulus+1 (intermediate value from
    // multiply/mod combination)
    // These assume the box will not be doing operations on numbers larger than the modulus!  If that happens, need to explictly resize
    // the workspace
    size_t nSpaceNeeded = CUnsignedArithmeticHelper::MultiplyMemoryNeeds(m_Modulus.GetSize(), m_Modulus.GetSize()) + m_Modulus.GetSize() + 2;
    // make sure we have enough memory for divides (used to take modulus after multiply).  Also adequate for import
    nSpaceNeeded = max(nSpaceNeeded, CUnsignedArithmeticHelper::DivisionMemoryNeeds(m_Modulus.GetSize()*2, m_Modulus.GetSize()) + m_Modulus.GetSize() + 2);
    // make sure have enough memory for computing inverses
    nSpaceNeeded = max(nSpaceNeeded, CUnsignedArithmeticHelper::GCDMemoryNeeds(m_Modulus.GetSize(), m_Modulus.GetSize(), true) + (m_Modulus.GetSize()<<1));
    // make sure have enough space for computing necessary power-modulus
    nSpaceNeeded = max(nSpaceNeeded, CUnsignedArithmeticHelper::PowerModulusMemoryNeeds(m_Modulus.GetSize(), m_Modulus.GetSize(), m_Modulus.GetSize()));
    m_Workspace.Reserve(nSpaceNeeded);
    // The modulus must be odd for Montgomery to work.  But if it is too small, the overhead isn't worth the extra effort.  Hence, not "suitable"
    m_bSuitableForMontgomery = ((m_Modulus.m_pnValue[0]&1) && (1 < m_Modulus.GetSize() || 65536 <= m_Modulus.GetValue()[0]));
    if(m_bSuitableForMontgomery)
    {
        // modulus is odd -- suitable for Montgomery!
        size_t nModulusPrimeSize, nRPrimeSize;
        m_ModulusPrime.Reserve(m_Modulus.GetSize()+1);  // one extra digit for overflow during computation
        m_RPrime.Reserve(m_Modulus.GetSize()+1);        // one extra digit for overflow during computation
        CUnsignedArithmeticHelper::GetMontgomeryParameters(m_Modulus.GetSize(),
                                                           nModulusPrimeSize,
                                                           nRPrimeSize,
                                                           m_Modulus.GetValue(),
                                                           m_ModulusPrime.GetValue(),
                                                           m_RPrime.GetValue(),
                                                           m_Workspace.GetSpace());
        m_ModulusPrime.SetSize(nModulusPrimeSize);
        m_RPrime.SetSize(nRPrimeSize);
    }
}
