//
// Created by alex on 11/13/19.
//

#ifndef R_TYPE_STATESSTACK_HPP
#define R_TYPE_STATESSTACK_HPP

#include "Definitions.hpp"
#include "AbstactState.hpp"
#include "Transition.hpp"

template<typename T> struct Transition;
template<typename T> class AbstractState;

using namespace std;

namespace ecs {

template<typename T>
class StateMachine {
public:
    StateMachine(unique_ptr<AbstractState<T>> initial);

    void run();
private:
    void transition(Transition<T> trans);
    void push(Box<AbstractState<T>> newState);
    Box<AbstractState<T>> pop();
    vector<Box<AbstractState<T>>> m_states;
    bool m_running;
};

template<typename T>
void StateMachine<T>::push(Box<AbstractState<T>> newState)
{
    if (!m_states.empty())
        m_states.back()->onPause();
    newState->onStart();
    m_states.push_back(move(newState));
}

template<typename T>
unique_ptr<AbstractState<T>> StateMachine<T>::pop()
{
    if (m_states.empty())
        return nullptr;
    auto ret = move(m_states.back());
    ret->onStop();
    m_states.pop_back();
    if (!m_states.empty())
        m_states.back()->onResume();
    return ret;
}

template<typename T>
void StateMachine<T>::run()
{
    while (m_running) {
        Transition<T> trans;

        if (!m_states.empty())
            trans = m_states.back()->update();
        else
            break;
        for (auto& s : m_states)
            s->shadowUpdate();
        this->transition(move(trans));
    }
}

template<typename T>
void StateMachine<T>::transition(Transition<T> trans)
{
    switch (trans.m_transition) {
    case Transition<T>::Name::POP:
        this->pop();
        break;
    case Transition<T>::Name::PUSH:
        this->push(move(trans.m_newState));
        break;
    case Transition<T>::Name::QUIT:
        for (auto &s: m_states)
            s->onStop();
        m_running = false;
        break;
    case Transition<T>::NONE:
        break;
    }
}

template<typename T>
StateMachine<T>::StateMachine(unique_ptr<AbstractState<T>> initial)
    : m_states()
    , m_running(true)
{
    m_states.push_back(move(initial));
}

}

#endif //R_TYPE_STATESSTACK_HPP
