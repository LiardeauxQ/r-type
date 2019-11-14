//
// Created by alex on 11/14/19.
//

#ifndef R_TYPE_DISPATCHER_HPP
#define R_TYPE_DISPATCHER_HPP

#include "Definitions.hpp"
#include "StateMachine.hpp"
#include <queue>

typedef uint8_t System; // TODO implement System

class Dispatcher {
public:
    explicit Dispatcher(uint8_t nbRunner);
    Dispatcher(Dispatcher&& dispatcher) noexcept;
    Dispatcher& operator=(Dispatcher&& dispatcher) noexcept;

    ~Dispatcher() = default;

    void dispatch();
private:
    uint8_t m_nbRunner;
    vector<System> m_systems;
};

#endif //R_TYPE_DISPATCHER_HPP
