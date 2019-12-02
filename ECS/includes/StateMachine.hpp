//
// Created by alex on 11/13/19.
//

#pragma once

#include "AbstractState.hpp"
#include "Event.hpp"
#include "Bundle.hpp"
#include "StopWatch.hpp"
#include "Transition.hpp"
#include "StateFactory.hpp"
#include "ThreadPool.hpp"
#include "World.hpp"
#include "ISystem.hpp"

namespace ecs {

template <typename T, typename E>
struct Transition;
template <typename T, typename E>
class AbstractState;
template <typename T>
struct StateData;

struct Error;

using namespace std;

template <typename T, typename E>
class StateMachine {
public:
    explicit StateMachine();

    void update(StateData<T> data);
    void start(const String &name, StateData<T> data);

    template<typename S>
    void registerState();

    template<typename S, typename... Args>
    void registerSystem(const String &name, Args&&... args);
    template<typename S>
    void registerSystem(const String &name);

    Transition<T, E> handleEvent(StateData<T> data, const E& event);
    void transition(Transition<T, E> trans, StateData<T>& data);
    bool m_running;

private:
    void push(Box<AbstractState<T, E>> newState, StateData<T>& data);
    unique_ptr<AbstractState<T, E>> pop(StateData<T>& data);
    shared_ptr<ThreadPool<ecs::StateData<T>, ecs::Error>> m_threadPool;
    vector<unique_ptr<AbstractState<T, E>>> m_states;
    StateFactory<T, E> m_factory;
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
    if (m_states.empty()) {
        m_running = false;
        return nullptr;
    }
    auto ret = move(m_states.back());
    ret->onStop(data);
    m_states.pop_back();
    if (!m_states.empty())
        m_states.back()->onResume(data);
    else
        m_running = false;
    return ret;
}

template <typename T, typename E>
Transition<T, E> StateMachine<T, E>::handleEvent(StateData<T> stateData, const E& event)
{
    return m_states.back()->handleEvent(stateData, event);
}

template <typename T, typename E>
void StateMachine<T, E>::update(StateData<T> stateData)
{
    if (m_running) {
        Transition<T, E> trans;

        if (!m_states.empty()) {
            trans = m_states.back()->update(stateData);
        } else {
            trans = Transition<T, E>(TransitionName::QUIT);
            m_running = false;
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
    case TransitionName::POP:
        this->pop(data);
        break;
    case TransitionName::PUSH:
        this->push(move(m_factory.queryState(trans.m_newStateName)), data);
        break;
    case TransitionName::QUIT:
        for (auto& s : m_states)
            s->onStop(data);
        m_running = false;
        break;
    case TransitionName::NONE:
        break;
    }
}

template <typename T, typename E>
StateMachine<T, E>::StateMachine()
    : m_running(true)
    , m_threadPool{make_shared<ThreadPool<ecs::StateData<T>, Error>>(1)} // TODO: Check if the game doesn't run the same system twice. Then try with the thread pool.
    , m_states()
    , m_factory()
{
}

template <typename T, typename E>
void StateMachine<T, E>::start(const String &name, StateData<T> stateData)
{
    auto newState = m_factory.queryState(name);
    newState->attachThreadPool(m_threadPool);
    m_states.push_back(move(newState));
    m_states.back()->onStart(stateData);
}

template<typename T, typename E>
template<typename S>
void StateMachine<T, E>::registerState()
{
    static_assert(is_base_of<AbstractState<T, E>, S>::value, "Should be a base of AbstractState.");
    m_factory.template registerState<S>();
}

template<typename T, typename E>
template<typename S, typename... Args>
void StateMachine<T, E>::registerSystem(const String &name, Args&&... args)
{
    static_assert(is_base_of<ISystem<StateData<T>>, S>::value, "Should be a base of ISystem.");
    m_factory.template registerSystem<S>(name, forward<Args>(args)...);
}

template<typename T, typename E>
template<typename S>
void StateMachine<T, E>::registerSystem(const String &name)
{
    static_assert(is_base_of<ISystem<StateData<T>>, S>::value, "Should be a base of ISystem.");
    m_factory.template registerSystem<S>(name);
}


}
