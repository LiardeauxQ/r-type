//
// Created by Quentin Liardeaux on 11/19/19.
//

#ifndef R_TYPE_EVENT_HPP
#define R_TYPE_EVENT_HPP

#include <memory>
#include <mutex>
#include <thread>
#include <deque>
#include <vector>

#include "AbstractEvent.hpp"

using namespace std;

class AbstractEventProducer {
public:
    virtual ~AbstractEventProducer() = default;
    virtual vector<unique_ptr<ecs::Event>> fetchEvents() = 0;
};

class EventHandler {
public:
    explicit EventHandler(shared_ptr<deque<unique_ptr<ecs::Event>>> events);
    ~EventHandler() = default;

    void start();
    void stop();
    void lock();
    void unlock();

    void addProducer(unique_ptr<AbstractEventProducer> producer);
    void addEvents(vector<unique_ptr<ecs::Event>> events);
    void addEvent(unique_ptr<ecs::Event> event);
private:
    void run();

    vector<unique_ptr<AbstractEventProducer>> m_producers;
    thread m_eventThread;
    mutex m_mutex;
    shared_ptr<deque<unique_ptr<ecs::Event>>> m_events;
    bool m_isRunning;
    bool m_isLock;
};

#endif //R_TYPE_EVENT_HPP
