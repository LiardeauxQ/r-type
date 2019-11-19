//
// Created by alex on 11/13/19.
//

#pragma once

#include "Definitions.hpp"
#include "Transition.hpp"
#include "Dispatcher.hpp"
#include <vector>

struct Transition;

struct Event {
    string name;
};
struct Error {
    string message;
};

class AbstractState {
public:
    AbstractState(AbstractState&&) noexcept;
    AbstractState() = default;
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
private:
    unique_ptr<Dispatcher<Event, Error>> m_dispatcher;
};
