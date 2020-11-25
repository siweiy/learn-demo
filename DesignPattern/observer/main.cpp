// 观察者模式 -- 可以理解为发布-订阅模式

// 观察者（Observer）模式的定义：指多个对象间存在一对多的依赖关系，
// 当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。
// 这种模式有时又称作发布-订阅模式、模型-视图模式，它是对象行为型模式。

/*
    【例1】利用观察者模式设计一个程序，分析“人民币汇率”的升值或贬值对进口公司的进口产品成本或出口公司的出口产品收入以及公司的利润率的影响。
    【例2】利用观察者模式设计一个学校铃声的事件处理程序。
*/

#include "observer.h"
#include "subject.h"

int main()
{
    ConcreteSubject *subject = new ConcreteSubject();       // 被观察者类
    Observer *obA = new ConcreteObserverA("observerA", -1); // 观察者A
    Observer *obB = new ConcreteObserverB("observerB", -1); // 观察者B

    // 添加观察者
    subject->Attach(obA);
    subject->Attach(obB);

    subject->SetState(0);
    subject->Notify();

    subject->SetState(1);
    subject->Notify();

    subject->Detach(obA);
    subject->SetState(0);
    subject->Notify();

    delete obA;
    delete obB;
    delete subject;

    return 0;
}

// 输出结果：
// observerA update state :0
// observerB update state :0
// observerA update state :1
// observerB update state :1
// observerB update state :0