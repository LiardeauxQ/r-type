//
// Created by alex on 11/21/19.
//

#include "DrawSystem.hpp"

ecs::EntityRequest DrawSystem::getDependencies() const
{
    return ecs::EntityRequest({}, {});
}

void DrawSystem::operator()(any entities, shared_ptr<ecs::StateData<string>> data)
{
    cout << "Test" << endl;
}
