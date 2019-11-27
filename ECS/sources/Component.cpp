//
// Created by nwmqpa on 11/11/19
//

#include <iostream>
#include "Component.hpp"

namespace ecs {

    ComponentAttribute::ComponentAttribute(const String &name, const AttributeType type, std::any value)
    : m_name(name)
    , m_type(type)
    , m_value(value)
    {}

    Component::Component()
    : m_name("")
    , m_attributes()
    {}

    Component::Component(const String &name)
    : m_name(name)
    , m_attributes()
    {}

    Vec<ComponentAttribute> Component::getAttributes() const {
        auto attributes = Vec<ComponentAttribute>();
        for (auto attribute : m_attributes) {
            attributes.push_back(attribute.second);
        }
        return attributes;
    }

    void Component::addAttribute(ComponentAttribute attribute) {
        m_attributes.insert({attribute.getName(), attribute});
    }

    void Component::removeAttribute(String name) {
        m_attributes.erase(name);
    }

    String Component::getName() const {
        return m_name;
    }

    bool Component::complyWith(const ComponentSchema &schema) {
        for (auto attributes : m_attributes) {
        }
        return true;
    }
    
    ComponentAttribute &Component::getAttribute(String name) {
        return m_attributes.at(name);
    }

    
    ComponentAttributeSchema::ComponentAttributeSchema(const String &name, AttributeType type)
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

    ComponentSchemaBuilder ComponentSchemaBuilder::with(ComponentAttributeSchema attributeSchema) {
        m_attributesSchema.push_back(attributeSchema);
        return *this;
    }

    ComponentSchema ComponentSchemaBuilder::build() {
        return ComponentSchema(m_name, m_attributesSchema);
    }

}

std::ostream &operator<<(std::ostream &stream, const ecs::Component &comp) {
    stream << "{ ";
    for (auto attribute : comp.getAttributes()) {
        stream << attribute << ", ";
    }
    stream << " }";
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const ecs::ComponentAttribute &attr) {
    stream << attr.getName() << ": ";
    switch (attr.getType()) {
        case ecs::AttributeType::INT:
            stream << "Int(" << attr.getValue<int>() << ")";
            break;
        case ecs::AttributeType::FLOAT:
            stream << "Float(" << attr.getValue<float>() << ")";
            break;
        case ecs::AttributeType::BOOL:
            stream << "Bool(" << attr.getValue<bool>() << ")";
            break;
        case ecs::AttributeType::STRING:
            stream << "String(" << attr.getValue<String>() << ")";
            break;
    }
    return stream;
}