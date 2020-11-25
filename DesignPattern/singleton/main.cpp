#include <iostream>
#include "Singleton.hpp"

class Test
{
public:
    void run() { std::cout << "Singleton test" << std::endl; }
};

int main(int argc, char const *argv[])
{
    Singleton<Test>::Instance()->run();

    return 0;
}
