//
// Created by alex on 11/10/19.
//

#pragma once

#include <exception>
#include <vector>
#include <string>
#include <protocol.hpp>

struct MessageDeserializationException : public std::exception {
	const char* what () const throw () {
    	return "Cannot deserialize a message";
    }
};

class Message {
public:
    explicit Message(uint8_t id) : m_id(id) {};
    virtual ~Message() = default;

    [[nodiscard]] virtual std::vector<uint8_t> serialize() const { return std::vector<uint8_t>(); };
    [[nodiscard]] virtual size_t getSize() const { return 0; }
    [[nodiscard]] uint8_t getId() const { return m_id; }

    static std::vector<uint8_t> createHeader(uint8_t id, uint16_t packet_size);
protected:
    uint8_t m_id;
    packet_header_t hdr;
};
