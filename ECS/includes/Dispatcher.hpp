//
// Created by alex on 11/14/19.
//

#ifndef R_TYPE_DISPATCHER_HPP
#define R_TYPE_DISPATCHER_HPP

#include "Definitions.hpp"
#include "StateMachine.hpp"
#include "ThreadPool.hpp"
#include "ISystem.hpp"
#include <iostream>
#include <queue>

namespace ecs {

template<typename T> class ISystem;

template <typename T, typename E>
class Dispatcher {
public:
    explicit Dispatcher(ThreadPool<T, E>& pool);
    Dispatcher(Dispatcher&& dispatcher) noexcept;
    Dispatcher& operator=(Dispatcher&& dispatcher) noexcept;

    ~Dispatcher() = default;

    void dispatch(shared_ptr<T> data);

    template<typename S>
    void registerSystem();

private:
    ThreadPool<T, E>& m_pool;
    vector<unique_ptr<ISystem<T>>> m_systems;
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
void Dispatcher<T, E>::dispatch(shared_ptr<T> inputData)
{
    for (auto& s : m_systems) {
        // auto& fetchedData = m_world.fetch(s.getDependencies());
        m_pool.enqueueWork([&s](shared_ptr<T> data) -> E {
            (*s)(1, data);
        }, inputData);
    }
}

template <typename T, typename E>
Dispatcher<T, E>::Dispatcher(ThreadPool<T, E>& pool)
    : m_pool(pool)
    , m_systems()
{
}

template <typename T, typename E>
template <typename S>
void Dispatcher<T, E>::registerSystem()
{
    static_assert(std::is_base_of<ecs::ISystem<T>, S>::value, "Dispatcher registered class need to be a ISystem.");
    m_systems.push_back(make_unique<S>());
}

}

#endif //R_TYPE_DISPATCHER_HPP
