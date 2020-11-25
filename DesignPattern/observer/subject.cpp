// subject.cpp
#include "subject.h"
#include "observer.h"

void Subject::Attach(Observer *pObs)
{
    m_pObs.push_back(pObs);
}

void Subject::Detach(Observer *pObs)
{
    vector<Observer *>::iterator it = m_pObs.begin();
    for (; it != m_pObs.end(); ++it)
    {
        if (*it == pObs)
        {
            m_pObs.erase(it);
            return;
        }
    }
}

void Subject::Notify()
{
    vector<Observer *>::iterator it = m_pObs.begin();
    for (; it != m_pObs.end(); ++it)
    {
        (*it)->update(this);
    }
}

void ConcreteSubject::SetState(const State &st)
{
    m_state = st;
}

State ConcreteSubject::GetState()
{
    return m_state;
}