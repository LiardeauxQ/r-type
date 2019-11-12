//
// Created by nwmqpa on 11/11/19
//

#include "Component.hpp"

namespace ecs {

    ComponentAttribute::ComponentAttribute(const String &name, const AttributeType type, std::any value)
    : m_name(name)
    , m_type(type)
    , m_value(value)
    {}

    Component::Component(const String &name)
    : m_name(name)
    , m_attributes()
    {}

    void Component::addAttribute(ComponentAttribute &attribute) {
        m_attributes.insert({attribute.getName(), attribute});
    }

    void Component::removeAttribute(String name) {
        m_attributes.erase(name);
    }

    String Component::getName() const {
        return m_name;
    }
    
    ComponentAttribute &Component::getAttribute(String name) {
        return m_attributes.at(name);
    }

    
    ComponentAttributeSchema::ComponentAttributeSchema(const String &name, AttributeType &type)
    : m_name(name)
    , m_type(type)
    {}

    ComponentSchema::ComponentSchema(const String &name, Vec<ComponentAttributeSchema> &attributesSchema)
    : m_name(name)
    , m_attributesSchema(attributesSchema)
    {}

    ComponentSchemaBuilder::ComponentSchemaBuilder(const String &name)
    : m_name(name)
    {}

    ComponentSchemaBuilder ComponentSchemaBuilder::with(ComponentAttributeSchema &attributeSchema) {
        m_attributesSchema.push_back(attributeSchema);
        return *this;
    }

    ComponentSchema ComponentSchemaBuilder::build() {
        return ComponentSchema(m_name, m_attributesSchema);
    }

}