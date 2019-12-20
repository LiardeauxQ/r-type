/*
** EPITECH PROJECT, 2019
** Entity.cpp
** File description:
** Entity implementation
*/

#include <SFML/Graphics/Rect.hpp>
#include "Entity.hpp"

Entity::Entity(): m_position(0.0, 0.0), m_sprite() {}

Entity::Entity(const sf::Texture *texture): m_position(0.0, 0.0), m_sprite()
{
    m_sprite.setTexture(*texture);
}

void Entity::setTexture(const sf::Texture *texture)
{
    m_sprite.setTexture(*texture);
}

void Entity::setPosition(const sf::Vector2f &position)
{
    m_position = position;
    m_sprite.setPosition(m_position);
}

void Entity::move(const sf::Vector2f &offset)
{
    m_position += offset;
    m_sprite.setPosition(m_position);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}
