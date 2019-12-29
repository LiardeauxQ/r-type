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
        GameState(std::shared_ptr<GameData> gameData);
        ~GameState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        Transition update();
        Transition handleEvent(sf::Event &envent);
};

#endif /* !GAMESTATE_HPP */
