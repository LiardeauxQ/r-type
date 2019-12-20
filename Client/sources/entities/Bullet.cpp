/*
** EPITECH PROJECT, 2019
** Bullet.cpp
** File description:
** Bullet implementation
*/

#include "entities/Bullet.hpp"

Bullet::Bullet(): Entity() {}

Bullet::Bullet(const sf::Texture *texture): Entity(texture)
{
    m_sprite.setTextureRect(sf::IntRect(249, 85, 16, 12));
    m_sprite.setScale(2, 2);
}

void Bullet::setTexture(const sf::Texture *texture)
{
    m_sprite.setTexture(*texture);
    m_sprite.setTextureRect(sf::IntRect(249, 85, 16, 12));
    m_sprite.setScale(2, 2);
}
