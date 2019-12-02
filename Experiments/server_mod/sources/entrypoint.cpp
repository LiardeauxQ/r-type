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
        app.registerComponent(ecs::ComponentSchemaBuilder(String("Player"))
            .build());
        app.registerComponent(ecs::ComponentSchemaBuilder(String("Enemy"))
            .build());
        app.registerComponent(ecs::ComponentSchemaBuilder(String("Bullet"))
            .build());
        app.registerComponent(ecs::ComponentSchemaBuilder(String("Spawner"))
            .build());
        app.registerComponent(ecs::ComponentSchemaBuilder(String("Health"))
            .with(ecs::ComponentAttributeSchema("max", ecs::AttributeType::INT))
            .with(ecs::ComponentAttributeSchema("current", ecs::AttributeType::INT))
            .build());
        app.registerComponent(ecs::ComponentSchemaBuilder(String("Damage"))
              .with(ecs::ComponentAttributeSchema("amount", ecs::AttributeType::INT))
              .build());
        app.registerComponent(ecs::ComponentSchemaBuilder(String("Team"))
            .with(ecs::ComponentAttributeSchema("id", ecs::AttributeType::INT))
            .build());
        app.registerComponent(ecs::ComponentSchemaBuilder(String("AttackSpeed"))
            .with(ecs::ComponentAttributeSchema("frequency", ecs::AttributeType::INT))
            .with(ecs::ComponentAttributeSchema("elapsed_time", ecs::AttributeType::INT))
            .build());
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
