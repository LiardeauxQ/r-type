//
// Created by Quentin Liardeaux on 11/19/19.
//

#include "Event.hpp"

EventHandler::EventHandler(shared_ptr<deque<unique_ptr<ecs::Event>>> events)
    : m_producers()
    , m_eventThread()
    , m_events(move(events))
    , m_isRunning(false) {
}

void EventHandler::start() {
    m_isRunning = true;
    m_eventThread = thread(&EventHandler::run, this);
}

void EventHandler::run() {
    while (m_isRunning) {
        for (auto &m_producer : m_producers) {
            addEvents(m_producer->fetchEvents());
        }
    }
}

void EventHandler::stop() {
    m_isRunning = false;
    m_eventThread.join();
}

void EventHandler::addEvents(vector<unique_ptr<ecs::Event>> events) {
    for (auto & event : events)
        m_events->push_back(move(event));
}

void EventHandler::addEvent(unique_ptr<ecs::Event> event) {
    m_events->push_back(move(event));
}

void EventHandler::addProducer(unique_ptr<AbstractEventProducer> producer) {
    m_producers.push_back(move(producer));
}