//
// Created by Quentin Liardeaux on 11/19/19.
//

#include "EventHandler.hpp"

EventHandler::EventHandler()
    : m_running(false)
    , m_eventThread()
    , m_producers()
{
}

void EventHandler::start() {
    m_running = true;
    m_eventThread = thread(&EventHandler::run, this);
}

void EventHandler::run() {
    while (m_running)
        for (auto& m_producer : m_producers)
            m_producer->pollEvents();
}

void EventHandler::addProducer(unique_ptr<IEventProducer> producer) {
    m_producers.push_back(move(producer));
}

EventHandler::~EventHandler()
{
    this->stop();
}

void EventHandler::stop()
{
    m_running = false;
    m_eventThread.join();
}
