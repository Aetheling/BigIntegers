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
16-bit DIGITs
A glitch in the code meant it didn't stop boosting the size to check.  Overnight run.  For size 268435456
the memory required for FFT meant some paging, which slowed it down -- though fft square doesn't require as much,
and looks like it was ok.  Size 536870912 was running FFT when I caught it, and was definitely running into
paging trouble for FFT -- enough to drop it to a quarter of a CPU or less instead of full -- and I killed
the run.
Size 1 x 1 digits       Memory (basic): 0 kB FFT: 0 kB
Non-FFT multiply:  0 microseconds
FFT multiply:      1 microseconds       Field size: 4 Length: 2
FFT square:        1 microseconds

Size 2 x 2 digits       Memory (basic): 0 kB FFT: 0 kB
Non-FFT multiply:  0 microseconds
FFT multiply:      1 microseconds       Field size: 4 Length: 4
FFT square:        0 microseconds

Size 4 x 4 digits       Memory (basic): 0 kB FFT: 0 kB
Non-FFT multiply:  0 microseconds
FFT multiply:      2 microseconds       Field size: 4 Length: 8
FFT square:        2 microseconds

Size 8 x 8 digits       Memory (basic): 0 kB FFT: 0 kB
Non-FFT multiply:  1 microseconds
FFT multiply:      5 microseconds       Field size: 4 Length: 16
FFT square:        4 microseconds

Size 16 x 16 digits     Memory (basic): 0 kB FFT: 0 kB
Non-FFT multiply:  0 microseconds
FFT multiply:      10 microseconds      Field size: 4 Length: 32
FFT square:        8 microseconds

Size 32 x 32 digits     Memory (basic): 0 kB FFT: 1 kB
Non-FFT multiply:  1 microseconds
FFT multiply:      26 microseconds      Field size: 4 Length: 64
FFT square:        47 microseconds

Size 64 x 64 digits     Memory (basic): 0 kB FFT: 2 kB
Non-FFT multiply:  3 microseconds
FFT multiply:      51 microseconds      Field size: 4 Length: 128
FFT square:        51 microseconds

Size 128 x 128 digits   Memory (basic): 1 kB FFT: 4 kB
Non-FFT multiply:  12 microseconds
FFT multiply:      62 microseconds      Field size: 8 Length: 128
FFT square:        53 microseconds

Size 256 x 256 digits   Memory (basic): 3 kB FFT: 9 kB
Non-FFT multiply:  26 microseconds
FFT multiply:      261 microseconds     Field size: 8 Length: 256
FFT square:        103 microseconds

Size 512 x 512 digits   Memory (basic): 6 kB FFT: 17 kB
Non-FFT multiply:  66 microseconds
FFT multiply:      250 microseconds     Field size: 16 Length: 256
FFT square:        195 microseconds

Size 1024 x 1024 digits Memory (basic): 12 kB FFT: 34 kB
Non-FFT multiply:  187 microseconds
FFT multiply:      550 microseconds     Field size: 16 Length: 512
FFT square:        422 microseconds

Size 2048 x 2048 digits Memory (basic): 24 kB FFT: 66 kB
Non-FFT multiply:  484 microseconds
FFT multiply:      1090 microseconds    Field size: 32 Length: 512
FFT square:        811 microseconds

Size 4096 x 4096 digits Memory (basic): 48 kB FFT: 132 kB
Non-FFT multiply:  1431 microseconds
FFT multiply:      2998 microseconds    Field size: 32 Length: 1024
FFT square:        2198 microseconds

Size 8192 x 8192 digits Memory (basic): 96 kB FFT: 260 kB
Non-FFT multiply:  4149 microseconds
FFT multiply:      6291 microseconds    Field size: 64 Length: 1024
FFT square:        5104 microseconds

Size 16384 x 16384 digits       Memory (basic): 192 kB FFT: 520 kB
Non-FFT multiply:  12408 microseconds
FFT multiply:      14674 microseconds   Field size: 64 Length: 2048
FFT square:        9275 microseconds

Size 32768 x 32768 digits       Memory (basic): 384 kB FFT: 1032 kB
Non-FFT multiply:  32439 microseconds
FFT multiply:      33898 microseconds   Field size: 128 Length: 2048
FFT square:        18313 microseconds

Size 65536 x 65536 digits       Memory (basic): 768 kB FFT: 2064 kB
Non-FFT multiply:  73526 microseconds
FFT multiply:      61517 microseconds   Field size: 128 Length: 4096
FFT square:        40439 microseconds

Size 131072 x 131072 digits     Memory (basic): 1536 kB FFT: 4112 kB
Non-FFT multiply:  196279 microseconds
FFT multiply:      148131 microseconds  Field size: 256 Length: 4096
FFT square:        112953 microseconds

Size 262144 x 262144 digits     Memory (basic): 3072 kB FFT: 8224 kB
Non-FFT multiply:  503429 microseconds
FFT multiply:      276629 microseconds  Field size: 256 Length: 8192
FFT square:        221983 microseconds

Size 524288 x 524288 digits     Memory (basic): 12288 kB FFT: 16416 kB
Non-FFT multiply:  1249065 microseconds
FFT multiply:      715274 microseconds  Field size: 512 Length: 8192
FFT square:        525922 microseconds

Size 1048576 x 1048576 digits   Memory (basic): 24576 kB FFT: 32832 kB
Non-FFT multiply:  2624524 microseconds
FFT multiply:      1450516 microseconds Field size: 512 Length: 16384
FFT square:        1068348 microseconds

Size 2097152 x 2097152 digits   Memory (basic): 49152 kB FFT: 65600 kB
Non-FFT multiply:  7674586 microseconds
FFT multiply:      3697381 microseconds Field size: 1024 Length: 16384
FFT square:        2898388 microseconds

Size 4194304 x 4194304 digits   Memory (basic): 98304 kB FFT: 131200 kB
Non-FFT multiply:  17527355 microseconds
FFT multiply:      8198641 microseconds Field size: 1024 Length: 32768
FFT square:        6221806 microseconds

Size 8388608 x 8388608 digits   Memory (basic): 196608 kB FFT: 262272 kB
Non-FFT multiply:  41490235 microseconds
FFT multiply:      19506699 microseconds        Field size: 2048 Length: 32768
FFT square:        14380397 microseconds

Size 16777216 x 16777216 digits Memory (basic): 393216 kB FFT: 524544 kB
Non-FFT multiply:  108299615 microseconds
FFT multiply:      39110705 microseconds        Field size: 2048 Length: 65536
Oopsie! a
FFT square:        28603240 microseconds

Size 33554432 x 33554432 digits Memory (basic): 786432 kB FFT: 1048832 kB
Non-FFT multiply:  266250460 microseconds
FFT multiply:      99082196 microseconds        Field size: 4096 Length: 65536
Oopsie! a
FFT square:        79706583 microseconds

Size 67108864 x 67108864 digits Memory (basic): 1572864 kB FFT: 2097664 kB
Non-FFT multiply:  611039332 microseconds
FFT multiply:      202262026 microseconds       Field size: 4096 Length: 131072
Oopsie! a
FFT square:        160500746 microseconds

Size 134217728 x 134217728 digits       Memory (basic): 3145728 kB FFT: 4194816 kB
Non-FFT multiply:  1577884315 microseconds
FFT multiply:      792932464 microseconds       Field size: 8192 Length: 131072
Oopsie! a
FFT square:        560408961 microseconds

Size 268435456 x 268435456 digits       Memory (basic): 6291456 kB FFT: 8389632 kB
Non-FFT multiply:  3865937840 microseconds
FFT multiply:      3681420619 microseconds      Field size: 8192 Length: 262144
Oopsie! a
FFT square:        1999236570 microseconds

Size 536870912 x 536870912 digits       Memory (basic): 12582912 kB FFT: 16778240 kB
Non-FFT multiply:  9252119753 microseconds
32-bit DIGITs
Size 1048576 x 1048576 digits   Memory (basic): 24576 kB FFT: 65664 kB
Non-FFT multiply:  2254079 microseconds
FFT multiply:      1293867 microseconds Field size: 512 Length: 16384
FFT square:        1146962 microseconds

Size 2097152 x 2097152 digits   Memory (basic): 98304 kB FFT: 131328 kB
Non-FFT multiply:  5113155 microseconds
FFT multiply:      2613738 microseconds Field size: 512 Length: 32768
FFT square:        2333267 microseconds

Size 4194304 x 4194304 digits   Memory (basic): 196608 kB FFT: 262400 kB
Non-FFT multiply:  12200036 microseconds
FFT multiply:      6389781 microseconds Field size: 1024 Length: 32768
FFT square:        5251841 microseconds

Size 8388608 x 8388608 digits   Memory (basic): 393216 kB FFT: 524800 kB
Non-FFT multiply:  31917341 microseconds
FFT multiply:      13237855 microseconds        Field size: 1024 Length: 65536
FFT square:        11566872 microseconds

Size 16777216 x 16777216 digits Memory (basic): 786432 kB FFT: 1049088 kB
Non-FFT multiply:  74563039 microseconds
FFT multiply:      31716128 microseconds        Field size: 2048 Length: 65536
FFT square:        27441403 microseconds

Size 33554432 x 33554432 digits Memory (basic): 1572864 kB FFT: 2098176 kB
Non-FFT multiply:  183891977 microseconds
FFT multiply:      63903001 microseconds        Field size: 2048 Length: 131072
FFT square:        56134715 microseconds

Size 67108864 x 67108864 digits Memory (basic): 3145728 kB FFT: 4195328 kB
Non-FFT multiply:  471217727 microseconds
FFT multiply:      160597996 microseconds       Field size: 4096 Length: 131072
FFT square:        145773495 microseconds

Size 2 x 2 bytes        Memory (basic): 0 kB FFT: 0 kB
Non-FFT multiply:  0 microseconds
FFT multiply:      0 microseconds       Field size: 4 Length: 2
FFT square:        1 microseconds

Size 4 x 4 bytes        Memory (basic): 0 kB FFT: 0 kB
Non-FFT multiply:  0 microseconds
FFT multiply:      1 microseconds       Field size: 4 Length: 4
FFT square:        1 microseconds

Size 8 x 8 bytes        Memory (basic): 0 kB FFT: 0 kB
Non-FFT multiply:  0 microseconds
FFT multiply:      2 microseconds       Field size: 4 Length: 8
FFT square:        1 microseconds

Size 16 x 16 bytes      Memory (basic): 0 kB FFT: 0 kB
Non-FFT multiply:  0 microseconds
FFT multiply:      4 microseconds       Field size: 4 Length: 16
FFT square:        4 microseconds

Size 32 x 32 bytes      Memory (basic): 0 kB FFT: 0 kB
Non-FFT multiply:  1 microseconds
FFT multiply:      23 microseconds      Field size: 4 Length: 32
FFT square:        7 microseconds

Size 64 x 64 bytes      Memory (basic): 0 kB FFT: 1 kB
Non-FFT multiply:  1 microseconds
FFT multiply:      50 microseconds      Field size: 4 Length: 64
FFT square:        42 microseconds

Size 128 x 128 bytes    Memory (basic): 0 kB FFT: 2 kB
Non-FFT multiply:  3 microseconds
FFT multiply:      48 microseconds      Field size: 4 Length: 128
FFT square:        38 microseconds

Size 256 x 256 bytes    Memory (basic): 1 kB FFT: 4 kB
Non-FFT multiply:  9 microseconds
FFT multiply:      77 microseconds      Field size: 8 Length: 128
FFT square:        46 microseconds

Size 512 x 512 bytes    Memory (basic): 3 kB FFT: 9 kB
Non-FFT multiply:  24 microseconds
FFT multiply:      138 microseconds     Field size: 8 Length: 256
FFT square:        115 microseconds

Size 1024 x 1024 bytes  Memory (basic): 6 kB FFT: 17 kB
Non-FFT multiply:  65 microseconds
FFT multiply:      242 microseconds     Field size: 16 Length: 256
FFT square:        257 microseconds

Size 2048 x 2048 bytes  Memory (basic): 12 kB FFT: 34 kB
Non-FFT multiply:  186 microseconds
FFT multiply:      536 microseconds     Field size: 16 Length: 512
FFT square:        370 microseconds

Size 4096 x 4096 bytes  Memory (basic): 24 kB FFT: 66 kB
Non-FFT multiply:  472 microseconds
FFT multiply:      1065 microseconds    Field size: 32 Length: 512
FFT square:        730 microseconds

Size 8192 x 8192 bytes  Memory (basic): 48 kB FFT: 132 kB
Non-FFT multiply:  1257 microseconds
FFT multiply:      2340 microseconds    Field size: 32 Length: 1024
FFT square:        1565 microseconds

Size 16384 x 16384 bytes        Memory (basic): 96 kB FFT: 260 kB
Non-FFT multiply:  3311 microseconds
FFT multiply:      4990 microseconds    Field size: 64 Length: 1024
FFT square:        4980 microseconds

Size 32768 x 32768 bytes        Memory (basic): 192 kB FFT: 520 kB
Non-FFT multiply:  12165 microseconds
FFT multiply:      13792 microseconds   Field size: 64 Length: 2048
FFT square:        9685 microseconds

Size 65536 x 65536 bytes        Memory (basic): 384 kB FFT: 1032 kB
Non-FFT multiply:  27043 microseconds
FFT multiply:      26431 microseconds   Field size: 128 Length: 2048
FFT square:        19381 microseconds

Size 131072 x 131072 bytes      Memory (basic): 768 kB FFT: 2064 kB
Non-FFT multiply:  74156 microseconds
FFT multiply:      65661 microseconds   Field size: 128 Length: 4096
FFT square:        39846 microseconds

Size 262144 x 262144 bytes      Memory (basic): 1536 kB FFT: 4112 kB
Non-FFT multiply:  185330 microseconds
FFT multiply:      147175 microseconds  Field size: 256 Length: 4096
FFT square:        115771 microseconds

Size 524288 x 524288 bytes      Memory (basic): 3072 kB FFT: 8224 kB
Non-FFT multiply:  476726 microseconds
FFT multiply:      278344 microseconds  Field size: 256 Length: 8192
FFT square:        216034 microseconds

Size 1048576 x 1048576 bytes    Memory (basic): 12288 kB FFT: 16416 kB
Non-FFT multiply:  1175009 microseconds
FFT multiply:      728192 microseconds  Field size: 512 Length: 8192
FFT square:        525859 microseconds

Size 2097152 x 2097152 bytes    Memory (basic): 24576 kB FFT: 32832 kB
Non-FFT multiply:  2616421 microseconds
FFT multiply:      1485186 microseconds Field size: 512 Length: 16384
FFT square:        1080443 microseconds

Size 4194304 x 4194304 bytes    Memory (basic): 49152 kB FFT: 65600 kB
Non-FFT multiply:  7852123 microseconds
FFT multiply:      3717497 microseconds Field size: 1024 Length: 16384
FFT square:        2985134 microseconds

Size 8388608 x 8388608 bytes    Memory (basic): 98304 kB FFT: 131200 kB
Non-FFT multiply:  17812996 microseconds
FFT multiply:      7844061 microseconds Field size: 1024 Length: 32768
FFT square:        6035109 microseconds

Size 16777216 x 16777216 bytes  Memory (basic): 196608 kB FFT: 262272 kB
Non-FFT multiply:  41659694 microseconds
FFT multiply:      19884605 microseconds        Field size: 2048 Length: 32768
FFT square:        14318553 microseconds

Size 33554432 x 33554432 bytes  Memory (basic): 393216 kB FFT: 524544 kB
Non-FFT multiply:  108541196 microseconds
FFT multiply:      38923343 microseconds        Field size: 2048 Length: 65536
FFT square:        29582722 microseconds

Size 67108864 x 67108864 bytes  Memory (basic): 786432 kB FFT: 1048832 kB
Non-FFT multiply:  267051622 microseconds
FFT multiply:      99469614 microseconds        Field size: 4096 Length: 65536
FFT square:        79768393 microseconds

Size 134217728 x 134217728 bytes        Memory (basic): 1572864 kB FFT: 2097664 kB
Non-FFT multiply:  608890459 microseconds
FFT multiply:      202539954 microseconds       Field size: 4096 Length: 131072
FFT square:        161289367 microseconds

Size 268435456 x 268435456 bytes        Memory (basic): 3145728 kB FFT: 4194816 kB
Non-FFT multiply:  1584910497 microseconds
FFT multiply:      759732035 microseconds       Field size: 8192 Length: 131072
FFT square:        537034445 microseconds
*/
void CArithmeticPerformanceTester::CompareBaseMultiplicationToFFT()
{
    CBigIntegerForTest nX,nY,nXCopy,nYCopy,nProduct,nProductBaseline;
    DWORD64            dwStartTime;
    CArithmeticBox     cBox;
    CWorkspace         cWork;
    size_t             nProductSize;
    printf("If you're not doing this with a retail build, you're not getting good numbers\n");
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
        ResetThresholdsForOptimization(); // so we DO use FFT multiply for subproblems (if appropriate to the size)
        // force top level at least to use FFT
        if (c_pnMultiplicationThresholds[e2NByN] <= nX.GetSize()) c_pnMultiplicationThresholds[e2NByN] = nX.GetSize() - 1;
        if (c_pnMultiplicationThresholds[e2NByN] <= nY.GetSize()) c_pnMultiplicationThresholds[e2NByN] = nY.GetSize() - 1;
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
        }
        ResetTimingData();
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
        Square(nX.GetSize(),nX.GetValue(),nProduct.GetValue(),cWork.GetSpace());
        dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        if(1000000>dwStartTime)
        {
            // redo -- looks like loading the basic code takes a while, throwing off timing data
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
            Square(nX.GetSize(),nX.GetValue(),nProduct.GetValue(),cWork.GetSpace());
        }
        printf("FFT square:        %I64u microseconds\n",dwStartTime);
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
    }
}

/*
Some sample times from the test: 32-bit DIGITs *definitely* work better on the computer the run was done on!
Values taken with parameters optimized for the given DIGIT size
16-bit DIGITs
Multiply two 2 BYTE numbers:    0 microseconds
Square   two 2 BYTE numbers:    0 microseconds
Multiply two 4 BYTE numbers:    0 microseconds
Square   two 4 BYTE numbers:    0 microseconds
Multiply two 8 BYTE numbers:    0 microseconds
Square   two 8 BYTE numbers:    0 microseconds
Multiply two 16 BYTE numbers:   0 microseconds
Square   two 16 BYTE numbers:   0 microseconds
Multiply two 32 BYTE numbers:   1 microseconds
Square   two 32 BYTE numbers:   0 microseconds
Multiply two 64 BYTE numbers:   1 microseconds
Square   two 64 BYTE numbers:   1 microseconds
Multiply two 128 BYTE numbers:  3 microseconds
Square   two 128 BYTE numbers:  3 microseconds
Multiply two 256 BYTE numbers:  8 microseconds
Square   two 256 BYTE numbers:  19 microseconds
Multiply two 512 BYTE numbers:  23 microseconds
Square   two 512 BYTE numbers:  20 microseconds
Multiply two 1024 BYTE numbers: 64 microseconds
Square   two 1024 BYTE numbers: 51 microseconds
Multiply two 2048 BYTE numbers: 174 microseconds
Square   two 2048 BYTE numbers: 148 microseconds
Multiply two 4096 BYTE numbers: 475 microseconds
Square   two 4096 BYTE numbers: 376 microseconds
Multiply two 8192 BYTE numbers: 1457 microseconds
Square   two 8192 BYTE numbers: 1058 microseconds
Multiply two 16384 BYTE numbers:        5038 microseconds
Square   two 16384 BYTE numbers:        3664 microseconds
Multiply two 32768 BYTE numbers:        12886 microseconds
Square   two 32768 BYTE numbers:        8887 microseconds
Multiply two 65536 BYTE numbers:        28408 microseconds
Square   two 65536 BYTE numbers:        20533 microseconds
Multiply two 131072 BYTE numbers:       76334 microseconds
Square   two 131072 BYTE numbers:       51898 microseconds
Multiply two 262144 BYTE numbers:       179871 microseconds
Square   two 262144 BYTE numbers:       131069 microseconds
Multiply two 524288 BYTE numbers:       320667 microseconds
Square   two 524288 BYTE numbers:       239898 microseconds
Multiply two 1048576 BYTE numbers:      738666 microseconds
Square   two 1048576 BYTE numbers:      564027 microseconds
Multiply two 2097152 BYTE numbers:      1561971 microseconds
Square   two 2097152 BYTE numbers:      1205823 microseconds
Multiply two 4194304 BYTE numbers:      3849631 microseconds
Square   two 4194304 BYTE numbers:      3016566 microseconds
Multiply two 8388608 BYTE numbers:      8049993 microseconds
Square   two 8388608 BYTE numbers:      6658954 microseconds
Multiply two 16777216 BYTE numbers:     21328371 microseconds
Square   two 16777216 BYTE numbers:     15730502 microseconds
Multiply two 33554432 BYTE numbers:     42074805 microseconds
Square   two 33554432 BYTE numbers:     30190172 microseconds
Multiply two 67108864 BYTE numbers:     103665839 microseconds
Square   two 67108864 BYTE numbers:     82758260 microseconds
Multiply two 134217728 BYTE numbers:    209512909 microseconds
Square   two 134217728 BYTE numbers:    167213775 microseconds
Multiply two 268435456 BYTE numbers:    771517689 microseconds
Square   two 268435456 BYTE numbers:    537943178 microseconds

32-bit DIGITs
Size: 4x4 (BYTEs) took  0 microseconds for multiply
Size: 4 (BYTEs) took  0 microseconds for square
Size: 4x4 (BYTEs) took  0 microseconds for multiply
Size: 4 (BYTEs) took  0 microseconds for square
Size: 8x8 (BYTEs) took  0 microseconds for multiply
Size: 8 (BYTEs) took  0 microseconds for square
Size: 16x16 (BYTEs) took  0 microseconds for multiply
Size: 16 (BYTEs) took  1 microseconds for square
Size: 32x32 (BYTEs) took  0 microseconds for multiply
Size: 32 (BYTEs) took  1 microseconds for square
Size: 64x64 (BYTEs) took  0 microseconds for multiply
Size: 64 (BYTEs) took  0 microseconds for square
Size: 128x128 (BYTEs) took  1 microseconds for multiply
Size: 128 (BYTEs) took  1 microseconds for square
Size: 256x256 (BYTEs) took  2 microseconds for multiply
Size: 256 (BYTEs) took  2 microseconds for square
Size: 512x512 (BYTEs) took  7 microseconds for multiply
Size: 512 (BYTEs) took  7 microseconds for square
Size: 1024x1024 (BYTEs) took  32 microseconds for multiply
Size: 1024 (BYTEs) took  31 microseconds for square
Size: 2048x2048 (BYTEs) took  49 microseconds for multiply
Size: 2048 (BYTEs) took  47 microseconds for square
Size: 4096x4096 (BYTEs) took  203 microseconds for multiply
Size: 4096 (BYTEs) took  133 microseconds for square
Size: 8192x8192 (BYTEs) took  340 microseconds for multiply
Size: 8192 (BYTEs) took  322 microseconds for square
Size: 16384x16384 (BYTEs) took  962 microseconds for multiply
Size: 16384 (BYTEs) took  956 microseconds for square
Size: 32768x32768 (BYTEs) took  2461 microseconds for multiply
Size: 32768 (BYTEs) took  2216 microseconds for square
Size: 65536x65536 (BYTEs) took  9947 microseconds for multiply
Size: 65536 (BYTEs) took  8612 microseconds for square
Size: 131072x131072 (BYTEs) took  20859 microseconds for multiply
Size: 131072 (BYTEs) took  16926 microseconds for square
Size: 262144x262144 (BYTEs) took  50054 microseconds for multiply
Size: 262144 (BYTEs) took  41462 microseconds for square
Size: 524288x524288 (BYTEs) took  106045 microseconds for multiply
Size: 524288 (BYTEs) took  84866 microseconds for square
Size: 1048576x1048576 (BYTEs) took  249249 microseconds for multiply
Size: 1048576 (BYTEs) took  207604 microseconds for square
Size: 2097152x2097152 (BYTEs) took  517250 microseconds for multiply
Size: 2097152 (BYTEs) took  428414 microseconds for square
Size: 4194304x4194304 (BYTEs) took  1238874 microseconds for multiply
Size: 4194304 (BYTEs) took  1073002 microseconds for square
Size: 8388608x8388608 (BYTEs) took  2578202 microseconds for multiply
Size: 8388608 (BYTEs) took  2185527 microseconds for square
Size: 16777216x16777216 (BYTEs) took  6390043 microseconds for multiply
Size: 16777216 (BYTEs) took  5629612 microseconds for square
Size: 33554432x33554432 (BYTEs) took  13280130 microseconds for multiply
Size: 33554432 (BYTEs) took  11397036 microseconds for square
Size: 67108864x67108864 (BYTEs) took  31985696 microseconds for multiply
Size: 67108864 (BYTEs) took  28496749 microseconds for square
Size: 134217728x134217728 (BYTEs) took  67252137 microseconds for multiply
Size: 134217728 (BYTEs) took  55928370 microseconds for square
Size: 268435456x268435456 (BYTEs) took  162160440 microseconds for multiply
Size: 268435456 (BYTEs) took  146095577 microseconds for square*/
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
        size_t nMemoryNeeds = MultiplyMemoryNeeds(nX.GetSize(),nY.GetSize());
        if(!cWork.Reserve(nMemoryNeeds))
        {
            printf("couldn't allocate workspace -- baseline\n");
            break;
        }
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
#if _CollectDetailedTimingData
        DWORD64 dwTimestamp = dwStartTime;
        MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProduct.GetValue(),cWork.GetSpace(),dwTimestamp);
#else
        MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProduct.GetValue(),cWork.GetSpace());
#endif
        dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        if(1000000>dwStartTime)
        {
            // redo -- looks like it takes a while to load the basic code, throwing off timing
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
#if _CollectDetailedTimingData
            DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
            MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProduct.GetValue(),cWork.GetSpace(),dwTimestamp,&nProductSize);
#else
            MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProduct.GetValue(),cWork.GetSpace(),&nProductSize);
#endif
            dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        }
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        printf("Multiply two %i BYTE numbers:\t%I64u microseconds\n",nX.GetSize()*sizeof(DIGIT),dwStartTime);
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
#if(_CollectDetailedTimingData)
        dwTimestamp = dwStartTime;
        SquareUBackend(nX.GetSize(), nX.GetValue(), nProduct.GetValue(), cWork.GetSpace(), dwStartTime);
#else
        SquareUBackend(nX.GetSize(), nX.GetValue(), nProduct.GetValue(), cWork.GetSpace());
#endif
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        if (1000000 > dwStartTime)
        {
            // redo -- looks like it takes a while to load the basic code, throwing off timing
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
#if(_CollectDetailedTimingData)
            dwTimestamp = dwStartTime;
            SquareUBackend(nX.GetSize(), nX.GetValue(), nProduct.GetValue(), cWork.GetSpace(), dwTimestamp);
#else
            SquareUBackend(nX.GetSize(), nX.GetValue(), nProduct.GetValue(), cWork.GetSpace());
#endif
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        }
        ReportMeasuredComponentTimingData(eMultiplicationMeasured);
        printf("Square   two %i BYTE numbers:\t%I64u microseconds\n", nX.GetSize() * sizeof(DIGIT), dwStartTime);
    }
}

