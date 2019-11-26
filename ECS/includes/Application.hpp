//
// Created by alex on 11/21/19.
//

#pragma once

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
    // void handleEvent(StateData<T> stateData);

    shared_ptr<ThreadPool<ecs::StateData<T>, ecs::Error>> m_threadPool;
    deque<Transition<T, E>> m_transitions;
    EventHandler m_eventHandler;
    unique_ptr<T> m_data;
    ecs::StateMachine<T, E> m_stateMachine;
    World m_world;
};

template <typename T, typename E>
Application<T, E>::Application(unique_ptr<AbstractState<T, E>> initialState, unique_ptr<T> data)
    : m_threadPool{make_shared<ThreadPool<ecs::StateData<T>, ecs::Error>>(1)} // TODO: Check if the game doesn't run the same system twice. Then try with the thread pool.
    , m_transitions()
    , m_eventHandler()
    , m_data(move(data))
    , m_stateMachine([&]() {
        initialState->attachThreadPool(this->m_threadPool);
        return move(initialState);
    }())
    , m_world()
{
    auto window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "ECSApplication");
    window->setFramerateLimit(30);
    window->setActive(false);
    auto queue = make_shared<deque<sf::Event>>();
    m_eventHandler.addProducer(make_unique<SFMLEventProducer>(*window, queue));
    m_world.writeResource<shared_ptr<deque<sf::Event>>>("sfEvent", move(queue));
    m_world.writeResource<sf::RenderWindow *>("window", window);
    m_world.writeResource<deque<Transition<T, E>> *>("transitionQueue", &m_transitions);
}

template <typename T, typename E>
void Application<T, E>::run()
{
    double deltaTime = 0;

    m_eventHandler.start();
    m_stateMachine.start(StateData<T> { m_world, deltaTime, *m_data });
    while (m_stateMachine.m_running) {
        m_world.m_timer.start();
        auto stateData = StateData<T> { m_world, deltaTime, *m_data };
        m_stateMachine.update(stateData);
        // this->handleEvent(stateData);
        this->handleTransition(stateData);
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
    while (m_transitions.size() > 0 && m_stateMachine.m_running) {
        m_stateMachine.transition(move(m_transitions.back()), stateData);
        m_transitions.pop_back();
    }
}

// template <typename T, typename E>
// void Application<T, E>::handleEvent(StateData<T> stateData)
// {
//     m_eventHandler.lock();
//     while (!m_events->empty()) {
//         Event event = m_events->back();
//         m_transitions.push_back(m_stateMachine.handleEvent(stateData, event));
//         m_events->pop_back();
//     }
//     m_eventHandler.unlock();
// }

}
