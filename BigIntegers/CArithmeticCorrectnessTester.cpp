#pragma once
#include "TestConstants.h"
#include "ArithmeticBox.h"
#include "CUnsignedArithmeticHelper.h"
#include "CArithmeticTestHelper.h"
#include "CBigIntegerVectors.h"
#include "CBigIntegerMatrix.h"
#include "SSystemData.h"
#include "math.h"

#pragma warning(disable:4267)    // conversion from 'size_t' to 'unsigned int' -- possible loss of data

bool CArithmeticCorrectnessTester::TestBigInteger(bool bVerbose)
{
    CBigIntegerForTest nX;
    CBigIntegerForTest nX2;
    CBigIntegerForTest nY;
    CBigIntegerForTest nZ;
    CBigIntegerForTest nNeg;
    CBigIntegerForTest nBad;
    CBigIntegerForTest nBaseTenTest;
    CWorkspace         cWork;
    DIGIT              *pWork;
    size_t             nMemNeeds;
    const char *szBase                  = "FFFFFFFFFFFFFFFF";
    const char *szBase10TestHexA        = "123456789ABCDEF0";
    const char *szBase10TestDecimalA    = "1311768467463790320";
    const char *szBase10TestHexB        = "-7890123456ABCDEF";
    const char *szBase10TestDecimalB    = "-8687463697199386095";
    const char *szShouldEqualBase       = "0FFFFFFFFFFFFFFFF";
    const char *szBasePlusOne           = "10000000000000000";
    const char *szBasePlusOneMinusSeven = "FFFFFFFFFFFFFFF9";
    const char *szMinusBase             = "-FFFFFFFFFFFFFFFF";
    const char *szBadHexString          = "-ABCDEFG";
#if(16==_DIGIT_SIZE_IN_BITS)
    const char *szSmall                 = "FFFF";
#else
    const char *szSmall                 = "FFFFFFFF";
#endif
    DIGIT      *pnYData                 = NULL;
    size_t     nSize                    = 0;
    bool       bTestWorked              = false;

    cWork.Reserve(1000000); // ample space for our simple usage
    pWork = cWork.GetSpace();
    ResetThresholdsForTest();
    if(bVerbose)
    {
        printf("DIGIT size (in BYTES): %i\n",sizeof(DIGIT));
    }
    // test set from string
    if(!nX.SetFromHexString(szBase))
    {
        printf("Failed to set from string.\n");
        goto exit;
    }
    if(nBad.SetFromHexString(szBadHexString))
    {
        printf("Didn't choke on bad hex string\n");
        goto exit;
    }
    printf("Printing x.  Expect: %s\nGot:                 ",szBase);
    if(!nX.PrintHexToScreen())
    {
        printf("<print failed>\n");
        goto exit;
    }
    printf("\n");
    nBaseTenTest.SetFromHexString(szBase10TestHexA);
    printf("Printing y, base 10.  Expect: %s\nGot:                          ",szBase10TestDecimalA);
    if(!nBaseTenTest.PrintDecimalToFile())
    {
        printf("<print to base 10 failed>\n");
        goto exit;
    }
    printf("And with optimized print:     ");
    nMemNeeds          = PrintToBase10MemoryNeeds(nBaseTenTest.GetSize());
    pWork[0]           = TEST_BUFFERGUARD;
    pWork[nMemNeeds+1] = TEST_BUFFERGUARD;
    PrintNumberToBase10(nBaseTenTest, pWork+1);
    nBaseTenTest.SetFromHexString(szBase10TestHexB);
    printf("Printing z, base 10.  Expect: %s\nGot:                          ",szBase10TestDecimalB);
    if(!nBaseTenTest.PrintDecimalToFile())
    {
        printf("<print to base 10 failed>\n");
        goto exit;
    }
    printf("And with optimized print:     ");
    PrintNumberToBase10(nBaseTenTest, pWork);
    if (TEST_BUFFERGUARD != pWork[0] || TEST_BUFFERGUARD != pWork[nMemNeeds + 1])
    {
        printf("Print to base 10 wrote past (or before) workspace\n");
        goto exit;
    }
    nBaseTenTest.SetFromHexString(szSmall);
    printf("Printing z, base 10.  Base:      ");
    nMemNeeds = PrintToBase10MemoryNeeds(nBaseTenTest.GetSize());
    pWork[0] = TEST_BUFFERGUARD;
    pWork[nMemNeeds + 1] = TEST_BUFFERGUARD;
    if (!nBaseTenTest.PrintDecimalToFile())
    {
        printf("<print to base 10 failed>\n");
        goto exit;
    }
    printf("Printing z, base 10.  Optimized: ");
    PrintNumberToBase10(nBaseTenTest, pWork);
    if (TEST_BUFFERGUARD != pWork[0] || TEST_BUFFERGUARD != pWork[nMemNeeds + 1])
    {
        printf("Print to base 10 wrote past (or before) workspace\n");
        goto exit;
    }
    nY.SetFromHexString(szBasePlusOne);
    nZ.SetFromHexString(szBasePlusOneMinusSeven);
    nX2.SetFromHexString(szShouldEqualBase);
    nNeg.SetFromHexString(szMinusBase);
    if(!nX.IsOdd())
    {
        printf("Base integer is odd\n");
        goto exit;
    }
    if(nX.IsNegative())
    {
        printf("Base integer is positive\n");
        goto exit;
    }
    if(!(nX += 1))
    {
        printf("AddSmall ran out of memory???\n");
        goto exit;
    }
    if(nX != nY)
    {
        printf("AddSmall went screwy.  Expected:\n");
        nY.PrintHexToFile();
        printf("Got:\n");
        nX.PrintHexToFile();
        printf("\n");
        goto exit;
    }
    if(!(nX -= 7))
    {
        printf("SubtractSmall ran out of memory???\n");
        goto exit;
    }
    if(nX != nZ)
    {
        printf("SubtractSmall went screwy.  Expected:\n");
        nZ.PrintHexToFile();
        printf("Got:\n");
        nX.PrintHexToFile();
        printf("\n");
        goto exit;
    }
    // test asiignment operator
    nX.SetFromHexString("12345678");
    nY = nX;
    if(nX != nY)
    {
        printf("assignment failed\n");
        goto exit;
    }
    pnYData = nY.GetValue();
    if (nX.GetValue() == pnYData)
    {
        printf("copied pointers, not data\n");
        goto exit;
    }
    nX.SetFromHexString("87654321");
    nY = nX;
    if (nY.GetValue() != pnYData)
    {
        printf("Shouldn't need to reallocate data for copy\n");
        goto exit;
    }
    if (nX != nY)
    {
        printf("assignment failed\n");
        goto exit;
    }
    nX.SetFromHexString("1234567890ABCDE1234567890ABCDE1234567890ABCDE");
    nZ.SetFromHexString("1234567890ABCDE1234567890ABCDE1234567890ABCDE");
    nY = nX;
    if (nY.GetValue() == pnYData)
    {
        printf("Should need to reallocate data for copy\n");
        goto exit;
    }
    if (nZ != nY)
    {
        printf("assignment failed\n");
        goto exit;
    }
    nX = nX;
    if (nX != nZ)
    {
        printf("assigning to self should not be destructive\n");
        goto exit;
    }
    // test set size
    nSize = nX.GetSize();
    if (nX.SetSize(1000000000) || nX.GetSize() != nSize)
    {
        printf("Should not be able to set size to greater than that allocated\n");
        goto exit;
    }
#if(16==_DIGIT_SIZE_IN_BITS)
    nY.SetFromHexString("BCDE");
#else
    nY.SetFromHexString("890ABCDE");
#endif
    if (!nX.SetSize(1) || nX != nY)
    {
        printf("SetSize() failed\n");
        goto exit;
    }
    // test set random -- used for test only
    for(size_t i=0;i<200;i++)
    {
        if(!nX.SetRandom(i,(0==i) ? ::GetTickCount() : 0))
        {
            printf("SetRandom failed\n");
            goto exit;
        }
        if(bVerbose)
        {
            nX.PrintHexToFile();
            printf("\n");
        }
    }
    // test copy-shift
    // first, make sure the trivial shift doesn't break anything, and that we ARE copying
    nX.CopyShiftLeft(nZ, 0);
    if(nX != nZ || nX.GetValue()==nZ.GetValue())
    {
        printf("0-bit left copy shift failed\n");
        goto exit;
    }
    nX.CopyShiftRight(nZ, 0);
    if(nX != nZ || nX.GetValue()==nZ.GetValue())
    {
        printf("0-bit right copy shift failed\n");
        goto exit;
    }
    // now some more substantial tests
    nX.CopyShiftLeft(nY, 12373);
    nY.CopyShiftRight(nZ, 12373);
    if(nX != nZ)
    {
        printf("copy-shift failed\n");
        nX.PrintHexToFile();
        nZ.PrintHexToFile();
        goto exit;
    }
    nX.SetFromHexString("ABCDDCBA");
    nX.CopyShiftLeft(nZ, 4);
    nX2.SetFromHexString("ABCDDCBA0");
    if (nZ != nX2)
    {
        printf("Copy shift left failed:\n");
        printf("Expected: ");
        nX2.PrintHexToFile();
        printf("Got:      ");
        nZ.PrintHexToFile();
        goto exit;
    }
    nX.SetFromHexString("AB");
    nX.CopyShiftLeft(nZ, 4);
    nX2.SetFromHexString("AB0");
    if (nZ != nX2)
    {
        printf("Copy shift left failed:\n");
        printf("Expected: ");
        nX2.PrintHexToFile();
        printf("Got:      ");
        nZ.PrintHexToFile();
        goto exit;
    }
    nX.SetFromHexString("ABCDDCBA");
    nX2.SetFromHexString("ABCDDCB");
    nX.CopyShiftRight(nZ, 4);
    if (nZ != nX2)
    {
        printf("Copy shift right failed:\n");
        printf("Expected: ");
        nX2.PrintHexToFile();
        printf("Got:      ");
        nZ.PrintHexToFile();
        goto exit;
    }
    nX.SetFromHexString("ABCDDCBA0");
    nX2.SetFromHexString("ABCDDCBA");
    nX.CopyShiftRight(nZ, 4);
    if (nZ != nX2)
    {
        printf("Copy shift right failed:\n");
        printf("Expected: ");
        nX2.PrintHexToFile();
        printf("Got:      ");
        nZ.PrintHexToFile();
        goto exit;
    }
    nX.SetFromHexString("ABCDDCBA");
    nX.ShiftLeft(4);
    nX2.SetFromHexString("ABCDDCBA0");
    if (nX != nX2)
    {
        printf("Shift left failed:\n");
        printf("Expected: ");
        nX2.PrintHexToFile();
        printf("Got:      ");
        nX.PrintHexToFile();
        goto exit;
    }
    nX.SetFromHexString("ABCDDCBA");
    nX.ShiftLeft(68);
    nX2.SetFromHexString("ABCDDCBA00000000000000000");
    if (nX != nX2)
    {
        printf("Shift left failed:\n");
        printf("Expected: ");
        nX2.PrintHexToFile();
        printf("Got:      ");
        nX.PrintHexToFile();
        goto exit;
    }
    nX.SetFromHexString("AB");
    nX.ShiftLeft(4);
    nX2.SetFromHexString("AB0");
    if (nX != nX2)
    {
        printf("Shift left failed:\n");
        printf("Expected: ");
        nX2.PrintHexToFile();
        printf("Got:      ");
        nX.PrintHexToFile();
        goto exit;
    }
    nX.SetFromHexString("ABCDDCBA");
    nX2.SetFromHexString("ABCDDCB");
    nX.ShiftRight(4);
    if (nX != nX2)
    {
        printf("Shift right failed:\n");
        printf("Expected: ");
        nX2.PrintHexToFile();
        printf("Got:      ");
        nX.PrintHexToFile();
        goto exit;
    }
    nX.SetFromHexString("ABCDDCBA0");
    nX2.SetFromHexString("ABCDDCBA");
    nX.ShiftRight(4);
    if (nX != nX2)
    {
        printf("Shift right failed:\n");
        printf("Expected: ");
        nX2.PrintHexToFile();
        printf("Got:      ");
        nX.PrintHexToFile();
        goto exit;
    }
    nX.SetFromHexString("ABCD");
    nY.SetFromHexString("ABCDE");
    // comparison operators
    // ABCD  <  ABCDE
    // ABCD  <= ABCDE
    // ABCDE >  ABCD
    // ABCDE >= ABCD
    // ABCD  != ABCDE
    // ABCDE != ABCD
    if(!(nX<nY && nX<=nY && nY>nX && nY>=nX && nX!=nY && nY!=nX))
    {
        printf("Inequalities which should hold didn't -- positive values\n");
        goto exit;
    }
    if(nY<nX || nY<=nX || nX>nY || nX>=nY)
    {
        printf("Inequalities which shouldn't hold did -- positive values\n");
        goto exit;
    }
    if(nY==nX || nX==nY)
    {
        printf("Equalities which shouldn't hold did -- positive values\n");
        goto exit;
    }
    // ABCD <  ACBD
    // ABCD <= ACBD
    // ACBD >  ABCD
    // ACBD >= ABCD
    // ABCD != ACBD
    // ACDB != ABCD
    nX.SetFromHexString("ABCD");
    nY.SetFromHexString("ACBD");
    if (!(nX < nY && nX <= nY && nY>nX && nY >= nX && nX != nY && nY != nX))
    {
        printf("Inequalities which should hold didn't -- positive values\n");
        goto exit;
    }
    if (nY < nX || nY <= nX || nX>nY || nX >= nY)
    {
        printf("Inequalities which shouldn't hold did -- positive values\n");
        goto exit;
    }
    if (nY == nX || nX == nY)
    {
        printf("Equalities which shouldn't hold did -- positive values\n");
        goto exit;
    }
    // -ABCD <  ABCD
    // -ABCD <= ABCD
    //  ABCD >  -ABCD
    //  ABCD >= -ABCD
    // -ABCD != ABCD
    //  ABCD != -ABCD
    nX.SetFromHexString("-ABCD");
    nY.SetFromHexString("ABCD");
    if (!(nX < nY && nX <= nY && nY>nX && nY >= nX && nX != nY && nY != nX))
    {
        printf("Inequalities which should hold didn't -- mixed signs\n");
        goto exit;
    }
    if (nY < nX || nY <= nX || nX>nY || nX >= nY)
    {
        printf("Inequalities which shouldn't hold did -- mixed signs\n");
        goto exit;
    }
    if (nY == nX || nX == nY)
    {
        printf("Equalities which shouldn't hold did -- mixed signs\n");
        goto exit;
    }
    // -ABCDE <  -ABCD
    // -ABCDE <= -ABCD
    //  -ABCD >  -ABCDE
    //  -ABCD >= -ABCDE
    //  -ABCD != -ABCDE
    // -ABCDE != -ABCD
    nX.SetFromHexString("-ABCDE");
    nY.SetFromHexString("-ABCD");
    if (!(nX<nY && nX <= nY && nY>nX && nY >= nX && nX != nY && nY != nX))
    {
        printf("Inequalities which should hold didn't -- negative values\n");
        goto exit;
    }
    if (nY<nX || nY <= nX || nX>nY || nX >= nY)
    {
        printf("Inequalities which shouldn't hold did -- negative values\n");
        goto exit;
    }
    if (nY == nX || nX == nY)
    {
        printf("Equalities which shouldn't hold did -- negative values\n");
        goto exit;
    }
    // -ACBD <  -ABCD
    // -ACBD <= -ABCD
    // -ABCD >  -ACBD
    // -ABCD >= -ACBD
    // -ACBD != -ABCD
    // -ABCD != -ACBD
    // -ABCDE != -ABCD
    nX.SetFromHexString("-ACBD");
    nY.SetFromHexString("-ABCD");
    if (!(nX<nY && nX <= nY && nY>nX && nY >= nX && nX != nY && nY != nX))
    {
        printf("Inequalities which should hold didn't -- negative values\n");
        goto exit;
    }
    if (nY<nX || nY <= nX || nX>nY || nX >= nY)
    {
        printf("Inequalities which shouldn't hold did -- negative values\n");
        goto exit;
    }
    if (nY == nX || nX == nY)
    {
        printf("Equalities which shouldn't hold did -- negative values\n");
        goto exit;
    }
    // ABCD == ABCD
    // ABCD <= ABCD
    // ABCD >= ABCD
    nX.SetFromHexString("ABCD");
    nY.SetFromHexString("ABCD");
    if (!(nX == nY && nX <= nY && nX >= nY))
    {
        printf("Equalities which should hold didn't -- positive signs\n");
        goto exit;
    }
    if(nX<nY || nX>nY || nX != nY)
    {
        printf("Inequalities which shouldn't hold did -- positive signs\n");
        goto exit;
    }
    // -ABCD == -ABCD
    // -ABCD <= -ABCD
    // -ABCD >= -ABCD
    nX.SetFromHexString("-ABCD");
    nY.SetFromHexString("-ABCD");
    if (!(nX == nY && nX <= nY && nX >= nY))
    {
        printf("Equalities which should hold didn't -- negative signs\n");
        goto exit;
    }
    if (nX<nY || nX>nY || nX != nY)
    {
        printf("Inequalities which shouldn't hold did -- negative signs\n");
        goto exit;
    }
    // test printing a few BIG numbers
    for(int i=0;i<100;i++)
    {
        const unsigned int c_nStringBufferSize = 25000;
        int nTimeBase, nTimeFast;
        FILE *f;
        int c,j;
        char s1[c_nStringBufferSize], s2[c_nStringBufferSize], *s;
        nX.SetRandom(2000*_DIGIT_SIZE_IN_BITS);
        errno_t err = fopen_s(&f,"foo","w+");
        if (0 != err)
        {
            printf("error opening file needed for test: 'foo'.  Aborting\n");
            goto exit;
        }
        nTimeBase = ::GetTickCount();
        nX.PrintDecimalToFile(f);
        nTimeBase = ::GetTickCount() - nTimeBase;
        fclose(f);
        err = fopen_s(&f, "foo", "r+");
        if (0 != err)
        {
            printf("error re-opening file needed for test: 'foo'.  Aborting\n");
            goto exit;
        }
        j = 0;
        do
        {
            c = getc(f);
            s1[j++] = c;
        }
        while(c != EOF);
        fclose(f);
        if (c_nStringBufferSize < PrintToBase10StringLength(nX.GetSize()) + 1)
        {
            printf("Not enough memory for output string\n");
            goto exit;
        }
        s     = s2 + PrintToBase10StringLength(nX.GetSize()) + 1; // note that print base 10 starts at the END of the memory buffer and works forward!
        s2[0] = 'x';
        nTimeFast = ::GetTickCount();
        PrintNumberToBase10(nX, s, pWork);
        nTimeFast = ::GetTickCount() - nTimeFast;
        if ('x' != s2[0])
        {
            printf("PrintNumberToBase10 wrote before buffer passed\n");
            goto exit;
        }
        // compare the values
        j = 0;
        do
        {
            if((s1[j]=='\0' || s1[j]=='\n') && (s[j]=='\0' || s[j]=='\n')) break;
            if (s1[j] != s[j])
            {
                printf("two methods of printing to base 10 disagree on iteration %i\n",i);
                printf("%s\n----------------------\n%s\n", s1, s);
                goto exit;
            }
            j++;
        }
        while(true);
        printf("Printing big integers to base 10: Base: %u ms\tFast: %u ms\n", nTimeBase, nTimeFast);
    }
    bTestWorked = true;
exit:
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestAddSubtract(bool bVerbose)
{
    CArithmeticBox     cBox;
    CBigIntegerForTest nX,nY,nSum,nDiff;
    bool               bWorked = false;
    ResetThresholdsForTest();
    // corner cases -- try one of the operands as the destination; 0 for one of the operands
    // do corner cases first!  Want to make sure memory allocation works when destination is one of the operands
    nX.SetFromHexString("FFFFFFFFFFFFFFFF");
    nSum.SetFromHexString("1FFFFFFFFFFFFFFFE");
    cBox.Add(nX, nX, nX);
    if (nX != nSum)
    {
        printf("Bad sum: expected "); nSum.PrintHexToFile();
        printf("Got:              "); nX.PrintHexToFile();
        goto exit;
    }
    nY.SetFromHexString("1");
    nDiff.SetFromHexString("-1FFFFFFFFFFFFFFFD");
    cBox.Subtract(nY, nX, nY);
    if (nY != nDiff)
    {
        printf("Bad difference: expected "); nDiff.PrintHexToFile();
        printf("Got:                     "); nY.PrintHexToFile();
        goto exit;
    }
    nX.SetFromHexString("-0");
    cBox.Add(nX, nY, nY);
    if (nY != nDiff)
    {
        printf("Bad sum of 0: expected "); nDiff.PrintHexToFile();
        printf("Got:                   "); nY.PrintHexToFile();
        goto exit;
    }
    cBox.Add(nY, nX, nX);
    if (nY != nX)
    {
        printf("Bad sum of 0: expected "); nDiff.PrintHexToFile();
        printf("Got:                   "); nX.PrintHexToFile();
        goto exit;
    }
    nX.SetFromHexString("0");
    cBox.Subtract(nY, nX, nY);
    if (nY != nDiff)
    {
        printf("Bad subtraction of 0: expected "); nDiff.PrintHexToFile();
        printf("Got:                           "); nY.PrintHexToFile();
        goto exit;
    }
    cBox.Subtract(nX, nY, nX);
    nDiff.Invert();
    if(nX != nDiff)
    {
        printf("Bad subtraction from 0.  Got"); nX.PrintHexToFile();
        printf("Expected                    "); nDiff.PrintHexToFile();
        goto exit;
    }
    // one or more of the args are 0
    nX.SetSize(0);
    nY.SetSize(0);
    nX += nY;
    if (!nX.IsZero() || nX.IsNegative())
    {
        printf("should get 0\n");
        goto exit;
    }
    nX -= nY;
    if (!nX.IsZero() || nX.IsNegative())
    {
        printf("should get 0\n");
        goto exit;
    }
    cBox.Add(nX, nY, nX);
    if (!nX.IsZero() || nX.IsNegative())
    {
        printf("should get 0\n");
        goto exit;
    }
    cBox.Subtract(nX, nY, nX);
    if (!nX.IsZero() || nX.IsNegative())
    {
        printf("should get 0\n");
        goto exit;
    }
    nY.SetFromHexString("-1");
    nX += nY;
    if (nX != nY)
    {
        printf("oops\n");
        goto exit;
    }
    nX.SetSize(0);
    cBox.Add(nX, nY, nX);
    if (nX != nY)
    {
        printf("oops\n");
        goto exit;
    }
    nDiff.SetFromHexString("1");
    nX.SetSize(0);
    nX -= nY;
    if(nX!=nDiff)
    {
        printf("oops\n");
        goto exit;
    }
    nX.SetSize(0);
    cBox.Subtract(nX, nY, nX);
    if (nX != nDiff)
    {
        printf("oops\n");
        goto exit;
    }
    nX.SetSize(0);
    nDiff = nY;
    nY += nX;
    if(nY!=nDiff)
    {
        printf("oops\n");
        goto exit;
    }
    nY -= nX;
    if (nY != nDiff)
    {
        printf("oops\n");
        goto exit;
    }
    cBox.Add(nY, nX, nY);
    if (nY != nDiff)
    {
        printf("oops\n");
        goto exit;
    }
    cBox.Subtract(nY, nX, nY);
    if (nY != nDiff)
    {
        printf("oops\n");
        goto exit;
    }
    // Try a bunch of problems to make sure we didn't miss anything
    for(int i=0; i<20000; i++)
    {
        if(i<10000)
        {
            // small values for corner cases
            nX.SetRandom(rand()%10);
            nY.SetRandom(rand()%10);
        }
        else
        {
            // large values for general case
            nX.SetRandom(rand()%1000);
            nY.SetRandom(rand()%1000);
        }
        if(0==rand()%2 && 0<nX.GetSize())
        {
            nX.SetNegative(true);
        }
        if(0==rand()%2 && 0<nY.GetSize())
        {
            nY.SetNegative(true);
        }
        if(eOperationSucceeded != cBox.Add(nX,nY,nSum))
        {
            printf("Add failed\n");
            break;
        }
        if(eOperationSucceeded != cBox.Subtract(nSum,nX,nDiff))
        {
            printf("Subtract failed\n");
            break;
        }
        if(bVerbose || nDiff!=nY)
        {
            printf("X:     ");
            nX.PrintHexToFile();
            printf("\nY:     ");
            nY.PrintHexToFile();
            printf("\nX+Y:   ");
            nSum.PrintHexToFile();
            printf("\nX+Y-X: ");
            nDiff.PrintHexToFile();
            printf("\n\n");
            bWorked = (nDiff==nY);
            if(!bWorked)
            {
                goto exit;
            }
        }
        // repeat, using += and -=
        nSum = nX;
        nX += nY;
        if(!nY.IsZero() && nX==nSum)
        {
            printf("Whoops -- expected a sum\n");
            goto exit;
        }
        nX -= nY;
        if(nX!=nSum)
        {
            printf("Whoops -- expected x+y-y == x\n");
            goto exit;
        }
    }
    bWorked = true;
exit:
    return bWorked;
}

bool CArithmeticCorrectnessTester::TestShortLongMultiply(bool bVerbose)
{
    CBigIntegerForTest nX, nY, nValidatedProduct, nTestProduct, nAdd;
    CArithmeticBox cBox;
    size_t         nProductSize;
    bool           bTestWorked = false;
    ResetThresholdsForTest();
    for(size_t i=1;i<13;i++)
    {
        nX.Reserve(i);
        for(size_t j=1;j<=200;j+=i)
        {
            nY.Reserve(j);
            nAdd.Reserve(i+j+1);
            nValidatedProduct.Reserve(i+j+1);
            nTestProduct.Reserve(i+j+1);
            for(size_t k=0;k<3;k++)
            {
                if(0==k)
                {
                    // Test multiplication of FFFF... -- maximum size operands, to make
                    // sure assumptions about overflow are met
                    for(size_t m=0;m<i;m++)
                    {
                        nX.GetValue()[m] = (DIGIT) -1;
                    }
                    for(size_t m=0;m<j;m++)
                    {
                        nY.GetValue()[m] = (DIGIT) -1;
                    }
                    nX.SetSize(i);
                    nY.SetSize(j);
                }
                else if(1==k)
                {
                    // Test with the larger operand having lots of internal 0s
                    nX.SetRandom(i*_DIGIT_SIZE_IN_BITS);
                    for(size_t m=0;m<j-1;m++)
                    {
                        nY.GetValue()[m] = 0;
                    }
                    nY.GetValue()[j-1] = 1;
                    nY.SetSize(j);
                }
                else
                {
                    // test more general multiplication
                    nX.SetRandom(i*_DIGIT_SIZE_IN_BITS);
                    nY.SetRandom(j*_DIGIT_SIZE_IN_BITS);
                }
                size_t nXSize = nX.GetSize();
                size_t nYSize = nY.GetSize();
                if(0<nX.GetSize() && 0<nY.GetSize())
                {
                    nValidatedProduct.SetSize(CUnsignedArithmeticHelper::MultOracle(nXSize,
                                                                                     nYSize,
                                                                                     nX.GetValue(),
                                                                                     nY.GetValue(),
                                                                                     nValidatedProduct.GetValue()));
                    if(nX.GetSize() <= nY.GetSize())
                    {
                        CUnsignedArithmeticHelper::MultUShortLong(nXSize,
                                                                  nYSize,
                                                                  nX.GetValue(),
                                                                  nY.GetValue(),
                                                                  nTestProduct.GetValue());
                    }
                    else
                    {
                        CUnsignedArithmeticHelper::MultUShortLong(nYSize,
                                                                  nXSize,
                                                                  nY.GetValue(),
                                                                  nX.GetValue(),
                                                                  nTestProduct.GetValue());
                    }
                    nProductSize = nXSize+nYSize;
                    if(0==nTestProduct.GetValue()[nProductSize-1])
                    {
                        nProductSize--;
                    }
                    nTestProduct.SetSize(nProductSize);
                    if(nTestProduct != nValidatedProduct || bVerbose)
                    {
                        printf("Multiply operands:\n");
                        nX.PrintHexToFile();
                        printf("\n");
                        nY.PrintHexToFile();
                        printf("\n");
                        printf("Expected product:\n");
                        nValidatedProduct.PrintHexToFile();
                        printf("\nComputed product:\n");
                        nTestProduct.PrintHexToFile();
                        printf("\n");
                        if(nTestProduct != nValidatedProduct)
                        {
                            printf("Multiply test failed: basic short/long\n");
                            goto exit;
                        }
                    }
                }
                // Then, MultAddUShortLong
                if(k==0)
                {
                    // Test multiplication of FFFF... -- maximum size operands, to make
                    // sure assumptions about overflow are met
                    for(size_t m=0;m<i;m++)
                    {
                        nX.GetValue()[m] = (DIGIT) -1;
                    }
                    for(size_t m=0;m<j;m++)
                    {
                        nY.GetValue()[m] = (DIGIT) -1;
                    }
                    for(size_t m=0;m<i+j;m++)
                    {
                        nAdd.GetValue()[m] = (DIGIT) -1;
                    }
                    nX.SetSize(i);
                    nY.SetSize(j);
                    nAdd.SetSize(i+j);
                }
                else
                {
                    // test more general multiplication
                    nX.SetRandom(i*_DIGIT_SIZE_IN_BITS);
                    nY.SetRandom(j*_DIGIT_SIZE_IN_BITS);
                    nAdd.SetRandom((i+j)*_DIGIT_SIZE_IN_BITS);
                }
                nXSize = nX.GetSize();
                nYSize = nY.GetSize();
                if(0==j%3)
                {
                    // prune back the size of Z for some variation
                    nAdd.SetSize(1+(rand()%(i+j)));
                }
                if(0<nX.GetSize() && 0<nY.GetSize())
                {
                    // initialize Z to format expected by MultUBasic
                    nTestProduct.Reserve(nXSize+nYSize+nTestProduct.GetSize(),true);
                    nTestProduct = nAdd;
                    // make sure pTestProduct has leading 0s
                    for(size_t m=nTestProduct.GetSize();m<i+j+1;m++)
                    {
                        nTestProduct.GetValue()[m] = 0;
                    }
                    // perform x*y+z -- where "z" is the previous iteration's result
                    nValidatedProduct.SetSize(CUnsignedArithmeticHelper::MultOracle(nXSize,
                                                                                    nYSize,
                                                                                    nX.GetValue(),
                                                                                    nY.GetValue(),
                                                                                    nValidatedProduct.GetValue()));
                    cBox.Add(nValidatedProduct,nAdd,nValidatedProduct);
                    nProductSize = nXSize+nYSize;
                    if(nProductSize <= nTestProduct.GetSize())
                    {
                        nProductSize = nTestProduct.GetSize();
                    }
                    nProductSize++;
                    if(nX.GetSize() <= nY.GetSize())
                    {
                        CUnsignedArithmeticHelper::MultAddUShortLong(nXSize,
                                                                     nYSize,
                                                                     nX.GetValue(),
                                                                     nY.GetValue(),
                                                                     nTestProduct.GetValue());
                    }
                    else
                    {
                        CUnsignedArithmeticHelper::MultAddUShortLong(nYSize,
                                                                     nXSize,
                                                                     nY.GetValue(),
                                                                     nX.GetValue(),
                                                                     nTestProduct.GetValue());
                    }
                    if(0==nTestProduct.GetValue()[nProductSize-1])
                    {
                        nProductSize--;
                        if(0==nTestProduct.GetValue()[nProductSize-1])
                        {
                            nProductSize--;
                        }
                    }
                    nTestProduct.SetSize(nProductSize);
                    if(nTestProduct != nValidatedProduct || bVerbose)
                    {
                        printf("z = x*y+z:  x, y, z:\n");
                        printf("x: ");  nX.PrintHexToFile();
                        printf("y: ");  nY.PrintHexToFile();
                        printf("z: ");  nAdd.PrintHexToFile();
                        printf("Expected result:\n");
                        nValidatedProduct.PrintHexToFile();
                        printf("\nComputed result:\n");
                        nTestProduct.PrintHexToFile();
                        printf("\n");
                        if(nTestProduct != nValidatedProduct)
                        {
                            printf("Multiply test failed: basic short/long add\n");
                            goto exit;
                        }
                    }
                }
            }
        }
    }
    bTestWorked = true;
exit:
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestStripedMultiply(bool bVerbose)
{
    CBigIntegerForTest nX, nY, nValidatedProduct, nTestProduct, nAdd;
    CArithmeticBox cBox;
    size_t         nProductSize;
    bool           bTestWorked = false;
    ResetThresholdsForTest();
    for(size_t i=1;i<13;i++)
    {
        nX.Reserve(i);
        for(size_t j=1;j<=200;j+=i)
        {
            nY.Reserve(j);
            nAdd.Reserve(i+j+1);
            nValidatedProduct.Reserve(i+j+1);
            nTestProduct.Reserve(i+j+1);
            for(size_t k=0;k<3;k++)
            {
                if(0==k)
                {
                    // Test multiplication of FFFF... -- maximum size operands, to make
                    // sure assumptions about overflow are met
                    for(size_t m=0;m<i;m++)
                    {
                        nX.GetValue()[m] = (DIGIT) -1;
                    }
                    for(size_t m=0;m<j;m++)
                    {
                        nY.GetValue()[m] = (DIGIT) -1;
                    }
                    nX.SetSize(i);
                    nY.SetSize(j);
                }
                else if(1==k)
                {
                    // Test with the larger operand having lots of internal 0s
                    nX.SetRandom(i*_DIGIT_SIZE_IN_BITS);
                    for(size_t m=0;m<j-1;m++)
                    {
                        nY.GetValue()[m] = 0;
                    }
                    nY.GetValue()[j-1] = 1;
                    nY.SetSize(j);
                }
                else
                {
                    // test more general multiplication
                    nX.SetRandom(i*_DIGIT_SIZE_IN_BITS);
                    nY.SetRandom(j*_DIGIT_SIZE_IN_BITS);
                }
                size_t nXSize = nX.GetSize();
                size_t nYSize = nY.GetSize();
                if(0<nX.GetSize() && 0<nY.GetSize())
                {
                    nValidatedProduct.SetSize(CUnsignedArithmeticHelper::MultOracle(nXSize,
                                                                                     nYSize,
                                                                                     nX.GetValue(),
                                                                                     nY.GetValue(),
                                                                                     nValidatedProduct.GetValue()));
                    if(nX.GetSize() <= nY.GetSize())
                    {
                        CUnsignedArithmeticHelper::MultUStriped(nXSize,
                                                                nYSize,
                                                                nX.GetValue(),
                                                                nY.GetValue(),
                                                                nTestProduct.GetValue(),
                                                                false);
                    }
                    else
                    {
                        CUnsignedArithmeticHelper::MultUStriped(nYSize,
                                                                nXSize,
                                                                nY.GetValue(),
                                                                nX.GetValue(),
                                                                nTestProduct.GetValue(),
                                                                false);
                    }
                    nProductSize = nXSize+nYSize;
                    if(0==nTestProduct.GetValue()[nProductSize-1])
                    {
                        nProductSize--;
                    }
                    nTestProduct.SetSize(nProductSize);
                    if(nTestProduct != nValidatedProduct || bVerbose)
                    {
                        printf("Multiply operands:\n");
                        nX.PrintHexToFile();
                        printf("\n");
                        nY.PrintHexToFile();
                        printf("\n");
                        printf("Expected product:\n");
                        nValidatedProduct.PrintHexToFile();
                        printf("\nComputed product:\n");
                        nTestProduct.PrintHexToFile();
                        printf("\n");
                        if(nTestProduct != nValidatedProduct)
                        {
                            printf("Multiply test failed: striped\n");
                            goto exit;
                        }
                    }
                }
                // Then, MultAddUShortLong
                if(k==0)
                {
                    // Test multiplication of FFFF... -- maximum size operands, to make
                    // sure assumptions about overflow are met
                    for(size_t m=0;m<i;m++)
                    {
                        nX.GetValue()[m] = (DIGIT) -1;
                    }
                    for(size_t m=0;m<j;m++)
                    {
                        nY.GetValue()[m] = (DIGIT) -1;
                    }
                    for(size_t m=0;m<i+j;m++)
                    {
                        nAdd.GetValue()[m] = (DIGIT) -1;
                    }
                    nX.SetSize(i);
                    nY.SetSize(j);
                    nAdd.SetSize(i+j);
                }
                else
                {
                    // test more general multiplication
                    nX.SetRandom(i*_DIGIT_SIZE_IN_BITS);
                    nY.SetRandom(j*_DIGIT_SIZE_IN_BITS);
                    nAdd.SetRandom((i+j)*_DIGIT_SIZE_IN_BITS);
                }
                nXSize = nX.GetSize();
                nYSize = nY.GetSize();
                if(0==j%3)
                {
                    // prune back the size of Z for some variation
                    nAdd.SetSize(1+(rand()%(i+j)));
                }
                if(0<nX.GetSize() && 0<nY.GetSize())
                {
                    // initialize Z to format expected by MultUBasic
                    nTestProduct.Reserve(nXSize+nYSize+nTestProduct.GetSize(),true);
                    nTestProduct = nAdd;
                    // make sure pTestProduct has leading 0s
                    for(size_t m=nTestProduct.GetSize();m<i+j+1;m++)
                    {
                        nTestProduct.GetValue()[m] = 0;
                    }
                    // perform x*y+z -- where "z" is the previous iteration's result
                    nValidatedProduct.SetSize(CUnsignedArithmeticHelper::MultOracle(nXSize,
                                                                                    nYSize,
                                                                                    nX.GetValue(),
                                                                                    nY.GetValue(),
                                                                                    nValidatedProduct.GetValue()));
                    cBox.Add(nValidatedProduct,nAdd,nValidatedProduct);
                    nProductSize = nXSize+nYSize;
                    if(nProductSize <= nTestProduct.GetSize())
                    {
                        nProductSize = nTestProduct.GetSize();
                    }
                    nProductSize++;
                    if(nX.GetSize() <= nY.GetSize())
                    {
                        CUnsignedArithmeticHelper::MultUStriped(nXSize,
                                                                nYSize,
                                                                nX.GetValue(),
                                                                nY.GetValue(),
                                                                nTestProduct.GetValue(),
                                                                true);
                    }
                    else
                    {
                        CUnsignedArithmeticHelper::MultUStriped(nYSize,
                                                                nXSize,
                                                                nY.GetValue(),
                                                                nX.GetValue(),
                                                                nTestProduct.GetValue(),
                                                                true);
                    }
                    if(0==nTestProduct.GetValue()[nProductSize-1])
                    {
                        nProductSize--;
                        if(0==nTestProduct.GetValue()[nProductSize-1])
                        {
                            nProductSize--;
                        }
                    }
                    nTestProduct.SetSize(nProductSize);
                    if(nTestProduct != nValidatedProduct || bVerbose)
                    {
                        printf("z = x*y+z:  x, y, z:\n");
                        printf("x: ");  nX.PrintHexToFile();
                        printf("y: ");  nY.PrintHexToFile();
                        printf("z: ");  nAdd.PrintHexToFile();
                        printf("Expected result:\n");
                        nValidatedProduct.PrintHexToFile();
                        printf("\nComputed result:\n");
                        nTestProduct.PrintHexToFile();
                        printf("\n");
                        if(nTestProduct != nValidatedProduct)
                        {
                            printf("Multiply test failed: striped add\n");
                            goto exit;
                        }
                    }
                }
            }
        }
    }
    bTestWorked = true;
exit:
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestBasicMultiply(bool bVerbose)
{
    CBigIntegerForTest nX, nY, nValidatedProduct, nTestProduct, nAdd;
    CArithmeticBox     cBox;
    size_t             nProductSize;
    bool               bTestWorked = false;
    ResetThresholdsForTest();
    for(size_t i=20;i<200;i++)
    {
        nX.Reserve(i);
        for(size_t j=20;j<200;j++)
        {
            nY.Reserve(j);
            nAdd.Reserve(i+j+1);
            nValidatedProduct.Reserve(i+j+2);
            nTestProduct.Reserve(i+j+2);
            for(int kk=1;kk<=6;kk++)
            {
                for(size_t k=0;k<4;k++)
                {
                    if(0==(k&1))
                    {
                        // Test multiplication of FFFF... -- maximum size operands, to make
                        // sure assumptions about overflow are met
                        for(size_t m=0;m<i;m++)
                        {
                            nX.GetValue()[m] = (DIGIT) -1;
                        }
                        for(size_t m=0;m<j;m++)
                        {
                            nY.GetValue()[m] = (DIGIT) -1;
                        }
                        for(size_t m=0;m<i+j;m++)
                        {
                            nAdd.GetValue()[m] = (DIGIT) -1;
                        }
                        nX.SetSize(i);
                        nY.SetSize(j);
                        nAdd.SetSize(i+j);
                    }
                    else if(1==k)
                    {
                        // sparse vs random
                        for(size_t n=0; n<i; n++)
                        {
                            nX.GetValue()[n] = (DIGIT)(n & 1);
                        }
                        if (0 == nX.GetValue()[i - 1]) nX.SetSize(i - 1);
                        else                           nX.SetSize(i);
                        nY.SetRandom(j*_DIGIT_SIZE_IN_BITS);
                    }
                    else
                    {
                        // test more general multiplication
                        nX.SetRandom(i*_DIGIT_SIZE_IN_BITS);
                        nY.SetRandom(j*_DIGIT_SIZE_IN_BITS);
                        nAdd.SetRandom((i+j)*_DIGIT_SIZE_IN_BITS);
                    }
                    if(0==j%3)
                    {
                        // prune back the size of Z for some variation
                        nAdd.SetSize(1+(rand()%(i+j)));
                    }
                    size_t nXSize = nX.GetSize();
                    size_t nYSize = nY.GetSize();
                    if(0<nX.GetSize() && 0<nY.GetSize())
                    {
                        nValidatedProduct.SetSize(CUnsignedArithmeticHelper::MultOracle(nXSize,
                                                                                        nYSize,
                                                                                        nX.GetValue(),
                                                                                        nY.GetValue(),
                                                                                        nValidatedProduct.GetValue()));
                        if(0 != (k&2))
                        {
                            // even iterations: mult-add
                            cBox.Add(nValidatedProduct,nAdd,nValidatedProduct);
                        }
                        size_t nSmallSize, nLargeSize;
                        DIGIT  *pnSmaller, *pnLarger;
                        if(nX<nY)
                        {
                            // X is smaller
                            pnSmaller  = nX.GetValue();
                            nSmallSize = nX.GetSize();
                            pnLarger   = nY.GetValue();
                            nLargeSize = nY.GetSize();
                        }
                        else
                        {
                            // Y is smaller (or they are the same size)
                            pnSmaller  = nY.GetValue();
                            nSmallSize = nY.GetSize();
                            pnLarger   = nX.GetValue();
                            nLargeSize = nX.GetSize();
                        }
                        if(0 != (k&2))
                        {
                            // even iterations: mult-add; odd: simple mult
                            nTestProduct = nAdd;
                            // make sure pTestProduct has leading 0s
                            for(size_t m=nTestProduct.GetSize();m<i+j+2;m++)
                            {
                                nTestProduct.GetValue()[m] = 0;
                            }
                        }
                        else
                        {
                            // even iterations: mult-add; even: simple mult
                            // make sure pTestProduct has leading 0s
                            for(size_t m=nSmallSize+nLargeSize;m<i+j+1;m++)
                            {
                                nTestProduct.GetValue()[m] = 0;
                            }
                        }
                        switch(kk)
                        {
                        case 1:
                            {
                                BasicMultiplyReg1(nSmallSize,
                                                  nLargeSize,
                                                  pnSmaller,
                                                  pnLarger,
                                                  nTestProduct.GetValue(),
                                                  (0 != (k&2))); // even iterations: mult-add; odd: simple mult
                                break;
                            }
                        case 2:
                            {
                                BasicMultiplyReg2(nSmallSize,
                                                  nLargeSize,
                                                  pnSmaller,
                                                  pnLarger,
                                                  nTestProduct.GetValue(),
                                                  (0 != (k&2))); // even iterations: mult-add; odd: simple mult
                                break;
                            }
                        case 3:
                            {
                                BasicMultiplyReg3(nSmallSize,
                                                  nLargeSize,
                                                  pnSmaller,
                                                  pnLarger,
                                                  nTestProduct.GetValue(),
                                                  (0 != (k&2))); // even iterations: mult-add; odd: simple mult
                                break;
                            }
                        case 4:
                            {
                                BasicMultiplyReg4(nSmallSize,
                                                  nLargeSize,
                                                  pnSmaller,
                                                  pnLarger,
                                                  nTestProduct.GetValue(),
                                                  (0 != (k&2))); // even iterations: mult-add; odd: simple mult
                                break;
                            }
                        case 5:
                            {
                                BasicMultiplyReg5(nSmallSize,
                                                  nLargeSize,
                                                  pnSmaller,
                                                  pnLarger,
                                                  nTestProduct.GetValue(),
                                                  (0 != (k&2))); // even iterations: mult-add; odd: simple mult
                                break;
                            }
                        case 6:
                            {
                                BasicMultiplyReg6(nSmallSize,
                                                  nLargeSize,
                                                  pnSmaller,
                                                  pnLarger,
                                                  nTestProduct.GetValue(),
                                                  (0 != (k&2))); // even iterations: mult-add; odd: simple mult
                                break;
                            }
                        default:
                            printf("Oops...\n");
                            goto exit;
                        }
                        nProductSize = nXSize+nYSize+1;
                        if(0==nTestProduct.GetValue()[nProductSize-1])
                        {
                            nProductSize--;
                            if(0==nTestProduct.GetValue()[nProductSize-1])
                            {
                                nProductSize--;
                            }
                        }
                        nTestProduct.SetSize(nProductSize);
                        if(nTestProduct != nValidatedProduct || bVerbose)
                        {
                            printf("Multiply operands:\n");
                            nX.PrintHexToFile();
                            printf("\n");
                            nY.PrintHexToFile();
                            printf("\n");
                            printf("Expected product:\n");
                            nValidatedProduct.PrintHexToFile();
                            printf("\nComputed product:\n");
                            nTestProduct.PrintHexToFile();
                            printf("\n");
                            if(nTestProduct != nValidatedProduct)
                            {
                                printf("Multiply test failed: basic algorithm, reg block size %i\n",kk);
                                goto exit;
                            }
                        }
                        // striped multiply: reset test product
                        // even iterations: mult-add; even: simple mult
                        if(0 != (k&2))
                        {
                            nTestProduct = nAdd;
                            // make sure pTestProduct has leading 0s
                            for(size_t m=nTestProduct.GetSize();m<i+j+2;m++)
                            {
                                nTestProduct.GetValue()[m] = 0;
                            }
                        }
                        else
                        {
                            // make sure pTestProduct has leading 0s
                            for(size_t m=nSmallSize+nLargeSize;m<i+j+1;m++)
                            {
                                nTestProduct.GetValue()[m] = 0;
                            }
                        }
                        MultUStriped(nSmallSize, nLargeSize, pnSmaller, pnLarger, nTestProduct.GetValue(), (0 != (k&2)));
                        nProductSize = nXSize+nYSize+1;
                        if(0==nTestProduct.GetValue()[nProductSize-1])
                        {
                            nProductSize--;
                            if(0==nTestProduct.GetValue()[nProductSize-1])
                            {
                                nProductSize--;
                            }
                        }
                        nTestProduct.SetSize(nProductSize);
                        if(nTestProduct != nValidatedProduct || bVerbose)
                        {
                            printf("Multiply operands:\n");
                            nX.PrintHexToFile();
                            printf("\n");
                            nY.PrintHexToFile();
                            printf("\n");
                            printf("Expected product:\n");
                            nValidatedProduct.PrintHexToFile();
                            printf("\nComputed product:\n");
                            nTestProduct.PrintHexToFile();
                            printf("\n");
                            if(nTestProduct != nValidatedProduct)
                            {
                                printf("Multiply test failed: striped algorithm\n");
                                goto exit;
                            }
                        }
                    }
                }
            }
        }
    }
    bTestWorked = true;
exit:
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestRecursiveMultiply(bool bVerbose)
{
    CArithmeticBox        cBox;
    size_t                nProductSize;
    CBigIntegerForTest    nX, nY, nValidatedProduct, nTestProduct, nAdd;
    const int             c_nMaxSize   = 300;
    bool                  bTestWorked  = false;
    DIGIT                 *pnWorkspace = (DIGIT *) malloc(sizeof(DIGIT)*200000); // plenty for this test, I hope
    ResetThresholdsForTest();
    nX.Reserve(c_nMaxSize);
    nY.Reserve(c_nMaxSize);
    c_pnMultiplicationThresholds[e2NByN] = c_nMaxSize + 1;
    // Test the larger multiplication algorithms against the oracle
    for(int nAlgorithm=1;nAlgorithm<e2NByN;nAlgorithm++)
    {
        for(size_t i=20;i<=c_nMaxSize;i++)
        {
            printf("algorithm %s: %i x (%i to %i)\n", GetMultiplicationAlgorithmName((EMultiplyAlgorithm) nAlgorithm), i, i, c_nMaxSize);
            for(size_t j=20;j<=c_nMaxSize;j++)
            {
                for(size_t k=0;k<5;k++)
                {
                    switch(k)
                    {
                    case 0:
                        // random values
                        nX.SetRandom(i*_DIGIT_SIZE_IN_BITS);
                        nY.SetRandom(j*_DIGIT_SIZE_IN_BITS);
                        break;
                    case 1:
                        // max values
                        for(size_t n=0;n<i;n++)
                        {
                            nX.GetValue()[n] = (DIGIT) -1;
                        }
                        for(size_t n=0;n<j;n++)
                        {
                            nY.GetValue()[n] = (DIGIT) -1;
                        }
                        nX.SetSize(i);
                        nY.SetSize(j);
                        break;
                    case 2:
                        // min values
                        for(size_t n=0;n<i-1;n++)
                        {
                            nX.GetValue()[n] = 0;
                        }
                        nX.GetValue()[i-1] = 1;
                        for(size_t n=0;n<j-1;n++)
                        {
                            nY.GetValue()[n] = 0;
                        }
                        nY.GetValue()[j-1] = 1;
                        nX.SetSize(i);
                        nY.SetSize(j);
                        break;
                    case 3:
                        // mixed values
                        for(size_t n=0;n<i;n++)
                        {
                            nX.GetValue()[n] = (DIGIT) -1;
                        }
                        for(size_t n=0;n<j-1;n++)
                        {
                            nY.GetValue()[n] = 0;
                        }
                        nY.GetValue()[j-1] = 1;
                        nX.SetSize(i);
                        nY.SetSize(j);
                        break;
                    case 4:
                        // sparse vs random
                        for(size_t n=0; n<i; n++)
                        {
                            nX.GetValue()[n] = (DIGIT) (n&1);
                        }
                        if (0 == nX.GetValue()[i - 1]) nX.SetSize(i - 1);
                        else                            nX.SetSize(i);
                        nY.SetRandom(j*_DIGIT_SIZE_IN_BITS);
                    }
                    size_t nXSize = nX.GetSize();
                    size_t nYSize = nY.GetSize();
                    if(0<nX.GetSize() && 0<nY.GetSize())
                    {
                        nValidatedProduct.Reserve(nXSize+nYSize);
                        nTestProduct.Reserve(nXSize+nYSize+1);
                        nTestProduct.GetValue()[nXSize + nYSize] = TEST_BUFFERGUARD;
                        nValidatedProduct.SetSize(CUnsignedArithmeticHelper::MultOracle(nXSize,
                                                                                        nYSize,
                                                                                        nX.GetValue(),
                                                                                        nY.GetValue(),
                                                                                        nValidatedProduct.GetValue()));
                        size_t nSmallSize, nLargeSize;
                        DIGIT  *pnSmaller, *pnLarger;
                        if(nX<nY)
                        {
                            // X is smaller
                            pnSmaller  = nX.GetValue();
                            nSmallSize = nX.GetSize();
                            pnLarger   = nY.GetValue();
                            nLargeSize = nY.GetSize();
                        }
                        else
                        {
                            // Y is smaller (or they are the same size)
                            pnSmaller  = nY.GetValue();
                            nSmallSize = nY.GetSize();
                            pnLarger   = nX.GetValue();
                            nLargeSize = nX.GetSize();
                        }
                        c_pnMultiplicationThresholds[eBasicMultiply] = nSmallSize;
                        for(int ii=0; ii<nAlgorithm; ii++) c_pnMultiplicationThresholds[ii] = nSmallSize;
                        c_pnMultiplicationThresholds[nAlgorithm] = nLargeSize+1;
                        int nMemoryNeeded = MultiplyMemoryNeeds(nXSize, nYSize);
                        pnWorkspace[nMemoryNeeded] = TEST_BUFFERGUARD;
                        Multiply(nXSize, nYSize, nX.GetValue(), nY.GetValue(), nTestProduct.GetValue(), pnWorkspace);
                        if(TEST_BUFFERGUARD != pnWorkspace[nMemoryNeeded])
                        {
                            printf("Overflowed supposed workspace memory needs for %s, size %ix%i type %i\n",
                                   GetMultiplicationAlgorithmName((EMultiplyAlgorithm) nAlgorithm),
                                   nXSize,
                                   nYSize,
                                   k);
                            goto exit;
                        }
                        if(nTestProduct.GetValue()[nXSize + nYSize] != TEST_BUFFERGUARD)
                        {
                            printf("Overflowed product for %s, size %ix%i type %i\n",
                                   GetMultiplicationAlgorithmName((EMultiplyAlgorithm) nAlgorithm),
                                   nXSize,
                                   nYSize,
                                   k);
                            goto exit;
                        }
                        nProductSize = nXSize+nYSize;
                        if(0==nTestProduct.GetValue()[nProductSize-1])
                        {
                            nProductSize--;
                        }
                        nTestProduct.SetSize(nProductSize);
                        if(nTestProduct != nValidatedProduct || bVerbose)
                        {
                            printf("Multiply operands:\n");
                            nX.PrintHexToFile();
                            printf("\n");
                            nY.PrintHexToFile();
                            printf("\n");
                            printf("Expected product:\n");
                            nValidatedProduct.PrintHexToFile();
                            printf("\nComputed product:\n");
                            nTestProduct.PrintHexToFile();
                            printf("\n");
                            if(nTestProduct != nValidatedProduct)
                            {
                                printf("Multiply test failed: multiplication %s, size %ix%i type %i\n",
                                       GetMultiplicationAlgorithmName((EMultiplyAlgorithm) nAlgorithm),
                                       nXSize,
                                       nYSize,
                                       k);
                                goto exit;
                            }
                        }
                    }
                }
            }
        }
    }
    bTestWorked = true;
exit:
    free(pnWorkspace);
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestMultiplyAdd(bool bVerbose)
{
    CArithmeticBox        cBox;
    size_t                nProductSize;
    CBigIntegerForTest    nX, nY, nZ, nValidatedProduct, nTestProduct, nAdd;
    bool                  bTestWorked        = false;
    DIGIT                 *pnWorkspace       = (DIGIT *) malloc(sizeof(DIGIT)*200000); // plenty for this test, I hope
    ResetThresholdsForTest();
    bTestWorked = true;
    for(size_t i=5;i<100;i++)
    {
        printf("X size: %u\n", i);
        for(size_t j=5;j<100;j++)
        {
            for(size_t k=5;k<100;k++)
            {
                for(int nZPos=0; nZPos<2; nZPos++)
                {
                    nX.SetRandom(i*_DIGIT_SIZE_IN_BITS,::GetTickCount());
                    nY.SetRandom(j*_DIGIT_SIZE_IN_BITS);
                    if(k&1)
                    {
                        nZ.SetRandom(k*_DIGIT_SIZE_IN_BITS);
                    }
                    else
                    {
                        nZ.Reserve(k);
                        nZ.SetSize(k);
                        for(int m=0;m<k;m++) nZ.GetValue()[m] = (DIGIT) -1;
                    }
                    nZ.SetNegative(nZPos);
                    nTestProduct = nZ;
                    cBox.MultiplyAdd(nX, nY, nTestProduct);
                    cBox.Multiply(nX, nY, nValidatedProduct);
                    cBox.Add(nValidatedProduct, nZ, nAdd);
                    if(nAdd != nTestProduct)
                    {
                        printf("failed at %i, %i, %i\t%i: %i,%i\n",i,j,k,nZPos,nAdd.GetSize(),nTestProduct.GetSize());
                        for(int m=0;m< nAdd.GetSize();m++)
                        {
                            if(nAdd.GetValue()[m] != nTestProduct.GetValue()[m])  printf("  %i\t%i %i\n", m, nAdd.GetValue()[m], nTestProduct.GetValue()[m]);
                        }
                        bTestWorked = false;
                        goto exit;
                    }
                }
            }
        }
    }
exit:
    free(pnWorkspace);
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestDivide(bool bVerbose)
{
    ResetThresholdsForTest();
    CBigIntegerForTest nX, nY, nYCopy, nZ, nProduct, nDiv, nRemainder;
    CArithmeticBox     cBox;
    size_t             nModSize,nDivSize,nMemoryNeeds;
    bool               bFailed       = false;
    bool               bTestWorked   = false;
    const size_t       c_nMaxSize    = 300;
    DIGIT              *pWorkspace   = new DIGIT[20000]; // enough for THIS test
    nX.Reserve(2*c_nMaxSize);
    nY.Reserve(2*c_nMaxSize);
    nZ.Reserve(2*c_nMaxSize);
    nDiv.Reserve(2*c_nMaxSize+1);
    nRemainder.Reserve(2*c_nMaxSize+1);
    nProduct.Reserve(2*c_nMaxSize+1);
    for(size_t i=2;i<c_nMaxSize;i++)
    {
        printf("%i digit divisor (up to %i) in to number of size %i to %i, inclusive\n", i, c_nMaxSize, i-1, c_nMaxSize);
        for(size_t j=i-1;j<2*c_nMaxSize;j++)
        {
            for(int k=0;k<5;k++)
            {
                nX.SetRandom(j*_DIGIT_SIZE_IN_BITS);
                nZ.SetRandom(i*_DIGIT_SIZE_IN_BITS);
                switch(k)
                {
                case 0:
                    // random divisor
                    do
                    {
                        nY.SetRandom(i*_DIGIT_SIZE_IN_BITS);
                    }
                    while(nY.IsZero());
                    break;
                case 1:
                    // one maximal divisor
                    for(size_t n=0;n<i;n++)
                    {
                        nY.GetValue()[n] = (DIGIT) -1;
                    }
                    nY.SetSize(i);
                    break;
                case 2:
                    // sparse divisor
                    for(size_t n=0;n<i;n++)
                    {
                        nY.GetValue()[n] = (1+n)&1;
                    }
                    nY.SetSize(0==nY.GetValue()[i-1] ? i-1 : i);
                    break;
                case 3:
                    // sparse divisor, sparse base
                    for(size_t n=0;n<j;n++)
                    {
                        nX.GetValue()[n] = (1+n)&1;
                    }
                    nX.SetSize(0==nX.GetValue()[j-1] ? j-1 : j);
                    for(size_t n=0;n<i;n++)
                    {
                        nY.GetValue()[n] = (1+n)&1;
                    }
                    nY.SetSize(0==nY.GetValue()[i-1] ? i-1 : i);
                    break;
                default:
                    // random divisor, sparse base
                    for(size_t n=0;n<j;n++)
                    {
                        nX.GetValue()[n] = (1+n)&1;
                    }
                    nX.SetSize(0==nX.GetValue()[j-1] ? j-1 : j);
                    nY.SetRandom(i*_DIGIT_SIZE_IN_BITS);
                    break;
                }
                if(nY <= nZ)
                {
                    nZ = nY;
                    nZ -= 1; // make SURE Z<Y
                }
                cBox.Multiply(nX,nY,nProduct);
                // first, test where the division should be exact -- no remainder
                nRemainder = nProduct;
                // basic division
                c_nDivideThresholdSmall  = nY.GetSize()+1;
                nMemoryNeeds             = DivisionMemoryNeeds(nRemainder.GetSize(), nY.GetSize());
                pWorkspace[nMemoryNeeds] = TEST_BUFFERGUARD;
                Divide(nRemainder.GetSize(),
                       nY.GetSize(),
                       nDivSize,
                       nModSize,
                       nRemainder.GetValue(),
                       nY.GetValue(),
                       nDiv.GetValue(),
                       pWorkspace);
                if(TEST_BUFFERGUARD != pWorkspace[nMemoryNeeds])
                {
                    printf("Overan workspace memory\n");
                    goto exit;
                }
                nRemainder.SetSize(nModSize);
                nDiv.SetSize(nDivSize);
                bFailed = (nDiv != nX || 0!=nModSize);
                // note the bufferguard checks do nothing in retail
                nRemainder.CheckBufferguard();
                nY.CheckBufferguard();
                nProduct.CheckBufferguard();
                nDiv.CheckBufferguard();
                nZ.CheckBufferguard();
                nX.CheckBufferguard();
                if(bFailed || bVerbose)
                {
                    printf("Basic division:\n");
                    printf("x*y = prod:\n");
                    printf("x:          ");
                    nX.PrintHexToFile();
                    printf("y:          ");
                    nY.PrintHexToFile();
                    printf("Prod:       ");
                    nProduct.PrintHexToFile();
                    printf("Prod/y:     ");
                    nDiv.PrintHexToFile();
                    printf("Prod mod y: ");
                    nRemainder.PrintHexToFile();
                    printf("\n");
                    if(bFailed)
                    {
                        goto exit;
                    }
                }
                // repeat, with a remainder
                cBox.Add(nProduct,nZ,nProduct);
                nRemainder = nProduct;
                // basic division, with remainder
                c_nDivideThresholdSmall  = nY.GetSize()+1;
                nMemoryNeeds             = DivisionMemoryNeeds(nRemainder.GetSize(), nY.GetSize());
                pWorkspace[nMemoryNeeds] = TEST_BUFFERGUARD;
                Divide(nRemainder.GetSize(),
                       nY.GetSize(),
                       nDivSize,
                       nModSize,
                       nRemainder.GetValue(),
                       nY.GetValue(),
                       nDiv.GetValue(),
                       pWorkspace);
                if(TEST_BUFFERGUARD != pWorkspace[nMemoryNeeds])
                {
                    printf("Overan workspace memory\n");
                    goto exit;
                }
                nRemainder.SetSize(nModSize);
                bFailed = (nDiv != nX || nZ != nRemainder);
                if(bFailed || bVerbose)
                {
                    printf("Basic division with remainder:\n");
                    printf("x*y+z = prod:\n");
                    printf("x:          ");
                    nX.PrintHexToFile();
                    printf("y:          ");
                    nY.PrintHexToFile();
                    printf("z:          ");
                    nZ.PrintHexToFile();
                    printf("Prod:       ");
                    nProduct.PrintHexToFile();
                    printf("Prod/y:     ");
                    nDiv.PrintHexToFile();
                    printf("Prod mod y: ");
                    nRemainder.PrintHexToFile();
                    printf("\n");
                    if(bFailed)
                    {
                        goto exit;
                    }
                }
                // if the divisor is large enough, repeat with the recursive algorithm
                if(8<=nY.GetSize())
                {
                    cBox.Multiply(nX,nY,nProduct);
                    // first, test where the division should be exact -- no remainder
                    nRemainder = nProduct;
                    // recursive division
                    c_nDivideThresholdSmall  = 4; // lowest possible threshold -- make sure recursion working as far down as possible
                    nMemoryNeeds             = DivisionMemoryNeeds(nRemainder.GetSize(), nY.GetSize());
                    pWorkspace[nMemoryNeeds] = TEST_BUFFERGUARD;
                    Divide(nRemainder.GetSize(),
                           nY.GetSize(),
                           nDivSize,
                           nModSize,
                           nRemainder.GetValue(),
                           nY.GetValue(),
                           nDiv.GetValue(),
                           pWorkspace);
                    if(TEST_BUFFERGUARD != pWorkspace[nMemoryNeeds])
                    {
                        printf("Overan workspace memory\n");
                        goto exit;
                    }
                    nRemainder.SetSize(nModSize);
                    nDiv.SetSize(nDivSize);
                    bFailed = (nDiv!=nX || 0!=nModSize);
                    if(bFailed || bVerbose)
                    {
                        printf("Recursive division:\n");
                        printf("x*y = prod:\n");
                        printf("x:          ");
                        nX.PrintHexToFile();
                        printf("y:          ");
                        nY.PrintHexToFile();
                        printf("Prod:       ");
                        nProduct.PrintHexToFile();
                        printf("Prod/y:     ");
                        nDiv.PrintHexToFile();
                        printf("Prod mod y: ");
                        nRemainder.PrintHexToFile();
                        printf("\n");
                        if(bFailed)
                        {
                            goto exit;
                        }
                    }
                    // repeat, with a remainder
                    cBox.Add(nProduct,nZ,nProduct);
                    // recursive division
                    nRemainder               = nProduct;
                    c_nDivideThresholdSmall  = 4; // lowest possible threshold -- make sure recursion working as far down as possible
                    nMemoryNeeds             = DivisionMemoryNeeds(nRemainder.GetSize(), nY.GetSize());
                    pWorkspace[nMemoryNeeds] = TEST_BUFFERGUARD;
                    Divide(nRemainder.GetSize(),
                           nY.GetSize(),
                           nDivSize,
                           nModSize,
                           nRemainder.GetValue(),
                           nY.GetValue(),
                           nDiv.GetValue(),
                           pWorkspace);
                    if(TEST_BUFFERGUARD != pWorkspace[nMemoryNeeds])
                    {
                        printf("Overan workspace memory\n");
                        goto exit;
                    }
                    nRemainder.SetSize(nModSize);
                    nDiv.SetSize(nDivSize);
                    bFailed = (nDiv != nX || nZ != nRemainder);
                    if(bFailed || bVerbose)
                    {
                        printf("Recursive division with remainder:\n");
                        printf("x*y+z = prod:\n");
                        printf("x:          ");
                        nX.PrintHexToFile();
                        printf("y:          ");
                        nY.PrintHexToFile();
                        printf("z:          ");
                        nZ.PrintHexToFile();
                        printf("Prod:       ");
                        nProduct.PrintHexToFile();
                        printf("Prod/y:     ");
                        nDiv.PrintHexToFile();
                        printf("Prod mod y: ");
                        nRemainder.PrintHexToFile();
                        printf("\n");
                        if(bFailed)
                        {
                            goto exit;
                        }
                    }
                }
            }
        }
    }
    // edge cases: largest possible number of a given size divided by smallest possible of a size;
    // smallest of a size divided by largest of a size
    for(size_t i=6;i<c_nMaxSize*3;i++)
    {
        nY.Reserve(i);
        nX.Reserve(i);
        nDiv.Reserve(i);
        nProduct.Reserve(i);
        // BIG x, small y
        if(i&1)
        {
            for(size_t k=0;k<i;k++)
            {
                nX.GetValue()[k] = (DIGIT) -1;
            }
        }
        else
        {
            for(size_t k=0;k<i/2;k++)
            {
                nX.GetValue()[k] = 0;
            }
            for(size_t k=i/2;k<i;k++)
            {
                nX.GetValue()[k] = (DIGIT) -1;
            }
        }
        nX.SetSize(i);
        for(size_t j=1;j<=((i-4) > 100 ? 100 : i-5);j++)
        {
            nY.GetValue()[0]=(DIGIT) (j&2);
            for(size_t k=1;k<j-1;k++)
            {
                nY.GetValue()[k] = 0;
            }
            nY.GetValue()[j-1] = 1;
            nY.SetSize(j);
            // basic division
            nZ = nX; // divide is destructive!
            c_nDivideThresholdSmall = c_nMaxSize+1;
            nYCopy = nY;
            // initialize XDivY to gibberish -- many 0s in result
            for (size_t k=0; k<nZ.GetSize()-nY.GetSize()+1; k++) nProduct.GetValue()[k] = TEST_BUFFERGUARD;
            Divide(nZ.GetSize(),nY.GetSize(),nDivSize,nModSize,nZ.GetValue(),nY.GetValue(),nDiv.GetValue(),pWorkspace);
            if (nY != nYCopy)
            {
                printf("Divide didn't restore y properly!\n");
                printf("Original:    "); nYCopy.PrintHexToFile();
                printf("Post-divide: "); nY.PrintHexToFile();
                goto exit;
            }
            nZ.SetSize(nModSize);
            nRemainder = nZ; // copy remainder for validation
            nDiv.SetSize(nDivSize);
            // recursive division
            nZ = nX; // divide is destructive!
            c_nDivideThresholdSmall = 4; // lowest possible threshold -- make sure recursion working as far down as possible
            Divide(nZ.GetSize(),nY.GetSize(),nDivSize,nModSize,nZ.GetValue(),nY.GetValue(),nProduct.GetValue(),pWorkspace);
            if (nY != nYCopy)
            {
                printf("Divide didn't restore y properly!\n");
                printf("Original:    "); nYCopy.PrintHexToFile();
                printf("Post-divide: "); nY.PrintHexToFile();
                goto exit;
            }
            nZ.SetSize(nModSize);
            nProduct.SetSize(nDivSize);
            // basic divide has div in pDiv, remainder in pRemainder
            // recursive divide has div in pProduct, remainder in pZ
            // Validate:
            bFailed = false;
            if(nDiv != nProduct || nRemainder != nZ)
            {
                printf("Divide BIG by little failed: div okay? %s  mod okay? %s\n",
                       (nDiv != nProduct) ? "no" : "yes",
                       (nRemainder != nZ) ? "no" : "yes");
                bFailed = true;
            }
            if(bFailed || bVerbose)
            {
                printf("x/y:\n");
                printf("x: "); nX.PrintHexToFile();
                printf("y: "); nY.PrintHexToFile();
                printf("Basic div:\n");
                nDiv.PrintHexToFile();
                printf("Basic mod:\n");
                nRemainder.PrintHexToFile();
                printf("Recursive div:\n");
                nProduct.PrintHexToFile();
                printf("Recursive mod:\n");
                nZ.PrintHexToFile();
                if(bFailed)
                {
                    goto exit;
                }
            }
        }
        // BIG y, small x
        for(size_t k=0;k<i-1;k++)
        {
            nX.GetValue()[k] = 0;
        }
        nX.GetValue()[i-1] = 1;
        nX.SetSize(i);
        for(size_t j=1;j<((i-4) > 100 ? 100 : i-4);j++)
        {
            for(size_t k=0;k<j;k++)
            {
                nY.GetValue()[k] = (DIGIT) -1;
            }
            nY.SetSize(j);
            nYCopy = nY;
            // basic division
            nZ = nX; // divide is destructive!
            c_nDivideThresholdSmall = c_nMaxSize;
            Divide(nZ.GetSize(),nY.GetSize(),nDivSize,nModSize,nZ.GetValue(),nY.GetValue(),nDiv.GetValue(),pWorkspace);
            if (nY != nYCopy)
            {
                printf("Divide didn't restore y properly!\n");
                printf("Original:    "); nYCopy.PrintHexToFile();
                printf("Post-divide: "); nY.PrintHexToFile();
                goto exit;
            }
            nZ.SetSize(nModSize);
            nRemainder = nZ; // copy remainder for validation
            nDiv.SetSize(nDivSize);
            // recursive division
            nZ = nX; // divide is destructive!
            c_nDivideThresholdSmall = 4; // lowest possible threshold -- make sure recursion working as far down as possible
            // initialize XDivY to gibberish -- many 0s in result
            for (size_t k=0; k<nZ.GetSize()-nY.GetSize()+1; k++) nProduct.GetValue()[k] = TEST_BUFFERGUARD;
            Divide(nZ.GetSize(),nY.GetSize(),nDivSize,nModSize,nZ.GetValue(),nY.GetValue(),nProduct.GetValue(),pWorkspace);
            if (nY != nYCopy)
            {
                printf("Divide didn't restore y properly!\n");
                printf("Original:    "); nYCopy.PrintHexToFile();
                printf("Post-divide: "); nY.PrintHexToFile();
                goto exit;
            }
            nZ.SetSize(nModSize);
            nProduct.SetSize(nDivSize);
            // basic divide has div in pDiv, remainder in pRemainder
            // recursive divide has div in pProduct, remainder in pZ
            // Validate:
            if(nDiv != nProduct || nRemainder != nZ)
            {
                printf("Divide little by BIG failed: div okay? %s  mod okay? %s\n",
                       (nDiv != nProduct) ? "no" : "yes",
                       (nRemainder != nZ) ? "no" : "yes");
                bFailed = true;
            }
            if(bFailed || bVerbose)
            {
                printf("x/y:\n");
                printf("x: "); nX.PrintHexToFile();
                printf("y: "); nY.PrintHexToFile();
                printf("Basic div:\n");
                nDiv.PrintHexToFile();
                printf("Basic mod:\n");
                nRemainder.PrintHexToFile();
                printf("Recursive div:\n");
                nProduct.PrintHexToFile();
                printf("Recursive mod:\n");
                nZ.PrintHexToFile();
                if(bFailed)
                {
                    goto exit;
                }
            }
        }
    }
    bTestWorked = true;
exit:
    delete pWorkspace;
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestBigGCD(bool bVerbose)
{
    ResetThresholdsForTest();
    bool                bXCoefNegative;
    CArithmeticBox      cBox;
    size_t              nXSize,nYSize,nMinSize,nMaxSize,nGCDMemNeeds,nGCDCoefMemNeeds,nGCDSize,nXCoefSize,nYCoefSize;
    CBigIntegerForTest  nX,nY,nGCD,nGCDCoef,nXCoef,nYCoef,nHold,nXDivGCD,nYDivGCD;
    const size_t        c_nWorkspaceSize = 1 + max(CUnsignedArithmeticHelper::GCDMemoryNeeds(1000, 1000, true),
                                                   CUnsignedArithmeticHelper::GCDMemoryNeeds(1000, c_nMaxBYTESizeForRecursiveGCD/sizeof(DIGIT), true));
    bool                bTestWorked      = false;
    DIGIT               *pWorkspace      = (DIGIT *) malloc(sizeof(DIGIT)*c_nWorkspaceSize); // enough for THIS test
    // bad input checks
    if(eBadArgument != cBox.GCDExtended(nX,nY,nGCD,nXCoef,nGCD) ||
       eBadArgument != cBox.GCDExtended(nX,nY,nXCoef,nGCD,nGCD) ||
       eBadArgument != cBox.GCDExtended(nX,nY,nXCoef,nXCoef,nGCD))
    {
        printf("Expected bad argument return value\n");
        goto exit;
    }
    nX.SetFromHexString("0");
    nY.SetFromHexString("0");
    if(eBadOperand != cBox.GCDExtended(nX,nY,nGCD,nXCoef,nYCoef))
    {
        printf("Trying to take the greatest common divisor of 0 and 0 doesn't make sense -- bad operand return value expected\n");
        goto exit;
    }
    nY.SetRandom(16);
    cBox.GCDExtended(nX, nY, nGCD, nXCoef, nYCoef);
    if (nY != nGCD || !nXCoef.IsZero() || 1 != nYCoef.GetSize() || 1 != nYCoef.GetValue()[0])
    {
        printf("error computing extended GCD where one of the values is 0\n");
        goto exit;
    }
    cBox.GCDExtended(nY, nX, nGCD, nYCoef, nXCoef);
    if (nY != nGCD || !nXCoef.IsZero() || 1 != nYCoef.GetSize() || 1 != nYCoef.GetValue()[0])
    {
        printf("error computing extended GCD where one of the values is 0\n");
        goto exit;
    }
    // what if one of x, y is also used for the GCD or a coefficient?
    nX.SetRandom(16);
    nHold = nX;
    cBox.GCDExtended(nX, nY, nX, nXCoef, nYCoef);
    cBox.Multiply(nHold, nXCoef, nGCDCoef);
    cBox.MultiplyAdd(nY, nYCoef, nGCDCoef);
    if (nX != nGCDCoef)
    {
        printf("error with extended GCD where operand reused for output\n");
        goto exit;
    }
    nX = nHold;
    cBox.GCDExtended(nX, nY, nGCD, nX, nYCoef);
    cBox.Multiply(nHold, nX, nGCDCoef);
    cBox.MultiplyAdd(nY, nYCoef, nGCDCoef);
    if (nGCD != nGCDCoef)
    {
        printf("error with extended GCD where operand reused for output\n");
        goto exit;
    }
    nX = nHold;
    cBox.GCDExtended(nX, nY, nGCD, nXCoef, nX);
    cBox.Multiply(nHold, nXCoef, nGCDCoef);
    cBox.MultiplyAdd(nY, nX, nGCDCoef);
    if (nGCD != nGCDCoef)
    {
        printf("error with extended GCD where operand reused for output\n");
        goto exit;
    }
    for (size_t i=1; i<1000; i += 10)
    {
        printf("Size %i, 1-991\n",i);
        for (size_t j=1; j<1000; j += 10)
        {
            nX.SetRandom(_DIGIT_SIZE_IN_BITS*i);
            nY.SetRandom(_DIGIT_SIZE_IN_BITS*j);
            nXSize           = nX.GetSize();
            nYSize           = nY.GetSize();
            nMinSize         = (nXSize < nYSize) ? nXSize : nYSize;
            nMaxSize         = (nXSize < nYSize) ? nYSize : nXSize;
            nGCDMemNeeds     = CUnsignedArithmeticHelper::GCDMemoryNeeds(nXSize, nYSize, false);
            nGCDCoefMemNeeds = CUnsignedArithmeticHelper::GCDMemoryNeeds(nXSize, nYSize, true);
            if (c_nWorkspaceSize <= nGCDMemNeeds || c_nWorkspaceSize <= nGCDCoefMemNeeds)
            {
                printf("Not enough workspace allocated, silly!\n");
                goto exit;
            }
            nXCoef.Reserve(nYSize + 2);      // space for maximum possible coef, +1 overflow for internal calculations, +1 for buffer guard
            nYCoef.Reserve(nXSize + 2);      // space for maximum possible coef, +1 overflow for internal calculations, +1 for buffer guard
            nGCD.Reserve(nMinSize + 1);      // space for largest possible GCD, +1 for buffer guard
            nGCDCoef.Reserve(nMaxSize + 1);  // Needs extra space for intermediate values, +1 for buffer guard
            nXCoef.GetValue()[nYSize + 1] = TEST_BUFFERGUARD; // set buffer guard -- one extra digit used for overflow
            nYCoef.GetValue()[nXSize + 1] = TEST_BUFFERGUARD; // set buffer guard -- one extra digit used for overflow
            nGCD.GetValue()[nMinSize]     = TEST_BUFFERGUARD; // set buffer guard
            nGCDCoef.GetValue()[nMaxSize] = TEST_BUFFERGUARD; // set buffer guard
            pWorkspace[nGCDMemNeeds]      = TEST_BUFFERGUARD; // set buffer guard
            // GCD and GCDCoef should produce the same GCD
            nGCD.SetSize(CUnsignedArithmeticHelper::GCD(nX.GetSize(),
                                                        nY.GetSize(),
                                                        nX.GetValue(),
                                                        nY.GetValue(),
                                                        nGCD.GetValue(),
                                                        pWorkspace));
            if (nMinSize < nGCD.GetSize() || TEST_BUFFERGUARD != nGCD.GetValue()[nMinSize])
            {
                printf("Error in GCD -- too big/overran memory allocation\n");
                goto exit;
            }
            if (pWorkspace[nGCDMemNeeds] != TEST_BUFFERGUARD)
            {
                printf("Overran workspace memory in basic GCD\n");
                goto exit;
            }
            pWorkspace[nGCDCoefMemNeeds] = TEST_BUFFERGUARD; // set buffer guard
            // try, computing both the X and Y coefficients
            CUnsignedArithmeticHelper::GCD(nX.GetSize(),
                                           nY.GetSize(),
                                           nGCDSize,
                                           nXCoefSize,
                                           nYCoefSize,
                                           nX.GetValue(),
                                           nY.GetValue(),
                                           nGCDCoef.GetValue(),
                                           nXCoef.GetValue(),
                                           nYCoef.GetValue(),
                                           bXCoefNegative,
                                           pWorkspace);
            if (TEST_BUFFERGUARD != nGCDCoef.m_pnValue[nMaxSize] ||
                TEST_BUFFERGUARD != nXCoef.m_pnValue[nYSize + 1] ||
                TEST_BUFFERGUARD != nYCoef.m_pnValue[nXSize + 1])
            {
                printf("Buffer overrun in GCDCoef\n");
                goto exit;
            }
            if (pWorkspace[nGCDCoefMemNeeds] != TEST_BUFFERGUARD)
            {
                printf("Overran workspace memory in GCD with coefficients\n");
                goto exit;
            }
            else if (nMinSize < nGCDSize ||
                     nYSize < nXCoefSize ||
                     nXSize < nYCoefSize)
            {
                printf("Error in GCDCoef -- sizes too big\n");
                goto exit;
            }
            nXCoef.SetSize(nXCoefSize);
            nXCoef.SetNegative(bXCoefNegative);
            nYCoef.SetSize(nYCoefSize);
            nYCoef.SetNegative(!bXCoefNegative);
            nGCDCoef.SetSize(nGCDSize);
            nGCDCoef.SetNegative(false);
            if (nGCD != nGCDCoef)
            {
                nGCD.PrintHexToFile();
                nGCDCoef.PrintHexToFile();
                printf("Two methods of computing GCD didn't agree\n");
                goto exit;
            }
            // validate that x*xcoef + y*ycoef == GCD
            if (0 != nXCoef.GetSize())
            {
                nXSize = nX.GetSize() + nXCoef.GetSize();
#if _CollectDetailedTimingData
                DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
                CUnsignedArithmeticHelper::MultUBackend(nX.GetSize(),
                                                        nXCoef.GetSize(),
                                                        nX.GetValue(),
                                                        nXCoef.GetValue(),
                                                        pWorkspace,
                                                        pWorkspace + nXSize,
                                                        dwTimestamp);
#else
                CUnsignedArithmeticHelper::MultUBackend(nX.GetSize(),
                                                        nXCoef.GetSize(),
                                                        nX.GetValue(),
                                                        nXCoef.GetValue(),
                                                        pWorkspace,
                                                        pWorkspace + nXSize);
#endif
                if (0 == pWorkspace[nXSize - 1])
                {
                    nXSize--;
                }
            }
            else
            {
                nXSize = 0;
            }
            if (0 != nYCoef.GetSize())
            {
                nYSize = nY.GetSize() + nYCoef.GetSize();
#if _CollectDetailedTimingData
                DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
                CUnsignedArithmeticHelper::MultUBackend(nY.GetSize(),
                                                        nYCoef.GetSize(),
                                                        nY.GetValue(),
                                                        nYCoef.GetValue(),
                                                        pWorkspace + nXSize,
                                                        pWorkspace + nXSize + nYSize,
                                                        dwTimestamp);
#else
                CUnsignedArithmeticHelper::MultUBackend(nY.GetSize(),
                                                        nYCoef.GetSize(),
                                                        nY.GetValue(),
                                                        nYCoef.GetValue(),
                                                        pWorkspace + nXSize,
                                                        pWorkspace + nXSize + nYSize);
#endif
                if (0 == pWorkspace[nYSize + nXSize - 1])
                {
                    nYSize--;
                }
            }
            else
            {
                nYSize = 0;
            }
            CUnsignedArithmeticHelper::AddSigned(nXSize,
                                                 nYSize,
                                                 nGCDSize,
                                                 pWorkspace,
                                                 pWorkspace + nXSize,
                                                 pWorkspace + nXSize + nYSize,
                                                 nXCoef.IsNegative(),
                                                 nYCoef.IsNegative(),
                                                 bXCoefNegative);
            if (bXCoefNegative)
            {
                printf("GCD is always positive\n");
                goto exit;
            }
            if (0 != CBigInteger::CompareUnsigned(nGCDSize,
                                                  nGCD.GetSize(),
                                                  pWorkspace + nXSize + nYSize,
                                                  nGCD.GetValue()))
            {
                printf("GCDCoef problems -- x*xCoef + y*yCoef != GCD as computed!\n");
                goto exit;
            }
            // validate that GCD divides x, y evenly
            cBox.Divide(nX, nGCD, nXDivGCD, nHold);
            if (0 != nHold.GetSize())
            {
                printf("Putative GCD doesn't divide X evenly!\n");
                goto exit;
            }
            cBox.Divide(nY, nGCD, nYDivGCD, nHold);
            if (0 != nHold.GetSize())
            {
                printf("Putative GCD doesn't divide Y evenly!\n");
                goto exit;
            }
            // validate that GCD(x/GCD(x,y),y/GCD(x,y)) == 1
            // set buffer guard
            nGCDMemNeeds = CUnsignedArithmeticHelper::GCDMemoryNeeds(nXDivGCD.GetSize(),
                                                                     nYDivGCD.GetSize(),
                                                                     false);
            pWorkspace[nGCDMemNeeds] = TEST_BUFFERGUARD;
            nHold.SetSize(CUnsignedArithmeticHelper::GCD(nXDivGCD.GetSize(),
                                                         nYDivGCD.GetSize(),
                                                         nXDivGCD.GetValue(),
                                                         nYDivGCD.GetValue(),
                                                         nHold.GetValue(),
                                                         pWorkspace));
            if (1 != nHold.GetSize() || 1 != nHold.GetValue()[0])
            {
                printf("1 != computed value of GCD(x/GCD(x,y),y/GCD(x,y))\n");
                goto exit;
            }
            // validate buffer guard
            if (pWorkspace[nGCDMemNeeds] != TEST_BUFFERGUARD)
            {
                printf("yet another buffer overrun\n");
                goto exit;
            }
            // try again, this time just asking for the x coef.  Should get the same value
            nHold.Reserve(nYSize + 2); // +2 : slot for TEST_BUFFERGUARD, one extra DIGIT for internal computations
            nHold.GetValue()[nYSize]  = TEST_BUFFERGUARD; // set buffer guard -- one extra digit used for overflow
            CUnsignedArithmeticHelper::GCD(nX.GetSize(),
                                           nY.GetSize(),
                                           nGCDSize,
                                           nXCoefSize,
                                           nYCoefSize,
                                           nX.GetValue(),
                                           nY.GetValue(),
                                           nGCDCoef.GetValue(),
                                           nHold.GetValue(), // for the x coef
                                           NULL,
                                           bXCoefNegative,
                                           pWorkspace);
            if (TEST_BUFFERGUARD != nHold.GetValue()[nYSize])
            {
                printf("Overran coefficient buffer\n");
                goto exit;
            }
            // GCD should be the same
            nHold.SetSize(nXCoefSize);
            nHold.SetNegative(bXCoefNegative);
            nGCDCoef.SetSize(nGCDSize);
            nGCDCoef.SetNegative(false);
            if (nGCD != nGCDCoef)
            {
                printf("GCD:\n");
                nGCD.PrintHexToFile();
                nGCDCoef.PrintHexToFile();
                printf("X, Y:\n");
                nX.PrintDecimalToFile();
                nY.PrintDecimalToFile();
                printf("Two methods of computing GCD didn't agree -- x-coef only; GCD differ\n");
                goto exit;
            }
            // x coef should be the same
            if (nHold != nXCoef)
            {
                nHold.PrintHexToFile();
                nXCoef.PrintHexToFile();
                printf("Two methods of computing GCD didn't agree -- x coef only; x-coefs differ\n");
                goto exit;
            }
            // and once more, just asking for the y coefficient
            CUnsignedArithmeticHelper::GCD(nX.GetSize(),
                                           nY.GetSize(),
                                           nGCDSize,
                                           nXCoefSize,
                                           nYCoefSize,
                                           nX.GetValue(),
                                           nY.GetValue(),
                                           nGCDCoef.GetValue(),
                                           NULL,
                                           nHold.GetValue(), // for the y coef
                                           bXCoefNegative,
                                           pWorkspace);
            // GCD should be the same
            nHold.SetSize(nYCoefSize);
            nHold.SetNegative(!bXCoefNegative);
            nGCDCoef.SetSize(nGCDSize);
            nGCDCoef.SetNegative(false);
            if (nGCD != nGCDCoef)
            {
                nGCD.PrintHexToFile();
                nGCDCoef.PrintHexToFile();
                printf("Two methods of computing GCD didn't agree -- y-coef only; GCD differ\n");
                goto exit;
            }
            // x coef should be the same
            if (nHold != nYCoef)
            {
                nHold.PrintHexToFile();
                nYCoef.PrintHexToFile();
                printf("Two methods of computing GCD didn't agree -- y coef only; y-coefs differ\n");
                goto exit;
            }
        }
    }
    // do some trials where the GCD is known and large.  And use the box, to validate that interface
    for (size_t i=0; i<1000; i++)
    {
        do
        {
            nHold.SetRandom(640);
        }
        while(nHold.GetSize()<10);
        if(0==i%100) printf("GCD tests: large GCD trials %i to %i (of 1000)\n",i+1,i+100);
        for (int j=0; j<200; j++)
        {
            do
            {
                nYCoef.SetRandom((j + 1)*_DIGIT_SIZE_IN_BITS);
            }
            while(nYCoef.GetSize() <= j);
            cBox.Multiply(nHold, nYCoef, nY);
            if (0 == j)
            {
                nX.SetFromHexString("0");
            }
            else if (1 == j)
            {
                nX = nHold;
            }
            else
            {
                nXCoef =  nYCoef;
                nXCoef += 1;
                cBox.Multiply(nXCoef, nHold, nX);
            }
            // Now we know (by construction) that the GCD of X and Y is in pHold (except for i==0, in which case X is 0 and the GCD is Y)
            // Verify things come out as expected
            cBox.GCDExtended(nX, nY, nGCDCoef, nXCoef, nYCoef);
            if (0 == j)
            {
                // expect xCoef is 0, yCoef is 1, and the GCD is Y
                if (!nXCoef.IsZero())
                {
                    printf("expected X coef to be 0\n");
                    goto exit;
                }
                else if (1 != nYCoef.GetSize() || 1 != nYCoef.GetValue()[0])
                {
                    printf("Expected Y coef to be 1\n");
                    goto exit;
                }
                else if (nY != nGCDCoef)
                {
                    printf("Expected the GCD to be Y");
                    goto exit;
                }
            }
            else
            {
                if (nHold != nGCDCoef)
                {
                    printf("Expected GCD to be ");
                    nHold.PrintHexToFile();
                    printf("But instead it was ");
                    nGCDCoef.PrintHexToFile();
                    goto exit;
                }
                // should have X*Xcoef + Y*Ycoef = GCD
                cBox.Multiply(nX, nXCoef, nGCD);
                cBox.MultiplyAdd(nY, nYCoef, nGCD);
                if (nGCD != nGCDCoef)
                {
                    printf("Expected X*XCoef + Y*YCoef to be the GCD, and it wasn't\n");
                    goto exit;
                }
            }
            // validate GCD, GCDExtended give same GCD
            cBox.GCD(nX, nY, nGCD);
            if (nGCD != nGCDCoef)
            {
                printf("Two methods of computing the greatest common divisor disagreed:\n");
                printf("x:            "); nX.PrintHexToFile();
                printf("y:            "); nY.PrintHexToFile();
                printf("GCD:          "); nGCD.PrintHexToFile();
                printf("GCD extended: "); nGCDCoef.PrintHexToFile();
                goto exit;
            }
            if(0==j)
            {
                // validate path where Y is 0 for GCD (not hit elsewhere)
                cBox.GCD(nY, nX, nGCD);
                if (nGCD != nGCDCoef)
                {
                    printf("Two methods of computing the greatest common divisor disagreed:\n");
                    printf("x:            "); nX.PrintHexToFile();
                    printf("y:            "); nY.PrintHexToFile();
                    printf("GCD:          "); nGCD.PrintHexToFile();
                    printf("GCD extended: "); nGCDCoef.PrintHexToFile();
                    goto exit;
                }
            }
        }
    }
    // final test: some VERY large GCD problems
    for(int i=0; i<100; i++)
    {
        nX.SetRandom(0x4000);
        nY.SetRandom(0x4000);
        cBox.GCDExtended(nX, nY, nGCDCoef, nXCoef, nYCoef);
        cBox.Multiply(nX, nXCoef, nGCD);
        cBox.MultiplyAdd(nY, nYCoef, nGCD);
        if (nGCD != nGCDCoef)
        {
            printf("oops\n");
            goto exit;
        }
    }
    bTestWorked = true;
exit:
    free(pWorkspace);
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestBigVector(bool bVerbose)
{
    CArithmeticBox cBox;
    ResetThresholdsForTest();
    bool               bTestWorked     = false;
    const unsigned int c_nVectorLength = 11;
    CBigIntegerVector  vVec(c_nVectorLength), vVecCopy(c_nVectorLength);
    CBigInteger        nBigInt("1"), nDotProduct, nExpectedProduct("B");
    for(int i=0;i<c_nVectorLength;i++)
    {
        vVec[i] = nBigInt;
    }
    if (!(vVecCopy = vVec))
    {
        printf("assignment failed\n");
        goto exit;
    }
    for (int i = 0; i < c_nVectorLength; i++)
    {
        if (vVec[i] != vVecCopy[i] || vVec[i].GetValue() == vVecCopy[i].GetValue())
        {
            printf("deep copy failed\n");
            goto exit;
        }
    }
    if(!CBigIntegerVector::DotProduct(vVec,vVec,nDotProduct,cBox))
    {
        printf("Dot product failed\n");
        goto exit;
    }
    else if(nDotProduct != nExpectedProduct || bVerbose)
    {
        printf("Vectors:\n");
        vVec.PrintVec();
        vVec.PrintVec();
        printf("Expected product:\n");
        nExpectedProduct.PrintHexToFile();
        printf("\nComputed product:\n");
        nDotProduct.PrintHexToFile();
        printf("\n");
        if(nDotProduct != nExpectedProduct)
        {
            goto exit;
        }
    }
    bTestWorked = true;
exit:
    return bTestWorked;
}

// debug resolve todo: quasi inverse where row swaps required!
bool CArithmeticCorrectnessTester::TestBigMatrix(bool bVerbose)
{
    ResetThresholdsForTest(true); // matrices used for 2n by n multiply;
                                  // DO NOT rely on the multiply for test!
    bool               bTestWorked   = false;
    const size_t       c_nMatrixSize = 15;
    const unsigned int c_nLargeTests = 20;
    CArithmeticBox     cBox;
    CBigIntegerForTest nBig;
    CBigIntegerVector  nDiagVector(c_nMatrixSize); // the diagonal of DiagMatrix
    CBigIntegerMatrix  nMat1(c_nMatrixSize), nMat2(c_nMatrixSize), nQuasiInverse(c_nMatrixSize), nProductMatrix(c_nMatrixSize), nDiagMatrix(c_nMatrixSize);
    CBigIntegerMatrix  nBigMat1(6*c_nMatrixSize,10*c_nMatrixSize),
                       nBigMat2(10*c_nMatrixSize,12*c_nMatrixSize),
                       nBigProdOracle(6*c_nMatrixSize,12*c_nMatrixSize),
                       nBigProduct(6*c_nMatrixSize,12*c_nMatrixSize);
    CBigIntegerMatrix  smallMatrix(3);
    CBigIntegerVector  diag(3);
    // validate accessor function -- [] overload
    for(int i=0; i<c_nMatrixSize; i++)
    {
        for(int j=0; j<c_nMatrixSize; j++)
        {
            nMat1[i][j].Reserve(1);
            nMat1[i][j].SetSize(1);
            nMat1[i][j].GetValue()[0] = i*c_nMatrixSize+j+1;
        }
    }
    nBig.SetFromHexString("1");
    for(int i=0; i<c_nMatrixSize; i++)
    {
        for(int j=0; j<c_nMatrixSize; j++)
        {
            if(nMat1.m_ppData[i][j] != nBig)
            {
                printf("accessor failed\n");
                goto exit;
            }
            nMat1[i][j] += 1;
            if(nMat1.m_ppData[i][j] == nBig)
            {
                printf("accessor failed\n");
                goto exit;
            }
            nBig += 1;
            if (nMat1.m_ppData[i][j] != nBig)
            {
                printf("accessor failed\n");
                goto exit;
            }
        }
    }
    // construct 2 triangular matrices with non-zero elements on the
    // diagonals -- 1, in this case.  These matrices WILL be invertible.
    for(size_t i=0;i<c_nMatrixSize;i++)
    {
        for(size_t j=0;j<i;j++)
        {
            nBig.SetFromHexString("0");
            nMat1[i][j] = nBig;
            nBig.SetRandom(_DIGIT_SIZE_IN_BITS*c_nMatrixSize);
            nBig.SetNegative(rand()%2);
            nMat2[i][j] = nBig;
        }
        nBig.SetFromHexString("1");
        nMat1[i][i] = nBig;
        nMat2[i][i] = nBig;
        for(size_t j=i+1;j<c_nMatrixSize;j++)
        {
            nBig.SetFromHexString("0");
            nMat2[i][j] = nBig;
            nBig.SetRandom(_DIGIT_SIZE_IN_BITS*c_nMatrixSize);
            nBig.SetNegative(rand()%2);
            nMat1[i][j] = nBig;
        }
    }
    if(CBigIntegerMatrix::eWorked != CBigIntegerMatrix::MultiplyOracle(nMat1,nMat2,nProductMatrix,cBox))
    {
        printf("Multiplication failed\n");
        goto exit;
    }
    // validate assignment (=)
    if(CBigIntegerMatrix::eMalformed != (nBigMat1 = nBigMat2))
    {
        printf("Malformed matrix assignment allowed\n");
        goto exit;
    }
    if(CBigIntegerMatrix::eWorked != (nQuasiInverse = nProductMatrix))
    {
        printf("copy failed\n");
        goto exit;
    }
    if (nQuasiInverse != nProductMatrix)
    {
        printf("Copies not equal???\n");
        goto exit;
    }
    if (nQuasiInverse.m_ppData == nProductMatrix.m_ppData)
    {
        printf("assignment wasn't deep copy\n");
        goto exit;
    }
    for(int i=0; i<nQuasiInverse.GetRows(); i++)
    {
        for(int j=0; j<nQuasiInverse.GetCols(); j++)
        {
            if(nQuasiInverse.GetValue(i,j) == nProductMatrix.GetValue(i,j))
            {
                printf("assignment wasn't deep copy\n");
                goto exit;
            }
        }
    }
    // validate back-end Strassen multiplication
    CBigIntegerMatrix::Multiply(nMat1, nMat2, nQuasiInverse, cBox);
    if (nQuasiInverse != nProductMatrix)
    {
        nMat1.Print();
        printf("==\n");
        nMat2.Print();
        printf("matrix multiplication optimized disagreed with the oracle\n");
        printf("should be:\n");
        nProductMatrix.Print();
        printf("got:\n");
        nQuasiInverse.Print();
        goto exit;
    }
    if(CBigIntegerMatrix::eWorked != nQuasiInverse.QuasiInverse(nDiagVector,cBox))
    {
        printf("Quasi inverse call failed\n");
        goto exit;
    }
    if(CBigIntegerMatrix::eWorked != CBigIntegerMatrix::Multiply(nQuasiInverse,
                                                                 nProductMatrix,
                                                                 nDiagMatrix,
                                                                 cBox))
    {
        printf("Multiplication failed\n");
        goto exit;
    }
    // validate that the product of the quasi-inverse and the original matrix is
    // the expected diagonal matrix
    for(size_t i=0;i<c_nMatrixSize;i++)
    {
        for(size_t j=i+1;j<c_nMatrixSize;j++)
        {
            if(0 != nDiagMatrix.GetValue(i,j)->GetSize() ||
               0 != nDiagMatrix.GetValue(j,i)->GetSize())
            {
                printf("didn't get diagonal matrix as expected\n");
                printf("matrix:\n");
                nProductMatrix.Print();
                printf("inverse:\n");
                nQuasiInverse.Print();
                printf("product:\n");
                nDiagMatrix.Print();
                goto exit;
            }
        }
    }
    for(size_t i=0;i<c_nMatrixSize;i++)
    {
        if(*(nDiagMatrix.GetValue(i,i)) != *(nDiagVector.GetValue(i)))
        {
            printf("Didn't get expected diagonal matrix\n");
            goto exit;
        }
    }
    // failure case: if we 0 out one of the diagonal entries of Mat1, it's product with
    // Mat2 is not invertible
    nMat1.GetValue(c_nMatrixSize/2,c_nMatrixSize/2)->SetSize(0);
    if(CBigIntegerMatrix::eWorked != CBigIntegerMatrix::Multiply(nMat1,nMat2,nProductMatrix,cBox))
    {
        printf("Multiplication failed\n");
        goto exit;
    }
    if(CBigIntegerMatrix::eWorked != (nQuasiInverse = nProductMatrix))
    {
        printf("copy failed\n");
        goto exit;
    }
    if(CBigIntegerMatrix::eSingular != nQuasiInverse.QuasiInverse(nDiagVector,cBox))
    {
        printf("Should not be able to invert singular matrix\n");
        goto exit;
    }
    // compute the quasi-inverse of the matrix
    // 0  1  1
    // 1  1  1
    // 1 -1  1
    // Note that this requires row exchanges.
    // It's quasi-inverse is
    // -1  1  0
    //  0  1 -1
    //  2 -1  1
    // and the quasi-inverse times the original matrix is
    //  1  0  0
    //  0  2  0
    //  0  0  2
    // so its diag is {1,2,2}
    nBig.SetFromHexString("1");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            smallMatrix[i][j] = nBig;
        }
    }
    smallMatrix[0][0].SetSize(0);
    smallMatrix[2][1].Invert();
    smallMatrix.QuasiInverse(diag, cBox);
    // validate the computed inverse
    if(smallMatrix[0][1] != nBig || !smallMatrix[0][2].IsZero() || !smallMatrix[1][0].IsZero() || smallMatrix[1][1] != nBig || smallMatrix[2][2] != nBig)
    {
        printf("error computing inverse where rows swaps necessary\n");
        smallMatrix.Print();
        goto exit;
    }
    if(diag[0] != nBig)
    {
        printf("error computing diagonal associated with the quasi inverse where row swaps needed\n");
        goto exit;
    }
    nBig.Invert();
    if(smallMatrix[0][0] != nBig || smallMatrix[1][2] != nBig || smallMatrix[2][1] != nBig)
    {
        printf("error computing inverse where rows swaps necessary\n");
        smallMatrix.Print();
        goto exit;
    }
    nBig.SetFromHexString("2");
    if(smallMatrix[2][0] != nBig)
    {
        printf("error computing inverse where rows swaps necessary\n");
        goto exit;
    }
    if(diag[1] != nBig || diag[2] != nBig)
    {
        printf("error computing diagonal associated with the quasi inverse where row swaps needed\n");
        smallMatrix.Print();
        goto exit;
    }
    // finally, just run a bunch of largish matrix multiplications: oracle vs performant (well; performant in retail anyway)
    for(int k=0;k<c_nLargeTests;k++)
    {
        printf("Testing multiplication: %i of %u\n", k + 1, c_nLargeTests);
        for(int i=0; i<nBigMat1.GetRows(); i++)
        {
            for(int j=0;j<nBigMat1.GetCols(); j++)
            {
                nBig.SetRandom(c_nMatrixSize*_DIGIT_SIZE_IN_BITS);
                nBigMat1[i][j] = nBig;
            }
        }
        for(int i=0; i<nBigMat2.GetRows(); i++)
        {
            for(int j=0;j<nBigMat2.GetCols(); j++)
            {
                nBig.SetRandom(c_nMatrixSize*_DIGIT_SIZE_IN_BITS);
                nBigMat2[i][j] = nBig;
            }
        }
        if (CBigIntegerMatrix::eWorked != CBigIntegerMatrix::MultiplyOracle(nBigMat1, nBigMat2, nBigProdOracle, cBox))
        {
            printf("Basic multiply failed\n");
            goto exit;
        }
        if (CBigIntegerMatrix::eWorked != CBigIntegerMatrix::Multiply(nBigMat1, nBigMat2, nBigProduct, cBox))
        {
            printf("Optimzed multiply failed\n");
            goto exit;
        }
        if (nBigProdOracle != nBigProduct)
        {
            printf("Multiplcation failed -- oracle and optimized got different results\n");
            goto exit;
        }
    }
    bTestWorked = true;
exit:
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::Test2NByNMultiply(bool bVerbose)
{
    DWORD                 dwTime;
    CArithmeticBox        cBox;
    CBigIntegerForTest    nX1, nX2, nX3, nProdMult, nProdOracle, nDiff;
    size_t                nXSize,nYSize,nZSize,nMemoryNeeds;
    SSystemData           *pSystemToUse;
    const unsigned int    c_nPiecesToTry     = 128;
    const unsigned int    c_nFinalTestDIGITs = 60000;
    char                  *szXHex            = NULL;
    char                  *szYHex            = NULL;
    const size_t          c_nMinPieces       = 5;
    const size_t          c_nMaxPieces       = 11;
    const size_t          c_nMaxSize         = 300; // must be greater than 10*c_nMaxPieces
    bool                  bTestWorked        = false;
    CBigIntegerForTest    *pX                = new CBigIntegerForTest();
    CBigIntegerForTest    *pY                = new CBigIntegerForTest();
    CBigIntegerForTest    *pValidatedProduct = new CBigIntegerForTest();
    CBigIntegerForTest    *pTestProduct      = new CBigIntegerForTest();
    DIGIT                 *pWorkspace        = (DIGIT *) malloc(sizeof(DIGIT)*2000000); // plenty for this test
#if _CollectDetailedTimingData
    DWORD64 dwTimestamp = 0;
#endif
    ResetThresholdsForTest();
    // a specific multiplication that has had trouble in the past -- it's working now
    nX1.SetFromHexString("6C446964AC385291F8157DBB76ACE7E791E6E51D5320BD56207E7E068A7F75BE0D48FE8272C7508C71FAAECA1C40AAA8CE9BEF62455E673D47AAC34A68E8A6B193EA423AE6DBD7B8EE15608FAB651B8B9A880C5BC94099ABE355EA155690CEDF36CDD9E576E964519D1EA240831A40C5C653C2720417D098EEFB5B79EECDAE94");
    nX2.SetFromHexString("6C446964AC385291F8157DBB76ACE7E791E6E51D5320BD56207E7E068A7F75BE0D48FE8272C7508C71FAAECA1C40AAA8CE9BEF62455E673D47AAC34A68E8A6B193EA423AE6DBD7B8EE15608FAB651B8B9A880C5BC94099ABE355EA155690CEDF36CDD9E576E964519D1EA240831A40C5C653C2720417D098EEFB5B79EECDAE940000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
    nX3 = nX2;
    nX3.SetSize(nX1.GetSize());
    cBox.Multiply(nX1, nX3, nProdMult);
    nProdOracle.Reserve(nX1.GetSize() + nX2.GetSize());
    nProdOracle.SetSize(MultOracle(nX1.GetSize(), nX3.GetSize(), nX1.GetValue(), nX3.GetValue(), nProdOracle.GetValue()));
    if (nProdMult != nProdOracle)
    {
        cBox.Subtract(nProdMult, nProdOracle, nDiff);
        printf("Product is %i DIGITs.  Diff should be 0, but is %i Digits. ", nX1.GetSize() + nX3.GetSize(), nDiff.GetSize()); nDiff.PrintHexToFile();
        for (int i = 0; i < nProdMult.GetSize(); i++) {
            if (nProdMult.GetValue()[i] != nProdOracle.GetValue()[i]) printf("%i\t%x %x\n", i, nProdMult.GetValue()[i], nProdOracle.GetValue()[i]); }
        printf("egads!\n");
        goto exit;
    }
    // first, make sure we can generate the system of equations needed to do the multiply
    for(size_t nPieces=c_nMinPieces;nPieces<c_nMaxPieces;nPieces++)
    {
        pSystemToUse = CUnsignedArithmeticHelper::GenerateSystem(nPieces);
        if(NULL == pSystemToUse)
        {
            printf("Failed to generate system of equations to execute the multiply\n");
            goto exit;
        }
    }
    // control coefs so WE decide how many pieces to use for the multiplication,
    // rather than the normal algorithm
    c_pnMultiplicationThresholds[e3By2]  = 0;
    c_pnMultiplicationThresholds[e5By3]  = 0;
    c_pnMultiplicationThresholds[e7By4]  = 0;
#if(32<=_DIGIT_SIZE_IN_BITS)
    c_pnMultiplicationThresholds[e9By5]  = 0;
#endif
    c_pnMultiplicationThresholds[e2NByN] = (DWORD) -1;
    // Now, note that chopping the problem up into LOTS of pieces requires that there be
    // LOTS of digits in the first place -- to avoid overflow problems, the subproblems
    // should all be at least 5 digits.  More for more pieces (since the coefficients
    // rise with the number of pieces).
    pValidatedProduct->Reserve(c_nMaxSize+c_nMaxSize); // make sure enough room for the product
    pTestProduct->Reserve(c_nMaxSize+c_nMaxSize+1);    // make sure enough room for the product, plus digit for buffer guard
    pX->Reserve(c_nMaxSize);
    pY->Reserve(c_nMaxSize);
    for(int nCacheChunkToTest = 1; nCacheChunkToTest<2; nCacheChunkToTest++) // start with 1: not using chunking for post step
    {
        unsigned int *pnCacheChunk;
        if(0==nCacheChunkToTest)
        {
            pnCacheChunk          = &c_nBuildBlockSizePost;
            c_nBuildBlockSizePre  = 10000; // so only looking at one cache size at a time -- bigger than anything used in this test
        }
        else
        {
            pnCacheChunk          = &c_nBuildBlockSizePre;
            c_nBuildBlockSizePost = 10000; // so only looking at one cache size at a time -- bigger than anything used in this test
        }
        for(*pnCacheChunk = 1; *pnCacheChunk<6; *pnCacheChunk = *pnCacheChunk+1)
        {
            for(size_t nPieces = c_nMinPieces; nPieces<c_nMaxPieces; nPieces++)
            {
                pSystemToUse = CUnsignedArithmeticHelper::GenerateSystem(nPieces);
                size_t nMinSize = 2*(2*nPieces-3)*sizeof(size_t)/sizeof(DIGIT); // minimum general size needed -- Z used to hold op sizes!
                printf("2n-1 by n: n=%i, pre %i, post %i -- minsize %i\n", nPieces, c_nBuildBlockSizePre, c_nBuildBlockSizePost, nMinSize);
                for(size_t i=nMinSize;i<c_nMaxSize;i++)
                {
                    // subproblems done with basic algorithm, but using 2n by n
                    // with the desired # of pieces at the top level
                    for (size_t j = 0; j < c_n2NBynSizeBreakpoints; j++)
                    {
                        c_pn2NByNBreakpoints[j] = 0;
                    }
                    c_pn2NByNBreakpoints[nPieces - 5] = i+1;
                    c_pnMultiplicationThresholds[eBasicMultiply] = i;
                    for(size_t j=i;j<c_nMaxSize;j++)
                    {
                        for(size_t k=0;k<5;k++)
                        {
                            switch(k)
                            {
                            case 0:
                                // random values
                                pX->SetRandom(i*_DIGIT_SIZE_IN_BITS);
                                pY->SetRandom(j*_DIGIT_SIZE_IN_BITS);
                                break;
                            case 1:
                                // max values
                                for(size_t n=0;n<i;n++)
                                {
                                    pX->GetValue()[n] = (DIGIT) -1;
                                }
                                for(size_t n=0;n<j;n++)
                                {
                                    pY->GetValue()[n] = (DIGIT) -1;
                                }
                                pX->SetSize(i);
                                pY->SetSize(j);
                                break;
                            case 2:
                                // min values
                                for(size_t n=0;n<i-1;n++)
                                {
                                    pX->GetValue()[n] = 0;
                                }
                                pX->GetValue()[i-1] = 1;
                                for(size_t n=0;n<j-1;n++)
                                {
                                    pY->GetValue()[n] = 0;
                                }
                                pY->GetValue()[j-1] = 1;
                                pX->SetSize(i);
                                pY->SetSize(j);
                                break;
                            case 3:
                                // mixed values
                                for(size_t n=0;n<i;n++)
                                {
                                    pX->GetValue()[n] = (DIGIT) n;
                                }
                                for(size_t n=0;n<j-1;n++)
                                {
                                    pY->GetValue()[n] = 0;
                                }
                                pY->GetValue()[j-1] = 8;
                                pX->SetSize(i);
                                pY->SetSize(j);
                                break;
                            case 4:
                                // leading 0s -- may happen as a subproblem
                                pX->SetRandom(i*_DIGIT_SIZE_IN_BITS);
                                pY->SetRandom(j*_DIGIT_SIZE_IN_BITS);
                                for(size_t nn = 1+rand()%pX->GetSize();nn<pX->GetSize();nn++)
                                {
                                    pX->GetValue()[nn] = 0;
                                }
                                for(size_t nn = 1+rand()%pY->GetSize();nn<pY->GetSize();nn++)
                                {
                                    pY->GetValue()[nn] = 0;
                                }
                                break;
                            }
                            nXSize = pX->GetSize();
                            nYSize = pY->GetSize();
                            pValidatedProduct->SetSize(MultOracle(nXSize,
                                                                  nYSize,
                                                                  pX->GetValue(),
                                                                  pY->GetValue(),
                                                                  pValidatedProduct->GetValue()));
                            // set buffer guard for test product
                            pTestProduct->GetValue()[nXSize+nYSize] = TEST_BUFFERGUARD;
                            // set buffer guard for the workspace
                            nMemoryNeeds                            = MultiplyMemoryNeeds(pX->GetSize(),pY->GetSize());
                            pWorkspace[nMemoryNeeds]                = TEST_BUFFERGUARD;
#if _CollectDetailedTimingData
                            dwTimestamp = s_Timer.GetMicroseconds();
                            MultUBackend(nXSize,
                                         nYSize,
                                         pX->GetValue(),
                                         pY->GetValue(),
                                         pTestProduct->GetValue(),
                                         pWorkspace,
                                         dwTimestamp,
                                         &nZSize);
#else
                            MultUBackend(nXSize,
                                         nYSize,
                                         pX->GetValue(),
                                         pY->GetValue(),
                                         pTestProduct->GetValue(),
                                         pWorkspace,
                                         &nZSize);
#endif
                            if(TEST_BUFFERGUARD != pTestProduct->GetValue()[nXSize+nYSize])
                            {
                                printf("2N-1 by 2N multiply overran product buffer\n");
                                goto exit;
                            }
                            if(TEST_BUFFERGUARD != pWorkspace[nMemoryNeeds])
                            {
                                printf("2N-1 by 2N multiply overran workspace buffer\n");
                                goto exit;
                            }
                            if(0==pTestProduct->GetValue()[nXSize+nYSize-1])
                            {
                                pTestProduct->SetSize(nXSize+nYSize-1);
                            }
                            else
                            {
                                pTestProduct->SetSize(nXSize+nYSize);
                            }
                            if(bVerbose || *pTestProduct != *pValidatedProduct)
                            {
                                printf("Pieces, sizes: %i, %i x %i\n",nPieces,i,j);
                                printf("X:\n");
                                pX->PrintHexToFile();
                                printf("\nY:\n");
                                pY->PrintHexToFile();
                                printf("\nComputed product: size %i\n", pTestProduct->GetSize());
                                pTestProduct->PrintHexToFile();
                                printf("\n");
                                if(*pTestProduct != *pValidatedProduct)
                                {
                                    printf("Expected product: size %i\n", pValidatedProduct->GetSize());
                                    pValidatedProduct->PrintHexToFile();
                                    for(int jj=0;jj<pTestProduct->GetSize();jj++)
                                    {
                                        if(pTestProduct->GetValue()[jj]!=pValidatedProduct->GetValue()[jj]) printf("Differ at digit %i\n",jj);
                                    }
                                    goto exit;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // and some tests for extreme numbers of pieces
    // first, try generating the systems for 5 through 128 pieces.  Note that the system is maintained by the back-end -- discarding it
    // does NOT cause a memory leak.
    printf("Testing large numbers of pieces: 5 through %i (inclusive)\n", c_nPiecesToTry);
    for(int nPieces=5; nPieces<=c_nPiecesToTry; nPieces++)
    {
        dwTime = ::GetTickCount();
        SSystemData *pSystem = GenerateSystem(nPieces);
        printf("Time to generate system for %i pieces: %i milliseconds (max divisor size %i DIGITs, max PI size %i, max RI size %i)\n",
               nPieces,
               ::GetTickCount()-dwTime,
               pSystem->m_nMaxDivisorSize,
               pSystem->m_nMaxSizePI,
               pSystem->m_nMaxSizeRI);
    }
    nX1.SetRandom(_DIGIT_SIZE_IN_BITS*c_nFinalTestDIGITs);
    nX2.SetRandom(_DIGIT_SIZE_IN_BITS*c_nFinalTestDIGITs);
    nProdMult.Reserve(nX1.GetSize() + nX2.GetSize() + 1);
    nProdMult.GetValue()[nX1.GetSize() + nX2.GetSize()] = TEST_BUFFERGUARD;
    nProdOracle.Reserve(nX1.GetSize() + nX2.GetSize());
    // now, try the actual multiplications
    dwTime = ::GetTickCount();
    nProdOracle.SetSize(MultOracle(nX1.GetSize(), nX2.GetSize(), nX1.GetValue(), nX2.GetValue(), nProdOracle.GetValue()));
    printf("Time for oracle to do multiply (in milliseconds): %u\n",::GetTickCount()-dwTime);
#if _CollectDetailedTimingData
    dwTimestamp = s_Timer.GetMicroseconds();
#endif
    for(int nPieces=5; nPieces<=c_nPiecesToTry; nPieces++)
    {
        dwTime = ::GetTickCount();
#if _CollectDetailedTimingData
        MultU2NByN(nX1.GetSize(), nX2.GetSize(), nX1.GetValue(), nX2.GetValue(), nProdMult.GetValue(), GenerateSystem(nPieces), pWorkspace, dwTimestamp);
#else
        MultU2NByN(nX1.GetSize(), nX2.GetSize(), nX1.GetValue(), nX2.GetValue(), nProdMult.GetValue(), GenerateSystem(nPieces), pWorkspace);
#endif
        dwTime = ::GetTickCount() - dwTime;
        printf("Time to multiply two %u-DIGIT numbers using general recursive algorithm with %u pieces: %u\n", c_nFinalTestDIGITs, nPieces, dwTime);
        nProdMult.SetSize(nX1.GetSize() + nX2.GetSize());
        if(0==nProdMult.GetValue()[nProdMult.GetSize()-1]) nProdMult.SetSize(nProdMult.GetSize()-1);
        if(TEST_BUFFERGUARD != nProdMult.GetValue()[nX1.GetSize()+nX2.GetSize()])
        {
            printf("Overran product space\n");
        }
        if (nProdMult != nProdOracle)
        {
            printf("2n by n multiplication failed for %u pieces\n", nPieces);
            printf("Oracle: "); nProdOracle.PrintHexToFile();
            printf("2NByN:  "); nProdMult.PrintHexToFile();
            printf("error at DIGIT ");
            for(int i=0; i<nProdOracle.GetSize(); i++)
            {
                if (nProdMult.GetValue()[i] != nProdOracle.GetValue()[i]) printf("%i ", i);
            }
            printf("\n");
            goto exit;
        }
    }
    bTestWorked = true;
exit:
    delete pX;
    delete pY;
    delete pValidatedProduct;
    delete pTestProduct;
    delete szXHex;
    delete szYHex;
    free(pWorkspace);
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestModBy2NPlus1(bool bVerbose)
{
    CBigInteger        *pTwoTo2N,*pOnePlusTwoToN;
    CBigIntegerForTest nX,nY,nProd,nSum;
    CArithmeticBox     cBox;
    nSum.Reserve(2002);
    nProd.Reserve(2002);
    DIGIT *pWorkspace = new DIGIT[100000];
    bool  bTestWorked = false;
    for(size_t n=1;n<1000;n++)
    {
        printf("Base size: %i\n",n);
        pTwoTo2N       =  NewBigIntegerOnePlus2ToN(2*n);
        pOnePlusTwoToN =  NewBigIntegerOnePlus2ToN(n);
        *pTwoTo2N      -= 1;
        // Note that ModBy2nPlus1 assumes the value being modded is at
        // most 2^(2n), and has leading 0s if smaller.  So make sure
        // we only pay attention to that range.
        // First, check the upper limit: 1 == 2^(2n) mod (1+2^n)
        ModBy2nPlus1(pTwoTo2N->GetValue(),nProd.GetValue(),n);
        if(1!=nProd.GetValue()[0])
        {
            printf("2^(2n) did not go to 1\n");
            goto exit;
        }
        for(size_t i=1;i<n+1;i++)
        {
            if(0!=nProd.GetValue()[i])
            {
                printf("2^(2n) did not go to 1\n");
                goto exit;
            }
        }
        // next, make a few more general tests
        for(size_t m=1;m<=n;m++)
        {
            nX.SetRandom(m*_DIGIT_SIZE_IN_BITS);
            // run twice: once where the divide is exact; then, with remainder
            for(size_t j=0;j<2;j++)
            {
                for(size_t i=0;i<1+2*n;i++)
                {
                    nSum.GetValue()[i] = 0;
                }
                if(0==j)
                {
                    // no remainder case
                    nY.SetSize(0);
                }
                else
                {
                    // remainder desired
                    nX -= 1;
                    nY.SetRandom(m*_DIGIT_SIZE_IN_BITS);
                }
#if _CollectDetailedTimingData
                DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
                MultUBackend(nX.GetSize(),
                             pOnePlusTwoToN->GetSize(),
                             nX.GetValue(),
                             pOnePlusTwoToN->GetValue(),
                             nProd.GetValue(),
                             pWorkspace,
                             dwTimestamp);
#else
                MultUBackend(nX.GetSize(),
                             pOnePlusTwoToN->GetSize(),
                             nX.GetValue(),
                             pOnePlusTwoToN->GetValue(),
                             nProd.GetValue(),
                             pWorkspace);
#endif
                if(0==nProd.GetValue()[nX.GetSize()+pOnePlusTwoToN->GetSize()-1])
                {
                    nProd.SetSize(nX.GetSize()+pOnePlusTwoToN->GetSize()-1);
                }
                else
                {
                    nProd.SetSize(nX.GetSize()+pOnePlusTwoToN->GetSize());
                }
                nSum.SetSize(Add(nProd.GetSize(),
                                 nY.GetSize(),
                                 nProd.GetValue(),
                                 nY.GetValue(),
                                 nSum.GetValue()));
                ModBy2nPlus1(nSum.GetValue(),nProd.GetValue(),n);
                // get the size of the mod value
                size_t i = n;
                while(i!=0 && 0==nProd.GetValue()[i])
                {
                    i--;
                }
                if(i!=0 || 0!=nProd.GetValue()[i])
                {
                    i++;
                }
                nProd.SetSize(i);
                // the value in nProd should be equal to y
                if(nProd != nY)
                {
                    printf("oops..\n");
                    printf("Test ModBy2nPlus1 failed: expected final result to be\n");
                    nY.PrintHexToFile();
                    printf("Instead, got\n");
                    nProd.PrintHexToFile();
                    delete pTwoTo2N;
                    delete pOnePlusTwoToN;
                    goto exit;
                }
            }
        }
        delete pTwoTo2N;
        delete pOnePlusTwoToN;
    }
    bTestWorked = true;
exit:
    delete pWorkspace;
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestMult2toMmodOnePlus2toN(bool bVerbose)
{
    const size_t       c_nMaxBaseSize = 100;
    const size_t       m_nMaxBitShiftMultiplier = 5;
    CArithmeticBox     cBox;
    CBigInteger        *pOnePlusTwoToN;
    CBigIntegerForTest nX,nProd,nSum;
    SBitShift          nShift;
    size_t             nDivSize,nRemainderSize;
    DIGIT              *pWorkspace = new DIGIT[1000000];
    bool               bTestWorked = false;
    nProd.Reserve(c_nMaxBaseSize*2*(1 + m_nMaxBitShiftMultiplier)+1);
    nSum.Reserve(c_nMaxBaseSize*2*(1 + m_nMaxBitShiftMultiplier)+1);
    nX.Reserve(c_nMaxBaseSize);
    for(size_t n=60; n<c_nMaxBaseSize;n++)
    {
        printf("Base size: %i\n",n);
        pOnePlusTwoToN = NewBigIntegerOnePlus2ToN(n);
        for(size_t m=0;m<=n*5*(sizeof(DIGIT)<<3);m++)
        {
            for(size_t k=0;k<3;k++)
            {
                // first, compute using the generic procedures
                CBigInteger *pTwoToMBits = NewBigIntegerOnePlus2ToN(m/_DIGIT_SIZE_IN_BITS);
                if(0<m/_DIGIT_SIZE_IN_BITS)
                {
                    *pTwoToMBits -= 1;
                }
                nSum.SetSize(1);
                nSum.GetValue()[0] = (1<<(m%_DIGIT_SIZE_IN_BITS));
#if _CollectDetailedTimingData
                DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
                MultUBackend(nSum.GetSize(),
                             pTwoToMBits->GetSize(),
                             nSum.GetValue(),
                             pTwoToMBits->GetValue(),
                             nProd.GetValue(),
                             pWorkspace,
                             dwTimestamp);
#else
                MultUBackend(nSum.GetSize(),
                             pTwoToMBits->GetSize(),
                             nSum.GetValue(),
                             pTwoToMBits->GetValue(),
                             nProd.GetValue(),
                             pWorkspace);
#endif
                nProd.SetSize((0==nProd.GetValue()[nSum.GetSize()+pTwoToMBits->GetSize()-1]) ? nSum.GetSize()+pTwoToMBits->GetSize()-1 :
                                                                                               nSum.GetSize()+pTwoToMBits->GetSize());
                // nProd is now set to 2^m
                if(0==k)
                {
                    // general case
                    nX.SetRandom(_DIGIT_SIZE_IN_BITS*n);
                    for(size_t i=nX.GetSize();i<n+1;i++)
                    {
                        nX.GetValue()[i] = 0;
                    }
                }
                else if(1==k)
                {
                    // corner case
                    nX.SetSize(n+1);
                    for(size_t i=0;i<n;i++)
                    {
                        nX.GetValue()[i] = 0;
                    }
                    nX.GetValue()[n] = 1;
                }
                else
                {
                    // another corner case
                    nX.SetSize(n);
                    for(size_t i=0;i<n;i++)
                    {
                        nX.GetValue()[i] = (DIGIT) -1;
                    }
                    nX.GetValue()[n] = 0;
                }
#if _CollectDetailedTimingData
                dwTimestamp = s_Timer.GetMicroseconds();
                MultUBackend(nProd.GetSize(),
                             nX.GetSize(),
                             nProd.GetValue(),
                             nX.GetValue(),
                             nSum.GetValue(),
                             pWorkspace,
                             dwTimestamp);
#else
                MultUBackend(nProd.GetSize(),
                             nX.GetSize(),
                             nProd.GetValue(),
                             nX.GetValue(),
                             nSum.GetValue(),
                             pWorkspace);
#endif
                nSum.SetSize((0 == nSum.GetValue()[nProd.GetSize() + nX.GetSize() - 1]) ? nProd.GetSize() + nX.GetSize() - 1 :
                                                                                          nProd.GetSize() + nX.GetSize());
                // nSum is now set to x*2^m
                Divide(nSum.GetSize(),
                       pOnePlusTwoToN->GetSize(),
                       nDivSize,
                       nRemainderSize,
                       nSum.GetValue(),
                       pOnePlusTwoToN->GetValue(),
                       nProd.GetValue(),
                       pWorkspace);
                // nProd now contains (x*2^m)/(1+2^n); nSum contains (x*2^m)%(1+2^n)
                nProd.SetSize(nDivSize);
                nSum.SetSize(nRemainderSize);
                // nSum has the mod in it now.  Recompute using the specialized proceedure, and compare
                nShift.m_nBitShift   = m%_DIGIT_SIZE_IN_BITS;
                nShift.m_nDigitShift = m/_DIGIT_SIZE_IN_BITS;
                Mult2toMmodOnePlus2toN(nX.GetValue(),n,nShift,nProd.GetValue());
                // compare the two and make sure they match
                size_t i = n;
                while(0==nProd.GetValue()[i] && 0 != i--)
                {
                    ;
                }
                nProd.SetSize(i+1);
                if(nSum != nProd)
                {
                    printf("Mult2toMmodOnePlus2toN failed: with a shift of %i digits, %i bits:\n", nShift.m_nDigitShift, nShift.m_nBitShift);
                    nX.PrintHexToFile();
                    printf("Got:\n");
                    nProd.PrintHexToFile();
                    printf("expected:\n");
                    nSum.PrintHexToFile();
                    for (int i=0; i<nProd.GetSize(); i++)
                    {
                        if (nProd.GetValue()[i] != nSum.GetValue()[i])
                        {
                            printf("Differ in digit %i: got %i; expected %i\n", i, nProd.GetValue()[i], nSum.GetValue()[i]);
                        }
                    }
                    delete pOnePlusTwoToN;
                    delete pTwoToMBits;
                    goto exit;
                }
                delete pTwoToMBits;
            }
        }
        delete pOnePlusTwoToN;
    }
    bTestWorked = true;
exit:
    return bTestWorked;
}

bool FFTForwardBackMatchesOriginal(DIGIT *pOriginal, DIGIT *pFFT_Inverse, size_t nOriginalSize, size_t nFFTLength, size_t nFieldSize)
{
    int  i, j, k;
    bool bEqual = true;
    // first part of FFT_Inverse should match the original value (with padding 0s)
    // first, the first full-sized pieces
    k = 0;
    for(i=0;i<nOriginalSize/((nFieldSize>>1)-1);i++)
    {
        for(j=0;j<(nFieldSize>>1)-1;j++)
        {
            if(pOriginal[k++] != pFFT_Inverse[i*(nFieldSize+1)+j])
            {
                bEqual = false;
                break;
            }
        }
        if(!bEqual)
        {
            break;
        }
        for(;j<nFieldSize+1;j++)
        {
            if(0 != pFFT_Inverse[i*(nFieldSize+1)+j])
            {
                bEqual = false;
                break;
            }
        }
        if(!bEqual)
        {
            break;
        }
    }
    if(bEqual)
    {
        // check the last, smaller piece
        if(nOriginalSize != i*((nFieldSize>>1)-1))
        {
            j = 0;
            for(;k<nOriginalSize;k++)
            {
                if(pOriginal[k] != pFFT_Inverse[i*(nFieldSize+1)+j])
                {
                    bEqual = false;
                    break;
                }
                j++;
            }
        }
        // the rest of the FFT_Inverse should be 0
        if(bEqual)
        {
            for(;j<nFieldSize+1;j++)
            {
                if(0 != pFFT_Inverse[i*(nFieldSize+1)+j])
                {
                    bEqual = false;
                    break;
                }
            }
            if(bEqual)
            {
                i++;
                // rest of FFT_Inverse should be 0
                for(;i<nFFTLength;i++)
                {
                    for(j=0;j<nFieldSize+1;j++)
                    {
                        if(0 != pFFT_Inverse[i*(nFieldSize+1)+j])
                        {
                            bEqual = false;
                            break;
                        }
                    }
                }
            }
        }
    }
    return bEqual;
}

bool CArithmeticCorrectnessTester::TestFFT(bool bVerbose)
{
#if(16==_DIGIT_SIZE_IN_BITS)
    const size_t       c_MaxElementSizeInDigits = 4096;
#else
    // my machine runs out of memory for the basic FFT crosscheck with large digits with 4096 of them
    const size_t       c_MaxElementSizeInDigits = 2048;
#endif
    CBigIntegerForTest nX,nFFT,nFFT_Inverse,nFFT2,nFFT_Inverse2;
    size_t             nFFTLength,nComputeSize,nChunkSize,nFFTMemoryNeeds,nFFTSize;
    SBitShift          nRootUnity;
    size_t             i,j,k;
    DIGIT              *pWorkspace = new DIGIT[2000000000];
    bool               bEqual;
    bool               bTestWorked = false;
    for(size_t nFieldSize = 4; nFieldSize<=c_MaxElementSizeInDigits; nFieldSize = nFieldSize<<1)
    {
        nRootUnity.m_nBitShift       = 0;
        nRootUnity.m_nDigitShift     = nFieldSize;
        nFFTLength                   = 2;
        do
        {
            nChunkSize = (nFieldSize>>1)-1;
            // set up the number whose FFT/FFT inverse we wish to compute
            nFFTSize =  nFFTLength*nFieldSize;
            nX.Reserve(nFFTSize);
            nFFTSize += nFFTLength;
            nFFT.Reserve(nFFTSize);
            nFFT.SetSize(nFFTSize);
            nFFT_Inverse.Reserve(nFFTSize);
            nFFT_Inverse.SetSize(nFFTSize);
            nFFT2.Reserve(nFFTSize);
            nFFT2.SetSize(nFFTSize);
            nFFT_Inverse2.Reserve(nFFTSize);
            nFFT_Inverse2.SetSize(nFFTSize);
            DIGIT *pToCompute    = nX.GetValue();
            DIGIT *pFFT          = nFFT.GetValue();
            DIGIT *pFFT_Inverse  = nFFT_Inverse.GetValue();
            DIGIT *pFFT2         = nFFT2.GetValue();
            DIGIT *pFFT_Inverse2 = nFFT_Inverse2.GetValue();
            nComputeSize    = 1+rand()%((nFFTLength>>1)*nChunkSize);
            for(size_t nTest=0;nTest<3;nTest++)
            {
                // note that basic FFT mult uses more memory -- but we don't care, since it is only
                // used as a cross-check with the version we DO use
                if(0==nTest)
                {
                    for(i=0;i<nComputeSize;i++)
                    {
                        pToCompute[i] = i+1;
                    }
                }
                else if(1==nTest)
                {
                    for(i=0;i<nComputeSize;i++)
                    {
                        pToCompute[i] = (DIGIT) -1;
                    }
                }
                else
                {
                    for(i=0;i<nComputeSize-1;i++)
                    {
                        pToCompute[i] = 0;
                    }
                    pToCompute[i] = 1;
                }
                nX.SetSize(nComputeSize);
                DWORD64 nFFTTime = s_Timer.GetMicroseconds();
                // if we take the FFT, then apply the inverse, we should be back where we started.  Otherwise there is a
                // Problem.
                ExpandBaseNumberForFFT(pToCompute,nComputeSize,nChunkSize,nFieldSize,nFFTLength,pWorkspace);
                FFT_basic(pWorkspace,pFFT,nFFTLength,nFieldSize,nRootUnity,nFieldSize+1,pWorkspace+nFFTLength*(nFieldSize+1));
                DWORD64 nFFTInverseTime = s_Timer.GetMicroseconds();
                nFFTTime = nFFTInverseTime - nFFTTime;
                FFT_Inverse_basic(pFFT,
                                  nFFTLength,
                                  nRootUnity,
                                  nFieldSize,
                                  pFFT_Inverse,
                                  pWorkspace);
                nFFTInverseTime = s_Timer.GetMicroseconds()-nFFTInverseTime;
                bEqual = FFTForwardBackMatchesOriginal(pToCompute, pFFT_Inverse, nComputeSize, nFFTLength, nFieldSize);
                printf("Length %i Field %i\tBit shift %i Digit shift %i\n",nFFTLength,nFieldSize,nRootUnity.m_nBitShift,nRootUnity.m_nDigitShift);
                printf("  Basic: forward:     %I64u microseconds\tInverse: %I64u microseconds\n",nFFTTime,nFFTInverseTime);
                if(!bEqual)
                {
                    fprintf(stderr,"FFT/FFT inverse failure for FFT length %i, element size %i:\n",nFFTLength,nFieldSize);
                    fprintf(stderr,"Base:\n");
                    nX.PrintHexToFile();
                    fprintf(stderr,"FFT:\n");
                    nFFT.PrintHexToFile();
                    fprintf(stderr,"FFT inverse:\n");
                    nFFT_Inverse.PrintHexToFile();
                    goto exit;
                }
                // repeat for optimized versions
                nFFTMemoryNeeds             = FFTMultiplyMemoryNeeds(nFFTLength, nFieldSize, false);
                pWorkspace[nFFTMemoryNeeds] = TEST_BUFFERGUARD;
                nFFTTime                    = s_Timer.GetMicroseconds();
                FFT(pToCompute,pFFT2,nComputeSize,nChunkSize,nChunkSize,nFFTLength,nFieldSize,nRootUnity,pWorkspace);
                nFFTInverseTime = s_Timer.GetMicroseconds();
                nFFTTime        = nFFTInverseTime-nFFTTime;
                if(0!=memcmp(pFFT,pFFT2,nFFTLength*(nFieldSize+1)*sizeof(DIGIT)))
                {
                    printf("old/new FFT mismatch:\n");
                    printf("Base:\n");
                    nFFT.PrintHexToFile();
                    printf("Optimized:\n");
                    nFFT2.PrintHexToFile();
                    goto exit;
                }
                if(TEST_BUFFERGUARD != pWorkspace[nFFTMemoryNeeds])
                {
                    printf("Um...  miscalculated necessary memory\n");
                    goto exit;
                }
                nFFTInverseTime = s_Timer.GetMicroseconds();
                FFT_Inverse(pFFT2,
                            pFFT_Inverse2,
                            nFFTLength,
                            nRootUnity,
                            nFieldSize,
                            pWorkspace);
                nFFTInverseTime = s_Timer.GetMicroseconds()-nFFTInverseTime;
                printf("  Optimized: forward: %I64u microseconds\tInverse: %I64u microseconds\n",nFFTTime,nFFTInverseTime);
                bEqual = (0==memcmp(pFFT_Inverse,pFFT_Inverse2,nFFTLength*(1+nFieldSize)));
                if(!bEqual)
                {
                    printf("FFT inverse failure for optimized FFT length %i, element size %i:\n",nFFTLength,nFieldSize);
                    printf("Base FFT inverse:\n");
                    nFFT_Inverse.PrintHexToFile();
                    printf("Optimized FFT inverse:\n");
                    nFFT_Inverse2.PrintHexToFile();
                    goto exit;
                }
            }
            nFFTLength = nFFTLength<<1;
        }
        while(nRootUnity.Halve());
    }
    bTestWorked = true;
exit:
    delete pWorkspace;
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestFFTMult(bool bVerbose)
{
    const size_t       c_nMinOversizedSize = 0x2000000/sizeof(DIGIT), c_nMaxOversizedSize = 0x10000000/sizeof(DIGIT);
    const size_t       c_nMaxFFTTest = 2000;
    CArithmeticBox     cBox;
    CBigIntegerForTest nX,nY,nProd,nProdComputed;
    size_t             nXBits,nYBits,nFFTMemoryNeeds;
    DIGIT *pnWorkspace = (DIGIT *) malloc(sizeof(DIGIT)*100000);
    bool  bTestWorked  = false;
    // Next, check fft & fft inverse
    nProd.Reserve(3*c_nMaxFFTTest+1);
    nProdComputed.Reserve(3*c_nMaxFFTTest+1);
    nX.Reserve(c_nMaxFFTTest);
    nY.Reserve(c_nMaxFFTTest*2);
    // note FFT needs base operand size at least 5!
    for(size_t i=5;i<=c_nMaxFFTTest;i+=5)
    {
        nX.SetSize(i);
        printf("Multiplication base size: %i (max %i)\n",i,c_nMaxFFTTest);
        for(size_t kk=i;kk<2*i;kk++)
        {
            nY.SetSize(kk);
            nFFTMemoryNeeds                = FFTMultiplyMemoryNeeds(nX.GetSize(), nY.GetSize(), false);
            pnWorkspace[nFFTMemoryNeeds]   = TEST_BUFFERGUARD;
            nProdComputed.GetValue()[i+kk] = TEST_BUFFERGUARD;
            for(int jj=0;jj<5;jj++)
            {
                // three basic tests: simple to manually check answer
                if(0==jj)
                {
                    for(size_t j=0;j<i;j++)
                    {
                        nX.GetValue()[j] = 1;
                    }
                    for(size_t j=0;j<kk;j++)
                    {
                        nY.GetValue()[j] = 1;
                    }
                }
                else if(1==jj)
                {
                    for(size_t j=0;j<i;j++)
                    {
                        nX.GetValue()[j] = (DIGIT) -1;
                    }
                    for(size_t j=0;j<kk;j++)
                    {
                        nY.GetValue()[j] = (DIGIT) -1;
                    }
                }
                else if(2==jj)
                {
                    for(size_t j=0;j<i-1;j++)
                    {
                        nX.GetValue()[j] = 0;
                    }
                    nX.GetValue()[i-1] = 1;
                    for(size_t j=0;j<kk-1;j++)
                    {
                        nY.GetValue()[j] = 0;
                    }
                    nY.GetValue()[kk-1] = 1;
                }
                else if (3 == jj)
                {
                    // lots of 0s vs full
                    for(size_t j=0;j<i;j++)
                    {
                        nX.GetValue()[j] = (DIGIT) -1;
                    }
                    for(size_t j=0;j<kk-1;j++)
                    {
                        nY.GetValue()[j] = 0;
                    }
                    nY.GetValue()[kk-1] = 1;
                }
                else
                {
                    // more general-case.  Note that Y must have at least as many digits as X!
                    nXBits = i*sizeof(DIGIT)<<3;
                    nYBits = kk*sizeof(DIGIT)<<3;
                    do
                    {
                        nX.SetRandom(nXBits);
                        nY.SetRandom(nYBits);
                    }
                    while(nY.GetSize()<nX.GetSize());
                }
                cBox.Multiply(nX,nY,nProd);
                nProd.CheckBufferguard();
                nProdComputed.GetValue()[i+kk] = TEST_BUFFERGUARD;
#if _CollectDetailedTimingData
                DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
                MultFFT(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProdComputed.GetValue(),pnWorkspace,dwTimestamp);
#else
                MultFFT(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProdComputed.GetValue(),pnWorkspace);
#endif
                nProdComputed.CheckBufferguard();
                if(TEST_BUFFERGUARD != nProdComputed.GetValue()[i+kk])
                {
                    printf("Wrote too far in the product!\n");
                    goto exit;
                }
                if(pnWorkspace[nFFTMemoryNeeds] != TEST_BUFFERGUARD)
                {
                    printf("Overran allocated workspace memory\n");
                    goto exit;
                }
                nProdComputed.SetSize(nProd.GetSize());
                if(nProd != nProdComputed)
                {
                    printf("unexpected product resulted!\n");
                    printf("X:\n");
                    nX.PrintHexToFile();
                    printf("Y:\n");
                    nY.PrintHexToFile();
                    printf("Product:\n");
                    nProd.PrintHexToFile();
                    printf("Computed:\n");
                    nProdComputed.PrintHexToFile();
                    goto exit;
                }
            }
        }
    }
    // and some really big multiplies with optimization threshold -- because I've seen errors there when small problems work fine.
    // These are big -- run tests in retail unless you really need debug.  Step out for coffee.
    for(size_t nSize=c_nMinOversizedSize; nSize<=c_nMaxOversizedSize; nSize *= 2)
    {
        printf("Checking FFT mult for two %I64u-DIGIT numbers\n", nSize);
        int nMaxIterations = (c_nMinOversizedSize==nSize) ? 4 : 1;
        for(int i=0; i<nMaxIterations; i++)
        {
            ResetThresholdsForOptimization();
            nX.SetRandom(nSize*_DIGIT_SIZE_IN_BITS);
            nY.SetRandom(nSize*_DIGIT_SIZE_IN_BITS);
            nProd.Reserve(nSize+nSize+1);
            nProdComputed.Reserve(nSize+nSize+1);
            nProdComputed.m_pnValue[nSize+nSize] = TEST_BUFFERGUARD;
            nProd.m_pnValue[nSize+nSize]         = TEST_BUFFERGUARD;
            c_pnMultiplicationThresholds[e2NByN] = nSize-1; // force single level of FFT
            nFFTMemoryNeeds                      = FFTMultiplyMemoryNeeds(nX.GetSize(), nY.GetSize(), false);
            cBox.m_Workspace.Reserve(nFFTMemoryNeeds + 1);
            cBox.m_Workspace.GetSpace()[nFFTMemoryNeeds] = TEST_BUFFERGUARD;
            cBox.Multiply(nX,nY,nProdComputed);
            nProdComputed.CheckBufferguard();
            if (cBox.m_Workspace.GetSpace()[nFFTMemoryNeeds] != TEST_BUFFERGUARD)
            {
                printf("FFT multiply overran allocated workspace memory for FFT multiply\n");
                goto exit;
            }
            if(nProdComputed.m_pnValue[nSize+nSize] != TEST_BUFFERGUARD)
            {
                printf("Overran allocated product space for FFT\n");
                goto exit;
            }
            // now, force non-FFT
            c_pnMultiplicationThresholds[e2NByN] = 2000000000; // force 2nby2 instead of fft
            nFFTMemoryNeeds                      = MultiplyMemoryNeeds(nX.GetSize(), nY.GetSize());
            cBox.m_Workspace.Reserve(nFFTMemoryNeeds + 1);
            cBox.m_Workspace.GetSpace()[nFFTMemoryNeeds] = TEST_BUFFERGUARD;
            cBox.Multiply(nX,nY,nProd);
            nProd.CheckBufferguard();
            if (cBox.m_Workspace.GetSpace()[nFFTMemoryNeeds] != TEST_BUFFERGUARD)
            {
                printf("FFT multiply overran allocated workspace memory for normal multiply\n");
                goto exit;
            }
            if (nProd.m_pnValue[nSize + nSize] != TEST_BUFFERGUARD)
            {
                printf("Overran allocated product space for normal multiply\n");
                goto exit;
            }
            if (nProd != nProdComputed)
            {
                printf("oh dear oh dear oh dear!  Products differ at DIGITs ");
                for(size_t i=0; i<nProd.GetSize();i++)
                {
                    if (nProd.GetValue()[i] != nProdComputed.GetValue()[i]) printf("%u ", i);
                }
                printf("\n");
                goto exit;
            }
        }
    }
    bTestWorked = true;
exit:
    free(pnWorkspace);
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestSquare()
{
    CArithmeticBox        cBox;
    CBigIntegerForTest    nX, nValidatedProduct, nTestProduct, nAdd;
    size_t                nProductSize;
    const int             c_nMaxSize   = 300;
    bool                  bTestWorked  = false;
    DIGIT                 *pnWorkspace = (DIGIT *) malloc(sizeof(DIGIT)*20000); // plenty for this test, I hope
    ResetThresholdsForTest();
    nX.Reserve(c_nMaxSize);
    c_pnSquareThresholds[e2NByN]                 = c_nMaxSize + 1;
    c_pnMultiplicationThresholds[eBasicMultiply] = c_nMaxSize + 1; // only used by 3by2 -- just make sure not doing anything silly with sub-multiplications
    // Then, test the larger multiplication algorithms against the oracle
    for(int nAlgorithm=1; nAlgorithm<eNumMultiplyAlgorithms; nAlgorithm++)
    {
        for(size_t i=20;i<=c_nMaxSize;i++)
        {
            if (c_nMaxSize == i) i = 500; // try big value
            printf("%s: %ix%i\n", GetMultiplicationAlgorithmName((EMultiplyAlgorithm) nAlgorithm), i, i);
            for (int nTrials=0; nTrials<100; nTrials++)
            {
                int nSeed = rand();
                srand(nSeed);
                for (size_t k=0; k<5; k++)
                {
                    if (0 != nTrials && 0 != k) continue; // no need to try the fixed problems repeatedly
                    switch (k)
                    {
                    case 0:
                        // random values
                        nX.SetRandom(i*_DIGIT_SIZE_IN_BITS);
                        break;
                    case 1:
                        // max values
                        for (size_t n=0; n<i; n++)
                        {
                            nX.GetValue()[n] = (DIGIT)-1;
                        }
                        nX.SetSize(i);
                        break;
                    case 2:
                        // min values
                        for (size_t n=0; n<i-1; n++)
                        {
                            nX.GetValue()[n] = 0;
                        }
                        nX.GetValue()[i - 1] = 1;
                        nX.SetSize(i);
                        break;
                    case 3:
                        // mixed values
                        for (size_t n=0; n<i/2; n++)
                        {
                            nX.GetValue()[n] = 0;
                        }
                        for (size_t n =i/2; n<i; n++)
                        {
                            nX.GetValue()[n] = (DIGIT) -1;
                        }
                        nX.SetSize(i);
                        break;
                    case 4:
                        // sparse values
                        size_t n = 0;
                        for (; n<i-1; n++)
                        {
                            nX.GetValue()[n] = (DIGIT) (n&1);
                        }
                        nX.GetValue()[n] = 1;
                        nX.SetSize(i);
                    }
                    size_t nXSize = nX.GetSize();
                    if (0<nX.GetSize())
                    {
                        nValidatedProduct.Reserve(nXSize + nXSize);
                        nTestProduct.Reserve(nXSize + nXSize);
                        nValidatedProduct.SetSize(CUnsignedArithmeticHelper::MultOracle(nXSize,
                                                                                        nXSize,
                                                                                        nX.GetValue(),
                                                                                        nX.GetValue(),
                                                                                        nValidatedProduct.GetValue()));
                        c_pnSquareThresholds[eBasicMultiply] = nXSize;
                        for(int ii=0; ii<nAlgorithm; ii++) c_pnSquareThresholds[ii] = nXSize;
                        c_pnSquareThresholds[nAlgorithm] = nXSize+1;
                        int nMemoryNeeded = SquareMemoryNeeds(nXSize, nXSize);
                        pnWorkspace[nMemoryNeeded] = TEST_BUFFERGUARD;
                        Square(nXSize, nX.GetValue(), nTestProduct.GetValue(), pnWorkspace);
                        if (TEST_BUFFERGUARD != pnWorkspace[nMemoryNeeded])
                        {
                            printf("Overflowed supposed memory needs for %s, size %ix%i type %i\n",
                                   GetMultiplicationAlgorithmName((EMultiplyAlgorithm) nAlgorithm),
                                   nXSize,
                                   nXSize,
                                   k);
                            goto exit;
                        }
                        nProductSize = nXSize + nXSize;
                        if (0 == nTestProduct.GetValue()[nProductSize - 1])
                        {
                            nProductSize--;
                        }
                        nTestProduct.SetSize(nProductSize);
                        if (nTestProduct != nValidatedProduct)
                        {
                            printf("Expected product:\n");
                            nValidatedProduct.PrintHexToFile();
                            printf("\nComputed product:\n");
                            nTestProduct.PrintHexToFile();
                            printf("\n");
                            printf("Multiply test failed: square algorithm %i, size %i type %i\n",
                                    nAlgorithm,
                                    nXSize,
                                    k);
                            goto exit;
                        }
                    }
                }
            }
        }
    }
    bTestWorked = true;
exit:
    free(pnWorkspace);
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestPowerModulus(bool bVerbose)
{
    const int          c_nIterations = 10; // more would be nice, but the brute-force validation is Really Slow
    CBigIntegerForTest nX, nY, nZ, nPowerModulus, nExpectedPowerModulus, nFoo, nThrowAwayValue;
    DIGIT              *pnWorkspace = (DIGIT *) malloc (sizeof(DIGIT)*10000000); // should be ample for the test
    size_t             nPowerModulusSize;
    CArithmeticBox     cBox;
    bool               bTestWorked = false;
    DWORD64            dw64Timestamp1,dw64Timestamp2,dw64Timestamp3,dw64Timestamp4;
    size_t             nPowerModulusWorkspaceMemoryNeeds;
    // perf test here, just because
    nX.SetRandom(16384);
    nY.SetRandom(16384);
    nZ.SetRandom(16384);
    printf("Power modulus test.  First, a perf check\n");
    nPowerModulus.Reserve(nZ.GetSize()+1); // one exra digit for buffer guard
    nPowerModulus.m_pnValue[nZ.GetSize()] = TEST_BUFFERGUARD;
    nPowerModulusWorkspaceMemoryNeeds = PowerModulusMemoryNeeds(nX.GetSize(), nY.GetSize(), nZ.GetSize());
    pnWorkspace[nPowerModulusWorkspaceMemoryNeeds] = TEST_BUFFERGUARD;
    dw64Timestamp1 = s_Timer.GetMicroseconds();
    PowerModulus(nX.GetSize(),nY.GetSize(),nZ.GetSize(),nPowerModulusSize,nX.GetValue(),nY.GetValue(),nZ.GetValue(),nPowerModulus.GetValue(),pnWorkspace,true);
    nPowerModulus.SetSize(nPowerModulusSize);
    if (TEST_BUFFERGUARD != pnWorkspace[nPowerModulusWorkspaceMemoryNeeds])
    {
        printf("Buffer overrun for power modulus: perf test a\n");
        goto exit;
    }
    if (TEST_BUFFERGUARD != nPowerModulus.m_pnValue[nZ.GetSize()])
    {
        printf("Power modulus overwrote output buffer\n");
        goto exit;
    }
    dw64Timestamp2 = s_Timer.GetMicroseconds();
    PowerModulus(nX.GetSize(),nY.GetSize(),nZ.GetSize(),nPowerModulusSize,nX.GetValue(),nY.GetValue(),nZ.GetValue(),nPowerModulus.GetValue(),pnWorkspace,false);
    nPowerModulus.SetSize(nPowerModulusSize);
    dw64Timestamp3 = s_Timer.GetMicroseconds();
    if (TEST_BUFFERGUARD != pnWorkspace[nPowerModulusWorkspaceMemoryNeeds])
    {
        printf("Buffer overrun for power modulus: perf test b\n");
        goto exit;
    }
    if (TEST_BUFFERGUARD != nPowerModulus.m_pnValue[nZ.GetSize()])
    {
        printf("Power modulus overwrote output buffer\n");
        goto exit;
    }
    printf("Big power modulus time: (a) %i microsoeconds where we care about timing; (b) %i where we don't\n",dw64Timestamp2-dw64Timestamp1,dw64Timestamp3-dw64Timestamp2);
    // do a bunch of small power-modulus, then brute-force check correctness
    for(int i=0;i<c_nIterations;i++)
    {
        do
        {
            nX.SetRandom(6);
            nY.SetRandom(20);
            nZ.SetRandom(128);
        }
        while(0==nX.GetSize() || 0==nY.GetSize() || 0==nZ.GetSize());
        if (0 == i)
        {
            // special case: make sure 1 works as a power
            nY.SetSize(1);
            nY.GetValue()[0] = 1;
        }
        nPowerModulusWorkspaceMemoryNeeds = PowerModulusMemoryNeeds(nX.GetSize(), nY.GetSize(), nZ.GetSize());
        pnWorkspace[nPowerModulusWorkspaceMemoryNeeds] = TEST_BUFFERGUARD;
        dw64Timestamp1 = s_Timer.GetMicroseconds();
        nFoo = nY;
        // first, compute the expected value, brute-force
        nExpectedPowerModulus.SetFromHexString("1");
        do
        {
            cBox.Multiply(nExpectedPowerModulus,nX,nPowerModulus);
            nExpectedPowerModulus = nPowerModulus;
            nFoo -= 1;
        }
        while(0!=nFoo.GetSize());
        cBox.Divide(nExpectedPowerModulus,nZ,nThrowAwayValue,nPowerModulus);
        dw64Timestamp2 = s_Timer.GetMicroseconds();
        nExpectedPowerModulus = nPowerModulus;
        // next, try the PowerModulus way of doing it -- with and without timing-attack paranoia
        nPowerModulus.m_pnValue[nZ.GetSize()] = TEST_BUFFERGUARD;
        PowerModulus(nX.GetSize(),nY.GetSize(),nZ.GetSize(),nPowerModulusSize,nX.GetValue(),nY.GetValue(),nZ.GetValue(),nPowerModulus.GetValue(),pnWorkspace,true);
        nPowerModulus.SetSize(nPowerModulusSize);
        dw64Timestamp3 = s_Timer.GetMicroseconds();
        if (TEST_BUFFERGUARD != pnWorkspace[nPowerModulusWorkspaceMemoryNeeds])
        {
            printf("Buffer overrun for power modulus: slow & small a\n");
            goto exit;
        }
        if (TEST_BUFFERGUARD != nPowerModulus.m_pnValue[nZ.GetSize()])
        {
            printf("Power modulus overwrote output buffer: slow & small a\n");
            goto exit;
        }
        if(nPowerModulus != nExpectedPowerModulus)
        {
            printf("Power modulus test failed (worried about timing attacks).\nExpected ");
            nExpectedPowerModulus.PrintHexToFile();
            printf("Got      ");
            nPowerModulus.PrintHexToFile();
            goto exit;
        }
        PowerModulus(nX.GetSize(),nY.GetSize(),nZ.GetSize(),nPowerModulusSize,nX.GetValue(),nY.GetValue(),nZ.GetValue(),nPowerModulus.GetValue(),pnWorkspace,false);
        nPowerModulus.SetSize(nPowerModulusSize);
        dw64Timestamp4 = s_Timer.GetMicroseconds();
        if (TEST_BUFFERGUARD != pnWorkspace[nPowerModulusWorkspaceMemoryNeeds])
        {
            printf("Buffer overrun for power modulus: slow & small b\n");
            goto exit;
        }
        if (TEST_BUFFERGUARD != nPowerModulus.m_pnValue[nZ.GetSize()])
        {
            printf("Power modulus overwrote output buffer: slow & small b\n");
            goto exit;
        }
        printf("Iteration %i (of %i).  Brute force: %i microseconds.  PM (a): %i microseconds.  PM (b): %i microseconds\n",i+1,c_nIterations,dw64Timestamp2-dw64Timestamp1,dw64Timestamp3-dw64Timestamp2,dw64Timestamp4-dw64Timestamp3);
        if(nPowerModulus != nExpectedPowerModulus)
        {
            printf("Power modulus test failed (timing-attack agnostic).\nExpected ");
            nExpectedPowerModulus.PrintHexToFile();
            printf("Got      ");
            nPowerModulus.PrintHexToFile();
            goto exit;
        }
    }
    // now some large ones.  Note that if 1<m<n and (m,n) are relatively prime then m^(n-2) != 1 and m^(n-1) == 1
    // 98096A1FC1FB69 is prime, so anything in 1 < n < 98096A1FC1FB69 is relatively prime to it
    nZ.SetFromHexString("98096A1FC1FB69");
    nPowerModulus.m_pnValue[nZ.GetSize()] = TEST_BUFFERGUARD;
    for(int i=0; i<c_nIterations; i++)
    {
        nX.SetRandom(52);
        nX += 2; // make sure not 0 or 1
        nY =  nZ;
        nY -= 2;
        nPowerModulusWorkspaceMemoryNeeds = PowerModulusMemoryNeeds(nX.GetSize(), nY.GetSize(), nZ.GetSize());
        pnWorkspace[nPowerModulusWorkspaceMemoryNeeds] = TEST_BUFFERGUARD;
        PowerModulus(nX.GetSize(), nY.GetSize(), nZ.GetSize(), nPowerModulusSize, nX.GetValue(), nY.GetValue(), nZ.GetValue(), nPowerModulus.GetValue(), pnWorkspace, false);
        if (TEST_BUFFERGUARD != pnWorkspace[nPowerModulusWorkspaceMemoryNeeds])
        {
            printf("Buffer overrun for power modulus: perfunctory a\n");
            goto exit;
        }
        if (TEST_BUFFERGUARD != nPowerModulus.m_pnValue[nZ.GetSize()])
        {
            printf("Power modulus overwrote output buffer: perfunctory a\n");
            goto exit;
        }
        if (0 == nPowerModulusSize || (1 == nPowerModulusSize && 1 == nPowerModulus.GetValue()[0]))
        {
            printf("We have a problem -- power modulus shouldn't be 0 or 1 at this stage\n");
            goto exit;
        }
        nY += 1;
        PowerModulus(nX.GetSize(), nY.GetSize(), nZ.GetSize(), nPowerModulusSize, nX.GetValue(), nY.GetValue(), nZ.GetValue(), nPowerModulus.GetValue(), pnWorkspace, false);
        if (TEST_BUFFERGUARD != pnWorkspace[nPowerModulusWorkspaceMemoryNeeds])
        {
            printf("Buffer overrun for power modulus: perfunctory b\n");
            goto exit;
        }
        if (TEST_BUFFERGUARD != nPowerModulus.m_pnValue[nZ.GetSize()])
        {
            printf("Power modulus overwrote output buffer: perfunctory b\n");
            goto exit;
        }
        if (1 != nPowerModulusSize || 1 != nPowerModulus.GetValue()[0])
        {
            printf("We have a problem -- power modulus should be 1\n");
            goto exit;
        }
    }
    // and a really big check: 70B7D9 0310FDB4 0C3F2BA6 43C03915 7EDA370D 60E87F29 B0E23AC3 F52A1859 55994A40 AECBC38E F4A9AE43 CB3730B9 679E614D A37C874D 5F699423 1DCBE1C1 DDDE2A4E 36FDCB11 B8343B9C 800AC83C 1B8A949F 9F91CEC5 065E332B CC55C635 CB15CEDB 55BD0F95 91794B8A 1951FAF7 D23447DC 0E414DEC DF5791B4 BCDFC20C 58D8AEBE C12286A7
    // is also prime
    nZ.SetFromHexString("70B7D90310FDB40C3F2BA643C039157EDA370D60E87F29B0E23AC3F52A185955994A40AECBC38EF4A9AE43CB3730B9679E614DA37C874D5F6994231DCBE1C1DDDE2A4E36FDCB11B8343B9C800AC83C1B8A949F9F91CEC5065E332BCC55C635CB15CEDB55BD0F9591794B8A1951FAF7D23447DC0E414DECDF5791B4BCDFC20C58D8AEBEC12286A7");
    nPowerModulus.Reserve(nZ.GetSize() + 1); // one exra digit for buffer guard
    nPowerModulus.m_pnValue[nZ.GetSize()] = TEST_BUFFERGUARD;
    for (int i=0; i<c_nIterations; i++)
    {
        nX.SetRandom(1000);
        nX += 2; // make sure not 0 or 1
        nY =  nZ;
        nY -= 2;
        nPowerModulusWorkspaceMemoryNeeds = PowerModulusMemoryNeeds(nX.GetSize(), nY.GetSize(), nZ.GetSize());
        pnWorkspace[nPowerModulusWorkspaceMemoryNeeds] = TEST_BUFFERGUARD;
        PowerModulus(nX.GetSize(), nY.GetSize(), nZ.GetSize(), nPowerModulusSize, nX.GetValue(), nY.GetValue(), nZ.GetValue(), nPowerModulus.GetValue(), pnWorkspace, false);
        if (TEST_BUFFERGUARD != pnWorkspace[nPowerModulusWorkspaceMemoryNeeds])
        {
            printf("Buffer overrun for power modulus: big prime power a\n");
            goto exit;
        }
        if (TEST_BUFFERGUARD != nPowerModulus.m_pnValue[nZ.GetSize()])
        {
            printf("Power modulus overwrote output buffer: big prime power a\n");
            goto exit;
        }
        if (0 == nPowerModulusSize || (1 == nPowerModulusSize && 1 == nPowerModulus.GetValue()[0]))
        {
            printf("We have a problem -- power modulus shouldn't be 0 or 1 at this stage\n");
            goto exit;
        }
        nY += 1;
        PowerModulus(nX.GetSize(), nY.GetSize(), nZ.GetSize(), nPowerModulusSize, nX.GetValue(), nY.GetValue(), nZ.GetValue(), nPowerModulus.GetValue(), pnWorkspace, false);
        if (TEST_BUFFERGUARD != pnWorkspace[nPowerModulusWorkspaceMemoryNeeds])
        {
            printf("Buffer overrun for power modulus: big prime power b\n");
            goto exit;
        }
        if (TEST_BUFFERGUARD != nPowerModulus.m_pnValue[nZ.GetSize()])
        {
            printf("Power modulus overwrote output buffer: big prime power b\n");
            goto exit;
        }
        if (1 != nPowerModulusSize || 1 != nPowerModulus.GetValue()[0])
        {
            printf("We have a problem -- power modulus should be 1\n");
            goto exit;
        }
    }
    // finally, try some big numbers and big modulus -- but small power, so actually have a chance of manually checking
    nPowerModulus.Reserve(8000); // more than needed -- need 8000 BITs, not 8000 DIGITs
    nY.Reserve(1);
    nY.SetSize(1);
    for (int i=0; i<c_nIterations; i++)
    {
        for(int nXLarger=0; nXLarger<2; nXLarger++)
        {
            if (nXLarger)
            {
                nX.SetRandom(3500);
                nZ.SetRandom(3000);
            }
            else
            {
                nX.SetRandom(3000);
                nZ.SetRandom(3500);
            }
            nPowerModulus.m_pnValue[nZ.GetSize()]          = TEST_BUFFERGUARD;
            nPowerModulusWorkspaceMemoryNeeds              = PowerModulusMemoryNeeds(nX.GetSize(), nY.GetSize(), nZ.GetSize());
            pnWorkspace[nPowerModulusWorkspaceMemoryNeeds] = TEST_BUFFERGUARD;
            if (nZ < nX) printf("modulus smaller\n");
            for(int nPower=1; nPower<17; nPower++)
            {
                nY.GetValue()[0] = nPower;
                // using power modulus
                PowerModulus(nX.GetSize(), nY.GetSize(), nZ.GetSize(), nPowerModulusSize, nX.GetValue(), nY.GetValue(), nZ.GetValue(), nPowerModulus.GetValue(), pnWorkspace, false);
                if (TEST_BUFFERGUARD != pnWorkspace[nPowerModulusWorkspaceMemoryNeeds])
                {
                    printf("Buffer overrun for power modulus: small power, big other values\n");
                    goto exit;
                }
                if (TEST_BUFFERGUARD != nPowerModulus.m_pnValue[nZ.GetSize()])
                {
                    printf("Power modulus overwrote output buffer: small power, big other values\n");
                    goto exit;
                }
                nPowerModulus.SetSize(nPowerModulusSize);
                // brute force: power
                nExpectedPowerModulus.Reserve(5*nX.GetSize());
                // first multiply
                nExpectedPowerModulus = nX;
                nFoo                  = nExpectedPowerModulus; // just in case power is 1
                // rest of the multiplies
                nPowerModulusSize = nX.GetSize();
                for(int i=0; i<nPower-1; i++)
                { 
                    cBox.Multiply(nExpectedPowerModulus, nX, nFoo);
                    nExpectedPowerModulus = nFoo;
                }
                // Brute force: modulus
                // note value in both nExpectedPowerModulus, nFoo
                cBox.Divide(nFoo, nZ, nThrowAwayValue, nExpectedPowerModulus);
                if (nExpectedPowerModulus != nPowerModulus)
                {
                    printf("oops: got ");
                    nPowerModulus.PrintHexToFile();
                    printf("expected  ");
                    nExpectedPowerModulus.PrintHexToFile();
                    goto exit;
                }
            }
        }
    }
    bTestWorked = true;
exit:
    free(pnWorkspace);
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestModularBox()
{
    CBigInteger           nTwoInverse, nProduct;
    CBigInteger           nModulus("AABB0123459"); // note this is odd, so guaranteed 2 is relatively prime (for simplicity).  It is also a multiple of 3
    CBigInteger           nOne("1");
    CBigInteger           nTwo("2");
    CBigInteger           nThree("3");
    CModularArithmeticBox cModularBox(nModulus, false);
    if(eOperationSucceeded != cModularBox.MultiplicativeInverse(&nTwo, &nTwoInverse))
    {
        return false;
    }
    if(eOperationSucceeded != cModularBox.Multiply(&nTwo,&nTwoInverse,&nProduct))
    {
        return false;
    }
    if(nOne != nProduct)
    {
        return false;
    }
    if(eBadArgument != cModularBox.MultiplicativeInverse(&nThree, &nTwoInverse))
    {
        return false;
    }
    return true;
}

bool CArithmeticCorrectnessTester::TestMontgomeryFormat()
{
#if(_CollectDetailedTimingData)
    DWORD64            dwTimestamp = s_Timer.GetMicroseconds();
#endif
    CArithmeticBox     cBox;
    int                nNumBits;
    const unsigned int c_nNumTestModulusValues = 4;
    const unsigned int c_nTests    = 1024;
    bool               bTestWorked = false;
    CBigIntegerForTest nX, nY, nN, nNPrime, nRPrime, nMontgomeryX, nMontgomeryY, nProduct, nConvertedBack, nDiv, nRemainder;
    size_t             nNPrimeSize, nRPrimeSize, nMontSize, nConvertBackSize;
    DIGIT              *pWorkspace = (DIGIT *) malloc(sizeof(DIGIT)*1000000); // plenty for this test
    const char         *c_szTestModuluses[c_nNumTestModulusValues] = {"98096A1FC1FB69", // prime
                                                                      "70B7D90310FDB40C3F2BA643C039157EDA370D60E87F29B0E23AC3F52A185955994A40AECBC38EF4A9AE43CB3730B9679E614DA37C874D5F6994231DCBE1C1DDDE2A4E36FDCB11B8343B9C800AC83C1B8A949F9F91CEC5065E332BCC55C635CB15CEDB55BD0F9591794B8A1951FAF7D23447DC0E414DECDF5791B4BCDFC20C58D8AEBEC12286A7",
                                                                      "54FBA35F116A51EEFDF1C05A57EA039867E4C328228706EA11788CAD0B9B728C6F593790E6E4C278200A3939EE50683A306CCBE11915C83635912E7C8EAB356D",  // modulus found to cause trouble previously
                                                                      "43FB698A22D31D79DDE37E878E7821D46629790C089F1C97B00AEDFB7D42995E2FCE8513743807B0694409DF50313EDEEC2F18A7F586148924F3054184BB914B"}; // modulus found to cause trouble previously
    for(int k=0; k<300; k++)
    {
        if(0==k%100) printf("Iterations %i through %i\n",k,k+99);
        if(k<c_nNumTestModulusValues)
        {
            // a few values that in the past have caused trouble
            nN.SetFromHexString(c_szTestModuluses[k]);
        }
        else
        {
            // a bunch of random values for further testing
            nN.SetRandom(13*k);
            nN.m_pnValue[0] |= 1; // needs to be odd for Montgomery to work
        }
        nNumBits = (nN.GetSize() - 1)*_DIGIT_SIZE_IN_BITS;
        nMontgomeryX.Reserve(nN.GetSize()*2);
        nMontgomeryY.Reserve(nN.GetSize()*2);
        nConvertedBack.Reserve(nN.GetSize()*2);
        nNPrime.Reserve(nN.GetSize()+1); // one extra digit for overflow during computation
        nRPrime.Reserve(nN.GetSize()+1); // one extra digit for overflow during computation
        GetMontgomeryParameters(nN.GetSize(), nNPrimeSize, nRPrimeSize, nN.GetValue(), nNPrime.GetValue(), nRPrime.GetValue(), pWorkspace);
        nNPrime.SetSize(nNPrimeSize);
        nRPrime.SetSize(nRPrimeSize);
        // Should have R*R' mod N = 1
        nProduct.Reserve(nN.GetSize() + nRPrime.GetSize());
        nProduct.SetSize(nN.GetSize() + nRPrime.GetSize());
        // set nProduct to R*R'
        memset(nProduct.GetValue(), 0, nN.GetSize()*sizeof(DIGIT));
        for(int i=0; i<nRPrimeSize; i++)
        {
            nProduct.GetValue()[nN.GetSize()+i] = nRPrime.GetValue()[i];
        }
        nProduct.SetSize(nRPrimeSize+nN.GetSize());
        cBox.Divide(nProduct, nN, nX, nY);
        if (1 != nY.GetSize() || 1 != nY.GetValue()[0])
        {
            printf("Test %i: problem with modulus ",k); nN.PrintHexToScreen();
            printf("Expected R*R' mod N to be 1; instead, got ");
            nY.PrintDecimalToFile();
            goto exit;
        }
        // N*N' - R*R'
        nProduct.SetNegative(true);
        cBox.MultiplyAdd(nN, nNPrime, nProduct);
        // should have R*R' - N*N' = 1:
        if (1 != nProduct.GetSize() || 1 != nProduct.GetValue()[0] || !nProduct.IsNegative())
        {
            printf("Test %i: problem with modulus ",k); nN.PrintHexToScreen();
            printf("Expected N*N' - R*R' to be -1; instead, got ");
            nProduct.PrintDecimalToFile();
            goto exit;
        }
        // test Montgomery conversion
        for(int i=0; i<c_nTests; i++)
        {
            nX.SetRandom(nNumBits);
#if(_CollectDetailedTimingData)
            ToMontgomeryForm(nX.GetSize(), nN.GetSize(), nMontSize, nX.GetValue(), nN.GetValue(), nMontgomeryX.GetValue(), dwTimestamp, pWorkspace);
            FromMontgomeryForm(nMontSize, nN.GetSize(), nRPrimeSize, nConvertBackSize, nMontgomeryX.GetValue(), nN.GetValue(), nRPrime.GetValue(), nConvertedBack.GetValue(), dwTimestamp, pWorkspace);
#else
            ToMontgomeryForm(nX.GetSize(), nN.GetSize(), nMontSize, nX.GetValue(), nN.GetValue(), nMontgomeryX.GetValue(), pWorkspace);
            FromMontgomeryForm(nMontSize, nN.GetSize(), nRPrimeSize, nConvertBackSize, nMontgomeryX.GetValue(), nN.GetValue(), nRPrime.GetValue(), nConvertedBack.GetValue(), pWorkspace);
#endif
            nConvertedBack.SetSize(nConvertBackSize);
            if (nX != nConvertedBack)
            {
                printf("Original:                              ");
                nX.PrintDecimalToFile();
                printf("converted to Montgomery form and back: ");
                nConvertedBack.PrintDecimalToFile();
                goto exit;
            }
        }
    }
    bTestWorked = true;
exit:
    free(pWorkspace);
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestMontgomeryMultiply()
{
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
#endif
    CArithmeticBox     cBox;
    int                nNumBits;
    const unsigned int c_nTests    = 1024;
    bool               bTestWorked = false;
    CBigIntegerForTest nX, nY, nN, nNPrime, nRPrime, nMontgomeryX, nMontgomeryY, nProduct, nConvertedBack, nDiv, nRemainder;
    size_t             nNPrimeSize, nRPrimeSize, nMontSize, nConvertBackSize;
    DIGIT              *pWorkspace = (DIGIT *) malloc(sizeof(DIGIT)*1000000); // plenty for this test
    // Note that 70B7D90310FDB40C3F2BA643C039157EDA370D60E87F29B0E23AC3F52A185955994A40AECBC38EF4A9AE43CB3730B9679E614DA37C874D5F6994231DCBE1C1DDDE2A4E36FDCB11B8343B9C800AC83C1B8A949F9F91CEC5065E332BCC55C635CB15CEDB55BD0F9591794B8A1951FAF7D23447DC0E414DECDF5791B4BCDFC20C58D8AEBEC12286A7
    // is prime
    nN.SetFromHexString("70B7D90310FDB40C3F2BA643C039157EDA370D60E87F29B0E23AC3F52A185955994A40AECBC38EF4A9AE43CB3730B9679E614DA37C874D5F6994231DCBE1C1DDDE2A4E36FDCB11B8343B9C800AC83C1B8A949F9F91CEC5065E332BCC55C635CB15CEDB55BD0F9591794B8A1951FAF7D23447DC0E414DECDF5791B4BCDFC20C58D8AEBEC12286A7");// 98096A1FC1FB69");
    nNumBits = (nN.GetSize() - 1)*_DIGIT_SIZE_IN_BITS;
    nMontgomeryX.Reserve(nN.GetSize()*2);
    nMontgomeryY.Reserve(nN.GetSize()*2);
    nConvertedBack.Reserve(nN.GetSize()*2);
    nNPrime.Reserve(nN.GetSize()+1); // one extra digit for overflow during computation
    nRPrime.Reserve(nN.GetSize()+1); // one extra digit for overflow during computation
    GetMontgomeryParameters(nN.GetSize(), nNPrimeSize, nRPrimeSize, nN.GetValue(), nNPrime.GetValue(), nRPrime.GetValue(), pWorkspace);
    nNPrime.SetSize(nNPrimeSize);
    nRPrime.SetSize(nRPrimeSize);
    // Should have R*R' mod N = 1
    nProduct.Reserve(nN.GetSize() + nRPrime.GetSize());
    nProduct.SetSize(nN.GetSize() + nRPrime.GetSize());
    memset(nProduct.GetValue(), 0, nN.GetSize()*sizeof(DIGIT));
    for(int i=0; i<nRPrimeSize; i++)
    {
        nProduct.GetValue()[nN.GetSize()+i] = nRPrime.GetValue()[i];
    }
    nProduct.SetSize(nRPrimeSize+nN.GetSize());
    cBox.Divide(nProduct, nN, nX, nY);
    nProduct.SetNegative(true);
    cBox.MultiplyAdd(nN, nNPrime, nProduct);
    // test some Montgomery multiplication: converting two numbers x, y to Montgomery form, multiplying them, and converting the product
    // back to regular form should get the same result as computing x*y mod N directly
    nProduct.Reserve(nN.GetSize()*2 + 1); // one extra digit for overflow during computation
    nConvertedBack.Reserve(nN.GetSize()*2);
    for(int i=0; i<c_nTests; i++)
    {
        nX.SetRandom(nNumBits);
        nY.SetRandom(nNumBits);
#if(_CollectDetailedTimingData)
        ToMontgomeryForm(nX.GetSize(), nN.GetSize(), nMontSize, nX.GetValue(), nN.GetValue(), nMontgomeryX.GetValue(), dwTimestamp, pWorkspace);
        nMontgomeryX.SetSize(nMontSize);
        ToMontgomeryForm(nY.GetSize(), nN.GetSize(), nMontSize, nY.GetValue(), nN.GetValue(), nMontgomeryY.GetValue(), dwTimestamp, pWorkspace);
        nMontgomeryY.SetSize(nMontSize);
#else
        ToMontgomeryForm(nX.GetSize(), nN.GetSize(), nMontSize, nX.GetValue(), nN.GetValue(), nMontgomeryX.GetValue(), pWorkspace);
        nMontgomeryX.SetSize(nMontSize);
        ToMontgomeryForm(nY.GetSize(), nN.GetSize(), nMontSize, nY.GetValue(), nN.GetValue(), nMontgomeryY.GetValue(), pWorkspace);
        nMontgomeryY.SetSize(nMontSize);
#endif
        MontgomeryMultiply(nMontgomeryX.GetSize(),
                           nMontgomeryY.GetSize(),
                           nN.GetSize(),
                           nNPrimeSize,
                           nMontSize,
                           nMontgomeryX.GetValue(),
                           nMontgomeryY.GetValue(),
                           nN.GetValue(),
                           nNPrime.GetValue(),
                           nProduct.GetValue(),
#if(_CollectDetailedTimingData)
                           dwTimestamp,
#endif
                           pWorkspace);
        FromMontgomeryForm(nMontSize,
                           nN.GetSize(),
                           nRPrimeSize,
                           nConvertBackSize,
                           nProduct.GetValue(),
                           nN.GetValue(),
                           nRPrime.GetValue(),
                           nConvertedBack.GetValue(),
#if(_CollectDetailedTimingData)
                           dwTimestamp,
#endif
                           pWorkspace);
        nConvertedBack.SetSize(nConvertBackSize);
        cBox.Multiply(nX, nY, nProduct);
        cBox.Divide(nProduct, nN, nDiv, nRemainder);
        if (nRemainder != nConvertedBack)
        {
            printf("x: ");
            nX.PrintDecimalToFile();
            printf("y: ");
            nY.PrintDecimalToFile();
            printf("Actual modular product: ");
            nRemainder.PrintDecimalToFile();
            printf("Using Montogomery:      ");
            nConvertedBack.PrintDecimalToFile();
            goto exit;
        }
    }
    bTestWorked = true;
exit:
    free(pWorkspace);
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestMontgomeryPowerModulus()
{
    CArithmeticBox     cBox;
    size_t             nBasicPowerModulusBufferSize, nWorkspaceMemoryNeeds;
    const unsigned int c_nTests_Small = 1024, c_nTests_Large = 64;
    bool               bTestWorked = false;
    CBigIntegerForTest nX, nY, nN, nNPrime, nRPrime, nPowerModulusBasic, nPowerModulusMontgomery;
    CBigIntegerForTest nXCopy, nYCopy, nNCopy, nNPrimeCopy, nRPrimeCopy;
    size_t             nNPrimeSize, nRPrimeSize, nMontSize, nPowerModulusSize;
    DIGIT              *pWorkspace = (DIGIT *) malloc(sizeof(DIGIT)*1000000); // plenty for this test
    nN.SetFromHexString("54FBA35F116A51EEFDF1C05A57EA039867E4C328228706EA11788CAD0B9B728C6F593790E6E4C278200A3939EE50683A306CCBE11915C83635912E7C8EAB356D"); // value that has had trouble before
    nNPrime.Reserve(nN.GetSize()+1); // needs a little extra space for overflow (of 0) to avoid checking boundaries
    nRPrime.Reserve(nN.GetSize()+1); // one extra digit for overflow during computation
    GetMontgomeryParameters(nN.GetSize(), nNPrimeSize, nRPrimeSize, nN.GetValue(), nNPrime.GetValue(), nRPrime.GetValue(), pWorkspace);
    nNPrime.SetSize(nNPrimeSize);
    nRPrime.SetSize(nRPrimeSize);
    nNPrimeCopy = nNPrime;
    nRPrimeCopy = nRPrime;
    nNCopy      = nN;
    nPowerModulusMontgomery.Reserve(nN.GetSize()+1); // one extra DIGIT for buffer guard
    nPowerModulusMontgomery.GetValue()[nN.GetSize()] = TEST_BUFFERGUARD;
    printf("Small Montgomery power modulus tests:\n");
    for(int nProtectVsTiming=0; nProtectVsTiming<2; nProtectVsTiming++)
    {
        bool bProtectAgainstTime = (0 != nProtectVsTiming);
        printf("Protecting against time: %s\n", bProtectAgainstTime ? "true" : "false");
        for (int nNumBits=48; nNumBits<=800; nNumBits += 8)
        {
            printf("Base bitsize: %i (max 800)\n", nNumBits);
            for (int i=0; i<c_nTests_Small; i++)
            {
                nX.SetRandom(nNumBits);
                nY.SetRandom(nNumBits);
                // basic power modulus needs space for <nXSize> digits in the power modulus if X is bigger than the modulus itself
                nBasicPowerModulusBufferSize = max(nX.GetSize(), nN.GetSize());
                nPowerModulusBasic.Reserve(nX.GetSize()+1); // one extra digit for buffer guard
                nPowerModulusBasic.Reserve(nBasicPowerModulusBufferSize + 1); // one extra digit for buffer guard
                nPowerModulusBasic.GetValue()[nBasicPowerModulusBufferSize] = TEST_BUFFERGUARD;
                nWorkspaceMemoryNeeds = PowerModulusMemoryNeeds(nX.GetSize(), nY.GetSize(), nN.GetSize());
                pWorkspace[nWorkspaceMemoryNeeds] = TEST_BUFFERGUARD;
                if(0==i)
                {
                    // try 1 as the power -- special case
                    nY.SetSize(1);
                    nY.GetValue()[0] = 1;
                }
                nXCopy = nX;
                nYCopy = nY;
                MontgomeryPowerModulus(nX.GetSize(),
                                       nY.GetSize(),
                                       nN.GetSize(),
                                       nNPrimeSize,
                                       nRPrimeSize,
                                       nPowerModulusSize,
                                       nX.GetValue(),
                                       nY.GetValue(),
                                       nRPrime.GetValue(),
                                       nN.GetValue(),
                                       nNPrime.GetValue(),
                                       nPowerModulusMontgomery.GetValue(),
                                       pWorkspace,
                                       bProtectAgainstTime);
                nPowerModulusMontgomery.SetSize(nPowerModulusSize);
                if (TEST_BUFFERGUARD != nPowerModulusMontgomery.GetValue()[nN.GetSize()])
                {
                    printf("Montgomery power modulus overran output buffer\n");
                    goto exit;
                }
                if (TEST_BUFFERGUARD != pWorkspace[nWorkspaceMemoryNeeds])
                {
                    printf("Overran workspace memory during Montgomery power modulus\n");
                    goto exit;
                }
                PowerModulus(nX.GetSize(),
                             nY.GetSize(),
                             nN.GetSize(),
                             nPowerModulusSize,
                             nX.GetValue(),
                             nY.GetValue(),
                             nN.GetValue(),
                             nPowerModulusBasic.GetValue(),
                             pWorkspace);
                nPowerModulusBasic.SetSize(nPowerModulusSize);
                if (TEST_BUFFERGUARD != nPowerModulusBasic.GetValue()[nBasicPowerModulusBufferSize])
                {
                    printf("Basic power modulus overran output buffer\n");
                    goto exit;
                }
                if (TEST_BUFFERGUARD != pWorkspace[nWorkspaceMemoryNeeds])
                {
                    printf("Overran workspace memory during standard power modulus\n");
                    goto exit;
                }
                if (nX != nXCopy)
                {
                    printf("X value got changed\n");
                    goto exit;
                }
                if (nY != nYCopy)
                {
                    printf("Y value got changed\n");
                    goto exit;
                }
                if (nN != nNCopy)
                {
                    printf("N value (modulus) got changed\n");
                    goto exit;
                }
                if (nNPrime != nNPrimeCopy)
                {
                    printf("N' (modulus') value got changed\n");
                    goto exit;
                }
                if (nRPrime != nRPrimeCopy)
                {
                    printf("R' value got changed\n");
                    goto exit;
                }
                if (nPowerModulusBasic != nPowerModulusMontgomery)
                {
                    printf("Power modulus mismatch:\n");
                    printf("Base:         ");
                    nX.PrintHexToFile();
                    printf("Power:        ");
                    nY.PrintHexToFile();
                    printf("Modulus:      ");
                    nN.PrintHexToFile();
                    printf("Got:          ");
                    nPowerModulusMontgomery.PrintHexToFile();
                    printf("but expected: ");
                    nPowerModulusBasic.PrintHexToFile();
                    goto exit;
                }
            }
            // fresh modulus!
            do
            {
                nN.SetRandom(640);
                nN.GetValue()[0] |= 1; // force odd to be suitable for Montgomery
            }
            while(nN.GetSize()*_DIGIT_SIZE_IN_BITS != 640);
            nNPrime.Reserve(nN.GetSize() + 1); // needs a little extra space for overflow (of 0) to avoid checking boundaries
            nRPrime.Reserve(nN.GetSize() + 1); // one extra digit for overflow during computation
            nPowerModulusMontgomery.Reserve(nN.GetSize() + 1); // one extra DIGIT for buffer guard
            nPowerModulusMontgomery.GetValue()[nN.GetSize()] = TEST_BUFFERGUARD;
            GetMontgomeryParameters(nN.GetSize(), nNPrimeSize, nRPrimeSize, nN.GetValue(), nNPrime.GetValue(), nRPrime.GetValue(), pWorkspace);
            nNPrime.SetSize(nNPrimeSize);
            nRPrime.SetSize(nRPrimeSize);
            nNPrimeCopy = nNPrime;
            nRPrimeCopy = nRPrime;
            nNCopy      = nN;
        }
    }
    printf("Large Montgomery power modulus tests:\n");
    for(int nProtectVsTiming=0; nProtectVsTiming<2; nProtectVsTiming++)
    {
        bool bProtectAgainstTime = (0 != nProtectVsTiming);
        printf("Protecting against time: %s\n", bProtectAgainstTime ? "true" : "false");
        for (int nNumBits=4000; nNumBits<=8000; nNumBits += 2000)
        {
            printf("Base bitsize: %i (max 8000)\n", nNumBits);
            nN.SetRandom(6000);
            nN.m_pnValue[0] |= 1; // force odd, so that it is suitable for Montgomery
            nNPrime.Reserve(nN.GetSize() + 1); // needs a little extra space for overflow (of 0) to avoid checking boundaries
            nRPrime.Reserve(nN.GetSize() + 1); // one extra digit for overflow during computation
            GetMontgomeryParameters(nN.GetSize(), nNPrimeSize, nRPrimeSize, nN.GetValue(), nNPrime.GetValue(), nRPrime.GetValue(), pWorkspace);
            nNPrime.SetSize(nNPrimeSize);
            nRPrime.SetSize(nRPrimeSize);
            nNPrimeCopy = nNPrime;
            nRPrimeCopy = nRPrime;
            nNCopy      = nN;
            nPowerModulusMontgomery.Reserve(nN.GetSize() + 1); // one extra DIGIT for buffer guard
            nPowerModulusMontgomery.GetValue()[nN.GetSize()] = TEST_BUFFERGUARD;
            nPowerModulusBasic.Reserve(nN.GetSize() + 1); // one extra digit for buffer guard
            nPowerModulusBasic.GetValue()[nN.GetSize()] = TEST_BUFFERGUARD;
            for (int i=0; i<c_nTests_Large; i++)
            {
                nX.SetRandom(nNumBits);
                nY.SetRandom(nNumBits);
                nBasicPowerModulusBufferSize = max(nX.GetSize(), nN.GetSize());
                nPowerModulusBasic.Reserve(nBasicPowerModulusBufferSize + 1); // one extra digit for buffer guard
                nPowerModulusBasic.GetValue()[nBasicPowerModulusBufferSize] = TEST_BUFFERGUARD;
                nPowerModulusBasic.Reserve(nX.GetSize());
                if(0==i)
                {
                    // try 1 as the power -- special case
                    nY.SetSize(1);
                    nY.GetValue()[0] = 1;
                }
                nXCopy = nX;
                nYCopy = nY;
                MontgomeryPowerModulus(nX.GetSize(),
                                       nY.GetSize(),
                                       nN.GetSize(),
                                       nNPrimeSize,
                                       nRPrimeSize,
                                       nPowerModulusSize,
                                       nX.GetValue(),
                                       nY.GetValue(),
                                       nRPrime.GetValue(),
                                       nN.GetValue(),
                                       nNPrime.GetValue(),
                                       nPowerModulusMontgomery.GetValue(),
                                       pWorkspace,
                                       bProtectAgainstTime);
                nPowerModulusMontgomery.SetSize(nPowerModulusSize);
                if (TEST_BUFFERGUARD != nPowerModulusMontgomery.GetValue()[nN.GetSize()])
                {
                    printf("Montgomery power modulus overran output buffer\n");
                    goto exit;
                }
                PowerModulus(nX.GetSize(),
                             nY.GetSize(),
                             nN.GetSize(),
                             nPowerModulusSize,
                             nX.GetValue(),
                             nY.GetValue(),
                             nN.GetValue(),
                             nPowerModulusBasic.GetValue(),
                             pWorkspace);
                nPowerModulusBasic.SetSize(nPowerModulusSize);
                if (TEST_BUFFERGUARD != nPowerModulusBasic.GetValue()[nBasicPowerModulusBufferSize])
                {
                    printf("Basic power modulus overran output buffer\n");
                    goto exit;
                }
                if (nX != nXCopy)
                {
                    printf("X value got changed\n");
                    goto exit;
                }
                if (nY != nYCopy)
                {
                    printf("Y value got changed\n");
                    goto exit;
                }
                if (nN != nNCopy)
                {
                    printf("N value (modulus) got changed\n");
                    goto exit;
                }
                if (nNPrime != nNPrimeCopy)
                {
                    printf("N' (modulus) value got changed\n");
                    goto exit;
                }
                if (nRPrime != nRPrimeCopy)
                {
                    printf("R' value got changed\n");
                    goto exit;
                }
                if (nPowerModulusBasic != nPowerModulusMontgomery)
                {
                    printf("Power modulus mismatch:\n");
                    printf("Base:         ");
                    nX.PrintHexToFile();
                    printf("Power:        ");
                    nY.PrintHexToFile();
                    printf("Modulus:      ");
                    nN.PrintHexToFile();
                    printf("Got:          ");
                    nPowerModulusMontgomery.PrintHexToFile();
                    printf("but expected: ");
                    nPowerModulusBasic.PrintHexToFile();
                    goto exit;
                }
            }
        }
    }
    // final test: validate things don't break down when x divides the modulus and the power is large -- expect the output to be 0
    nN.SetFromHexString("3333333333333333333333333333333333333333333333");
    nY.SetFromHexString("7777777777777777777777777777777777777777777777");
    nX.SetFromHexString("3");
    GetMontgomeryParameters(nN.GetSize(), nNPrimeSize, nRPrimeSize, nN.GetValue(), nNPrime.GetValue(), nRPrime.GetValue(), pWorkspace);
    nNPrime.SetSize(nNPrimeSize);
    nRPrime.SetSize(nRPrimeSize);
    nNPrimeCopy = nNPrime;
    nRPrimeCopy = nRPrime;
    nNCopy      = nN;
    nPowerModulusMontgomery.Reserve(nN.GetSize() + 1); // one extra DIGIT for buffer guard
    nPowerModulusMontgomery.GetValue()[nN.GetSize()] = TEST_BUFFERGUARD;
    nPowerModulusBasic.Reserve(nN.GetSize() + 1); // one extra digit for buffer guard
    nPowerModulusBasic.GetValue()[nN.GetSize()] = TEST_BUFFERGUARD;
    for (int nProtectVsTiming = 0; nProtectVsTiming < 2; nProtectVsTiming++)
    {
        bool bProtectAgainstTime = (0 != nProtectVsTiming);
        nXCopy = nX;
        nYCopy = nY;
        nBasicPowerModulusBufferSize = max(nX.GetSize(), nN.GetSize());
        nPowerModulusBasic.Reserve(nBasicPowerModulusBufferSize + 1); // one extra digit for buffer guard
        nPowerModulusBasic.GetValue()[nBasicPowerModulusBufferSize] = TEST_BUFFERGUARD;
        MontgomeryPowerModulus(nX.GetSize(),
                               nY.GetSize(),
                               nN.GetSize(),
                               nNPrimeSize,
                               nRPrimeSize,
                               nPowerModulusSize,
                               nX.GetValue(),
                               nY.GetValue(),
                               nRPrime.GetValue(),
                               nN.GetValue(),
                               nNPrime.GetValue(),
                               nPowerModulusMontgomery.GetValue(),
                               pWorkspace,
                               bProtectAgainstTime);
        nPowerModulusMontgomery.SetSize(nPowerModulusSize);
        if (TEST_BUFFERGUARD != nPowerModulusMontgomery.GetValue()[nBasicPowerModulusBufferSize])
        {
            printf("Montgomery power modulus overran output buffer\n");
            goto exit;
        }
        PowerModulus(nX.GetSize(),
                     nY.GetSize(),
                     nN.GetSize(),
                     nPowerModulusSize,
                     nX.GetValue(),
                     nY.GetValue(),
                     nN.GetValue(),
                     nPowerModulusBasic.GetValue(),
                     pWorkspace);
        nPowerModulusBasic.SetSize(nPowerModulusSize);
        if (TEST_BUFFERGUARD != nPowerModulusBasic.GetValue()[nN.GetSize()])
        {
            printf("Basic power modulus overran output buffer\n");
            goto exit;
        }
        if (nX != nXCopy)
        {
            printf("X value got changed\n");
            goto exit;
        }
        if (nY != nYCopy)
        {
            printf("Y value got changed\n");
            goto exit;
        }
        if (nN != nNCopy)
        {
            printf("N value (modulus) got changed\n");
            goto exit;
        }
        if (nNPrime != nNPrimeCopy)
        {
            printf("N' (modulus') value got changed\n");
            goto exit;
        }
        if (nRPrime != nRPrimeCopy)
        {
            printf("R' value got changed\n");
            goto exit;
        }
        if (nPowerModulusBasic != nPowerModulusMontgomery)
        {
            printf("Power modulus mismatch:\n");
            printf("Base:         ");
            nX.PrintHexToFile();
            printf("Power:        ");
            nY.PrintHexToFile();
            printf("Modulus:      ");
            nN.PrintHexToFile();
            printf("Got:          ");
            nPowerModulusMontgomery.PrintHexToFile();
            printf("but expected: ");
            nPowerModulusBasic.PrintHexToFile();
            goto exit;
        }
    }
    bTestWorked = true;
exit:
    free(pWorkspace);
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestSquareRoot()
{
#if(_CollectDetailedTimingData)
    DWORD64            dwTimestamp = s_Timer.GetMicroseconds();
#endif
    size_t             nRootSize;
    DOUBLEDIGIT        nStep, nVal, nSqrt, nHold;
    CArithmeticBox     cBox;
    CBigIntegerForTest nX1, nX1Copy, nX2, nX2Copy, nX3, nSum, nSquareRoot, nSquare;
    size_t             nMemoryNeeds;
    const unsigned int c_nMinBitSize                      = 16;
    const unsigned int c_nMaxBitSize                      = 131072;
    const unsigned int c_nTests                           = 100;
    const unsigned int c_nSquareTests                     = c_nTests/10;
    const unsigned int c_nMaxToTest                       = 1000000000; // one BILLION
    const int          c_nNumSpecialCases                 = 5;
    // samples 2 and 3: was a glitch in computing Ya + 1<<BitDiff in generalsquarerootrecursive; first catches it with 16-GIT DIGITs;
    // second for 32-BIT DIGITs.  Both are included in the general test suite -- assuming no mucking around with the random number
    // generator, and keep the same number of tests.
    // Case 4: wasn't initializing overflow space to 0
    const char         *c_szX1Samples[c_nNumSpecialCases] = { "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
                                                              "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
                                                              "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
                                                              "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
                                                              "2C69FDEA28377D30235A0418B6D281222087C5C3A321E74D975D259DD1931164"};
    const char         *c_szX2Samples[c_nNumSpecialCases] = { "2DC9CB351A2EC0743A75E864C98231D8CA3BE5A4C44B11C80DB357D84AF3DD57048424C5F46D891DDA9F1A8F94F2A1283D70872F0BB35DF8B61DD0EA1E98B777FDBB0CCC52F186F058859A1DC1339807ED17B9DBF3ADC4B01EA32030B843062CDC2B96EEFE2296F906B78C00A77C03D0BB90B1EB653F449CB5758D3E91C9D771A1D51A0E01A7D6837405566DE1460F20C87BE5E48CB11BA82F039EE7624479828EF92B50A568A31A757F9ED7484829D276B70988CF8AC6FE7CFC173E250A78DB2515A018728C9C891A7349F1F5780000666415DCDA930309CD4FFD9814B3A23727EA8F08347B9CDDB4717DAF430F81087AE03C2295D2CE77942C9787A716059195764C05F3DCC35FD5499F44CA85D984D3CDF4DF2A8F673283026ADF984CEE25B1FA6D32F8976D9D4F0A54246490764FD208F4D502524A658C823BB3E1AAEA6FFDF5C9F2CED33761320383022B2805861AB23008C7E1347CDE9A1058BCCAC72A392673E93DF801B7D1C550D2778574848C2ADEBC63452323ED7A2F60A1829351698CC2FB50ADE6EABC1F21C7E41EF0E3490F7474FFC655456A911C9F4BEA9B20CC694B4A4FDA4486C6209B5549AAE781B342A6F404E9480E46909E29B3596D13E53AE43BC5A6BA560018A530C12207786BE16B3F1C78B8E9B264B9511167D5E574BFA3717A792466BB96644AA5BD3C23534DF8993179A381213FB4AAE1ECE291",
                                                              "B5B69A841FE2D0624A281D51A71AC13326E14C6A3E40A1D8930579B20CAE2EE6",
                                                              "958727BC228E63703EB928751B0B19EEC95B6F65E8125D5472EC85057D63217A8D8EBC38583C2C99A4FA8A7E14D2F6098D7CDC3108C57BF083E874B8D99C1704",
                                                              "B2153727879D384FB797069470E63E1F85F68006D34FE87D8BCA5113184919C773982AAB904B06E8B74A99C583D08E9339A7E51D514A937ADACBE1E9851E518714A2C793EE9AB511935A0F72B8EBB91AC8DF487C831BB8808754EF067B02C5399B8647777043088B606B3000EE42124358930359571C38EDC9A66671F89FE70D4DD8242C2243FF557360071A42202ADE4EF7B02CFBE9366314476F723AE16973B16A17CB52D5DCAD635EDCA51111D3FA507E28AEDB5E13BF1DFA7391BEF43C198A511AAC8D74201504C73AC9F9E11DE743DA85D4A5976F22DCC21C94414391F0E0E16666A2DC8E4B6D3EE9EED89A5A344C011FD747EE2EEB84E35485C27ADB27",
                                                              "3F30BAC554E29F022B3923040481476AE48765001E19B0367EFA3B79D5034216B03F757CECBA0984F0C04C9D4F57827D86A3BC31A9097D3AA8BEDB83008CEDE7"};
    bool               bTestWorked    = false;
    DIGIT              *pnWorkspace   = (DIGIT *) malloc(sizeof(DIGIT)*100000000); // plenty for this test
    CBigInteger nFoo;
    nFoo.Reserve(100000);
    // test square root function: Newton
    for(int nBitSize=c_nMinBitSize; nBitSize<=c_nMaxBitSize; nBitSize *= 2)
    {
        // want to make sure we hit 3-DIGIT numbers, too
        if(_DIGIT_SIZE_IN_BITS*4 == nBitSize) nBitSize -= _DIGIT_SIZE_IN_BITS;
        else if(_DIGIT_SIZE_IN_BITS*6 == nBitSize) nBitSize -= (2*_DIGIT_SIZE_IN_BITS);
        printf("Testing square root of %i bit numbers using Newton\n", nBitSize);
        for(int i=0;i<c_nTests; i++)
        {
            if(64==nBitSize && 0==i)
            {
                // special case: sqrt from math.h rounds in fashion we don't like for 8091A2AFC30A4730 -- make sure we handle
                // this case correctly
                nX1.SetFromHexString("8091A2AFC30A4730");
            }
            else if(i<c_nSquareTests)
            {
                // try a few perfect squares: corner cases
                nSquareRoot.SetRandom(nBitSize>>1);
                cBox.Square(nSquareRoot, nX1);
            }
            else
            {
                nX1.SetRandom(nBitSize);
            }
            nSquareRoot.Reserve(nX1.GetSize());
            nMemoryNeeds              = SquareRootNewtonMemoryNeeds(nX1.GetSize());
            pnWorkspace[nMemoryNeeds] = TEST_BUFFERGUARD;
#if(_CollectDetailedTimingData)
            SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSquareRoot.GetValue(), dwTimestamp, pnWorkspace);
#else
            SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSquareRoot.GetValue(), pnWorkspace);
#endif
            nSquareRoot.SetSize(nRootSize);
            if (eOperationSucceeded != cBox.Square(nSquareRoot, nSquare))
            {
                printf("Square failed\n");
                goto exit;
            }
            if (TEST_BUFFERGUARD != pnWorkspace[nMemoryNeeds])
            {
                printf("Newton's method for determining the square root overran allocated workspace memory\n");
                goto exit;
            }
            if (nX1 < nSquare)
            {
                printf("expected square of putative square root to be at most X.  Instead...\n");
                printf("X:      ");
                nX1.PrintHexToFile();
                printf("Square: ");
                nSquare.PrintHexToFile();
                goto exit;
            }
            nSquareRoot += 1;
            if (eOperationSucceeded != cBox.Square(nSquareRoot, nSquare))
            {
                printf("Square failed\n");
                goto exit;
            }
            if(nSquare<nX1)
            {
                printf("expected 1 + square of putative square root to be at least X.  Instead...\n");
                printf("X:          ");
                nX1.PrintHexToFile();
                printf("1 + Square: ");
                nSquare.PrintHexToFile();
                goto exit;
            }
        }
    }
    // test square root function: recursive
    for(int nBitSize=c_nMinBitSize; nBitSize<=c_nMaxBitSize; nBitSize *= 2)
    {
        // want to make sure we hit 3-DIGIT numbers, too
        if(_DIGIT_SIZE_IN_BITS*4 == nBitSize) nBitSize -= _DIGIT_SIZE_IN_BITS;
        else if(_DIGIT_SIZE_IN_BITS*6 == nBitSize) nBitSize -= (2*_DIGIT_SIZE_IN_BITS);
        printf("Testing square root of %i bit numbers using recursive method\n", nBitSize);
        for(int i=0;i<c_nTests; i++)
        {
            if (96 == nBitSize && 0 == i)
            {
                // another special case: rounding twice in Newton if not careful leads to overshooting target
                nX1.SetFromHexString("2A86474DD2566831CEF5D9");
            }
            else
            {
                do
                {
                    if(i<c_nSquareTests)
                    {
                        // try a few perfect squares: corner cases
                        nSquareRoot.SetRandom(nBitSize>>1);
                        cBox.Square(nSquareRoot, nX1);
                    }
                    else
                    {
                        nX1.SetRandom(nBitSize);
                    }
                }
                while(nX1.IsZero());
            }
            nSquareRoot.Reserve(nX1.GetSize());
            nMemoryNeeds              = SquareRootMemoryNeeds(nX1.GetSize());
            pnWorkspace[nMemoryNeeds] = TEST_BUFFERGUARD;
#if(_CollectDetailedTimingData)
            SquareRootRecursive(nX1.GetSize(), nRootSize, nX1.GetValue(), nSquareRoot.GetValue(), dwTimestamp, pnWorkspace);
#else
            SquareRootRecursive(nX1.GetSize(), nRootSize, nX1.GetValue(), nSquareRoot.GetValue(), pnWorkspace);
#endif
            nSquareRoot.SetSize(nRootSize);
            if (eOperationSucceeded != cBox.Square(nSquareRoot, nSquare))
            {
                printf("Square failed\n");
                goto exit;
            }
            if (TEST_BUFFERGUARD != pnWorkspace[nMemoryNeeds])
            {
                printf("Recursive method for determining the square root overran allocated workspace memory\n");
                goto exit;
            }
            if (nX1 < nSquare)
            {
                printf("expected square of putative square root to be at most X.  Instead...\n");
                printf("X:      ");
                nX1.PrintHexToFile();
                printf("Root:   ");
                nSquareRoot.PrintHexToFile();
                printf("Square: ");
                nSquare.PrintHexToFile();
                printf("actual: ");
#if(_CollectDetailedTimingData)
                SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSquareRoot.GetValue(), dwTimestamp, pnWorkspace);
#else
                SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSquareRoot.GetValue(), pnWorkspace);
#endif
                nSquareRoot.PrintHexToFile();
                goto exit;
            }
            nSquareRoot += 1;
            if (eOperationSucceeded != cBox.Square(nSquareRoot, nSquare))
            {
                printf("Square failed\n");
                goto exit;
            }
            if(nSquare<nX1)
            {
                printf("expected 1 + square of putative square root to be at least X.  Instead...\n");
                printf("X:          ");
                nX1.PrintHexToFile();
                printf("Root:   ");
                nSquareRoot.PrintHexToFile();
                printf("1 + Square: ");
                nSquare.PrintHexToFile();
                printf("actual: ");
#if(_CollectDetailedTimingData)
                SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSquareRoot.GetValue(), dwTimestamp, pnWorkspace);
#else
                SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSquareRoot.GetValue(), pnWorkspace);
#endif
                nSquareRoot.PrintHexToFile();
                goto exit;
            }
        }
    }
    // test square root helper function -- Newton: find the largest integer y' s.t. (x1 + y')*y' <= x2
    // Note if 0==x1, this is just the floor of the square root
    for(int nBitSize=c_nMinBitSize; nBitSize<=c_nMaxBitSize; nBitSize *= 2)
    {
        printf("Testing helper square root of %i bit numbers: Newton\n", nBitSize);
        for(int i=0;i<c_nTests; i++)
        {
            // try a few perfect squares: corner cases
            do // back end doesn't handle x2 == 0
            {
                if (i < c_nSquareTests)
                {
                    nSquareRoot.SetRandom(nBitSize >> 1);
                    cBox.Square(nSquareRoot, nX2);
                }
                else
                {
                    nX2.SetRandom(nBitSize);
                }
            }
            while(nX2.IsZero());
            // note the general function assumes x1 < x2
            if(i<2*c_nSquareTests)
            {
                nX1.SetSize(0);
            }
            else if(i<4*c_nSquareTests && 1<nX2.GetSize())
            {
                // corner cases
                size_t nDigits = 1+(i%(nX2.GetSize()-1));
                nX1.Reserve(nDigits+1);
                if(i<3*c_nSquareTests)
                {
                    for(int j=0; j<nDigits; j++)
                    {
                        nX1.GetValue()[j] = c_nClearHigh;
                    }
                }
                else
                {
                    for(int j=0; j<nDigits-1; j++)
                    {
                        nX1.GetValue()[j] = 0;
                    }
                    nX1.GetValue()[nDigits-1] = 1<<(i%_DIGIT_SIZE_IN_BITS);
                }
                nX1.SetSize(nDigits);
            }
            else
            {
                do
                {
                    nX1.SetRandom((i%11)*nBitSize/10);
                }
                while(nX2<=nX1);
                nX1.Reserve(nX1.GetSize() + 1, true); // a little extra space for internal calculations
            }
            nSquareRoot.Reserve(nX2.GetSize()+1); // +1: intermediate values might be larger
            nMemoryNeeds              = GeneralSquareRootNewtonMemoryNeeds(nX1.GetSize(), nX2.GetSize());
            pnWorkspace[nMemoryNeeds] = TEST_BUFFERGUARD;
#if(_CollectDetailedTimingData)
            GeneralSquareRootNewton(nX1.GetSize(), nX2.GetSize(), nRootSize, nX1.GetValue(), nX2.GetValue(), nSquareRoot.GetValue(), dwTimestamp, pnWorkspace);
#else
            GeneralSquareRootNewton(nX1.GetSize(), nX2.GetSize(), nRootSize, nX1.GetValue(), nX2.GetValue(), nSquareRoot.GetValue(), pnWorkspace);
#endif
            nSquareRoot.SetSize(nRootSize);
            if (eOperationSucceeded != cBox.Add(nX1, nSquareRoot, nSum))
            {
                printf("Add failed\n");
                goto exit;
            }
            if (TEST_BUFFERGUARD != pnWorkspace[nMemoryNeeds])
            {
                printf("Newton's method for determining the general square root overran allocated workspace memory\n");
                goto exit;
            }
            if (eOperationSucceeded != cBox.Multiply(nSum, nSquareRoot, nSquare))
            {
                printf("Multiply failed\n");
                goto exit;
            }
            if (nX2 < nSquare)
            {
                printf("expected square of putative twiddled square root to be at most X2.  Instead...\n");
                printf("X1:      "); nX1.PrintHexToFile();
                printf("X2:      ");
                nX2.PrintHexToFile();
                printf("Square: ");
                nSquare.PrintHexToFile();
                goto exit;
            }
            nSquareRoot += 1;
            if (eOperationSucceeded != cBox.Add(nX1, nSquareRoot, nSum))
            {
                printf("Add failed\n");
                goto exit;
            }
            if (eOperationSucceeded != cBox.Multiply(nSum, nSquareRoot, nSquare))
            {
                printf("Multiply failed\n");
                goto exit;
            }
            if(nSquare<nX2)
            {
                printf("expected square of 1 + putative twiddled square root to be at least X.  Instead...\n");
                printf("X:          ");
                nX2.PrintHexToFile();
                printf("1 + Square: ");
                nSquare.PrintHexToFile();
                goto exit;
            }
        }
    }
    // test square root helper function -- recursive: find the largest integer y' s.t. (x1 + y')*y' <= x2
    // Note if 0==x1, this is just the floor of the square root
    // Note that this is destructive -- overwrites X1, X2
    for(int nBitSize=c_nMinBitSize; nBitSize<=c_nMaxBitSize; nBitSize *= 2)
    {
        printf("Testing helper square root of %i bit numbers: Recursive\n", nBitSize);
        for(int i=0;i<c_nTests; i++)
        {
            // try a few perfect squares: corner cases
            do // back end doesn't handle x2 == 0
            {
                if (i<c_nSquareTests)
                {
                    if(0==i)
                    {
                        // square with little remainder
                        nSquareRoot.SetFromHexString("1");
                        nSquareRoot.ShiftLeft((nBitSize>>1)-1);
                    }
                    else
                    {
                        nSquareRoot.SetRandom(nBitSize>>1);
                    }
                    cBox.Square(nSquareRoot, nX2);
                }
                else
                {
                    nX2.SetRandom(nBitSize);
                }
            }
            while(nX2.IsZero());
            // note the general function assumes x1 < x2
            if(i<2*c_nSquareTests)
            {
                nX1.SetSize(0);
            }
            else if(i<4*c_nSquareTests && 1<nX2.GetSize())
            {
                // corner cases
                size_t nDigits = 1+(i%(nX2.GetSize()-1));
                nX1.Reserve(nDigits+1);
                if(i<3*c_nSquareTests)
                {
                    for(int j=0; j<nDigits; j++)
                    {
                        nX1.GetValue()[j] = c_nClearHigh;
                    }
                }
                else
                {
                    for(int j=0; j<nDigits-1; j++)
                    {
                        nX1.GetValue()[j] = 0;
                    }
                    nX1.GetValue()[nDigits-1] = 1<<(i%_DIGIT_SIZE_IN_BITS);
                }
                nX1.SetSize(nDigits);
            }
            else
            {
                do
                {
                    nX1.SetRandom((i%21)*nBitSize/20);
                }
                while(nX2<=nX1);
            }
            nX1Copy.Reserve(nX2.GetSize() + 1); // needs extra space for internal calculations
            nX2Copy.Reserve(nX2.GetSize() + 1); // needs extra space for internal calculations
            nX1Copy = nX1;
            nX2Copy = nX2;
            nSquareRoot.Reserve(nX2.GetSize()+1); // +1: intermediate values might be larger
            nMemoryNeeds              = GeneralSquareRootRecursiveMemoryNeeds(nX1.GetSize(), nX2.GetSize());
            pnWorkspace[nMemoryNeeds] = TEST_BUFFERGUARD;
#if(_CollectDetailedTimingData)
            GeneralSquareRootRecursive(nX1Copy.GetSize(), nX2Copy.GetSize(), nRootSize, nX1Copy.GetValue(), nX2Copy.GetValue(), nSquareRoot.GetValue(), dwTimestamp, pnWorkspace);
#else
            GeneralSquareRootRecursive(nX1Copy.GetSize(), nX2Copy.GetSize(), nRootSize, nX1Copy.GetValue(), nX2Copy.GetValue(), nSquareRoot.GetValue(), pnWorkspace);
#endif
            nSquareRoot.SetSize(nRootSize);
            if (eOperationSucceeded != cBox.Add(nX1, nSquareRoot, nSum))
            {
                printf("Add failed\n");
                goto exit;
            }
            if (TEST_BUFFERGUARD != pnWorkspace[nMemoryNeeds])
            {
                printf("Recursive method for determining the general square root overran allocated workspace memory\n");
                goto exit;
            }
            if (eOperationSucceeded != cBox.Multiply(nSum, nSquareRoot, nSquare))
            {
                printf("Multiply failed\n");
                goto exit;
            }
            if (nX2 < nSquare)
            {
                printf("(x1 + root)*root to be at most X2.  Instead...\n");
                printf("X1:               "); nX1.PrintHexToScreen();
                printf("X2:               "); nX2.PrintHexToScreen();
                printf("(x1 + root)*root: "); nSquare.PrintHexToScreen();
#if(_CollectDetailedTimingData)
                GeneralSquareRootNewton(nX1.GetSize(), nX2.GetSize(), nRootSize, nX1.GetValue(), nX2.GetValue(), nFoo.GetValue(), dwTimestamp, pnWorkspace);
#else
                GeneralSquareRootNewton(nX1.GetSize(), nX2.GetSize(), nRootSize, nX1.GetValue(), nX2.GetValue(), nFoo.GetValue(), pnWorkspace);
#endif
                nFoo.SetSize(nRootSize);
                printf("Root:             "); nSquareRoot.PrintHexToFile();
                printf("Root (Newton):    "); nFoo.PrintHexToFile();
                goto exit;
            }
            nSquareRoot += 1;
            if (eOperationSucceeded != cBox.Add(nX1, nSquareRoot, nSum))
            {
                printf("Add failed\n");
                goto exit;
            }
            if (eOperationSucceeded != cBox.Multiply(nSum, nSquareRoot, nSquare))
            {
                printf("Multiply failed\n");
                goto exit;
            }
            if(nSquare<nX2)
            {
                nSquareRoot -= 1;
                printf("(x1 + 1 + root)*(1 + root) to be at least X2.  Instead...\n");
                printf("X1:                         "); nX1.PrintHexToScreen();
                printf("X2:                         "); nX2.PrintHexToScreen();
                printf("(x1 + 1 + root)*(1 + root): "); nSquare.PrintHexToScreen();
                printf("Root:                       "); nSquareRoot.PrintHexToFile();
#if(_CollectDetailedTimingData)
                GeneralSquareRootNewton(nX1.GetSize(), nX2.GetSize(), nRootSize, nX1.GetValue(), nX2.GetValue(), nFoo.GetValue(), dwTimestamp, pnWorkspace);
#else
                GeneralSquareRootNewton(nX1.GetSize(), nX2.GetSize(), nRootSize, nX1.GetValue(), nX2.GetValue(), nFoo.GetValue(), pnWorkspace);
#endif
                nFoo.SetSize(nRootSize);
                printf("Root (Newton):              "); nFoo.PrintHexToFile();
                goto exit;
            }
        }
    }
    // special cases -- individual test cases for which previous versions of the code had trouble
    for(int i=0;i<c_nNumSpecialCases; i++)
    {
        nX1.SetFromHexString(c_szX1Samples[i]);
        nX2.SetFromHexString(c_szX2Samples[i]);
        nX1Copy.Reserve(nX2.GetSize() + 2); // needs extra space for internal computations; final extra DIGIT for buffer guard
        nX2Copy.Reserve(nX2.GetSize() + 2); // needs extra DIGIT for internal computations; second extra DIGIT for buffer guard
        nX1Copy                               = nX1;
        nX2Copy                               = nX2;
        nX1Copy.GetValue()[nX2.GetSize() + 1] = TEST_BUFFERGUARD;
        nX2Copy.GetValue()[nX2.GetSize() + 1] = TEST_BUFFERGUARD;
        nSquareRoot.Reserve(nX2Copy.GetSize() + 1); // +1: intermediate values might be larger
#if(_CollectDetailedTimingData)
        GeneralSquareRootRecursive(nX1Copy.GetSize(), nX2Copy.GetSize(), nRootSize, nX1Copy.GetValue(), nX2Copy.GetValue(), nSquareRoot.GetValue(), dwTimestamp, pnWorkspace);
#else
        GeneralSquareRootRecursive(nX1Copy.GetSize(), nX2Copy.GetSize(), nRootSize, nX1Copy.GetValue(), nX2Copy.GetValue(), nSquareRoot.GetValue(), pnWorkspace);
#endif
        nSquareRoot.SetSize(nRootSize);
        if (TEST_BUFFERGUARD != nX2Copy.GetValue()[nX2.GetSize() + 1])
        {
            printf("Overran x2 buffer\n");
        }
        if (TEST_BUFFERGUARD != nX1Copy.GetValue()[nX2.GetSize() + 1])
        {
            printf("Overran x1 buffer\n");
            goto exit;
        }
        if (TEST_BUFFERGUARD != nX2Copy.GetValue()[nX2.GetSize() + 1])
        {
            printf("Overran x2 buffer\n");
            goto exit;
        }
        if (eOperationSucceeded != cBox.Add(nX1, nSquareRoot, nSum))
        {
            printf("Add failed\n");
            goto exit;
        }
        if (eOperationSucceeded != cBox.Multiply(nSum, nSquareRoot, nSquare))
        {
            printf("Multiply failed\n");
            goto exit;
        }
        if (nX2<nSquare)
        {
            printf("expected (X1+Y)Y to be at most X2.  Instead...\n");
            printf("X1:         "); nX1.PrintHexToFile();
            printf("X2:         "); nX2.PrintHexToFile();
            printf("(X1+Y)Y:    "); nSquare.PrintHexToFile();
            printf("Y:          "); nSquareRoot.PrintHexToFile();
#if(_CollectDetailedTimingData)
            GeneralSquareRootNewton(nX1.GetSize(), nX2.GetSize(), nRootSize, nX1.GetValue(), nX2.GetValue(), nSquareRoot.GetValue(), dwTimestamp, pnWorkspace);
#else
            GeneralSquareRootNewton(nX1.GetSize(), nX2.GetSize(), nRootSize, nX1.GetValue(), nX2.GetValue(), nSquareRoot.GetValue(), pnWorkspace);
#endif
            nSquareRoot.SetSize(nRootSize);
            printf("Y (Newton): "); nSquareRoot.PrintHexToFile();
            goto exit;
        }
        nSquareRoot += 1;
        if (eOperationSucceeded != cBox.Add(nX1, nSquareRoot, nSum))
        {
            printf("Add failed\n");
            goto exit;
        }
        if (eOperationSucceeded != cBox.Multiply(nSum, nSquareRoot, nSquare))
        {
            printf("Multiply failed\n");
            goto exit;
        }
        if (nSquare < nX2)
        {
            printf("expected X < (X1+1+Y)(1+Y).  Instead...\n");
            printf("X1:            "); nX1.PrintHexToFile();
            printf("X2:            "); nX2.PrintHexToFile();
            printf("(X1+1+Y)(1+Y): "); nSquare.PrintHexToFile();
            printf("1+Y:           "); nSquareRoot.PrintHexToFile();
#if(_CollectDetailedTimingData)
            GeneralSquareRootNewton(nX1.GetSize(), nX2.GetSize(), nRootSize, nX1.GetValue(), nX2.GetValue(), nSquareRoot.GetValue(), dwTimestamp, pnWorkspace);
#else
            GeneralSquareRootNewton(nX1.GetSize(), nX2.GetSize(), nRootSize, nX1.GetValue(), nX2.GetValue(), nSquareRoot.GetValue(), pnWorkspace);
#endif
            nSquareRoot.SetSize(nRootSize);
            nSquareRoot += 1;
            printf("1+Y (Newton):  "); nSquareRoot.PrintHexToFile();
            goto exit;
        }
    }
    // finally, a few tests using the arithmetic box to make sure that interface is working properly
    for(int i=0;i<c_nTests; i++)
    {
        nX1.SetRandom(i*_DIGIT_SIZE_IN_BITS);
        nX1Copy = nX1;
        cBox.SQRT(nX1Copy, nX1Copy); // if we can overwrite x, we can put the result anywhere
        cBox.Square(nX1Copy, nX2);
        if(nX1<nX2)
        {
            printf("expected square of putative square root of x to be at most x\n");
            goto exit;
        }
        nX1Copy += 1;
        cBox.Square(nX1Copy, nX2);
        if(nX2<=nX1)
        {
            printf("expected square of (sqt(x)+1) to be greater than x\n");
            goto exit;
        }
    }
    bTestWorked = true;
exit:
    free(pnWorkspace);
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestPower()
{
    CArithmeticBox     cBox;
    CWorkspace         workspace;
    CBigIntegerForTest nX, nPowerReal, nPowerComputed;
    size_t             nPowerSize, nMemoryNeeds;
    bool bTestWorked = false;
    nPowerReal.Reserve(256*32);
    nPowerComputed.Reserve(256*32 + 1);
    workspace.Reserve(200000000);
    // special case that has caused Issues in the past
    nX.SetFromHexString("7F76A72");
    // brute force to compute the power (hence, relatively small powers)
    nPowerReal.SetFromHexString("1");
    for(unsigned int i=0; i<77; i++)
    {
        cBox.Multiply(nX, nPowerReal, nPowerComputed);
        nPowerReal = nPowerComputed;
    }
    cBox.Power(nX, 77, nPowerComputed);
    if (nPowerComputed != nPowerReal)
    {
        printf("Problem computing power:\n");
        printf("Power: 77\tX: ");
        nX.PrintHexToFile();
        printf("Computed power: ");
        nPowerComputed.PrintHexToFile();
        printf("actual power:   ");
        nPowerReal.PrintHexToFile();
        goto exit;
    }
    for(int j=0; j<2; j++)
    {
        // first pass: some powers of random values
        // second pass: powers of maximum value for size
        if(0==j) nX.SetRandom(256);
        else     nX.SetFromHexString("ffffffffffffffffffffffffffffffff");
        for(unsigned int n=1; n<=32; n++)
        {
            // brute force to compute the power (hence, relatively small powers)
            nPowerReal.SetFromHexString("1");
            for(unsigned int i=0; i<n; i++)
            {
                cBox.Multiply(nX, nPowerReal, nPowerComputed);
                nPowerReal = nPowerComputed;
            }
            nMemoryNeeds                              = PowerMemoryNeeds(nX.GetValue(), nX.GetSize(), n);
            workspace.GetSpace()[nMemoryNeeds]        = TEST_BUFFERGUARD;
            nPowerComputed.GetValue()[nX.GetSize()*n] = TEST_BUFFERGUARD;
            Power(nX.GetSize(), nPowerSize, n, nX.GetValue(), nPowerComputed.GetValue(), workspace.GetSpace());
            if (TEST_BUFFERGUARD != workspace.GetSpace()[nMemoryNeeds])
            {
                printf("Overran workspace in computing power\n");
                goto exit;
            }
            if (TEST_BUFFERGUARD != nPowerComputed.GetValue()[nX.GetSize()*n])
            {
                printf("Overran output buffer in computing power\n");
                goto exit;
            }
            nPowerComputed.SetSize(nPowerSize);
            if (nPowerComputed != nPowerReal)
            {
                printf("Problem computing power:\n");
                printf("Power: %u\tX: ", n);
                nX.PrintHexToFile();
                printf("Computed power: ");
                nPowerComputed.PrintHexToFile();
                printf("actual power:   ");
                nPowerReal.PrintHexToFile();
                goto exit;
            }
        }
    }
    bTestWorked = true;
exit:
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestNthRootHelper()
{
    const unsigned int c_nIterations = 1000;
    unsigned int       nTimePower, nTimeRoot;
    size_t             nRootSize, nRootSizeHint, nRoot, nMemoryNeeds;
    CArithmeticBox     cBox;
    CBigIntegerForTest nTrueRoot, nRootTruncated, nY, nComputedRoot;
    bool bTestWorked = false;
    printf("Testing nth root recursive helper function\n");
    for(nRoot=2; nRoot<33; nRoot++)
    {
        printf("Testing %u root\n", nRoot);
        for(size_t nRootSize=4; nRootSize<11; nRootSize++)
        {
            for(unsigned int nIteration=0; nIteration<c_nIterations; nIteration++)
            {
                nTrueRoot.SetRandom(nRootSize*_DIGIT_SIZE_IN_BITS);
#if _DEBUG
                for(int nBigAdd=0; nBigAdd<2; nBigAdd++)
                {
                    CUnsignedArithmeticHelper::s_bForceBigAddForValidatingNthRoot = (0==nBigAdd);
#else
                {
#endif
                    cBox.Power(nTrueRoot, nRoot, nY);
                    // try a y value one larger than the root to its power first
                    nY += 1;
                    nRootTruncated.Reserve(nTrueRoot.GetSize() + 1); // "hint" -- starting point for the procedure -- expected to have one extra DIGIT, initialize to 0, for overflow
                    nRootTruncated = nTrueRoot;
                    for(int i=0; i<nTrueRoot.GetSize()/2 - 1; i++)
                    {
                        nRootTruncated.m_pnValue[i] = 0;
                    }
                    nRootTruncated.m_pnValue[nTrueRoot.GetSize()] = 0; // overflow guard
                    nRootSizeHint = nRootTruncated.GetSize();
                    nMemoryNeeds  = NthRootMemoryNeeds(nY.GetSize(), nRoot);
                    cBox.m_Workspace.Reserve(nMemoryNeeds + 1);
                    cBox.m_Workspace.GetSpace()[nMemoryNeeds] = TEST_BUFFERGUARD;
                    NthRootRecursiveWithHint(nRoot, nRootSizeHint, nY.GetSize(), (nTrueRoot.GetSize()/2 - 1)*_DIGIT_SIZE_IN_BITS, nRootTruncated.GetValue(), nY.GetValue(), cBox.m_Workspace.GetSpace());
                    if(TEST_BUFFERGUARD != cBox.m_Workspace.GetSpace()[nMemoryNeeds])
                    {
                        printf("Nth root test overran purputed workspace needs\n");
                        goto exit;
                    }
                    // nRootTruncated should be replaced with the true root
                    nRootTruncated.SetSize(nRootSizeHint);
                    if(nRootTruncated != nTrueRoot)
                    {
                        printf("Helper function failure!\n");
                        printf("Y:                "); nY.PrintHexToFile();
                        printf("sqrt(Y):          "); nTrueRoot.PrintHexToFile();
                        printf("computed sqrt(Y): "); nRootTruncated.PrintHexToFile();
                        goto exit;
                    }
                    // try with Y the equal to root^power
                    nY -= 1;
                    nRootTruncated.Reserve(nTrueRoot.GetSize() + 1); // "hint" -- starting point for the procedure -- expected to have one extra DIGIT, initialize to 0, for overflow
                    nRootTruncated = nTrueRoot;
                    for(int i=0; i<nTrueRoot.GetSize()/2 - 1; i++)
                    {
                        nRootTruncated.m_pnValue[i] = 0;
                    }
                    nRootTruncated.m_pnValue[nTrueRoot.GetSize()] = 0; // overflow guard
                    nRootSizeHint = nRootTruncated.GetSize();
                    nMemoryNeeds  = NthRootMemoryNeeds(nY.GetSize(), nRoot);
                    cBox.m_Workspace.Reserve(nMemoryNeeds + 1);
                    cBox.m_Workspace.GetSpace()[nMemoryNeeds] = TEST_BUFFERGUARD;
                    NthRootRecursiveWithHint(nRoot, nRootSizeHint, nY.GetSize(), (nTrueRoot.GetSize()/2 - 1)*_DIGIT_SIZE_IN_BITS, nRootTruncated.GetValue(), nY.GetValue(), cBox.m_Workspace.GetSpace());
                    if(TEST_BUFFERGUARD != cBox.m_Workspace.GetSpace()[nMemoryNeeds])
                    {
                        printf("Nth root test overran purputed workspace needs\n");
                        goto exit;
                    }
                    // nRootTruncated should be replaced with the true root
                    nRootTruncated.SetSize(nRootSizeHint);
                    if(nRootTruncated != nTrueRoot)
                    {
                        printf("Helper function failure!\n");
                        printf("Y:                "); nY.PrintHexToFile();
                        printf("sqrt(Y):          "); nTrueRoot.PrintHexToFile();
                        printf("computed sqrt(Y): "); nRootTruncated.PrintHexToFile();
                        goto exit;
                    }
                    // repeat, but with a number one less than a perfect power
                    nY             -= 1;
                    nTrueRoot      -= 1;
                    nRootTruncated =  nTrueRoot;
                    for(int i=0; i<nTrueRoot.GetSize()/2 - 1; i++)
                    {
                        nRootTruncated.m_pnValue[i] = 0;
                    }
                    nRootTruncated.m_pnValue[nTrueRoot.GetSize()] = 0; // overflow guard
                    nRootSizeHint = nRootTruncated.GetSize();
                    NthRootRecursiveWithHint(nRoot, nRootSizeHint, nY.GetSize(), (nTrueRoot.GetSize()/2 - 1)*_DIGIT_SIZE_IN_BITS, nRootTruncated.GetValue(), nY.GetValue(), cBox.m_Workspace.GetSpace());
                    if (TEST_BUFFERGUARD != cBox.m_Workspace.GetSpace()[nMemoryNeeds])
                    {
                        printf("Nth root test overran purputed workspace needs\n");
                        goto exit;
                    }
                    // nRootTruncated should be replaced with the true root
                    nRootTruncated.SetSize(nRootSizeHint);
                    if(nRootTruncated != nTrueRoot)
                    {
                        printf("Helper function failure!\n");
                        printf("Y:                "); nY.PrintHexToFile();
                        printf("sqrt(Y):          "); nTrueRoot.PrintHexToFile();
                        printf("computed sqrt(Y): "); nRootTruncated.PrintHexToFile();
                        goto exit;
                    }
                }
            }
        }
    }
    /*
    // now: a REALLY big problem
#if (16==_DIGIT_SIZE_IN_BITS)
    nRoot = 60000;
#else
    nRoot = 1000000;
#endif
    nTrueRoot.SetRandom(50*_DIGIT_SIZE_IN_BITS);
    nTimePower = ::GetTickCount();
    cBox.Power(nTrueRoot, nRoot, nY);
    nTimePower = ::GetTickCount() - nTimePower;
    nY += 1; // start one over root
    printf("Large trials: %uth root of a %i BYTE number\n",nRoot,nY.GetSize()*sizeof(DIGIT));
    nRootTruncated.Reserve(nTrueRoot.GetSize() + 1); // "hint" -- starting point for the procedure -- expected to have one extra DIGIT, initialize to 0, for overflow
    nRootTruncated = nTrueRoot;
    for(int i=0; i<nTrueRoot.GetSize()/2 - 1; i++)
    {
        nRootTruncated.m_pnValue[i] = 0;
    }
    nRootTruncated.m_pnValue[nTrueRoot.GetSize()] = 0; // overflow guard
    nRootSizeHint = nRootTruncated.GetSize();
    nMemoryNeeds  = NthRootMemoryNeeds(nY.GetSize(), nRoot);
    cBox.m_Workspace.Reserve(nMemoryNeeds + 1);
    cBox.m_Workspace.GetSpace()[nMemoryNeeds] = TEST_BUFFERGUARD;
    nTimeRoot = ::GetTickCount();
    NthRootRecursiveWithHint(nRoot, nRootSizeHint, nY.GetSize(), nRootTruncated.GetValue(), nY.GetValue(), cBox.m_Workspace.GetSpace());
    nTimeRoot = ::GetTickCount() - nTimeRoot;
    printf("Number one over root to power: %u milliseconds to construct, %u for root\n", nTimePower, nTimeRoot);
    if (TEST_BUFFERGUARD != cBox.m_Workspace.GetSpace()[nMemoryNeeds])
    {
        printf("Nth root test overran supposed workspace needs\n");
        goto exit;
    }
    // nRootTruncated should be replaced with the true root
    nRootTruncated.SetSize(nRootSizeHint);
    if(nRootTruncated != nTrueRoot)
    {
        printf("Helper function failure!\n"); // don't print -- too darned big for it to be useful
        goto exit;
    }
    nY -= 1; // the root itself
    nRootTruncated.Reserve(nTrueRoot.GetSize() + 1); // "hint" -- starting point for the procedure -- expected to have one extra DIGIT, initialize to 0, for overflow
    nRootTruncated = nTrueRoot;
    for(int i=0; i<nTrueRoot.GetSize()/2 - 1; i++)
    {
        nRootTruncated.m_pnValue[i] = 0;
    }
    nRootTruncated.m_pnValue[nTrueRoot.GetSize()] = 0; // overflow guard
    nRootSizeHint = nRootTruncated.GetSize();
    nMemoryNeeds  = NthRootMemoryNeeds(nY.GetSize(), nRoot);
    cBox.m_Workspace.Reserve(nMemoryNeeds + 1); // *5: for newton -- it needs more space debug resolve todo
    cBox.m_Workspace.GetSpace()[nMemoryNeeds] = TEST_BUFFERGUARD;
    nTimeRoot = ::GetTickCount();
    NthRootRecursiveWithHint(nRoot, nRootSizeHint, nY.GetSize(), nRootTruncated.GetValue(), nY.GetValue(), cBox.m_Workspace.GetSpace());
    nTimeRoot = ::GetTickCount() - nTimeRoot;
    printf("Number equal root to power: %u for root\n", nTimeRoot);
    if (TEST_BUFFERGUARD != cBox.m_Workspace.GetSpace()[nMemoryNeeds])
    {
        printf("Nth root test overran supposed workspace needs\n");
        goto exit;
    }
    // nRootTruncated should be replaced with the true root
    nRootTruncated.SetSize(nRootSizeHint);
    if(nRootTruncated != nTrueRoot)
    {
        printf("Helper function failure!\n");
        goto exit;
    }
    // repeat, but with a number one less than a perfect power
    nY             -= 1;
    nTrueRoot      -= 1;
    nRootTruncated =  nTrueRoot;
    for(int i=0; i<nTrueRoot.GetSize()/2 - 1; i++)
    {
        nRootTruncated.m_pnValue[i] = 0;
    }
    nRootTruncated.m_pnValue[nTrueRoot.GetSize()] = 0; // overflow guard
    nRootSizeHint = nRootTruncated.GetSize();
    nTimeRoot = ::GetTickCount();
    NthRootRecursiveWithHint(nRoot, nRootSizeHint, nY.GetSize(), nRootTruncated.GetValue(), nY.GetValue(), cBox.m_Workspace.GetSpace());
    nTimeRoot = ::GetTickCount() - nTimeRoot;
    printf("Number one less than root to power: %u for root\n", nTimeRoot);
    if (TEST_BUFFERGUARD != cBox.m_Workspace.GetSpace()[nMemoryNeeds])
    {
        printf("Nth root test overran supposed workspace needs\n");
        goto exit;
    }
    // nRootTruncated should be replaced with the true root
    nRootTruncated.SetSize(nRootSizeHint);
    if(nRootTruncated != nTrueRoot)
    {
        printf("Helper function failure!\n");
        goto exit;
    }
    */
    /* Don't do it!  This took over 3 days on my machine and hadn't completed when then system decided it was time to reboot
    nRootTruncated.Reserve(2*nY.GetSize()+1); // much bigger than needed -- but Newton needs more space than the basic here.  Lazy; not checking how much more
    nTimeRoot = ::GetTickCount();
    NthRootNewton(nY.GetSize(), nRoot, nRootSize, nY.GetValue(), nRootTruncated.GetValue(), cBox.m_Workspace.GetSpace());
    nTimeRoot = ::GetTickCount() - nTimeRoot;
    printf("Number one less than root to power: %u for root (Newton)\n", nTimeRoot);
    */
    bTestWorked = true;
exit:
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestNthRoot()
{
    CArithmeticBox     cBox;
    unsigned int       i, j, n, nMemoryNeedsRoot, nMemoryNeedsPower;
    size_t             nRootSize, nPowerSize;
    CBigIntegerForTest nX, nRoot, nPower, nXCopy;
    DIGIT              *pWorkspace;
    const unsigned int one_BILLION                           = 1000000000;
    const unsigned int one_MILLION                           = 1000000;
    const unsigned int c_nMaxRoot                            = 320, c_nMaxSize = 100;
    const size_t       c_nMaxOverflow                        = 1 + (c_nMaxRoot + _DIGIT_SIZE_IN_BITS - 1)/_DIGIT_SIZE_IN_BITS; // max overflow might get from computing power, in DIGITS
    const int          c_nNumSpecialCases                    = 1;
    bool               bTestWorked                           = false;
    const char         *szSpecialCase[c_nNumSpecialCases]    = { "5CA11FD105915F7D1EB73DF930603D58212A4F205FF5D0A46F0AD8EBA0327FE8A389F8CDC1BB1C2F817B48BC63ED3A478DC4AEE812D687F2A3DA3576602D23239036E734FB4CF833A9CEA655C425141D628DFF27EA3BFDB1E9CC08CAFF9A0CCDBACB35EC11D1C5993D232E7BC3E62DBB5647AB626451249004F34B4009F5BD66F6AB6A1D9F1393AF222FFB260C49263F5FF65D633E832E81FCA1386F4CF8F7AD597A52308420B5057DE5658F8CACE109B1DDFD31757D8CB1156B482ED5A0BBA2391BF4CADD42BC6BB578082B72A87FB9C381B412472AF091D5243395F2284B852BB39CD4070579F16E5CBBB32A1A622E4BA5EE8F31B64ACF01E0F5FC310C29D404A3D176" };
    DIGIT              nSpecialCaseRoots[c_nNumSpecialCases] = { 77 };
    cBox.m_Workspace.Reserve(one_BILLION);
    pWorkspace = cBox.m_Workspace.GetSpace();
    nX.Reserve(c_nMaxSize+1); // one extra DIGIT for overflow -- recall nth root backend is destructive
    nXCopy.Reserve(c_nMaxSize);
    nRoot.Reserve(max(c_nMaxRoot, c_nMaxSize)+1); 
    nPower.Reserve(c_nMaxSize + c_nMaxOverflow);
#ifdef _DEBUG
    for(int nBigAdd=0; nBigAdd<2; nBigAdd++)
    {
        CUnsignedArithmeticHelper::s_bForceBigAddForValidatingNthRoot = (0 == nBigAdd);
#else
    {
#endif
        printf("testing nth root: special cases\n");
        // some individual instances that have, in the past, caused Problems
        for(int i=0; i<c_nNumSpecialCases; i++)
        {
            nX.SetFromHexString(szSpecialCase[i]);
            n      = nSpecialCaseRoots[i];
            nXCopy = nX; // since the backend procedures destroy x to make higher-level functions more efficient
            NthRootNewton(nXCopy.GetSize(), n, nRootSize, nXCopy.GetValue(), nRoot.GetValue(), pWorkspace);
            nRoot.SetSize(nRootSize);
            Power(nRootSize, nPowerSize, n, nRoot.GetValue(), nPower.GetValue(), pWorkspace);
            nPower.SetSize(nPowerSize);
            if (nX < nPower)
            {
                printf("Newton: %u root\n",n);
                printf("%u root of x, taken to %u power, should be at most x\n", n,n);
                printf("X:                                \t"); nX.PrintHexToFile();
                printf("%u root of X, taken to %u power:\t", n,n); nPower.PrintHexToFile();
                printf("The root:                         \t"); nRoot.PrintHexToFile();
                nPower = nRoot;
                for (int i=0; i<n-1; i++)
                {
                    cBox.Multiply(nPower, nRoot, nXCopy);
                    nPower = nXCopy;
                }
                printf("%u root of X, taken to Nth power:\t", n); nPower.PrintHexToFile();
                goto exit;
            }
            nRoot += 1;
            Power(nRootSize, nPowerSize, n, nRoot.GetValue(), nPower.GetValue(), pWorkspace);
            nPower.SetSize(nPowerSize);
            if (nPower < nX)
            {
                printf("Newton: %u root\n",n);
                printf("%u root of x, taken to %u power, should be at greater than x\n",n+1,n+1);
                printf("X:                                 \t"); nX.PrintHexToFile();
                printf("%u root of X, taken to %u power:\t",n+1,n+1); nPower.PrintHexToFile();
                printf("The root + 1:                      \t"); nRoot.PrintHexToFile();
                goto exit;
            }
        }
        printf("testing nth root: general\n");
        for (n=2; n <= c_nMaxRoot; n++)
        {
            // first, test to make sure that the newton method is working properly
            printf("Testing Newton:    %u root\n",n);
            for (i=1; i<100000; i++)
            {
                if(i<32768)
                {
                    nX.SetSize(1);
                    nX.GetValue()[0] = i;
                }
                else if (i<65536)
                {
                    nX.SetSize(1);
                    nX.GetValue()[0] = c_nClearHigh - i + 32768;
                }
                else
                {
                    nX.SetRandom(512);
                }
                nXCopy = nX; // since the backend procedures destroy x to make higher-level functions more efficient
                NthRootNewton(nXCopy.GetSize(), n, nRootSize, nXCopy.GetValue(), nRoot.GetValue(), pWorkspace);
                nRoot.SetSize(nRootSize);
                Power(nRootSize, nPowerSize, n, nRoot.GetValue(), nPower.GetValue(), pWorkspace);
                nPower.SetSize(nPowerSize);
                if (nX < nPower)
                {
                    printf("Newton:\n");
                    printf("nth root of x, taken to nth power, should be at most x\n");
                    printf("X:                                 "); nX.PrintHexToFile();
                    printf("Nth root of X, taken to Nth power: "); nPower.PrintHexToFile();
                    goto exit;
                }
                nRoot += 1;
                Power(nRootSize, nPowerSize, n, nRoot.GetValue(), nPower.GetValue(), pWorkspace);
                nPower.SetSize(nPowerSize);
                if (nPower < nX)
                {
                    printf("Newton:\n");
                    printf("1 + nth root of x, taken to nth power, should be at greater than x\n");
                    printf("X:                                     "); nX.PrintHexToFile();
                    printf("1 + Nth root of X, taken to Nth power: "); nPower.PrintHexToFile();
                    goto exit;
                }
            }
            printf("Testing optimized: %i root\n", n);
            // next, test the hopefully-faster method: small tests
            for (size_t nSize=2; nSize<=c_nMaxSize; nSize++)
            {
                nMemoryNeedsRoot = NthRootMemoryNeeds(nSize, n);
                for(i=0;i<3;i++)
                {
                    switch (i)
                    {
                    case 0:
                        // minimum nSize-DIGIT number
                        nXCopy.SetSize(nSize);
                        for(j=0;j<nSize-1;j++) nXCopy.m_pnValue[j] = 0;
                        nXCopy.m_pnValue[j] = 1;
                        break;
                    case 1:
                        // maximum nSize-DIGIT number
                        nXCopy.SetSize(nSize);
                        for(j=0;j<nSize;j++) nXCopy.m_pnValue[j] = c_nClearHigh;
                        break;
                    default:
                        // random nSize-DIGIT number
                        nXCopy.SetRandom(nSize*_DIGIT_SIZE_IN_BITS);
                    }
                    pWorkspace[nMemoryNeedsRoot] = TEST_BUFFERGUARD;
                    nX                           = nXCopy;
                    NthRoot(nX.GetSize(), n, nRootSize, nX.GetValue(), nRoot.GetValue(), pWorkspace);
                    nRoot.SetSize(nRootSize);
                    if (pWorkspace[nMemoryNeedsRoot] != TEST_BUFFERGUARD)
                    {
                        printf("Workspace overflow computing root %u of %u DIGIT number\n", n, nSize);
                        goto exit;
                    }
                    // the computed root, taken to the nth power, should be at most nX
                    nMemoryNeedsPower             = PowerMemoryNeeds(nRoot.GetValue(), nRootSize, n);
                    pWorkspace[nMemoryNeedsPower] = TEST_BUFFERGUARD;
                    Power(nRootSize, nPowerSize, n, nRoot.GetValue(), nPower.GetValue(), pWorkspace);
                    if (pWorkspace[nMemoryNeedsPower] != TEST_BUFFERGUARD)
                    {
                        printf("Workspace overflow computing power %u of %u DIGIT number\n", nRootSize, nSize);
                        goto exit;
                    }
                    nPower.SetSize(nPowerSize);
                    if (nX < nPower)
                    {
                        printf("Optimized for n = %u, size %u:\n", n, nSize);
                        printf("nth root of x, taken to nth power, should be at most x\n");
                        printf("X:                                 "); nX.PrintHexToFile();
                        printf("nth root of X, taken to Nth power: "); nPower.PrintHexToFile();
                        printf("nth root of X:                     "); nRoot.PrintHexToFile();
                        goto exit;
                    }
                    // <1+the computed root>, taken to the nth power, should be greater than nX
                    nRoot += 1;
                    nMemoryNeedsPower             = PowerMemoryNeeds(nRoot.GetValue(), nRoot.GetSize(), n);
                    pWorkspace[nMemoryNeedsPower] = TEST_BUFFERGUARD;
                    Power(nRoot.GetSize(), nPowerSize, n, nRoot.GetValue(), nPower.GetValue(), pWorkspace);
                    nPower.SetSize(nPowerSize);
                    if (pWorkspace[nMemoryNeedsPower] != TEST_BUFFERGUARD)
                    {
                        printf("Workspace overflow computing power %u of %u DIGIT number\n", nRootSize, nSize);
                        goto exit;
                    }
                    if (nPower < nX)
                    {
                        printf("Optimized for n = %u, size %u:\n", n, nSize);
                        printf("1 + nth root of x, taken to nth power, should be at greater than x\n");
                        printf("X:                                       "); nX.PrintHexToFile();
                        printf("1 + <nth root of X>, taken to Nth power: "); nPower.PrintHexToFile();
                        printf("1 + <nth root of X>:                     "); nRoot.PrintHexToFile();
                        goto exit;
                    }
                }
            }
        }
        printf("Testing, using... The Box\n");
        nX.SetRandom(8*one_MILLION);
        nXCopy = nX;
        for(DIGIT n=8*27; n<8*27+10; n++)
        {
            cBox.NthRoot(nX, n, nRoot);
            if (nX != nXCopy)
            {
                printf("uh-oh\n");
            }
            cBox.Power(nRoot, n, nPower);
      //      printf("%u %u %u %u b %u %u\n",n, nRoot.GetSize(), nPower.GetSize(),nX.GetSize(), nPower.m_pnValue[nPower.GetSize()-1], nX.m_pnValue[nX.GetSize() - 1]);
            if (nX != nXCopy)
            {
                printf("oh-uh\n");
            }
            if(nX<nPower)
            {
                printf("Oh dear -- using The Box, the %u root of a %u byte number was too large\n", n, nX.GetSize()*sizeof(DIGIT));
                goto exit;
            }
            nRoot += 1;
            cBox.Power(nRoot, n, nPower);
            if(nPower<=nX)
            {
                printf("Oh dear -- using The Box, the %u root of a %u byte number was too small\n", n, nX.GetSize()*sizeof(DIGIT));
                goto exit;
            }
        }
    }
    bTestWorked = true;
exit:
    return bTestWorked;
}

bool CArithmeticCorrectnessTester::TestAVXMultiply()
{
#if _USEAVX
    CBigIntegerForTest x, y, zAdd, zFinal, z1, z2;
    bool         bMultAdd;
    bool         bTestWorked = false;
    int          nVariation  = 1;
    DIGIT        gibberish   = 0xACDC;

    // 4-DIGIT x:
    x.Reserve(4);
    x.SetSize(4);
    for (size_t nSize = 4; nSize <= 48; nSize++)
    {
        y.Reserve(nSize);
        y.SetSize(nSize);
        z1.Reserve(x.GetSize() + y.GetSize());
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.Reserve(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        // basic multiply
        bMultAdd = false;
        for (int i = 0; i < x.GetSize(); i++) x.GetValue()[i] = (i + 1);
        for (int i = 0; i < y.GetSize(); i++) y.GetValue()[i] = (i + 1);
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult4DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }
        for (int i = 0; i < x.GetSize(); i++) x.GetValue()[i] = (i<<16);
        for (int i = 0; i < y.GetSize(); i++) y.GetValue()[i] = (i<<16);
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult4DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }
        for (int i = 0; i < x.GetSize(); i++) x.GetValue()[i] = 0xFFFFFFFF;
        for (int i = 0; i < y.GetSize(); i++) y.GetValue()[i] = 0xFFFFFFFF;
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult4DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }
        // with an internal multiply, y COULD have leading 0s
        x.SetRandom(4*_DIGIT_SIZE_IN_BITS);
        for (int i = 0; i < y.GetSize(); i++) y.GetValue()[i] = 0;
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult4DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }
        x.SetRandom(4*_DIGIT_SIZE_IN_BITS);
        y.SetRandom(nSize*_DIGIT_SIZE_IN_BITS);
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult4DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }

        // multiply/add
        bMultAdd = true;
        // first, where z is the same size as x*y
        zFinal =  z2;
        zFinal *= 2;
        zAdd   =  z2;
        z2.Reserve(x.GetSize() + y.GetSize() + 1, true);
        for (int i = z2.GetSize(); i < x.GetSize() + y.GetSize() + 1; i++) z2.GetValue()[i] = 0;
        CAVXMultiply::Mult4DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        z2.SetSize(x.GetSize() + y.GetSize() + 1);
        while (0 < z2.GetSize() && 0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z2 != zFinal)
        {
            goto exit;
        }
        // next, z smaller than x*y
        zAdd.SetFromHexString("FFFFFFFF");
        z2.SetSize(CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z2.GetValue()));
        zFinal.SetSize(CUnsignedArithmeticHelper::Add(z2.GetSize(), zAdd.GetSize(), z2.GetValue(), zAdd.GetValue(), zFinal.GetValue()));
        z2 = zAdd;
        for (int i = z2.GetSize(); i < x.GetSize() + y.GetSize() + 1; i++) z2.GetValue()[i] = 0;
        CAVXMultiply::Mult4DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        z2.SetSize(max(x.GetSize() + y.GetSize(), zAdd.GetSize()) + 1);
        while (0 < z2.GetSize() && 0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z2 != zFinal)
        {
            goto exit;
        }
        // finally, z larger than x*y
        zAdd.Reserve(x.GetSize() + y.GetSize() + 5);
        zAdd.SetSize(x.GetSize() + y.GetSize() + 5);
        zFinal.Reserve(x.GetSize() + y.GetSize() + 6);
        for(int i=0;i<zAdd.GetSize();i++) zAdd.GetValue()[i] = 0xFFFFFFFF;
        z2.SetSize(CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z2.GetValue()));
        zFinal.SetSize(CUnsignedArithmeticHelper::Add(z2.GetSize(), zAdd.GetSize(), z2.GetValue(), zAdd.GetValue(), zFinal.GetValue()));
        z2.Reserve(max(x.GetSize()+y.GetSize(), zAdd.GetSize())+1);
        z2 = zAdd;
        for (int i = z2.GetSize(); i < max(x.GetSize() + y.GetSize(), zAdd.GetSize()) + 1; i++) z2.GetValue()[i] = 0;
        CAVXMultiply::Mult4DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        z2.SetSize(max(x.GetSize() + y.GetSize(), zAdd.GetSize()) + 1);
        while (0 < z2.GetSize() && 0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z2 != zFinal)
        {
            goto exit;
        }
    }

    // 8-DIGIT x:
    nVariation = 2;
    x.Reserve(8);
    x.SetSize(8);
    for (size_t nSize=8; nSize<=96; nSize++)
    {
        y.Reserve(nSize);
        y.SetSize(nSize);
        z1.Reserve(x.GetSize() + y.GetSize());
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.Reserve(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        // basic multiply
        bMultAdd = false;
        for (int i = 0; i < x.GetSize(); i++) x.GetValue()[i] = (i + 1);
        for (int i = 0; i < y.GetSize(); i++) y.GetValue()[i] = (i + 1);
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult8DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }
        for (int i = 0; i < x.GetSize(); i++) x.GetValue()[i] = (i<<16);
        for (int i = 0; i < y.GetSize(); i++) y.GetValue()[i] = (i<<16);
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult8DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }
        for (int i = 0; i < x.GetSize(); i++) x.GetValue()[i] = 0xFFFFFFFF;
        for (int i = 0; i < y.GetSize(); i++) y.GetValue()[i] = 0xFFFFFFFF;
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult8DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }
        // with an internal multiply, y COULD have leading 0s
        x.SetRandom(8*_DIGIT_SIZE_IN_BITS);
        for (int i = 0; i < y.GetSize(); i++) y.GetValue()[i] = 0;
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult8DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }
        x.SetRandom(8*_DIGIT_SIZE_IN_BITS);
        y.SetRandom(nSize*_DIGIT_SIZE_IN_BITS);
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult8DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }

        // multiply/add
        bMultAdd = true;
        // first, where z is the same size as x*y
        zFinal =  z2;
        zFinal *= 2;
        zAdd   =  z2;
        z2.Reserve(x.GetSize() + y.GetSize() + 1, true);
        for (int i = z2.GetSize(); i < x.GetSize() + y.GetSize() + 1; i++) z2.GetValue()[i] = 0;
        CAVXMultiply::Mult8DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        z2.SetSize(x.GetSize() + y.GetSize() + 1);
        while (0 < z2.GetSize() && 0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z2 != zFinal)
        {
            goto exit;
        }
        // next, z smaller than x*y
        zAdd.SetFromHexString("FFFFFFFF");
        z2.SetSize(CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z2.GetValue()));
        zFinal.SetSize(CUnsignedArithmeticHelper::Add(z2.GetSize(), zAdd.GetSize(), z2.GetValue(), zAdd.GetValue(), zFinal.GetValue()));
        z2 = zAdd;
        for (int i = z2.GetSize(); i < x.GetSize() + y.GetSize() + 1; i++) z2.GetValue()[i] = 0;
        CAVXMultiply::Mult8DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        z2.SetSize(max(x.GetSize() + y.GetSize(), zAdd.GetSize()) + 1);
        while (0 < z2.GetSize() && 0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z2 != zFinal)
        {
            goto exit;
        }
        // finally, z larger than x*y
        zAdd.Reserve(x.GetSize() + y.GetSize() + 5);
        zAdd.SetSize(x.GetSize() + y.GetSize() + 5);
        zFinal.Reserve(x.GetSize() + y.GetSize() + 6);
        for (int i = 0; i < zAdd.GetSize(); i++) zAdd.GetValue()[i] = 0xFFFFFFFF;
        z2.SetSize(CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z2.GetValue()));
        zFinal.SetSize(CUnsignedArithmeticHelper::Add(z2.GetSize(), zAdd.GetSize(), z2.GetValue(), zAdd.GetValue(), zFinal.GetValue()));
        z2.Reserve(max(x.GetSize() + y.GetSize(), zAdd.GetSize()) + 1);
        z2 = zAdd;
        for (int i = z2.GetSize(); i < max(x.GetSize() + y.GetSize(), zAdd.GetSize()) + 1; i++) z2.GetValue()[i] = 0;
        CAVXMultiply::Mult8DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        z2.SetSize(max(x.GetSize() + y.GetSize(), zAdd.GetSize()) + 1);
        while (0 < z2.GetSize() && 0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z2 != zFinal)
        {
            goto exit;
        }
    }

    // 12-DIGIT x:
    x.Reserve(12);
    x.SetSize(12);
    nVariation = 3;
    for (size_t nSize = 12; nSize <= 144; nSize++)
    {
        y.Reserve(nSize);
        y.SetSize(nSize);
        z1.Reserve(x.GetSize() + y.GetSize());
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.Reserve(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        // basic multiply
        bMultAdd = false;
        for (int i = 0; i < x.GetSize(); i++) x.GetValue()[i] = (i + 1);
        for (int i = 0; i < y.GetSize(); i++) y.GetValue()[i] = (i + 1);
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult12DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }
        for (int i = 0; i < x.GetSize(); i++) x.GetValue()[i] = (i<<16);
        for (int i = 0; i < y.GetSize(); i++) y.GetValue()[i] = (i<<16);
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult12DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }
        for (int i = 0; i < x.GetSize(); i++) x.GetValue()[i] = 0xFFFFFFFF;
        for (int i = 0; i < y.GetSize(); i++) y.GetValue()[i] = 0xFFFFFFFF;
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult12DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }
        // with an internal multiply, y COULD have leading 0s
        x.SetRandom(12*_DIGIT_SIZE_IN_BITS);
        for (int i = 0; i < y.GetSize(); i++) y.GetValue()[i] = 0;
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult12DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }
        x.SetRandom(12*_DIGIT_SIZE_IN_BITS);
        y.SetRandom(nSize*_DIGIT_SIZE_IN_BITS);
        z1.SetSize(x.GetSize() + y.GetSize());
        z2.SetSize(x.GetSize() + y.GetSize());
        for (int i = 0; i < z2.GetSize(); i++)
        {
            z1.GetValue()[i] = gibberish;
            z2.GetValue()[i] = gibberish;
        }
        CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z1.GetValue());
        if (0 == z1.GetValue()[z1.GetSize() - 1]) z1.SetSize(z1.GetSize() - 1);
        CAVXMultiply::Mult12DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        if (0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z1 != z2)
        {
            goto exit;
        }

        // multiply/add
        bMultAdd = true;
        // first, where z is the same size as x*y
        zFinal   =  z2;
        zFinal   *= 2;
        zAdd     =  z2;
        z2.Reserve(x.GetSize() + y.GetSize() + 1, true);
        for (int i = z2.GetSize(); i < x.GetSize() + y.GetSize() + 1; i++) z2.GetValue()[i] = 0;
        CAVXMultiply::Mult12DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        z2.SetSize(x.GetSize() + y.GetSize() + 1);
        while (0 < z2.GetSize() && 0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z2 != zFinal)
        {
            goto exit;
        }
        // next, z smaller than x*y
        zAdd.SetFromHexString("FFFFFFFF");
        z2.SetSize(CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z2.GetValue()));
        zFinal.SetSize(CUnsignedArithmeticHelper::Add(z2.GetSize(), zAdd.GetSize(), z2.GetValue(), zAdd.GetValue(), zFinal.GetValue()));
        z2 = zAdd;
        for (int i = z2.GetSize(); i < x.GetSize() + y.GetSize() + 1; i++) z2.GetValue()[i] = 0;
        CAVXMultiply::Mult12DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        z2.SetSize(max(x.GetSize() + y.GetSize(), zAdd.GetSize()) + 1);
        while (0 < z2.GetSize() && 0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z2 != zFinal)
        {
            goto exit;
        }
        // finally, z larger than x*y
        zAdd.Reserve(x.GetSize() + y.GetSize() + 5);
        zAdd.SetSize(x.GetSize() + y.GetSize() + 5);
        zFinal.Reserve(x.GetSize() + y.GetSize() + 6);
        for (int i = 0; i < zAdd.GetSize(); i++) zAdd.GetValue()[i] = 0xFFFFFFFF;
        z2.SetSize(CUnsignedArithmeticHelper::MultOracle(x.GetSize(), y.GetSize(), x.GetValue(), y.GetValue(), z2.GetValue()));
        zFinal.SetSize(CUnsignedArithmeticHelper::Add(z2.GetSize(), zAdd.GetSize(), z2.GetValue(), zAdd.GetValue(), zFinal.GetValue()));
        z2.Reserve(max(x.GetSize() + y.GetSize(), zAdd.GetSize()) + 1);
        z2 = zAdd;
        for (int i = z2.GetSize(); i < max(x.GetSize() + y.GetSize(), zAdd.GetSize()) + 1; i++) z2.GetValue()[i] = 0;
        CAVXMultiply::Mult12DigitX(x.GetValue(), y.GetValue(), y.GetSize(), z2.GetValue(), bMultAdd);
        z2.SetSize(max(x.GetSize() + y.GetSize(), zAdd.GetSize()) + 1);
        while (0 < z2.GetSize() && 0 == z2.GetValue()[z2.GetSize() - 1]) z2.SetSize(z2.GetSize() - 1);
        if (z2 != zFinal)
        {
            goto exit;
        }
    }
    bTestWorked = true;
exit:
    if(!bTestWorked)
    {
        switch (nVariation) {
        case 1:
            printf("Mult4DigitX is WRONG for Y size %i\n", y.GetSize());
            break;
        case 2:
            printf("Mult8DigitX is WRONG for Y size %i\n", y.GetSize());
            break;
        case 3:
            printf("Mult12DigitX is WRONG for Y size %i\n", y.GetSize());
            break;
        default:
            printf("unknown variation failed!\n");
            break;
        }
        if (bMultAdd)
        {
            printf("Computing x*y + z, where\n");
            printf("x: "); x.PrintHexToFile();
            printf("y: "); y.PrintHexToFile();
            printf("z: "); zAdd.PrintHexToFile();
            printf("Computed: "); z2.PrintHexToFile();
            printf("Correct:  "); zFinal.PrintHexToFile();
        }
        else
        {
            printf("X: "); x.PrintHexToFile();
            printf("Y: "); y.PrintHexToFile();
            printf("correct:  ");  z1.PrintHexToFile();
            printf("Computed: ");  z2.PrintHexToFile();
        }
    }
    return bTestWorked;
#else
    printf("AVX not supported.  AVX instructions must be available, AND DIGITs must be 32 bits each.  See constants.h\n");
    return false;
#endif
}