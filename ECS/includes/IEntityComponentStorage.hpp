//
// Created by alex on 11/8/19.
//

#pragma once

#include <vector>
#include "Definitions.hpp"
#include "EntityRequest.hpp"
#include "Entity.hpp"
#include "Component.hpp"

namespace ecs {

    class IEntityComponentStorage {

        public:
            Vec<Entity> request(Box<EntityRequest> request);
            void store(const Vec<Entity> &entities);

            void addComponentSchema(Box<ComponentSchema> schema);
            void removeComponentSchema(String &componentName);

    };

}
