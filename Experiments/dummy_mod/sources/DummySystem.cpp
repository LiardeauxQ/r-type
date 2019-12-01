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

void DummySystem::operator()(any entities, shared_ptr<ecs::StateData<string>> data) {
    auto tempEntities = any_cast<Vec<ecs::Entity>>(entities);

    for (const auto& entity : tempEntities) {
        std::cout << entity.getName() << std::endl;
        for (const auto& tuple : entity.getComponents()) {
            std::cout << "\t" << tuple.first << ": " << tuple.second << std::endl;
        }
    }
}

Box<IFactorizable<String>> DummySystem::copy() const
{
    return static_unique_pointer_cast<IFactorizable<String>>(std::make_unique<DummySystem>());
}

String DummySystem::getKey() const
{
    return String("base::DummySystem");
}