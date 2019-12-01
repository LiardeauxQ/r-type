//

#include "Definitions.hpp"
#include "AbstractFactory.hpp"
#include "Message.hpp"
#include "MD5Hasher.hpp"
#include <tuple>

class MessageFactory {

    public:
        MessageFactory()
        : m_factory()
        , m_store()
        {
        }

        template<typename T>
        void registerMessage() {
            m_factory.registerFactorizable<T>();
        }

        Vec<Box<Message>> deserialize_packets(Vec<u8> const &bytes);
    
    private:
        AbstractFactory<String, MD5Hasher> m_factory;
        Vec<u8> m_store;

};
