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
#if(_CollectDetailedTimingData)
                    BasicMultiplyReg1(nSize,nSize,nX,nY,nZ,false,dwDummy);
#else
                    BasicMultiplyReg1(nSize,nSize,nX,nY,nZ,false);
#endif
                    break;
                case 1:
#if(_CollectDetailedTimingData)
                    BasicMultiplyReg2(nSize,nSize,nX,nY,nZ,false,dwDummy);
#else
                    BasicMultiplyReg2(nSize,nSize,nX,nY,nZ,false);
#endif
                    break;
                case 2:
#if(_CollectDetailedTimingData)
                    BasicMultiplyReg3(nSize,nSize,nX,nY,nZ,false,dwDummy);
#else
                    BasicMultiplyReg3(nSize,nSize,nX,nY,nZ,false);
#endif
                    break;
                case 3:
#if(_CollectDetailedTimingData)
                    BasicMultiplyReg4(nSize,nSize,nX,nY,nZ,false,dwDummy);
#else
                    BasicMultiplyReg4(nSize,nSize,nX,nY,nZ,false);
#endif
                    break;
                case 4:
#if(_CollectDetailedTimingData)
                    BasicMultiplyReg5(nSize,nSize,nX,nY,nZ,false,dwDummy);
#else
                    BasicMultiplyReg5(nSize,nSize,nX,nY,nZ,false);
#endif
                    break;
                case 5:
#if(_CollectDetailedTimingData)
                    BasicMultiplyReg6(nSize,nSize,nX,nY,nZ,fnTalse,dwDummy);
#else
                    BasicMultiplyReg6(nSize,nSize,nX,nY,nZ,false);
#endif
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
    CBigIntegerForTest nX,nY,nProduct,nProductBaseline;
    DWORD64            dwStartTime;
    CArithmeticBox     cBox;
    CWorkspace         cWork;
    size_t             nProductSize;
    printf("If you're not doing this with a retail build, you're not getting good numbers\n");
    // note size 5 DIGITs is the smallest size FFTMult will work with
#ifndef _USESMALLDIGITS
    for(size_t i=16; i<=((size_t) 1)<<31; i=i<<1)
#else
    for(size_t i=16; i<=((size_t) 1)<<31; i=i<<1)
#endif
    {
        size_t nFFTLength,nFieldSize,nChunkSize;
        BYTE   byChunkSize;
        SBitShift nRoot;
        nX.SetRandom(i);
        nY.SetRandom(i);
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
#if _CollectDetailedTimingData
        DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
        MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProductBaseline.GetValue(),cWork.GetSpace(),dwTimestamp,eTopLevel);
#else
        MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProductBaseline.GetValue(),cWork.GetSpace());
#endif
        dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        if(1000000>dwStartTime)
        {
            // redo -- looks like it takes a while to load the basic code, throwing off timing
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
#if _CollectDetailedTimingData
            DWORD64 dwTimestamp = s_Timer.GetMicroseconds();
            MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProductBaseline.GetValue(),cWork.GetSpace(),dwTimestamp,eTopLevel);
#else
            MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProductBaseline.GetValue(),cWork.GetSpace());
#endif
            dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        }
        ReportTimingData();
        printf("Non-FFT multiply:  %I64u microseconds\n",dwStartTime);
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
        ResetThresholdsForOptimization(); // so we DO use FFT multiply (if appropriate to the size)
        dwStartTime = s_Timer.GetMicroseconds();
#if _CollectDetailedTimingData
        dwTimestamp = dwStartTime;
        MultFFT(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProduct.GetValue(),cWork.GetSpace(),dwTimestamp,eTopLevel);
#else
        MultFFT(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProduct.GetValue(),cWork.GetSpace());
#endif
        dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        if(1000000>dwStartTime)
        {
            // redo -- looks like it takes a while to load the basic code, throwing off timing
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
#if _CollectDetailedTimingData
            dwTimestamp = dwStartTime;
            MultFFT(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProduct.GetValue(),cWork.GetSpace(),dwTimestamp,eTopLevel);
#else
            MultFFT(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProduct.GetValue(),cWork.GetSpace());
#endif
            dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        }
        ReportTimingData();
        nProductSize = nX.GetSize()+nY.GetSize();
        while(0<nProductSize && 0==nProduct.GetValue()[nProductSize-1])
        {
            nProductSize--;
        }
        nProduct.SetSize(nProductSize);
        printf("FFT multiply:      %I64u microseconds\tField size: %I64u Length: %I64u\n",dwStartTime, nFieldSize, nFFTLength);
        if(nProduct != nProductBaseline)
        {
            printf("Oopsie!\n");
        }
        ResetTimingData();
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
#if _CollectDetailedTimingData
        dwTimestamp = s_Timer.GetMicroseconds();
        SquareFFT(nX.GetSize(),nX.GetValue(),nProduct.GetValue(),cWork.GetSpace(),dwTimestamp,eTopLevel);
