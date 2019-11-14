//
// Created by Quentin Liardeaux on 11/10/19.
//

#ifndef R_TYPE_SERVER_GEOMETRYOBJECT_HPP
#define R_TYPE_SERVER_GEOMETRYOBJECT_HPP

#include <cmath>
#include <string>
#include <exception>
#include <ostream>

#define PI 3.14159265
#define RAD 180
#define MIN_PRECISION 0.0000001

using namespace std;

class Point {
public:
    Point(double x, double y);

    [[nodiscard]] double computeSlope(const Point &other) const;
    [[nodiscard]] double dotProduct(const Point &other) const;
    [[nodiscard]] Point rotateBy(double angle) const;
    [[nodiscard]] double norm() const;
    Point &floor(double precision);
    [[nodiscard]] double scalarProjection(const Point &other) const;
    [[nodiscard]] Point projectVectorOn(const Point &other) const;
    [[nodiscard]] bool isIn(tuple<Point, Point> const &interval) const;
    [[nodiscard]] bool isXIn(tuple<Point, Point> const &interval) const;
    [[nodiscard]] bool isYIn(tuple<Point, Point> const &interval) const;
    [[nodiscard]] bool areSame(double a, double b) const;

    bool operator>(Point const &other);
    bool operator>=(Point const &other);
    bool operator<(Point const &other);
    bool operator<=(Point const &other);
    Point operator*(double coefficent);

    double m_x;
    double m_y;
};

ostream &operator<<(ostream &out, Point const &point);

struct Frame {
    double x;
    double y;
    double width;
    double height;
};

class GeometryError: public exception {
public:
    GeometryError(string const &msg) : m_msg(msg) {};
    ~GeometryError() = default;

    virtual const char *what() const noexcept { return m_msg.c_str(); }
private:
    string m_msg;
};

#endif //R_TYPE_SERVER_GEOMETRYOBJECT_HPP
