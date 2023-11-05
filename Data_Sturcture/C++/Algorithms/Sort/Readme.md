

排序算法，测试用例全部以vector为容器，兼容性好一些

所有的排序算法在namespace Sort下
按不同的分类，写在不同的文件中


由于算法的实现有较大变数，所以在可能变化的地方做了处理，注释或者用virtual修饰
尽可能不用stl函数实现，因为可以用stl简化，但是stl展开就不那么容易了
涉及到优化和改进的排序算法实现在namespace Sort::Optimize下，暂时未完成
也就是说namespace Sort下的算法都是最简单原始也是最经典的实现

目前已完成
# 插入排序
- 直接插入排序
- 希尔排序

# 交换排序
- 冒泡排序
- 快速排序

# 选择排序
- 直接选择排序
- 堆排序

推荐资料
Wikipedia: https://zh.wikipedia.org/wiki/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95
