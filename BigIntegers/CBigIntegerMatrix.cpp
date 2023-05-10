#include "BigIntegers.h"
#include "CBigIntegerVectors.h"
#include "ArithmeticBox.h"
#include "CBigIntegerMatrix.h"

CBigIntegerMatrix::CBigIntegerMatrix(size_t nRowsCols)
{
    size_t i,j;

    m_nRows  = nRowsCols;
    m_nCols  = nRowsCols;
    m_ppData = (CBigInteger **) malloc(sizeof(CBigInteger *)*nRowsCols);
    for(i=0;i<nRowsCols;i++)
    {
        m_ppData[i] = new CBigInteger[nRowsCols];
    }
}

CBigIntegerMatrix::CBigIntegerMatrix(size_t nRows, size_t nCols)
{
    unsigned int i,j;

    m_nRows  = nRows;
    m_nCols  = nCols;
    m_ppData = (CBigInteger **) malloc(sizeof(CBigInteger *)*nRows);
    for(i=0;i<nRows;i++)
    {
        m_ppData[i] = new CBigInteger[nCols];
    }
}

CBigIntegerMatrix::~CBigIntegerMatrix()
{
    for(size_t i=0;i<m_nRows;i++)
    {
        if(m_ppData[i])
        {
            delete[] m_ppData[i];
        }
    }
    free(m_ppData);
}

size_t CBigIntegerMatrix::GetRows()
{
    return m_nRows;
}

size_t CBigIntegerMatrix::GetCols()
{
    return m_nCols;
}

CBigInteger *CBigIntegerMatrix::GetValue(size_t nRow, size_t nCol)
{
    if(m_nRows <= nRow || m_nCols <= nCol)
    {
        return NULL;
    }
    return &m_ppData[nRow][nCol];
}

// Performs the matrix-vector multiply.
bool CBigIntegerMatrix::MatVecMultiply(CBigIntegerVector &vV,
                                       CBigIntegerVector &vProd,
                                       CArithmeticBox    &cArithmeticBox)
{
    if(vV.GetLength() != m_nCols || vProd.GetLength() != m_nRows)
    {
        return false;  // sizes don't match
    }
    for(size_t i=0; i<m_nRows; i++)
    {
        if(!CBigIntegerVector::DotProduct(vV.m_pnValues,
                                          m_ppData[i],
                                          m_nCols,
                                          vProd.m_pnValues[i],
                                          cArithmeticBox))
        {
            return false;
        }
    }
    return true;
}