#else
        SquareFFT(nX.GetSize(),nX.GetValue(),nProduct.GetValue(),cWork.GetSpace());
#endif
        dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        if(1000000>dwStartTime)
        {
            // redo -- looks like loading the basic code takes a while, throwing off timing data
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
#if _CollectDetailedTimingData
            dwTimestamp = s_Timer.GetMicroseconds();
            SquareFFT(nX.GetSize(),nX.GetValue(),nProduct.GetValue(),cWork.GetSpace(),dwTimestamp,eTopLevel);
#else
            SquareFFT(nX.GetSize(),nX.GetValue(),nProduct.GetValue(),cWork.GetSpace());
#endif
            dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        }
        ReportTimingData();
        printf("FFT square:        %I64u microseconds\n\n",dwStartTime);
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
        MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProduct.GetValue(),cWork.GetSpace(),dwTimestamp,eTopLevel);
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
            MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProduct.GetValue(),cWork.GetSpace(),dwTimestamp,eTopLevel,&nProductSize);
#else
            MultUBackend(nX.GetSize(),nY.GetSize(),nX.GetValue(),nY.GetValue(),nProduct.GetValue(),cWork.GetSpace(),&nProductSize);
#endif
            dwStartTime = s_Timer.GetMicroseconds()-dwStartTime;
        }
        ReportTimingData();
        printf("Multiply two %i BYTE numbers:\t%I64u microseconds\n",nX.GetSize()*sizeof(DIGIT),dwStartTime);
        ResetTimingData();
        dwStartTime = s_Timer.GetMicroseconds();
#if(_CollectDetailedTimingData)
        dwTimestamp = dwStartTime;
        SquareUBackend(nX.GetSize(), nX.GetValue(), nProduct.GetValue(), cWork.GetSpace(), dwStartTime, eTopLevel);
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
            SquareUBackend(nX.GetSize(), nX.GetValue(), nProduct.GetValue(), cWork.GetSpace(), dwTimestamp, eTopLevel);
#else
            SquareUBackend(nX.GetSize(), nX.GetValue(), nProduct.GetValue(), cWork.GetSpace());
#endif
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        }
        ReportTimingData();
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
#if(_CollectDetailedTimingData)
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
            dwTimestamp = dwStartTime;
            MultUBackend(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue(), cWork.GetSpace(), dwTimestamp, eTopLevel);
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            if (TEST_BUFFERGUARD != cWork.GetSpace()[nMemoryNeeds])
            {
                printf("Overran workspace memory bounds for algorithm %i multiply.  Oops.\n", eAlgorithm);
                return;
            }
            ReportTimingData();
            printf("%I64u microseconds for algorithm %i for multiply size: %I64ux%I64u (BYTEs)\n", dwStartTime, eAlgorithm, nX.GetSize() * sizeof(DIGIT), nY.GetSize() * sizeof(DIGIT));
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
            dwTimestamp = dwStartTime;
            SquareUBackend(nX.GetSize(), nX.GetValue(), nProduct.GetValue(), cWork.GetSpace(), dwTimestamp, eTopLevel);
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            if (TEST_BUFFERGUARD != cWork.GetSpace()[nMemoryNeeds])
            {
                printf("Overran workspace memory bounds for algorithm %i square.  Oops.\n", eAlgorithm);
                return;
            }
            ReportTimingData();
            printf("%I64u microseconds for algorithm %i for square size:   %I64u (BYTEs)\n", dwStartTime, eAlgorithm, nX.GetSize() * sizeof(DIGIT));
