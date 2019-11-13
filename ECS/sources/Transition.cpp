//
// Created by alex on 11/14/19.
//

#include "Transition.hpp"

Transition::Transition(Transition::Name trans, Box<AbstractState> newState)
    : m_transition(trans)
    , m_newState(move(newState))
{}
