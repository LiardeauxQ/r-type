/*
** EPITECH PROJECT, 2019
** Ship.hpp
** File description:
** Ship header
*/

#ifndef SHIP_HPP
	#define SHIP_HPP

#include "entities/Bullet.hpp"

class Ship : public Entity {
    public:
        Ship();
        Ship(const sf::Texture *texture);
        ~Ship() = default;
        void setTexture(const sf::Texture *texture);
        Bullet shot();
};

#endif /* !SHIP_HPP */
