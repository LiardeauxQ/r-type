/*
** EPITECH PROJECT, 2019
** test.c
** File description:
** Criterion
*/

#include "EventHandler.hpp"
#include <criterion/criterion.h>

Test(EventHandler, test_event_handler) {
    auto queue = make_shared<deque<ecs::Event>>();

    EventHandler handler(queue);

    auto producer = make_unique<TestEventProducer>();

    handler.addProducer(move(producer));
    handler.start();
    this_thread::sleep_for(1s);
    handler.stop();

    auto event = queue->front();

    cr_assert(event.isOfType("test"));
    cr_assert_eq(event.getValue<int>(), 1);
}
