#pragma once
#include "TestConstants.h"
#include "ArithmeticBox.h"
#include "CUnsignedArithmeticHelper.h"
#include "CArithmeticTestHelper.h"
#include "CBigIntegerVectors.h"
#include "CBigIntegerMatrix.h"
#include "SSystemData.h"
#include "CRandomGenerator.h"
#include "math.h"
#include "..\BigIntegersBase\SmallPrimes.h"
#pragma warning(disable:4267)    // conversion from 'size_t' to 'unsigned int' -- possible loss of data

void CArithmeticPerformanceTester::SaveMultiplicationThresholds()
{
    for(int i=0; i<CUnsignedArithmeticHelper::c_n2NBynSizeBreakpoints; i++)
    {
        m_pnTemp2NByNBreakpoints[i]       = c_pn2NByNBreakpoints[i];
        m_pnTemp2NByNSquareBreakpoints[i] = c_pn2NByNSquareBreakpoints[i];
    }
    for(int i=0; i<eNumMultiplyAlgorithms-1; i++)
    {
        m_pnTempMultiplicationThresholds[i] = c_pnMultiplicationThresholds[i];
        m_pnTempSquareThresholds[i]         = c_pnSquareThresholds[i];
    }
}

void CArithmeticPerformanceTester::RestoreMultiplicationThresholds()
{
    for(int i=0; i<CUnsignedArithmeticHelper::c_n2NBynSizeBreakpoints; i++)
    {
        c_pn2NByNBreakpoints[i]       = m_pnTemp2NByNBreakpoints[i];
        c_pn2NByNSquareBreakpoints[i] = m_pnTemp2NByNSquareBreakpoints[i];
    }
    for(int i=0; i<eNumMultiplyAlgorithms-1; i++)
    {
        c_pnMultiplicationThresholds[i] = m_pnTempMultiplicationThresholds[i];
        c_pnSquareThresholds[i]         = m_pnTempSquareThresholds[i];
    }
}

/*
16-bit DIGITS
Size (BYTEs): 2 Size (DIGITs): 1        Register block size: 1  Iterations: 10000000    Time: 163491
Size (BYTEs): 2 Size (DIGITs): 1        Register block size: 2  Iterations: 10000000    Time: 62158
Size (BYTEs): 2 Size (DIGITs): 1        Register block size: 3  Iterations: 10000000    Time: 73463
Size (BYTEs): 2 Size (DIGITs): 1        Register block size: 4  Iterations: 10000000    Time: 67942
Size (BYTEs): 2 Size (DIGITs): 1        Register block size: 5  Iterations: 10000000    Time: 72254
Size (BYTEs): 2 Size (DIGITs): 1        Register block size: 6  Iterations: 10000000    Time: 75479
Size (BYTEs): 4 Size (DIGITs): 2        Register block size: 1  Iterations: 10000000    Time: 200168
Size (BYTEs): 4 Size (DIGITs): 2        Register block size: 2  Iterations: 10000000    Time: 208919
Size (BYTEs): 4 Size (DIGITs): 2        Register block size: 3  Iterations: 10000000    Time: 212125
Size (BYTEs): 4 Size (DIGITs): 2        Register block size: 4  Iterations: 10000000    Time: 218585
Size (BYTEs): 4 Size (DIGITs): 2        Register block size: 5  Iterations: 10000000    Time: 190529
Size (BYTEs): 4 Size (DIGITs): 2        Register block size: 6  Iterations: 10000000    Time: 196630
Size (BYTEs): 6 Size (DIGITs): 3        Register block size: 1  Iterations: 10000000    Time: 218142
Size (BYTEs): 6 Size (DIGITs): 3        Register block size: 2  Iterations: 10000000    Time: 245957
Size (BYTEs): 6 Size (DIGITs): 3        Register block size: 3  Iterations: 10000000    Time: 241974
Size (BYTEs): 6 Size (DIGITs): 3        Register block size: 4  Iterations: 10000000    Time: 247865
Size (BYTEs): 6 Size (DIGITs): 3        Register block size: 5  Iterations: 10000000    Time: 255549
Size (BYTEs): 6 Size (DIGITs): 3        Register block size: 6  Iterations: 10000000    Time: 250037
Size (BYTEs): 8 Size (DIGITs): 4        Register block size: 1  Iterations: 10000000    Time: 285730
Size (BYTEs): 8 Size (DIGITs): 4        Register block size: 2  Iterations: 10000000    Time: 323743
Size (BYTEs): 8 Size (DIGITs): 4        Register block size: 3  Iterations: 10000000    Time: 317589
Size (BYTEs): 8 Size (DIGITs): 4        Register block size: 4  Iterations: 10000000    Time: 315994
Size (BYTEs): 8 Size (DIGITs): 4        Register block size: 5  Iterations: 10000000    Time: 350538
Size (BYTEs): 8 Size (DIGITs): 4        Register block size: 6  Iterations: 10000000    Time: 333775
Size (BYTEs): 10 Size (DIGITs): 5       Register block size: 1  Iterations: 10000000    Time: 376657
Size (BYTEs): 10 Size (DIGITs): 5       Register block size: 2  Iterations: 10000000    Time: 416829
Size (BYTEs): 10 Size (DIGITs): 5       Register block size: 3  Iterations: 10000000    Time: 442020
Size (BYTEs): 10 Size (DIGITs): 5       Register block size: 4  Iterations: 10000000    Time: 363392
Size (BYTEs): 10 Size (DIGITs): 5       Register block size: 5  Iterations: 10000000    Time: 438498
Size (BYTEs): 10 Size (DIGITs): 5       Register block size: 6  Iterations: 10000000    Time: 427358
Size (BYTEs): 12 Size (DIGITs): 6       Register block size: 1  Iterations: 10000000    Time: 478902
Size (BYTEs): 12 Size (DIGITs): 6       Register block size: 2  Iterations: 10000000    Time: 521803
Size (BYTEs): 12 Size (DIGITs): 6       Register block size: 3  Iterations: 10000000    Time: 511942
Size (BYTEs): 12 Size (DIGITs): 6       Register block size: 4  Iterations: 10000000    Time: 502801
Size (BYTEs): 12 Size (DIGITs): 6       Register block size: 5  Iterations: 10000000    Time: 513803
Size (BYTEs): 12 Size (DIGITs): 6       Register block size: 6  Iterations: 10000000    Time: 623201
Size (BYTEs): 14 Size (DIGITs): 7       Register block size: 1  Iterations: 10000000    Time: 701968
Size (BYTEs): 14 Size (DIGITs): 7       Register block size: 2  Iterations: 10000000    Time: 647018
Size (BYTEs): 14 Size (DIGITs): 7       Register block size: 3  Iterations: 10000000    Time: 660231
Size (BYTEs): 14 Size (DIGITs): 7       Register block size: 4  Iterations: 10000000    Time: 693258
Size (BYTEs): 14 Size (DIGITs): 7       Register block size: 5  Iterations: 10000000    Time: 644019
Size (BYTEs): 14 Size (DIGITs): 7       Register block size: 6  Iterations: 10000000    Time: 573656
Size (BYTEs): 16 Size (DIGITs): 8       Register block size: 1  Iterations: 10000000    Time: 755565
Size (BYTEs): 16 Size (DIGITs): 8       Register block size: 2  Iterations: 10000000    Time: 740749
Size (BYTEs): 16 Size (DIGITs): 8       Register block size: 3  Iterations: 10000000    Time: 811960
Size (BYTEs): 16 Size (DIGITs): 8       Register block size: 4  Iterations: 10000000    Time: 729023
Size (BYTEs): 16 Size (DIGITs): 8       Register block size: 5  Iterations: 10000000    Time: 779295
Size (BYTEs): 16 Size (DIGITs): 8       Register block size: 6  Iterations: 10000000    Time: 713976
Size (BYTEs): 18 Size (DIGITs): 9       Register block size: 1  Iterations: 10000000    Time: 928867
Size (BYTEs): 18 Size (DIGITs): 9       Register block size: 2  Iterations: 10000000    Time: 866121
Size (BYTEs): 18 Size (DIGITs): 9       Register block size: 3  Iterations: 10000000    Time: 952229
Size (BYTEs): 18 Size (DIGITs): 9       Register block size: 4  Iterations: 10000000    Time: 775684
Size (BYTEs): 18 Size (DIGITs): 9       Register block size: 5  Iterations: 10000000    Time: 983941
Size (BYTEs): 18 Size (DIGITs): 9       Register block size: 6  Iterations: 10000000    Time: 906516
Size (BYTEs): 20 Size (DIGITs): 10      Register block size: 1  Iterations: 10000000    Time: 1128339
Size (BYTEs): 20 Size (DIGITs): 10      Register block size: 2  Iterations: 10000000    Time: 1035434
Size (BYTEs): 20 Size (DIGITs): 10      Register block size: 3  Iterations: 10000000    Time: 966454
Size (BYTEs): 20 Size (DIGITs): 10      Register block size: 4  Iterations: 10000000    Time: 993368
Size (BYTEs): 20 Size (DIGITs): 10      Register block size: 5  Iterations: 10000000    Time: 1082850
Size (BYTEs): 20 Size (DIGITs): 10      Register block size: 6  Iterations: 10000000    Time: 1119419
Size (BYTEs): 22 Size (DIGITs): 11      Register block size: 1  Iterations: 10000000    Time: 1385668
Size (BYTEs): 22 Size (DIGITs): 11      Register block size: 2  Iterations: 10000000    Time: 1199597
Size (BYTEs): 22 Size (DIGITs): 11      Register block size: 3  Iterations: 10000000    Time: 1289095
Size (BYTEs): 22 Size (DIGITs): 11      Register block size: 4  Iterations: 10000000    Time: 1208774
Size (BYTEs): 22 Size (DIGITs): 11      Register block size: 5  Iterations: 10000000    Time: 1036034
Size (BYTEs): 22 Size (DIGITs): 11      Register block size: 6  Iterations: 10000000    Time: 1333042
Size (BYTEs): 24 Size (DIGITs): 12      Register block size: 1  Iterations: 10000000    Time: 1628913
Size (BYTEs): 24 Size (DIGITs): 12      Register block size: 2  Iterations: 10000000    Time: 1373751
Size (BYTEs): 24 Size (DIGITs): 12      Register block size: 3  Iterations: 10000000    Time: 1361898
Size (BYTEs): 24 Size (DIGITs): 12      Register block size: 4  Iterations: 10000000    Time: 1344619
Size (BYTEs): 24 Size (DIGITs): 12      Register block size: 5  Iterations: 10000000    Time: 1290100
Size (BYTEs): 24 Size (DIGITs): 12      Register block size: 6  Iterations: 10000000    Time: 1400006
Size (BYTEs): 26 Size (DIGITs): 13      Register block size: 1  Iterations: 10000000    Time: 1879101
Size (BYTEs): 26 Size (DIGITs): 13      Register block size: 2  Iterations: 10000000    Time: 1560974
Size (BYTEs): 26 Size (DIGITs): 13      Register block size: 3  Iterations: 10000000    Time: 1470537
Size (BYTEs): 26 Size (DIGITs): 13      Register block size: 4  Iterations: 10000000    Time: 1347147
Size (BYTEs): 26 Size (DIGITs): 13      Register block size: 5  Iterations: 10000000    Time: 1554696
Size (BYTEs): 26 Size (DIGITs): 13      Register block size: 6  Iterations: 10000000    Time: 1420119
Size (BYTEs): 28 Size (DIGITs): 14      Register block size: 1  Iterations: 10000000    Time: 2194703
Size (BYTEs): 28 Size (DIGITs): 14      Register block size: 2  Iterations: 10000000    Time: 1771308
Size (BYTEs): 28 Size (DIGITs): 14      Register block size: 3  Iterations: 10000000    Time: 1741314
Size (BYTEs): 28 Size (DIGITs): 14      Register block size: 4  Iterations: 10000000    Time: 1624886
Size (BYTEs): 28 Size (DIGITs): 14      Register block size: 5  Iterations: 10000000    Time: 1846800
Size (BYTEs): 28 Size (DIGITs): 14      Register block size: 6  Iterations: 10000000    Time: 1711612
Size (BYTEs): 30 Size (DIGITs): 15      Register block size: 1  Iterations: 10000000    Time: 2462862
Size (BYTEs): 30 Size (DIGITs): 15      Register block size: 2  Iterations: 10000000    Time: 2008158
Size (BYTEs): 30 Size (DIGITs): 15      Register block size: 3  Iterations: 10000000    Time: 2032323
Size (BYTEs): 30 Size (DIGITs): 15      Register block size: 4  Iterations: 10000000    Time: 2007565
Size (BYTEs): 30 Size (DIGITs): 15      Register block size: 5  Iterations: 10000000    Time: 2111639
Size (BYTEs): 30 Size (DIGITs): 15      Register block size: 6  Iterations: 10000000    Time: 2181545
Size (BYTEs): 32 Size (DIGITs): 16      Register block size: 1  Iterations: 10000000    Time: 2941169
Size (BYTEs): 32 Size (DIGITs): 16      Register block size: 2  Iterations: 10000000    Time: 2237148
Size (BYTEs): 32 Size (DIGITs): 16      Register block size: 3  Iterations: 10000000    Time: 2027819
Size (BYTEs): 32 Size (DIGITs): 16      Register block size: 4  Iterations: 10000000    Time: 2141324
Size (BYTEs): 32 Size (DIGITs): 16      Register block size: 5  Iterations: 10000000    Time: 1882126
Size (BYTEs): 32 Size (DIGITs): 16      Register block size: 6  Iterations: 10000000    Time: 2342808
Size (BYTEs): 34 Size (DIGITs): 17      Register block size: 1  Iterations: 10000000    Time: 3145388
Size (BYTEs): 34 Size (DIGITs): 17      Register block size: 2  Iterations: 10000000    Time: 2480327
Size (BYTEs): 34 Size (DIGITs): 17      Register block size: 3  Iterations: 10000000    Time: 2396696
Size (BYTEs): 34 Size (DIGITs): 17      Register block size: 4  Iterations: 10000000    Time: 2086078
Size (BYTEs): 34 Size (DIGITs): 17      Register block size: 5  Iterations: 10000000    Time: 2229773
Size (BYTEs): 34 Size (DIGITs): 17      Register block size: 6  Iterations: 10000000    Time: 2715405
Size (BYTEs): 36 Size (DIGITs): 18      Register block size: 1  Iterations: 10000000    Time: 3517192
Size (BYTEs): 36 Size (DIGITs): 18      Register block size: 2  Iterations: 10000000    Time: 2765052
Size (BYTEs): 36 Size (DIGITs): 18      Register block size: 3  Iterations: 10000000    Time: 2576729
Size (BYTEs): 36 Size (DIGITs): 18      Register block size: 4  Iterations: 10000000    Time: 2481841
Size (BYTEs): 36 Size (DIGITs): 18      Register block size: 5  Iterations: 10000000    Time: 2619419
Size (BYTEs): 36 Size (DIGITs): 18      Register block size: 6  Iterations: 10000000    Time: 2838592
Size (BYTEs): 38 Size (DIGITs): 19      Register block size: 1  Iterations: 10000000    Time: 3975665
Size (BYTEs): 38 Size (DIGITs): 19      Register block size: 2  Iterations: 10000000    Time: 3124076
Size (BYTEs): 38 Size (DIGITs): 19      Register block size: 3  Iterations: 10000000    Time: 2825172
Size (BYTEs): 38 Size (DIGITs): 19      Register block size: 4  Iterations: 10000000    Time: 2947063
Size (BYTEs): 38 Size (DIGITs): 19      Register block size: 5  Iterations: 10000000    Time: 3109855
Size (BYTEs): 38 Size (DIGITs): 19      Register block size: 6  Iterations: 10000000    Time: 3018142
Size (BYTEs): 40 Size (DIGITs): 20      Register block size: 1  Iterations: 10000000    Time: 4647545
Size (BYTEs): 40 Size (DIGITs): 20      Register block size: 2  Iterations: 10000000    Time: 3431621
Size (BYTEs): 40 Size (DIGITs): 20      Register block size: 3  Iterations: 10000000    Time: 3218967
Size (BYTEs): 40 Size (DIGITs): 20      Register block size: 4  Iterations: 10000000    Time: 3088330
Size (BYTEs): 40 Size (DIGITs): 20      Register block size: 5  Iterations: 10000000    Time: 3258122
Size (BYTEs): 40 Size (DIGITs): 20      Register block size: 6  Iterations: 10000000    Time: 3900625
Size (BYTEs): 42 Size (DIGITs): 21      Register block size: 1  Iterations: 10000000    Time: 5331409
Size (BYTEs): 42 Size (DIGITs): 21      Register block size: 2  Iterations: 10000000    Time: 3953927
Size (BYTEs): 42 Size (DIGITs): 21      Register block size: 3  Iterations: 10000000    Time: 3850825
Size (BYTEs): 42 Size (DIGITs): 21      Register block size: 4  Iterations: 10000000    Time: 3093096
Size (BYTEs): 42 Size (DIGITs): 21      Register block size: 5  Iterations: 10000000    Time: 2979457
Size (BYTEs): 42 Size (DIGITs): 21      Register block size: 6  Iterations: 10000000    Time: 3619160
Size (BYTEs): 44 Size (DIGITs): 22      Register block size: 1  Iterations: 10000000    Time: 5259984
Size (BYTEs): 44 Size (DIGITs): 22      Register block size: 2  Iterations: 10000000    Time: 4017862
Size (BYTEs): 44 Size (DIGITs): 22      Register block size: 3  Iterations: 10000000    Time: 3562882
Size (BYTEs): 44 Size (DIGITs): 22      Register block size: 4  Iterations: 10000000    Time: 3510028
Size (BYTEs): 44 Size (DIGITs): 22      Register block size: 5  Iterations: 10000000    Time: 3534233
Size (BYTEs): 44 Size (DIGITs): 22      Register block size: 6  Iterations: 10000000    Time: 4454515
Size (BYTEs): 46 Size (DIGITs): 23      Register block size: 1  Iterations: 10000000    Time: 5739994
Size (BYTEs): 46 Size (DIGITs): 23      Register block size: 2  Iterations: 10000000    Time: 4725180
Size (BYTEs): 46 Size (DIGITs): 23      Register block size: 3  Iterations: 10000000    Time: 4008505
Size (BYTEs): 46 Size (DIGITs): 23      Register block size: 4  Iterations: 10000000    Time: 3997388
Size (BYTEs): 46 Size (DIGITs): 23      Register block size: 5  Iterations: 10000000    Time: 3949845
Size (BYTEs): 46 Size (DIGITs): 23      Register block size: 6  Iterations: 10000000    Time: 4611297
Size (BYTEs): 48 Size (DIGITs): 24      Register block size: 1  Iterations: 10000000    Time: 6431409
Size (BYTEs): 48 Size (DIGITs): 24      Register block size: 2  Iterations: 10000000    Time: 4891517
Size (BYTEs): 48 Size (DIGITs): 24      Register block size: 3  Iterations: 10000000    Time: 4692018
Size (BYTEs): 48 Size (DIGITs): 24      Register block size: 4  Iterations: 10000000    Time: 4620584
Size (BYTEs): 48 Size (DIGITs): 24      Register block size: 5  Iterations: 10000000    Time: 4683910
Size (BYTEs): 48 Size (DIGITs): 24      Register block size: 6  Iterations: 10000000    Time: 4942309
Size (BYTEs): 50 Size (DIGITs): 25      Register block size: 1  Iterations: 10000000    Time: 7311042
Size (BYTEs): 50 Size (DIGITs): 25      Register block size: 2  Iterations: 10000000    Time: 5494738
Size (BYTEs): 50 Size (DIGITs): 25      Register block size: 3  Iterations: 10000000    Time: 4718852
Size (BYTEs): 50 Size (DIGITs): 25      Register block size: 4  Iterations: 10000000    Time: 4424246
Size (BYTEs): 50 Size (DIGITs): 25      Register block size: 5  Iterations: 10000000    Time: 5334773
Size (BYTEs): 50 Size (DIGITs): 25      Register block size: 6  Iterations: 10000000    Time: 4698252
Size (BYTEs): 52 Size (DIGITs): 26      Register block size: 1  Iterations: 10000000    Time: 7877826
Size (BYTEs): 52 Size (DIGITs): 26      Register block size: 2  Iterations: 10000000    Time: 5978534
Size (BYTEs): 52 Size (DIGITs): 26      Register block size: 3  Iterations: 10000000    Time: 5200201
Size (BYTEs): 52 Size (DIGITs): 26      Register block size: 4  Iterations: 10000000    Time: 4871810
Size (BYTEs): 52 Size (DIGITs): 26      Register block size: 5  Iterations: 10000000    Time: 4704488
Size (BYTEs): 52 Size (DIGITs): 26      Register block size: 6  Iterations: 10000000    Time: 5618395
Size (BYTEs): 54 Size (DIGITs): 27      Register block size: 1  Iterations: 10000000    Time: 8823827
Size (BYTEs): 54 Size (DIGITs): 27      Register block size: 2  Iterations: 10000000    Time: 6798549
Size (BYTEs): 54 Size (DIGITs): 27      Register block size: 3  Iterations: 10000000    Time: 6038453
Size (BYTEs): 54 Size (DIGITs): 27      Register block size: 4  Iterations: 10000000    Time: 5578023
Size (BYTEs): 54 Size (DIGITs): 27      Register block size: 5  Iterations: 10000000    Time: 5392891
Size (BYTEs): 54 Size (DIGITs): 27      Register block size: 6  Iterations: 10000000    Time: 6648731
Size (BYTEs): 56 Size (DIGITs): 28      Register block size: 1  Iterations: 10000000    Time: 9168172
Size (BYTEs): 56 Size (DIGITs): 28      Register block size: 2  Iterations: 10000000    Time: 6677196
Size (BYTEs): 56 Size (DIGITs): 28      Register block size: 3  Iterations: 10000000    Time: 5564471
Size (BYTEs): 56 Size (DIGITs): 28      Register block size: 4  Iterations: 10000000    Time: 5764848
Size (BYTEs): 56 Size (DIGITs): 28      Register block size: 5  Iterations: 10000000    Time: 6111437
Size (BYTEs): 56 Size (DIGITs): 28      Register block size: 6  Iterations: 10000000    Time: 6916591
Size (BYTEs): 58 Size (DIGITs): 29      Register block size: 1  Iterations: 10000000    Time: 9823882
Size (BYTEs): 58 Size (DIGITs): 29      Register block size: 2  Iterations: 10000000    Time: 7139690
Size (BYTEs): 58 Size (DIGITs): 29      Register block size: 3  Iterations: 10000000    Time: 6609442
Size (BYTEs): 58 Size (DIGITs): 29      Register block size: 4  Iterations: 10000000    Time: 5653313
Size (BYTEs): 58 Size (DIGITs): 29      Register block size: 5  Iterations: 10000000    Time: 6710660
Size (BYTEs): 58 Size (DIGITs): 29      Register block size: 6  Iterations: 10000000    Time: 7193606
Size (BYTEs): 60 Size (DIGITs): 30      Register block size: 1  Iterations: 10000000    Time: 9938561
Size (BYTEs): 60 Size (DIGITs): 30      Register block size: 2  Iterations: 10000000    Time: 7704033
Size (BYTEs): 60 Size (DIGITs): 30      Register block size: 3  Iterations: 10000000    Time: 6580132
Size (BYTEs): 60 Size (DIGITs): 30      Register block size: 4  Iterations: 10000000    Time: 6290058
Size (BYTEs): 60 Size (DIGITs): 30      Register block size: 5  Iterations: 10000000    Time: 6222951
Size (BYTEs): 60 Size (DIGITs): 30      Register block size: 6  Iterations: 10000000    Time: 7013691
Size (BYTEs): 62 Size (DIGITs): 31      Register block size: 1  Iterations: 10000000    Time: 10508746
Size (BYTEs): 62 Size (DIGITs): 31      Register block size: 2  Iterations: 10000000    Time: 8024864
Size (BYTEs): 62 Size (DIGITs): 31      Register block size: 3  Iterations: 10000000    Time: 6678518
Size (BYTEs): 62 Size (DIGITs): 31      Register block size: 4  Iterations: 10000000    Time: 6813427
Size (BYTEs): 62 Size (DIGITs): 31      Register block size: 5  Iterations: 10000000    Time: 6388910
Size (BYTEs): 62 Size (DIGITs): 31      Register block size: 6  Iterations: 10000000    Time: 6905368
Size (BYTEs): 64 Size (DIGITs): 32      Register block size: 1  Iterations: 10000000    Time: 11304423
Size (BYTEs): 64 Size (DIGITs): 32      Register block size: 2  Iterations: 10000000    Time: 8283318
Size (BYTEs): 64 Size (DIGITs): 32      Register block size: 3  Iterations: 10000000    Time: 7374438
Size (BYTEs): 64 Size (DIGITs): 32      Register block size: 4  Iterations: 10000000    Time: 6981914
Size (BYTEs): 64 Size (DIGITs): 32      Register block size: 5  Iterations: 10000000    Time: 6822040
Size (BYTEs): 64 Size (DIGITs): 32      Register block size: 6  Iterations: 10000000    Time: 7547282
Size (BYTEs): 66 Size (DIGITs): 33      Register block size: 1  Iterations: 10000000    Time: 12621748
Size (BYTEs): 66 Size (DIGITs): 33      Register block size: 2  Iterations: 10000000    Time: 8834506
Size (BYTEs): 66 Size (DIGITs): 33      Register block size: 3  Iterations: 10000000    Time: 7690351
Size (BYTEs): 66 Size (DIGITs): 33      Register block size: 4  Iterations: 10000000    Time: 7035271
Size (BYTEs): 66 Size (DIGITs): 33      Register block size: 5  Iterations: 10000000    Time: 7525193
Size (BYTEs): 66 Size (DIGITs): 33      Register block size: 6  Iterations: 10000000    Time: 8292703
Size (BYTEs): 68 Size (DIGITs): 34      Register block size: 1  Iterations: 10000000    Time: 12737482
Size (BYTEs): 68 Size (DIGITs): 34      Register block size: 2  Iterations: 10000000    Time: 9553300
Size (BYTEs): 68 Size (DIGITs): 34      Register block size: 3  Iterations: 10000000    Time: 8387797
Size (BYTEs): 68 Size (DIGITs): 34      Register block size: 4  Iterations: 10000000    Time: 7710021
Size (BYTEs): 68 Size (DIGITs): 34      Register block size: 5  Iterations: 10000000    Time: 8245798
Size (BYTEs): 68 Size (DIGITs): 34      Register block size: 6  Iterations: 10000000    Time: 10527330
Size (BYTEs): 70 Size (DIGITs): 35      Register block size: 1  Iterations: 10000000    Time: 14224713
Size (BYTEs): 70 Size (DIGITs): 35      Register block size: 2  Iterations: 10000000    Time: 9838471
Size (BYTEs): 70 Size (DIGITs): 35      Register block size: 3  Iterations: 10000000    Time: 9277127
Size (BYTEs): 70 Size (DIGITs): 35      Register block size: 4  Iterations: 10000000    Time: 8572855
Size (BYTEs): 70 Size (DIGITs): 35      Register block size: 5  Iterations: 10000000    Time: 8344250
Size (BYTEs): 70 Size (DIGITs): 35      Register block size: 6  Iterations: 10000000    Time: 9912685
Size (BYTEs): 72 Size (DIGITs): 36      Register block size: 1  Iterations: 10000000    Time: 14618305
Size (BYTEs): 72 Size (DIGITs): 36      Register block size: 2  Iterations: 10000000    Time: 10585861
Size (BYTEs): 72 Size (DIGITs): 36      Register block size: 3  Iterations: 10000000    Time: 9288659
Size (BYTEs): 72 Size (DIGITs): 36      Register block size: 4  Iterations: 10000000    Time: 9076145
Size (BYTEs): 72 Size (DIGITs): 36      Register block size: 5  Iterations: 10000000    Time: 8078977
Size (BYTEs): 72 Size (DIGITs): 36      Register block size: 6  Iterations: 10000000    Time: 9817416
Total microseconds for 1 registers: 184737558 20+ DIGITS only: 156369068
Total microseconds for 2 registers: 139522289 20+ DIGITS only: 115933167
Total microseconds for 3 registers: 125653208 20+ DIGITS only: 102741638
Total microseconds for 4 registers: 119178566 20+ DIGITS only: 97081357
Total microseconds for 5 registers: 121279653 20+ DIGITS only: 98287935
Total microseconds for 6 registers: 136801274 20+ DIGITS only: 112619956
*/
void CArithmeticPerformanceTester::SpeedCheckBasicMultiply()
{
#if(_CollectDetailedTimingData)
    DWORD64 dwDummy;
#endif
    size_t       nIterations;
    const size_t c_nMinSize     = 1;
    const size_t c_nMaxSize     = 36; // the cutover point between basic multiply and 3 by 2 multiply seems to be around 32 for both large and small DIGITs
    DWORD64      pnTotalTime[6] = { 0,0,0,0,0,0 };
    DWORD64      pnTotalTimeLarge[6] = { 0,0,0,0,0,0 };
    DIGIT        *nX            = new DIGIT[c_nMaxSize];
    DIGIT        *nY            = new DIGIT[c_nMaxSize];
    DIGIT        *nZ            = new DIGIT[2*c_nMaxSize];
    for(size_t nSize = c_nMinSize; nSize <= c_nMaxSize; nSize++) // *= 10)
    {
        nIterations = 10000;
        nIterations = nIterations*nIterations/10;
        for(int nAlgorithm=0;nAlgorithm<6;nAlgorithm++)
        {
            for(int i=0;i<c_nMaxSize;i++)
            {
                nX[i]        = (DIGIT) -1;
                nY[i]        = (DIGIT) -1;
                nZ[i<<1]     = (DIGIT) -1;
                nZ[1+(i<<1)] = (DIGIT) -1;
            }
            DWORD64 dw64Start = s_Timer.GetMicroseconds();
            for(size_t nIterationCount=0;nIterationCount<nIterations;nIterationCount++)
            {
                switch(nAlgorithm)
                {
                case 0:
                    BasicMultiplyReg1(nSize,nSize,nX,nY,nZ,false);
                    break;
                case 1:
                    BasicMultiplyReg2(nSize,nSize,nX,nY,nZ,false);
                    break;
                case 2:
                    BasicMultiplyReg3(nSize,nSize,nX,nY,nZ,false);
                    break;
                case 3:
                    BasicMultiplyReg4(nSize,nSize,nX,nY,nZ,false);
                    break;
                case 4:
                    BasicMultiplyReg5(nSize,nSize,nX,nY,nZ,false);
                    break;
                case 5:
                    BasicMultiplyReg6(nSize,nSize,nX,nY,nZ,false);
                    break;
                }
            }
            dw64Start = s_Timer.GetMicroseconds() - dw64Start;
            pnTotalTime[nAlgorithm] += dw64Start;
            if(20<=nSize) pnTotalTimeLarge[nAlgorithm] += dw64Start;
            printf("Size (BYTEs): %i Size (DIGITs): %i\tRegister block size: %i\tIterations: %i\tTime: %I64u\n",nSize*sizeof(DIGIT),nSize,nAlgorithm+1,nIterations,dw64Start);
        }
    }
    for (int i=0; i<6; i++)
    {
        printf("Total microseconds for %i registers: %I64u 20+ DIGITS only: %I64u\n", i + 1, pnTotalTime[i], pnTotalTimeLarge[i]);
    }
    delete nX;
    delete nY;
    delete nZ;
}

/*
e.g. for 32-bit DIGITs
Size: 1x64
        Short/long:          1807816
        Mult/add short/long: 2409273
        Basic:               1853188
        Basic mult/add:      2396444

Size: 2x64
        Short/long:          1326558
        Mult/add short/long: 1564949
        Basic:               2679694
        Basic mult/add:      2906222

Size: 3x64
        Short/long:          1217025
        Mult/add short/long: 1284623
        Basic:               3025049
        Basic mult/add:      3140273

Size: 4x64
        Short/long:          1062501
        Mult/add short/long: 1181841
        Basic:               3099646
        Basic mult/add:      3288806

Size: 5x64
        Short/long:          1028160
        Mult/add short/long: 1164377
        Basic:               1908309
        Basic mult/add:      1999801

Size: 6x64
        Short/long:          1038263
        Mult/add short/long: 1085103
        Basic:               2243086
        Basic mult/add:      2233027

Size: 7x64
        Short/long:          995546
        Mult/add short/long: 1042609
        Basic:               2245814
        Basic mult/add:      2337971

Size: 8x64
        Short/long:          995461
        Mult/add short/long: 1019306
        Basic:               2468230
        Basic mult/add:      2536777

Size: 9x64
        Short/long:          989520
        Mult/add short/long: 1008296
        Basic:               1662258
        Basic mult/add:      1713466

Size: 10x64
        Short/long:          973644
        Mult/add short/long: 1078993
        Basic:               1840668
        Basic mult/add:      1883473

Size: 11x64
        Short/long:          1010543
        Mult/add short/long: 1006654
        Basic:               2028609
        Basic mult/add:      2004599

Size: 12x64
        Short/long:          972918
        Mult/add short/long: 998885
        Basic:               2098789
        Basic mult/add:      2152013

for 16-bit DIGITs
Size: 1x64
        Short/long:          2255227
        Mult/add short/long: 3584797
        Basic:               1801938
        Basic mult/add:      2407080

Size: 2x64
        Short/long:          1249728
        Mult/add short/long: 1489046
        Basic:               2449284
        Basic mult/add:      2579104

Size: 3x64
        Short/long:          1089228
        Mult/add short/long: 1255761
        Basic:               2470908
        Basic mult/add:      2611467

Size: 4x64
        Short/long:          999902
        Mult/add short/long: 1124122
        Basic:               2514630
        Basic mult/add:      2562989

Size: 5x64
        Short/long:          996701
        Mult/add short/long: 1068686
        Basic:               1855289
        Basic mult/add:      1966318

Size: 6x64
        Short/long:          1006059
        Mult/add short/long: 1043391
        Basic:               2056310
        Basic mult/add:      2078444

Size: 7x64
        Short/long:          1099610
        Mult/add short/long: 1012326
        Basic:               2281572
        Basic mult/add:      2317560

Size: 8x64
        Short/long:          992329
        Mult/add short/long: 1015906
        Basic:               2292610
        Basic mult/add:      2202224

Size: 9x64
        Short/long:          992431
        Mult/add short/long: 989296
        Basic:               1621491
        Basic mult/add:      1629133

Size: 10x64
        Short/long:          984963
        Mult/add short/long: 975578
        Basic:               1669775
        Basic mult/add:      1728678

Size: 11x64
        Short/long:          1089436
        Mult/add short/long: 1022753
        Basic:               1766072
        Basic mult/add:      1860841

Size: 12x64
        Short/long:          973536
        Mult/add short/long: 974217
        Basic:               1866017
        Basic mult/add:      1838268

Note for the 16-bit, short/long appears to be considerably slower than basic for all n for 1xn multiply, whereas for 32-bit they are the same.
Hence the switch in 16-bit only.
*/
void CArithmeticPerformanceTester::CompareBasicMultiplicationToLongShortMultiplication()
{
    printf("Compare basic to short-long\n");
    DWORD64 dwTimesMult[13],dwTimesMultAdd[13];
    const unsigned int c_nMaxSizeY = 16384;
    DIGIT *pX = (DIGIT *) malloc(sizeof(DIGIT)*(12+c_nMaxSizeY)*2);
    DIGIT *pY = pX + 12;
    DIGIT *pZ = pY + c_nMaxSizeY;
    for(int i=0; i<12+c_nMaxSizeY; i++) pX[i] = (DIGIT) -1;
    for(size_t j=1; j<=c_nMaxSizeY; j*=2)
    {
        for(size_t i=1; i<=12; i++)
        {
            if(j<i) continue;
            size_t  nIterations = ((size_t) 10000)*(12*c_nMaxSizeY)/(i*j);
            DWORD64 dwTimeBasic = s_Timer.GetMicroseconds();
            for(int k=0;k<nIterations;k++)
            {
                MultUBasic(i, j, pX, pY, pZ, false);
            }
            DWORD64 dwTimeShortLong = s_Timer.GetMicroseconds();
            dwTimeBasic = dwTimeShortLong - dwTimeBasic;
            for(int k=0;k<nIterations;k++)
            {
                MultUShortLong(i, j, pX, pY, pZ);
            }
            dwTimeShortLong = s_Timer.GetMicroseconds() - dwTimeShortLong;
            dwTimesMult[i]  = dwTimeShortLong;
            DWORD64 dwTimeBasicMultAdd = s_Timer.GetMicroseconds();
            for(int k=0;k<nIterations;k++)
            {
                MultUBasic(i, j, pX, pY, pZ, true);
            }
            DWORD64 dwTimeShortLongAdd = s_Timer.GetMicroseconds();
            dwTimeBasicMultAdd = dwTimeShortLongAdd - dwTimeBasicMultAdd;
            for(int k=0;k<nIterations;k++)
            {
                MultAddUShortLong(i, j, pX, pY, pZ);
            }
            dwTimeShortLongAdd = s_Timer.GetMicroseconds() - dwTimeShortLongAdd;
            dwTimesMultAdd[i]  = dwTimeShortLongAdd;
            printf("Size: %ux%u\n\tShort/long:          %I64u\n\tMult/add short/long: %I64u\n\tBasic:               %I64u\n\tBasic mult/add:      %I64u\n\n", i, j, dwTimeShortLong, dwTimeShortLongAdd, dwTimeBasic, dwTimeBasicMultAdd);
        }
    }
}

/*
e.g. for 32-bit DIGITs (size in DIGITs, not bytes):
Size: 58x16384
        Basic:            120880
        Mult/add basic:   125209
        Striped:          92589
        Mult/add striped: 86990
Size: 59x16384
        Basic:            122406
        Mult/add basic:   125716
        Striped:          89478
        Mult/add striped: 86576
Size: 60x16384
        Basic:            125612
        Mult/add basic:   130343
        Striped:          86563
        Mult/add striped: 88122

for 16-bit DIGITs:
Size: 58x16384
        Basic:            121537
        Mult/add basic:   121003
        Striped:          88214
        Mult/add striped: 90538
Size: 59x16384
        Basic:            122718
        Mult/add basic:   122775
        Striped:          91592
        Mult/add striped: 89622
Size: 60x16384
        Basic:            125067
        Mult/add basic:   124370
        Striped:          92472
        Mult/add striped: 91338
*/
void CArithmeticPerformanceTester::CompareBasicMultiplicationToStripedMultiplication()
{
    printf("Compare basic to striped\n");
    const unsigned int c_nMaxSizeY = 16384;
    DIGIT *pX = (DIGIT *) malloc(sizeof(DIGIT)*(60+c_nMaxSizeY)*2);
    DIGIT *pY = pX + 60;
    DIGIT *pZ = pY + c_nMaxSizeY;
    for(int i=0; i<60+c_nMaxSizeY; i++) pX[i] = (DIGIT) -1;
    for(size_t j=16; j<=c_nMaxSizeY; j*=2)
    {
        for(size_t i=13; i<=60; i++)
        {
            if(j<i) continue;
            size_t  nIterations = ((size_t) 1000)*(12*c_nMaxSizeY)/(i*j);
            DWORD64 dwTimeBasic = s_Timer.GetMicroseconds();
            for(int k=0;k<nIterations;k++)
            {
                MultUBasic(i, j, pX, pY, pZ, false);
            }
            DWORD64 dwTimeShortLong = s_Timer.GetMicroseconds();
            dwTimeBasic = dwTimeShortLong - dwTimeBasic;
            for(int k=0;k<nIterations;k++)
            {
                MultUStriped(i, j, pX, pY, pZ, false);
            }
            dwTimeShortLong = s_Timer.GetMicroseconds() - dwTimeShortLong;
            DWORD64 dwTimeBasicMultAdd = s_Timer.GetMicroseconds();
            for(int k=0;k<nIterations;k++)
            {
                MultUBasic(i, j, pX, pY, pZ, true);
            }
            DWORD64 dwTimeShortLongAdd = s_Timer.GetMicroseconds();
            dwTimeBasicMultAdd = dwTimeShortLongAdd - dwTimeBasicMultAdd;
            for(int k=0;k<nIterations;k++)
            {
                MultUStriped(i, j, pX, pY, pZ, true);
            }
            dwTimeShortLongAdd = s_Timer.GetMicroseconds() - dwTimeShortLongAdd;
            printf("Size: %ux%u\n\tBasic:            %I64u\n\tMult/add basic:   %I64u\n\tStriped:          %I64u\n\tMult/add striped: %I64u\n", i, j, dwTimeBasic, dwTimeBasicMultAdd, dwTimeShortLong, dwTimeShortLongAdd);
        }
    }
}

/*
32 bit DIGITS
Size 32 x 32 bytes      Memory (basic): 0 kB FFT: 0 kB
Non-FFT multiply:  27 microseconds
FFT multiply:      0 microseconds       Field size: 4 Length: 16
FFT square:        114078730781 microseconds
Size 64 x 64 bytes      Memory (basic): 0 kB FFT: 1 kB
Non-FFT multiply:  30 microseconds
FFT multiply:      0 microseconds       Field size: 4 Length: 32
FFT square:        114078731028 microseconds
Size 128 x 128 bytes    Memory (basic): 0 kB FFT: 2 kB
Non-FFT multiply:  10 microseconds
FFT multiply:      2 microseconds       Field size: 4 Length: 64
FFT square:        114078731261 microseconds
Size 256 x 256 bytes    Memory (basic): 1 kB FFT: 5 kB
Non-FFT multiply:  40 microseconds
FFT multiply:      3 microseconds       Field size: 4 Length: 128
FFT square:        114078731558 microseconds
Size 512 x 512 bytes    Memory (basic): 3 kB FFT: 10 kB
Non-FFT multiply:  23 microseconds
FFT multiply:      13 microseconds      Field size: 4 Length: 256
FFT square:        114078732066 microseconds
Size 1024 x 1024 bytes  Memory (basic): 6 kB FFT: 18 kB
Non-FFT multiply:  102 microseconds
FFT multiply:      26 microseconds      Field size: 8 Length: 256
FFT square:        114078732596 microseconds
Size 2048 x 2048 bytes  Memory (basic): 12 kB FFT: 36 kB
Non-FFT multiply:  90 microseconds
FFT multiply:      116 microseconds     Field size: 8 Length: 512
FFT square:        114078733340 microseconds
Size 4096 x 4096 bytes  Memory (basic): 24 kB FFT: 68 kB
Non-FFT multiply:  338 microseconds
FFT multiply:      297 microseconds     Field size: 16 Length: 512
FFT square:        114078735523 microseconds
Size 8192 x 8192 bytes  Memory (basic): 48 kB FFT: 136 kB
Non-FFT multiply:  710 microseconds
FFT multiply:      621 microseconds     Field size: 16 Length: 1024
FFT square:        114078738585 microseconds
Size 16384 x 16384 bytes        Memory (basic): 96 kB FFT: 264 kB
Non-FFT multiply:  1592 microseconds
FFT multiply:      1582 microseconds    Field size: 32 Length: 1024
FFT square:        114078749031 microseconds
Size 32768 x 32768 bytes        Memory (basic): 192 kB FFT: 528 kB
Non-FFT multiply:  4245 microseconds
FFT multiply:      3526 microseconds    Field size: 32 Length: 2048
FFT square:        114078765029 microseconds
Size 65536 x 65536 bytes        Memory (basic): 384 kB FFT: 1040 kB
Non-FFT multiply:  8801 microseconds
FFT multiply:      9916 microseconds    Field size: 64 Length: 2048
FFT square:        114078805359 microseconds
Size 131072 x 131072 bytes      Memory (basic): 768 kB FFT: 2080 kB
Non-FFT multiply:  25890 microseconds
FFT multiply:      28258 microseconds   Field size: 64 Length: 4096
FFT square:        114078908547 microseconds
Size 262144 x 262144 bytes      Memory (basic): 3072 kB FFT: 4128 kB
Non-FFT multiply:  82192 microseconds
FFT multiply:      66281 microseconds   Field size: 128 Length: 4096
FFT square:        114079141110 microseconds
Size 524288 x 524288 bytes      Memory (basic): 6144 kB FFT: 8256 kB
Non-FFT multiply:  162882 microseconds
FFT multiply:      108014 microseconds  Field size: 128 Length: 8192
FFT square:        114079601906 microseconds
Size 1048576 x 1048576 bytes    Memory (basic): 12288 kB FFT: 16448 kB
Non-FFT multiply:  369003 microseconds
FFT multiply:      295139 microseconds  Field size: 256 Length: 8192
FFT square:        114080663176 microseconds
Size 2097152 x 2097152 bytes    Memory (basic): 24576 kB FFT: 32896 kB
Non-FFT multiply:  1148844 microseconds
FFT multiply:      595737 microseconds  Field size: 256 Length: 16384
FFT square:        114083268701 microseconds
Size 4194304 x 4194304 bytes    Memory (basic): 49152 kB FFT: 65664 kB
Non-FFT multiply:  2671857 microseconds
FFT multiply:      1332463 microseconds Field size: 512 Length: 16384
FFT square:        1268205 microseconds
Size 8388608 x 8388608 bytes    Memory (basic): 98304 kB FFT: 131328 kB
Non-FFT multiply:  5909614 microseconds
FFT multiply:      2737957 microseconds Field size: 512 Length: 32768
FFT square:        2337327 microseconds
Size 16777216 x 16777216 bytes  Memory (basic): 196608 kB FFT: 262400 kB
Non-FFT multiply:  13932783 microseconds
FFT multiply:      7604432 microseconds Field size: 1024 Length: 32768
FFT square:        6184376 microseconds
Size 33554432 x 33554432 bytes  Memory (basic): 393216 kB FFT: 524800 kB
Non-FFT multiply:  41220971 microseconds
FFT multiply:      13514867 microseconds        Field size: 1024 Length: 65536
FFT square:        10451343 microseconds
Size 67108864 x 67108864 bytes  Memory (basic): 786432 kB FFT: 1049088 kB
Non-FFT multiply:  85523827 microseconds
FFT multiply:      33355803 microseconds        Field size: 2048 Length: 65536
FFT square:        27882809 microseconds
Size 134217728 x 134217728 bytes        Memory (basic): 1572864 kB FFT: 2098176 kB
Non-FFT multiply:  193217056 microseconds
FFT multiply:      66109755 microseconds        Field size: 2048 Length: 131072
FFT square:        56747776 microseconds
Size 268435456 x 268435456 bytes        Memory (basic): 3145728 kB FFT: 4195328 kB
Non-FFT multiply:  452288274 microseconds
FFT multiply:      179206162 microseconds       Field size: 4096 Length: 131072
FFT square:        184404624 microseconds

16 bit DIGITs
Size 16 x 16 bytes      Memory (basic): 0 kB FFT: 0 kB
Non-FFT multiply:  31 microseconds
Non-FFT square:    0 microseconds
FFT multiply:      1 microseconds       Field size: 4 Length: 16
FFT square:        1 microseconds
Size 32 x 32 bytes      Memory (basic): 0 kB FFT: 0 kB
Non-FFT multiply:  50 microseconds
Non-FFT square:    1 microseconds
FFT multiply:      0 microseconds       Field size: 4 Length: 32
FFT square:        1 microseconds
Size 64 x 64 bytes      Memory (basic): 0 kB FFT: 1 kB
Non-FFT multiply:  11 microseconds
Non-FFT square:    2 microseconds
FFT multiply:      1 microseconds       Field size: 4 Length: 64
FFT square:        2 microseconds
Size 128 x 128 bytes    Memory (basic): 0 kB FFT: 2 kB
Non-FFT multiply:  38 microseconds
Non-FFT square:    3 microseconds
FFT multiply:      18 microseconds      Field size: 4 Length: 128
FFT square:        4 microseconds
Size 256 x 256 bytes    Memory (basic): 1 kB FFT: 4 kB
Non-FFT multiply:  58 microseconds
Non-FFT square:    25 microseconds
FFT multiply:      26 microseconds      Field size: 8 Length: 128
FFT square:        11 microseconds
Size 512 x 512 bytes    Memory (basic): 3 kB FFT: 9 kB
Non-FFT multiply:  75 microseconds
Non-FFT square:    39 microseconds
FFT multiply:      46 microseconds      Field size: 8 Length: 256
FFT square:        29 microseconds
Size 1024 x 1024 bytes  Memory (basic): 6 kB FFT: 17 kB
Non-FFT multiply:  114 microseconds
Non-FFT square:    159 microseconds
FFT multiply:      100 microseconds     Field size: 16 Length: 256
FFT square:        100 microseconds
Size 2048 x 2048 bytes  Memory (basic): 12 kB FFT: 34 kB
Non-FFT multiply:  316 microseconds
Non-FFT square:    233 microseconds
FFT multiply:      283 microseconds     Field size: 16 Length: 512
FFT square:        251 microseconds
Size 4096 x 4096 bytes  Memory (basic): 24 kB FFT: 66 kB
Non-FFT multiply:  725 microseconds
Non-FFT square:    588 microseconds
FFT multiply:      987 microseconds     Field size: 32 Length: 512
FFT square:        785 microseconds
Size 8192 x 8192 bytes  Memory (basic): 48 kB FFT: 132 kB
Non-FFT multiply:  2218 microseconds
Non-FFT square:    1682 microseconds
FFT multiply:      1922 microseconds    Field size: 32 Length: 1024
FFT square:        1681 microseconds
Size 16384 x 16384 bytes        Memory (basic): 96 kB FFT: 260 kB
Non-FFT multiply:  5141 microseconds
Non-FFT square:    4209 microseconds
FFT multiply:      5926 microseconds    Field size: 64 Length: 1024
FFT square:        4826 microseconds
Size 32768 x 32768 bytes        Memory (basic): 192 kB FFT: 520 kB
Non-FFT multiply:  8867 microseconds
Non-FFT square:    6345 microseconds
FFT multiply:      7293 microseconds    Field size: 64 Length: 2048
FFT square:        6737 microseconds
Size 65536 x 65536 bytes        Memory (basic): 384 kB FFT: 1032 kB
Non-FFT multiply:  23137 microseconds
Non-FFT square:    22782 microseconds
FFT multiply:      24456 microseconds   Field size: 128 Length: 2048
FFT square:        22767 microseconds
Size 131072 x 131072 bytes      Memory (basic): 1536 kB FFT: 2064 kB
Non-FFT multiply:  63011 microseconds
Non-FFT square:    63775 microseconds
FFT multiply:      83102 microseconds   Field size: 128 Length: 4096
FFT square:        48813 microseconds
Size 262144 x 262144 bytes      Memory (basic): 3072 kB FFT: 4112 kB
Non-FFT multiply:  168617 microseconds
Non-FFT square:    138177 microseconds
FFT multiply:      143804 microseconds  Field size: 256 Length: 4096
FFT square:        103052 microseconds
Size 524288 x 524288 bytes      Memory (basic): 6144 kB FFT: 8224 kB
Non-FFT multiply:  420576 microseconds
Non-FFT square:    351718 microseconds
FFT multiply:      237526 microseconds  Field size: 256 Length: 8192
FFT square:        183433 microseconds
Size 1048576 x 1048576 bytes    Memory (basic): 12288 kB FFT: 16416 kB
Non-FFT multiply:  899517 microseconds
Non-FFT square:    897320 microseconds
FFT multiply:      636265 microseconds  Field size: 512 Length: 8192
FFT square:        515954 microseconds
Size 2097152 x 2097152 bytes    Memory (basic): 24576 kB FFT: 32832 kB
Non-FFT multiply:  2324728 microseconds
Non-FFT square:    2135220 microseconds
FFT multiply:      1216412 microseconds Field size: 512 Length: 16384
FFT square:        998334 microseconds
Size 4194304 x 4194304 bytes    Memory (basic): 49152 kB FFT: 65600 kB
Non-FFT multiply:  5555484 microseconds
Non-FFT square:    5937841 microseconds
FFT multiply:      2903248 microseconds Field size: 1024 Length: 16384
FFT square:        2471143 microseconds
Size 8388608 x 8388608 bytes    Memory (basic): 98304 kB FFT: 131200 kB
Non-FFT multiply:  14895423 microseconds
Non-FFT square:    13629755 microseconds
FFT multiply:      6033301 microseconds Field size: 1024 Length: 32768
FFT square:        4981013 microseconds
Size 16777216 x 16777216 bytes  Memory (basic): 196608 kB FFT: 262272 kB
Non-FFT multiply:  34402340 microseconds
Non-FFT square:    32654191 microseconds
FFT multiply:      15810898 microseconds        Field size: 2048 Length: 32768
FFT square:        13497053 microseconds
Size 33554432 x 33554432 bytes  Memory (basic): 393216 kB FFT: 524544 kB
Non-FFT multiply:  87939140 microseconds
Non-FFT square:    74427687 microseconds
FFT multiply:      32209652 microseconds        Field size: 2048 Length: 65536
FFT square:        27299084 microseconds
Size 67108864 x 67108864 bytes  Memory (basic): 786432 kB FFT: 1048832 kB
Non-FFT multiply:  217548127 microseconds
Non-FFT square:    203906559 microseconds
FFT multiply:      78615110 microseconds        Field size: 4096 Length: 65536
FFT square:        67025058 microseconds
Size 134217728 x 134217728 bytes        Memory (basic): 1572864 kB FFT: 2097664 kB
Non-FFT multiply:  492654658 microseconds
Non-FFT square:    480504557 microseconds
FFT multiply:      159877922 microseconds       Field size: 4096 Length: 131072
FFT square:        134434066 microseconds
Size 268435456 x 268435456 bytes        Memory (basic): 3145728 kB FFT: 4194816 kB
Non-FFT multiply:  1393865861 microseconds
Non-FFT square:    1128826332 microseconds
FFT multiply:      438359307 microseconds       Field size: 8192 Length: 131072
FFT square:        367196053 microseconds
*/

void CArithmeticPerformanceTester::CompareBaseMultiplicationToFFT()
{
    CBigIntegerForTest nX,nY,nXCopy,nYCopy,nProduct,nProductBaseline;
    DWORD64            dwStartTime;
    CArithmeticBox     cBox;
    CWorkspace         cWork;
    size_t             nProductSize;
    printf("If you're not doing this with a retail build, you're not getting good numbers\n");
    SaveMultiplicationThresholds();
    // note size 5 DIGITs is the smallest size FFTMult will work with; we start with 8 -- smallest power of 2 which is at least 5
    for(size_t i=8*_DIGIT_SIZE_IN_BITS; i<=((size_t) 1)<<31; i=i<<1)
    {
        size_t nFFTLength,nFieldSize,nChunkSize;
        BYTE   byChunkSize;
        SBitShift nRoot;
        nX.SetRandom(i);
        nY.SetRandom(i);
        nXCopy = nX;
        nYCopy = nY;
        GetFFTSize(nX.GetSize(),nY.GetSize(),nFFTLength,nFieldSize,nChunkSize,byChunkSize,nRoot);
        nProduct.Reserve(nX.GetSize()+nY.GetSize()+1);
        nProductBaseline.Reserve(nX.GetSize()+nY.GetSize());
        c_pnMultiplicationThresholds[e2NByN] = nX.GetSize()+nY.GetSize(); // so we don't use FFT multiply
        c_pnSquareThresholds[e2NByN]         = nX.GetSize()+nY.GetSize(); // so we don't use FFT multiply
        printf("Size %i x %i bytes\tMemory (basic): %I64u kB FFT: %I64u kB\n",
               nX.GetSize()*sizeof(DIGIT),
               nY.GetSize()*sizeof(DIGIT),
               MultiplyMemoryNeeds(nX.GetSize(),nY.GetSize())*sizeof(DIGIT)/1024,
               FFTMultiplyMemoryNeeds(nX.GetSize(),nY.GetSize(),false)*sizeof(DIGIT)/1024);
        if(!cWork.Reserve(MultiplyMemoryNeeds(nX.GetSize(),nY.GetSize())))
        {
            printf("couldn't allocate workspace -- baseline\n");
            break;
        }
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        Multiply(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProductBaseline.GetValue(),cWork.GetSpace());
        dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        printf("Non-FFT multiply:  %I64u microseconds\n",dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        Square(nX.GetSize(), nX.GetValue(), nProduct.GetValue(), cWork.GetSpace());
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        printf("Non-FFT square:    %I64u microseconds\n", dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        nProductSize = nX.GetSize()+nY.GetSize();
        while(0<nProductSize && 0==nProductBaseline.GetValue()[nProductSize-1])
        {
            nProductSize--;
        }
        nProductBaseline.SetSize(nProductSize);
        if(!cWork.Reserve(FFTMultiplyMemoryNeeds(nX.GetSize(),nY.GetSize(),false)))
        {
            printf("couldn't allocate workspace -- FFT\n");
            break;
        }
        ResetTimingData();
        RestoreMultiplicationThresholds(); // so we DO use FFT multiply for subproblems (if appropriate to the size)
        // force top level at least to use FFT
        if (c_pnMultiplicationThresholds[e2NByN] <= nX.GetSize()) c_pnMultiplicationThresholds[e2NByN] = nX.GetSize() - 1;
        if (c_pnMultiplicationThresholds[e2NByN] <= nY.GetSize()) c_pnMultiplicationThresholds[e2NByN] = nY.GetSize() - 1;
        if (c_pnSquareThresholds[e2NByN] <= nX.GetSize())         c_pnSquareThresholds[e2NByN] = nX.GetSize() - 1;
        if (c_pnSquareThresholds[e2NByN] <= nY.GetSize())         c_pnSquareThresholds[e2NByN] = nY.GetSize() - 1;
        dwStartTime = s_Timer.GetMicroseconds();
        Multiply(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProduct.GetValue(),cWork.GetSpace());
        dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        nProductSize = nX.GetSize()+nY.GetSize();
        while(0<nProductSize && 0==nProduct.GetValue()[nProductSize-1])
        {
            nProductSize--;
        }
        nProduct.SetSize(nProductSize);
        printf("FFT multiply:      %I64u microseconds\tField size: %I64u Length: %I64u\n",dwStartTime, nFieldSize, nFFTLength);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        if(nProduct != nProductBaseline)
        {
            printf("Oopsie!  Error found; best investigate\n");
            cWork.CheckBufferguard();
        }
        ResetTimingData();
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        Square(nX.GetSize(),nX.GetValue(),nProduct.GetValue(),cWork.GetSpace());
        dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        printf("FFT square:        %I64u microseconds\n",dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        RestoreMultiplicationThresholds();
    }
}

// checks how long it takes to get the FFT in preparation for a multiplication of 2 numbers of two billion bits each
void CArithmeticPerformanceTester::FFTTimes()
{
    const size_t       c_nTwoBILLION = 2000000000;
    unsigned int       nStartTime;
    size_t             nFFTLength, nFieldSize, nFFTSpace;
    size_t             nChunkSize;
    SBitShift          nRootUnity;
    DIGIT              *pnFFT_x, *pnFFT_XInverse, *pnWorkspace;
    BYTE               byMaxOverflowSize;
    CBigIntegerForTest nX;
    printf("Comparing standard DFT vs reordered DFT.  Doing this in retail?  If not, you won't get good numbers\n");
    nX.SetRandom(c_nTwoBILLION);
    GetFFTSize(nX.GetSize(), nX.GetSize(), nFFTLength, nFieldSize, nChunkSize, byMaxOverflowSize, nRootUnity);
    nFFTSpace      = FFTMultiplyMemoryNeeds(nX.GetSize(), nX.GetSize(), false);
    pnFFT_x        = (DIGIT *) malloc(sizeof(DIGIT)*nFFTSpace);
    pnFFT_XInverse = pnFFT_x + (nFFTLength/2);
    pnWorkspace    = (DIGIT *) malloc(sizeof(DIGIT)*1000000); // should be plenty of space
    // do an untimed FFT, so always start with the same memory position
    FFT(nX.GetValue(), pnFFT_x, nX.GetSize(), nChunkSize, nChunkSize, nFFTLength, nFieldSize, nRootUnity, pnWorkspace);
    // and a timed one
    nStartTime = ::GetTickCount();
    FFT(nX.GetValue(), pnFFT_x, nX.GetSize(), nChunkSize, nChunkSize, nFFTLength, nFieldSize, nRootUnity, pnWorkspace);
    printf("Standard FFT took %i milliseconds for a %I64u-bit number\n",::GetTickCount()-nStartTime,c_nTwoBILLION);
    // Repeat for inverse FFT
    FFT_Inverse(pnFFT_x, pnFFT_XInverse, nFFTLength, nRootUnity, nFieldSize, pnWorkspace);
    nStartTime = ::GetTickCount();
    FFT_Inverse(pnFFT_x, pnFFT_XInverse, nFFTLength, nRootUnity, nFieldSize, pnWorkspace);
    printf("Standard FFT inverse took %i milliseconds for a %I64u-bit number\n", ::GetTickCount() - nStartTime, c_nTwoBILLION);
}

/*
Some sample times from the test: 32-bit DIGITs *definitely* work better on the computer the run was done on!
Values taken with parameters optimized for the given DIGIT size

32 bit DIGITS
Multiply two 4194304 BYTE numbers:      1100601 microseconds
Square   two 4194304 BYTE numbers:      923203 microseconds
Multiply two 8388608 BYTE numbers:      2286448 microseconds
Square   two 8388608 BYTE numbers:      1903781 microseconds
Multiply two 16777216 BYTE numbers:     5622603 microseconds
Square   two 16777216 BYTE numbers:     4556410 microseconds
Multiply two 33554432 BYTE numbers:     11904948 microseconds
Square   two 33554432 BYTE numbers:     9756674 microseconds
Multiply two 67108864 BYTE numbers:     29374374 microseconds
Square   two 67108864 BYTE numbers:     24645173 microseconds
Multiply two 134217728 BYTE numbers:    59826451 microseconds
Square   two 134217728 BYTE numbers:    48053681 microseconds
Multiply two 268435456 BYTE numbers:    144211343 microseconds
Square   two 268435456 BYTE numbers:    130277890 microseconds

16 bit DIGITs
Multiply two 4194304 BYTE numbers:      2947556 microseconds
Square   two 4194304 BYTE numbers:      2409407 microseconds
Multiply two 8388608 BYTE numbers:      6057252 microseconds
Square   two 8388608 BYTE numbers:      4923954 microseconds
Multiply two 16777216 BYTE numbers:     14923656 microseconds
Square   two 16777216 BYTE numbers:     13283467 microseconds
Multiply two 33554432 BYTE numbers:     30380220 microseconds
Square   two 33554432 BYTE numbers:     28284801 microseconds
Multiply two 67108864 BYTE numbers:     78958932 microseconds
Square   two 67108864 BYTE numbers:     73027993 microseconds
Multiply two 134217728 BYTE numbers:    161109520 microseconds
Square   two 134217728 BYTE numbers:    134518998 microseconds
Multiply two 268435456 BYTE numbers:    401347268 microseconds
Square   two 268435456 BYTE numbers:    374121914 microseconds
*/

void CArithmeticPerformanceTester::TestMultiplyTimes()
{
    CBigIntegerForTest nX,nY,nProduct;
    DWORD64            dwStartTime;
    CWorkspace         cWork;
    size_t             nProductSize;
    printf("If you're not doing this with a retail build, you're not getting good numbers.  All sizes in BYTES, not DIGITs!\n");
    for(size_t i=2;i<=(((size_t) 1)<<28);i=i<<1)
    {
        nX.SetRandom(i<<3);
        nY.SetRandom(i<<3);
        nProduct.Reserve(nX.GetSize()+nY.GetSize());
        size_t nMemoryNeeds = max(MultiplyMemoryNeeds(nX.GetSize(),nY.GetSize()), SquareMemoryNeeds(nX.GetSize(), nY.GetSize()));
        if(!cWork.Reserve(nMemoryNeeds))
        {
            printf("couldn't allocate workspace -- baseline\n");
            break;
        }
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        Multiply(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue(), cWork.GetSpace());
        dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        printf("Multiply two %i BYTE numbers:\t%I64u microseconds\n", nX.GetSize() * sizeof(DIGIT), dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        Square(nX.GetSize(), nX.GetValue(), nProduct.GetValue(), cWork.GetSpace());
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        printf("Square a     %i BYTE numbers:\t%I64u microseconds\n", nX.GetSize() * sizeof(DIGIT), dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
    }
}

/*
32-bit DIGITS
Multiply size:    2000000x2000000 (BYTEs): 251673 microseconds (FFT multiply)
Square size:      2000000x2000000 (BYTEs): 192092 microseconds (FFT multiply)
Multiply size:    2000000x2000000 (BYTEs): 834918 microseconds (2n by n multiply)
Square size:      2000000x2000000 (BYTEs): 751884 microseconds (2n by n multiply)
Multiply size:    2000000x2000000 (BYTEs): 658633 microseconds (9 by 5 multiply)
Square size:      2000000x2000000 (BYTEs): 644464 microseconds (9 by 5 multiply)
Multiply size:    2000000x2000000 (BYTEs): 819698 microseconds (7 by 4 multiply)
Square size:      2000000x2000000 (BYTEs): 790391 microseconds (7 by 4 multiply)
Multiply size:    2000000x2000000 (BYTEs): 1452709 microseconds (5 by 3 multiply)
Square size:      2000000x2000000 (BYTEs): 1267758 microseconds (5 by 3 multiply)
Multiply size:    2000000x2000000 (BYTEs): 4086818 microseconds (3 by 2 multiply)
Square size:      2000000x2000000 (BYTEs): 3722569 microseconds (3 by 2 multiply)
Multiply size:    2000000x2000000 (BYTEs): 126453486 microseconds (striped)
Multiply size:    2000000x2000000 (BYTEs): 154961095 microseconds (basic)
Multiply size:    2000000x2000000 (BYTEs): 308394876 microseconds (oracle)

Multiply size:    4000000x4000000 (BYTEs): 557002 microseconds (FFT multiply)
Square size:      4000000x4000000 (BYTEs): 427502 microseconds (FFT multiply)
Multiply size:    4000000x4000000 (BYTEs): 2268030 microseconds (2n by n multiply)
Square size:      4000000x4000000 (BYTEs): 1868426 microseconds (2n by n multiply)
Multiply size:    4000000x4000000 (BYTEs): 1778068 microseconds (9 by 5 multiply)
Square size:      4000000x4000000 (BYTEs): 1651463 microseconds (9 by 5 multiply)
Multiply size:    4000000x4000000 (BYTEs): 2593188 microseconds (7 by 4 multiply)
Square size:      4000000x4000000 (BYTEs): 2240716 microseconds (7 by 4 multiply)
Multiply size:    4000000x4000000 (BYTEs): 4880952 microseconds (5 by 3 multiply)
Square size:      4000000x4000000 (BYTEs): 4047068 microseconds (5 by 3 multiply)
Multiply size:    4000000x4000000 (BYTEs): 12374641 microseconds (3 by 2 multiply)
Square size:      4000000x4000000 (BYTEs): 12304156 microseconds (3 by 2 multiply)
Multiply size:    4000000x4000000 (BYTEs): 505658265 microseconds (striped)
Multiply size:    4000000x4000000 (BYTEs): 613809664 microseconds (basic)
Multiply size:    4000000x4000000 (BYTEs): 1252677395 microseconds (oracle)

Multiply size:    8000000x8000000 (BYTEs): 1123330 microseconds (FFT multiply)
Square size:      8000000x8000000 (BYTEs): 948789 microseconds (FFT multiply)
Multiply size:    8000000x8000000 (BYTEs): 5475420 microseconds (2n by n multiply)
Square size:      8000000x8000000 (BYTEs): 5021163 microseconds (2n by n multiply)
Multiply size:    8000000x8000000 (BYTEs): 4334139 microseconds (9 by 5 multiply)
Square size:      8000000x8000000 (BYTEs): 4210769 microseconds (9 by 5 multiply)
Multiply size:    8000000x8000000 (BYTEs): 6132156 microseconds (7 by 4 multiply)
Square size:      8000000x8000000 (BYTEs): 5460643 microseconds (7 by 4 multiply)
Multiply size:    8000000x8000000 (BYTEs): 11100345 microseconds (5 by 3 multiply)
Square size:      8000000x8000000 (BYTEs): 10057452 microseconds (5 by 3 multiply)
Multiply size:    8000000x8000000 (BYTEs): 34465058 microseconds (3 by 2 multiply)
Square size:      8000000x8000000 (BYTEs): 34735421 microseconds (3 by 2 multiply)

Multiply size:    16000000x16000000 (BYTEs): 2468035 microseconds (FFT multiply)
Square size:      16000000x16000000 (BYTEs): 2023476 microseconds (FFT multiply)
Multiply size:    16000000x16000000 (BYTEs): 15222628 microseconds (2n by n multiply)
Square size:      16000000x16000000 (BYTEs): 13272742 microseconds (2n by n multiply)
Multiply size:    16000000x16000000 (BYTEs): 12547102 microseconds (9 by 5 multiply)
Square size:      16000000x16000000 (BYTEs): 10554118 microseconds (9 by 5 multiply)
Multiply size:    16000000x16000000 (BYTEs): 15959370 microseconds (7 by 4 multiply)
Square size:      16000000x16000000 (BYTEs): 13713883 microseconds (7 by 4 multiply)
Multiply size:    16000000x16000000 (BYTEs): 31374836 microseconds (5 by 3 multiply)
Square size:      16000000x16000000 (BYTEs): 28512041 microseconds (5 by 3 multiply)
Multiply size:    16000000x16000000 (BYTEs): 102290625 microseconds (3 by 2 multiply)
Square size:      16000000x16000000 (BYTEs): 100570124 microseconds (3 by 2 multiply)

Multiply size:    32000000x32000000 (BYTEs): 6149474 microseconds (FFT multiply)
Square size:      32000000x32000000 (BYTEs): 5083969 microseconds (FFT multiply)
Multiply size:    32000000x32000000 (BYTEs): 40877672 microseconds (2n by n multiply)
Square size:      32000000x32000000 (BYTEs): 27400029 microseconds (2n by n multiply)
Multiply size:    32000000x32000000 (BYTEs): 29220686 microseconds (9 by 5 multiply)
Square size:      32000000x32000000 (BYTEs): 28408017 microseconds (9 by 5 multiply)
Multiply size:    32000000x32000000 (BYTEs): 43989493 microseconds (7 by 4 multiply)
Square size:      32000000x32000000 (BYTEs): 41331158 microseconds (7 by 4 multiply)
Multiply size:    32000000x32000000 (BYTEs): 88662465 microseconds (5 by 3 multiply)
Square size:      32000000x32000000 (BYTEs): 80292080 microseconds (5 by 3 multiply)
Multiply size:    32000000x32000000 (BYTEs): 303405435 microseconds (3 by 2 multiply)
Square size:      32000000x32000000 (BYTEs): 301068093 microseconds (3 by 2 multiply)

Multiply size:    64000000x64000000 (BYTEs): 11875240 microseconds (FFT multiply)
Square size:      64000000x64000000 (BYTEs): 9348888 microseconds (FFT multiply)
Multiply size:    64000000x64000000 (BYTEs): 100436910 microseconds (2n by n multiply)
Square size:      64000000x64000000 (BYTEs): 76069862 microseconds (2n by n multiply)
Multiply size:    64000000x64000000 (BYTEs): 84580777 microseconds (9 by 5 multiply)
Square size:      64000000x64000000 (BYTEs): 71935567 microseconds (9 by 5 multiply)
Multiply size:    64000000x64000000 (BYTEs): 128364925 microseconds (7 by 4 multiply)
Square size:      64000000x64000000 (BYTEs): 104553988 microseconds (7 by 4 multiply)
Multiply size:    64000000x64000000 (BYTEs): 269061820 microseconds (5 by 3 multiply)
Square size:      64000000x64000000 (BYTEs): 223316177 microseconds (5 by 3 multiply)
Multiply size:    64000000x64000000 (BYTEs): 928215836 microseconds (3 by 2 multiply)
Square size:      64000000x64000000 (BYTEs): 970136225 microseconds (3 by 2 multiply)

Multiply size:    128000000x128000000 (BYTEs): 29405942 microseconds (FFT multiply)
Square size:      128000000x128000000 (BYTEs): 23790187 microseconds (FFT multiply)
Multiply size:    128000000x128000000 (BYTEs): 274310216 microseconds (2n by n multiply)
Square size:      128000000x128000000 (BYTEs): 187529349 microseconds (2n by n multiply)
Multiply size:    128000000x128000000 (BYTEs): 207925382 microseconds (9 by 5 multiply)
Square size:      128000000x128000000 (BYTEs): 181342955 microseconds (9 by 5 multiply)
Multiply size:    128000000x128000000 (BYTEs): 297368752 microseconds (7 by 4 multiply)
Square size:      128000000x128000000 (BYTEs): 274044456 microseconds (7 by 4 multiply)
Multiply size:    128000000x128000000 (BYTEs): 650464368 microseconds (5 by 3 multiply)
Square size:      128000000x128000000 (BYTEs): 602384099 microseconds (5 by 3 multiply)
Multiply size:    128000000x128000000 (BYTEs): 2712021910 microseconds (3 by 2 multiply)
Square size:      128000000x128000000 (BYTEs): 2718924601 microseconds (3 by 2 multiply)

16 bit DIGITs
Multiply size:    2000000x2000000 (BYTEs): 593065 microseconds (FFT multiply)
Square size:      2000000x2000000 (BYTEs): 533753 microseconds (FFT multiply)
Multiply size:    2000000x2000000 (BYTEs): 2217976 microseconds (2n by n multiply)
Square size:      2000000x2000000 (BYTEs): 2019581 microseconds (2n by n multiply)
Multiply size:    2000000x2000000 (BYTEs): 2347608 microseconds (7 by 4 multiply)
Square size:      2000000x2000000 (BYTEs): 2070305 microseconds (7 by 4 multiply)
Multiply size:    2000000x2000000 (BYTEs): 4101707 microseconds (5 by 3 multiply)
Square size:      2000000x2000000 (BYTEs): 3696212 microseconds (5 by 3 multiply)
Multiply size:    2000000x2000000 (BYTEs): 11594262 microseconds (3 by 2 multiply)
Square size:      2000000x2000000 (BYTEs): 11489087 microseconds (3 by 2 multiply)
Multiply size:    2000000x2000000 (BYTEs): 476378162 microseconds (striped)
Multiply size:    2000000x2000000 (BYTEs): 589729561 microseconds (basic)
Multiply size:    2000000x2000000 (BYTEs): 1180028907 microseconds (oracle)

Multiply size:    4000000x4000000 (BYTEs): 1221572 microseconds (FFT multiply)
Square size:      4000000x4000000 (BYTEs): 1004080 microseconds (FFT multiply)
Multiply size:    4000000x4000000 (BYTEs): 5389458 microseconds (2n by n multiply)
Square size:      4000000x4000000 (BYTEs): 4899371 microseconds (2n by n multiply)
Multiply size:    4000000x4000000 (BYTEs): 6512852 microseconds (7 by 4 multiply)
Square size:      4000000x4000000 (BYTEs): 5802297 microseconds (7 by 4 multiply)
Multiply size:    4000000x4000000 (BYTEs): 11359357 microseconds (5 by 3 multiply)
Square size:      4000000x4000000 (BYTEs): 9895566 microseconds (5 by 3 multiply)
Multiply size:    4000000x4000000 (BYTEs): 33496773 microseconds (3 by 2 multiply)
Square size:      4000000x4000000 (BYTEs): 32928701 microseconds (3 by 2 multiply)
Multiply size:    4000000x4000000 (BYTEs): 1890552244 microseconds (striped)
Multiply size:    4000000x4000000 (BYTEs): 2344962362 microseconds (basic)
Multiply size:    4000000x4000000 (BYTEs): 4721174561 microseconds (oracle)

Multiply size:    8000000x8000000 (BYTEs): 2896190 microseconds (FFT multiply)
Square size:      8000000x8000000 (BYTEs): 2424425 microseconds (FFT multiply)
Multiply size:    8000000x8000000 (BYTEs): 13923610 microseconds (2n by n multiply)
Square size:      8000000x8000000 (BYTEs): 12552018 microseconds (2n by n multiply)
Multiply size:    8000000x8000000 (BYTEs): 16629921 microseconds (7 by 4 multiply)
Square size:      8000000x8000000 (BYTEs): 14431314 microseconds (7 by 4 multiply)
Multiply size:    8000000x8000000 (BYTEs): 31100635 microseconds (5 by 3 multiply)
Square size:      8000000x8000000 (BYTEs): 27725806 microseconds (5 by 3 multiply)
Multiply size:    8000000x8000000 (BYTEs): 99104068 microseconds (3 by 2 multiply)
Square size:      8000000x8000000 (BYTEs): 99239545 microseconds (3 by 2 multiply)

Multiply size:    16000000x16000000 (BYTEs): 5927702 microseconds (FFT multiply)
Square size:      16000000x16000000 (BYTEs): 4916469 microseconds (FFT multiply)
Multiply size:    16000000x16000000 (BYTEs): 32037259 microseconds (2n by n multiply)
Square size:      16000000x16000000 (BYTEs): 30573220 microseconds (2n by n multiply)
Multiply size:    16000000x16000000 (BYTEs): 45869238 microseconds (7 by 4 multiply)
Square size:      16000000x16000000 (BYTEs): 40063921 microseconds (7 by 4 multiply)
Multiply size:    16000000x16000000 (BYTEs): 88841375 microseconds (5 by 3 multiply)
Square size:      16000000x16000000 (BYTEs): 77777671 microseconds (5 by 3 multiply)
Multiply size:    16000000x16000000 (BYTEs): 299065962 microseconds (3 by 2 multiply)
Square size:      16000000x16000000 (BYTEs): 298279216 microseconds (3 by 2 multiply)

Multiply size:    32000000x32000000 (BYTEs): 15968507 microseconds (FFT multiply)
Square size:      32000000x32000000 (BYTEs): 13565165 microseconds (FFT multiply)
Multiply size:    32000000x32000000 (BYTEs): 81020720 microseconds (2n by n multiply)
Square size:      32000000x32000000 (BYTEs): 69348834 microseconds (2n by n multiply)
Multiply size:    32000000x32000000 (BYTEs): 115158987 microseconds (7 by 4 multiply)
Square size:      32000000x32000000 (BYTEs): 102655030 microseconds (7 by 4 multiply)
Multiply size:    32000000x32000000 (BYTEs): 241853955 microseconds (5 by 3 multiply)
Square size:      32000000x32000000 (BYTEs): 211415259 microseconds (5 by 3 multiply)
Multiply size:    32000000x32000000 (BYTEs): 900405243 microseconds (3 by 2 multiply)
Square size:      32000000x32000000 (BYTEs): 893959765 microseconds (3 by 2 multiply)

Multiply size:    64000000x64000000 (BYTEs): 32590204 microseconds (FFT multiply)
Square size:      64000000x64000000 (BYTEs): 27075589 microseconds (FFT multiply)
Multiply size:    64000000x64000000 (BYTEs): 224562917 microseconds (2n by n multiply)
Square size:      64000000x64000000 (BYTEs): 190402229 microseconds (2n by n multiply)
Multiply size:    64000000x64000000 (BYTEs): 333088313 microseconds (7 by 4 multiply)
Square size:      64000000x64000000 (BYTEs): 282948628 microseconds (7 by 4 multiply)
Multiply size:    64000000x64000000 (BYTEs): 658882220 microseconds (5 by 3 multiply)
Square size:      64000000x64000000 (BYTEs): 583739026 microseconds (5 by 3 multiply)
Multiply size:    64000000x64000000 (BYTEs): 2692320866 microseconds (3 by 2 multiply)
Square size:      64000000x64000000 (BYTEs): 2689254297 microseconds (3 by 2 multiply)

Multiply size:    128000000x128000000 (BYTEs): 79336397 microseconds (FFT multiply)
Square size:      128000000x128000000 (BYTEs): 66080562 microseconds (FFT multiply)
Multiply size:    128000000x128000000 (BYTEs): 458967734 microseconds (2n by n multiply)
Square size:      128000000x128000000 (BYTEs): 447166593 microseconds (2n by n multiply)
Multiply size:    128000000x128000000 (BYTEs): 806436738 microseconds (7 by 4 multiply)
Square size:      128000000x128000000 (BYTEs): 731690450 microseconds (7 by 4 multiply)
Multiply size:    128000000x128000000 (BYTEs): 1867321884 microseconds (5 by 3 multiply)
Square size:      128000000x128000000 (BYTEs): 1628672508 microseconds (5 by 3 multiply)
Multiply size:    128000000x128000000 (BYTEs): 8081704413 microseconds (3 by 2 multiply)
Square size:      128000000x128000000 (BYTEs): 8110045542 microseconds (3 by 2 multiply)
*/
void CArithmeticPerformanceTester::CompareMultiplicationAlgorithms()
{
    const unsigned int c_nMinProblemSize = 2000000, c_nMaxProblemSize = 128000000; // number of BYTEs in numbers to multiply
    CBigIntegerForTest nX, nY, nProduct;
    DWORD64            dwStartTime;
#if(_CollectDetailedTimingData)
    DWORD64            dwTimestamp;
#endif
    CWorkspace         cWork;
    size_t             nProductSize;
    SaveMultiplicationThresholds();
    printf("If you're not doing this with a retail build, you're not getting good numbers.  All sizes in BYTES, not DIGITs!\n");

    for (int nProblemSize = c_nMinProblemSize; nProblemSize <= c_nMaxProblemSize; nProblemSize *= 2)
    {
        RestoreMultiplicationThresholds();
        nX.SetRandom(nProblemSize*8);
        nY.SetRandom(nProblemSize*8);
        nProduct.Reserve(nX.GetSize() + nY.GetSize());
        for (int eAlgorithm = eFFTMult; eBasicMultiply < eAlgorithm; eAlgorithm--)
        {
            c_pnMultiplicationThresholds[eAlgorithm] = 2000000000; // to force use of algorithm for any large problem
            c_pnSquareThresholds[eAlgorithm]         = 2000000000; // to force use of algorithm for any large problem
            unsigned int nMemoryNeeds = MultiplyMemoryNeeds(nX.GetSize(), nY.GetSize());
            if (!cWork.Reserve(nMemoryNeeds + 1))
            {
                printf("couldn't allocate workspace\n");
                return;
            }
            cWork.GetSpace()[nMemoryNeeds] = TEST_BUFFERGUARD; // validate not using more memory than expected
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
            Multiply(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue(), cWork.GetSpace());
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Multiply size:    %I64ux%I64u (BYTEs): %I64u microseconds (%s)\n",  nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime, GetMultiplicationAlgorithmName((EMultiplyAlgorithm) eAlgorithm));
            if (TEST_BUFFERGUARD != cWork.GetSpace()[nMemoryNeeds])
            {
                printf("Overran workspace memory bounds for algorithm %i multiply.  Oops.\n", eAlgorithm);
                return;
            }
            ReportMeasuredComponentTimingData(eMultiplicationMeasured);
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
            Square(nX.GetSize(), nX.GetValue(), nProduct.GetValue(), cWork.GetSpace());
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Square size:      %I64ux%I64u (BYTEs): %I64u microseconds (%s)\n", nX.GetSize()*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime, GetMultiplicationAlgorithmName((EMultiplyAlgorithm) eAlgorithm));
            if (TEST_BUFFERGUARD != cWork.GetSpace()[nMemoryNeeds])
            {
                printf("Overran workspace memory bounds for algorithm %i square.  Oops.\n", eAlgorithm);
                return;
            }
            ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        }
        if(nProblemSize<=4000000)
        {
            // only do basic multiply comparison for relatively small problem sizes -- too slow!
            c_pnMultiplicationThresholds[eBasicMultiply] = 10000000000; // to force use of algorithm for any large problem
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
            Multiply(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue(), cWork.GetSpace());
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Multiply size:    %I64ux%I64u (BYTEs): %I64u microseconds (striped)\n", nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime);
            ReportMeasuredComponentTimingData(eMultiplicationMeasured);
            dwStartTime = s_Timer.GetMicroseconds();
            MultUBasic(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue(), false);
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Multiply size:    %I64ux%I64u (BYTEs): %I64u microseconds (basic)\n", nX.GetSize() * sizeof(DIGIT), nY.GetSize() * sizeof(DIGIT), dwStartTime);
            dwStartTime = s_Timer.GetMicroseconds();
            MultOracle(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue());
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Multiply size:    %I64ux%I64u (BYTEs): %I64u microseconds (oracle)\n", nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime);
        }
        printf("\n");
    }
}

/*
32-bit DIGITs
Time for 65536 1000x1000 BYTE multiplications: 1134793 microseconds
Time for 65536 divisions of 2000 BYTE number by 1000 BYTE number: 9439219 microseconds (divide:multiply ratio: 8.318009) -- basic
Time for 65536 divisions of 2000 BYTE number by 1000 BYTE number: 3102969 microseconds (divide:multiply ratio: 2.734392)
Time for 65536 1000x2000 BYTE multiplications: 10405330 microseconds
Time for 65536 divisions of 3000 BYTE number by 1000 BYTE number: 5608694 microseconds (divide:multiply ratio: 0.539021)
Time for 65536 divisions of 3000 BYTE number by 2000 BYTE number: 3779414 microseconds (divide:multiply ratio: 0.363219)
Time for 4096 10000x10000 BYTE multiplications: 1816822 microseconds
Time for 4096 divisions of 20000 BYTE number by 10000 BYTE number: 61882764 microseconds (divide:multiply ratio: 34.060993) -- basic
Time for 4096 divisions of 20000 BYTE number by 10000 BYTE number: 5338165 microseconds (divide:multiply ratio: 2.938188)
Time for 4096 10000x20000 BYTE multiplications: 6543744 microseconds
Time for 4096 divisions of 30000 BYTE number by 10000 BYTE number: 11096384 microseconds (divide:multiply ratio: 1.695724)
Time for 4096 divisions of 30000 BYTE number by 20000 BYTE number: 7206856 microseconds (divide:multiply ratio: 1.101335)
Time for 128 100000x100000 BYTE multiplications: 1381880 microseconds
Time for 128 divisions of 200000 BYTE number by 100000 BYTE number: 204345299 microseconds (divide:multiply ratio: 147.874847) -- basic
Time for 128 divisions of 200000 BYTE number by 100000 BYTE number: 4550769 microseconds (divide:multiply ratio: 3.293172)
Time for 128 100000x200000 BYTE multiplications: 2633226 microseconds
Time for 128 divisions of 300000 BYTE number by 100000 BYTE number: 8747797 microseconds (divide:multiply ratio: 3.322084)
Time for 128 divisions of 300000 BYTE number by 200000 BYTE number: 5715540 microseconds (divide:multiply ratio: 2.170547)
Time for 16 1000000x1000000 BYTE multiplications: 1577745 microseconds
Time for 16 divisions of 2000000 BYTE number by 1000000 BYTE number: 1954689266 microseconds (divide:multiply ratio: 1238.913330) -- basic
Time for 16 divisions of 2000000 BYTE number by 1000000 BYTE number: 10979541 microseconds (divide:multiply ratio: 6.959009)
Time for 16 1000000x2000000 BYTE multiplications: 3077097 microseconds
Time for 16 divisions of 3000000 BYTE number by 1000000 BYTE number: 21265340 microseconds (divide:multiply ratio: 6.910845)
Time for 16 divisions of 3000000 BYTE number by 2000000 BYTE number: 12647639 microseconds (divide:multiply ratio: 4.110250)
Time for 1 10000000x10000000 BYTE multiplications: 2302350 microseconds
Time for 1 divisions of 20000000 BYTE number by 10000000 BYTE number: 14493098 microseconds (divide:multiply ratio: 6.294915)
Time for 1 10000000x20000000 BYTE multiplications: 4832709 microseconds
Time for 1 divisions of 30000000 BYTE number by 10000000 BYTE number: 29517777 microseconds (divide:multiply ratio: 6.107915)
Time for 1 divisions of 30000000 BYTE number by 20000000 BYTE number: 17134261 microseconds (divide:multiply ratio: 3.545477)
Time for 1 100000000x100000000 BYTE multiplications: 30472178 microseconds
Time for 1 divisions of 200000000 BYTE number by 100000000 BYTE number: 198437979 microseconds (divide:multiply ratio: 6.512104)
Time for 1 100000000x200000000 BYTE multiplications: 59968542 microseconds
Time for 1 divisions of 300000000 BYTE number by 100000000 BYTE number: 397395738 microseconds (divide:multiply ratio: 6.626737)
Time for 1 divisions of 300000000 BYTE number by 200000000 BYTE number: 233535932 microseconds (divide:multiply ratio: 3.894307)

16-bit DIGITs
Time for 32768 1000x1000 BYTE multiplications: 1602430 microseconds
Time for 32768 divisions of 2000 BYTE number by 1000 BYTE number: 18571035 microseconds (divide:multiply ratio: 11.589296) -- basic
Time for 32768 divisions of 2000 BYTE number by 1000 BYTE number: 4806437 microseconds (divide:multiply ratio: 2.999468)
Time for 32768 1000x2000 BYTE multiplications: 9872040 microseconds
Time for 32768 divisions of 3000 BYTE number by 1000 BYTE number: 8908027 microseconds (divide:multiply ratio: 0.902349)
Time for 32768 divisions of 3000 BYTE number by 2000 BYTE number: 6473980 microseconds (divide:multiply ratio: 0.655789)
Time for 1024 10000x10000 BYTE multiplications: 1538414 microseconds
Time for 1024 divisions of 20000 BYTE number by 10000 BYTE number: 80355308 microseconds (divide:multiply ratio: 52.232567) -- basic
Time for 1024 divisions of 20000 BYTE number by 10000 BYTE number: 4208659 microseconds (divide:multiply ratio: 2.735713)
Time for 1024 10000x20000 BYTE multiplications: 3822785 microseconds
Time for 1024 divisions of 30000 BYTE number by 10000 BYTE number: 7942428 microseconds (divide:multiply ratio: 2.077655)
Time for 1024 divisions of 30000 BYTE number by 20000 BYTE number: 5634889 microseconds (divide:multiply ratio: 1.474027)
Time for 64 100000x100000 BYTE multiplications: 1577503 microseconds
Time for 64 divisions of 200000 BYTE number by 100000 BYTE number: 457194195 microseconds (divide:multiply ratio: 289.821442) -- basic
Time for 64 divisions of 200000 BYTE number by 100000 BYTE number: 6589952 microseconds (divide:multiply ratio: 4.177458)
Time for 64 100000x200000 BYTE multiplications: 3296531 microseconds
Time for 64 divisions of 300000 BYTE number by 100000 BYTE number: 12863038 microseconds (divide:multiply ratio: 3.901992)
Time for 64 divisions of 300000 BYTE number by 200000 BYTE number: 8809091 microseconds (divide:multiply ratio: 2.672230)
Time for 4 1000000x1000000 BYTE multiplications: 1129815 microseconds
Time for 4 divisions of 2000000 BYTE number by 1000000 BYTE number: 1645700111 microseconds (divide:multiply ratio: 1456.610229) -- basic
Time for 4 divisions of 2000000 BYTE number by 1000000 BYTE number: 6339988 microseconds (divide:multiply ratio: 5.611527)
Time for 4 1000000x2000000 BYTE multiplications: 1884850 microseconds
Time for 4 divisions of 3000000 BYTE number by 1000000 BYTE number: 12405217 microseconds (divide:multiply ratio: 6.581541)
Time for 4 divisions of 3000000 BYTE number by 2000000 BYTE number: 7139491 microseconds (divide:multiply ratio: 3.787830)
Time for 1 10000000x10000000 BYTE multiplications: 6143587 microseconds
Time for 1 divisions of 20000000 BYTE number by 10000000 BYTE number: 39616527 microseconds (divide:multiply ratio: 6.448436)
Time for 1 10000000x20000000 BYTE multiplications: 11816029 microseconds
Time for 1 divisions of 30000000 BYTE number by 10000000 BYTE number: 74134939 microseconds (divide:multiply ratio: 6.274099)
Time for 1 divisions of 30000000 BYTE number by 20000000 BYTE number: 44677393 microseconds (divide:multiply ratio: 3.781084)
Time for 1 100000000x100000000 BYTE multiplications: 79057210 microseconds
Time for 1 divisions of 200000000 BYTE number by 100000000 BYTE number: 484658657 microseconds (divide:multiply ratio: 6.130480)
Time for 1 100000000x200000000 BYTE multiplications: 159440073 microseconds
Time for 1 divisions of 300000000 BYTE number by 100000000 BYTE number: 1047474405 microseconds (divide:multiply ratio: 6.569706)
Time for 1 divisions of 300000000 BYTE number by 200000000 BYTE number: 664104722 microseconds (divide:multiply ratio: 4.165231)
*/
void CArithmeticPerformanceTester::CompareDivideTimes()
{
    size_t             nWorkspaceMemoryNeeds;
    const unsigned int c_nMinSize = 1000, c_nMaxSize = 100000000; // my system can allocate enough memory for 100,000,000 -- but not 1,000,000,000
    CBigIntegerForTest nX, nXCopy, nY, nProduct1, nProduct2, nDiv;
    DWORD64            dwStartTime, dwMultTime;
    unsigned int       nIterations;
    CWorkspace         cWork;
    size_t             nDivSize, nRemainderSize;
    unsigned int       nDivideThresholdSmallOriginal = c_nDivideThresholdSmall;
    SaveMultiplicationThresholds();
    printf("If you're not doing this with a retail build, you're not getting good numbers.  All sizes in BYTES, not DIGITs!\n");
    for (int nSize = c_nMinSize; nSize <= c_nMaxSize; nSize *= 10)
    {
        nX.SetRandom(nSize*8); // want size in BYTEs; set random size bits
        nY.SetRandom(2*nSize*8); // want size in BYTES; set random size bits
        nProduct1.Reserve(nX.GetSize() + nY.GetSize());
        nProduct2.Reserve(nX.GetSize() + nY.GetSize());
        nDiv.Reserve(nY.GetSize()+1);
        cWork.Reserve(MultiplyMemoryNeeds(nX.GetSize(), nY.GetSize()));
        cWork.Reserve(DivisionMemoryNeeds(nX.GetSize() + nY.GetSize(), nX.GetSize()));
        cWork.Reserve(DivisionMemoryNeeds(nX.GetSize() + nY.GetSize(), nY.GetSize()));
        // find out how many iterations needed to take 10+ seconds for the given multiply size
        nIterations = 1;
        do
        {
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
            for (int i=0; i<nIterations; i++)
            {
                Multiply(nX.GetSize(), nX.GetSize(), nX.GetValue(), nY.GetValue(), nProduct1.GetValue(), cWork.GetSpace());
            }
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            if(1000000<dwStartTime || true) break; // 10 seconds better?  Or 1 second? // debug restore todo
            nIterations *= 2;
        }
        while (true);
        printf("Time for %i %ix%i BYTE multiplications: %I64u microseconds\n", nIterations, nX.GetSize()*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        ResetTimingData();
        dwMultTime = dwStartTime;
        if(nX.GetSize()<=1000000 && false) // debug restore todo
        {
            c_nDivideThresholdSmall = 2000000000; // force the system to use basic division
            // bigger numbers just too slow!  Works fine.  You have been warned.
            dwStartTime = s_Timer.GetMicroseconds();
            for (int i=0; i<nIterations; i++)
            {
                memcpy(nProduct2.m_pnValue, nProduct1.m_pnValue, (nX.GetSize() + nX.GetSize())*sizeof(DIGIT));
                Divide(nX.GetSize() + nX.GetSize(), nX.GetSize(), nDivSize, nRemainderSize, nProduct2.GetValue(), nX.GetValue(), nDiv.GetValue(), cWork.GetSpace());
            }
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Time for %i divisions of %i BYTE number by %i BYTE number: %I64u microseconds (divide:multiply ratio: %f) -- basic\n", nIterations, 2*nX.GetSize()*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime, (float) dwStartTime/dwMultTime);
            ReportMeasuredComponentTimingData(eDivideMeasured);
            ResetTimingData();
            c_nDivideThresholdSmall = nDivideThresholdSmallOriginal;
        }
        dwStartTime = s_Timer.GetMicroseconds();
        for (int i=0; i<nIterations; i++)
        {
            memcpy(nProduct2.m_pnValue, nProduct1.m_pnValue, (nX.GetSize() + nX.GetSize())*sizeof(DIGIT));
            Divide(nX.GetSize() + nX.GetSize(), nX.GetSize(), nDivSize, nRemainderSize, nProduct2.GetValue(), nX.GetValue(), nDiv.GetValue(), cWork.GetSpace());
        }
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        printf("Time for %i divisions of %i BYTE number by %i BYTE number: %I64u microseconds (divide:multiply ratio: %f)\n", nIterations, 2*nX.GetSize()*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime, (float) dwStartTime/dwMultTime);
        ReportMeasuredComponentTimingData(eDivideMeasured);
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        for (int i=0; i<nIterations; i++)
        {
            Multiply(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct1.GetValue(), cWork.GetSpace());
        }
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        dwMultTime  = dwStartTime;
        printf("Time for %i %ix%i BYTE multiplications: %I64u microseconds\n", nIterations, nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        for(int i=0; i<nIterations; i++)
        {
            memcpy(nProduct2.m_pnValue, nProduct1.m_pnValue, (nX.GetSize() + nY.GetSize())*sizeof(DIGIT));
            Divide(nX.GetSize() + nY.GetSize(), nX.GetSize(), nDivSize, nRemainderSize, nProduct2.GetValue(), nX.GetValue(), nDiv.GetValue(), cWork.GetSpace());
        }
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        printf("Time for %i divisions of %i BYTE number by %i BYTE number: %I64u microseconds (divide:multiply ratio: %f)\n", nIterations, (nX.GetSize() + nY.GetSize())*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime, (float) dwStartTime/dwMultTime);
        ReportMeasuredComponentTimingData(eDivideMeasured);
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        for(int i=0; i<nIterations; i++)
        {
            memcpy(nProduct2.m_pnValue, nProduct1.m_pnValue, (nX.GetSize() + nY.GetSize())*sizeof(DIGIT));
            Divide((nX.GetSize() + nY.GetSize()), nY.GetSize(), nDivSize, nRemainderSize, nProduct2.GetValue(), nY.GetValue(), nDiv.GetValue(), cWork.GetSpace());
        }
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        printf("Time for %i divisions of %i BYTE number by %i BYTE number: %I64u microseconds (divide:multiply ratio: %f)\n", nIterations, (nX.GetSize() + nY.GetSize())*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime, (float) dwStartTime/dwMultTime);
        ReportMeasuredComponentTimingData(eDivideMeasured);
    }
    /*for(int nSize=100000; nSize<=c_nMaxSize; nSize *= 10)
    {
        nX.SetRandom(16*nSize);
        nY.SetRandom(8*nSize);
        nXCopy = nX;
        nDiv.Reserve(nX.GetSize()-nY.GetSize()+1);
        ResetTimingData();
        nWorkspaceMemoryNeeds = DivisionMemoryNeeds(nX.GetSize(), nY.GetSize());
        cWork.Reserve(nWorkspaceMemoryNeeds);
        dwStartTime = s_Timer.GetMicroseconds();
        Divide(nX.GetSize(), nY.GetSize(), nDivSize, nRemainderSize, nXCopy.GetValue(), nY.GetValue(), nDiv.GetValue(), cWork.GetSpace());
        printf("Dividing a %i-BYTE number by a %i-BYTE one took %I64u microseconds\n", nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), s_Timer.GetMicroseconds() - dwStartTime);
        ReportMeasuredComponentTimingData(eDivideMeasured);
    }*/
}

/*
* 16-bit DIGITs
Time to get the GCD of 16777216 pairs of 2-byte numbers:            5750 milliseconds
Time to get the GCD of 16777216 pairs of 2-byte numbers (extended): 9187 milliseconds
Time to get the GCD of 8388608 pairs of 4-byte numbers:            5719 milliseconds
Time to get the GCD of 8388608 pairs of 4-byte numbers (extended): 9687 milliseconds
Time to get the GCD of 4194304 pairs of 8-byte numbers:            5891 milliseconds
Time to get the GCD of 4194304 pairs of 8-byte numbers (extended): 10125 milliseconds
Time to get the GCD of 2097152 pairs of 16-byte numbers:            6391 milliseconds
Time to get the GCD of 2097152 pairs of 16-byte numbers (extended): 11312 milliseconds
Time to get the GCD of 1048576 pairs of 32-byte numbers:            7766 milliseconds
Time to get the GCD of 1048576 pairs of 32-byte numbers (extended): 13453 milliseconds
Time to get the GCD of 524288 pairs of 64-byte numbers:            9437 milliseconds
Time to get the GCD of 524288 pairs of 64-byte numbers (extended): 17938 milliseconds
Time to get the GCD of 262144 pairs of 128-byte numbers:            13625 milliseconds
Time to get the GCD of 262144 pairs of 128-byte numbers (extended): 26719 milliseconds
Time to get the GCD of 131072 pairs of 256-byte numbers:            21531 milliseconds
Time to get the GCD of 131072 pairs of 256-byte numbers (extended): 43984 milliseconds
Time to get the GCD of 65536 pairs of 512-byte numbers:            37203 milliseconds
Time to get the GCD of 65536 pairs of 512-byte numbers (extended): 82282 milliseconds
Time to get the GCD of 32768 pairs of 1024-byte numbers:            67265 milliseconds
Time to get the GCD of 32768 pairs of 1024-byte numbers (extended): 149563 milliseconds
Time to get the GCD of 16384 pairs of 2048-byte numbers:            128406 milliseconds
Time to get the GCD of 16384 pairs of 2048-byte numbers (extended): 303906 milliseconds
Time to get the GCD of 8192 pairs of 4096-byte numbers:            253985 milliseconds
Time to get the GCD of 8192 pairs of 4096-byte numbers (extended): 595312 milliseconds
Time to get the GCD of 4096 pairs of 8192-byte numbers:            507141 milliseconds
Time to get the GCD of 4096 pairs of 8192-byte numbers (extended): 1172015 milliseconds

32-bit DIGITs
Time to get the GCD of 16777216 pairs of 4-byte numbers:            11875 milliseconds
Time to get the GCD of 16777216 pairs of 4-byte numbers (extended): 19282 milliseconds
Time to get the GCD of 8388608 pairs of 8-byte numbers:            11515 milliseconds
Time to get the GCD of 8388608 pairs of 8-byte numbers (extended): 18469 milliseconds
Time to get the GCD of 4194304 pairs of 16-byte numbers:            11188 milliseconds
Time to get the GCD of 4194304 pairs of 16-byte numbers (extended): 18750 milliseconds
Time to get the GCD of 2097152 pairs of 32-byte numbers:            12390 milliseconds
Time to get the GCD of 2097152 pairs of 32-byte numbers (extended): 20438 milliseconds
Time to get the GCD of 1048576 pairs of 64-byte numbers:            13718 milliseconds
Time to get the GCD of 1048576 pairs of 64-byte numbers (extended): 24610 milliseconds
Time to get the GCD of 524288 pairs of 128-byte numbers:            18781 milliseconds
Time to get the GCD of 524288 pairs of 128-byte numbers (extended): 33984 milliseconds
Time to get the GCD of 262144 pairs of 256-byte numbers:            26641 milliseconds
Time to get the GCD of 262144 pairs of 256-byte numbers (extended): 47844 milliseconds
Time to get the GCD of 131072 pairs of 512-byte numbers:            42219 milliseconds
Time to get the GCD of 131072 pairs of 512-byte numbers (extended): 84109 milliseconds
Time to get the GCD of 65536 pairs of 1024-byte numbers:            73062 milliseconds
Time to get the GCD of 65536 pairs of 1024-byte numbers (extended): 149938 milliseconds
Time to get the GCD of 32768 pairs of 2048-byte numbers:            136141 milliseconds
Time to get the GCD of 32768 pairs of 2048-byte numbers (extended): 293937 milliseconds
Time to get the GCD of 16384 pairs of 4096-byte numbers:            257609 milliseconds
Time to get the GCD of 16384 pairs of 4096-byte numbers (extended): 552813 milliseconds
Time to get the GCD of 8192 pairs of 8192-byte numbers:            505531 milliseconds
Time to get the GCD of 8192 pairs of 8192-byte numbers (extended): 1086797 milliseconds
Time to get the GCD of 4096 pairs of 16384-byte numbers:            1029625 milliseconds
Time to get the GCD of 4096 pairs of 16384-byte numbers (extended): 2206641 milliseconds
*/
void CArithmeticPerformanceTester::GCDTimes()
{
    CArithmeticBox     cBox;
    CRandomGenerator   cRandom;
    CBigInteger        x, y, nGCD, nXCoef, nYCoef;
    bool               bXCoefNeg;
    size_t             nGCDSize, nXCoefSize, nYCoefSize;
    const unsigned int c_nMaxDigits          = 0x1000;
    const unsigned int c_nStartingIterations = 0x1000000;
    unsigned int       nIterations           = c_nStartingIterations;

    printf("If you're not doing this with a retail build, you're not getting good numbers.\n");
    x.Reserve(c_nMaxDigits);
    y.Reserve(c_nMaxDigits);
    for(int nDigits=1; nDigits<=c_nMaxDigits; nDigits=(nDigits<<1))
    {
        ResetTimingData();
        unsigned int nTime = ::GetTickCount();
        for (int i=0; i<nIterations; i++)
        {
            do
            {
                cRandom.RandomBits(nDigits, 0, true, x);
            }
            while(0==x.GetSize());
            do
            {
                cRandom.RandomBits(nDigits, 0, true, y);
            }
            while(0==y.GetSize());
            cBox.GCD(x, y, nGCD);
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to get the GCD of %i pairs of %i-byte numbers:            %i milliseconds\n", nIterations, nDigits*sizeof(DIGIT), nTime);
        ReportMeasuredComponentTimingData(eGCDMeasured);
        ResetTimingData();
        nTime = ::GetTickCount();
        for (int i=0; i<nIterations; i++)
        {
            do
            {
                cRandom.RandomBits(nDigits, 0, true, x);
            }
            while(0==x.GetSize());
            do
            {
                cRandom.RandomBits(nDigits, 0, true, y);
            }
            while(0==y.GetSize());
            cBox.GCDExtended(x, y, nGCD, nXCoef, nYCoef);
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to get the GCD of %i pairs of %i-byte numbers (extended): %i milliseconds\n", nIterations, nDigits*sizeof(DIGIT), nTime);
        ReportMeasuredComponentTimingData(eGCDMeasured);
        nIterations /= 2;
    }
}

/*
32-bit DIGITs
Time to do 16777216  standard  power-modulus operations of size 16 bits: 10515 milliseconds
Time to do 16777216 Montgomery power-modulus operations of size 16 bits: 15891 milliseconds
Time to do 4194304  standard  power-modulus operations of size 32 bits: 22515 milliseconds
Time to do 4194304 Montgomery power-modulus operations of size 32 bits: 18016 milliseconds
Time to do 1048576  standard  power-modulus operations of size 64 bits: 13266 milliseconds
Time to do 1048576 Montgomery power-modulus operations of size 64 bits: 8922 milliseconds
Time to do 262144  standard  power-modulus operations of size 128 bits: 12578 milliseconds
Time to do 262144 Montgomery power-modulus operations of size 128 bits: 5843 milliseconds
Time to do 65536  standard  power-modulus operations of size 256 bits: 12344 milliseconds
Time to do 65536 Montgomery power-modulus operations of size 256 bits: 5656 milliseconds
Time to do 16384  standard  power-modulus operations of size 512 bits: 14563 milliseconds
Time to do 16384 Montgomery power-modulus operations of size 512 bits: 7328 milliseconds
Time to do 4096  standard  power-modulus operations of size 1024 bits: 18516 milliseconds
Time to do 4096 Montgomery power-modulus operations of size 1024 bits: 11484 milliseconds
Time to do 1024  standard  power-modulus operations of size 2048 bits: 23141 milliseconds
Time to do 1024 Montgomery power-modulus operations of size 2048 bits: 19047 milliseconds
Time to do 256  standard  power-modulus operations of size 4096 bits: 36218 milliseconds
Time to do 256 Montgomery power-modulus operations of size 4096 bits: 28078 milliseconds
Time to do 64  standard  power-modulus operations of size 8192 bits: 49532 milliseconds
Time to do 64 Montgomery power-modulus operations of size 8192 bits: 40422 milliseconds
Time to do 16  standard  power-modulus operations of size 16384 bits: 69546 milliseconds
Time to do 16 Montgomery power-modulus operations of size 16384 bits: 53047 milliseconds
Time to do 4  standard  power-modulus operations of size 32768 bits: 94078 milliseconds
Time to do 4 Montgomery power-modulus operations of size 32768 bits: 72188 milliseconds
Time to do 1  standard  power-modulus operations of size 65536 bits: 133515 milliseconds
Time to do 1 Montgomery power-modulus operations of size 65536 bits: 99922 milliseconds

16-bit DIGITs
Time to do 16777216  standard  power-modulus operations of size 16 bits: 14672 milliseconds
Time to do 16777216 Montgomery power-modulus operations of size 16 bits: 22281 milliseconds
Time to do 4194304  standard  power-modulus operations of size 32 bits: 11563 milliseconds
Time to do 4194304 Montgomery power-modulus operations of size 32 bits: 10578 milliseconds
Time to do 1048576  standard  power-modulus operations of size 64 bits: 12859 milliseconds
Time to do 1048576 Montgomery power-modulus operations of size 64 bits: 7938 milliseconds
Time to do 262144  standard  power-modulus operations of size 128 bits: 19828 milliseconds
Time to do 262144 Montgomery power-modulus operations of size 128 bits: 9500 milliseconds
Time to do 65536  standard  power-modulus operations of size 256 bits: 35797 milliseconds
Time to do 65536 Montgomery power-modulus operations of size 256 bits: 13703 milliseconds
Time to do 16384  standard  power-modulus operations of size 512 bits: 35047 milliseconds
Time to do 16384 Montgomery power-modulus operations of size 512 bits: 22062 milliseconds
Time to do 4096  standard  power-modulus operations of size 1024 bits: 54094 milliseconds
Time to do 4096 Montgomery power-modulus operations of size 1024 bits: 38125 milliseconds
Time to do 1024  standard  power-modulus operations of size 2048 bits: 73359 milliseconds
Time to do 1024 Montgomery power-modulus operations of size 2048 bits: 60329 milliseconds
Time to do 256  standard  power-modulus operations of size 4096 bits: 107937 milliseconds
Time to do 256 Montgomery power-modulus operations of size 4096 bits: 82109 milliseconds
Time to do 64  standard  power-modulus operations of size 8192 bits: 147547 milliseconds
Time to do 64 Montgomery power-modulus operations of size 8192 bits: 126485 milliseconds
Time to do 16  standard  power-modulus operations of size 16384 bits: 211578 milliseconds
Time to do 16 Montgomery power-modulus operations of size 16384 bits: 157344 milliseconds
Time to do 4  standard  power-modulus operations of size 32768 bits: 285485 milliseconds
Time to do 4 Montgomery power-modulus operations of size 32768 bits: 230313 milliseconds
Time to do 1  standard  power-modulus operations of size 65536 bits: 381515 milliseconds
Time to do 1 Montgomery power-modulus operations of size 65536 bits: 290344 milliseconds
*/
void CArithmeticPerformanceTester::PowerModulusMontgomeryVsStandard()
{
    CRandomGenerator   cRandom;
    CBigInteger        nBase, nPower, nModulus, nResult, nNPrime, nRPrime, nPowerModulus;
    size_t             nNPrimeSize, nRPrimeSize, nMontSize, nPowerModSize, nLeadDigit, nLeadBit;
    unsigned int       nTime;
    const unsigned int c_nMinBits   = 16;
    const unsigned int c_nMaxBits   = 65536;
    unsigned int       nIterations  = 0x1000000;
    DIGIT              *pnWorkspace = (DIGIT *) malloc(sizeof(DIGIT)*1000000);
    printf("Doing this in retail?  If not, your numbers won't be representative\n");
    for(int nBits=c_nMinBits; nBits<=c_nMaxBits; nBits *= 2)
    {
        cRandom.RandomBits(nBits/_DIGIT_SIZE_IN_BITS, nBits%_DIGIT_SIZE_IN_BITS, true, nBase);
        cRandom.RandomBits(nBits/_DIGIT_SIZE_IN_BITS, nBits%_DIGIT_SIZE_IN_BITS, true, nPower);
        cRandom.RandomBits(nBits/_DIGIT_SIZE_IN_BITS, nBits%_DIGIT_SIZE_IN_BITS, true, nModulus);
        nResult.Reserve(2*nModulus.GetSize()+1);
        nModulus.GetValue()[0] |= 1; // force the modulus to be odd, so it is suitable for Montgomery
        // first, standard power modulus
        ResetTimingData();
        nTime = ::GetTickCount();
        for(int i=0;i<nIterations; i++)
        {
            PowerModulus(nBase.GetSize(), nPower.GetSize(), nModulus.GetSize(), nPowerModSize, nBase.GetValue(), nPower.GetValue(), nModulus.GetValue(), nResult.GetValue(), pnWorkspace);
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i  standard  power-modulus operations of size %i bits: %i milliseconds\n", nIterations, nBits, nTime);
        ReportMeasuredComponentTimingData(ePowerModulusMeasured);
        // Then, Montgomery power-modulus
        nNPrime.Reserve(nModulus.GetSize());
        nRPrime.Reserve(nModulus.GetSize());
        GetMontgomeryParameters(nModulus.GetSize(), nNPrimeSize, nRPrimeSize, nModulus.GetValue(), nNPrime.GetValue(), nRPrime.GetValue(), pnWorkspace);
        GetLeadBit(nModulus.GetSize(), nModulus.GetValue(), nLeadDigit, nLeadBit);
        nPowerModulus.Reserve(2*nModulus.GetSize() + 1);
        ResetTimingData();
        nTime = ::GetTickCount();
        for(int i=0;i<nIterations; i++)
        {
            MontgomeryPowerModulus(nBase.GetSize(),
                                   nPower.GetSize(),
                                   nModulus.GetSize(),
                                   nNPrimeSize,
                                   nRPrimeSize,
                                   nPowerModSize,
                                   nBase.GetValue(),
                                   nPower.GetValue(),
                                   nRPrime.GetValue(),
                                   nModulus.GetValue(),
                                   nNPrime.GetValue(),
                                   nPowerModulus.GetValue(),
                                   pnWorkspace);
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i Montgomery power-modulus operations of size %i bits: %i milliseconds\n", nIterations, nBits, nTime);
        ReportMeasuredComponentTimingData(ePowerModulusMeasured);
        nIterations /= 4;
    }
}

/*
16-bit DIGITs
Time to do 8388608 square roots of a 16 bit number (Newton):                  31 milliseconds (0.000004 average)
Time to do 8388608 square roots of a 16 bit number using general Newton:      1109 milliseconds (0.000132 average)
Time to do 8388608 square roots of a 16 bit number using recursive algorithm: 94 milliseconds (0.000011 average)
Time to do 8388608 divides of a 16 bit number by its square root:             281 milliseconds (0.000033 average)
Time to do 8388608 general roots of a 10, 16 bit numbers: Newton:             1453 milliseconds (0.000173 average)
Time to do 8388608 general roots of a 10, 16 bit numbers: Recursive:          1579 milliseconds (0.000188 average)
Time to do 4194304 square roots of a 32 bit number (Newton):                  15 milliseconds (0.000004 average)
Time to do 4194304 square roots of a 32 bit number using general Newton:      1094 milliseconds (0.000261 average)
Time to do 4194304 square roots of a 32 bit number using recursive algorithm: 31 milliseconds (0.000007 average)
Time to do 4194304 divides of a 32 bit number by its square root:             141 milliseconds (0.000034 average)
Time to do 4194304 general roots of a 21, 32 bit numbers: Newton:             1187 milliseconds (0.000283 average)
Time to do 4194304 general roots of a 21, 32 bit numbers: Recursive:          1266 milliseconds (0.000302 average)
Time to do 2097152 square roots of a 48 bit number (Newton):                  422 milliseconds (0.000201 average)
Time to do 2097152 square roots of a 48 bit number using general Newton:      672 milliseconds (0.000320 average)
Time to do 2097152 square roots of a 48 bit number using recursive algorithm: 453 milliseconds (0.000216 average)
Time to do 2097152 divides of a 48 bit number by its square root:             140 milliseconds (0.000067 average)
Time to do 2097152 general roots of a 32, 48 bit numbers: Newton:             625 milliseconds (0.000298 average)
Time to do 2097152 general roots of a 32, 48 bit numbers: Recursive:          360 milliseconds (0.000172 average)
Time to do 1048576 square roots of a 64 bit number (Newton):                  234 milliseconds (0.000223 average)
Time to do 1048576 square roots of a 64 bit number using general Newton:      500 milliseconds (0.000477 average)
Time to do 1048576 square roots of a 64 bit number using recursive algorithm: 266 milliseconds (0.000254 average)
Time to do 1048576 divides of a 64 bit number by its square root:             62 milliseconds (0.000059 average)
Time to do 1048576 general roots of a 42, 64 bit numbers: Newton:             375 milliseconds (0.000358 average)
Time to do 1048576 general roots of a 42, 64 bit numbers: Recursive:          250 milliseconds (0.000238 average)
Time to do 524288 square roots of a 128 bit number (Newton):                  344 milliseconds (0.000656 average)
Time to do 524288 square roots of a 128 bit number using general Newton:      703 milliseconds (0.001341 average)
Time to do 524288 square roots of a 128 bit number using recursive algorithm: 266 milliseconds (0.000507 average)
Time to do 524288 divides of a 128 bit number by its square root:             62 milliseconds (0.000118 average)
Time to do 524288 general roots of a 85, 128 bit numbers: Newton:             313 milliseconds (0.000597 average)
Time to do 524288 general roots of a 85, 128 bit numbers: Recursive:          109 milliseconds (0.000208 average)
Time to do 262144 square roots of a 256 bit number (Newton):                  688 milliseconds (0.002625 average)
Time to do 262144 square roots of a 256 bit number using general Newton:      1343 milliseconds (0.005123 average)
Time to do 262144 square roots of a 256 bit number using recursive algorithm: 172 milliseconds (0.000656 average)
Time to do 262144 divides of a 256 bit number by its square root:             110 milliseconds (0.000420 average)
Time to do 262144 general roots of a 170, 256 bit numbers: Newton:             437 milliseconds (0.001667 average)
Time to do 262144 general roots of a 170, 256 bit numbers: Recursive:          125 milliseconds (0.000477 average)
Time to do 131072 square roots of a 512 bit number (Newton):                  891 milliseconds (0.006798 average)
Time to do 131072 square roots of a 512 bit number using general Newton:      1484 milliseconds (0.011322 average)
Time to do 131072 square roots of a 512 bit number using recursive algorithm: 172 milliseconds (0.001312 average)
Time to do 131072 divides of a 512 bit number by its square root:             141 milliseconds (0.001076 average)
Time to do 131072 general roots of a 341, 512 bit numbers: Newton:             609 milliseconds (0.004646 average)
Time to do 131072 general roots of a 341, 512 bit numbers: Recursive:          156 milliseconds (0.001190 average)
Time to do 65536 square roots of a 1024 bit number (Newton):                  1282 milliseconds (0.019562 average)
Time to do 65536 square roots of a 1024 bit number using general Newton:      2484 milliseconds (0.037903 average)
Time to do 65536 square roots of a 1024 bit number using recursive algorithm: 234 milliseconds (0.003571 average)
Time to do 65536 divides of a 1024 bit number by its square root:             141 milliseconds (0.002151 average)
Time to do 65536 general roots of a 682, 1024 bit numbers: Newton:             719 milliseconds (0.010971 average)
Time to do 65536 general roots of a 682, 1024 bit numbers: Recursive:          140 milliseconds (0.002136 average)
Time to do 32768 square roots of a 2048 bit number (Newton):                  1985 milliseconds (0.060577 average)
Time to do 32768 square roots of a 2048 bit number using general Newton:      3687 milliseconds (0.112518 average)
Time to do 32768 square roots of a 2048 bit number using recursive algorithm: 266 milliseconds (0.008118 average)
Time to do 32768 divides of a 2048 bit number by its square root:             203 milliseconds (0.006195 average)
Time to do 32768 general roots of a 1365, 2048 bit numbers: Newton:             1047 milliseconds (0.031952 average)
Time to do 32768 general roots of a 1365, 2048 bit numbers: Recursive:          234 milliseconds (0.007141 average)
Time to do 16384 square roots of a 4096 bit number (Newton):                  3703 milliseconds (0.226013 average)
Time to do 16384 square roots of a 4096 bit number using general Newton:      5969 milliseconds (0.364319 average)
Time to do 16384 square roots of a 4096 bit number using recursive algorithm: 328 milliseconds (0.020020 average)
Time to do 16384 divides of a 4096 bit number by its square root:             297 milliseconds (0.018127 average)
Time to do 16384 general roots of a 2730, 4096 bit numbers: Newton:             1359 milliseconds (0.082947 average)
Time to do 16384 general roots of a 2730, 4096 bit numbers: Recursive:          329 milliseconds (0.020081 average)
Time to do 8192 square roots of a 8192 bit number (Newton):                  4375 milliseconds (0.534058 average)
Time to do 8192 square roots of a 8192 bit number using general Newton:      7531 milliseconds (0.919312 average)
Time to do 8192 square roots of a 8192 bit number using recursive algorithm: 453 milliseconds (0.055298 average)
Time to do 8192 divides of a 8192 bit number by its square root:             422 milliseconds (0.051514 average)
Time to do 8192 general roots of a 5461, 8192 bit numbers: Newton:             1812 milliseconds (0.221191 average)
Time to do 8192 general roots of a 5461, 8192 bit numbers: Recursive:          407 milliseconds (0.049683 average)
Time to do 4096 square roots of a 16384 bit number (Newton):                  7218 milliseconds (1.762207 average)
Time to do 4096 square roots of a 16384 bit number using general Newton:      12688 milliseconds (3.097656 average)
Time to do 4096 square roots of a 16384 bit number using recursive algorithm: 656 milliseconds (0.160156 average)
Time to do 4096 divides of a 16384 bit number by its square root:             625 milliseconds (0.152588 average)
Time to do 4096 general roots of a 10922, 16384 bit numbers: Newton:             2297 milliseconds (0.560791 average)
Time to do 4096 general roots of a 10922, 16384 bit numbers: Recursive:          547 milliseconds (0.133545 average)
Time to do 2048 square roots of a 32768 bit number (Newton):                  10969 milliseconds (5.355957 average)
Time to do 2048 square roots of a 32768 bit number using general Newton:      17515 milliseconds (8.552246 average)
Time to do 2048 square roots of a 32768 bit number using recursive algorithm: 985 milliseconds (0.480957 average)
Time to do 2048 divides of a 32768 bit number by its square root:             890 milliseconds (0.434570 average)
Time to do 2048 general roots of a 21845, 32768 bit numbers: Newton:             3313 milliseconds (1.617676 average)
Time to do 2048 general roots of a 21845, 32768 bit numbers: Recursive:          672 milliseconds (0.328125 average)
Time to do 1024 square roots of a 65536 bit number (Newton):                  16687 milliseconds (16.295898 average)
Time to do 1024 square roots of a 65536 bit number using general Newton:      26438 milliseconds (25.818359 average)
Time to do 1024 square roots of a 65536 bit number using recursive algorithm: 1296 milliseconds (1.265625 average)
Time to do 1024 divides of a 65536 bit number by its square root:             1219 milliseconds (1.190430 average)
Time to do 1024 general roots of a 43690, 65536 bit numbers: Newton:             4391 milliseconds (4.288086 average)
Time to do 1024 general roots of a 43690, 65536 bit numbers: Recursive:          984 milliseconds (0.960938 average)
Time to do 512 square roots of a 131072 bit number (Newton):                  25172 milliseconds (49.164062 average)
Time to do 512 square roots of a 131072 bit number using general Newton:      37984 milliseconds (74.187500 average)
Time to do 512 square roots of a 131072 bit number using recursive algorithm: 1735 milliseconds (3.388672 average)
Time to do 512 divides of a 131072 bit number by its square root:             1609 milliseconds (3.142578 average)
Time to do 512 general roots of a 87381, 131072 bit numbers: Newton:             6156 milliseconds (12.023438 average)
Time to do 512 general roots of a 87381, 131072 bit numbers: Recursive:          1454 milliseconds (2.839844 average)
Time to do 256 square roots of a 262144 bit number (Newton):                  38828 milliseconds (151.671875 average)
Time to do 256 square roots of a 262144 bit number using general Newton:      56359 milliseconds (220.152344 average)
Time to do 256 square roots of a 262144 bit number using recursive algorithm: 2313 milliseconds (9.035156 average)
Time to do 256 divides of a 262144 bit number by its square root:             2359 milliseconds (9.214844 average)
Time to do 256 general roots of a 174762, 262144 bit numbers: Newton:             8125 milliseconds (31.738281 average)
Time to do 256 general roots of a 174762, 262144 bit numbers: Recursive:          1844 milliseconds (7.203125 average)
Time to do 128 square roots of a 524288 bit number (Newton):                  55390 milliseconds (432.734375 average)
Time to do 128 square roots of a 524288 bit number using general Newton:      85032 milliseconds (664.312500 average)
Time to do 128 square roots of a 524288 bit number using recursive algorithm: 2953 milliseconds (23.070312 average)
Time to do 128 divides of a 524288 bit number by its square root:             2968 milliseconds (23.187500 average)
Time to do 128 general roots of a 349525, 524288 bit numbers: Newton:             11204 milliseconds (87.531250 average)
Time to do 128 general roots of a 349525, 524288 bit numbers: Recursive:          2375 milliseconds (18.554688 average)
And the time to do a single 33554432 bit square root using the full algorithm: 6766 milliseconds
Simple Newton:                                                                 166844 milliseconds
General recursive (half-size x1):                                              7828 milliseconds
General recursive (two thirds-size x1):                                        3984 milliseconds
General recursive (one third-size x1):                                         8328 milliseconds
And, for comparison, squaring that square root again:                          1172 milliseconds
And to divide that large number by its square root:                            6922 milliseconds

32-bit DIGITs
Time to do 8388608 square roots of a 16 bit number (Newton):                  47 milliseconds (0.000006 average)
Time to do 8388608 square roots of a 16 bit number using general Newton:      6359 milliseconds (0.000758 average)
Time to do 8388608 square roots of a 16 bit number using recursive algorithm: 63 milliseconds (0.000008 average)
Time to do 8388608 divides of a 16 bit number by its square root:             234 milliseconds (0.000028 average)
Time to do 8388608 general roots of a 10, 16 bit numbers: Newton:             6422 milliseconds (0.000766 average)
Time to do 8388608 general roots of a 10, 16 bit numbers: Recursive:          7062 milliseconds (0.000842 average)
Time to do 4194304 square roots of a 32 bit number (Newton):                  16 milliseconds (0.000004 average)
Time to do 4194304 square roots of a 32 bit number using general Newton:      688 milliseconds (0.000164 average)
Time to do 4194304 square roots of a 32 bit number using recursive algorithm: 31 milliseconds (0.000007 average)
Time to do 4194304 divides of a 32 bit number by its square root:             125 milliseconds (0.000030 average)
Time to do 4194304 general roots of a 21, 32 bit numbers: Newton:             562 milliseconds (0.000134 average)
Time to do 4194304 general roots of a 21, 32 bit numbers: Recursive:          641 milliseconds (0.000153 average)
Time to do 2097152 square roots of a 64 bit number (Newton):                  16 milliseconds (0.000008 average)
Time to do 2097152 square roots of a 64 bit number using general Newton:      578 milliseconds (0.000276 average)
Time to do 2097152 square roots of a 64 bit number using recursive algorithm: 15 milliseconds (0.000007 average)
Time to do 2097152 divides of a 64 bit number by its square root:             63 milliseconds (0.000030 average)
Time to do 2097152 general roots of a 42, 64 bit numbers: Newton:             390 milliseconds (0.000186 average)
Time to do 2097152 general roots of a 42, 64 bit numbers: Recursive:          422 milliseconds (0.000201 average)
Time to do 1048576 square roots of a 96 bit number (Newton):                  1235 milliseconds (0.001178 average)
Time to do 1048576 square roots of a 96 bit number using general Newton:      1265 milliseconds (0.001206 average)
Time to do 1048576 square roots of a 96 bit number using recursive algorithm: 328 milliseconds (0.000313 average)
Time to do 1048576 divides of a 96 bit number by its square root:             79 milliseconds (0.000075 average)
Time to do 1048576 general roots of a 64, 96 bit numbers: Newton:             218 milliseconds (0.000208 average)
Time to do 1048576 general roots of a 64, 96 bit numbers: Recursive:          110 milliseconds (0.000105 average)
Time to do 524288 square roots of a 128 bit number (Newton):                  172 milliseconds (0.000328 average)
Time to do 524288 square roots of a 128 bit number using general Newton:      390 milliseconds (0.000744 average)
Time to do 524288 square roots of a 128 bit number using recursive algorithm: 63 milliseconds (0.000120 average)
Time to do 524288 divides of a 128 bit number by its square root:             31 milliseconds (0.000059 average)
Time to do 524288 general roots of a 85, 128 bit numbers: Newton:             172 milliseconds (0.000328 average)
Time to do 524288 general roots of a 85, 128 bit numbers: Recursive:          78 milliseconds (0.000149 average)
Time to do 262144 square roots of a 256 bit number (Newton):                  234 milliseconds (0.000893 average)
Time to do 262144 square roots of a 256 bit number using general Newton:      250 milliseconds (0.000954 average)
Time to do 262144 square roots of a 256 bit number using recursive algorithm: 110 milliseconds (0.000420 average)
Time to do 262144 divides of a 256 bit number by its square root:             31 milliseconds (0.000118 average)
Time to do 262144 general roots of a 170, 256 bit numbers: Newton:             156 milliseconds (0.000595 average)
Time to do 262144 general roots of a 170, 256 bit numbers: Recursive:          78 milliseconds (0.000298 average)
Time to do 131072 square roots of a 512 bit number (Newton):                  297 milliseconds (0.002266 average)
Time to do 131072 square roots of a 512 bit number using general Newton:      375 milliseconds (0.002861 average)
Time to do 131072 square roots of a 512 bit number using recursive algorithm: 78 milliseconds (0.000595 average)
Time to do 131072 divides of a 512 bit number by its square root:             47 milliseconds (0.000359 average)
Time to do 131072 general roots of a 341, 512 bit numbers: Newton:             203 milliseconds (0.001549 average)
Time to do 131072 general roots of a 341, 512 bit numbers: Recursive:          63 milliseconds (0.000481 average)
Time to do 65536 square roots of a 1024 bit number (Newton):                  297 milliseconds (0.004532 average)
Time to do 65536 square roots of a 1024 bit number using general Newton:      531 milliseconds (0.008102 average)
Time to do 65536 square roots of a 1024 bit number using recursive algorithm: 94 milliseconds (0.001434 average)
Time to do 65536 divides of a 1024 bit number by its square root:             47 milliseconds (0.000717 average)
Time to do 65536 general roots of a 682, 1024 bit numbers: Newton:             296 milliseconds (0.004517 average)
Time to do 65536 general roots of a 682, 1024 bit numbers: Recursive:          79 milliseconds (0.001205 average)
Time to do 32768 square roots of a 2048 bit number (Newton):                  640 milliseconds (0.019531 average)
Time to do 32768 square roots of a 2048 bit number using general Newton:      1125 milliseconds (0.034332 average)
Time to do 32768 square roots of a 2048 bit number using recursive algorithm: 94 milliseconds (0.002869 average)
Time to do 32768 divides of a 2048 bit number by its square root:             62 milliseconds (0.001892 average)
Time to do 32768 general roots of a 1365, 2048 bit numbers: Newton:             297 milliseconds (0.009064 average)
Time to do 32768 general roots of a 1365, 2048 bit numbers: Recursive:          78 milliseconds (0.002380 average)
Time to do 16384 square roots of a 4096 bit number (Newton):                  1000 milliseconds (0.061035 average)
Time to do 16384 square roots of a 4096 bit number using general Newton:      1641 milliseconds (0.100159 average)
Time to do 16384 square roots of a 4096 bit number using recursive algorithm: 125 milliseconds (0.007629 average)
Time to do 16384 divides of a 4096 bit number by its square root:             109 milliseconds (0.006653 average)
Time to do 16384 general roots of a 2730, 4096 bit numbers: Newton:             453 milliseconds (0.027649 average)
Time to do 16384 general roots of a 2730, 4096 bit numbers: Recursive:          94 milliseconds (0.005737 average)
Time to do 8192 square roots of a 8192 bit number (Newton):                  1328 milliseconds (0.162109 average)
Time to do 8192 square roots of a 8192 bit number using general Newton:      2563 milliseconds (0.312866 average)
Time to do 8192 square roots of a 8192 bit number using recursive algorithm: 140 milliseconds (0.017090 average)
Time to do 8192 divides of a 8192 bit number by its square root:             125 milliseconds (0.015259 average)
Time to do 8192 general roots of a 5461, 8192 bit numbers: Newton:             563 milliseconds (0.068726 average)
Time to do 8192 general roots of a 5461, 8192 bit numbers: Recursive:          140 milliseconds (0.017090 average)
Time to do 4096 square roots of a 16384 bit number (Newton):                  2297 milliseconds (0.560791 average)
Time to do 4096 square roots of a 16384 bit number using general Newton:      3610 milliseconds (0.881348 average)
Time to do 4096 square roots of a 16384 bit number using recursive algorithm: 187 milliseconds (0.045654 average)
Time to do 4096 divides of a 16384 bit number by its square root:             172 milliseconds (0.041992 average)
Time to do 4096 general roots of a 10922, 16384 bit numbers: Newton:             828 milliseconds (0.202148 average)
Time to do 4096 general roots of a 10922, 16384 bit numbers: Recursive:          172 milliseconds (0.041992 average)
Time to do 2048 square roots of a 32768 bit number (Newton):                  3234 milliseconds (1.579102 average)
Time to do 2048 square roots of a 32768 bit number using general Newton:      5922 milliseconds (2.891602 average)
Time to do 2048 square roots of a 32768 bit number using recursive algorithm: 281 milliseconds (0.137207 average)
Time to do 2048 divides of a 32768 bit number by its square root:             313 milliseconds (0.152832 average)
Time to do 2048 general roots of a 21845, 32768 bit numbers: Newton:             1000 milliseconds (0.488281 average)
Time to do 2048 general roots of a 21845, 32768 bit numbers: Recursive:          234 milliseconds (0.114258 average)
Time to do 1024 square roots of a 65536 bit number (Newton):                  4688 milliseconds (4.578125 average)
Time to do 1024 square roots of a 65536 bit number using general Newton:      8984 milliseconds (8.773438 average)
Time to do 1024 square roots of a 65536 bit number using recursive algorithm: 375 milliseconds (0.366211 average)
Time to do 1024 divides of a 65536 bit number by its square root:             344 milliseconds (0.335938 average)
Time to do 1024 general roots of a 43690, 65536 bit numbers: Newton:             1422 milliseconds (1.388672 average)
Time to do 1024 general roots of a 43690, 65536 bit numbers: Recursive:          281 milliseconds (0.274414 average)
Time to do 512 square roots of a 131072 bit number (Newton):                  7516 milliseconds (14.679688 average)
Time to do 512 square roots of a 131072 bit number using general Newton:      11062 milliseconds (21.605469 average)
Time to do 512 square roots of a 131072 bit number using recursive algorithm: 516 milliseconds (1.007812 average)
Time to do 512 divides of a 131072 bit number by its square root:             547 milliseconds (1.068359 average)
Time to do 512 general roots of a 87381, 131072 bit numbers: Newton:             1890 milliseconds (3.691406 average)
Time to do 512 general roots of a 87381, 131072 bit numbers: Recursive:          407 milliseconds (0.794922 average)
Time to do 256 square roots of a 262144 bit number (Newton):                  9515 milliseconds (37.167969 average)
Time to do 256 square roots of a 262144 bit number using general Newton:      14250 milliseconds (55.664062 average)
Time to do 256 square roots of a 262144 bit number using recursive algorithm: 735 milliseconds (2.871094 average)
Time to do 256 divides of a 262144 bit number by its square root:             718 milliseconds (2.804688 average)
Time to do 256 general roots of a 174762, 262144 bit numbers: Newton:             2594 milliseconds (10.132812 average)
Time to do 256 general roots of a 174762, 262144 bit numbers: Recursive:          547 milliseconds (2.136719 average)
Time to do 128 square roots of a 524288 bit number (Newton):                  14469 milliseconds (113.039062 average)
Time to do 128 square roots of a 524288 bit number using general Newton:      20547 milliseconds (160.523438 average)
Time to do 128 square roots of a 524288 bit number using recursive algorithm: 921 milliseconds (7.195312 average)
Time to do 128 divides of a 524288 bit number by its square root:             891 milliseconds (6.960938 average)
Time to do 128 general roots of a 349525, 524288 bit numbers: Newton:             3188 milliseconds (24.906250 average)
Time to do 128 general roots of a 349525, 524288 bit numbers: Recursive:          765 milliseconds (5.976562 average)
And the time to do a single 33554432 bit square root using the full algorithm: 2375 milliseconds
Simple Newton:                                                                 55532 milliseconds
General recursive (half-size x1):                                              2735 milliseconds
General recursive (two thirds-size x1):                                        1391 milliseconds
General recursive (one third-size x1):                                         2688 milliseconds
And, for comparison, squaring that square root again:                          375 milliseconds
And to divide that large number by its square root:                            2281 milliseconds

Testing square root times.  Doing this in retail?  If not, your numbers won't be representative
compute the square root of 2 to 1,000,000 base 10 digits
Time to compute the power: 78 ms
Time to compute the root: 250 ms (207621 DIGIT base number)
Time to print the square root in base 10 to a file: 468 ms
Time to validate the root: 94 ms
And finally: the time to compute the square root of 2 to 20,000,000 base-10 digits
Time to compute the power: 1938 ms
Time to compute the root: 11813 ms (4152411 DIGIT base number)
Time to print the square root in base 10 to a file: 24187 ms
Time to validate the root: 2125 ms
*/
void CArithmeticPerformanceTester::SquareRootTimes()
{
#if _CollectDetailedTimingData
    DWORD64            dwTimestamp = s_Timer.GetMicroseconds();
#endif
    CArithmeticBox     cBox;
    size_t             nRootSize;
    CBigIntegerForTest nX1, nX1Copy, nX2, nX2Copy, nSqrtX, nExtra;
    DIGIT              *pWorkspace   = (DIGIT *) malloc(sizeof(DIGIT)*100000000);
    const unsigned int c_nMinBitSize = 16, c_nMaxBitSize = 524288;
    unsigned       int nTests        = c_nMaxBitSize*16, nTime;
    printf("Testing square root times.  Doing this in retail?  If not, your numbers won't be representative\n");
    /*for(int nSize=c_nMinBitSize; nSize<=c_nMaxBitSize; nSize *= 2)
    {
        nX2.SetSize(0);
        // want to make sure we hit 3-DIGIT numbers, too
        if(_DIGIT_SIZE_IN_BITS*4 == nSize) nSize -= _DIGIT_SIZE_IN_BITS;
        else if(_DIGIT_SIZE_IN_BITS*6 == nSize) nSize -= (2*_DIGIT_SIZE_IN_BITS);
        nX1.SetRandom(nSize);
        nSqrtX.Reserve(nX1.GetSize()+1); // extra digit for overflow --  only needed in single-digit case
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
#if _CollectDetailedTimingData
            SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
            SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i square roots of a %i bit number (Newton):                  %i milliseconds (%f average)\n",nTests,nSize,nTime,((float) nTime)/nTests);
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
#if _CollectDetailedTimingData
            GeneralSquareRootNewton(nX2.GetSize(), nX1.GetSize(), nRootSize, nX2.GetValue(), nX1.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
            GeneralSquareRootNewton(nX2.GetSize(), nX1.GetSize(), nRootSize, nX2.GetValue(), nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i square roots of a %i bit number using general Newton:      %i milliseconds (%f average)\n",nTests,nSize,nTime,((float) nTime)/nTests);
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
#if _CollectDetailedTimingData
            SquareRootRecursive(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
            SquareRootRecursive(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
        }
        nTime = ::GetTickCount() - nTime;
        nSqrtX.SetSize(nRootSize);
        printf("Time to do %i square roots of a %i bit number using recursive algorithm: %i milliseconds (%f average)\n",nTests,nSize,nTime,((float) nTime)/nTests);
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
            cBox.Divide(nX1, nSqrtX, nX2, nExtra);
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i divides of a %i bit number by its square root:             %i milliseconds (%f average)\n",nTests,nSize,nTime,((float) nTime)/nTests);
        // Compare general recursive square root vs its Newton equivalent, on sizes roughly in line with what would get from the square root function:
        // x1 ~ 2/3 the size of x2 (or in this case x2 ~ 2/3 the size of x1, since numbers reversed in this test)
        nX2.SetRandom(2*nSize/3);
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
#if _CollectDetailedTimingData
            GeneralSquareRootNewton(nX2.GetSize(), nX1.GetSize(), nRootSize, nX2.GetValue(), nX1.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
            GeneralSquareRootNewton(nX2.GetSize(), nX1.GetSize(), nRootSize, nX2.GetValue(), nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i general roots of a %i, %i bit numbers: Newton:             %i milliseconds (%f average)\n",nTests,2*nSize/3,nSize,nTime,((float) nTime)/nTests);
        nX2Copy.Reserve(nX1.GetSize()+1); // needs a bit of extra space!
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
            // GeneralSquareRootRecursive destructive -- copy data
            nX1Copy = nX1;
            nX2Copy = nX2;
#if _CollectDetailedTimingData
            GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
            GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i general roots of a %i, %i bit numbers: Recursive:          %i milliseconds (%f average)\n",nTests,2*nSize/3,nSize,nTime,((float) nTime)/nTests);
        nTests /= 2;
    }
    nX1.SetRandom(c_nMaxBitSize*64);
    nSqrtX.Reserve(nX1.GetSize());
    nX2Copy.Reserve(nX1.GetSize()+1); // needs more working space
    ResetTimingData();
    nTime   = ::GetTickCount();
    cBox.SQRT(nX1, nSqrtX);
    printf("And the time to do a single %i bit square root using the full algorithm: %i milliseconds\n",c_nMaxBitSize*64,::GetTickCount()-nTime);
    ReportMeasuredComponentTimingData(eSQRTMeasured);
    nTime   = ::GetTickCount();
#if _CollectDetailedTimingData
    SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
    SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
    printf("Simple Newton:                                                                 %i milliseconds\n",::GetTickCount()-nTime);
    nX2.SetRandom(nX1.GetSize()*_DIGIT_SIZE_IN_BITS/2);
    nX1Copy = nX1;
    nX2Copy = nX2;
    nTime   = ::GetTickCount();
#if _CollectDetailedTimingData
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
    printf("General recursive (half-size x1):                                              %i milliseconds\n", ::GetTickCount() - nTime);
    nX2.SetRandom(nX1.GetSize()*_DIGIT_SIZE_IN_BITS*2/3);
    nX1Copy = nX1;
    nX2Copy = nX2;
    nTime   = ::GetTickCount();
#if _CollectDetailedTimingData
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
    printf("General recursive (two thirds-size x1):                                        %i milliseconds\n", ::GetTickCount() - nTime);
    nX2.SetRandom(nX1.GetSize()*_DIGIT_SIZE_IN_BITS/3);
    nX1Copy = nX1;
    nX2Copy = nX2;
    nTime   = ::GetTickCount();
#if _CollectDetailedTimingData
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), dwTimestamp, pWorkspace);
#else
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), pWorkspace);
#endif
    printf("General recursive (one third-size x1):                                         %i milliseconds\n", ::GetTickCount() - nTime);
    ResetTimingData();
    nTime = ::GetTickCount();
    if (eOperationSucceeded != cBox.Square(nSqrtX, nX2))
    {
        printf("Square failed\n");
    }
    printf("And, for comparison, squaring that square root again:                          %i milliseconds\n",::GetTickCount()-nTime);
    ReportMeasuredComponentTimingData(eMultiplicationMeasured);
    ResetTimingData();
    nTime   = ::GetTickCount();
    if (eOperationSucceeded != cBox.Divide(nX1, nSqrtX, nX2, nExtra))
    {
        printf("Divide failed\n");
    }
    printf("And to divide that large number by its square root:                            %i milliseconds\n",::GetTickCount()-nTime);
    ReportMeasuredComponentTimingData(eDivideMeasured);*/
printf("compute the square root of 2 to 1,000,000 base 10 digits\n");
    nX1.SetFromHexString("64"); // 64 base 16 is 100 base 10
    nTime = ::GetTickCount();
    cBox.Power(nX1, 1000000, nX2); // 100 to 1,000,000 -> multiply root by 10 to the 1,000,000
    nTime = ::GetTickCount() - nTime;
    printf("Time to compute the power: %i ms\n", nTime);
    nX2.ShiftLeft(1); // multiply by 2
    nTime = ::GetTickCount();
    cBox.SQRT(nX2, nSqrtX);
    nTime = ::GetTickCount() - nTime;
    printf("Time to compute the root: %i ms (%u DIGIT base number)\n", nTime, nX2.GetSize());
    FILE *f;
    nX2Copy = nSqrtX; // PrintNumberToBase10 is destructive
    nTime = ::GetTickCount();
    fopen_s(&f, "sqrt2_a", "w");
    PrintNumberToBase10(nX2Copy, cBox.m_Workspace.GetSpace(), f);
    fclose(f);
    nTime = ::GetTickCount() - nTime;
    printf("Time to print the square root in base 10 to a file: %u ms\n", nTime);
    // validate
    nTime = ::GetTickCount();
    cBox.Square(nSqrtX, nX1);
    if (nX2 < nX1) printf("square root of 2 too big!\n");
    nSqrtX += 1;
    cBox.Square(nSqrtX, nX1);
    if (nX1 <= nX2)
    {
        printf("square root of 2 too small!\n");
        cBox.Subtract(nX2, nX1, nExtra);
        printf("Computed + 1: ",nSqrtX.PrintDecimalToFile());
    }
    nTime = ::GetTickCount() - nTime;
    printf("Time to validate the root: %i ms\n", nTime);
    printf("And finally: the time to compute the square root of 2 to 20,000,000 base-10 digits\n");
    nX1.SetFromHexString("64"); // 64 base 16 is 100 base 10
    nTime = ::GetTickCount();
    cBox.Power(nX1, 20000000, nX2); // 100 to 20,000 -> multiply root by 10 to the 20000000
    nTime = ::GetTickCount() - nTime;
    printf("Time to compute the power: %i ms\n", nTime);
    nX2.ShiftLeft(1); // multiply by 2
    nTime = ::GetTickCount();
    cBox.SQRT(nX2, nSqrtX);
    nTime = ::GetTickCount() - nTime;
    printf("Time to compute the root: %i ms (%u DIGIT base number)\n", nTime, nX2.GetSize());
    nX2Copy = nSqrtX; // PrintNumberToBase10 is destructive
    nTime = ::GetTickCount();
    fopen_s(&f, "sqrt2_b", "w");
    PrintNumberToBase10(nX2Copy, cBox.m_Workspace.GetSpace(), f);
    fclose(f);
    nTime = ::GetTickCount() - nTime;
    printf("Time to print the square root in base 10 to a file: %u ms\n", nTime);
    // validate
    nTime = ::GetTickCount();
    cBox.Square(nSqrtX, nX1);
    if (nX2 < nX1) printf("square root of 2 too big!\n");
    nSqrtX += 1;
    cBox.Square(nSqrtX, nX1);
    if (nX1 <= nX2)
    {
        printf("square root of 2 too small!\n");
        cBox.Subtract(nX2, nX1, nExtra);
        printf("Computed + 1: ",nSqrtX.PrintDecimalToFile());
    }
    nTime = ::GetTickCount() - nTime;
    printf("Time to validate the root: %i ms\n", nTime);
    free(pWorkspace);
}

/*
32-bit DIGITs
Testing general root times.  Doing this in retail?  If not, your numbers won't be representative
Square root of a 1000000 BYTE number: SQRT 344 ms; general nth root 531 ms
Square root of a 1000000 BYTE number: SQRT 344 ms; general nth root 531 ms
Square root of a 1000000 BYTE number: SQRT 328 ms; general nth root 406 ms
Square root of a 1000000 BYTE number: SQRT 313 ms; general nth root 469 ms
Square root of a 1000000 BYTE number: SQRT 313 ms; general nth root 578 ms
Square root of a 1000000 BYTE number: SQRT 297 ms; general nth root 438 ms
Square root of a 1000000 BYTE number: SQRT 297 ms; general nth root 469 ms
Square root of a 1000000 BYTE number: SQRT 344 ms; general nth root 562 ms
Square root of a 1000000 BYTE number: SQRT 312 ms; general nth root 500 ms
Square root of a 1000000 BYTE number: SQRT 312 ms; general nth root 609 ms
2 root of a 1000000 BYTE number: general newton 19563 ms; general nth root 515 ms
3 root of a 1000000 BYTE number: general newton 7672 ms; general nth root 594 ms
4 root of a 1000000 BYTE number: general newton 27156 ms; general nth root 906 ms
5 root of a 1000000 BYTE number: general newton 28329 ms; general nth root 718 ms
6 root of a 1000000 BYTE number: general newton 6953 ms; general nth root 1047 ms
7 root of a 1000000 BYTE number: general newton 5671 ms; general nth root 922 ms
8 root of a 1000000 BYTE number: general newton 63859 ms; general nth root 1266 ms
9 root of a 1000000 BYTE number: general newton 4563 ms; general nth root 797 ms
10 root of a 1000000 BYTE number: general newton 70281 ms; general nth root 1172 ms
11 root of a 1000000 BYTE number: general newton 5453 ms; general nth root 968 ms
12 root of a 1000000 BYTE number: general newton 8109 ms; general nth root 1391 ms
13 root of a 1000000 BYTE number: general newton 5891 ms; general nth root 875 ms
14 root of a 1000000 BYTE number: general newton 7984 ms; general nth root 1281 ms
15 root of a 1000000 BYTE number: general newton 8469 ms; general nth root 1422 ms
16 root of a 1000000 BYTE number: general newton 115343 ms; general nth root 1375 ms
17 root of a 1000000 BYTE number: general newton 5062 ms; general nth root 719 ms
18 root of a 1000000 BYTE number: general newton 7375 ms; general nth root 1031 ms
19 root of a 1000000 BYTE number: general newton 5094 ms; general nth root 844 ms
20 root of a 1000000 BYTE number: general newton 138671 ms; general nth root 2079 ms
21 root of a 1000000 BYTE number: general newton 6063 ms; general nth root 843 ms
22 root of a 1000000 BYTE number: general newton 8937 ms; general nth root 1219 ms
23 root of a 1000000 BYTE number: general newton 8453 ms; general nth root 1000 ms
24 root of a 1000000 BYTE number: general newton 10453 ms; general nth root 1406 ms
25 root of a 1000000 BYTE number: general newton 111265 ms; general nth root 1188 ms
26 root of a 1000000 BYTE number: general newton 9234 ms; general nth root 1203 ms
27 root of a 1000000 BYTE number: general newton 8391 ms; general nth root 1000 ms
28 root of a 1000000 BYTE number: general newton 12969 ms; general nth root 1843 ms
29 root of a 1000000 BYTE number: general newton 9312 ms; general nth root 953 ms
30 root of a 1000000 BYTE number: general newton 8890 ms; general nth root 1453 ms
31 root of a 1000000 BYTE number: general newton 8390 ms; general nth root 1266 ms
32 root of a 1000000 BYTE number: general newton 9188 ms; general nth root 1687 ms
33 root of a 1000000 BYTE number: general newton 5922 ms; general nth root 766 ms
34 root of a 1000000 BYTE number: general newton 9844 ms; general nth root 1141 ms
35 root of a 1000000 BYTE number: general newton 7625 ms; general nth root 860 ms
36 root of a 1000000 BYTE number: general newton 11266 ms; general nth root 1281 ms
37 root of a 1000000 BYTE number: general newton 7125 ms; general nth root 796 ms
38 root of a 1000000 BYTE number: general newton 9531 ms; general nth root 1141 ms
39 root of a 1000000 BYTE number: general newton 8938 ms; general nth root 984 ms
40 root of a 1000000 BYTE number: general newton 274047 ms; general nth root 1296 ms
41 root of a 1000000 BYTE number: general newton 3094 ms; general nth root 703 ms
42 root of a 1000000 BYTE number: general newton 10110 ms; general nth root 1062 ms
43 root of a 1000000 BYTE number: general newton 6781 ms; general nth root 937 ms
44 root of a 1000000 BYTE number: general newton 12500 ms; general nth root 1234 ms
45 root of a 1000000 BYTE number: general newton 4719 ms; general nth root 781 ms
46 root of a 1000000 BYTE number: general newton 12625 ms; general nth root 1172 ms
47 root of a 1000000 BYTE number: general newton 5531 ms; general nth root 1188 ms
48 root of a 1000000 BYTE number: general newton 9313 ms; general nth root 1343 ms
49 root of a 1000000 BYTE number: general newton 6656 ms; general nth root 1016 ms
50 root of a 1000000 BYTE number: general newton 279438 ms; general nth root 1750 ms
51 root of a 1000000 BYTE number: general newton 5563 ms; general nth root 906 ms
52 root of a 1000000 BYTE number: general newton 14343 ms; general nth root 1266 ms
53 root of a 1000000 BYTE number: general newton 224563 ms; general nth root 812 ms
54 root of a 1000000 BYTE number: general newton 13484 ms; general nth root 1203 ms
55 root of a 1000000 BYTE number: general newton 7875 ms; general nth root 985 ms
56 root of a 1000000 BYTE number: general newton 16422 ms; general nth root 1391 ms
57 root of a 1000000 BYTE number: general newton 4407 ms; general nth root 781 ms
58 root of a 1000000 BYTE number: general newton 15796 ms; general nth root 1204 ms
59 root of a 1000000 BYTE number: general newton 11281 ms; general nth root 1016 ms
60 root of a 1000000 BYTE number: general newton 15031 ms; general nth root 1391 ms
61 root of a 1000000 BYTE number: general newton 7344 ms; general nth root 859 ms
62 root of a 1000000 BYTE number: general newton 14297 ms; general nth root 1375 ms
63 root of a 1000000 BYTE number: general newton 13719 ms; general nth root 1062 ms
64 root of a 1000000 BYTE number: general newton 5735 ms; general nth root 1500 ms
65 root of a 1000000 BYTE number: general newton 3563 ms; general nth root 1171 ms
66 root of a 1000000 BYTE number: general newton 11328 ms; general nth root 1062 ms
67 root of a 1000000 BYTE number: general newton 2953 ms; general nth root 890 ms
68 root of a 1000000 BYTE number: general newton 15484 ms; general nth root 1438 ms
69 root of a 1000000 BYTE number: general newton 10891 ms; general nth root 1000 ms
70 root of a 1000000 BYTE number: general newton 8266 ms; general nth root 1125 ms
71 root of a 1000000 BYTE number: general newton 14031 ms; general nth root 1000 ms
72 root of a 1000000 BYTE number: general newton 18265 ms; general nth root 1375 ms
73 root of a 1000000 BYTE number: general newton 11516 ms; general nth root 781 ms
74 root of a 1000000 BYTE number: general newton 17313 ms; general nth root 1312 ms
75 root of a 1000000 BYTE number: general newton 7828 ms; general nth root 875 ms
76 root of a 1000000 BYTE number: general newton 16750 ms; general nth root 1172 ms
77 root of a 1000000 BYTE number: general newton 11485 ms; general nth root 796 ms
78 root of a 1000000 BYTE number: general newton 16281 ms; general nth root 1172 ms
79 root of a 1000000 BYTE number: general newton 5829 ms; general nth root 906 ms
80 root of a 1000000 BYTE number: general newton 504625 ms; general nth root 1344 ms
81 root of a 1000000 BYTE number: general newton 7500 ms; general nth root 672 ms
82 root of a 1000000 BYTE number: general newton 4297 ms; general nth root 1015 ms
83 root of a 1000000 BYTE number: general newton 8359 ms; general nth root 1250 ms
84 root of a 1000000 BYTE number: general newton 18484 ms; general nth root 1329 ms
85 root of a 1000000 BYTE number: general newton 6422 ms; general nth root 765 ms
86 root of a 1000000 BYTE number: general newton 542500 ms; general nth root 1203 ms
87 root of a 1000000 BYTE number: general newton 17907 ms; general nth root 937 ms
88 root of a 1000000 BYTE number: general newton 5094 ms; general nth root 1281 ms
89 root of a 1000000 BYTE number: general newton 335734 ms; general nth root 735 ms
90 root of a 1000000 BYTE number: general newton 5844 ms; general nth root 1047 ms
91 root of a 1000000 BYTE number: general newton 15234 ms; general nth root 875 ms
92 root of a 1000000 BYTE number: general newton 13813 ms; general nth root 1218 ms
93 root of a 1000000 BYTE number: general newton 9109 ms; general nth root 938 ms
94 root of a 1000000 BYTE number: general newton 15203 ms; general nth root 1125 ms
95 root of a 1000000 BYTE number: general newton 10641 ms; general nth root 969 ms
96 root of a 1000000 BYTE number: general newton 19797 ms; general nth root 1563 ms
97 root of a 1000000 BYTE number: general newton 11828 ms; general nth root 750 ms
98 root of a 1000000 BYTE number: general newton 10484 ms; general nth root 1219 ms
99 root of a 1000000 BYTE number: general newton 16797 ms; general nth root 922 ms
100 root of a 1000000 BYTE number: general newton 626953 ms; general nth root 1141 ms
2 root of a 1000000 BYTE number: 219 ms; 2 root of THAT: 484 ms (703 ms overall)
4 root of a 1000000 BYTE number: 718 ms
3 root of a 1000000 BYTE number: 110 ms; 2 root of THAT: 500 ms (610 ms overall)
6 root of a 1000000 BYTE number: 984 ms
4 root of a 1000000 BYTE number: 110 ms; 2 root of THAT: 703 ms (813 ms overall)
8 root of a 1000000 BYTE number: 1078 ms
5 root of a 1000000 BYTE number: 78 ms; 2 root of THAT: 672 ms (750 ms overall)
10 root of a 1000000 BYTE number: 1015 ms
6 root of a 1000000 BYTE number: 47 ms; 2 root of THAT: 969 ms (1016 ms overall)
12 root of a 1000000 BYTE number: 1219 ms
7 root of a 1000000 BYTE number: 47 ms; 2 root of THAT: 859 ms (906 ms overall)
14 root of a 1000000 BYTE number: 1156 ms
8 root of a 1000000 BYTE number: 32 ms; 2 root of THAT: 1078 ms (1110 ms overall)
16 root of a 1000000 BYTE number: 1281 ms
9 root of a 1000000 BYTE number: 31 ms; 2 root of THAT: 672 ms (703 ms overall)
18 root of a 1000000 BYTE number: 953 ms
10 root of a 1000000 BYTE number: 31 ms; 2 root of THAT: 1000 ms (1031 ms overall)
20 root of a 1000000 BYTE number: 1125 ms
2 root of a 1000000 BYTE number: 265 ms; 3 root of THAT: 485 ms (750 ms overall)
6 root of a 1000000 BYTE number: 969 ms
3 root of a 1000000 BYTE number: 141 ms; 3 root of THAT: 500 ms (641 ms overall)
9 root of a 1000000 BYTE number: 656 ms
4 root of a 1000000 BYTE number: 94 ms; 3 root of THAT: 719 ms (813 ms overall)
12 root of a 1000000 BYTE number: 1203 ms
5 root of a 1000000 BYTE number: 93 ms; 3 root of THAT: 672 ms (765 ms overall)
15 root of a 1000000 BYTE number: 953 ms
6 root of a 1000000 BYTE number: 62 ms; 3 root of THAT: 985 ms (1047 ms overall)
18 root of a 1000000 BYTE number: 953 ms
7 root of a 1000000 BYTE number: 47 ms; 3 root of THAT: 844 ms (891 ms overall)
21 root of a 1000000 BYTE number: 719 ms
8 root of a 1000000 BYTE number: 47 ms; 3 root of THAT: 1078 ms (1125 ms overall)
24 root of a 1000000 BYTE number: 1250 ms
9 root of a 1000000 BYTE number: 31 ms; 3 root of THAT: 672 ms (703 ms overall)
27 root of a 1000000 BYTE number: 875 ms
10 root of a 1000000 BYTE number: 31 ms; 3 root of THAT: 1016 ms (1047 ms overall)
30 root of a 1000000 BYTE number: 1203 ms
2 root of a 1000000 BYTE number: 453 ms; 4 root of THAT: 484 ms (937 ms overall)
8 root of a 1000000 BYTE number: 1079 ms
3 root of a 1000000 BYTE number: 218 ms; 4 root of THAT: 500 ms (718 ms overall)
12 root of a 1000000 BYTE number: 1203 ms
4 root of a 1000000 BYTE number: 171 ms; 4 root of THAT: 704 ms (875 ms overall)
16 root of a 1000000 BYTE number: 1266 ms
5 root of a 1000000 BYTE number: 141 ms; 4 root of THAT: 672 ms (813 ms overall)
20 root of a 1000000 BYTE number: 1140 ms
6 root of a 1000000 BYTE number: 94 ms; 4 root of THAT: 953 ms (1047 ms overall)
24 root of a 1000000 BYTE number: 1234 ms
7 root of a 1000000 BYTE number: 125 ms; 4 root of THAT: 875 ms (1000 ms overall)
28 root of a 1000000 BYTE number: 1375 ms
8 root of a 1000000 BYTE number: 63 ms; 4 root of THAT: 1125 ms (1188 ms overall)
32 root of a 1000000 BYTE number: 1437 ms
9 root of a 1000000 BYTE number: 47 ms; 4 root of THAT: 672 ms (719 ms overall)
36 root of a 1000000 BYTE number: 1078 ms
10 root of a 1000000 BYTE number: 78 ms; 4 root of THAT: 1000 ms (1078 ms overall)
40 root of a 1000000 BYTE number: 1157 ms
2 root of a 1000000 BYTE number: 438 ms; 5 root of THAT: 484 ms (922 ms overall)
10 root of a 1000000 BYTE number: 1000 ms
3 root of a 1000000 BYTE number: 203 ms; 5 root of THAT: 500 ms (703 ms overall)
15 root of a 1000000 BYTE number: 953 ms
4 root of a 1000000 BYTE number: 172 ms; 5 root of THAT: 719 ms (891 ms overall)
20 root of a 1000000 BYTE number: 1125 ms
5 root of a 1000000 BYTE number: 156 ms; 5 root of THAT: 672 ms (828 ms overall)
25 root of a 1000000 BYTE number: 703 ms
6 root of a 1000000 BYTE number: 78 ms; 5 root of THAT: 969 ms (1047 ms overall)
30 root of a 1000000 BYTE number: 1219 ms
7 root of a 1000000 BYTE number: 62 ms; 5 root of THAT: 844 ms (906 ms overall)
35 root of a 1000000 BYTE number: 750 ms
8 root of a 1000000 BYTE number: 62 ms; 5 root of THAT: 1094 ms (1156 ms overall)
40 root of a 1000000 BYTE number: 1157 ms
9 root of a 1000000 BYTE number: 47 ms; 5 root of THAT: 656 ms (703 ms overall)
45 root of a 1000000 BYTE number: 719 ms
10 root of a 1000000 BYTE number: 62 ms; 5 root of THAT: 1031 ms (1093 ms overall)
50 root of a 1000000 BYTE number: 1047 ms
2 root of a 1000000 BYTE number: 437 ms; 6 root of THAT: 485 ms (922 ms overall)
12 root of a 1000000 BYTE number: 1203 ms
3 root of a 1000000 BYTE number: 234 ms; 6 root of THAT: 485 ms (719 ms overall)
18 root of a 1000000 BYTE number: 953 ms
4 root of a 1000000 BYTE number: 187 ms; 6 root of THAT: 719 ms (906 ms overall)
24 root of a 1000000 BYTE number: 1360 ms
5 root of a 1000000 BYTE number: 172 ms; 6 root of THAT: 687 ms (859 ms overall)
30 root of a 1000000 BYTE number: 1234 ms
6 root of a 1000000 BYTE number: 94 ms; 6 root of THAT: 969 ms (1063 ms overall)
36 root of a 1000000 BYTE number: 1062 ms
7 root of a 1000000 BYTE number: 94 ms; 6 root of THAT: 844 ms (938 ms overall)
42 root of a 1000000 BYTE number: 953 ms
8 root of a 1000000 BYTE number: 79 ms; 6 root of THAT: 1109 ms (1188 ms overall)
48 root of a 1000000 BYTE number: 1250 ms
9 root of a 1000000 BYTE number: 63 ms; 6 root of THAT: 671 ms (734 ms overall)
54 root of a 1000000 BYTE number: 1141 ms
10 root of a 1000000 BYTE number: 62 ms; 6 root of THAT: 1031 ms (1093 ms overall)
60 root of a 1000000 BYTE number: 1328 ms
2 root of a 1000000 BYTE number: 344 ms; 7 root of THAT: 485 ms (829 ms overall)
14 root of a 1000000 BYTE number: 1156 ms
3 root of a 1000000 BYTE number: 219 ms; 7 root of THAT: 500 ms (719 ms overall)
21 root of a 1000000 BYTE number: 718 ms
4 root of a 1000000 BYTE number: 157 ms; 7 root of THAT: 703 ms (860 ms overall)
28 root of a 1000000 BYTE number: 1265 ms
5 root of a 1000000 BYTE number: 109 ms; 7 root of THAT: 657 ms (766 ms overall)
35 root of a 1000000 BYTE number: 734 ms
6 root of a 1000000 BYTE number: 94 ms; 7 root of THAT: 953 ms (1047 ms overall)
42 root of a 1000000 BYTE number: 953 ms
7 root of a 1000000 BYTE number: 79 ms; 7 root of THAT: 828 ms (907 ms overall)
49 root of a 1000000 BYTE number: 1000 ms
8 root of a 1000000 BYTE number: 62 ms; 7 root of THAT: 1078 ms (1140 ms overall)
56 root of a 1000000 BYTE number: 1281 ms
9 root of a 1000000 BYTE number: 47 ms; 7 root of THAT: 672 ms (719 ms overall)
63 root of a 1000000 BYTE number: 1094 ms
10 root of a 1000000 BYTE number: 47 ms; 7 root of THAT: 1000 ms (1047 ms overall)
70 root of a 1000000 BYTE number: 937 ms
2 root of a 1000000 BYTE number: 500 ms; 8 root of THAT: 469 ms (969 ms overall)
16 root of a 1000000 BYTE number: 1266 ms
3 root of a 1000000 BYTE number: 297 ms; 8 root of THAT: 484 ms (781 ms overall)
24 root of a 1000000 BYTE number: 1203 ms
4 root of a 1000000 BYTE number: 235 ms; 8 root of THAT: 703 ms (938 ms overall)
32 root of a 1000000 BYTE number: 1390 ms
5 root of a 1000000 BYTE number: 219 ms; 8 root of THAT: 656 ms (875 ms overall)
40 root of a 1000000 BYTE number: 1156 ms
6 root of a 1000000 BYTE number: 109 ms; 8 root of THAT: 954 ms (1063 ms overall)
48 root of a 1000000 BYTE number: 1219 ms
7 root of a 1000000 BYTE number: 94 ms; 8 root of THAT: 843 ms (937 ms overall)
56 root of a 1000000 BYTE number: 1281 ms
8 root of a 1000000 BYTE number: 109 ms; 8 root of THAT: 1063 ms (1172 ms overall)
64 root of a 1000000 BYTE number: 1453 ms
9 root of a 1000000 BYTE number: 62 ms; 8 root of THAT: 657 ms (719 ms overall)
72 root of a 1000000 BYTE number: 1172 ms
10 root of a 1000000 BYTE number: 63 ms; 8 root of THAT: 1000 ms (1063 ms overall)
80 root of a 1000000 BYTE number: 1171 ms
2 root of a 1000000 BYTE number: 281 ms; 9 root of THAT: 469 ms (750 ms overall)
18 root of a 1000000 BYTE number: 938 ms
3 root of a 1000000 BYTE number: 219 ms; 9 root of THAT: 500 ms (719 ms overall)
27 root of a 1000000 BYTE number: 890 ms
4 root of a 1000000 BYTE number: 110 ms; 9 root of THAT: 703 ms (813 ms overall)
36 root of a 1000000 BYTE number: 1016 ms
5 root of a 1000000 BYTE number: 110 ms; 9 root of THAT: 656 ms (766 ms overall)
45 root of a 1000000 BYTE number: 703 ms
6 root of a 1000000 BYTE number: 94 ms; 9 root of THAT: 953 ms (1047 ms overall)
54 root of a 1000000 BYTE number: 1093 ms
7 root of a 1000000 BYTE number: 78 ms; 9 root of THAT: 844 ms (922 ms overall)
63 root of a 1000000 BYTE number: 1016 ms
8 root of a 1000000 BYTE number: 47 ms; 9 root of THAT: 1062 ms (1109 ms overall)
72 root of a 1000000 BYTE number: 1172 ms
9 root of a 1000000 BYTE number: 47 ms; 9 root of THAT: 656 ms (703 ms overall)
81 root of a 1000000 BYTE number: 625 ms
10 root of a 1000000 BYTE number: 47 ms; 9 root of THAT: 1016 ms (1063 ms overall)
90 root of a 1000000 BYTE number: 1015 ms
2 root of a 1000000 BYTE number: 594 ms; 10 root of THAT: 469 ms (1063 ms overall)
20 root of a 1000000 BYTE number: 1125 ms
3 root of a 1000000 BYTE number: 328 ms; 10 root of THAT: 500 ms (828 ms overall)
30 root of a 1000000 BYTE number: 1188 ms
4 root of a 1000000 BYTE number: 281 ms; 10 root of THAT: 687 ms (968 ms overall)
40 root of a 1000000 BYTE number: 1157 ms
5 root of a 1000000 BYTE number: 219 ms; 10 root of THAT: 656 ms (875 ms overall)
50 root of a 1000000 BYTE number: 1000 ms
6 root of a 1000000 BYTE number: 140 ms; 10 root of THAT: 953 ms (1093 ms overall)
60 root of a 1000000 BYTE number: 1297 ms
7 root of a 1000000 BYTE number: 94 ms; 10 root of THAT: 828 ms (922 ms overall)
70 root of a 1000000 BYTE number: 953 ms
8 root of a 1000000 BYTE number: 93 ms; 10 root of THAT: 1063 ms (1156 ms overall)
80 root of a 1000000 BYTE number: 1172 ms
9 root of a 1000000 BYTE number: 62 ms; 10 root of THAT: 657 ms (719 ms overall)
90 root of a 1000000 BYTE number: 984 ms
10 root of a 1000000 BYTE number: 110 ms; 10 root of THAT: 1000 ms (1110 ms overall)
100 root of a 1000000 BYTE number: 1109 ms
square root of a 1000000 BYTE number: 204 ms; 2 root of THAT: 281 ms (485 ms overall)
2 root of a 1000000 BYTE number: 109 ms; square root of THAT: 484 ms (593 ms overall)
4 root of a 1000000 BYTE number: 703 ms
square root of a 1000000 BYTE number: 281 ms; 3 root of THAT: 266 ms (547 ms overall)
3 root of a 1000000 BYTE number: 62 ms; square root of THAT: 485 ms (547 ms overall)
6 root of a 1000000 BYTE number: 953 ms
square root of a 1000000 BYTE number: 453 ms; 4 root of THAT: 282 ms (735 ms overall)
4 root of a 1000000 BYTE number: 63 ms; square root of THAT: 687 ms (750 ms overall)
8 root of a 1000000 BYTE number: 1062 ms
square root of a 1000000 BYTE number: 437 ms; 5 root of THAT: 266 ms (703 ms overall)
5 root of a 1000000 BYTE number: 31 ms; square root of THAT: 657 ms (688 ms overall)
10 root of a 1000000 BYTE number: 1000 ms
square root of a 1000000 BYTE number: 438 ms; 6 root of THAT: 281 ms (719 ms overall)
6 root of a 1000000 BYTE number: 31 ms; square root of THAT: 953 ms (984 ms overall)
12 root of a 1000000 BYTE number: 1172 ms
square root of a 1000000 BYTE number: 344 ms; 7 root of THAT: 281 ms (625 ms overall)
7 root of a 1000000 BYTE number: 31 ms; square root of THAT: 828 ms (859 ms overall)
14 root of a 1000000 BYTE number: 1156 ms
square root of a 1000000 BYTE number: 516 ms; 8 root of THAT: 266 ms (782 ms overall)
8 root of a 1000000 BYTE number: 16 ms; square root of THAT: 1062 ms (1078 ms overall)
16 root of a 1000000 BYTE number: 1250 ms
square root of a 1000000 BYTE number: 281 ms; 9 root of THAT: 297 ms (578 ms overall)
9 root of a 1000000 BYTE number: 16 ms; square root of THAT: 656 ms (672 ms overall)
18 root of a 1000000 BYTE number: 922 ms
square root of a 1000000 BYTE number: 578 ms; 10 root of THAT: 281 ms (859 ms overall)
10 root of a 1000000 BYTE number: 15 ms; square root of THAT: 1016 ms (1031 ms overall)
20 root of a 1000000 BYTE number: 1125 ms
square root of a 1000000 BYTE number: 344 ms; 11 root of THAT: 266 ms (610 ms overall)
11 root of a 1000000 BYTE number: 0 ms; square root of THAT: 828 ms (828 ms overall)
22 root of a 1000000 BYTE number: 1062 ms
square root of a 1000000 BYTE number: 500 ms; 12 root of THAT: 266 ms (766 ms overall)
12 root of a 1000000 BYTE number: 16 ms; square root of THAT: 1187 ms (1203 ms overall)
24 root of a 1000000 BYTE number: 1250 ms
square root of a 1000000 BYTE number: 328 ms; 13 root of THAT: 266 ms (594 ms overall)
13 root of a 1000000 BYTE number: 0 ms; square root of THAT: 765 ms (765 ms overall)
26 root of a 1000000 BYTE number: 1063 ms
square root of a 1000000 BYTE number: 500 ms; 14 root of THAT: 281 ms (781 ms overall)
14 root of a 1000000 BYTE number: 15 ms; square root of THAT: 1141 ms (1156 ms overall)
28 root of a 1000000 BYTE number: 1266 ms
square root of a 1000000 BYTE number: 406 ms; 15 root of THAT: 266 ms (672 ms overall)
15 root of a 1000000 BYTE number: 16 ms; square root of THAT: 953 ms (969 ms overall)
30 root of a 1000000 BYTE number: 1187 ms
square root of a 1000000 BYTE number: 594 ms; 16 root of THAT: 281 ms (875 ms overall)
16 root of a 1000000 BYTE number: 15 ms; square root of THAT: 1266 ms (1281 ms overall)
32 root of a 1000000 BYTE number: 1391 ms
square root of a 1000000 BYTE number: 297 ms; 17 root of THAT: 266 ms (563 ms overall)
17 root of a 1000000 BYTE number: 0 ms; square root of THAT: 640 ms (640 ms overall)
34 root of a 1000000 BYTE number: 938 ms
square root of a 1000000 BYTE number: 406 ms; 18 root of THAT: 281 ms (687 ms overall)
18 root of a 1000000 BYTE number: 0 ms; square root of THAT: 953 ms (953 ms overall)
36 root of a 1000000 BYTE number: 1032 ms
square root of a 1000000 BYTE number: 344 ms; 19 root of THAT: 296 ms (640 ms overall)
19 root of a 1000000 BYTE number: 0 ms; square root of THAT: 781 ms (781 ms overall)
38 root of a 1000000 BYTE number: 1000 ms
square root of a 1000000 BYTE number: 703 ms; 20 root of THAT: 266 ms (969 ms overall)
20 root of a 1000000 BYTE number: 0 ms; square root of THAT: 1125 ms (1125 ms overall)
40 root of a 1000000 BYTE number: 1156 ms
square root of a 1000000 BYTE number: 297 ms; 21 root of THAT: 266 ms (563 ms overall)
21 root of a 1000000 BYTE number: 0 ms; square root of THAT: 719 ms (719 ms overall)
42 root of a 1000000 BYTE number: 968 ms
square root of a 1000000 BYTE number: 469 ms; 22 root of THAT: 266 ms (735 ms overall)
22 root of a 1000000 BYTE number: 0 ms; square root of THAT: 1047 ms (1047 ms overall)
44 root of a 1000000 BYTE number: 1140 ms
square root of a 1000000 BYTE number: 391 ms; 23 root of THAT: 266 ms (657 ms overall)
23 root of a 1000000 BYTE number: 0 ms; square root of THAT: 859 ms (859 ms overall)
46 root of a 1000000 BYTE number: 1062 ms
square root of a 1000000 BYTE number: 531 ms; 24 root of THAT: 266 ms (797 ms overall)
24 root of a 1000000 BYTE number: 0 ms; square root of THAT: 1250 ms (1250 ms overall)
48 root of a 1000000 BYTE number: 1203 ms
square root of a 1000000 BYTE number: 453 ms; 25 root of THAT: 282 ms (735 ms overall)
25 root of a 1000000 BYTE number: 0 ms; square root of THAT: 703 ms (703 ms overall)
50 root of a 1000000 BYTE number: 1000 ms
square root of a 1000000 BYTE number: 485 ms; 26 root of THAT: 281 ms (766 ms overall)
26 root of a 1000000 BYTE number: 0 ms; square root of THAT: 1062 ms (1062 ms overall)
52 root of a 1000000 BYTE number: 1172 ms
square root of a 1000000 BYTE number: 391 ms; 27 root of THAT: 281 ms (672 ms overall)
27 root of a 1000000 BYTE number: 0 ms; square root of THAT: 875 ms (875 ms overall)
54 root of a 1000000 BYTE number: 1109 ms
square root of a 1000000 BYTE number: 578 ms; 28 root of THAT: 266 ms (844 ms overall)
28 root of a 1000000 BYTE number: 0 ms; square root of THAT: 1266 ms (1266 ms overall)
56 root of a 1000000 BYTE number: 1281 ms
square root of a 1000000 BYTE number: 344 ms; 29 root of THAT: 265 ms (609 ms overall)
29 root of a 1000000 BYTE number: 0 ms; square root of THAT: 797 ms (797 ms overall)
58 root of a 1000000 BYTE number: 1094 ms
square root of a 1000000 BYTE number: 531 ms; 30 root of THAT: 281 ms (812 ms overall)
30 root of a 1000000 BYTE number: 16 ms; square root of THAT: 1187 ms (1203 ms overall)
60 root of a 1000000 BYTE number: 1281 ms
square root of a 1000000 BYTE number: 437 ms; 31 root of THAT: 266 ms (703 ms overall)
31 root of a 1000000 BYTE number: 0 ms; square root of THAT: 1000 ms (1000 ms overall)
62 root of a 1000000 BYTE number: 1219 ms
square root of a 1000000 BYTE number: 625 ms; 32 root of THAT: 281 ms (906 ms overall)
32 root of a 1000000 BYTE number: 0 ms; square root of THAT: 1407 ms (1407 ms overall)
64 root of a 1000000 BYTE number: 1453 ms
square root of a 1000000 BYTE number: 313 ms; 33 root of THAT: 265 ms (578 ms overall)
33 root of a 1000000 BYTE number: 0 ms; square root of THAT: 609 ms (609 ms overall)
66 root of a 1000000 BYTE number: 1000 ms
square root of a 1000000 BYTE number: 468 ms; 34 root of THAT: 282 ms (750 ms overall)
34 root of a 1000000 BYTE number: 16 ms; square root of THAT: 953 ms (969 ms overall)
68 root of a 1000000 BYTE number: 1156 ms
square root of a 1000000 BYTE number: 344 ms; 35 root of THAT: 266 ms (610 ms overall)
35 root of a 1000000 BYTE number: 0 ms; square root of THAT: 750 ms (750 ms overall)
70 root of a 1000000 BYTE number: 922 ms
square root of a 1000000 BYTE number: 484 ms; 36 root of THAT: 281 ms (765 ms overall)
36 root of a 1000000 BYTE number: 0 ms; square root of THAT: 1031 ms (1031 ms overall)
72 root of a 1000000 BYTE number: 1172 ms
square root of a 1000000 BYTE number: 296 ms; 37 root of THAT: 282 ms (578 ms overall)
37 root of a 1000000 BYTE number: 0 ms; square root of THAT: 704 ms (704 ms overall)
74 root of a 1000000 BYTE number: 937 ms
square root of a 1000000 BYTE number: 453 ms; 38 root of THAT: 266 ms (719 ms overall)
38 root of a 1000000 BYTE number: 0 ms; square root of THAT: 984 ms (984 ms overall)
76 root of a 1000000 BYTE number: 1078 ms
square root of a 1000000 BYTE number: 375 ms; 39 root of THAT: 266 ms (641 ms overall)
39 root of a 1000000 BYTE number: 0 ms; square root of THAT: 828 ms (828 ms overall)
78 root of a 1000000 BYTE number: 1031 ms
square root of a 1000000 BYTE number: 593 ms; 40 root of THAT: 282 ms (875 ms overall)
40 root of a 1000000 BYTE number: 0 ms; square root of THAT: 1141 ms (1141 ms overall)
80 root of a 1000000 BYTE number: 1172 ms
square root of a 1000000 BYTE number: 297 ms; 41 root of THAT: 265 ms (562 ms overall)
41 root of a 1000000 BYTE number: 0 ms; square root of THAT: 641 ms (641 ms overall)
82 root of a 1000000 BYTE number: 891 ms
square root of a 1000000 BYTE number: 437 ms; 42 root of THAT: 281 ms (718 ms overall)
42 root of a 1000000 BYTE number: 15 ms; square root of THAT: 985 ms (1000 ms overall)
84 root of a 1000000 BYTE number: 1094 ms
square root of a 1000000 BYTE number: 375 ms; 43 root of THAT: 266 ms (641 ms overall)
43 root of a 1000000 BYTE number: 0 ms; square root of THAT: 812 ms (812 ms overall)
86 root of a 1000000 BYTE number: 1000 ms
square root of a 1000000 BYTE number: 515 ms; 44 root of THAT: 266 ms (781 ms overall)
44 root of a 1000000 BYTE number: 0 ms; square root of THAT: 1125 ms (1125 ms overall)
88 root of a 1000000 BYTE number: 1141 ms
square root of a 1000000 BYTE number: 328 ms; 45 root of THAT: 266 ms (594 ms overall)
45 root of a 1000000 BYTE number: 0 ms; square root of THAT: 734 ms (734 ms overall)
90 root of a 1000000 BYTE number: 953 ms
square root of a 1000000 BYTE number: 484 ms; 46 root of THAT: 282 ms (766 ms overall)
46 root of a 1000000 BYTE number: 0 ms; square root of THAT: 1047 ms (1047 ms overall)
92 root of a 1000000 BYTE number: 1125 ms
square root of a 1000000 BYTE number: 407 ms; 47 root of THAT: 265 ms (672 ms overall)
47 root of a 1000000 BYTE number: 0 ms; square root of THAT: 859 ms (859 ms overall)
94 root of a 1000000 BYTE number: 1063 ms
square root of a 1000000 BYTE number: 563 ms; 48 root of THAT: 265 ms (828 ms overall)
48 root of a 1000000 BYTE number: 0 ms; square root of THAT: 1218 ms (1218 ms overall)
96 root of a 1000000 BYTE number: 1360 ms
square root of a 1000000 BYTE number: 328 ms; 49 root of THAT: 281 ms (609 ms overall)
49 root of a 1000000 BYTE number: 0 ms; square root of THAT: 1016 ms (1016 ms overall)
98 root of a 1000000 BYTE number: 1062 ms
square root of a 1000000 BYTE number: 719 ms; 50 root of THAT: 266 ms (985 ms overall)
50 root of a 1000000 BYTE number: 0 ms; square root of THAT: 1000 ms (1000 ms overall)
100 root of a 1000000 BYTE number: 1125 ms

Taking root 7 of a 1000000000 BYTE number took 3030485 milliseconds
Taking root 49 of a 1000000000 BYTE number took 2082172 milliseconds
Taking root 343 of a 1000000000 BYTE number took 2150047 milliseconds
Taking root 2401 of a 1000000000 BYTE number took 1729125 milliseconds
Taking root 16807 of a 1000000000 BYTE number took 1618203 milliseconds
Taking root 117649 of a 1000000000 BYTE number took 3492109 milliseconds
Taking root 823543 of a 1000000000 BYTE number took 12530328 milliseconds

Taking root 7 of a 1000000 BYTE number took 1047 milliseconds
Taking root 49 of a 1000000 BYTE number took 1000 milliseconds
Taking root 343 of a 1000000 BYTE number took 781 milliseconds
Taking root 2401 of a 1000000 BYTE number took 547 milliseconds
Taking root 16807 of a 1000000 BYTE number took 1360 milliseconds
Taking root 117649 of a 1000000 BYTE number took 2054921 milliseconds <- spent a LOT of time in Newton; the first 5 at least largely avoided it
Taking root 823543 of a 1000000 BYTE number took 138829 milliseconds
Taking root 5764801 of a 1000000 BYTE number took 171 milliseconds
Taking root 40353607 of a 1000000 BYTE number took 0 milliseconds
Taking root 282475249 of a 1000000 BYTE number took 0 milliseconds
Taking root 1977326743 of a 1000000 BYTE number took 875 milliseconds

Taking root 5 of a 1000000 BYTE number took 812 milliseconds
Taking root 25 of a 1000000 BYTE number took 828 milliseconds
Taking root 125 of a 1000000 BYTE number took 844 milliseconds
Taking root 625 of a 1000000 BYTE number took 719 milliseconds
Taking root 3125 of a 1000000 BYTE number took 484 milliseconds
Taking root 15625 of a 1000000 BYTE number took 15953 milliseconds
Taking root 78125 of a 1000000 BYTE number took 56500 milliseconds
Taking root 390625 of a 1000000 BYTE number took 35146641 milliseconds
Taking root 1953125 of a 1000000 BYTE number took 4875 milliseconds
Taking root 9765625 of a 1000000 BYTE number took 0 milliseconds
Taking root 48828125 of a 1000000 BYTE number took 0 milliseconds
Taking root 244140625 of a 1000000 BYTE number took 0 milliseconds
Taking root 1220703125 of a 1000000 BYTE number took 375 milliseconds

Testing general root times.  Doing this in retail?  If not, your numbers won't be representative
Taking root 5 of a 1000000 BYTE number took 797 milliseconds
Taking root 25 of a 1000000 BYTE number took 907 milliseconds
Taking root 125 of a 1000000 BYTE number took 1046 milliseconds
Taking root 625 of a 1000000 BYTE number took 860 milliseconds
Newton: Root 3125 Y: 28122 bits Guess: 9 bits B upper: 9 bits b actual: 4 Time: 31 milliseconds
Taking root 3125 of a 1000000 BYTE number took 562 milliseconds
Newton: Root 15625 Y: 140622 bits Guess: 9 bits B upper: 9 bits b actual: 4 Time: 328 milliseconds
Newton: Root 15625 Y: 265622 bits Guess: 17 bits B upper: 17 bits b actual: 8 Time: 14719 milliseconds
Taking root 15625 of a 1000000 BYTE number took 15547 milliseconds
Newton: Root 78125 Y: 265622 bits Guess: 4 bits B upper: 4 bits b actual: 0 Time: 31 milliseconds
Newton: Root 78125 Y: 421872 bits Guess: 6 bits B upper: 6 bits b actual: 2 Time: 188 milliseconds
Newton: Root 78125 Y: 812497 bits Guess: 11 bits B upper: 11 bits b actual: 3 Time: 12265 milliseconds
Newton: Root 78125 Y: 1515622 bits Guess: 20 bits B upper: 15 bits b actual: 7 Time: 43922 milliseconds
Taking root 78125 of a 1000000 BYTE number took 57125 milliseconds
Newton: Root 390625 Y: 968747 bits Guess: 3 bits B upper: 3 bits b actual: 1 Time: 78 milliseconds
Newton: Root 390625 Y: 1359372 bits Guess: 4 bits B upper: 4 bits b actual: 1 Time: 203 milliseconds
Newton: Root 390625 Y: 2140622 bits Guess: 6 bits B upper: 6 bits b actual: 0 Time: 1735 milliseconds
Newton: Root 390625 Y: 4093747 bits Guess: 11 bits B upper: 11 bits b actual: 5 Time: 128687 milliseconds
Newton: Root 390625 Y: 7999997 bits Guess: 21 bits B upper: 21 bits b actual: 8 Time: 37063359 milliseconds
Taking root 390625 of a 1000000 BYTE number took 37194219 milliseconds
Newton: Root 1953125 Y: 4093747 bits Guess: 3 bits B upper: 3 bits b actual: 0 Time: 500 milliseconds
Newton: Root 1953125 Y: 7999997 bits Guess: 5 bits B upper: 5 bits b actual: 1 Time: 4375 milliseconds
Taking root 1953125 of a 1000000 BYTE number took 5047 milliseconds
Taking root 9765625 of a 1000000 BYTE number took 0 milliseconds
Taking root 48828125 of a 1000000 BYTE number took 0 milliseconds
Taking root 244140625 of a 1000000 BYTE number took 0 milliseconds
Taking root 1220703125 of a 1000000 BYTE number took 359 milliseconds

improved bounds on the size of B:
Testing general root times.  Doing this in retail?  If not, your numbers won't be representative
Taking root 5 of a 1000000 BYTE number took 796 milliseconds
Taking root 25 of a 1000000 BYTE number took 860 milliseconds
Taking root 125 of a 1000000 BYTE number took 890 milliseconds
Taking root 625 of a 1000000 BYTE number took 735 milliseconds
Taking root 3125 of a 1000000 BYTE number took 453 milliseconds
Taking root 15625 of a 1000000 BYTE number took 547 milliseconds
Newton: Root 78125 Y: 812497 bits Guess: 11 bits B upper: 5 bits b actual: 3 Time: 157 milliseconds
Newton: Root 78125 Y: 1515622 bits Guess: 20 bits B upper: 9 bits b actual: 7 Time: 672 milliseconds
Taking root 78125 of a 1000000 BYTE number took 1547 milliseconds
Newton: Root 390625 Y: 4093747 bits Guess: 11 bits B upper: 5 bits b actual: 5 Time: 547 milliseconds
Newton: Root 390625 Y: 7999997 bits Guess: 21 bits B upper: 10 bits b actual: 8 Time: 14391 milliseconds
Taking root 390625 of a 1000000 BYTE number took 15234 milliseconds
Taking root 1953125 of a 1000000 BYTE number took 328 milliseconds
Taking root 9765625 of a 1000000 BYTE number took 0 milliseconds
Taking root 48828125 of a 1000000 BYTE number took 0 milliseconds
Taking root 244140625 of a 1000000 BYTE number took 0 milliseconds
Taking root 1220703125 of a 1000000 BYTE number took 672 milliseconds

===========================================================================
tests with processor pinned:
Testing general root times.  Doing this in retail?  If not, your numbers won't be representative
Square root of a 1000000 BYTE number: SQRT 344 ms; general nth root 562 ms
Square root of a 1000000 BYTE number: SQRT 312 ms; general nth root 547 ms
Square root of a 1000000 BYTE number: SQRT 313 ms; general nth root 453 ms
Square root of a 1000000 BYTE number: SQRT 375 ms; general nth root 484 ms
Square root of a 1000000 BYTE number: SQRT 312 ms; general nth root 563 ms
Square root of a 1000000 BYTE number: SQRT 297 ms; general nth root 422 ms
Square root of a 1000000 BYTE number: SQRT 282 ms; general nth root 421 ms
Square root of a 1000000 BYTE number: SQRT 313 ms; general nth root 546 ms
Square root of a 1000000 BYTE number: SQRT 297 ms; general nth root 500 ms
Square root of a 1000000 BYTE number: SQRT 281 ms; general nth root 532 ms
2 root of a 1000000 BYTE number: general newton 17375 ms; general nth root 485 ms
3 root of a 1000000 BYTE number: general newton 6203 ms; general nth root 531 ms
4 root of a 1000000 BYTE number: general newton 24047 ms; general nth root 797 ms
5 root of a 1000000 BYTE number: general newton 26547 ms; general nth root 672 ms
6 root of a 1000000 BYTE number: general newton 6812 ms; general nth root 1047 ms
7 root of a 1000000 BYTE number: general newton 5219 ms; general nth root 875 ms
8 root of a 1000000 BYTE number: general newton 53735 ms; general nth root 1172 ms
9 root of a 1000000 BYTE number: general newton 4265 ms; general nth root 688 ms
10 root of a 1000000 BYTE number: general newton 63687 ms; general nth root 1109 ms
11 root of a 1000000 BYTE number: general newton 5125 ms; general nth root 922 ms
12 root of a 1000000 BYTE number: general newton 7485 ms; general nth root 1375 ms
13 root of a 1000000 BYTE number: general newton 5813 ms; general nth root 843 ms
14 root of a 1000000 BYTE number: general newton 7313 ms; general nth root 1218 ms
15 root of a 1000000 BYTE number: general newton 7141 ms; general nth root 1000 ms
16 root of a 1000000 BYTE number: general newton 102531 ms; general nth root 1313 ms
17 root of a 1000000 BYTE number: general newton 4875 ms; general nth root 656 ms
18 root of a 1000000 BYTE number: general newton 7125 ms; general nth root 985 ms
19 root of a 1000000 BYTE number: general newton 5032 ms; general nth root 812 ms
20 root of a 1000000 BYTE number: general newton 130765 ms; general nth root 1813 ms
21 root of a 1000000 BYTE number: general newton 5203 ms; general nth root 735 ms
22 root of a 1000000 BYTE number: general newton 7922 ms; general nth root 1109 ms
23 root of a 1000000 BYTE number: general newton 7375 ms; general nth root 875 ms
24 root of a 1000000 BYTE number: general newton 9469 ms; general nth root 1328 ms
25 root of a 1000000 BYTE number: general newton 101469 ms; general nth root 1078 ms
26 root of a 1000000 BYTE number: general newton 8250 ms; general nth root 1141 ms
27 root of a 1000000 BYTE number: general newton 7485 ms; general nth root 921 ms
28 root of a 1000000 BYTE number: general newton 10797 ms; general nth root 1375 ms
29 root of a 1000000 BYTE number: general newton 7516 ms; general nth root 812 ms
30 root of a 1000000 BYTE number: general newton 7562 ms; general nth root 1234 ms
31 root of a 1000000 BYTE number: general newton 7000 ms; general nth root 1016 ms
32 root of a 1000000 BYTE number: general newton 7750 ms; general nth root 1453 ms
33 root of a 1000000 BYTE number: general newton 5062 ms; general nth root 625 ms
34 root of a 1000000 BYTE number: general newton 8250 ms; general nth root 985 ms
35 root of a 1000000 BYTE number: general newton 6422 ms; general nth root 766 ms
36 root of a 1000000 BYTE number: general newton 9859 ms; general nth root 1062 ms
37 root of a 1000000 BYTE number: general newton 6141 ms; general nth root 687 ms
38 root of a 1000000 BYTE number: general newton 8172 ms; general nth root 1015 ms
39 root of a 1000000 BYTE number: general newton 7687 ms; general nth root 859 ms
40 root of a 1000000 BYTE number: general newton 245969 ms; general nth root 1203 ms
41 root of a 1000000 BYTE number: general newton 2891 ms; general nth root 640 ms
42 root of a 1000000 BYTE number: general newton 9515 ms; general nth root 1000 ms
43 root of a 1000000 BYTE number: general newton 6406 ms; general nth root 828 ms
44 root of a 1000000 BYTE number: general newton 11937 ms; general nth root 1438 ms
45 root of a 1000000 BYTE number: general newton 4750 ms; general nth root 734 ms
46 root of a 1000000 BYTE number: general newton 12407 ms; general nth root 1281 ms
47 root of a 1000000 BYTE number: general newton 5343 ms; general nth root 1125 ms
48 root of a 1000000 BYTE number: general newton 8875 ms; general nth root 1266 ms
49 root of a 1000000 BYTE number: general newton 6328 ms; general nth root 969 ms
50 root of a 1000000 BYTE number: general newton 263781 ms; general nth root 1656 ms
51 root of a 1000000 BYTE number: general newton 5328 ms; general nth root 844 ms
52 root of a 1000000 BYTE number: general newton 13094 ms; general nth root 1297 ms
53 root of a 1000000 BYTE number: general newton 212484 ms; general nth root 797 ms
54 root of a 1000000 BYTE number: general newton 13594 ms; general nth root 1188 ms
55 root of a 1000000 BYTE number: general newton 7641 ms; general nth root 937 ms
56 root of a 1000000 BYTE number: general newton 15765 ms; general nth root 1344 ms
57 root of a 1000000 BYTE number: general newton 4172 ms; general nth root 750 ms
58 root of a 1000000 BYTE number: general newton 14500 ms; general nth root 1140 ms
59 root of a 1000000 BYTE number: general newton 10906 ms; general nth root 922 ms
60 root of a 1000000 BYTE number: general newton 14235 ms; general nth root 1359 ms
61 root of a 1000000 BYTE number: general newton 7172 ms; general nth root 843 ms
62 root of a 1000000 BYTE number: general newton 13828 ms; general nth root 1328 ms
63 root of a 1000000 BYTE number: general newton 13188 ms; general nth root 1015 ms
64 root of a 1000000 BYTE number: general newton 5547 ms; general nth root 1515 ms
65 root of a 1000000 BYTE number: general newton 3688 ms; general nth root 1140 ms
66 root of a 1000000 BYTE number: general newton 10954 ms; general nth root 1015 ms
67 root of a 1000000 BYTE number: general newton 2844 ms; general nth root 875 ms
68 root of a 1000000 BYTE number: general newton 13453 ms; general nth root 1203 ms
69 root of a 1000000 BYTE number: general newton 10156 ms; general nth root 875 ms
70 root of a 1000000 BYTE number: general newton 7235 ms; general nth root 1000 ms
71 root of a 1000000 BYTE number: general newton 12703 ms; general nth root 891 ms
72 root of a 1000000 BYTE number: general newton 15875 ms; general nth root 1156 ms
73 root of a 1000000 BYTE number: general newton 9938 ms; general nth root 656 ms
74 root of a 1000000 BYTE number: general newton 14453 ms; general nth root 1062 ms
75 root of a 1000000 BYTE number: general newton 6234 ms; general nth root 781 ms
76 root of a 1000000 BYTE number: general newton 15422 ms; general nth root 1125 ms
77 root of a 1000000 BYTE number: general newton 10750 ms; general nth root 719 ms
78 root of a 1000000 BYTE number: general newton 15172 ms; general nth root 1109 ms
79 root of a 1000000 BYTE number: general newton 5453 ms; general nth root 859 ms
80 root of a 1000000 BYTE number: general newton 479531 ms; general nth root 1265 ms
81 root of a 1000000 BYTE number: general newton 7094 ms; general nth root 687 ms
82 root of a 1000000 BYTE number: general newton 4234 ms; general nth root 953 ms
83 root of a 1000000 BYTE number: general newton 8265 ms; general nth root 1469 ms
84 root of a 1000000 BYTE number: general newton 19344 ms; general nth root 1469 ms
85 root of a 1000000 BYTE number: general newton 6281 ms; general nth root 750 ms
86 root of a 1000000 BYTE number: general newton 466953 ms; general nth root 1016 ms
87 root of a 1000000 BYTE number: general newton 14937 ms; general nth root 844 ms
88 root of a 1000000 BYTE number: general newton 4719 ms; general nth root 1266 ms
89 root of a 1000000 BYTE number: general newton 331469 ms; general nth root 688 ms
90 root of a 1000000 BYTE number: general newton 5687 ms; general nth root 1016 ms
91 root of a 1000000 BYTE number: general newton 14812 ms; general nth root 860 ms
92 root of a 1000000 BYTE number: general newton 13375 ms; general nth root 1172 ms
93 root of a 1000000 BYTE number: general newton 8782 ms; general nth root 906 ms
94 root of a 1000000 BYTE number: general newton 14829 ms; general nth root 1125 ms
95 root of a 1000000 BYTE number: general newton 10422 ms; general nth root 922 ms
96 root of a 1000000 BYTE number: general newton 18187 ms; general nth root 1344 ms
97 root of a 1000000 BYTE number: general newton 10407 ms; general nth root 656 ms
98 root of a 1000000 BYTE number: general newton 9172 ms; general nth root 1094 ms
99 root of a 1000000 BYTE number: general newton 15954 ms; general nth root 968 ms
100 root of a 1000000 BYTE number: general newton 628421 ms; general nth root 1157 ms

515 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 2 root of THAT (250 ms)
563 ms to take the 2 root of a 1000000 BYTE number (438 ms) then take the square root of THAT: (125 ms)
672 ms to take the 4 root of a 1000000 BYTE number
531 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 3 root of THAT (266 ms)
563 ms to take the 3 root of a 1000000 BYTE number (500 ms) then take the square root of THAT: (63 ms)
937 ms to take the 6 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 4 root of THAT (344 ms)
750 ms to take the 4 root of a 1000000 BYTE number (703 ms) then take the square root of THAT: (47 ms)
1172 ms to take the 8 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 5 root of THAT (313 ms)
703 ms to take the 5 root of a 1000000 BYTE number (656 ms) then take the square root of THAT: (47 ms)
1015 ms to take the 10 root of a 1000000 BYTE number
704 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 6 root of THAT (438 ms)
968 ms to take the 6 root of a 1000000 BYTE number (937 ms) then take the square root of THAT: (31 ms)
1172 ms to take the 12 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 7 root of THAT (344 ms)
860 ms to take the 7 root of a 1000000 BYTE number (828 ms) then take the square root of THAT: (32 ms)
1140 ms to take the 14 root of a 1000000 BYTE number
766 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 8 root of THAT (500 ms)
1094 ms to take the 8 root of a 1000000 BYTE number (1078 ms) then take the square root of THAT: (16 ms)
1234 ms to take the 16 root of a 1000000 BYTE number
609 ms to take the square root of a 1000000 BYTE number (328 ms) then take the 9 root of THAT (281 ms)
703 ms to take the 9 root of a 1000000 BYTE number (688 ms) then take the square root of THAT: (15 ms)
1079 ms to take the 18 root of a 1000000 BYTE number
765 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 10 root of THAT (500 ms)
1063 ms to take the 10 root of a 1000000 BYTE number (1047 ms) then take the square root of THAT: (16 ms)
1203 ms to take the 20 root of a 1000000 BYTE number
672 ms to take the square root of a 1000000 BYTE number (328 ms) then take the 11 root of THAT (344 ms)
859 ms to take the 11 root of a 1000000 BYTE number (843 ms) then take the square root of THAT: (16 ms)
1047 ms to take the 22 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 12 root of THAT (500 ms)
1187 ms to take the 12 root of a 1000000 BYTE number (1172 ms) then take the square root of THAT: (15 ms)
1235 ms to take the 24 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 13 root of THAT (313 ms)
765 ms to take the 13 root of a 1000000 BYTE number (765 ms) then take the square root of THAT: (0 ms)
1063 ms to take the 26 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 14 root of THAT (515 ms)
1156 ms to take the 14 root of a 1000000 BYTE number (1156 ms) then take the square root of THAT: (0 ms)
1266 ms to take the 28 root of a 1000000 BYTE number
672 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 15 root of THAT (391 ms)
953 ms to take the 15 root of a 1000000 BYTE number (953 ms) then take the square root of THAT: (0 ms)
1188 ms to take the 30 root of a 1000000 BYTE number
859 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 16 root of THAT (594 ms)
1250 ms to take the 16 root of a 1000000 BYTE number (1250 ms) then take the square root of THAT: (0 ms)
1391 ms to take the 32 root of a 1000000 BYTE number
562 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 17 root of THAT (281 ms)
641 ms to take the 17 root of a 1000000 BYTE number (625 ms) then take the square root of THAT: (16 ms)
937 ms to take the 34 root of a 1000000 BYTE number
688 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 18 root of THAT (422 ms)
922 ms to take the 18 root of a 1000000 BYTE number (922 ms) then take the square root of THAT: (0 ms)
1016 ms to take the 36 root of a 1000000 BYTE number
640 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 19 root of THAT (359 ms)
782 ms to take the 19 root of a 1000000 BYTE number (782 ms) then take the square root of THAT: (0 ms)
968 ms to take the 38 root of a 1000000 BYTE number
782 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 20 root of THAT (500 ms)
1109 ms to take the 20 root of a 1000000 BYTE number (1109 ms) then take the square root of THAT: (0 ms)
1156 ms to take the 40 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 21 root of THAT (312 ms)
719 ms to take the 21 root of a 1000000 BYTE number (704 ms) then take the square root of THAT: (15 ms)
938 ms to take the 42 root of a 1000000 BYTE number
750 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 22 root of THAT (469 ms)
1062 ms to take the 22 root of a 1000000 BYTE number (1047 ms) then take the square root of THAT: (15 ms)
1110 ms to take the 44 root of a 1000000 BYTE number
656 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 23 root of THAT (375 ms)
875 ms to take the 23 root of a 1000000 BYTE number (875 ms) then take the square root of THAT: (0 ms)
1047 ms to take the 46 root of a 1000000 BYTE number
812 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 24 root of THAT (531 ms)
1219 ms to take the 24 root of a 1000000 BYTE number (1219 ms) then take the square root of THAT: (0 ms)
1203 ms to take the 48 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 25 root of THAT (313 ms)
703 ms to take the 25 root of a 1000000 BYTE number (687 ms) then take the square root of THAT: (16 ms)
984 ms to take the 50 root of a 1000000 BYTE number
750 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 26 root of THAT (484 ms)
1047 ms to take the 26 root of a 1000000 BYTE number (1047 ms) then take the square root of THAT: (0 ms)
1187 ms to take the 52 root of a 1000000 BYTE number
657 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 27 root of THAT (391 ms)
875 ms to take the 27 root of a 1000000 BYTE number (875 ms) then take the square root of THAT: (0 ms)
1109 ms to take the 54 root of a 1000000 BYTE number
828 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 28 root of THAT (562 ms)
1266 ms to take the 28 root of a 1000000 BYTE number (1266 ms) then take the square root of THAT: (0 ms)
1343 ms to take the 56 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 29 root of THAT (359 ms)
782 ms to take the 29 root of a 1000000 BYTE number (782 ms) then take the square root of THAT: (0 ms)
1188 ms to take the 58 root of a 1000000 BYTE number
812 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 30 root of THAT (547 ms)
1203 ms to take the 30 root of a 1000000 BYTE number (1203 ms) then take the square root of THAT: (0 ms)
1282 ms to take the 60 root of a 1000000 BYTE number
718 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 31 root of THAT (437 ms)
1000 ms to take the 31 root of a 1000000 BYTE number (985 ms) then take the square root of THAT: (15 ms)
1266 ms to take the 62 root of a 1000000 BYTE number
938 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 32 root of THAT (657 ms)
1468 ms to take the 32 root of a 1000000 BYTE number (1468 ms) then take the square root of THAT: (0 ms)
1578 ms to take the 64 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 33 root of THAT (359 ms)
703 ms to take the 33 root of a 1000000 BYTE number (703 ms) then take the square root of THAT: (0 ms)
1094 ms to take the 66 root of a 1000000 BYTE number
812 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 34 root of THAT (515 ms)
954 ms to take the 34 root of a 1000000 BYTE number (938 ms) then take the square root of THAT: (16 ms)
1171 ms to take the 68 root of a 1000000 BYTE number
610 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 35 root of THAT (344 ms)
750 ms to take the 35 root of a 1000000 BYTE number (734 ms) then take the square root of THAT: (16 ms)
922 ms to take the 70 root of a 1000000 BYTE number
750 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 36 root of THAT (485 ms)
1047 ms to take the 36 root of a 1000000 BYTE number (1047 ms) then take the square root of THAT: (0 ms)
1156 ms to take the 72 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 37 root of THAT (313 ms)
671 ms to take the 37 root of a 1000000 BYTE number (671 ms) then take the square root of THAT: (0 ms)
907 ms to take the 74 root of a 1000000 BYTE number
718 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 38 root of THAT (437 ms)
985 ms to take the 38 root of a 1000000 BYTE number (985 ms) then take the square root of THAT: (0 ms)
1062 ms to take the 76 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 39 root of THAT (375 ms)
828 ms to take the 39 root of a 1000000 BYTE number (828 ms) then take the square root of THAT: (0 ms)
1000 ms to take the 78 root of a 1000000 BYTE number
813 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 40 root of THAT (547 ms)
1140 ms to take the 40 root of a 1000000 BYTE number (1140 ms) then take the square root of THAT: (0 ms)
1156 ms to take the 80 root of a 1000000 BYTE number
563 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 41 root of THAT (297 ms)
625 ms to take the 41 root of a 1000000 BYTE number (625 ms) then take the square root of THAT: (0 ms)
906 ms to take the 82 root of a 1000000 BYTE number
703 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 42 root of THAT (438 ms)
953 ms to take the 42 root of a 1000000 BYTE number (953 ms) then take the square root of THAT: (0 ms)
1188 ms to take the 84 root of a 1000000 BYTE number
640 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 43 root of THAT (375 ms)
797 ms to take the 43 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (0 ms)
984 ms to take the 86 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 44 root of THAT (515 ms)
1110 ms to take the 44 root of a 1000000 BYTE number (1110 ms) then take the square root of THAT: (0 ms)
1140 ms to take the 88 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 45 root of THAT (328 ms)
734 ms to take the 45 root of a 1000000 BYTE number (734 ms) then take the square root of THAT: (0 ms)
969 ms to take the 90 root of a 1000000 BYTE number
735 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 46 root of THAT (469 ms)
1062 ms to take the 46 root of a 1000000 BYTE number (1062 ms) then take the square root of THAT: (0 ms)
1109 ms to take the 92 root of a 1000000 BYTE number
672 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 47 root of THAT (390 ms)
1047 ms to take the 47 root of a 1000000 BYTE number (1047 ms) then take the square root of THAT: (0 ms)
1047 ms to take the 94 root of a 1000000 BYTE number
859 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 48 root of THAT (578 ms)
1219 ms to take the 48 root of a 1000000 BYTE number (1219 ms) then take the square root of THAT: (0 ms)
1219 ms to take the 96 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 49 root of THAT (375 ms)
906 ms to take the 49 root of a 1000000 BYTE number (906 ms) then take the square root of THAT: (0 ms)
1204 ms to take the 98 root of a 1000000 BYTE number
734 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 50 root of THAT (453 ms)
1000 ms to take the 50 root of a 1000000 BYTE number (1000 ms) then take the square root of THAT: (0 ms)
1125 ms to take the 100 root of a 1000000 BYTE number
656 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 51 root of THAT (375 ms)
828 ms to take the 51 root of a 1000000 BYTE number (828 ms) then take the square root of THAT: (0 ms)
1047 ms to take the 102 root of a 1000000 BYTE number
844 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 52 root of THAT (578 ms)
1187 ms to take the 52 root of a 1000000 BYTE number (1187 ms) then take the square root of THAT: (0 ms)
1219 ms to take the 104 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 53 root of THAT (344 ms)
735 ms to take the 53 root of a 1000000 BYTE number (735 ms) then take the square root of THAT: (0 ms)
1031 ms to take the 106 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 54 root of THAT (500 ms)
1093 ms to take the 54 root of a 1000000 BYTE number (1093 ms) then take the square root of THAT: (0 ms)
1204 ms to take the 108 root of a 1000000 BYTE number
687 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 55 root of THAT (422 ms)
906 ms to take the 55 root of a 1000000 BYTE number (906 ms) then take the square root of THAT: (0 ms)
1141 ms to take the 110 root of a 1000000 BYTE number
891 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 56 root of THAT (625 ms)
1484 ms to take the 56 root of a 1000000 BYTE number (1484 ms) then take the square root of THAT: (0 ms)
1672 ms to take the 112 root of a 1000000 BYTE number
640 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 57 root of THAT (359 ms)
766 ms to take the 57 root of a 1000000 BYTE number (766 ms) then take the square root of THAT: (0 ms)
1047 ms to take the 114 root of a 1000000 BYTE number
812 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 58 root of THAT (531 ms)
1188 ms to take the 58 root of a 1000000 BYTE number (1188 ms) then take the square root of THAT: (0 ms)
1266 ms to take the 116 root of a 1000000 BYTE number
671 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 59 root of THAT (406 ms)
938 ms to take the 59 root of a 1000000 BYTE number (938 ms) then take the square root of THAT: (0 ms)
1109 ms to take the 118 root of a 1000000 BYTE number
875 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 60 root of THAT (593 ms)
1266 ms to take the 60 root of a 1000000 BYTE number (1266 ms) then take the square root of THAT: (0 ms)
1312 ms to take the 120 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 61 root of THAT (375 ms)
797 ms to take the 61 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (0 ms)
1094 ms to take the 122 root of a 1000000 BYTE number
953 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 62 root of THAT (672 ms)
1281 ms to take the 62 root of a 1000000 BYTE number (1281 ms) then take the square root of THAT: (0 ms)
1672 ms to take the 124 root of a 1000000 BYTE number
1047 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 63 root of THAT (766 ms)
1015 ms to take the 63 root of a 1000000 BYTE number (1000 ms) then take the square root of THAT: (15 ms)
2000 ms to take the 126 root of a 1000000 BYTE number
906 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 64 root of THAT (640 ms)
1469 ms to take the 64 root of a 1000000 BYTE number (1453 ms) then take the square root of THAT: (16 ms)
1391 ms to take the 128 root of a 1000000 BYTE number
640 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 65 root of THAT (359 ms)
907 ms to take the 65 root of a 1000000 BYTE number (891 ms) then take the square root of THAT: (16 ms)
1250 ms to take the 130 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 66 root of THAT (516 ms)
1000 ms to take the 66 root of a 1000000 BYTE number (1000 ms) then take the square root of THAT: (0 ms)
1281 ms to take the 132 root of a 1000000 BYTE number
688 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 67 root of THAT (422 ms)
828 ms to take the 67 root of a 1000000 BYTE number (812 ms) then take the square root of THAT: (16 ms)
1187 ms to take the 134 root of a 1000000 BYTE number
891 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 68 root of THAT (625 ms)
1156 ms to take the 68 root of a 1000000 BYTE number (1156 ms) then take the square root of THAT: (0 ms)
1406 ms to take the 136 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 69 root of THAT (375 ms)
859 ms to take the 69 root of a 1000000 BYTE number (859 ms) then take the square root of THAT: (0 ms)
1157 ms to take the 138 root of a 1000000 BYTE number
703 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 70 root of THAT (438 ms)
937 ms to take the 70 root of a 1000000 BYTE number (937 ms) then take the square root of THAT: (0 ms)
1031 ms to take the 140 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 71 root of THAT (359 ms)
797 ms to take the 71 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (0 ms)
984 ms to take the 142 root of a 1000000 BYTE number
1000 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 72 root of THAT (718 ms)
1157 ms to take the 72 root of a 1000000 BYTE number (1157 ms) then take the square root of THAT: (0 ms)
1796 ms to take the 144 root of a 1000000 BYTE number
563 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 73 root of THAT (281 ms)
625 ms to take the 73 root of a 1000000 BYTE number (625 ms) then take the square root of THAT: (0 ms)
891 ms to take the 146 root of a 1000000 BYTE number
703 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 74 root of THAT (422 ms)
922 ms to take the 74 root of a 1000000 BYTE number (922 ms) then take the square root of THAT: (0 ms)
1031 ms to take the 148 root of a 1000000 BYTE number
640 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 75 root of THAT (375 ms)
766 ms to take the 75 root of a 1000000 BYTE number (766 ms) then take the square root of THAT: (0 ms)
953 ms to take the 150 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 76 root of THAT (500 ms)
1063 ms to take the 76 root of a 1000000 BYTE number (1063 ms) then take the square root of THAT: (0 ms)
1109 ms to take the 152 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 77 root of THAT (312 ms)
719 ms to take the 77 root of a 1000000 BYTE number (719 ms) then take the square root of THAT: (0 ms)
922 ms to take the 154 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 78 root of THAT (500 ms)
1156 ms to take the 78 root of a 1000000 BYTE number (1156 ms) then take the square root of THAT: (0 ms)
1172 ms to take the 156 root of a 1000000 BYTE number
750 ms to take the square root of a 1000000 BYTE number (328 ms) then take the 79 root of THAT (422 ms)
875 ms to take the 79 root of a 1000000 BYTE number (875 ms) then take the square root of THAT: (0 ms)
1047 ms to take the 158 root of a 1000000 BYTE number
812 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 80 root of THAT (546 ms)
1172 ms to take the 80 root of a 1000000 BYTE number (1172 ms) then take the square root of THAT: (0 ms)
1157 ms to take the 160 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 81 root of THAT (297 ms)
609 ms to take the 81 root of a 1000000 BYTE number (609 ms) then take the square root of THAT: (0 ms)
938 ms to take the 162 root of a 1000000 BYTE number
687 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 82 root of THAT (406 ms)
891 ms to take the 82 root of a 1000000 BYTE number (891 ms) then take the square root of THAT: (0 ms)
984 ms to take the 164 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 83 root of THAT (453 ms)
1140 ms to take the 83 root of a 1000000 BYTE number (1140 ms) then take the square root of THAT: (0 ms)
1266 ms to take the 166 root of a 1000000 BYTE number
844 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 84 root of THAT (563 ms)
1187 ms to take the 84 root of a 1000000 BYTE number (1187 ms) then take the square root of THAT: (0 ms)
1532 ms to take the 168 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 85 root of THAT (313 ms)
765 ms to take the 85 root of a 1000000 BYTE number (765 ms) then take the square root of THAT: (0 ms)
907 ms to take the 170 root of a 1000000 BYTE number
718 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 86 root of THAT (437 ms)
985 ms to take the 86 root of a 1000000 BYTE number (985 ms) then take the square root of THAT: (0 ms)
1047 ms to take the 172 root of a 1000000 BYTE number
640 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 87 root of THAT (375 ms)
828 ms to take the 87 root of a 1000000 BYTE number (828 ms) then take the square root of THAT: (0 ms)
969 ms to take the 174 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 88 root of THAT (516 ms)
1141 ms to take the 88 root of a 1000000 BYTE number (1141 ms) then take the square root of THAT: (0 ms)
1109 ms to take the 176 root of a 1000000 BYTE number
562 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 89 root of THAT (281 ms)
657 ms to take the 89 root of a 1000000 BYTE number (657 ms) then take the square root of THAT: (0 ms)
890 ms to take the 178 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 90 root of THAT (437 ms)
953 ms to take the 90 root of a 1000000 BYTE number (953 ms) then take the square root of THAT: (0 ms)
1047 ms to take the 180 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 91 root of THAT (359 ms)
828 ms to take the 91 root of a 1000000 BYTE number (828 ms) then take the square root of THAT: (0 ms)
953 ms to take the 182 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 92 root of THAT (500 ms)
1125 ms to take the 92 root of a 1000000 BYTE number (1125 ms) then take the square root of THAT: (0 ms)
1110 ms to take the 184 root of a 1000000 BYTE number
812 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 93 root of THAT (547 ms)
1141 ms to take the 93 root of a 1000000 BYTE number (1141 ms) then take the square root of THAT: (0 ms)
1609 ms to take the 186 root of a 1000000 BYTE number
750 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 94 root of THAT (484 ms)
1047 ms to take the 94 root of a 1000000 BYTE number (1047 ms) then take the square root of THAT: (0 ms)
1094 ms to take the 188 root of a 1000000 BYTE number
672 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 95 root of THAT (407 ms)
890 ms to take the 95 root of a 1000000 BYTE number (890 ms) then take the square root of THAT: (0 ms)
1016 ms to take the 190 root of a 1000000 BYTE number
1047 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 96 root of THAT (766 ms)
1218 ms to take the 96 root of a 1000000 BYTE number (1218 ms) then take the square root of THAT: (0 ms)
1641 ms to take the 192 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 97 root of THAT (281 ms)
625 ms to take the 97 root of a 1000000 BYTE number (625 ms) then take the square root of THAT: (0 ms)
906 ms to take the 194 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 98 root of THAT (438 ms)
1219 ms to take the 98 root of a 1000000 BYTE number (1219 ms) then take the square root of THAT: (0 ms)
1093 ms to take the 196 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 99 root of THAT (359 ms)
797 ms to take the 99 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (0 ms)
953 ms to take the 198 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 100 root of THAT (515 ms)
1110 ms to take the 100 root of a 1000000 BYTE number (1110 ms) then take the square root of THAT: (0 ms)
1125 ms to take the 200 root of a 1000000 BYTE number
593 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 101 root of THAT (312 ms)
703 ms to take the 101 root of a 1000000 BYTE number (703 ms) then take the square root of THAT: (0 ms)
1016 ms to take the 202 root of a 1000000 BYTE number
828 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 102 root of THAT (547 ms)
1156 ms to take the 102 root of a 1000000 BYTE number (1156 ms) then take the square root of THAT: (0 ms)
1172 ms to take the 204 root of a 1000000 BYTE number
703 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 103 root of THAT (437 ms)
1110 ms to take the 103 root of a 1000000 BYTE number (1110 ms) then take the square root of THAT: (0 ms)
1000 ms to take the 206 root of a 1000000 BYTE number
828 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 104 root of THAT (547 ms)
1219 ms to take the 104 root of a 1000000 BYTE number (1203 ms) then take the square root of THAT: (16 ms)
1156 ms to take the 208 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 105 root of THAT (312 ms)
672 ms to take the 105 root of a 1000000 BYTE number (672 ms) then take the square root of THAT: (0 ms)
937 ms to take the 210 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 106 root of THAT (453 ms)
1016 ms to take the 106 root of a 1000000 BYTE number (1016 ms) then take the square root of THAT: (0 ms)
1078 ms to take the 212 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 107 root of THAT (516 ms)
844 ms to take the 107 root of a 1000000 BYTE number (844 ms) then take the square root of THAT: (0 ms)
1235 ms to take the 214 root of a 1000000 BYTE number
812 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 108 root of THAT (531 ms)
1188 ms to take the 108 root of a 1000000 BYTE number (1188 ms) then take the square root of THAT: (0 ms)
1187 ms to take the 216 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 109 root of THAT (360 ms)
765 ms to take the 109 root of a 1000000 BYTE number (765 ms) then take the square root of THAT: (0 ms)
969 ms to take the 218 root of a 1000000 BYTE number
766 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 110 root of THAT (500 ms)
1125 ms to take the 110 root of a 1000000 BYTE number (1125 ms) then take the square root of THAT: (0 ms)
1140 ms to take the 220 root of a 1000000 BYTE number
844 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 111 root of THAT (578 ms)
1172 ms to take the 111 root of a 1000000 BYTE number (1172 ms) then take the square root of THAT: (0 ms)
1469 ms to take the 222 root of a 1000000 BYTE number
1125 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 112 root of THAT (860 ms)
1547 ms to take the 112 root of a 1000000 BYTE number (1547 ms) then take the square root of THAT: (0 ms)
1781 ms to take the 224 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 113 root of THAT (313 ms)
656 ms to take the 113 root of a 1000000 BYTE number (656 ms) then take the square root of THAT: (0 ms)
953 ms to take the 226 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 114 root of THAT (484 ms)
1016 ms to take the 114 root of a 1000000 BYTE number (1016 ms) then take the square root of THAT: (0 ms)
1109 ms to take the 228 root of a 1000000 BYTE number
656 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 115 root of THAT (375 ms)
860 ms to take the 115 root of a 1000000 BYTE number (860 ms) then take the square root of THAT: (0 ms)
1031 ms to take the 230 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 116 root of THAT (531 ms)
1281 ms to take the 116 root of a 1000000 BYTE number (1281 ms) then take the square root of THAT: (0 ms)
1203 ms to take the 232 root of a 1000000 BYTE number
610 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 117 root of THAT (328 ms)
797 ms to take the 117 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (0 ms)
1000 ms to take the 234 root of a 1000000 BYTE number
765 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 118 root of THAT (484 ms)
1156 ms to take the 118 root of a 1000000 BYTE number (1156 ms) then take the square root of THAT: (0 ms)
1172 ms to take the 236 root of a 1000000 BYTE number
688 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 119 root of THAT (422 ms)
953 ms to take the 119 root of a 1000000 BYTE number (953 ms) then take the square root of THAT: (0 ms)
1078 ms to take the 238 root of a 1000000 BYTE number
859 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 120 root of THAT (593 ms)
1329 ms to take the 120 root of a 1000000 BYTE number (1329 ms) then take the square root of THAT: (0 ms)
1250 ms to take the 240 root of a 1000000 BYTE number
593 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 121 root of THAT (328 ms)
969 ms to take the 121 root of a 1000000 BYTE number (969 ms) then take the square root of THAT: (0 ms)
1016 ms to take the 242 root of a 1000000 BYTE number
765 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 122 root of THAT (500 ms)
1094 ms to take the 122 root of a 1000000 BYTE number (1094 ms) then take the square root of THAT: (0 ms)
1172 ms to take the 244 root of a 1000000 BYTE number
766 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 123 root of THAT (500 ms)
921 ms to take the 123 root of a 1000000 BYTE number (921 ms) then take the square root of THAT: (0 ms)
1204 ms to take the 246 root of a 1000000 BYTE number
1375 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 124 root of THAT (1094 ms)
1812 ms to take the 124 root of a 1000000 BYTE number (1812 ms) then take the square root of THAT: (0 ms)
2266 ms to take the 248 root of a 1000000 BYTE number
687 ms to take the square root of a 1000000 BYTE number (312 ms) then take the 125 root of THAT (375 ms)
813 ms to take the 125 root of a 1000000 BYTE number (813 ms) then take the square root of THAT: (0 ms)
1078 ms to take the 250 root of a 1000000 BYTE number
1187 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 126 root of THAT (906 ms)
2016 ms to take the 126 root of a 1000000 BYTE number (2016 ms) then take the square root of THAT: (0 ms)
2094 ms to take the 252 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 127 root of THAT (500 ms)
1016 ms to take the 127 root of a 1000000 BYTE number (1016 ms) then take the square root of THAT: (0 ms)
1234 ms to take the 254 root of a 1000000 BYTE number
891 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 128 root of THAT (625 ms)
1406 ms to take the 128 root of a 1000000 BYTE number (1406 ms) then take the square root of THAT: (0 ms)
1328 ms to take the 256 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 129 root of THAT (312 ms)
672 ms to take the 129 root of a 1000000 BYTE number (672 ms) then take the square root of THAT: (0 ms)
1016 ms to take the 258 root of a 1000000 BYTE number
765 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 130 root of THAT (500 ms)
1281 ms to take the 130 root of a 1000000 BYTE number (1281 ms) then take the square root of THAT: (0 ms)
1188 ms to take the 260 root of a 1000000 BYTE number
859 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 131 root of THAT (593 ms)
891 ms to take the 131 root of a 1000000 BYTE number (891 ms) then take the square root of THAT: (0 ms)
1375 ms to take the 262 root of a 1000000 BYTE number
844 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 132 root of THAT (578 ms)
1281 ms to take the 132 root of a 1000000 BYTE number (1281 ms) then take the square root of THAT: (0 ms)
1297 ms to take the 264 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 133 root of THAT (360 ms)
859 ms to take the 133 root of a 1000000 BYTE number (859 ms) then take the square root of THAT: (0 ms)
1266 ms to take the 266 root of a 1000000 BYTE number
828 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 134 root of THAT (547 ms)
1219 ms to take the 134 root of a 1000000 BYTE number (1219 ms) then take the square root of THAT: (0 ms)
1250 ms to take the 268 root of a 1000000 BYTE number
718 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 135 root of THAT (437 ms)
985 ms to take the 135 root of a 1000000 BYTE number (985 ms) then take the square root of THAT: (0 ms)
1265 ms to take the 270 root of a 1000000 BYTE number
1110 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 136 root of THAT (844 ms)
1750 ms to take the 136 root of a 1000000 BYTE number (1750 ms) then take the square root of THAT: (0 ms)
1781 ms to take the 272 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 137 root of THAT (344 ms)
813 ms to take the 137 root of a 1000000 BYTE number (813 ms) then take the square root of THAT: (0 ms)
1171 ms to take the 274 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 138 root of THAT (515 ms)
1172 ms to take the 138 root of a 1000000 BYTE number (1172 ms) then take the square root of THAT: (0 ms)
1250 ms to take the 276 root of a 1000000 BYTE number
703 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 139 root of THAT (422 ms)
969 ms to take the 139 root of a 1000000 BYTE number (969 ms) then take the square root of THAT: (0 ms)
1172 ms to take the 278 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 140 root of THAT (531 ms)
1031 ms to take the 140 root of a 1000000 BYTE number (1031 ms) then take the square root of THAT: (0 ms)
1188 ms to take the 280 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 141 root of THAT (344 ms)
828 ms to take the 141 root of a 1000000 BYTE number (828 ms) then take the square root of THAT: (0 ms)
968 ms to take the 282 root of a 1000000 BYTE number
813 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 142 root of THAT (531 ms)
984 ms to take the 142 root of a 1000000 BYTE number (984 ms) then take the square root of THAT: (0 ms)
1125 ms to take the 284 root of a 1000000 BYTE number
828 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 143 root of THAT (546 ms)
922 ms to take the 143 root of a 1000000 BYTE number (922 ms) then take the square root of THAT: (0 ms)
1375 ms to take the 286 root of a 1000000 BYTE number
1157 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 144 root of THAT (860 ms)
1921 ms to take the 144 root of a 1000000 BYTE number (1921 ms) then take the square root of THAT: (0 ms)
2000 ms to take the 288 root of a 1000000 BYTE number
688 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 145 root of THAT (406 ms)
969 ms to take the 145 root of a 1000000 BYTE number (969 ms) then take the square root of THAT: (0 ms)
1281 ms to take the 290 root of a 1000000 BYTE number
984 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 146 root of THAT (703 ms)
875 ms to take the 146 root of a 1000000 BYTE number (875 ms) then take the square root of THAT: (0 ms)
1687 ms to take the 292 root of a 1000000 BYTE number
657 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 147 root of THAT (375 ms)
734 ms to take the 147 root of a 1000000 BYTE number (734 ms) then take the square root of THAT: (0 ms)
1031 ms to take the 294 root of a 1000000 BYTE number
813 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 148 root of THAT (547 ms)
1125 ms to take the 148 root of a 1000000 BYTE number (1125 ms) then take the square root of THAT: (0 ms)
1187 ms to take the 296 root of a 1000000 BYTE number
610 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 149 root of THAT (344 ms)
672 ms to take the 149 root of a 1000000 BYTE number (672 ms) then take the square root of THAT: (0 ms)
984 ms to take the 298 root of a 1000000 BYTE number
766 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 150 root of THAT (500 ms)
968 ms to take the 150 root of a 1000000 BYTE number (968 ms) then take the square root of THAT: (0 ms)
1157 ms to take the 300 root of a 1000000 BYTE number
687 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 151 root of THAT (422 ms)
813 ms to take the 151 root of a 1000000 BYTE number (813 ms) then take the square root of THAT: (0 ms)
1078 ms to take the 302 root of a 1000000 BYTE number
875 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 152 root of THAT (610 ms)
1125 ms to take the 152 root of a 1000000 BYTE number (1125 ms) then take the square root of THAT: (0 ms)
1250 ms to take the 304 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 153 root of THAT (344 ms)
656 ms to take the 153 root of a 1000000 BYTE number (656 ms) then take the square root of THAT: (0 ms)
1000 ms to take the 306 root of a 1000000 BYTE number
766 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 154 root of THAT (485 ms)
953 ms to take the 154 root of a 1000000 BYTE number (953 ms) then take the square root of THAT: (0 ms)
1140 ms to take the 308 root of a 1000000 BYTE number
688 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 155 root of THAT (406 ms)
797 ms to take the 155 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (0 ms)
1062 ms to take the 310 root of a 1000000 BYTE number
860 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 156 root of THAT (579 ms)
1093 ms to take the 156 root of a 1000000 BYTE number (1093 ms) then take the square root of THAT: (0 ms)
1235 ms to take the 312 root of a 1000000 BYTE number
718 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 157 root of THAT (453 ms)
750 ms to take the 157 root of a 1000000 BYTE number (750 ms) then take the square root of THAT: (0 ms)
1313 ms to take the 314 root of a 1000000 BYTE number
1000 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 158 root of THAT (719 ms)
1031 ms to take the 158 root of a 1000000 BYTE number (1031 ms) then take the square root of THAT: (0 ms)
1641 ms to take the 316 root of a 1000000 BYTE number
859 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 159 root of THAT (578 ms)
891 ms to take the 159 root of a 1000000 BYTE number (875 ms) then take the square root of THAT: (16 ms)
1437 ms to take the 318 root of a 1000000 BYTE number
938 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 160 root of THAT (656 ms)
1187 ms to take the 160 root of a 1000000 BYTE number (1187 ms) then take the square root of THAT: (0 ms)
1328 ms to take the 320 root of a 1000000 BYTE number
579 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 161 root of THAT (313 ms)
625 ms to take the 161 root of a 1000000 BYTE number (625 ms) then take the square root of THAT: (0 ms)
984 ms to take the 322 root of a 1000000 BYTE number
750 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 162 root of THAT (469 ms)
953 ms to take the 162 root of a 1000000 BYTE number (953 ms) then take the square root of THAT: (0 ms)
1172 ms to take the 324 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 163 root of THAT (359 ms)
781 ms to take the 163 root of a 1000000 BYTE number (781 ms) then take the square root of THAT: (0 ms)
953 ms to take the 326 root of a 1000000 BYTE number
844 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 164 root of THAT (547 ms)
984 ms to take the 164 root of a 1000000 BYTE number (984 ms) then take the square root of THAT: (0 ms)
1485 ms to take the 328 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 165 root of THAT (297 ms)
828 ms to take the 165 root of a 1000000 BYTE number (828 ms) then take the square root of THAT: (0 ms)
859 ms to take the 330 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 166 root of THAT (422 ms)
1469 ms to take the 166 root of a 1000000 BYTE number (1469 ms) then take the square root of THAT: (0 ms)
1062 ms to take the 332 root of a 1000000 BYTE number
656 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 167 root of THAT (375 ms)
922 ms to take the 167 root of a 1000000 BYTE number (922 ms) then take the square root of THAT: (0 ms)
1000 ms to take the 334 root of a 1000000 BYTE number
906 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 168 root of THAT (640 ms)
1547 ms to take the 168 root of a 1000000 BYTE number (1547 ms) then take the square root of THAT: (0 ms)
1375 ms to take the 336 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 169 root of THAT (296 ms)
610 ms to take the 169 root of a 1000000 BYTE number (610 ms) then take the square root of THAT: (0 ms)
844 ms to take the 338 root of a 1000000 BYTE number
703 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 170 root of THAT (422 ms)
906 ms to take the 170 root of a 1000000 BYTE number (906 ms) then take the square root of THAT: (0 ms)
969 ms to take the 340 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 171 root of THAT (343 ms)
766 ms to take the 171 root of a 1000000 BYTE number (766 ms) then take the square root of THAT: (0 ms)
906 ms to take the 342 root of a 1000000 BYTE number
766 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 172 root of THAT (485 ms)
1062 ms to take the 172 root of a 1000000 BYTE number (1062 ms) then take the square root of THAT: (0 ms)
1063 ms to take the 344 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 173 root of THAT (329 ms)
781 ms to take the 173 root of a 1000000 BYTE number (781 ms) then take the square root of THAT: (0 ms)
890 ms to take the 346 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 174 root of THAT (453 ms)
1000 ms to take the 174 root of a 1000000 BYTE number (1000 ms) then take the square root of THAT: (0 ms)
1016 ms to take the 348 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 175 root of THAT (484 ms)
844 ms to take the 175 root of a 1000000 BYTE number (844 ms) then take the square root of THAT: (0 ms)
1094 ms to take the 350 root of a 1000000 BYTE number
875 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 176 root of THAT (594 ms)
1140 ms to take the 176 root of a 1000000 BYTE number (1140 ms) then take the square root of THAT: (0 ms)
1250 ms to take the 352 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 177 root of THAT (281 ms)
610 ms to take the 177 root of a 1000000 BYTE number (610 ms) then take the square root of THAT: (0 ms)
968 ms to take the 354 root of a 1000000 BYTE number
704 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 178 root of THAT (422 ms)
921 ms to take the 178 root of a 1000000 BYTE number (921 ms) then take the square root of THAT: (0 ms)
1032 ms to take the 356 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 179 root of THAT (344 ms)
750 ms to take the 179 root of a 1000000 BYTE number (750 ms) then take the square root of THAT: (0 ms)
937 ms to take the 358 root of a 1000000 BYTE number
750 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 180 root of THAT (484 ms)
1063 ms to take the 180 root of a 1000000 BYTE number (1063 ms) then take the square root of THAT: (0 ms)
1062 ms to take the 360 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 181 root of THAT (313 ms)
719 ms to take the 181 root of a 1000000 BYTE number (719 ms) then take the square root of THAT: (0 ms)
890 ms to take the 362 root of a 1000000 BYTE number
735 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 182 root of THAT (453 ms)
968 ms to take the 182 root of a 1000000 BYTE number (968 ms) then take the square root of THAT: (0 ms)
1063 ms to take the 364 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 183 root of THAT (453 ms)
875 ms to take the 183 root of a 1000000 BYTE number (875 ms) then take the square root of THAT: (0 ms)
1140 ms to take the 366 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 184 root of THAT (515 ms)
1125 ms to take the 184 root of a 1000000 BYTE number (1125 ms) then take the square root of THAT: (0 ms)
1110 ms to take the 368 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 185 root of THAT (313 ms)
657 ms to take the 185 root of a 1000000 BYTE number (657 ms) then take the square root of THAT: (0 ms)
890 ms to take the 370 root of a 1000000 BYTE number
1016 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 186 root of THAT (735 ms)
1610 ms to take the 186 root of a 1000000 BYTE number (1610 ms) then take the square root of THAT: (0 ms)
1765 ms to take the 372 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 187 root of THAT (359 ms)
813 ms to take the 187 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (16 ms)
953 ms to take the 374 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 188 root of THAT (500 ms)
1109 ms to take the 188 root of a 1000000 BYTE number (1109 ms) then take the square root of THAT: (0 ms)
1110 ms to take the 376 root of a 1000000 BYTE number
609 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 189 root of THAT (328 ms)
718 ms to take the 189 root of a 1000000 BYTE number (718 ms) then take the square root of THAT: (0 ms)
1016 ms to take the 378 root of a 1000000 BYTE number
750 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 190 root of THAT (469 ms)
1109 ms to take the 190 root of a 1000000 BYTE number (1109 ms) then take the square root of THAT: (0 ms)
1188 ms to take the 380 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 191 root of THAT (438 ms)
906 ms to take the 191 root of a 1000000 BYTE number (906 ms) then take the square root of THAT: (0 ms)
1062 ms to take the 382 root of a 1000000 BYTE number
922 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 192 root of THAT (656 ms)
1719 ms to take the 192 root of a 1000000 BYTE number (1719 ms) then take the square root of THAT: (0 ms)
1406 ms to take the 384 root of a 1000000 BYTE number
547 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 193 root of THAT (281 ms)
610 ms to take the 193 root of a 1000000 BYTE number (610 ms) then take the square root of THAT: (0 ms)
875 ms to take the 386 root of a 1000000 BYTE number
703 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 194 root of THAT (422 ms)
922 ms to take the 194 root of a 1000000 BYTE number (922 ms) then take the square root of THAT: (0 ms)
1109 ms to take the 388 root of a 1000000 BYTE number
672 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 195 root of THAT (391 ms)
1031 ms to take the 195 root of a 1000000 BYTE number (1031 ms) then take the square root of THAT: (0 ms)
938 ms to take the 390 root of a 1000000 BYTE number
765 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 196 root of THAT (484 ms)
1078 ms to take the 196 root of a 1000000 BYTE number (1078 ms) then take the square root of THAT: (0 ms)
1110 ms to take the 392 root of a 1000000 BYTE number
593 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 197 root of THAT (312 ms)
750 ms to take the 197 root of a 1000000 BYTE number (750 ms) then take the square root of THAT: (0 ms)
922 ms to take the 394 root of a 1000000 BYTE number
703 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 198 root of THAT (421 ms)
985 ms to take the 198 root of a 1000000 BYTE number (985 ms) then take the square root of THAT: (0 ms)
1000 ms to take the 396 root of a 1000000 BYTE number
859 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 199 root of THAT (594 ms)
860 ms to take the 199 root of a 1000000 BYTE number (860 ms) then take the square root of THAT: (0 ms)
1531 ms to take the 398 root of a 1000000 BYTE number
765 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 200 root of THAT (484 ms)
1125 ms to take the 200 root of a 1000000 BYTE number (1125 ms) then take the square root of THAT: (0 ms)
1094 ms to take the 400 root of a 1000000 BYTE number
562 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 201 root of THAT (281 ms)
625 ms to take the 201 root of a 1000000 BYTE number (625 ms) then take the square root of THAT: (0 ms)
844 ms to take the 402 root of a 1000000 BYTE number
688 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 202 root of THAT (407 ms)
953 ms to take the 202 root of a 1000000 BYTE number (953 ms) then take the square root of THAT: (0 ms)
968 ms to take the 404 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 203 root of THAT (359 ms)
797 ms to take the 203 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (0 ms)
953 ms to take the 406 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 204 root of THAT (515 ms)
1110 ms to take the 204 root of a 1000000 BYTE number (1110 ms) then take the square root of THAT: (0 ms)
1031 ms to take the 408 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 205 root of THAT (313 ms)
734 ms to take the 205 root of a 1000000 BYTE number (734 ms) then take the square root of THAT: (0 ms)
875 ms to take the 410 root of a 1000000 BYTE number
734 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 206 root of THAT (453 ms)
1016 ms to take the 206 root of a 1000000 BYTE number (1016 ms) then take the square root of THAT: (0 ms)
1016 ms to take the 412 root of a 1000000 BYTE number
656 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 207 root of THAT (391 ms)
859 ms to take the 207 root of a 1000000 BYTE number (859 ms) then take the square root of THAT: (0 ms)
938 ms to take the 414 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 208 root of THAT (500 ms)
1188 ms to take the 208 root of a 1000000 BYTE number (1188 ms) then take the square root of THAT: (0 ms)
1078 ms to take the 416 root of a 1000000 BYTE number
656 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 209 root of THAT (391 ms)
875 ms to take the 209 root of a 1000000 BYTE number (875 ms) then take the square root of THAT: (0 ms)
1250 ms to take the 418 root of a 1000000 BYTE number
703 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 210 root of THAT (422 ms)
938 ms to take the 210 root of a 1000000 BYTE number (938 ms) then take the square root of THAT: (0 ms)
984 ms to take the 420 root of a 1000000 BYTE number
609 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 211 root of THAT (343 ms)
782 ms to take the 211 root of a 1000000 BYTE number (782 ms) then take the square root of THAT: (0 ms)
906 ms to take the 422 root of a 1000000 BYTE number
765 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 212 root of THAT (484 ms)
1110 ms to take the 212 root of a 1000000 BYTE number (1110 ms) then take the square root of THAT: (0 ms)
1047 ms to take the 424 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 213 root of THAT (313 ms)
703 ms to take the 213 root of a 1000000 BYTE number (703 ms) then take the square root of THAT: (0 ms)
891 ms to take the 426 root of a 1000000 BYTE number
1031 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 214 root of THAT (766 ms)
1265 ms to take the 214 root of a 1000000 BYTE number (1265 ms) then take the square root of THAT: (0 ms)
1954 ms to take the 428 root of a 1000000 BYTE number
687 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 215 root of THAT (406 ms)
938 ms to take the 215 root of a 1000000 BYTE number (938 ms) then take the square root of THAT: (0 ms)
985 ms to take the 430 root of a 1000000 BYTE number
813 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 216 root of THAT (547 ms)
1187 ms to take the 216 root of a 1000000 BYTE number (1187 ms) then take the square root of THAT: (0 ms)
1078 ms to take the 432 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 217 root of THAT (515 ms)
1078 ms to take the 217 root of a 1000000 BYTE number (1078 ms) then take the square root of THAT: (0 ms)
1500 ms to take the 434 root of a 1000000 BYTE number
703 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 218 root of THAT (437 ms)
985 ms to take the 218 root of a 1000000 BYTE number (985 ms) then take the square root of THAT: (0 ms)
1015 ms to take the 436 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 219 root of THAT (375 ms)
828 ms to take the 219 root of a 1000000 BYTE number (828 ms) then take the square root of THAT: (0 ms)
938 ms to take the 438 root of a 1000000 BYTE number
1031 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 220 root of THAT (734 ms)
1172 ms to take the 220 root of a 1000000 BYTE number (1172 ms) then take the square root of THAT: (0 ms)
1672 ms to take the 440 root of a 1000000 BYTE number
609 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 221 root of THAT (344 ms)
750 ms to take the 221 root of a 1000000 BYTE number (750 ms) then take the square root of THAT: (0 ms)
906 ms to take the 442 root of a 1000000 BYTE number
844 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 222 root of THAT (562 ms)
1500 ms to take the 222 root of a 1000000 BYTE number (1484 ms) then take the square root of THAT: (16 ms)
1266 ms to take the 444 root of a 1000000 BYTE number
687 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 223 root of THAT (406 ms)
906 ms to take the 223 root of a 1000000 BYTE number (906 ms) then take the square root of THAT: (0 ms)
985 ms to take the 446 root of a 1000000 BYTE number
1109 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 224 root of THAT (828 ms)
1797 ms to take the 224 root of a 1000000 BYTE number (1797 ms) then take the square root of THAT: (0 ms)
1688 ms to take the 448 root of a 1000000 BYTE number
562 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 225 root of THAT (281 ms)
781 ms to take the 225 root of a 1000000 BYTE number (781 ms) then take the square root of THAT: (0 ms)
875 ms to take the 450 root of a 1000000 BYTE number
703 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 226 root of THAT (421 ms)
969 ms to take the 226 root of a 1000000 BYTE number (969 ms) then take the square root of THAT: (0 ms)
1016 ms to take the 452 root of a 1000000 BYTE number
640 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 227 root of THAT (359 ms)
829 ms to take the 227 root of a 1000000 BYTE number (829 ms) then take the square root of THAT: (0 ms)
1015 ms to take the 454 root of a 1000000 BYTE number
844 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 228 root of THAT (547 ms)
1109 ms to take the 228 root of a 1000000 BYTE number (1109 ms) then take the square root of THAT: (0 ms)
1157 ms to take the 456 root of a 1000000 BYTE number
593 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 229 root of THAT (312 ms)
719 ms to take the 229 root of a 1000000 BYTE number (719 ms) then take the square root of THAT: (0 ms)
922 ms to take the 458 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 230 root of THAT (453 ms)
1047 ms to take the 230 root of a 1000000 BYTE number (1047 ms) then take the square root of THAT: (0 ms)
1062 ms to take the 460 root of a 1000000 BYTE number
688 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 231 root of THAT (422 ms)
890 ms to take the 231 root of a 1000000 BYTE number (890 ms) then take the square root of THAT: (0 ms)
1031 ms to take the 462 root of a 1000000 BYTE number
813 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 232 root of THAT (531 ms)
1219 ms to take the 232 root of a 1000000 BYTE number (1219 ms) then take the square root of THAT: (0 ms)
1140 ms to take the 464 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 233 root of THAT (296 ms)
672 ms to take the 233 root of a 1000000 BYTE number (672 ms) then take the square root of THAT: (0 ms)
907 ms to take the 466 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 234 root of THAT (500 ms)
1000 ms to take the 234 root of a 1000000 BYTE number (1000 ms) then take the square root of THAT: (0 ms)
1265 ms to take the 468 root of a 1000000 BYTE number
657 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 235 root of THAT (391 ms)
828 ms to take the 235 root of a 1000000 BYTE number (828 ms) then take the square root of THAT: (0 ms)
1000 ms to take the 470 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 236 root of THAT (516 ms)
1187 ms to take the 236 root of a 1000000 BYTE number (1187 ms) then take the square root of THAT: (0 ms)
1141 ms to take the 472 root of a 1000000 BYTE number
656 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 237 root of THAT (375 ms)
859 ms to take the 237 root of a 1000000 BYTE number (859 ms) then take the square root of THAT: (0 ms)
1000 ms to take the 474 root of a 1000000 BYTE number
829 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 238 root of THAT (563 ms)
1156 ms to take the 238 root of a 1000000 BYTE number (1156 ms) then take the square root of THAT: (0 ms)
1140 ms to take the 476 root of a 1000000 BYTE number
688 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 239 root of THAT (422 ms)
1359 ms to take the 239 root of a 1000000 BYTE number (1359 ms) then take the square root of THAT: (0 ms)
1094 ms to take the 478 root of a 1000000 BYTE number
828 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 240 root of THAT (547 ms)
1281 ms to take the 240 root of a 1000000 BYTE number (1281 ms) then take the square root of THAT: (0 ms)
1204 ms to take the 480 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 241 root of THAT (297 ms)
672 ms to take the 241 root of a 1000000 BYTE number (672 ms) then take the square root of THAT: (0 ms)
890 ms to take the 482 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 242 root of THAT (438 ms)
1031 ms to take the 242 root of a 1000000 BYTE number (1031 ms) then take the square root of THAT: (0 ms)
1063 ms to take the 484 root of a 1000000 BYTE number
640 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 243 root of THAT (375 ms)
844 ms to take the 243 root of a 1000000 BYTE number (844 ms) then take the square root of THAT: (0 ms)
984 ms to take the 486 root of a 1000000 BYTE number
782 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 244 root of THAT (516 ms)
1187 ms to take the 244 root of a 1000000 BYTE number (1187 ms) then take the square root of THAT: (0 ms)
1219 ms to take the 488 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 245 root of THAT (516 ms)
781 ms to take the 245 root of a 1000000 BYTE number (781 ms) then take the square root of THAT: (0 ms)
1469 ms to take the 490 root of a 1000000 BYTE number
1078 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 246 root of THAT (813 ms)
1219 ms to take the 246 root of a 1000000 BYTE number (1219 ms) then take the square root of THAT: (0 ms)
1890 ms to take the 492 root of a 1000000 BYTE number
875 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 247 root of THAT (593 ms)
1453 ms to take the 247 root of a 1000000 BYTE number (1453 ms) then take the square root of THAT: (0 ms)
1532 ms to take the 494 root of a 1000000 BYTE number
1234 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 248 root of THAT (953 ms)
2188 ms to take the 248 root of a 1000000 BYTE number (2172 ms) then take the square root of THAT: (16 ms)
2046 ms to take the 496 root of a 1000000 BYTE number
735 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 249 root of THAT (469 ms)
1078 ms to take the 249 root of a 1000000 BYTE number (1078 ms) then take the square root of THAT: (0 ms)
1406 ms to take the 498 root of a 1000000 BYTE number
750 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 250 root of THAT (485 ms)
1062 ms to take the 250 root of a 1000000 BYTE number (1062 ms) then take the square root of THAT: (0 ms)
1110 ms to take the 500 root of a 1000000 BYTE number
687 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 251 root of THAT (406 ms)
1360 ms to take the 251 root of a 1000000 BYTE number (1360 ms) then take the square root of THAT: (0 ms)
1031 ms to take the 502 root of a 1000000 BYTE number
1219 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 252 root of THAT (954 ms)
2109 ms to take the 252 root of a 1000000 BYTE number (2109 ms) then take the square root of THAT: (0 ms)
2031 ms to take the 504 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 253 root of THAT (516 ms)
1250 ms to take the 253 root of a 1000000 BYTE number (1250 ms) then take the square root of THAT: (0 ms)
1500 ms to take the 506 root of a 1000000 BYTE number
1125 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 254 root of THAT (844 ms)
1234 ms to take the 254 root of a 1000000 BYTE number (1234 ms) then take the square root of THAT: (0 ms)
1938 ms to take the 508 root of a 1000000 BYTE number
906 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 255 root of THAT (625 ms)
1016 ms to take the 255 root of a 1000000 BYTE number (1016 ms) then take the square root of THAT: (0 ms)
1578 ms to take the 510 root of a 1000000 BYTE number
891 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 256 root of THAT (610 ms)
1484 ms to take the 256 root of a 1000000 BYTE number (1484 ms) then take the square root of THAT: (0 ms)
1375 ms to take the 512 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 257 root of THAT (297 ms)
688 ms to take the 257 root of a 1000000 BYTE number (688 ms) then take the square root of THAT: (0 ms)
984 ms to take the 514 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 258 root of THAT (453 ms)
1000 ms to take the 258 root of a 1000000 BYTE number (1000 ms) then take the square root of THAT: (0 ms)
1078 ms to take the 516 root of a 1000000 BYTE number
640 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 259 root of THAT (359 ms)
891 ms to take the 259 root of a 1000000 BYTE number (875 ms) then take the square root of THAT: (16 ms)
1000 ms to take the 518 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 260 root of THAT (531 ms)
1203 ms to take the 260 root of a 1000000 BYTE number (1203 ms) then take the square root of THAT: (0 ms)
1172 ms to take the 520 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 261 root of THAT (328 ms)
766 ms to take the 261 root of a 1000000 BYTE number (766 ms) then take the square root of THAT: (0 ms)
968 ms to take the 522 root of a 1000000 BYTE number
782 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 262 root of THAT (516 ms)
1406 ms to take the 262 root of a 1000000 BYTE number (1406 ms) then take the square root of THAT: (0 ms)
1187 ms to take the 524 root of a 1000000 BYTE number
688 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 263 root of THAT (406 ms)
922 ms to take the 263 root of a 1000000 BYTE number (922 ms) then take the square root of THAT: (0 ms)
1062 ms to take the 526 root of a 1000000 BYTE number
844 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 264 root of THAT (563 ms)
1312 ms to take the 264 root of a 1000000 BYTE number (1312 ms) then take the square root of THAT: (0 ms)
1219 ms to take the 528 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 265 root of THAT (312 ms)
703 ms to take the 265 root of a 1000000 BYTE number (703 ms) then take the square root of THAT: (0 ms)
953 ms to take the 530 root of a 1000000 BYTE number
750 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 266 root of THAT (469 ms)
1063 ms to take the 266 root of a 1000000 BYTE number (1063 ms) then take the square root of THAT: (0 ms)
1125 ms to take the 532 root of a 1000000 BYTE number
844 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 267 root of THAT (562 ms)
891 ms to take the 267 root of a 1000000 BYTE number (891 ms) then take the square root of THAT: (0 ms)
1531 ms to take the 534 root of a 1000000 BYTE number
828 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 268 root of THAT (547 ms)
1266 ms to take the 268 root of a 1000000 BYTE number (1266 ms) then take the square root of THAT: (0 ms)
1187 ms to take the 536 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 269 root of THAT (360 ms)
797 ms to take the 269 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (0 ms)
1000 ms to take the 538 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 270 root of THAT (516 ms)
1187 ms to take the 270 root of a 1000000 BYTE number (1187 ms) then take the square root of THAT: (0 ms)
1188 ms to take the 540 root of a 1000000 BYTE number
796 ms to take the square root of a 1000000 BYTE number (328 ms) then take the 271 root of THAT (468 ms)
1016 ms to take the 271 root of a 1000000 BYTE number (1016 ms) then take the square root of THAT: (0 ms)
1109 ms to take the 542 root of a 1000000 BYTE number
875 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 272 root of THAT (593 ms)
1797 ms to take the 272 root of a 1000000 BYTE number (1797 ms) then take the square root of THAT: (0 ms)
1266 ms to take the 544 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 273 root of THAT (297 ms)
688 ms to take the 273 root of a 1000000 BYTE number (688 ms) then take the square root of THAT: (0 ms)
1015 ms to take the 546 root of a 1000000 BYTE number
860 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 274 root of THAT (594 ms)
1062 ms to take the 274 root of a 1000000 BYTE number (1062 ms) then take the square root of THAT: (0 ms)
1609 ms to take the 548 root of a 1000000 BYTE number
657 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 275 root of THAT (391 ms)
984 ms to take the 275 root of a 1000000 BYTE number (984 ms) then take the square root of THAT: (0 ms)
1047 ms to take the 550 root of a 1000000 BYTE number
844 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 276 root of THAT (563 ms)
1250 ms to take the 276 root of a 1000000 BYTE number (1250 ms) then take the square root of THAT: (0 ms)
1218 ms to take the 552 root of a 1000000 BYTE number
672 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 277 root of THAT (390 ms)
797 ms to take the 277 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (0 ms)
1125 ms to take the 554 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 278 root of THAT (500 ms)
1204 ms to take the 278 root of a 1000000 BYTE number (1204 ms) then take the square root of THAT: (0 ms)
1328 ms to take the 556 root of a 1000000 BYTE number
1109 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 279 root of THAT (812 ms)
1625 ms to take the 279 root of a 1000000 BYTE number (1625 ms) then take the square root of THAT: (0 ms)
1938 ms to take the 558 root of a 1000000 BYTE number
875 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 280 root of THAT (594 ms)
1296 ms to take the 280 root of a 1000000 BYTE number (1296 ms) then take the square root of THAT: (0 ms)
1282 ms to take the 560 root of a 1000000 BYTE number
609 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 281 root of THAT (344 ms)
656 ms to take the 281 root of a 1000000 BYTE number (656 ms) then take the square root of THAT: (0 ms)
1016 ms to take the 562 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 282 root of THAT (500 ms)
969 ms to take the 282 root of a 1000000 BYTE number (969 ms) then take the square root of THAT: (0 ms)
1187 ms to take the 564 root of a 1000000 BYTE number
672 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 283 root of THAT (406 ms)
813 ms to take the 283 root of a 1000000 BYTE number (813 ms) then take the square root of THAT: (0 ms)
1109 ms to take the 566 root of a 1000000 BYTE number
1203 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 284 root of THAT (937 ms)
1141 ms to take the 284 root of a 1000000 BYTE number (1141 ms) then take the square root of THAT: (0 ms)
2172 ms to take the 568 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 285 root of THAT (375 ms)
828 ms to take the 285 root of a 1000000 BYTE number (828 ms) then take the square root of THAT: (0 ms)
1047 ms to take the 570 root of a 1000000 BYTE number
859 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 286 root of THAT (562 ms)
1375 ms to take the 286 root of a 1000000 BYTE number (1375 ms) then take the square root of THAT: (0 ms)
1266 ms to take the 572 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 287 root of THAT (453 ms)
1203 ms to take the 287 root of a 1000000 BYTE number (1203 ms) then take the square root of THAT: (0 ms)
1156 ms to take the 574 root of a 1000000 BYTE number
1219 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 288 root of THAT (938 ms)
1875 ms to take the 288 root of a 1000000 BYTE number (1875 ms) then take the square root of THAT: (0 ms)
1953 ms to take the 576 root of a 1000000 BYTE number
609 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 289 root of THAT (312 ms)
610 ms to take the 289 root of a 1000000 BYTE number (610 ms) then take the square root of THAT: (0 ms)
984 ms to take the 578 root of a 1000000 BYTE number
860 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 290 root of THAT (579 ms)
1281 ms to take the 290 root of a 1000000 BYTE number (1281 ms) then take the square root of THAT: (0 ms)
1437 ms to take the 580 root of a 1000000 BYTE number
656 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 291 root of THAT (390 ms)
1031 ms to take the 291 root of a 1000000 BYTE number (1031 ms) then take the square root of THAT: (0 ms)
1079 ms to take the 582 root of a 1000000 BYTE number
1171 ms to take the square root of a 1000000 BYTE number (296 ms) then take the 292 root of THAT (875 ms)
1750 ms to take the 292 root of a 1000000 BYTE number (1750 ms) then take the square root of THAT: (0 ms)
2469 ms to take the 584 root of a 1000000 BYTE number
750 ms to take the square root of a 1000000 BYTE number (328 ms) then take the 293 root of THAT (422 ms)
891 ms to take the 293 root of a 1000000 BYTE number (891 ms) then take the square root of THAT: (0 ms)
1140 ms to take the 586 root of a 1000000 BYTE number
938 ms to take the square root of a 1000000 BYTE number (313 ms) then take the 294 root of THAT (625 ms)
1125 ms to take the 294 root of a 1000000 BYTE number (1125 ms) then take the square root of THAT: (0 ms)
1344 ms to take the 588 root of a 1000000 BYTE number
718 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 295 root of THAT (437 ms)
860 ms to take the 295 root of a 1000000 BYTE number (860 ms) then take the square root of THAT: (0 ms)
1125 ms to take the 590 root of a 1000000 BYTE number
890 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 296 root of THAT (609 ms)
1172 ms to take the 296 root of a 1000000 BYTE number (1172 ms) then take the square root of THAT: (0 ms)
1375 ms to take the 592 root of a 1000000 BYTE number
609 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 297 root of THAT (328 ms)
657 ms to take the 297 root of a 1000000 BYTE number (657 ms) then take the square root of THAT: (0 ms)
1031 ms to take the 594 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 298 root of THAT (500 ms)
1063 ms to take the 298 root of a 1000000 BYTE number (1063 ms) then take the square root of THAT: (0 ms)
1281 ms to take the 596 root of a 1000000 BYTE number
938 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 299 root of THAT (656 ms)
1375 ms to take the 299 root of a 1000000 BYTE number (1375 ms) then take the square root of THAT: (0 ms)
1641 ms to take the 598 root of a 1000000 BYTE number
875 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 300 root of THAT (594 ms)
1140 ms to take the 300 root of a 1000000 BYTE number (1140 ms) then take the square root of THAT: (0 ms)
1297 ms to take the 600 root of a 1000000 BYTE number
656 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 301 root of THAT (375 ms)
797 ms to take the 301 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (0 ms)
1094 ms to take the 602 root of a 1000000 BYTE number
828 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 302 root of THAT (563 ms)
1062 ms to take the 302 root of a 1000000 BYTE number (1062 ms) then take the square root of THAT: (0 ms)
1266 ms to take the 604 root of a 1000000 BYTE number
734 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 303 root of THAT (469 ms)
922 ms to take the 303 root of a 1000000 BYTE number (922 ms) then take the square root of THAT: (0 ms)
1156 ms to take the 606 root of a 1000000 BYTE number
922 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 304 root of THAT (640 ms)
1219 ms to take the 304 root of a 1000000 BYTE number (1219 ms) then take the square root of THAT: (0 ms)
1406 ms to take the 608 root of a 1000000 BYTE number
610 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 305 root of THAT (329 ms)
640 ms to take the 305 root of a 1000000 BYTE number (640 ms) then take the square root of THAT: (0 ms)
1031 ms to take the 610 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 306 root of THAT (515 ms)
969 ms to take the 306 root of a 1000000 BYTE number (969 ms) then take the square root of THAT: (0 ms)
1203 ms to take the 612 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 307 root of THAT (500 ms)
954 ms to take the 307 root of a 1000000 BYTE number (954 ms) then take the square root of THAT: (0 ms)
1390 ms to take the 614 root of a 1000000 BYTE number
875 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 308 root of THAT (609 ms)
1141 ms to take the 308 root of a 1000000 BYTE number (1141 ms) then take the square root of THAT: (0 ms)
1297 ms to take the 616 root of a 1000000 BYTE number
656 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 309 root of THAT (375 ms)
734 ms to take the 309 root of a 1000000 BYTE number (734 ms) then take the square root of THAT: (0 ms)
1157 ms to take the 618 root of a 1000000 BYTE number
937 ms to take the square root of a 1000000 BYTE number (328 ms) then take the 310 root of THAT (609 ms)
1078 ms to take the 310 root of a 1000000 BYTE number (1078 ms) then take the square root of THAT: (0 ms)
1360 ms to take the 620 root of a 1000000 BYTE number
734 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 311 root of THAT (453 ms)
891 ms to take the 311 root of a 1000000 BYTE number (891 ms) then take the square root of THAT: (0 ms)
1187 ms to take the 622 root of a 1000000 BYTE number
906 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 312 root of THAT (640 ms)
1235 ms to take the 312 root of a 1000000 BYTE number (1235 ms) then take the square root of THAT: (0 ms)
1390 ms to take the 624 root of a 1000000 BYTE number
657 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 313 root of THAT (391 ms)
703 ms to take the 313 root of a 1000000 BYTE number (703 ms) then take the square root of THAT: (0 ms)
1125 ms to take the 626 root of a 1000000 BYTE number
953 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 314 root of THAT (688 ms)
1297 ms to take the 314 root of a 1000000 BYTE number (1297 ms) then take the square root of THAT: (0 ms)
1890 ms to take the 628 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 315 root of THAT (437 ms)
859 ms to take the 315 root of a 1000000 BYTE number (859 ms) then take the square root of THAT: (0 ms)
1157 ms to take the 630 root of a 1000000 BYTE number
906 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 316 root of THAT (625 ms)
1625 ms to take the 316 root of a 1000000 BYTE number (1625 ms) then take the square root of THAT: (0 ms)
1375 ms to take the 632 root of a 1000000 BYTE number
781 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 317 root of THAT (515 ms)
766 ms to take the 317 root of a 1000000 BYTE number (766 ms) then take the square root of THAT: (0 ms)
1281 ms to take the 634 root of a 1000000 BYTE number
891 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 318 root of THAT (625 ms)
1437 ms to take the 318 root of a 1000000 BYTE number (1437 ms) then take the square root of THAT: (0 ms)
1328 ms to take the 636 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 319 root of THAT (531 ms)
1031 ms to take the 319 root of a 1000000 BYTE number (1031 ms) then take the square root of THAT: (0 ms)
1297 ms to take the 638 root of a 1000000 BYTE number
1016 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 320 root of THAT (719 ms)
1343 ms to take the 320 root of a 1000000 BYTE number (1343 ms) then take the square root of THAT: (0 ms)
1407 ms to take the 640 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 321 root of THAT (344 ms)
656 ms to take the 321 root of a 1000000 BYTE number (656 ms) then take the square root of THAT: (0 ms)
1047 ms to take the 642 root of a 1000000 BYTE number
937 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 322 root of THAT (672 ms)
985 ms to take the 322 root of a 1000000 BYTE number (985 ms) then take the square root of THAT: (0 ms)
1671 ms to take the 644 root of a 1000000 BYTE number
688 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 323 root of THAT (406 ms)
812 ms to take the 323 root of a 1000000 BYTE number (812 ms) then take the square root of THAT: (0 ms)
1157 ms to take the 646 root of a 1000000 BYTE number
875 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 324 root of THAT (594 ms)
1156 ms to take the 324 root of a 1000000 BYTE number (1156 ms) then take the square root of THAT: (0 ms)
1297 ms to take the 648 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 325 root of THAT (359 ms)
688 ms to take the 325 root of a 1000000 BYTE number (688 ms) then take the square root of THAT: (0 ms)
1062 ms to take the 650 root of a 1000000 BYTE number
704 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 326 root of THAT (422 ms)
953 ms to take the 326 root of a 1000000 BYTE number (953 ms) then take the square root of THAT: (0 ms)
968 ms to take the 652 root of a 1000000 BYTE number
672 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 327 root of THAT (390 ms)
750 ms to take the 327 root of a 1000000 BYTE number (750 ms) then take the square root of THAT: (0 ms)
1032 ms to take the 654 root of a 1000000 BYTE number
718 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 328 root of THAT (437 ms)
1469 ms to take the 328 root of a 1000000 BYTE number (1469 ms) then take the square root of THAT: (0 ms)
922 ms to take the 656 root of a 1000000 BYTE number
531 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 329 root of THAT (250 ms)
578 ms to take the 329 root of a 1000000 BYTE number (578 ms) then take the square root of THAT: (0 ms)
719 ms to take the 658 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 330 root of THAT (344 ms)
844 ms to take the 330 root of a 1000000 BYTE number (844 ms) then take the square root of THAT: (0 ms)
812 ms to take the 660 root of a 1000000 BYTE number
563 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 331 root of THAT (297 ms)
797 ms to take the 331 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (0 ms)
781 ms to take the 662 root of a 1000000 BYTE number
672 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 332 root of THAT (406 ms)
969 ms to take the 332 root of a 1000000 BYTE number (969 ms) then take the square root of THAT: (0 ms)
859 ms to take the 664 root of a 1000000 BYTE number
547 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 333 root of THAT (281 ms)
656 ms to take the 333 root of a 1000000 BYTE number (656 ms) then take the square root of THAT: (0 ms)
781 ms to take the 666 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 334 root of THAT (438 ms)
906 ms to take the 334 root of a 1000000 BYTE number (906 ms) then take the square root of THAT: (0 ms)
984 ms to take the 668 root of a 1000000 BYTE number
610 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 335 root of THAT (344 ms)
797 ms to take the 335 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (0 ms)
828 ms to take the 670 root of a 1000000 BYTE number
968 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 336 root of THAT (703 ms)
1344 ms to take the 336 root of a 1000000 BYTE number (1344 ms) then take the square root of THAT: (0 ms)
1500 ms to take the 672 root of a 1000000 BYTE number
563 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 337 root of THAT (297 ms)
609 ms to take the 337 root of a 1000000 BYTE number (609 ms) then take the square root of THAT: (0 ms)
719 ms to take the 674 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 338 root of THAT (360 ms)
844 ms to take the 338 root of a 1000000 BYTE number (844 ms) then take the square root of THAT: (0 ms)
812 ms to take the 676 root of a 1000000 BYTE number
563 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 339 root of THAT (282 ms)
718 ms to take the 339 root of a 1000000 BYTE number (718 ms) then take the square root of THAT: (0 ms)
734 ms to take the 678 root of a 1000000 BYTE number
688 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 340 root of THAT (406 ms)
969 ms to take the 340 root of a 1000000 BYTE number (969 ms) then take the square root of THAT: (0 ms)
875 ms to take the 680 root of a 1000000 BYTE number
531 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 341 root of THAT (266 ms)
703 ms to take the 341 root of a 1000000 BYTE number (703 ms) then take the square root of THAT: (0 ms)
750 ms to take the 682 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 342 root of THAT (375 ms)
906 ms to take the 342 root of a 1000000 BYTE number (906 ms) then take the square root of THAT: (0 ms)
844 ms to take the 684 root of a 1000000 BYTE number
593 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 343 root of THAT (312 ms)
797 ms to take the 343 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (0 ms)
781 ms to take the 686 root of a 1000000 BYTE number
704 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 344 root of THAT (422 ms)
1046 ms to take the 344 root of a 1000000 BYTE number (1046 ms) then take the square root of THAT: (0 ms)
985 ms to take the 688 root of a 1000000 BYTE number
562 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 345 root of THAT (265 ms)
657 ms to take the 345 root of a 1000000 BYTE number (657 ms) then take the square root of THAT: (0 ms)
890 ms to take the 690 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 346 root of THAT (360 ms)
906 ms to take the 346 root of a 1000000 BYTE number (906 ms) then take the square root of THAT: (0 ms)
875 ms to take the 692 root of a 1000000 BYTE number
703 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 347 root of THAT (422 ms)
750 ms to take the 347 root of a 1000000 BYTE number (750 ms) then take the square root of THAT: (0 ms)
1031 ms to take the 694 root of a 1000000 BYTE number
704 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 348 root of THAT (422 ms)
1015 ms to take the 348 root of a 1000000 BYTE number (1015 ms) then take the square root of THAT: (0 ms)
953 ms to take the 696 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 349 root of THAT (453 ms)
688 ms to take the 349 root of a 1000000 BYTE number (688 ms) then take the square root of THAT: (0 ms)
1125 ms to take the 698 root of a 1000000 BYTE number
687 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 350 root of THAT (406 ms)
1094 ms to take the 350 root of a 1000000 BYTE number (1094 ms) then take the square root of THAT: (0 ms)
906 ms to take the 700 root of a 1000000 BYTE number
813 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 351 root of THAT (547 ms)
1046 ms to take the 351 root of a 1000000 BYTE number (1046 ms) then take the square root of THAT: (0 ms)
1344 ms to take the 702 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 352 root of THAT (516 ms)
1250 ms to take the 352 root of a 1000000 BYTE number (1250 ms) then take the square root of THAT: (0 ms)
1094 ms to take the 704 root of a 1000000 BYTE number
609 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 353 root of THAT (344 ms)
985 ms to take the 353 root of a 1000000 BYTE number (985 ms) then take the square root of THAT: (0 ms)
1062 ms to take the 706 root of a 1000000 BYTE number
609 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 354 root of THAT (343 ms)
969 ms to take the 354 root of a 1000000 BYTE number (969 ms) then take the square root of THAT: (0 ms)
844 ms to take the 708 root of a 1000000 BYTE number
750 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 355 root of THAT (484 ms)
937 ms to take the 355 root of a 1000000 BYTE number (937 ms) then take the square root of THAT: (0 ms)
1282 ms to take the 710 root of a 1000000 BYTE number
765 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 356 root of THAT (484 ms)
1016 ms to take the 356 root of a 1000000 BYTE number (1016 ms) then take the square root of THAT: (0 ms)
1062 ms to take the 712 root of a 1000000 BYTE number
688 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 357 root of THAT (391 ms)
750 ms to take the 357 root of a 1000000 BYTE number (750 ms) then take the square root of THAT: (0 ms)
1141 ms to take the 714 root of a 1000000 BYTE number
687 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 358 root of THAT (406 ms)
922 ms to take the 358 root of a 1000000 BYTE number (922 ms) then take the square root of THAT: (0 ms)
922 ms to take the 716 root of a 1000000 BYTE number
656 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 359 root of THAT (391 ms)
781 ms to take the 359 root of a 1000000 BYTE number (781 ms) then take the square root of THAT: (0 ms)
953 ms to take the 718 root of a 1000000 BYTE number
750 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 360 root of THAT (468 ms)
1063 ms to take the 360 root of a 1000000 BYTE number (1063 ms) then take the square root of THAT: (0 ms)
1109 ms to take the 720 root of a 1000000 BYTE number
610 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 361 root of THAT (328 ms)
609 ms to take the 361 root of a 1000000 BYTE number (609 ms) then take the square root of THAT: (0 ms)
969 ms to take the 722 root of a 1000000 BYTE number
640 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 362 root of THAT (359 ms)
875 ms to take the 362 root of a 1000000 BYTE number (875 ms) then take the square root of THAT: (0 ms)
844 ms to take the 724 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 363 root of THAT (313 ms)
765 ms to take the 363 root of a 1000000 BYTE number (765 ms) then take the square root of THAT: (0 ms)
797 ms to take the 726 root of a 1000000 BYTE number
688 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 364 root of THAT (407 ms)
1046 ms to take the 364 root of a 1000000 BYTE number (1031 ms) then take the square root of THAT: (15 ms)
875 ms to take the 728 root of a 1000000 BYTE number
563 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 365 root of THAT (281 ms)
672 ms to take the 365 root of a 1000000 BYTE number (672 ms) then take the square root of THAT: (0 ms)
765 ms to take the 730 root of a 1000000 BYTE number
657 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 366 root of THAT (391 ms)
1140 ms to take the 366 root of a 1000000 BYTE number (1140 ms) then take the square root of THAT: (0 ms)
875 ms to take the 732 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 367 root of THAT (343 ms)
828 ms to take the 367 root of a 1000000 BYTE number (828 ms) then take the square root of THAT: (0 ms)
813 ms to take the 734 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 368 root of THAT (438 ms)
1093 ms to take the 368 root of a 1000000 BYTE number (1093 ms) then take the square root of THAT: (0 ms)
922 ms to take the 736 root of a 1000000 BYTE number
532 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 369 root of THAT (250 ms)
593 ms to take the 369 root of a 1000000 BYTE number (593 ms) then take the square root of THAT: (0 ms)
750 ms to take the 738 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 370 root of THAT (359 ms)
891 ms to take the 370 root of a 1000000 BYTE number (891 ms) then take the square root of THAT: (0 ms)
937 ms to take the 740 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 371 root of THAT (344 ms)
797 ms to take the 371 root of a 1000000 BYTE number (781 ms) then take the square root of THAT: (16 ms)
812 ms to take the 742 root of a 1000000 BYTE number
875 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 372 root of THAT (593 ms)
1782 ms to take the 372 root of a 1000000 BYTE number (1782 ms) then take the square root of THAT: (0 ms)
1265 ms to take the 744 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 373 root of THAT (343 ms)
735 ms to take the 373 root of a 1000000 BYTE number (735 ms) then take the square root of THAT: (0 ms)
953 ms to take the 746 root of a 1000000 BYTE number
734 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 374 root of THAT (453 ms)
953 ms to take the 374 root of a 1000000 BYTE number (953 ms) then take the square root of THAT: (0 ms)
1094 ms to take the 748 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 375 root of THAT (328 ms)
813 ms to take the 375 root of a 1000000 BYTE number (813 ms) then take the square root of THAT: (0 ms)
828 ms to take the 750 root of a 1000000 BYTE number
703 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 376 root of THAT (422 ms)
1094 ms to take the 376 root of a 1000000 BYTE number (1094 ms) then take the square root of THAT: (0 ms)
953 ms to take the 752 root of a 1000000 BYTE number
531 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 377 root of THAT (266 ms)
812 ms to take the 377 root of a 1000000 BYTE number (812 ms) then take the square root of THAT: (0 ms)
766 ms to take the 754 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 378 root of THAT (360 ms)
968 ms to take the 378 root of a 1000000 BYTE number (968 ms) then take the square root of THAT: (0 ms)
860 ms to take the 756 root of a 1000000 BYTE number
609 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 379 root of THAT (328 ms)
781 ms to take the 379 root of a 1000000 BYTE number (781 ms) then take the square root of THAT: (0 ms)
813 ms to take the 758 root of a 1000000 BYTE number
687 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 380 root of THAT (421 ms)
1063 ms to take the 380 root of a 1000000 BYTE number (1063 ms) then take the square root of THAT: (0 ms)
921 ms to take the 760 root of a 1000000 BYTE number
766 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 381 root of THAT (484 ms)
1219 ms to take the 381 root of a 1000000 BYTE number (1219 ms) then take the square root of THAT: (0 ms)
1344 ms to take the 762 root of a 1000000 BYTE number
687 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 382 root of THAT (406 ms)
1016 ms to take the 382 root of a 1000000 BYTE number (1016 ms) then take the square root of THAT: (0 ms)
922 ms to take the 764 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 383 root of THAT (360 ms)
843 ms to take the 383 root of a 1000000 BYTE number (843 ms) then take the square root of THAT: (0 ms)
844 ms to take the 766 root of a 1000000 BYTE number
750 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 384 root of THAT (453 ms)
1375 ms to take the 384 root of a 1000000 BYTE number (1375 ms) then take the square root of THAT: (0 ms)
938 ms to take the 768 root of a 1000000 BYTE number
531 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 385 root of THAT (250 ms)
578 ms to take the 385 root of a 1000000 BYTE number (578 ms) then take the square root of THAT: (0 ms)
750 ms to take the 770 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 386 root of THAT (359 ms)
859 ms to take the 386 root of a 1000000 BYTE number (859 ms) then take the square root of THAT: (0 ms)
860 ms to take the 772 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 387 root of THAT (297 ms)
750 ms to take the 387 root of a 1000000 BYTE number (750 ms) then take the square root of THAT: (0 ms)
781 ms to take the 774 root of a 1000000 BYTE number
875 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 388 root of THAT (594 ms)
1109 ms to take the 388 root of a 1000000 BYTE number (1109 ms) then take the square root of THAT: (0 ms)
1329 ms to take the 776 root of a 1000000 BYTE number
546 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 389 root of THAT (265 ms)
657 ms to take the 389 root of a 1000000 BYTE number (657 ms) then take the square root of THAT: (0 ms)
781 ms to take the 778 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 390 root of THAT (375 ms)
968 ms to take the 390 root of a 1000000 BYTE number (968 ms) then take the square root of THAT: (0 ms)
875 ms to take the 780 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 391 root of THAT (312 ms)
813 ms to take the 391 root of a 1000000 BYTE number (813 ms) then take the square root of THAT: (0 ms)
781 ms to take the 782 root of a 1000000 BYTE number
734 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 392 root of THAT (453 ms)
1078 ms to take the 392 root of a 1000000 BYTE number (1078 ms) then take the square root of THAT: (0 ms)
1000 ms to take the 784 root of a 1000000 BYTE number
657 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 393 root of THAT (375 ms)
1078 ms to take the 393 root of a 1000000 BYTE number (1078 ms) then take the square root of THAT: (0 ms)
1125 ms to take the 786 root of a 1000000 BYTE number
656 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 394 root of THAT (375 ms)
906 ms to take the 394 root of a 1000000 BYTE number (906 ms) then take the square root of THAT: (0 ms)
906 ms to take the 788 root of a 1000000 BYTE number
547 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 395 root of THAT (265 ms)
719 ms to take the 395 root of a 1000000 BYTE number (719 ms) then take the square root of THAT: (0 ms)
672 ms to take the 790 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 396 root of THAT (344 ms)
1031 ms to take the 396 root of a 1000000 BYTE number (1031 ms) then take the square root of THAT: (0 ms)
828 ms to take the 792 root of a 1000000 BYTE number
547 ms to take the square root of a 1000000 BYTE number (313 ms) then take the 397 root of THAT (234 ms)
719 ms to take the 397 root of a 1000000 BYTE number (719 ms) then take the square root of THAT: (0 ms)
703 ms to take the 794 root of a 1000000 BYTE number
875 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 398 root of THAT (609 ms)
1609 ms to take the 398 root of a 1000000 BYTE number (1609 ms) then take the square root of THAT: (0 ms)
1204 ms to take the 796 root of a 1000000 BYTE number
546 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 399 root of THAT (281 ms)
797 ms to take the 399 root of a 1000000 BYTE number (797 ms) then take the square root of THAT: (0 ms)
703 ms to take the 798 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 400 root of THAT (359 ms)
1047 ms to take the 400 root of a 1000000 BYTE number (1047 ms) then take the square root of THAT: (0 ms)
782 ms to take the 800 root of a 1000000 BYTE number
500 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 401 root of THAT (219 ms)
562 ms to take the 401 root of a 1000000 BYTE number (562 ms) then take the square root of THAT: (0 ms)
625 ms to take the 802 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 402 root of THAT (297 ms)
844 ms to take the 402 root of a 1000000 BYTE number (844 ms) then take the square root of THAT: (0 ms)
719 ms to take the 804 root of a 1000000 BYTE number
687 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 403 root of THAT (406 ms)
703 ms to take the 403 root of a 1000000 BYTE number (703 ms) then take the square root of THAT: (0 ms)
1094 ms to take the 806 root of a 1000000 BYTE number
609 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 404 root of THAT (328 ms)
985 ms to take the 404 root of a 1000000 BYTE number (985 ms) then take the square root of THAT: (0 ms)
750 ms to take the 808 root of a 1000000 BYTE number
515 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 405 root of THAT (234 ms)
657 ms to take the 405 root of a 1000000 BYTE number (657 ms) then take the square root of THAT: (0 ms)
672 ms to take the 810 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 406 root of THAT (313 ms)
937 ms to take the 406 root of a 1000000 BYTE number (937 ms) then take the square root of THAT: (0 ms)
750 ms to take the 812 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 407 root of THAT (313 ms)
1000 ms to take the 407 root of a 1000000 BYTE number (1000 ms) then take the square root of THAT: (0 ms)
781 ms to take the 814 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 408 root of THAT (375 ms)
1047 ms to take the 408 root of a 1000000 BYTE number (1047 ms) then take the square root of THAT: (0 ms)
765 ms to take the 816 root of a 1000000 BYTE number
500 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 409 root of THAT (234 ms)
734 ms to take the 409 root of a 1000000 BYTE number (734 ms) then take the square root of THAT: (0 ms)
641 ms to take the 818 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 410 root of THAT (313 ms)
890 ms to take the 410 root of a 1000000 BYTE number (890 ms) then take the square root of THAT: (0 ms)
719 ms to take the 820 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 411 root of THAT (438 ms)
969 ms to take the 411 root of a 1000000 BYTE number (969 ms) then take the square root of THAT: (0 ms)
1171 ms to take the 822 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 412 root of THAT (359 ms)
1016 ms to take the 412 root of a 1000000 BYTE number (1016 ms) then take the square root of THAT: (0 ms)
781 ms to take the 824 root of a 1000000 BYTE number
547 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 413 root of THAT (281 ms)
672 ms to take the 413 root of a 1000000 BYTE number (672 ms) then take the square root of THAT: (0 ms)
672 ms to take the 826 root of a 1000000 BYTE number
610 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 414 root of THAT (329 ms)
953 ms to take the 414 root of a 1000000 BYTE number (953 ms) then take the square root of THAT: (0 ms)
765 ms to take the 828 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 415 root of THAT (296 ms)
813 ms to take the 415 root of a 1000000 BYTE number (813 ms) then take the square root of THAT: (0 ms)
703 ms to take the 830 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 416 root of THAT (360 ms)
1093 ms to take the 416 root of a 1000000 BYTE number (1093 ms) then take the square root of THAT: (0 ms)
797 ms to take the 832 root of a 1000000 BYTE number
516 ms to take the square root of a 1000000 BYTE number (297 ms) then take the 417 root of THAT (219 ms)
578 ms to take the 417 root of a 1000000 BYTE number (578 ms) then take the square root of THAT: (0 ms)
641 ms to take the 834 root of a 1000000 BYTE number
609 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 418 root of THAT (344 ms)
1250 ms to take the 418 root of a 1000000 BYTE number (1250 ms) then take the square root of THAT: (0 ms)
797 ms to take the 836 root of a 1000000 BYTE number
562 ms to take the square root of a 1000000 BYTE number (296 ms) then take the 419 root of THAT (266 ms)
703 ms to take the 419 root of a 1000000 BYTE number (703 ms) then take the square root of THAT: (0 ms)
813 ms to take the 838 root of a 1000000 BYTE number
609 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 420 root of THAT (328 ms)
1000 ms to take the 420 root of a 1000000 BYTE number (1000 ms) then take the square root of THAT: (0 ms)
750 ms to take the 840 root of a 1000000 BYTE number
516 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 421 root of THAT (235 ms)
656 ms to take the 421 root of a 1000000 BYTE number (656 ms) then take the square root of THAT: (0 ms)
687 ms to take the 842 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 422 root of THAT (375 ms)
922 ms to take the 422 root of a 1000000 BYTE number (922 ms) then take the square root of THAT: (0 ms)
844 ms to take the 844 root of a 1000000 BYTE number
562 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 423 root of THAT (281 ms)
969 ms to take the 423 root of a 1000000 BYTE number (969 ms) then take the square root of THAT: (0 ms)
703 ms to take the 846 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 424 root of THAT (359 ms)
1063 ms to take the 424 root of a 1000000 BYTE number (1063 ms) then take the square root of THAT: (0 ms)
781 ms to take the 848 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 425 root of THAT (344 ms)
1172 ms to take the 425 root of a 1000000 BYTE number (1172 ms) then take the square root of THAT: (0 ms)
1094 ms to take the 850 root of a 1000000 BYTE number
609 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 426 root of THAT (343 ms)
922 ms to take the 426 root of a 1000000 BYTE number (922 ms) then take the square root of THAT: (0 ms)
766 ms to take the 852 root of a 1000000 BYTE number
547 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 427 root of THAT (266 ms)
765 ms to take the 427 root of a 1000000 BYTE number (765 ms) then take the square root of THAT: (0 ms)
688 ms to take the 854 root of a 1000000 BYTE number
875 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 428 root of THAT (594 ms)
1766 ms to take the 428 root of a 1000000 BYTE number (1766 ms) then take the square root of THAT: (0 ms)
1328 ms to take the 856 root of a 1000000 BYTE number
531 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 429 root of THAT (250 ms)
844 ms to take the 429 root of a 1000000 BYTE number (844 ms) then take the square root of THAT: (0 ms)
703 ms to take the 858 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 430 root of THAT (344 ms)
953 ms to take the 430 root of a 1000000 BYTE number (953 ms) then take the square root of THAT: (0 ms)
750 ms to take the 860 root of a 1000000 BYTE number
719 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 431 root of THAT (438 ms)
1343 ms to take the 431 root of a 1000000 BYTE number (1343 ms) then take the square root of THAT: (0 ms)
1141 ms to take the 862 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 432 root of THAT (375 ms)
1078 ms to take the 432 root of a 1000000 BYTE number (1078 ms) then take the square root of THAT: (0 ms)
797 ms to take the 864 root of a 1000000 BYTE number
500 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 433 root of THAT (219 ms)
609 ms to take the 433 root of a 1000000 BYTE number (609 ms) then take the square root of THAT: (0 ms)
625 ms to take the 866 root of a 1000000 BYTE number
797 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 434 root of THAT (516 ms)
1500 ms to take the 434 root of a 1000000 BYTE number (1500 ms) then take the square root of THAT: (0 ms)
1266 ms to take the 868 root of a 1000000 BYTE number
531 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 435 root of THAT (250 ms)
750 ms to take the 435 root of a 1000000 BYTE number (750 ms) then take the square root of THAT: (0 ms)
687 ms to take the 870 root of a 1000000 BYTE number
641 ms to take the square root of a 1000000 BYTE number (282 ms) then take the 436 root of THAT (359 ms)
1016 ms to take the 436 root of a 1000000 BYTE number (1016 ms) then take the square root of THAT: (0 ms)
765 ms to take the 872 root of a 1000000 BYTE number
672 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 437 root of THAT (391 ms)
1063 ms to take the 437 root of a 1000000 BYTE number (1063 ms) then take the square root of THAT: (0 ms)
1078 ms to take the 874 root of a 1000000 BYTE number
593 ms to take the square root of a 1000000 BYTE number (265 ms) then take the 438 root of THAT (328 ms)
954 ms to take the 438 root of a 1000000 BYTE number (954 ms) then take the square root of THAT: (0 ms)
734 ms to take the 876 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 439 root of THAT (297 ms)
813 ms to take the 439 root of a 1000000 BYTE number (813 ms) then take the square root of THAT: (0 ms)
703 ms to take the 878 root of a 1000000 BYTE number
734 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 440 root of THAT (453 ms)
1672 ms to take the 440 root of a 1000000 BYTE number (1672 ms) then take the square root of THAT: (0 ms)
1031 ms to take the 880 root of a 1000000 BYTE number
516 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 441 root of THAT (235 ms)
625 ms to take the 441 root of a 1000000 BYTE number (625 ms) then take the square root of THAT: (0 ms)
656 ms to take the 882 root of a 1000000 BYTE number
594 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 442 root of THAT (328 ms)
906 ms to take the 442 root of a 1000000 BYTE number (906 ms) then take the square root of THAT: (0 ms)
750 ms to take the 884 root of a 1000000 BYTE number
734 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 443 root of THAT (453 ms)
985 ms to take the 443 root of a 1000000 BYTE number (985 ms) then take the square root of THAT: (0 ms)
1109 ms to take the 886 root of a 1000000 BYTE number
625 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 444 root of THAT (359 ms)
1281 ms to take the 444 root of a 1000000 BYTE number (1281 ms) then take the square root of THAT: (0 ms)
782 ms to take the 888 root of a 1000000 BYTE number
547 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 445 root of THAT (266 ms)
718 ms to take the 445 root of a 1000000 BYTE number (718 ms) then take the square root of THAT: (0 ms)
672 ms to take the 890 root of a 1000000 BYTE number
703 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 446 root of THAT (437 ms)
985 ms to take the 446 root of a 1000000 BYTE number (985 ms) then take the square root of THAT: (0 ms)
1047 ms to take the 892 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 447 root of THAT (297 ms)
953 ms to take the 447 root of a 1000000 BYTE number (953 ms) then take the square root of THAT: (0 ms)
719 ms to take the 894 root of a 1000000 BYTE number
718 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 448 root of THAT (437 ms)
1703 ms to take the 448 root of a 1000000 BYTE number (1703 ms) then take the square root of THAT: (0 ms)
922 ms to take the 896 root of a 1000000 BYTE number
500 ms to take the square root of a 1000000 BYTE number (266 ms) then take the 449 root of THAT (234 ms)
578 ms to take the 449 root of a 1000000 BYTE number (578 ms) then take the square root of THAT: (0 ms)
657 ms to take the 898 root of a 1000000 BYTE number
578 ms to take the square root of a 1000000 BYTE number (281 ms) then take the 450 root of THAT (297 ms)
875 ms to take the 450 root of a 1000000 BYTE number (875 ms) then take the square root of THAT: (0 ms)
750 ms to take the 900 root of a 1000000 BYTE number
*/
void CArithmeticPerformanceTester::GeneralRootTimes()
{
    CArithmeticBox     cBox;
    const unsigned int c_nNumberSizeInBYTEs = 1000000;
    const unsigned int c_nOneBILLION        = 1000000000;
    const unsigned int c_nMaxRoot           = 900;
    unsigned int       nTimeA, nTimeB;
    size_t             nRootSize;
    CBigIntegerForTest nX, nRootX, nXCopy;
    DIGIT              *pWorkspace = (DIGIT *) malloc(sizeof(DIGIT)*c_nNumberSizeInBYTEs*10);
    printf("Testing general root times.  Doing this in retail?  If not, your numbers won't be representative\n");
    // for "large" numbers, compare mth root(sqrt)) vs (2m)th root
    nX.Reserve(c_nNumberSizeInBYTEs); // more than needed
    nXCopy.Reserve(c_nNumberSizeInBYTEs); // more than needed
    nRootX.Reserve(c_nNumberSizeInBYTEs); // more than needed
    // for "large" numbers, compare computing the square root using general root vs square root function
   /* for(int i=0;i<10;i++)
    {
        nX.SetRandom(c_nNumberSizeInBYTEs*8);
        nXCopy = nX;
        nTimeA = ::GetTickCount();
        SQRT(nXCopy.GetSize(), nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
        nTimeA = ::GetTickCount() - nTimeA;
        nXCopy = nX;
        nTimeB = ::GetTickCount();
        NthRoot(nXCopy.GetSize(), 2, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
        nTimeB = ::GetTickCount() - nTimeB;
        printf("Square root of a %u BYTE number: SQRT %u ms; general nth root %u ms\n",c_nNumberSizeInBYTEs, nTimeA, nTimeB);
    };
    // for "large" numbers, compare general root vs Newton
    for(DIGIT n=2;n<=c_nMaxRoot;n++)
    {
        nX.SetRandom(c_nNumberSizeInBYTEs*8);
        nXCopy = nX;
        nTimeA = ::GetTickCount();
        NthRootNewton(nXCopy.GetSize(), n, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
        nTimeA = ::GetTickCount() - nTimeA;
        nXCopy = nX;
        nTimeB = ::GetTickCount();
        NthRoot(nXCopy.GetSize(), n, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
        nTimeB = ::GetTickCount() - nTimeB;
        printf("%u root of a %u BYTE number: general newton %u ms; general nth root %u ms\n",n, c_nNumberSizeInBYTEs, nTimeA, nTimeB);
    }*/
    // for "large" numbers, compare mth root(sqrt)) vs (2m)th root
    for(DIGIT m=2; m<=c_nMaxRoot/2; m++)
    {
        nXCopy = nX;
        nTimeB = ::GetTickCount();
        SQRT(nXCopy.GetSize(), nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
        nTimeB = ::GetTickCount() - nTimeB;
        nTimeA = ::GetTickCount();
        NthRoot(nRootSize, m, nRootSize, nRootX.GetValue(), nXCopy.GetValue(), pWorkspace);
        nTimeA = ::GetTickCount() - nTimeA;
        printf("%u ms to take the square root of a %u BYTE number (%u ms) then take the %u root of THAT (%u ms)\n", nTimeA + nTimeB, c_nNumberSizeInBYTEs, nTimeB, m, nTimeA);
        nXCopy = nX;
        nTimeB = ::GetTickCount();
        NthRoot(nXCopy.GetSize(), m, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
        nTimeB = ::GetTickCount() - nTimeB;
        nTimeA = ::GetTickCount();
        SQRT(nRootSize, nRootSize, nRootX.GetValue(), nXCopy.GetValue(), pWorkspace);
        nTimeA = ::GetTickCount() - nTimeA;
        printf("%u ms to take the %u root of a %u BYTE number (%u ms) then take the square root of THAT: (%u ms)\n", nTimeA + nTimeB, m, c_nNumberSizeInBYTEs, nTimeB, nTimeA);
        nXCopy = nX;
        nTimeB = ::GetTickCount();
        NthRoot(nXCopy.GetSize(), m*2, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
        nTimeB = ::GetTickCount() - nTimeB;
        printf("%u ms to take the %u root of a %u BYTE number\n", nTimeB,m*2, c_nNumberSizeInBYTEs);
    }
    free(pWorkspace);
    /*
    // try roots of varying powers of 7 for a large number -- how do the times compare?
    for(size_t nSize=c_nNumberSizeInBYTEs; nSize<=c_nOneBILLION; nSize *= 10)
    {
        nX.SetRandom(8*nSize);
        nTimeA = ::GetTickCount();
        cBox.SQRT(nX, nRootX);
        nTimeA = ::GetTickCount() - nTimeA;
        printf("Taking square root of a %u BYTE number took %u milliseconds ",nX.GetSize()*sizeof(DIGIT), nTimeA);
        // validate it, because - why not?
        nTimeA = ::GetTickCount();
        cBox.Power(nRootX, 2, nXCopy);
        if(nX<nXCopy)
        {
            printf("Whoops -- computed root too big\n");
        }
        nRootX += 1;
        cBox.Power(nRootX, 2, nXCopy);
        if(nXCopy<=nX)
        {
            printf("Whoops -- computed root too small\n");
        }
        nTimeA = ::GetTickCount() - nTimeA;
        printf("Validate: %u milliseconds\n", nTimeA);
        for(size_t n=7; n<((size_t) 1<<_DIGIT_SIZE_IN_BITS)-1; n *= 7)
        {
            nTimeA = ::GetTickCount();
            cBox.NthRoot(nX, (DIGIT) n, nRootX);
            nTimeA = ::GetTickCount() - nTimeA;
            printf("Taking root %u of a %u BYTE number took %u milliseconds ",n,nX.GetSize()*sizeof(DIGIT), nTimeA);
            // validate it, because - why not?
            nTimeA = ::GetTickCount();
            cBox.Power(nRootX, n, nXCopy);
            if(nX<nXCopy)
            {
                printf("Whoops -- computed root too big\n");
            }
            nRootX += 1;
            cBox.Power(nRootX, n, nXCopy);
            if(nXCopy<=nX)
            {
                printf("Whoops -- computed root too small\n");
            }
            nTimeA = ::GetTickCount() - nTimeA;
            printf("Validate: %u milliseconds\n", nTimeA);
        }
    }*/
}

/*
2330 ms to take the 2 root of a 100000 BYTE number (1645 ms) then take the  2 root of THAT (685 ms) 100 times
5531 ms to take the 4 root of a 100000 BYTE number 100 times

3234 ms to take the 3 root of a 100000 BYTE number (2967 ms) then take the  2 root of THAT (267 ms) 100 times
3187 ms to take the 2 root of a 100000 BYTE number (1422 ms) then take the  3 root of THAT (1765 ms) 100 times
6484 ms to take the 6 root of a 100000 BYTE number 100 times

5659 ms to take the 5 root of a 100000 BYTE number (5473 ms) then take the  2 root of THAT (186 ms) 100 times
4187 ms to take the 2 root of a 100000 BYTE number (1564 ms) then take the  5 root of THAT (2623 ms) 100 times
9018 ms to take the 10 root of a 100000 BYTE number 100 times

4610 ms to take the 7 root of a 100000 BYTE number (4594 ms) then take the  2 root of THAT (16 ms) 100 times
3611 ms to take the 2 root of a 100000 BYTE number (1530 ms) then take the  7 root of THAT (2081 ms) 100 times
7173 ms to take the 14 root of a 100000 BYTE number 100 times

5889 ms to take the 11 root of a 100000 BYTE number (5874 ms) then take the  2 root of THAT (15 ms) 100 times
3894 ms to take the 2 root of a 100000 BYTE number (1434 ms) then take the  11 root of THAT (2460 ms) 100 times
8155 ms to take the 22 root of a 100000 BYTE number 100 times

6406 ms to take the 13 root of a 100000 BYTE number (6390 ms) then take the  2 root of THAT (16 ms) 100 times
4000 ms to take the 2 root of a 100000 BYTE number (1472 ms) then take the  13 root of THAT (2528 ms) 100 times
9124 ms to take the 26 root of a 100000 BYTE number 100 times

5535 ms to take the 17 root of a 100000 BYTE number (5489 ms) then take the  2 root of THAT (46 ms) 100 times
3532 ms to take the 2 root of a 100000 BYTE number (1509 ms) then take the  17 root of THAT (2023 ms) 100 times
7232 ms to take the 34 root of a 100000 BYTE number 100 times

6172 ms to take the 19 root of a 100000 BYTE number (6156 ms) then take the  2 root of THAT (16 ms) 100 times
4185 ms to take the 2 root of a 100000 BYTE number (1503 ms) then take the  19 root of THAT (2682 ms) 100 times
8167 ms to take the 38 root of a 100000 BYTE number 100 times

7235 ms to take the 23 root of a 100000 BYTE number (7219 ms) then take the  2 root of THAT (16 ms) 100 times
4283 ms to take the 2 root of a 100000 BYTE number (1440 ms) then take the  23 root of THAT (2843 ms) 100 times
8484 ms to take the 46 root of a 100000 BYTE number 100 times

7844 ms to take the 29 root of a 100000 BYTE number (7797 ms) then take the  2 root of THAT (47 ms) 100 times
4987 ms to take the 2 root of a 100000 BYTE number (1589 ms) then take the  29 root of THAT (3398 ms) 100 times
11077 ms to take the 58 root of a 100000 BYTE number 100 times

7251 ms to take the 31 root of a 100000 BYTE number (7251 ms) then take the  2 root of THAT (0 ms) 100 times
5049 ms to take the 2 root of a 100000 BYTE number (1498 ms) then take the  31 root of THAT (3551 ms) 100 times
11216 ms to take the 62 root of a 100000 BYTE number 100 times

5408 ms to take the 37 root of a 100000 BYTE number (5408 ms) then take the  2 root of THAT (0 ms) 100 times
3613 ms to take the 2 root of a 100000 BYTE number (1517 ms) then take the  37 root of THAT (2096 ms) 100 times
6797 ms to take the 74 root of a 100000 BYTE number 100 times

5219 ms to take the 41 root of a 100000 BYTE number (5203 ms) then take the  2 root of THAT (16 ms) 100 times
3453 ms to take the 2 root of a 100000 BYTE number (1659 ms) then take the  41 root of THAT (1794 ms) 100 times
5687 ms to take the 82 root of a 100000 BYTE number 100 times

6265 ms to take the 43 root of a 100000 BYTE number (6249 ms) then take the  2 root of THAT (16 ms) 100 times
3770 ms to take the 2 root of a 100000 BYTE number (1527 ms) then take the  43 root of THAT (2243 ms) 100 times
6265 ms to take the 86 root of a 100000 BYTE number 100 times

7548 ms to take the 47 root of a 100000 BYTE number (7548 ms) then take the  2 root of THAT (0 ms) 100 times
3908 ms to take the 2 root of a 100000 BYTE number (1517 ms) then take the  47 root of THAT (2391 ms) 100 times
6656 ms to take the 94 root of a 100000 BYTE number 100 times

6546 ms to take the 53 root of a 100000 BYTE number (6546 ms) then take the  2 root of THAT (0 ms) 100 times
3906 ms to take the 2 root of a 100000 BYTE number (1665 ms) then take the  53 root of THAT (2241 ms) 100 times
6657 ms to take the 106 root of a 100000 BYTE number 100 times

7653 ms to take the 59 root of a 100000 BYTE number (7638 ms) then take the  2 root of THAT (15 ms) 100 times
4128 ms to take the 2 root of a 100000 BYTE number (1492 ms) then take the  59 root of THAT (2636 ms) 100 times
6860 ms to take the 118 root of a 100000 BYTE number 100 times

6918 ms to take the 61 root of a 100000 BYTE number (6903 ms) then take the  2 root of THAT (15 ms) 100 times
3673 ms to take the 2 root of a 100000 BYTE number (1462 ms) then take the  61 root of THAT (2211 ms) 100 times
6658 ms to take the 122 root of a 100000 BYTE number 100 times

5345 ms to take the 67 root of a 100000 BYTE number (5345 ms) then take the  2 root of THAT (0 ms) 100 times
3263 ms to take the 2 root of a 100000 BYTE number (1530 ms) then take the  67 root of THAT (1733 ms) 100 times
4969 ms to take the 134 root of a 100000 BYTE number 100 times

8938 ms to take the 71 root of a 100000 BYTE number (8938 ms) then take the  2 root of THAT (0 ms) 100 times
4687 ms to take the 2 root of a 100000 BYTE number (1513 ms) then take the  71 root of THAT (3174 ms) 100 times
8874 ms to take the 142 root of a 100000 BYTE number 100 times

4202 ms to take the 3 root of a 100000 BYTE number (3154 ms) then take the  3 root of THAT (1048 ms) 100 times
4578 ms to take the 9 root of a 100000 BYTE number 100 times

6078 ms to take the 5 root of a 100000 BYTE number (5553 ms) then take the  3 root of THAT (525 ms) 100 times
4044 ms to take the 3 root of a 100000 BYTE number (3083 ms) then take the  5 root of THAT (961 ms) 100 times
5967 ms to take the 15 root of a 100000 BYTE number 100 times

4783 ms to take the 7 root of a 100000 BYTE number (4547 ms) then take the  3 root of THAT (236 ms) 100 times
4265 ms to take the 3 root of a 100000 BYTE number (3076 ms) then take the  7 root of THAT (1189 ms) 100 times
5453 ms to take the 21 root of a 100000 BYTE number 100 times

6283 ms to take the 11 root of a 100000 BYTE number (5970 ms) then take the  3 root of THAT (313 ms) 100 times
4331 ms to take the 3 root of a 100000 BYTE number (3001 ms) then take the  11 root of THAT (1330 ms) 100 times
4889 ms to take the 33 root of a 100000 BYTE number 100 times

6643 ms to take the 13 root of a 100000 BYTE number (6596 ms) then take the  3 root of THAT (47 ms) 100 times
4560 ms to take the 3 root of a 100000 BYTE number (3358 ms) then take the  13 root of THAT (1202 ms) 100 times
6810 ms to take the 39 root of a 100000 BYTE number 100 times

4858 ms to take the 17 root of a 100000 BYTE number (4778 ms) then take the  3 root of THAT (80 ms) 100 times
4454 ms to take the 3 root of a 100000 BYTE number (2999 ms) then take the  17 root of THAT (1455 ms) 100 times
7453 ms to take the 51 root of a 100000 BYTE number 100 times

6014 ms to take the 19 root of a 100000 BYTE number (5827 ms) then take the  3 root of THAT (187 ms) 100 times
4923 ms to take the 3 root of a 100000 BYTE number (3051 ms) then take the  19 root of THAT (1872 ms) 100 times
5950 ms to take the 57 root of a 100000 BYTE number 100 times

7316 ms to take the 23 root of a 100000 BYTE number (7286 ms) then take the  3 root of THAT (30 ms) 100 times
4517 ms to take the 3 root of a 100000 BYTE number (3111 ms) then take the  23 root of THAT (1406 ms) 100 times
4858 ms to take the 69 root of a 100000 BYTE number 100 times

8095 ms to take the 29 root of a 100000 BYTE number (8048 ms) then take the  3 root of THAT (47 ms) 100 times
4127 ms to take the 3 root of a 100000 BYTE number (3036 ms) then take the  29 root of THAT (1091 ms) 100 times
5032 ms to take the 87 root of a 100000 BYTE number 100 times

7155 ms to take the 31 root of a 100000 BYTE number (7109 ms) then take the  3 root of THAT (46 ms) 100 times
4470 ms to take the 3 root of a 100000 BYTE number (3019 ms) then take the  31 root of THAT (1451 ms) 100 times
4656 ms to take the 93 root of a 100000 BYTE number 100 times

5670 ms to take the 37 root of a 100000 BYTE number (5654 ms) then take the  3 root of THAT (16 ms) 100 times
4327 ms to take the 3 root of a 100000 BYTE number (3028 ms) then take the  37 root of THAT (1299 ms) 100 times
5768 ms to take the 111 root of a 100000 BYTE number 100 times

5091 ms to take the 41 root of a 100000 BYTE number (5060 ms) then take the  3 root of THAT (31 ms) 100 times
4235 ms to take the 3 root of a 100000 BYTE number (2981 ms) then take the  41 root of THAT (1254 ms) 100 times
5686 ms to take the 123 root of a 100000 BYTE number 100 times

6562 ms to take the 43 root of a 100000 BYTE number (6500 ms) then take the  3 root of THAT (62 ms) 100 times
4687 ms to take the 3 root of a 100000 BYTE number (3095 ms) then take the  43 root of THAT (1592 ms) 100 times
4467 ms to take the 129 root of a 100000 BYTE number 100 times

7219 ms to take the 47 root of a 100000 BYTE number (7189 ms) then take the  3 root of THAT (30 ms) 100 times
4373 ms to take the 3 root of a 100000 BYTE number (3230 ms) then take the  47 root of THAT (1143 ms) 100 times
4142 ms to take the 141 root of a 100000 BYTE number 100 times

6844 ms to take the 53 root of a 100000 BYTE number (6844 ms) then take the  3 root of THAT (0 ms) 100 times
4297 ms to take the 3 root of a 100000 BYTE number (3561 ms) then take the  53 root of THAT (736 ms) 100 times
3606 ms to take the 159 root of a 100000 BYTE number 100 times

8359 ms to take the 59 root of a 100000 BYTE number (8328 ms) then take the  3 root of THAT (31 ms) 100 times
3939 ms to take the 3 root of a 100000 BYTE number (3207 ms) then take the  59 root of THAT (732 ms) 100 times
2860 ms to take the 177 root of a 100000 BYTE number 100 times

7138 ms to take the 61 root of a 100000 BYTE number (7092 ms) then take the  3 root of THAT (46 ms) 100 times
3767 ms to take the 3 root of a 100000 BYTE number (3080 ms) then take the  61 root of THAT (687 ms) 100 times
3034 ms to take the 183 root of a 100000 BYTE number 100 times

5296 ms to take the 67 root of a 100000 BYTE number (5266 ms) then take the  3 root of THAT (30 ms) 100 times
3716 ms to take the 3 root of a 100000 BYTE number (3000 ms) then take the  67 root of THAT (716 ms) 100 times
2830 ms to take the 201 root of a 100000 BYTE number 100 times

9172 ms to take the 71 root of a 100000 BYTE number (9156 ms) then take the  3 root of THAT (16 ms) 100 times
3812 ms to take the 3 root of a 100000 BYTE number (3029 ms) then take the  71 root of THAT (783 ms) 100 times
2829 ms to take the 213 root of a 100000 BYTE number 100 times

6532 ms to take the 5 root of a 100000 BYTE number (5560 ms) then take the  5 root of THAT (972 ms) 100 times
7281 ms to take the 25 root of a 100000 BYTE number 100 times

4802 ms to take the 7 root of a 100000 BYTE number (4448 ms) then take the  5 root of THAT (354 ms) 100 times
6093 ms to take the 5 root of a 100000 BYTE number (5556 ms) then take the  7 root of THAT (537 ms) 100 times
6501 ms to take the 35 root of a 100000 BYTE number 100 times

6344 ms to take the 11 root of a 100000 BYTE number (6204 ms) then take the  5 root of THAT (140 ms) 100 times
7373 ms to take the 5 root of a 100000 BYTE number (6309 ms) then take the  11 root of THAT (1064 ms) 100 times
8516 ms to take the 55 root of a 100000 BYTE number 100 times

7205 ms to take the 13 root of a 100000 BYTE number (7031 ms) then take the  5 root of THAT (174 ms) 100 times
6687 ms to take the 5 root of a 100000 BYTE number (5815 ms) then take the  13 root of THAT (872 ms) 100 times
6049 ms to take the 65 root of a 100000 BYTE number 100 times

5108 ms to take the 17 root of a 100000 BYTE number (4969 ms) then take the  5 root of THAT (139 ms) 100 times
6654 ms to take the 5 root of a 100000 BYTE number (5843 ms) then take the  17 root of THAT (811 ms) 100 times
6909 ms to take the 85 root of a 100000 BYTE number 100 times

6781 ms to take the 19 root of a 100000 BYTE number (6673 ms) then take the  5 root of THAT (108 ms) 100 times
6621 ms to take the 5 root of a 100000 BYTE number (5759 ms) then take the  19 root of THAT (862 ms) 100 times
6422 ms to take the 95 root of a 100000 BYTE number 100 times

7736 ms to take the 23 root of a 100000 BYTE number (7625 ms) then take the  5 root of THAT (111 ms) 100 times
6676 ms to take the 5 root of a 100000 BYTE number (6082 ms) then take the  23 root of THAT (594 ms) 100 times
5577 ms to take the 115 root of a 100000 BYTE number 100 times

8469 ms to take the 29 root of a 100000 BYTE number (8423 ms) then take the  5 root of THAT (46 ms) 100 times
6235 ms to take the 5 root of a 100000 BYTE number (5655 ms) then take the  29 root of THAT (580 ms) 100 times
3593 ms to take the 145 root of a 100000 BYTE number 100 times

7221 ms to take the 31 root of a 100000 BYTE number (7174 ms) then take the  5 root of THAT (47 ms) 100 times
6204 ms to take the 5 root of a 100000 BYTE number (5609 ms) then take the  31 root of THAT (595 ms) 100 times
4404 ms to take the 155 root of a 100000 BYTE number 100 times

5298 ms to take the 37 root of a 100000 BYTE number (5267 ms) then take the  5 root of THAT (31 ms) 100 times
5828 ms to take the 5 root of a 100000 BYTE number (5419 ms) then take the  37 root of THAT (409 ms) 100 times
3469 ms to take the 185 root of a 100000 BYTE number 100 times

4998 ms to take the 41 root of a 100000 BYTE number (4935 ms) then take the  5 root of THAT (63 ms) 100 times
5674 ms to take the 5 root of a 100000 BYTE number (5360 ms) then take the  41 root of THAT (314 ms) 100 times
2873 ms to take the 205 root of a 100000 BYTE number 100 times

6281 ms to take the 43 root of a 100000 BYTE number (6281 ms) then take the  5 root of THAT (0 ms) 100 times
5719 ms to take the 5 root of a 100000 BYTE number (5435 ms) then take the  43 root of THAT (284 ms) 100 times
3328 ms to take the 215 root of a 100000 BYTE number 100 times

7125 ms to take the 47 root of a 100000 BYTE number (7078 ms) then take the  5 root of THAT (47 ms) 100 times
5906 ms to take the 5 root of a 100000 BYTE number (5516 ms) then take the  47 root of THAT (390 ms) 100 times
2844 ms to take the 235 root of a 100000 BYTE number 100 times

6033 ms to take the 53 root of a 100000 BYTE number (6033 ms) then take the  5 root of THAT (0 ms) 100 times
5735 ms to take the 5 root of a 100000 BYTE number (5438 ms) then take the  53 root of THAT (297 ms) 100 times
2669 ms to take the 265 root of a 100000 BYTE number 100 times

7452 ms to take the 59 root of a 100000 BYTE number (7452 ms) then take the  5 root of THAT (0 ms) 100 times
5750 ms to take the 5 root of a 100000 BYTE number (5405 ms) then take the  59 root of THAT (345 ms) 100 times
2844 ms to take the 295 root of a 100000 BYTE number 100 times

6796 ms to take the 61 root of a 100000 BYTE number (6796 ms) then take the  5 root of THAT (0 ms) 100 times
5767 ms to take the 5 root of a 100000 BYTE number (5343 ms) then take the  61 root of THAT (424 ms) 100 times
2625 ms to take the 305 root of a 100000 BYTE number 100 times

5187 ms to take the 67 root of a 100000 BYTE number (5171 ms) then take the  5 root of THAT (16 ms) 100 times
5876 ms to take the 5 root of a 100000 BYTE number (5598 ms) then take the  67 root of THAT (278 ms) 100 times
2874 ms to take the 335 root of a 100000 BYTE number 100 times

8736 ms to take the 71 root of a 100000 BYTE number (8736 ms) then take the  5 root of THAT (0 ms) 100 times
5628 ms to take the 5 root of a 100000 BYTE number (5363 ms) then take the  71 root of THAT (265 ms) 100 times
2740 ms to take the 355 root of a 100000 BYTE number 100 times

4830 ms to take the 7 root of a 100000 BYTE number (4413 ms) then take the  7 root of THAT (417 ms) 100 times
5486 ms to take the 49 root of a 100000 BYTE number 100 times

5938 ms to take the 11 root of a 100000 BYTE number (5502 ms) then take the  7 root of THAT (436 ms) 100 times
4862 ms to take the 7 root of a 100000 BYTE number (4461 ms) then take the  11 root of THAT (401 ms) 100 times
5344 ms to take the 77 root of a 100000 BYTE number 100 times

6454 ms to take the 13 root of a 100000 BYTE number (6343 ms) then take the  7 root of THAT (111 ms) 100 times
4764 ms to take the 7 root of a 100000 BYTE number (4388 ms) then take the  13 root of THAT (376 ms) 100 times
5171 ms to take the 91 root of a 100000 BYTE number 100 times

4890 ms to take the 17 root of a 100000 BYTE number (4734 ms) then take the  7 root of THAT (156 ms) 100 times
4873 ms to take the 7 root of a 100000 BYTE number (4339 ms) then take the  17 root of THAT (534 ms) 100 times
8691 ms to take the 119 root of a 100000 BYTE number 100 times

6091 ms to take the 19 root of a 100000 BYTE number (6011 ms) then take the  7 root of THAT (80 ms) 100 times
5001 ms to take the 7 root of a 100000 BYTE number (4642 ms) then take the  19 root of THAT (359 ms) 100 times
3952 ms to take the 133 root of a 100000 BYTE number 100 times

7467 ms to take the 23 root of a 100000 BYTE number (7451 ms) then take the  7 root of THAT (16 ms) 100 times
4809 ms to take the 7 root of a 100000 BYTE number (4589 ms) then take the  23 root of THAT (220 ms) 100 times
2752 ms to take the 161 root of a 100000 BYTE number 100 times

7908 ms to take the 29 root of a 100000 BYTE number (7877 ms) then take the  7 root of THAT (31 ms) 100 times
5147 ms to take the 7 root of a 100000 BYTE number (4866 ms) then take the  29 root of THAT (281 ms) 100 times
3590 ms to take the 203 root of a 100000 BYTE number 100 times

7350 ms to take the 31 root of a 100000 BYTE number (7318 ms) then take the  7 root of THAT (32 ms) 100 times
4745 ms to take the 7 root of a 100000 BYTE number (4491 ms) then take the  31 root of THAT (254 ms) 100 times
3156 ms to take the 217 root of a 100000 BYTE number 100 times

5716 ms to take the 37 root of a 100000 BYTE number (5653 ms) then take the  7 root of THAT (63 ms) 100 times
4892 ms to take the 7 root of a 100000 BYTE number (4642 ms) then take the  37 root of THAT (250 ms) 100 times
2998 ms to take the 259 root of a 100000 BYTE number 100 times

5816 ms to take the 41 root of a 100000 BYTE number (5769 ms) then take the  7 root of THAT (47 ms) 100 times
4906 ms to take the 7 root of a 100000 BYTE number (4625 ms) then take the  41 root of THAT (281 ms) 100 times
3972 ms to take the 287 root of a 100000 BYTE number 100 times

6485 ms to take the 43 root of a 100000 BYTE number (6455 ms) then take the  7 root of THAT (30 ms) 100 times
5030 ms to take the 7 root of a 100000 BYTE number (4734 ms) then take the  43 root of THAT (296 ms) 100 times
3530 ms to take the 301 root of a 100000 BYTE number 100 times

7359 ms to take the 47 root of a 100000 BYTE number (7344 ms) then take the  7 root of THAT (15 ms) 100 times
4799 ms to take the 7 root of a 100000 BYTE number (4562 ms) then take the  47 root of THAT (237 ms) 100 times
2921 ms to take the 329 root of a 100000 BYTE number 100 times

6389 ms to take the 53 root of a 100000 BYTE number (6373 ms) then take the  7 root of THAT (16 ms) 100 times
4876 ms to take the 7 root of a 100000 BYTE number (4677 ms) then take the  53 root of THAT (199 ms) 100 times
3017 ms to take the 371 root of a 100000 BYTE number 100 times

7545 ms to take the 59 root of a 100000 BYTE number (7514 ms) then take the  7 root of THAT (31 ms) 100 times
4671 ms to take the 7 root of a 100000 BYTE number (4513 ms) then take the  59 root of THAT (158 ms) 100 times
2703 ms to take the 413 root of a 100000 BYTE number 100 times

7000 ms to take the 61 root of a 100000 BYTE number (6984 ms) then take the  7 root of THAT (16 ms) 100 times
4766 ms to take the 7 root of a 100000 BYTE number (4470 ms) then take the  61 root of THAT (296 ms) 100 times
2844 ms to take the 427 root of a 100000 BYTE number 100 times

5639 ms to take the 67 root of a 100000 BYTE number (5639 ms) then take the  7 root of THAT (0 ms) 100 times
4653 ms to take the 7 root of a 100000 BYTE number (4433 ms) then take the  67 root of THAT (220 ms) 100 times
2704 ms to take the 469 root of a 100000 BYTE number 100 times

9076 ms to take the 71 root of a 100000 BYTE number (9060 ms) then take the  7 root of THAT (16 ms) 100 times
4628 ms to take the 7 root of a 100000 BYTE number (4443 ms) then take the  71 root of THAT (185 ms) 100 times
2844 ms to take the 497 root of a 100000 BYTE number 100 times

6143 ms to take the 11 root of a 100000 BYTE number (6001 ms) then take the  11 root of THAT (142 ms) 100 times
4686 ms to take the 121 root of a 100000 BYTE number 100 times

6673 ms to take the 13 root of a 100000 BYTE number (6549 ms) then take the  11 root of THAT (124 ms) 100 times
6077 ms to take the 11 root of a 100000 BYTE number (6000 ms) then take the  13 root of THAT (77 ms) 100 times
4591 ms to take the 143 root of a 100000 BYTE number 100 times

4829 ms to take the 17 root of a 100000 BYTE number (4751 ms) then take the  11 root of THAT (78 ms) 100 times
6748 ms to take the 11 root of a 100000 BYTE number (6670 ms) then take the  17 root of THAT (78 ms) 100 times
2986 ms to take the 187 root of a 100000 BYTE number 100 times

6125 ms to take the 19 root of a 100000 BYTE number (6047 ms) then take the  11 root of THAT (78 ms) 100 times
6029 ms to take the 11 root of a 100000 BYTE number (5874 ms) then take the  19 root of THAT (155 ms) 100 times
2751 ms to take the 209 root of a 100000 BYTE number 100 times

7327 ms to take the 23 root of a 100000 BYTE number (7265 ms) then take the  11 root of THAT (62 ms) 100 times
5924 ms to take the 11 root of a 100000 BYTE number (5782 ms) then take the  23 root of THAT (142 ms) 100 times
2796 ms to take the 253 root of a 100000 BYTE number 100 times

7780 ms to take the 29 root of a 100000 BYTE number (7764 ms) then take the  11 root of THAT (16 ms) 100 times
5999 ms to take the 11 root of a 100000 BYTE number (5921 ms) then take the  29 root of THAT (78 ms) 100 times
2937 ms to take the 319 root of a 100000 BYTE number 100 times

7206 ms to take the 31 root of a 100000 BYTE number (7145 ms) then take the  11 root of THAT (61 ms) 100 times
6498 ms to take the 11 root of a 100000 BYTE number (6341 ms) then take the  31 root of THAT (157 ms) 100 times
3060 ms to take the 341 root of a 100000 BYTE number 100 times

5765 ms to take the 37 root of a 100000 BYTE number (5750 ms) then take the  11 root of THAT (15 ms) 100 times
6126 ms to take the 11 root of a 100000 BYTE number (6047 ms) then take the  37 root of THAT (79 ms) 100 times
2813 ms to take the 407 root of a 100000 BYTE number 100 times

5061 ms to take the 41 root of a 100000 BYTE number (5014 ms) then take the  11 root of THAT (47 ms) 100 times
6060 ms to take the 11 root of a 100000 BYTE number (5933 ms) then take the  41 root of THAT (127 ms) 100 times
2763 ms to take the 451 root of a 100000 BYTE number 100 times

6236 ms to take the 43 root of a 100000 BYTE number (6236 ms) then take the  11 root of THAT (0 ms) 100 times
5967 ms to take the 11 root of a 100000 BYTE number (5858 ms) then take the  43 root of THAT (109 ms) 100 times
2769 ms to take the 473 root of a 100000 BYTE number 100 times

7188 ms to take the 47 root of a 100000 BYTE number (7188 ms) then take the  11 root of THAT (0 ms) 100 times
6308 ms to take the 11 root of a 100000 BYTE number (6199 ms) then take the  47 root of THAT (109 ms) 100 times
2919 ms to take the 517 root of a 100000 BYTE number 100 times

5984 ms to take the 53 root of a 100000 BYTE number (5984 ms) then take the  11 root of THAT (0 ms) 100 times
5957 ms to take the 11 root of a 100000 BYTE number (5847 ms) then take the  53 root of THAT (110 ms) 100 times
2764 ms to take the 583 root of a 100000 BYTE number 100 times

7610 ms to take the 59 root of a 100000 BYTE number (7610 ms) then take the  11 root of THAT (0 ms) 100 times
5935 ms to take the 11 root of a 100000 BYTE number (5841 ms) then take the  59 root of THAT (94 ms) 100 times
2607 ms to take the 649 root of a 100000 BYTE number 100 times

6985 ms to take the 61 root of a 100000 BYTE number (6985 ms) then take the  11 root of THAT (0 ms) 100 times
6001 ms to take the 11 root of a 100000 BYTE number (5969 ms) then take the  61 root of THAT (32 ms) 100 times
2968 ms to take the 671 root of a 100000 BYTE number 100 times

5361 ms to take the 67 root of a 100000 BYTE number (5345 ms) then take the  11 root of THAT (16 ms) 100 times
6051 ms to take the 11 root of a 100000 BYTE number (5876 ms) then take the  67 root of THAT (175 ms) 100 times
3109 ms to take the 737 root of a 100000 BYTE number 100 times

9094 ms to take the 71 root of a 100000 BYTE number (9078 ms) then take the  11 root of THAT (16 ms) 100 times
5987 ms to take the 11 root of a 100000 BYTE number (5831 ms) then take the  71 root of THAT (156 ms) 100 times
4484 ms to take the 781 root of a 100000 BYTE number 100 times

6487 ms to take the 13 root of a 100000 BYTE number (6347 ms) then take the  13 root of THAT (140 ms) 100 times
2891 ms to take the 169 root of a 100000 BYTE number 100 times

4873 ms to take the 17 root of a 100000 BYTE number (4809 ms) then take the  13 root of THAT (64 ms) 100 times
6625 ms to take the 13 root of a 100000 BYTE number (6530 ms) then take the  17 root of THAT (95 ms) 100 times
3014 ms to take the 221 root of a 100000 BYTE number 100 times

6030 ms to take the 19 root of a 100000 BYTE number (5967 ms) then take the  13 root of THAT (63 ms) 100 times
6548 ms to take the 13 root of a 100000 BYTE number (6454 ms) then take the  19 root of THAT (94 ms) 100 times
3125 ms to take the 247 root of a 100000 BYTE number 100 times

7625 ms to take the 23 root of a 100000 BYTE number (7562 ms) then take the  13 root of THAT (63 ms) 100 times
6471 ms to take the 13 root of a 100000 BYTE number (6302 ms) then take the  23 root of THAT (169 ms) 100 times
2891 ms to take the 299 root of a 100000 BYTE number 100 times

7918 ms to take the 29 root of a 100000 BYTE number (7902 ms) then take the  13 root of THAT (16 ms) 100 times
6487 ms to take the 13 root of a 100000 BYTE number (6457 ms) then take the  29 root of THAT (30 ms) 100 times
2735 ms to take the 377 root of a 100000 BYTE number 100 times

7172 ms to take the 31 root of a 100000 BYTE number (7141 ms) then take the  13 root of THAT (31 ms) 100 times
6578 ms to take the 13 root of a 100000 BYTE number (6437 ms) then take the  31 root of THAT (141 ms) 100 times
4283 ms to take the 403 root of a 100000 BYTE number 100 times

5389 ms to take the 37 root of a 100000 BYTE number (5358 ms) then take the  13 root of THAT (31 ms) 100 times
6530 ms to take the 13 root of a 100000 BYTE number (6419 ms) then take the  37 root of THAT (111 ms) 100 times
2988 ms to take the 481 root of a 100000 BYTE number 100 times

5233 ms to take the 41 root of a 100000 BYTE number (5233 ms) then take the  13 root of THAT (0 ms) 100 times
6531 ms to take the 13 root of a 100000 BYTE number (6439 ms) then take the  41 root of THAT (92 ms) 100 times
2686 ms to take the 533 root of a 100000 BYTE number 100 times

6376 ms to take the 43 root of a 100000 BYTE number (6376 ms) then take the  13 root of THAT (0 ms) 100 times
6499 ms to take the 13 root of a 100000 BYTE number (6483 ms) then take the  43 root of THAT (16 ms) 100 times
2704 ms to take the 559 root of a 100000 BYTE number 100 times

7186 ms to take the 47 root of a 100000 BYTE number (7171 ms) then take the  13 root of THAT (15 ms) 100 times
6425 ms to take the 13 root of a 100000 BYTE number (6379 ms) then take the  47 root of THAT (46 ms) 100 times
2813 ms to take the 611 root of a 100000 BYTE number 100 times

6065 ms to take the 53 root of a 100000 BYTE number (6065 ms) then take the  13 root of THAT (0 ms) 100 times
6533 ms to take the 13 root of a 100000 BYTE number (6470 ms) then take the  53 root of THAT (63 ms) 100 times
3513 ms to take the 689 root of a 100000 BYTE number 100 times

7513 ms to take the 59 root of a 100000 BYTE number (7513 ms) then take the  13 root of THAT (0 ms) 100 times
6531 ms to take the 13 root of a 100000 BYTE number (6436 ms) then take the  59 root of THAT (95 ms) 100 times
2625 ms to take the 767 root of a 100000 BYTE number 100 times

6907 ms to take the 61 root of a 100000 BYTE number (6876 ms) then take the  13 root of THAT (31 ms) 100 times
6452 ms to take the 13 root of a 100000 BYTE number (6420 ms) then take the  61 root of THAT (32 ms) 100 times
2627 ms to take the 793 root of a 100000 BYTE number 100 times

5501 ms to take the 67 root of a 100000 BYTE number (5486 ms) then take the  13 root of THAT (15 ms) 100 times
6466 ms to take the 13 root of a 100000 BYTE number (6387 ms) then take the  67 root of THAT (79 ms) 100 times
2688 ms to take the 871 root of a 100000 BYTE number 100 times

8998 ms to take the 71 root of a 100000 BYTE number (8982 ms) then take the  13 root of THAT (16 ms) 100 times
6578 ms to take the 13 root of a 100000 BYTE number (6563 ms) then take the  71 root of THAT (15 ms) 100 times
3376 ms to take the 923 root of a 100000 BYTE number 100 times

4873 ms to take the 17 root of a 100000 BYTE number (4857 ms) then take the  17 root of THAT (16 ms) 100 times
2639 ms to take the 289 root of a 100000 BYTE number 100 times

6030 ms to take the 19 root of a 100000 BYTE number (5935 ms) then take the  17 root of THAT (95 ms) 100 times
4891 ms to take the 17 root of a 100000 BYTE number (4766 ms) then take the  19 root of THAT (125 ms) 100 times
2814 ms to take the 323 root of a 100000 BYTE number 100 times

7345 ms to take the 23 root of a 100000 BYTE number (7314 ms) then take the  17 root of THAT (31 ms) 100 times
4922 ms to take the 17 root of a 100000 BYTE number (4874 ms) then take the  23 root of THAT (48 ms) 100 times
2937 ms to take the 391 root of a 100000 BYTE number 100 times

7859 ms to take the 29 root of a 100000 BYTE number (7828 ms) then take the  17 root of THAT (31 ms) 100 times
4844 ms to take the 17 root of a 100000 BYTE number (4748 ms) then take the  29 root of THAT (96 ms) 100 times
2687 ms to take the 493 root of a 100000 BYTE number 100 times

7205 ms to take the 31 root of a 100000 BYTE number (7205 ms) then take the  17 root of THAT (0 ms) 100 times
5263 ms to take the 17 root of a 100000 BYTE number (5200 ms) then take the  31 root of THAT (63 ms) 100 times
2751 ms to take the 527 root of a 100000 BYTE number 100 times

5422 ms to take the 37 root of a 100000 BYTE number (5375 ms) then take the  17 root of THAT (47 ms) 100 times
4890 ms to take the 17 root of a 100000 BYTE number (4827 ms) then take the  37 root of THAT (63 ms) 100 times
2828 ms to take the 629 root of a 100000 BYTE number 100 times

5127 ms to take the 41 root of a 100000 BYTE number (5111 ms) then take the  17 root of THAT (16 ms) 100 times
4857 ms to take the 17 root of a 100000 BYTE number (4777 ms) then take the  41 root of THAT (80 ms) 100 times
2814 ms to take the 697 root of a 100000 BYTE number 100 times

6079 ms to take the 43 root of a 100000 BYTE number (6047 ms) then take the  17 root of THAT (32 ms) 100 times
4861 ms to take the 17 root of a 100000 BYTE number (4799 ms) then take the  43 root of THAT (62 ms) 100 times
3594 ms to take the 731 root of a 100000 BYTE number 100 times

7137 ms to take the 47 root of a 100000 BYTE number (7090 ms) then take the  17 root of THAT (47 ms) 100 times
4877 ms to take the 17 root of a 100000 BYTE number (4799 ms) then take the  47 root of THAT (78 ms) 100 times
3282 ms to take the 799 root of a 100000 BYTE number 100 times

6248 ms to take the 53 root of a 100000 BYTE number (6216 ms) then take the  17 root of THAT (32 ms) 100 times
4781 ms to take the 17 root of a 100000 BYTE number (4720 ms) then take the  53 root of THAT (61 ms) 100 times
2752 ms to take the 901 root of a 100000 BYTE number 100 times

7644 ms to take the 59 root of a 100000 BYTE number (7629 ms) then take the  17 root of THAT (15 ms) 100 times
4873 ms to take the 17 root of a 100000 BYTE number (4795 ms) then take the  59 root of THAT (78 ms) 100 times
2845 ms to take the 1003 root of a 100000 BYTE number 100 times

6984 ms to take the 61 root of a 100000 BYTE number (6968 ms) then take the  17 root of THAT (16 ms) 100 times
4939 ms to take the 17 root of a 100000 BYTE number (4832 ms) then take the  61 root of THAT (107 ms) 100 times
4205 ms to take the 1037 root of a 100000 BYTE number 100 times

5375 ms to take the 67 root of a 100000 BYTE number (5375 ms) then take the  17 root of THAT (0 ms) 100 times
4826 ms to take the 17 root of a 100000 BYTE number (4778 ms) then take the  67 root of THAT (48 ms) 100 times
3171 ms to take the 1139 root of a 100000 BYTE number 100 times

9295 ms to take the 71 root of a 100000 BYTE number (9295 ms) then take the  17 root of THAT (0 ms) 100 times
5378 ms to take the 17 root of a 100000 BYTE number (5347 ms) then take the  71 root of THAT (31 ms) 100 times
3281 ms to take the 1207 root of a 100000 BYTE number 100 times

6485 ms to take the 19 root of a 100000 BYTE number (6438 ms) then take the  19 root of THAT (47 ms) 100 times
3016 ms to take the 361 root of a 100000 BYTE number 100 times

7518 ms to take the 23 root of a 100000 BYTE number (7422 ms) then take the  19 root of THAT (96 ms) 100 times
5908 ms to take the 19 root of a 100000 BYTE number (5876 ms) then take the  23 root of THAT (32 ms) 100 times
2670 ms to take the 437 root of a 100000 BYTE number 100 times

7672 ms to take the 29 root of a 100000 BYTE number (7656 ms) then take the  19 root of THAT (16 ms) 100 times
5876 ms to take the 19 root of a 100000 BYTE number (5845 ms) then take the  29 root of THAT (31 ms) 100 times
2655 ms to take the 551 root of a 100000 BYTE number 100 times

7218 ms to take the 31 root of a 100000 BYTE number (7186 ms) then take the  19 root of THAT (32 ms) 100 times
6172 ms to take the 19 root of a 100000 BYTE number (6077 ms) then take the  31 root of THAT (95 ms) 100 times
2578 ms to take the 589 root of a 100000 BYTE number 100 times

5392 ms to take the 37 root of a 100000 BYTE number (5376 ms) then take the  19 root of THAT (16 ms) 100 times
5922 ms to take the 19 root of a 100000 BYTE number (5860 ms) then take the  37 root of THAT (62 ms) 100 times
2701 ms to take the 703 root of a 100000 BYTE number 100 times

4988 ms to take the 41 root of a 100000 BYTE number (4956 ms) then take the  19 root of THAT (32 ms) 100 times
5922 ms to take the 19 root of a 100000 BYTE number (5859 ms) then take the  41 root of THAT (63 ms) 100 times
4389 ms to take the 779 root of a 100000 BYTE number 100 times

6160 ms to take the 43 root of a 100000 BYTE number (6128 ms) then take the  19 root of THAT (32 ms) 100 times
5905 ms to take the 19 root of a 100000 BYTE number (5889 ms) then take the  43 root of THAT (16 ms) 100 times
2545 ms to take the 817 root of a 100000 BYTE number 100 times

6970 ms to take the 47 root of a 100000 BYTE number (6970 ms) then take the  19 root of THAT (0 ms) 100 times
6220 ms to take the 19 root of a 100000 BYTE number (6141 ms) then take the  47 root of THAT (79 ms) 100 times
2889 ms to take the 893 root of a 100000 BYTE number 100 times

6063 ms to take the 53 root of a 100000 BYTE number (6048 ms) then take the  19 root of THAT (15 ms) 100 times
6014 ms to take the 19 root of a 100000 BYTE number (5951 ms) then take the  53 root of THAT (63 ms) 100 times
2875 ms to take the 1007 root of a 100000 BYTE number 100 times

7327 ms to take the 59 root of a 100000 BYTE number (7327 ms) then take the  19 root of THAT (0 ms) 100 times
5904 ms to take the 19 root of a 100000 BYTE number (5842 ms) then take the  59 root of THAT (62 ms) 100 times
3059 ms to take the 1121 root of a 100000 BYTE number 100 times

6765 ms to take the 61 root of a 100000 BYTE number (6765 ms) then take the  19 root of THAT (0 ms) 100 times
5938 ms to take the 19 root of a 100000 BYTE number (5922 ms) then take the  61 root of THAT (16 ms) 100 times
2736 ms to take the 1159 root of a 100000 BYTE number 100 times

5248 ms to take the 67 root of a 100000 BYTE number (5217 ms) then take the  19 root of THAT (31 ms) 100 times
5953 ms to take the 19 root of a 100000 BYTE number (5938 ms) then take the  67 root of THAT (15 ms) 100 times
3045 ms to take the 1273 root of a 100000 BYTE number 100 times

8875 ms to take the 71 root of a 100000 BYTE number (8875 ms) then take the  19 root of THAT (0 ms) 100 times
6001 ms to take the 19 root of a 100000 BYTE number (5938 ms) then take the  71 root of THAT (63 ms) 100 times
2736 ms to take the 1349 root of a 100000 BYTE number 100 times

7144 ms to take the 23 root of a 100000 BYTE number (7113 ms) then take the  23 root of THAT (31 ms) 100 times
2924 ms to take the 529 root of a 100000 BYTE number 100 times

7546 ms to take the 29 root of a 100000 BYTE number (7500 ms) then take the  23 root of THAT (46 ms) 100 times
7578 ms to take the 23 root of a 100000 BYTE number (7547 ms) then take the  29 root of THAT (31 ms) 100 times
2689 ms to take the 667 root of a 100000 BYTE number 100 times

7028 ms to take the 31 root of a 100000 BYTE number (7013 ms) then take the  23 root of THAT (15 ms) 100 times
7234 ms to take the 23 root of a 100000 BYTE number (7172 ms) then take the  31 root of THAT (62 ms) 100 times
3122 ms to take the 713 root of a 100000 BYTE number 100 times

5407 ms to take the 37 root of a 100000 BYTE number (5407 ms) then take the  23 root of THAT (0 ms) 100 times
7156 ms to take the 23 root of a 100000 BYTE number (7033 ms) then take the  37 root of THAT (123 ms) 100 times
2639 ms to take the 851 root of a 100000 BYTE number 100 times

5031 ms to take the 41 root of a 100000 BYTE number (4968 ms) then take the  23 root of THAT (63 ms) 100 times
7204 ms to take the 23 root of a 100000 BYTE number (7189 ms) then take the  41 root of THAT (15 ms) 100 times
2686 ms to take the 943 root of a 100000 BYTE number 100 times

6027 ms to take the 43 root of a 100000 BYTE number (5997 ms) then take the  23 root of THAT (30 ms) 100 times
7660 ms to take the 23 root of a 100000 BYTE number (7614 ms) then take the  43 root of THAT (46 ms) 100 times
2844 ms to take the 989 root of a 100000 BYTE number 100 times

7046 ms to take the 47 root of a 100000 BYTE number (7030 ms) then take the  23 root of THAT (16 ms) 100 times
7029 ms to take the 23 root of a 100000 BYTE number (6982 ms) then take the  47 root of THAT (47 ms) 100 times
3486 ms to take the 1081 root of a 100000 BYTE number 100 times

6092 ms to take the 53 root of a 100000 BYTE number (6045 ms) then take the  23 root of THAT (47 ms) 100 times
7048 ms to take the 23 root of a 100000 BYTE number (7032 ms) then take the  53 root of THAT (16 ms) 100 times
2673 ms to take the 1219 root of a 100000 BYTE number 100 times

7424 ms to take the 59 root of a 100000 BYTE number (7424 ms) then take the  23 root of THAT (0 ms) 100 times
7081 ms to take the 23 root of a 100000 BYTE number (7065 ms) then take the  59 root of THAT (16 ms) 100 times
2814 ms to take the 1357 root of a 100000 BYTE number 100 times

6721 ms to take the 61 root of a 100000 BYTE number (6721 ms) then take the  23 root of THAT (0 ms) 100 times
7232 ms to take the 23 root of a 100000 BYTE number (7154 ms) then take the  61 root of THAT (78 ms) 100 times
2955 ms to take the 1403 root of a 100000 BYTE number 100 times

5170 ms to take the 67 root of a 100000 BYTE number (5155 ms) then take the  23 root of THAT (15 ms) 100 times
7374 ms to take the 23 root of a 100000 BYTE number (7374 ms) then take the  67 root of THAT (0 ms) 100 times
4171 ms to take the 1541 root of a 100000 BYTE number 100 times

8686 ms to take the 71 root of a 100000 BYTE number (8686 ms) then take the  23 root of THAT (0 ms) 100 times
7012 ms to take the 23 root of a 100000 BYTE number (6996 ms) then take the  71 root of THAT (16 ms) 100 times
3127 ms to take the 1633 root of a 100000 BYTE number 100 times

7515 ms to take the 29 root of a 100000 BYTE number (7467 ms) then take the  29 root of THAT (48 ms) 100 times
2674 ms to take the 841 root of a 100000 BYTE number 100 times

7061 ms to take the 31 root of a 100000 BYTE number (6983 ms) then take the  29 root of THAT (78 ms) 100 times
7655 ms to take the 29 root of a 100000 BYTE number (7609 ms) then take the  31 root of THAT (46 ms) 100 times
2735 ms to take the 899 root of a 100000 BYTE number 100 times

5312 ms to take the 37 root of a 100000 BYTE number (5312 ms) then take the  29 root of THAT (0 ms) 100 times
7684 ms to take the 29 root of a 100000 BYTE number (7669 ms) then take the  37 root of THAT (15 ms) 100 times
3092 ms to take the 1073 root of a 100000 BYTE number 100 times

5000 ms to take the 41 root of a 100000 BYTE number (4969 ms) then take the  29 root of THAT (31 ms) 100 times
7592 ms to take the 29 root of a 100000 BYTE number (7576 ms) then take the  41 root of THAT (16 ms) 100 times
2890 ms to take the 1189 root of a 100000 BYTE number 100 times

5878 ms to take the 43 root of a 100000 BYTE number (5878 ms) then take the  29 root of THAT (0 ms) 100 times
7564 ms to take the 29 root of a 100000 BYTE number (7564 ms) then take the  43 root of THAT (0 ms) 100 times
4155 ms to take the 1247 root of a 100000 BYTE number 100 times

7093 ms to take the 47 root of a 100000 BYTE number (7093 ms) then take the  29 root of THAT (0 ms) 100 times
7608 ms to take the 29 root of a 100000 BYTE number (7545 ms) then take the  47 root of THAT (63 ms) 100 times
2889 ms to take the 1363 root of a 100000 BYTE number 100 times

5987 ms to take the 53 root of a 100000 BYTE number (5955 ms) then take the  29 root of THAT (32 ms) 100 times
8252 ms to take the 29 root of a 100000 BYTE number (8236 ms) then take the  53 root of THAT (16 ms) 100 times
4190 ms to take the 1537 root of a 100000 BYTE number 100 times

7454 ms to take the 59 root of a 100000 BYTE number (7454 ms) then take the  29 root of THAT (0 ms) 100 times
7533 ms to take the 29 root of a 100000 BYTE number (7517 ms) then take the  59 root of THAT (16 ms) 100 times
2810 ms to take the 1711 root of a 100000 BYTE number 100 times

6857 ms to take the 61 root of a 100000 BYTE number (6857 ms) then take the  29 root of THAT (0 ms) 100 times
7594 ms to take the 29 root of a 100000 BYTE number (7578 ms) then take the  61 root of THAT (16 ms) 100 times
4423 ms to take the 1769 root of a 100000 BYTE number 100 times

5218 ms to take the 67 root of a 100000 BYTE number (5202 ms) then take the  29 root of THAT (16 ms) 100 times
7610 ms to take the 29 root of a 100000 BYTE number (7595 ms) then take the  67 root of THAT (15 ms) 100 times
2892 ms to take the 1943 root of a 100000 BYTE number 100 times

9092 ms to take the 71 root of a 100000 BYTE number (9076 ms) then take the  29 root of THAT (16 ms) 100 times
7483 ms to take the 29 root of a 100000 BYTE number (7451 ms) then take the  71 root of THAT (32 ms) 100 times
4514 ms to take the 2059 root of a 100000 BYTE number 100 times

7328 ms to take the 31 root of a 100000 BYTE number (7312 ms) then take the  31 root of THAT (16 ms) 100 times
4233 ms to take the 961 root of a 100000 BYTE number 100 times

5436 ms to take the 37 root of a 100000 BYTE number (5421 ms) then take the  31 root of THAT (15 ms) 100 times
7092 ms to take the 31 root of a 100000 BYTE number (7029 ms) then take the  37 root of THAT (63 ms) 100 times
2955 ms to take the 1147 root of a 100000 BYTE number 100 times

5064 ms to take the 41 root of a 100000 BYTE number (5064 ms) then take the  31 root of THAT (0 ms) 100 times
7251 ms to take the 31 root of a 100000 BYTE number (7206 ms) then take the  41 root of THAT (45 ms) 100 times
2878 ms to take the 1271 root of a 100000 BYTE number 100 times

6485 ms to take the 43 root of a 100000 BYTE number (6454 ms) then take the  31 root of THAT (31 ms) 100 times
7093 ms to take the 31 root of a 100000 BYTE number (7078 ms) then take the  43 root of THAT (15 ms) 100 times
2752 ms to take the 1333 root of a 100000 BYTE number 100 times

7269 ms to take the 47 root of a 100000 BYTE number (7254 ms) then take the  31 root of THAT (15 ms) 100 times
7204 ms to take the 31 root of a 100000 BYTE number (7188 ms) then take the  47 root of THAT (16 ms) 100 times
2827 ms to take the 1457 root of a 100000 BYTE number 100 times

6249 ms to take the 53 root of a 100000 BYTE number (6249 ms) then take the  31 root of THAT (0 ms) 100 times
7203 ms to take the 31 root of a 100000 BYTE number (7203 ms) then take the  53 root of THAT (0 ms) 100 times
3342 ms to take the 1643 root of a 100000 BYTE number 100 times

7419 ms to take the 59 root of a 100000 BYTE number (7419 ms) then take the  31 root of THAT (0 ms) 100 times
7737 ms to take the 31 root of a 100000 BYTE number (7689 ms) then take the  59 root of THAT (48 ms) 100 times
3621 ms to take the 1829 root of a 100000 BYTE number 100 times

7954 ms to take the 61 root of a 100000 BYTE number (7923 ms) then take the  31 root of THAT (31 ms) 100 times
7886 ms to take the 31 root of a 100000 BYTE number (7854 ms) then take the  61 root of THAT (32 ms) 100 times
3312 ms to take the 1891 root of a 100000 BYTE number 100 times

5297 ms to take the 67 root of a 100000 BYTE number (5297 ms) then take the  31 root of THAT (0 ms) 100 times
7096 ms to take the 31 root of a 100000 BYTE number (7065 ms) then take the  67 root of THAT (31 ms) 100 times
4372 ms to take the 2077 root of a 100000 BYTE number 100 times

8952 ms to take the 71 root of a 100000 BYTE number (8952 ms) then take the  31 root of THAT (0 ms) 100 times
7061 ms to take the 31 root of a 100000 BYTE number (7014 ms) then take the  71 root of THAT (47 ms) 100 times
3109 ms to take the 2201 root of a 100000 BYTE number 100 times

5563 ms to take the 37 root of a 100000 BYTE number (5547 ms) then take the  37 root of THAT (16 ms) 100 times
3687 ms to take the 1369 root of a 100000 BYTE number 100 times

4953 ms to take the 41 root of a 100000 BYTE number (4953 ms) then take the  37 root of THAT (0 ms) 100 times
5327 ms to take the 37 root of a 100000 BYTE number (5327 ms) then take the  41 root of THAT (0 ms) 100 times
2642 ms to take the 1517 root of a 100000 BYTE number 100 times

6157 ms to take the 43 root of a 100000 BYTE number (6157 ms) then take the  37 root of THAT (0 ms) 100 times
5407 ms to take the 37 root of a 100000 BYTE number (5391 ms) then take the  43 root of THAT (16 ms) 100 times
2844 ms to take the 1591 root of a 100000 BYTE number 100 times

7189 ms to take the 47 root of a 100000 BYTE number (7189 ms) then take the  37 root of THAT (0 ms) 100 times
5391 ms to take the 37 root of a 100000 BYTE number (5328 ms) then take the  47 root of THAT (63 ms) 100 times
2938 ms to take the 1739 root of a 100000 BYTE number 100 times

6003 ms to take the 53 root of a 100000 BYTE number (5988 ms) then take the  37 root of THAT (15 ms) 100 times
5375 ms to take the 37 root of a 100000 BYTE number (5360 ms) then take the  53 root of THAT (15 ms) 100 times
3017 ms to take the 1961 root of a 100000 BYTE number 100 times

7800 ms to take the 59 root of a 100000 BYTE number (7800 ms) then take the  37 root of THAT (0 ms) 100 times
5278 ms to take the 37 root of a 100000 BYTE number (5231 ms) then take the  59 root of THAT (47 ms) 100 times
3078 ms to take the 2183 root of a 100000 BYTE number 100 times

6905 ms to take the 61 root of a 100000 BYTE number (6873 ms) then take the  37 root of THAT (32 ms) 100 times
5419 ms to take the 37 root of a 100000 BYTE number (5389 ms) then take the  61 root of THAT (30 ms) 100 times
3735 ms to take the 2257 root of a 100000 BYTE number 100 times

5299 ms to take the 67 root of a 100000 BYTE number (5284 ms) then take the  37 root of THAT (15 ms) 100 times
5408 ms to take the 37 root of a 100000 BYTE number (5361 ms) then take the  67 root of THAT (47 ms) 100 times
5264 ms to take the 2479 root of a 100000 BYTE number 100 times

8889 ms to take the 71 root of a 100000 BYTE number (8858 ms) then take the  37 root of THAT (31 ms) 100 times
5500 ms to take the 37 root of a 100000 BYTE number (5468 ms) then take the  71 root of THAT (32 ms) 100 times
3499 ms to take the 2627 root of a 100000 BYTE number 100 times

5046 ms to take the 41 root of a 100000 BYTE number (5046 ms) then take the  41 root of THAT (0 ms) 100 times
2938 ms to take the 1681 root of a 100000 BYTE number 100 times

6076 ms to take the 43 root of a 100000 BYTE number (6060 ms) then take the  41 root of THAT (16 ms) 100 times
5189 ms to take the 41 root of a 100000 BYTE number (5189 ms) then take the  43 root of THAT (0 ms) 100 times
3998 ms to take the 1763 root of a 100000 BYTE number 100 times

7203 ms to take the 47 root of a 100000 BYTE number (7203 ms) then take the  41 root of THAT (0 ms) 100 times
5044 ms to take the 41 root of a 100000 BYTE number (5044 ms) then take the  47 root of THAT (0 ms) 100 times
3047 ms to take the 1927 root of a 100000 BYTE number 100 times

6281 ms to take the 53 root of a 100000 BYTE number (6265 ms) then take the  41 root of THAT (16 ms) 100 times
5203 ms to take the 41 root of a 100000 BYTE number (5172 ms) then take the  53 root of THAT (31 ms) 100 times
3063 ms to take the 2173 root of a 100000 BYTE number 100 times

7545 ms to take the 59 root of a 100000 BYTE number (7545 ms) then take the  41 root of THAT (0 ms) 100 times
5329 ms to take the 41 root of a 100000 BYTE number (5329 ms) then take the  59 root of THAT (0 ms) 100 times
3531 ms to take the 2419 root of a 100000 BYTE number 100 times

6999 ms to take the 61 root of a 100000 BYTE number (6999 ms) then take the  41 root of THAT (0 ms) 100 times
5108 ms to take the 41 root of a 100000 BYTE number (5093 ms) then take the  61 root of THAT (15 ms) 100 times
3593 ms to take the 2501 root of a 100000 BYTE number 100 times

5514 ms to take the 67 root of a 100000 BYTE number (5499 ms) then take the  41 root of THAT (15 ms) 100 times
5217 ms to take the 41 root of a 100000 BYTE number (5201 ms) then take the  67 root of THAT (16 ms) 100 times
3516 ms to take the 2747 root of a 100000 BYTE number 100 times

9344 ms to take the 71 root of a 100000 BYTE number (9344 ms) then take the  41 root of THAT (0 ms) 100 times
5138 ms to take the 41 root of a 100000 BYTE number (5123 ms) then take the  71 root of THAT (15 ms) 100 times
3030 ms to take the 2911 root of a 100000 BYTE number 100 times

6470 ms to take the 43 root of a 100000 BYTE number (6455 ms) then take the  43 root of THAT (15 ms) 100 times
3150 ms to take the 1849 root of a 100000 BYTE number 100 times

7514 ms to take the 47 root of a 100000 BYTE number (7498 ms) then take the  43 root of THAT (16 ms) 100 times
6360 ms to take the 43 root of a 100000 BYTE number (6360 ms) then take the  47 root of THAT (0 ms) 100 times
3127 ms to take the 2021 root of a 100000 BYTE number 100 times

6328 ms to take the 53 root of a 100000 BYTE number (6328 ms) then take the  43 root of THAT (0 ms) 100 times
6438 ms to take the 43 root of a 100000 BYTE number (6422 ms) then take the  53 root of THAT (16 ms) 100 times
3391 ms to take the 2279 root of a 100000 BYTE number 100 times

7908 ms to take the 59 root of a 100000 BYTE number (7892 ms) then take the  43 root of THAT (16 ms) 100 times
6375 ms to take the 43 root of a 100000 BYTE number (6360 ms) then take the  59 root of THAT (15 ms) 100 times
3578 ms to take the 2537 root of a 100000 BYTE number 100 times

6985 ms to take the 61 root of a 100000 BYTE number (6985 ms) then take the  43 root of THAT (0 ms) 100 times
6533 ms to take the 43 root of a 100000 BYTE number (6518 ms) then take the  61 root of THAT (15 ms) 100 times
3280 ms to take the 2623 root of a 100000 BYTE number 100 times

5283 ms to take the 67 root of a 100000 BYTE number (5283 ms) then take the  43 root of THAT (0 ms) 100 times
6154 ms to take the 43 root of a 100000 BYTE number (6138 ms) then take the  67 root of THAT (16 ms) 100 times
2941 ms to take the 2881 root of a 100000 BYTE number 100 times

9080 ms to take the 71 root of a 100000 BYTE number (9080 ms) then take the  43 root of THAT (0 ms) 100 times
6139 ms to take the 43 root of a 100000 BYTE number (6139 ms) then take the  71 root of THAT (0 ms) 100 times
5783 ms to take the 3053 root of a 100000 BYTE number 100 times

7141 ms to take the 47 root of a 100000 BYTE number (7141 ms) then take the  47 root of THAT (0 ms) 100 times
3248 ms to take the 2209 root of a 100000 BYTE number 100 times

6001 ms to take the 53 root of a 100000 BYTE number (5955 ms) then take the  47 root of THAT (46 ms) 100 times
7344 ms to take the 47 root of a 100000 BYTE number (7344 ms) then take the  53 root of THAT (0 ms) 100 times
4075 ms to take the 2491 root of a 100000 BYTE number 100 times

7515 ms to take the 59 root of a 100000 BYTE number (7500 ms) then take the  47 root of THAT (15 ms) 100 times
7059 ms to take the 47 root of a 100000 BYTE number (7027 ms) then take the  59 root of THAT (32 ms) 100 times
3061 ms to take the 2773 root of a 100000 BYTE number 100 times

6780 ms to take the 61 root of a 100000 BYTE number (6764 ms) then take the  47 root of THAT (16 ms) 100 times
7078 ms to take the 47 root of a 100000 BYTE number (7078 ms) then take the  61 root of THAT (0 ms) 100 times
3125 ms to take the 2867 root of a 100000 BYTE number 100 times

5296 ms to take the 67 root of a 100000 BYTE number (5280 ms) then take the  47 root of THAT (16 ms) 100 times
7108 ms to take the 47 root of a 100000 BYTE number (7062 ms) then take the  67 root of THAT (46 ms) 100 times
3360 ms to take the 3149 root of a 100000 BYTE number 100 times

9125 ms to take the 71 root of a 100000 BYTE number (9110 ms) then take the  47 root of THAT (15 ms) 100 times
7127 ms to take the 47 root of a 100000 BYTE number (7081 ms) then take the  71 root of THAT (46 ms) 100 times
3109 ms to take the 3337 root of a 100000 BYTE number 100 times

5955 ms to take the 53 root of a 100000 BYTE number (5955 ms) then take the  53 root of THAT (0 ms) 100 times
3077 ms to take the 2809 root of a 100000 BYTE number 100 times

7561 ms to take the 59 root of a 100000 BYTE number (7546 ms) then take the  53 root of THAT (15 ms) 100 times
5924 ms to take the 53 root of a 100000 BYTE number (5924 ms) then take the  59 root of THAT (0 ms) 100 times
3453 ms to take the 3127 root of a 100000 BYTE number 100 times

6892 ms to take the 61 root of a 100000 BYTE number (6892 ms) then take the  53 root of THAT (0 ms) 100 times
6203 ms to take the 53 root of a 100000 BYTE number (6203 ms) then take the  61 root of THAT (0 ms) 100 times
3184 ms to take the 3233 root of a 100000 BYTE number 100 times

5267 ms to take the 67 root of a 100000 BYTE number (5267 ms) then take the  53 root of THAT (0 ms) 100 times
6420 ms to take the 53 root of a 100000 BYTE number (6420 ms) then take the  67 root of THAT (0 ms) 100 times
3625 ms to take the 3551 root of a 100000 BYTE number 100 times

8906 ms to take the 71 root of a 100000 BYTE number (8906 ms) then take the  53 root of THAT (0 ms) 100 times
5956 ms to take the 53 root of a 100000 BYTE number (5925 ms) then take the  71 root of THAT (31 ms) 100 times
3327 ms to take the 3763 root of a 100000 BYTE number 100 times

7578 ms to take the 59 root of a 100000 BYTE number (7578 ms) then take the  59 root of THAT (0 ms) 100 times
3907 ms to take the 3481 root of a 100000 BYTE number 100 times

6938 ms to take the 61 root of a 100000 BYTE number (6891 ms) then take the  59 root of THAT (47 ms) 100 times
7577 ms to take the 59 root of a 100000 BYTE number (7577 ms) then take the  61 root of THAT (0 ms) 100 times
3565 ms to take the 3599 root of a 100000 BYTE number 100 times

5266 ms to take the 67 root of a 100000 BYTE number (5266 ms) then take the  59 root of THAT (0 ms) 100 times
7876 ms to take the 59 root of a 100000 BYTE number (7860 ms) then take the  67 root of THAT (16 ms) 100 times
4204 ms to take the 3953 root of a 100000 BYTE number 100 times

8905 ms to take the 71 root of a 100000 BYTE number (8905 ms) then take the  59 root of THAT (0 ms) 100 times
7970 ms to take the 59 root of a 100000 BYTE number (7970 ms) then take the  71 root of THAT (0 ms) 100 times
4953 ms to take the 4189 root of a 100000 BYTE number 100 times

7749 ms to take the 61 root of a 100000 BYTE number (7733 ms) then take the  61 root of THAT (16 ms) 100 times
3800 ms to take the 3721 root of a 100000 BYTE number 100 times

6123 ms to take the 67 root of a 100000 BYTE number (6077 ms) then take the  61 root of THAT (46 ms) 100 times
7014 ms to take the 61 root of a 100000 BYTE number (6982 ms) then take the  67 root of THAT (32 ms) 100 times
4437 ms to take the 4087 root of a 100000 BYTE number 100 times

9298 ms to take the 71 root of a 100000 BYTE number (9298 ms) then take the  61 root of THAT (0 ms) 100 times
7016 ms to take the 61 root of a 100000 BYTE number (7001 ms) then take the  71 root of THAT (15 ms) 100 times
3907 ms to take the 4331 root of a 100000 BYTE number 100 times

5391 ms to take the 67 root of a 100000 BYTE number (5359 ms) then take the  67 root of THAT (32 ms) 100 times
3830 ms to take the 4489 root of a 100000 BYTE number 100 times

8953 ms to take the 71 root of a 100000 BYTE number (8953 ms) then take the  67 root of THAT (0 ms) 100 times
5344 ms to take the 67 root of a 100000 BYTE number (5328 ms) then take the  71 root of THAT (16 ms) 100 times
5013 ms to take the 4757 root of a 100000 BYTE number 100 times

8798 ms to take the 71 root of a 100000 BYTE number (8798 ms) then take the  71 root of THAT (0 ms) 100 times
3673 ms to take the 5041 root of a 100000 BYTE number 100 times

4139 ms to take the 2 root of a 1000000 BYTE number (2969 ms) then take the  2 root of THAT (1170 ms) 10 times
7987 ms to take the 4 root of a 1000000 BYTE number 10 times

5768 ms to take the 3 root of a 1000000 BYTE number (5034 ms) then take the  2 root of THAT (734 ms) 10 times
5642 ms to take the 2 root of a 1000000 BYTE number (2969 ms) then take the  3 root of THAT (2673 ms) 10 times
9703 ms to take the 6 root of a 1000000 BYTE number 10 times

8486 ms to take the 5 root of a 1000000 BYTE number (8126 ms) then take the  2 root of THAT (360 ms) 10 times
6970 ms to take the 2 root of a 1000000 BYTE number (2923 ms) then take the  5 root of THAT (4047 ms) 10 times
13515 ms to take the 10 root of a 1000000 BYTE number 10 times

8937 ms to take the 7 root of a 1000000 BYTE number (8658 ms) then take the  2 root of THAT (279 ms) 10 times
6732 ms to take the 2 root of a 1000000 BYTE number (2982 ms) then take the  7 root of THAT (3750 ms) 10 times
11623 ms to take the 14 root of a 1000000 BYTE number 10 times

8375 ms to take the 11 root of a 1000000 BYTE number (8281 ms) then take the  2 root of THAT (94 ms) 10 times
6517 ms to take the 2 root of a 1000000 BYTE number (2953 ms) then take the  11 root of THAT (3564 ms) 10 times
10621 ms to take the 22 root of a 1000000 BYTE number 10 times

8216 ms to take the 13 root of a 1000000 BYTE number (8138 ms) then take the  2 root of THAT (78 ms) 10 times
6315 ms to take the 2 root of a 1000000 BYTE number (3031 ms) then take the  13 root of THAT (3284 ms) 10 times
11001 ms to take the 26 root of a 1000000 BYTE number 10 times

6407 ms to take the 17 root of a 1000000 BYTE number (6328 ms) then take the  2 root of THAT (79 ms) 10 times
5858 ms to take the 2 root of a 1000000 BYTE number (2920 ms) then take the  17 root of THAT (2938 ms) 10 times
9407 ms to take the 34 root of a 1000000 BYTE number 10 times

7812 ms to take the 19 root of a 1000000 BYTE number (7782 ms) then take the  2 root of THAT (30 ms) 10 times
6438 ms to take the 2 root of a 1000000 BYTE number (2921 ms) then take the  19 root of THAT (3517 ms) 10 times
9811 ms to take the 38 root of a 1000000 BYTE number 10 times

8736 ms to take the 23 root of a 1000000 BYTE number (8704 ms) then take the  2 root of THAT (32 ms) 10 times
7062 ms to take the 2 root of a 1000000 BYTE number (2984 ms) then take the  23 root of THAT (4078 ms) 10 times
10595 ms to take the 46 root of a 1000000 BYTE number 10 times

8032 ms to take the 29 root of a 1000000 BYTE number (8032 ms) then take the  2 root of THAT (0 ms) 10 times
6487 ms to take the 2 root of a 1000000 BYTE number (3001 ms) then take the  29 root of THAT (3486 ms) 10 times
10999 ms to take the 58 root of a 1000000 BYTE number 10 times

10078 ms to take the 31 root of a 1000000 BYTE number (10047 ms) then take the  2 root of THAT (31 ms) 10 times
7563 ms to take the 2 root of a 1000000 BYTE number (2938 ms) then take the  31 root of THAT (4625 ms) 10 times
12841 ms to take the 62 root of a 1000000 BYTE number 10 times

6688 ms to take the 37 root of a 1000000 BYTE number (6672 ms) then take the  2 root of THAT (16 ms) 10 times
6017 ms to take the 2 root of a 1000000 BYTE number (2938 ms) then take the  37 root of THAT (3079 ms) 10 times
9266 ms to take the 74 root of a 1000000 BYTE number 10 times

6391 ms to take the 41 root of a 1000000 BYTE number (6359 ms) then take the  2 root of THAT (32 ms) 10 times
5845 ms to take the 2 root of a 1000000 BYTE number (2922 ms) then take the  41 root of THAT (2923 ms) 10 times
9174 ms to take the 82 root of a 1000000 BYTE number 10 times

8157 ms to take the 43 root of a 1000000 BYTE number (8141 ms) then take the  2 root of THAT (16 ms) 10 times
6676 ms to take the 2 root of a 1000000 BYTE number (2956 ms) then take the  43 root of THAT (3720 ms) 10 times
10266 ms to take the 86 root of a 1000000 BYTE number 10 times

10516 ms to take the 47 root of a 1000000 BYTE number (10516 ms) then take the  2 root of THAT (0 ms) 10 times
7014 ms to take the 2 root of a 1000000 BYTE number (2951 ms) then take the  47 root of THAT (4063 ms) 10 times
10624 ms to take the 94 root of a 1000000 BYTE number 10 times

7609 ms to take the 53 root of a 1000000 BYTE number (7578 ms) then take the  2 root of THAT (31 ms) 10 times
6329 ms to take the 2 root of a 1000000 BYTE number (2905 ms) then take the  53 root of THAT (3424 ms) 10 times
10269 ms to take the 106 root of a 1000000 BYTE number 10 times

9440 ms to take the 59 root of a 1000000 BYTE number (9424 ms) then take the  2 root of THAT (16 ms) 10 times
7187 ms to take the 2 root of a 1000000 BYTE number (2999 ms) then take the  59 root of THAT (4188 ms) 10 times
11546 ms to take the 118 root of a 1000000 BYTE number 10 times

8125 ms to take the 61 root of a 1000000 BYTE number (8110 ms) then take the  2 root of THAT (15 ms) 10 times
6752 ms to take the 2 root of a 1000000 BYTE number (2971 ms) then take the  61 root of THAT (3781 ms) 10 times
11203 ms to take the 122 root of a 1000000 BYTE number 10 times

8188 ms to take the 67 root of a 1000000 BYTE number (8157 ms) then take the  2 root of THAT (31 ms) 10 times
7484 ms to take the 2 root of a 1000000 BYTE number (2986 ms) then take the  67 root of THAT (4498 ms) 10 times
12062 ms to take the 134 root of a 1000000 BYTE number 10 times

8062 ms to take the 71 root of a 1000000 BYTE number (8062 ms) then take the  2 root of THAT (0 ms) 10 times
6641 ms to take the 2 root of a 1000000 BYTE number (2921 ms) then take the  71 root of THAT (3720 ms) 10 times
9735 ms to take the 142 root of a 1000000 BYTE number 10 times

6424 ms to take the 3 root of a 1000000 BYTE number (4984 ms) then take the  3 root of THAT (1440 ms) 10 times
6562 ms to take the 9 root of a 1000000 BYTE number 10 times

9092 ms to take the 5 root of a 1000000 BYTE number (8109 ms) then take the  3 root of THAT (983 ms) 10 times
7736 ms to take the 3 root of a 1000000 BYTE number (5437 ms) then take the  5 root of THAT (2299 ms) 10 times
9656 ms to take the 15 root of a 1000000 BYTE number 10 times

8968 ms to take the 7 root of a 1000000 BYTE number (8375 ms) then take the  3 root of THAT (593 ms) 10 times
7251 ms to take the 3 root of a 1000000 BYTE number (5000 ms) then take the  7 root of THAT (2251 ms) 10 times
7157 ms to take the 21 root of a 1000000 BYTE number 10 times

8503 ms to take the 11 root of a 1000000 BYTE number (8248 ms) then take the  3 root of THAT (255 ms) 10 times
7248 ms to take the 3 root of a 1000000 BYTE number (4922 ms) then take the  11 root of THAT (2326 ms) 10 times
6250 ms to take the 33 root of a 1000000 BYTE number 10 times

8235 ms to take the 13 root of a 1000000 BYTE number (8079 ms) then take the  3 root of THAT (156 ms) 10 times
7047 ms to take the 3 root of a 1000000 BYTE number (4922 ms) then take the  13 root of THAT (2125 ms) 10 times
8327 ms to take the 39 root of a 1000000 BYTE number 10 times

6549 ms to take the 17 root of a 1000000 BYTE number (6359 ms) then take the  3 root of THAT (190 ms) 10 times
7172 ms to take the 3 root of a 1000000 BYTE number (4922 ms) then take the  17 root of THAT (2250 ms) 10 times
8359 ms to take the 51 root of a 1000000 BYTE number 10 times

8015 ms to take the 19 root of a 1000000 BYTE number (7829 ms) then take the  3 root of THAT (186 ms) 10 times
7874 ms to take the 3 root of a 1000000 BYTE number (4904 ms) then take the  19 root of THAT (2970 ms) 10 times
7376 ms to take the 57 root of a 1000000 BYTE number 10 times

9173 ms to take the 23 root of a 1000000 BYTE number (9062 ms) then take the  3 root of THAT (111 ms) 10 times
7874 ms to take the 3 root of a 1000000 BYTE number (4953 ms) then take the  23 root of THAT (2921 ms) 10 times
8156 ms to take the 69 root of a 1000000 BYTE number 10 times

8113 ms to take the 29 root of a 1000000 BYTE number (8017 ms) then take the  3 root of THAT (96 ms) 10 times
7266 ms to take the 3 root of a 1000000 BYTE number (4953 ms) then take the  29 root of THAT (2313 ms) 10 times
8344 ms to take the 87 root of a 1000000 BYTE number 10 times

9998 ms to take the 31 root of a 1000000 BYTE number (9951 ms) then take the  3 root of THAT (47 ms) 10 times
8328 ms to take the 3 root of a 1000000 BYTE number (5031 ms) then take the  31 root of THAT (3297 ms) 10 times
10329 ms to take the 93 root of a 1000000 BYTE number 10 times

6703 ms to take the 37 root of a 1000000 BYTE number (6607 ms) then take the  3 root of THAT (96 ms) 10 times
7408 ms to take the 3 root of a 1000000 BYTE number (4845 ms) then take the  37 root of THAT (2563 ms) 10 times
10032 ms to take the 111 root of a 1000000 BYTE number 10 times

6405 ms to take the 41 root of a 1000000 BYTE number (6297 ms) then take the  3 root of THAT (108 ms) 10 times
7252 ms to take the 3 root of a 1000000 BYTE number (4858 ms) then take the  41 root of THAT (2394 ms) 10 times
9125 ms to take the 123 root of a 1000000 BYTE number 10 times

8296 ms to take the 43 root of a 1000000 BYTE number (8220 ms) then take the  3 root of THAT (76 ms) 10 times
7984 ms to take the 3 root of a 1000000 BYTE number (4906 ms) then take the  43 root of THAT (3078 ms) 10 times
6874 ms to take the 129 root of a 1000000 BYTE number 10 times

10639 ms to take the 47 root of a 1000000 BYTE number (10639 ms) then take the  3 root of THAT (0 ms) 10 times
7891 ms to take the 3 root of a 1000000 BYTE number (4892 ms) then take the  47 root of THAT (2999 ms) 10 times
7750 ms to take the 141 root of a 1000000 BYTE number 10 times

7517 ms to take the 53 root of a 1000000 BYTE number (7453 ms) then take the  3 root of THAT (64 ms) 10 times
7216 ms to take the 3 root of a 1000000 BYTE number (4889 ms) then take the  53 root of THAT (2327 ms) 10 times
9122 ms to take the 159 root of a 1000000 BYTE number 10 times

9016 ms to take the 59 root of a 1000000 BYTE number (9001 ms) then take the  3 root of THAT (15 ms) 10 times
7422 ms to take the 3 root of a 1000000 BYTE number (4875 ms) then take the  59 root of THAT (2547 ms) 10 times
5984 ms to take the 177 root of a 1000000 BYTE number 10 times

8000 ms to take the 61 root of a 1000000 BYTE number (7968 ms) then take the  3 root of THAT (32 ms) 10 times
7750 ms to take the 3 root of a 1000000 BYTE number (4830 ms) then take the  61 root of THAT (2920 ms) 10 times
11157 ms to take the 183 root of a 1000000 BYTE number 10 times

8160 ms to take the 67 root of a 1000000 BYTE number (8113 ms) then take the  3 root of THAT (47 ms) 10 times
7846 ms to take the 3 root of a 1000000 BYTE number (5097 ms) then take the  67 root of THAT (2749 ms) 10 times
6297 ms to take the 201 root of a 1000000 BYTE number 10 times

7970 ms to take the 71 root of a 1000000 BYTE number (7970 ms) then take the  3 root of THAT (0 ms) 10 times
7717 ms to take the 3 root of a 1000000 BYTE number (4921 ms) then take the  71 root of THAT (2796 ms) 10 times
6954 ms to take the 213 root of a 1000000 BYTE number 10 times

9766 ms to take the 5 root of a 1000000 BYTE number (8218 ms) then take the  5 root of THAT (1548 ms) 10 times
9235 ms to take the 25 root of a 1000000 BYTE number 10 times

8937 ms to take the 7 root of a 1000000 BYTE number (8297 ms) then take the  5 root of THAT (640 ms) 10 times
9531 ms to take the 5 root of a 1000000 BYTE number (8390 ms) then take the  7 root of THAT (1141 ms) 10 times
7348 ms to take the 35 root of a 1000000 BYTE number 10 times

8563 ms to take the 11 root of a 1000000 BYTE number (8154 ms) then take the  5 root of THAT (409 ms) 10 times
9267 ms to take the 5 root of a 1000000 BYTE number (7969 ms) then take the  11 root of THAT (1298 ms) 10 times
9203 ms to take the 55 root of a 1000000 BYTE number 10 times

7906 ms to take the 13 root of a 1000000 BYTE number (7579 ms) then take the  5 root of THAT (327 ms) 10 times
9424 ms to take the 5 root of a 1000000 BYTE number (7986 ms) then take the  13 root of THAT (1438 ms) 10 times
10079 ms to take the 65 root of a 1000000 BYTE number 10 times

6504 ms to take the 17 root of a 1000000 BYTE number (6282 ms) then take the  5 root of THAT (222 ms) 10 times
9045 ms to take the 5 root of a 1000000 BYTE number (7938 ms) then take the  17 root of THAT (1107 ms) 10 times
7482 ms to take the 85 root of a 1000000 BYTE number 10 times

7937 ms to take the 19 root of a 1000000 BYTE number (7765 ms) then take the  5 root of THAT (172 ms) 10 times
9313 ms to take the 5 root of a 1000000 BYTE number (7953 ms) then take the  19 root of THAT (1360 ms) 10 times
8828 ms to take the 95 root of a 1000000 BYTE number 10 times

8796 ms to take the 23 root of a 1000000 BYTE number (8626 ms) then take the  5 root of THAT (170 ms) 10 times
9950 ms to take the 5 root of a 1000000 BYTE number (8249 ms) then take the  23 root of THAT (1701 ms) 10 times
8500 ms to take the 115 root of a 1000000 BYTE number 10 times

8095 ms to take the 29 root of a 1000000 BYTE number (7985 ms) then take the  5 root of THAT (110 ms) 10 times
9534 ms to take the 5 root of a 1000000 BYTE number (7971 ms) then take the  29 root of THAT (1563 ms) 10 times
8842 ms to take the 145 root of a 1000000 BYTE number 10 times

9985 ms to take the 31 root of a 1000000 BYTE number (9844 ms) then take the  5 root of THAT (141 ms) 10 times
9440 ms to take the 5 root of a 1000000 BYTE number (7969 ms) then take the  31 root of THAT (1471 ms) 10 times
8265 ms to take the 155 root of a 1000000 BYTE number 10 times

6736 ms to take the 37 root of a 1000000 BYTE number (6596 ms) then take the  5 root of THAT (140 ms) 10 times
9188 ms to take the 5 root of a 1000000 BYTE number (7969 ms) then take the  37 root of THAT (1219 ms) 10 times
6546 ms to take the 185 root of a 1000000 BYTE number 10 times

6391 ms to take the 41 root of a 1000000 BYTE number (6313 ms) then take the  5 root of THAT (78 ms) 10 times
9091 ms to take the 5 root of a 1000000 BYTE number (7952 ms) then take the  41 root of THAT (1139 ms) 10 times
7016 ms to take the 205 root of a 1000000 BYTE number 10 times

8030 ms to take the 43 root of a 1000000 BYTE number (7952 ms) then take the  5 root of THAT (78 ms) 10 times
9828 ms to take the 5 root of a 1000000 BYTE number (8313 ms) then take the  43 root of THAT (1515 ms) 10 times
8593 ms to take the 215 root of a 1000000 BYTE number 10 times

10486 ms to take the 47 root of a 1000000 BYTE number (10391 ms) then take the  5 root of THAT (95 ms) 10 times
9547 ms to take the 5 root of a 1000000 BYTE number (7937 ms) then take the  47 root of THAT (1610 ms) 10 times
8468 ms to take the 235 root of a 1000000 BYTE number 10 times

7501 ms to take the 53 root of a 1000000 BYTE number (7424 ms) then take the  5 root of THAT (77 ms) 10 times
9408 ms to take the 5 root of a 1000000 BYTE number (7999 ms) then take the  53 root of THAT (1409 ms) 10 times
7280 ms to take the 265 root of a 1000000 BYTE number 10 times

9143 ms to take the 59 root of a 1000000 BYTE number (9079 ms) then take the  5 root of THAT (64 ms) 10 times
9499 ms to take the 5 root of a 1000000 BYTE number (8031 ms) then take the  59 root of THAT (1468 ms) 10 times
8482 ms to take the 295 root of a 1000000 BYTE number 10 times

8033 ms to take the 61 root of a 1000000 BYTE number (7970 ms) then take the  5 root of THAT (63 ms) 10 times
9298 ms to take the 5 root of a 1000000 BYTE number (7954 ms) then take the  61 root of THAT (1344 ms) 10 times
6422 ms to take the 305 root of a 1000000 BYTE number 10 times

8080 ms to take the 67 root of a 1000000 BYTE number (8080 ms) then take the  5 root of THAT (0 ms) 10 times
9608 ms to take the 5 root of a 1000000 BYTE number (8251 ms) then take the  67 root of THAT (1357 ms) 10 times
8813 ms to take the 335 root of a 1000000 BYTE number 10 times

7936 ms to take the 71 root of a 1000000 BYTE number (7904 ms) then take the  5 root of THAT (32 ms) 10 times
9545 ms to take the 5 root of a 1000000 BYTE number (8031 ms) then take the  71 root of THAT (1514 ms) 10 times
11016 ms to take the 355 root of a 1000000 BYTE number 10 times

9187 ms to take the 7 root of a 1000000 BYTE number (8377 ms) then take the  7 root of THAT (810 ms) 10 times
8797 ms to take the 49 root of a 1000000 BYTE number 10 times

9063 ms to take the 11 root of a 1000000 BYTE number (8657 ms) then take the  7 root of THAT (406 ms) 10 times
9201 ms to take the 7 root of a 1000000 BYTE number (8296 ms) then take the  11 root of THAT (905 ms) 10 times
6953 ms to take the 77 root of a 1000000 BYTE number 10 times

7858 ms to take the 13 root of a 1000000 BYTE number (7532 ms) then take the  7 root of THAT (326 ms) 10 times
9079 ms to take the 7 root of a 1000000 BYTE number (8298 ms) then take the  13 root of THAT (781 ms) 10 times
8359 ms to take the 91 root of a 1000000 BYTE number 10 times

7186 ms to take the 17 root of a 1000000 BYTE number (6874 ms) then take the  7 root of THAT (312 ms) 10 times
9391 ms to take the 7 root of a 1000000 BYTE number (8484 ms) then take the  17 root of THAT (907 ms) 10 times
9639 ms to take the 119 root of a 1000000 BYTE number 10 times

7986 ms to take the 19 root of a 1000000 BYTE number (7735 ms) then take the  7 root of THAT (251 ms) 10 times
9330 ms to take the 7 root of a 1000000 BYTE number (8252 ms) then take the  19 root of THAT (1078 ms) 10 times
7890 ms to take the 133 root of a 1000000 BYTE number 10 times

8813 ms to take the 23 root of a 1000000 BYTE number (8625 ms) then take the  7 root of THAT (188 ms) 10 times
9361 ms to take the 7 root of a 1000000 BYTE number (8390 ms) then take the  23 root of THAT (971 ms) 10 times
6076 ms to take the 161 root of a 1000000 BYTE number 10 times

8468 ms to take the 29 root of a 1000000 BYTE number (8359 ms) then take the  7 root of THAT (109 ms) 10 times
9219 ms to take the 7 root of a 1000000 BYTE number (8313 ms) then take the  29 root of THAT (906 ms) 10 times
7766 ms to take the 203 root of a 1000000 BYTE number 10 times

10047 ms to take the 31 root of a 1000000 BYTE number (9888 ms) then take the  7 root of THAT (159 ms) 10 times
9922 ms to take the 7 root of a 1000000 BYTE number (8312 ms) then take the  31 root of THAT (1610 ms) 10 times
10293 ms to take the 217 root of a 1000000 BYTE number 10 times

6673 ms to take the 37 root of a 1000000 BYTE number (6610 ms) then take the  7 root of THAT (63 ms) 10 times
9626 ms to take the 7 root of a 1000000 BYTE number (8641 ms) then take the  37 root of THAT (985 ms) 10 times
8703 ms to take the 259 root of a 1000000 BYTE number 10 times

6407 ms to take the 41 root of a 1000000 BYTE number (6328 ms) then take the  7 root of THAT (79 ms) 10 times
9313 ms to take the 7 root of a 1000000 BYTE number (8330 ms) then take the  41 root of THAT (983 ms) 10 times
11516 ms to take the 287 root of a 1000000 BYTE number 10 times

8110 ms to take the 43 root of a 1000000 BYTE number (8000 ms) then take the  7 root of THAT (110 ms) 10 times
9360 ms to take the 7 root of a 1000000 BYTE number (8297 ms) then take the  43 root of THAT (1063 ms) 10 times
7500 ms to take the 301 root of a 1000000 BYTE number 10 times

10892 ms to take the 47 root of a 1000000 BYTE number (10813 ms) then take the  7 root of THAT (79 ms) 10 times
9282 ms to take the 7 root of a 1000000 BYTE number (8298 ms) then take the  47 root of THAT (984 ms) 10 times
5969 ms to take the 329 root of a 1000000 BYTE number 10 times

7626 ms to take the 53 root of a 1000000 BYTE number (7611 ms) then take the  7 root of THAT (15 ms) 10 times
9202 ms to take the 7 root of a 1000000 BYTE number (8312 ms) then take the  53 root of THAT (890 ms) 10 times
7500 ms to take the 371 root of a 1000000 BYTE number 10 times

8984 ms to take the 59 root of a 1000000 BYTE number (8953 ms) then take the  7 root of THAT (31 ms) 10 times
9656 ms to take the 7 root of a 1000000 BYTE number (8640 ms) then take the  59 root of THAT (1016 ms) 10 times
6733 ms to take the 413 root of a 1000000 BYTE number 10 times

8063 ms to take the 61 root of a 1000000 BYTE number (8033 ms) then take the  7 root of THAT (30 ms) 10 times
9155 ms to take the 7 root of a 1000000 BYTE number (8280 ms) then take the  61 root of THAT (875 ms) 10 times
7390 ms to take the 427 root of a 1000000 BYTE number 10 times

8202 ms to take the 67 root of a 1000000 BYTE number (8141 ms) then take the  7 root of THAT (61 ms) 10 times
9327 ms to take the 7 root of a 1000000 BYTE number (8313 ms) then take the  67 root of THAT (1014 ms) 10 times
7079 ms to take the 469 root of a 1000000 BYTE number 10 times

8294 ms to take the 71 root of a 1000000 BYTE number (8248 ms) then take the  7 root of THAT (46 ms) 10 times
9562 ms to take the 7 root of a 1000000 BYTE number (8267 ms) then take the  71 root of THAT (1295 ms) 10 times
7922 ms to take the 497 root of a 1000000 BYTE number 10 times

8750 ms to take the 11 root of a 1000000 BYTE number (8155 ms) then take the  11 root of THAT (595 ms) 10 times
9374 ms to take the 121 root of a 1000000 BYTE number 10 times

7909 ms to take the 13 root of a 1000000 BYTE number (7563 ms) then take the  11 root of THAT (346 ms) 10 times
8580 ms to take the 11 root of a 1000000 BYTE number (8158 ms) then take the  13 root of THAT (422 ms) 10 times
8952 ms to take the 143 root of a 1000000 BYTE number 10 times

6751 ms to take the 17 root of a 1000000 BYTE number (6421 ms) then take the  11 root of THAT (330 ms) 10 times
8764 ms to take the 11 root of a 1000000 BYTE number (8357 ms) then take the  17 root of THAT (407 ms) 10 times
7997 ms to take the 187 root of a 1000000 BYTE number 10 times

8001 ms to take the 19 root of a 1000000 BYTE number (7750 ms) then take the  11 root of THAT (251 ms) 10 times
8733 ms to take the 11 root of a 1000000 BYTE number (8156 ms) then take the  19 root of THAT (577 ms) 10 times
9361 ms to take the 209 root of a 1000000 BYTE number 10 times

9047 ms to take the 23 root of a 1000000 BYTE number (8797 ms) then take the  11 root of THAT (250 ms) 10 times
9235 ms to take the 11 root of a 1000000 BYTE number (8485 ms) then take the  23 root of THAT (750 ms) 10 times
12499 ms to take the 253 root of a 1000000 BYTE number 10 times

8112 ms to take the 29 root of a 1000000 BYTE number (7955 ms) then take the  11 root of THAT (157 ms) 10 times
8719 ms to take the 11 root of a 1000000 BYTE number (8187 ms) then take the  29 root of THAT (532 ms) 10 times
9372 ms to take the 319 root of a 1000000 BYTE number 10 times

10033 ms to take the 31 root of a 1000000 BYTE number (9890 ms) then take the  11 root of THAT (143 ms) 10 times
8656 ms to take the 11 root of a 1000000 BYTE number (8110 ms) then take the  31 root of THAT (546 ms) 10 times
7202 ms to take the 341 root of a 1000000 BYTE number 10 times

6674 ms to take the 37 root of a 1000000 BYTE number (6580 ms) then take the  11 root of THAT (94 ms) 10 times
8639 ms to take the 11 root of a 1000000 BYTE number (8185 ms) then take the  37 root of THAT (454 ms) 10 times
9499 ms to take the 407 root of a 1000000 BYTE number 10 times

6393 ms to take the 41 root of a 1000000 BYTE number (6329 ms) then take the  11 root of THAT (64 ms) 10 times
8593 ms to take the 11 root of a 1000000 BYTE number (8156 ms) then take the  41 root of THAT (437 ms) 10 times
8108 ms to take the 451 root of a 1000000 BYTE number 10 times

9172 ms to take the 43 root of a 1000000 BYTE number (9108 ms) then take the  11 root of THAT (64 ms) 10 times
10156 ms to take the 11 root of a 1000000 BYTE number (9468 ms) then take the  43 root of THAT (688 ms) 10 times
6423 ms to take the 473 root of a 1000000 BYTE number 10 times

10548 ms to take the 47 root of a 1000000 BYTE number (10439 ms) then take the  11 root of THAT (109 ms) 10 times
8813 ms to take the 11 root of a 1000000 BYTE number (8158 ms) then take the  47 root of THAT (655 ms) 10 times
6954 ms to take the 517 root of a 1000000 BYTE number 10 times

7626 ms to take the 53 root of a 1000000 BYTE number (7533 ms) then take the  11 root of THAT (93 ms) 10 times
8736 ms to take the 11 root of a 1000000 BYTE number (8204 ms) then take the  53 root of THAT (532 ms) 10 times
9234 ms to take the 583 root of a 1000000 BYTE number 10 times

9142 ms to take the 59 root of a 1000000 BYTE number (9079 ms) then take the  11 root of THAT (63 ms) 10 times
8846 ms to take the 11 root of a 1000000 BYTE number (8173 ms) then take the  59 root of THAT (673 ms) 10 times
6984 ms to take the 649 root of a 1000000 BYTE number 10 times

8063 ms to take the 61 root of a 1000000 BYTE number (8000 ms) then take the  11 root of THAT (63 ms) 10 times
8584 ms to take the 11 root of a 1000000 BYTE number (8146 ms) then take the  61 root of THAT (438 ms) 10 times
6939 ms to take the 671 root of a 1000000 BYTE number 10 times

8217 ms to take the 67 root of a 1000000 BYTE number (8122 ms) then take the  11 root of THAT (95 ms) 10 times
8954 ms to take the 11 root of a 1000000 BYTE number (8453 ms) then take the  67 root of THAT (501 ms) 10 times
6016 ms to take the 737 root of a 1000000 BYTE number 10 times

7923 ms to take the 71 root of a 1000000 BYTE number (7877 ms) then take the  11 root of THAT (46 ms) 10 times
8969 ms to take the 11 root of a 1000000 BYTE number (8155 ms) then take the  71 root of THAT (814 ms) 10 times
9891 ms to take the 781 root of a 1000000 BYTE number 10 times

7955 ms to take the 13 root of a 1000000 BYTE number (7596 ms) then take the  13 root of THAT (359 ms) 10 times
6265 ms to take the 169 root of a 1000000 BYTE number 10 times

6594 ms to take the 17 root of a 1000000 BYTE number (6312 ms) then take the  13 root of THAT (282 ms) 10 times
8264 ms to take the 13 root of a 1000000 BYTE number (7890 ms) then take the  17 root of THAT (374 ms) 10 times
8170 ms to take the 221 root of a 1000000 BYTE number 10 times

8046 ms to take the 19 root of a 1000000 BYTE number (7779 ms) then take the  13 root of THAT (267 ms) 10 times
8251 ms to take the 13 root of a 1000000 BYTE number (7719 ms) then take the  19 root of THAT (532 ms) 10 times
13358 ms to take the 247 root of a 1000000 BYTE number 10 times

8888 ms to take the 23 root of a 1000000 BYTE number (8686 ms) then take the  13 root of THAT (202 ms) 10 times
8217 ms to take the 13 root of a 1000000 BYTE number (7547 ms) then take the  23 root of THAT (670 ms) 10 times
12267 ms to take the 299 root of a 1000000 BYTE number 10 times

8093 ms to take the 29 root of a 1000000 BYTE number (7969 ms) then take the  13 root of THAT (124 ms) 10 times
8000 ms to take the 13 root of a 1000000 BYTE number (7548 ms) then take the  29 root of THAT (452 ms) 10 times
7622 ms to take the 377 root of a 1000000 BYTE number 10 times

10016 ms to take the 31 root of a 1000000 BYTE number (9907 ms) then take the  13 root of THAT (109 ms) 10 times
8032 ms to take the 13 root of a 1000000 BYTE number (7579 ms) then take the  31 root of THAT (453 ms) 10 times
7267 ms to take the 403 root of a 1000000 BYTE number 10 times

6718 ms to take the 37 root of a 1000000 BYTE number (6625 ms) then take the  13 root of THAT (93 ms) 10 times
8345 ms to take the 13 root of a 1000000 BYTE number (7938 ms) then take the  37 root of THAT (407 ms) 10 times
5982 ms to take the 481 root of a 1000000 BYTE number 10 times

6471 ms to take the 41 root of a 1000000 BYTE number (6409 ms) then take the  13 root of THAT (62 ms) 10 times
8000 ms to take the 13 root of a 1000000 BYTE number (7591 ms) then take the  41 root of THAT (409 ms) 10 times
7641 ms to take the 533 root of a 1000000 BYTE number 10 times

8047 ms to take the 43 root of a 1000000 BYTE number (7983 ms) then take the  13 root of THAT (64 ms) 10 times
8093 ms to take the 13 root of a 1000000 BYTE number (7531 ms) then take the  43 root of THAT (562 ms) 10 times
11092 ms to take the 559 root of a 1000000 BYTE number 10 times

10796 ms to take the 47 root of a 1000000 BYTE number (10688 ms) then take the  13 root of THAT (108 ms) 10 times
8127 ms to take the 13 root of a 1000000 BYTE number (7563 ms) then take the  47 root of THAT (564 ms) 10 times
8812 ms to take the 611 root of a 1000000 BYTE number 10 times

7593 ms to take the 53 root of a 1000000 BYTE number (7561 ms) then take the  13 root of THAT (32 ms) 10 times
7908 ms to take the 13 root of a 1000000 BYTE number (7578 ms) then take the  53 root of THAT (330 ms) 10 times
5296 ms to take the 689 root of a 1000000 BYTE number 10 times

9029 ms to take the 59 root of a 1000000 BYTE number (8983 ms) then take the  13 root of THAT (46 ms) 10 times
7966 ms to take the 13 root of a 1000000 BYTE number (7564 ms) then take the  59 root of THAT (402 ms) 10 times
7954 ms to take the 767 root of a 1000000 BYTE number 10 times

8108 ms to take the 61 root of a 1000000 BYTE number (8076 ms) then take the  13 root of THAT (32 ms) 10 times
7858 ms to take the 13 root of a 1000000 BYTE number (7546 ms) then take the  61 root of THAT (312 ms) 10 times
5656 ms to take the 793 root of a 1000000 BYTE number 10 times

8159 ms to take the 67 root of a 1000000 BYTE number (8144 ms) then take the  13 root of THAT (15 ms) 10 times
7969 ms to take the 13 root of a 1000000 BYTE number (7594 ms) then take the  67 root of THAT (375 ms) 10 times
7233 ms to take the 871 root of a 1000000 BYTE number 10 times

8044 ms to take the 71 root of a 1000000 BYTE number (7998 ms) then take the  13 root of THAT (46 ms) 10 times
8154 ms to take the 13 root of a 1000000 BYTE number (7797 ms) then take the  71 root of THAT (357 ms) 10 times
6314 ms to take the 923 root of a 1000000 BYTE number 10 times

6687 ms to take the 17 root of a 1000000 BYTE number (6406 ms) then take the  17 root of THAT (281 ms) 10 times
6174 ms to take the 289 root of a 1000000 BYTE number 10 times

7955 ms to take the 19 root of a 1000000 BYTE number (7719 ms) then take the  17 root of THAT (236 ms) 10 times
6689 ms to take the 17 root of a 1000000 BYTE number (6250 ms) then take the  19 root of THAT (439 ms) 10 times
8062 ms to take the 323 root of a 1000000 BYTE number 10 times

8827 ms to take the 23 root of a 1000000 BYTE number (8623 ms) then take the  17 root of THAT (204 ms) 10 times
6624 ms to take the 17 root of a 1000000 BYTE number (6265 ms) then take the  23 root of THAT (359 ms) 10 times
8437 ms to take the 391 root of a 1000000 BYTE number 10 times

8123 ms to take the 29 root of a 1000000 BYTE number (7969 ms) then take the  17 root of THAT (154 ms) 10 times
6593 ms to take the 17 root of a 1000000 BYTE number (6266 ms) then take the  29 root of THAT (327 ms) 10 times
8485 ms to take the 493 root of a 1000000 BYTE number 10 times

9968 ms to take the 31 root of a 1000000 BYTE number (9830 ms) then take the  17 root of THAT (138 ms) 10 times
6654 ms to take the 17 root of a 1000000 BYTE number (6313 ms) then take the  31 root of THAT (341 ms) 10 times
8986 ms to take the 527 root of a 1000000 BYTE number 10 times

6796 ms to take the 37 root of a 1000000 BYTE number (6656 ms) then take the  17 root of THAT (140 ms) 10 times
6936 ms to take the 17 root of a 1000000 BYTE number (6593 ms) then take the  37 root of THAT (343 ms) 10 times
8017 ms to take the 629 root of a 1000000 BYTE number 10 times

6439 ms to take the 41 root of a 1000000 BYTE number (6329 ms) then take the  17 root of THAT (110 ms) 10 times
6515 ms to take the 17 root of a 1000000 BYTE number (6296 ms) then take the  41 root of THAT (219 ms) 10 times
5563 ms to take the 697 root of a 1000000 BYTE number 10 times

8046 ms to take the 43 root of a 1000000 BYTE number (7968 ms) then take the  17 root of THAT (78 ms) 10 times
6842 ms to take the 17 root of a 1000000 BYTE number (6514 ms) then take the  43 root of THAT (328 ms) 10 times
8094 ms to take the 731 root of a 1000000 BYTE number 10 times

11829 ms to take the 47 root of a 1000000 BYTE number (11751 ms) then take the  17 root of THAT (78 ms) 10 times
6969 ms to take the 17 root of a 1000000 BYTE number (6673 ms) then take the  47 root of THAT (296 ms) 10 times
6092 ms to take the 799 root of a 1000000 BYTE number 10 times

7546 ms to take the 53 root of a 1000000 BYTE number (7530 ms) then take the  17 root of THAT (16 ms) 10 times
6499 ms to take the 17 root of a 1000000 BYTE number (6282 ms) then take the  53 root of THAT (217 ms) 10 times
5186 ms to take the 901 root of a 1000000 BYTE number 10 times

9016 ms to take the 59 root of a 1000000 BYTE number (8954 ms) then take the  17 root of THAT (62 ms) 10 times
6577 ms to take the 17 root of a 1000000 BYTE number (6296 ms) then take the  59 root of THAT (281 ms) 10 times
6298 ms to take the 1003 root of a 1000000 BYTE number 10 times

8078 ms to take the 61 root of a 1000000 BYTE number (8031 ms) then take the  17 root of THAT (47 ms) 10 times
6827 ms to take the 17 root of a 1000000 BYTE number (6594 ms) then take the  61 root of THAT (233 ms) 10 times
5655 ms to take the 1037 root of a 1000000 BYTE number 10 times

8109 ms to take the 67 root of a 1000000 BYTE number (8079 ms) then take the  17 root of THAT (30 ms) 10 times
6578 ms to take the 17 root of a 1000000 BYTE number (6266 ms) then take the  67 root of THAT (312 ms) 10 times
6094 ms to take the 1139 root of a 1000000 BYTE number 10 times

7938 ms to take the 71 root of a 1000000 BYTE number (7874 ms) then take the  17 root of THAT (64 ms) 10 times
6623 ms to take the 17 root of a 1000000 BYTE number (6282 ms) then take the  71 root of THAT (341 ms) 10 times
7812 ms to take the 1207 root of a 1000000 BYTE number 10 times

8046 ms to take the 19 root of a 1000000 BYTE number (7766 ms) then take the  19 root of THAT (280 ms) 10 times
6391 ms to take the 361 root of a 1000000 BYTE number 10 times

9000 ms to take the 23 root of a 1000000 BYTE number (8690 ms) then take the  19 root of THAT (310 ms) 10 times
8155 ms to take the 19 root of a 1000000 BYTE number (7718 ms) then take the  23 root of THAT (437 ms) 10 times
10592 ms to take the 437 root of a 1000000 BYTE number 10 times

8155 ms to take the 29 root of a 1000000 BYTE number (7906 ms) then take the  19 root of THAT (249 ms) 10 times
8030 ms to take the 19 root of a 1000000 BYTE number (7780 ms) then take the  29 root of THAT (250 ms) 10 times
8861 ms to take the 551 root of a 1000000 BYTE number 10 times

10344 ms to take the 31 root of a 1000000 BYTE number (10188 ms) then take the  19 root of THAT (156 ms) 10 times
8221 ms to take the 19 root of a 1000000 BYTE number (7844 ms) then take the  31 root of THAT (377 ms) 10 times
7700 ms to take the 589 root of a 1000000 BYTE number 10 times

6735 ms to take the 37 root of a 1000000 BYTE number (6625 ms) then take the  19 root of THAT (110 ms) 10 times
7968 ms to take the 19 root of a 1000000 BYTE number (7766 ms) then take the  37 root of THAT (202 ms) 10 times
7094 ms to take the 703 root of a 1000000 BYTE number 10 times

6454 ms to take the 41 root of a 1000000 BYTE number (6329 ms) then take the  19 root of THAT (125 ms) 10 times
7903 ms to take the 19 root of a 1000000 BYTE number (7716 ms) then take the  41 root of THAT (187 ms) 10 times
6609 ms to take the 779 root of a 1000000 BYTE number 10 times

8424 ms to take the 43 root of a 1000000 BYTE number (8328 ms) then take the  19 root of THAT (96 ms) 10 times
7922 ms to take the 19 root of a 1000000 BYTE number (7733 ms) then take the  43 root of THAT (189 ms) 10 times
5201 ms to take the 817 root of a 1000000 BYTE number 10 times

10547 ms to take the 47 root of a 1000000 BYTE number (10421 ms) then take the  19 root of THAT (126 ms) 10 times
8078 ms to take the 19 root of a 1000000 BYTE number (7812 ms) then take the  47 root of THAT (266 ms) 10 times
5547 ms to take the 893 root of a 1000000 BYTE number 10 times

7500 ms to take the 53 root of a 1000000 BYTE number (7468 ms) then take the  19 root of THAT (32 ms) 10 times
7890 ms to take the 19 root of a 1000000 BYTE number (7655 ms) then take the  53 root of THAT (235 ms) 10 times
10858 ms to take the 1007 root of a 1000000 BYTE number 10 times

9030 ms to take the 59 root of a 1000000 BYTE number (8937 ms) then take the  19 root of THAT (93 ms) 10 times
8031 ms to take the 19 root of a 1000000 BYTE number (7765 ms) then take the  59 root of THAT (266 ms) 10 times
6005 ms to take the 1121 root of a 1000000 BYTE number 10 times

8061 ms to take the 61 root of a 1000000 BYTE number (8015 ms) then take the  19 root of THAT (46 ms) 10 times
8001 ms to take the 19 root of a 1000000 BYTE number (7766 ms) then take the  61 root of THAT (235 ms) 10 times
6486 ms to take the 1159 root of a 1000000 BYTE number 10 times

8156 ms to take the 67 root of a 1000000 BYTE number (8111 ms) then take the  19 root of THAT (45 ms) 10 times
8359 ms to take the 19 root of a 1000000 BYTE number (8062 ms) then take the  67 root of THAT (297 ms) 10 times
5921 ms to take the 1273 root of a 1000000 BYTE number 10 times

7984 ms to take the 71 root of a 1000000 BYTE number (7937 ms) then take the  19 root of THAT (47 ms) 10 times
7986 ms to take the 19 root of a 1000000 BYTE number (7749 ms) then take the  71 root of THAT (237 ms) 10 times
5094 ms to take the 1349 root of a 1000000 BYTE number 10 times

8874 ms to take the 23 root of a 1000000 BYTE number (8625 ms) then take the  23 root of THAT (249 ms) 10 times
6314 ms to take the 529 root of a 1000000 BYTE number 10 times

8047 ms to take the 29 root of a 1000000 BYTE number (7906 ms) then take the  23 root of THAT (141 ms) 10 times
8798 ms to take the 23 root of a 1000000 BYTE number (8608 ms) then take the  29 root of THAT (190 ms) 10 times
6657 ms to take the 667 root of a 1000000 BYTE number 10 times

10063 ms to take the 31 root of a 1000000 BYTE number (9906 ms) then take the  23 root of THAT (157 ms) 10 times
8876 ms to take the 23 root of a 1000000 BYTE number (8625 ms) then take the  31 root of THAT (251 ms) 10 times
5404 ms to take the 713 root of a 1000000 BYTE number 10 times

6750 ms to take the 37 root of a 1000000 BYTE number (6608 ms) then take the  23 root of THAT (142 ms) 10 times
8826 ms to take the 23 root of a 1000000 BYTE number (8673 ms) then take the  37 root of THAT (153 ms) 10 times
5844 ms to take the 851 root of a 1000000 BYTE number 10 times

6391 ms to take the 41 root of a 1000000 BYTE number (6329 ms) then take the  23 root of THAT (62 ms) 10 times
8953 ms to take the 23 root of a 1000000 BYTE number (8798 ms) then take the  41 root of THAT (155 ms) 10 times
6751 ms to take the 943 root of a 1000000 BYTE number 10 times

8062 ms to take the 43 root of a 1000000 BYTE number (7954 ms) then take the  23 root of THAT (108 ms) 10 times
8829 ms to take the 23 root of a 1000000 BYTE number (8626 ms) then take the  43 root of THAT (203 ms) 10 times
5660 ms to take the 989 root of a 1000000 BYTE number 10 times

10531 ms to take the 47 root of a 1000000 BYTE number (10467 ms) then take the  23 root of THAT (64 ms) 10 times
8861 ms to take the 23 root of a 1000000 BYTE number (8627 ms) then take the  47 root of THAT (234 ms) 10 times
5967 ms to take the 1081 root of a 1000000 BYTE number 10 times

7593 ms to take the 53 root of a 1000000 BYTE number (7466 ms) then take the  23 root of THAT (127 ms) 10 times
9360 ms to take the 23 root of a 1000000 BYTE number (9172 ms) then take the  53 root of THAT (188 ms) 10 times
6655 ms to take the 1219 root of a 1000000 BYTE number 10 times

8999 ms to take the 59 root of a 1000000 BYTE number (8984 ms) then take the  23 root of THAT (15 ms) 10 times
8782 ms to take the 23 root of a 1000000 BYTE number (8593 ms) then take the  59 root of THAT (189 ms) 10 times
7122 ms to take the 1357 root of a 1000000 BYTE number 10 times

8032 ms to take the 61 root of a 1000000 BYTE number (7969 ms) then take the  23 root of THAT (63 ms) 10 times
8860 ms to take the 23 root of a 1000000 BYTE number (8704 ms) then take the  61 root of THAT (156 ms) 10 times
7906 ms to take the 1403 root of a 1000000 BYTE number 10 times

9456 ms to take the 67 root of a 1000000 BYTE number (9408 ms) then take the  23 root of THAT (48 ms) 10 times
9939 ms to take the 23 root of a 1000000 BYTE number (9732 ms) then take the  67 root of THAT (207 ms) 10 times
7624 ms to take the 1541 root of a 1000000 BYTE number 10 times

8108 ms to take the 71 root of a 1000000 BYTE number (8076 ms) then take the  23 root of THAT (32 ms) 10 times
8734 ms to take the 23 root of a 1000000 BYTE number (8641 ms) then take the  71 root of THAT (93 ms) 10 times
4172 ms to take the 1633 root of a 1000000 BYTE number 10 times

8158 ms to take the 29 root of a 1000000 BYTE number (8048 ms) then take the  29 root of THAT (110 ms) 10 times
5061 ms to take the 841 root of a 1000000 BYTE number 10 times

10237 ms to take the 31 root of a 1000000 BYTE number (10095 ms) then take the  29 root of THAT (142 ms) 10 times
8145 ms to take the 29 root of a 1000000 BYTE number (7923 ms) then take the  31 root of THAT (222 ms) 10 times
8670 ms to take the 899 root of a 1000000 BYTE number 10 times

6750 ms to take the 37 root of a 1000000 BYTE number (6640 ms) then take the  29 root of THAT (110 ms) 10 times
8048 ms to take the 29 root of a 1000000 BYTE number (7924 ms) then take the  37 root of THAT (124 ms) 10 times
5126 ms to take the 1073 root of a 1000000 BYTE number 10 times

6454 ms to take the 41 root of a 1000000 BYTE number (6344 ms) then take the  29 root of THAT (110 ms) 10 times
8065 ms to take the 29 root of a 1000000 BYTE number (7937 ms) then take the  41 root of THAT (128 ms) 10 times
7784 ms to take the 1189 root of a 1000000 BYTE number 10 times

8111 ms to take the 43 root of a 1000000 BYTE number (8017 ms) then take the  29 root of THAT (94 ms) 10 times
8125 ms to take the 29 root of a 1000000 BYTE number (7970 ms) then take the  43 root of THAT (155 ms) 10 times
7046 ms to take the 1247 root of a 1000000 BYTE number 10 times

10467 ms to take the 47 root of a 1000000 BYTE number (10405 ms) then take the  29 root of THAT (62 ms) 10 times
8173 ms to take the 29 root of a 1000000 BYTE number (8047 ms) then take the  47 root of THAT (126 ms) 10 times
5126 ms to take the 1363 root of a 1000000 BYTE number 10 times

7518 ms to take the 53 root of a 1000000 BYTE number (7470 ms) then take the  29 root of THAT (48 ms) 10 times
8360 ms to take the 29 root of a 1000000 BYTE number (8235 ms) then take the  53 root of THAT (125 ms) 10 times
4861 ms to take the 1537 root of a 1000000 BYTE number 10 times

9018 ms to take the 59 root of a 1000000 BYTE number (8987 ms) then take the  29 root of THAT (31 ms) 10 times
8061 ms to take the 29 root of a 1000000 BYTE number (7952 ms) then take the  59 root of THAT (109 ms) 10 times
5454 ms to take the 1711 root of a 1000000 BYTE number 10 times

8203 ms to take the 61 root of a 1000000 BYTE number (8173 ms) then take the  29 root of THAT (30 ms) 10 times
8077 ms to take the 29 root of a 1000000 BYTE number (8031 ms) then take the  61 root of THAT (46 ms) 10 times
4346 ms to take the 1769 root of a 1000000 BYTE number 10 times

8139 ms to take the 67 root of a 1000000 BYTE number (8139 ms) then take the  29 root of THAT (0 ms) 10 times
8172 ms to take the 29 root of a 1000000 BYTE number (8110 ms) then take the  67 root of THAT (62 ms) 10 times
3969 ms to take the 1943 root of a 1000000 BYTE number 10 times

7873 ms to take the 71 root of a 1000000 BYTE number (7858 ms) then take the  29 root of THAT (15 ms) 10 times
8000 ms to take the 29 root of a 1000000 BYTE number (7968 ms) then take the  71 root of THAT (32 ms) 10 times
4063 ms to take the 2059 root of a 1000000 BYTE number 10 times

10077 ms to take the 31 root of a 1000000 BYTE number (9890 ms) then take the  31 root of THAT (187 ms) 10 times
6891 ms to take the 961 root of a 1000000 BYTE number 10 times

6750 ms to take the 37 root of a 1000000 BYTE number (6625 ms) then take the  31 root of THAT (125 ms) 10 times
9923 ms to take the 31 root of a 1000000 BYTE number (9844 ms) then take the  37 root of THAT (79 ms) 10 times
7061 ms to take the 1147 root of a 1000000 BYTE number 10 times

6544 ms to take the 41 root of a 1000000 BYTE number (6436 ms) then take the  31 root of THAT (108 ms) 10 times
9953 ms to take the 31 root of a 1000000 BYTE number (9843 ms) then take the  41 root of THAT (110 ms) 10 times
6954 ms to take the 1271 root of a 1000000 BYTE number 10 times

8032 ms to take the 43 root of a 1000000 BYTE number (7985 ms) then take the  31 root of THAT (47 ms) 10 times
9968 ms to take the 31 root of a 1000000 BYTE number (9874 ms) then take the  43 root of THAT (94 ms) 10 times
4641 ms to take the 1333 root of a 1000000 BYTE number 10 times

10468 ms to take the 47 root of a 1000000 BYTE number (10375 ms) then take the  31 root of THAT (93 ms) 10 times
10329 ms to take the 31 root of a 1000000 BYTE number (10251 ms) then take the  47 root of THAT (78 ms) 10 times
4547 ms to take the 1457 root of a 1000000 BYTE number 10 times

7515 ms to take the 53 root of a 1000000 BYTE number (7469 ms) then take the  31 root of THAT (46 ms) 10 times
9953 ms to take the 31 root of a 1000000 BYTE number (9890 ms) then take the  53 root of THAT (63 ms) 10 times
6234 ms to take the 1643 root of a 1000000 BYTE number 10 times

9032 ms to take the 59 root of a 1000000 BYTE number (9001 ms) then take the  31 root of THAT (31 ms) 10 times
9876 ms to take the 31 root of a 1000000 BYTE number (9814 ms) then take the  59 root of THAT (62 ms) 10 times
3720 ms to take the 1829 root of a 1000000 BYTE number 10 times

8094 ms to take the 61 root of a 1000000 BYTE number (8048 ms) then take the  31 root of THAT (46 ms) 10 times
10311 ms to take the 31 root of a 1000000 BYTE number (10217 ms) then take the  61 root of THAT (94 ms) 10 times
5529 ms to take the 1891 root of a 1000000 BYTE number 10 times

8066 ms to take the 67 root of a 1000000 BYTE number (8018 ms) then take the  31 root of THAT (48 ms) 10 times
9940 ms to take the 31 root of a 1000000 BYTE number (9877 ms) then take the  67 root of THAT (63 ms) 10 times
4373 ms to take the 2077 root of a 1000000 BYTE number 10 times

7939 ms to take the 71 root of a 1000000 BYTE number (7923 ms) then take the  31 root of THAT (16 ms) 10 times
9906 ms to take the 31 root of a 1000000 BYTE number (9814 ms) then take the  71 root of THAT (92 ms) 10 times
3907 ms to take the 2201 root of a 1000000 BYTE number 10 times

7059 ms to take the 37 root of a 1000000 BYTE number (6951 ms) then take the  37 root of THAT (108 ms) 10 times
4953 ms to take the 1369 root of a 1000000 BYTE number 10 times

6407 ms to take the 41 root of a 1000000 BYTE number (6376 ms) then take the  37 root of THAT (31 ms) 10 times
6685 ms to take the 37 root of a 1000000 BYTE number (6622 ms) then take the  41 root of THAT (63 ms) 10 times
4919 ms to take the 1517 root of a 1000000 BYTE number 10 times

8015 ms to take the 43 root of a 1000000 BYTE number (7953 ms) then take the  37 root of THAT (62 ms) 10 times
6673 ms to take the 37 root of a 1000000 BYTE number (6610 ms) then take the  43 root of THAT (63 ms) 10 times
4985 ms to take the 1591 root of a 1000000 BYTE number 10 times

10375 ms to take the 47 root of a 1000000 BYTE number (10344 ms) then take the  37 root of THAT (31 ms) 10 times
6700 ms to take the 37 root of a 1000000 BYTE number (6653 ms) then take the  47 root of THAT (47 ms) 10 times
4404 ms to take the 1739 root of a 1000000 BYTE number 10 times

7548 ms to take the 53 root of a 1000000 BYTE number (7516 ms) then take the  37 root of THAT (32 ms) 10 times
6674 ms to take the 37 root of a 1000000 BYTE number (6626 ms) then take the  53 root of THAT (48 ms) 10 times
3876 ms to take the 1961 root of a 1000000 BYTE number 10 times

9000 ms to take the 59 root of a 1000000 BYTE number (8985 ms) then take the  37 root of THAT (15 ms) 10 times
6688 ms to take the 37 root of a 1000000 BYTE number (6672 ms) then take the  59 root of THAT (16 ms) 10 times
4141 ms to take the 2183 root of a 1000000 BYTE number 10 times

8220 ms to take the 61 root of a 1000000 BYTE number (8220 ms) then take the  37 root of THAT (0 ms) 10 times
6722 ms to take the 37 root of a 1000000 BYTE number (6659 ms) then take the  61 root of THAT (63 ms) 10 times
3890 ms to take the 2257 root of a 1000000 BYTE number 10 times

8532 ms to take the 67 root of a 1000000 BYTE number (8516 ms) then take the  37 root of THAT (16 ms) 10 times
6672 ms to take the 37 root of a 1000000 BYTE number (6642 ms) then take the  67 root of THAT (30 ms) 10 times
4143 ms to take the 2479 root of a 1000000 BYTE number 10 times

7907 ms to take the 71 root of a 1000000 BYTE number (7907 ms) then take the  37 root of THAT (0 ms) 10 times
6672 ms to take the 37 root of a 1000000 BYTE number (6641 ms) then take the  71 root of THAT (31 ms) 10 times
4796 ms to take the 2627 root of a 1000000 BYTE number 10 times

6375 ms to take the 41 root of a 1000000 BYTE number (6328 ms) then take the  41 root of THAT (47 ms) 10 times
3654 ms to take the 1681 root of a 1000000 BYTE number 10 times

8032 ms to take the 43 root of a 1000000 BYTE number (8016 ms) then take the  41 root of THAT (16 ms) 10 times
6329 ms to take the 41 root of a 1000000 BYTE number (6298 ms) then take the  43 root of THAT (31 ms) 10 times
4234 ms to take the 1763 root of a 1000000 BYTE number 10 times

10674 ms to take the 47 root of a 1000000 BYTE number (10659 ms) then take the  41 root of THAT (15 ms) 10 times
6389 ms to take the 41 root of a 1000000 BYTE number (6266 ms) then take the  47 root of THAT (123 ms) 10 times
4220 ms to take the 1927 root of a 1000000 BYTE number 10 times

7564 ms to take the 53 root of a 1000000 BYTE number (7533 ms) then take the  41 root of THAT (31 ms) 10 times
6391 ms to take the 41 root of a 1000000 BYTE number (6329 ms) then take the  53 root of THAT (62 ms) 10 times
4483 ms to take the 2173 root of a 1000000 BYTE number 10 times

8999 ms to take the 59 root of a 1000000 BYTE number (8968 ms) then take the  41 root of THAT (31 ms) 10 times
6529 ms to take the 41 root of a 1000000 BYTE number (6529 ms) then take the  59 root of THAT (0 ms) 10 times
4456 ms to take the 2419 root of a 1000000 BYTE number 10 times

8391 ms to take the 61 root of a 1000000 BYTE number (8345 ms) then take the  41 root of THAT (46 ms) 10 times
6392 ms to take the 41 root of a 1000000 BYTE number (6313 ms) then take the  61 root of THAT (79 ms) 10 times
4404 ms to take the 2501 root of a 1000000 BYTE number 10 times

8154 ms to take the 67 root of a 1000000 BYTE number (8154 ms) then take the  41 root of THAT (0 ms) 10 times
6374 ms to take the 41 root of a 1000000 BYTE number (6282 ms) then take the  67 root of THAT (92 ms) 10 times
4593 ms to take the 2747 root of a 1000000 BYTE number 10 times

7952 ms to take the 71 root of a 1000000 BYTE number (7906 ms) then take the  41 root of THAT (46 ms) 10 times
6390 ms to take the 41 root of a 1000000 BYTE number (6374 ms) then take the  71 root of THAT (16 ms) 10 times
4689 ms to take the 2911 root of a 1000000 BYTE number 10 times

8000 ms to take the 43 root of a 1000000 BYTE number (7937 ms) then take the  43 root of THAT (63 ms) 10 times
4627 ms to take the 1849 root of a 1000000 BYTE number 10 times

10969 ms to take the 47 root of a 1000000 BYTE number (10921 ms) then take the  43 root of THAT (48 ms) 10 times
8530 ms to take the 43 root of a 1000000 BYTE number (8515 ms) then take the  47 root of THAT (15 ms) 10 times
4641 ms to take the 2021 root of a 1000000 BYTE number 10 times

8030 ms to take the 53 root of a 1000000 BYTE number (7985 ms) then take the  43 root of THAT (45 ms) 10 times
8111 ms to take the 43 root of a 1000000 BYTE number (8079 ms) then take the  53 root of THAT (32 ms) 10 times
4125 ms to take the 2279 root of a 1000000 BYTE number 10 times

9017 ms to take the 59 root of a 1000000 BYTE number (8985 ms) then take the  43 root of THAT (32 ms) 10 times
8093 ms to take the 43 root of a 1000000 BYTE number (8062 ms) then take the  59 root of THAT (31 ms) 10 times
4156 ms to take the 2537 root of a 1000000 BYTE number 10 times

8077 ms to take the 61 root of a 1000000 BYTE number (8030 ms) then take the  43 root of THAT (47 ms) 10 times
8202 ms to take the 43 root of a 1000000 BYTE number (8156 ms) then take the  61 root of THAT (46 ms) 10 times
5203 ms to take the 2623 root of a 1000000 BYTE number 10 times

8172 ms to take the 67 root of a 1000000 BYTE number (8157 ms) then take the  43 root of THAT (15 ms) 10 times
8046 ms to take the 43 root of a 1000000 BYTE number (7999 ms) then take the  67 root of THAT (47 ms) 10 times
3813 ms to take the 2881 root of a 1000000 BYTE number 10 times

7954 ms to take the 71 root of a 1000000 BYTE number (7893 ms) then take the  43 root of THAT (61 ms) 10 times
7984 ms to take the 43 root of a 1000000 BYTE number (7921 ms) then take the  71 root of THAT (63 ms) 10 times
4736 ms to take the 3053 root of a 1000000 BYTE number 10 times

10611 ms to take the 47 root of a 1000000 BYTE number (10579 ms) then take the  47 root of THAT (32 ms) 10 times
3956 ms to take the 2209 root of a 1000000 BYTE number 10 times

7547 ms to take the 53 root of a 1000000 BYTE number (7516 ms) then take the  47 root of THAT (31 ms) 10 times
10440 ms to take the 47 root of a 1000000 BYTE number (10408 ms) then take the  53 root of THAT (32 ms) 10 times
4453 ms to take the 2491 root of a 1000000 BYTE number 10 times

9001 ms to take the 59 root of a 1000000 BYTE number (8985 ms) then take the  47 root of THAT (16 ms) 10 times
10438 ms to take the 47 root of a 1000000 BYTE number (10376 ms) then take the  59 root of THAT (62 ms) 10 times
5779 ms to take the 2773 root of a 1000000 BYTE number 10 times

8313 ms to take the 61 root of a 1000000 BYTE number (8313 ms) then take the  47 root of THAT (0 ms) 10 times
10470 ms to take the 47 root of a 1000000 BYTE number (10407 ms) then take the  61 root of THAT (63 ms) 10 times
5125 ms to take the 2867 root of a 1000000 BYTE number 10 times

8298 ms to take the 67 root of a 1000000 BYTE number (8283 ms) then take the  47 root of THAT (15 ms) 10 times
10468 ms to take the 47 root of a 1000000 BYTE number (10422 ms) then take the  67 root of THAT (46 ms) 10 times
4485 ms to take the 3149 root of a 1000000 BYTE number 10 times

7906 ms to take the 71 root of a 1000000 BYTE number (7874 ms) then take the  47 root of THAT (32 ms) 10 times
10734 ms to take the 47 root of a 1000000 BYTE number (10687 ms) then take the  71 root of THAT (47 ms) 10 times
4013 ms to take the 3337 root of a 1000000 BYTE number 10 times

7515 ms to take the 53 root of a 1000000 BYTE number (7485 ms) then take the  53 root of THAT (30 ms) 10 times
4031 ms to take the 2809 root of a 1000000 BYTE number 10 times

9172 ms to take the 59 root of a 1000000 BYTE number (9125 ms) then take the  53 root of THAT (47 ms) 10 times
7533 ms to take the 53 root of a 1000000 BYTE number (7533 ms) then take the  59 root of THAT (0 ms) 10 times
4531 ms to take the 3127 root of a 1000000 BYTE number 10 times

7983 ms to take the 61 root of a 1000000 BYTE number (7952 ms) then take the  53 root of THAT (31 ms) 10 times
7467 ms to take the 53 root of a 1000000 BYTE number (7406 ms) then take the  61 root of THAT (61 ms) 10 times
4668 ms to take the 3233 root of a 1000000 BYTE number 10 times

8563 ms to take the 67 root of a 1000000 BYTE number (8532 ms) then take the  53 root of THAT (31 ms) 10 times
7532 ms to take the 53 root of a 1000000 BYTE number (7500 ms) then take the  67 root of THAT (32 ms) 10 times
4328 ms to take the 3551 root of a 1000000 BYTE number 10 times

7876 ms to take the 71 root of a 1000000 BYTE number (7860 ms) then take the  53 root of THAT (16 ms) 10 times
7485 ms to take the 53 root of a 1000000 BYTE number (7469 ms) then take the  71 root of THAT (16 ms) 10 times
4067 ms to take the 3763 root of a 1000000 BYTE number 10 times

8954 ms to take the 59 root of a 1000000 BYTE number (8907 ms) then take the  59 root of THAT (47 ms) 10 times
4375 ms to take the 3481 root of a 1000000 BYTE number 10 times

8017 ms to take the 61 root of a 1000000 BYTE number (8001 ms) then take the  59 root of THAT (16 ms) 10 times
9374 ms to take the 59 root of a 1000000 BYTE number (9374 ms) then take the  61 root of THAT (0 ms) 10 times
4593 ms to take the 3599 root of a 1000000 BYTE number 10 times

8138 ms to take the 67 root of a 1000000 BYTE number (8138 ms) then take the  59 root of THAT (0 ms) 10 times
9001 ms to take the 59 root of a 1000000 BYTE number (8953 ms) then take the  67 root of THAT (48 ms) 10 times
5592 ms to take the 3953 root of a 1000000 BYTE number 10 times

7908 ms to take the 71 root of a 1000000 BYTE number (7892 ms) then take the  59 root of THAT (16 ms) 10 times
8952 ms to take the 59 root of a 1000000 BYTE number (8921 ms) then take the  71 root of THAT (31 ms) 10 times
4372 ms to take the 4189 root of a 1000000 BYTE number 10 times

7999 ms to take the 61 root of a 1000000 BYTE number (7999 ms) then take the  61 root of THAT (0 ms) 10 times
5157 ms to take the 3721 root of a 1000000 BYTE number 10 times

8424 ms to take the 67 root of a 1000000 BYTE number (8424 ms) then take the  61 root of THAT (0 ms) 10 times
8031 ms to take the 61 root of a 1000000 BYTE number (8015 ms) then take the  67 root of THAT (16 ms) 10 times
5373 ms to take the 4087 root of a 1000000 BYTE number 10 times

7907 ms to take the 71 root of a 1000000 BYTE number (7861 ms) then take the  61 root of THAT (46 ms) 10 times
8016 ms to take the 61 root of a 1000000 BYTE number (7985 ms) then take the  71 root of THAT (31 ms) 10 times
4357 ms to take the 4331 root of a 1000000 BYTE number 10 times

8122 ms to take the 67 root of a 1000000 BYTE number (8076 ms) then take the  67 root of THAT (46 ms) 10 times
4283 ms to take the 4489 root of a 1000000 BYTE number 10 times

7893 ms to take the 71 root of a 1000000 BYTE number (7846 ms) then take the  67 root of THAT (47 ms) 10 times
8593 ms to take the 67 root of a 1000000 BYTE number (8563 ms) then take the  71 root of THAT (30 ms) 10 times
3845 ms to take the 4757 root of a 1000000 BYTE number 10 times

7908 ms to take the 71 root of a 1000000 BYTE number (7877 ms) then take the  71 root of THAT (31 ms) 10 times
4405 ms to take the 5041 root of a 1000000 BYTE number 10 times

8422 ms to take the 2 root of a 10000000 BYTE number (5922 ms) then take the  2 root of THAT (2500 ms) 1 times
13532 ms to take the 4 root of a 10000000 BYTE number 1 times

9734 ms to take the 3 root of a 10000000 BYTE number (8469 ms) then take the  2 root of THAT (1265 ms) 1 times
9687 ms to take the 2 root of a 10000000 BYTE number (5984 ms) then take the  3 root of THAT (3703 ms) 1 times
12062 ms to take the 6 root of a 10000000 BYTE number 1 times

8125 ms to take the 5 root of a 10000000 BYTE number (7375 ms) then take the  2 root of THAT (750 ms) 1 times
9329 ms to take the 2 root of a 10000000 BYTE number (5907 ms) then take the  5 root of THAT (3422 ms) 1 times
10515 ms to take the 10 root of a 10000000 BYTE number 1 times

13454 ms to take the 7 root of a 10000000 BYTE number (12985 ms) then take the  2 root of THAT (469 ms) 1 times
11922 ms to take the 2 root of a 10000000 BYTE number (5906 ms) then take the  7 root of THAT (6016 ms) 1 times
17562 ms to take the 14 root of a 10000000 BYTE number 1 times

12343 ms to take the 11 root of a 10000000 BYTE number (12093 ms) then take the  2 root of THAT (250 ms) 1 times
11235 ms to take the 2 root of a 10000000 BYTE number (5938 ms) then take the  11 root of THAT (5297 ms) 1 times
15235 ms to take the 22 root of a 10000000 BYTE number 1 times

12797 ms to take the 13 root of a 10000000 BYTE number (12594 ms) then take the  2 root of THAT (203 ms) 1 times
11515 ms to take the 2 root of a 10000000 BYTE number (5890 ms) then take the  13 root of THAT (5625 ms) 1 times
16985 ms to take the 26 root of a 10000000 BYTE number 1 times

13203 ms to take the 17 root of a 10000000 BYTE number (13047 ms) then take the  2 root of THAT (156 ms) 1 times
11734 ms to take the 2 root of a 10000000 BYTE number (5906 ms) then take the  17 root of THAT (5828 ms) 1 times
18781 ms to take the 34 root of a 10000000 BYTE number 1 times

16891 ms to take the 19 root of a 10000000 BYTE number (16750 ms) then take the  2 root of THAT (141 ms) 1 times
13266 ms to take the 2 root of a 10000000 BYTE number (5938 ms) then take the  19 root of THAT (7328 ms) 1 times
20657 ms to take the 38 root of a 10000000 BYTE number 1 times

13906 ms to take the 23 root of a 10000000 BYTE number (13812 ms) then take the  2 root of THAT (94 ms) 1 times
12063 ms to take the 2 root of a 10000000 BYTE number (5891 ms) then take the  23 root of THAT (6172 ms) 1 times
16406 ms to take the 46 root of a 10000000 BYTE number 1 times

13344 ms to take the 29 root of a 10000000 BYTE number (13266 ms) then take the  2 root of THAT (78 ms) 1 times
12047 ms to take the 2 root of a 10000000 BYTE number (5922 ms) then take the  29 root of THAT (6125 ms) 1 times
17250 ms to take the 58 root of a 10000000 BYTE number 1 times

16391 ms to take the 31 root of a 10000000 BYTE number (16329 ms) then take the  2 root of THAT (62 ms) 1 times
13000 ms to take the 2 root of a 10000000 BYTE number (5921 ms) then take the  31 root of THAT (7079 ms) 1 times
19172 ms to take the 62 root of a 10000000 BYTE number 1 times

14625 ms to take the 37 root of a 10000000 BYTE number (14563 ms) then take the  2 root of THAT (62 ms) 1 times
12344 ms to take the 2 root of a 10000000 BYTE number (6015 ms) then take the  37 root of THAT (6329 ms) 1 times
18562 ms to take the 74 root of a 10000000 BYTE number 1 times

11219 ms to take the 41 root of a 10000000 BYTE number (11188 ms) then take the  2 root of THAT (31 ms) 1 times
11610 ms to take the 2 root of a 10000000 BYTE number (5969 ms) then take the  41 root of THAT (5641 ms) 1 times
15250 ms to take the 82 root of a 10000000 BYTE number 1 times

13204 ms to take the 43 root of a 10000000 BYTE number (13172 ms) then take the  2 root of THAT (32 ms) 1 times
12031 ms to take the 2 root of a 10000000 BYTE number (5890 ms) then take the  43 root of THAT (6141 ms) 1 times
16234 ms to take the 86 root of a 10000000 BYTE number 1 times

14891 ms to take the 47 root of a 10000000 BYTE number (14860 ms) then take the  2 root of THAT (31 ms) 1 times
12484 ms to take the 2 root of a 10000000 BYTE number (5922 ms) then take the  47 root of THAT (6562 ms) 1 times
16750 ms to take the 94 root of a 10000000 BYTE number 1 times

12797 ms to take the 53 root of a 10000000 BYTE number (12766 ms) then take the  2 root of THAT (31 ms) 1 times
12016 ms to take the 2 root of a 10000000 BYTE number (5984 ms) then take the  53 root of THAT (6032 ms) 1 times
16235 ms to take the 106 root of a 10000000 BYTE number 1 times

14531 ms to take the 59 root of a 10000000 BYTE number (14500 ms) then take the  2 root of THAT (31 ms) 1 times
12391 ms to take the 2 root of a 10000000 BYTE number (5891 ms) then take the  59 root of THAT (6500 ms) 1 times
17078 ms to take the 118 root of a 10000000 BYTE number 1 times

13766 ms to take the 61 root of a 10000000 BYTE number (13735 ms) then take the  2 root of THAT (31 ms) 1 times
11860 ms to take the 2 root of a 10000000 BYTE number (5907 ms) then take the  61 root of THAT (5953 ms) 1 times
16640 ms to take the 122 root of a 10000000 BYTE number 1 times

15000 ms to take the 67 root of a 10000000 BYTE number (14968 ms) then take the  2 root of THAT (32 ms) 1 times
12516 ms to take the 2 root of a 10000000 BYTE number (5906 ms) then take the  67 root of THAT (6610 ms) 1 times
17515 ms to take the 134 root of a 10000000 BYTE number 1 times

17391 ms to take the 71 root of a 10000000 BYTE number (17359 ms) then take the  2 root of THAT (32 ms) 1 times
14703 ms to take the 2 root of a 10000000 BYTE number (6719 ms) then take the  71 root of THAT (7984 ms) 1 times
19547 ms to take the 142 root of a 10000000 BYTE number 1 times

11547 ms to take the 3 root of a 10000000 BYTE number (8406 ms) then take the  3 root of THAT (3141 ms) 1 times
13375 ms to take the 9 root of a 10000000 BYTE number 1 times

8797 ms to take the 5 root of a 10000000 BYTE number (7375 ms) then take the  3 root of THAT (1422 ms) 1 times
11078 ms to take the 3 root of a 10000000 BYTE number (8406 ms) then take the  5 root of THAT (2672 ms) 1 times
13532 ms to take the 15 root of a 10000000 BYTE number 1 times

13985 ms to take the 7 root of a 10000000 BYTE number (13250 ms) then take the  3 root of THAT (735 ms) 1 times
11140 ms to take the 3 root of a 10000000 BYTE number (8406 ms) then take the  7 root of THAT (2734 ms) 1 times
11360 ms to take the 21 root of a 10000000 BYTE number 1 times

12282 ms to take the 11 root of a 10000000 BYTE number (11672 ms) then take the  3 root of THAT (610 ms) 1 times
12109 ms to take the 3 root of a 10000000 BYTE number (8406 ms) then take the  11 root of THAT (3703 ms) 1 times
13016 ms to take the 33 root of a 10000000 BYTE number 1 times

12610 ms to take the 13 root of a 10000000 BYTE number (12172 ms) then take the  3 root of THAT (438 ms) 1 times
11578 ms to take the 3 root of a 10000000 BYTE number (8469 ms) then take the  13 root of THAT (3109 ms) 1 times
14672 ms to take the 39 root of a 10000000 BYTE number 1 times

13344 ms to take the 17 root of a 10000000 BYTE number (13047 ms) then take the  3 root of THAT (297 ms) 1 times
11781 ms to take the 3 root of a 10000000 BYTE number (8875 ms) then take the  17 root of THAT (2906 ms) 1 times
13782 ms to take the 51 root of a 10000000 BYTE number 1 times

17125 ms to take the 19 root of a 10000000 BYTE number (16844 ms) then take the  3 root of THAT (281 ms) 1 times
12016 ms to take the 3 root of a 10000000 BYTE number (8407 ms) then take the  19 root of THAT (3609 ms) 1 times
12360 ms to take the 57 root of a 10000000 BYTE number 1 times

14078 ms to take the 23 root of a 10000000 BYTE number (13828 ms) then take the  3 root of THAT (250 ms) 1 times
12641 ms to take the 3 root of a 10000000 BYTE number (8453 ms) then take the  23 root of THAT (4188 ms) 1 times
13625 ms to take the 69 root of a 10000000 BYTE number 1 times

13344 ms to take the 29 root of a 10000000 BYTE number (13203 ms) then take the  3 root of THAT (141 ms) 1 times
11547 ms to take the 3 root of a 10000000 BYTE number (8500 ms) then take the  29 root of THAT (3047 ms) 1 times
14734 ms to take the 87 root of a 10000000 BYTE number 1 times

16578 ms to take the 31 root of a 10000000 BYTE number (16437 ms) then take the  3 root of THAT (141 ms) 1 times
12078 ms to take the 3 root of a 10000000 BYTE number (8406 ms) then take the  31 root of THAT (3672 ms) 1 times
12656 ms to take the 93 root of a 10000000 BYTE number 1 times

14937 ms to take the 37 root of a 10000000 BYTE number (14812 ms) then take the  3 root of THAT (125 ms) 1 times
11657 ms to take the 3 root of a 10000000 BYTE number (8516 ms) then take the  37 root of THAT (3141 ms) 1 times
15031 ms to take the 111 root of a 10000000 BYTE number 1 times

11250 ms to take the 41 root of a 10000000 BYTE number (11156 ms) then take the  3 root of THAT (94 ms) 1 times
11390 ms to take the 3 root of a 10000000 BYTE number (8390 ms) then take the  41 root of THAT (3000 ms) 1 times
15532 ms to take the 123 root of a 10000000 BYTE number 1 times

13313 ms to take the 43 root of a 10000000 BYTE number (13203 ms) then take the  3 root of THAT (110 ms) 1 times
12125 ms to take the 3 root of a 10000000 BYTE number (8406 ms) then take the  43 root of THAT (3719 ms) 1 times
11797 ms to take the 129 root of a 10000000 BYTE number 1 times

14453 ms to take the 47 root of a 10000000 BYTE number (14359 ms) then take the  3 root of THAT (94 ms) 1 times
13000 ms to take the 3 root of a 10000000 BYTE number (8562 ms) then take the  47 root of THAT (4438 ms) 1 times
13454 ms to take the 141 root of a 10000000 BYTE number 1 times

12734 ms to take the 53 root of a 10000000 BYTE number (12672 ms) then take the  3 root of THAT (62 ms) 1 times
11563 ms to take the 3 root of a 10000000 BYTE number (8406 ms) then take the  53 root of THAT (3157 ms) 1 times
15078 ms to take the 159 root of a 10000000 BYTE number 1 times

14938 ms to take the 59 root of a 10000000 BYTE number (14875 ms) then take the  3 root of THAT (63 ms) 1 times
11687 ms to take the 3 root of a 10000000 BYTE number (8422 ms) then take the  59 root of THAT (3265 ms) 1 times
10922 ms to take the 177 root of a 10000000 BYTE number 1 times

13485 ms to take the 61 root of a 10000000 BYTE number (13422 ms) then take the  3 root of THAT (63 ms) 1 times
11468 ms to take the 3 root of a 10000000 BYTE number (8406 ms) then take the  61 root of THAT (3062 ms) 1 times
14375 ms to take the 183 root of a 10000000 BYTE number 1 times

14969 ms to take the 67 root of a 10000000 BYTE number (14906 ms) then take the  3 root of THAT (63 ms) 1 times
12860 ms to take the 3 root of a 10000000 BYTE number (9204 ms) then take the  67 root of THAT (3656 ms) 1 times
12750 ms to take the 201 root of a 10000000 BYTE number 1 times

16672 ms to take the 71 root of a 10000000 BYTE number (16609 ms) then take the  3 root of THAT (63 ms) 1 times
12250 ms to take the 3 root of a 10000000 BYTE number (8641 ms) then take the  71 root of THAT (3609 ms) 1 times
12312 ms to take the 213 root of a 10000000 BYTE number 1 times

9110 ms to take the 5 root of a 10000000 BYTE number (7375 ms) then take the  5 root of THAT (1735 ms) 1 times
11890 ms to take the 25 root of a 10000000 BYTE number 1 times

14171 ms to take the 7 root of a 10000000 BYTE number (13015 ms) then take the  5 root of THAT (1156 ms) 1 times
9547 ms to take the 5 root of a 10000000 BYTE number (7406 ms) then take the  7 root of THAT (2141 ms) 1 times
15859 ms to take the 35 root of a 10000000 BYTE number 1 times

12235 ms to take the 11 root of a 10000000 BYTE number (11610 ms) then take the  5 root of THAT (625 ms) 1 times
9203 ms to take the 5 root of a 10000000 BYTE number (7375 ms) then take the  11 root of THAT (1828 ms) 1 times
15031 ms to take the 55 root of a 10000000 BYTE number 1 times

12891 ms to take the 13 root of a 10000000 BYTE number (12266 ms) then take the  5 root of THAT (625 ms) 1 times
9281 ms to take the 5 root of a 10000000 BYTE number (7531 ms) then take the  13 root of THAT (1750 ms) 1 times
12360 ms to take the 65 root of a 10000000 BYTE number 1 times

13422 ms to take the 17 root of a 10000000 BYTE number (13109 ms) then take the  5 root of THAT (313 ms) 1 times
8813 ms to take the 5 root of a 10000000 BYTE number (7391 ms) then take the  17 root of THAT (1422 ms) 1 times
12265 ms to take the 85 root of a 10000000 BYTE number 1 times

17390 ms to take the 19 root of a 10000000 BYTE number (17094 ms) then take the  5 root of THAT (296 ms) 1 times
9187 ms to take the 5 root of a 10000000 BYTE number (7406 ms) then take the  19 root of THAT (1781 ms) 1 times
14750 ms to take the 95 root of a 10000000 BYTE number 1 times

13641 ms to take the 23 root of a 10000000 BYTE number (13391 ms) then take the  5 root of THAT (250 ms) 1 times
9735 ms to take the 5 root of a 10000000 BYTE number (7344 ms) then take the  23 root of THAT (2391 ms) 1 times
17343 ms to take the 115 root of a 10000000 BYTE number 1 times

13531 ms to take the 29 root of a 10000000 BYTE number (13312 ms) then take the  5 root of THAT (219 ms) 1 times
9141 ms to take the 5 root of a 10000000 BYTE number (7359 ms) then take the  29 root of THAT (1782 ms) 1 times
12125 ms to take the 145 root of a 10000000 BYTE number 1 times

16468 ms to take the 31 root of a 10000000 BYTE number (16265 ms) then take the  5 root of THAT (203 ms) 1 times
9985 ms to take the 5 root of a 10000000 BYTE number (7782 ms) then take the  31 root of THAT (2203 ms) 1 times
15219 ms to take the 155 root of a 10000000 BYTE number 1 times

14594 ms to take the 37 root of a 10000000 BYTE number (14469 ms) then take the  5 root of THAT (125 ms) 1 times
8922 ms to take the 5 root of a 10000000 BYTE number (7437 ms) then take the  37 root of THAT (1485 ms) 1 times
11453 ms to take the 185 root of a 10000000 BYTE number 1 times

11828 ms to take the 41 root of a 10000000 BYTE number (11688 ms) then take the  5 root of THAT (140 ms) 1 times
9109 ms to take the 5 root of a 10000000 BYTE number (7359 ms) then take the  41 root of THAT (1750 ms) 1 times
14281 ms to take the 205 root of a 10000000 BYTE number 1 times

13235 ms to take the 43 root of a 10000000 BYTE number (13125 ms) then take the  5 root of THAT (110 ms) 1 times
9203 ms to take the 5 root of a 10000000 BYTE number (7391 ms) then take the  43 root of THAT (1812 ms) 1 times
13953 ms to take the 215 root of a 10000000 BYTE number 1 times

14641 ms to take the 47 root of a 10000000 BYTE number (14531 ms) then take the  5 root of THAT (110 ms) 1 times
9438 ms to take the 5 root of a 10000000 BYTE number (7375 ms) then take the  47 root of THAT (2063 ms) 1 times
14156 ms to take the 235 root of a 10000000 BYTE number 1 times

12859 ms to take the 53 root of a 10000000 BYTE number (12750 ms) then take the  5 root of THAT (109 ms) 1 times
9297 ms to take the 5 root of a 10000000 BYTE number (7640 ms) then take the  53 root of THAT (1657 ms) 1 times
12063 ms to take the 265 root of a 10000000 BYTE number 1 times

14594 ms to take the 59 root of a 10000000 BYTE number (14500 ms) then take the  5 root of THAT (94 ms) 1 times
9359 ms to take the 5 root of a 10000000 BYTE number (7359 ms) then take the  59 root of THAT (2000 ms) 1 times
14781 ms to take the 295 root of a 10000000 BYTE number 1 times

13547 ms to take the 61 root of a 10000000 BYTE number (13469 ms) then take the  5 root of THAT (78 ms) 1 times
9515 ms to take the 5 root of a 10000000 BYTE number (7640 ms) then take the  61 root of THAT (1875 ms) 1 times
11813 ms to take the 305 root of a 10000000 BYTE number 1 times

14968 ms to take the 67 root of a 10000000 BYTE number (14890 ms) then take the  5 root of THAT (78 ms) 1 times
9016 ms to take the 5 root of a 10000000 BYTE number (7391 ms) then take the  67 root of THAT (1625 ms) 1 times
14422 ms to take the 335 root of a 10000000 BYTE number 1 times

19062 ms to take the 71 root of a 10000000 BYTE number (19000 ms) then take the  5 root of THAT (62 ms) 1 times
9047 ms to take the 5 root of a 10000000 BYTE number (7344 ms) then take the  71 root of THAT (1703 ms) 1 times
12110 ms to take the 355 root of a 10000000 BYTE number 1 times

14219 ms to take the 7 root of a 10000000 BYTE number (13000 ms) then take the  7 root of THAT (1219 ms) 1 times
11516 ms to take the 49 root of a 10000000 BYTE number 1 times

12672 ms to take the 11 root of a 10000000 BYTE number (11844 ms) then take the  7 root of THAT (828 ms) 1 times
14500 ms to take the 7 root of a 10000000 BYTE number (12953 ms) then take the  11 root of THAT (1547 ms) 1 times
14531 ms to take the 77 root of a 10000000 BYTE number 1 times

12703 ms to take the 13 root of a 10000000 BYTE number (12141 ms) then take the  7 root of THAT (562 ms) 1 times
14156 ms to take the 7 root of a 10000000 BYTE number (12953 ms) then take the  13 root of THAT (1203 ms) 1 times
14000 ms to take the 91 root of a 10000000 BYTE number 1 times

13453 ms to take the 17 root of a 10000000 BYTE number (13063 ms) then take the  7 root of THAT (390 ms) 1 times
14265 ms to take the 7 root of a 10000000 BYTE number (13062 ms) then take the  17 root of THAT (1203 ms) 1 times
14844 ms to take the 119 root of a 10000000 BYTE number 1 times

17453 ms to take the 19 root of a 10000000 BYTE number (17047 ms) then take the  7 root of THAT (406 ms) 1 times
14625 ms to take the 7 root of a 10000000 BYTE number (13125 ms) then take the  19 root of THAT (1500 ms) 1 times
12953 ms to take the 133 root of a 10000000 BYTE number 1 times

13735 ms to take the 23 root of a 10000000 BYTE number (13422 ms) then take the  7 root of THAT (313 ms) 1 times
14500 ms to take the 7 root of a 10000000 BYTE number (12969 ms) then take the  23 root of THAT (1531 ms) 1 times
11844 ms to take the 161 root of a 10000000 BYTE number 1 times

13532 ms to take the 29 root of a 10000000 BYTE number (13313 ms) then take the  7 root of THAT (219 ms) 1 times
14187 ms to take the 7 root of a 10000000 BYTE number (12968 ms) then take the  29 root of THAT (1219 ms) 1 times
14563 ms to take the 203 root of a 10000000 BYTE number 1 times

16516 ms to take the 31 root of a 10000000 BYTE number (16297 ms) then take the  7 root of THAT (219 ms) 1 times
14828 ms to take the 7 root of a 10000000 BYTE number (13328 ms) then take the  31 root of THAT (1500 ms) 1 times
11610 ms to take the 217 root of a 10000000 BYTE number 1 times

14578 ms to take the 37 root of a 10000000 BYTE number (14422 ms) then take the  7 root of THAT (156 ms) 1 times
14234 ms to take the 7 root of a 10000000 BYTE number (12937 ms) then take the  37 root of THAT (1297 ms) 1 times
13547 ms to take the 259 root of a 10000000 BYTE number 1 times

11375 ms to take the 41 root of a 10000000 BYTE number (11219 ms) then take the  7 root of THAT (156 ms) 1 times
14235 ms to take the 7 root of a 10000000 BYTE number (12969 ms) then take the  41 root of THAT (1266 ms) 1 times
15219 ms to take the 287 root of a 10000000 BYTE number 1 times

13375 ms to take the 43 root of a 10000000 BYTE number (13234 ms) then take the  7 root of THAT (141 ms) 1 times
14812 ms to take the 7 root of a 10000000 BYTE number (13281 ms) then take the  43 root of THAT (1531 ms) 1 times
13187 ms to take the 301 root of a 10000000 BYTE number 1 times

14406 ms to take the 47 root of a 10000000 BYTE number (14281 ms) then take the  7 root of THAT (125 ms) 1 times
14438 ms to take the 7 root of a 10000000 BYTE number (13000 ms) then take the  47 root of THAT (1438 ms) 1 times
11015 ms to take the 329 root of a 10000000 BYTE number 1 times

13172 ms to take the 53 root of a 10000000 BYTE number (13078 ms) then take the  7 root of THAT (94 ms) 1 times
14125 ms to take the 7 root of a 10000000 BYTE number (12953 ms) then take the  53 root of THAT (1172 ms) 1 times
12172 ms to take the 371 root of a 10000000 BYTE number 1 times

14594 ms to take the 59 root of a 10000000 BYTE number (14516 ms) then take the  7 root of THAT (78 ms) 1 times
14438 ms to take the 7 root of a 10000000 BYTE number (12985 ms) then take the  59 root of THAT (1453 ms) 1 times
11985 ms to take the 413 root of a 10000000 BYTE number 1 times

13517 ms to take the 61 root of a 10000000 BYTE number (13407 ms) then take the  7 root of THAT (110 ms) 1 times
14422 ms to take the 7 root of a 10000000 BYTE number (13172 ms) then take the  61 root of THAT (1250 ms) 1 times
12687 ms to take the 427 root of a 10000000 BYTE number 1 times

15250 ms to take the 67 root of a 10000000 BYTE number (15141 ms) then take the  7 root of THAT (109 ms) 1 times
14359 ms to take the 7 root of a 10000000 BYTE number (13031 ms) then take the  67 root of THAT (1328 ms) 1 times
11719 ms to take the 469 root of a 10000000 BYTE number 1 times

16656 ms to take the 71 root of a 10000000 BYTE number (16594 ms) then take the  7 root of THAT (62 ms) 1 times
14563 ms to take the 7 root of a 10000000 BYTE number (13016 ms) then take the  71 root of THAT (1547 ms) 1 times
17453 ms to take the 497 root of a 10000000 BYTE number 1 times

12469 ms to take the 11 root of a 10000000 BYTE number (11703 ms) then take the  11 root of THAT (766 ms) 1 times
13015 ms to take the 121 root of a 10000000 BYTE number 1 times

12968 ms to take the 13 root of a 10000000 BYTE number (12265 ms) then take the  11 root of THAT (703 ms) 1 times
12297 ms to take the 11 root of a 10000000 BYTE number (11578 ms) then take the  13 root of THAT (719 ms) 1 times
16234 ms to take the 143 root of a 10000000 BYTE number 1 times

13579 ms to take the 17 root of a 10000000 BYTE number (13094 ms) then take the  11 root of THAT (485 ms) 1 times
12297 ms to take the 11 root of a 10000000 BYTE number (11703 ms) then take the  17 root of THAT (594 ms) 1 times
13125 ms to take the 187 root of a 10000000 BYTE number 1 times

17468 ms to take the 19 root of a 10000000 BYTE number (17109 ms) then take the  11 root of THAT (359 ms) 1 times
12407 ms to take the 11 root of a 10000000 BYTE number (11657 ms) then take the  19 root of THAT (750 ms) 1 times
11125 ms to take the 209 root of a 10000000 BYTE number 1 times

13719 ms to take the 23 root of a 10000000 BYTE number (13407 ms) then take the  11 root of THAT (312 ms) 1 times
12406 ms to take the 11 root of a 10000000 BYTE number (11594 ms) then take the  23 root of THAT (812 ms) 1 times
13359 ms to take the 253 root of a 10000000 BYTE number 1 times

13578 ms to take the 29 root of a 10000000 BYTE number (13297 ms) then take the  11 root of THAT (281 ms) 1 times
12344 ms to take the 11 root of a 10000000 BYTE number (11562 ms) then take the  29 root of THAT (782 ms) 1 times
15828 ms to take the 319 root of a 10000000 BYTE number 1 times

16453 ms to take the 31 root of a 10000000 BYTE number (16250 ms) then take the  11 root of THAT (203 ms) 1 times
12797 ms to take the 11 root of a 10000000 BYTE number (12031 ms) then take the  31 root of THAT (766 ms) 1 times
11562 ms to take the 341 root of a 10000000 BYTE number 1 times

14562 ms to take the 37 root of a 10000000 BYTE number (14406 ms) then take the  11 root of THAT (156 ms) 1 times
12219 ms to take the 11 root of a 10000000 BYTE number (11594 ms) then take the  37 root of THAT (625 ms) 1 times
13140 ms to take the 407 root of a 10000000 BYTE number 1 times

11828 ms to take the 41 root of a 10000000 BYTE number (11672 ms) then take the  11 root of THAT (156 ms) 1 times
12391 ms to take the 11 root of a 10000000 BYTE number (11782 ms) then take the  41 root of THAT (609 ms) 1 times
14890 ms to take the 451 root of a 10000000 BYTE number 1 times

13328 ms to take the 43 root of a 10000000 BYTE number (13187 ms) then take the  11 root of THAT (141 ms) 1 times
12312 ms to take the 11 root of a 10000000 BYTE number (11562 ms) then take the  43 root of THAT (750 ms) 1 times
11766 ms to take the 473 root of a 10000000 BYTE number 1 times

14437 ms to take the 47 root of a 10000000 BYTE number (14312 ms) then take the  11 root of THAT (125 ms) 1 times
12453 ms to take the 11 root of a 10000000 BYTE number (11625 ms) then take the  47 root of THAT (828 ms) 1 times
11656 ms to take the 517 root of a 10000000 BYTE number 1 times

12859 ms to take the 53 root of a 10000000 BYTE number (12734 ms) then take the  11 root of THAT (125 ms) 1 times
12907 ms to take the 11 root of a 10000000 BYTE number (11860 ms) then take the  53 root of THAT (1047 ms) 1 times
22718 ms to take the 583 root of a 10000000 BYTE number 1 times

14641 ms to take the 59 root of a 10000000 BYTE number (14531 ms) then take the  11 root of THAT (110 ms) 1 times
13015 ms to take the 11 root of a 10000000 BYTE number (11640 ms) then take the  59 root of THAT (1375 ms) 1 times
19156 ms to take the 649 root of a 10000000 BYTE number 1 times

13406 ms to take the 61 root of a 10000000 BYTE number (13313 ms) then take the  11 root of THAT (93 ms) 1 times
12250 ms to take the 11 root of a 10000000 BYTE number (11546 ms) then take the  61 root of THAT (704 ms) 1 times
14062 ms to take the 671 root of a 10000000 BYTE number 1 times

15375 ms to take the 67 root of a 10000000 BYTE number (15265 ms) then take the  11 root of THAT (110 ms) 1 times
12562 ms to take the 11 root of a 10000000 BYTE number (11578 ms) then take the  67 root of THAT (984 ms) 1 times
15313 ms to take the 737 root of a 10000000 BYTE number 1 times

16656 ms to take the 71 root of a 10000000 BYTE number (16578 ms) then take the  11 root of THAT (78 ms) 1 times
12438 ms to take the 11 root of a 10000000 BYTE number (11672 ms) then take the  71 root of THAT (766 ms) 1 times
11828 ms to take the 781 root of a 10000000 BYTE number 1 times

12718 ms to take the 13 root of a 10000000 BYTE number (12172 ms) then take the  13 root of THAT (546 ms) 1 times
11203 ms to take the 169 root of a 10000000 BYTE number 1 times

13578 ms to take the 17 root of a 10000000 BYTE number (13110 ms) then take the  13 root of THAT (468 ms) 1 times
12719 ms to take the 13 root of a 10000000 BYTE number (12172 ms) then take the  17 root of THAT (547 ms) 1 times
19906 ms to take the 221 root of a 10000000 BYTE number 1 times

17079 ms to take the 19 root of a 10000000 BYTE number (16750 ms) then take the  13 root of THAT (329 ms) 1 times
12828 ms to take the 13 root of a 10000000 BYTE number (12172 ms) then take the  19 root of THAT (656 ms) 1 times
14313 ms to take the 247 root of a 10000000 BYTE number 1 times

14219 ms to take the 23 root of a 10000000 BYTE number (13922 ms) then take the  13 root of THAT (297 ms) 1 times
13000 ms to take the 13 root of a 10000000 BYTE number (12235 ms) then take the  23 root of THAT (765 ms) 1 times
14813 ms to take the 299 root of a 10000000 BYTE number 1 times

13437 ms to take the 29 root of a 10000000 BYTE number (13219 ms) then take the  13 root of THAT (218 ms) 1 times
12703 ms to take the 13 root of a 10000000 BYTE number (12141 ms) then take the  29 root of THAT (562 ms) 1 times
11468 ms to take the 377 root of a 10000000 BYTE number 1 times

17344 ms to take the 31 root of a 10000000 BYTE number (17140 ms) then take the  13 root of THAT (204 ms) 1 times
12843 ms to take the 13 root of a 10000000 BYTE number (12172 ms) then take the  31 root of THAT (671 ms) 1 times
12312 ms to take the 403 root of a 10000000 BYTE number 1 times

14718 ms to take the 37 root of a 10000000 BYTE number (14531 ms) then take the  13 root of THAT (187 ms) 1 times
13063 ms to take the 13 root of a 10000000 BYTE number (12469 ms) then take the  37 root of THAT (594 ms) 1 times
10781 ms to take the 481 root of a 10000000 BYTE number 1 times

11375 ms to take the 41 root of a 10000000 BYTE number (11234 ms) then take the  13 root of THAT (141 ms) 1 times
12719 ms to take the 13 root of a 10000000 BYTE number (12156 ms) then take the  41 root of THAT (563 ms) 1 times
11984 ms to take the 533 root of a 10000000 BYTE number 1 times

13750 ms to take the 43 root of a 10000000 BYTE number (13609 ms) then take the  13 root of THAT (141 ms) 1 times
12953 ms to take the 13 root of a 10000000 BYTE number (12234 ms) then take the  43 root of THAT (719 ms) 1 times
24656 ms to take the 559 root of a 10000000 BYTE number 1 times

14453 ms to take the 47 root of a 10000000 BYTE number (14281 ms) then take the  13 root of THAT (172 ms) 1 times
13407 ms to take the 13 root of a 10000000 BYTE number (12625 ms) then take the  47 root of THAT (782 ms) 1 times
13344 ms to take the 611 root of a 10000000 BYTE number 1 times

12812 ms to take the 53 root of a 10000000 BYTE number (12703 ms) then take the  13 root of THAT (109 ms) 1 times
12953 ms to take the 13 root of a 10000000 BYTE number (12250 ms) then take the  53 root of THAT (703 ms) 1 times
11172 ms to take the 689 root of a 10000000 BYTE number 1 times

15015 ms to take the 59 root of a 10000000 BYTE number (14922 ms) then take the  13 root of THAT (93 ms) 1 times
12797 ms to take the 13 root of a 10000000 BYTE number (12156 ms) then take the  59 root of THAT (641 ms) 1 times
13187 ms to take the 767 root of a 10000000 BYTE number 1 times

13469 ms to take the 61 root of a 10000000 BYTE number (13344 ms) then take the  13 root of THAT (125 ms) 1 times
12750 ms to take the 13 root of a 10000000 BYTE number (12172 ms) then take the  61 root of THAT (578 ms) 1 times
11328 ms to take the 793 root of a 10000000 BYTE number 1 times

14968 ms to take the 67 root of a 10000000 BYTE number (14890 ms) then take the  13 root of THAT (78 ms) 1 times
12781 ms to take the 13 root of a 10000000 BYTE number (12156 ms) then take the  67 root of THAT (625 ms) 1 times
15782 ms to take the 871 root of a 10000000 BYTE number 1 times

17156 ms to take the 71 root of a 10000000 BYTE number (17062 ms) then take the  13 root of THAT (94 ms) 1 times
12844 ms to take the 13 root of a 10000000 BYTE number (12156 ms) then take the  71 root of THAT (688 ms) 1 times
12594 ms to take the 923 root of a 10000000 BYTE number 1 times

13672 ms to take the 17 root of a 10000000 BYTE number (13172 ms) then take the  17 root of THAT (500 ms) 1 times
11625 ms to take the 289 root of a 10000000 BYTE number 1 times

17547 ms to take the 19 root of a 10000000 BYTE number (17172 ms) then take the  17 root of THAT (375 ms) 1 times
13609 ms to take the 17 root of a 10000000 BYTE number (13047 ms) then take the  19 root of THAT (562 ms) 1 times
14016 ms to take the 323 root of a 10000000 BYTE number 1 times

13656 ms to take the 23 root of a 10000000 BYTE number (13406 ms) then take the  17 root of THAT (250 ms) 1 times
13563 ms to take the 17 root of a 10000000 BYTE number (13032 ms) then take the  23 root of THAT (531 ms) 1 times
13531 ms to take the 391 root of a 10000000 BYTE number 1 times

13609 ms to take the 29 root of a 10000000 BYTE number (13375 ms) then take the  17 root of THAT (234 ms) 1 times
13578 ms to take the 17 root of a 10000000 BYTE number (13078 ms) then take the  29 root of THAT (500 ms) 1 times
12156 ms to take the 493 root of a 10000000 BYTE number 1 times

16781 ms to take the 31 root of a 10000000 BYTE number (16562 ms) then take the  17 root of THAT (219 ms) 1 times
14593 ms to take the 17 root of a 10000000 BYTE number (13843 ms) then take the  31 root of THAT (750 ms) 1 times
15907 ms to take the 527 root of a 10000000 BYTE number 1 times

14750 ms to take the 37 root of a 10000000 BYTE number (14562 ms) then take the  17 root of THAT (188 ms) 1 times
13578 ms to take the 17 root of a 10000000 BYTE number (13047 ms) then take the  37 root of THAT (531 ms) 1 times
12969 ms to take the 629 root of a 10000000 BYTE number 1 times

11360 ms to take the 41 root of a 10000000 BYTE number (11219 ms) then take the  17 root of THAT (141 ms) 1 times
13563 ms to take the 17 root of a 10000000 BYTE number (13078 ms) then take the  41 root of THAT (485 ms) 1 times
11500 ms to take the 697 root of a 10000000 BYTE number 1 times

13313 ms to take the 43 root of a 10000000 BYTE number (13188 ms) then take the  17 root of THAT (125 ms) 1 times
13969 ms to take the 17 root of a 10000000 BYTE number (13437 ms) then take the  43 root of THAT (532 ms) 1 times
12422 ms to take the 731 root of a 10000000 BYTE number 1 times

14406 ms to take the 47 root of a 10000000 BYTE number (14297 ms) then take the  17 root of THAT (109 ms) 1 times
13594 ms to take the 17 root of a 10000000 BYTE number (13031 ms) then take the  47 root of THAT (563 ms) 1 times
13313 ms to take the 799 root of a 10000000 BYTE number 1 times

13125 ms to take the 53 root of a 10000000 BYTE number (13031 ms) then take the  17 root of THAT (94 ms) 1 times
13563 ms to take the 17 root of a 10000000 BYTE number (13063 ms) then take the  53 root of THAT (500 ms) 1 times
11141 ms to take the 901 root of a 10000000 BYTE number 1 times

14703 ms to take the 59 root of a 10000000 BYTE number (14609 ms) then take the  17 root of THAT (94 ms) 1 times
13813 ms to take the 17 root of a 10000000 BYTE number (13266 ms) then take the  59 root of THAT (547 ms) 1 times
13141 ms to take the 1003 root of a 10000000 BYTE number 1 times

13453 ms to take the 61 root of a 10000000 BYTE number (13359 ms) then take the  17 root of THAT (94 ms) 1 times
13578 ms to take the 17 root of a 10000000 BYTE number (13047 ms) then take the  61 root of THAT (531 ms) 1 times
11891 ms to take the 1037 root of a 10000000 BYTE number 1 times

15265 ms to take the 67 root of a 10000000 BYTE number (15140 ms) then take the  17 root of THAT (125 ms) 1 times
13859 ms to take the 17 root of a 10000000 BYTE number (13297 ms) then take the  67 root of THAT (562 ms) 1 times
12937 ms to take the 1139 root of a 10000000 BYTE number 1 times

16859 ms to take the 71 root of a 10000000 BYTE number (16781 ms) then take the  17 root of THAT (78 ms) 1 times
14047 ms to take the 17 root of a 10000000 BYTE number (13344 ms) then take the  71 root of THAT (703 ms) 1 times
18344 ms to take the 1207 root of a 10000000 BYTE number 1 times

17125 ms to take the 19 root of a 10000000 BYTE number (16781 ms) then take the  19 root of THAT (344 ms) 1 times
12031 ms to take the 361 root of a 10000000 BYTE number 1 times

13844 ms to take the 23 root of a 10000000 BYTE number (13531 ms) then take the  19 root of THAT (313 ms) 1 times
17515 ms to take the 19 root of a 10000000 BYTE number (17125 ms) then take the  23 root of THAT (390 ms) 1 times
11640 ms to take the 437 root of a 10000000 BYTE number 1 times

13485 ms to take the 29 root of a 10000000 BYTE number (13219 ms) then take the  19 root of THAT (266 ms) 1 times
17172 ms to take the 19 root of a 10000000 BYTE number (16750 ms) then take the  29 root of THAT (422 ms) 1 times
14469 ms to take the 551 root of a 10000000 BYTE number 1 times

16781 ms to take the 31 root of a 10000000 BYTE number (16500 ms) then take the  19 root of THAT (281 ms) 1 times
17907 ms to take the 19 root of a 10000000 BYTE number (17407 ms) then take the  31 root of THAT (500 ms) 1 times
12641 ms to take the 589 root of a 10000000 BYTE number 1 times

14656 ms to take the 37 root of a 10000000 BYTE number (14437 ms) then take the  19 root of THAT (219 ms) 1 times
17500 ms to take the 19 root of a 10000000 BYTE number (17078 ms) then take the  37 root of THAT (422 ms) 1 times
15250 ms to take the 703 root of a 10000000 BYTE number 1 times

11328 ms to take the 41 root of a 10000000 BYTE number (11172 ms) then take the  19 root of THAT (156 ms) 1 times
17204 ms to take the 19 root of a 10000000 BYTE number (16829 ms) then take the  41 root of THAT (375 ms) 1 times
12969 ms to take the 779 root of a 10000000 BYTE number 1 times

13328 ms to take the 43 root of a 10000000 BYTE number (13188 ms) then take the  19 root of THAT (140 ms) 1 times
17235 ms to take the 19 root of a 10000000 BYTE number (16813 ms) then take the  43 root of THAT (422 ms) 1 times
10484 ms to take the 817 root of a 10000000 BYTE number 1 times

14438 ms to take the 47 root of a 10000000 BYTE number (14297 ms) then take the  19 root of THAT (141 ms) 1 times
19016 ms to take the 19 root of a 10000000 BYTE number (18532 ms) then take the  47 root of THAT (484 ms) 1 times
13250 ms to take the 893 root of a 10000000 BYTE number 1 times

12844 ms to take the 53 root of a 10000000 BYTE number (12703 ms) then take the  19 root of THAT (141 ms) 1 times
17203 ms to take the 19 root of a 10000000 BYTE number (16766 ms) then take the  53 root of THAT (437 ms) 1 times
13953 ms to take the 1007 root of a 10000000 BYTE number 1 times

14687 ms to take the 59 root of a 10000000 BYTE number (14562 ms) then take the  19 root of THAT (125 ms) 1 times
17360 ms to take the 19 root of a 10000000 BYTE number (16766 ms) then take the  59 root of THAT (594 ms) 1 times
14578 ms to take the 1121 root of a 10000000 BYTE number 1 times

13812 ms to take the 61 root of a 10000000 BYTE number (13656 ms) then take the  19 root of THAT (156 ms) 1 times
17359 ms to take the 19 root of a 10000000 BYTE number (16828 ms) then take the  61 root of THAT (531 ms) 1 times
15343 ms to take the 1159 root of a 10000000 BYTE number 1 times

15062 ms to take the 67 root of a 10000000 BYTE number (14953 ms) then take the  19 root of THAT (109 ms) 1 times
17703 ms to take the 19 root of a 10000000 BYTE number (17156 ms) then take the  67 root of THAT (547 ms) 1 times
11969 ms to take the 1273 root of a 10000000 BYTE number 1 times

16657 ms to take the 71 root of a 10000000 BYTE number (16547 ms) then take the  19 root of THAT (110 ms) 1 times
17328 ms to take the 19 root of a 10000000 BYTE number (16750 ms) then take the  71 root of THAT (578 ms) 1 times
14047 ms to take the 1349 root of a 10000000 BYTE number 1 times

14313 ms to take the 23 root of a 10000000 BYTE number (13938 ms) then take the  23 root of THAT (375 ms) 1 times
11078 ms to take the 529 root of a 10000000 BYTE number 1 times

13625 ms to take the 29 root of a 10000000 BYTE number (13235 ms) then take the  23 root of THAT (390 ms) 1 times
13828 ms to take the 23 root of a 10000000 BYTE number (13407 ms) then take the  29 root of THAT (421 ms) 1 times
21391 ms to take the 667 root of a 10000000 BYTE number 1 times

16453 ms to take the 31 root of a 10000000 BYTE number (16203 ms) then take the  23 root of THAT (250 ms) 1 times
13703 ms to take the 23 root of a 10000000 BYTE number (13375 ms) then take the  31 root of THAT (328 ms) 1 times
10671 ms to take the 713 root of a 10000000 BYTE number 1 times

14687 ms to take the 37 root of a 10000000 BYTE number (14468 ms) then take the  23 root of THAT (219 ms) 1 times
14015 ms to take the 23 root of a 10000000 BYTE number (13734 ms) then take the  37 root of THAT (281 ms) 1 times
12047 ms to take the 851 root of a 10000000 BYTE number 1 times

11563 ms to take the 41 root of a 10000000 BYTE number (11375 ms) then take the  23 root of THAT (188 ms) 1 times
13766 ms to take the 23 root of a 10000000 BYTE number (13485 ms) then take the  41 root of THAT (281 ms) 1 times
16656 ms to take the 943 root of a 10000000 BYTE number 1 times

13437 ms to take the 43 root of a 10000000 BYTE number (13265 ms) then take the  23 root of THAT (172 ms) 1 times
13719 ms to take the 23 root of a 10000000 BYTE number (13360 ms) then take the  43 root of THAT (359 ms) 1 times
11968 ms to take the 989 root of a 10000000 BYTE number 1 times

14453 ms to take the 47 root of a 10000000 BYTE number (14297 ms) then take the  23 root of THAT (156 ms) 1 times
14125 ms to take the 23 root of a 10000000 BYTE number (13750 ms) then take the  47 root of THAT (375 ms) 1 times
11406 ms to take the 1081 root of a 10000000 BYTE number 1 times

12844 ms to take the 53 root of a 10000000 BYTE number (12688 ms) then take the  23 root of THAT (156 ms) 1 times
13797 ms to take the 23 root of a 10000000 BYTE number (13468 ms) then take the  53 root of THAT (329 ms) 1 times
12922 ms to take the 1219 root of a 10000000 BYTE number 1 times

15156 ms to take the 59 root of a 10000000 BYTE number (15016 ms) then take the  23 root of THAT (140 ms) 1 times
13797 ms to take the 23 root of a 10000000 BYTE number (13391 ms) then take the  59 root of THAT (406 ms) 1 times
18969 ms to take the 1357 root of a 10000000 BYTE number 1 times

13422 ms to take the 61 root of a 10000000 BYTE number (13313 ms) then take the  23 root of THAT (109 ms) 1 times
13860 ms to take the 23 root of a 10000000 BYTE number (13563 ms) then take the  61 root of THAT (297 ms) 1 times
12188 ms to take the 1403 root of a 10000000 BYTE number 1 times

15031 ms to take the 67 root of a 10000000 BYTE number (14922 ms) then take the  23 root of THAT (109 ms) 1 times
15937 ms to take the 23 root of a 10000000 BYTE number (15578 ms) then take the  67 root of THAT (359 ms) 1 times
11937 ms to take the 1541 root of a 10000000 BYTE number 1 times

16968 ms to take the 71 root of a 10000000 BYTE number (16859 ms) then take the  23 root of THAT (109 ms) 1 times
13985 ms to take the 23 root of a 10000000 BYTE number (13656 ms) then take the  71 root of THAT (329 ms) 1 times
10094 ms to take the 1633 root of a 10000000 BYTE number 1 times

13468 ms to take the 29 root of a 10000000 BYTE number (13218 ms) then take the  29 root of THAT (250 ms) 1 times
10656 ms to take the 841 root of a 10000000 BYTE number 1 times

16859 ms to take the 31 root of a 10000000 BYTE number (16625 ms) then take the  29 root of THAT (234 ms) 1 times
13484 ms to take the 29 root of a 10000000 BYTE number (13203 ms) then take the  31 root of THAT (281 ms) 1 times
11922 ms to take the 899 root of a 10000000 BYTE number 1 times

14625 ms to take the 37 root of a 10000000 BYTE number (14407 ms) then take the  29 root of THAT (218 ms) 1 times
13469 ms to take the 29 root of a 10000000 BYTE number (13219 ms) then take the  37 root of THAT (250 ms) 1 times
11437 ms to take the 1073 root of a 10000000 BYTE number 1 times

11344 ms to take the 41 root of a 10000000 BYTE number (11188 ms) then take the  29 root of THAT (156 ms) 1 times
13578 ms to take the 29 root of a 10000000 BYTE number (13328 ms) then take the  41 root of THAT (250 ms) 1 times
11922 ms to take the 1189 root of a 10000000 BYTE number 1 times

13391 ms to take the 43 root of a 10000000 BYTE number (13235 ms) then take the  29 root of THAT (156 ms) 1 times
14047 ms to take the 29 root of a 10000000 BYTE number (13750 ms) then take the  43 root of THAT (297 ms) 1 times
14688 ms to take the 1247 root of a 10000000 BYTE number 1 times

14437 ms to take the 47 root of a 10000000 BYTE number (14250 ms) then take the  29 root of THAT (187 ms) 1 times
13610 ms to take the 29 root of a 10000000 BYTE number (13188 ms) then take the  47 root of THAT (422 ms) 1 times
19375 ms to take the 1363 root of a 10000000 BYTE number 1 times

12782 ms to take the 53 root of a 10000000 BYTE number (12672 ms) then take the  29 root of THAT (110 ms) 1 times
13422 ms to take the 29 root of a 10000000 BYTE number (13187 ms) then take the  53 root of THAT (235 ms) 1 times
10140 ms to take the 1537 root of a 10000000 BYTE number 1 times

14750 ms to take the 59 root of a 10000000 BYTE number (14640 ms) then take the  29 root of THAT (110 ms) 1 times
13812 ms to take the 29 root of a 10000000 BYTE number (13547 ms) then take the  59 root of THAT (265 ms) 1 times
13875 ms to take the 1711 root of a 10000000 BYTE number 1 times

13484 ms to take the 61 root of a 10000000 BYTE number (13390 ms) then take the  29 root of THAT (94 ms) 1 times
13516 ms to take the 29 root of a 10000000 BYTE number (13281 ms) then take the  61 root of THAT (235 ms) 1 times
11516 ms to take the 1769 root of a 10000000 BYTE number 1 times

15406 ms to take the 67 root of a 10000000 BYTE number (15313 ms) then take the  29 root of THAT (93 ms) 1 times
13500 ms to take the 29 root of a 10000000 BYTE number (13234 ms) then take the  67 root of THAT (266 ms) 1 times
12766 ms to take the 1943 root of a 10000000 BYTE number 1 times

16688 ms to take the 71 root of a 10000000 BYTE number (16594 ms) then take the  29 root of THAT (94 ms) 1 times
13625 ms to take the 29 root of a 10000000 BYTE number (13187 ms) then take the  71 root of THAT (438 ms) 1 times
18797 ms to take the 2059 root of a 10000000 BYTE number 1 times

16516 ms to take the 31 root of a 10000000 BYTE number (16250 ms) then take the  31 root of THAT (266 ms) 1 times
10688 ms to take the 961 root of a 10000000 BYTE number 1 times

14688 ms to take the 37 root of a 10000000 BYTE number (14453 ms) then take the  31 root of THAT (235 ms) 1 times
16891 ms to take the 31 root of a 10000000 BYTE number (16657 ms) then take the  37 root of THAT (234 ms) 1 times
13469 ms to take the 1147 root of a 10000000 BYTE number 1 times

11375 ms to take the 41 root of a 10000000 BYTE number (11172 ms) then take the  31 root of THAT (203 ms) 1 times
16500 ms to take the 31 root of a 10000000 BYTE number (16266 ms) then take the  41 root of THAT (234 ms) 1 times
14578 ms to take the 1271 root of a 10000000 BYTE number 1 times

13704 ms to take the 43 root of a 10000000 BYTE number (13516 ms) then take the  31 root of THAT (188 ms) 1 times
16610 ms to take the 31 root of a 10000000 BYTE number (16328 ms) then take the  43 root of THAT (282 ms) 1 times
12594 ms to take the 1333 root of a 10000000 BYTE number 1 times

14422 ms to take the 47 root of a 10000000 BYTE number (14281 ms) then take the  31 root of THAT (141 ms) 1 times
16859 ms to take the 31 root of a 10000000 BYTE number (16609 ms) then take the  47 root of THAT (250 ms) 1 times
10375 ms to take the 1457 root of a 10000000 BYTE number 1 times

12922 ms to take the 53 root of a 10000000 BYTE number (12782 ms) then take the  31 root of THAT (140 ms) 1 times
16484 ms to take the 31 root of a 10000000 BYTE number (16265 ms) then take the  53 root of THAT (219 ms) 1 times
11813 ms to take the 1643 root of a 10000000 BYTE number 1 times

15266 ms to take the 59 root of a 10000000 BYTE number (15125 ms) then take the  31 root of THAT (141 ms) 1 times
16625 ms to take the 31 root of a 10000000 BYTE number (16375 ms) then take the  59 root of THAT (250 ms) 1 times
10922 ms to take the 1829 root of a 10000000 BYTE number 1 times

13500 ms to take the 61 root of a 10000000 BYTE number (13344 ms) then take the  31 root of THAT (156 ms) 1 times
16984 ms to take the 31 root of a 10000000 BYTE number (16672 ms) then take the  61 root of THAT (312 ms) 1 times
17047 ms to take the 1891 root of a 10000000 BYTE number 1 times

15047 ms to take the 67 root of a 10000000 BYTE number (14937 ms) then take the  31 root of THAT (110 ms) 1 times
16437 ms to take the 31 root of a 10000000 BYTE number (16203 ms) then take the  67 root of THAT (234 ms) 1 times
11766 ms to take the 2077 root of a 10000000 BYTE number 1 times

16875 ms to take the 71 root of a 10000000 BYTE number (16781 ms) then take the  31 root of THAT (94 ms) 1 times
16547 ms to take the 31 root of a 10000000 BYTE number (16281 ms) then take the  71 root of THAT (266 ms) 1 times
10922 ms to take the 2201 root of a 10000000 BYTE number 1 times

14906 ms to take the 37 root of a 10000000 BYTE number (14578 ms) then take the  37 root of THAT (328 ms) 1 times
17187 ms to take the 1369 root of a 10000000 BYTE number 1 times

11296 ms to take the 41 root of a 10000000 BYTE number (11140 ms) then take the  37 root of THAT (156 ms) 1 times
14594 ms to take the 37 root of a 10000000 BYTE number (14406 ms) then take the  41 root of THAT (188 ms) 1 times
11437 ms to take the 1517 root of a 10000000 BYTE number 1 times

13344 ms to take the 43 root of a 10000000 BYTE number (13203 ms) then take the  37 root of THAT (141 ms) 1 times
15000 ms to take the 37 root of a 10000000 BYTE number (14797 ms) then take the  43 root of THAT (203 ms) 1 times
12781 ms to take the 1591 root of a 10000000 BYTE number 1 times

14375 ms to take the 47 root of a 10000000 BYTE number (14250 ms) then take the  37 root of THAT (125 ms) 1 times
14688 ms to take the 37 root of a 10000000 BYTE number (14469 ms) then take the  47 root of THAT (219 ms) 1 times
12343 ms to take the 1739 root of a 10000000 BYTE number 1 times

12843 ms to take the 53 root of a 10000000 BYTE number (12734 ms) then take the  37 root of THAT (109 ms) 1 times
14625 ms to take the 37 root of a 10000000 BYTE number (14422 ms) then take the  53 root of THAT (203 ms) 1 times
10734 ms to take the 1961 root of a 10000000 BYTE number 1 times

14719 ms to take the 59 root of a 10000000 BYTE number (14610 ms) then take the  37 root of THAT (109 ms) 1 times
15032 ms to take the 37 root of a 10000000 BYTE number (14813 ms) then take the  59 root of THAT (219 ms) 1 times
13093 ms to take the 2183 root of a 10000000 BYTE number 1 times

13422 ms to take the 61 root of a 10000000 BYTE number (13328 ms) then take the  37 root of THAT (94 ms) 1 times
14703 ms to take the 37 root of a 10000000 BYTE number (14484 ms) then take the  61 root of THAT (219 ms) 1 times
10672 ms to take the 2257 root of a 10000000 BYTE number 1 times

15281 ms to take the 67 root of a 10000000 BYTE number (15187 ms) then take the  37 root of THAT (94 ms) 1 times
14625 ms to take the 37 root of a 10000000 BYTE number (14391 ms) then take the  67 root of THAT (234 ms) 1 times
13750 ms to take the 2479 root of a 10000000 BYTE number 1 times

16640 ms to take the 71 root of a 10000000 BYTE number (16562 ms) then take the  37 root of THAT (78 ms) 1 times
15031 ms to take the 37 root of a 10000000 BYTE number (14766 ms) then take the  71 root of THAT (265 ms) 1 times
12687 ms to take the 2627 root of a 10000000 BYTE number 1 times

11344 ms to take the 41 root of a 10000000 BYTE number (11203 ms) then take the  41 root of THAT (141 ms) 1 times
13110 ms to take the 1681 root of a 10000000 BYTE number 1 times

13312 ms to take the 43 root of a 10000000 BYTE number (13140 ms) then take the  41 root of THAT (172 ms) 1 times
11515 ms to take the 41 root of a 10000000 BYTE number (11250 ms) then take the  43 root of THAT (265 ms) 1 times
16891 ms to take the 1763 root of a 10000000 BYTE number 1 times

14453 ms to take the 47 root of a 10000000 BYTE number (14328 ms) then take the  41 root of THAT (125 ms) 1 times
11438 ms to take the 41 root of a 10000000 BYTE number (11250 ms) then take the  47 root of THAT (188 ms) 1 times
12641 ms to take the 1927 root of a 10000000 BYTE number 1 times

13219 ms to take the 53 root of a 10000000 BYTE number (13094 ms) then take the  41 root of THAT (125 ms) 1 times
11344 ms to take the 41 root of a 10000000 BYTE number (11204 ms) then take the  53 root of THAT (140 ms) 1 times
12125 ms to take the 2173 root of a 10000000 BYTE number 1 times

15219 ms to take the 59 root of a 10000000 BYTE number (15125 ms) then take the  41 root of THAT (94 ms) 1 times
11656 ms to take the 41 root of a 10000000 BYTE number (11375 ms) then take the  59 root of THAT (281 ms) 1 times
14750 ms to take the 2419 root of a 10000000 BYTE number 1 times

15110 ms to take the 61 root of a 10000000 BYTE number (15016 ms) then take the  41 root of THAT (94 ms) 1 times
12781 ms to take the 41 root of a 10000000 BYTE number (12578 ms) then take the  61 root of THAT (203 ms) 1 times
12953 ms to take the 2501 root of a 10000000 BYTE number 1 times

17484 ms to take the 67 root of a 10000000 BYTE number (17312 ms) then take the  41 root of THAT (172 ms) 1 times
12844 ms to take the 41 root of a 10000000 BYTE number (12563 ms) then take the  67 root of THAT (281 ms) 1 times
22360 ms to take the 2747 root of a 10000000 BYTE number 1 times

18969 ms to take the 71 root of a 10000000 BYTE number (18875 ms) then take the  41 root of THAT (94 ms) 1 times
15172 ms to take the 41 root of a 10000000 BYTE number (14953 ms) then take the  71 root of THAT (219 ms) 1 times
15094 ms to take the 2911 root of a 10000000 BYTE number 1 times

15219 ms to take the 43 root of a 10000000 BYTE number (14938 ms) then take the  43 root of THAT (281 ms) 1 times
20328 ms to take the 1849 root of a 10000000 BYTE number 1 times

16578 ms to take the 47 root of a 10000000 BYTE number (16406 ms) then take the  43 root of THAT (172 ms) 1 times
14938 ms to take the 43 root of a 10000000 BYTE number (14719 ms) then take the  47 root of THAT (219 ms) 1 times
13640 ms to take the 2021 root of a 10000000 BYTE number 1 times

14359 ms to take the 53 root of a 10000000 BYTE number (14203 ms) then take the  43 root of THAT (156 ms) 1 times
15204 ms to take the 43 root of a 10000000 BYTE number (15032 ms) then take the  53 root of THAT (172 ms) 1 times
15031 ms to take the 2279 root of a 10000000 BYTE number 1 times

16609 ms to take the 59 root of a 10000000 BYTE number (16469 ms) then take the  43 root of THAT (140 ms) 1 times
15016 ms to take the 43 root of a 10000000 BYTE number (14797 ms) then take the  59 root of THAT (219 ms) 1 times
12421 ms to take the 2537 root of a 10000000 BYTE number 1 times

15297 ms to take the 61 root of a 10000000 BYTE number (15156 ms) then take the  43 root of THAT (141 ms) 1 times
15172 ms to take the 43 root of a 10000000 BYTE number (14938 ms) then take the  61 root of THAT (234 ms) 1 times
16766 ms to take the 2623 root of a 10000000 BYTE number 1 times

17250 ms to take the 67 root of a 10000000 BYTE number (17125 ms) then take the  43 root of THAT (125 ms) 1 times
15625 ms to take the 43 root of a 10000000 BYTE number (15438 ms) then take the  67 root of THAT (187 ms) 1 times
11781 ms to take the 2881 root of a 10000000 BYTE number 1 times

18968 ms to take the 71 root of a 10000000 BYTE number (18859 ms) then take the  43 root of THAT (109 ms) 1 times
15250 ms to take the 43 root of a 10000000 BYTE number (15063 ms) then take the  71 root of THAT (187 ms) 1 times
14625 ms to take the 3053 root of a 10000000 BYTE number 1 times

15969 ms to take the 47 root of a 10000000 BYTE number (15797 ms) then take the  47 root of THAT (172 ms) 1 times
11266 ms to take the 2209 root of a 10000000 BYTE number 1 times

13953 ms to take the 53 root of a 10000000 BYTE number (13766 ms) then take the  47 root of THAT (187 ms) 1 times
15672 ms to take the 47 root of a 10000000 BYTE number (15516 ms) then take the  53 root of THAT (156 ms) 1 times
14328 ms to take the 2491 root of a 10000000 BYTE number 1 times

15922 ms to take the 59 root of a 10000000 BYTE number (15766 ms) then take the  47 root of THAT (156 ms) 1 times
15235 ms to take the 47 root of a 10000000 BYTE number (15047 ms) then take the  59 root of THAT (188 ms) 1 times
12625 ms to take the 2773 root of a 10000000 BYTE number 1 times

14266 ms to take the 61 root of a 10000000 BYTE number (14125 ms) then take the  47 root of THAT (141 ms) 1 times
15125 ms to take the 47 root of a 10000000 BYTE number (14969 ms) then take the  61 root of THAT (156 ms) 1 times
14156 ms to take the 2867 root of a 10000000 BYTE number 1 times

17250 ms to take the 67 root of a 10000000 BYTE number (17110 ms) then take the  47 root of THAT (140 ms) 1 times
15734 ms to take the 47 root of a 10000000 BYTE number (15562 ms) then take the  67 root of THAT (172 ms) 1 times
12593 ms to take the 3149 root of a 10000000 BYTE number 1 times

17906 ms to take the 71 root of a 10000000 BYTE number (17797 ms) then take the  47 root of THAT (109 ms) 1 times
15484 ms to take the 47 root of a 10000000 BYTE number (15344 ms) then take the  71 root of THAT (140 ms) 1 times
12578 ms to take the 3337 root of a 10000000 BYTE number 1 times

15312 ms to take the 53 root of a 10000000 BYTE number (15187 ms) then take the  53 root of THAT (125 ms) 1 times
11843 ms to take the 2809 root of a 10000000 BYTE number 1 times

15375 ms to take the 59 root of a 10000000 BYTE number (15250 ms) then take the  53 root of THAT (125 ms) 1 times
13375 ms to take the 53 root of a 10000000 BYTE number (13219 ms) then take the  59 root of THAT (156 ms) 1 times
13907 ms to take the 3127 root of a 10000000 BYTE number 1 times

14329 ms to take the 61 root of a 10000000 BYTE number (14219 ms) then take the  53 root of THAT (110 ms) 1 times
13344 ms to take the 53 root of a 10000000 BYTE number (13203 ms) then take the  61 root of THAT (141 ms) 1 times
12031 ms to take the 3233 root of a 10000000 BYTE number 1 times

15626 ms to take the 67 root of a 10000000 BYTE number (15485 ms) then take the  53 root of THAT (141 ms) 1 times
13766 ms to take the 53 root of a 10000000 BYTE number (13547 ms) then take the  67 root of THAT (219 ms) 1 times
22531 ms to take the 3551 root of a 10000000 BYTE number 1 times

17235 ms to take the 71 root of a 10000000 BYTE number (17141 ms) then take the  53 root of THAT (94 ms) 1 times
13359 ms to take the 53 root of a 10000000 BYTE number (13219 ms) then take the  71 root of THAT (140 ms) 1 times
14610 ms to take the 3763 root of a 10000000 BYTE number 1 times

14953 ms to take the 59 root of a 10000000 BYTE number (14812 ms) then take the  59 root of THAT (141 ms) 1 times
16344 ms to take the 3481 root of a 10000000 BYTE number 1 times

13782 ms to take the 61 root of a 10000000 BYTE number (13672 ms) then take the  59 root of THAT (110 ms) 1 times
15000 ms to take the 59 root of a 10000000 BYTE number (14875 ms) then take the  61 root of THAT (125 ms) 1 times
12531 ms to take the 3599 root of a 10000000 BYTE number 1 times

15204 ms to take the 67 root of a 10000000 BYTE number (15094 ms) then take the  59 root of THAT (110 ms) 1 times
14968 ms to take the 59 root of a 10000000 BYTE number (14859 ms) then take the  67 root of THAT (109 ms) 1 times
13062 ms to take the 3953 root of a 10000000 BYTE number 1 times

18719 ms to take the 71 root of a 10000000 BYTE number (18625 ms) then take the  59 root of THAT (94 ms) 1 times
16922 ms to take the 59 root of a 10000000 BYTE number (16797 ms) then take the  71 root of THAT (125 ms) 1 times
13735 ms to take the 4189 root of a 10000000 BYTE number 1 times

16765 ms to take the 61 root of a 10000000 BYTE number (16640 ms) then take the  61 root of THAT (125 ms) 1 times
12625 ms to take the 3721 root of a 10000000 BYTE number 1 times

18563 ms to take the 67 root of a 10000000 BYTE number (18469 ms) then take the  61 root of THAT (94 ms) 1 times
16938 ms to take the 61 root of a 10000000 BYTE number (16797 ms) then take the  67 root of THAT (141 ms) 1 times
14906 ms to take the 4087 root of a 10000000 BYTE number 1 times

19468 ms to take the 71 root of a 10000000 BYTE number (19390 ms) then take the  61 root of THAT (78 ms) 1 times
14156 ms to take the 61 root of a 10000000 BYTE number (14031 ms) then take the  71 root of THAT (125 ms) 1 times
12281 ms to take the 4331 root of a 10000000 BYTE number 1 times

15609 ms to take the 67 root of a 10000000 BYTE number (15500 ms) then take the  67 root of THAT (109 ms) 1 times
10766 ms to take the 4489 root of a 10000000 BYTE number 1 times

17281 ms to take the 71 root of a 10000000 BYTE number (17171 ms) then take the  67 root of THAT (110 ms) 1 times
15484 ms to take the 67 root of a 10000000 BYTE number (15375 ms) then take the  71 root of THAT (109 ms) 1 times
11250 ms to take the 4757 root of a 10000000 BYTE number 1 times

17312 ms to take the 71 root of a 10000000 BYTE number (17140 ms) then take the  71 root of THAT (172 ms) 1 times
11235 ms to take the 5041 root of a 10000000 BYTE number 1 times*/

void CArithmeticPerformanceTester::CompareNthRootProblemBreakdownTimes()
{
    const unsigned int c_nMinNumberSizeInBYTEs = 100000, c_nMaxNumberSizeInBYTEs = 10000000;
    unsigned int       nTimeA, nTimeB, nTime;
    size_t             nRootSize;
    CBigIntegerForTest nX, nRootX, nXCopy;
    int                nIterations = 100;
    nX.Reserve(c_nMaxNumberSizeInBYTEs + 1);
    nRootX.Reserve(c_nMaxNumberSizeInBYTEs + 1);
    nXCopy.Reserve(c_nMaxNumberSizeInBYTEs + 1);
    // comparing problem paritioning for compouting general roots.  Doing this in retail?  If no, your
    // numbers might not be representative
    DIGIT *pWorkspace = (DIGIT *) malloc(sizeof(DIGIT)*NthRootMemoryNeeds(c_nMaxNumberSizeInBYTEs, c_pnOneBYTEPrimes[19])*2);
    for (size_t nSize = c_nMinNumberSizeInBYTEs; nSize <= c_nMaxNumberSizeInBYTEs; nSize *= 10)
    {
        for(int i=0; i<20; i++) // upper bound at most c_nNumOneBYTEPrimes
        {
            DIGIT m = c_pnOneBYTEPrimes[i];
            for(int j=i; j<20; j++)
            {
                DIGIT n = c_pnOneBYTEPrimes[j];
                nTimeA = 0;
                nTimeB = 0;
                for (int k=0; k<nIterations; k++)
                {
                    srand(k);
                    nX.SetRandom(nSize*8);
                    nXCopy = nX;
                    nTime  = ::GetTickCount();
                    if (2 == n)
                    {
                        SQRT(nXCopy.GetSize(), nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
                    }
                    else
                    {
                        NthRoot(nXCopy.GetSize(), n, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
                    }
                    nTimeA += (::GetTickCount() - nTime);
                    nXCopy =  nX;
                    nTime  =  ::GetTickCount();
                    if (2 == m)
                    {
                        SQRT(nRootSize, nRootSize, nRootX.GetValue(), nXCopy.GetValue(), pWorkspace);
                    }
                    else
                    {
                        NthRoot(nRootSize, m, nRootSize, nRootX.GetValue(), nXCopy.GetValue(), pWorkspace);
                    }
                    nTimeB += (::GetTickCount() - nTime);
                }
                printf("%u ms to take the %u root of a %u BYTE number (%u ms) then take the  %u root of THAT (%u ms) %u times\n", nTimeA + nTimeB, n, nX.GetSize()*sizeof(DIGIT), nTimeA, m, nTimeB, nIterations);
                if (n != m)
                {
                    nTimeA = 0;
                    nTimeB = 0;
                    for (int k=0; k<nIterations; k++)
                    {
                        srand(k);
                        nX.SetRandom(nSize*8);
                        nXCopy = nX;
                        nTime  = ::GetTickCount();
                        if (2 == m)
                        {
                            SQRT(nXCopy.GetSize(), nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
                        }
                        else
                        {
                            NthRoot(nXCopy.GetSize(), m, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
                        }
                        nTimeA += (::GetTickCount() - nTime);
                        nXCopy =  nX;
                        nTime  =  ::GetTickCount();
                        if (2 == n)
                        {
                            SQRT(nRootSize, nRootSize, nRootX.GetValue(), nXCopy.GetValue(), pWorkspace);
                        }
                        else
                        {
                            NthRoot(nRootSize, n, nRootSize, nRootX.GetValue(), nXCopy.GetValue(), pWorkspace);
                        }
                        nTimeB += (::GetTickCount() - nTime);
                    }
                    printf("%u ms to take the %u root of a %u BYTE number (%u ms) then take the  %u root of THAT (%u ms) %u times\n", nTimeA + nTimeB, m, nX.GetSize()*sizeof(DIGIT), nTimeA, n, nTimeB, nIterations);
                }
                nTimeA = 0;
                for (int k=0; k<nIterations; k++)
                {
                    srand(k);
                    nX.SetRandom(nSize * 8);
                    nXCopy = nX;
                    nTime = ::GetTickCount();
                    NthRoot(nXCopy.GetSize(), m*n, nRootSize, nXCopy.GetValue(), nRootX.GetValue(), pWorkspace);
                    nTimeA += (::GetTickCount() - nTime);
                }
                nTimeB = ::GetTickCount() - nTimeB;
                printf("%u ms to take the %u root of a %u BYTE number %u times\n\n", nTimeA, m*n, nX.GetSize()*sizeof(DIGIT), nIterations);
            }
        }
        nIterations /= 10;
    }
    free(pWorkspace);
}

void CArithmeticPerformanceTester::MatrixMultiplyTimes()
{
    CBigIntegerForTest nBigInt;
    CArithmeticBox     cBox;
    const unsigned int c_nMaxMatrixSize = 1536; // up to c_nMaxMatrixSizexc_nMaxMatrixSize matrix multiplication
    const unsigned int c_nMaxNumberSize = 16;   // size in DIGITs
    unsigned int       nTime;
    unsigned int       nIterations = 1, nSize = 12;
    // find minimum number of iterations for 12x12 basic multiplication with 1-DIGIT numbers to take 1 second
    do
    {
        CBigIntegerMatrix nMat1(nSize, nSize);
        CBigIntegerMatrix nMat2(nSize, nSize);
        CBigIntegerMatrix nProdOracle(nSize, nSize);
        for (int i=0; i<nSize; i++)
        {
            for (int j=0; j<nSize; j++)
            {
                nBigInt.SetRandom(_DIGIT_SIZE_IN_BITS);
                nBigInt.SetNegative(rand()%2);
                nMat1[i][j] = nBigInt;
                nBigInt.SetRandom(_DIGIT_SIZE_IN_BITS);
                nBigInt.SetNegative(rand()%2);
                nMat2[i][j] = nBigInt;
            }
        }
        nTime = ::GetTickCount();
        for(int i=0;i<nIterations; i++)
        {
            CBigIntegerMatrix::MultiplyOracle(nMat1, nMat2, nProdOracle, cBox);
        }
        nTime = ::GetTickCount()-nTime;
        if(1000<nTime) break;
        nIterations *= 2;
    }
    while (true);
    for(;nSize<=c_nMaxMatrixSize;nSize*=2)
    {
        CBigIntegerMatrix nMat1(nSize, nSize);
        CBigIntegerMatrix nMat2(nSize, nSize);
        CBigIntegerMatrix nProdOracle(nSize, nSize);
        CBigIntegerMatrix nProdStrassen(nSize, nSize);
        printf("Using %i iterations\n", nIterations);
        for (int nDigits=1; nDigits<=c_nMaxNumberSize; nDigits++)
        {
            for (int i=0; i<nSize; i++)
            {
                for (int j=0; j<nSize; j++)
                {
                    nBigInt.SetRandom(nDigits*_DIGIT_SIZE_IN_BITS);
                    nBigInt.SetNegative(rand()%2);
                    nMat1[i][j] = nBigInt;
                    nBigInt.SetRandom(nDigits*_DIGIT_SIZE_IN_BITS);
                    nBigInt.SetNegative(rand()%2);
                    nMat2[i][j] = nBigInt;
                }
            }
            nTime = ::GetTickCount();
            for(int i=0;i<nIterations; i++)
            {
                CBigIntegerMatrix::MultiplyOracle(nMat1, nMat2, nProdOracle, cBox);
            }
            nTime = ::GetTickCount() - nTime;
            printf("Basic matrix multiplier took    %u milliseconds for square matrix of size %u with entries of %u DIGITs\n",nTime,nSize,nDigits);
            nTime = ::GetTickCount();
            for(int i=0;i<nIterations; i++)
            {
                CBigIntegerMatrix::Multiply(nMat1, nMat2, nProdStrassen, cBox);
            }
            printf("Strassen matrix multiplier took %u milliseconds for square matrix of size %u with entries of %u DIGITs\n",::GetTickCount()-nTime,nSize,nDigits);
            if (nProdStrassen != nProdOracle) printf("uh-oh -- %u %u\n", nSize, nDigits);
        }
        nIterations = (nIterations+7)/8;
    }
}