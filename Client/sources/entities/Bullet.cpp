/*
** EPITECH PROJECT, 2019
** Bullet.cpp
** File description:
** Bullet implementation
*/

#include "entities/Bullet.hpp"
#include <cmath>

Bullet::Bullet(): Entity(), m_movement(0, 0) {}

Bullet::Bullet(const sf::Texture *texture): Entity(texture), m_movement(0, 0)
{
    m_sprite.setTextureRect(sf::IntRect(249, 85, 16, 12));
    m_sprite.setOrigin(16/2, 12/2);
    m_sprite.setScale(2, 2);
}

void Bullet::setTexture(const sf::Texture *texture)
{
    m_sprite.setTexture(*texture);
    m_sprite.setTextureRect(sf::IntRect(249, 85, 16, 12));
    m_sprite.setOrigin(16/2, 12/2);
    m_sprite.setScale(2, 2);
}

void Bullet::setMovement(const sf::Vector2f &movement)
{
    m_movement = movement;
    float angleInRadians = std::atan2(m_movement.y, m_movement.x);
    float angleInDegrees = static_cast<float>((static_cast<double>(angleInRadians) / M_PI) * 180.0);
    m_sprite.setRotation(angleInDegrees);
}

void Bullet::setMovement(const float &xMovement, const float &yMovement)
{
    m_movement = sf::Vector2f(xMovement, yMovement);
    float angleInRadians = std::atan2(m_movement.y, m_movement.x);
    float angleInDegrees = static_cast<float>((static_cast<double>(angleInRadians) / M_PI) * 180.0);
    m_sprite.setRotation(angleInDegrees);
}

void Bullet::update(const float &deltaTime)
{
    m_position += m_movement * deltaTime;
    m_sprite.setPosition(m_position);
}

bool Bullet::isOutOfMap()
{
    if (m_position.x <= -10 || m_position.x >= 1546)
        return true;
    if (m_position.y <= -10 || m_position.y >= 874)
        return true;
    return false;
}
