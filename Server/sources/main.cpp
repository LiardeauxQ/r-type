/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Main file.
*/

#include <iostream>
#include <ostream>
#include "MainMenuState.hpp"
#include "Dispatcher.hpp"
#include "Application.hpp"
#include "MessageFactory.hpp"
#include "BasicEntityComponentStorage.hpp"
#include "Loader.hpp"
/*#include <GameServer.hpp>

#ifndef VERSION
    #define VERSION "0.1.0"
#endif


int main(int argc, char *argv[]) {
    std::cout << "Welcome to server V" << VERSION << "." << std::endl;
    try {
        CreateRoom request("Test");
        auto server = GameServer(8080);
        return server.run();
    } catch(char const *msg) {
        cerr << msg << endl;
        return 84;
    }
}
*/

class CreateRoom : public Message {

    public:
        String getKey() const override {
            return Message::getKey() + "::CreateRoom";
        }

        void deserialize(Vec<u8> &data) override {
            for (auto chr : data) {
            }
        };

        Box<IFactorizable<String>> copy() const override {
            return std::unique_ptr<IFactorizable<String>>(new CreateRoom());
        };

        Vec<u8> serialize() const override {
            return Vec<u8>();
        };

};

int main(void) {
/*
    MessageFactory factory;
    Vec<u8> vec1 = {'R', '-', 'T', 'Y', 0xC4, 0x54, 0xAD, 0xEC, 0xC9, 0xE0, 0x63, 0x69, 0x2A, 0x64, 0xCF, 0xAC, 0xB9, 0x7C, 0x49 };
    Vec<u8> vec2 = {0x34, 0x05, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 'R', '-'};
    Vec<u8> vec3 = {'T', 'Y', 0xC4, 0x54, 0xAD, 0xEC, 0xC9, 0xE0, 0x63, 0x69, 0x2A, 0x64, 0xCF, 0xAC, 0xB9, 0x7C, 0x49};
    Vec<u8> vec4 = {0x34, 0x05, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 'R', '-', 'T', 'Y', 0xC4, 0x54, 0xAD, 0xEC, 0xC9, 0xE0, 0x63, 0x69, 0x2A, 0x64, 0xCF, 0xAC, 0xB9, 0x7C, 0x49, 0x34, 0x05, 0x00, 0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00};
    factory.registerMessage<CreateRoom>();

    auto packets1 = factory.deserialize_packets(vec1);
    std::cout << "First:" << std::endl;
    for (auto it = packets1.begin(); it != packets1.end(); ++it) {
        std::cout << (*it).get() << std::endl;
    }

    auto packets2 = factory.deserialize_packets(vec2);
    std::cout << "Second:" << std::endl;
    for (auto it = packets2.begin(); it != packets2.end(); ++it) {
        std::cout << (*it).get() << std::endl;
    }

    auto packets3 = factory.deserialize_packets(vec3);
    std::cout << "Third:" << std::endl;
    for (auto it = packets3.begin(); it != packets3.end(); ++it) {
        std::cout << (*it).get() << std::endl;
    }

    auto packets4 = factory.deserialize_packets(vec4);
    std::cout << "Fourth:" << std::endl;
    for (auto & it : packets4) {
        std::cout << it.get() << std::endl;
    }

    ecs::BasicEntityComponentStorage storage;

    storage.addComponentSchema(
        ecs::ComponentSchemaBuilder(String("Position"))
            .with(ecs::ComponentAttributeSchema("x", ecs::AttributeType::INT))
            .with(ecs::ComponentAttributeSchema("y", ecs::AttributeType::INT))
            .with(ecs::ComponentAttributeSchema("z", ecs::AttributeType::STRING))
            .build()
    );
    storage.addComponentSchema(
        ecs::ComponentSchemaBuilder(String("Velocity"))
            .with(ecs::ComponentAttributeSchema("x", ecs::AttributeType::INT))
            .with(ecs::ComponentAttributeSchema("y", ecs::AttributeType::INT))
            .with(ecs::ComponentAttributeSchema("z", ecs::AttributeType::STRING))
            .build()
    );
    auto entities = Vec<ecs::Entity>();
    for (int i = 0; i < 10; i++) {
        auto position = ecs::Component("Position");
        auto velocity = ecs::Component("Velocity");

        position.addAttribute(ecs::ComponentAttribute(String("x"), ecs::AttributeType::INT, std::any(i)));
        position.addAttribute(ecs::ComponentAttribute(String("y"), ecs::AttributeType::INT, std::any(i)));
        position.addAttribute(ecs::ComponentAttribute(String("z"), ecs::AttributeType::STRING, std::any(String("TESTVEL"))));
        velocity.addAttribute(ecs::ComponentAttribute(String("x"), ecs::AttributeType::INT, std::any(i)));
        velocity.addAttribute(ecs::ComponentAttribute(String("y"), ecs::AttributeType::INT, std::any(i)));
        velocity.addAttribute(ecs::ComponentAttribute(String("z"), ecs::AttributeType::STRING, std::any(String("TESTVEL"))));
        auto entityBuilder = ecs::EntityBuilder().with(position);
        if (i % 2)
            entityBuilder.with(velocity);
        entities.push_back(entityBuilder.build());
    }
    storage.store(entities);
    auto request = ecs::EntityRequestBuilder()
        .with(String("Position"))
        .with(String("Velocity"))
        .build();
    auto newEntities = storage.request(move(request));
    for (auto entity : newEntities) {
        std::cout << entity.getName() << std::endl;
    }
    std::cout << storage << std::endl;
    */

    try {
        Loader loader;
        auto lib = Library(std::filesystem::path(String("../../Experiments/dummy_mod.so")));
        loader.registerLibrary(std::move(lib));
        //auto dispatcher = make_unique<ecs::Dispatcher<ecs::StateData<string>, ecs::Error>>();
        //loader.useSymbol<int, Box<ecs::Dispatcher<ecs::StateData<std::string>, ecs::Error>> &>(String("registerSystems"), dispatcher);
        //auto initialState = make_unique<MainMenuState>(move(dispatcher));

        ecs::Application<string, ecs::Event> app(make_unique<string>());

        loader.useSymbol<int, ecs::World &>(String("registerSchemas"), app.getWorld());
        for (int i = 0; i < 10; i++) {
            auto position = ecs::Component("Position");
            auto velocity = ecs::Component("Velocity");

            position.addAttribute(ecs::ComponentAttribute(String("x"), ecs::AttributeType::INT, std::any(i)));
            position.addAttribute(ecs::ComponentAttribute(String("y"), ecs::AttributeType::INT, std::any(i)));
            position.addAttribute(ecs::ComponentAttribute(String("z"), ecs::AttributeType::INT, std::any(i)));
            velocity.addAttribute(ecs::ComponentAttribute(String("x"), ecs::AttributeType::INT, std::any(i)));
            velocity.addAttribute(ecs::ComponentAttribute(String("y"), ecs::AttributeType::INT, std::any(i)));
            velocity.addAttribute(ecs::ComponentAttribute(String("z"), ecs::AttributeType::INT, std::any(i)));
            auto entityBuilder = ecs::EntityBuilder().with(position);
            if (i % 2)
                entityBuilder.with(velocity);
            app.getWorld().storeEntity(entityBuilder.build());
        }
        app.registerState<MainMenuState>();
        app.run("base::MainMenuState");
    } catch(const exception& e) {
        cout << e.what() << endl;
    } catch(const char *str) {
        cout << str << endl;
    }
    return 0;


}