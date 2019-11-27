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
    const char* what() const throw()
    {
        return "Component does not comply with schema";
    }
};

struct SchemaNameAlreadyExistsException : public std::exception {
    const char* what() const throw()
    {
        return "Schema already exists";
    }
};

struct SchemaNotFound : public std::exception {
    const char* what() const throw()
    {
        return "Schema was not found";
    }
};

class IEntityComponentStorage {

public:
    virtual Vec<Entity> request(Box<EntityRequest> request) = 0;
    virtual void store(const Vec<Entity>& entities) = 0;

    virtual void addComponentSchema(Box<ComponentSchema> schema) = 0;
    virtual void removeComponentSchema(String& componentName) = 0;
};

}
