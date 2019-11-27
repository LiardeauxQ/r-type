//
// Created by nwmqpa on 11/11/19
//

#include <iostream>
#include <utility>
#include "Component.hpp"

namespace ecs {

    ComponentAttribute::ComponentAttribute(String name, AttributeType type, std::any value)
        : m_name(move(name))
        , m_type(type)
        , m_value(move(value))
    {}

    Component::Component()
        : m_name()
        , m_attributes()
    {}


    ComponentSchema& ComponentSchema::operator=(ComponentSchema&& rhs) noexcept
    {
        m_name.swap(rhs.m_name);
        m_attributesSchema.swap(rhs.m_attributesSchema);
        return *this;
    }

    Component::Component(String name)
        : m_name(move(name))
        , m_attributes()
    {}

    Vec<ComponentAttribute> Component::getAttributes() const {
        auto attributes = Vec<ComponentAttribute>();
        for (const auto& attribute : m_attributes) {
            attributes.push_back(attribute.second);
        }
        return attributes;
    }



    void Component::addAttribute(ComponentAttribute attribute) {
        m_attributes.insert({ attribute.m_name, move(attribute) });
    }

    void Component::removeAttribute(const String& name) {
        m_attributes.erase(name);
    }

    String Component::getName() const {
        return m_name;
    }

    bool Component::complyWith(const ComponentSchema &schema) const {
        if (m_attributes.size() == schema.m_attributesSchema.size()) {
            for (const auto& attribute : schema.m_attributesSchema) {
                auto tempAttribute = m_attributes.find(attribute.m_name);
                if (tempAttribute == m_attributes.end() || !tempAttribute->second.complyWith(attribute))
                    return false;
            }
        }
        return true;
    }
    
    ComponentAttribute &Component::getAttribute(String name) {
        return m_attributes.at(name);
    }

    bool ComponentAttribute::complyWith(const ComponentAttributeSchema& schema) const {
        return m_type == schema.m_type;
    }
    
    ComponentAttributeSchema::ComponentAttributeSchema(String name, AttributeType type)
        : m_name(move(name))
        , m_type(type)
    {}

    ComponentSchema::ComponentSchema(String name, Vec<ComponentAttributeSchema> attributesSchema)
        : m_name(move(name))
        , m_attributesSchema(move(attributesSchema))
    {}

    ComponentSchema::ComponentSchema(ComponentSchema&& rhs) noexcept
        : m_name(move(rhs.m_name))
        , m_attributesSchema(move(rhs.m_attributesSchema))
    {
    }

    ComponentSchemaBuilder::ComponentSchemaBuilder(String name)
        : m_name(move(name))
    {}

    ComponentSchemaBuilder ComponentSchemaBuilder::with(ComponentAttributeSchema attributeSchema) {
        m_attributesSchema.push_back(move(attributeSchema));
        return *this;
    }

    ComponentSchema ComponentSchemaBuilder::build() {
        return ComponentSchema(m_name, m_attributesSchema);
    }

}

std::ostream &operator<<(std::ostream &stream, const ecs::Component &comp) {
    stream << "{ ";
    for (const auto& attribute : comp.getAttributes()) {
        stream << attribute << ", ";
    }
    stream << " }";
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const ecs::ComponentAttribute &attr) {
    stream << attr.m_name << ": ";
    switch (attr.m_type) {
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