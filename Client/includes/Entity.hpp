/*
** EPITECH PROJECT, 2019
** Entity.hpp
** File description:
** Entity header
*/

#ifndef ENTITY_HPP
	#define ENTITY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class Entity : public sf::Drawable, public sf::Transformable {
    public:
        Entity();
        Entity(const sf::Texture *texture);
        ~Entity() = default;
        void setTexture(const sf::Texture *texture);
        void move(const sf::Vector2f &offset);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const final;
        sf::Vector2f m_position;
    protected:
        sf::Sprite m_sprite;
};

#endif /* !ENTITY_HPP */
