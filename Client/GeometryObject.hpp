//
// Created by Quentin Liardeaux on 11/10/19.
//

#ifndef R_TYPE_SERVER_GEOMETRYOBJECT_HPP
#define R_TYPE_SERVER_GEOMETRYOBJECT_HPP

#include <cmath>

class Point {
public:
    Point(double x, double y);

    [[nodiscard]] double computeSlope(const Point &other) const;
    [[nodiscard]] double dotProduct(const Point &other) const;
    [[nodiscard]] Point rotateBy(double angle) const;
    [[nodiscard]] double norm() const;
    [[nodiscard]] double scalarProjection(const Point &other) const;
    [[nodiscard]] Point projectVectorOn(const Point &other) const;

    bool operator>(Point const &other);
    bool operator<(Point const &other);
    Point operator*(double coefficent);

    double m_x;
    double m_y;
};

struct Frame {
    double x;
    double y;
    double width;
    double height;
};

#endif //R_TYPE_SERVER_GEOMETRYOBJECT_HPP
