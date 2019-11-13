#include "AbstractFactory.hpp"
#include "Message.hpp"
#include "MD5Hasher.hpp"
#include <iostream>

class CreateRoom : public Message {

    public:
        String getKey() const override {
            return Message::getKey() + "::CreateRoom";
        }

        void deserialize(Vec<u8> &data) override {

        };

        Box<IFactorizable<String>> copy() const override {
            return std::unique_ptr<IFactorizable<String>>(new CreateRoom());
        };

        Vec<u8> serialize() const override {
            return Vec<u8>();
        };

};

int main(void) {

    AbstractFactory<String, MD5Hasher> factory;

    factory.register_factorizable<CreateRoom>();

    std::cout << factory.create("base::CreateRoom").get() << std::endl;

}