//
// Created by nwmqpa on 11/10/19
//

#pragma once

#include "Definitions.hpp"

namespace ecs {

using namespace std;
using ComponentVector = vector<string>;

/// TODO: Implements Serialize/Deserialize
class EntityRequest {
public:
    EntityRequest(ComponentVector withs, ComponentVector without);
    EntityRequest(EntityRequest&& request) noexcept;

    [[nodiscard]] ComponentVector getWiths() const { return m_withs; }
    [[nodiscard]] ComponentVector getWithouts() const { return m_withouts; }

private:
    ComponentVector m_withs;
    ComponentVector m_withouts;
};

class EntityRequestBuilder {
public:
    EntityRequestBuilder();

    EntityRequestBuilder with(const String& componentName);
    EntityRequestBuilder without(const String& componentName);
    EntityRequest build();

private:
    ComponentVector m_withs;
    ComponentVector m_withouts;
};

}