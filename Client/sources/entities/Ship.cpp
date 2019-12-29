/*
** EPITECH PROJECT, 2019
** Ship.cpp
** File description:
** Ship implementation
*/

#include "entities/Ship.hpp"

Ship::Ship()
    : Entity()
    , m_patern(ShotPatern::SINGLE)
    , m_fireRate(0.3f)
    , m_cooldown(0.0)
    , m_clock()
{}

Ship::Ship(const sf::Texture *texture)
    : Entity(texture)
    , m_patern(ShotPatern::SINGLE)
    , m_fireRate(0.3f)
    , m_cooldown(0.0)
    , m_clock()
{
    m_sprite.setTextureRect(sf::IntRect(101, 0, 33, 17));
    m_sprite.setOrigin(33/2, 17/2);
    m_sprite.setScale(2, 2);
}

void Ship::setTexture(const sf::Texture *texture)
{
    m_sprite.setTexture(*texture);
    m_sprite.setTextureRect(sf::IntRect(101, 0, 33, 17));
    m_sprite.setOrigin(33/2, 17/2);
    m_sprite.setScale(2, 2);
}

bool Ship::isShotReady()
{
    m_cooldown -= m_clock.getElapsedTime().asSeconds();
    m_clock.restart();
    if (m_cooldown > 0)
        return false;
    m_cooldown = m_fireRate;
    return true;
}

void Ship::shot(std::vector<Bullet> &bullets)
{
    m_cooldown -= m_clock.getElapsedTime().asSeconds();
    m_clock.restart();
    if (m_cooldown > 0)
        return;
    m_cooldown = m_fireRate;
    switch (m_patern) {
        case ShotPatern::SINGLE:
            this->singleShot(bullets);
            break;
        case ShotPatern::DOUBLE:
            this->doubleShot(bullets);
            break;
        case ShotPatern::TRIPLE:
            this->tripleShot(bullets);
            break;
        default:
            break;
    }
}

void Ship::singleShot(std::vector<Bullet> &bullets)
{
    Bullet bullet(this->m_sprite.getTexture());
    bullet.setPosition(m_position + sf::Vector2f(9, 3));
    bullet.setMovement(400, 0);
    bullets.push_back(bullet);
}

void Ship::doubleShot(std::vector<Bullet> &bullets)
{
    Bullet bullet1(this->m_sprite.getTexture());
    bullet1.setPosition(m_position + sf::Vector2f(9, 3 + -17 / 2));
    bullet1.setMovement(400, 0);
    bullets.push_back(bullet1);

    Bullet bullet2(this->m_sprite.getTexture());
    bullet2.setPosition(m_position + sf::Vector2f(9, 3 + 17 / 2));
    bullet2.setMovement(400, 0);
    bullets.push_back(bullet2);
}

void Ship::tripleShot(std::vector<Bullet> &bullets)
{
    Bullet bullet1(this->m_sprite.getTexture());
    bullet1.setPosition(m_position + sf::Vector2f(9, 3));
    bullet1.setMovement(400, 0);
    bullets.push_back(bullet1);

    Bullet bullet2(this->m_sprite.getTexture());
    bullet2.setPosition(m_position + sf::Vector2f(9, 3));
    bullet2.setMovement(400, -100);
    bullets.push_back(bullet2);

    Bullet bullet3(this->m_sprite.getTexture());
    bullet3.setPosition(m_position + sf::Vector2f(9, 3));
    bullet3.setMovement(400, 100);
    bullets.push_back(bullet3);
}
