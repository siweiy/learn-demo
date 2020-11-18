/*
    智能指针
*/
#include <iostream>
#include <vector>
#include "boost/scoped_ptr.hpp"
#include "boost/scoped_array.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/shared_array.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/intrusive_ptr.hpp"
#include "boost/ptr_container/ptr_vector.hpp"
#include <thread>

using namespace std;

// 作用域指针
void test1() {
	boost::scoped_ptr<int> i(new int);

	*i = 2;
	cout << *i << endl;

	*i.get() = 1;
	cout << *i << endl;

	i.reset(new int);
	cout << *i << endl;
}

// 作用域数组
void test2() {
	boost::scoped_array<int> arr(new int[2]);

	*arr.get() = 1;
	cout << arr[0] << endl;

	arr[1] = 2; 
	arr.reset(new int[3]);
}

// 共享指针
void test3() {
	std::vector< boost::shared_ptr<int> > v;
	v.push_back(boost::shared_ptr<int>(new int(1)));
	v.push_back(boost::shared_ptr<int>(new int(2)));

	cout << *v[0] << endl;
	cout << *v[1] << endl;

	boost::shared_ptr<int> i1(new int(1)); 
	boost::shared_ptr<int> i2(i1); 

	cout << *i1 << endl;// 1
	cout << *i2 << endl;// 1

	i1.reset(new int(2));

	cout << *i1 << endl; // 2
	cout << *i2 << endl; // 1
}

// 共享数组
void test4() {
	boost::shared_array<int> i1(new int[2]);
	boost::shared_array<int> i2(i1);

	i1[0] = 1; 
	std::cout << i2[0] << std::endl;
}


void reset_task(void *p) {
	boost::shared_ptr<int> *sh = static_cast<boost::shared_ptr<int> *>(p);
	sh->reset();
}

void print_task(void *p) {
	boost::weak_ptr<int> *w = static_cast<boost::weak_ptr<int> *>(p);
	boost::shared_ptr<int> sh = w->lock();
	if (sh) {
		cout << *sh << endl;
	}else{
		cout << "sh is reset" << endl;
	}
}

// 弱指针: 只有在配合共享指针一起使用时才有意义
// 一个潜在的问题：reset() 线程在销毁对象的时候print() 线程可能正在访问它。
// 通过调用弱指针的 lock() 函数可以解决这个问题：
// 如果对象存在，那么 lock() 函数返回的共享指针指向这个合法的对象。
// 否则，返回的共享指针被设置为0，这等价于标准的null指针。
void test5() {
	boost::shared_ptr<int> sh(new int(99)); 
	boost::weak_ptr<int> w(sh);

	thread th1, th2;
	th1 = thread(reset_task, &sh);
	th2 = thread(print_task, &w);

	th1.join();
	th2.join();
}

// 介入式指针:大体上工作方式和共享指针完全一样
// COM 对象是使用 boost::intrusive_ptr 的绝佳范例，因为 COM 对象需要记录当前有多少指针引用着它。
// 通过调用 AddRef() 和 Release() 函数，内部的引用计数分别增 1 或者减 1。当引用计数为 0 时，COM 对象自动销毁
void test6() {
	// boost::intrusive_ptr<int> i(new int(6));

}

// 指针容器
void test7() {
#if 0	// 效率低，不推荐用
	std::vector<boost::shared_ptr<int> > v; 
	v.push_back(boost::shared_ptr<int>(new int(1))); 
	v.push_back(boost::shared_ptr<int>(new int(2)));
#else
	boost::ptr_vector<int> pv;
	pv.push_back(new int(6));
	pv.push_back(new int(7));

	cout << pv[0] << endl;
	cout << pv[1] << endl;
#endif
}

int main(int argc, char const *argv[]) {

	test7();
	
	return 0;
}
