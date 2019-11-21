//
// Created by alex on 11/13/19.
//

#pragma once

#include "AbstactState.hpp"
#include "StopWatch.hpp"
#include "Transition.hpp"
#include "World.hpp"

namespace ecs {

template <typename T>
struct Transition;
template <typename T>
class AbstractState;
template <typename T>
struct StateData;

using namespace std;

template <typename T>
class StateMachine {
public:
    StateMachine(unique_ptr<AbstractState<T>> initial, shared_ptr<World> world);

    void run(T data);
private:
    void transition(Transition<T> trans, StateData<T>& data);
    void push(Box<AbstractState<T>> newState, StateData<T>& data);
    Box<AbstractState<T>> pop(StateData<T>& data);
    vector<Box<AbstractState<T>>> m_states;
    bool m_running;
    shared_ptr<World> m_world;
    int64_t m_deltaTime;
};

template <typename T>
void StateMachine<T>::push(unique_ptr<AbstractState<T>> newState, StateData<T>& data)
{
    if (!m_states.empty())
        m_states.back()->onPause(data);
    newState->onStart(data);
    m_states.push_back(move(newState));
}

template <typename T>
unique_ptr<AbstractState<T>> StateMachine<T>::pop(StateData<T>& data)
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

template <typename T>
void StateMachine<T>::run(T data)
{
    StateData<T> stateData{ m_world, m_deltaTime, data };
    m_states.back()->onStart(stateData);
    while (m_running) {
        m_world->m_timer.start();
        Transition<T> trans;

        if (!m_states.empty()) {
            trans = m_states.back()->update(stateData);
        } else {
            break;
        }
        for (auto& s : m_states)
            s->shadowUpdate(stateData);
        this->transition(move(trans), stateData);
        m_deltaTime = m_world->m_timer.elapsed();
    }
}

template <typename T>
void StateMachine<T>::transition(Transition<T> trans, StateData<T>& data)
{
    switch (trans.m_transition) {
    case Transition<T>::Name::POP:
        this->pop(data);
        break;
    case Transition<T>::Name::PUSH:
        this->push(move(trans.m_newState), data);
        break;
    case Transition<T>::Name::QUIT:
        for (auto& s : m_states)
            s->onStop(data);
        m_running = false;
        break;
    case Transition<T>::NONE:
        break;
    }
}

template <typename T>
StateMachine<T>::StateMachine(unique_ptr<AbstractState<T>> initial, shared_ptr<World> world)
    : m_states()
    , m_running(true)
    , m_world(move(world))
    , m_deltaTime()
{
    m_states.push_back(move(initial));
}

}
