//
// Created by alex on 11/14/19.
//

#ifndef R_TYPE_DISPATCHER_HPP
#define R_TYPE_DISPATCHER_HPP

#include "Definitions.hpp"
#include "StateMachine.hpp"
#include "ThreadPool.hpp"
#include <iostream>
#include <queue>

namespace ecs {

typedef uint8_t System; // TODO implement System

template <typename T, typename E>
class Dispatcher {
public:
    explicit Dispatcher(ThreadPool<T, E>& pool);
    Dispatcher(Dispatcher&& dispatcher) noexcept;
    Dispatcher& operator=(Dispatcher&& dispatcher) noexcept;

    ~Dispatcher() = default;

    void dispatch(T& data);

private:
    ThreadPool<T, E>& m_pool;
    vector<System> m_systems;
};

template <typename T, typename E>
Dispatcher<T, E>::Dispatcher(Dispatcher&& dispatcher) noexcept
    : m_pool(dispatcher.m_pool)
    , m_systems(move(dispatcher.m_systems))
{
}

template <typename T, typename E>
Dispatcher<T, E>& Dispatcher<T, E>::operator=(Dispatcher&& dispatcher) noexcept
{
    m_systems.swap(dispatcher.m_systems);
    m_pool = dispatcher.m_pool;
    return *this;
}

template <typename T, typename E>
void Dispatcher<T, E>::dispatch(T& data)
{
    for (auto& s : m_systems) {
        // auto& fetchedData = m_world.fetch(s.getDependencies());
        // m_pool->enqueueWork([fetchedData, &s](StateData<T> data) -> E {
        //     s(world, fetchedData);
        // });
    }
}

template <typename T, typename E>
Dispatcher<T, E>::Dispatcher(ThreadPool<T, E>& pool)
    : m_pool(pool)
    , m_systems()
{
}

}

#endif //R_TYPE_DISPATCHER_HPP
