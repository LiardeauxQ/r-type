//
// Created by alex on 11/24/19.
//

#ifndef R_TYPE_TRANSFORM_HPP
#define R_TYPE_TRANSFORM_HPP

#include <Component.hpp>

class Transform : public ecs::Component {
public:
    explicit Transform(float x = 0, float y = 0)
        : Component("Transform")
        , m_x(x)
        , m_y(y)
    {}

    float m_x;
    float m_y;
};

#endif //R_TYPE_TRANSFORM_HPP
