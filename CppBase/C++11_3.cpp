#include <iostream>
#include <typeinfo>
using namespace std;

template <class T>
void f2(T &&t)
{

    const type_info &t0 = typeid(t);
    const type_info &t1 = typeid(int);
    cout << (t0.name() == t1.name()) << ":" << t << endl;
}

template <class T>
void f3(T &&val)
{
    T t = val;
}


template <class F, class T1, class T2>
void flip(F f, T1&& t1, T2&& t2) {
    f(forward<T2>(t2), forward<T1>(t1));
}

int main(int argc, char const *argv[])
{
    int num = 10;
    // int && a = num;  //右值引用不能初始化为左值
    int &&a = 10;

    a = 100;
    cout << a << endl;
    int i = 0;
    const int ci = 2;
    f2(move(i)); //i是一个int，模板参数类型T是int，因为非const可以转化为const
    f2(ci);      //ci是一个const int，模板参数T是int
    f2(5);

    f3(i);
    f3(ci);
    f3(5);


    return 0;
}
