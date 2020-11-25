/**
 * 抽象工厂模式
 */
#include <iostream>
#include <string>
using namespace std;

// 卡车抽象类
class Trunk_A
{
public:
    virtual void Run() = 0;
};

// 轿车抽象类
class Sedan_A
{
public:
    virtual void Run() = 0;
};

// 具体的宝马卡车产品类
class BmwTrunk : public Trunk_A
{
public:
    virtual void Run()
    {
        cout << "宝马卡车" << endl;
    }
};

// 具体的宝马轿车产品类
class BmwSedan : public Sedan_A
{
public:
    virtual void Run()
    {
        cout << "宝马轿车" << endl;
    }
};

// 具体的奥迪卡车产品类
class AodiTrunk : public Trunk_A
{
public:
    virtual void Run()
    {
        cout << "奥迪卡车" << endl;
    }
};

// 具体的奥迪轿车产品类
class AodiSedan : public Sedan_A
{
public:
    virtual void Run()
    {
        cout << "奥迪轿车" << endl;
    }
};

// 抽象工厂类
class CarFactory
{
public:
    virtual Trunk_A *productTrunk() = 0;
    virtual Sedan_A *productSedan() = 0;
};

// 宝马工厂类(一个工厂是生产一个产品族的工厂而不是生产单一的产品)
class BmwFactory : public CarFactory
{
public:
    virtual Trunk_A *productTrunk()
    {
        return new BmwTrunk;
    }
    virtual Sedan_A *productSedan()
    {
        return new BmwSedan;
    }
};

// 奥迪工厂类
class AodiFactory : public CarFactory
{
public:
    virtual Trunk_A *productTrunk()
    {
        return new AodiTrunk;
    }
    virtual Sedan_A *productSedan()
    {
        return new AodiSedan;
    }
};

int main()
{
    // 客户端
    CarFactory *bm = new BmwFactory();
    bm->productTrunk()->Run();
    bm->productSedan()->Run();

    return 0;
}
