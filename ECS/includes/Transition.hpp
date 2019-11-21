//
// Created by alex on 11/14/19.
//

#ifndef R_TYPE_TRANSITION_HPP
#define R_TYPE_TRANSITION_HPP

#include "AbstractState.hpp"

using namespace std;

namespace ecs {

template <typename T>
class AbstractState;

template <typename T>
struct Transition {
    enum Name {
        POP,
        QUIT,
        PUSH,
        NONE,
    };

    explicit Transition(Name trans = NONE, Box<AbstractState<T>> newState = nullptr);
    Transition(Transition&& trans) noexcept;
    Transition& operator=(Transition&& trans) noexcept;

    Name m_transition;
    unique_ptr<AbstractState<T>> m_newState;
};

template <typename T>
Transition<T>::Transition(Transition::Name trans, unique_ptr<AbstractState<T>> newState)
    : m_transition(trans)
    , m_newState(move(newState))
{
}

template <typename T>
Transition<T>::Transition(Transition&& trans) noexcept
    : m_transition(trans.m_transition)
    , m_newState(move(trans.m_newState))
{
}

template <typename T>
Transition<T>& Transition<T>::operator=(Transition&& trans) noexcept
{
    m_transition = trans.m_transition;
    m_newState.swap(trans.m_newState);
    return *this;
}

}

#endif //R_TYPE_TRANSITION_HPP
