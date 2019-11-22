//
// Created by Quentin Liardeaux on 11/19/19.
//

#include "TestEvent.hpp"

TestEventProducer::TestEventProducer() {}

vector<ecs::Event> TestEventProducer::fetchEvents() {
    vector<ecs::Event> events;

    for (int i = 0 ; i < 2 ; i++)
        events.push_back(ecs::Event("test", 1));
    return events;
}
