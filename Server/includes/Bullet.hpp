//
// Created by Quentin Liardeaux on 12/29/19.
//

#ifndef R_TYPE_BULLET_HPP
#define R_TYPE_BULLET_HPP

#include "Entity.hpp"

class Bullet: public Entity {
public:
    Bullet(size_t id, Position position, Position velocity)
            : Entity(id, position, velocity) {}
    ~Bullet() override = default;
};

#endif //R_TYPE_BULLET_HPP
