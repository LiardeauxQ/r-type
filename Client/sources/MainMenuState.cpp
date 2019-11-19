//
// Created by alex on 11/19/19.
//

#include "MainMenuState.hpp"

void MainMenuState::onStart()
{
    cout << "Starting Main menu" << endl;
}

void MainMenuState::onStop()
{
    cout << "Stopping Main Menu" << endl;
}

void MainMenuState::onPause()
{
    cout << "Pausing Main Menu" << endl;
}

void MainMenuState::onResume()
{
    cout << "Resuming Main Menu" << endl;
}

Transition MainMenuState::update()
{
    cout << "Updating Main Menu" << endl;
    return Transition();
}

Transition MainMenuState::handleEvent()
{
    cout << "Handling event of Main Menu" << endl;
    return Transition();
}
Transition MainMenuState::fixedUpdate()
{
    cout << "Fixed update." << endl;
    return Transition();
}

void MainMenuState::shadowUpdate()
{
    cout << "Shadow update." << endl;
}

void MainMenuState::shadowFixedUpdate()
{
    cout << "Shadow fixed update." << endl;
}
