//
// Created by alex on 11/21/19.
//

#ifndef R_TYPE_WITHPARAMETERSYSTEM_HPP
#define R_TYPE_WITHPARAMETERSYSTEM_HPP

#include "ISystem.hpp"

class WithParameterSystem : public ecs::ISystem<ecs::StateData<string>> {
public:
    explicit WithParameterSystem(int readerId);
    ~WithParameterSystem() override = default;
    [[nodiscard]] ecs::EntityRequest getDependencies() const override;
    void operator()(any entities, shared_ptr<ecs::StateData<string>> data) override;

    Box<IFactorizable> copy() const;
    String getKey() const;

private:
    int m_readerId;
};

#endif //R_TYPE_WITHPARAMETERSYSTEM_HPP