CBigIntegerMatrix::EMatrixOpReturnValue CBigIntegerMatrix::QuasiInverse(CBigIntegerVector &vD,
                                                                        CArithmeticBox    &cArithmeticBox)
{
    size_t               i,ii,j,jj,k,*pnPermutation;
    CBigInteger          nCoef1,nCoef2,nCoef3,nCoef4,nThrowAway;
    CBigIntegerMatrix    nQuasiInverse(m_nRows);
    EMatrixOpReturnValue eStatus = eWorked;
#ifdef _DEBUG
    // make a copy of the original matrix so we can validate the quasi-inverse
    CBigIntegerMatrix nbimCopy(m_nRows);
    CBigIntegerMatrix nProd(m_nRows);
    DWORD             dwTime    = 0;
    nbimCopy = *this;
#endif

    if(m_nRows != m_nCols)
    {
        return eMalformed;
    }
    pnPermutation  = new size_t[m_nRows];

    // initialize the pnPermutation vector
    for(i=0;i<m_nRows;i++)
    {
        pnPermutation[i] = i;
    }

    // initialize the quasi-inverse matrix to the identity matrix
    // note that the default value for a big integer is 0.  Ned only look at the main diagonal
    for(i=0;i<m_nRows;i++)
    {
        nQuasiInverse[i][i].SetFromHexString("1");
    }

    // Forward elimination
    for(ii=0;ii<m_nRows-1;ii++)
    {
        i = pnPermutation[ii];
        if(m_ppData[i][ii].IsZero()) // need to swap rows
        {
            for(jj=ii+1;jj<m_nRows;jj++)
            {
                j = pnPermutation[jj];
                if(0 != m_ppData[j][ii].GetSize())
                {
                    break;
                }
            }
            if(jj==m_nRows)  // matrix is singular
            {
                eStatus = eSingular;
                goto Cleanup;
            }
            // "swap" the rows -- adjust the permutation "matrix" (vector)
            pnPermutation[ii] = j;
            pnPermutation[jj] = i;
            i                 = j;
        }

        // ready to do the elimination
        for(jj=ii+1;jj<m_nRows;jj++)
        {
            j = pnPermutation[jj];
            if(!m_ppData[j][ii].IsZero())  // is, indeed, work to do
            {
                // Set pCoef4 to the GCD of [i][i] and [j][i].
                // Set pCoef1 to [i][i]/pCoef4 and pCoef2 to [j][i]/pCoef4.
                // Subtract pCoef2*(row i) from pCoef1*(row j)
                if(eOperationSucceeded != cArithmeticBox.GCD(m_ppData[i][ii],
                                                             m_ppData[j][ii],
                                                             nCoef4))
                {
                    eStatus = eOutOfMemory;  // ran out of memory
                    goto Cleanup;
                }
                if(1 != nCoef4.GetSize() || 1 != nCoef4.GetValue()[0])  // GCD is interesting
                {
                    // Divide is destructive, so copy [i][i] before
                    // computing pCoef1.  But we don't care about [j][i]
                    // after this point, so it can be destroyed (it will
                    // in fact be set to 0, as it should be, since the remainder
                    // of the division is, by design, 0).
                    if(eOperationSucceeded != cArithmeticBox.Divide(m_ppData[i][ii],
                                                                    nCoef4,
                                                                    nCoef1,
                                                                    nThrowAway)   ||
                       eOperationSucceeded != cArithmeticBox.Divide(m_ppData[j][ii],
                                                                    nCoef4,
                                                                    nCoef2,
                                                                    nThrowAway))
                    {
                        eStatus = eOutOfMemory;  // ran out of memory
                        goto Cleanup;
                    }
                    // Subtract pCoef2*(row i) from pCoef1*(row j)
                    // first, the base matrix
                    for(k=ii+1;k<m_nCols;k++)
                    {
                        if(eOperationSucceeded != cArithmeticBox.Multiply(nCoef2,
                                                                          m_ppData[i][k],
                                                                          nCoef4)          ||
                           eOperationSucceeded != cArithmeticBox.Multiply(nCoef1,
                                                                          m_ppData[j][k],
                                                                          nCoef3)          ||
                           eOperationSucceeded != cArithmeticBox.Subtract(nCoef3,
                                                                          nCoef4,
                                                                          m_ppData[j][k]))
                        {
                            eStatus = eOutOfMemory;  // ran out of memory
                            goto Cleanup;
                        }
                    }
                    // Next, the "inverse" matrix.  Note that due to row swaps
                    // the matrix might not be so well structured.
                    // Subtract pCoef2*(row i) from pCoef1*(row j)
                    for(k=0;k<m_nCols;k++)
                    {
                        if(!nQuasiInverse[i][k].IsZero())
                        {
                            if(!nQuasiInverse[j][k].IsZero())
                            {
                                if(eOperationSucceeded != cArithmeticBox.Multiply(nCoef1,
                                                                                  nQuasiInverse[j][k],
                                                                                  nCoef3) ||
                                   eOperationSucceeded != cArithmeticBox.Multiply(nCoef2,
                                                                                  nQuasiInverse[i][k],
                                                                                  nCoef4) ||
                                   eOperationSucceeded != cArithmeticBox.Subtract(nCoef3,
                                                                                  nCoef4,
                                                                                  nQuasiInverse[j][k]))
                                {
                                    eStatus = eOutOfMemory;  // ran out of memory
                                    goto Cleanup;
                                }
                            }
                            else
                            {
                                if(eOperationSucceeded != cArithmeticBox.Multiply(nCoef2,
                                                                                  nQuasiInverse[i][k],
                                                                                  nQuasiInverse[j][k]))
                                {
                                    eStatus = eOutOfMemory;  // ran out of memory
                                    goto Cleanup;
                                }
                                nQuasiInverse[j][k].Invert();
                            }
                        }
                        else if(!nQuasiInverse[j][k].IsZero())
                        {
                            if(eOperationSucceeded != cArithmeticBox.Multiply(nCoef1,
                                                                              nQuasiInverse[j][k],
                                                                              nCoef3))
                            {
                                eStatus = eOutOfMemory;  // ran out of memory
                                goto Cleanup;
                            }
                            CBigInteger::Swap(nCoef3, nQuasiInverse[j][k]);
                        }
                    }
                }
                else // GCD = 1; no need to divide by it to find the
                     // multiples needed
                {
                    // subtract [i][j]*(row i) from [i][i]*(row j)
                    // First, the base matrix
                    for(k=ii+1; k<m_nCols; k++)
                    {
                        if(eOperationSucceeded != cArithmeticBox.Multiply(m_ppData[i][k],
                                                                          m_ppData[j][ii],
                                                                          nCoef1)            ||
                           eOperationSucceeded != cArithmeticBox.Multiply(m_ppData[j][k],
                                                                          m_ppData[i][ii],
                                                                          nCoef2)            ||
                           eOperationSucceeded != cArithmeticBox.Subtract(nCoef2,
                                                                          nCoef1,
                                                                          m_ppData[j][k]))
                        {
                            eStatus = eOutOfMemory;  // ran out of memory
                            goto Cleanup;
                        }
                    }
                    // next, the inverse.  Note that due to row swaps
                    // the structure will not in general be so nice.
                    // Also many of the entries are likely to be 0,
                    // so it's worth checking
                    // subtract [i][j]*(row i) from [i][i]*(row j)
                    for(k=0; k<m_nCols; k++)
                    {
                        if(!nQuasiInverse[i][k].IsZero() != 0)
                        {
                            if(!nQuasiInverse[j][k].IsZero() != 0)
                            {
                                if(eOperationSucceeded != cArithmeticBox.Multiply(m_ppData[i][ii],
                                                                                  nQuasiInverse[j][k],
                                                                                  nCoef1) ||
                                   eOperationSucceeded != cArithmeticBox.Multiply(m_ppData[j][ii],
                                                                                  nQuasiInverse[i][k],
                                                                                  nCoef2) ||
                                   eOperationSucceeded != cArithmeticBox.Subtract(nCoef1,
                                                                                  nCoef2,
                                                                                  nQuasiInverse[j][k]))
                                {
                                    eStatus = eOutOfMemory;  // ran out of memory
                                    goto Cleanup;
                                }
                            }
                            else
                            {
                                if(eOperationSucceeded != cArithmeticBox.Multiply(m_ppData[j][ii],
                                                                                  nQuasiInverse[i][k],
                                                                                  nQuasiInverse[j][k]))
                                {
                                    eStatus = eOutOfMemory;  // ran out of memory
                                    goto Cleanup;
                                }
                                nQuasiInverse[j][k].Invert();
                            }
                        }
                        else if(!nQuasiInverse[j][k].IsZero() != 0)
                        {
                            if(eOperationSucceeded != cArithmeticBox.Multiply(m_ppData[i][ii],
                                                                              nQuasiInverse[j][k],
                                                                              nCoef4))
                            {
                                eStatus = eOutOfMemory;  // ran out of memory
                                goto Cleanup;
                            }
                            CBigInteger::Swap(nCoef4, nQuasiInverse[j][k]);
                        }
                    }
                }
            }
        }
    }
    if(m_ppData[pnPermutation[m_nRows-1]][m_nRows-1].IsZero()) // system is singular
    {
        eStatus = eSingular;
        goto Cleanup;
    }

    // Backwards elimination
    for(ii=m_nRows-1;ii>0;ii--)
    {
        i = pnPermutation[ii];
        // Divide through by the GCD of the row (if > 0) to shrink
        // the sizes as much as possible
        if(1 < m_ppData[i][ii].GetSize() || (!m_ppData[i][ii].IsZero() && 1 < m_ppData[i][ii].GetValue()[0]))
        {
            // there might be a GCD of interest
            // (note that comparison ignores sign,
            // so is okay)
            nCoef1 = m_ppData[i][ii];  // slightly wasteful
            for(j=0;j<m_nCols;j++)
            {
                if(1 == nQuasiInverse[i][j].GetSize() &&
                   1 == nQuasiInverse[i][j].GetValue()[0]) // no interesting GCD
                {
                    break;
                }
                if(!nQuasiInverse[i][j].IsZero() != 0)
                {
                    if(eOperationSucceeded != cArithmeticBox.GCD(nCoef1,
                                                                 nQuasiInverse[i][j],
                                                                 nCoef1))
                    {
                        break;  // note that we can still continue even if this
                                // fails
                    }
                }
            }
            if(j==m_nCols)  // have an interesting GCD
            {
                if(eOperationSucceeded != cArithmeticBox.Divide(m_ppData[i][ii],
                                                                nCoef1,
                                                                nCoef2,
                                                                nThrowAway))
                {
                    eStatus = eOutOfMemory;  // ran out of memory, and the
                                             // system is now in bad shape
                    goto Cleanup;
                }
                CBigInteger::Swap(nCoef2, m_ppData[i][ii]);
                for(j=0;j<m_nCols;j++)
                {
                    if(!nQuasiInverse[i][j].IsZero() != 0)
                    {
                        if(eOperationSucceeded != cArithmeticBox.Divide(nQuasiInverse[i][j],
                                                                        nCoef1,
                                                                        nCoef2,
                                                                        nThrowAway))
                        {
                            eStatus = eOutOfMemory;  // ran out of memory, and the
                                                     // system is now in bad shape
                            goto Cleanup;
                        }
                        CBigInteger::Swap(nCoef2, nQuasiInverse[i][j]);
                    }
                }
            }
        }
        // do the elimination
        for(jj=ii;jj>0;jj--)
        {
            j = pnPermutation[jj-1];
            if(!m_ppData[j][ii].IsZero())  // some elimination to do
            {
                // Set pCoef4 to the GCD of [i][j] and [i][i]
                if(eOperationSucceeded != cArithmeticBox.GCD(m_ppData[i][ii],
                                                             m_ppData[j][ii],
                                                             nCoef4))
                {
                    eStatus = eOutOfMemory;  // ran out of memory
                    goto Cleanup;
                }
                if(1 != nCoef4.GetSize() ||
                   1 != nCoef4.GetValue()[0]) // interesting GCD
                {
                    // set pCoef1 to [i][i]/GCD and pCoef2 to [j][i]/GCD
                    // Note that while we still care about [i][i] -- it
                    // gives the diagonal for the matrix -- we don't care
                    // about [j][i]
                    nCoef3 = m_ppData[i][ii];
                    if(eOperationSucceeded != cArithmeticBox.Divide(nCoef3,
                                                                    nCoef4,
                                                                    nCoef1,
                                                                    nThrowAway)    ||
                       eOperationSucceeded != cArithmeticBox.Divide(m_ppData[j][ii],
                                                                    nCoef4,
                                                                    nCoef2,
                                                                    nThrowAway))
                    {
                        eStatus = eOutOfMemory;  // ran out of memory
                        goto Cleanup;
                    }
                    // subtract pCoef2*(row i) from pCoef1*(row j)
                    // First, the portion of the base matrix still
                    // of interest
                    for(k=jj-1;k<ii;k++)
                    {
                        if(eOperationSucceeded != cArithmeticBox.Multiply(m_ppData[j][k],
                                                                          nCoef1,
                                                                          nCoef3))
                        {
                            eStatus = eOutOfMemory;  // ran out of memory
                            goto Cleanup;
                        }
                        CBigInteger::Swap(nCoef3, m_ppData[j][k]);
                    }
                    // Now, the inverse matrix
                    for(k=0;k<m_nCols;k++)
                    {
                        if(eOperationSucceeded != cArithmeticBox.Multiply(nCoef1,
                                                                          nQuasiInverse[j][k],
                                                                          nCoef3)  ||
                           eOperationSucceeded != cArithmeticBox.Multiply(nCoef2,
                                                                          nQuasiInverse[i][k],
                                                                          nCoef4)  ||
                           eOperationSucceeded != cArithmeticBox.Subtract(nCoef3,
                                                                          nCoef4,
                                                                          nQuasiInverse[j][k]))
                        {
                            eStatus = eOutOfMemory;  // ran out of memory
                            goto Cleanup;
                        }
                    }
                }
                else // GCD is 1
                {
                    // subtract [j][i]*(row i) from [i][i]*(row j)
                    // First, that portion of the base matrix still of
                    // interest
                    for(k=jj-1;k<ii;k++)
                    {
                        if(eOperationSucceeded != cArithmeticBox.Multiply(m_ppData[i][ii],
                                                                          m_ppData[j][k],
                                                                          nCoef1))
                        {
                            eStatus = eOutOfMemory;  // ran out of memory
                            goto Cleanup;
                        }
                        CBigInteger::Swap(nCoef1, m_ppData[j][k]);
                    }
                    // Then, the inverse matrix
                    for(k=0;k<m_nCols;k++)
                    {
                        if(eOperationSucceeded != cArithmeticBox.Multiply(m_ppData[i][ii],
                                                                          nQuasiInverse[j][k],
                                                                          nCoef1)  ||
                           eOperationSucceeded != cArithmeticBox.Multiply(m_ppData[j][ii],
                                                                          nQuasiInverse[i][k],
                                                                          nCoef2)  ||
                           eOperationSucceeded != cArithmeticBox.Subtract(nCoef1,
                                                                          nCoef2,
                                                                          nQuasiInverse[j][k]))
                        {
                            eStatus = eOutOfMemory;  // ran out of memory
                            goto Cleanup;
                        }
                    }
                }
            }
        }
    }
    // And last: the GCD of row "0"
    // Divide through by the GCD of the row (if > 1) to shrink
    // the sizes as much as possible
    i = pnPermutation[0];
    if(1 < m_ppData[i][0].GetSize() ||
       !m_ppData[i][0].IsZero() && 1 < m_ppData[i][0].GetValue()[0])  // there might be a GCD of interest
    {
        nCoef1 = m_ppData[i][0];  // slightly wasteful
        for(j=0;j<m_nCols;j++)
        {
            if(1 == nQuasiInverse[i][j].GetSize() &&
               1 == nQuasiInverse[i][j].GetValue()[0]) // no interesting GCD
            {
                break;
            }
            if(!nQuasiInverse[i][j].IsZero())
            {
                if(eOperationSucceeded != cArithmeticBox.GCD(nCoef1,
                                                             nQuasiInverse[i][j],
                                                             nCoef1))
                {
                    break;  // note that we can still continue even if this
                            // fails
                }
            }
        }
        if(j==m_nCols)  // have an interesting GCD
        {
            if(eOperationSucceeded == cArithmeticBox.Divide(m_ppData[i][0],
                                                            nCoef1,
                                                            nCoef2,
                                                            nThrowAway))
            {
                CBigInteger::Swap(nCoef2, m_ppData[i][0]);
                for(j=0;j<m_nCols;j++)
                {
                    if(!nQuasiInverse[i][j].IsZero())
                    {
                        if(eOperationSucceeded != cArithmeticBox.Divide(nQuasiInverse[i][j],
                                                                        nCoef1,
                                                                        nCoef2,
                                                                        nThrowAway))
                        {
                            eStatus = eOutOfMemory;  // ran out of memory, and the
                                                     // system is now in bad shape
                            goto Cleanup;
                        }
                        CBigInteger::Swap(nCoef2, nQuasiInverse[i][j]);
                    }
                }
            }
        }
    }
    // Now, nQuasiInverse contains the sort-of inverse of the original
    // matrix, the diagonal elements of the original matrix contain the
    // D matrix, and the rest of the values of the original matrix are
    // garbage.
    for(i=0;i<m_nCols;i++)
    {
        vD[i] = m_ppData[pnPermutation[i]][i];
   //     vD.Assign(i, m_ppData[pnPermutation[i]][i]);
    }
    for(i=0;i<m_nCols;i++)
    {
        ii = pnPermutation[i];
        for(j=0;j<m_nCols;j++)
        {
            CBigInteger::Swap(m_ppData[i][j], nQuasiInverse[ii][j]);
        }
    }
    // One last tweak: make sure the diagonals are all positive, adjusting
    // the inverse matrix as necessary
    for(i=0;i<m_nCols;i++)
    {
        if(vD.m_pnValues[i].IsNegative())
        {
            vD.m_pnValues[i].Invert();
            for(j=0;j<m_nCols;j++)
            {
                m_ppData[i][j].Invert();
            }
        }
    }
#ifdef _DEBUG
    // validate: The original matrix contains its quasi-inverse; we have a copy of the original.  The product of these
    // should be a diagonal matrix, with values given in the diag (pD) vector
    if (eWorked != Multiply(*this, nbimCopy, nProd, cArithmeticBox))
    {
        printf("Matrix multiply failed\n");
    }
    else
    {
        // validate the product
        bool bAllOkay = true;
        for (int i=0; i<m_nRows; i++)
        {
            for (int j=0; j<m_nRows; j++)
            {
                if (i == j)
                {
                    if (nProd[i][i] != vD.m_pnValues[i])
                    {
                        printf("element %i, %i\n", i, i);
                        printf("Diag is off: "); nProd[i][i].PrintHexToFile();
                        printf("vs           "); vD.m_pnValues[i].PrintHexToFile();
                        bAllOkay = false;
                    }
                }
                else if (!nProd[i][j].IsZero())
                {
                    printf("Off-diag element %i, %i should be 0; instead, it's ",i,j); nProd[i][j].PrintHexToFile();
                    bAllOkay = false;
                }
            }
        }
        if (!bAllOkay)
        {
            printf("oops\n");
        }
    }
#endif
Cleanup:
    delete pnPermutation;
    return eStatus;
}

