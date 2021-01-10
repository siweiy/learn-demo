#include <iostream>
#include "Singleton.hpp"
using namespace std;

class Test {
public:
    Test() {}
    ~Test() {}

    void print() {
        cout << "111111-- " << endl;
    }
};

int main()
{
    Singleton<Test>::getInstance()->print();

    std::cout << "Hello world" << std::endl;
    Singleton<Test>::releaseSingletonAddress();

    return 0;
}

