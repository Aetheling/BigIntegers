#include "CBigIntegerVectors.h"
#include "ArithmeticBox.h"
#include "stdlib.h"

CBigIntegerVector::CBigIntegerVector(size_t nLength)
{
    m_pnValues = new CBigInteger[nLength];
    m_nLength  = nLength;
}

CBigIntegerVector::~CBigIntegerVector()
{
    delete[] m_pnValues;
    m_pnValues = NULL;
}

CBigInteger &CBigIntegerVector::operator[](size_t index)
{
    return m_pnValues[index];
}

bool CBigIntegerVector::operator=(CBigIntegerVector &vVec)
{
    if(m_nLength != vVec.m_nLength) return false;
    for(size_t i=0; i<m_nLength; i++)
    {
        if(!(m_pnValues[i] = vVec[i])) return false;
    }
    return true;
}

CBigInteger *CBigIntegerVector::GetValue(size_t i)
{
    if(m_nLength<=i)
    {
        return NULL;
    }
    else
    {
        return &m_pnValues[i];
    }
}

size_t CBigIntegerVector::GetLength()
{
    return m_nLength;
}

// Synopsis:	Performs the dot product of the vectors, and puts it
//              in the passed CBigInteger.  It returns
//              true on success.  On failure (which can only happen
//              if the vectors are of different lengths, or there isn't
//              enough memory, or NULLs are passed), it returns false.
bool CBigIntegerVector::DotProduct(const CBigIntegerVector &vV1,
                                   const CBigIntegerVector &vV2,
                                   CBigInteger             &nProduct,
                                   CArithmeticBox          &cArithmeticBox)
{
    if(vV1.m_nLength != vV2.m_nLength)
    {
        return false;
    }
    if(0==vV1.m_nLength)
    {
        nProduct.SetSize(0);
        return true;
    }
    else
    {
        return DotProduct(vV1.m_pnValues, vV2.m_pnValues, vV1.m_nLength, nProduct, cArithmeticBox);
    }
}

bool CBigIntegerVector::DotProduct(const CBigInteger *pV1,
                                   const CBigInteger *pV2,
                                   size_t            nLength,
                                   CBigInteger       &nProduct,
                                   CArithmeticBox    &cBox)
{
    if(eOperationSucceeded != cBox.Multiply(pV1[0], pV2[0], nProduct))
    {
        return false;
    }
    for(size_t i=1; i<nLength; i++)
    {
        if(eOperationSucceeded != cBox.MultiplyAdd(pV1[i], pV2[i], nProduct))
        {
            return false;
        }
    }
    return true;
}

void CBigIntegerVector::PrintVec(FILE *f)
{
    size_t i;
    fprintf(f,"{ ");
    for(i=0;i<m_nLength;i++)
    {
        if(0 != i)
        {
            fprintf(f,", ");
        }
        m_pnValues[i].PrintHexToFile(f);
    }
    printf(" }\n");
}