// Since the individual element operations are rather expensive, likely a lower threshold of viability for Strassen matrix multiplication.  TODO?
CBigIntegerMatrix::EMatrixOpReturnValue CBigIntegerMatrix::MultiplyOracle(CBigIntegerMatrix &A,
                                                                          CBigIntegerMatrix &B,
                                                                          CBigIntegerMatrix &C,
                                                                          CArithmeticBox    &cArithmeticBox)
{
    size_t               i,j,k;
    EMatrixOpReturnValue eReturnCode;

    if(A.m_nCols != B.m_nRows ||
       C.m_nCols != B.m_nCols ||
       C.m_nRows != A.m_nRows)
    {
        eReturnCode = eMalformed;
        goto exit;
    }
    for(i=0;i<A.m_nRows;i++)
    {
        for(j=0;j<B.m_nCols;j++)
        {
            if(eOperationSucceeded != cArithmeticBox.Multiply(A[i][0],
                                                              B[0][j],
                                                              C[i][j]))
            {
                eReturnCode = eOutOfMemory;
                goto exit;
            }
            for(k=1;k<A.m_nCols;k++)
            {
                if(eOperationSucceeded != cArithmeticBox.MultiplyAdd(A[i][k],
                                                                     B[k][j],
                                                                     C[i][j]))
                {
                    eReturnCode = eOutOfMemory;
                    goto exit;
                }
            }
        }
    }
    eReturnCode = eWorked;
exit:
    return eReturnCode;
}

