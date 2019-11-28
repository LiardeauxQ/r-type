//
// Created by alex on 11/8/19.
//

#pragma once

#include "BasicEntityComponentStorage.hpp"
#include "Definitions.hpp"
#include "Entity.hpp"
#include "IEntityComponentStorage.hpp"
#include "StopWatch.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace ecs {

using namespace std;

using Id = size_t;

class World {
public:
    explicit World(unique_ptr<IEntityComponentStorage> storage);
    ~World() = default;

    template<typename T>
    T& fetchResource(const string& name);

    template<typename T>
    void writeResource(const string& name, T&& data);

    template<typename T>
    void writeResource(const string& name);

    template<typename T, typename... Args>
    void writeResource(const string& name, Args&&... args);

    vector<Entity> fetchStorage(EntityRequest request);
    void registerComponent(ComponentSchema schema);
    void storeEntity(Entity entity);

    StopWatch m_timer;
    unique_ptr<IEntityComponentStorage> m_storage;
private:
    unordered_map<string, any> m_resources;
    unordered_map<string, vector<Component>> m_components;
};

template<typename T>
T& World::fetchResource(const string& name)
{
    return any_cast<T&>(m_resources.at(name));
}

template<typename T>
void World::writeResource(const string& name, T&& data)
{
    m_resources.insert_or_assign(name, forward<T>(data));
}

template<typename T>
void World::writeResource(const string& name)
{
    static_assert(is_default_constructible<T>::value, "To write a resource without argument the class need to implement a default constructor.");
    m_resources[name] = make_any<T>();
}

template<typename T, typename... Args>
void World::writeResource(const string& name, Args&&... args)
{
    m_resources.insert_or_assign(name, make_any<T>(forward<Args>(args)...));
}

}
