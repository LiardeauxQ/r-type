/*
** EPITECH PROJECT, 2019
** EntityBuilder.hpp
** File description:
** EntityBuilder header
*/

#ifndef ENTITYBUILDER_HPP
	#define ENTITYBUILDER_HPP

#include "protocol.hpp"
#include "entities/Ship.hpp"
#include "entities/Enemy.hpp"
#include "entities/Explosion.hpp"
#include "TextureBuilder.hpp"

class EntityBuilder {
    public:
        EntityBuilder();
        ~EntityBuilder() = default;
        Entity *create(const EntityType &type);
    private:
        Ship *createShip();
        Enemy *createEnemy();
        Bullet *createBullet();
        Explosion *createExplosion();
        void initializeTexture();
        TextureBuilder m_textureBuilder;
};

#endif /* !ENTITYBUILDER_HPP */
