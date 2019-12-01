/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Main file.
*/

#include <iostream>
#include <ostream>
#include "Dispatcher.hpp"
#include "Application.hpp"
#include "MessageFactory.hpp"
#include "BasicEntityComponentStorage.hpp"
#include "Loader.hpp"

int main(void) {
    try {
        Loader loader;
        auto lib = Library(std::filesystem::path(String("Experiments/dummy_mod.so")));
        loader.registerLibrary(std::move(lib));

        ecs::Application<string, ecs::Event> app(make_unique<string>());

        loader.useSymbol<int, ecs::Application<string, ecs::Event> &>(String("registerSchemas"), app);
        loader.useSymbol<int, ecs::Application<string, ecs::Event> &>(String("registerStates"), app);
        loader.useSymbol<int, ecs::Application<string, ecs::Event> &>(String("registerSystems"), app);
        loader.useSymbol<int, ecs::Application<string, ecs::Event> &>(String("addBundle"), app);

        app.run("base::MainMenuState");
    } catch(const char *str) {
        cout << str << endl;
    } catch(const exception& e) {
        cout << e.what() << endl;
    }
    return 0;


}