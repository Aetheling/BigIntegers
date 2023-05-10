#include "CModularBoxTest.h"

bool CModularBoxTest::PowerModulusTest()
{
	CBigInteger           nPower, nPowerMod;
	// Note that if 1<m<n and (m,n) are relatively prime then m^(n-2) != 1 and m^(n-1) == 1
    // 70...6A7 is prime, so anything in 1 < n < 70...6A7 is relatively prime to it
	CModularArithmeticBox cBox("70B7D90310FDB40C3F2BA643C039157EDA370D60E87F29B0E23AC3F52A185955994A40AECBC38EF4A9AE43CB3730B9679E614DA37C874D5F6994231DCBE1C1DDDE2A4E36FDCB11B8343B9C800AC83C1B8A949F9F91CEC5065E332BCC55C635CB15CEDB55BD0F9591794B8A1951FAF7D23447DC0E414DECDF5791B4BCDFC20C58D8AEBEC12286A7", false);
	CBigInteger           nOne("1");
	CBigInteger           nTest("952C98CA");
	cBox.GetModulus(&nPower);
	nPower -= 2;
	cBox.Power(&nTest, &nPower, &nPowerMod);
	if (nPowerMod == nOne)
	{
		// oops
		printf("power failed -- result shouldn't be 1\n");
		return false;
	}
	nPower += 1;
	cBox.Power(&nTest, &nPower, &nPowerMod);
	if (nPowerMod != nOne)
	{
		// oops
		printf("power failed -- result should be 1\n");
		return false;
	}
	return true;
}