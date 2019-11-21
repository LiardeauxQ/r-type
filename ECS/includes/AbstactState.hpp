//
// Created by alex on 11/13/19.
//

#pragma once

#include "Definitions.hpp"
#include "Transition.hpp"
#include "Dispatcher.hpp"
#include <utility>
#include <vector>
#include "World.hpp"
#include "ISystem.hpp"

namespace ecs {

template <typename T>
struct Transition;

struct Error {
    uint32_t code;
    string message;
};

template <typename T>
struct StateData {
    shared_ptr<ecs::World> world;
    const int64_t delta = 0;
    T& data;
};

template <typename T>
class AbstractState {
public:
    AbstractState(AbstractState&&) noexcept;
    AbstractState(unique_ptr<Dispatcher<StateData<T>, Error>> dispatcher);
    AbstractState& operator=(AbstractState&&) noexcept;

    virtual ~AbstractState() = default;

    template<typename S>
    void registerSystem(S system);

    virtual void onStart(StateData<T>& data) = 0;
    virtual void onStop(StateData<T>& data) = 0;
    virtual void onPause(StateData<T>& data) = 0;
    virtual void onResume(StateData<T>& data) = 0;

    virtual Transition<T> update(StateData<T>& data) = 0;
    virtual Transition<T> fixedUpdate(StateData<T>& data) = 0;

    virtual void shadowUpdate(StateData<T>& data) = 0;
    virtual void shadowFixedUpdate(StateData<T>& data) = 0;

    virtual Transition<T> handleEvent(StateData<T>& data) = 0;

protected:
    unique_ptr<Dispatcher<StateData<T>, Error>> m_dispatcher;
};

template <typename T>
AbstractState<T>::AbstractState(AbstractState<T>&& rhs) noexcept
    : m_dispatcher(move(rhs.m_dispatcher))
{
}

template <typename T>
AbstractState<T>& AbstractState<T>::operator=(AbstractState<T>&& rhs) noexcept
{
    m_dispatcher.swap(rhs.m_dispatcher);
    return *this;
}

template <typename T>
template <typename S>
void AbstractState<T>::registerSystem(S system)
{
    m_dispatcher->registerSystem(system);
}

template <typename T>
AbstractState<T>::AbstractState(unique_ptr<Dispatcher<StateData<T>, Error>> dispatcher)
    : m_dispatcher(move(dispatcher))
{
}

}
