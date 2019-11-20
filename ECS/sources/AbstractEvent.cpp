//
// Created by Quentin Liardeaux on 11/19/19.
//

#include "AbstractEvent.hpp"

ecs::Event::Event(string const &type, any value)
    : m_type(hash<string>()(type))
    , m_value(value) {}

bool ecs::Event::isOfType(string const &type) const {
    return m_type == hash<string>()(type);
}