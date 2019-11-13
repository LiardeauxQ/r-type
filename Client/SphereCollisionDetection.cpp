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
    Vector vector(abs(sphereObject->m_center.m_x - m_center.m_x),
            abs(sphereObject->m_center.m_y - m_center.m_y));
    double distance = sqrt(pow(vector.m_x, 2) + pow(vector.m_y, 2));

    return distance < sphereObject->m_radius + m_radius;
}