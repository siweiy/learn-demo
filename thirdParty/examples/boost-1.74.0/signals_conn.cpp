/*
    事件处理
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include "boost/signals2.hpp"
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
#include "boost/bind.hpp"

int func(int i) {
    std::cout << "[func ------]" << i << ":Hello world" << std::endl;
    return 1;
}

int func2(int i) {
    std::cout << "[func2 ++++++]" << i << ":Hello world" << std::endl;
    return 100;
}

void test1() {

    boost::signals2::signal<int (int)> s;

    // 按顺序
    // s.connect(func);
    // s.connect(func2);

    // 按值
    boost::signals2::connection c = s.connect(1, func);// c可以管理s
    s.connect(0, func2);
    s.disconnect(func);

    if (!s.empty()){
        std::cout << s.num_slots() << std::endl;
        s(1);
        s.disconnect_all_slots();
    }
    
    boost::function<int (int)> f; 
    f = func;
    f = func2;
    f(2);
}

// 合成器(combiner)
// boost::signal 要求这个合成器定义一个名为 result_type 的类型，用于说明 operator()() 操作符返回值的类型
// 返回最小的一个值
template <typename T>
struct min_element {
    typedef T result_type;

    template <typename InputIterator> 
    T operator()(InputIterator first, InputIterator last) const { 
        return *std::min_element(first, last);
    }
};

void test2() {

    boost::signals2::signal<int (int), min_element<int> > s; 
    s.connect(func);
    s.connect(func2);
    std::cout << s(2) << std::endl;// 返回最小值，而不是最后一个
}

// 保存所有返回值
template <typename T> 
struct element { 
    typedef T result_type; 

    template <typename InputIterator> 
    T operator()(InputIterator first, InputIterator last) const { 
        return T(first, last); 
    } 
};

void test3() {

    boost::signals2::signal<int (int), element<std::vector<int> > > s; 
    s.connect(1, func); 
    s.connect(0, func2); 
    std::vector<int> v = s(1);
    std::for_each(v.begin(), v.end(), std::cout << boost::lambda::_1 << " ");
    // std::cout << *std::min_element(v.begin(), v.end()) << std::endl;
}

void test4() {

    boost::signals2::signal<void()> s;
    boost::signals2::connection c = s.connect([]{ std::cout << "Hello, world!\n"; });
    s();
    boost::signals2::shared_connection_block b1{c, false};
    b1.block();// 被 block() 调用所阻塞
    
    std::cout << std::boolalpha << b1.blocking() << '\n';// std::boolalpha指定输出格式：false， 若无：1
    s();

    b1.unblock();// 被 unblock() 解除阻塞
    s();
}

void test5() {

    boost::signals2::signal<int (int)> s; 
    {
        // 作用域连接：在析构时自动释放连接
        boost::signals2::scoped_connection c = s.connect(func); 
    } 
    s(1);
}

class world : public boost::signals2::trackable { 
public: 
    void hello() const { 
        std::cout << "Hello, world!" << std::endl; 
    } 
}; 

void test6() {

    boost::signals2::signal<void ()> s;
    {
        std::auto_ptr<world> w(new world()); 
        s.connect(boost::bind(&world::hello, w.get())); 
    }
    // 继承boost::signals2::trackable， 以确保不会试图调用已销毁对象之上的方法
    std::cout << s.num_slots() << std::endl; 
    s();
}

int main(int argc, char const *argv[])
{
    test6();

    return 0;
}
