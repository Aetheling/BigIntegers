#include "BigIntegers.h"
#include "ArithmeticBox.h"
#include "CArithmeticTestHelper.h"
#include "Timer.h"
#include "CRSATest.h"
#include "CModularBoxTest.h"

class CRandom
{
public: // functions
    static int Random(int n)
    {
        if(0==(s_nSeed++)%1000000)
        {
            srand(time(NULL));
        }
        return 1+(rand()%n);
    }
private: // variables
    static int s_nSeed;
};

int CRandom::s_nSeed = 0;

bool PinThreadToProcessor(DWORD dwProcessID)
{
	// pin the process to the CPU passed (or top CPU if none given); when testing best cache sizes, need to maintain the cache!
	// And...  pinning to a processor REALLY speeds things up.
    // WARNING: also sets proces priority to realtime, and thread priority to highest -- DO NOT DO THIS if running multithreaded!
    SYSTEM_INFO  sysInfo;
    HANDLE       hCurrentProcessHandle = GetCurrentProcess(), hCurrentThreadHandle = GetCurrentThread();
    DWORD_PTR    pProcessAffinityMask,pSystemAffinityMask,pProcessorMask=1;
    DWORD        dwRetVal = GetProcessAffinityMask(hCurrentProcessHandle, 
                                                   &pProcessAffinityMask, 
                                                   &pSystemAffinityMask);
	bool        bAllOK    = false;
    if(0==dwRetVal)
    {
        printf("unable to get process affinity mask\n");
    }
	else
	{
		GetSystemInfo(&sysInfo);
		if((DWORD) -1 == dwProcessID)
		{
			dwProcessID = sysInfo.dwNumberOfProcessors-1;
		}
		else if(sysInfo.dwNumberOfProcessors-1<dwProcessID)
		{
			printf("Bad processor ID -- passed %i, but only %i processors exist!\n",dwProcessID,sysInfo.dwNumberOfProcessors);
			goto exit;
		}
		pProcessorMask =  pProcessorMask<<dwProcessID;
		pProcessorMask &= pProcessAffinityMask;
		if(0==pProcessorMask)
		{
			printf("processor specified not in allowed set\n");
            goto exit;
		}
		else if(0==SetThreadAffinityMask(hCurrentThreadHandle, pProcessorMask))
		{
			printf("Unable to set affinity mask\n");
            goto exit;
		}
        if (!SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS))
        {
            printf("Failed to boost process priority to realtime\n");
            goto exit;
        }
        if (!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST))
        {
            printf("Failed to boost thread priority to highest\n");
            goto exit;
        }
    }
    bAllOK = true;
exit:
	return bAllOK;
}

bool UnpinProcessor()
{
    SYSTEM_INFO  sysInfo;
    HANDLE       hCurrentProcessHandle = GetCurrentProcess(), hCurrentThreadHandle = GetCurrentThread();
    DWORD_PTR    pProcessAffinityMask,pSystemAffinityMask,pProcessorMask=1;
    DWORD        dwRetVal = GetProcessAffinityMask(hCurrentProcessHandle, 
                                                   &pProcessAffinityMask, 
                                                   &pSystemAffinityMask);
	bool        bAllOK    = false;
    if(0==dwRetVal)
    {
        printf("unable to get process affinity mask\n");
    }
	else
	{
		GetSystemInfo(&sysInfo);
		pProcessorMask =  (pProcessorMask<<sysInfo.dwNumberOfProcessors)-1;
		pProcessorMask &= pProcessAffinityMask;
		if(0==pProcessorMask)
		{
			printf("processor specified not in allowed set\n");
            goto exit;
		}
		else if(0==SetThreadAffinityMask(hCurrentThreadHandle, pProcessorMask))
		{
			printf("Unable to set affinity mask\n");
            goto exit;
		}
        if (!SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS))
        {
            printf("Failed to restore process priority to realtime\n");
        }
        if (!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL))
        {
            printf("Failed to restore thread priority to normal\n");
        }
	}
    bAllOK = true;
exit:
	return bAllOK;
}

