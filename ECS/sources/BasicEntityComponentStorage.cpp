//
// Created by nwmqpa on 11/25/19
//

#include "BasicEntityComponentStorage.hpp"
#include <algorithm>
#include <iostream>
#include <tuple>

namespace ecs {

BasicEntityComponentStorage::BasicEntityComponentStorage()
    : m_schemas()
    , m_components()
{
}

bool BasicEntityComponentStorage::hasSchema(const String& name) const
{
    for (const auto& m_schema : m_schemas) {
        if (m_schema.m_name == name) {
            return true;
        }
    }
    return false;
}

void BasicEntityComponentStorage::addComponentSchema(ComponentSchema schema)
{
    if (hasSchema(schema.m_name))
        throw SchemaNameAlreadyExistsException();
    m_components[schema.m_name] = Map<String, Component>();
    m_schemas.push_back(move(schema));
}

void BasicEntityComponentStorage::removeComponentSchema(const String& name)
{
    for (auto it = m_schemas.begin(); it != m_schemas.end(); it++) {
        if (it->m_name == name) {
            m_schemas.erase(it, it + 1);
            break;
        }
    }
}

Vec<Entity> BasicEntityComponentStorage::request(EntityRequest request)
{
    auto componentList = request.getWiths();
    auto newComponentList = std::vector<std::tuple<String, int>>();
    auto entityNameList = Vec<String>();
    auto entityList = Vec<Entity>();

    std::transform(componentList.begin(), componentList.end(), std::back_inserter(newComponentList), [this](const String& componentName) -> std::tuple<String, size_t> {
        return std::make_tuple<String, size_t>(String(componentName), this->getComponents(componentName).size());
    });
    std::sort(newComponentList.begin(), newComponentList.end(), [](auto component1, auto component2) {
        return std::get<1>(component1) < std::get<1>(component2);
    });
    auto it = newComponentList.begin();
    std::transform(
        m_components.at(std::get<0>(*it)).begin(),
        m_components.at(std::get<0>(*it)).end(),
        std::back_inserter(entityNameList),
        [this](auto tuple) {
            return std::get<0>(tuple);
        });
    for (auto& componentName : newComponentList) {
        auto comp = m_components.at(std::get<0>(componentName));
        auto entityNameListTemp = Vec<String>();
        std::copy_if(
            entityNameList.begin(),
            entityNameList.end(),
            std::back_inserter(entityNameListTemp),
            [comp](const String& name) {
                return comp.find(name) != comp.end();
            });
        entityNameList = entityNameListTemp;
    }
    std::transform(
        entityNameList.begin(),
        entityNameList.end(),
        std::back_inserter(entityList),
        [this, componentList](String entityName) {
            auto builder = EntityBuilder();
            for (auto& componentName : componentList) {
                builder.with(this->getComponents(componentName).find(entityName)->second);
            }
            auto entity = builder.build(entityName);
            entity.markNonDirty();
            return entity;
        });
    return entityList;
}

void BasicEntityComponentStorage::store(const Vec<Entity>& entities)
{
    for (const auto& entity : entities) {
        if (entity.isDirty()) {
            std::cout << "Stored:" << entity.getComponents().at("Position") << std::endl;
            for (auto component : entity.getComponents()) {
                if (!hasSchema(component.first))
                    throw SchemaNotFound();
                if (!component.second.complyWith(getSchema(component.first))) {
                    throw ComponentDoesNotComplyWithSchema();
                }
                m_components.at(component.first)[entity.getName()] = component.second;
            }
        }
    }
}

const ComponentSchema& BasicEntityComponentStorage::getSchema(const String& name) const
{
    for (const auto &m_schema : m_schemas) {
        if (m_schema.m_name == name) {
            return m_schema;
        }
    }
    throw SchemaNotFound();
}

Map<String, Component> BasicEntityComponentStorage::getComponents(const String& name) const
{
    if (hasSchema(name))
        return m_components.at(name);
    throw SchemaNotFound();
}

}

std::ostream& operator<<(std::ostream& stream, const ecs::BasicEntityComponentStorage& components)
{
    for (const auto& schema : components.m_schemas) {
        stream << schema.m_name << ":" << std::endl;
        for (const auto& map : components.getComponents(schema.m_name)) {
            stream << "\t" << map.first << ": " << map.second << std::endl;
        }
        stream << std::endl;
    }
    return stream;
}