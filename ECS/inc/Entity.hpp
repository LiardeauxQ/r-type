//
// Created by nwmqpa on 11/10/19
//

#pragma once

#include "Definitions.hpp"
#include "Component.hpp"

namespace ecs {

    class Entity {
        
        public:
            Entity(Vec<Component> components);

            Component &getComponent(String componentName);

            void markDirty();
            bool isDirty() const;

        private:
            Map<String, Component> m_components;
            bool m_isDirty;

    };

    class EntityBuilder {

        public:
            EntityBuilder();
            EntityBuilder with(Component &component);
            Entity build();

        private:
            Vec<Component> m_components;

    };

}