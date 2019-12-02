//
// Created by nwmqpa on 11/11/19
//

#pragma once

#include "Definitions.hpp"
#include <any>

namespace ecs {

using namespace std;

enum AttributeType {
    BOOL = 0,
    INT = 1,
    FLOAT = 2,
    STRING = 3
};

/// TODO: Implements Serialize/Deserialize
struct ComponentAttributeSchema {

    ComponentAttributeSchema(String name, AttributeType type);

    String m_name;
    AttributeType m_type;
};

/// TODO: Implements Serialize/Deserialize
struct ComponentSchema {

    ComponentSchema(String name, Vec<ComponentAttributeSchema> attributesSchema);
    ComponentSchema(ComponentSchema&& schema) noexcept;
    ComponentSchema& operator=(ComponentSchema&& rhs) noexcept;

    Vec<ComponentAttributeSchema> m_attributesSchema;
    String m_name;
};

/// TODO: Implements Serialize/Deserialize
struct ComponentAttribute {

    ComponentAttribute(String name, AttributeType type, std::any value);

    [[nodiscard]] bool complyWith(const ComponentAttributeSchema& schema) const;

    template<typename T>
    const T& getValue() const
    {
        return any_cast<const T&>(m_value);
    }

    std::any m_value;
    String m_name;
    AttributeType m_type;
};

/// TODO: Implements Serialize/Deserialize
class Component {

public:
    Component();
    Component(String name);

    void addAttribute(ComponentAttribute attribute);
    void removeAttribute(const String& name);
    ComponentAttribute& getAttribute(String name);
    Vec<ComponentAttribute> getAttributes() const;
    String getName() const;
    bool complyWith(const ComponentSchema& schema) const;

private:
    String m_name;
    HashMap<String, ComponentAttribute> m_attributes;
};

/// auto componentSchema = ComponentSchemaBuilder("Position")
///                             .with(ComponentSchema("X"), AttributeType::INT)
///   String              .with(ComponentSchema("Y"), AttributeType::INT)
///                             .with(ComponentSchema("X"), AttributeType::INT)
///                             .build()
class ComponentSchemaBuilder {

public:
    ComponentSchemaBuilder(String name);
    ComponentSchemaBuilder with(ComponentAttributeSchema attributeSchema);
    ComponentSchema build();

private:
    String m_name;
    Vec<ComponentAttributeSchema> m_attributesSchema;
};

}

std::ostream& operator<<(std::ostream& stream, const ecs::Component& comp);
std::ostream& operator<<(std::ostream& stream, const ecs::ComponentAttribute& attr);