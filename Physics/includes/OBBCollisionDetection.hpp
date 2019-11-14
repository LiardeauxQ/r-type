//
// Created by Quentin Liardeaux on 11/10/19.
//

#ifndef R_TYPE_SERVER_OBBCOLLISIONDETECTION_HPP
#define R_TYPE_SERVER_OBBCOLLISIONDETECTION_HPP

#include <vector>

#include "CollisionDetection.hpp"
#include "GeometryObject.hpp"

class OBBCollisionDetection: public CollisionDetection {
public:
    explicit OBBCollisionDetection(const vector<Point> &points);
    ~OBBCollisionDetection() final = default;

    [[nodiscard]] bool isCollidingWith(shared_ptr<CollisionDetection> object) const final;

    vector<Point> m_points;
private:
    [[nodiscard]] bool projectOn(const Point &normalVector,
            const vector<Point> &object1,
            const vector<Point> &object2) const;
    [[nodiscard]] tuple<Point, Point> findMinMaxPoints(const Point &normalVector,
            const vector<Point> &object) const;
    [[nodiscard]] Point handleNormalVectorComputationError(Point const &p1, Point const &p2) const;
};

#endif //R_TYPE_SERVER_OBBCOLLISIONDETECTION_HPP
