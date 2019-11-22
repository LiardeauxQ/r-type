//
// Created by alex on 11/13/19.
//

#pragma once

#include "AbstractState.hpp"
#include "StopWatch.hpp"
#include "Transition.hpp"
#include "World.hpp"

namespace ecs {

template <typename T, typename E>
struct Transition;
template <typename T, typename E>
class AbstractState;
template <typename T>
struct StateData;

using namespace std;

template <typename T, typename E>
class StateMachine {
public:
    explicit StateMachine(unique_ptr<AbstractState<T, E>> initial);

    void update(StateData<T> data);
    void start(StateData<T> data);
    void handleEvent(StateData<T> data, const E& event);
    void transition(Transition<T, E> trans, StateData<T>& data);
private:
    void push(Box<AbstractState<T, E>> newState, StateData<T>& data);
    unique_ptr<AbstractState<T, E>> pop(StateData<T>& data);
    vector<unique_ptr<AbstractState<T, E>>> m_states;
    bool m_running;
};

template <typename T, typename E>
void StateMachine<T, E>::push(unique_ptr<AbstractState<T, E>> newState, StateData<T>& data)
{
    if (!m_states.empty())
        m_states.back()->onPause(data);
    newState->onStart(data);
    m_states.push_back(move(newState));
}

template <typename T, typename E>
unique_ptr<AbstractState<T, E>> StateMachine<T, E>::pop(StateData<T>& data)
{
    if (m_states.empty())
        return nullptr;
    auto ret = move(m_states.back());
    ret->onStop(data);
    m_states.pop_back();
    if (!m_states.empty())
        m_states.back()->onResume(data);
    return ret;
}

template <typename T, typename E>
void StateMachine<T, E>::handleEvent(StateData<T> stateData, const E& event)
{
    m_states.back()->handleEvent(stateData, event);
}

template <typename T, typename E>
void StateMachine<T, E>::update(StateData<T> stateData)
{
    if (m_running) {
        Transition<T, E> trans;

        if (!m_states.empty()) {
            trans = m_states.back()->update(stateData);
        } else {
            trans = Transition<T, E>();
        }
        for (auto& s : m_states)
            s->shadowUpdate(stateData);
        this->transition(move(trans), stateData);
    }
}

template <typename T, typename E>
void StateMachine<T, E>::transition(Transition<T, E> trans, StateData<T>& data)
{
    switch (trans.m_transition) {
    case Transition<T, E>::Name::POP:
        this->pop(data);
        break;
    case Transition<T, E>::Name::PUSH:
        this->push(move(trans.m_newState), data);
        break;
    case Transition<T, E>::Name::QUIT:
        for (auto& s : m_states)
            s->onStop(data);
        m_running = false;
        break;
    case Transition<T, E>::NONE:
        break;
    }
}

template <typename T, typename E>
StateMachine<T, E>::StateMachine(unique_ptr<AbstractState<T, E>> initial)
    : m_states()
    , m_running(true)
{
    m_states.push_back(move(initial));
}

template <typename T, typename E>
void StateMachine<T, E>::start(StateData<T> stateData)
{
    m_states.back()->onStart(stateData);
}

}
