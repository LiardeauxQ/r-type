//
// Created by alex on 11/21/19.
//

#pragma once

#include "AbstractEvent.hpp"
#include "AbstractState.hpp"
#include "Event.hpp"
#include "StateMachine.hpp"
#include "SFMLEventProducer.hpp"

namespace ecs {

using namespace std;

template <typename T, typename E = Event>
class Application {
public:
    Application(unique_ptr<AbstractState<T, E>> initialState, unique_ptr<T> data);
    ~Application() = default;

    void registerState(unique_ptr<AbstractState<T, E>> newState);
    void run();

private:
    void handleTransition(StateData<T> stateData);
    void handleEvent(StateData<T> stateData);

    ThreadPool<ecs::StateData<T>, ecs::Error> m_threadPool;
    World m_world;
    ecs::StateMachine<T, E> m_stateMachine;
    shared_ptr<deque<Event>> m_events;
    deque<Transition<T, E>> m_transitions;
    bool m_isRunning;
    EventHandler m_eventHandler;
    unique_ptr<T> m_data;
};

template <typename T, typename E>
Application<T, E>::Application(unique_ptr<AbstractState<T, E>> initialState, unique_ptr<T> data)
    : m_threadPool()
    , m_world()
    , m_stateMachine([this, &initialState]() -> unique_ptr<AbstractState<T, E>> {
        initialState->attachThreadPool(&this->m_threadPool);
        return move(initialState);
    }())
    , m_events()
    , m_transitions()
    , m_isRunning(true)
    , m_eventHandler(m_events)
    , m_data(move(data))
{
    auto window = make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Name");
    m_world.writeResource("window", window);
    m_eventHandler.addProducer(make_unique<SFMLEventProducer>(window));
}

template <typename T, typename E>
void Application<T, E>::run()
{
    int64_t deltaTime = 0;

    m_eventHandler.start();
    while (m_isRunning) {
        m_world.m_timer.start();
        auto stateData = StateData<T> { m_world, deltaTime, *m_data };
        m_stateMachine.update(stateData);
        this->handleTransition(stateData);
        this->handleEvent(stateData);
        deltaTime = m_world.m_timer.elapsed();
    }
}

template <typename T, typename E>
void Application<T, E>::registerState(unique_ptr<AbstractState<T, E>> newState)
{
    newState->attachThreadPool(&m_threadPool);
    m_stateMachine.push(move(newState));
}

template <typename T, typename E>
void Application<T, E>::handleTransition(StateData<T> stateData)
{
    while (m_transitions.size() > 0) {
        m_stateMachine.transition(move(m_transitions.back()), stateData);
        m_transitions.pop_back();
    }
}

template <typename T, typename E>
void Application<T, E>::handleEvent(StateData<T> stateData)
{
    m_eventHandler.lock();
    while (!m_events->empty()) {
        Event event = m_events->back();
        m_stateMachine.handleEvent(stateData, event);
        m_events->pop_back();
    }
    m_eventHandler.unlock();
}

}
