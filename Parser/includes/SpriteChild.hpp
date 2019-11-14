//
// Created by Quentin Liardeaux on 11/14/19.
//

#ifndef R_TYPE_SPRITECHILD_HPP
#define R_TYPE_SPRITECHILD_HPP

#include <vector>

#include "includes/SpriteFile.hpp"

using namespace std;

enum SpritePosition {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
    JUMP_LEFT,
    JUMP_RIGHT,
    FIRE_LEFT,
    FIRE_RIGHT
};

class SpriteChild {
public:
    SpriteChild(SpritePosition position, vector<int> const &points);
    ~SpriteChild() = default;
private:
    SpritePosition m_position;
    vector<int> m_points;
};


#endif //R_TYPE_SPRITECHILD_HPP
