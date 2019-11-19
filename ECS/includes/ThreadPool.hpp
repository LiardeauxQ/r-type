//
// Created by alex on 11/15/19.
//

#ifndef R_TYPE_THREADPOOL_HPP
#define R_TYPE_THREADPOOL_HPP

#include "Definitions.hpp"
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <thread>

template <typename Resources, typename E>
class ThreadPool {
public:
    explicit ThreadPool(shared_ptr<Resources> res, uint32_t nbThread = thread::hardware_concurrency());
    ~ThreadPool();

    future<E> enqueueWork(function<E(shared_ptr<Resources>)> work);
    uint32_t m_nbThread;
private:
    deque<function<E(shared_ptr<Resources>)>> m_works;
    shared_ptr<Resources> m_sharedData;
    vector<thread> m_threads;
    mutex m_worksLock;
    bool m_isRunning;
};

template <typename Resources, typename E>
ThreadPool<Resources, E>::ThreadPool(shared_ptr<Resources> res, uint32_t nbThread)
    : m_nbThread(nbThread)
    , m_works()
    , m_sharedData(res)
    , m_threads()
    , m_worksLock()
    , m_isRunning(true)
{
    auto worker = [&]() {
        size_t size = 0;
        function<E(shared_ptr<Resources>)> f = nullptr;
        {
            lock_guard<mutex> lock(m_worksLock);
            size = m_works.size();
        }
        while (m_isRunning || size != 0) {
            {
                lock_guard<mutex> lock(m_worksLock);
                size = m_works.size();
                if (size != 0) {
                    f = m_works.back();
                    m_works.pop_back();
                }
            }
            if (f)
                f(m_sharedData);
        }
    };

    for(unsigned int i = 0; i < nbThread; ++i)
        m_threads.push_back(thread(worker));
}

template <typename T, typename E>
ThreadPool<T, E>::~ThreadPool()
{
    m_isRunning = false;
    for (auto& t: m_threads)
        t.join();
}

template <typename T, typename E>
future<E> ThreadPool<T, E>::enqueueWork(function<E(shared_ptr<T>)> work)
{
    lock_guard<mutex> lock(m_worksLock);
    m_works.push_front(work);
    return future<E>();
}

#endif //R_TYPE_THREADPOOL_HPP
