/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Main file.
*/

#include <iostream>
#include <ostream>

#ifndef VERSION
    #define VERSION "NOT DEFINED"
#endif

int main(void) {
    std::cout << "Welcome to server V" << VERSION << "." << std::endl;
    return 0;
}
