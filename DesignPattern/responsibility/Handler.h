#ifndef _HANDLER_H_
#define _HANDLER_H_
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

/*
责任链模式
有很多的对象可以处理请求，
但是用户并不感知是那个对象处理了他的请求。
*/

//抽象类
class Handler
{
public:
    virtual void handleRequest(string number) = 0;
    virtual void setNextHandler(Handler *handler) = 0;
};

//具体处理者1
class Beijing : public Handler
{
public:
    Beijing();
    void handleRequest(string number) override;
    void setNextHandler(Handler *handler) override;

private:
    Handler *myHandler;
    list<string> numberList;
};

//具体处理者2
class Shanghai : public Handler
{
public:
    Shanghai();
    void handleRequest(string number) override;
    void setNextHandler(Handler *handler) override;

private:
    Handler *myHandler;
    list<string> numberList;
};

//具体处理者3
class Tianjin : public Handler
{
public:
    Tianjin();
    void handleRequest(string number) override;
    void setNextHandler(Handler *handler) override;

private:
    Handler *myHandler;
    list<string> numberList;
};

//具体处理者4
class Guangdong : public Handler
{
public:
    Guangdong();
    void handleRequest(string number) override;
    void setNextHandler(Handler *handler) override;

private:
    Handler *myHandler;
    list<string> numberList;
};

#endif