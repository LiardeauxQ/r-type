/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Main file.
*/

#include <iostream>
#include <ostream>
#include <GameServer.hpp>
#include "Protocol/CreateRoom.hpp"

#ifndef VERSION
    #define VERSION "0.1.0"
#endif

int main(int argc, char *argv[]) {
    std::cout << "Welcome to server V" << VERSION << "." << std::endl;
    try {
        CreateRoom request("Test");
        auto server = GameServer(8080);
        return server.run();
    } catch(char const *msg) {
        cerr << msg << endl;
        return 84;
    }
}
