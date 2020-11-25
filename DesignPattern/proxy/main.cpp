/*
    代理模式(proxy pattern):为其他对象提供一种代理以控制对这个对象的访问
    
    代理模式的应用场景：
    如果已有的方法在使用的时候需要对原有的方法进行改进，此时有两种办法：
    1、修改原有的方法来适应。这样违反了“对扩展开放，对修改关闭”的原则。
    2、就是采用一个代理类调用原有的方法，且对产生的结果进行控制。这种方法就是代理模式。
    使用代理模式，可以将功能划分的更加清晰，有助于后期维护

    代理模式最大的好处便是逻辑与实现的彻底解耦
*/

#include <iostream>
using namespace std;

class Girl
{
public:
    Girl(char *name = "") : mName(name) {}
    char *getName()
    {
        return mName;
    }

private:
    char *mName;
};

class GiveGift // 接口
{
public:
    virtual void GiveDolls() = 0;
    virtual void GiveFlowers() = 0;
    virtual void GiveChocolate() = 0;
};

class Puisuit : public GiveGift // 送礼物实例类
{
public:
    Puisuit(Girl mm) : mGirl(mm) {}

    virtual void GiveDolls()
    {
        cout << "送" << mGirl.getName() << "玩具！" << endl;
    }

    virtual void GiveFlowers()
    {
        cout << "送" << mGirl.getName() << "鲜花！" << endl;
    }

    virtual void GiveChocolate()
    {
        cout << "送" << mGirl.getName() << "巧克力！" << endl;
    }

private:
    Girl mGirl;
};

class Proxy : public GiveGift // 送礼物代理类
{
public:
    Proxy(Girl mm)
    {
        mPuisuit = new Puisuit(mm);
    }

    virtual void GiveDolls()
    {
        mPuisuit->GiveDolls();
    }

    virtual void GiveFlowers()
    {
        mPuisuit->GiveFlowers();
    }

    virtual void GiveChocolate()
    {
        mPuisuit->GiveChocolate();
    }

private:
    Puisuit *mPuisuit;
};

int main()
{
    Girl mm("小娟");
    Proxy pro(mm);

    pro.GiveChocolate();
    pro.GiveDolls();
    pro.GiveFlowers();

    return 0;
}