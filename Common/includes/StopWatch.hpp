//
// Created by alex on 11/20/19.
//

#ifndef R_TYPE_STOPWATCH_HPP
#define R_TYPE_STOPWATCH_HPP

#include <chrono>

using namespace std;

class StopWatch {
public:
    StopWatch() = default;
    ~StopWatch() = default;

    void start();
    void reset();
    double elapsed();
private:
    using timePoint = chrono::time_point<chrono::high_resolution_clock, chrono::duration<double>>;

    timePoint m_started;

};

#endif //R_TYPE_STOPWATCH_HPP
