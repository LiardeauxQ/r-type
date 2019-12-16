//
// Created by nwmqpa on 29/11/2019
//

#include <iostream>
#include "DummySystem.hpp"

[[nodiscard]] ecs::EntityRequest DummySystem::getDependencies() const {
    std::cout << "fetched." << std::endl;
    return ecs::EntityRequestBuilder()
                .with("Position")
                .with("Velocity")
                .build();
}

any DummySystem::operator()(any entities, shared_ptr<ecs::StateData<string>> data) {
    Vec<ecs::Entity> &tempEntities = any_cast<Vec<ecs::Entity> &>(entities);

    for (const auto& entity : tempEntities) {
        std::cout << entity.getName() << std::endl;
        for (const auto& component: entity.getComponents()) {
            std::cout << "\t" << component.first << ": " << component.second << std::endl;
        }
    }

    for (auto& entity : tempEntities) {
        auto& position = entity.getComponent("Position");
        auto& velocity = entity.getComponent("Velocity");
        position.getAttribute("x").setValue(position.getAttribute("x").getValue<int>() + velocity.getAttribute("x").getValue<int>());
        position.getAttribute("y").setValue(position.getAttribute("y").getValue<int>() + velocity.getAttribute("y").getValue<int>());
        position.getAttribute("z").setValue(position.getAttribute("z").getValue<int>() + velocity.getAttribute("z").getValue<int>());
        entity.markDirty();
    }
    return entities;

}

Box<IFactorizable<String>> DummySystem::copy() const
{
    return static_unique_pointer_cast<IFactorizable<String>>(std::make_unique<DummySystem>());
}

String DummySystem::getKey() const
{
    return String("base::DummySystem");
}
