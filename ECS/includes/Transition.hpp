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


    explicit Transition(TransitionName trans = NONE, String newStateName = "");
    Transition(Transition&& trans) noexcept;
    Transition& operator=(Transition&& trans) noexcept;

    TransitionName m_transition;
    String m_newStateName;
};

template <typename T, typename E>
Transition<T, E>::Transition(TransitionName trans, String newStateName)
    : m_transition(trans)
    , m_newStateName(move(newStateName))
{
}

template <typename T, typename E>
Transition<T, E>::Transition(Transition&& trans) noexcept
    : m_transition(trans.m_transition)
    , m_newStateName(move(trans.m_newStateName))
{
}

template <typename T, typename E>
Transition<T, E>& Transition<T, E>::operator=(Transition&& trans) noexcept
{
    m_transition = trans.m_transition;
    m_newStateName.swap(trans.m_newStateName);
    return *this;
}

}

#endif //R_TYPE_TRANSITION_HPP
