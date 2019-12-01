//
// Created by Quentin Liardeaux on 11/19/19.
//

#ifndef R_TYPE_TESTEVENT_HPP
#define R_TYPE_TESTEVENT_HPP

#include <string>
#include <any>

#include "Event.hpp"
#include "EventHandler.hpp"

using namespace std;

class TestEventProducer: public AbstractEventProducer {
public:
    TestEventProducer();
    ~TestEventProducer() final = default;

    vector<ecs::Event> fetchEvents() final;
};

#endif //R_TYPE_TESTEVENT_HPP