CBigIntegerMatrix::EMatrixOpReturnValue CBigIntegerMatrix::Multiply(CBigIntegerMatrix &A,
                                                                    CBigIntegerMatrix &B,
                                                                    CBigIntegerMatrix &C,
                                                                    CArithmeticBox    &cArithmeticBox)
{
    if (A.m_nCols != B.m_nRows ||
        C.m_nCols != B.m_nCols ||
        C.m_nRows != A.m_nRows)
    {
        return eMalformed;
    }
    return Multiply(A, B, C, 0, 0, A.m_nRows, A.m_nCols, 0, 0, B.m_nCols, 0, 0, cArithmeticBox);
}

/*
Strassen matrix multiplication:
Consider the matrix multiplication AB = C where
    { a11   a12 }       { b11  b12 }
A = { a21   a22 }   B = { b21  b22 }

We only consider square matrices.  Where the size is odd, the larger half is the first row/first column

Taking m1 = (a21 + a22 - a11)(b22 - b12 + b11)
       m2 = (a11)(b11)                   <- Store this in c11 of product matrix
       m3 = (a12)(b21)
       m4 = (a11 - a21)(b22 - b12)
       m5 = (a21 + a22)(b12 - b11)       <- Note that even when matrix is odd-sized, product can fit in c22 of product matrix: short rows for A; don't care about odd column
       m6 = (a12 - a21 + a11 - a22)(b22) <- Note that even when matrix is odd-sized, product can fit in c12 of product matrix
       m7 = (a22)(b11 + b22 - b12 - b21) <- Note that even when matrix is odd-sized, product can fit in c21 of product matrix
we get that
    { m2 + m3              m1 + m2 + m5 + m6 }
C = { m1 + m2 + m4 - m7    m1 + m2 + m4 + m5 }
This gives C in 7 half-sized multiplications, for assymptotic performance n^(log base 2 (7)), or about n^2.81 -- a bit better than the n^3 of
regular matrix multiplication.  It contains 14 matrix additions/subtractions for the arguanets for the multiplications, and another 10 to
combine the products into the final result -- but these can be reused.
let x1 = a11 - a21
    x2 = a22 - x1
    x3 = a12 - x2
    y1 = b22 - b12
    y2 = y1 + b11
    y3 = y2 - b21
then m1 = x2*y2
     m4 = x1*y1
     m6 = (x3)(b22)
     m7 = (a22)(y3)
reducing the argument additions from 14 to 8
Similarly if we let z1 = m1 + m2
                    z2 = z1 + m4
    { m2 + m3    z1 + m5 + m6 }
C = { z2 - m7    z2 + m5 }
reducing the additions/subtractions for putting the final result together from 10 to 7, for a total of 15 half-sezed matrix additions

*/
CBigIntegerMatrix::EMatrixOpReturnValue CBigIntegerMatrix::Multiply(CBigIntegerMatrix &A,
                                                                    CBigIntegerMatrix &B,
                                                                    CBigIntegerMatrix &C,
                                                                    size_t            nFirstRowA,
                                                                    size_t            nFirstColA,
                                                                    size_t            nRowsA,
                                                                    size_t            nRowLengthA,
                                                                    size_t            nFirstRowB,
                                                                    size_t            nFirstColB,
                                                                    size_t            nColsB,
                                                                    size_t            nFirstRowC,
                                                                    size_t            nFirstColC,
                                                                    CArithmeticBox    &cArithmeticBox)
{
    size_t               i, j;
    EMatrixOpReturnValue eReturnCode;
    if(ShouldUseBasicMultiply(A,B,nFirstRowA,nFirstColA,nRowsA,nRowLengthA,nFirstRowB,nFirstColB,nColsB))
    {
        // do directly with standard algorithm instead of Strassen
        for(i=0; i<nRowsA; i++)
        {
            for(int j=0; j<nColsB; j++)
            {
                if(eOperationSucceeded != cArithmeticBox.Multiply(A[nFirstRowA+i][nFirstColA],
                                                                  B[nFirstRowB][nFirstColB+j],
                                                                  C[nFirstRowC+i][nFirstColC+j]))
                {
                    return eOutOfMemory;
                }
                for(size_t k=1; k<nRowLengthA; k++)
                {
                    if (eOperationSucceeded != cArithmeticBox.MultiplyAdd(A[nFirstRowA + i][nFirstColA + k],
                                                                          B[nFirstRowB + k][nFirstColB + j],
                                                                          C[nFirstRowC + i][nFirstColC + j]))
                    {
                        return eOutOfMemory;
                    }
                }
            }
        }
    }
    else
    {
        size_t nHalfRows      = (nRowsA+1)/2;
        size_t nHalfCols      = (nColsB+1)/2;
        size_t nHalfRowLength = (nRowLengthA+1)/2;
        CBigIntegerMatrix mLocalAArgs(nHalfRows,nHalfRowLength);
        CBigIntegerMatrix mLocalBArgs(nHalfRowLength,nHalfCols);
        CBigIntegerMatrix mLocalProduct(nHalfRows, nHalfCols);
        // start with m4
        // A argument: a11 - a21 (x1)
        for(i=0; i<nRowsA-nHalfRows; i++)
        {
            for(j=0; j<nHalfRowLength; j++)
            {
                if (eOperationSucceeded != cArithmeticBox.Subtract(A[nFirstRowA+i][nFirstColA+j],
                                                                   A[nFirstRowA+nHalfRows+i][nFirstColA+j],
                                                                   mLocalAArgs[i][j]))
                {
                    return eOutOfMemory;
                }
            }
        }
        for(; i<nHalfRows; i++)
        {
            for(j=0; j<nHalfRowLength; j++)
            {
                if(!(mLocalAArgs[i][j] = A[nFirstRowA+i][nFirstColA+j])) return eOutOfMemory;
            }
        }
        // B argument: b22 - b12 (y1)
        for(i=0; i<nRowLengthA-nHalfRowLength; i++)
        {
            for(j=0; j<nColsB-nHalfCols; j++)
            {
                if (eOperationSucceeded != cArithmeticBox.Subtract(B[nFirstRowB+nHalfRowLength+i][nFirstColB+nHalfCols+j],
                                                                   B[nFirstRowB+i][nFirstColB+nHalfCols+j],
                                                                   mLocalBArgs[i][j]))
                {
                    return eOutOfMemory;
                }
            }
        }
        for(; i<nHalfRowLength; i++)
        {
            for(j=0; j<nColsB-nHalfCols; j++)
            {
                if(!(mLocalBArgs[i][j] = B[nFirstRowB+i][nFirstColB+nHalfCols+j])) return eOutOfMemory;
                mLocalBArgs[i][j].Invert();
            }
        }
        // compute m4 (store in c22)
        eReturnCode = Multiply(mLocalAArgs,
                               mLocalBArgs,
                               C,
                               0,
                               0,
                               nRowsA-nHalfRows,
                               nHalfRowLength,
                               0,
                               0,
                               nColsB-nHalfCols,
                               nFirstRowC+nHalfRows,
                               nFirstColC+nHalfCols,
                               cArithmeticBox);
        if (eWorked != eReturnCode) return eReturnCode;
        // next up: m1
        // A argument (x2): a22 - x1
        for(i=0; i<nRowsA-nHalfRows; i++)
        {
            for(j=0; j<nRowLengthA-nHalfRowLength; j++)
            {
                if (eOperationSucceeded != cArithmeticBox.Subtract(A[nFirstRowA+nHalfRows+i][nFirstColA+nHalfRowLength+j], mLocalAArgs[i][j], mLocalAArgs[i][j])) return eOutOfMemory;
            }
            for(; j<nHalfRowLength; j++)
            {
                mLocalAArgs[i][j].Invert();
            }
        }
        for(; i<nHalfRows; i++)
        {
            for(j=0; j<nHalfRowLength; j++)
            {
                mLocalAArgs[i][j].Invert();
            }
        }
        // B argument (y2): y1 + b11
        for(i=0; i<nHalfRowLength; i++)
        {
            for(j=0; j<nHalfCols; j++)
            {
                if(!(mLocalBArgs[i][j] += B[nFirstRowB+i][nFirstColB+j])) return eOutOfMemory;
            }
        }
        // compute m1 (store in mLocalProduct)
        eReturnCode = Multiply(mLocalAArgs,
                               mLocalBArgs,
                               mLocalProduct,
                               0,
                               0,
                               nHalfRows,
                               nHalfRowLength,
                               0,
                               0,
                               nHalfCols,
                               0,
                               0,
                               cArithmeticBox);
        if (eWorked != eReturnCode) return eReturnCode;
        // next: m6 -- (a12 - a21 + a11 - a22)(b22)
        // A argument (x3): a12 - x2
        for(i=0; i<nHalfRows; i++)
        {
            for(j=0; j<nRowLengthA-nHalfRowLength; j++)
            {
                if (eOperationSucceeded != cArithmeticBox.Subtract(A[nFirstRowA+i][nFirstColA+nHalfRowLength+j], mLocalAArgs[i][j], mLocalAArgs[i][j])) return eOutOfMemory;
            }
            /* unecessary -- ignore last column in multiply anyway, and don't use x3 again after this
            for(; j<nHalfRowLength; j++)
            {
                mLocalAArgs[i][j].Invert();
            }*/
        }
        // compute m6 (store in c12)
        eReturnCode = Multiply(mLocalAArgs,
                               B,
                               C,
                               0,
                               0,
                               nHalfRows,
                               nRowLengthA-nHalfRowLength,
                               nFirstRowB+nHalfRowLength,
                               nFirstColB+nHalfCols,
                               nColsB-nHalfCols,
                               nFirstRowC,
                               nFirstColC+nHalfCols,
                               cArithmeticBox);
        if(eWorked != eReturnCode) return eReturnCode;
        // next: m7
        // B argument (y3): y2 - b21
        // In fact compute (b21 - y2) -- want -m7
        for(i=0; i<nRowLengthA-nHalfRowLength; i++)
        {
            for(j=0; j<nHalfCols; j++)
            {
                if (eOperationSucceeded != cArithmeticBox.Subtract(B[nFirstRowB+nHalfRowLength+i][nFirstColB+j],
                                                                   mLocalBArgs[i][j],
                                                                   mLocalBArgs[i][j]))
                {
                    return eOutOfMemory;
                }
            }
        }
        /* Note we don't need this -- don't use the residual row in the B args in the multiply, and never use y3 again
        for (; i<nHalfRowLength; i++)
        {
            for(j=0; j<nHalfCols; j++)
            {
                mLocalBArgs[i][j].Invert();
            }
        }*/
        // compute -m7 (store in c21)
        eReturnCode = Multiply(A,
                               mLocalBArgs,
                               C,
                               nFirstRowA+nHalfRows,
                               nFirstColA+nHalfRowLength,
                               nRowsA-nHalfRows,
                               nRowLengthA-nHalfRowLength,
                               0,
                               0,
                               nHalfCols,
                               nFirstRowC+nHalfRows,
                               nFirstColC,
                               cArithmeticBox);
        if (eWorked != eReturnCode)
            return eReturnCode;
        // now:
        // m1 in local product
        // m4 is in c22
        // m6 is in c12
        // -m7 is in c21
        // next: m2 -- (a11)(b11).  Put in c11
        eReturnCode = Multiply(A,
                               B,
                               C,
                               nFirstRowA,
                               nFirstColA,
                               nHalfRows,
                               nHalfRowLength,
                               nFirstRowB,
                               nFirstColB,
                               nHalfCols,
                               nFirstRowC,
                               nFirstColC,
                               cArithmeticBox);
        if (eWorked != eReturnCode) return eReturnCode;
        // add m2 to m1.  Add m1+m2 to m4 (in c22) and m6 (in c12).  Add m1+m2+m4 to -m7 (in c21)
        for(i=0; i<nRowsA-nHalfRows; i++)
        {
            for(j=0; j<nColsB-nHalfCols; j++)
            {
                if(!(mLocalProduct[i][j]                               += C[nFirstRowC+i][nFirstColC+j])) return eOutOfMemory;                      // m1+m2
                if(!(C[nFirstRowC+nHalfRows+i][nFirstColC+nHalfCols+j] += mLocalProduct[i][j])) return eOutOfMemory;                                // m1+m2+m4     -- c22
                if(!(C[nFirstRowC+i][nFirstColC+nHalfCols+j]           += mLocalProduct[i][j])) return eOutOfMemory;                                // m1+m2+m6     -- c12
                if(!(C[nFirstRowC+nHalfRows+i][nFirstColC+j]           += C[nFirstRowC+nHalfRows+i][nFirstColC+nHalfCols+j])) return eOutOfMemory;  // m1+m2+m4-m7  -- c21
            }
            for(; j<nHalfCols; j++)
            {
                if(!(mLocalProduct[i][j]                               += C[nFirstRowC+i][nFirstColC+j])) return eOutOfMemory;                      // m1+m2
                if(!(C[nFirstRowC+nHalfRows+i][nFirstColC+j]           += mLocalProduct[i][j])) return eOutOfMemory;                                // m1+m2+m4-m7  -- c21
            }
        }
        for(; i<nHalfRows; i++)
        {
            for(j=0; j<nColsB-nHalfCols; j++)
            {
                if(!(mLocalProduct[i][j]                               += C[nFirstRowC+i][nFirstColC+j])) return eOutOfMemory;                      // m1+m2
                if(!(C[nFirstRowC+i][nFirstColC+nHalfCols+j]           += mLocalProduct[i][j])) return eOutOfMemory;                                // m1+m2+m6     -- c12
            }
        }
        // Now:
        //     { m2            m1+m2+m6 }
        // C = { m1+m2+m4-m7   m1+m2+m4 }
        // compute m3 -- a12*b21  (put in local product)
        eReturnCode = Multiply(A,
                               B,
                               mLocalProduct,
                               nFirstRowA,
                               nFirstColA+nHalfRowLength,
                               nHalfRows,
                               nRowLengthA-nHalfRowLength,
                               nFirstRowB+nHalfRowLength,
                               nFirstColB,
                               nHalfCols,
                               0,
                               0,
                               cArithmeticBox);
        if (eWorked != eReturnCode) return eReturnCode;
        // add m3 into place
        for(i=0; i<nHalfRows; i++)
        {
            for(j=0; j<nHalfCols; j++)
            {
                if(!(C[nFirstRowC+i][nFirstColC+j] += mLocalProduct[i][j])) return eOutOfMemory;
            }
        }
        // finally, m5
        // A argument: a21 + a22
        for(i=0; i<nRowsA-nHalfRows; i++)
        {
            for(j=0; j<nRowLengthA-nHalfRowLength; j++)
            {
                if (eOperationSucceeded != cArithmeticBox.Add(A[nFirstRowA+nHalfRows+i][nFirstColA+j],
                                                              A[nFirstRowA+nHalfRows+i][nFirstColA+nHalfRowLength+j],
                                                              mLocalAArgs[i][j]))
                {
                    return eOutOfMemory;
                }
            }
            for(; j<nHalfRowLength; j++)
            {
                if(!(mLocalAArgs[i][j] = A[nFirstRowA+nHalfRows+i][nFirstColA+j])) return eOutOfMemory;
            }
        }
        // B argument: b12 - b11
        for(i=0; i<nHalfRowLength; i++)
        {
            for(j=0; j<nColsB-nHalfCols; j++)
            {
                if (eOperationSucceeded != cArithmeticBox.Subtract(B[nFirstRowB+i][nFirstColB+nHalfCols+j],
                                                                   B[nFirstRowB+i][nFirstColB+j],
                                                                   mLocalBArgs[i][j]))
                {
                    return eOutOfMemory;
                }
            }
            /* not needed -- don't use the residual column of m5
            for(; j<nHalfCols; j++)
            {
                mLocalBArgs[i][j] = B[nFirstRowB+i][nFirstColB+j];
                mLocalBArgs[i][j].Invert();
            }*/
        }
        // compute m5 (put in local product)
        eReturnCode = Multiply(mLocalAArgs,
                               mLocalBArgs,
                               mLocalProduct,
                               0,
                               0,
                               nRowsA-nHalfRows,
                               nHalfRowLength,
                               0,
                               0,
                               nColsB-nHalfCols,
                               0,
                               0,
                               cArithmeticBox);
        if (eWorked != eReturnCode) return eReturnCode;
        // add m5 to c12 and c22 and we're done
        for(i=0; i<nRowsA-nHalfRows; i++)
        {
            for(j=0; j<nColsB-nHalfCols; j++)
            {
                if(!(C[nFirstRowC+i][nFirstColC+nHalfCols+j]           += mLocalProduct[i][j])) return eOutOfMemory;  // c12 += m5
                if(!(C[nFirstRowC+nHalfRows+i][nFirstColC+nHalfCols+j] += mLocalProduct[i][j])) return eOutOfMemory;  // c22 += m5
            }
        }
    }
    return eWorked;
}

