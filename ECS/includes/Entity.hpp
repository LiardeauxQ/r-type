//
// Created by nwmqpa on 11/10/19
//

#pragma once

#include "Component.hpp"
#include "Definitions.hpp"
#include <iostream>

namespace ecs {

class Entity {

public:
    explicit Entity(Vec<Component> components);
    Entity(Vec<Component> components, String name);

    Entity(Entity&& entity) noexcept;
    Entity& operator=(Entity&& entity) noexcept;

    Entity(const Entity& entity);

    Component& getComponent(String componentName);
    [[nodiscard]] Map<String, Component> getComponents() const { return m_components; }
    [[nodiscard]] String getName() const { return m_name; }

    void markDirty();
    void markNonDirty();
    [[nodiscard]] bool isDirty() const;

private:
    Map<String, Component> m_components;
    bool m_isDirty;
    String m_name;
};

class EntityBuilder {

public:
    EntityBuilder();
    EntityBuilder with(Component& component);
    Entity build();
    Entity build(const String& name);

private:
    Vec<Component> m_components;
};

}