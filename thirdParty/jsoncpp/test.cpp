#include <iostream>
#include "json/json.h"

int main(int argc, char const *argv[])
{
	Json::Value root;
	Json::Value data;

	root["action"] = "run";
	data["number"] = 1;
	root["data"] = data;

	constexpr bool shouldUseOldWay = true;

	// 过时版本
	if (shouldUseOldWay)// 去除格式化
	{
		Json::FastWriter writer;
		const std::string json_file = writer.write(root);
		std::cout << json_file << std::endl;
	}
	else// 格式化
	{
		Json::StreamWriterBuilder builder;
		const std::string json_file = Json::writeString(builder, root);
		std::cout << json_file << std::endl;
	}

	return 0;
}
