//
// Created by Quentin Liardeaux on 11/19/19.
//

#include "TestEvent.hpp"

TestEvent::TestEvent(string const &type)
    : ecs::Event(type, 1) {}

TestEventProducer::TestEventProducer() {}

vector<unique_ptr<ecs::Event>> TestEventProducer::fetchEvents() {
    vector<unique_ptr<ecs::Event>> events;

    for (int i = 0 ; i < 2 ; i++)
        events.push_back(make_unique<TestEvent>("test"));
    return events;
}
