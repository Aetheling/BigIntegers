#include "SSystemData.h"
#include "ArithmeticBox.h"
#include "CBigIntegerMatrix.h"
#include "CBigIntegerVectors.h"
#include "Constants.h"

////////////////////////////////////////////////////////////////////////
//                                                                    //
//                            SSystemData                             //
//                                                                    //
////////////////////////////////////////////////////////////////////////

SSystemData::SSystemData()
{
    m_pppCoefficientsPi = NULL;
    m_pppCoefficientsRi = NULL;
    m_ppnSizesPi        = NULL;
    m_ppnSizesRi        = NULL;
    m_ppbSigns          = NULL;
    m_nSystemSize       = 0;
    m_nMaxSizeRI        = 0;
    m_nMaxSizePI        = 0;
}

SSystemData::~SSystemData()
{
    Clear();
}

void SSystemData::Clear()
{
    size_t i;
    if(NULL == m_ppnSizesRi)
    {
        // clear has already been called, or Init wasn't called in the first place
        ;
    }
    else
    {
        // first, free up the memory for the Ri stuff
        delete m_ppnSizesRi[0];
        free(m_ppnSizesRi);
        delete m_pppCoefficientsRi[0][0];
        for(i=0;i<2*m_nSystemSize-3;i++)
        {
            free(m_pppCoefficientsRi[i]);
        }
        free(m_pppCoefficientsRi);

        // then, for the Pi
        delete m_ppbSigns[0];
        free(m_ppbSigns);
        delete m_ppnSizesPi[0];
        free(m_ppnSizesPi);
        delete m_pppCoefficientsPi[0][0];
        for(i=0;i<2*m_nSystemSize-3;i++)
        {
            free(m_pppCoefficientsPi[i]);
        }
        free(m_pppCoefficientsPi);

        // make things look clean
        m_ppnSizesPi        = NULL;
        m_ppnSizesRi        = NULL;
        m_ppbSigns          = NULL;
        m_pppCoefficientsPi = NULL;
        m_pppCoefficientsRi = NULL;
    }
}

