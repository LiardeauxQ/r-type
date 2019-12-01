//
// Created by alex on 11/14/19.
//

#ifndef R_TYPE_TRANSITION_HPP
#define R_TYPE_TRANSITION_HPP

#include "AbstractState.hpp"

using namespace std;

namespace ecs {

template <typename T, typename E>
class AbstractState;


enum TransitionName {
    POP,
    QUIT,
    PUSH,
    NONE,
};

template <typename T, typename E>
struct Transition {


    explicit Transition(TransitionName trans = NONE, unique_ptr<AbstractState<T, E>> newState = nullptr);
    Transition(Transition&& trans) noexcept;
    Transition& operator=(Transition&& trans) noexcept;

    TransitionName m_transition;
    unique_ptr<AbstractState<T, E>> m_newState;
};

template <typename T, typename E>
Transition<T, E>::Transition(TransitionName trans, unique_ptr<AbstractState<T, E>> newState)
    : m_transition(trans)
    , m_newState(move(newState))
{
}

template <typename T, typename E>
Transition<T, E>::Transition(Transition&& trans) noexcept
    : m_transition(trans.m_transition)
    , m_newState(move(trans.m_newState))
{
}

template <typename T, typename E>
Transition<T, E>& Transition<T, E>::operator=(Transition&& trans) noexcept
{
    m_transition = trans.m_transition;
    m_newState.swap(trans.m_newState);
    return *this;
}

}

#endif //R_TYPE_TRANSITION_HPP
