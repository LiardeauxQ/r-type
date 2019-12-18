//
// Created by Quentin Liardeaux on 12/17/19.
//

#include "../includes/Application.hpp"

Application::Application(uint16_t port)
    : m_listener(port) {
}

void Application::run() {
    m_streamer = m_listener.accept();
    m_listener.listen(30);
}