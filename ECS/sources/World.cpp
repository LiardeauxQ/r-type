//
// Created by alex on 11/27/19.
//

#include "World.hpp"

void ecs::World::storeEntity(Entity entity)
{
    m_storage->store({ move(entity) }); //TODO: use store unique.
}

ecs::World::World(unique_ptr<IEntityComponentStorage> storage)
    : m_storage(move(storage))
{
}

vector<ecs::Entity> ecs::World::fetchStorage(ecs::EntityRequest request)
{
    return m_storage->request(move(request));
}

void ecs::World::registerComponent(ecs::ComponentSchema schema)
{
    m_storage->addComponentSchema(move(schema));
}
