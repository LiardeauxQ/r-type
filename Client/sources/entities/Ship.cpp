/*
** EPITECH PROJECT, 2019
** Ship.cpp
** File description:
** Ship implementation
*/

#include "entities/Ship.hpp"

Ship::Ship(): Entity() {}

Ship::Ship(const sf::Texture *texture): Entity(texture)
{
    m_sprite.setTextureRect(sf::IntRect(101, 0, 33, 17));
    m_sprite.setScale(2, 2);
}

void Ship::setTexture(const sf::Texture *texture)
{
    m_sprite.setTexture(*texture);
    m_sprite.setTextureRect(sf::IntRect(101, 0, 33, 17));
    m_sprite.setScale(2, 2);
}

Bullet Ship::shot()
{
    Bullet bullet(this->m_sprite.getTexture());

    bullet.setPosition(m_position + sf::Vector2f(17.0, 17.0 / 2));
    return bullet;
}
