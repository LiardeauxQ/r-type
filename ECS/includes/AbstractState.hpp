//
// Created by alex on 11/13/19.
//

#pragma once

#include "Definitions.hpp"
#include "Transition.hpp"
#include "Dispatcher.hpp"
#include "Event.hpp"
#include "World.hpp"
#include "ThreadPool.hpp"
#include "IFactorizable.hpp"

#include <deque>
#include <utility>
#include <vector>
#include "World.hpp"
#include "ISystem.hpp"

namespace ecs {

template <typename T, typename E>
struct Transition;

struct Error {
    uint32_t code;
    string message;
};

template <typename T>
struct StateData {
    ecs::World& world;
    const double delta = 0;
    T& data;
};

template <typename T, typename E>
class Dispatcher;

template <typename T, typename E>
class AbstractState : public IFactorizable<String> {
public:
    explicit AbstractState(unique_ptr<Dispatcher<StateData<T>, ecs::Error>>);
    explicit AbstractState();

    AbstractState& operator=(AbstractState&&) noexcept;
    AbstractState(AbstractState&&) noexcept;

    ~AbstractState() override = default;

    template <typename S, typename... Args>
    void registerSystem(Args... args);
    template <typename S>
    void registerSystem();
    void attachThreadPool(shared_ptr<ThreadPool<ecs::StateData<T>, ecs::Error>> pool);

    void registerOn(const String &name);

    virtual void onStart(StateData<T>& data) = 0;
    virtual void onStop(StateData<T>& data) = 0;
    virtual void onPause(StateData<T>& data) = 0;
    virtual void onResume(StateData<T>& data) = 0;

    virtual Transition<T, E> update(StateData<T>& data) = 0;
    virtual Transition<T, E> fixedUpdate(StateData<T>& data) = 0;

    virtual void shadowUpdate(StateData<T>& data) = 0;
    virtual void shadowFixedUpdate(StateData<T>& data) = 0;

    virtual Transition<T, E> handleEvent(StateData<T>& data, E event) = 0;

protected:
    deque<unique_ptr<ecs::Event>> m_events;
    unique_ptr<Dispatcher<StateData<T>, Error>> m_dispatcher;
};

template <typename T, typename E>
AbstractState<T, E>::AbstractState(AbstractState<T, E>&& rhs) noexcept
    : m_dispatcher(move(rhs.m_dispatcher))
{
}

template <typename T, typename E>
AbstractState<T, E>& AbstractState<T, E>::operator=(AbstractState<T, E>&& rhs) noexcept
{
    m_dispatcher.swap(rhs.m_dispatcher);
    return *this;
}

template <typename T, typename E>
template <typename S, typename... Args>
void AbstractState<T, E>::registerSystem(Args... args)
{
    m_dispatcher->template registerSystem<S>(args...);
}

template <typename T, typename E>
template <typename S>
void AbstractState<T, E>::registerSystem()
{
    m_dispatcher->template registerSystem<S>();
}


template <typename T, typename E>
AbstractState<T, E>::AbstractState(unique_ptr<ecs::Dispatcher<ecs::StateData<T>, ecs::Error>> dispatcher)
    : m_dispatcher(move(dispatcher))
{}

template<typename T, typename E>
AbstractState<T, E>::AbstractState()
    : m_dispatcher(make_unique<Dispatcher<StateData<T>, Error>>())
{
}

template <typename T, typename E>
void AbstractState<T, E>::attachThreadPool(shared_ptr<ThreadPool<ecs::StateData<T>, ecs::Error>> pool)
{
    m_dispatcher->attachThreadPool(pool);
}

}
