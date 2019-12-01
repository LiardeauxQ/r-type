//
// Created by nwmqpa on 29/11/2019
//

#include "DummySystem.hpp"
#include "Dispatcher.hpp"

extern "C" {

    int registerSystems(Box<ecs::Dispatcher<ecs::StateData<string>, ecs::Error>> &dispatcher) {
        dispatcher->registerSystem<DummySystem>();
        return 1;
    }

    int registerSchemas(ecs::World &world) {
        world.registerComponent(ecs::ComponentSchemaBuilder(String("Position"))
            .with(ecs::ComponentAttributeSchema("x", ecs::AttributeType::INT))
            .with(ecs::ComponentAttributeSchema("y", ecs::AttributeType::INT))
            .with(ecs::ComponentAttributeSchema("z", ecs::AttributeType::INT))
            .build());
        world.registerComponent(ecs::ComponentSchemaBuilder(String("Velocity"))
            .with(ecs::ComponentAttributeSchema("x", ecs::AttributeType::INT))
            .with(ecs::ComponentAttributeSchema("y", ecs::AttributeType::INT))
            .with(ecs::ComponentAttributeSchema("z", ecs::AttributeType::INT))
            .build());
        return 1;
    }

}
