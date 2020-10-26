#include <iostream>
#include "json/json.h"

void sample1() {
	Json::Value root;
	Json::Value data;

	root["action"] = "run";
	data["number"] = 1;
	root["data"] = data;

	// constexpr bool shouldUseOldWay = true;

	// 过时版本
	// if (shouldUseOldWay)// 去除格式化
	// {
	// 	Json::FastWriter writer;
	// 	const std::string json_file = writer.write(root);
	// 	std::cout << json_file << std::endl;
	// }
	// else// 格式化
	{
		Json::StreamWriterBuilder builder;
		const std::string json_file = Json::writeString(builder, root);
		std::cout << json_file << std::endl;
	}
}

void sample2() {
	Json::Value root;
	Json::Value data;

	root["action"] = "run";
	data["number"] = 1;
	root["data"] = data;

	Json::StreamWriterBuilder builder;
	const std::string json_file = Json::writeString(builder, root);
	std::cout << json_file << std::endl;
}

void sample3() {

	// 构建json数组
    Json::Value array;
	Json::Value array2;
    Json::Value root;
    Json::Value person;
	Json::Value data;

	// 添加数组1
    person["name"] = "allen";
    person["age"] = 10; 
    person["sex"] = "male";
    // root.append(person);
	array[0] = person;
 
    person["name"] = "keiv";
    person["age"] = 20; 
    person["sex"] = "female";
	array[1] = person;
    
    person["name"] = "lihua";
    person["age"] = 10; 
    person["sex"] = "female";
	array[2] = person;
 
    // 数组加道root
    root["array"] = Json::Value(array);

	// 添加结点
	data["number"] = 1;
	root["data"] = data;

	// root添加成员
	root["111"] = "111";
	root["444"] = true;
	root["333"] = 44;
	root["22"] = 44.66;

	// 在数组1上在再添加一个数组成员
	person["name"] = "lihua";
    person["age"] = 10; 
    person["sex"] = "female";
	array[3] = person;
	root["array"] = Json::Value(array);// 必须再添加一次

	// 添加第二个数组
	person["name"] = "allen";
    person["age"] = 10; 
    person["sex"] = "male";
    // root.append(person);
	array2[0] = person;
	root["array2"] = Json::Value(array2);

#if 1
    Json::String strValue = root.toStyledString();
    std::cout << strValue << std::endl;
#else
	Json::StreamWriterBuilder builder;
	const std::string data = Json::writeString(builder, root);
	std::cout << data << std::endl;
 #endif


	// 解析Json字符串
	Json::Value value;
	Json::Value bRoot;
	JSONCPP_STRING err;
    Json::CharReaderBuilder builder;
    
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(strValue.c_str(), strValue.c_str() + strValue.length(), &bRoot, &err)) {
      std::cout << err.data() << std::endl;
      return;
    }

	// 数组
	Json::Value arr = bRoot["array"];
	for (unsigned int i = 0; i < arr.size(); i++)
	{   
		Json::String name = arr[i]["name"].asString();
		int     	  age = arr[i]["age"].asInt();
		Json::String sex  = arr[i]["sex"].asString();
		std::cout << name << " " << age << " " << sex << std::endl;
	}

	std::cout << bRoot["111"] << std::endl;

	std::cout << bRoot["data"]["number"] << std::endl;
}

int main(int argc, char const *argv[])
{
	
	sample3();
	return 0;
}
