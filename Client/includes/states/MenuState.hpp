/*
** EPITECH PROJECT, 2019
** MenuState.hpp
** File description:
** MenuState header
*/

#ifndef MENUSTATE_HPP
	#define MENUSTATE_HPP

#include "State.hpp"

class MenuState : public State {
    public:
        MenuState(std::shared_ptr<GameData> gameData);
        ~MenuState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        Transition update();
        Transition handleEvent(sf::Event &event);
};

#endif /* !MENUSTATE_HPP */
