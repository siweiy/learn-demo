#include "Handler.h"

Beijing::Beijing()
{
    numberList.push_back("11129812340930034");
    numberList.push_back("11129812340930035");
    numberList.push_back("11129812340930036");
    numberList.push_back("11129812340930037");
}

void Beijing::handleRequest(string number)
{
    list<string>::iterator it;
    it = find(numberList.begin(), numberList.end(), number);
    if (it != numberList.end()) //存在
    {
        cout << "该人在北京居住" << endl;
    }
    else
    {
        cout << "该人不在北京居住" << endl;
        if (NULL != myHandler)
        {
            myHandler->handleRequest(number);
        }
    }
}

void Beijing::setNextHandler(Handler *handler)
{
    myHandler = handler;
}

Shanghai::Shanghai()
{
    numberList.push_back("10129812340930031");
    numberList.push_back("10129812340930032");
    numberList.push_back("10129812340930036");
    numberList.push_back("10129812340930037");
}

void Shanghai::handleRequest(string number)
{
    list<string>::iterator it;
    it = find(numberList.begin(), numberList.end(), number);
    if (it != numberList.end()) //存在
    {
        cout << "该人在上海居住" << endl;
    }
    else
    {
        cout << "该人不在上海居住" << endl;
        if (NULL != myHandler)
        {
            myHandler->handleRequest(number);
        }
    }
}

void Shanghai::setNextHandler(Handler *handler)
{
    myHandler = handler;
}

Tianjin::Tianjin()
{
    numberList.push_back("10029812340930031");
    numberList.push_back("10029812340930032");
    numberList.push_back("10029812340930036");
    numberList.push_back("10029812340930037");
}

void Tianjin::handleRequest(string number)
{
    list<string>::iterator it;
    it = find(numberList.begin(), numberList.end(), number);
    if (it != numberList.end()) //存在
    {
        cout << "该人在天津居住" << endl;
    }
    else
    {
        cout << "该人不在天津居住" << endl;
        if (NULL != myHandler)
        {
            myHandler->handleRequest(number);
        }
    }
}

void Tianjin::setNextHandler(Handler *handler)
{
    myHandler = handler;
}

Guangdong::Guangdong()
{
    numberList.push_back("10029812340930088");
    numberList.push_back("10029812340930089");
    numberList.push_back("10029812340930090");
    numberList.push_back("10029812340930091");
}

void Guangdong::handleRequest(string number)
{
    list<string>::iterator it;
    it = find(numberList.begin(), numberList.end(), number);
    if (it != numberList.end()) //存在
    {
        cout << "该人在广东居住" << endl;
    }
    else
    {
        cout << "该人不在广东居住" << endl;
        if (NULL != myHandler)
        {
            myHandler->handleRequest(number);
        }
    }
}

void Guangdong::setNextHandler(Handler *handler)
{
    myHandler = handler;
}
