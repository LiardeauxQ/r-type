/*
** EPITECH PROJECT, 2019
** GameState.hpp
** File description:
** PauseState header
*/

#ifndef GAMESTATE_HPP
	#define GAMESTATE_HPP

#include <vector>
#include "State.hpp"
#include "entities/Ship.hpp"

class GameState : public State {
    public:
        GameState(std::shared_ptr<ClientPacketDispatcher> dispatcher, TextureBuilder &textureBuilder);
        ~GameState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        void update();
        Transition handleEvent(sf::Event &envent);
    private:
        Ship m_player;
        std::vector<Bullet> m_bullets;
};

#endif /* !GAMESTATE_HPP */
