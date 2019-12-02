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

    cout << "With Parameters: " << this_thread::get_id() << " " << m_readerId << endl;
}

WithParameterSystem::WithParameterSystem(int readerId)
    : m_readerId(readerId)
{
}

Box<IFactorizable<String>> WithParameterSystem::copy() const
{
    return static_unique_pointer_cast<IFactorizable<String>>(std::make_unique<WithParameterSystem>());
}

String WithParameterSystem::getKey() const
{
    return String("base::WithParameterSystem");
}
