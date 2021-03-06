//
// Created by Quentin Liardeaux on 11/7/19.
//

#ifndef R_TYPE_SERVER_COLLISIONDETECTION_HPP
#define R_TYPE_SERVER_COLLISIONDETECTION_HPP

#include <memory>

using namespace std;

class CollisionDetection {
public:
    virtual ~CollisionDetection() {};

    virtual bool isCollidingWith(shared_ptr<CollisionDetection> object) const = 0;
};

#endif //R_TYPE_SERVER_COLLISIONDETECTION_HPP
