//
// Created by Quentin Liardeaux on 12/29/19.
//

#ifndef R_TYPE_ENTITY_HPP
#define R_TYPE_ENTITY_HPP

#include <cstdlib>

#include "protocol.hpp"
#include "Position.hpp"

class Entity {
public:
    Entity(size_t id, Position position, Position velocity)
    : m_id(id)
    , m_position(position)
    , m_velocity(velocity) {}

    virtual ~Entity() = default;

    Entity(const Entity& other) = default;
    Entity &operator=(const Entity& other) = default;

    void move(Direction dir, float elapsedTime);

    [[nodiscard]] size_t getId() const { return m_id; }
    [[nodiscard]] const Position& getPosition() const { return m_position; }
    [[nodiscard]] const Position& getVelocity() const { return m_velocity; }
protected:
    size_t m_id;
    Position m_position;
    Position m_velocity;
};

#endif //R_TYPE_ENTITY_HPP
