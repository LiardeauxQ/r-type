//
// Created by Quentin Liardeaux on 11/10/19.
//

#include "OBBCollisionDetection.hpp"

OBBCollisionDetection::OBBCollisionDetection(const vector<Point> &points)
    : m_points(points) {}

tuple<Point, Point> OBBCollisionDetection::findMinMaxPoints(const Point &normalVector,
        const vector<Point> &object) const {
    Point max = normalVector.projectVectorOn(object[0]);
    Point min = max;

    for (size_t i = 1 ; i < object.size() ; i++) {
        Point projection = normalVector.projectVectorOn(object[i]);
        if (projection > max)
            max = projection;
        else if (projection < min)
            min = projection;
    }
    return tuple<Point, Point>(min, max);
}

bool OBBCollisionDetection::projectOn(const Point &normalVector,
                                      const vector<Point> &object1,
                                      const vector<Point> &object2) const {
    tuple<Point, Point> minMax1 = findMinMaxPoints(normalVector, object1);
    tuple<Point, Point> minMax2 = findMinMaxPoints(normalVector, object2);

    if (get<0>(minMax2).m_x > get<0>(minMax1).m_x
    || get<0>(minMax2).m_y > get<0>(minMax1).m_y)
        return true;
    else if (get<1>(minMax2).m_x < get<1>(minMax1).m_x
    || get<1>(minMax2).m_y < get<1>(minMax1).m_y)
        return true;
    return false;
}

bool OBBCollisionDetection::isCollidingWith(shared_ptr<CollisionDetection> object) const {
    auto pointsObject = dynamic_pointer_cast<OBBCollisionDetection>(object);
    size_t i = 0;

    while (i < m_points.size()) {
        double slope = m_points[i].computeSlope(m_points[(i + 1 == m_points.size() ? 0 : i + 1)]);
        Point normalVector = Point(1, slope).rotateBy(90);

        if (!projectOn(normalVector, m_points, pointsObject->m_points))
            return false;
        i++;
    }
    return true;
}