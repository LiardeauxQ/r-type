//
// Created by alex on 11/13/19.
//

#include "StateMachine.hpp"

void StateMachine::push(Box<AbstractState> newState)
{
    if (!m_states.empty())
        m_states.back()->onPause();
    newState->onStart();
    m_states.push_back(move(newState));
}

Box<AbstractState> StateMachine::pop()
{
    if (m_states.empty())
        return nullptr;
    auto ret = move(m_states.back());
    ret->onStop();
    m_states.pop_back();
    if (!m_states.empty())
        m_states.back()->onResume();
    return ret;
}

void StateMachine::run()
{
    while (m_running) {
        Transition trans;

        if (!m_states.empty())
            trans = m_states.back()->update();
        else
            break;
        for (auto& s : m_states)
            s->shadowUpdate();
        this->transition(move(trans));
    }
}

void StateMachine::transition(Transition trans)
{
    switch (trans.m_transition) {
    case Transition::Name::POP:
        this->pop();
        break;
    case Transition::Name::PUSH:
        this->push(move(trans.m_newState));
        break;
    case Transition::Name::QUIT:
        for (auto &s: m_states)
            s->onStop();
        m_running = false;
        break;
    case Transition::NONE:
        break;
    }
}
StateMachine::StateMachine(unique_ptr<AbstractState> initial)
    : m_states()
    , m_running(true)
{
    m_states.push_back(move(initial));
}
