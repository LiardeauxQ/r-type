//
// Created by alex on 11/20/19.
//

#include "StopWatch.hpp"

void StopWatch::start()
{
    m_started = chrono::high_resolution_clock::now();
}

void StopWatch::reset()
{
    start();
}

double StopWatch::elapsed()
{
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - m_started).count();
    return static_cast<double>(elapsed) / 1000;
}