/*
Strassen is assymptotically superior to the basic algorithm, but uses more memory and has a poorer access pattern -- plus
for small matrices it is more work; assymptotically  superior does not mean *everywhere* superior.  So where to draw the line?
Suppose n = 2m, for some integer n.
Using the standard algorithm we need n^3 (big) integer multiplications and (n-1)*n^2 additions, or 2n^3 - n^2 (big) integer operations
overall -- 16m*3 - 4m^2 (for now, just assume that an integer multiplication takes at least as long as an addition)
Using Strassen for the big problem and the standard algorithm for the small ones it generates:
The half-sized additions each take m^2 integer additions and the multiplies 2m^3 - n^2 operations, so this method uses
15m^2 + 7(2m^3 - m^2) = 14m^3 + 8m^2 operations
We get a clear win for Strassen (ignoring greater code overhead and less-efficient memory access patterns for Strassen in comparison to the standard
algorithm) assuming 14m^3 + 8m^2 <= 16m^3 - 4m^2.
14m^3 + 8m^2 <= 16m^3 - 4m^2 <-> 14m^3 + 12m^2 <= 16m^3
                             <-> 12m^2 <= 2m^3
                             <->  6 <= m
So for 12x12 and larger matrix multiplications we should use Strassen, and standard for smaller matrices.  Note that this is relatively conservative --
in fact the integer multiplies are more expensive than the additions.
So, that's the theory.
To test the actual performance, I did a bunch of square matrix multiplications using all entries of a fixed size in DIGITs for both 16 and 32-bit
DIGITs
16-bit changeovers:
Size: 2  Digits: 37  Iterations: 131072 Basic: 1485 milliseconds  Strassen: 1484 milliseconds
Size: 2  Digits: 37  Iterations: 131072 Basic: 1547 milliseconds  Strassen: 1500 milliseconds
Size: 4  Digits: 21  Iterations: 32768  Basic: 1250 milliseconds  Strassen: 1203 milliseconds
Size: 4  Digits: 22  Iterations: 32768  Basic: 1188 milliseconds  Strassen: 1172 milliseconds
Size: 8  Digits: 15  Iterations: 8192   Basic: 1453 milliseconds  Strassen: 1391 milliseconds
Size: 8  Digits: 11  Iterations: 16384  Basic: 1750 milliseconds  Strassen: 1703 milliseconds
Size: 16  Digits: 10  Iterations: 2048  Basic: 1391 milliseconds  Strassen: 1343 milliseconds
Size: 16  Digits: 10  Iterations: 2048  Basic: 1531 milliseconds  Strassen: 1516 milliseconds
Size: 32  Digits: 5  Iterations: 512    Basic: 1125 milliseconds  Strassen: 1047 milliseconds
Size: 32  Digits: 5  Iterations: 512    Basic: 1078 milliseconds  Strassen: 1078 milliseconds
Size: 64  Digits: 2  Iterations: 128    Basic: 1468 milliseconds  Strassen: 1453 milliseconds
Size: 64  Digits: 3  Iterations: 128    Basic: 1657 milliseconds  Strassen: 1625 milliseconds
Size: 128  Digits: 1  Iterations: 16    Basic: 1609 milliseconds  Strassen: 1547 milliseconds
Size: 128  Digits: 1  Iterations: 16    Basic: 1500 milliseconds  Strassen: 1375 milliseconds

32-bit changeovers:
Size: 2  Digits: 35  Iterations: 131072 Basic: 1235 milliseconds  Strassen: 1218 milliseconds
Size: 2  Digits: 44  Iterations: 131072 Basic: 1469 milliseconds  Strassen: 1453 milliseconds
Size: 4  Digits: 31  Iterations: 32768  Basic: 1546 milliseconds  Strassen: 1469 milliseconds
Size: 4  Digits: 23  Iterations: 32768  Basic: 1031 milliseconds  Strassen: 984 milliseconds
Size: 8  Digits: 15  Iterations: 8192   Basic: 1047 milliseconds  Strassen: 1015 milliseconds
Size: 8  Digits: 15  Iterations: 8192   Basic: 1172 milliseconds  Strassen: 1047 milliseconds
Size: 16  Digits: 10  Iterations: 2048  Basic: 1266 milliseconds  Strassen: 1234 milliseconds
Size: 16  Digits: 10  Iterations: 2048  Basic: 1281 milliseconds  Strassen: 1234 milliseconds
Size: 32  Digits: 5  Iterations: 512    Basic: 1078 milliseconds  Strassen: 1047 milliseconds
Size: 32  Digits: 10  Iterations: 256   Basic: 1219 milliseconds  Strassen: 1156 milliseconds
Size: 64  Digits: 3  Iterations: 128    Basic: 1609 milliseconds  Strassen: 1484 milliseconds
Size: 64  Digits: 3  Iterations: 128    Basic: 1500 milliseconds  Strassen: 1406 milliseconds
Size: 128  Digits: 1  Iterations: 16    Basic: 1281 milliseconds  Strassen: 1235 milliseconds
Size: 128  Digits: 1  Iterations: 16    Basic: 1500 milliseconds  Strassen: 1375 milliseconds

(For smaller matrices for the given entry size, basic is better.)

So... 12 is not a good general-purpose threshold.
If the minimum size (A rows, A cols, B cols) is at least 128, use Strassen.  (Note the matrices might
not be square!)
Otherwise, add up the total number of DIGITs for all the elements of A and B.  If that sum, divided
by the smallest dimension, is at least 256 use Strassen.
If neither of the above hold, use the basic algorithm.

That, at least, is for retail.  In debug we don't *really* care about performance; we care about testing.
In debug, use Strassen whenever we can: so long as the minimum dimension is at least 2.  That way we
get greater depth of Strassen usage for a given problem size, making validation easier.
*/
bool CBigIntegerMatrix::ShouldUseBasicMultiply(CBigIntegerMatrix &A,
                                               CBigIntegerMatrix &B,
                                               size_t            nFirstRowA,
                                               size_t            nFirstColA,
                                               size_t            nRowsA,
                                               size_t            nRowLengthA,
                                               size_t            nFirstRowB,
                                               size_t            nFirstColB,
                                               size_t            nColsB)
{
    size_t nTotalDIGITs;
    size_t nMinDimension = min(nRowsA, min(nRowLengthA, nColsB));
#ifdef _DEBUG
    return (1==nMinDimension);
#endif
    if (128 <= nMinDimension) return false;
    if (1==nMinDimension)     return true; // Strassen won't work
    nTotalDIGITs = 0;
    for(size_t i=nFirstRowA; i<nFirstRowA+nRowsA; i++)
    {
        for(size_t j=nFirstColA; j<nFirstColA+nRowLengthA; j++)
        {
            nTotalDIGITs += A[i][j].GetSize();
        }
    }
    for(size_t i=nFirstRowB; i<nFirstRowB+nRowLengthA; i++)
    {
        for(size_t j=nFirstColB; j<nFirstColB+nColsB; j++)
        {
            nTotalDIGITs += B[i][j].GetSize();
        }
    }
    return (nTotalDIGITs < nMinDimension*256);
}

