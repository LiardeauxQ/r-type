//
// Created by Quentin Liardeaux on 12/17/19.
//

#include "Application.hpp"

Application::Application(int ac, char **av)
    : m_dispatcher(8678, "0.0.0.0") {
}

void Application::run() {
    m_dispatcher.run();
}