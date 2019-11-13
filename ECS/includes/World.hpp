//
// Created by alex on 11/8/19.
//

#pragma once

#include <vector>
#include <string>
#include "Definitions.hpp"
#include "Entity.hpp"
#include "IEntityComponentStorage.hpp"

namespace ecs {

    using namespace std;

    using Id = size_t;

    class World {
        public:
            World(Box<IEntityComponentStorage> database);
            ~World() = default;

            void createEntity();

            void createResource(const string& name);

            void registerComponent(Box<std::string> schema);

            Entity& fetchEntity(const string& name);
            //Resource& fetchResource(const string& name);
        private:
            Box<IEntityComponentStorage> database;
    };

}
