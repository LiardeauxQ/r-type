//
// Created by Quentin Liardeaux on 12/29/19.
//

#ifndef R_TYPE_POSITION_HPP
#define R_TYPE_POSITION_HPP

struct Position {
    Position(int x, int y)
            : m_x(x)
            , m_y(y) {}

    int m_x;
    int m_y;
};

#endif //R_TYPE_POSITION_HPP
