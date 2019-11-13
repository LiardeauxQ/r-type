//
// Created by alex on 11/13/19.
//

#include "States.hpp"

void States::push(Box<AbstractState> newState)
{
    m_states.push_back(move(newState));
}

Box<AbstractState> States::pop()
{
    if (m_states.empty())
        return nullptr;
    auto ret = move(m_states.back());
    m_states.pop_back();
    return ret;
}
void States::update()
{
    Transition trans;

    if (!m_states.empty())
        trans = m_states.back()->update();

    for (auto& s: m_states) {
        s->shadowUpdate();
    }

    switch (trans.m_transition) {
    case Transition::Name::POP:
        this->pop();
        break;
    case Transition::Name::PUSH:
        this->push(move(trans.m_newState));
        break;
    case Transition::Name::PAUSE:
        if (!m_states.empty()) {
            m_states.back()->onPause();
            // TODO: Pause
        }
        break;
    case Transition::NONE:
        break;
    }
}