int main()
{
    CArithmeticCorrectnessTester cCorrectnessTester;
	CArithmeticTuner             cTuner;
	CArithmeticPerformanceTester cPerfTester;
    CRSATest                     cRSATester;
    CModularBoxTest              cModBoxTester;
	int                          i;
	////////////////////////////////////////////////////////////////////////////////////////
	//                                                                                    //
	//                              Test correctness                                      //
	//                                                                                    //
	////////////////////////////////////////////////////////////////////////////////////////
    cCorrectnessTester.ResetThresholdsForTest();
    /*
    if(!cCorrectnessTester.TestBigInteger())
    {
        printf("BigInteger test failed\n");
        return 1;
    }
    else
    {
        printf("BigInteger test passed\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cCorrectnessTester.TestAddSubtract())
    {
        printf("Add/subtract test failed\n");
        return 1;
    }
    else
    {
        printf("Add/subtract test passed\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cCorrectnessTester.TestShortLongMultiply())
    {
        printf("Multiply short/long test failed\n");
        return 1;
    }
    else
    {
        printf("Multiply short/long test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cCorrectnessTester.TestStripedMultiply())
    {
        printf("Striped multiply test failed\n");
        return 1;
    }
    else
    {
        printf("Striped multiply test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cCorrectnessTester.TestBasicMultiply())
    {
        printf("Basic multiply test failed\n");
        return 1;
    }
    else
    {
        printf("Basic multiply test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cCorrectnessTester.TestRecursiveMultiply())
    {
        printf("Recursive multiply test failed\n");
        return 1;
    }
    else
    {
        printf("Recursive multiply test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest(true);
    if(!cCorrectnessTester.TestDivide()) // long test -- even in retail
    {
        printf("Divide test failed\n");
        return 1;
    }
    else
    {
        printf("Divide test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest(true);
    if(!cCorrectnessTester.TestBigVector())
    {
        printf("Vector test failed\n");
        return 1;
    }
    else
    {
        printf("Vector test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest(true);
    if(!cCorrectnessTester.TestBigGCD())
    {
        printf("GCD test failed\n");
        return 1;
    }
    else
    {
        printf("GCD test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest(true);
    if(!cCorrectnessTester.TestMultiplyAdd())
    {
        printf("Multiply/add test failed\n");
        return 1;
    }
    else
    {
        printf("Multiply/add test succeeded\n");
    }
#if _USEAVX
    cCorrectnessTester.ResetThresholdsForTest(true);
    if (!cCorrectnessTester.TestAVXMultiply())
    {
        printf("AVX multiply test failed\n");
        return 1;
    }
    else
    {
        printf("AVX multiply test succeeded\n");
    }
#endif
    cCorrectnessTester.ResetThresholdsForTest(true);
    if(!cCorrectnessTester.TestBigMatrix())
    {
        printf("Matrix test failed\n");
        return 1;
    }
    else
    {
        printf("Matrix test succeeded\n");
    }
    // note that the 2n-1 by 2n multiply requires divide, GCD, and
    // matrix ops.  So we test it after testing those functions
    cCorrectnessTester.ResetThresholdsForTest();
	if(!cCorrectnessTester.Test2NByNMultiply()) // long test!  especially in debug (in debug, also validates generating the system of equations which takes time, above and beyond just generating it)
	{
		printf("2N-1 by 2N multiply test failed\n");
        return 1;
	}
	else
	{
		printf("2N-1 by 2N multiply test succeeded\n");
	}
    cCorrectnessTester.ResetThresholdsForTest();
    // Long test
    if(!cCorrectnessTester.TestModBy2NPlus1())
    {
        printf("Mod by 1+2^n test failed\n");
        return 1;
    }
    else
    {
        printf("Mod by 1+2^n test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cCorrectnessTester.TestMult2toMmodOnePlus2toN())
    {
        printf("Multiply by 2^m, then mod by 2^n test failed\n");
        return 1;
    }
    else
    {
        printf("Multiply by 2^m, then mod by 2^n test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cCorrectnessTester.TestFFT())
    {
        printf("FFT test failed\n");
        return 1;
    }
    else
    {
        printf("FFT test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    // warning!  LONG test!
    if(!cCorrectnessTester.TestFFTMult())
    {
        printf("FFT multiply test failed\n");
        return 1;
    }
    else
    {
        printf("FFT multiply test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if (!cCorrectnessTester.TestSquare())
    {
        printf("Square test failed\n");
        return 1;
    }
    else
    {
        printf("Square test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    // really slow test
	if(!cCorrectnessTester.TestPowerModulus())
	{
		printf("Power modulus test failed\n");
        return 1;
	}
	else
	{
		printf("Power modulus test succeeded\n");
	}
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cCorrectnessTester.TestModularBox())
    {
        printf("Modular box test failed\n");
        return 1;
    }
    else
    {
        printf("Modular box test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cModBoxTester.PowerModulusTest())
    {
        printf("Modular box:PowerModulusTest failed\n");
        return 1;
    }
    else
    {
        printf("Modular box:PowerModulusTest succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cCorrectnessTester.TestMontgomeryFormat())
    {
        printf("Montgomery format test failed\n");
        return 1;
    }
    else
    {
        printf("Montgomery format test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cCorrectnessTester.TestMontgomeryMultiply())
    {
        printf("Montgomery multiply test failed\n");
        return 1;
    }
    else
    {
        printf("Montgomery multiply test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if (!cCorrectnessTester.TestMontgomeryPowerModulus()) // another long test!
    {
        printf("Montgomery power modulus test failed\n");
        return 1;
    }
    else
    {
        printf("Montgomery power modulus test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if (!cCorrectnessTester.TestSquareRoot())
    {
        printf("Square root test failed\n");
        return 1;
    }
    else
    {
        printf("Square root test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cCorrectnessTester.TestPower())
    {
        printf("Power test failed\n");
        return 1;
    }
    else
    {
        printf("Power test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cCorrectnessTester.TestNthRootHelper())
    {
        printf("Nth root helper test failed\n");
        return 1;
    }
    else
    {
        printf("Nth root helper test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cCorrectnessTester.TestNthRoot())
    {
        printf("Nth root test failed\n");
        return 1;
    }
    else
    {
        printf("Nth root test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if(!cRSATester.TestProbablyPrime())
    {
        printf("Probably prime test failed\n");
        return 1;
    }
    else
    {
        printf("Probably prime test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if (!cRSATester.TestRSA(true))
    {
        printf("RSA with timing protection test failed\n");
        return 1;
    }
    else
    {
        printf("RSA with timing protection test succeeded\n");
    }
    cCorrectnessTester.ResetThresholdsForTest();
    if (!cRSATester.TestRSA(false))
    {
        printf("RSA without timing protection test failed\n");
        return 1;
    }
    else
    {
        printf("RSA without timing protection test succeeded\n");
    }*/
	////////////////////////////////////////////////////////////////////////////////////////
	//                                                                                    //
	//                              Tune parameters                                       //
	//                                                                                    //
	////////////////////////////////////////////////////////////////////////////////////////
	PinThreadToProcessor((DWORD) -1); // want to keep the thread on the same processor -- trying to
	                                  // optimize cache parameters (at least in part)!
    //cTuner.ResetThresholdsForTest();
    //cTuner.Test2NByNBlockSizes(); // likely no need for this -- by the time the problem is big enough for doing it in chunks to help, FFT is faster regardless
    //cTuner.FindBestMultiplicationThresholds();
    //cTuner.FindBestDivideThresholds();
	////////////////////////////////////////////////////////////////////////////////////////
	//                                                                                    //
	//                              Performance tests                                     //
	//                                                                                    //
	////////////////////////////////////////////////////////////////////////////////////////
    
    // For sample times, see PerfRun.txt

    cPerfTester.ResetThresholdsForOptimization();
    if (!PinThreadToProcessor((DWORD)-1))
    {
        printf("Pinning processor failed!\n");
        return 1;
    }
    else
    {
        printf("tests with processor pinned:\n");
    }
    // on my machine, striped multiply is (almost) always faster than basic multiply.  But if basic multiply is faster on your
    // machine, you will want to adjust CUnsignedArithmeticHelper::MultUBackend, CUnsignedArithmeticHelper::MultAddUBackend,
    // and perhaps CUnsignedArithmeticHelper::SquareUBackend
    // to take account
    cPerfTester.SpeedCheckBasicMultiply();
    cPerfTester.AVXMultTimes();
    cPerfTester.CompareBasicMultiplicationToStripedMultiplication();
    cPerfTester.CompareBasicMultiplicationToLongShortMultiplication();
    cPerfTester.TestMultiplyTimes();
    cPerfTester.CompareBaseMultiplicationToFFT();
    cPerfTester.CompareMultiplicationAlgorithms();
    cPerfTester.CompareDivideTimes();
    cPerfTester.SquareRootTimes();
    cPerfTester.GeneralRootTimes(); // very long test
    cPerfTester.CompareNthRootProblemBreakdownTimes(); // very long test
    cPerfTester.GCDTimes();
    cPerfTester.MatrixMultiplyTimes();
    cPerfTester.PowerModulusMontgomeryVsStandard();
    cPerfTester.FFTTimes();
    cRSATester.PerfTestDivisibleBySmallPrime();
    cRSATester.PerfTestProbablyPrime();
    cRSATester.PerfTestGetPrime();
    if (!cRSATester.PerfTestRSA())
    {
        printf("Perf test revealed encrypt-decrypt error\n");
    }
    if (!UnpinProcessor())
    {
        printf("Unpinning processor failed!\n");
        return 1;
    }
    return 0;
}