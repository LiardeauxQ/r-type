//
// Created by alex on 11/8/19.
//

#ifndef CPP_RTYPE_2019_WORLD_HPP
#define CPP_RTYPE_2019_WORLD_HPP

#include <vector>
#include "Definitions.hpp"

namespace ecs {

using namespace std;

using Id = size_t;

class World {
public:
    World(Box<IEcdb> database);
    ~World() = default;

    void createEntity();

    void createResource(const string& name);

    void registerComponent(Box<ComponentSchema> schema);

    Entity& fetchEntity(const string& name);
    Resource& fetchResource(const string& name);
private:
    Box<IEcdb> database;
};

}
#endif //CPP_RTYPE_2019_WORLD_HPP
