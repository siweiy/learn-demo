#include <iostream>
#include <tinyxml2.h>

//function：create a xml file
//param：xmlPath:xml文件路径
//return：0,成功；非0，失败
int createXML(const char *xmlPath)
{
	tinyxml2::XMLDocument doc;

#if 0 // 手动添加
	const char* declaration ="<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	doc.Parse(declaration);//会覆盖xml所有内容
#else
	// <?xml version="1.0" encoding="UTF-8"?>
	tinyxml2::XMLDeclaration *declaration = doc.NewDeclaration();
	doc.InsertFirstChild(declaration);
#endif

	tinyxml2::XMLElement *root = doc.NewElement("DBUSER");
	doc.InsertEndChild(root);

	return doc.SaveFile(xmlPath);
}

// load a xml file and add node
int insertXMLNode(const char *xmlPath)
{
	tinyxml2::XMLDocument doc;
	int res = doc.LoadFile(xmlPath);
	if (res != 0)
	{
		std::cout << "load xml file failed" << std::endl;
		return res;
	}

	tinyxml2::XMLElement *root = doc.RootElement();

	// root中插入一个node
	tinyxml2::XMLElement *userNode = doc.NewElement("User");
	userNode->SetAttribute("Name", "root");
	userNode->SetAttribute("Password", "123456");
	root->InsertEndChild(userNode);

	// userNode中插入一个node
	tinyxml2::XMLElement *gender = doc.NewElement("Gender");
	tinyxml2::XMLText *genderText = doc.NewText("22");
	gender->InsertEndChild(genderText);
	userNode->InsertEndChild(gender);

	tinyxml2::XMLElement *mobile = doc.NewElement("Mobile");
	mobile->InsertEndChild(doc.NewText("1234567890"));
	userNode->InsertEndChild(mobile);

	tinyxml2::XMLElement *email = doc.NewElement("Email");
	email->InsertEndChild(doc.NewText("1258915@163.com"));
	userNode->InsertEndChild(email);

	return doc.SaveFile(xmlPath);
}

//function:根据用户名获取用户节点
//param:root:xml文件根节点；userName：用户名
//return：用户节点
tinyxml2::XMLElement *queryUserNodeByName(tinyxml2::XMLElement *root, const char *userName)
{
	tinyxml2::XMLElement *userNode = root->FirstChildElement("User");

	while (userNode != NULL)
	{
		if (!strcmp(userNode->Attribute("Name"), userName))
		{
			break;
		}

		userNode = userNode->NextSiblingElement(); //下一个兄弟节点
	}

	return userNode;
}
void select(const char *xmlPath, const char *userName)
{
	tinyxml2::XMLDocument doc;
	int res = doc.LoadFile(xmlPath);
	if (res != 0)
	{
		std::cout << "load xml file failed" << std::endl;
		return;
	}
	tinyxml2::XMLElement *root = doc.RootElement();

	// doc必须还在才能继续
	tinyxml2::XMLElement *userNode = queryUserNodeByName(root, userName);
	if (userNode != NULL)
	{
		const char *Password = userNode->Attribute("Password");
		if (Password)
			puts(Password);

		tinyxml2::XMLElement *genderNode = userNode->FirstChildElement("Gender");
		if (genderNode)
		{
			const char *Gender = genderNode->GetText();
			puts(Gender);
		}

		tinyxml2::XMLElement *mobileNode = userNode->FirstChildElement("Mobile");
		if (mobileNode)
		{
			const char *Mobile = mobileNode->GetText();
			puts(Mobile);
		}

		tinyxml2::XMLElement *emailNode = userNode->FirstChildElement("Email");
		if (emailNode)
		{
			const char *Email = emailNode->GetText();
			puts(Email);
		}
	}
	else
	{
		std::cout << "userNode is null" << std::endl;
	}

	std::cout << std::endl;
}

//function:修改指定节点内容
//param:xmlPath:xml文件路径；user：用户对象
//return：bool
bool updateUser(const char *xmlPath, const char *userName)
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(xmlPath) != 0)
	{
		std::cout << "load xml file failed" << std::endl;
		return false;
	}
	tinyxml2::XMLElement *root = doc.RootElement();

	// 找到节点
	tinyxml2::XMLElement *userNode = queryUserNodeByName(root, userName);

	if (userNode != NULL)
	{
		// if (password != userNode->Attribute("Password"))
		{
			userNode->SetAttribute("Password", "9876543321"); //修改属性
		}

		tinyxml2::XMLElement *genderNode = userNode->FirstChildElement("Gender");
		// if (gender != atoi(genderNode->GetText()))
		{
			genderNode->SetText("男"); //修改节点内容
		}
		tinyxml2::XMLElement *mobileNode = userNode->FirstChildElement("Mobile");
		// if (mobile != mobileNode->GetText())
		{
			mobileNode->SetText("00000000000");
		}
		tinyxml2::XMLElement *emailNode = userNode->FirstChildElement("Email");
		// if (email != emailNode->GetText())
		{
			emailNode->SetText("214214@qq.com");
		}

		if (doc.SaveFile(xmlPath) == 0)
			return true;
	}

	return false;
}

//function:删除指定节点内容
//param:xmlPath:xml文件路径；userName：用户名称
//return：bool
bool deleteUserByName(const char *xmlPath, const char *userName)
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(xmlPath) != 0)
	{
		std::cout << "load xml file failed" << std::endl;
		return false;
	}
	tinyxml2::XMLElement *root = doc.RootElement();

	//doc.DeleteNode(root);//删除xml所有节点

	tinyxml2::XMLElement *userNode = queryUserNodeByName(root, userName);
	if (userNode != NULL)
	{
		userNode->DeleteAttribute("Password"); //删除属性
		tinyxml2::XMLElement *emailNode = userNode->FirstChildElement("Email");
		userNode->DeleteChild(emailNode); //删除指定节点
		//userNode->DeleteChildren();//删除节点的所有孩子节点
		if (doc.SaveFile(xmlPath) == 0)
			return true;
	}
	return false;
}

//function:获取xml文件申明
//param:xmlPath:xml文件路径；strDecl：xml申明
//return：bool
bool getXMLDeclaration(const char *xmlPath)
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(xmlPath) != 0)
	{
		std::cout << "load xml file failed" << std::endl;
		return false;
	}
	tinyxml2::XMLNode *decl = doc.FirstChild();
	if (NULL != decl)
	{
		tinyxml2::XMLDeclaration *declaration = decl->ToDeclaration();
		if (NULL != declaration)
		{
			std::cout << declaration->Value() << std::endl;
			return true;
		}
	}
	return false;
}

//function:将xml文件内容输出到标准输出
//param:xmlPath:xml文件路径
void printXML(const char *xmlPath)
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(xmlPath) != 0)
	{
		std::cout << "load xml file failed" << std::endl;
		return;
	}
	doc.Print();
	
	// tinyxml2::XMLPrinter printer;
	// doc.Print(&printer);
}

int main(int argc, char const *argv[])
{
	if (createXML("test.xml"))
	{
		std::cout << "createXML test.xml error" << std::endl;
	}
	else
	{
		insertXMLNode("test.xml");
		select("test.xml", "root");
		updateUser("test.xml", "root");
		select("test.xml", "root");
		deleteUserByName("test.xml", "root");
		select("test.xml", "root");
		getXMLDeclaration("test.xml");
		printXML("test.xml");
	}

	return 0;
}
