//
// Created by alex on 11/10/19.
//

#pragma once

#include "Definitions.hpp"

class ISerializable {
    public:
        virtual ~ISerializable() = default;
        virtual Vec<u8> serialize() const = 0;
        virtual void deserialize(Vec<u8> &data) = 0;
};
