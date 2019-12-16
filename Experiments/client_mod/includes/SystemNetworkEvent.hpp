//
// Created by alex on 11/26/19.
//

#ifndef R_TYPE_SYSTEMNETWORKEVENT_HPP
#define R_TYPE_SYSTEMNETWORKEVENT_HPP

#include "Event.hpp"
#include "ISystem.hpp"
#include "AbstractState.hpp"

class SystemNetworkEvent : public ecs::ISystem<ecs::StateData<string>> {
public:
    ~SystemNetworkEvent() override = default;
    [[nodiscard]] ecs::EntityRequest getDependencies() const override;
    any operator()(any entities, shared_ptr<ecs::StateData<string>> data) override;

    Box<IFactorizable> copy() const;
    String getKey() const;
};

#endif //R_TYPE_SYSTEMNETWORKEVENT_HPP
