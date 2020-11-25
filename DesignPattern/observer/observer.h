// observer.h
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef int State;

class Subject;

// 观察者抽象
class Observer
{
public:
    Observer() {}
    virtual ~Observer() {}
    virtual void update(Subject *sub) = 0;
    virtual void outputState();

protected:
    string m_name;
    State m_observerState;
};

// 观察者A
class ConcreteObserverA : public Observer
{
public:
    ConcreteObserverA(string name, State init_state)
    {
        m_name = name;
        m_observerState = init_state;
    }
    ~ConcreteObserverA() {}
    void update(Subject *sub);

private:

};

// 观察者B
class ConcreteObserverB : public Observer
{
public:
    ConcreteObserverB(string name, State init_state)
    {
        m_name = name;
        m_observerState = init_state;
    }
    ~ConcreteObserverB() {}
    void update(Subject *sub);

private:

};