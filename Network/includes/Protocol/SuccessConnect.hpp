//
// Created by Quentin Liardeaux on 12/23/19.
//

#ifndef R_TYPE_SUCCESSCONNECT_HPP
#define R_TYPE_SUCCESSCONNECT_HPP

class SuccessConnect : public Message {
public:
    SuccessConnect(uint8_t id)
            : Message(TCP_COMMUNICATION::SUCCESS_CONNECT)
            , m_id(id) {}
    SuccessConnect(void *data);
    ~SuccessConnect() override = default;

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + SUCCESS_CONNECT_SIZE; }

    uint8_t getId() const { return m_id; }
private:
    uint8_t m_idPlayer;
};


#endif //R_TYPE_SUCCESSCONNECT_HPP
