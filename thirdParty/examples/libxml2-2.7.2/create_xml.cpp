#include <iostream>
#include "libxml/parser.h"
#include "libxml/tree.h"
using namespace std;

int main(int argc, char *argv[])
{
	//定义文档指针
	xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
	//定义节点指针
	xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "root");

	//设置根节点
	xmlDocSetRootElement(doc, root_node);

	//在根节点中直接创建节点
	xmlNewTextChild(root_node, NULL, BAD_CAST "newNode1", BAD_CAST "newNode1 content");
	xmlNewTextChild(root_node, NULL, BAD_CAST "newNode2", BAD_CAST "newNode2 content");
	xmlNewTextChild(root_node, NULL, BAD_CAST "newNode3", BAD_CAST "newNode3 content");

	//创建一个节点，设置其内容和属性，然后加入根结点
	xmlNodePtr node = xmlNewNode(NULL, BAD_CAST "node2");
	xmlNodePtr content = xmlNewText(BAD_CAST "NODE CONTENT");
	xmlAddChild(root_node, node);
	xmlAddChild(node, content);
	xmlNewProp(node, BAD_CAST "attribute", BAD_CAST "yes");

	//创建一个儿子和孙子节点
	node = xmlNewNode(NULL, BAD_CAST "son");
	xmlAddChild(root_node, node);
	xmlNodePtr grandson = xmlNewNode(NULL, BAD_CAST "grandson");
	xmlAddChild(node, grandson);
	xmlAddChild(grandson, xmlNewText(BAD_CAST "This is a grandson node"));

	//存储xml文档
	int nRel = xmlSaveFormatFile("create_xml.xml", doc, XML_DOC_HTML);
	// int nRel = xmlSaveFile("create_xml.xml", doc);
	if (nRel != -1)
	{
		cout << "create_xml文档被创建，写入" << nRel << "个字节" << endl;
	}
	//释放文档内节点动态申请的内存
	xmlFreeDoc(doc);

	return 0;
}