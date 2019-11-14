//
// Created by alex on 11/14/19.
//

#include "AbstactState.hpp"

AbstractState::AbstractState(AbstractState&& rhs) noexcept
    : m_systems(move(rhs.m_systems))
{}

AbstractState& AbstractState::operator=(AbstractState&& rhs) noexcept
{
    m_systems.swap(rhs.m_systems);
    return *this;
}
