//
// Created by Quentin Liardeaux on 11/19/19.
//

#include "EventHandler.hpp"

EventHandler::EventHandler(shared_ptr<deque<ecs::Event>> events)
    : m_producers()
    , m_eventThread()
    , m_mutex()
    , m_events(move(events))
    , m_isRunning(false)
    , m_isLock(false) {
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

void EventHandler::lock() {
    m_isLock = true;
}

void EventHandler::unlock() {
    m_isLock = false;
}

void EventHandler::addEvents(vector<ecs::Event> events) {
    if (m_isLock)
        lock_guard<mutex> lock(m_mutex);
    for (const auto& event : events)
        m_events->push_back(event);
}

void EventHandler::addEvent(const ecs::Event& event) {
    m_events->push_back(event);
}

void EventHandler::addProducer(unique_ptr<AbstractEventProducer> producer) {
    m_producers.push_back(move(producer));
}