/*
** EPITECH PROJECT, 2019
** test.c
** File description:
** Criterion
*/

#include <criterion/criterion.h>
#include "ThreadPool.hpp"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
#include <iostream>

Test(ThreadPool, creation) {
    struct Event {
        Event(string msg) : message(move(msg)) {};
        string message;
    };
    int i = 0;
    {
        ThreadPool<Event, void> pool(make_shared<Event>("test"));

        pool.enqueueWork([&i](shared_ptr<Event> e) {
            i += 1;
            std::cout << "1" << std::endl;
        });
        pool.enqueueWork([&i](shared_ptr<Event> e) {
            i += 1;
            std::cout << "2" << std::endl;
        });
        pool.enqueueWork([&i](shared_ptr<Event> e) {
            i += 1;
            std::cout << "3" << std::endl;
        });
    }
    cout << "Final: " << i << endl;
}

#pragma clang diagnostic pop