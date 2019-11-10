//
// Created by Quentin Liardeaux on 11/7/19.
//

#ifndef R_TYPE_SERVER_SPHERECOLLISIONDETECTION_HPP
#define R_TYPE_SERVER_SPHERECOLLISIONDETECTION_HPP

#include <math.h>
#include "CollisionDetection.hpp"

struct Point {
    double x;
    double y;
};

typedef Point Vector;

class SphereCollisionDetection: public CollisionDetection {
public:
    explicit SphereCollisionDetection(double radius, const Point &center);
    ~SphereCollisionDetection() final = default;

    [[nodiscard]] bool isCollidingWith(shared_ptr<CollisionDetection> object) const final;

    [[nodiscard]] double getRadius() const { return m_radius; }

    Point m_center;
private:
    double m_radius;
};

#endif //R_TYPE_SERVER_SPHERECOLLISIONDETECTION_HPP
