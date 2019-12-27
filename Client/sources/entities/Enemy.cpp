/*
** EPITECH PROJECT, 2019
** Enemy.cpp
** File description:
** Enemy implementation
*/

#include  "entities/Enemy.hpp"

Enemy::Enemy()
    : Entity()
{}

Enemy::Enemy(const sf::Texture *texture)
    : Entity(texture)
{
    m_sprite.setTextureRect(sf::IntRect(5, 0, 21, 36));
    m_sprite.setOrigin(21/2, 36/2);
    m_sprite.setScale(2, 2);
}

void Enemy::setTexture(const sf::Texture *texture)
{
    m_sprite.setTexture(*texture);
    m_sprite.setTextureRect(sf::IntRect(5, 0, 21, 36));
    m_sprite.setOrigin(21/2, 36/2);
    m_sprite.setScale(2, 2);
}
