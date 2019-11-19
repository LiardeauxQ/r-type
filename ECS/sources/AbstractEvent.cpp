//
// Created by Quentin Liardeaux on 11/19/19.
//

#include "AbstractEvent.hpp"

ecs::AbstractEvent::AbstractEvent(string const &type, any value)
    : m_type(hash<string>()(type))
    , m_value(value) {}

bool ecs::AbstractEvent::isOfType(string const &type) const {
    return m_type == hash<string>()(type);
}