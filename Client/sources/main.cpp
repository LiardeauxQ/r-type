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
#include "WithParameterSystem.hpp"
#include "SystemNetworkEvent.hpp"

int main(int argc, char* argv[])
{
    try {
        auto dispatcher = make_unique<ecs::Dispatcher<ecs::StateData<string>, ecs::Error>>();
        dispatcher->registerSystem<DrawSystem>();
        dispatcher->registerSystem<MovementSystem>();
        dispatcher->registerSystem<WithParameterSystem>(100);
        dispatcher->registerSystem<SystemNetworkEvent>();
        auto initialState = make_unique<MainMenuState>(move(dispatcher));

        ecs::Application<string, ecs::Event> app(move(initialState), make_unique<string>());
        app.run();
    } catch(const exception& e) {
        cout << e.what() << endl;
    } catch(const char *str) {
        cout << str << endl;
    }
    return 0;
}
