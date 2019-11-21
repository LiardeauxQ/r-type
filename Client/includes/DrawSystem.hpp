//
// Created by alex on 11/21/19.
//

#ifndef R_TYPE_DRAWSYSTEM_HPP
#define R_TYPE_DRAWSYSTEM_HPP

#include "ISystem.hpp"

class DrawSystem : public ecs::ISystem<ecs::StateData<string>> {
public:
    ~DrawSystem() override = default;
    [[nodiscard]] ecs::EntityRequest getDependencies() const override;
    void operator()(any entities, shared_ptr<ecs::StateData<string>> data) override;
};

#endif //R_TYPE_DRAWSYSTEM_HPP
