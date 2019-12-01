//
// Created by alex on 11/8/19.
//

#pragma once

#include "Component.hpp"
#include "Definitions.hpp"
#include "Entity.hpp"
#include "EntityRequest.hpp"
#include <exception>
#include <vector>

namespace ecs {

struct ComponentDoesNotComplyWithSchema : public std::exception {
    [[nodiscard]] const char* what() const noexcept final
    {
        return "Component does not comply with schema";
    }
};

struct SchemaNameAlreadyExistsException : public std::exception {
    [[nodiscard]] const char* what() const noexcept final
    {
        return "Schema already exists";
    }
};

struct SchemaNotFound : public std::exception {
    [[nodiscard]] const char* what() const noexcept final
    {
        return "Schema was not found";
    }
};

class IEntityComponentStorage {
public:
    virtual ~IEntityComponentStorage() = default;
    virtual Vec<Entity> request(EntityRequest request) = 0;

    virtual void store(const Vec<Entity>& entities) = 0;

    virtual void addComponentSchema(ComponentSchema schema) = 0;
    virtual void removeComponentSchema(const String& componentName) = 0;
};

}
