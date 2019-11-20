//
// Created by alex on 11/20/19.
//

#include "StopWatch.hpp"
#include <criterion/criterion.h>
#include <thread>
#include <iostream>

using namespace std;

Test(StopWatch, basic) {
    StopWatch timer;

    timer.start();
    this_thread::sleep_for(chrono::duration(chrono::milliseconds(20)));
    double one = timer.elapsed();
    this_thread::sleep_for(chrono::duration(chrono::milliseconds(20)));
    double two = timer.elapsed();
    timer.reset();
    this_thread::sleep_for(chrono::duration(chrono::milliseconds(20)));
    double three = timer.elapsed();

    cr_assert(one < two, "%f should be inferior a %f.", one, two);
    cr_assert(two > three, "%f should be inferior a %f.", three, two);
}

Test(StopWatch, deltaTime) {
    StopWatch timer;
    StopWatch deltaTimer;
    vector<int64_t> elapsedTimes;

    timer.start();
    while (timer.elapsed() < 1000) {
        deltaTimer.start();
        this_thread::sleep_for(chrono::duration(chrono::milliseconds(1000)));
        elapsedTimes.push_back(deltaTimer.elapsed());
    }
    int64_t mean = 0;
    for (int64_t e : elapsedTimes)
        mean += e;
    static_cast<unsigned long>(mean) / elapsedTimes.size();
    cr_assert_eq(static_cast<int>(mean), 1000);
}