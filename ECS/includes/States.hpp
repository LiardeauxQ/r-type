//
// Created by alex on 11/13/19.
//

#ifndef R_TYPE_STATESSTACK_HPP
#define R_TYPE_STATESSTACK_HPP

#include "Definitions.hpp"
#include "AbstactState.hpp"
#include "Transition.hpp"

class States {
public:
    States() = default;

    void update();
private:
    void push(Box<AbstractState> newState);
    Box<AbstractState> pop();
    vector<Box<AbstractState>> m_states;
};

#endif //R_TYPE_STATESSTACK_HPP
