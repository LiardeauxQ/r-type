//
// Created by nwmqpa on 29/11/2019
//

#include "DummySystem.hpp"
#include "DummyBundle.hpp"
#include "MainMenuState.hpp"
#include "Application.hpp"

extern "C" {

    int registerStates(ecs::Application<string, ecs::Event> &app) {
        app.registerState<MainMenuState>();
        return 1;
    }

    int registerSystems(ecs::Application<string, ecs::Event> &app) {
        app.registerSystem<DummySystem>("base::MainMenuState");
        return 1;
    }

    int registerSchemas(ecs::Application<string, ecs::Event> &app) {
        app.registerComponent(ecs::ComponentSchemaBuilder(String("Position"))
            .with(ecs::ComponentAttributeSchema("x", ecs::AttributeType::INT))
            .with(ecs::ComponentAttributeSchema("y", ecs::AttributeType::INT))
            .with(ecs::ComponentAttributeSchema("z", ecs::AttributeType::INT))
            .build());
        app.registerComponent(ecs::ComponentSchemaBuilder(String("Velocity"))
            .with(ecs::ComponentAttributeSchema("x", ecs::AttributeType::INT))
            .with(ecs::ComponentAttributeSchema("y", ecs::AttributeType::INT))
            .with(ecs::ComponentAttributeSchema("z", ecs::AttributeType::INT))
            .build());
        return 1;
    }

    int addBundle(ecs::Application<string, ecs::Event> &app) {
        app.withBundle<DummyBundle>();
        return 1;
    }

}
