/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Main file.
*/

#ifndef VERSION
#define VERSION "NOT DEFINED"
#endif

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

namespace animation {

    enum AnimationType {
        LOOP,
        TRIGO
    };

    class Animation {

    public:
        Animation(const sf::Texture &text, sf::Vector2f size, int interval = 0, AnimationType type = AnimationType::LOOP, sf::Vector2u limit = sf::Vector2u(-1, -1))
        : m_type(type)
        , m_interval(interval)
        , m_sprite()
        , backward(false)
        {
            m_sprite.setTexture(text);
            m_sprite.setScale({4, 4});

            auto tempSize = limit.x == -1 ? text.getSize() : limit;
            for (int i = 0; i + size.y <= tempSize.y; i += size.y) {
                for (int j = 0; j + size.x <= tempSize.x; j += size.x) {
                    rects.push_back(sf::IntRect{j, i, size.x, size.y});
                }
            }
            it = rects.begin();
        }

        sf::Sprite &animate(sf::Time time) {
            elapsed += time.asMicroseconds();
            m_sprite.setTextureRect(*it);
            if (elapsed > m_interval) {
                it += AnimationType::LOOP ? 1 : (backward ? -1 : 1);
                elapsed = m_interval - elapsed;
            }
            if (it == rects.end()) {
                it = m_type == AnimationType::LOOP ? rects.begin() : rects.end() - 1;
                backward = m_type == AnimationType::LOOP ? false : true;
            }
            if (AnimationType::TRIGO && backward && it == rects.begin()) {
                backward = false;
            }
            return m_sprite;
        }

        void setPosition(const sf::Vector2f& pos)
        {
            m_sprite.setPosition(pos);
        }

        sf::Vector2f getPosition() const {
            return m_sprite.getPosition();
        }

        sf::FloatRect getBoundingBox() const {
            return m_sprite.getGlobalBounds();
        }

    private:
        AnimationType m_type;
        int m_interval;
        sf::Sprite m_sprite;

        std::vector<sf::IntRect> rects;
        std::vector<sf::IntRect>::iterator it;
        bool backward;
        int elapsed;

    };


    class Projectile {
        public:
            Projectile(const sf::Texture &text, sf::Vector2f initialPos) 
            : m_sprite()
            {
                m_sprite.setTexture(text);
                m_sprite.setPosition(initialPos);
                m_sprite.setTextureRect({104, 170, 80, 15});

            }

            sf::Sprite &animate(sf::Time time) {
                auto oldPos = m_sprite.getPosition();
                oldPos.x += time.asMilliseconds();
                m_sprite.setPosition(oldPos);
                return m_sprite;
            }

            sf::FloatRect getBoundingBox() const {
                return m_sprite.getGlobalBounds();
            }
        
        private:
            sf::Sprite m_sprite;
    };

    class Enemy {

    public:
        Enemy(const sf::Texture &text, const sf::RenderWindow& window, sf::Vector2f size, int interval = 0, AnimationType type = AnimationType::LOOP, sf::Vector2u limit = sf::Vector2u(-1, -1))
        : m_type(type)
        , m_interval(interval)
        , m_sprite()
        , backward(false)
        {
            m_sprite.setTexture(text);
            m_sprite.setScale({4, 4});
            auto windowSize = window.getSize();

            m_sprite.setPosition({windowSize.x, 0});

            auto tempSize = limit.x == -1 ? text.getSize() : limit;
            for (int i = 0; i + size.y <= tempSize.y; i += size.y) {
                for (int j = 0; j + size.x <= tempSize.x; j += size.x) {
                    rects.push_back(sf::IntRect{j, i, size.x, size.y});
                }
            }
            it = rects.begin();
        }

        sf::Sprite &animate(sf::Time time) {
            auto oldPos = m_sprite.getPosition();
            oldPos.x -= (((double) time.asMilliseconds()) / 1000) * 100;
            oldPos.y -= (((double) time.asMilliseconds()) / 1000) * 0;
            m_sprite.setPosition(oldPos);
            elapsed += time.asMicroseconds();
            m_sprite.setTextureRect(*it);
            if (elapsed > m_interval) {
                it += AnimationType::LOOP ? 1 : (backward ? -1 : 1);
                elapsed = m_interval - elapsed;
            }
            if (it == rects.end()) {
                it = m_type == AnimationType::LOOP ? rects.begin() : rects.end() - 1;
                backward = m_type == AnimationType::LOOP ? false : true;
            }
            if (AnimationType::TRIGO && backward && it == rects.begin()) {
                backward = false;
            }
            return m_sprite;
        }

        void setPosition(const sf::Vector2f& pos)
        {
            m_sprite.setPosition(pos);
        }

        sf::Vector2f getPosition() const {
            return m_sprite.getPosition();
        }

        sf::FloatRect getBoundingBox() const {
            return m_sprite.getGlobalBounds();
        }

    private:
        AnimationType m_type;
        int m_interval;
        sf::Sprite m_sprite;

