#include "BigIntegers.h"
#include "ArithmeticBox.h"
#include "CUnsignedArithmeticHelper.h"
#include "math.h" // for sqrt

CHighPerfTimer CArithmeticBox::s_Timer;
CArithmeticBox::CArithmeticBox()
{
    ;
}

CArithmeticBox::~CArithmeticBox()
{
    ;
}

EArithmeticOperationResult CArithmeticBox::Add(const CBigInteger &nX,
                                               const CBigInteger &nY,
                                               CBigInteger       &nXPlusY)
{
    EArithmeticOperationResult eResult = eOperationSucceeded;
    size_t                     nXSize, nYSize, nSumSize;
    bool                       bSumNegative;
    nXSize = nX.GetSize();
    nYSize = nY.GetSize();
    // the back end doesn't handle x and y both having size 0, so we need to check
    // for it.  And if we check for it, might as well do directly if one has size 0
    if(0 == nXSize)
    {
        // the sum is nY
        if(&nY != &nXPlusY)
        {
            // copy nY into the sum
            if(!(nXPlusY = nY))
            {
                eResult = eOutOfMemory;
            }
        }
        goto exit;
    }
    else if(0 == nYSize)
    {
        if(&nX != &nXPlusY)
        {
            // copy nX into the sum
            if(!(nXPlusY = nX))
            {
                eResult = eOutOfMemory;
            }
        }
        goto exit;
    }
    nSumSize = (nXSize<nYSize) ? nYSize+1 : nXSize+1;
    if(!nXPlusY.Reserve(nSumSize, &nX==&nXPlusY || &nY==&nXPlusY))
    {
        eResult = eOutOfMemory;
        goto exit;
    }
    nXPlusY.GetValue()[nSumSize - 1] = 0; // overflow guard
    CUnsignedArithmeticHelper::AddSigned(nXSize,
                                         nYSize,
                                         nSumSize,
                                         nX.GetValue(),
                                         nY.GetValue(),
                                         nXPlusY.GetValue(),
                                         nX.IsNegative(),
                                         nY.IsNegative(),
                                         bSumNegative);
    nXPlusY.SetSize(nSumSize);
    nXPlusY.SetNegative(bSumNegative);
exit:
    // note that bufferguard checks are compiled away in retail
    nX.CheckBufferguard();
    nY.CheckBufferguard();
    nXPlusY.CheckBufferguard();
    return eResult;
}

CBigInteger *CArithmeticBox::Add(const CBigInteger &nX,
                                 const CBigInteger &nY)
{
    CBigInteger *pZ = new CBigInteger();
    if(NULL != pZ)
    {
        if(eOperationSucceeded != Add(nX,nY,*pZ))
        {
            delete pZ;
            pZ = NULL;
        }
    }
    return pZ;
}

EArithmeticOperationResult CArithmeticBox::Subtract(const CBigInteger &nX,
                                                    const CBigInteger &nY,
                                                    CBigInteger       &nXMinusY)
{
    EArithmeticOperationResult eResult = eOperationSucceeded;
    size_t                     nXSize, nYSize, nSumSize;
    bool                       bSumNegative;
    nXSize   = nX.GetSize();
    nYSize   = nY.GetSize();
    // back end doesn't deal well with both values being 0.  So need to check the sizes.  Since checking anyway, might
    // as well just do the two cases directly
    if(0==nXSize)
    {
        if(&nY != &nXMinusY)
        {
            if(!(nXMinusY = nY))
            {
                eResult = eOutOfMemory;
                goto exit;
            }
        }
        nXMinusY.Invert();
        goto exit;
    }
    if(0==nYSize)
    {
        if(&nX != &nXMinusY)
        {
            if(!(nXMinusY = nX))
            {
                eResult = eOutOfMemory;
                goto exit;
            }
        }
        goto exit;
    }
    nSumSize = (nXSize<nYSize) ? nYSize+1 : nXSize+1;
    if(!nXMinusY.Reserve(nSumSize, &nX==&nXMinusY || &nY==&nXMinusY))
    {
        eResult = eOutOfMemory;
        goto exit;
    }
    nXMinusY.GetValue()[nSumSize - 1] = 0; // overflow guard
    CUnsignedArithmeticHelper::AddSigned(nXSize,
                                         nYSize,
                                         nSumSize,
                                         nX.GetValue(),
                                         nY.GetValue(),
                                         nXMinusY.GetValue(),
                                         nX.IsNegative(),
                                         !nY.IsNegative(),
                                         bSumNegative);
    nXMinusY.SetSize(nSumSize);
    nXMinusY.SetNegative(bSumNegative);
exit:
    // note that bufferguard checks are compiled away in retail
    nX.CheckBufferguard();
    nY.CheckBufferguard();
    nXMinusY.CheckBufferguard();
    return eResult;
}

