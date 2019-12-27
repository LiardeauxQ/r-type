/*
** EPITECH PROJECT, 2019
** EntityBuilder.hpp
** File description:
** EntityBuilder header
*/

#ifndef ENTITYBUILDER_HPP
	#define ENTITYBUILDER_HPP

#include "entities/Ship.hpp"
#include "entities/Enemy.hpp"
#include "TextureBuilder.hpp"

enum EntityType {
    SHIP,
    ENEMY
};

class EntityBuilder {
    public:
        EntityBuilder();
        ~EntityBuilder() = default;
        Entity *create(const EntityType &type);
    private:
        Ship *createShip();
        Enemy *createEnemy();
        void initializeTexture();
        TextureBuilder m_textureBuilder;
};

#endif /* !ENTITYBUILDER_HPP */
