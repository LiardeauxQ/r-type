//
// Created by Quentin Liardeaux on 11/19/19.
//

#ifndef R_TYPE_TESTEVENT_HPP
#define R_TYPE_TESTEVENT_HPP

#include <string>
#include <any>

#include "AbstractEvent.hpp"
#include "Event.hpp"

using namespace std;

class TestEvent: public ecs::Event {
public:
    TestEvent(string const &type);
    ~TestEvent() = default;
};

class TestEventProducer: public AbstractEventProducer {
public:
    TestEventProducer();
    ~TestEventProducer() final = default;

    vector<unique_ptr<ecs::Event>> fetchEvents() final;
};

#endif //R_TYPE_TESTEVENT_HPP
