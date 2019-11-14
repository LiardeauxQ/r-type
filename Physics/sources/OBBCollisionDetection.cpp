//
// Created by Quentin Liardeaux on 11/10/19.
//

#include "OBBCollisionDetection.hpp"

#include <iostream>

OBBCollisionDetection::OBBCollisionDetection(const vector<Point> &points)
    : m_points(points) {}

tuple<Point, Point> OBBCollisionDetection::findMinMaxPoints(const Point &normalVector,
        const vector<Point> &object) const {
    Point max = normalVector.projectVectorOn(object[0]);
    Point min = max;

    for (size_t i = 1 ; i < object.size() ; i++) {
        Point projection = normalVector.projectVectorOn(object[i]);
        if (projection.m_x >= max.m_x)
            max = projection;
        else if (projection.m_x <= min.m_x)
            min = projection;
    }
    return tuple<Point, Point>(min, max);
}

bool OBBCollisionDetection::projectOn(const Point &normalVector,
                                      const vector<Point> &object1,
                                      const vector<Point> &object2) const {
    tuple<Point, Point> minMax1 = findMinMaxPoints(normalVector, object1);
    tuple<Point, Point> minMax2 = findMinMaxPoints(normalVector, object2);

    if (get<0>(minMax2).isXIn(minMax1)) {
        return true;
    } else if (get<1>(minMax2).isXIn(minMax1)) {
        return true;
    }
    if (normalVector.m_x == 0) {
        if (get<0>(minMax2).isYIn(minMax1))
            return true;
        else if (get<1>(minMax2).isYIn(minMax1))
            return true;
    }
    return false;
}

Point OBBCollisionDetection::handleNormalVectorComputationError(Point const &p1, Point const &p2) const
{
    try {
        double slope = p1.computeSlope(p2);
        return Point(1, slope).rotateBy(90.0);
    } catch (GeometryError const &e) {
        return Point(0, 1).rotateBy(90.0);
    }
}

bool OBBCollisionDetection::isCollidingWith(shared_ptr<CollisionDetection> object) const {
    auto pointsObject = dynamic_pointer_cast<OBBCollisionDetection>(object);
    size_t i = 0;

    while (i < m_points.size()) {
        Point normalVector = handleNormalVectorComputationError(m_points[i],
                m_points[(i + 1 == m_points.size() ? 0 : i + 1)]);

        if (!projectOn(normalVector, m_points, pointsObject->m_points))
            return false;
        i++;
    }
    return true;
}