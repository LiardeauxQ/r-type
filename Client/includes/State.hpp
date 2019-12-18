/*
** EPITECH PROJECT, 2019
** State.hpp
** File description:
** State header
*/

#ifndef STATE_HPP
	#define STATE_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

enum States {
    EMPTY,
    LOAD,
    MENU,
    PAUSE,
    GAME
};

class State {
    public:
        State(): m_window(nullptr), m_event(), m_isPaused(false) {};
        virtual ~State() {};
        void linkWindow(std::shared_ptr<sf::RenderWindow> window) { m_window = window; };
        virtual void onStart() = 0;
        virtual void onStop() = 0;
        virtual void onPause() = 0;
        virtual void onResume() = 0;
        virtual void update() = 0;
        virtual void handleEvent() = 0;
    protected:
        std::shared_ptr<sf::RenderWindow> m_window;
        sf::Event m_event;
        bool m_isPaused;
};

#endif /* !STATE_HPP */
