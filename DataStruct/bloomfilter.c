/*
    假设：有一个待检测的值：25
    第一步：将25化为二进制11001
    第二步：分别取奇数位和偶数位各自化成整数，比如上例：红色的奇数位：101，是5；偶数位10，是2（这两个就是生成的hashfunc）
    第三步：对Bit Array总位数取模，也就是哈希运算，
    5 mod1 1=5，将索引5位的数置1
    2 mod1 1=2，将索引2的数置1
*/  

#include <stdio.h>

int main(int argc, char const *argv[])
{
    
    return 0;
}
