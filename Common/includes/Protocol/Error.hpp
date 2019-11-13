//
// Created by alex on 11/12/19.
//

#ifndef R_TYPE_ERROR_HPP
#define R_TYPE_ERROR_HPP

#include "Message.hpp"

class Error : Message {
    Error(uint32_t code, MESSAGE_ID idFrom);

    MESSAGE_ID m_idFrom;
    uint32_t m_code;
};

#endif //R_TYPE_ERROR_HPP
