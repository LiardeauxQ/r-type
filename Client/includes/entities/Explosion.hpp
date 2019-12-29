/*
** EPITECH PROJECT, 2019
** Explosion.hpp
** File description:
** Explosion header
*/

#ifndef EXPLOSION_HPP
	#define EXPLOSION_HPP

#include <SFML/System/Clock.hpp>
#include <vector>
#include "Entity.hpp"

class Explosion : public Entity {
    public:
        Explosion();
        Explosion(const sf::Texture *texture);
        ~Explosion() = default;
        void setTexture(const sf::Texture *texture);
        void update();
        bool isAnimationFinished() const { return m_isFinished; };
    private:
        void setNextFrame();
        std::vector<sf::IntRect> m_frames;
        size_t m_currentFrame;
        float m_cooldown;
        sf::Clock m_clock;
        bool m_isFinished;
};

#endif /* !EXPLOSION_HPP */
