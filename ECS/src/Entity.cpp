//
// Created by nwmqpa on 11/10/19
//

#include "Entity.hpp"

namespace ecs {

    Entity::Entity(Vec<Component> components)
    : m_components()
    {
        for (auto component : components) {
            m_components.insert({component.getName(), component});
        }
    }

    Component &Entity::getComponent(String componentName) {
        return m_components.at(componentName);
    }

    void Entity::markDirty() {
        m_isDirty = true;
    }

    bool Entity::isDirty() const {
        return m_isDirty;
    }

    EntityBuilder::EntityBuilder()
    : m_components()
    {}
    
    EntityBuilder EntityBuilder::with(Component &component) {
        m_components.push_back(component);
        return *this;
    }

    Entity EntityBuilder::build() {
        return Entity(m_components);
    }

}