CBigInteger *CArithmeticBox::Subtract(const CBigInteger &nX, const CBigInteger &nY)
{
    CBigInteger *pZ = new CBigInteger();
    if(eOperationSucceeded != Subtract(nX,nY,*pZ))
    {
        delete pZ;
        pZ = NULL;
    }
    return pZ;
}

EArithmeticOperationResult CArithmeticBox::Multiply(const CBigInteger &nX,
                                                    const CBigInteger &nY,
                                                    CBigInteger       &nXTimesY)
{
    EArithmeticOperationResult eResult = eOperationSucceeded;
    if(&nX == &nXTimesY || &nY == &nXTimesY)
    {
        eResult = eBadArgument;
    }
    else
    {
        size_t nXSize = nX.GetSize();
        size_t nYSize = nY.GetSize();
        if(0==nXSize || 0==nYSize)
        {
            nXTimesY.SetSize(0);
        }
        else if(!nXTimesY.Reserve(nXSize+nYSize) ||
                !m_Workspace.Reserve(CUnsignedArithmeticHelper::MultiplyMemoryNeeds(nXSize,nYSize)))
        {
            eResult = eOutOfMemory;
        }
        else
        {
            DIGIT *pZValue = nXTimesY.GetValue();
            CUnsignedArithmeticHelper::Multiply(nXSize, nYSize, nX.GetValue(), nY.GetValue(), pZValue, m_Workspace.GetSpace());
            nXTimesY.SetSize((0==pZValue[nXSize+nYSize-1]) ? nXSize+nYSize-1 : nXSize+nYSize);
            nXTimesY.SetNegative(nX.IsNegative()!=nY.IsNegative());
        }
    }
    // note that bufferguard checks are compiled away in retail
    nX.CheckBufferguard();
    nY.CheckBufferguard();
    nXTimesY.CheckBufferguard();
    m_Workspace.CheckBufferguard();
    return eResult;
}

CBigInteger *CArithmeticBox::Multiply(const CBigInteger &nX,
                                      const CBigInteger &nY)
{
    CBigInteger *pXTimesY = new CBigInteger();
    if(eOperationSucceeded != Multiply(nX,nY,*pXTimesY))
    {
        delete pXTimesY;
        pXTimesY = NULL;
    }
    return pXTimesY;
}

EArithmeticOperationResult CArithmeticBox::Square(const CBigInteger &nX,
                                                  CBigInteger       &nSquare)
{
    EArithmeticOperationResult eResult = eOperationSucceeded;
    if(&nX == &nSquare)
    {
        eResult = eBadArgument;
    }
    else
    {
        size_t nXSize = nX.GetSize();
        if(0==nXSize)
        {
            nSquare.SetSize(0);
        }
        else if(!nSquare.Reserve(nXSize<<1) ||
                !m_Workspace.Reserve(CUnsignedArithmeticHelper::SquareMemoryNeeds(nXSize,nXSize)))
        {
            eResult = eOutOfMemory;
        }
        else
        {
            DIGIT *pZValue = nSquare.GetValue();
            CUnsignedArithmeticHelper::Square(nXSize, nX.GetValue(), pZValue, m_Workspace.GetSpace());
            nSquare.SetSize((0==pZValue[nXSize+nXSize-1]) ? nXSize+nXSize-1 : nXSize+nXSize);
            nSquare.SetNegative(false);
        }
    }
    // note that bufferguard checks are compiled away in retail
    nX.CheckBufferguard();
    nSquare.CheckBufferguard();
    m_Workspace.CheckBufferguard();
    return eResult;
}

CBigInteger *CArithmeticBox::Square(const CBigInteger &nX)
{
    CBigInteger *pSquare = new CBigInteger();
    if(eOperationSucceeded != Square(nX, *pSquare))
    {
        delete pSquare;
        pSquare = NULL;
    }
    return pSquare;
}

