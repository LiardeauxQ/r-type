/*
** EPITECH PROJECT, 2019
** Ship.hpp
** File description:
** Ship header
*/

#ifndef SHIP_HPP
	#define SHIP_HPP

#include "entities/Bullet.hpp"
#include <SFML/System/Clock.hpp>
#include <vector>

class Ship : public Entity {
    public:
        Ship();
        Ship(const sf::Texture *texture);
        ~Ship() = default;
        void setTexture(const sf::Texture *texture);
        void shot(std::vector<Bullet> &bullets);
    private:
        float m_fireRate;
        float m_cooldown;
        sf::Clock m_clock;
};

#endif /* !SHIP_HPP */
