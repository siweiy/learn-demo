// observer.cpp
#include "observer.h"
#include "subject.h"

void Observer::outputState()
{
    cout << m_name << " update state :" << m_observerState << endl;
}

void ConcreteObserverA::update(Subject *sub)
{
    m_observerState = sub->GetState();
    outputState();
}

void ConcreteObserverB::update(Subject *sub)
{
    m_observerState = sub->GetState();
    outputState();
}
