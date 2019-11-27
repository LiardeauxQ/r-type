//
// Created by nwmqpa on 11/10/19
//

#pragma once

#include <iostream>
#include "Definitions.hpp"
#include "Component.hpp"

namespace ecs {

    class Entity {
        
        public:
            Entity(Vec<Component> components);
            Entity(Vec<Component> components, String name);

            Entity(const Entity &entity);

            Component &getComponent(String componentName);
            Map<String, Component> getComponents() const { return m_components; }
            String getName() const { return m_name; }

            void markDirty();
            bool isDirty() const;

        private:
            Map<String, Component> m_components;
            bool m_isDirty;
            String m_name;

    };

    class EntityBuilder {

        public:
            EntityBuilder();
            EntityBuilder with(Component &component);
            Entity build();
            Entity build(const String &name);

        private:
            Vec<Component> m_components;

    };

}