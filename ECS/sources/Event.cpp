//
// Created by Quentin Liardeaux on 11/19/19.
//

#include "Event.hpp"

ecs::Event::Event(const string& type, any value)
    : m_type(hash<string>()(type))
    , m_value(value) {}

ecs::Event::Event(const Event& other)
    : m_type(other.m_type)
    , m_value(other.m_value) {}

bool ecs::Event::isOfType(const string& type) const {
    return m_type == hash<string>()(type);
}

ecs::Event& ecs::Event::operator=(const ecs::Event& other) {
    m_type = other.m_type;
    m_value = other.m_value;
    return (*this);
}
