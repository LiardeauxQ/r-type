//
// Created by alex on 11/14/19.
//

#ifndef R_TYPE_DISPATCHER_HPP
#define R_TYPE_DISPATCHER_HPP

#include "Definitions.hpp"
#include "StateMachine.hpp"

class Dispatcher {
public:
    Dispatcher(uint8_t nbRunner);
private:
    uint8_t m_nbRunner;
};

#endif //R_TYPE_DISPATCHER_HPP
