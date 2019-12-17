/*
** EPITECH PROJECT, 2019
** State.hpp
** File description:
** State header
*/

#ifndef STATE_HPP
	#define STATE_HPP

enum States {
    EMPTY,
    LOAD,
    MENU,
    PAUSE,
    GAME
};

class State {
    public:
        State() {};
        virtual ~State() {};
        virtual void onStart() = 0;
        virtual void onStop() = 0;
        virtual void onPause() = 0;
        virtual void onResume() = 0;
        virtual void update() = 0;
        virtual void handleEvent() = 0;
};

#endif /* !STATE_HPP */
