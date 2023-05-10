#pragma once
#include "BigIntegers.h"

// used to hold the system of equations for a single size (number of pieces)
// See the GenerateSystem procedure for details.  Its index in the SystemDataNode
// list gives its size.
struct SSystemData
{
public: // data
    DIGIT  ***m_pppCoefficientsPi; // coefficients used to compute the P(i)
    DIGIT  ***m_pppCoefficientsRi; // coefficients used to compute the R(i)
    size_t **m_ppnSizesPi;         // the sizes of the coefficients used to compute the P(i), in DIGITs
    size_t **m_ppnSizesRi;         // the sizes of the coefficients used to compute the R(i), in DIGITs
    bool   **m_ppbSigns;           // The m_ppbSigns of the coefficients used to compute the P(i) from R(j).
                                   // Note that by design, all the coefs for computing the R(i) are
                                   // positive
    size_t m_nMaxSizeRI, m_nMaxSizePI;  // the maximum size of the coefficients used to compute
                                        // the R(i) and P(i), respectively, in DIGITs
    size_t m_nMaxDivisorSize;           // the largest divisor used in constructing the P(i)s
    size_t m_nSystemSize;     // the number of "pieces" this system corresponds to
public: // functions
    SSystemData();
    ~SSystemData();
    void Clear();
    void Init(size_t n);
    // Just prints as integers, in matrix format, unless bVerbose is set,
    // in which case it prints the FULL values (useful for multiple-digit entries)
    void PrintSystem(bool bVerbose = false);
};

// Used to hold all the systems currently known, as an ordered chunked linked list
struct SSystemDataNode
{
public:  // variables
    SSystemData     m_pData[5];
    SSystemDataNode *m_pNext;
public:  // functions
    SSystemDataNode();
};