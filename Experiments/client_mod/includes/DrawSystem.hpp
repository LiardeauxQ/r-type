//
// Created by alex on 11/21/19.
//

#ifndef R_TYPE_DRAWSYSTEM_HPP
#define R_TYPE_DRAWSYSTEM_HPP

#include "ISystem.hpp"
#include <SFML/Graphics.hpp>

class DrawSystem : public ecs::ISystem<ecs::StateData<string>> {
public:
    DrawSystem() = default;
    ~DrawSystem() override = default;
    [[nodiscard]] ecs::EntityRequest getDependencies() const override;
    any operator()(any entities, shared_ptr<ecs::StateData<string>> data) override;

    Box<IFactorizable> copy() const;
    String getKey() const;
};

#endif //R_TYPE_DRAWSYSTEM_HPP
