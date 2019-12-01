//
// Created by nwmqpa on 11/25/19.
//

#pragma once

#include "IEntityComponentStorage.hpp"
#include <ostream>

namespace ecs {

class BasicEntityComponentStorage : public IEntityComponentStorage {

public:
    BasicEntityComponentStorage();

    [[nodiscard]] bool hasSchema(const String& name) const;
    [[nodiscard]] const ComponentSchema& getSchema(const String& name) const;

    Vec<Entity> request(EntityRequest request);
    void store(const Vec<Entity>& entities);

    void addComponentSchema(ComponentSchema schema);
    void removeComponentSchema(const String& componentName);

    [[nodiscard]] Map<String, Component> getComponents(const String& name) const;

    Vec<ComponentSchema> m_schemas;

private:
    Map<String, Map<String, Component>> m_components;
};

}

std::ostream& operator<<(std::ostream& stream, const ecs::BasicEntityComponentStorage& components);
