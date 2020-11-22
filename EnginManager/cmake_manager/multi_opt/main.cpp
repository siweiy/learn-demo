#include <iostream>

#include "config.h"
#ifdef USE_MYMATH
#include "calc.h"
#endif

int main(int argc, char const *argv[])
{
#ifdef USE_MYMATH
	std::cout << add(2, 3) << std::endl;
#endif

	printf("Version %d.%d\n", VERSION_MAJOR, VERSION_MINOR);
	std::cout << "hello" << std::endl;
	
	return 0;
}
