#include <iostream>
using namespace std;

#if 1
template <typename T, typename U>
// decltype(T() + U()) add(T t, U u)
auto add(T t, U u) -> decltype(t + u) // 推荐使用 --》 返回类型后置（trailing-return-type，又称跟踪返回类型）语法
{
    return t + u;
}

#else

// 考虑到 T、U 可能是没有无参构造函数的类，正确的写法应该是这样
template <typename T, typename U>
decltype((*(T*)0) + (*(U*)0)) add(T t, U u)
{
    return t + u;
}

#endif

void operator"" _log(unsigned long long n) {
    cout << n << endl;
}


// 类型别名模板
template< typename T, typename U>
class SuckType {
public:
    T a;
    U b;
    SuckType(int value):a(value),b(value){}
};

template <typename T>
using NewType = SuckType<int, T>;    // 合法

void test1()
{
    5_log;
    NewType<int> a(2);
    cout << add(10, '1') << endl;
}

int main(int argc, char const *argv[])
{
    test1();

    return 0;
}
