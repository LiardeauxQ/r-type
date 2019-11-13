//
// Created by alex on 11/14/19.
//

#ifndef R_TYPE_TRANSITION_HPP
#define R_TYPE_TRANSITION_HPP

#include "AbstactState.hpp"

class AbstractState;

struct Transition {
    enum Name {
        POP,
        PUSH,
        PAUSE,
        NONE,
    };

    explicit Transition(Name trans = NONE, Box<AbstractState> newState = nullptr);

    Name m_transition;
    Box<AbstractState> m_newState;
};


#endif //R_TYPE_TRANSITION_HPP
