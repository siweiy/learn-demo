/*
    C++11特性
*/

#include <iostream>
#include <vector>
#include <array>
#include <initializer_list>
#include <algorithm>

// decltype
// 拖尾返回类型
// template <typename T, typename U>
template<typename T = int, typename U = int> // 默认参数
auto add(T x, U y) -> decltype(x + y) // c++11
// auto add(T x, U y) // c++14
{
    return x + y;
}

class A {
public:
    A(int _a, float _b): a(_a), b(_b) {}
private:
    int a;
    float b;
};

class Magic {
public:
    Magic(std::initializer_list<int> list) {
        std::cout << *list.begin() << std::endl;
    }
};

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

// 委托构造
class Base {
public:
    int value1;
    int value2;
    Base() {
        value1 = 1;
    }
    Base(int value) : Base() {  // 委托 Base() 构造函数
        value2 = 2;
    }
};

// 继承构造
struct D
{
    D(int i) { std::cout << "1" << std::endl; }
    D(double d,int i){ std::cout << "2" << std::endl; }
    D(float f,int i,const char* c){ std::cout << "3" << std::endl; }
    //...等等系列的构造函数版本
};
struct E:D
{
    using D::D;
    //关于基类各构造函数的继承一句话搞定
    //......
};

void foo(int *p, int len) {
    return;
}

int main()
{
    // nullptr
    // char *ptr = nullptr;

    // constexpr
    // constexpr int num = 5;

    // auto
    // for(auto itr = vec.begin(); itr != vec.end(); ++itr);

    // decltype
    // int i = 0, j = 2;
    // std::cout << add(i, j) << std::endl;

    // 区间迭代
    // std::vector<int> v(2, 10);
    // for (auto &i : v)
    // {
    //     std::cout << i << std::endl;
    // }

    // 初始化列表
    // A a{1, 20.2};
    // Magic magic = {1,2,3,4,5};
    // std::vector<int> v1 = {1, 2, 3, 4};

    // 尖括号 >, 使得模板使用 >> 合法
    // std::vector<std::vector<int>> wow;

    // 类型别名模板
    // NewType<int> t(5);

    // // 继承构造
    // E b(1);
    // E c(2.2, 1);
    // E d(2.2, 1, "111");

    // Lambda 表达式
    // 1) []不捕获任何变量。
    // 2) [&]捕获外部作用域中所有变量，并作为引用在函数体中使用（按引用捕获）。
    // 3) [=]捕获外部作用域中所有变量，并作为副本在函数体中使用(按值捕获)。注意值捕获的前提是变量可以拷贝，且被捕获的变量在
    // 4) [=,&foo]按值捕获外部作用域中所有变量，并按引用捕获foo变量。
    // 5) [bar]按值捕获bar变量，同时不捕获其他变量。
    // 6) [this]捕获当前类中的this指针，让lambda表达式拥有和当前类成员函数同样的访问权限。如果已经使用了&或者=，就默认添加此选项
    // int a = 0;
    // auto f1 = [=] { return a; };
    // a+=1;
    // std::cout << f1() << std::endl;       //输出0

    // int b = 0;
    // auto f2 = [&b] { return b; };
    // b+=1;
    // std::cout << f2() << std::endl;       //输出1

    // int a = 0;
    // // auto f1 = [=] { return a++; };                //error
    // auto f2 = [=] () mutable { return a++; };       //OK

    // auto a = [] { std::cout << "A" << std::endl; };
    // auto b = [] { std::cout << "B" << std::endl; };
    // // a = b;   // 非法，lambda无法赋值
    // auto c = a;   // 合法，生成一个副本

    // std::vector<int> v(10);
    // int a = 0;
    // int b = 1;
    // std::generate(v.begin(), v.end(), [&a, &b] { int value = b; b = b + a; a = value; return value; });

    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
    // int even_count = 0;
    // for_each(v.begin(), v.end(), [&even_count](int val){
    //     if(!(val & 1)){
    //         ++ even_count;
    //     }
    // });
    // std::cout << "The number of even is " << even_count << std::endl;

    // 新增容器 std::array
    // std::array 保存在栈内存中，相比堆内存中的 std::vector，我们能够灵活的访问这里面的元素，从而获得更高的性能
    // std::array<int, 4> arr = {1,2,3,4};
    // // C 风格接口传参
    // // foo(arr, arr.size());           // 非法, 无法隐式转换
    // foo(&arr[0], arr.size());
    // foo(arr.data(), arr.size());
    // // 使用 `std::sort`
    // std::sort(arr.begin(), arr.end());


    return 0;
}