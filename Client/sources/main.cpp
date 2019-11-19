/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Main file.
*/

#include <iostream>

#ifndef VERSION
    #define VERSION "NOT DEFINED"
#endif

#include "StateMachine.hpp"
#include "MainMenuState.hpp"
#include "World.hpp"
#include <chrono>

int main(void) {
    try {
        auto world = make_shared<ecs::World>();
        auto begin = chrono::high_resolution_clock::now();
        world->createResource("Delta");

        ecs::StateMachine states(unique_ptr<AbstractState>(new MainMenuState()));
        auto end = chrono::high_resolution_clock::now();
        world->writeResource("Delta", std::chrono::duration<double>(end - begin));
        cout << world->fetchResource<std::chrono::duration<double>>("Delta").count() << endl;
        // states.run();
    } catch(const exception& e) {
        cout << e.what() << endl;
    }
    return 0;
}