EArithmeticOperationResult CArithmeticBox::MultiplyAdd(const CBigInteger &nX,
                                                       const CBigInteger &nY,
                                                       CBigInteger       &nRunningSum)
{
    size_t nMemNeeded;
    EArithmeticOperationResult eResult = eOperationSucceeded;
    if(&nX == &nRunningSum || &nY == &nRunningSum)
    {
        eResult = eBadArgument;
    }
    else
    {
        bool   bProdNeg  = (nX.IsNegative()!=nY.IsNegative());
        bool   bDoingAdd = (nRunningSum.IsZero() || (bProdNeg == nRunningSum.IsNegative()));
        size_t nXSize    = nX.GetSize();
        size_t nYSize    = nY.GetSize();
        size_t nSumSize  = nRunningSum.GetSize();
        if(0<nXSize && 0<nYSize)
        {
            size_t nProdSize      = nXSize+nYSize;
            size_t nMaxOutputSize = nProdSize;
            if(nMaxOutputSize<nSumSize)
            {
                nMaxOutputSize = nSumSize;
            }
            if(bDoingAdd)
            {
                nMaxOutputSize++; // make sure have enough space for the carry
                nMemNeeded = CUnsignedArithmeticHelper::MultiplyMemoryNeeds(nXSize, nYSize, nSumSize) + nProdSize;
            }
            else
            {
                nMemNeeded = CUnsignedArithmeticHelper::MultiplyMemoryNeeds(nXSize, nYSize) + nProdSize;
            }
            if(!nRunningSum.Reserve(nMaxOutputSize,true) || !m_Workspace.Reserve(nMemNeeded))
            {
                eResult = eOutOfMemory;
            }
            else
            {
                // zero out the leading digits of the running sum
                for(size_t i=nSumSize; i<nMaxOutputSize; i++)
                {
                    nRunningSum.GetValue()[i] = 0;
                }
                if(bDoingAdd)
                {
                    CUnsignedArithmeticHelper::MultiplyAdd(nXSize,
                                                           nYSize,
                                                           nSumSize,
                                                           nX.GetValue(),
                                                           nY.GetValue(),
                                                           nRunningSum.GetValue(),
                                                           m_Workspace.GetSpace());
                    nRunningSum.SetSize(nSumSize);
                }
                else
                {
                    // actually doing z = x*y-z (in terms of absolute values)
                    CUnsignedArithmeticHelper::Multiply(nXSize, nYSize, nX.GetValue(), nY.GetValue(), m_Workspace.GetSpace(), m_Workspace.GetSpace() + nProdSize);
                    if(0==m_Workspace.GetSpace()[nProdSize-1])
                    {
                        nProdSize--;
                    }
                    CUnsignedArithmeticHelper::AddSigned(nProdSize,
                                                         nSumSize,
                                                         nSumSize,
                                                         m_Workspace.GetSpace(),
                                                         nRunningSum.GetValue(),
                                                         nRunningSum.GetValue(),
                                                         bProdNeg,
                                                         nRunningSum.IsNegative(),
                                                         bProdNeg);
                    nRunningSum.SetSize(nSumSize);
                }
                nRunningSum.SetNegative(bProdNeg);
            }
        }
    }
    // note that bufferguard checks are compiled away in retail
    nX.CheckBufferguard();
    nY.CheckBufferguard();
    nRunningSum.CheckBufferguard();
    m_Workspace.CheckBufferguard();
    return eResult;
}

