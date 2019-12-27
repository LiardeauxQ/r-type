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

enum ShotPatern {
    SINGLE,
    DOUBLE,
    TRIPLE
};

class Ship : public Entity {
    public:
        Ship();
        Ship(const sf::Texture *texture);
        ~Ship() = default;
        void setTexture(const sf::Texture *texture);
        void shot(std::vector<Bullet> &bullets);
        void setShotPatern(const ShotPatern &patern) { m_patern = patern; };
    private:
        void singleShot(std::vector<Bullet> &bullets);
        void doubleShot(std::vector<Bullet> &bullets);
        void tripleShot(std::vector<Bullet> &bullets);
        ShotPatern m_patern;
        float m_fireRate;
        float m_cooldown;
        sf::Clock m_clock;
};

#endif /* !SHIP_HPP */
