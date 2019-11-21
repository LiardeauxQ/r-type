//
// Created by alex on 11/8/19.
//

#include "World.hpp"

void ecs::World::createEntity()
{

}

ecs::Entity* ecs::World::fetchEntity(const std::string& name)
{
    return nullptr;
}

void ecs::World::registerComponent(std::string schema)
{
    m_resources.insert_or_assign(move(schema), any());
}
