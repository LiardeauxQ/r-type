/*
** EPITECH PROJECT, 2019
** Game.hpp
** File description:
** Game header
*/

#include <SFML/Graphics.hpp>
#include "TextureBuilder.hpp"
#include "StateBuilder.hpp"
#include "StateStack.hpp"

#ifndef GAME_HPP
	#define GAME_HPP

    #define WINDOW_NAME "test"
    #define WINDOW_WIDTH 1536
    #define WINDOW_HEIGHT 864

class Game {
    public:
        Game();
        ~Game();
        void run();
    private:
        void handleTransition(Transition transition);
        void loop();
        TextureBuilder m_textureBuilder;
        StateBuilder m_stateBuilder;
        StateStack m_states;
        bool m_isRunning;
        sf::RenderWindow *m_window;
        sf::Event m_event;
        float m_deltaTime;
};

#endif /* !GAME_HPP */
