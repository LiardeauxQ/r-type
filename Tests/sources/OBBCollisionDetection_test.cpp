//
// Created by Quentin Liardeaux on 11/13/19.
//

#include <criterion/criterion.h>
#include "OBBCollisionDetection.hpp"

Test(OBBCollisionDetection, same_object_collision_test)
{
    auto object1 = shared_ptr<OBBCollisionDetection>(new OBBCollisionDetection(vector<Point>{Point(1, 1), Point(1, 2), Point(2, 3)}));
    auto object2 = shared_ptr<OBBCollisionDetection>(new OBBCollisionDetection(vector<Point>{Point(1, 1), Point(1, 2), Point(2, 3)}));

    cr_assert(object1->isCollidingWith(object2));
    cr_assert(object2->isCollidingWith(object1));
}

Test(OBBCollisionDetection, no_collision_test)
{
    auto object1 = shared_ptr<OBBCollisionDetection>(new OBBCollisionDetection(vector<Point>{Point(1, 1), Point(1, 2), Point(2, 3)}));
    auto object2 = shared_ptr<OBBCollisionDetection>(new OBBCollisionDetection(vector<Point>{Point(4, 4), Point(4, 5), Point(6, 5)}));

    cr_assert(!object1->isCollidingWith(object2));
    cr_assert(!object2->isCollidingWith(object1));
}

Test(OBBCollisionDetection, common_point_collision_test)
{
    auto object1 = shared_ptr<OBBCollisionDetection>(new OBBCollisionDetection(vector<Point>{Point(1, 1), Point(1, 2), Point(2, 3)}));
    auto object2 = shared_ptr<OBBCollisionDetection>(new OBBCollisionDetection(vector<Point>{Point(2, 3), Point(4, 5), Point(6, 5)}));

    cr_assert(object1->isCollidingWith(object2));
    cr_assert(object2->isCollidingWith(object1));
}

Test(OBBCollisionDetection, close_object_collision_test)
{
    auto object1 = shared_ptr<OBBCollisionDetection>(new OBBCollisionDetection(vector<Point>{Point(1, 1), Point(1, 2), Point(2, 3)}));
    auto object2 = shared_ptr<OBBCollisionDetection>(new OBBCollisionDetection(vector<Point>{Point(2.1, 3), Point(4, 5), Point(6, 5)}));

    cr_assert(!object1->isCollidingWith(object2));
    cr_assert(!object2->isCollidingWith(object1));
}

Test(OBBCollisionDetection, close_top_object_collision_test)
{
    auto object1 = shared_ptr<OBBCollisionDetection>(new OBBCollisionDetection(vector<Point>{Point(1, 1), Point(1, 2), Point(2, 3)}));
    auto object2 = shared_ptr<OBBCollisionDetection>(new OBBCollisionDetection(vector<Point>{Point(0, 3.1), Point(4, 5), Point(6, 5)}));

    cr_assert(!object1->isCollidingWith(object2));
    cr_assert(!object2->isCollidingWith(object1));
}