#include <stdio.h>
// forward declarations
class CBigInteger;
class CArithmeticBox;

class __declspec(dllexport) CBigIntegerVector
{
    friend class CBigIntegerMatrix;
public: // functions
    // creates a vector with size nLength slots.
    CBigIntegerVector(size_t nLength);
    ~CBigIntegerVector();
    // returns NULL if the index passed is outside the vector
    CBigInteger *GetValue(size_t i);
    size_t GetLength();
    // does a deep copy.  Returns false on failure (out of memory or malformerd -- vectors of different length)
    bool operator=(CBigIntegerVector &vVec);
    // does NOT do bounds checking!
    CBigInteger &operator[](size_t index);
    // Computes the dot product of the passed vectors.  Returns true on success.
    // Returns false if the vectors are of different length, or of length 0, or
    // insufficient memory is available, or NULLs are passed
    static bool DotProduct(const CBigIntegerVector &vV1,
                           const CBigIntegerVector &vV2,
                           CBigInteger             &nProduct,
                           CArithmeticBox          &cArithmeticBox);
    // Prints the vector to the file passed (or stdout, if not pass), one big integer/line
    void PrintVec(FILE *f = stdout);
protected: // functions
    // Same, but works directly on the arrays of CBigIntegers.  Does no error checking!
    static bool DotProduct(const CBigInteger *pV1,
                           const CBigInteger *pV2,
                           size_t            nLength,
                           CBigInteger       &nProduct,
                           CArithmeticBox    &cBox);
protected: // data
    CBigInteger *m_pnValues;
    size_t      m_nLength;
};