/*
16-bit DIGITS
Algorithm 5 for multiply size:    2000000x2000000 (BYTEs): 711426 microseconds
Algorithm 5 for square size:      2000000x2000000 (BYTEs): 567577 microseconds
Algorithm 4 for multiply size:    2000000x2000000 (BYTEs): 2405780 microseconds
Algorithm 4 for square size:      2000000x2000000 (BYTEs): 2030463 microseconds
Algorithm 3 for multiply size:    2000000x2000000 (BYTEs): 3123851 microseconds
Algorithm 3 for square size:      2000000x2000000 (BYTEs): 2391142 microseconds
Algorithm 2 for multiply size:    2000000x2000000 (BYTEs): 6244673 microseconds
Algorithm 2 for square size:      2000000x2000000 (BYTEs): 5104703 microseconds
Algorithm 1 for multiply size:    2000000x2000000 (BYTEs): 16628669 microseconds
Algorithm 1 for square size:      2000000x2000000 (BYTEs): 16451480 microseconds
Basic multiply for multiply size: 2000000x2000000 (BYTEs): 586763073 microseconds
Mult oracle for multiply size:    2000000x2000000 (BYTEs): 1184487932 microseconds
Algorithm 5 for multiply size:    4000000x4000000 (BYTEs): 1480700 microseconds
Algorithm 5 for square size:      4000000x4000000 (BYTEs): 1087361 microseconds
Algorithm 4 for multiply size:    4000000x4000000 (BYTEs): 7004757 microseconds
Algorithm 4 for square size:      4000000x4000000 (BYTEs): 5748723 microseconds
Algorithm 3 for multiply size:    4000000x4000000 (BYTEs): 8052703 microseconds
Algorithm 3 for square size:      4000000x4000000 (BYTEs): 5964921 microseconds
Algorithm 2 for multiply size:    4000000x4000000 (BYTEs): 16452479 microseconds
Algorithm 2 for square size:      4000000x4000000 (BYTEs): 12587456 microseconds
Algorithm 1 for multiply size:    4000000x4000000 (BYTEs): 49021224 microseconds
Algorithm 1 for square size:      4000000x4000000 (BYTEs): 48458853 microseconds
Basic multiply for multiply size: 4000000x4000000 (BYTEs): 2333501118 microseconds
Mult oracle for multiply size:    4000000x4000000 (BYTEs): 4733772971 microseconds
Algorithm 5 for multiply size:    8000000x8000000 (BYTEs): 3759544 microseconds
Algorithm 5 for square size:      8000000x8000000 (BYTEs): 2897931 microseconds
Algorithm 4 for multiply size:    8000000x8000000 (BYTEs): 15560860 microseconds
Algorithm 4 for square size:      8000000x8000000 (BYTEs): 13215657 microseconds
Algorithm 3 for multiply size:    8000000x8000000 (BYTEs): 21868603 microseconds
Algorithm 3 for square size:      8000000x8000000 (BYTEs): 16522508 microseconds
Algorithm 2 for multiply size:    8000000x8000000 (BYTEs): 41133476 microseconds
Algorithm 2 for square size:      8000000x8000000 (BYTEs): 35621575 microseconds
Algorithm 1 for multiply size:    8000000x8000000 (BYTEs): 146502512 microseconds
Algorithm 1 for square size:      8000000x8000000 (BYTEs): 146791955 microseconds
Algorithm 5 for multiply size:    16000000x16000000 (BYTEs): 7650763 microseconds
Algorithm 5 for square size:      16000000x16000000 (BYTEs): 6126312 microseconds
Algorithm 4 for multiply size:    16000000x16000000 (BYTEs): 38803187 microseconds
Algorithm 4 for square size:      16000000x16000000 (BYTEs): 34058976 microseconds
Algorithm 3 for multiply size:    16000000x16000000 (BYTEs): 56187349 microseconds
Algorithm 3 for square size:      16000000x16000000 (BYTEs): 41419414 microseconds
Algorithm 2 for multiply size:    16000000x16000000 (BYTEs): 121587471 microseconds
Algorithm 2 for square size:      16000000x16000000 (BYTEs): 93551154 microseconds
Algorithm 1 for multiply size:    16000000x16000000 (BYTEs): 439361891 microseconds
Algorithm 1 for square size:      16000000x16000000 (BYTEs): 440901548 microseconds
Algorithm 5 for multiply size:    32000000x32000000 (BYTEs): 19250783 microseconds
Algorithm 5 for square size:      32000000x32000000 (BYTEs): 14835864 microseconds
Algorithm 4 for multiply size:    32000000x32000000 (BYTEs): 102855496 microseconds
Algorithm 4 for square size:      32000000x32000000 (BYTEs): 85533055 microseconds
Algorithm 3 for multiply size:    32000000x32000000 (BYTEs): 150729887 microseconds
Algorithm 3 for square size:      32000000x32000000 (BYTEs): 116211074 microseconds
Algorithm 2 for multiply size:    32000000x32000000 (BYTEs): 323009600 microseconds
Algorithm 2 for square size:      32000000x32000000 (BYTEs): 240745277 microseconds
Algorithm 1 for multiply size:    32000000x32000000 (BYTEs): 1325302074 microseconds
Algorithm 1 for square size:      32000000x32000000 (BYTEs): 1341245239 microseconds
Algorithm 5 for multiply size:    64000000x64000000 (BYTEs): 39422957 microseconds
Algorithm 5 for square size:      64000000x64000000 (BYTEs): 29880672 microseconds
Algorithm 4 for multiply size:    64000000x64000000 (BYTEs): 256808964 microseconds
Algorithm 4 for square size:      64000000x64000000 (BYTEs): 221077435 microseconds
Algorithm 3 for multiply size:    64000000x64000000 (BYTEs): 399039650 microseconds
Algorithm 3 for square size:      64000000x64000000 (BYTEs): 291925959 microseconds
Algorithm 2 for multiply size:    64000000x64000000 (BYTEs): 940593331 microseconds
Algorithm 2 for square size:      64000000x64000000 (BYTEs): 810355434 microseconds
Algorithm 1 for multiply size:    64000000x64000000 (BYTEs): 3960476827 microseconds
Algorithm 1 for square size:      64000000x64000000 (BYTEs): 3972635554 microseconds
Algorithm 5 for multiply size:    128000000x128000000 (BYTEs): 100057901 microseconds
Algorithm 5 for square size:      128000000x128000000 (BYTEs): 79936857 microseconds
Algorithm 4 for multiply size:    128000000x128000000 (BYTEs): 561760676 microseconds
Algorithm 4 for square size:      128000000x128000000 (BYTEs): 453281693 microseconds
Algorithm 3 for multiply size:    128000000x128000000 (BYTEs): 1079992888 microseconds
Algorithm 3 for square size:      128000000x128000000 (BYTEs): 1025812142 microseconds
Algorithm 2 for multiply size:    128000000x128000000 (BYTEs): 2914363976 microseconds
Algorithm 2 for square size:      128000000x128000000 (BYTEs): 2409936165 microseconds
Algorithm 1 for multiply size:    128000000x128000000 (BYTEs): 12600325964 microseconds
Algorithm 1 for square size:      128000000x128000000 (BYTEs): 13081911353 microseconds
32-bit DIGITs
Algorithm 6 for multiply size:    2000000x2000000 (BYTEs): 266725 microseconds
Algorithm 6 for square size:      2000000x2000000 (BYTEs): 204069 microseconds
Algorithm 5 for multiply size:    2000000x2000000 (BYTEs): 765868 microseconds
Algorithm 5 for square size:      2000000x2000000 (BYTEs): 736236 microseconds
Algorithm 4 for multiply size:    2000000x2000000 (BYTEs): 759336 microseconds
Algorithm 4 for square size:      2000000x2000000 (BYTEs): 712351 microseconds
Algorithm 3 for multiply size:    2000000x2000000 (BYTEs): 947814 microseconds
Algorithm 3 for square size:      2000000x2000000 (BYTEs): 931801 microseconds
Algorithm 2 for multiply size:    2000000x2000000 (BYTEs): 1798813 microseconds
Algorithm 2 for square size:      2000000x2000000 (BYTEs): 1563469 microseconds
Algorithm 1 for multiply size:    2000000x2000000 (BYTEs): 4296739 microseconds
Algorithm 1 for square size:      2000000x2000000 (BYTEs): 4328059 microseconds
Basic multiply for multiply size: 2000000x2000000 (BYTEs): 150200065 microseconds
Mult oracle for multiply size:    2000000x2000000 (BYTEs): 302511895 microseconds
Algorithm 6 for multiply size:    4000000x4000000 (BYTEs): 544087 microseconds
Algorithm 6 for square size:      4000000x4000000 (BYTEs): 430137 microseconds
Algorithm 5 for multiply size:    4000000x4000000 (BYTEs): 1938615 microseconds
Algorithm 5 for square size:      4000000x4000000 (BYTEs): 1792500 microseconds
Algorithm 4 for multiply size:    4000000x4000000 (BYTEs): 1916522 microseconds
Algorithm 4 for square size:      4000000x4000000 (BYTEs): 1738891 microseconds
Algorithm 3 for multiply size:    4000000x4000000 (BYTEs): 2583597 microseconds
Algorithm 3 for square size:      4000000x4000000 (BYTEs): 2432837 microseconds
Algorithm 2 for multiply size:    4000000x4000000 (BYTEs): 4580113 microseconds
Algorithm 2 for square size:      4000000x4000000 (BYTEs): 4147781 microseconds
Algorithm 1 for multiply size:    4000000x4000000 (BYTEs): 12848516 microseconds
Algorithm 1 for square size:      4000000x4000000 (BYTEs): 12830645 microseconds
Basic multiply for multiply size: 4000000x4000000 (BYTEs): 589172851 microseconds
Mult oracle for multiply size:    4000000x4000000 (BYTEs): 1208085110 microseconds
Algorithm 6 for multiply size:    8000000x8000000 (BYTEs): 1236293 microseconds
Algorithm 6 for square size:      8000000x8000000 (BYTEs): 1068859 microseconds
Algorithm 5 for multiply size:    8000000x8000000 (BYTEs): 4526428 microseconds
Algorithm 5 for square size:      8000000x8000000 (BYTEs): 4122767 microseconds
Algorithm 4 for multiply size:    8000000x8000000 (BYTEs): 4934007 microseconds
Algorithm 4 for square size:      8000000x8000000 (BYTEs): 4691675 microseconds
Algorithm 3 for multiply size:    8000000x8000000 (BYTEs): 6574545 microseconds
Algorithm 3 for square size:      8000000x8000000 (BYTEs): 6641130 microseconds
Algorithm 2 for multiply size:    8000000x8000000 (BYTEs): 12847225 microseconds
Algorithm 2 for square size:      8000000x8000000 (BYTEs): 12243742 microseconds
Algorithm 1 for multiply size:    8000000x8000000 (BYTEs): 37617208 microseconds
Algorithm 1 for square size:      8000000x8000000 (BYTEs): 37827458 microseconds
Algorithm 6 for multiply size:    16000000x16000000 (BYTEs): 2522197 microseconds
Algorithm 6 for square size:      16000000x16000000 (BYTEs): 2193480 microseconds
Algorithm 5 for multiply size:    16000000x16000000 (BYTEs): 11404755 microseconds
Algorithm 5 for square size:      16000000x16000000 (BYTEs): 10851707 microseconds
Algorithm 4 for multiply size:    16000000x16000000 (BYTEs): 13299954 microseconds
Algorithm 4 for square size:      16000000x16000000 (BYTEs): 11588511 microseconds
Algorithm 3 for multiply size:    16000000x16000000 (BYTEs): 18007043 microseconds
Algorithm 3 for square size:      16000000x16000000 (BYTEs): 16508574 microseconds
Algorithm 2 for multiply size:    16000000x16000000 (BYTEs): 35620968 microseconds
Algorithm 2 for square size:      16000000x16000000 (BYTEs): 32246178 microseconds
Algorithm 1 for multiply size:    16000000x16000000 (BYTEs): 113601133 microseconds
Algorithm 1 for square size:      16000000x16000000 (BYTEs): 113491818 microseconds
Algorithm 6 for multiply size:    32000000x32000000 (BYTEs): 6472550 microseconds
Algorithm 6 for square size:      32000000x32000000 (BYTEs): 5306876 microseconds
Algorithm 5 for multiply size:    32000000x32000000 (BYTEs): 30828063 microseconds
Algorithm 5 for square size:      32000000x32000000 (BYTEs): 26753785 microseconds
Algorithm 4 for multiply size:    32000000x32000000 (BYTEs): 33093007 microseconds
Algorithm 4 for square size:      32000000x32000000 (BYTEs): 31802382 microseconds
Algorithm 3 for multiply size:    32000000x32000000 (BYTEs): 46668693 microseconds
Algorithm 3 for square size:      32000000x32000000 (BYTEs): 44014242 microseconds
Algorithm 2 for multiply size:    32000000x32000000 (BYTEs): 99289893 microseconds
Algorithm 2 for square size:      32000000x32000000 (BYTEs): 97050687 microseconds
Algorithm 1 for multiply size:    32000000x32000000 (BYTEs): 360479144 microseconds
Algorithm 1 for square size:      32000000x32000000 (BYTEs): 352248337 microseconds
Algorithm 6 for multiply size:    64000000x64000000 (BYTEs): 13030486 microseconds
Algorithm 6 for square size:      64000000x64000000 (BYTEs): 10454069 microseconds
Algorithm 5 for multiply size:    64000000x64000000 (BYTEs): 73365201 microseconds
Algorithm 5 for square size:      64000000x64000000 (BYTEs): 63837360 microseconds
Algorithm 4 for multiply size:    64000000x64000000 (BYTEs): 90409548 microseconds
Algorithm 4 for square size:      64000000x64000000 (BYTEs): 88192744 microseconds
Algorithm 3 for multiply size:    64000000x64000000 (BYTEs): 138617167 microseconds
Algorithm 3 for square size:      64000000x64000000 (BYTEs): 127796186 microseconds
Algorithm 2 for multiply size:    64000000x64000000 (BYTEs): 279991628 microseconds
Algorithm 2 for square size:      64000000x64000000 (BYTEs): 264020416 microseconds
Algorithm 1 for multiply size:    64000000x64000000 (BYTEs): 1083048443 microseconds
Algorithm 1 for square size:      64000000x64000000 (BYTEs): 1300101526 microseconds
Algorithm 6 for multiply size:    128000000x128000000 (BYTEs): 40685548 microseconds
Algorithm 6 for square size:      128000000x128000000 (BYTEs): 37907852 microseconds
Algorithm 5 for multiply size:    128000000x128000000 (BYTEs): 254175569 microseconds
Algorithm 5 for square size:      128000000x128000000 (BYTEs): 236403283 microseconds
Algorithm 4 for multiply size:    128000000x128000000 (BYTEs): 314730173 microseconds
Algorithm 4 for square size:      128000000x128000000 (BYTEs): 287644114 microseconds
Algorithm 3 for multiply size:    128000000x128000000 (BYTEs): 402206838 microseconds
Algorithm 3 for square size:      128000000x128000000 (BYTEs): 315862454 microseconds
Algorithm 2 for multiply size:    128000000x128000000 (BYTEs): 753919175 microseconds
Algorithm 2 for square size:      128000000x128000000 (BYTEs): 690383404 microseconds
Algorithm 1 for multiply size:    128000000x128000000 (BYTEs): 3080038231 microseconds
Algorithm 1 for square size:      128000000x128000000 (BYTEs): 3079717233 microseconds
full breakdown, 32 bit DIGITs
FFT multiply for multiply size:    2000000x2000000 (BYTEs): 279015 microseconds
1 calls to multiply
  221157 calls to Basic multiply:
    Basic multiply time:        123434 microseconds (0.558128 average)
  73710 calls to 3 by 2 multiply:
    Construct subproblems time: 5236 microseconds (0.071035 average)
    Combine subproblems time:   12621 microseconds (0.171225 average)
  8193 calls to 9 by 5 multiply:
    Construct subproblems time: 10472 microseconds (1.278164 average)
    Combine subproblems time:   29730 microseconds (3.628707 average)
  1 calls to FFT multiply:
    Construct subproblems time: 65199 microseconds (65199.000000 average)
    Combine subproblems time:   32322 microseconds (32322.000000 average)
Total multiply time: 279014 microseconds (279014.000000 average)

FFT multiply for square size:      2000000x2000000 (BYTEs): 253914 microseconds
1 calls to multiply
  221166 calls to Basic multiply:
    Basic multiply time:        133940 microseconds (0.605608 average)
  73719 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   6358 microseconds (0.086246 average)
  8192 calls to 9 by 5 multiply:
    Construct subproblems time: 7438 microseconds (0.907959 average)
    Combine subproblems time:   32659 microseconds (3.986694 average)
  1 calls to FFT multiply:
    Construct subproblems time: 35761 microseconds (35761.000000 average)
    Combine subproblems time:   37757 microseconds (37757.000000 average)
Total multiply time: 253913 microseconds (253913.000000 average)

2n by n multiply for multiply size:    2000000x2000000 (BYTEs): 851676 microseconds
1 calls to multiply
  531441 calls to Basic multiply:
    Basic multiply time:        457028 microseconds (0.859979 average)
  66430 calls to 9 by 5 multiply:
    Construct subproblems time: 82498 microseconds (1.241879 average)
    Combine subproblems time:   312149 microseconds (4.698916 average)
Total multiply time: 851675 microseconds (851675.000000 average)

2n by n multiply for square size:      2000000x2000000 (BYTEs): 751808 microseconds
1 calls to multiply
  531441 calls to Basic multiply:
    Basic multiply time:        424572 microseconds (0.798907 average)
  66430 calls to 9 by 5 multiply:
    Construct subproblems time: 40098 microseconds (0.603613 average)
    Combine subproblems time:   287138 microseconds (4.322414 average)
Total multiply time: 751808 microseconds (751808.000000 average)

9 by 5 multiply for multiply size:    2000000x2000000 (BYTEs): 750701 microseconds
1 calls to multiply
  531441 calls to Basic multiply:
    Basic multiply time:        405728 microseconds (0.763449 average)
  66430 calls to 9 by 5 multiply:
    Construct subproblems time: 72597 microseconds (1.092835 average)
    Combine subproblems time:   272376 microseconds (4.100196 average)
Total multiply time: 750701 microseconds (750701.000000 average)

9 by 5 multiply for square size:      2000000x2000000 (BYTEs): 727223 microseconds
1 calls to multiply
  531441 calls to Basic multiply:
    Basic multiply time:        412479 microseconds (0.776152 average)
  66430 calls to 9 by 5 multiply:
    Construct subproblems time: 39078 microseconds (0.588258 average)
    Combine subproblems time:   275666 microseconds (4.149722 average)
Total multiply time: 727223 microseconds (727223.000000 average)

7 by 4 multiply for multiply size:    2000000x2000000 (BYTEs): 968733 microseconds
1 calls to multiply
  823543 calls to Basic multiply:
    Basic multiply time:        587209 microseconds (0.713028 average)
  137257 calls to 7 by 4 multiply:
    Construct subproblems time: 77003 microseconds (0.561013 average)
    Combine subproblems time:   300479 microseconds (2.189171 average)
Total multiply time: 968733 microseconds (968733.000000 average)

7 by 4 multiply for square size:      2000000x2000000 (BYTEs): 1037836 microseconds
1 calls to multiply
  823543 calls to Basic multiply:
    Basic multiply time:        650283 microseconds (0.789616 average)
  137257 calls to 7 by 4 multiply:
    Construct subproblems time: 45666 microseconds (0.332704 average)
    Combine subproblems time:   337491 microseconds (2.458825 average)
Total multiply time: 1037834 microseconds (1037834.000000 average)

5 by 3 multiply for multiply size:    2000000x2000000 (BYTEs): 1897821 microseconds
1 calls to multiply
  3482671 calls to Basic multiply:
    Basic multiply time:        1148605 microseconds (0.329806 average)
  1546023 calls to 3 by 2 multiply:
    Construct subproblems time: 100086 microseconds (0.064738 average)
    Combine subproblems time:   239633 microseconds (0.155000 average)
  97656 calls to 5 by 3 multiply:
    Construct subproblems time: 61499 microseconds (0.629751 average)
    Combine subproblems time:   347997 microseconds (3.563498 average)
Total multiply time: 1897820 microseconds (1897820.000000 average)

5 by 3 multiply for square size:      2000000x2000000 (BYTEs): 1669506 microseconds
1 calls to multiply
  3449717 calls to Basic multiply:
    Basic multiply time:        1135680 microseconds (0.329210 average)
  1529546 calls to 3 by 2 multiply:
    Construct subproblems time: 24241 microseconds (0.015848 average)
    Combine subproblems time:   133049 microseconds (0.086986 average)
  97656 calls to 5 by 3 multiply:
    Construct subproblems time: 32984 microseconds (0.337757 average)
    Combine subproblems time:   340774 microseconds (3.489535 average)
Total multiply time: 1669506 microseconds (1669506.000000 average)

3 by 2 multiply for multiply size:    2000000x2000000 (BYTEs): 4526684 microseconds
1 calls to multiply
  4782969 calls to Basic multiply:
    Basic multiply time:        3417342 microseconds (0.714481 average)
  2391484 calls to 3 by 2 multiply:
    Construct subproblems time: 261718 microseconds (0.109437 average)
    Combine subproblems time:   847623 microseconds (0.354434 average)
Total multiply time: 4526683 microseconds (4526683.000000 average)

3 by 2 multiply for square size:      2000000x2000000 (BYTEs): 4497674 microseconds
1 calls to multiply
  4782969 calls to Basic multiply:
    Basic multiply time:        3404323 microseconds (0.711759 average)
  2391484 calls to 3 by 2 multiply:
    Construct subproblems time: 256314 microseconds (0.107178 average)
    Combine subproblems time:   837037 microseconds (0.350007 average)
Total multiply time: 4497674 microseconds (4497674.000000 average)

Basic multiply for multiply size: 2000000x2000000 (BYTEs): 159750175 microseconds
1 calls to multiply
  1 calls to Basic multiply:
    Basic multiply time:        159750175 microseconds (159750176.000000 average)
Total multiply time: 159750175 microseconds (159750176.000000 average)

Mult oracle for multiply size:    2000000x2000000 (BYTEs): 306703273 microseconds

FFT multiply for multiply size:    4000000x4000000 (BYTEs): 623086 microseconds
1 calls to multiply
  442332 calls to Basic multiply:
    Basic multiply time:        275283 microseconds (0.622345 average)
  147438 calls to 3 by 2 multiply:
    Construct subproblems time: 11779 microseconds (0.079891 average)
    Combine subproblems time:   27513 microseconds (0.186607 average)
  16384 calls to 9 by 5 multiply:
    Construct subproblems time: 23147 microseconds (1.412781 average)
    Combine subproblems time:   65272 microseconds (3.983887 average)
  1 calls to FFT multiply:
    Construct subproblems time: 134079 microseconds (134079.000000 average)
    Combine subproblems time:   86012 microseconds (86012.000000 average)
Total multiply time: 623085 microseconds (623085.000000 average)

FFT multiply for square size:      4000000x4000000 (BYTEs): 459771 microseconds
1 calls to multiply
  442332 calls to Basic multiply:
    Basic multiply time:        238125 microseconds (0.538340 average)
  147438 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   11161 microseconds (0.075700 average)
  16384 calls to 9 by 5 multiply:
    Construct subproblems time: 12706 microseconds (0.775513 average)
    Combine subproblems time:   58078 microseconds (3.544800 average)
  1 calls to FFT multiply:
    Construct subproblems time: 66876 microseconds (66876.000000 average)
    Combine subproblems time:   72824 microseconds (72824.000000 average)
Total multiply time: 459770 microseconds (459770.000000 average)

2n by n multiply for multiply size:    4000000x4000000 (BYTEs): 2020507 microseconds
1 calls to multiply
  1594323 calls to Basic multiply:
    Basic multiply time:        1192068 microseconds (0.747695 average)
  531441 calls to 3 by 2 multiply:
    Construct subproblems time: 39958 microseconds (0.075188 average)
    Combine subproblems time:   105755 microseconds (0.198997 average)
  66430 calls to 9 by 5 multiply:
    Construct subproblems time: 140855 microseconds (2.120352 average)
    Combine subproblems time:   541869 microseconds (8.156992 average)
Total multiply time: 2020505 microseconds (2020505.000000 average)

2n by n multiply for square size:      4000000x4000000 (BYTEs): 1836653 microseconds
1 calls to multiply
  1594323 calls to Basic multiply:
    Basic multiply time:        1170902 microseconds (0.734420 average)
  531441 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   44467 microseconds (0.083673 average)
  66430 calls to 9 by 5 multiply:
    Construct subproblems time: 72410 microseconds (1.090020 average)
    Combine subproblems time:   548874 microseconds (8.262442 average)
Total multiply time: 1836653 microseconds (1836653.000000 average)

9 by 5 multiply for multiply size:    4000000x4000000 (BYTEs): 2010497 microseconds
1 calls to multiply
  1594323 calls to Basic multiply:
    Basic multiply time:        1184220 microseconds (0.742773 average)
  531441 calls to 3 by 2 multiply:
    Construct subproblems time: 39975 microseconds (0.075220 average)
    Combine subproblems time:   105042 microseconds (0.197655 average)
  66430 calls to 9 by 5 multiply:
    Construct subproblems time: 140485 microseconds (2.114783 average)
    Combine subproblems time:   540774 microseconds (8.140509 average)
Total multiply time: 2010496 microseconds (2010496.000000 average)

9 by 5 multiply for square size:      4000000x4000000 (BYTEs): 1847956 microseconds
1 calls to multiply
  1594323 calls to Basic multiply:
    Basic multiply time:        1175480 microseconds (0.737291 average)
  531441 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   44675 microseconds (0.084064 average)
  66430 calls to 9 by 5 multiply:
    Construct subproblems time: 73332 microseconds (1.103899 average)
    Combine subproblems time:   554468 microseconds (8.346651 average)
Total multiply time: 1847955 microseconds (1847955.000000 average)

7 by 4 multiply for multiply size:    4000000x4000000 (BYTEs): 2767619 microseconds
1 calls to multiply
  2470629 calls to Basic multiply:
    Basic multiply time:        1782744 microseconds (0.721575 average)
  823543 calls to 3 by 2 multiply:
    Construct subproblems time: 60507 microseconds (0.073472 average)
    Combine subproblems time:   160694 microseconds (0.195125 average)
  137257 calls to 7 by 4 multiply:
    Construct subproblems time: 150442 microseconds (1.096061 average)
    Combine subproblems time:   609067 microseconds (4.437420 average)
Total multiply time: 2767619 microseconds (2767619.000000 average)

7 by 4 multiply for square size:      4000000x4000000 (BYTEs): 2497627 microseconds
1 calls to multiply
  2470629 calls to Basic multiply:
    Basic multiply time:        1740899 microseconds (0.704638 average)
  823543 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   67888 microseconds (0.082434 average)
  137257 calls to 7 by 4 multiply:
    Construct subproblems time: 76413 microseconds (0.556715 average)
    Combine subproblems time:   608357 microseconds (4.432248 average)
Total multiply time: 2497627 microseconds (2497627.000000 average)

5 by 3 multiply for multiply size:    4000000x4000000 (BYTEs): 4959347 microseconds
1 calls to multiply
  5859375 calls to Basic multiply:
    Basic multiply time:        3086363 microseconds (0.526739 average)
  1953125 calls to 3 by 2 multiply:
    Construct subproblems time: 132458 microseconds (0.067818 average)
    Combine subproblems time:   328187 microseconds (0.168032 average)
  488281 calls to 5 by 3 multiply:
    Construct subproblems time: 218003 microseconds (0.446470 average)
    Combine subproblems time:   1194335 microseconds (2.445999 average)
Total multiply time: 4959346 microseconds (4959346.000000 average)

5 by 3 multiply for square size:      4000000x4000000 (BYTEs): 4631867 microseconds
1 calls to multiply
  5859375 calls to Basic multiply:
    Basic multiply time:        3120909 microseconds (0.532635 average)
  1953125 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   151407 microseconds (0.077520 average)
  488281 calls to 5 by 3 multiply:
    Construct subproblems time: 124465 microseconds (0.254904 average)
    Combine subproblems time:   1219912 microseconds (2.498381 average)
Total multiply time: 4631866 microseconds (4631866.000000 average)

3 by 2 multiply for multiply size:    4000000x4000000 (BYTEs): 13908457 microseconds
1 calls to multiply
  14348907 calls to Basic multiply:
    Basic multiply time:        10490900 microseconds (0.731129 average)
  7174453 calls to 3 by 2 multiply:
    Construct subproblems time: 806511 microseconds (0.112414 average)
    Combine subproblems time:   2611046 microseconds (0.363937 average)
Total multiply time: 13908457 microseconds (13908457.000000 average)

3 by 2 multiply for square size:      4000000x4000000 (BYTEs): 14154999 microseconds
1 calls to multiply
  14348907 calls to Basic multiply:
    Basic multiply time:        10707982 microseconds (0.746258 average)
  7174453 calls to 3 by 2 multiply:
    Construct subproblems time: 820118 microseconds (0.114311 average)
    Combine subproblems time:   2626899 microseconds (0.366146 average)
Total multiply time: 14154999 microseconds (14154999.000000 average)

Basic multiply for multiply size: 4000000x4000000 (BYTEs): 605137364 microseconds
1 calls to multiply
  1 calls to Basic multiply:
    Basic multiply time:        605137363 microseconds (605137344.000000 average)
Total multiply time: 605137363 microseconds (605137344.000000 average)

Mult oracle for multiply size:    4000000x4000000 (BYTEs): 1271859277 microseconds

FFT multiply for multiply size:    8000000x8000000 (BYTEs): 1820532 microseconds
1 calls to multiply
  1032156 calls to Basic multiply:
    Basic multiply time:        816304 microseconds (0.790873 average)
  9 calls to 3 by 2 multiply:
    Construct subproblems time: 1 microseconds (0.111111 average)
    Combine subproblems time:   1 microseconds (0.111111 average)
  147447 calls to 7 by 4 multiply:
    Construct subproblems time: 58464 microseconds (0.396509 average)
    Combine subproblems time:   209420 microseconds (1.420307 average)
  16384 calls to 9 by 5 multiply:
    Construct subproblems time: 55997 microseconds (3.417786 average)
    Combine subproblems time:   154920 microseconds (9.455566 average)
  1 calls to FFT multiply:
    Construct subproblems time: 284072 microseconds (284072.000000 average)
    Combine subproblems time:   235555 microseconds (235555.000000 average)
Total multiply time: 1820531 microseconds (1820531.000000 average)

FFT multiply for square size:      8000000x8000000 (BYTEs): 1382114 microseconds
1 calls to multiply
  1032156 calls to Basic multiply:
    Basic multiply time:        658689 microseconds (0.638168 average)
  9 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   0 microseconds (0.000000 average)
  147447 calls to 7 by 4 multiply:
    Construct subproblems time: 26941 microseconds (0.182717 average)
    Combine subproblems time:   170701 microseconds (1.157711 average)
  16384 calls to 9 by 5 multiply:
    Construct subproblems time: 28969 microseconds (1.768127 average)
    Combine subproblems time:   129377 microseconds (7.896545 average)
  1 calls to FFT multiply:
    Construct subproblems time: 203591 microseconds (203591.000000 average)
    Combine subproblems time:   158726 microseconds (158726.000000 average)
Total multiply time: 1382114 microseconds (1382114.000000 average)

2n by n multiply for multiply size:    8000000x8000000 (BYTEs): 5603444 microseconds
12003 calls to multiply
  3378406 calls to Basic multiply:
    Basic multiply time:        3235702 microseconds (0.957760 average)
  1121931 calls to 3 by 2 multiply:
    Construct subproblems time: 96344 microseconds (0.085873 average)
    Combine subproblems time:   248745 microseconds (0.221712 average)
  140239 calls to 9 by 5 multiply:
    Construct subproblems time: 328312 microseconds (2.341089 average)
    Combine subproblems time:   1264689 microseconds (9.018098 average)
  1 calls to 2n by n multiply:
    Construct subproblems time: 106923 microseconds (106923.000000 average)
    Combine subproblems time:   709179 microseconds (709179.000000 average)
Total multiply time: 5603872 microseconds (466.872620 average)

2n by n multiply for square size:      8000000x8000000 (BYTEs): 4685290 microseconds
1 calls to multiply
  3366260 calls to Basic multiply:
    Basic multiply time:        2852572 microseconds (0.847401 average)
  1121931 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   97085 microseconds (0.086534 average)
  140239 calls to 9 by 5 multiply:
    Construct subproblems time: 153170 microseconds (1.092207 average)
    Combine subproblems time:   1159326 microseconds (8.266788 average)
  1 calls to 2n by n multiply:
    Construct subproblems time: 45416 microseconds (45416.000000 average)
    Combine subproblems time:   700947 microseconds (700947.000000 average)
Total multiply time: 4685290 microseconds (4685290.000000 average)

9 by 5 multiply for multiply size:    8000000x8000000 (BYTEs): 5656424 microseconds
1 calls to multiply
  4782969 calls to Basic multiply:
    Basic multiply time:        2888002 microseconds (0.603809 average)
  597871 calls to 9 by 5 multiply:
    Construct subproblems time: 585454 microseconds (0.979231 average)
    Combine subproblems time:   2182967 microseconds (3.651234 average)
Total multiply time: 5656423 microseconds (5656423.000000 average)

9 by 5 multiply for square size:      8000000x8000000 (BYTEs): 5030270 microseconds
1 calls to multiply
  4782969 calls to Basic multiply:
    Basic multiply time:        2695234 microseconds (0.563506 average)
  597871 calls to 9 by 5 multiply:
    Construct subproblems time: 288146 microseconds (0.481953 average)
    Combine subproblems time:   2046889 microseconds (3.423630 average)
Total multiply time: 5030269 microseconds (5030269.000000 average)

7 by 4 multiply for multiply size:    8000000x8000000 (BYTEs): 7119434 microseconds
1 calls to multiply
  5764801 calls to Basic multiply:
    Basic multiply time:        4312281 microseconds (0.748036 average)
  960800 calls to 7 by 4 multiply:
    Construct subproblems time: 559231 microseconds (0.582047 average)
    Combine subproblems time:   2218474 microseconds (2.308986 average)
Total multiply time: 7119433 microseconds (7119433.000000 average)

7 by 4 multiply for square size:      8000000x8000000 (BYTEs): 6872003 microseconds
1 calls to multiply
  5764801 calls to Basic multiply:
    Basic multiply time:        4312290 microseconds (0.748038 average)
  960800 calls to 7 by 4 multiply:
    Construct subproblems time: 296150 microseconds (0.308233 average)
    Combine subproblems time:   2233477 microseconds (2.324601 average)
Total multiply time: 6872001 microseconds (6872001.000000 average)

5 by 3 multiply for multiply size:    8000000x8000000 (BYTEs): 13849201 microseconds
1 calls to multiply
  9765625 calls to Basic multiply:
    Basic multiply time:        8860309 microseconds (0.907296 average)
  2441406 calls to 5 by 3 multiply:
    Construct subproblems time: 802408 microseconds (0.328666 average)
    Combine subproblems time:   4186484 microseconds (1.714784 average)
Total multiply time: 13849201 microseconds (13849201.000000 average)

5 by 3 multiply for square size:      8000000x8000000 (BYTEs): 13884678 microseconds
1 calls to multiply
  9765625 calls to Basic multiply:
    Basic multiply time:        9126718 microseconds (0.934576 average)
  2441406 calls to 5 by 3 multiply:
    Construct subproblems time: 460727 microseconds (0.188714 average)
    Combine subproblems time:   4218331 microseconds (1.727829 average)
Total multiply time: 13884677 microseconds (13884677.000000 average)

3 by 2 multiply for multiply size:    8000000x8000000 (BYTEs): 42791402 microseconds
1 calls to multiply
  43046721 calls to Basic multiply:
    Basic multiply time:        32297167 microseconds (0.750282 average)
  21523360 calls to 3 by 2 multiply:
    Construct subproblems time: 2477291 microseconds (0.115098 average)
    Combine subproblems time:   8016944 microseconds (0.372476 average)
Total multiply time: 42791402 microseconds (42791400.000000 average)

3 by 2 multiply for square size:      8000000x8000000 (BYTEs): 41785091 microseconds
1 calls to multiply
  43046721 calls to Basic multiply:
    Basic multiply time:        31559458 microseconds (0.733144 average)
  21523360 calls to 3 by 2 multiply:
    Construct subproblems time: 2411064 microseconds (0.112021 average)
    Combine subproblems time:   7814569 microseconds (0.363074 average)
Total multiply time: 41785091 microseconds (41785092.000000 average)

FFT multiply for multiply size:    16000000x16000000 (BYTEs): 2695645 microseconds
1 calls to multiply
  2064312 calls to Basic multiply:
    Basic multiply time:        1128716 microseconds (0.546776 average)
  18 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   2 microseconds (0.111111 average)
  294894 calls to 7 by 4 multiply:
    Construct subproblems time: 78594 microseconds (0.266516 average)
    Combine subproblems time:   289576 microseconds (0.981966 average)
  32768 calls to 9 by 5 multiply:
    Construct subproblems time: 83376 microseconds (2.544434 average)
    Combine subproblems time:   222406 microseconds (6.787292 average)
  1 calls to FFT multiply:
    Construct subproblems time: 586001 microseconds (586001.000000 average)
    Combine subproblems time:   298168 microseconds (298168.000000 average)
Total multiply time: 2695644 microseconds (2695644.000000 average)

FFT multiply for square size:      16000000x16000000 (BYTEs): 2353938 microseconds
1 calls to multiply
  2064312 calls to Basic multiply:
    Basic multiply time:        1145357 microseconds (0.554837 average)
  18 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   3 microseconds (0.166667 average)
  294894 calls to 7 by 4 multiply:
    Construct subproblems time: 45390 microseconds (0.153920 average)
    Combine subproblems time:   294904 microseconds (1.000034 average)
  32768 calls to 9 by 5 multiply:
    Construct subproblems time: 51608 microseconds (1.574951 average)
    Combine subproblems time:   225997 microseconds (6.896881 average)
  1 calls to FFT multiply:
    Construct subproblems time: 276033 microseconds (276033.000000 average)
    Combine subproblems time:   305659 microseconds (305659.000000 average)
Total multiply time: 2353937 microseconds (2353937.000000 average)

2n by n multiply for multiply size:    16000000x16000000 (BYTEs): 12530343 microseconds
1 calls to multiply
  10097990 calls to Basic multiply:
    Basic multiply time:        6344805 microseconds (0.628324 average)
  1262170 calls to 9 by 5 multiply:
    Construct subproblems time: 1123979 microseconds (0.890513 average)
    Combine subproblems time:   4213595 microseconds (3.338374 average)
  1 calls to 2n by n multiply:
    Construct subproblems time: 195520 microseconds (195520.000000 average)
    Combine subproblems time:   1390563 microseconds (1390563.000000 average)
Total multiply time: 12530342 microseconds (12530342.000000 average)

2n by n multiply for square size:      16000000x16000000 (BYTEs): 12317743 microseconds
1 calls to multiply
  10097846 calls to Basic multiply:
    Basic multiply time:        6479528 microseconds (0.641674 average)
  1262170 calls to 9 by 5 multiply:
    Construct subproblems time: 614160 microseconds (0.486591 average)
    Combine subproblems time:   4324350 microseconds (3.426123 average)
  1 calls to 2n by n multiply:
    Construct subproblems time: 99710 microseconds (99710.000000 average)
    Combine subproblems time:   1497887 microseconds (1497887.000000 average)
Total multiply time: 12317743 microseconds (12317743.000000 average)

9 by 5 multiply for multiply size:    16000000x16000000 (BYTEs): 14022381 microseconds
1 calls to multiply
  14348907 calls to Basic multiply:
    Basic multiply time:        7785620 microseconds (0.542593 average)
  4782969 calls to 3 by 2 multiply:
    Construct subproblems time: 331984 microseconds (0.069410 average)
    Combine subproblems time:   806052 microseconds (0.168525 average)
  597871 calls to 9 by 5 multiply:
    Construct subproblems time: 1055333 microseconds (1.765152 average)
    Combine subproblems time:   4043391 microseconds (6.762982 average)
Total multiply time: 14022380 microseconds (14022380.000000 average)

9 by 5 multiply for square size:      16000000x16000000 (BYTEs): 12890991 microseconds
1 calls to multiply
  14348907 calls to Basic multiply:
    Basic multiply time:        7805282 microseconds (0.543964 average)
  4782969 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   364694 microseconds (0.076248 average)
  597871 calls to 9 by 5 multiply:
    Construct subproblems time: 552890 microseconds (0.924765 average)
    Combine subproblems time:   4168125 microseconds (6.971612 average)
Total multiply time: 12890991 microseconds (12890991.000000 average)

7 by 4 multiply for multiply size:    16000000x16000000 (BYTEs): 19422967 microseconds
1 calls to multiply
  17294403 calls to Basic multiply:
    Basic multiply time:        12507592 microseconds (0.723216 average)
  5764801 calls to 3 by 2 multiply:
    Construct subproblems time: 424040 microseconds (0.073557 average)
    Combine subproblems time:   1122041 microseconds (0.194637 average)
  960800 calls to 7 by 4 multiply:
    Construct subproblems time: 1039468 microseconds (1.081878 average)
    Combine subproblems time:   4300836 microseconds (4.476307 average)
Total multiply time: 19422966 microseconds (19422966.000000 average)

7 by 4 multiply for square size:      16000000x16000000 (BYTEs): 17697470 microseconds
1 calls to multiply
  17294403 calls to Basic multiply:
    Basic multiply time:        12302137 microseconds (0.711336 average)
  5764801 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   476926 microseconds (0.082731 average)
  960800 calls to 7 by 4 multiply:
    Construct subproblems time: 544434 microseconds (0.566647 average)
    Combine subproblems time:   4345458 microseconds (4.522750 average)
Total multiply time: 17697469 microseconds (17697468.000000 average)

5 by 3 multiply for multiply size:    16000000x16000000 (BYTEs): 38501231 microseconds
1 calls to multiply
  29296875 calls to Basic multiply:
    Basic multiply time:        26029798 microseconds (0.888484 average)
  9765625 calls to 3 by 2 multiply:
    Construct subproblems time: 782357 microseconds (0.080113 average)
    Combine subproblems time:   2118488 microseconds (0.216933 average)
  2441406 calls to 5 by 3 multiply:
    Construct subproblems time: 1456416 microseconds (0.596548 average)
    Combine subproblems time:   8114172 microseconds (3.323565 average)
Total multiply time: 38501231 microseconds (38501232.000000 average)

5 by 3 multiply for square size:      16000000x16000000 (BYTEs): 34875755 microseconds
1 calls to multiply
  29296875 calls to Basic multiply:
    Basic multiply time:        25249285 microseconds (0.861842 average)
  9765625 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   890064 microseconds (0.091143 average)
  2441406 calls to 5 by 3 multiply:
    Construct subproblems time: 774108 microseconds (0.317075 average)
    Combine subproblems time:   7889606 microseconds (3.231583 average)
Total multiply time: 34875755 microseconds (34875756.000000 average)

3 by 2 multiply for multiply size:    16000000x16000000 (BYTEs): 130439756 microseconds
1 calls to multiply
  129140163 calls to Basic multiply:
    Basic multiply time:        98528100 microseconds (0.762955 average)
  64570081 calls to 3 by 2 multiply:
    Construct subproblems time: 7587687 microseconds (0.117511 average)
    Combine subproblems time:   24323969 microseconds (0.376706 average)
Total multiply time: 130439756 microseconds (130439760.000000 average)

3 by 2 multiply for square size:      16000000x16000000 (BYTEs): 129572694 microseconds
1 calls to multiply
  129140163 calls to Basic multiply:
    Basic multiply time:        98030370 microseconds (0.759101 average)
  64570081 calls to 3 by 2 multiply:
    Construct subproblems time: 7473058 microseconds (0.115736 average)
    Combine subproblems time:   24069265 microseconds (0.372762 average)
Total multiply time: 129572693 microseconds (129572696.000000 average)

FFT multiply for multiply size:    32000000x32000000 (BYTEs): 7007455 microseconds
1 calls to multiply
  7962327 calls to Basic multiply:
    Basic multiply time:        3045479 microseconds (0.382486 average)
  2654046 calls to 3 by 2 multiply:
    Construct subproblems time: 171836 microseconds (0.064745 average)
    Combine subproblems time:   376123 microseconds (0.141717 average)
  27 calls to 7 by 4 multiply:
    Construct subproblems time: 10 microseconds (0.370370 average)
    Combine subproblems time:   24 microseconds (0.888889 average)
  327663 calls to 9 by 5 multiply:
    Construct subproblems time: 386288 microseconds (1.178919 average)
    Combine subproblems time:   1288519 microseconds (3.932452 average)
  1 calls to FFT multiply:
    Construct subproblems time: 1138033 microseconds (1138033.000000 average)
    Combine subproblems time:   601141 microseconds (601141.000000 average)
Total multiply time: 7007453 microseconds (7007453.000000 average)

FFT multiply for square size:      32000000x32000000 (BYTEs): 5718897 microseconds
1 calls to multiply
  7962444 calls to Basic multiply:
    Basic multiply time:        2922896 microseconds (0.367085 average)
  2654127 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   174866 microseconds (0.065885 average)
  9 calls to 7 by 4 multiply:
    Construct subproblems time: 13 microseconds (1.444444 average)
    Combine subproblems time:   8 microseconds (0.888889 average)
  327671 calls to 9 by 5 multiply:
    Construct subproblems time: 218636 microseconds (0.667242 average)
    Combine subproblems time:   1304161 microseconds (3.980093 average)
  1 calls to FFT multiply:
    Construct subproblems time: 541493 microseconds (541493.000000 average)
    Combine subproblems time:   556823 microseconds (556823.000000 average)
Total multiply time: 5718897 microseconds (5718897.000000 average)

2n by n multiply for multiply size:    32000000x32000000 (BYTEs): 34294226 microseconds
1 calls to multiply
  30292748 calls to Basic multiply:
    Basic multiply time:        18849443 microseconds (0.622243 average)
  10097379 calls to 3 by 2 multiply:
    Construct subproblems time: 747089 microseconds (0.073988 average)
    Combine subproblems time:   1782356 microseconds (0.176517 average)
  1262170 calls to 9 by 5 multiply:
    Construct subproblems time: 2299797 microseconds (1.822098 average)
    Combine subproblems time:   8831985 microseconds (6.997461 average)
  1 calls to 2n by n multiply:
    Construct subproblems time: 405418 microseconds (405418.000000 average)
    Combine subproblems time:   2948495 microseconds (2948495.000000 average)
Total multiply time: 34294226 microseconds (34294224.000000 average)

2n by n multiply for square size:      32000000x32000000 (BYTEs): 31663001 microseconds
1 calls to multiply
  30292604 calls to Basic multiply:
    Basic multiply time:        18715326 microseconds (0.617818 average)
  10097379 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   809371 microseconds (0.080157 average)
  1262170 calls to 9 by 5 multiply:
    Construct subproblems time: 1194330 microseconds (0.946251 average)
    Combine subproblems time:   9047160 microseconds (7.167941 average)
  1 calls to 2n by n multiply:
    Construct subproblems time: 193093 microseconds (193093.000000 average)
    Combine subproblems time:   3094523 microseconds (3094523.000000 average)
Total multiply time: 31663001 microseconds (31663000.000000 average)

9 by 5 multiply for multiply size:    32000000x32000000 (BYTEs): 37564063 microseconds
1 calls to multiply
  33480783 calls to Basic multiply:
    Basic multiply time:        20110642 microseconds (0.600662 average)
  4782969 calls to 7 by 4 multiply:
    Construct subproblems time: 1404596 microseconds (0.293666 average)
    Combine subproblems time:   5111639 microseconds (1.068717 average)
  597871 calls to 9 by 5 multiply:
    Construct subproblems time: 2247756 microseconds (3.759600 average)
    Combine subproblems time:   8540442 microseconds (14.284757 average)
Total multiply time: 37564062 microseconds (37564064.000000 average)

9 by 5 multiply for square size:      32000000x32000000 (BYTEs): 34695344 microseconds
1 calls to multiply
  33480783 calls to Basic multiply:
    Basic multiply time:        19365099 microseconds (0.578394 average)
  4782969 calls to 7 by 4 multiply:
    Construct subproblems time: 768032 microseconds (0.160576 average)
    Combine subproblems time:   4951584 microseconds (1.035253 average)
  597871 calls to 9 by 5 multiply:
    Construct subproblems time: 1116778 microseconds (1.867925 average)
    Combine subproblems time:   8343386 microseconds (13.955161 average)
Total multiply time: 34695343 microseconds (34695344.000000 average)

7 by 4 multiply for multiply size:    32000000x32000000 (BYTEs): 54082029 microseconds
1 calls to multiply
  40353607 calls to Basic multiply:
    Basic multiply time:        32778972 microseconds (0.812293 average)
  6725601 calls to 7 by 4 multiply:
    Construct subproblems time: 4237898 microseconds (0.630114 average)
    Combine subproblems time:   16849860 microseconds (2.505332 average)
Total multiply time: 54082028 microseconds (54082028.000000 average)

7 by 4 multiply for square size:      32000000x32000000 (BYTEs): 50147324 microseconds
1 calls to multiply
  40353607 calls to Basic multiply:
    Basic multiply time:        31379860 microseconds (0.777622 average)
  6725601 calls to 7 by 4 multiply:
    Construct subproblems time: 2181188 microseconds (0.324311 average)
    Combine subproblems time:   16370111 microseconds (2.434000 average)
Total multiply time: 50147323 microseconds (50147324.000000 average)

5 by 3 multiply for multiply size:    32000000x32000000 (BYTEs): 117102185 microseconds
1 calls to multiply
  146484375 calls to Basic multiply:
    Basic multiply time:        71168975 microseconds (0.485847 average)
  48828125 calls to 3 by 2 multiply:
    Construct subproblems time: 3451106 microseconds (0.070679 average)
    Combine subproblems time:   7992518 microseconds (0.163687 average)
  12207031 calls to 5 by 3 multiply:
    Construct subproblems time: 5394332 microseconds (0.441904 average)
    Combine subproblems time:   29095254 microseconds (2.383483 average)
Total multiply time: 117102185 microseconds (117102184.000000 average)

5 by 3 multiply for square size:      32000000x32000000 (BYTEs): 102603628 microseconds
1 calls to multiply
  146484375 calls to Basic multiply:
    Basic multiply time:        68012122 microseconds (0.464296 average)
  48828125 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   3574586 microseconds (0.073208 average)
  12207031 calls to 5 by 3 multiply:
    Construct subproblems time: 2861047 microseconds (0.234377 average)
    Combine subproblems time:   27778015 microseconds (2.275575 average)
Total multiply time: 102603627 microseconds (102603624.000000 average)

3 by 2 multiply for multiply size:    32000000x32000000 (BYTEs): 370622241 microseconds
1 calls to multiply
  387420489 calls to Basic multiply:
    Basic multiply time:        279462529 microseconds (0.721342 average)
  193710244 calls to 3 by 2 multiply:
    Construct subproblems time: 21469596 microseconds (0.110834 average)
    Combine subproblems time:   69690116 microseconds (0.359765 average)
Total multiply time: 370622241 microseconds (370622240.000000 average)

3 by 2 multiply for square size:      32000000x32000000 (BYTEs): 396960238 microseconds
1 calls to multiply
  387420489 calls to Basic multiply:
    Basic multiply time:        299786830 microseconds (0.773802 average)
  193710244 calls to 3 by 2 multiply:
    Construct subproblems time: 23299364 microseconds (0.120279 average)
    Combine subproblems time:   73874042 microseconds (0.381364 average)
Total multiply time: 396960236 microseconds (396960224.000000 average)

FFT multiply for multiply size:    64000000x64000000 (BYTEs): 15083027 microseconds
1 calls to multiply
  15924951 calls to Basic multiply:
    Basic multiply time:        6445825 microseconds (0.404763 average)
  5308254 calls to 3 by 2 multiply:
    Construct subproblems time: 366360 microseconds (0.069017 average)
    Combine subproblems time:   790102 microseconds (0.148844 average)
  27 calls to 7 by 4 multiply:
    Construct subproblems time: 13 microseconds (0.481481 average)
    Combine subproblems time:   32 microseconds (1.185185 average)
  655343 calls to 9 by 5 multiply:
    Construct subproblems time: 817544 microseconds (1.247506 average)
    Combine subproblems time:   2721663 microseconds (4.153036 average)
  1 calls to FFT multiply:
    Construct subproblems time: 2621030 microseconds (2621030.000000 average)
    Combine subproblems time:   1320457 microseconds (1320457.000000 average)
Total multiply time: 15083026 microseconds (15083026.000000 average)

FFT multiply for square size:      64000000x64000000 (BYTEs): 12197212 microseconds
1 calls to multiply
  15924888 calls to Basic multiply:
    Basic multiply time:        6059849 microseconds (0.380527 average)
  5308254 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   366060 microseconds (0.068961 average)
  18 calls to 7 by 4 multiply:
    Construct subproblems time: 4 microseconds (0.222222 average)
    Combine subproblems time:   25 microseconds (1.388889 average)
  655342 calls to 9 by 5 multiply:
    Construct subproblems time: 453977 microseconds (0.692733 average)
    Combine subproblems time:   2698238 microseconds (4.117298 average)
  1 calls to FFT multiply:
    Construct subproblems time: 1231281 microseconds (1231281.000000 average)
    Combine subproblems time:   1387778 microseconds (1387778.000000 average)
Total multiply time: 12197212 microseconds (12197212.000000 average)

2n by n multiply for multiply size:    64000000x64000000 (BYTEs): 86903291 microseconds
1 calls to multiply
  63962287 calls to Basic multiply:
    Basic multiply time:        46900954 microseconds (0.733259 average)
  21316689 calls to 3 by 2 multiply:
    Construct subproblems time: 1615733 microseconds (0.075797 average)
    Combine subproblems time:   3857373 microseconds (0.180956 average)
  2664541 calls to 9 by 5 multiply:
    Construct subproblems time: 4903413 microseconds (1.840247 average)
    Combine subproblems time:   18695018 microseconds (7.016224 average)
  20 calls to 2n by n multiply:
    Construct subproblems time: 2518210 microseconds (125910.500000 average)
    Combine subproblems time:   17900485 microseconds (895024.187500 average)
Total multiply time: 86903290 microseconds (86903288.000000 average)

2n by n multiply for square size:      64000000x64000000 (BYTEs): 79453649 microseconds
1 calls to multiply
  63959407 calls to Basic multiply:
    Basic multiply time:        45352318 microseconds (0.709080 average)
  21316689 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   1737811 microseconds (0.081524 average)
  2664541 calls to 9 by 5 multiply:
    Construct subproblems time: 2559647 microseconds (0.960633 average)
    Combine subproblems time:   19049751 microseconds (7.149356 average)
  20 calls to 2n by n multiply:
    Construct subproblems time: 1235974 microseconds (61798.699219 average)
    Combine subproblems time:   17838875 microseconds (891943.812500 average)
Total multiply time: 79453648 microseconds (79453648.000000 average)

9 by 5 multiply for multiply size:    64000000x64000000 (BYTEs): 104393252 microseconds
1 calls to multiply
  129114277 calls to Basic multiply:
    Basic multiply time:        53766867 microseconds (0.416429 average)
  43033778 calls to 3 by 2 multiply:
    Construct subproblems time: 3049977 microseconds (0.070874 average)
    Combine subproblems time:   6550587 microseconds (0.152220 average)
  5380840 calls to 9 by 5 multiply:
    Construct subproblems time: 8903433 microseconds (1.654655 average)
    Combine subproblems time:   32122387 microseconds (5.969772 average)
Total multiply time: 104393251 microseconds (104393248.000000 average)

9 by 5 multiply for square size:      64000000x64000000 (BYTEs): 93368116 microseconds
1 calls to multiply
  129114277 calls to Basic multiply:
    Basic multiply time:        52318909 microseconds (0.405214 average)
  43033778 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   3134317 microseconds (0.072834 average)
  5380840 calls to 9 by 5 multiply:
    Construct subproblems time: 4718290 microseconds (0.876869 average)
    Combine subproblems time:   33196599 microseconds (6.169408 average)
Total multiply time: 93368115 microseconds (93368112.000000 average)

7 by 4 multiply for multiply size:    64000000x64000000 (BYTEs): 151612802 microseconds
1 calls to multiply
  121060821 calls to Basic multiply:
    Basic multiply time:        97336279 microseconds (0.804028 average)
  40353607 calls to 3 by 2 multiply:
    Construct subproblems time: 3386403 microseconds (0.083918 average)
    Combine subproblems time:   8640039 microseconds (0.214108 average)
  6725601 calls to 7 by 4 multiply:
    Construct subproblems time: 8291453 microseconds (1.232820 average)
    Combine subproblems time:   33733350 microseconds (5.015664 average)
Total multiply time: 151612801 microseconds (151612800.000000 average)

7 by 4 multiply for square size:      64000000x64000000 (BYTEs): 137466833 microseconds
1 calls to multiply
  121060821 calls to Basic multiply:
    Basic multiply time:        95292792 microseconds (0.787148 average)
  40353607 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   3698824 microseconds (0.091660 average)
  6725601 calls to 7 by 4 multiply:
    Construct subproblems time: 4318374 microseconds (0.642080 average)
    Combine subproblems time:   33937602 microseconds (5.046032 average)
Total multiply time: 137466832 microseconds (137466832.000000 average)

5 by 3 multiply for multiply size:    64000000x64000000 (BYTEs): 310080593 microseconds
1 calls to multiply
  244140625 calls to Basic multiply:
    Basic multiply time:        191855406 microseconds (0.785840 average)
  61035156 calls to 5 by 3 multiply:
    Construct subproblems time: 19470243 microseconds (0.319000 average)
    Combine subproblems time:   98754943 microseconds (1.618001 average)
Total multiply time: 310080592 microseconds (310080576.000000 average)

5 by 3 multiply for square size:      64000000x64000000 (BYTEs): 284856395 microseconds
1 calls to multiply
  244140625 calls to Basic multiply:
    Basic multiply time:        181242514 microseconds (0.742369 average)
  61035156 calls to 5 by 3 multiply:
    Construct subproblems time: 10203676 microseconds (0.167177 average)
    Combine subproblems time:   91488222 microseconds (1.498943 average)
Total multiply time: 284856395 microseconds (284856384.000000 average)

3 by 2 multiply for multiply size:    64000000x64000000 (BYTEs): 1141229748 microseconds
1 calls to multiply
  1162261467 calls to Basic multiply:
    Basic multiply time:        859494644 microseconds (0.739502 average)
  581130733 calls to 3 by 2 multiply:
    Construct subproblems time: 66702834 microseconds (0.114781 average)
    Combine subproblems time:   215032270 microseconds (0.370024 average)
Total multiply time: 1141229748 microseconds (1141229696.000000 average)

3 by 2 multiply for square size:      64000000x64000000 (BYTEs): 1203885039 microseconds
1 calls to multiply
  1162261467 calls to Basic multiply:
    Basic multiply time:        909467729 microseconds (0.782498 average)
  581130733 calls to 3 by 2 multiply:
    Construct subproblems time: 70727667 microseconds (0.121707 average)
    Combine subproblems time:   223689642 microseconds (0.384921 average)
Total multiply time: 1203885038 microseconds (1203885056.000000 average)

FFT multiply for multiply size:    128000000x128000000 (BYTEs): 34829174 microseconds
1 calls to multiply
  35847827 calls to Basic multiply:
    Basic multiply time:        14988794 microseconds (0.418123 average)
  2883739 calls to 3 by 2 multiply:
    Construct subproblems time: 204410 microseconds (0.070884 average)
    Combine subproblems time:   479155 microseconds (0.166158 average)
  1376214 calls to 5 by 3 multiply:
    Construct subproblems time: 232333 microseconds (0.168820 average)
    Combine subproblems time:   993372 microseconds (0.721815 average)
  3211166 calls to 7 by 4 multiply:
    Construct subproblems time: 749418 microseconds (0.233379 average)
    Combine subproblems time:   2649777 microseconds (0.825176 average)
  655370 calls to 9 by 5 multiply:
    Construct subproblems time: 1497632 microseconds (2.285170 average)
    Combine subproblems time:   5086264 microseconds (7.760904 average)
  1 calls to FFT multiply:
    Construct subproblems time: 5044528 microseconds (5044528.000000 average)
    Combine subproblems time:   2807151 microseconds (2807151.000000 average)
Total multiply time: 34829174 microseconds (34829176.000000 average)

FFT multiply for square size:      128000000x128000000 (BYTEs): 29915278 microseconds
1 calls to multiply
  35847888 calls to Basic multiply:
    Basic multiply time:        14718830 microseconds (0.410591 average)
  2883621 calls to 3 by 2 multiply:
    Construct subproblems time: 55638 microseconds (0.019294 average)
    Combine subproblems time:   268260 microseconds (0.093029 average)
  1376235 calls to 5 by 3 multiply:
    Construct subproblems time: 135680 microseconds (0.098588 average)
    Combine subproblems time:   966932 microseconds (0.702592 average)
  3211215 calls to 7 by 4 multiply:
    Construct subproblems time: 426960 microseconds (0.132959 average)
    Combine subproblems time:   2631118 microseconds (0.819353 average)
  655360 calls to 9 by 5 multiply:
    Construct subproblems time: 809241 microseconds (1.234804 average)
    Combine subproblems time:   5043053 microseconds (7.695088 average)
  1 calls to FFT multiply:
    Construct subproblems time: 2333045 microseconds (2333045.000000 average)
    Combine subproblems time:   2386158 microseconds (2386158.000000 average)
Total multiply time: 29915277 microseconds (29915276.000000 average)

2n by n multiply for multiply size:    128000000x128000000 (BYTEs): 207308106 microseconds
1 calls to multiply
  149229043 calls to Basic multiply:
    Basic multiply time:        108710401 microseconds (0.728480 average)
  21316689 calls to 7 by 4 multiply:
    Construct subproblems time: 6454416 microseconds (0.302787 average)
    Combine subproblems time:   23179033 microseconds (1.087366 average)
  2664541 calls to 9 by 5 multiply:
    Construct subproblems time: 9650590 microseconds (3.621858 average)
    Combine subproblems time:   36974225 microseconds (13.876395 average)
  20 calls to 2n by n multiply:
    Construct subproblems time: 4787966 microseconds (239398.296875 average)
    Combine subproblems time:   35624859 microseconds (1781243.000000 average)
Total multiply time: 207308105 microseconds (207308112.000000 average)

2n by n multiply for square size:      128000000x128000000 (BYTEs): 209293238 microseconds
1 calls to multiply
  149226163 calls to Basic multiply:
    Basic multiply time:        112920413 microseconds (0.756707 average)
  21316689 calls to 7 by 4 multiply:
    Construct subproblems time: 3886025 microseconds (0.182300 average)
    Combine subproblems time:   24729684 microseconds (1.160109 average)
  2664541 calls to 9 by 5 multiply:
    Construct subproblems time: 5286002 microseconds (1.983832 average)
    Combine subproblems time:   39677872 microseconds (14.891072 average)
  20 calls to 2n by n multiply:
    Construct subproblems time: 2444563 microseconds (122228.148438 average)
    Combine subproblems time:   36445784 microseconds (1822289.250000 average)
Total multiply time: 209293237 microseconds (209293232.000000 average)

9 by 5 multiply for multiply size:    128000000x128000000 (BYTEs): 264113937 microseconds
1 calls to multiply
  289792217 calls to Basic multiply:
    Basic multiply time:        133728304 microseconds (0.461463 average)
  23745808 calls to 3 by 2 multiply:
    Construct subproblems time: 1888456 microseconds (0.079528 average)
    Combine subproblems time:   4294440 microseconds (0.180850 average)
  11703867 calls to 5 by 3 multiply:
    Construct subproblems time: 2196341 microseconds (0.187659 average)
    Combine subproblems time:   9241498 microseconds (0.789611 average)
  25406402 calls to 7 by 4 multiply:
    Construct subproblems time: 6524488 microseconds (0.256805 average)
    Combine subproblems time:   22998814 microseconds (0.905237 average)
  5380840 calls to 9 by 5 multiply:
    Construct subproblems time: 17606086 microseconds (3.271996 average)
    Combine subproblems time:   64811356 microseconds (12.044840 average)
Total multiply time: 264113935 microseconds (264113936.000000 average)

9 by 5 multiply for square size:      128000000x128000000 (BYTEs): 242390181 microseconds
1 calls to multiply
  289792217 calls to Basic multiply:
    Basic multiply time:        129805694 microseconds (0.447927 average)
  23745808 calls to 3 by 2 multiply:
    Construct subproblems time: 528290 microseconds (0.022248 average)
    Combine subproblems time:   2388410 microseconds (0.100582 average)
  11703867 calls to 5 by 3 multiply:
    Construct subproblems time: 1270106 microseconds (0.108520 average)
    Combine subproblems time:   8879375 microseconds (0.758670 average)
  25406402 calls to 7 by 4 multiply:
    Construct subproblems time: 3675597 microseconds (0.144672 average)
    Combine subproblems time:   22579795 microseconds (0.888744 average)
  5380840 calls to 9 by 5 multiply:
    Construct subproblems time: 8716967 microseconds (1.620001 average)
    Combine subproblems time:   63328509 microseconds (11.769260 average)
Total multiply time: 242390180 microseconds (242390176.000000 average)

7 by 4 multiply for multiply size:    128000000x128000000 (BYTEs): 347559867 microseconds
1 calls to multiply
  282475249 calls to Basic multiply:
    Basic multiply time:        209871347 microseconds (0.742972 average)
  47079208 calls to 7 by 4 multiply:
    Construct subproblems time: 27509470 microseconds (0.584323 average)
    Combine subproblems time:   108757449 microseconds (2.310095 average)
Total multiply time: 347559865 microseconds (347559872.000000 average)

7 by 4 multiply for square size:      128000000x128000000 (BYTEs): 344372212 microseconds
1 calls to multiply
  282475249 calls to Basic multiply:
    Basic multiply time:        215227851 microseconds (0.761935 average)
  47079208 calls to 7 by 4 multiply:
    Construct subproblems time: 15057662 microseconds (0.319837 average)
    Combine subproblems time:   112590549 microseconds (2.391513 average)
Total multiply time: 344372211 microseconds (344372224.000000 average)

5 by 3 multiply for multiply size:    128000000x128000000 (BYTEs): 813927098 microseconds
1 calls to multiply
  732421875 calls to Basic multiply:
    Basic multiply time:        533618887 microseconds (0.728568 average)
  244140625 calls to 3 by 2 multiply:
    Construct subproblems time: 18360616 microseconds (0.075205 average)
    Combine subproblems time:   47862274 microseconds (0.196044 average)
  61035156 calls to 5 by 3 multiply:
    Construct subproblems time: 32886021 microseconds (0.538805 average)
    Combine subproblems time:   181199300 microseconds (2.968769 average)
Total multiply time: 813927098 microseconds (813927104.000000 average)

5 by 3 multiply for square size:      128000000x128000000 (BYTEs): 769305372 microseconds
1 calls to multiply
  732421875 calls to Basic multiply:
    Basic multiply time:        543704461 microseconds (0.742338 average)
  244140625 calls to 3 by 2 multiply:
    Construct subproblems time: 0 microseconds (0.000000 average)
    Combine subproblems time:   21285569 microseconds (0.087186 average)
  61035156 calls to 5 by 3 multiply:
    Construct subproblems time: 18664607 microseconds (0.305801 average)
    Combine subproblems time:   183747365 microseconds (3.010517 average)
Total multiply time: 769305370 microseconds (769305344.000000 average)

3 by 2 multiply for multiply size:    128000000x128000000 (BYTEs): 3432157147 microseconds
1 calls to multiply
  -808182895 calls to Basic multiply:
    Basic multiply time:        2587441721 microseconds (0.742071 average)
  1743392200 calls to 3 by 2 multiply:
    Construct subproblems time: 200500285 microseconds (0.115006 average)
    Combine subproblems time:   644215141 microseconds (0.369518 average)
Total multiply time: 3432157147 microseconds (3432157184.000000 average)

3 by 2 multiply for square size:      128000000x128000000 (BYTEs): 3505264442 microseconds
1 calls to multiply
  -808182895 calls to Basic multiply:
    Basic multiply time:        2645600824 microseconds (0.758751 average)
  1743392200 calls to 3 by 2 multiply:
    Construct subproblems time: 204931759 microseconds (0.117548 average)
    Combine subproblems time:   654731857 microseconds (0.375551 average)
Total multiply time: 3505264440 microseconds (3505264384.000000 average)
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
    printf("If you're not doing this with a retail build, you're not getting good numbers.  All sizes in BYTES, not DIGITs!\n");

    for (int nProblemSize = c_nMinProblemSize; nProblemSize <= c_nMaxProblemSize; nProblemSize *= 2)
    {
        ResetThresholdsForOptimization();
        nX.SetRandom(nProblemSize*8);
        nY.SetRandom(nProblemSize*8);
        nProduct.Reserve(nX.GetSize() + nY.GetSize());
        for (int eAlgorithm = eFFTMult; eBasicMultiply < eAlgorithm; eAlgorithm--)
        {
            c_pnMultiplicationThresholds[eAlgorithm] = 10000000000; // to force use of algorithm for any large problem
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
            printf("%s for multiply size:    %I64ux%I64u (BYTEs): %I64u microseconds\n", GetMultiplicationAlgorithmName((EMultiplyAlgorithm) eAlgorithm), nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime);
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
            printf("%s for square size:      %I64ux%I64u (BYTEs): %I64u microseconds\n", GetMultiplicationAlgorithmName((EMultiplyAlgorithm)eAlgorithm), nX.GetSize()*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime);
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
            printf("Basic multiply for multiply size: %I64ux%I64u (BYTEs): %I64u microseconds\n", nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime);
            ReportMeasuredComponentTimingData(eMultiplicationMeasured);
            dwStartTime = s_Timer.GetMicroseconds();
            MultOracle(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue());
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Mult oracle for multiply size:    %I64ux%I64u (BYTEs): %I64u microseconds\n", nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime);
            printf("\n");
        }
    }
}

/*
* 32-bit
Time for 65536 1000x1000 BYTE multiplications: 1178828 microseconds
Time for 65536 divisions of 2000 BYTE number by 1000 BYTE number: 7057662 microseconds (divide:multiply ratio: 5.987016) -- basic
Time for 65536 divisions of 2000 BYTE number by 1000 BYTE number: 2995242 microseconds (divide:multiply ratio: 2.540864)
Time for 65536 1000x2000 BYTE multiplications: 2406288 microseconds
Time for 65536 divisions of 3000 BYTE number by 1000 BYTE number: 5948484 microseconds (divide:multiply ratio: 2.472058)
Time for 65536 divisions of 3000 BYTE number by 2000 BYTE number: 4856545 microseconds (divide:multiply ratio: 2.018273)
Time for 2048 10000x10000 BYTE multiplications: 1091818 microseconds
Time for 2048 divisions of 20000 BYTE number by 10000 BYTE number: 31703547 microseconds (divide:multiply ratio: 29.037394) -- basic
Time for 2048 divisions of 20000 BYTE number by 10000 BYTE number: 3043133 microseconds (divide:multiply ratio: 2.787216)
Time for 2048 10000x20000 BYTE multiplications: 2087866 microseconds
Time for 2048 divisions of 30000 BYTE number by 10000 BYTE number: 6166754 microseconds (divide:multiply ratio: 2.953616)
Time for 2048 divisions of 30000 BYTE number by 20000 BYTE number: 4114748 microseconds (divide:multiply ratio: 1.970791)
Time for 128 100000x100000 BYTE multiplications: 1338069 microseconds
Time for 128 divisions of 200000 BYTE number by 100000 BYTE number: 206145332 microseconds (divide:multiply ratio: 154.061813) -- basic
Time for 128 divisions of 200000 BYTE number by 100000 BYTE number: 4895465 microseconds (divide:multiply ratio: 3.658604)
Time for 128 100000x200000 BYTE multiplications: 2851032 microseconds
Time for 128 divisions of 300000 BYTE number by 100000 BYTE number: 10034576 microseconds (divide:multiply ratio: 3.519629)
Time for 128 divisions of 300000 BYTE number by 200000 BYTE number: 6191491 microseconds (divide:multiply ratio: 2.171667)
Time for 16 1000000x1000000 BYTE multiplications: 1690593 microseconds
Time for 16 divisions of 2000000 BYTE number by 1000000 BYTE number: 2573392692 microseconds (divide:multiply ratio: 1522.183472) -- basic
Time for 16 divisions of 2000000 BYTE number by 1000000 BYTE number: 10592098 microseconds (divide:multiply ratio: 6.265315)
Time for 16 1000000x2000000 BYTE multiplications: 3370204 microseconds
Time for 16 divisions of 3000000 BYTE number by 1000000 BYTE number: 21096732 microseconds (divide:multiply ratio: 6.259779)
Time for 16 divisions of 3000000 BYTE number by 2000000 BYTE number: 12648538 microseconds (divide:multiply ratio: 3.753048)
Time for 1 10000000x10000000 BYTE multiplications: 2529712 microseconds
Time for 1 divisions of 20000000 BYTE number by 10000000 BYTE number: 15918285 microseconds (divide:multiply ratio: 6.292529)
Time for 1 10000000x20000000 BYTE multiplications: 5033066 microseconds
Time for 1 divisions of 30000000 BYTE number by 10000000 BYTE number: 31792795 microseconds (divide:multiply ratio: 6.316785)
Time for 1 divisions of 30000000 BYTE number by 20000000 BYTE number: 19010005 microseconds (divide:multiply ratio: 3.777023)
Time for 1 100000000x100000000 BYTE multiplications: 30960012 microseconds
Time for 1 divisions of 200000000 BYTE number by 100000000 BYTE number: 209530671 microseconds (divide:multiply ratio: 6.767784)
Time for 1 100000000x200000000 BYTE multiplications: 63069821 microseconds
Time for 1 divisions of 300000000 BYTE number by 100000000 BYTE number: 419078616 microseconds (divide:multiply ratio: 6.644678)
Time for 1 divisions of 300000000 BYTE number by 200000000 BYTE number: 241927068 microseconds (divide:multiply ratio: 3.835861)

with full timing data collected (older version -- just proportions):
Dividing a 200000000-BYTE number by a 100000000-BYTE one took 280748591 microseconds
532113006 calls to Basic multiply:
        Build time:         0
        Recursive time:     0
        Process time:       89332426
218906941 calls to 3 by 2 multiply:
        Build time:         19197983
        Recursive time:     0
        Process time:       16384527
9554139 calls to 5 by 3 multiply:
        Build time:         2914077
        Recursive time:     92056750
        Process time:       3480360
38374267 calls to 7 by 4 multiply:
        Build time:         33805055
        Recursive time:     96946758
        Process time:       24053164
0 calls to 9 by 5 multiply:
        Build time:         0
        Recursive time:     0
        Process time:       0
0 calls to 2n by n multiply:
        Build time:         0
        Recursive time:     0
        Process time:       327
2046 calls to FFT multiply:
        Build time:         41071376
        Recursive time:     161060980
        Process time:       22543470
Total calls to divide: 1
        Process time:           5478368
        Basic divide time:      2046166
        Time in multiplication: 272200628
        Total divide time:      280748591
Faster with full perf turned off:
Dividing a 200000-BYTE number by a 100000-BYTE one took 55407 microseconds
Dividing a 2000000-BYTE number by a 1000000-BYTE one took 950979 microseconds
Dividing a 20000000-BYTE number by a 10000000-BYTE one took 18648567 microseconds
Dividing a 200000000-BYTE number by a 100000000-BYTE one took 253381757 microseconds

16-bit
Time for 16384 1000x1000 BYTE multiplications: 1264217 microseconds
Time for 16384 divisions of 2000 BYTE number by 1000 BYTE number: 9689536 microseconds (divide:multiply ratio: 7.664456) -- basic
Time for 16384 divisions of 2000 BYTE number by 1000 BYTE number: 2831927 microseconds (divide:multiply ratio: 2.240064)
Time for 16384 1000x2000 BYTE multiplications: 2263267 microseconds
Time for 16384 divisions of 3000 BYTE number by 1000 BYTE number: 5665477 microseconds (divide:multiply ratio: 2.503230)
Time for 16384 divisions of 3000 BYTE number by 2000 BYTE number: 4328893 microseconds (divide:multiply ratio: 1.912674)
Time for 512 10000x10000 BYTE multiplications: 1083575 microseconds
Time for 512 divisions of 20000 BYTE number by 10000 BYTE number: 38882366 microseconds (divide:multiply ratio: 35.883411) -- basic
Time for 512 divisions of 20000 BYTE number by 10000 BYTE number: 2783803 microseconds (divide:multiply ratio: 2.569091)
Time for 512 10000x20000 BYTE multiplications: 1912838 microseconds
Time for 512 divisions of 30000 BYTE number by 10000 BYTE number: 5422868 microseconds (divide:multiply ratio: 2.834985)
Time for 512 divisions of 30000 BYTE number by 20000 BYTE number: 3854664 microseconds (divide:multiply ratio: 2.015154)
Time for 64 100000x100000 BYTE multiplications: 1814802 microseconds
Time for 64 divisions of 200000 BYTE number by 100000 BYTE number: 486730250 microseconds (divide:multiply ratio: 268.200195) -- basic
Time for 64 divisions of 200000 BYTE number by 100000 BYTE number: 7964939 microseconds (divide:multiply ratio: 4.388875)
Time for 64 100000x200000 BYTE multiplications: 3514164 microseconds
Time for 64 divisions of 300000 BYTE number by 100000 BYTE number: 15615676 microseconds (divide:multiply ratio: 4.443639)
Time for 64 divisions of 300000 BYTE number by 200000 BYTE number: 9536248 microseconds (divide:multiply ratio: 2.713660)
Time for 4 1000000x1000000 BYTE multiplications: 1148450 microseconds
Time for 4 divisions of 2000000 BYTE number by 1000000 BYTE number: 1764759681 microseconds (divide:multiply ratio: 1536.644775) -- basic
Time for 4 divisions of 2000000 BYTE number by 1000000 BYTE number: 7769457 microseconds (divide:multiply ratio: 6.765168)
Time for 4 1000000x2000000 BYTE multiplications: 2537627 microseconds
Time for 4 divisions of 3000000 BYTE number by 1000000 BYTE number: 16854012 microseconds (divide:multiply ratio: 6.641643)
Time for 4 divisions of 3000000 BYTE number by 2000000 BYTE number: 9055741 microseconds (divide:multiply ratio: 3.568586)
Time for 1 10000000x10000000 BYTE multiplications: 7721213 microseconds
Time for 1 divisions of 20000000 BYTE number by 10000000 BYTE number: 50381570 microseconds (divide:multiply ratio: 6.525084)
Time for 1 10000000x20000000 BYTE multiplications: 15350490 microseconds
Time for 1 divisions of 30000000 BYTE number by 10000000 BYTE number: 107269252 microseconds (divide:multiply ratio: 6.988001)
Time for 1 divisions of 30000000 BYTE number by 20000000 BYTE number: 59456765 microseconds (divide:multiply ratio: 3.873281)
Time for 1 100000000x100000000 BYTE multiplications: 103871500 microseconds
Time for 1 divisions of 200000000 BYTE number by 100000000 BYTE number: 660012231 microseconds (divide:multiply ratio: 6.354122)
Time for 1 100000000x200000000 BYTE multiplications: 198125137 microseconds
Time for 1 divisions of 300000000 BYTE number by 100000000 BYTE number: 1412293301 microseconds (divide:multiply ratio: 7.128289)
Time for 1 divisions of 300000000 BYTE number by 200000000 BYTE number: 880910895 microseconds (divide:multiply ratio: 4.446235)

Time for 16384 1000x1000 BYTE multiplications: 1097362 microseconds
Time for 16384 divisions of 2000 BYTE number by 1000 BYTE number: 10108823 microseconds (divide:multiply ratio: 9.211931) -- basic
Time for 16384 divisions of 2000 BYTE number by 1000 BYTE number: 3049790 microseconds (divide:multiply ratio: 2.779202)
Time for 16384 1000x2000 BYTE multiplications: 2277496 microseconds
Time for 16384 divisions of 3000 BYTE number by 1000 BYTE number: 5511143 microseconds (divide:multiply ratio: 2.419826)
Time for 16384 divisions of 3000 BYTE number by 2000 BYTE number: 3863420 microseconds (divide:multiply ratio: 1.696345)
Time for 1024 10000x10000 BYTE multiplications: 1828978 microseconds
Time for 1024 divisions of 20000 BYTE number by 10000 BYTE number: 70599407 microseconds (divide:multiply ratio: 38.600468) -- basic
Time for 1024 divisions of 20000 BYTE number by 10000 BYTE number: 5530161 microseconds (divide:multiply ratio: 3.023634)
Time for 1024 10000x20000 BYTE multiplications: 3859482 microseconds
Time for 1024 divisions of 30000 BYTE number by 10000 BYTE number: 10615460 microseconds (divide:multiply ratio: 2.750488)
Time for 1024 divisions of 30000 BYTE number by 20000 BYTE number: 7343304 microseconds (divide:multiply ratio: 1.902666)
Time for 64 100000x100000 BYTE multiplications: 1752178 microseconds
Time for 64 divisions of 200000 BYTE number by 100000 BYTE number: 376901036 microseconds (divide:multiply ratio: 215.104294) -- basic
Time for 64 divisions of 200000 BYTE number by 100000 BYTE number: 7713614 microseconds (divide:multiply ratio: 4.402300)
Time for 64 100000x200000 BYTE multiplications: 3553777 microseconds
Time for 64 divisions of 300000 BYTE number by 100000 BYTE number: 15423747 microseconds (divide:multiply ratio: 4.340100)
Time for 64 divisions of 300000 BYTE number by 200000 BYTE number: 9434207 microseconds (divide:multiply ratio: 2.654699)
Time for 4 1000000x1000000 BYTE multiplications: 1175065 microseconds
Time for 4 divisions of 2000000 BYTE number by 1000000 BYTE number: 3438432767 microseconds (divide:multiply ratio: 2926.163818) -- basic
Time for 4 divisions of 2000000 BYTE number by 1000000 BYTE number: 8052458 microseconds (divide:multiply ratio: 6.852777)
Time for 4 1000000x2000000 BYTE multiplications: 2341066 microseconds
Time for 4 divisions of 3000000 BYTE number by 1000000 BYTE number: 15267051 microseconds (divide:multiply ratio: 6.521410)
Time for 4 divisions of 3000000 BYTE number by 2000000 BYTE number: 9235101 microseconds (divide:multiply ratio: 3.944827)
Time for 1 10000000x10000000 BYTE multiplications: 7802610 microseconds
Time for 1 divisions of 20000000 BYTE number by 10000000 BYTE number: 50148490 microseconds (divide:multiply ratio: 6.427143)
Time for 1 10000000x20000000 BYTE multiplications: 15439938 microseconds
Time for 1 divisions of 30000000 BYTE number by 10000000 BYTE number: 98853049 microseconds (divide:multiply ratio: 6.402425)
Time for 1 divisions of 30000000 BYTE number by 20000000 BYTE number: 56814540 microseconds (divide:multiply ratio: 3.679713)
Time for 1 100000000x100000000 BYTE multiplications: 103448897 microseconds
Time for 1 divisions of 200000000 BYTE number by 100000000 BYTE number: 725978837 microseconds (divide:multiply ratio: 7.017753)
Time for 1 100000000x200000000 BYTE multiplications: 232934948 microseconds
Time for 1 divisions of 300000000 BYTE number by 100000000 BYTE number: 1387310472 microseconds (divide:multiply ratio: 5.955785)
Time for 1 divisions of 300000000 BYTE number by 200000000 BYTE number: 939119649 microseconds (divide:multiply ratio: 4.031682)

full breakdown
32-bit DIGITs
Time for 65536 1000x1000 BYTE multiplications: 1411682 microseconds
65536 calls to multiply
  1769472 calls to Basic multiply:
    Basic multiply time:        963081 microseconds (0.544276 average)
  589824 calls to 3 by 2 multiply:
    Construct subproblems time: 44130 microseconds (0.074819 average)
    Combine subproblems time:   102524 microseconds (0.173821 average)
  65536 calls to 9 by 5 multiply:
    Construct subproblems time: 62373 microseconds (0.951736 average)
    Combine subproblems time:   237272 microseconds (3.620483 average)
Total multiply time: 1409380 microseconds (21.505432 average)

Time for 65536 divisions of 2000 BYTE number by 1000 BYTE number: 10256586 microseconds (divide:multiply ratio: 7.265507) -- basic
Total calls to divide: 65536
  Time in recursive divide: 0 microseconds (0.000000 average)
  Time in multiplication:   0 microseconds (0.000000 average)
  Time in basic divide:     10229565 microseconds (156.090775 average)
  Total divide time:        10246375 microseconds (156.347275 average)

Time for 65536 divisions of 2000 BYTE number by 1000 BYTE number: 4291627 microseconds (divide:multiply ratio: 3.040081)Total calls to divide: 65536
  Time in recursive divide: 767757 microseconds (11.715042 average)
  Time in multiplication:   2313629 microseconds (35.303177 average)
  Time in basic divide:     932964 microseconds (14.235901 average)
  Total divide time:        4283607 microseconds (65.362656 average)

Time for 65536 1000x2000 BYTE multiplications: 2917315 microseconds
65536 calls to multiply
  3538944 calls to Basic multiply:
    Basic multiply time:        1967096 microseconds (0.555843 average)
  1179648 calls to 3 by 2 multiply:
    Construct subproblems time: 90252 microseconds (0.076508 average)
    Combine subproblems time:   209447 microseconds (0.177550 average)
  131072 calls to 9 by 5 multiply:
    Construct subproblems time: 133636 microseconds (1.019562 average)
    Combine subproblems time:   514070 microseconds (3.922043 average)
Total multiply time: 2914501 microseconds (44.471756 average)

Time for 65536 divisions of 3000 BYTE number by 1000 BYTE number: 10122145 microseconds (divide:multiply ratio: 3.469678)
Total calls to divide: 65536
  Time in recursive divide: 1808351 microseconds (27.593246 average)
  Time in multiplication:   5529082 microseconds (84.367096 average)
  Time in basic divide:     2174885 microseconds (33.186111 average)
  Total divide time:        10109892 microseconds (154.264709 average)

Time for 65536 divisions of 3000 BYTE number by 2000 BYTE number: 6717171 microseconds (divide:multiply ratio: 2.302518)Total calls to divide: 65536
  Time in recursive divide: 924273 microseconds (14.103287 average)
  Time in multiplication:   4165840 microseconds (63.565674 average)
  Time in basic divide:     1303343 microseconds (19.887436 average)
  Total divide time:        6705835 microseconds (102.322922 average)

Time for 2048 10000x10000 BYTE multiplications: 1262784 microseconds
2048 calls to multiply
  1161216 calls to Basic multiply:
    Basic multiply time:        742418 microseconds (0.639345 average)
  165888 calls to 7 by 4 multiply:
    Construct subproblems time: 54399 microseconds (0.327926 average)
    Combine subproblems time:   188048 microseconds (1.133584 average)
  20480 calls to 9 by 5 multiply:
    Construct subproblems time: 56207 microseconds (2.744483 average)
    Combine subproblems time:   215816 microseconds (10.537890 average)
Total multiply time: 1262590 microseconds (616.499023 average)

Time for 2048 divisions of 20000 BYTE number by 10000 BYTE number: 29104910 microseconds (divide:multiply ratio: 23.048210) -- basic
Total calls to divide: 2048
  Time in recursive divide: 0 microseconds (0.000000 average)
  Time in multiplication:   0 microseconds (0.000000 average)
  Time in basic divide:     29096351 microseconds (14207.203125 average)
  Total divide time:        29100964 microseconds (14209.455078 average)

Time for 2048 divisions of 20000 BYTE number by 10000 BYTE number: 3644981 microseconds (divide:multiply ratio: 2.886464)
Total calls to divide: 2048
  Time in recursive divide: 268254 microseconds (130.983398 average)
  Time in multiplication:   2985988 microseconds (1458.001953 average)
  Time in basic divide:     317471 microseconds (155.015137 average)
  Total divide time:        3643031 microseconds (1778.823730 average)

Time for 2048 10000x20000 BYTE multiplications: 2236282 microseconds
2048 calls to multiply
  2322432 calls to Basic multiply:
    Basic multiply time:        1293583 microseconds (0.556995 average)
  331776 calls to 7 by 4 multiply:
    Construct subproblems time: 99836 microseconds (0.300914 average)
    Combine subproblems time:   334376 microseconds (1.007837 average)
  40960 calls to 9 by 5 multiply:
    Construct subproblems time: 101275 microseconds (2.472534 average)
    Combine subproblems time:   397046 microseconds (9.693506 average)
Total multiply time: 2236160 microseconds (1091.875000 average)

Time for 2048 divisions of 30000 BYTE number by 10000 BYTE number: 6977273 microseconds (divide:multiply ratio: 3.120033)
Total calls to divide: 2048
  Time in recursive divide: 514899 microseconds (251.415527 average)
  Time in multiplication:   5710673 microseconds (2788.414551 average)
  Time in basic divide:     613527 microseconds (299.573730 average)
  Total divide time:        6974247 microseconds (3405.394043 average)

Time for 2048 divisions of 30000 BYTE number by 20000 BYTE number: 4700753 microseconds (divide:multiply ratio: 2.102040)
Total calls to divide: 2048
  Time in recursive divide: 280988 microseconds (137.201172 average)
  Time in multiplication:   4080818 microseconds (1992.586914 average)
  Time in basic divide:     262142 microseconds (127.999023 average)
  Total divide time:        4697943 microseconds (2293.917480 average)

Time for 128 100000x100000 BYTE multiplications: 1425198 microseconds
128 calls to multiply
  785920 calls to Basic multiply:
    Basic multiply time:        589489 microseconds (0.750062 average)
  261888 calls to 3 by 2 multiply:
    Construct subproblems time: 37145 microseconds (0.141835 average)
    Combine subproblems time:   52514 microseconds (0.200521 average)
  128 calls to FFT multiply:
    Construct subproblems time: 474833 microseconds (3709.632812 average)
    Combine subproblems time:   271170 microseconds (2118.515625 average)
Total multiply time: 1425151 microseconds (11133.992188 average)

Time for 128 divisions of 200000 BYTE number by 100000 BYTE number: 189467523 microseconds (divide:multiply ratio: 132.941193) -- basic
Total calls to divide: 128
  Time in recursive divide: 0 microseconds (0.000000 average)
  Time in multiplication:   0 microseconds (0.000000 average)
  Time in basic divide:     189463361 microseconds (1480182.500000 average)
  Total divide time:        189465367 microseconds (1480198.125000 average)

Time for 128 divisions of 200000 BYTE number by 100000 BYTE number: 5503719 microseconds (divide:multiply ratio: 3.861722)
Total calls to divide: 128
  Time in recursive divide: 246958 microseconds (1929.359375 average)
  Time in multiplication:   4973664 microseconds (38856.750000 average)
  Time in basic divide:     214136 microseconds (1672.937500 average)
  Total divide time:        5501781 microseconds (42982.664062 average)

Time for 128 100000x200000 BYTE multiplications: 2764530 microseconds
128 calls to multiply
  1571840 calls to Basic multiply:
    Basic multiply time:        1137653 microseconds (0.723772 average)
  523776 calls to 3 by 2 multiply:
    Construct subproblems time: 71585 microseconds (0.136671 average)
    Combine subproblems time:   101325 microseconds (0.193451 average)
  256 calls to FFT multiply:
    Construct subproblems time: 924765 microseconds (3612.363281 average)
    Combine subproblems time:   529160 microseconds (2067.031250 average)
Total multiply time: 2764488 microseconds (21597.562500 average)

Time for 128 divisions of 300000 BYTE number by 100000 BYTE number: 11007551 microseconds (divide:multiply ratio: 3.981708)
Total calls to divide: 128
  Time in recursive divide: 493921 microseconds (3858.757812 average)
  Time in multiplication:   9957345 microseconds (77791.757812 average)
  Time in basic divide:     421006 microseconds (3289.109375 average)
  Total divide time:        11004423 microseconds (85972.054688 average)

Time for 128 divisions of 300000 BYTE number by 200000 BYTE number: 7102879 microseconds (divide:multiply ratio: 2.569290)
Total calls to divide: 128
  Time in recursive divide: 265914 microseconds (2077.453125 average)
  Time in multiplication:   6584456 microseconds (51441.062500 average)
  Time in basic divide:     179353 microseconds (1401.195312 average)
  Total divide time:        7100016 microseconds (55468.875000 average)

Time for 16 1000000x1000000 BYTE multiplications: 1970561 microseconds
16 calls to multiply
  1179504 calls to Basic multiply:
    Basic multiply time:        720654 microseconds (0.610981 average)
  48 calls to 3 by 2 multiply:
    Construct subproblems time: 31 microseconds (0.645833 average)
    Combine subproblems time:   18 microseconds (0.375000 average)
  131040 calls to 9 by 5 multiply:
    Construct subproblems time: 91403 microseconds (0.697520 average)
    Combine subproblems time:   253067 microseconds (1.931219 average)
  16 calls to FFT multiply:
    Construct subproblems time: 576337 microseconds (36021.062500 average)
    Combine subproblems time:   329040 microseconds (20565.000000 average)
Total multiply time: 1970550 microseconds (123159.375000 average)

Time for 16 divisions of 2000000 BYTE number by 1000000 BYTE number: 2627611540 microseconds (divide:multiply ratio: 1333.433350) -- basic
Total calls to divide: 16
  Time in recursive divide: 0 microseconds (0.000000 average)
  Time in multiplication:   0 microseconds (0.000000 average)
  Time in basic divide:     2627603890 microseconds (164225248.000000 average)
  Total divide time:        2627606401 microseconds (164225408.000000 average)

Time for 16 divisions of 2000000 BYTE number by 1000000 BYTE number: 12138194 microseconds (divide:multiply ratio: 6.159766)
Total calls to divide: 16
  Time in recursive divide: 322782 microseconds (20173.875000 average)
  Time in multiplication:   11450692 microseconds (715668.250000 average)
  Time in basic divide:     290704 microseconds (18169.000000 average)
  Total divide time:        12134929 microseconds (758433.062500 average)

Time for 16 1000000x2000000 BYTE multiplications: 3641018 microseconds
16 calls to multiply
  2359008 calls to Basic multiply:
    Basic multiply time:        1344909 microseconds (0.570116 average)
  96 calls to 3 by 2 multiply:
    Construct subproblems time: 74 microseconds (0.770833 average)
    Combine subproblems time:   24 microseconds (0.250000 average)
  262080 calls to 9 by 5 multiply:
    Construct subproblems time: 169722 microseconds (0.647596 average)
    Combine subproblems time:   471289 microseconds (1.798264 average)
  32 calls to FFT multiply:
    Construct subproblems time: 1063628 microseconds (33238.375000 average)
    Combine subproblems time:   591362 microseconds (18480.062500 average)
Total multiply time: 3641008 microseconds (227563.000000 average)

Time for 16 divisions of 3000000 BYTE number by 1000000 BYTE number: 23208137 microseconds (divide:multiply ratio: 6.374079)
Total calls to divide: 16
  Time in recursive divide: 616853 microseconds (38553.312500 average)
  Time in multiplication:   21903681 microseconds (1368980.000000 average)
  Time in basic divide:     548713 microseconds (34294.562500 average)
  Total divide time:        23203366 microseconds (1450210.375000 average)

Time for 16 divisions of 3000000 BYTE number by 2000000 BYTE number: 13399904 microseconds (divide:multiply ratio: 3.680263)
Total calls to divide: 16
  Time in recursive divide: 323587 microseconds (20224.187500 average)
  Time in multiplication:   12756578 microseconds (797286.125000 average)
  Time in basic divide:     244775 microseconds (15298.437500 average)
  Total divide time:        13395456 microseconds (837216.000000 average)

Time for 1 10000000x10000000 BYTE multiplications: 2724279 microseconds
1 calls to multiply
  2064339 calls to Basic multiply:
    Basic multiply time:        1157070 microseconds (0.560504 average)
  27 calls to 3 by 2 multiply:
    Construct subproblems time: 4 microseconds (0.148148 average)
    Combine subproblems time:   8 microseconds (0.296296 average)
  294894 calls to 7 by 4 multiply:
    Construct subproblems time: 80656 microseconds (0.273508 average)
    Combine subproblems time:   296346 microseconds (1.004924 average)
  32769 calls to 9 by 5 multiply:
    Construct subproblems time: 84714 microseconds (2.585187 average)
    Combine subproblems time:   227056 microseconds (6.928988 average)
  1 calls to FFT multiply:
    Construct subproblems time: 572942 microseconds (572942.000000 average)
    Combine subproblems time:   296486 microseconds (296486.000000 average)
Total multiply time: 2724279 microseconds (2724279.000000 average)

Time for 1 divisions of 20000000 BYTE number by 10000000 BYTE number: 17778551 microseconds (divide:multiply ratio: 6.525966)
Total calls to divide: 1
  Time in recursive divide: 195688 microseconds (195688.000000 average)
  Time in multiplication:   17344074 microseconds (17344074.000000 average)
  Time in basic divide:     199896 microseconds (199896.000000 average)
  Total divide time:        17774322 microseconds (17774322.000000 average)

Time for 1 10000000x20000000 BYTE multiplications: 5590083 microseconds
1 calls to multiply
  4128687 calls to Basic multiply:
    Basic multiply time:        2362965 microseconds (0.572328 average)
  36 calls to 3 by 2 multiply:
    Construct subproblems time: 2 microseconds (0.055556 average)
    Combine subproblems time:   8 microseconds (0.222222 average)
  589797 calls to 7 by 4 multiply:
    Construct subproblems time: 165412 microseconds (0.280456 average)
    Combine subproblems time:   606451 microseconds (1.028237 average)
  65537 calls to 9 by 5 multiply:
    Construct subproblems time: 172972 microseconds (2.639303 average)
    Combine subproblems time:   465014 microseconds (7.095442 average)
  2 calls to FFT multiply:
    Construct subproblems time: 1195764 microseconds (597882.000000 average)
    Combine subproblems time:   602818 microseconds (301409.000000 average)
Total multiply time: 5590082 microseconds (5590082.000000 average)

Time for 1 divisions of 30000000 BYTE number by 10000000 BYTE number: 34568017 microseconds (divide:multiply ratio: 6.183811)
Total calls to divide: 1
  Time in recursive divide: 394033 microseconds (394033.000000 average)
  Time in multiplication:   33716188 microseconds (33716188.000000 average)
  Time in basic divide:     387049 microseconds (387049.000000 average)
  Total divide time:        34564013 microseconds (34564012.000000 average)

Time for 1 divisions of 30000000 BYTE number by 20000000 BYTE number: 20531721 microseconds (divide:multiply ratio: 3.672883)
Total calls to divide: 1
  Time in recursive divide: 208947 microseconds (208947.000000 average)
  Time in multiplication:   20086450 microseconds (20086450.000000 average)
  Time in basic divide:     195956 microseconds (195956.000000 average)
  Total divide time:        20528155 microseconds (20528156.000000 average)

Time for 1 100000000x100000000 BYTE multiplications: 34545840 microseconds
1 calls to multiply
  35847584 calls to Basic multiply:
    Basic multiply time:        15116238 microseconds (0.421681 average)
  2883658 calls to 3 by 2 multiply:
    Construct subproblems time: 207782 microseconds (0.072055 average)
    Combine subproblems time:   483918 microseconds (0.167814 average)
  1376214 calls to 5 by 3 multiply:
    Construct subproblems time: 234095 microseconds (0.170101 average)
    Combine subproblems time:   1000752 microseconds (0.727178 average)
  3211166 calls to 7 by 4 multiply:
    Construct subproblems time: 752929 microseconds (0.234472 average)
    Combine subproblems time:   2669543 microseconds (0.831331 average)
  655360 calls to 9 by 5 multiply:
    Construct subproblems time: 1491522 microseconds (2.275882 average)
    Combine subproblems time:   5131817 microseconds (7.830531 average)
  1 calls to FFT multiply:
    Construct subproblems time: 4958231 microseconds (4958231.000000 average)
    Combine subproblems time:   2401523 microseconds (2401523.000000 average)
Total multiply time: 34545840 microseconds (34545840.000000 average)

Time for 1 divisions of 200000000 BYTE number by 100000000 BYTE number: 230345757 microseconds (divide:multiply ratio: 6.667829)
Total calls to divide: 1
  Time in recursive divide: 2734711 microseconds (2734711.000000 average)
  Time in multiplication:   225707340 microseconds (225707344.000000 average)
  Time in basic divide:     1319403 microseconds (1319403.000000 average)
  Total divide time:        230304064 microseconds (230304064.000000 average)

Time for 1 100000000x200000000 BYTE multiplications: 67926605 microseconds
1 calls to multiply
  71695411 calls to Basic multiply:
    Basic multiply time:        30151856 microseconds (0.420555 average)
  5767397 calls to 3 by 2 multiply:
    Construct subproblems time: 412076 microseconds (0.071449 average)
    Combine subproblems time:   962306 microseconds (0.166853 average)
  2752428 calls to 5 by 3 multiply:
    Construct subproblems time: 462899 microseconds (0.168178 average)
    Combine subproblems time:   1987993 microseconds (0.722269 average)
  6422332 calls to 7 by 4 multiply:
    Construct subproblems time: 1492735 microseconds (0.232429 average)
    Combine subproblems time:   5296223 microseconds (0.824657 average)
  1310730 calls to 9 by 5 multiply:
    Construct subproblems time: 2978651 microseconds (2.272513 average)
    Combine subproblems time:   10184740 microseconds (7.770281 average)
  2 calls to FFT multiply:
    Construct subproblems time: 9058524 microseconds (4529262.000000 average)
    Combine subproblems time:   4744967 microseconds (2372483.500000 average)
Total multiply time: 67926604 microseconds (67926608.000000 average)

Time for 1 divisions of 300000000 BYTE number by 100000000 BYTE number: 466669713 microseconds (divide:multiply ratio: 6.870205)
Total calls to divide: 1
  Time in recursive divide: 5482848 microseconds (5482848.000000 average)
  Time in multiplication:   457504537 microseconds (457504544.000000 average)
  Time in basic divide:     2542556 microseconds (2542556.000000 average)
  Total divide time:        466614508 microseconds (466614496.000000 average)

Time for 1 divisions of 300000000 BYTE number by 200000000 BYTE number: 263333944 microseconds (divide:multiply ratio: 3.876742)
Total calls to divide: 1
  Time in recursive divide: 2901667 microseconds (2901667.000000 average)
  Time in multiplication:   258201095 microseconds (258201088.000000 average)
  Time in basic divide:     1600951 microseconds (1600951.000000 average)
  Total divide time:        263283822 microseconds (263283824.000000 average)
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
    printf("If you're not doing this with a retail build, you're not getting good numbers.  All sizes in BYTES, not DIGITs!\n");
    for (int nSize = c_nMinSize; nSize <= c_nMaxSize; nSize *= 10)
    {
        nX.SetRandom(nSize*8); // want size in BYTEs; set random size bits
        nY.SetRandom(2*nSize*8); // want size in BYTES; set random size bits
        nProduct1.Reserve(nX.GetSize() + nY.GetSize());
        nProduct2.Reserve(nX.GetSize() + nY.GetSize());
        nDiv.Reserve(nY.GetSize());
        cWork.Reserve(MultiplyMemoryNeeds(nX.GetSize(), nY.GetSize()));
        cWork.Reserve(DivisionMemoryNeeds(nX.GetSize() + nY.GetSize(), nX.GetSize()));
        cWork.Reserve(DivisionMemoryNeeds(nX.GetSize() + nY.GetSize(), nY.GetSize()));
        ResetThresholdsForOptimization();
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
        ResetThresholdsForOptimization();
        dwMultTime = dwStartTime;
        if(nX.GetSize()<=1000000)
        {
            c_nDivideThresholdSmall = 1000000000; // force the system to use basic division
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
        }
        ResetThresholdsForOptimization();
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
        ResetThresholdsForOptimization();
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
        ResetThresholdsForOptimization();
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
        ResetThresholdsForOptimization();
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
Time to get the GCD of 16777216 pairs of 1-DIGIT numbers:              9109 milliseconds
Time to get the GCD of 16777216 pairs of 1-DIGIT numbers, x-coef only: 9110 milliseconds
Time to get the GCD of 8388608 pairs of 2-DIGIT numbers:              9422 milliseconds
Time to get the GCD of 8388608 pairs of 2-DIGIT numbers, x-coef only: 9375 milliseconds
Time to get the GCD of 4194304 pairs of 4-DIGIT numbers:              10782 milliseconds
Time to get the GCD of 4194304 pairs of 4-DIGIT numbers, x-coef only: 10375 milliseconds
Time to get the GCD of 2097152 pairs of 8-DIGIT numbers:              11968 milliseconds
Time to get the GCD of 2097152 pairs of 8-DIGIT numbers, x-coef only: 11657 milliseconds
Time to get the GCD of 1048576 pairs of 16-DIGIT numbers:              13671 milliseconds
Time to get the GCD of 1048576 pairs of 16-DIGIT numbers, x-coef only: 13532 milliseconds
Time to get the GCD of 524288 pairs of 32-DIGIT numbers:              18515 milliseconds
Time to get the GCD of 524288 pairs of 32-DIGIT numbers, x-coef only: 19110 milliseconds
Time to get the GCD of 262144 pairs of 64-DIGIT numbers:              27515 milliseconds
Time to get the GCD of 262144 pairs of 64-DIGIT numbers, x-coef only: 28516 milliseconds
Time to get the GCD of 131072 pairs of 128-DIGIT numbers:              45328 milliseconds
Time to get the GCD of 131072 pairs of 128-DIGIT numbers, x-coef only: 47500 milliseconds
Time to get the GCD of 65536 pairs of 256-DIGIT numbers:              87281 milliseconds
Time to get the GCD of 65536 pairs of 256-DIGIT numbers, x-coef only: 84032 milliseconds
Time to get the GCD of 32768 pairs of 512-DIGIT numbers:              165656 milliseconds
Time to get the GCD of 32768 pairs of 512-DIGIT numbers, x-coef only: 156094 milliseconds
Time to get the GCD of 16384 pairs of 1024-DIGIT numbers:              290687 milliseconds
Time to get the GCD of 16384 pairs of 1024-DIGIT numbers, x-coef only: 272938 milliseconds
Time to get the GCD of 8192 pairs of 2048-DIGIT numbers:              568781 milliseconds
Time to get the GCD of 8192 pairs of 2048-DIGIT numbers, x-coef only: 551844 milliseconds
Time to get the GCD of 4096 pairs of 4096-DIGIT numbers:              1095156 milliseconds
Time to get the GCD of 4096 pairs of 4096-DIGIT numbers, x-coef only: 1125734 milliseconds

Time to get the GCD of 16777216 pairs of 2-byte numbers:              9578 milliseconds
Time to get the GCD of 16777216 pairs of 2-byte numbers, x-coef only: 9766 milliseconds
Time to get the GCD of 8388608 pairs of 4-byte numbers:              10422 milliseconds
Time to get the GCD of 8388608 pairs of 4-byte numbers, x-coef only: 10109 milliseconds
Time to get the GCD of 4194304 pairs of 8-byte numbers:              10719 milliseconds
Time to get the GCD of 4194304 pairs of 8-byte numbers, x-coef only: 10766 milliseconds
Time to get the GCD of 2097152 pairs of 16-byte numbers:              12218 milliseconds
Time to get the GCD of 2097152 pairs of 16-byte numbers, x-coef only: 12766 milliseconds
Time to get the GCD of 1048576 pairs of 32-byte numbers:              14656 milliseconds
Time to get the GCD of 1048576 pairs of 32-byte numbers, x-coef only: 14860 milliseconds
Time to get the GCD of 524288 pairs of 64-byte numbers:              19734 milliseconds
Time to get the GCD of 524288 pairs of 64-byte numbers, x-coef only: 21047 milliseconds
Time to get the GCD of 262144 pairs of 128-byte numbers:              29375 milliseconds
Time to get the GCD of 262144 pairs of 128-byte numbers, x-coef only: 31484 milliseconds
Time to get the GCD of 131072 pairs of 256-byte numbers:              48625 milliseconds
Time to get the GCD of 131072 pairs of 256-byte numbers, x-coef only: 50781 milliseconds
Time to get the GCD of 65536 pairs of 512-byte numbers:              95844 milliseconds
Time to get the GCD of 65536 pairs of 512-byte numbers, x-coef only: 89485 milliseconds
Time to get the GCD of 32768 pairs of 1024-byte numbers:              178390 milliseconds
Time to get the GCD of 32768 pairs of 1024-byte numbers, x-coef only: 159906 milliseconds
Time to get the GCD of 16384 pairs of 2048-byte numbers:              330329 milliseconds
Time to get the GCD of 16384 pairs of 2048-byte numbers, x-coef only: 313031 milliseconds
Time to get the GCD of 8192 pairs of 4096-byte numbers:              646500 milliseconds
Time to get the GCD of 8192 pairs of 4096-byte numbers, x-coef only: 578125 milliseconds
Time to get the GCD of 4096 pairs of 8192-byte numbers:              1119937 milliseconds
Time to get the GCD of 4096 pairs of 8192-byte numbers, x-coef only: 1075531 milliseconds

32-bit DIGITS
Time to get the GCD of 16777216 pairs of 1-DIGIT numbers:              17312 milliseconds
Time to get the GCD of 16777216 pairs of 1-DIGIT numbers, x-coef only: 16578 milliseconds
Time to get the GCD of 8388608 pairs of 2-DIGIT numbers:              16703 milliseconds
Time to get the GCD of 8388608 pairs of 2-DIGIT numbers, x-coef only: 16891 milliseconds
Time to get the GCD of 4194304 pairs of 4-DIGIT numbers:              17687 milliseconds
Time to get the GCD of 4194304 pairs of 4-DIGIT numbers, x-coef only: 17532 milliseconds
Time to get the GCD of 2097152 pairs of 8-DIGIT numbers:              19187 milliseconds
Time to get the GCD of 2097152 pairs of 8-DIGIT numbers, x-coef only: 19578 milliseconds
Time to get the GCD of 1048576 pairs of 16-DIGIT numbers:              22688 milliseconds
Time to get the GCD of 1048576 pairs of 16-DIGIT numbers, x-coef only: 23156 milliseconds
Time to get the GCD of 524288 pairs of 32-DIGIT numbers:              30516 milliseconds
Time to get the GCD of 524288 pairs of 32-DIGIT numbers, x-coef only: 30937 milliseconds
Time to get the GCD of 262144 pairs of 64-DIGIT numbers:              47188 milliseconds
Time to get the GCD of 262144 pairs of 64-DIGIT numbers, x-coef only: 46718 milliseconds
Time to get the GCD of 131072 pairs of 128-DIGIT numbers:              82641 milliseconds
Time to get the GCD of 131072 pairs of 128-DIGIT numbers, x-coef only: 78438 milliseconds
Time to get the GCD of 65536 pairs of 256-DIGIT numbers:              148640 milliseconds
Time to get the GCD of 65536 pairs of 256-DIGIT numbers, x-coef only: 139985 milliseconds
Time to get the GCD of 32768 pairs of 512-DIGIT numbers:              277921 milliseconds
Time to get the GCD of 32768 pairs of 512-DIGIT numbers, x-coef only: 270219 milliseconds
Time to get the GCD of 16384 pairs of 1024-DIGIT numbers:              553375 milliseconds
Time to get the GCD of 16384 pairs of 1024-DIGIT numbers, x-coef only: 535594 milliseconds
Time to get the GCD of 8192 pairs of 2048-DIGIT numbers:              1065171 milliseconds
Time to get the GCD of 8192 pairs of 2048-DIGIT numbers, x-coef only: 1022110 milliseconds
Time to get the GCD of 4096 pairs of 4096-DIGIT numbers:              2161219 milliseconds
Time to get the GCD of 4096 pairs of 4096-DIGIT numbers, x-coef only: 2112093 milliseconds

32-bit
Time to get the GCD of 16777216 pairs of 1-DIGIT numbers:              16875 milliseconds
Time to get the GCD of 16777216 pairs of 1-DIGIT numbers, x-coef only: 16516 milliseconds
Time to get the GCD of 8388608 pairs of 2-DIGIT numbers:              17625 milliseconds
Time to get the GCD of 8388608 pairs of 2-DIGIT numbers, x-coef only: 18093 milliseconds
Time to get the GCD of 4194304 pairs of 4-DIGIT numbers:              17672 milliseconds
Time to get the GCD of 4194304 pairs of 4-DIGIT numbers, x-coef only: 17328 milliseconds
Time to get the GCD of 2097152 pairs of 8-DIGIT numbers:              19485 milliseconds
Time to get the GCD of 2097152 pairs of 8-DIGIT numbers, x-coef only: 19078 milliseconds
Time to get the GCD of 1048576 pairs of 16-DIGIT numbers:              22906 milliseconds
Time to get the GCD of 1048576 pairs of 16-DIGIT numbers, x-coef only: 23500 milliseconds
Time to get the GCD of 524288 pairs of 32-DIGIT numbers:              31406 milliseconds
Time to get the GCD of 524288 pairs of 32-DIGIT numbers, x-coef only: 33000 milliseconds
Time to get the GCD of 262144 pairs of 64-DIGIT numbers:              50454 milliseconds
Time to get the GCD of 262144 pairs of 64-DIGIT numbers, x-coef only: 51046 milliseconds
Time to get the GCD of 131072 pairs of 128-DIGIT numbers:              91360 milliseconds
Time to get the GCD of 131072 pairs of 128-DIGIT numbers, x-coef only: 87062 milliseconds
Time to get the GCD of 65536 pairs of 256-DIGIT numbers:              164969 milliseconds
Time to get the GCD of 65536 pairs of 256-DIGIT numbers, x-coef only: 160641 milliseconds
Time to get the GCD of 32768 pairs of 512-DIGIT numbers:              313062 milliseconds
Time to get the GCD of 32768 pairs of 512-DIGIT numbers, x-coef only: 305735 milliseconds
Time to get the GCD of 16384 pairs of 1024-DIGIT numbers:              594406 milliseconds
Time to get the GCD of 16384 pairs of 1024-DIGIT numbers, x-coef only: 587015 milliseconds
Time to get the GCD of 8192 pairs of 2048-DIGIT numbers:              1171313 milliseconds
Time to get the GCD of 8192 pairs of 2048-DIGIT numbers, x-coef only: 1157625 milliseconds
Time to get the GCD of 4096 pairs of 4096-DIGIT numbers:              2314609 milliseconds
Time to get the GCD of 4096 pairs of 4096-DIGIT numbers, x-coef only: 2292703 milliseconds

full breakdown:
32-bit DIGITs
Time to get the GCD of 16777216 pairs of 4-byte numbers:            40250 milliseconds
Total calls to GCD: 16777216
  Time spent in GCD overhead:     586740 microseconds (0.034972 average)
  Time spent in GCD multiplying:  0 microseconds (0.000000 average)
  Time spent in GCD dividing:     32768087 microseconds (1.953130 average)
  Total time spent computing GCD: 33354827 microseconds (1.988103 average)

Time to get the GCD of 16777216 pairs of 4-byte numbers (extended): 63344 milliseconds
Total calls to GCD: 16777216
  Time spent in GCD overhead:     11352240 microseconds (0.676646 average)
  Time spent in GCD multiplying:  10933657 microseconds (0.651697 average)
  Time spent in GCD dividing:     33567644 microseconds (2.000787 average)
  Total time spent computing GCD: 55853541 microseconds (3.329130 average)

Time to get the GCD of 8388608 pairs of 8-byte numbers:            39765 milliseconds
Total calls to GCD: 8388608
  Time spent in GCD overhead:     295724 microseconds (0.035253 average)
  Time spent in GCD multiplying:  0 microseconds (0.000000 average)
  Time spent in GCD dividing:     34599159 microseconds (4.124541 average)
  Total time spent computing GCD: 34894883 microseconds (4.159794 average)

Time to get the GCD of 8388608 pairs of 8-byte numbers (extended): 63953 milliseconds
Total calls to GCD: 8388608
  Time spent in GCD overhead:     11335266 microseconds (1.351269 average)
  Time spent in GCD multiplying:  11597651 microseconds (1.382548 average)
  Time spent in GCD dividing:     35830936 microseconds (4.271380 average)
  Total time spent computing GCD: 58763853 microseconds (7.005197 average)

Time to get the GCD of 4194304 pairs of 16-byte numbers:            39641 milliseconds
Total calls to GCD: 4194304
  Time spent in GCD overhead:     148791 microseconds (0.035475 average)
  Time spent in GCD multiplying:  0 microseconds (0.000000 average)
  Time spent in GCD dividing:     35628893 microseconds (8.494590 average)
  Total time spent computing GCD: 35777684 microseconds (8.530065 average)

Time to get the GCD of 4194304 pairs of 16-byte numbers (extended): 64656 milliseconds
Total calls to GCD: 4194304
  Time spent in GCD overhead:     11414429 microseconds (2.721412 average)
  Time spent in GCD multiplying:  11971731 microseconds (2.854283 average)
  Time spent in GCD dividing:     37191775 microseconds (8.867210 average)
  Total time spent computing GCD: 60577935 microseconds (14.442905 average)

Time to get the GCD of 2097152 pairs of 32-byte numbers:            40390 milliseconds
Total calls to GCD: 2097152
  Time spent in GCD overhead:     76298 microseconds (0.036382 average)
  Time spent in GCD multiplying:  0 microseconds (0.000000 average)
  Time spent in GCD dividing:     36981420 microseconds (17.634115 average)
  Total time spent computing GCD: 37057718 microseconds (17.670498 average)

Time to get the GCD of 2097152 pairs of 32-byte numbers (extended): 66906 milliseconds
Total calls to GCD: 2097152
  Time spent in GCD overhead:     11879099 microseconds (5.664396 average)
  Time spent in GCD multiplying:  12594500 microseconds (6.005526 average)
  Time spent in GCD dividing:     38874382 microseconds (18.536751 average)
  Total time spent computing GCD: 63347981 microseconds (30.206671 average)

Time to get the GCD of 1048576 pairs of 64-byte numbers:            43438 milliseconds
Total calls to GCD: 1048576
  Time spent in GCD overhead:     109554 microseconds (0.104479 average)
  Time spent in GCD multiplying:  0 microseconds (0.000000 average)
  Time spent in GCD dividing:     40109867 microseconds (38.251751 average)
  Total time spent computing GCD: 40219421 microseconds (38.356228 average)

Time to get the GCD of 1048576 pairs of 64-byte numbers (extended): 70500 milliseconds
Total calls to GCD: 1048576
  Time spent in GCD overhead:     12735488 microseconds (12.145508 average)
  Time spent in GCD multiplying:  13533008 microseconds (12.906082 average)
  Time spent in GCD dividing:     41039379 microseconds (39.138203 average)
  Total time spent computing GCD: 67307875 microseconds (64.189789 average)

Time to get the GCD of 524288 pairs of 128-byte numbers:            46515 milliseconds
Total calls to GCD: 524288
  Time spent in GCD overhead:     58547 microseconds (0.111670 average)
  Time spent in GCD multiplying:  0 microseconds (0.000000 average)
  Time spent in GCD dividing:     43458807 microseconds (82.891098 average)
  Total time spent computing GCD: 43517354 microseconds (83.002762 average)

Time to get the GCD of 524288 pairs of 128-byte numbers (extended): 79672 milliseconds
Total calls to GCD: 524288
  Time spent in GCD overhead:     14674189 microseconds (27.988794 average)
  Time spent in GCD multiplying:  16064063 microseconds (30.639769 average)
  Time spent in GCD dividing:     45805895 microseconds (87.367813 average)
  Total time spent computing GCD: 76544147 microseconds (145.996368 average)

Time to get the GCD of 262144 pairs of 256-byte numbers:            55578 milliseconds
Total calls to GCD: 262144
  Time spent in GCD overhead:     33538 microseconds (0.127937 average)
  Time spent in GCD multiplying:  0 microseconds (0.000000 average)
  Time spent in GCD dividing:     52525697 microseconds (200.369629 average)
  Total time spent computing GCD: 52559235 microseconds (200.497574 average)

Time to get the GCD of 262144 pairs of 256-byte numbers (extended): 100718 milliseconds
Total calls to GCD: 262144
  Time spent in GCD overhead:     19408607 microseconds (74.037964 average)
  Time spent in GCD multiplying:  22640548 microseconds (86.366837 average)
  Time spent in GCD dividing:     55490298 microseconds (211.678680 average)
  Total time spent computing GCD: 97539453 microseconds (372.083496 average)

Time to get the GCD of 131072 pairs of 512-byte numbers:            71813 milliseconds
Total calls to GCD: 131072
  Time spent in GCD overhead:     19169 microseconds (0.146248 average)
  Time spent in GCD multiplying:  0 microseconds (0.000000 average)
  Time spent in GCD dividing:     68895667 microseconds (525.632202 average)
  Total time spent computing GCD: 68914836 microseconds (525.778442 average)

Time to get the GCD of 131072 pairs of 512-byte numbers (extended): 144921 milliseconds
Total calls to GCD: 131072
  Time spent in GCD overhead:     28121295 microseconds (214.548462 average)
  Time spent in GCD multiplying:  43828196 microseconds (334.382599 average)
  Time spent in GCD dividing:     70165168 microseconds (535.317749 average)
  Total time spent computing GCD: 142114659 microseconds (1084.248779 average)

Time to get the GCD of 65536 pairs of 1024-byte numbers:            101453 milliseconds
Total calls to GCD: 65536
  Time spent in GCD overhead:     14482 microseconds (0.220978 average)
  Time spent in GCD multiplying:  0 microseconds (0.000000 average)
  Time spent in GCD dividing:     98589136 microseconds (1504.350830 average)
  Total time spent computing GCD: 98603618 microseconds (1504.571777 average)

Time to get the GCD of 65536 pairs of 1024-byte numbers (extended): 218844 milliseconds
Total calls to GCD: 65536
  Time spent in GCD overhead:     45336571 microseconds (691.781189 average)
  Time spent in GCD multiplying:  67628499 microseconds (1031.928955 average)
  Time spent in GCD dividing:     103018601 microseconds (1571.939087 average)
  Total time spent computing GCD: 215983671 microseconds (3295.649170 average)

Time to get the GCD of 32768 pairs of 2048-byte numbers:            161578 milliseconds
Total calls to GCD: 32768
  Time spent in GCD overhead:     10611 microseconds (0.323822 average)
  Time spent in GCD multiplying:  0 microseconds (0.000000 average)
  Time spent in GCD dividing:     158823357 microseconds (4846.904297 average)
  Total time spent computing GCD: 158833968 microseconds (4847.228027 average)

Time to get the GCD of 32768 pairs of 2048-byte numbers (extended): 359781 milliseconds
Total calls to GCD: 32768
  Time spent in GCD overhead:     78566667 microseconds (2397.664307 average)
  Time spent in GCD multiplying:  112917975 microseconds (3445.983154 average)
  Time spent in GCD dividing:     165546526 microseconds (5052.079102 average)
  Total time spent computing GCD: 357031168 microseconds (10895.726562 average)

Time to get the GCD of 16384 pairs of 4096-byte numbers:            285422 milliseconds
Total calls to GCD: 16384
  Time spent in GCD overhead:     10384 microseconds (0.633789 average)
  Time spent in GCD multiplying:  0 microseconds (0.000000 average)
  Time spent in GCD dividing:     282681896 microseconds (17253.533203 average)
  Total time spent computing GCD: 282692280 microseconds (17254.167969 average)

Time to get the GCD of 16384 pairs of 4096-byte numbers (extended): 643266 milliseconds
Total calls to GCD: 16384
  Time spent in GCD overhead:     145986573 microseconds (8910.313477 average)
  Time spent in GCD multiplying:  203870024 microseconds (12443.238281 average)
  Time spent in GCD dividing:     290705421 microseconds (17743.250000 average)
  Total time spent computing GCD: 640562018 microseconds (39096.804688 average)

Time to get the GCD of 8192 pairs of 8192-byte numbers:            531844 milliseconds
Total calls to GCD: 8192
  Time spent in GCD overhead:     9160 microseconds (1.118164 average)
  Time spent in GCD multiplying:  0 microseconds (0.000000 average)
  Time spent in GCD dividing:     529175797 microseconds (64596.656250 average)
  Total time spent computing GCD: 529184957 microseconds (64597.773438 average)

Time to get the GCD of 8192 pairs of 8192-byte numbers (extended): 1277781 milliseconds
Total calls to GCD: 8192
  Time spent in GCD overhead:     296115011 microseconds (36146.851562 average)
  Time spent in GCD multiplying:  408217378 microseconds (49831.222656 average)
  Time spent in GCD dividing:     570548993 microseconds (69647.093750 average)
  Total time spent computing GCD: 1274881382 microseconds (155625.171875 average)

Time to get the GCD of 4096 pairs of 16384-byte numbers:            1064328 milliseconds
Total calls to GCD: 4096
  Time spent in GCD overhead:     9516 microseconds (2.323242 average)
  Time spent in GCD multiplying:  0 microseconds (0.000000 average)
  Time spent in GCD dividing:     1061520049 microseconds (259160.171875 average)
  Total time spent computing GCD: 1061529565 microseconds (259162.484375 average)

Time to get the GCD of 4096 pairs of 16384-byte numbers (extended): 2499171 milliseconds
Total calls to GCD: 4096
  Time spent in GCD overhead:     580035457 microseconds (141610.218750 average)
  Time spent in GCD multiplying:  790131752 microseconds (192903.265625 average)
  Time spent in GCD dividing:     1126125468 microseconds (274932.968750 average)
  Total time spent computing GCD: 2496292677 microseconds (609446.437500 average)
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

    printf("If you're not doing this with a retail build, you're not getting good numbers.  All sizes in BYTES, not DIGITs!\n");
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
Nutshell: Montgomery is faster except for very small sizes: 32-bit DIGITs (I think -- better redo)
Time to do 16777216  standard  power-modulus operations of size 16 bits: 11500 milliseconds
Time to do 16777216 Montgomery power-modulus operations of size 16 bits: 15547 milliseconds
Time to do 4194304  standard  power-modulus operations of size 32 bits: 19125 milliseconds
Time to do 4194304 Montgomery power-modulus operations of size 32 bits: 16719 milliseconds
Time to do 1048576  standard  power-modulus operations of size 64 bits: 12359 milliseconds
Time to do 1048576 Montgomery power-modulus operations of size 64 bits: 8188 milliseconds
Time to do 262144  standard  power-modulus operations of size 128 bits: 10031 milliseconds
Time to do 262144 Montgomery power-modulus operations of size 128 bits: 5281 milliseconds
Time to do 65536  standard  power-modulus operations of size 256 bits: 11797 milliseconds
Time to do 65536 Montgomery power-modulus operations of size 256 bits: 7109 milliseconds
Time to do 16384  standard  power-modulus operations of size 512 bits: 18500 milliseconds
Time to do 16384 Montgomery power-modulus operations of size 512 bits: 11282 milliseconds
Time to do 4096  standard  power-modulus operations of size 1024 bits: 24375 milliseconds
Time to do 4096 Montgomery power-modulus operations of size 1024 bits: 17312 milliseconds
Time to do 1024  standard  power-modulus operations of size 2048 bits: 41984 milliseconds
Time to do 1024 Montgomery power-modulus operations of size 2048 bits: 27313 milliseconds
Time to do 256  standard  power-modulus operations of size 4096 bits: 60703 milliseconds
Time to do 256 Montgomery power-modulus operations of size 4096 bits: 36031 milliseconds
Time to do 64  standard  power-modulus operations of size 8192 bits: 95547 milliseconds
Time to do 64 Montgomery power-modulus operations of size 8192 bits: 53047 milliseconds
Time to do 16  standard  power-modulus operations of size 16384 bits: 130094 milliseconds
Time to do 16 Montgomery power-modulus operations of size 16384 bits: 68281 milliseconds
Time to do 4  standard  power-modulus operations of size 32768 bits: 199469 milliseconds
Time to do 4 Montgomery power-modulus operations of size 32768 bits: 95593 milliseconds
Time to do 1  standard  power-modulus operations of size 65536 bits: 283000 milliseconds
Time to do 1 Montgomery power-modulus operations of size 65536 bits: 129125 milliseconds

Full breakdown:
32-bit DIGITs
Time to do 16777216  standard  power-modulus operations of size 16 bits: 61672 milliseconds
Total calls to power modulus:  16777216
  Time spent in Power Modulus overhead:     9633696 microseconds (0.574213 average)
  Time spent in Power Modulus multiplying:  13537726 microseconds (0.806911 average)
  Time spent in Power Modulus dividing:     37907652 microseconds (2.259472 average)
  Total time spent computing Power Modulus: 61079074 microseconds (3.640596 average)

Time to do 16777216 Montgomery power-modulus operations of size 16 bits: 60594 milliseconds
Total calls to power modulus:  16777216
  Time spent in Power Modulus overhead:     12794795 microseconds (0.762629 average)
  Time spent in Power Modulus multiplying:  44354765 microseconds (2.643750 average)
  Time spent in Power Modulus dividing:     1847680 microseconds (0.110130 average)
  Total time spent computing Power Modulus: 59786060 microseconds (3.563527 average)

Time to do 4194304  standard  power-modulus operations of size 32 bits: 76203 milliseconds
Total calls to power modulus:  4194304
  Time spent in Power Modulus overhead:     9658012 microseconds (2.302649 average)
  Time spent in Power Modulus multiplying:  13661523 microseconds (3.257161 average)
  Time spent in Power Modulus dividing:     52734182 microseconds (12.572809 average)
  Total time spent computing Power Modulus: 76053717 microseconds (18.132620 average)

Time to do 4194304 Montgomery power-modulus operations of size 32 bits: 56125 milliseconds
Total calls to power modulus:  4194304
  Time spent in Power Modulus overhead:     13040359 microseconds (3.109064 average)
  Time spent in Power Modulus multiplying:  42090140 microseconds (10.035071 average)
  Time spent in Power Modulus dividing:     596811 microseconds (0.142291 average)
  Total time spent computing Power Modulus: 55932908 microseconds (13.335444 average)

Time to do 1048576  standard  power-modulus operations of size 64 bits: 33453 milliseconds
Total calls to power modulus:  1048576
  Time spent in Power Modulus overhead:     3565212 microseconds (3.400051 average)
  Time spent in Power Modulus multiplying:  5690575 microseconds (5.426955 average)
  Time spent in Power Modulus dividing:     24164889 microseconds (23.045433 average)
  Total time spent computing Power Modulus: 33420676 microseconds (31.872440 average)

Time to do 1048576 Montgomery power-modulus operations of size 64 bits: 22735 milliseconds
Total calls to power modulus:  1048576
  Time spent in Power Modulus overhead:     5029507 microseconds (4.796512 average)
  Time spent in Power Modulus multiplying:  17393806 microseconds (16.588026 average)
  Time spent in Power Modulus dividing:     203461 microseconds (0.194036 average)
  Total time spent computing Power Modulus: 22682769 microseconds (21.631973 average)

Time to do 262144  standard  power-modulus operations of size 128 bits: 16593 milliseconds
Total calls to power modulus:  262144
  Time spent in Power Modulus overhead:     1486352 microseconds (5.669983 average)
  Time spent in Power Modulus multiplying:  3154816 microseconds (12.034668 average)
  Time spent in Power Modulus dividing:     11941179 microseconds (45.551983 average)
  Total time spent computing Power Modulus: 16582347 microseconds (63.256634 average)

Time to do 262144 Montgomery power-modulus operations of size 128 bits: 11953 milliseconds
Total calls to power modulus:  262144
  Time spent in Power Modulus overhead:     2401483 microseconds (9.160931 average)
  Time spent in Power Modulus multiplying:  9471907 microseconds (36.132458 average)
  Time spent in Power Modulus dividing:     50246 microseconds (0.191673 average)
  Total time spent computing Power Modulus: 11941415 microseconds (45.552883 average)

Time to do 65536  standard  power-modulus operations of size 256 bits: 17578 milliseconds
Total calls to power modulus:  65536
  Time spent in Power Modulus overhead:     747028 microseconds (11.398743 average)
  Time spent in Power Modulus multiplying:  3105797 microseconds (47.390701 average)
  Time spent in Power Modulus dividing:     13723222 microseconds (209.399750 average)
  Total time spent computing Power Modulus: 17576047 microseconds (268.189209 average)

Time to do 65536 Montgomery power-modulus operations of size 256 bits: 10860 milliseconds
Total calls to power modulus:  65536
  Time spent in Power Modulus overhead:     1337045 microseconds (20.401688 average)
  Time spent in Power Modulus multiplying:  9474777 microseconds (144.573624 average)
  Time spent in Power Modulus dividing:     34440 microseconds (0.525513 average)
  Total time spent computing Power Modulus: 10855374 microseconds (165.639862 average)

Time to do 16384  standard  power-modulus operations of size 512 bits: 23031 milliseconds
Total calls to power modulus:  16384
  Time spent in Power Modulus overhead:     395852 microseconds (24.160889 average)
  Time spent in Power Modulus multiplying:  3833705 microseconds (233.990784 average)
  Time spent in Power Modulus dividing:     18791697 microseconds (1146.954102 average)
  Total time spent computing Power Modulus: 23021254 microseconds (1405.105835 average)

Time to do 16384 Montgomery power-modulus operations of size 512 bits: 11203 milliseconds
Total calls to power modulus:  16384
  Time spent in Power Modulus overhead:     814690 microseconds (49.724731 average)
  Time spent in Power Modulus multiplying:  10356785 microseconds (632.127991 average)
  Time spent in Power Modulus dividing:     22670 microseconds (1.383667 average)
  Total time spent computing Power Modulus: 11199371 microseconds (683.555359 average)

Time to do 4096  standard  power-modulus operations of size 1024 bits: 31375 milliseconds
Total calls to power modulus:  4096
  Time spent in Power Modulus overhead:     168010 microseconds (41.018066 average)
  Time spent in Power Modulus multiplying:  4724990 microseconds (1153.562012 average)
  Time spent in Power Modulus dividing:     26482000 microseconds (6465.332031 average)
  Total time spent computing Power Modulus: 31375000 microseconds (7659.912109 average)

Time to do 4096 Montgomery power-modulus operations of size 1024 bits: 14672 milliseconds
Total calls to power modulus:  4096
  Time spent in Power Modulus overhead:     530666 microseconds (129.557129 average)
  Time spent in Power Modulus multiplying:  14117008 microseconds (3446.535156 average)
  Time spent in Power Modulus dividing:     18010 microseconds (4.396973 average)
  Total time spent computing Power Modulus: 14669088 microseconds (3581.320312 average)

Time to do 1024  standard  power-modulus operations of size 2048 bits: 41765 milliseconds
Total calls to power modulus:  1024
  Time spent in Power Modulus overhead:     99735 microseconds (97.397461 average)
  Time spent in Power Modulus multiplying:  7907033 microseconds (7721.711914 average)
  Time spent in Power Modulus dividing:     33748474 microseconds (32957.492188 average)
  Total time spent computing Power Modulus: 41755242 microseconds (40776.601562 average)

Time to do 1024 Montgomery power-modulus operations of size 2048 bits: 25938 milliseconds
Total calls to power modulus:  1024
  Time spent in Power Modulus overhead:     447650 microseconds (437.158203 average)
  Time spent in Power Modulus multiplying:  25467410 microseconds (24870.517578 average)
  Time spent in Power Modulus dividing:     12565 microseconds (12.270508 average)
  Total time spent computing Power Modulus: 25930588 microseconds (25322.839844 average)

Time to do 256  standard  power-modulus operations of size 4096 bits: 61766 milliseconds
Total calls to power modulus:  256
  Time spent in Power Modulus overhead:     89936 microseconds (351.312500 average)
  Time spent in Power Modulus multiplying:  13271375 microseconds (51841.308594 average)
  Time spent in Power Modulus dividing:     48409699 microseconds (189100.390625 average)
  Total time spent computing Power Modulus: 61771010 microseconds (241293.000000 average)

Time to do 256 Montgomery power-modulus operations of size 4096 bits: 39578 milliseconds
Total calls to power modulus:  256
  Time spent in Power Modulus overhead:     447325 microseconds (1747.363281 average)
  Time spent in Power Modulus multiplying:  39121535 microseconds (152818.500000 average)
  Time spent in Power Modulus dividing:     8274 microseconds (32.320312 average)
  Total time spent computing Power Modulus: 39579285 microseconds (154606.578125 average)

Time to do 64  standard  power-modulus operations of size 8192 bits: 77125 milliseconds
Total calls to power modulus:  64
  Time spent in Power Modulus overhead:     68129 microseconds (1064.515625 average)
  Time spent in Power Modulus multiplying:  17786810 microseconds (277918.906250 average)
  Time spent in Power Modulus dividing:     59267649 microseconds (926057.000000 average)
  Total time spent computing Power Modulus: 77122588 microseconds (1205040.500000 average)

Time to do 64 Montgomery power-modulus operations of size 8192 bits: 55766 milliseconds
Total calls to power modulus:  64
  Time spent in Power Modulus overhead:     411532 microseconds (6430.187500 average)
  Time spent in Power Modulus multiplying:  55351492 microseconds (864867.062500 average)
  Time spent in Power Modulus dividing:     4798 microseconds (74.968750 average)
  Total time spent computing Power Modulus: 55769395 microseconds (871396.812500 average)

Time to do 16  standard  power-modulus operations of size 16384 bits: 111234 milliseconds
Total calls to power modulus:  16
  Time spent in Power Modulus overhead:     50608 microseconds (3163.000000 average)
  Time spent in Power Modulus multiplying:  25693727 microseconds (1605858.000000 average)
  Time spent in Power Modulus dividing:     85497190 microseconds (5343574.500000 average)
  Total time spent computing Power Modulus: 111241525 microseconds (6952595.500000 average)

Time to do 16 Montgomery power-modulus operations of size 16384 bits: 74218 milliseconds
Total calls to power modulus:  16
  Time spent in Power Modulus overhead:     393161 microseconds (24572.562500 average)
  Time spent in Power Modulus multiplying:  73826097 microseconds (4614131.000000 average)
  Time spent in Power Modulus dividing:     3285 microseconds (205.312500 average)
  Total time spent computing Power Modulus: 74223615 microseconds (4638976.000000 average)

Time to do 4  standard  power-modulus operations of size 32768 bits: 143641 milliseconds
Total calls to power modulus:  4
  Time spent in Power Modulus overhead:     37797 microseconds (9449.250000 average)
  Time spent in Power Modulus multiplying:  34061304 microseconds (8515326.000000 average)
  Time spent in Power Modulus dividing:     109539731 microseconds (27384932.000000 average)
  Total time spent computing Power Modulus: 143638832 microseconds (35909708.000000 average)

Time to do 4 Montgomery power-modulus operations of size 32768 bits: 104188 milliseconds
Total calls to power modulus:  4
  Time spent in Power Modulus overhead:     377773 microseconds (94443.250000 average)
  Time spent in Power Modulus multiplying:  103803119 microseconds (25950780.000000 average)
  Time spent in Power Modulus dividing:     2390 microseconds (597.500000 average)
  Total time spent computing Power Modulus: 104184160 microseconds (26046040.000000 average)

Time to do 1  standard  power-modulus operations of size 65536 bits: 181656 milliseconds
Total calls to power modulus:  1
  Time spent in Power Modulus overhead:     22416 microseconds (22416.000000 average)
  Time spent in Power Modulus multiplying:  42071862 microseconds (42071864.000000 average)
  Time spent in Power Modulus dividing:     139557699 microseconds (139557696.000000 average)
  Total time spent computing Power Modulus: 181651977 microseconds (181651984.000000 average)

Time to do 1 Montgomery power-modulus operations of size 65536 bits: 120469 milliseconds
Total calls to power modulus:  1
  Time spent in Power Modulus overhead:     344035 microseconds (344035.000000 average)
  Time spent in Power Modulus multiplying:  120116895 microseconds (120116896.000000 average)
  Time spent in Power Modulus dividing:     2213 microseconds (2213.000000 average)
  Total time spent computing Power Modulus: 120463520 microseconds (120463520.000000 average)
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
* small DIGITs (16-bit DIGITs)
* Time to do 8388608 square roots of a 16 bit number (Newton):                  78 milliseconds (0.000009 average)
Time to do 8388608 square roots of a 16 bit number using general Newton:      765 milliseconds (0.000091 average)
Time to do 8388608 square roots of a 16 bit number using recursive algorithm: 78 milliseconds (0.000009 average)
Time to do 8388608 divides of a 16 bit number by its square root:             266 milliseconds (0.000032 average)
Time to do 8388608 general roots of a 10, 16 bit numbers: Newton:             984 milliseconds (0.000117 average)
Time to do 8388608 general roots of a 10, 16 bit numbers: Recursive:          1016 milliseconds (0.000121 average)
Time to do 4194304 square roots of a 32 bit number (Newton):                  16 milliseconds (0.000004 average)
Time to do 4194304 square roots of a 32 bit number using general Newton:      1031 milliseconds (0.000246 average)
Time to do 4194304 square roots of a 32 bit number using recursive algorithm: 31 milliseconds (0.000007 average)
Time to do 4194304 divides of a 32 bit number by its square root:             110 milliseconds (0.000026 average)
Time to do 4194304 general roots of a 21, 32 bit numbers: Newton:             906 milliseconds (0.000216 average)
Time to do 4194304 general roots of a 21, 32 bit numbers: Recursive:          1031 milliseconds (0.000246 average)
Time to do 2097152 square roots of a 48 bit number (Newton):                  391 milliseconds (0.000186 average)
Time to do 2097152 square roots of a 48 bit number using general Newton:      625 milliseconds (0.000298 average)
Time to do 2097152 square roots of a 48 bit number using recursive algorithm: 375 milliseconds (0.000179 average)
Time to do 2097152 divides of a 48 bit number by its square root:             125 milliseconds (0.000060 average)
Time to do 2097152 general roots of a 32, 48 bit numbers: Newton:             484 milliseconds (0.000231 average)
Time to do 2097152 general roots of a 32, 48 bit numbers: Recursive:          328 milliseconds (0.000156 average)
Time to do 1048576 square roots of a 64 bit number (Newton):                  187 milliseconds (0.000178 average)
Time to do 1048576 square roots of a 64 bit number using general Newton:      328 milliseconds (0.000313 average)
Time to do 1048576 square roots of a 64 bit number using recursive algorithm: 235 milliseconds (0.000224 average)
Time to do 1048576 divides of a 64 bit number by its square root:             47 milliseconds (0.000045 average)
Time to do 1048576 general roots of a 42, 64 bit numbers: Newton:             312 milliseconds (0.000298 average)
Time to do 1048576 general roots of a 42, 64 bit numbers: Recursive:          188 milliseconds (0.000179 average)
Time to do 524288 square roots of a 128 bit number (Newton):                  297 milliseconds (0.000566 average)
Time to do 524288 square roots of a 128 bit number using general Newton:      468 milliseconds (0.000893 average)
Time to do 524288 square roots of a 128 bit number using recursive algorithm: 203 milliseconds (0.000387 average)
Time to do 524288 divides of a 128 bit number by its square root:             63 milliseconds (0.000120 average)
Time to do 524288 general roots of a 85, 128 bit numbers: Newton:             234 milliseconds (0.000446 average)
Time to do 524288 general roots of a 85, 128 bit numbers: Recursive:          172 milliseconds (0.000328 average)
Time to do 262144 square roots of a 256 bit number (Newton):                  563 milliseconds (0.002148 average)
Time to do 262144 square roots of a 256 bit number using general Newton:      656 milliseconds (0.002502 average)
Time to do 262144 square roots of a 256 bit number using recursive algorithm: 156 milliseconds (0.000595 average)
Time to do 262144 divides of a 256 bit number by its square root:             94 milliseconds (0.000359 average)
Time to do 262144 general roots of a 170, 256 bit numbers: Newton:             391 milliseconds (0.001492 average)
Time to do 262144 general roots of a 170, 256 bit numbers: Recursive:          109 milliseconds (0.000416 average)
Time to do 131072 square roots of a 512 bit number (Newton):                  922 milliseconds (0.007034 average)
Time to do 131072 square roots of a 512 bit number using general Newton:      1422 milliseconds (0.010849 average)
Time to do 131072 square roots of a 512 bit number using recursive algorithm: 140 milliseconds (0.001068 average)
Time to do 131072 divides of a 512 bit number by its square root:             157 milliseconds (0.001198 average)
Time to do 131072 general roots of a 341, 512 bit numbers: Newton:             562 milliseconds (0.004288 average)
Time to do 131072 general roots of a 341, 512 bit numbers: Recursive:          125 milliseconds (0.000954 average)
Time to do 65536 square roots of a 1024 bit number (Newton):                  1094 milliseconds (0.016693 average)
Time to do 65536 square roots of a 1024 bit number using general Newton:      1781 milliseconds (0.027176 average)
Time to do 65536 square roots of a 1024 bit number using recursive algorithm: 203 milliseconds (0.003098 average)
Time to do 65536 divides of a 1024 bit number by its square root:             141 milliseconds (0.002151 average)
Time to do 65536 general roots of a 682, 1024 bit numbers: Newton:             687 milliseconds (0.010483 average)
Time to do 65536 general roots of a 682, 1024 bit numbers: Recursive:          188 milliseconds (0.002869 average)
Time to do 32768 square roots of a 2048 bit number (Newton):                  1640 milliseconds (0.050049 average)
Time to do 32768 square roots of a 2048 bit number using general Newton:      3032 milliseconds (0.092529 average)
Time to do 32768 square roots of a 2048 bit number using recursive algorithm: 281 milliseconds (0.008575 average)
Time to do 32768 divides of a 2048 bit number by its square root:             187 milliseconds (0.005707 average)
Time to do 32768 general roots of a 1365, 2048 bit numbers: Newton:             1000 milliseconds (0.030518 average)
Time to do 32768 general roots of a 1365, 2048 bit numbers: Recursive:          219 milliseconds (0.006683 average)
Time to do 16384 square roots of a 4096 bit number (Newton):                  3156 milliseconds (0.192627 average)
Time to do 16384 square roots of a 4096 bit number using general Newton:      5360 milliseconds (0.327148 average)
Time to do 16384 square roots of a 4096 bit number using recursive algorithm: 328 milliseconds (0.020020 average)
Time to do 16384 divides of a 4096 bit number by its square root:             297 milliseconds (0.018127 average)
Time to do 16384 general roots of a 2730, 4096 bit numbers: Newton:             1454 milliseconds (0.088745 average)
Time to do 16384 general roots of a 2730, 4096 bit numbers: Recursive:          265 milliseconds (0.016174 average)
Time to do 8192 square roots of a 8192 bit number (Newton):                  4500 milliseconds (0.549316 average)
Time to do 8192 square roots of a 8192 bit number using general Newton:      7422 milliseconds (0.906006 average)
Time to do 8192 square roots of a 8192 bit number using recursive algorithm: 453 milliseconds (0.055298 average)
Time to do 8192 divides of a 8192 bit number by its square root:             438 milliseconds (0.053467 average)
Time to do 8192 general roots of a 5461, 8192 bit numbers: Newton:             1968 milliseconds (0.240234 average)
Time to do 8192 general roots of a 5461, 8192 bit numbers: Recursive:          438 milliseconds (0.053467 average)
Time to do 4096 square roots of a 16384 bit number (Newton):                  7812 milliseconds (1.907227 average)
Time to do 4096 square roots of a 16384 bit number using general Newton:      11782 milliseconds (2.876465 average)
Time to do 4096 square roots of a 16384 bit number using recursive algorithm: 625 milliseconds (0.152588 average)
Time to do 4096 divides of a 16384 bit number by its square root:             640 milliseconds (0.156250 average)
Time to do 4096 general roots of a 10922, 16384 bit numbers: Newton:             2657 milliseconds (0.648682 average)
Time to do 4096 general roots of a 10922, 16384 bit numbers: Recursive:          593 milliseconds (0.144775 average)
Time to do 2048 square roots of a 32768 bit number (Newton):                  12594 milliseconds (6.149414 average)
Time to do 2048 square roots of a 32768 bit number using general Newton:      17656 milliseconds (8.621094 average)
Time to do 2048 square roots of a 32768 bit number using recursive algorithm: 922 milliseconds (0.450195 average)
Time to do 2048 divides of a 32768 bit number by its square root:             906 milliseconds (0.442383 average)
Time to do 2048 general roots of a 21845, 32768 bit numbers: Newton:             3891 milliseconds (1.899902 average)
Time to do 2048 general roots of a 21845, 32768 bit numbers: Recursive:          828 milliseconds (0.404297 average)
Time to do 1024 square roots of a 65536 bit number (Newton):                  16094 milliseconds (15.716797 average)
Time to do 1024 square roots of a 65536 bit number using general Newton:      24344 milliseconds (23.773438 average)
Time to do 1024 square roots of a 65536 bit number using recursive algorithm: 1234 milliseconds (1.205078 average)
Time to do 1024 divides of a 65536 bit number by its square root:             1250 milliseconds (1.220703 average)
Time to do 1024 general roots of a 43690, 65536 bit numbers: Newton:             4969 milliseconds (4.852539 average)
Time to do 1024 general roots of a 43690, 65536 bit numbers: Recursive:          1063 milliseconds (1.038086 average)
Time to do 512 square roots of a 131072 bit number (Newton):                  28218 milliseconds (55.113281 average)
Time to do 512 square roots of a 131072 bit number using general Newton:      39610 milliseconds (77.363281 average)
Time to do 512 square roots of a 131072 bit number using recursive algorithm: 1750 milliseconds (3.417969 average)
Time to do 512 divides of a 131072 bit number by its square root:             1750 milliseconds (3.417969 average)
Time to do 512 general roots of a 87381, 131072 bit numbers: Newton:             6953 milliseconds (13.580078 average)
Time to do 512 general roots of a 87381, 131072 bit numbers: Recursive:          1469 milliseconds (2.869141 average)
Time to do 256 square roots of a 262144 bit number (Newton):                  36656 milliseconds (143.187500 average)
Time to do 256 square roots of a 262144 bit number using general Newton:      62406 milliseconds (243.773438 average)
Time to do 256 square roots of a 262144 bit number using recursive algorithm: 2438 milliseconds (9.523438 average)
Time to do 256 divides of a 262144 bit number by its square root:             2578 milliseconds (10.070312 average)
Time to do 256 general roots of a 174762, 262144 bit numbers: Newton:             9390 milliseconds (36.679688 average)
Time to do 256 general roots of a 174762, 262144 bit numbers: Recursive:          2016 milliseconds (7.875000 average)
Time to do 128 square roots of a 524288 bit number (Newton):                  72734 milliseconds (568.234375 average)
Time to do 128 square roots of a 524288 bit number using general Newton:      93391 milliseconds (729.617188 average)
Time to do 128 square roots of a 524288 bit number using recursive algorithm: 3562 milliseconds (27.828125 average)
Time to do 128 divides of a 524288 bit number by its square root:             3672 milliseconds (28.687500 average)
Time to do 128 general roots of a 349525, 524288 bit numbers: Newton:             12313 milliseconds (96.195312 average)
Time to do 128 general roots of a 349525, 524288 bit numbers: Recursive:          2797 milliseconds (21.851562 average)
And the time to do a single 33554432 bit square root using the full algorithm: 8500 milliseconds
Simple Newton:                                                                 180437 milliseconds
General recursive (half-size x1):                                              9390 milliseconds
General recursive (two thirds-size x1):                                        4234 milliseconds
General recursive (one third-size x1):                                         8625 milliseconds
And, for comparison, squaring that square root again:                          1015 milliseconds
And to divide that large number by its square root:                            7610 milliseconds

Time to do 8388608 square roots of a 16 bit number (Newton):                  31 milliseconds (0.000004 average)
Time to do 8388608 square roots of a 16 bit number using general Newton:      937 milliseconds (0.000112 average)
Time to do 8388608 square roots of a 16 bit number using recursive algorithm: 63 milliseconds (0.000008 average)
Time to do 8388608 divides of a 16 bit number by its square root:             234 milliseconds (0.000028 average)
Time to do 8388608 general roots of a 10, 16 bit numbers: Newton:             969 milliseconds (0.000116 average)
Time to do 8388608 general roots of a 10, 16 bit numbers: Recursive:          1125 milliseconds (0.000134 average)
Time to do 4194304 square roots of a 32 bit number (Newton):                  16 milliseconds (0.000004 average)
Time to do 4194304 square roots of a 32 bit number using general Newton:      1015 milliseconds (0.000242 average)
Time to do 4194304 square roots of a 32 bit number using recursive algorithm: 32 milliseconds (0.000008 average)
Time to do 4194304 divides of a 32 bit number by its square root:             140 milliseconds (0.000033 average)
Time to do 4194304 general roots of a 21, 32 bit numbers: Newton:             844 milliseconds (0.000201 average)
Time to do 4194304 general roots of a 21, 32 bit numbers: Recursive:          953 milliseconds (0.000227 average)
Time to do 2097152 square roots of a 48 bit number (Newton):                  578 milliseconds (0.000276 average)
Time to do 2097152 square roots of a 48 bit number using general Newton:      828 milliseconds (0.000395 average)
Time to do 2097152 square roots of a 48 bit number using recursive algorithm: 360 milliseconds (0.000172 average)
Time to do 2097152 divides of a 48 bit number by its square root:             140 milliseconds (0.000067 average)
Time to do 2097152 general roots of a 32, 48 bit numbers: Newton:             500 milliseconds (0.000238 average)
Time to do 2097152 general roots of a 32, 48 bit numbers: Recursive:          360 milliseconds (0.000172 average)
Time to do 1048576 square roots of a 64 bit number (Newton):                  250 milliseconds (0.000238 average)
Time to do 1048576 square roots of a 64 bit number using general Newton:      359 milliseconds (0.000342 average)
Time to do 1048576 square roots of a 64 bit number using recursive algorithm: 156 milliseconds (0.000149 average)
Time to do 1048576 divides of a 64 bit number by its square root:             63 milliseconds (0.000060 average)
Time to do 1048576 general roots of a 42, 64 bit numbers: Newton:             344 milliseconds (0.000328 average)
Time to do 1048576 general roots of a 42, 64 bit numbers: Recursive:          250 milliseconds (0.000238 average)
Time to do 524288 square roots of a 128 bit number (Newton):                  484 milliseconds (0.000923 average)
Time to do 524288 square roots of a 128 bit number using general Newton:      516 milliseconds (0.000984 average)
Time to do 524288 square roots of a 128 bit number using recursive algorithm: 203 milliseconds (0.000387 average)
Time to do 524288 divides of a 128 bit number by its square root:             62 milliseconds (0.000118 average)
Time to do 524288 general roots of a 85, 128 bit numbers: Newton:             281 milliseconds (0.000536 average)
Time to do 524288 general roots of a 85, 128 bit numbers: Recursive:          125 milliseconds (0.000238 average)
Time to do 262144 square roots of a 256 bit number (Newton):                  515 milliseconds (0.001965 average)
Time to do 262144 square roots of a 256 bit number using general Newton:      735 milliseconds (0.002804 average)
Time to do 262144 square roots of a 256 bit number using recursive algorithm: 172 milliseconds (0.000656 average)
Time to do 262144 divides of a 256 bit number by its square root:             93 milliseconds (0.000355 average)
Time to do 262144 general roots of a 170, 256 bit numbers: Newton:             422 milliseconds (0.001610 average)
Time to do 262144 general roots of a 170, 256 bit numbers: Recursive:          141 milliseconds (0.000538 average)
Time to do 131072 square roots of a 512 bit number (Newton):                  703 milliseconds (0.005363 average)
Time to do 131072 square roots of a 512 bit number using general Newton:      1297 milliseconds (0.009895 average)
Time to do 131072 square roots of a 512 bit number using recursive algorithm: 172 milliseconds (0.001312 average)
Time to do 131072 divides of a 512 bit number by its square root:             93 milliseconds (0.000710 average)
Time to do 131072 general roots of a 341, 512 bit numbers: Newton:             594 milliseconds (0.004532 average)
Time to do 131072 general roots of a 341, 512 bit numbers: Recursive:          172 milliseconds (0.001312 average)
Time to do 65536 square roots of a 1024 bit number (Newton):                  1469 milliseconds (0.022415 average)
Time to do 65536 square roots of a 1024 bit number using general Newton:      2234 milliseconds (0.034088 average)
Time to do 65536 square roots of a 1024 bit number using recursive algorithm: 250 milliseconds (0.003815 average)
Time to do 65536 divides of a 1024 bit number by its square root:             172 milliseconds (0.002625 average)
Time to do 65536 general roots of a 682, 1024 bit numbers: Newton:             797 milliseconds (0.012161 average)
Time to do 65536 general roots of a 682, 1024 bit numbers: Recursive:          203 milliseconds (0.003098 average)
Time to do 32768 square roots of a 2048 bit number (Newton):                  2500 milliseconds (0.076294 average)
Time to do 32768 square roots of a 2048 bit number using general Newton:      4406 milliseconds (0.134460 average)
Time to do 32768 square roots of a 2048 bit number using recursive algorithm: 297 milliseconds (0.009064 average)
Time to do 32768 divides of a 2048 bit number by its square root:             266 milliseconds (0.008118 average)
Time to do 32768 general roots of a 1365, 2048 bit numbers: Newton:             1172 milliseconds (0.035767 average)
Time to do 32768 general roots of a 1365, 2048 bit numbers: Recursive:          265 milliseconds (0.008087 average)
Time to do 16384 square roots of a 4096 bit number (Newton):                  4094 milliseconds (0.249878 average)
Time to do 16384 square roots of a 4096 bit number using general Newton:      7094 milliseconds (0.432983 average)
Time to do 16384 square roots of a 4096 bit number using recursive algorithm: 500 milliseconds (0.030518 average)
Time to do 16384 divides of a 4096 bit number by its square root:             406 milliseconds (0.024780 average)
Time to do 16384 general roots of a 2730, 4096 bit numbers: Newton:             1797 milliseconds (0.109680 average)
Time to do 16384 general roots of a 2730, 4096 bit numbers: Recursive:          422 milliseconds (0.025757 average)
Time to do 8192 square roots of a 8192 bit number (Newton):                  7203 milliseconds (0.879272 average)
Time to do 8192 square roots of a 8192 bit number using general Newton:      10781 milliseconds (1.316040 average)
Time to do 8192 square roots of a 8192 bit number using recursive algorithm: 578 milliseconds (0.070557 average)
Time to do 8192 divides of a 8192 bit number by its square root:             578 milliseconds (0.070557 average)
Time to do 8192 general roots of a 5461, 8192 bit numbers: Newton:             2344 milliseconds (0.286133 average)
Time to do 8192 general roots of a 5461, 8192 bit numbers: Recursive:          485 milliseconds (0.059204 average)
Time to do 4096 square roots of a 16384 bit number (Newton):                  10234 milliseconds (2.498535 average)
Time to do 4096 square roots of a 16384 bit number using general Newton:      18594 milliseconds (4.539551 average)
Time to do 4096 square roots of a 16384 bit number using recursive algorithm: 843 milliseconds (0.205811 average)
Time to do 4096 divides of a 16384 bit number by its square root:             860 milliseconds (0.209961 average)
Time to do 4096 general roots of a 10922, 16384 bit numbers: Newton:             3062 milliseconds (0.747559 average)
Time to do 4096 general roots of a 10922, 16384 bit numbers: Recursive:          657 milliseconds (0.160400 average)
Time to do 2048 square roots of a 32768 bit number (Newton):                  14468 milliseconds (7.064453 average)
Time to do 2048 square roots of a 32768 bit number using general Newton:      23985 milliseconds (11.711426 average)
Time to do 2048 square roots of a 32768 bit number using recursive algorithm: 1172 milliseconds (0.572266 average)
Time to do 2048 divides of a 32768 bit number by its square root:             1140 milliseconds (0.556641 average)
Time to do 2048 general roots of a 21845, 32768 bit numbers: Newton:             4594 milliseconds (2.243164 average)
Time to do 2048 general roots of a 21845, 32768 bit numbers: Recursive:          1062 milliseconds (0.518555 average)
Time to do 1024 square roots of a 65536 bit number (Newton):                  22282 milliseconds (21.759766 average)
Time to do 1024 square roots of a 65536 bit number using general Newton:      36781 milliseconds (35.918945 average)
Time to do 1024 square roots of a 65536 bit number using recursive algorithm: 1656 milliseconds (1.617188 average)
Time to do 1024 divides of a 65536 bit number by its square root:             1688 milliseconds (1.648438 average)
Time to do 1024 general roots of a 43690, 65536 bit numbers: Newton:             6047 milliseconds (5.905273 average)
Time to do 1024 general roots of a 43690, 65536 bit numbers: Recursive:          1375 milliseconds (1.342773 average)
Time to do 512 square roots of a 131072 bit number (Newton):                  38406 milliseconds (75.011719 average)
Time to do 512 square roots of a 131072 bit number using general Newton:      55406 milliseconds (108.214844 average)
Time to do 512 square roots of a 131072 bit number using recursive algorithm: 2281 milliseconds (4.455078 average)
Time to do 512 divides of a 131072 bit number by its square root:             2344 milliseconds (4.578125 average)
Time to do 512 general roots of a 87381, 131072 bit numbers: Newton:             8641 milliseconds (16.876953 average)
Time to do 512 general roots of a 87381, 131072 bit numbers: Recursive:          1797 milliseconds (3.509766 average)
Time to do 256 square roots of a 262144 bit number (Newton):                  52437 milliseconds (204.832031 average)
Time to do 256 square roots of a 262144 bit number using general Newton:      94859 milliseconds (370.542969 average)
Time to do 256 square roots of a 262144 bit number using recursive algorithm: 3235 milliseconds (12.636719 average)
Time to do 256 divides of a 262144 bit number by its square root:             3265 milliseconds (12.753906 average)
Time to do 256 general roots of a 174762, 262144 bit numbers: Newton:             11407 milliseconds (44.558594 average)
Time to do 256 general roots of a 174762, 262144 bit numbers: Recursive:          2453 milliseconds (9.582031 average)
Time to do 128 square roots of a 524288 bit number (Newton):                  83578 milliseconds (652.953125 average)
Time to do 128 square roots of a 524288 bit number using general Newton:      113141 milliseconds (883.914062 average)
Time to do 128 square roots of a 524288 bit number using recursive algorithm: 4750 milliseconds (37.109375 average)
Time to do 128 divides of a 524288 bit number by its square root:             4968 milliseconds (38.812500 average)
Time to do 128 general roots of a 349525, 524288 bit numbers: Newton:             15375 milliseconds (120.117188 average)
Time to do 128 general roots of a 349525, 524288 bit numbers: Recursive:          3328 milliseconds (26.000000 average)
And the time to do a single 33554432 bit square root using the full algorithm: 9797 milliseconds
Simple Newton:                                                                 246344 milliseconds
General recursive (half-size x1):                                              11250 milliseconds
General recursive (two thirds-size x1):                                        5313 milliseconds
General recursive (one third-size x1):                                         10969 milliseconds
And, for comparison, squaring that square root again:                          1296 milliseconds
And to divide that large number by its square root:                            9594 milliseconds

* large DIGITs (32-bit DIGITs)
Time to do 8388608 square roots of a 16 bit number (Newton):                  46 milliseconds (0.000005 average)
Time to do 8388608 square roots of a 16 bit number using general Newton:      5719 milliseconds (0.000682 average)
Time to do 8388608 square roots of a 16 bit number using recursive algorithm: 47 milliseconds (0.000006 average)
Time to do 8388608 divides of a 16 bit number by its square root:             234 milliseconds (0.000028 average)
Time to do 8388608 general roots of a 10, 16 bit numbers: Newton:             5469 milliseconds (0.000652 average)
Time to do 8388608 general roots of a 10, 16 bit numbers: Recursive:          5641 milliseconds (0.000672 average)
Time to do 4194304 square roots of a 32 bit number (Newton):                  15 milliseconds (0.000004 average)
Time to do 4194304 square roots of a 32 bit number using general Newton:      579 milliseconds (0.000138 average)
Time to do 4194304 square roots of a 32 bit number using recursive algorithm: 15 milliseconds (0.000004 average)
Time to do 4194304 divides of a 32 bit number by its square root:             125 milliseconds (0.000030 average)
Time to do 4194304 general roots of a 21, 32 bit numbers: Newton:             656 milliseconds (0.000156 average)
Time to do 4194304 general roots of a 21, 32 bit numbers: Recursive:          750 milliseconds (0.000179 average)
Time to do 2097152 square roots of a 64 bit number (Newton):                  16 milliseconds (0.000008 average)
Time to do 2097152 square roots of a 64 bit number using general Newton:      625 milliseconds (0.000298 average)
Time to do 2097152 square roots of a 64 bit number using recursive algorithm: 16 milliseconds (0.000008 average)
Time to do 2097152 divides of a 64 bit number by its square root:             62 milliseconds (0.000030 average)
Time to do 2097152 general roots of a 42, 64 bit numbers: Newton:             360 milliseconds (0.000172 average)
Time to do 2097152 general roots of a 42, 64 bit numbers: Recursive:          421 milliseconds (0.000201 average)
Time to do 1048576 square roots of a 96 bit number (Newton):                  266 milliseconds (0.000254 average)
Time to do 1048576 square roots of a 96 bit number using general Newton:      359 milliseconds (0.000342 average)
Time to do 1048576 square roots of a 96 bit number using recursive algorithm: 219 milliseconds (0.000209 average)
Time to do 1048576 divides of a 96 bit number by its square root:             63 milliseconds (0.000060 average)
Time to do 1048576 general roots of a 64, 96 bit numbers: Newton:             281 milliseconds (0.000268 average)
Time to do 1048576 general roots of a 64, 96 bit numbers: Recursive:          172 milliseconds (0.000164 average)
Time to do 524288 square roots of a 128 bit number (Newton):                  172 milliseconds (0.000328 average)
Time to do 524288 square roots of a 128 bit number using general Newton:      250 milliseconds (0.000477 average)
Time to do 524288 square roots of a 128 bit number using recursive algorithm: 62 milliseconds (0.000118 average)
Time to do 524288 divides of a 128 bit number by its square root:             31 milliseconds (0.000059 average)
Time to do 524288 general roots of a 85, 128 bit numbers: Newton:             157 milliseconds (0.000299 average)
Time to do 524288 general roots of a 85, 128 bit numbers: Recursive:          109 milliseconds (0.000208 average)
Time to do 262144 square roots of a 256 bit number (Newton):                  234 milliseconds (0.000893 average)
Time to do 262144 square roots of a 256 bit number using general Newton:      297 milliseconds (0.001133 average)
Time to do 262144 square roots of a 256 bit number using recursive algorithm: 94 milliseconds (0.000359 average)
Time to do 262144 divides of a 256 bit number by its square root:             31 milliseconds (0.000118 average)
Time to do 262144 general roots of a 170, 256 bit numbers: Newton:             157 milliseconds (0.000599 average)
Time to do 262144 general roots of a 170, 256 bit numbers: Recursive:          93 milliseconds (0.000355 average)
Time to do 131072 square roots of a 512 bit number (Newton):                  297 milliseconds (0.002266 average)
Time to do 131072 square roots of a 512 bit number using general Newton:      485 milliseconds (0.003700 average)
Time to do 131072 square roots of a 512 bit number using recursive algorithm: 78 milliseconds (0.000595 average)
Time to do 131072 divides of a 512 bit number by its square root:             47 milliseconds (0.000359 average)
Time to do 131072 general roots of a 341, 512 bit numbers: Newton:             203 milliseconds (0.001549 average)
Time to do 131072 general roots of a 341, 512 bit numbers: Recursive:          47 milliseconds (0.000359 average)
Time to do 65536 square roots of a 1024 bit number (Newton):                  375 milliseconds (0.005722 average)
Time to do 65536 square roots of a 1024 bit number using general Newton:      671 milliseconds (0.010239 average)
Time to do 65536 square roots of a 1024 bit number using recursive algorithm: 94 milliseconds (0.001434 average)
Time to do 65536 divides of a 1024 bit number by its square root:             47 milliseconds (0.000717 average)
Time to do 65536 general roots of a 682, 1024 bit numbers: Newton:             281 milliseconds (0.004288 average)
Time to do 65536 general roots of a 682, 1024 bit numbers: Recursive:          78 milliseconds (0.001190 average)
Time to do 32768 square roots of a 2048 bit number (Newton):                  704 milliseconds (0.021484 average)
Time to do 32768 square roots of a 2048 bit number using general Newton:      1062 milliseconds (0.032410 average)
Time to do 32768 square roots of a 2048 bit number using recursive algorithm: 94 milliseconds (0.002869 average)
Time to do 32768 divides of a 2048 bit number by its square root:             78 milliseconds (0.002380 average)
Time to do 32768 general roots of a 1365, 2048 bit numbers: Newton:             312 milliseconds (0.009521 average)
Time to do 32768 general roots of a 1365, 2048 bit numbers: Recursive:          94 milliseconds (0.002869 average)
Time to do 16384 square roots of a 4096 bit number (Newton):                  1125 milliseconds (0.068665 average)
Time to do 16384 square roots of a 4096 bit number using general Newton:      1891 milliseconds (0.115417 average)
Time to do 16384 square roots of a 4096 bit number using recursive algorithm: 125 milliseconds (0.007629 average)
Time to do 16384 divides of a 4096 bit number by its square root:             94 milliseconds (0.005737 average)
Time to do 16384 general roots of a 2730, 4096 bit numbers: Newton:             484 milliseconds (0.029541 average)
Time to do 16384 general roots of a 2730, 4096 bit numbers: Recursive:          94 milliseconds (0.005737 average)
Time to do 8192 square roots of a 8192 bit number (Newton):                  1672 milliseconds (0.204102 average)
Time to do 8192 square roots of a 8192 bit number using general Newton:      2796 milliseconds (0.341309 average)
Time to do 8192 square roots of a 8192 bit number using recursive algorithm: 141 milliseconds (0.017212 average)
Time to do 8192 divides of a 8192 bit number by its square root:             141 milliseconds (0.017212 average)
Time to do 8192 general roots of a 5461, 8192 bit numbers: Newton:             609 milliseconds (0.074341 average)
Time to do 8192 general roots of a 5461, 8192 bit numbers: Recursive:          141 milliseconds (0.017212 average)
Time to do 4096 square roots of a 16384 bit number (Newton):                  2609 milliseconds (0.636963 average)
Time to do 4096 square roots of a 16384 bit number using general Newton:      4500 milliseconds (1.098633 average)
Time to do 4096 square roots of a 16384 bit number using recursive algorithm: 219 milliseconds (0.053467 average)
Time to do 4096 divides of a 16384 bit number by its square root:             203 milliseconds (0.049561 average)
Time to do 4096 general roots of a 10922, 16384 bit numbers: Newton:             891 milliseconds (0.217529 average)
Time to do 4096 general roots of a 10922, 16384 bit numbers: Recursive:          171 milliseconds (0.041748 average)
Time to do 2048 square roots of a 32768 bit number (Newton):                  3625 milliseconds (1.770020 average)
Time to do 2048 square roots of a 32768 bit number using general Newton:      6063 milliseconds (2.960449 average)
Time to do 2048 square roots of a 32768 bit number using recursive algorithm: 297 milliseconds (0.145020 average)
Time to do 2048 divides of a 32768 bit number by its square root:             265 milliseconds (0.129395 average)
Time to do 2048 general roots of a 21845, 32768 bit numbers: Newton:             1157 milliseconds (0.564941 average)
Time to do 2048 general roots of a 21845, 32768 bit numbers: Recursive:          250 milliseconds (0.122070 average)
Time to do 1024 square roots of a 65536 bit number (Newton):                  5781 milliseconds (5.645508 average)
Time to do 1024 square roots of a 65536 bit number using general Newton:      9422 milliseconds (9.201172 average)
Time to do 1024 square roots of a 65536 bit number using recursive algorithm: 437 milliseconds (0.426758 average)
Time to do 1024 divides of a 65536 bit number by its square root:             407 milliseconds (0.397461 average)
Time to do 1024 general roots of a 43690, 65536 bit numbers: Newton:             1578 milliseconds (1.541016 average)
Time to do 1024 general roots of a 43690, 65536 bit numbers: Recursive:          328 milliseconds (0.320312 average)
Time to do 512 square roots of a 131072 bit number (Newton):                  8359 milliseconds (16.326172 average)
Time to do 512 square roots of a 131072 bit number using general Newton:      13953 milliseconds (27.251953 average)
Time to do 512 square roots of a 131072 bit number using recursive algorithm: 594 milliseconds (1.160156 average)
Time to do 512 divides of a 131072 bit number by its square root:             563 milliseconds (1.099609 average)
Time to do 512 general roots of a 87381, 131072 bit numbers: Newton:             2031 milliseconds (3.966797 average)
Time to do 512 general roots of a 87381, 131072 bit numbers: Recursive:          453 milliseconds (0.884766 average)
Time to do 256 square roots of a 262144 bit number (Newton):                  12578 milliseconds (49.132812 average)
Time to do 256 square roots of a 262144 bit number using general Newton:      18063 milliseconds (70.558594 average)
Time to do 256 square roots of a 262144 bit number using recursive algorithm: 781 milliseconds (3.050781 average)
Time to do 256 divides of a 262144 bit number by its square root:             844 milliseconds (3.296875 average)
Time to do 256 general roots of a 174762, 262144 bit numbers: Newton:             2937 milliseconds (11.472656 average)
Time to do 256 general roots of a 174762, 262144 bit numbers: Recursive:          656 milliseconds (2.562500 average)
Time to do 128 square roots of a 524288 bit number (Newton):                  15860 milliseconds (123.906250 average)
Time to do 128 square roots of a 524288 bit number using general Newton:      22937 milliseconds (179.195312 average)
Time to do 128 square roots of a 524288 bit number using recursive algorithm: 985 milliseconds (7.695312 average)
Time to do 128 divides of a 524288 bit number by its square root:             1000 milliseconds (7.812500 average)
Time to do 128 general roots of a 349525, 524288 bit numbers: Newton:             5656 milliseconds (44.187500 average)
Time to do 128 general roots of a 349525, 524288 bit numbers: Recursive:          781 milliseconds (6.101562 average)
And the time to do a single 33554432 bit square root using the full algorithm: 2610 milliseconds
Simple Newton:                                                                 58718 milliseconds
General recursive (half-size x1):                                              3125 milliseconds
General recursive (two thirds-size x1):                                        1516 milliseconds
General recursive (one third-size x1):                                         3063 milliseconds
And, for comparison, squaring that square root again:                          422 milliseconds
And to divide that large number by its square root:                            2640 milliseconds
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

/*
16-bit DIGITs
Using 16384 iterations
Basic matrix multiplier took    891 milliseconds for square matrix of size 12 with entries of 1 DIGITs
Strassen matrix multiplier took 953 milliseconds for square matrix of size 12 with entries of 1 DIGITs
Basic matrix multiplier took    1016 milliseconds for square matrix of size 12 with entries of 2 DIGITs
Strassen matrix multiplier took 1062 milliseconds for square matrix of size 12 with entries of 2 DIGITs
Basic matrix multiplier took    1266 milliseconds for square matrix of size 12 with entries of 3 DIGITs
Strassen matrix multiplier took 1281 milliseconds for square matrix of size 12 with entries of 3 DIGITs
Basic matrix multiplier took    1422 milliseconds for square matrix of size 12 with entries of 4 DIGITs
Strassen matrix multiplier took 1422 milliseconds for square matrix of size 12 with entries of 4 DIGITs
Basic matrix multiplier took    1609 milliseconds for square matrix of size 12 with entries of 5 DIGITs
Strassen matrix multiplier took 1625 milliseconds for square matrix of size 12 with entries of 5 DIGITs
Basic matrix multiplier took    1719 milliseconds for square matrix of size 12 with entries of 6 DIGITs
Strassen matrix multiplier took 1734 milliseconds for square matrix of size 12 with entries of 6 DIGITs
Basic matrix multiplier took    2094 milliseconds for square matrix of size 12 with entries of 7 DIGITs
Strassen matrix multiplier took 2156 milliseconds for square matrix of size 12 with entries of 7 DIGITs
Basic matrix multiplier took    2625 milliseconds for square matrix of size 12 with entries of 8 DIGITs
Strassen matrix multiplier took 2578 milliseconds for square matrix of size 12 with entries of 8 DIGITs
Basic matrix multiplier took    4594 milliseconds for square matrix of size 12 with entries of 9 DIGITs
Strassen matrix multiplier took 3922 milliseconds for square matrix of size 12 with entries of 9 DIGITs
Basic matrix multiplier took    4656 milliseconds for square matrix of size 12 with entries of 10 DIGITs
Strassen matrix multiplier took 4469 milliseconds for square matrix of size 12 with entries of 10 DIGITs
Basic matrix multiplier took    5515 milliseconds for square matrix of size 12 with entries of 11 DIGITs
Strassen matrix multiplier took 5766 milliseconds for square matrix of size 12 with entries of 11 DIGITs
Basic matrix multiplier took    6297 milliseconds for square matrix of size 12 with entries of 12 DIGITs
Strassen matrix multiplier took 6953 milliseconds for square matrix of size 12 with entries of 12 DIGITs
Basic matrix multiplier took    6453 milliseconds for square matrix of size 12 with entries of 13 DIGITs
Strassen matrix multiplier took 6578 milliseconds for square matrix of size 12 with entries of 13 DIGITs
Basic matrix multiplier took    7500 milliseconds for square matrix of size 12 with entries of 14 DIGITs
Strassen matrix multiplier took 7922 milliseconds for square matrix of size 12 with entries of 14 DIGITs
Basic matrix multiplier took    10766 milliseconds for square matrix of size 12 with entries of 15 DIGITs
Strassen matrix multiplier took 11000 milliseconds for square matrix of size 12 with entries of 15 DIGITs
Basic matrix multiplier took    11250 milliseconds for square matrix of size 12 with entries of 16 DIGITs
Strassen matrix multiplier took 11968 milliseconds for square matrix of size 12 with entries of 16 DIGITs
Using 2048 iterations
Basic matrix multiplier took    1188 milliseconds for square matrix of size 24 with entries of 1 DIGITs
Strassen matrix multiplier took 1265 milliseconds for square matrix of size 24 with entries of 1 DIGITs
Basic matrix multiplier took    1297 milliseconds for square matrix of size 24 with entries of 2 DIGITs
Strassen matrix multiplier took 1375 milliseconds for square matrix of size 24 with entries of 2 DIGITs
Basic matrix multiplier took    1500 milliseconds for square matrix of size 24 with entries of 3 DIGITs
Strassen matrix multiplier took 1516 milliseconds for square matrix of size 24 with entries of 3 DIGITs
Basic matrix multiplier took    1672 milliseconds for square matrix of size 24 with entries of 4 DIGITs
Strassen matrix multiplier took 1640 milliseconds for square matrix of size 24 with entries of 4 DIGITs
Basic matrix multiplier took    1891 milliseconds for square matrix of size 24 with entries of 5 DIGITs
Strassen matrix multiplier took 1969 milliseconds for square matrix of size 24 with entries of 5 DIGITs
Basic matrix multiplier took    2219 milliseconds for square matrix of size 24 with entries of 6 DIGITs
Strassen matrix multiplier took 2421 milliseconds for square matrix of size 24 with entries of 6 DIGITs
Basic matrix multiplier took    3579 milliseconds for square matrix of size 24 with entries of 7 DIGITs
Strassen matrix multiplier took 3656 milliseconds for square matrix of size 24 with entries of 7 DIGITs
Basic matrix multiplier took    3156 milliseconds for square matrix of size 24 with entries of 8 DIGITs
Strassen matrix multiplier took 3203 milliseconds for square matrix of size 24 with entries of 8 DIGITs
Basic matrix multiplier took    4469 milliseconds for square matrix of size 24 with entries of 9 DIGITs
Strassen matrix multiplier took 4766 milliseconds for square matrix of size 24 with entries of 9 DIGITs
Basic matrix multiplier took    5656 milliseconds for square matrix of size 24 with entries of 10 DIGITs
Strassen matrix multiplier took 6016 milliseconds for square matrix of size 24 with entries of 10 DIGITs
Basic matrix multiplier took    8125 milliseconds for square matrix of size 24 with entries of 11 DIGITs
Strassen matrix multiplier took 7969 milliseconds for square matrix of size 24 with entries of 11 DIGITs
Basic matrix multiplier took    7562 milliseconds for square matrix of size 24 with entries of 12 DIGITs
Strassen matrix multiplier took 5657 milliseconds for square matrix of size 24 with entries of 12 DIGITs
Basic matrix multiplier took    5609 milliseconds for square matrix of size 24 with entries of 13 DIGITs
Strassen matrix multiplier took 5687 milliseconds for square matrix of size 24 with entries of 13 DIGITs
Basic matrix multiplier took    6594 milliseconds for square matrix of size 24 with entries of 14 DIGITs
Strassen matrix multiplier took 6578 milliseconds for square matrix of size 24 with entries of 14 DIGITs
Basic matrix multiplier took    9312 milliseconds for square matrix of size 24 with entries of 15 DIGITs
Strassen matrix multiplier took 8641 milliseconds for square matrix of size 24 with entries of 15 DIGITs
Basic matrix multiplier took    10047 milliseconds for square matrix of size 24 with entries of 16 DIGITs
Strassen matrix multiplier took 9656 milliseconds for square matrix of size 24 with entries of 16 DIGITs
Using 256 iterations
Basic matrix multiplier took    1031 milliseconds for square matrix of size 48 with entries of 1 DIGITs
Strassen matrix multiplier took 1094 milliseconds for square matrix of size 48 with entries of 1 DIGITs
Basic matrix multiplier took    1203 milliseconds for square matrix of size 48 with entries of 2 DIGITs
Strassen matrix multiplier took 1156 milliseconds for square matrix of size 48 with entries of 2 DIGITs
Basic matrix multiplier took    1250 milliseconds for square matrix of size 48 with entries of 3 DIGITs
Strassen matrix multiplier took 1375 milliseconds for square matrix of size 48 with entries of 3 DIGITs
Basic matrix multiplier took    1391 milliseconds for square matrix of size 48 with entries of 4 DIGITs
Strassen matrix multiplier took 1500 milliseconds for square matrix of size 48 with entries of 4 DIGITs
Basic matrix multiplier took    1704 milliseconds for square matrix of size 48 with entries of 5 DIGITs
Strassen matrix multiplier took 1750 milliseconds for square matrix of size 48 with entries of 5 DIGITs
Basic matrix multiplier took    1890 milliseconds for square matrix of size 48 with entries of 6 DIGITs
Strassen matrix multiplier took 2031 milliseconds for square matrix of size 48 with entries of 6 DIGITs
Basic matrix multiplier took    2235 milliseconds for square matrix of size 48 with entries of 7 DIGITs
Strassen matrix multiplier took 2265 milliseconds for square matrix of size 48 with entries of 7 DIGITs
Basic matrix multiplier took    2516 milliseconds for square matrix of size 48 with entries of 8 DIGITs
Strassen matrix multiplier took 2609 milliseconds for square matrix of size 48 with entries of 8 DIGITs
Basic matrix multiplier took    3813 milliseconds for square matrix of size 48 with entries of 9 DIGITs
Strassen matrix multiplier took 3672 milliseconds for square matrix of size 48 with entries of 9 DIGITs
Basic matrix multiplier took    4656 milliseconds for square matrix of size 48 with entries of 10 DIGITs
Strassen matrix multiplier took 4375 milliseconds for square matrix of size 48 with entries of 10 DIGITs
Basic matrix multiplier took    5718 milliseconds for square matrix of size 48 with entries of 11 DIGITs
Strassen matrix multiplier took 5032 milliseconds for square matrix of size 48 with entries of 11 DIGITs
Basic matrix multiplier took    5937 milliseconds for square matrix of size 48 with entries of 12 DIGITs
Strassen matrix multiplier took 5328 milliseconds for square matrix of size 48 with entries of 12 DIGITs
Basic matrix multiplier took    5875 milliseconds for square matrix of size 48 with entries of 13 DIGITs
Strassen matrix multiplier took 5219 milliseconds for square matrix of size 48 with entries of 13 DIGITs
Basic matrix multiplier took    6765 milliseconds for square matrix of size 48 with entries of 14 DIGITs
Strassen matrix multiplier took 6391 milliseconds for square matrix of size 48 with entries of 14 DIGITs
Basic matrix multiplier took    9594 milliseconds for square matrix of size 48 with entries of 15 DIGITs
Strassen matrix multiplier took 7906 milliseconds for square matrix of size 48 with entries of 15 DIGITs
Basic matrix multiplier took    10422 milliseconds for square matrix of size 48 with entries of 16 DIGITs
Strassen matrix multiplier took 8828 milliseconds for square matrix of size 48 with entries of 16 DIGITs
Using 32 iterations
Basic matrix multiplier took    1094 milliseconds for square matrix of size 96 with entries of 1 DIGITs
Strassen matrix multiplier took 1140 milliseconds for square matrix of size 96 with entries of 1 DIGITs
Basic matrix multiplier took    1203 milliseconds for square matrix of size 96 with entries of 2 DIGITs
Strassen matrix multiplier took 1235 milliseconds for square matrix of size 96 with entries of 2 DIGITs
Basic matrix multiplier took    1437 milliseconds for square matrix of size 96 with entries of 3 DIGITs
Strassen matrix multiplier took 1297 milliseconds for square matrix of size 96 with entries of 3 DIGITs
Basic matrix multiplier took    1515 milliseconds for square matrix of size 96 with entries of 4 DIGITs
Strassen matrix multiplier took 1422 milliseconds for square matrix of size 96 with entries of 4 DIGITs
Basic matrix multiplier took    1813 milliseconds for square matrix of size 96 with entries of 5 DIGITs
Strassen matrix multiplier took 1625 milliseconds for square matrix of size 96 with entries of 5 DIGITs
Basic matrix multiplier took    2047 milliseconds for square matrix of size 96 with entries of 6 DIGITs
Strassen matrix multiplier took 1843 milliseconds for square matrix of size 96 with entries of 6 DIGITs
Basic matrix multiplier took    2297 milliseconds for square matrix of size 96 with entries of 7 DIGITs
Strassen matrix multiplier took 2078 milliseconds for square matrix of size 96 with entries of 7 DIGITs
Basic matrix multiplier took    2609 milliseconds for square matrix of size 96 with entries of 8 DIGITs
Strassen matrix multiplier took 2422 milliseconds for square matrix of size 96 with entries of 8 DIGITs
Basic matrix multiplier took    3812 milliseconds for square matrix of size 96 with entries of 9 DIGITs
Strassen matrix multiplier took 3250 milliseconds for square matrix of size 96 with entries of 9 DIGITs
Basic matrix multiplier took    4688 milliseconds for square matrix of size 96 with entries of 10 DIGITs
Strassen matrix multiplier took 3875 milliseconds for square matrix of size 96 with entries of 10 DIGITs
Basic matrix multiplier took    5546 milliseconds for square matrix of size 96 with entries of 11 DIGITs
Strassen matrix multiplier took 4360 milliseconds for square matrix of size 96 with entries of 11 DIGITs
Basic matrix multiplier took    6125 milliseconds for square matrix of size 96 with entries of 12 DIGITs
Strassen matrix multiplier took 4454 milliseconds for square matrix of size 96 with entries of 12 DIGITs
Basic matrix multiplier took    6141 milliseconds for square matrix of size 96 with entries of 13 DIGITs
Strassen matrix multiplier took 4906 milliseconds for square matrix of size 96 with entries of 13 DIGITs
Basic matrix multiplier took    7281 milliseconds for square matrix of size 96 with entries of 14 DIGITs
Strassen matrix multiplier took 6000 milliseconds for square matrix of size 96 with entries of 14 DIGITs
Basic matrix multiplier took    9937 milliseconds for square matrix of size 96 with entries of 15 DIGITs
Strassen matrix multiplier took 6484 milliseconds for square matrix of size 96 with entries of 15 DIGITs
Basic matrix multiplier took    9438 milliseconds for square matrix of size 96 with entries of 16 DIGITs
Strassen matrix multiplier took 7562 milliseconds for square matrix of size 96 with entries of 16 DIGITs
Using 4 iterations
Basic matrix multiplier took    1140 milliseconds for square matrix of size 192 with entries of 1 DIGITs
Strassen matrix multiplier took 1110 milliseconds for square matrix of size 192 with entries of 1 DIGITs
Basic matrix multiplier took    1375 milliseconds for square matrix of size 192 with entries of 2 DIGITs
Strassen matrix multiplier took 1172 milliseconds for square matrix of size 192 with entries of 2 DIGITs
Basic matrix multiplier took    1531 milliseconds for square matrix of size 192 with entries of 3 DIGITs
Strassen matrix multiplier took 1157 milliseconds for square matrix of size 192 with entries of 3 DIGITs
Basic matrix multiplier took    1610 milliseconds for square matrix of size 192 with entries of 4 DIGITs
Strassen matrix multiplier took 1359 milliseconds for square matrix of size 192 with entries of 4 DIGITs
Basic matrix multiplier took    2047 milliseconds for square matrix of size 192 with entries of 5 DIGITs
Strassen matrix multiplier took 1421 milliseconds for square matrix of size 192 with entries of 5 DIGITs
Basic matrix multiplier took    2234 milliseconds for square matrix of size 192 with entries of 6 DIGITs
Strassen matrix multiplier took 1594 milliseconds for square matrix of size 192 with entries of 6 DIGITs
Basic matrix multiplier took    2328 milliseconds for square matrix of size 192 with entries of 7 DIGITs
Strassen matrix multiplier took 1750 milliseconds for square matrix of size 192 with entries of 7 DIGITs
Basic matrix multiplier took    2610 milliseconds for square matrix of size 192 with entries of 8 DIGITs
Strassen matrix multiplier took 2125 milliseconds for square matrix of size 192 with entries of 8 DIGITs
Basic matrix multiplier took    3813 milliseconds for square matrix of size 192 with entries of 9 DIGITs
Strassen matrix multiplier took 2781 milliseconds for square matrix of size 192 with entries of 9 DIGITs
Basic matrix multiplier took    4625 milliseconds for square matrix of size 192 with entries of 10 DIGITs
Strassen matrix multiplier took 3281 milliseconds for square matrix of size 192 with entries of 10 DIGITs
Basic matrix multiplier took    5422 milliseconds for square matrix of size 192 with entries of 11 DIGITs
Strassen matrix multiplier took 3563 milliseconds for square matrix of size 192 with entries of 11 DIGITs
Basic matrix multiplier took    5688 milliseconds for square matrix of size 192 with entries of 12 DIGITs
Strassen matrix multiplier took 3719 milliseconds for square matrix of size 192 with entries of 12 DIGITs
Basic matrix multiplier took    6046 milliseconds for square matrix of size 192 with entries of 13 DIGITs
Strassen matrix multiplier took 4016 milliseconds for square matrix of size 192 with entries of 13 DIGITs
Basic matrix multiplier took    6781 milliseconds for square matrix of size 192 with entries of 14 DIGITs
Strassen matrix multiplier took 4812 milliseconds for square matrix of size 192 with entries of 14 DIGITs
Basic matrix multiplier took    9438 milliseconds for square matrix of size 192 with entries of 15 DIGITs
Strassen matrix multiplier took 5984 milliseconds for square matrix of size 192 with entries of 15 DIGITs
Basic matrix multiplier took    10718 milliseconds for square matrix of size 192 with entries of 16 DIGITs
Strassen matrix multiplier took 7344 milliseconds for square matrix of size 192 with entries of 16 DIGITs
Using 1 iterations
Basic matrix multiplier took    3562 milliseconds for square matrix of size 384 with entries of 1 DIGITs
Strassen matrix multiplier took 1984 milliseconds for square matrix of size 384 with entries of 1 DIGITs
Basic matrix multiplier took    4141 milliseconds for square matrix of size 384 with entries of 2 DIGITs
Strassen matrix multiplier took 2078 milliseconds for square matrix of size 384 with entries of 2 DIGITs
Basic matrix multiplier took    4610 milliseconds for square matrix of size 384 with entries of 3 DIGITs
Strassen matrix multiplier took 2421 milliseconds for square matrix of size 384 with entries of 3 DIGITs
Basic matrix multiplier took    4891 milliseconds for square matrix of size 384 with entries of 4 DIGITs
Strassen matrix multiplier took 2750 milliseconds for square matrix of size 384 with entries of 4 DIGITs
Basic matrix multiplier took    6203 milliseconds for square matrix of size 384 with entries of 5 DIGITs
Strassen matrix multiplier took 3016 milliseconds for square matrix of size 384 with entries of 5 DIGITs
Basic matrix multiplier took    6438 milliseconds for square matrix of size 384 with entries of 6 DIGITs
Strassen matrix multiplier took 3187 milliseconds for square matrix of size 384 with entries of 6 DIGITs
Basic matrix multiplier took    6844 milliseconds for square matrix of size 384 with entries of 7 DIGITs
Strassen matrix multiplier took 3344 milliseconds for square matrix of size 384 with entries of 7 DIGITs
Basic matrix multiplier took    7297 milliseconds for square matrix of size 384 with entries of 8 DIGITs
Strassen matrix multiplier took 4219 milliseconds for square matrix of size 384 with entries of 8 DIGITs
Basic matrix multiplier took    9688 milliseconds for square matrix of size 384 with entries of 9 DIGITs
Strassen matrix multiplier took 5672 milliseconds for square matrix of size 384 with entries of 9 DIGITs
Basic matrix multiplier took    11547 milliseconds for square matrix of size 384 with entries of 10 DIGITs
Strassen matrix multiplier took 6469 milliseconds for square matrix of size 384 with entries of 10 DIGITs
Basic matrix multiplier took    13109 milliseconds for square matrix of size 384 with entries of 11 DIGITs
Strassen matrix multiplier took 7016 milliseconds for square matrix of size 384 with entries of 11 DIGITs
Basic matrix multiplier took    13500 milliseconds for square matrix of size 384 with entries of 12 DIGITs
Strassen matrix multiplier took 6922 milliseconds for square matrix of size 384 with entries of 12 DIGITs
Basic matrix multiplier took    14125 milliseconds for square matrix of size 384 with entries of 13 DIGITs
Strassen matrix multiplier took 7532 milliseconds for square matrix of size 384 with entries of 13 DIGITs
Basic matrix multiplier took    15954 milliseconds for square matrix of size 384 with entries of 14 DIGITs
Strassen matrix multiplier took 9359 milliseconds for square matrix of size 384 with entries of 14 DIGITs
Basic matrix multiplier took    20562 milliseconds for square matrix of size 384 with entries of 15 DIGITs
Strassen matrix multiplier took 10453 milliseconds for square matrix of size 384 with entries of 15 DIGITs
Basic matrix multiplier took    20031 milliseconds for square matrix of size 384 with entries of 16 DIGITs
Strassen matrix multiplier took 11469 milliseconds for square matrix of size 384 with entries of 16 DIGITs
Using 1 iterations
Basic matrix multiplier took    29875 milliseconds for square matrix of size 768 with entries of 1 DIGITs
Strassen matrix multiplier took 13063 milliseconds for square matrix of size 768 with entries of 1 DIGITs
Basic matrix multiplier took    29703 milliseconds for square matrix of size 768 with entries of 2 DIGITs
Strassen matrix multiplier took 13609 milliseconds for square matrix of size 768 with entries of 2 DIGITs
Basic matrix multiplier took    35766 milliseconds for square matrix of size 768 with entries of 3 DIGITs
Strassen matrix multiplier took 14234 milliseconds for square matrix of size 768 with entries of 3 DIGITs
Basic matrix multiplier took    37687 milliseconds for square matrix of size 768 with entries of 4 DIGITs
Strassen matrix multiplier took 15594 milliseconds for square matrix of size 768 with entries of 4 DIGITs
Basic matrix multiplier took    46328 milliseconds for square matrix of size 768 with entries of 5 DIGITs
Strassen matrix multiplier took 17641 milliseconds for square matrix of size 768 with entries of 5 DIGITs
Basic matrix multiplier took    50281 milliseconds for square matrix of size 768 with entries of 6 DIGITs
Strassen matrix multiplier took 19454 milliseconds for square matrix of size 768 with entries of 6 DIGITs
Basic matrix multiplier took    54359 milliseconds for square matrix of size 768 with entries of 7 DIGITs
Strassen matrix multiplier took 21719 milliseconds for square matrix of size 768 with entries of 7 DIGITs
Basic matrix multiplier took    60891 milliseconds for square matrix of size 768 with entries of 8 DIGITs
Strassen matrix multiplier took 27313 milliseconds for square matrix of size 768 with entries of 8 DIGITs
Basic matrix multiplier took    76063 milliseconds for square matrix of size 768 with entries of 9 DIGITs
Strassen matrix multiplier took 34469 milliseconds for square matrix of size 768 with entries of 9 DIGITs
Basic matrix multiplier took    90687 milliseconds for square matrix of size 768 with entries of 10 DIGITs
Strassen matrix multiplier took 42172 milliseconds for square matrix of size 768 with entries of 10 DIGITs
Basic matrix multiplier took    101594 milliseconds for square matrix of size 768 with entries of 11 DIGITs
Strassen matrix multiplier took 42265 milliseconds for square matrix of size 768 with entries of 11 DIGITs
Basic matrix multiplier took    106922 milliseconds for square matrix of size 768 with entries of 12 DIGITs
Strassen matrix multiplier took 45094 milliseconds for square matrix of size 768 with entries of 12 DIGITs
Basic matrix multiplier took    108734 milliseconds for square matrix of size 768 with entries of 13 DIGITs
Strassen matrix multiplier took 47938 milliseconds for square matrix of size 768 with entries of 13 DIGITs
Basic matrix multiplier took    124484 milliseconds for square matrix of size 768 with entries of 14 DIGITs
Strassen matrix multiplier took 63031 milliseconds for square matrix of size 768 with entries of 14 DIGITs
Basic matrix multiplier took    163640 milliseconds for square matrix of size 768 with entries of 15 DIGITs
Strassen matrix multiplier took 69641 milliseconds for square matrix of size 768 with entries of 15 DIGITs
Basic matrix multiplier took    167015 milliseconds for square matrix of size 768 with entries of 16 DIGITs
Strassen matrix multiplier took 79891 milliseconds for square matrix of size 768 with entries of 16 DIGITs
Using 1 iterations
Basic matrix multiplier took    274859 milliseconds for square matrix of size 1536 with entries of 1 DIGITs
Strassen matrix multiplier took 90813 milliseconds for square matrix of size 1536 with entries of 1 DIGITs
Basic matrix multiplier took    253797 milliseconds for square matrix of size 1536 with entries of 2 DIGITs
Strassen matrix multiplier took 93875 milliseconds for square matrix of size 1536 with entries of 2 DIGITs
Basic matrix multiplier took    311672 milliseconds for square matrix of size 1536 with entries of 3 DIGITs
Strassen matrix multiplier took 99750 milliseconds for square matrix of size 1536 with entries of 3 DIGITs
Basic matrix multiplier took    326937 milliseconds for square matrix of size 1536 with entries of 4 DIGITs
Strassen matrix multiplier took 109813 milliseconds for square matrix of size 1536 with entries of 4 DIGITs
Basic matrix multiplier took    416188 milliseconds for square matrix of size 1536 with entries of 5 DIGITs
Strassen matrix multiplier took 124843 milliseconds for square matrix of size 1536 with entries of 5 DIGITs
Basic matrix multiplier took    524453 milliseconds for square matrix of size 1536 with entries of 6 DIGITs
Strassen matrix multiplier took 150750 milliseconds for square matrix of size 1536 with entries of 6 DIGITs
Basic matrix multiplier took    510500 milliseconds for square matrix of size 1536 with entries of 7 DIGITs
Strassen matrix multiplier took 163187 milliseconds for square matrix of size 1536 with entries of 7 DIGITs
Basic matrix multiplier took    544953 milliseconds for square matrix of size 1536 with entries of 8 DIGITs
Strassen matrix multiplier took 195141 milliseconds for square matrix of size 1536 with entries of 8 DIGITs
Basic matrix multiplier took    678906 milliseconds for square matrix of size 1536 with entries of 9 DIGITs
Strassen matrix multiplier took 282047 milliseconds for square matrix of size 1536 with entries of 9 DIGITs
Basic matrix multiplier took    779937 milliseconds for square matrix of size 1536 with entries of 10 DIGITs
Strassen matrix multiplier took 290219 milliseconds for square matrix of size 1536 with entries of 10 DIGITs
Basic matrix multiplier took    880016 milliseconds for square matrix of size 1536 with entries of 11 DIGITs
Strassen matrix multiplier took 306859 milliseconds for square matrix of size 1536 with entries of 11 DIGITs
Basic matrix multiplier took    934015 milliseconds for square matrix of size 1536 with entries of 12 DIGITs
Strassen matrix multiplier took 319172 milliseconds for square matrix of size 1536 with entries of 12 DIGITs
Basic matrix multiplier took    984954 milliseconds for square matrix of size 1536 with entries of 13 DIGITs
Strassen matrix multiplier took 350609 milliseconds for square matrix of size 1536 with entries of 13 DIGITs
Basic matrix multiplier took    1204172 milliseconds for square matrix of size 1536 with entries of 14 DIGITs
Strassen matrix multiplier took 430656 milliseconds for square matrix of size 1536 with entries of 14 DIGITs
Basic matrix multiplier took    1385688 milliseconds for square matrix of size 1536 with entries of 15 DIGITs
Strassen matrix multiplier took 485719 milliseconds for square matrix of size 1536 with entries of 15 DIGITs
Basic matrix multiplier took    1415406 milliseconds for square matrix of size 1536 with entries of 16 DIGITs
Strassen matrix multiplier took 557266 milliseconds for square matrix of size 1536 with entries of 16 DIGITs
*/
void  CArithmeticPerformanceTester::MatrixMultiplyTimes()
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