#include "serializer.h"
#include <iostream>

//自定义类型需要重载操作符>>和<<
class foo {
public:
    foo() {}
    foo(int a, std::string s) : n(a), str(s) {}
    friend Serializer& operator>>(Serializer& in, foo& f)
    {
        in >> f.n >> f.str;
        return in;
    }
    friend Serializer& operator<<(Serializer& out, foo& f)
    {
        out << f.n << f.str;
        return out;
    }

	int n;
    std::string str;
};

// 测试原生类型的序列化和反序列化
void test1()
{
    int a = 100;
    std::string c = "hello";
    Serializer sr;
    sr << a << c;  //序列化

	std::cout << sr.toString() << std::endl;

    int b = 0;
    std::string d;
    sr >> b >> d; //反序列化
    std::cout << "b=" << b << ", d=" << d << std::endl;
}

//测试自定义类型的序列化和反序列化
void test2()
{
    foo a(100, "2020-09-26");
    Serializer sr;
    sr << a;

	std::cout << sr.toString() << std::endl;

    foo b;
    sr >> b;
    std::cout << "b.n=" << b.n << ", b.str=" << b.str << std::endl;
}

int main(int argc, char** argv)
{
    test1();
    test2();
    return 0;
}