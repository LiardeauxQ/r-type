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
#include <memory>

shared_ptr<ecs::World> initializeWorld() {
    auto world = make_shared<ecs::World>();
    auto stateData = make_shared<ecs::StateData<string>>(ecs::StateData<string> { world, "Salut"});
    auto pool = new ecs::ThreadPool<ecs::StateData<string>, ecs::Error>(stateData);
    world->createResource("threadPool");
    world->writeResource("threadPool", pool);
    world->createResource("delta");
    world->writeResource("delta", chrono::duration<double>(0));
    return world;
}

unique_ptr<ecs::AbstractState<string>> initializeMainMenu(shared_ptr<ecs::World> world) {
    auto pool = world->fetchResource<ecs::ThreadPool<ecs::StateData<string>, ecs::Error> *>("threadPool");
    ecs::Dispatcher<ecs::StateData<string>, ecs::Error> dispatcher(*pool);
    auto state = make_unique<MainMenuState>();
    return state;
}

int main(int argc, char *argv[]) {
    auto world = initializeWorld();
    auto initialState = initializeMainMenu(world);
    ecs::StateMachine states(move(initialState));

    // states.run();
    return 0;
}
