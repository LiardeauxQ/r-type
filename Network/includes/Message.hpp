//
// Created by alex on 11/10/19.
//

#pragma once

#include "ISerializable.hpp"
#include "IFactorizable.hpp"
#include "Definitions.hpp"
#include <exception>

struct MessageDeserializationException : public std::exception {
	const char* what () const throw () {
    	return "Cannot deserialize a message";
    }
};

class Message : public ISerializable, public IFactorizable<String> {

    public:
        explicit Message() {};

        virtual String getKey() const {
            return "base";
        }

};
