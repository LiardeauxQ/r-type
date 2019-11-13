//
// Created by Quentin Liardeaux on 11/12/19.
//

#include "GeometryObject.hpp"

Point::Point(double x, double y)
    : m_x(x)
    , m_y(y) {}

double Point::computeSlope(const Point &other) const {
    return (other.m_y - m_y / other.m_x - m_x);
}

Point Point::rotateBy(double angle) const {
    return Point(m_x * cos(angle) - m_y * sin(angle),
                 m_x * sin(angle) + m_y * cos(angle));
}

double Point::norm() const {
    return sqrt(pow(m_x, 2) + pow(m_y, 2));
}

double Point::dotProduct(const Point &other) const {
    return (m_x * other.m_x) + (m_y * other.m_y);
}

double Point::scalarProjection(const Point &other) const {
    return dotProduct(other) / norm();
}

Point Point::projectVectorOn(const Point &other) const {
    double k = scalarProjection(other);

    return Point(k * m_x, k * m_y);
}

bool Point::operator>(Point const &other) {
    return (m_x > other.m_x && m_y > other.m_y);
}

bool Point::operator<(Point const &other) {
    return (m_x < other.m_x && m_y < other.m_y);
}

Point Point::operator*(double coefficent) {
    return Point(coefficent * m_x, coefficent * m_y);
}