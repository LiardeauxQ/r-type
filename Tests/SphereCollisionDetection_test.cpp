//
// Created by Quentin Liardeaux on 11/7/19.
//

#include <criterion/criterion.h>
#include "SphereCollisionDetection.hpp"

Test(SphereCollisionDetection, simple_valid_collision_test)
{
    auto object1 = shared_ptr<SphereCollisionDetection>(new SphereCollisionDetection(1, {1, 1}));
    auto object2 = shared_ptr<SphereCollisionDetection>(new SphereCollisionDetection(1, {1, 1}));

    cr_assert(object1->isCollidingWith(object2));
    cr_assert(object2->isCollidingWith(object1));
}

Test(SphereCollisionDetection, simple_nonvalid_collision_test)
{
    auto object1 = shared_ptr<SphereCollisionDetection>(new SphereCollisionDetection(1, {1, 1}));
    auto object2 = shared_ptr<SphereCollisionDetection>(new SphereCollisionDetection(1, {3, 3}));

    cr_assert(!object1->isCollidingWith(object2));
    cr_assert(!object2->isCollidingWith(object1));
}

Test(SphereCollisionDetection, simple_nonvalid_collision_test2)
{
    auto object1 = shared_ptr<SphereCollisionDetection>(new SphereCollisionDetection(1, {1, 1}));
    auto object2 = shared_ptr<SphereCollisionDetection>(new SphereCollisionDetection(1, { 2.1, 2.1}));

    cr_assert(object1->isCollidingWith(object2));
    cr_assert(object2->isCollidingWith(object1));
}
