/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Main file.
*/

#ifndef VERSION
#define VERSION "NOT DEFINED"
#endif

#include "Dispatcher.hpp"
#include "MainMenuState.hpp"
#include "Application.hpp"
#include "ThreadPool.hpp"

#include "DrawSystem.hpp"
#include "MovementSystem.hpp"

int main(int argc, char* argv[])
{
    try {
        auto dispatcher = make_unique<ecs::Dispatcher<ecs::StateData<string>, ecs::Error>>();
        dispatcher->registerSystem<DrawSystem>();
        dispatcher->registerSystem<MovementSystem>();
        auto initialState = make_unique<MainMenuState>(move(dispatcher));

        ecs::Application<string, ecs::Event> app(move(initialState), make_unique<string>());
        app.run();
    } catch(char const *e) {
        cout << e << endl;
    }
    return 0;
}
