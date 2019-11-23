//
// Created by alex on 11/21/19.
//

#include "WithParameterSystem.hpp"

ecs::EntityRequest WithParameterSystem::getDependencies() const
{
    return ecs::EntityRequest({}, {});
}

void WithParameterSystem::operator()(any entities, shared_ptr<ecs::StateData<string>> data)
{
    cout << "With Parameters: " << m_readerId << endl;
}

WithParameterSystem::WithParameterSystem(int readerId)
    : m_readerId(readerId)
{
}