void CBigIntegerMatrix::Print(FILE *f)
{
    size_t row, col;
    if(f==NULL)
    {
        f = stdout;
    }
    for(row=0;row<m_nRows;row++)
    {
        for(col=0;col<m_nCols;col++)
        {
            fprintf(f,"%i,%i: ",row,col);
            m_ppData[row][col].PrintHexToFile(f);
        }
    }
}

CBigIntegerMatrix::EMatrixOpReturnValue CBigIntegerMatrix::operator=(CBigIntegerMatrix &nMatrix)
{
    if (m_nRows != nMatrix.m_nRows || m_nCols != nMatrix.m_nCols) return eMalformed;
    for(size_t i=0;i<m_nRows; i++)
    {
        for(size_t j=0; j<m_nCols; j++)
        {
            if(!(m_ppData[i][j] = nMatrix[i][j])) return eOutOfMemory;
        }
    }
    return eWorked;
}

bool CBigIntegerMatrix::operator==(const CBigIntegerMatrix &toCompare)
{
    if(m_nCols != toCompare.m_nCols || m_nRows != toCompare.m_nRows) return false;
    for(size_t i=0; i<m_nRows; i++)
    {
        for(size_t j=0; j<m_nCols; j++)
        {
            if(m_ppData[i][j] != toCompare[i][j]) return false;
        }
    }
    return true;
}

bool CBigIntegerMatrix::operator!=(const CBigIntegerMatrix &toCompare)
{
    if(m_nCols != toCompare.m_nCols || m_nRows != toCompare.m_nRows) return true;
    for(size_t i=0; i<m_nRows; i++)
    {
        for(size_t j=0; j<m_nCols; j++)
        {
            if(m_ppData[i][j] != toCompare[i][j]) return true;
        }
    }
    return false;
}