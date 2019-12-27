/*
** EPITECH PROJECT, 2019
** Enemy.hpp
** File description:
** Enemy header
*/

#ifndef ENEMY_HPP
	#define ENEMY_HPP

#include "Entity.hpp"

class Enemy : public Entity {
    public:
        Enemy();
        Enemy(const sf::Texture *texture);
        ~Enemy() = default;
        void setTexture(const sf::Texture *texture);
};

#endif /* !ENEMY_HPP */
