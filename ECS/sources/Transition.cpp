//
// Created by alex on 11/14/19.
//

#include "Transition.hpp"

Transition::Transition(Transition::Name trans, Box<AbstractState> newState)
    : m_transition(trans)
    , m_newState(move(newState))
{}

Transition::Transition(Transition&& trans)
    : m_transition(trans.m_transition)
    , m_newState(move(trans.m_newState))
{}

Transition& Transition::operator=(Transition&& trans)
{
    m_transition = trans.m_transition;
    m_newState.swap(trans.m_newState);
    return *this;
}
