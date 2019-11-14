//
// Created by alex on 11/13/19.
//

#pragma once

#include "Definitions.hpp"
#include "Transition.hpp"
#include <vector>

typedef uint32_t System;

struct Transition;

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
    virtual void shadowUpdate(/* Data<T> */) = 0;
private:
    vector<System> m_systems;
};
