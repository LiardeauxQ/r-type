//
// Created by alex on 11/13/19.
//

#pragma once

#include "Definitions.hpp"
#include "Transition.hpp"
#include "Dispatcher.hpp"
#include "AbstractEvent.hpp"
#include "Event.hpp"
#include <vector>
#include <deque>

struct Transition;
class Dispatcher;

class AbstractState {
public:
    AbstractState(AbstractState&&) noexcept;
    AbstractState& operator=(AbstractState&&) noexcept;

    virtual ~AbstractState() = default;

    virtual void onStart(/* Data<T> */) = 0;
    virtual void onStop(/* Data<T> */) = 0;
    virtual void onPause(/* Data<T> */) = 0;
    virtual void onResume(/* Data<T> */) = 0;

    virtual Transition update(/* Data<T> */) = 0;
    virtual Transition fixedUpdate(/* Data<T> */) = 0;

    virtual void shadowUpdate(/* Data<T> */) = 0;
    virtual void shadowFixedUpdate(/* Data<T> */) = 0;

    virtual Transition handleEvent(/* Event */) = 0;

protected:
    deque<unique_ptr<ecs::Event>> m_events;
private:
    unique_ptr<Dispatcher> m_dispatcher;
};
