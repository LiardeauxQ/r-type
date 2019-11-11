//
// Created by nwmqpa on 11/11/19
//

#pragma once

#include <any>
#include "Definitions.hpp"

namespace ecs {

    enum AttributeType {
        BOOL = 0,
        INT = 1,
        FLOAT = 2,
        STRING = 3
    };

    /// TODO: Implements Serialize/Deserialize
    class ComponentAttribute {

        public:
            ComponentAttribute(const String &name, const AttributeType type, std::any value);

            template<typename T>
            T getValue() const { return std::any_cast<T>(m_value); }

            template<typename T>
            void setValue(T value) {
                m_value = value;
            }

            String getName() const { return m_name; }

        private:
            String m_name;
            AttributeType m_type;
            std::any m_value;

    };

    /// TODO: Implements Serialize/Deserialize
    class Component {

        public:
            Component(const String &name);

            void addAttribute(ComponentAttribute &attribute);
            void removeAttribute(String name);
            ComponentAttribute &getAttribute(String name);
            String getName() const;

        private:
            String m_name;
            HashMap<String, ComponentAttribute> m_attributes;

    };

    /// TODO: Implements Serialize/Deserialize
    class ComponentAttributeSchema {

        public:
            ComponentAttributeSchema(const String &name, AttributeType &type);

        private:
            String m_name;
            AttributeType m_type;

    };

    /// TODO: Implements Serialize/Deserialize
    class ComponentSchema {

        public:
            ComponentSchema(const String &name, Vec<ComponentAttributeSchema> &attributesSchema);

        private:
            String m_name;
            Vec<ComponentAttributeSchema> m_attributesSchema;

    };

    /// auto componentSchema = ComponentSchemaBuilder("Position")
    ///                             .with(ComponentSchema("X"), AttributeType::INT)
    ///                             .with(ComponentSchema("Y"), AttributeType::INT)
    ///                             .with(ComponentSchema("X"), AttributeType::INT)
    ///                             .build()
    class ComponentSchemaBuilder {

        public:
            ComponentSchemaBuilder(const String &name);
            ComponentSchemaBuilder with(ComponentAttributeSchema &attributeSchema);
            ComponentSchema build();

        private:
            String m_name;
            Vec<ComponentAttributeSchema> m_attributesSchema;
    };

}