void SSystemData::Init(size_t n)
{
    CArithmeticBox       cBox;
    CBigIntegerVector    cDiag(2*n - 1);
    const CBigInteger    nOne("1"), nZero("0");
    CBigInteger          nCoef("1");
    size_t               i,j,k,nSp=0,nSpaceNeeded=0;
    CBigIntegerMatrix    cBigMat(2*n-1);
    //CBigIntegerVector    *pDiag   = new CBigIntegerVector(2*n-1);

    m_nSystemSize         = n; // only use m_nSystemSize for cleanup, printing
    cBigMat[0][0]         = nOne;
    cBigMat[2*n-2][2*n-2] = nOne;
    for(i=1;i<2*n-1;i++)
    {
        cBigMat[0][i]       = nZero;
        cBigMat[2*n-2][i-1] = nZero;
    }
    nSpaceNeeded = 0;
    for(j=1;j<2*n-2;j++)
    {
       // pBigMat->Assign(j,0,nOne);
        cBigMat[j][0] = nOne;
        for(i=1;i<n;i++)
        {
            cBox.Multiply(nCoef,cBigMat[j][i-1], cBigMat[j][i]);
            nSpaceNeeded += cBigMat[j][i].GetSize();
        }
        for(;i<2*n-1;i++)
        {
            cBox.Multiply(nCoef, cBigMat[j][i-1], cBigMat[j][i]);
        }
        nCoef += 1;
    }
    // Allocate the space for the Ri coefficient portion.  Note we don't care
    // about the first and last rows, every element is positive, and the first
    // column of the middle 2n-3 rows is all ones, so we can cut back on the
    // stored values somewhat
    m_pppCoefficientsRi = (DIGIT ***) malloc(sizeof(DIGIT **)*(2*n-3));
    m_ppnSizesRi        = (size_t **) malloc(sizeof(size_t *)*(2*n-3));
    m_ppnSizesRi[0]     = new size_t[(2*n-3)*(n-1)];
    for(i=0;i<2*n-3;i++)
    {
        m_pppCoefficientsRi[i] = (DIGIT **) malloc(sizeof(DIGIT *)*(n-1));
        m_ppnSizesRi[i]        = m_ppnSizesRi[0] + i*(n-1);
    }
    m_pppCoefficientsRi[0][0] = new DIGIT[nSpaceNeeded];
    
    // copy the coefs into the appropriate portion of the SystemData structure
    for(i=0;i<2*n-3;i++)
    {
        for(j=0;j<n-1;j++)
        {
            m_pppCoefficientsRi[i][j] = m_pppCoefficientsRi[0][0] + nSp;
            memcpy(m_pppCoefficientsRi[i][j],
                   cBigMat[i+1][j+1].GetValue(),
                   cBigMat[i+1][j+1].GetSize()*sizeof(DIGIT));
            k                  =  cBigMat[i+1][j+1].GetSize();
            m_ppnSizesRi[i][j] =  k;
            nSp                += k;
        }
    }
    m_nMaxSizeRI = m_ppnSizesRi[2*n-4][n-2];
    // At this point, the basic system has been constructed.
    // Compute its quasi-inverse.
    cBigMat.QuasiInverse(cDiag, cBox);
    // Find the space needed for the inverse system -- note that for efficiency
    // reasons it is NOT stored as a standard matrix!  (Not all the rows are
    // stored flattened rather than the full matrix structure)
    nSpaceNeeded = 0;
    for(i=1;i<2*n-2;i++)
    {
        for(j=0;j<2*n-1;j++)
        {
            nSp = cBigMat[i][j].GetSize();
            nSpaceNeeded += nSp;
            if(nSp>m_nMaxSizePI)
            {
                m_nMaxSizePI = nSp;
            }
        }
        nSpaceNeeded += cDiag.GetValue(i)->GetSize();
    }
    // Allocate the space for the Pi portion
    // Note that we don't need the m_ppbSigns for the diag components: by
    // the construction of the inverse, these are all positive
    m_pppCoefficientsPi = (DIGIT ***) malloc(sizeof(DIGIT **)*(2*n-3));
    m_ppbSigns          = (bool **)   malloc(sizeof(bool *)*(2*n-3));
    m_ppbSigns[0]       = new bool[(2*n-3)*(2*n-1)];
    m_ppnSizesPi        = (size_t **)   malloc(sizeof(size_t *)*(2*n-3));
    m_ppnSizesPi[0]     = new size_t[(2*n-3)*2*n];
    for(i=0;i<2*n-3;i++)
    {
        m_pppCoefficientsPi[i] = (DIGIT **) malloc(sizeof(DIGIT *)*(2*n));
        m_ppbSigns[i]          = m_ppbSigns[0]   + i*(2*n-1);
        m_ppnSizesPi[i]        = m_ppnSizesPi[0] + i*2*n;
    }
    m_pppCoefficientsPi[0][0] = new DIGIT[nSpaceNeeded];
    // Copy that inverse system into the waiting SystemDataNode structure
    // in the proper format.  Note that the first and last rows are known,
    // so are not included.  The last "column" in each row is used to
    // hold the divisor (diag) elements
    nSp = 0;
    m_nMaxDivisorSize = 0;
    for(i=0;i<2*n-3;i++)
    {
        for(j=0;j<2*n-1;j++)
        {
            m_pppCoefficientsPi[i][j] = m_pppCoefficientsPi[0][0] + nSp;
            memcpy(m_pppCoefficientsPi[i][j],
                   cBigMat[i+1][j].GetValue(),
                   cBigMat[i+1][j].GetSize()*sizeof(DIGIT));
            m_ppbSigns[i][j]   =  cBigMat[i+1][j].IsNegative();
            k                  =  cBigMat[i+1][j].GetSize();
            m_ppnSizesPi[i][j] =  k;
            nSp                += k;
        }
        m_pppCoefficientsPi[i][j] = m_pppCoefficientsPi[0][0] + nSp;
        memcpy(m_pppCoefficientsPi[i][j],
               cDiag.GetValue(i+1)->GetValue(),
               (cDiag.GetValue(i+1)->GetSize())*sizeof(DIGIT));
        m_ppnSizesPi[i][j] = cDiag.GetValue(i+1)->GetSize();
        if(m_nMaxDivisorSize<cDiag.GetValue(i+1)->GetSize())
        {
            m_nMaxDivisorSize = cDiag.GetValue(i+1)->GetSize();
        }
        nSp += cDiag.GetValue(i+1)->GetSize();
    }
    if(m_nMaxSizePI < m_nMaxDivisorSize)
    {
        m_nMaxSizePI = m_nMaxDivisorSize;
    }
}

