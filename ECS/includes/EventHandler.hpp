//
// Created by Quentin Liardeaux on 11/19/19.
//

#ifndef R_TYPE_EVENTHANDLER_HPP
#define R_TYPE_EVENTHANDLER_HPP

#include <memory>
#include <mutex>
#include <thread>
#include <deque>
#include <vector>

#include "Event.hpp"

using namespace std;

class IEventProducer {
public:
    virtual ~IEventProducer() = default;
    virtual void pollEvents() = 0;
};

class EventHandler {
public:
    EventHandler();
    ~EventHandler();

    void start();
    void stop();

    void addProducer(unique_ptr<IEventProducer> producer);
private:
    void run();

    bool m_running;
    vector<unique_ptr<IEventProducer>> m_producers;
    thread m_eventThread;
};

#endif //R_TYPE_EVENTHANDLER_HPP
