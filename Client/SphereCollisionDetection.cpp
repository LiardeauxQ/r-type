//
// Created by Quentin Liardeaux on 11/7/19.
//

#include "SphereCollisionDetection.hpp"
#include <iostream>

SphereCollisionDetection::SphereCollisionDetection(double radius, const Point &center)
    : m_center(center)
    , m_radius(radius)
{}

bool SphereCollisionDetection::isCollidingWith(shared_ptr<CollisionDetection> object) const {
    auto sphereObject = dynamic_pointer_cast<SphereCollisionDetection>(object);
    Vector vector = {abs(sphereObject->m_center.x - m_center.x),
                     abs(sphereObject->m_center.y - m_center.y)};
    double distance = sqrt(pow(vector.x, 2) + pow(vector.y, 2));

    return distance < sphereObject->m_radius + m_radius;
}