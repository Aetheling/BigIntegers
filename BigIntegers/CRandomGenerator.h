#include <stdio.h>
#include <windows.h>
#include "Constants.h"
// forward declarations
class CBigInteger;
// function that returns a random 8-bit number, in case the user has a better random number generator than
// the built-in C function (which is not entirely implausible)
typedef BYTE (*PFnRandomBYTE)();

class __declspec(dllexport) CRandomGenerator
{
public:  // functions
    CRandomGenerator(PFnRandomBYTE pfRandomBYTEGenerator = NULL);
	~CRandomGenerator();
	// produces a random big integer of the given number of bits.  If bForceLead
	// is set, it forces the most-significant bit to be 1.
	void RandomBits(size_t nDigits, BYTE nBits, bool bForceLead, CBigInteger &nRandom);
	// generates a random big integer in the range given by the two values passed, inclusive
	// returns false if nHigh<nLow, and the value of nRandom is undefined
	bool RandomInRange(CBigInteger &nLow, CBigInteger &nHigh, CBigInteger &nRandom);
	// returns a random DIGIT
	DIGIT RandomDigit();
	static BYTE DefaultRandomBYTE();
public:  // variables
private: // variables
	PFnRandomBYTE m_pFnRandomBYTE;
	static DWORD  m_dwCount; // counts number of randoms produced, if the default generator is used
	const static DWORD c_dwMaxRandomsForReseed = 10000; // after that many random numbers generated, reseeds
	                                                    // if the default random number generator is used
};