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
        State();
        virtual ~State() = 0;
        virtual void onStart() = 0;
        virtual void onStop() = 0;
        virtual void onPause() = 0;
        virtual void onResume() = 0;
        virtual void update() = 0;
        virtual void handleEvent() = 0;
};

class EmptyState : public State {
    public:
        EmptyState();
        ~EmptyState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        void update();
        void handleEvent();
};

class LoadState : public State {
    public:
        LoadState();
        ~LoadState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        void update();
        void handleEvent();
};

class MenuState : public State {
    public:
        MenuState();
        ~MenuState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        void update();
        void handleEvent();
};

class PauseState : public State {
    public:
        PauseState();
        ~PauseState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        void update();
        void handleEvent();
};
class GameState : public State {
    public:
        GameState();
        ~GameState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        void update();
        void handleEvent();
};

#endif /* !STATE_HPP */