EArithmeticOperationResult CArithmeticBox::Divide(const CBigInteger &nX,
                                                  const CBigInteger &nY,
                                                  CBigInteger       &nXDivY,
                                                  CBigInteger       &nRemainder)
{
    EArithmeticOperationResult eResult;
    bool                       bResultNegative;
    size_t                     nXSize     = nX.GetSize();
    size_t                     nYSize     = nY.GetSize();
    size_t                     nDivSpace  = (nXSize>=nYSize) ? nXSize-nYSize+1 : 0;
    size_t                     nWorkspace = CUnsignedArithmeticHelper::DivisionMemoryNeeds(nXSize, nYSize);

    if(&nX == &nXDivY || &nX == &nRemainder || &nY == &nXDivY || &nY == &nRemainder)
    {
        eResult = eBadArgument;
    }
    else if(0==nY.GetSize())
    {
        eResult = eBadOperand;
    }
    else if(!nXDivY.Reserve(nDivSpace))
    {
        eResult = eOutOfMemory;
    }
    else if(!(nRemainder = nX) || !m_Workspace.Reserve(nWorkspace) || !nXDivY.Reserve(nDivSpace))
    {
        eResult = eOutOfMemory;
    }
    else
    {
        size_t nDivSize, nModSize;
        CUnsignedArithmeticHelper::Divide(nXSize,
                                          nYSize,
                                          nDivSize,
                                          nModSize,
                                          nRemainder.GetValue(),
                                          nY.GetValue(),
                                          nXDivY.GetValue(),
                                          m_Workspace.GetSpace());
        bResultNegative = (nX.IsNegative() != nY.IsNegative());
        nXDivY.SetSize(nDivSize);
        nXDivY.SetNegative(bResultNegative);
        nRemainder.SetSize(nModSize);
        nRemainder.SetNegative(bResultNegative);
        eResult = eOperationSucceeded;
    }
    // note that bufferguard checks are compiled away in retail
    nX.CheckBufferguard();
    nY.CheckBufferguard();
    nXDivY.CheckBufferguard();
    nRemainder.CheckBufferguard();
    m_Workspace.CheckBufferguard();
    return eResult;
}

EArithmeticOperationResult CArithmeticBox::GCD(const CBigInteger &nX,
                                               const CBigInteger &nY,
                                               CBigInteger       &nGCD)
{
    EArithmeticOperationResult eReturn;
    if (0 == nX.GetSize())
    {
        if (0 == nY.GetSize())
        {
            eReturn = eBadOperand;
        }
        else if (&nY != &nGCD && !(nGCD = nY))
        {
            eReturn = eOutOfMemory;
        }
        else
        {
            eReturn = eOperationSucceeded;
        }
    }
    else if (0 == nY.GetSize())
    {
        if (&nX != &nGCD && !(nGCD = nX))
        {
            eReturn = eOutOfMemory;
        }
        else
        {
            eReturn = eOperationSucceeded;
        }
    }
    else
    {
        size_t nXSize = nX.GetSize();
        size_t nYSize = nY.GetSize();
        if (!m_Workspace.Reserve(CUnsignedArithmeticHelper::GCDMemoryNeeds(nXSize, nYSize, false)))
        {
            eReturn = eOutOfMemory;
        }
        else
        {
            // GCD needs space for the larger of (x,y) -- the GCD cannot be bigger than the smaller, BUT we need extra space for intermediate values
            if (!nGCD.Reserve((nXSize < nYSize) ? nYSize : nXSize, (&nGCD==&nX || &nGCD==&nY)) ||
                !m_Workspace.Reserve(CUnsignedArithmeticHelper::GCDMemoryNeeds(nXSize, nYSize, false)))
            {
                eReturn = eOutOfMemory;
            }
            else
            {
                nGCD.SetSize(CUnsignedArithmeticHelper::GCD(nXSize,
                                                            nYSize,
                                                            nX.GetValue(),
                                                            nY.GetValue(),
                                                            nGCD.GetValue(),
                                                            m_Workspace.GetSpace()));
                eReturn = eOperationSucceeded;
            }
        }
    }
    // note that bufferguard checks are compiled away in retail
    nX.CheckBufferguard();
    nY.CheckBufferguard();
    nGCD.CheckBufferguard();
    m_Workspace.CheckBufferguard();
    return eReturn;
}

