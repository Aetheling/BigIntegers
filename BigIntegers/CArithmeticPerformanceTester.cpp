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
            if(1000000<dwStartTime) break; // 10 seconds better?  Or 1 second?
            nIterations *= 2;
        }
        while (true);
        printf("Time for %i %ix%i BYTE multiplications: %I64u microseconds\n", nIterations, nX.GetSize()*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        ResetTimingData();
        dwMultTime = dwStartTime;
        if(nX.GetSize()<=1000000)
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
    printf("Doing this in retail?  If not, your numbers won't be representative\n");
    for(int nSize=c_nMinBitSize; nSize<=c_nMaxBitSize; nSize *= 2)
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
    ReportMeasuredComponentTimingData(eDivideMeasured);
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