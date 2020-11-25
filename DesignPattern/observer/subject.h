// subject.h
#include <vector>
#include <string>
using namespace std;

typedef int State;

class Observer;

// 被观察者抽象
class Subject
{
public:
    Subject() {}
    virtual ~Subject() {}
    virtual void Attach(Observer *obv); // 注册观察者
    virtual void Detach(Observer *obv); // 注销观察者
    virtual void Notify();              // 通知观察者
    virtual void SetState(const State &st) = 0;
    virtual State GetState() = 0;

private:
    //观察者列表
    vector<Observer *> m_pObs;
};

// 被观察者
class ConcreteSubject : public Subject
{
public:
    ConcreteSubject() {}
    ~ConcreteSubject() {}
    State GetState();
    void SetState(const State &st);

private:
    State m_state;
};