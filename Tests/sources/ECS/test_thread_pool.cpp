/*
** EPITECH PROJECT, 2019
** test.c
** File description:
** Criterion
*/

#include <criterion/criterion.h>
#include "ThreadPool.hpp"
#include <iostream>
#include <atomic>

using namespace std;
using namespace ecs;

struct Event {
    Event(string msg) : message(move(msg)) {};
    string message;
};

Test(ThreadPool, creation) {

    ThreadPool<Event, void> pool;
}

Test(ThreadPool, enqueue_100_works_4_thread) {
    atomic<int> print = 0;
    auto toto = make_shared<Event>("test");
    {
        ThreadPool<Event, void> pool(4);

        for (int i = 0; i < 100; i++) {
            pool.enqueueWork([&print](shared_ptr<Event> e) {
                print += 1;
            }, toto);
        }
    }
    cr_assert_eq(print, 100, "Should be 100, it's %d", print.load());
}

Test(ThreadPool, enqueue_100_works_1_thread) {
    atomic<int> print = 0;
    auto toto = make_shared<Event>("test");
    {
        ThreadPool<Event, void> pool(1);

        for (int i = 0; i < 100; i++) {
            pool.enqueueWork([&print](shared_ptr<Event> e) {
                print += 1;
            }, toto);
        }
    }
    cr_assert_eq(print, 100, "Should be 100, it's %d", print.load());
}

Test(ThreadPool, data_race_test_1) {
    atomic<int> add = 0;
    atomic<int> remove = 100;
    auto toto = make_shared<Event>("test");
    {
        ThreadPool<Event, void> pool(1);

        for (int i = 0; i < 100; i++) {
            pool.enqueueWork([&add, &remove](shared_ptr<Event> e) {
                add -= remove;
                add++;
                remove--;
                remove += add;
            }, toto);
        }
    }
    cr_assert_eq(101, add);
    cr_assert_eq(2, remove);
}