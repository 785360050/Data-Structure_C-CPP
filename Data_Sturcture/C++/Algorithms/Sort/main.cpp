

// 生成一个可以复用的随机数组序列


void TestSort()
{
    int n = 10;
    SortList *l = generateRandomArray(n, 0, n);

    SortList_Show(l);

    // testSort("Directly Insert Sort", Sort_Insert_Direct, l);
    // testSort("Optimized Directly Insert Sort", Sort_Insert_Direct_Optimized, l);
    // testSort("Shell Sort", Sort_Insert_Shell, l);
    // testSort("Bubble Sort", Sort_Bubble_Classic, l);
    // testSort("Bubble Sort Optimized 1", Sort_Bubble_Optimized_1, l);
    // testSort("Bubble Sort Optimized 2", Sort_Bubble_Optimized_2, l);
    // testSort("Quick Sort Double Way", Sort_Quick_DoubleWay, l);
    // testSort("Quick Sort Single Way", Sort_Quick_SingleWay, l);
    // testSort("Heap Sort", Sort_Heap, l);
    testSort("Binary Merge Sort", Sort_Merge, l);

    SortList_Show(l);
    SortList_Destroy(l);
}