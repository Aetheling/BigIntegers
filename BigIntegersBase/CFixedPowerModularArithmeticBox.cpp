#include "..\BigIntegers\ArithmeticBox.h"
#include "..\BigIntegers\CUnsignedArithmeticHelper.h"

CFixedPowerModularArithmeticBox::CFixedPowerModularArithmeticBox(CBigInteger &nPower, CBigInteger &nModulus, bool bProtectAgainstTimingAttacks) : CModularArithmeticBox(nModulus, bProtectAgainstTimingAttacks)
{
    m_nPower = nPower;
    CUnsignedArithmeticHelper::GetLeadBit(nPower.GetSize(), nPower.GetValue(), m_nPowerLeadDigit, m_nPowerLeadBit);
}

void CFixedPowerModularArithmeticBox::Power(CBigInteger &nX, CBigInteger &nXToPower)
{
    PowerLeadPowerDigitKnown(&nX, &m_nPower, m_nPowerLeadDigit, m_nPowerLeadBit, &nXToPower);
}