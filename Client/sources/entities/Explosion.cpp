/*
** EPITECH PROJECT, 2019
** Explosion.cpp
** File description:
** Explosion implementation
*/

#include "entities/Explosion.hpp"

Explosion::Explosion()
    : Entity()
    , m_frames()
    , m_currentFrame(0)
    , m_cooldown(0.5)
    , m_clock()
    , m_isFinished(false)
{
    m_frames.push_back(sf::IntRect(72, 296, 32, 30));
    m_frames.push_back(sf::IntRect(108, 296, 33, 30));
    m_frames.push_back(sf::IntRect(146, 296, 32, 30));
    m_frames.push_back(sf::IntRect(183, 296, 32, 30));
    m_frames.push_back(sf::IntRect(218, 296, 27, 30));
    m_frames.push_back(sf::IntRect(248, 296, 18, 30));
}

Explosion::Explosion(const sf::Texture *texture)
    : Entity()
    , m_frames()
    , m_currentFrame(0)
    , m_cooldown(0.5)
    , m_clock()
    , m_isFinished(false)
{
    m_frames.push_back(sf::IntRect(72, 296, 32, 30));
    m_frames.push_back(sf::IntRect(108, 296, 33, 30));
    m_frames.push_back(sf::IntRect(146, 296, 32, 30));
    m_frames.push_back(sf::IntRect(183, 296, 32, 30));
    m_frames.push_back(sf::IntRect(218, 296, 27, 30));
    m_frames.push_back(sf::IntRect(248, 296, 18, 30));
    m_sprite.setTextureRect(m_frames[0]);
    m_sprite.setOrigin(m_frames[0].width/2, m_frames[0].height/2);
    m_sprite.setScale(2, 2);
}

void Explosion::setTexture(const sf::Texture *texture)
{
    m_sprite.setTexture(*texture);
    m_sprite.setTextureRect(m_frames[0]);
    m_sprite.setOrigin(m_frames[0].width/2, m_frames[0].height/2);
    m_sprite.setScale(2, 2);
}

void Explosion::update()
{
    m_cooldown -= m_clock.getElapsedTime().asSeconds();
    m_clock.restart();
    if (m_cooldown > 0)
        return;
    m_cooldown = 0.5;
    this->setNextFrame();
}

void Explosion::setNextFrame()
{
    if (m_currentFrame + 1 < m_frames.size()) {
        m_sprite.setTextureRect(m_frames[++m_currentFrame]);
        m_sprite.setOrigin(m_frames[m_currentFrame].width/2, m_frames[m_currentFrame].height/2);
    } else
        m_isFinished = true;
}
