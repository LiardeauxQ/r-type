//
// Created by alex on 11/21/19.
//

#pragma once

#include "AbstractState.hpp"
#include "Event.hpp"
#include "StateMachine.hpp"
#include "Bundle.hpp"

namespace ecs {

using namespace std;

template <typename T, typename E = Event>
class Application {
public:
    Application(unique_ptr<T> data);
    ~Application() = default;

    template<typename S>
    void registerState();

    template<typename S, typename... Args>
    void registerSystem(const String &name, Args... args);

    template<typename S>
    void registerSystem(const String &name);

    void run(const String &stateName);
    void withBundle(Bundle& bundle);

    template <typename B, typename... Args>
    void withBundle(Args&&... args);

    void registerComponent(ComponentSchema schema);


private:
    void handleTransition(StateData<T> stateData);
    // void handleEvent(StateData<T> stateData);

    deque<Transition<T, E>> m_transitions;
    EventHandler m_eventHandler;
    unique_ptr<T> m_data;
    ecs::StateMachine<T, E> m_stateMachine;
    World m_world;
};

template <typename T, typename E>
Application<T, E>::Application(unique_ptr<T> data)
    : m_transitions()
    , m_eventHandler()
    , m_data(move(data))
    , m_stateMachine()
    , m_world(unique_ptr<IEntityComponentStorage>(new BasicEntityComponentStorage()))
{
    m_world.writeResource<deque<Transition<T, E>> *>("transitionQueue", &m_transitions);
}

template <typename T, typename E>
void Application<T, E>::run(const String &stateName)
{
    double deltaTime = 0;

    m_eventHandler.start();
    m_stateMachine.start(stateName, StateData<T> { m_world, deltaTime, *m_data });
    while (m_stateMachine.m_running) {
        m_world.m_timer.start();
        auto stateData = StateData<T> { m_world, deltaTime, *m_data };
        m_stateMachine.update(stateData);
        // this->handleEvent(stateData);
        this->handleTransition(stateData);
        deltaTime = m_world.m_timer.elapsed();
    }
}

template<typename T, typename E>
template<typename S>
void Application<T, E>::registerState()
{
    static_assert(is_base_of<AbstractState<T, E>, S>::value, "Should be a base of AbstractState.");
    m_stateMachine.template registerState<S>();
}

template<typename T, typename E>
template<typename S, typename... Args>
void Application<T, E>::registerSystem(const String &name, Args... args)
{
    static_assert(is_base_of<ISystem<StateData<T>>, S>::value, "Should be a base of ISystem.");
    m_stateMachine.template registerSystem<S>(name, args...);
}

template<typename T, typename E>
template<typename S>
void Application<T, E>::registerSystem(const String &name)
{
    static_assert(is_base_of<ISystem<StateData<T>>, S>::value, "Should be a base of ISystem.");
    m_stateMachine.template registerSystem<S>(name);
}


template<typename T, typename E>
void Application<T, E>::registerComponent(ComponentSchema schema)
{
    m_world.registerComponent(move(schema));
}

template <typename T, typename E>
void Application<T, E>::handleTransition(StateData<T> stateData)
{
    while (m_transitions.size() > 0 && m_stateMachine.m_running) {
        m_stateMachine.transition(move(m_transitions.back()), stateData);
        m_transitions.pop_back();
    }
}

template <typename T, typename E>
void ecs::Application<T, E>::withBundle(Bundle& bundle)
{
    bundle.load(m_world, m_eventHandler);
}

template <typename T, typename E>
template <typename B, typename... Args>
void Application<T, E>::withBundle(Args&&... args)
{
    static_assert(is_base_of<Bundle, B>::value, "Should be a base of Bundle.");
    B instance(forward<Args>(args)...);
    this->withBundle(instance);
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
