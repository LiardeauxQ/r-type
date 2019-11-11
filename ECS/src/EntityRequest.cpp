//
// Created by nwmqpa on 11/10/19
//

#include "EntityRequest.hpp"

namespace ecs {

    EntityRequest::EntityRequest(ComponentVector withs, ComponentVector without)
    : m_withs()
    , m_withouts()
    {}

    EntityRequestBuilder::EntityRequestBuilder()
    : m_withs()
    , m_withouts()
    {}

    EntityRequestBuilder EntityRequestBuilder::with(const String &componentName) {
        m_withs.push_back(componentName);
        return *this;
    }

    EntityRequestBuilder EntityRequestBuilder::without(const String &componentName) {
        m_withouts.push_back(componentName);
        return *this;
    }

    EntityRequest EntityRequestBuilder::build() {
        return EntityRequest(m_withs, m_withouts);
    }

}