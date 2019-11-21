//
// Created by alex on 11/21/19.
//

#include "MovementSystem.hpp"

ecs::EntityRequest MovementSystem::getDependencies() const
{
    return ecs::EntityRequest({}, {});
}

void MovementSystem::operator()(any entities, shared_ptr<ecs::StateData<string>> data)
{
    cout << "Moving entities." << endl;
}
