//
// Created by Quentin Liardeaux on 12/17/19.
//

#ifndef R_TYPE_APPLICATION_HPP
#define R_TYPE_APPLICATION_HPP

#include "TcpListener.hpp"
#include "TcpStream.hpp"
#include "ServerPacketDispatcher.hpp"
#include <optional>

class Application {
public:
    Application(int ac, char **av);
    ~Application() = default;

    void run();
private:
    ServerPacketDispatcher m_dispatcher;
};

#endif //R_TYPE_APPLICATION_HPP