EArithmeticOperationResult CArithmeticBox::GCDExtended(const CBigInteger &nX,
                                                       const CBigInteger &nY,
                                                       CBigInteger       &nGCD,
                                                       CBigInteger       &nXCoef,
                                                       CBigInteger       &nYCoef)
{
    EArithmeticOperationResult eReturn;
    if (&nGCD==&nXCoef || &nGCD==&nYCoef || &nXCoef==&nYCoef)
    {
        eReturn = eBadArgument;
    }
    else if (0 == nX.GetSize())
    {
        if (0 == nY.GetSize())
        {
            eReturn = eBadOperand;
        }
        else if (!(nGCD = nY) || !nYCoef.Reserve(1))
        {
            eReturn = eOutOfMemory;
        }
        else
        {
            nXCoef.SetSize(0); // by convention
            nYCoef.SetSize(1);
            nYCoef.GetValue()[0] = 1;
            eReturn              = eOperationSucceeded;
        }
    }
    else if (0 == nY.GetSize())
    {
        if (!(nGCD = nX) || !nXCoef.Reserve(1))
        {
            eReturn = eOutOfMemory;
        }
        else
        {
            nXCoef.SetSize(1);
            nYCoef.SetSize(0); // by convention
            nXCoef.GetValue()[0] = 1;
            eReturn              = eOperationSucceeded;
        }
    }
    else
    {
        size_t nXSize = nX.GetSize();
        size_t nYSize = nY.GetSize();
        if (!m_Workspace.Reserve(CUnsignedArithmeticHelper::GCDMemoryNeeds(nXSize, nYSize, true)))
        {
            eReturn = eOutOfMemory;
        }
        else
        {
            // GCD needs space for the larger of (x,y) -- the GCD cannot be bigger than the smaller, BUT we need extra space for intermediate values
            if (!nGCD.Reserve((nXSize < nYSize) ? nYSize : nXSize, (&nGCD==&nX || &nGCD==&nY)))
            {
                eReturn = eOutOfMemory;
            }
            else
            {
                // note that the x coef can't be larger than y, nor can the y coef be
                // larger than x, so this should give enough space!
                // Add one extra digit for overflow (Add can "carry" out a 0) for the coefs
                if (!nXCoef.Reserve(nYSize + 1, &nXCoef == &nX || &nXCoef == &nY) || !nYCoef.Reserve(nXSize + 1, &nYCoef == &nX || &nYCoef == &nY))
                {
                    eReturn = eOutOfMemory;
                }
                else
                {
                    bool   bXCoefNegative;
                    size_t nXCoefSize, nYCoefSize, nGCDCoefSize;
                    CUnsignedArithmeticHelper::GCD(nXSize,
                                                   nYSize,
                                                   nGCDCoefSize,
                                                   nXCoefSize,
                                                   nYCoefSize,
                                                   nX.GetValue(),
                                                   nY.GetValue(),
                                                   nGCD.GetValue(),
                                                   nXCoef.GetValue(),
                                                   nYCoef.GetValue(),
                                                   bXCoefNegative,
                                                   m_Workspace.GetSpace());
                    nGCD.SetSize(nGCDCoefSize);
                    nXCoef.SetSize(nXCoefSize);
                    nYCoef.SetSize(nYCoefSize);
                    // coef signs computed assuming x, y positive.  Adjust as needed
                    if (0 < nXCoefSize)
                    {
                        nXCoef.SetNegative(nX.IsNegative() ? !bXCoefNegative : bXCoefNegative);
                    }
                    if (0 < nYCoefSize)
                    {
                        nYCoef.SetNegative(nY.IsNegative() ? bXCoefNegative : !bXCoefNegative);
                    }
                }
                eReturn = eOperationSucceeded;
            }
        }
    }
    // note that bufferguard checks are compiled away in retail
    nX.CheckBufferguard();
    nY.CheckBufferguard();
    nGCD.CheckBufferguard();
    nXCoef.CheckBufferguard();
    nYCoef.CheckBufferguard();
    return eReturn;
}

EArithmeticOperationResult CArithmeticBox::SQRT(const CBigInteger &nX, CBigInteger &nSqrt)
{
    size_t nRootSize;
    if(!nSqrt.Reserve((nX.GetSize()+1)>>1) || !m_Workspace.Reserve(CUnsignedArithmeticHelper::SquareRootMemoryNeeds(nX.GetSize())))
    {
        return eOutOfMemory;
    }
    if (nX.IsNegative()) return eBadOperand;
    CUnsignedArithmeticHelper::SQRT(nX.GetSize(), nRootSize, nX.GetValue(), nSqrt.GetValue(), m_Workspace.GetSpace());
    nSqrt.SetSize(nRootSize);
    nSqrt.SetNegative(false);
    // note that bufferguard checks are compiled away in retail
    nX.CheckBufferguard();
    nSqrt.CheckBufferguard();
    m_Workspace.CheckBufferguard();
    return eOperationSucceeded;
}