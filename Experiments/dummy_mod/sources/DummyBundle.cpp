//
// Created by alex on 11/26/19.
//

#include "DummyBundle.hpp"

void DummyBundle::load(ecs::World& m_world, EventHandler& handler)
{
    for (int i = 0; i < 10; i++) {
        auto position = ecs::Component("Position");
        auto velocity = ecs::Component("Velocity");

        position.addAttribute(ecs::ComponentAttribute(String("x"), ecs::AttributeType::INT, std::any(i)));
        position.addAttribute(ecs::ComponentAttribute(String("y"), ecs::AttributeType::INT, std::any(i)));
        position.addAttribute(ecs::ComponentAttribute(String("z"), ecs::AttributeType::INT, std::any(i)));
        velocity.addAttribute(ecs::ComponentAttribute(String("x"), ecs::AttributeType::INT, std::any(i)));
        velocity.addAttribute(ecs::ComponentAttribute(String("y"), ecs::AttributeType::INT, std::any(i)));
        velocity.addAttribute(ecs::ComponentAttribute(String("z"), ecs::AttributeType::INT, std::any(i)));
        auto entityBuilder = ecs::EntityBuilder().with(position);
        if (i % 2)
            entityBuilder.with(velocity);
        m_world.storeEntity(entityBuilder.build());
    }
}