#else
            dwStartTime = s_Timer.GetMicroseconds();
            MultUBackend(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue(), cWork.GetSpace());
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Algorithm %i for multiply size:    %I64ux%I64u (BYTEs): %I64u microseconds\n", eAlgorithm, nX.GetSize() * sizeof(DIGIT), nY.GetSize() * sizeof(DIGIT), dwStartTime);
            dwStartTime = s_Timer.GetMicroseconds();
            SquareUBackend(nX.GetSize(), nX.GetValue(), nProduct.GetValue(), cWork.GetSpace());
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Algorithm %i for square size:      %I64ux%I64u (BYTEs): %I64u microseconds\n", eAlgorithm, nX.GetSize() * sizeof(DIGIT), nX.GetSize() * sizeof(DIGIT), dwStartTime);
#endif
        }
        if(nProblemSize<=4000000)
        {
            // only do basic multiply comparison for relatively small problem sizes -- too slow!
            c_pnMultiplicationThresholds[eBasicMultiply] = 10000000000; // to force use of algorithm for any large problem
#if(_CollectDetailedTimingData)
            ResetTimingData();
            dwStartTime = s_Timer.GetMicroseconds();
            dwTimestamp = dwStartTime;
            MultUBackend(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue(), cWork.GetSpace(), dwTimestamp, eTopLevel);
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            ReportTimingData();
            printf("%I64u microseconds for basic multiply for multiply size: %I64ux%I64u (BYTEs)\n", dwStartTime, sizeof(DIGIT)*nProblemSize, sizeof(DIGIT)*nProblemSize);
            dwStartTime = s_Timer.GetMicroseconds();
            MultOracle(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue());
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("%I64u microseconds for mult oracle for multiply size: %I64ux%I64u (BYTEs)\n", dwStartTime, sizeof(DIGIT)*nProblemSize, sizeof(DIGIT)*nProblemSize);
#else
            dwStartTime = s_Timer.GetMicroseconds();
            MultUBackend(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue(), cWork.GetSpace());
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Basic multiply for multiply size: %I64ux%I64u (BYTEs): %I64u microseconds\n", nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime);
            dwStartTime = s_Timer.GetMicroseconds();
            MultOracle(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct.GetValue());
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Mult oracle for multiply size:    %I64ux%I64u (BYTEs): %I64u microseconds\n", nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime);
#endif
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
*/
void CArithmeticPerformanceTester::CompareDivideTimes()
{
    size_t             nWorkspaceMemoryNeeds;
    const unsigned int c_nMinSize = 1000, c_nMaxSize = 100000000; // my system can allocate enough memory for 100,000,000 -- but not 1,000,000,000
    CBigIntegerForTest nX, nXCopy, nY, nProduct1, nProduct2, nDiv;
    DWORD64            dwStartTime, dwMultTime;
#if(_CollectDetailedTimingData)
    DWORD64 dwTimestamp;
    s_Timer.Start();
#endif
    unsigned int       nIterations;
    CWorkspace         cWork;
    size_t             nDivSize, nRemainderSize;
    ResetThresholdsForOptimization();
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
        // find out how many iterations needed to take 10+ seconds for the given multiply size
        nIterations = 1;
        do
        {
#if(_CollectDetailedTimingData)
            ResetTimingData();
#endif
            dwStartTime = s_Timer.GetMicroseconds();
            for (int i=0; i<nIterations; i++)
            {
#if(_CollectDetailedTimingData)
                dwTimestamp = s_Timer.GetMicroseconds();
                MultUBackend(nX.GetSize(), nX.GetSize(), nX.GetValue(), nY.GetValue(), nProduct1.GetValue(), cWork.GetSpace(), dwTimestamp, eTopLevel);
#else
                MultUBackend(nX.GetSize(), nX.GetSize(), nX.GetValue(), nY.GetValue(), nProduct1.GetValue(), cWork.GetSpace());
#endif
            }
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            if(1000000<dwStartTime) break; // 10 seconds better?  Or 1 second?
            nIterations *= 2;
        }
        while (true);
        printf("Time for %i %ix%i BYTE multiplications: %I64u microseconds\n", nIterations, nX.GetSize()*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime);
#if(_CollectDetailedTimingData)
        ReportTimingData();
        printf("\n");
        ResetTimingData();
#endif
        dwMultTime = dwStartTime;
        if(nX.GetSize()<=1000000)
        {
            // bigger numbers just too slow!  Works fine.  You have been warned.
            dwStartTime = s_Timer.GetMicroseconds();
            for (int i=0; i<nIterations; i++)
            {
                memcpy(nProduct2.m_pnValue, nProduct1.m_pnValue, (nX.GetSize() + nX.GetSize())*sizeof(DIGIT));
                DivideBasic(nX.GetSize() + nX.GetSize(), nX.GetSize(), nProduct2.GetValue(), nX.GetValue(), nDiv.GetValue());
            }
            dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
            printf("Time for %i divisions of %i BYTE number by %i BYTE number: %I64u microseconds (divide:multiply ratio: %f) -- basic\n", nIterations, 2*nX.GetSize()*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime, (float) dwStartTime/dwMultTime);
        }
#if(_CollectDetailedTimingData)
        ReportTimingData();
        printf("\n");
        ResetTimingData();
#endif
        dwStartTime = s_Timer.GetMicroseconds();
        for (int i=0; i<nIterations; i++)
        {
            memcpy(nProduct2.m_pnValue, nProduct1.m_pnValue, (nX.GetSize() + nX.GetSize())*sizeof(DIGIT));
            Divide(nX.GetSize() + nX.GetSize(), nX.GetSize(), nDivSize, nRemainderSize, nProduct2.GetValue(), nX.GetValue(), nDiv.GetValue(), cWork.GetSpace());
        }
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        printf("Time for %i divisions of %i BYTE number by %i BYTE number: %I64u microseconds (divide:multiply ratio: %f)\n", nIterations, 2*nX.GetSize()*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime, (float) dwStartTime/dwMultTime);
#if(_CollectDetailedTimingData)
        ReportTimingData();
        printf("\n");
        ResetTimingData();
#endif
        dwStartTime = s_Timer.GetMicroseconds();
        for (int i=0; i<nIterations; i++)
        {
#if(_CollectDetailedTimingData)
            dwTimestamp = s_Timer.GetMicroseconds();
            MultUBackend(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct1.GetValue(), cWork.GetSpace(), dwTimestamp, eTopLevel);
#else
            MultUBackend(nX.GetSize(), nY.GetSize(), nX.GetValue(), nY.GetValue(), nProduct1.GetValue(), cWork.GetSpace());
#endif
        }
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        dwMultTime  = dwStartTime;
        printf("Time for %i %ix%i BYTE multiplications: %I64u microseconds\n", nIterations, nX.GetSize()*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime);
#if(_CollectDetailedTimingData)
        ReportTimingData();
        printf("\n");
        ResetTimingData();
#endif
        dwStartTime = s_Timer.GetMicroseconds();
        for(int i=0; i<nIterations; i++)
        {
            memcpy(nProduct2.m_pnValue, nProduct1.m_pnValue, (nX.GetSize() + nY.GetSize())*sizeof(DIGIT));
            Divide(nX.GetSize() + nY.GetSize(), nX.GetSize(), nDivSize, nRemainderSize, nProduct2.GetValue(), nX.GetValue(), nDiv.GetValue(), cWork.GetSpace());
        }
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        printf("Time for %i divisions of %i BYTE number by %i BYTE number: %I64u microseconds (divide:multiply ratio: %f)\n", nIterations, (nX.GetSize() + nY.GetSize())*sizeof(DIGIT), nX.GetSize()*sizeof(DIGIT), dwStartTime, (float) dwStartTime/dwMultTime);
#if(_CollectDetailedTimingData)
        ReportTimingData();
        printf("\n");
        ResetTimingData();
#endif
        dwStartTime = s_Timer.GetMicroseconds();
        for(int i=0; i<nIterations; i++)
        {
            memcpy(nProduct2.m_pnValue, nProduct1.m_pnValue, (nX.GetSize() + nY.GetSize())*sizeof(DIGIT));
            Divide((nX.GetSize() + nY.GetSize()), nY.GetSize(), nDivSize, nRemainderSize, nProduct2.GetValue(), nY.GetValue(), nDiv.GetValue(), cWork.GetSpace());
        }
        dwStartTime = s_Timer.GetMicroseconds() - dwStartTime;
        printf("Time for %i divisions of %i BYTE number by %i BYTE number: %I64u microseconds (divide:multiply ratio: %f)\n", nIterations, (nX.GetSize() + nY.GetSize())*sizeof(DIGIT), nY.GetSize()*sizeof(DIGIT), dwStartTime, (float) dwStartTime/dwMultTime);
#if(_CollectDetailedTimingData)
        ReportTimingData();
        printf("\n");
#endif
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
        ReportTimingData();
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
*/
void CArithmeticPerformanceTester::GCDTimes()
{
    CRandomGenerator   cRandom;
    CBigInteger        x, y;
    bool               bXCoefNeg;
    size_t             nGCDSize, nXCoefSize, nYCoefSize;
    const unsigned int c_nMaxDigits          = 0x1000;
    const unsigned int c_nStartingIterations = 0x1000000;
    unsigned int       nIterations           = c_nStartingIterations;
    DIGIT              *pGCD                 = (DIGIT *) malloc(sizeof(DIGIT)*200000000); // more than enough
    DIGIT              *pXCoef               = pGCD   + c_nMaxDigits;
    DIGIT              *pYCoef               = pXCoef + c_nMaxDigits + 1; // need 1 extra DIGIT for overflow during internal calculations
    DIGIT              *pWorkspace           = pYCoef + c_nMaxDigits + 1; // need 1 extra DIGIT for overflow during internal calculations
    x.Reserve(c_nMaxDigits);
    y.Reserve(c_nMaxDigits);
    for(int nDigits=1; nDigits<=c_nMaxDigits; nDigits=(nDigits<<1))
    {
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
            if (x<y)
            {
                GCDCoef(y.GetSize(), x.GetSize(), nGCDSize, nYCoefSize, nXCoefSize, y.GetValue(), x.GetValue(), pGCD, pYCoef, pXCoef, bXCoefNeg, pWorkspace);
                bXCoefNeg = !bXCoefNeg; // since x, y swapped order
            }
            else
            {
                GCDCoef(x.GetSize(), y.GetSize(), nGCDSize, nXCoefSize, nYCoefSize, x.GetValue(), y.GetValue(), pGCD, pXCoef, pYCoef, bXCoefNeg, pWorkspace);
            }
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to get the GCD of %i pairs of %i-byte numbers:              %i milliseconds\n", nIterations, nDigits*sizeof(DIGIT), nTime);
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
            if (x<y)
            {
                GCDCoef(y.GetSize(), x.GetSize(), nGCDSize, nYCoefSize, nXCoefSize, y.GetValue(), x.GetValue(), pGCD, NULL, pXCoef, bXCoefNeg, pWorkspace);
                bXCoefNeg = !bXCoefNeg; // since x, y swapped order
            }
            else
            {
                GCDCoef(x.GetSize(), y.GetSize(), nGCDSize, nXCoefSize, nYCoefSize, x.GetValue(), y.GetValue(), pGCD, pXCoef, NULL, bXCoefNeg, pWorkspace);
            }
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to get the GCD of %i pairs of %i-byte numbers, x-coef only: %i milliseconds\n", nIterations, nDigits*sizeof(DIGIT), nTime);
        nIterations /= 2;
    }
    free(pGCD);
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
        cRandom.RandomBits(nBits/c_nDigitSize, nBits%c_nDigitSize, true, nBase);
        cRandom.RandomBits(nBits/c_nDigitSize, nBits%c_nDigitSize, true, nPower);
        cRandom.RandomBits(nBits/c_nDigitSize, nBits%c_nDigitSize, true, nModulus);
        nResult.Reserve(2*nModulus.GetSize()+1);
        nModulus.GetValue()[0] |= 1; // force the modulus to be odd, so it is suitable for Montgomery
        // first, standard power modulus
        nTime = ::GetTickCount();
        for(int i=0;i<nIterations; i++)
        {
            PowerModulus(nBase.GetSize(), nPower.GetSize(), nModulus.GetSize(), nPowerModSize, nBase.GetValue(), nPower.GetValue(), nModulus.GetValue(), nResult.GetValue(), pnWorkspace);
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i  standard  power-modulus operations of size %i bits: %i milliseconds\n", nIterations, nBits, nTime);
        // Then, Montgomery power-modulus
        nNPrime.Reserve(nModulus.GetSize());
        nRPrime.Reserve(nModulus.GetSize());
        GetMontgomeryParameters(nModulus.GetSize(), nNPrimeSize, nRPrimeSize, nModulus.GetValue(), nNPrime.GetValue(), nRPrime.GetValue(), pnWorkspace);
        GetLeadBit(nModulus.GetSize(), nModulus.GetValue(), nLeadDigit, nLeadBit);
        nPowerModulus.Reserve(2*nModulus.GetSize() + 1);
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
        if(c_nDigitSize*4 == nSize) nSize -= c_nDigitSize;
        else if(c_nDigitSize*6 == nSize) nSize -= (2*c_nDigitSize);
        nX1.SetRandom(nSize);
        nSqrtX.Reserve(nX1.GetSize()+1); // extra digit for overflow --  only needed in single-digit case
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
            SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i square roots of a %i bit number (Newton):                  %i milliseconds (%f average)\n",nTests,nSize,nTime,((float) nTime)/nTests);
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
            GeneralSquareRootNewton(nX2.GetSize(), nX1.GetSize(), nRootSize, nX2.GetValue(), nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i square roots of a %i bit number using general Newton:      %i milliseconds (%f average)\n",nTests,nSize,nTime,((float) nTime)/nTests);
        nTime = ::GetTickCount();
        for(int i=0; i<nTests; i++)
        {
            SquareRootRecursive(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
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
            GeneralSquareRootNewton(nX2.GetSize(), nX1.GetSize(), nRootSize, nX2.GetValue(), nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
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
            GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), pWorkspace);
        }
        nTime = ::GetTickCount() - nTime;
        printf("Time to do %i general roots of a %i, %i bit numbers: Recursive:          %i milliseconds (%f average)\n",nTests,2*nSize/3,nSize,nTime,((float) nTime)/nTests);
        nTests /= 2;
    }
    nX1.SetRandom(c_nMaxBitSize*64);
    nSqrtX.Reserve(nX1.GetSize());
    nX2Copy.Reserve(nX1.GetSize()+1); // needs more working space
    nTime   = ::GetTickCount();
    SquareRootRecursive(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
    nSqrtX.SetSize(nRootSize);
    printf("And the time to do a single %i bit square root using the full algorithm: %i milliseconds\n",c_nMaxBitSize*64,::GetTickCount()-nTime);
    nTime   = ::GetTickCount();
    SquareRootNewton(nX1.GetSize(), nRootSize, nX1.GetValue(), nSqrtX.GetValue(), pWorkspace);
    printf("Simple Newton:                                                                 %i milliseconds\n",::GetTickCount()-nTime);
    nX2.SetRandom(nX1.GetSize()*c_nDigitSize/2);
    nX1Copy = nX1;
    nX2Copy = nX2;
    nTime   = ::GetTickCount();
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), pWorkspace);
    printf("General recursive (half-size x1):                                              %i milliseconds\n", ::GetTickCount() - nTime);
    nX2.SetRandom(nX1.GetSize()*c_nDigitSize*2/3);
    nX1Copy = nX1;
    nX2Copy = nX2;
    nTime   = ::GetTickCount();
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), pWorkspace);
    printf("General recursive (two thirds-size x1):                                        %i milliseconds\n", ::GetTickCount() - nTime);
    nX2.SetRandom(nX1.GetSize()*c_nDigitSize/3);
    nX1Copy = nX1;
    nX2Copy = nX2;
    nTime   = ::GetTickCount();
    GeneralSquareRootRecursive(nX2Copy.GetSize(), nX1Copy.GetSize(), nRootSize, nX2Copy.GetValue(), nX1Copy.GetValue(), nSqrtX.GetValue(), pWorkspace);
    printf("General recursive (one third-size x1):                                         %i milliseconds\n", ::GetTickCount() - nTime);
    nTime = ::GetTickCount();
    if (eOperationSucceeded != cBox.Square(nSqrtX, nX2))
    {
        printf("Square failed\n");
    }
    printf("And, for comparison, squaring that square root again:                          %i milliseconds\n",::GetTickCount()-nTime);
    nTime   = ::GetTickCount();
    if (eOperationSucceeded != cBox.Divide(nX1, nSqrtX, nX2, nExtra))
    {
        printf("Divide failed\n");
    }
    printf("And to divide that large number by its square root:                            %i milliseconds\n",::GetTickCount()-nTime);
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
                nBigInt.SetRandom(c_nDigitSize);
                nBigInt.SetNegative(rand()%2);
                nMat1[i][j] = nBigInt;
                nBigInt.SetRandom(c_nDigitSize);
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
                    nBigInt.SetRandom(nDigits*c_nDigitSize);
                    nBigInt.SetNegative(rand()%2);
                    nMat1[i][j] = nBigInt;
                    nBigInt.SetRandom(nDigits*c_nDigitSize);
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