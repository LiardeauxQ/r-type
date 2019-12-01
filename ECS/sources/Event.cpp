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

ecs::Event::Event(ecs::Event&& other) noexcept
    : m_type(other.m_type)
    , m_value(move(other.m_value))
{}
ecs::Event& ecs::Event::operator=(ecs::Event&& other) noexcept
{
    m_value.swap(other.m_value);
    m_type = other.m_type;
    return *this;
}
