#include <iostream>
#include <type_traits>
#include <typeinfo>
using namespace std;

// 元编程
template <int N, int M>
struct meta_func
{
    static const int value = N + M;
};

#if 0
using one_type = std::integral_constant<int, 1>;
#else
template <class T>
struct one_type : std::integral_constant<int, 1>
{
};
#endif

template<typename T>
struct PointerOf
{
    using Result = T*;
};
 
template<typename T>
struct Pointer2Of
{
    using Result = typename PointerOf<typename PointerOf<T>::Result>::Result;
};
 
int* pi;
Pointer2Of<int>::Result ppi = &pi;

// #define __pointer(...) typename PointerOf<__VA_ARGS__>::Result
 
// template<typename T>
// struct Pointer2Of
// {
//     using Result = __pointer(__pointer(T));
// };

int main(int argc, char const *argv[])
{
    int i = 1, j = 2;

    cout << meta_func<1, 2>::value << endl;
    cout << one_type<int>::value << endl;

    typedef std::conditional<true, int, float>::type A;  // int
    typedef std::conditional<false, int, float>::type B; // float

    typedef std::conditional<(sizeof(long long) > sizeof(long double)),
                             long long, long double>::type max_size_t;

    cout << typeid(max_size_t).name() << endl;


    return 0;
}
