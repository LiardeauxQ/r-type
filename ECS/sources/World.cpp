//
// Created by alex on 11/8/19.
//

#include "World.hpp"

// ecs::World::World(Box<ecs::IEntityComponentStorage> database)
// {
//
// }

void ecs::World::createEntity()
{

}

ecs::Entity* ecs::World::fetchEntity(const std::string& name)
{
    return nullptr;
}

void ecs::World::createResource(std::string name)
{
    m_resources.insert_or_assign(move(name), any());
}

void ecs::World::registerComponent(std::string schema)
{
    m_resources.insert_or_assign(move(schema), any());
}
