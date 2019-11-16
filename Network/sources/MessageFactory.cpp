//
// Created by nwmqpa on 12/11/19
//

#include <string.h>
#include "MessageFactory.hpp"

Vec<Box<Message>> MessageFactory::deserialize_packets(Vec<u8> const &bytes) {
    Vec<Box<Message>> vector;

    m_store.insert(m_store.end(), bytes.begin(), bytes.end());
    
    try {
        while (true) {
            char hash[17];
            char *data = reinterpret_cast<char *>(m_store.data());
            if (m_store.size() < 24 || strncmp(data, "R-TY", 4))
                throw MessageDeserializationException();
            auto messageLength = *reinterpret_cast<int *>(data + 20);
            if (m_store.size() < 24 + messageLength)
                throw MessageDeserializationException();
            memset(hash, 0, 17);
            strncpy(hash, data + 4, 16);
            /// TODO: Add a segfault barrier in case of a failed dynamic cast
            auto message = static_unique_pointer_cast<Message>(m_factory.createWithHash(String(hash)));
            Vec<u8> tempVec;
            tempVec.assign(m_store.begin() + 24, m_store.begin() + 24 + messageLength);
            m_store.erase(m_store.begin(), m_store.begin() + 24);
            message->deserialize(tempVec);
            m_store.erase(m_store.begin(), m_store.begin() + messageLength);
            vector.push_back(std::move(message));
        }
    } catch(MessageDeserializationException &ex) {
        return vector;
    }
}