//
// Created by alex on 11/14/19.
//

#include "Dispatcher.hpp"
#include <iostream>

Dispatcher::Dispatcher(uint8_t nbRunner)
    : m_nbRunner(nbRunner)
{}

Dispatcher::Dispatcher(Dispatcher&& dispatcher) noexcept
    : m_nbRunner(dispatcher.m_nbRunner)
    , m_systems(move(dispatcher.m_systems))
{}

Dispatcher& Dispatcher::operator=(Dispatcher&& dispatcher) noexcept
{
    m_systems.swap(dispatcher.m_systems);
    m_nbRunner = dispatcher.m_nbRunner;
    return *this;
}
void Dispatcher::dispatch()
{ // TODO Orchestrate over threads.
    for (auto& s: m_systems) {
        cout << "Running system: " << s << endl;
    }
}
