//
// Created by alex on 11/12/19.
//

#include "Protocol/Error.hpp"

Error::Error(uint32_t code, MESSAGE_ID idFrom)
    : Message(ERROR)
    , m_idFrom(idFrom)
    , m_code(code)
{}
