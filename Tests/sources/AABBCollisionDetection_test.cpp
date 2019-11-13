/*
** EPITECH PROJECT, 2019
** test.c
** File description:
** Criterion
*/

#include <criterion/criterion.h>
#include "includes/AABBCollisionDetection.hpp"

Test(AABBCollisionDetection, simple_valid_collision_test)
{
    auto object1 = shared_ptr<AABBCollisionDetection>(new AABBCollisionDetection({1, 1, 1, 1}));
    auto object2 = shared_ptr<AABBCollisionDetection>(new AABBCollisionDetection({1, 1, 1, 1}));

    cr_assert(object1->isCollidingWith(object2));
    cr_assert(object2->isCollidingWith(object1));
}

Test(AABBCollisionDetection, simple_nonvalid_collision_test)
{
    auto object1 = shared_ptr<AABBCollisionDetection>(new AABBCollisionDetection({1, 1, 1, 1}));
    auto object2 = shared_ptr<AABBCollisionDetection>(new AABBCollisionDetection({5, 5, 1, 1}));

    cr_assert(!object1->isCollidingWith(object2));
    cr_assert(!object2->isCollidingWith(object1));
}

Test(AABBCollisionDetection, bottom_right_valid_collision_test)
{
    auto object1 = shared_ptr<AABBCollisionDetection>(new AABBCollisionDetection({1, 1, 1, 1}));
    auto object2 = shared_ptr<AABBCollisionDetection>(new AABBCollisionDetection({1.5, 1.9, 1, 1}));

    cr_assert(object1->isCollidingWith(object2));
    cr_assert(object2->isCollidingWith(object1));
}

Test(AABBCollisionDetection, bottom_right_nonvalid_collision_test)
{
    auto object1 = shared_ptr<AABBCollisionDetection>(new AABBCollisionDetection({1, 1, 1, 1}));
    auto object2 = shared_ptr<AABBCollisionDetection>(new AABBCollisionDetection({2.1, 2.1, 1, 1}));

    cr_assert(!object1->isCollidingWith(object2));
    cr_assert(!object2->isCollidingWith(object1));
}
