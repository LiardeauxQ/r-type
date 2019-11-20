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
    T data;
};

template <typename T>
class AbstractState {
public:
    AbstractState(AbstractState&&) noexcept;
    AbstractState() = default;
    AbstractState& operator=(AbstractState&&) noexcept;

    virtual ~AbstractState() = default;

    virtual void onStart(StateData<T>& data) = 0;
    virtual void onStop(StateData<T>& data) = 0;
    virtual void onPause(StateData<T>& data) = 0;
    virtual void onResume(StateData<T>& data) = 0;

    virtual Transition<T> update(StateData<T>& data) = 0;
    virtual Transition<T> fixedUpdate(StateData<T>& data) = 0;

    virtual void shadowUpdate(StateData<T>& data) = 0;
    virtual void shadowFixedUpdate(StateData<T>& data) = 0;

    virtual Transition<T> handleEvent(StateData<T>& data) = 0;

private:
    unique_ptr<Dispatcher<StateData<T>, Error>> m_dispatcher;
    shared_ptr<StateData<T>> m_sharedData;
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

}
