//
// Created by alex on 11/13/19.
//

#ifndef R_TYPE_STATESSTACK_HPP
#define R_TYPE_STATESSTACK_HPP

#include "Definitions.hpp"
#include "AbstactState.hpp"
#include "Transition.hpp"

struct Transition;
class AbstractState;

class StateMachine {
public:
    StateMachine();

    void update();
private:
    void transition(Transition trans);
    void push(Box<AbstractState> newState);
    Box<AbstractState> pop();
    vector<Box<AbstractState>> m_states;
    bool m_running;
};

#endif //R_TYPE_STATESSTACK_HPP
