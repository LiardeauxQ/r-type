//
// Created by nwmqpa on 11/10/19
//

#include "Entity.hpp"
#include "MD5Hasher.hpp"

namespace ecs {

Entity::Entity(Vec<Component> components)
    : m_components()
    , m_isDirty(true)
    , m_name(MD5Hasher::genRandomString(32))
{
    for (const auto& component : components) {
        m_components.insert({ component.getName(), component });
    }
}

Entity::Entity(Vec<Component> components, String name)
    : m_components()
    , m_isDirty(true)
    , m_name(name)
{
    for (const auto& component : components) {
        m_components.insert({ component.getName(), component });
    }
}

Entity::Entity(const Entity& entity)
    : m_components(entity.m_components)
    , m_isDirty(entity.m_isDirty)
    , m_name(entity.m_name)
{
}

Component& Entity::getComponent(String componentName)
{
    return m_components.at(componentName);
}

void Entity::markDirty()
{
    m_isDirty = true;
}

void Entity::markNonDirty()
{
    m_isDirty = false;
}

bool Entity::isDirty() const
{
    return m_isDirty;
}
Entity::Entity(Entity&& entity) noexcept
    : m_components(move(entity.m_components))
    , m_isDirty(entity.m_isDirty)
    , m_name(move(entity.m_name))
{
}

Entity& Entity::operator=(Entity&& entity) noexcept
{
    m_components.swap(entity.m_components);
    m_isDirty = entity.m_isDirty;
    m_name.swap(entity.m_name);
    return *this;
}

EntityBuilder::EntityBuilder()
    : m_components()
{
}

EntityBuilder EntityBuilder::with(Component& component)
{
    m_components.push_back(component);
    return *this;
}

Entity EntityBuilder::build()
{
    return Entity(m_components);
}

Entity EntityBuilder::build(const String& name)
{
    return Entity(m_components, name);
}

}