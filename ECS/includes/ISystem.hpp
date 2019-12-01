//
// Created by nwmqpa on 11/20/19
//

#pragma once

#include "AbstractState.hpp"
#include "Definitions.hpp"
#include "EntityRequest.hpp"
#include "IFactorizable.hpp"
#include <any>

namespace ecs {

using namespace std;
template<typename T> struct StateData;

template <typename T>
class ISystem : public IFactorizable<String> {

public:
    virtual ~ISystem() = default;
    [[nodiscard]] virtual EntityRequest getDependencies() const = 0;
    virtual void operator()(any entities, shared_ptr<T> data) = 0;
};

}
