//
// Created by alex on 11/10/19.
//

#pragma once

#include "ISerializable.hpp"
#include "IFactorizable.hpp"
#include "Definitions.hpp"

class Message : ISerializable, IFactorizable<String> {

    public:
        explicit Message() {};

        String getId() const {
            return "base";
        }

        virtual void deserialize(Vec<u8> data) = 0;

        virtual Box<IFactorizable> copy() const = 0;

        virtual Vec<u8> serialize() const override = 0;

};
