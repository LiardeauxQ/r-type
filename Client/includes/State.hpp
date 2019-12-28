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
#include "GameData.hpp"
#include "Transition.hpp"
#include "TcpCommunication.hpp"
#include "UdpCommunication.hpp"
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
        State(std::shared_ptr<GameData> gameData)
        : m_gameData(std::move(gameData)), m_window(nullptr), m_deltaTime(0), m_isPaused(false) {};
        virtual ~State() {};
        void linkToGame(boost::shared_ptr<UdpCommunication> udpHandler, sf::RenderWindow *window, float *deltaTime)
        { m_udpHandler = std::move(udpHandler); m_window = window; m_deltaTime = deltaTime; };
        virtual void onStart() = 0;
        virtual void onStop() = 0;
        virtual void onPause() = 0;
        virtual void onResume() = 0;
        virtual Transition update() = 0;
        virtual Transition handleEvent(sf::Event &event) = 0;
    protected:
        std::shared_ptr<GameData> m_gameData;
        boost::shared_ptr<UdpCommunication> m_udpHandler;
        sf::RenderWindow *m_window;
        float *m_deltaTime;
        bool m_isPaused;
};

#endif /* !STATE_HPP */
