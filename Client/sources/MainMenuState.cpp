//
// Created by alex on 11/19/19.
//

#include "MainMenuState.hpp"

void MainMenuState::onStart(ecs::StateData<string>& data)
{
    cout << "Starting Main menu" << endl;
}

void MainMenuState::onStop(ecs::StateData<string>& data)
{
    cout << "Stopping Main Menu" << endl;
}

void MainMenuState::onPause(ecs::StateData<string>& data)
{
    cout << "Pausing Main Menu" << endl;
}

void MainMenuState::onResume(ecs::StateData<string>& data)
{
    cout << "Resuming Main Menu" << endl;
}

ecs::Transition<string> MainMenuState::update(ecs::StateData<string>& data)
{
    cout << "Updating Main Menu" << endl;
    return ecs::Transition<string>();
}

ecs::Transition<string> MainMenuState::handleEvent(ecs::StateData<string>& data)
{
    cout << "Handling event of Main Menu" << endl;
    return ecs::Transition<string>();
}

ecs::Transition<string> MainMenuState::fixedUpdate(ecs::StateData<string>& data)
{
    cout << "Fixed update." << endl;
    return ecs::Transition<string>();
}

void MainMenuState::shadowUpdate(ecs::StateData<string>& data)
{
    cout << "Shadow update." << endl;
}

void MainMenuState::shadowFixedUpdate(ecs::StateData<string>& data)
{
    cout << "Shadow fixed update." << endl;
}
