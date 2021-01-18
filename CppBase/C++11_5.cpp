#include <iostream>
#include <vector>
#include <deque>
using namespace std;

template <typename T, template <typename Elem, typename Allocator = std::allocator<Elem>> class Container = std::vector>
struct Stack
{
    // 这个时候Container已经带参数了
    Container<T> elems;
};

// 数值计算，编译期得到答案，不重要，会产生时间消耗
template<int X, int Y>
struct Caculate
{
    enum    // 定义成员变量
    {
        Sum = X + Y,
        Dec = X - Y,
        Mul = X * Y,
        Div = X / Y
    };
};

// using关键字来专门定义类型别名,即代替typedef
template<typename T>
struct PointerOf
{
    // typedef T* Type;
    using Type = T*;
};

// 模板递归
template<int N>
struct Factorial
{
    enum { Value = N * Factorial<N - 1>::Value };
};

// 全特化
template<>
struct Factorial<1>
{
    enum { Value = 1 };
};

int main(int argc, char const *argv[])
{
    Stack<int, std::deque> intStack;
    intStack.elems.push_back(-1);

    PointerOf<const char>::Type s = "Hello world!";

    clock_t start = clock();

    // 分别获得10和2的加减乘除的结果
    Caculate<10, 2>::Sum;
    Caculate<10, 2>::Dec;
    Caculate<10, 2>::Mul;
    Caculate<10, 2>::Div;

    Factorial<10>::Value;
    clock_t end = clock();

    cout << (end-start) << "us"<< endl;

    return 0;
}
