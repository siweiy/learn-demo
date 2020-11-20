/*
    格式化输出库 Boost.Format
*/
#include <iostream>
#include "boost/format.hpp"

int main(int argc, char const *argv[])
{
    std::cout << \
    // Boost.Format 类使用置于两个百分号之间的数字作为占位符
    // boost::format("%1%.%2%.%3%") % 16 % 9 % 2008 // 16.9.2008
    boost::format("%2%.%1%.%3%") % 16 % 9 % 2008 // 9.16.2008
    << std::endl; 
    

    std::cout << \
    // 因为操作器 std::showpos() 通过 boost::io::group() 与数字 99 连接，
    // 所以只要显示 99 ， 在它前面就会自动加上 + 号
    boost::format("%1% %2% %1%") % boost::io::group(std::showpos, 99) % 100
    << std::endl;

    // 如果需要 + 号仅在 99 第一次输出时显示， 则需要改造格式化占位符
    std::cout << boost::format("%|1$+| %2% %1%") % 99 % 100 << std::endl; 

    // 不引用数据的方法
    std::cout << boost::format("%|+| %|| %||") % 99 % 100 % 99 << std::endl; 

    // 这看起来就像 std::printf() ，但是 Boost.Format 库有类型安全的优点
    std::cout << boost::format("%+d %5d %d") % 99 % 100 % 99 << std::endl; 

    std::cout << boost::format("%+s %s %s") % "ccc" % 100 % 99 << std::endl; 

    return 0;
}
