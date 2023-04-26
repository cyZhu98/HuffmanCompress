# 数据结构作业

**本项目为fork版，对原版部分内容改进，包括如下**

* 用```priority_queue```替代原项目的手写最小堆
* 优化逻辑，部分内容加上引用、或替换为指针
* 更多的使用vector
* 删除多余成员
* 一些错误处理

# TODO

bug: 解压版本后有多余字母

如果中文乱码，是因为原项目使用GBK格式

精力有限，没有理解和修改数据流写入与读取部分

# 项目要求

采用哈夫曼编码思想实现文件的压缩和解压功能，并提供压缩前后的占用空间之比。

# 使用方法

CMake；；VS加入源文件；；```g++ -o main main.cpp BitStream.cpp BitStream.hpp HuffmanTree.cpp HuffmanTree.h ``` ++ ```./main```
