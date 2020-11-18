/*
    函数对象
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/bind.hpp>
using namespace std;

namespace Boost_Bind{// Boost.Bind && Boost.Ref

    void printv(int num) {
        std::cout << num << std::endl;
    }

    // 函数对象
    class Add : public std::binary_function<int, int, void>// 参1、参2、返回类型
    {
    public:
        void operator()(int i, int j) const {// 仿函数
            cout << i + j << endl;
        }
    };

    void Add2(int i, int j) {
        cout << i + j << endl;
    }

    void Add3(int i, int j, std::ostream &out) { 
        out << i + j << std::endl; 
    }

    bool compare(int i, int j) { 
        return i > j; 
    } 

    void test() {
        std::vector<int> v;
        v.push_back(1);
        v.push_back(3);
        v.push_back(2);

        std::for_each(v.begin(), v.end(), printv);

        std::for_each(v.begin(), v.end(), std::bind1st(Add(), 10));
        std::for_each(v.begin(), v.end(), boost::bind(Add2, 10, _1));// 一元函数

        // std::sort(v.begin(), v.end(), compare);
        std::sort(v.begin(), v.end(), boost::bind(compare, _1, _2));// 二元函数,（降序多余操作）
        std::sort(v.begin(), v.end(), boost::bind(compare, _2, _1));// 二元函数,（升序操作）

        // 要以引用方式传递常量对象，可以使用模板函数 boost::cref()
        std::for_each(v.begin(), v.end(), boost::bind(Add3, 10, _1, boost::ref(std::cout)));

        for (unsigned int i = 0; i < v.size(); i++) {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;
    }
}

#include "boost/function.hpp"

namespace Boost_Function {// Boost.Function
    
    struct world { 
        void Hello(std::ostream &out) { 
            out << "Hello, world!" << std::endl; 
        } 
    }; 

    void test() {
        boost::function<int (const char *)> FUNC = std::atoi;
        std::cout << FUNC("100") << std::endl;
        FUNC = std::strlen;
        std::cout << FUNC("123456") << std::endl;

        try { 
            boost::function<int (const char*)> f; 
            f(""); 
        } 
        catch (boost::bad_function_call &ex) { 
            std::cout << ex.what() << std::endl; 
        }

        boost::function<void (world*, std::ostream&)> f = &world::Hello; 
        world w; 
        f(&w, boost::ref(std::cout));
    }
}

#include "boost/lambda/lambda.hpp"
#include "boost/lambda/if.hpp"

namespace Boost_Lambda{// Boost.Lambda

    void test() {
        std::vector<int> v; 
        v.push_back(1); 
        v.push_back(3); 
        v.push_back(2);

        // 要插入换行的话，必须用 "\n" 来替代 std::endl 才能成功编译
        std::for_each(v.begin(), v.end(), std::cout << boost::lambda::_1 << "\n");

        // 只将大于1的元素写出到标准输出流
        std::for_each(v.begin(), v.end(), boost::lambda::if_then(boost::lambda::_1 > 1, \
        std::cout << boost::lambda::_1 << "\n"));
    }
}


class divide_by : public std::binary_function<int, int, int> 
{ 
public: 
    int operator()(int n, int div) const 
    { 
        return n / div;
    } 
};

int divide_by2(int n, int div) {
    return n / div;
}

void test() {
    std::vector<int> numbers; 
    numbers.push_back(10); 
    numbers.push_back(20); 
    numbers.push_back(30); 

    // std::transform(numbers.begin(), numbers.end(), numbers.begin(), std::bind2nd(divide_by(), 2));
    // std::transform(numbers.begin(), numbers.end(), numbers.begin(), boost::bind(divide_by2, 2, _1));

    for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << std::endl; 
    }  
}


int main(int argc, char const *argv[])
{
    // Boost_Bind::test();
    // Boost_Function::test();
    // Boost_Lambda::test();
    test();

    return 0;
}
