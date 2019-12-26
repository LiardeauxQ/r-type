//
// Created by Quentin Liardeaux on 12/18/19.
//

#ifndef R_TYPE_FIRSTCONNECTION_HPP
#define R_TYPE_FIRSTCONNECTION_HPP

#include <string>
#include <memory>

#include "Message.hpp"
#include "protocol.hpp"

class ClientConnect : public Message {
public:
    ClientConnect(uint16_t port, std::string addr)
            : Message(TCP_COMMUNICATION::CLIENT_CONNECT)
            , m_port(port)
            , m_addr(std::move(addr)) {}
    ~ClientConnect() override = default;

    static std::unique_ptr<Message> from(void *data);

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + CLIENT_CONNECT_SIZE; }

    uint16_t getPort() const { return m_port; }
    const std::string &getAddr() const { return m_addr; }
private:
    uint16_t m_port;
    std::string m_addr;
};

#endif //R_TYPE_FIRSTCONNECTION_HPP
