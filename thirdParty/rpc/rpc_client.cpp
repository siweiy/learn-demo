#include <string>
#include <iostream>
#include <thread>
#include "rpc.h"

int main()
{
	rpc client;
	client.as_client("127.0.0.1", 5555);
	std::string str = client.call<std::string>("Strcat", "even", 24).value();
	std::cout << "str= " << str << std::endl;
	int result = client.call<int>("add", 3, 4).value();
	std::cout << "result= " << result << std::endl;

	while (1)
	{
		std::cout << "result= " << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		break;
	}

	return 0;
}
