/*
** EPITECH PROJECT, 2019
** test.c
** File description:
** Criterion
*/

#include "Event.hpp"
#include "TestEvent.hpp"
#include <criterion/criterion.h>

Test(EventHandler, test_event_handler) {
    auto queue = make_shared<deque<unique_ptr<ecs::Event>>>();

    EventHandler handler(queue);

    auto producer = make_unique<TestEventProducer>();

    handler.addProducer(move(producer));
    handler.start();
    this_thread::sleep_for(1s);
    handler.stop();

    auto event = queue->front().get();

    cr_assert(event->isOfType("test"));
    cr_assert_eq(any_cast<int>(event->getValue()), 1);
}