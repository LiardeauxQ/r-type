//
// Created by alex on 11/14/19.
//

#include "AbstactState.hpp"

AbstractState::AbstractState(AbstractState&& rhs) noexcept
    : m_dispatcher(move(rhs.m_dispatcher))
{}

AbstractState& AbstractState::operator=(AbstractState&& rhs) noexcept
{
    m_dispatcher.swap(rhs.m_dispatcher);
    return *this;
}
