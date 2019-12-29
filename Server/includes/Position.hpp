//
// Created by Quentin Liardeaux on 12/29/19.
//

#ifndef R_TYPE_POSITION_HPP
#define R_TYPE_POSITION_HPP

struct Position {
    Position(float x, float y)
            : m_x(x)
            , m_y(y) {}

    float m_x;
    float m_y;
};

#endif //R_TYPE_POSITION_HPP
