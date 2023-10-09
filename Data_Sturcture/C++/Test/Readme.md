
# 每个单元测试的文件可以单独编译并执行
例：编译单元测试文件，然后检查内存泄漏
1. g++ Link_Stack.cpp -g -o Link_Stack -Wall -Wextra -lboost_unit_test_framework -std=c++20
2. valgrind --leak-check=full -s ./Link_Stack 

```bash
jevon@Kubuntu:/mnt/WorkSpace/GitHub/Data-Structure_C-CPP/Data_Sturcture/C++/Test/Unit_Test/Linear_Stucture/Linear_Stack$ g++ Link_Stack.cpp -g -o Link_Stack -Wall -Wextra -lboost_unit_test_framework -std=c++20
jevon@Kubuntu:/mnt/WorkSpace/GitHub/Data-Structure_C-CPP/Data_Sturcture/C++/Test/Unit_Test/Linear_Stucture/Linear_Stack$ valgrind --leak-check=full -s ./Link_Stack 
==39095== Memcheck, a memory error detector
==39095== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==39095== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==39095== Command: ./Link_Stack
==39095== 
Running 5 test cases...
Pramater Constructed [0-0-0]:{1,1}
Move Constructed [0-0-1]:{1,1} from [0-0-0]:{1,Null}
Deconstructed [0-0-0]:{1,Null}
Pramater Constructed [1-0-0]:{2,2}
Move Constructed [1-0-1]:{2,2} from [1-0-0]:{2,Null}
Deconstructed [1-0-0]:{2,Null}
Pramater Constructed [2-0-0]:{3,3}
Move Constructed [2-0-1]:{3,3} from [2-0-0]:{3,Null}
Deconstructed [2-0-0]:{3,Null}
Pramater Constructed [3-0-0]:{4,4}
Move Constructed [3-0-1]:{4,4} from [3-0-0]:{4,Null}
Deconstructed [3-0-0]:{4,Null}
Pramater Constructed [4-0-0]:{5,5}
Move Constructed [4-0-1]:{5,5} from [4-0-0]:{5,Null}
Deconstructed [4-0-0]:{5,Null}
Pramater Constructed [5-0-0]:{5,5}
Deconstructed [5-0-0]:{5,5} pointer deleted
Deconstructed [4-0-1]:{5,5} pointer deleted
Pramater Constructed [6-0-0]:{4,4}
Deconstructed [6-0-0]:{4,4} pointer deleted
Deconstructed [3-0-1]:{4,4} pointer deleted
Pramater Constructed [7-0-0]:{3,3}
Deconstructed [7-0-0]:{3,3} pointer deleted
Deconstructed [2-0-1]:{3,3} pointer deleted
Pramater Constructed [8-0-0]:{2,2}
Deconstructed [8-0-0]:{2,2} pointer deleted
Deconstructed [1-0-1]:{2,2} pointer deleted
Pramater Constructed [9-0-0]:{1,1}
Deconstructed [9-0-0]:{1,1} pointer deleted
Deconstructed [0-0-1]:{1,1} pointer deleted

*** No errors detected
==39095== 
==39095== HEAP SUMMARY:
==39095==     in use at exit: 0 bytes in 0 blocks
==39095==   total heap usage: 3,136 allocs, 3,136 frees, 283,232 bytes allocated
==39095== 
==39095== All heap blocks were freed -- no leaks are possible
==39095== 
==39095== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```