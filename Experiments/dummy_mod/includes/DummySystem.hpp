//
// Created by nwmqpa on 28/11/19
//

#include "ISystem.hpp"

class DummySystem : public ecs::ISystem<ecs::StateData<string>> {
public:
    DummySystem() = default;
    [[nodiscard]] ecs::EntityRequest getDependencies() const;
    any operator()(any entities, shared_ptr<ecs::StateData<string>> data);

    Box<IFactorizable> copy() const;
    String getKey() const;

};