void SSystemData::PrintSystem(bool bVerbose)
{
    size_t i,j;
    printf("System for constructing R[i]s:\n");
    if(bVerbose)
    {
        CBigInteger ToPrint;
        ToPrint.Reserve(m_nMaxSizeRI+m_nMaxSizePI+m_nMaxDivisorSize); // AMPLE space
        ToPrint.SetSize(1);
        ToPrint.GetValue()[0]=1;
        printf("0,0: ");
        ToPrint.PrintHexToFile();
        ToPrint.SetSize(0);
        for(i=0;i<m_nSystemSize-1;i++)
        {
            printf("0,%i: ",i);
            ToPrint.PrintHexToFile();
        }
        for(i=0;i<2*m_nSystemSize-3;i++)
        {
            for(j=0;j<m_nSystemSize-1;j++)
            {
                printf("%i,%i: ",i+1,j);
                ToPrint.SetSize(m_ppnSizesRi[i][j]);
                memcpy(ToPrint.GetValue(),m_pppCoefficientsRi[i][j],m_ppnSizesRi[i][j]*sizeof(DIGIT));
                ToPrint.PrintHexToFile();
            }
        }
        ToPrint.SetSize(0);
        for(j=0;j<m_nSystemSize-1;j++)
        {
            printf("%i,%i: ",i+1,j);
            ToPrint.PrintHexToFile();
        }
        ToPrint.SetSize(1);
        ToPrint.GetValue()[0]=1;
        printf("%i,%i: ",j,i);
        ToPrint.PrintHexToFile();
        printf("\nSystem for constructing P[i]s\n");
        ToPrint.SetNegative(false); // all elements of first, last row positive -- including diag
        ToPrint.SetSize(1);
        ToPrint.GetValue()[0]=1;
        printf("0,0: ");
        ToPrint.PrintHexToFile();
        ToPrint.SetSize(0);
        for(i=0;i<2*m_nSystemSize-2;i++)
        {
            printf("0,%i: ",i);
            ToPrint.PrintHexToFile();
        }
        printf("0,D: ",i);
        ToPrint.SetSize(1);
        ToPrint.GetValue()[0]=1;
        ToPrint.PrintHexToFile();
        for(i=0;i<2*m_nSystemSize-3;i++)
        {
            for(j=0;j<2*m_nSystemSize;j++)
            {
                ToPrint.SetNegative(m_ppbSigns[i][j]);
                ToPrint.SetSize(m_ppnSizesPi[i][j]);
                memcpy(ToPrint.GetValue(),m_pppCoefficientsPi[i][j],m_ppnSizesPi[i][j]*sizeof(DIGIT));
                if(2*m_nSystemSize-1==j)
                {
                    // diagonal
                    ToPrint.SetNegative(false); // all elements of diag positive
                    printf("%i,D: ",i+1);
                }
                else
                {
                    printf("%i,%i: ",i+1,j);
                }
                ToPrint.PrintHexToFile();
            }
        }
        ToPrint.SetNegative(false); // all elements of first, last row positive -- including diag
        ToPrint.SetSize(0);
        for(j=0;j<2*m_nSystemSize-2;j++)
        {
            printf("%i,%i: ",i+1,j);
            ToPrint.PrintHexToFile();
        }
        ToPrint.SetSize(1);
        ToPrint.GetValue()[0]=1;
        printf("%i,%i: ",i+1,j);
        ToPrint.PrintHexToFile();
        printf("%i,D: ",i+1);
        ToPrint.PrintHexToFile();
    }
    else
    {
        printf("1 ");
        for(i=0;i<m_nSystemSize-1;i++)
        {
            printf("0 ");
        }
        printf("\n");
        for(i=0;i<2*m_nSystemSize-3;i++)
        {
            printf("1 ");
            for(j=0;j<m_nSystemSize-1;j++)
            {
                if(m_ppnSizesRi[i][j]==2)
                {
                    printf("%I64u ",m_pppCoefficientsRi[i][j][0]+(((DOUBLEDIGIT) m_pppCoefficientsRi[i][j][1])<<_DIGIT_SIZE_IN_BITS));
                }
                else
                {
                    // assume a single DIGIT
                    printf("%I64u ",(DOUBLEDIGIT) (m_pppCoefficientsRi[i][j][0]));
                }
            }
            printf("\n");
        }
        for(i=0;i<m_nSystemSize-1;i++)
        {
            printf("0 ");
        }
        printf("1\n\n");
        printf("System for constructing P[i]s\n1 ");
        for(i=0;i<2*m_nSystemSize-2;i++)
        {
            printf("0 ");
        }
        printf(" :\t1\n");
        for(i=0;i<2*m_nSystemSize-3;i++)
        {
            for(j=0;j<2*m_nSystemSize;j++)
            {
                if(2*m_nSystemSize-1==j)
                {
                    // diagonal
                    printf(" :\t");
                }
                if(m_ppbSigns[i][j] && 2*m_nSystemSize-1!=j)
                {
                    // negative
                    printf("-");
                }
                if(m_ppnSizesPi[i][j]==2)
                {
                    printf("%I64u ",m_pppCoefficientsPi[i][j][0]+(((DOUBLEDIGIT) m_pppCoefficientsPi[i][j][1])<<_DIGIT_SIZE_IN_BITS));
                }
                else
                {
                    printf("%I64u ",(DOUBLEDIGIT) (m_pppCoefficientsPi[i][j][0]));
                }
            }
            printf("\n");
        }
        for(i=0;i<2*m_nSystemSize-2;i++)
        {
            printf("0 ");
        }
        printf("1 :\t1\n\n");
        /*
        printf("And the diagonal:\n1 ");
        for(i=0;i<2*m_nSystemSize-3;i++)
        {
            printf("%i ",(DIGIT) (m_pppCoefficientsPi[i][2*m_nSystemSize-1][0]));
        }
        printf("1\n");
        */
        printf("R(i) coefficient sizes:\n");
        for(i=0;i<2*m_nSystemSize-3;i++)
        {
            for(j=0;j<m_nSystemSize-1;j++)
            {
                printf("%i ",m_ppnSizesRi[i][j]);
            }
            printf("\n");
        }
        printf("P(i) coefficient sizes:\n");
        for(i=0;i<2*m_nSystemSize-3;i++)
        {
            for(j=0;j<2*m_nSystemSize-1;j++)
            {
                printf("%i ",m_ppnSizesPi[i][j]);
            }
            printf("\n");
        }
        printf("Diagonal (divisor) sizes:\n");
        for(i=0;i<2*m_nSystemSize-3;i++)
        {
            printf("%i ",m_ppnSizesPi[i][2*m_nSystemSize-1]);
        }
        printf("\n");
    }
}

////////////////////////////////////////////////////////////////////////
//                                                                    //
//                          SSystemDataNode                           //
//                                                                    //
////////////////////////////////////////////////////////////////////////

SSystemDataNode::SSystemDataNode()
{
    // use Coefficients to signal system not yet generated
    m_pData[0].m_pppCoefficientsPi = NULL;
    m_pData[1].m_pppCoefficientsPi = NULL;
    m_pData[2].m_pppCoefficientsPi = NULL;
    m_pData[3].m_pppCoefficientsPi = NULL;
    m_pData[4].m_pppCoefficientsPi = NULL;
    m_pNext                        = NULL;
}