//
// Created by Quentin Liardeaux on 12/17/19.
//

#ifndef R_TYPE_APPLICATION_HPP
#define R_TYPE_APPLICATION_HPP

#include "TcpListener.hpp"
#include "TcpStream.hpp"
#include <optional>

class Application {
public:
    Application(uint16_t port=8676);
    ~Application() = default;

    void run();
private:
    TcpListener m_listener;
    std::optional<TcpStream> m_streamer;
};

#endif //R_TYPE_APPLICATION_HPP
