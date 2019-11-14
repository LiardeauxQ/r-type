//
// Created by Quentin Liardeaux on 11/12/19.
//

#include "GeometryObject.hpp"

#include <iostream>

Point::Point(double x, double y)
    : m_x(x)
    , m_y(y) {}

double Point::computeSlope(const Point &other) const {
    if (other.m_x - m_x == 0)
        throw GeometryError("Invalid division by zero");
    return (other.m_y - m_y / other.m_x - m_x);
}

Point Point::rotateBy(double angle) const {
    double x = m_x * cos(angle * PI / RAD) - m_y * sin(angle * PI / RAD);
    double y = m_x * sin(angle * PI / RAD) + m_y * cos(angle * PI / RAD);

    return Point(x, y).floor(MIN_PRECISION);
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

    return Point(k * m_x, k * m_y).floor(MIN_PRECISION);
}

Point &Point::floor(double precision) {
    m_x = m_x < precision && m_x > - precision ? 0 : m_x;
    m_y = m_y < precision && m_y > - precision ? 0 : m_y;
    return *this;
}

bool Point::areSame(double a, double b) const {
    return fabs(a - b) < MIN_PRECISION;
}

bool Point::isIn(tuple<Point, Point> const &interval) const {
    double x0 = get<0>(interval).m_x;
    double x1 = get<1>(interval).m_x;
    double y0 = get<0>(interval).m_y;
    double y1 = get<1>(interval).m_y;

    return ((m_x > x0 || areSame(m_x, x0)) && (m_x < x1 || areSame(m_x, x1))
    && (m_y > y0 || areSame(m_y, y0)) && (m_y < y1 || areSame(m_y, y1)));
}

bool Point::isXIn(tuple<Point, Point> const &interval) const {
    double x0 = get<0>(interval).m_x;
    double x1 = get<1>(interval).m_x;

    return (m_x > x0 || areSame(m_x, x0)) && (m_x < x1 || areSame(m_x, x1));
}

bool Point::isYIn(tuple<Point, Point> const &interval) const {
    double y0 = get<0>(interval).m_y;
    double y1 = get<1>(interval).m_y;

    return (m_y > y0 || areSame(m_y, y0)) && (m_y < y1 || areSame(m_y, y1));
}

bool Point::operator>(Point const &other) {
    return (m_x > other.m_x && m_y > other.m_y);
}

bool Point::operator>=(Point const &other) {
    return (m_x >= other.m_x && m_y >= other.m_y);
}

bool Point::operator<(Point const &other) {
    return (m_x < other.m_x && m_y < other.m_y);
}

bool Point::operator<=(Point const &other) {
    return (m_x <= other.m_x && m_y <= other.m_y);
}

Point Point::operator*(double coefficent) {
    return Point(coefficent * m_x, coefficent * m_y);
}

ostream &operator<<(ostream &out, Point const &point) {
    out << "Point(x:" << point.m_x << ";" << point.m_y << ")";
    return out;
}