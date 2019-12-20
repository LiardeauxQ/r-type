/*
** EPITECH PROJECT, 2019
** Bullet.hpp
** File description:
** Bullet header
*/

#ifndef BULLET_HPP
	#define BULLET_HPP

#include "Entity.hpp"

class Bullet : public Entity {
    public:
        Bullet();
        Bullet(const sf::Texture *texture);
        ~Bullet() = default;
        void setTexture(const sf::Texture *texture);
};

#endif /* !BULLET_HPP */