        std::vector<sf::IntRect> rects;
        std::vector<sf::IntRect>::iterator it;
        bool backward;
        int elapsed;

    };


}


int main(int argc, char* argv[])
{
    srand((int)time(0));
    sf::VideoMode mode(1280, 720, 32);
    sf::RenderWindow window(mode, "PUTAIN");
    sf::Clock clock;
    sf::Text highscore;
    sf::Font font;
    int score = 0;
    int respawn_time = 4000000;
    int elapsed = respawn_time;

    font.loadFromFile("Client/assets/Roboto-Bold.ttf");
    highscore.setFont(font);
    highscore.setPosition({10, 10});
    sf::Texture spaceshipText;
    spaceshipText.loadFromFile("Client/assets/r-typesheet42.gif");
    sf::Texture projectileText;
    projectileText.loadFromFile("Client/assets/r-typesheet1.gif");
    sf::Texture enemyText;
    enemyText.loadFromFile("Client/assets/r-typesheet11.gif");

    std::vector<animation::Projectile> projectiles;
    std::vector<animation::Enemy> enemies;
    sf::Texture text;
    sf::Sprite sprite;

    text.loadFromFile("Client/assets/stars.png");

    sprite.setTexture(text);
    auto ship1 = animation::Animation(spaceshipText, sf::Vector2f(33, 17), 400000, animation::AnimationType::TRIGO, sf::Vector2u(166, 17));
    int ship1Cooldown = 0;
    sf::Vector2f pos1(20, (window.getSize().y / 4));
    auto ship2 = animation::Animation(spaceshipText, sf::Vector2f(33, 17), 400000, animation::AnimationType::TRIGO, sf::Vector2u(166, 17));
    int ship2Cooldown = 0;
    sf::Vector2f pos2(20, (window.getSize().y / 4) * 3);
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            pos1.y -= pos1.y <= 0 ? 0 : 4;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            pos1.y += pos1.y >= window.getSize().y ? 0 : 4;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            pos1.x -= pos1.x <= 0 ? 0 : 4;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            pos1.x += pos1.x >= window.getSize().x ? 0 : 4;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pos2.y -= pos2.y <= 0 ? 0 : 4;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pos2.y += pos2.y >= window.getSize().y ? 0 : 4;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            pos2.x -= pos2.x <= 0 ? 0 : 4;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            pos2.x += pos2.x >= window.getSize().x ? 0 : 4;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            if (!ship1Cooldown) {
                projectiles.push_back(std::move(animation::Projectile(projectileText, ship1.getPosition())));
                ship1Cooldown = 500000;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            if (!ship2Cooldown) {
                projectiles.push_back(std::move(animation::Projectile(projectileText, ship2.getPosition())));
                ship2Cooldown = 500000;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        ship1.setPosition(pos1);
        ship2.setPosition(pos2);
        window.clear();
        window.draw(sprite);
        window.draw(ship1.animate(clock.getElapsedTime()));
        window.draw(ship2.animate(clock.getElapsedTime()));
        elapsed -= clock.getElapsedTime().asMicroseconds();
        ship1Cooldown = ship1Cooldown - clock.getElapsedTime().asMicroseconds() < 0 ? 0 : ship1Cooldown - clock.getElapsedTime().asMicroseconds();
        ship2Cooldown = ship2Cooldown - clock.getElapsedTime().asMicroseconds() < 0 ? 0 : ship2Cooldown - clock.getElapsedTime().asMicroseconds();
        if (elapsed < 0) {
            elapsed += respawn_time;
            enemies.push_back(std::move(animation::Enemy(enemyText, window, sf::Vector2f(33, 34), 400000, animation::AnimationType::TRIGO, sf::Vector2u(100, 34))));
            enemies.back().setPosition({window.getSize().x - (rand() % 100), rand() % window.getSize().y});
            respawn_time -= 10000;
        }
        for (auto it = projectiles.begin(); it != projectiles.end();) {
            auto hasTouched = false;
            for (auto it2 = enemies.begin(); it2 != enemies.end();) {
                if ((*it2).getBoundingBox().intersects((*it).getBoundingBox())) {
                    enemies.erase(it2, it2 + 1);
                    projectiles.erase(it, it + 1);
                    hasTouched = true;
                    score += 10;
                } else {
                    ++it2;
                }
            }
            if (!hasTouched)
                ++it;
        }
        for (auto& projectile : projectiles) {
            window.draw(projectile.animate(clock.getElapsedTime()));
        }
        for (auto& enemy : enemies) {
            window.draw(enemy.animate(clock.getElapsedTime()));
            if (enemy.getPosition().x < 0 || enemy.getBoundingBox().intersects(ship1.getBoundingBox()) || enemy.getBoundingBox().intersects(ship2.getBoundingBox())) {
                window.close();
            }
        }
        highscore.setString("Score: " + std::to_string(score));
        window.draw(highscore);
        clock.restart();
        window.display();
    }
    return 0;
}