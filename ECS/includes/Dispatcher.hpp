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
#include <array>

namespace ecs {

template<typename T> class ISystem;

template <typename T, typename E>
class Dispatcher {
public:
    explicit Dispatcher();
    Dispatcher(Dispatcher&& dispatcher) noexcept;
    Dispatcher& operator=(Dispatcher&& dispatcher) noexcept;

    ~Dispatcher();

    void attachThreadPool(shared_ptr<ThreadPool<T, E>> pool);
    void dispatch(shared_ptr<T> data);

    template<typename S>
    void registerSystem();

    template<typename S, typename... Args>
    void registerSystem(Args... args);

    Box<Dispatcher<T, E>> copy() const;

    [[nodiscard]] vector<string> getSystemNames() const;


private:
    shared_ptr<ThreadPool<T, E>> m_pool;
    vector<unique_ptr<ISystem<T>>> m_systems;
    vector<bool> m_workersData;
    [[nodiscard]] uint32_t prepareDispatch(const vector<Entity>&) const;
};

template <typename T, typename E>
Dispatcher<T, E>::Dispatcher(Dispatcher&& dispatcher) noexcept
    : m_pool(move(dispatcher.m_pool))
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
uint32_t Dispatcher<T, E>::prepareDispatch(const vector<Entity>& entites) const
{
    uint32_t i = 0;

    while (true) {
        if (!m_workersData[i] /* workerData.conflict(fetchedData) */)
            return i;
        i++;
        i %= m_pool->m_nbThread;
    }
}

template <typename T, typename E>
void Dispatcher<T, E>::dispatch(shared_ptr<T> inputData)
{
    if (!m_pool)
        throw "Cannot dispatch without a ThreadPool attached.";
    for (auto& s : m_systems) {
        auto dependencies = s->getDependencies();
        vector<Entity> fetchedData = inputData->world.fetchStorage(move(dependencies));
        uint32_t index = this->prepareDispatch(fetchedData);
        m_workersData[index] = true;
        m_pool->enqueueWork([&s, this, index, fetched{ move(fetchedData) }](shared_ptr<T> data) -> E {
            (*s)(fetched, data);
            this->m_workersData[index] = false;
        }, inputData);
    }
}

template <typename T, typename E>
Dispatcher<T, E>::Dispatcher()
    : m_pool(nullptr)
    , m_systems()
    , m_workersData()
{
}

template <typename T, typename E>
template <typename S>
void Dispatcher<T, E>::registerSystem()
{
    static_assert(std::is_base_of<ecs::ISystem<T>, S>::value, "Dispatcher registered class need to be a ISystem.");
    static_assert(std::is_default_constructible<S>::value);
    m_systems.push_back(make_unique<S>());
}

template <typename T, typename E>
void Dispatcher<T, E>::attachThreadPool(shared_ptr<ThreadPool<T, E>> pool)
{
    m_workersData.reserve(pool->m_nbThread);
    for (uint32_t i = 0; i < pool->m_nbThread; ++i)
        m_workersData.push_back(false);
    m_pool = pool;
}
template <typename T, typename E>
template <typename S, typename... Args>
void Dispatcher<T, E>::registerSystem(Args... args)
{
    static_assert(std::is_base_of<ecs::ISystem<T>, S>::value, "Dispatcher registered class need to be a ISystem.");
    m_systems.push_back(make_unique<S>(forward<Args>(args)...));
}

template <typename T, typename E>
Dispatcher<T, E>::~Dispatcher()
{
    for (uint32_t i = 0; i < m_pool->m_nbThread; ++i)
        if (m_workersData[i]) {
            i--;
            continue;
        }
}

template <typename T, typename E>
Box<Dispatcher<T, E>> Dispatcher<T, E>::copy() const
{
    Box<Dispatcher<T, E>> dispatcher = std::make_unique<Dispatcher<T, E>>();
    std::cout << m_systems.size() << std::endl;
    for (const auto& system : m_systems) {
        dispatcher->m_systems.push_back(static_unique_pointer_cast<ISystem<T>>(move(system->copy())));
    }
    return dispatcher;
}


template <typename T, typename E>
vector<string> Dispatcher<T, E>::getSystemNames() const
{
    std::cout << m_systems.size() << std::endl;
    return vector<string>();
}

}

#endif //R_TYPE_DISPATCHER_HPP
