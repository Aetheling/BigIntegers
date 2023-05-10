// forward declarations
class CBigIntegerVector;
class CArithmeticBox;
class CBigInteger;

class __declspec(dllexport) CBigIntegerMatrix
{
    friend class CArithmeticCorrectnessTester;
public:
    enum EMatrixOpReturnValue {eWorked, eSingular, eOutOfMemory, eMalformed};

    CBigIntegerMatrix(size_t nRowsCols);

    CBigIntegerMatrix(size_t nRows, size_t nCols);

    ~CBigIntegerMatrix();

    // how many rows the matrix has
    size_t GetRows();
    // how many cols the matrix has
    size_t GetCols();
    // this one DOES do bounds checking
    CBigInteger *GetValue(size_t nRow, size_t nCol);

    // Performs the matrix-vector multiply.
    bool MatVecMultiply(CBigIntegerVector &vV,
                        CBigIntegerVector &vProd,
                        CArithmeticBox    &cArithmeticBox);

    // Print out the matrix
    void Print(FILE *f = NULL);

    bool operator==(const CBigIntegerMatrix &toCompare);
    bool operator!=(const CBigIntegerMatrix &toCompare);

    // accessor.  Note we can get element(i,j) with matrix[i][j].  Does NOT do bounds checking!
    CBigInteger *operator[](size_t nRow) const
    {
        return m_ppData[nRow];
    }

    // does a deep copy.  Matrices must be the same shape.
    EMatrixOpReturnValue operator=(CBigIntegerMatrix &nMatrix);

    //+--------------------------------------------------------
    //
    // Member:		CBigIntegerMatrix::QuasiInverse, public
    //
    // Synopsis:	Given a nonsingular matrix A (this), computes matrices B and D,
    //              where D is a diagonal matrix, such that BA = D, where the
    //              greatest common divisor of the elements of D is 1.  (D is
    //              stored as a CBigIntegerVector.)  The A matrix is replaced
    //              with its quasi-inverse (B).
    //
    // Algorithm:   Guassian elimination
    //
    // pQuasiInverse is created in the procedure; if an existing matrix is passed,
    // it is deleted
    //
    //----------------------------------------------------------
    EMatrixOpReturnValue QuasiInverse(CBigIntegerVector &vD,
                                      CArithmeticBox    &cArithmeticBox);

    //+--------------------------------------------------------
    //
    // Member:		CBigIntegerMatrix::MultiplyOracle
    //
    // Synopsis:	Computes the matrix product [C] = [A][B].  Note
    //              that this is a matrix multiplication, and in general
    //              [A][B] != [B][A]
    //              Returns true if the multiplication succeeded, false
    //              otherwise (i.e., there was insufficient memory)
    //
    // Algorithm:   For integers (or floats, for that matter) the algorithm
    //              would be
    //              for(i=0;i<size;i++)
    //              {
    //                for(j=0;j<size;j++)
    //                {
    //                  C[i][j] = 0;
    //                  for(k=0;k<size;k++)
    //                  {
    //                    C[i][j] += A[i][k]*B[k][j];
    //                  }
    //                }
    //              }
    //              Here it is the same, adjusted for using extended-
    //              precision integers
    // Note that this is primarily for validation purposes; use Multiply() for
    // use where you care about performance
    //----------------------------------------------------------
    static EMatrixOpReturnValue MultiplyOracle(CBigIntegerMatrix &A,
                                               CBigIntegerMatrix &B,
                                               CBigIntegerMatrix &C,
                                               CArithmeticBox    &cArithmeticBox);

    // optimized matrix multiplication
    static EMatrixOpReturnValue Multiply(CBigIntegerMatrix &A,
                                         CBigIntegerMatrix &B,
                                         CBigIntegerMatrix &C,
                                         CArithmeticBox    &cArithmeticBox);

protected:
    // backend matrix multiplication: allows for picking out a region of the two matrices to multiply, and puts
    // results to a region of the destination matrix.  Uses Strassen assuming the matrix is large enough.
    static EMatrixOpReturnValue Multiply(CBigIntegerMatrix &A,
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
                                         CArithmeticBox    &cArithmeticBox);

    // whether for the particular pair of matrices it would be better to use the basic multiplication
    // algorithm or a step of Strassen
    static bool ShouldUseBasicMultiply(CBigIntegerMatrix &A,
                                       CBigIntegerMatrix &B,
                                       size_t            nFirstRowA,
                                       size_t            nFirstColA,
                                       size_t            nRowsA,
                                       size_t            nRowLengthA,
                                       size_t            nFirstRowB,
                                       size_t            nFirstColB,
                                       size_t            nColsB);

    CBigInteger **m_ppData;
    size_t      m_nRows;
    size_t      m_nCols;
};