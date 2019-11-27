//
// Created by nwmqpa on 11/25/19.
//

#pragma once

#include <ostream>
#include "IEntityComponentStorage.hpp"

namespace ecs {

    class BasicEntityComponentStorage {

        public:
            BasicEntityComponentStorage();

            bool hasSchema(const String &name) const;
            ComponentSchema getSchema(const String &name) const;

            Vec<Entity> request(const EntityRequest &request);
            void store(const Vec<Entity> &entities);

            void addComponentSchema(const ComponentSchema &schema);
            void removeComponentSchema(const String &componentName);

            Map<String, Component> getComponents(const String &name) const;

            Vec<ComponentSchema> getComponentsSchemas() const { return m_schemas; }

        private:

            Vec<ComponentSchema> m_schemas;
            Map<String, Map<String, Component>> m_components;

    };

}

std::ostream &operator<<(std::ostream &stream, const ecs::BasicEntityComponentStorage &components);
