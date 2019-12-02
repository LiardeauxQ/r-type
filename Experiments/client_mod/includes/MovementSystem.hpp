//
// Created by alex on 11/21/19.
//

#ifndef R_TYPE_MOVEMENTSYSTEM_HPP
#define R_TYPE_MOVEMENTSYSTEM_HPP

#include <ISystem.hpp>
#include <AbstractState.hpp>
#include <SFML/Graphics.hpp>

class MovementSystem : public ecs::ISystem<ecs::StateData<string>> {
public:
    ~MovementSystem() override = default;
    ecs::EntityRequest getDependencies() const override;
    void operator()(any entities, shared_ptr<ecs::StateData<string>> data) override;

    Box<IFactorizable> copy() const;
    String getKey() const;
};

#endif //R_TYPE_MOVEMENTSYSTEM_HPP
