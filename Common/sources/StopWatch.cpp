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
    return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - m_started).count();
}
