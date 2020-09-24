#include <iostream>
#include <memory> // std::addressof

// ************************************* //
class codebreaker {
public:
	int operator&() const { // 当重载时，打印&c不能输出地址，只能通过std::addressof()
		return 13;
	}
};

int test_addressof_1() {
	codebreaker c;

	std::cout << "&c: " << (&c) << '\n';
	std::cout << "addressof(c): " << std::addressof(c) << '\n';

	return 0;
}

// ************************************* //
class Buffer
{
private:
	static const size_t buffer_size = 256;
	int bufferId; 			 // 80x7ffdc6fcf110 -- std::addressof
	char buffer[buffer_size];// 80x7ffdc6fcf114 -- &this

public:
	Buffer(int bufferId_) : bufferId(bufferId_) {}
	Buffer* operator&() { return reinterpret_cast<Buffer*> (&buffer); }
};

template<typename T>
void getAddress(T t)
{
	std::cout << "Address returned by & operator: " << std::ios::hex << &t << "\n";				 // 80x7ffdc6fcf114
	std::cout << "Address returned by addressof: " << std::ios::hex << std::addressof(t) << "\n";// 80x7ffdc6fcf110
}

int test_addressof_2()
{
	int a = 3;
	fprintf(stderr, "a &: %p, address of: %p\n", &a, std::addressof(a));// 输出一样的地址

	Buffer b(1);
	std::cout << "Getting the address of a Buffer type: \n";
	getAddress(b);

	return 0;
}


int main(int argc, char const *argv[])
{
	test_addressof_2();
	return 0;
}
