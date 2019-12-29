/*
** EPITECH PROJECT, 2019
** EntityBuilder.cpp
** File description:
** EntityBuilder implementation
*/

#include "EntityBuilder.hpp"

EntityBuilder::EntityBuilder()
    : m_textureBuilder()
{
    this->initializeTexture();
}

Entity *EntityBuilder::create(const EntityType &type)
{
    switch (type) {
        case EntityType::SHIP:
            return this->createShip();
        case EntityType::ENEMY:
            return this->createEnemy();
        case EntityType::BULLET:
            return this->createBullet();
        case EntityType::EXPLOSION:
            return this->createExplosion();
        default:
            return nullptr;
    }
}

Ship *EntityBuilder::createShip()
{
    return new Ship(m_textureBuilder.getTexture("SHIP"));
}

Enemy *EntityBuilder::createEnemy()
{
    return new Enemy(m_textureBuilder.getTexture("ENEMY"));
}

Bullet *EntityBuilder::createBullet()
{
    return new Bullet(m_textureBuilder.getTexture("SHIP"));
}

Explosion *EntityBuilder::createExplosion()
{
    return new Explosion(m_textureBuilder.getTexture("SHIP"));
}

void EntityBuilder::initializeTexture()
{
    m_textureBuilder.createTexture("../Client/assets/r-typesheet1.gif", "SHIP");
    m_textureBuilder.createTexture("../Client/assets/r-typesheet5.gif", "ENEMY");
}
