//
// Created by Quentin Liardeaux on 12/29/19.
//

#include "Entity.hpp"

void Entity::move(Direction dir, float elapsedTime) {
    switch (dir) {
        case RIGHT:
            m_position.m_x += m_velocity.m_x * elapsedTime;
            break;
        case LEFT:
            m_position.m_x -= m_velocity.m_x * elapsedTime;
            break;
        case TOP:
            m_position.m_y += m_velocity.m_y * elapsedTime;
            break;
        case BOTTOM:
            m_position.m_y -= m_velocity.m_y * elapsedTime;
            break;
        default:
            break;
    }
}