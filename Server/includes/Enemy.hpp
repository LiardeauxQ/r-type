//
// Created by Quentin Liardeaux on 12/29/19.
//

#ifndef R_TYPE_ENEMY_HPP
#define R_TYPE_ENEMY_HPP

#include "Entity.hpp"

class Enemy: public Entity {
public:
    Enemy(size_t id, Position position, Position velocity)
    : Entity(id, position, velocity) {}
    ~Enemy() override = default;
};

#endif //R_TYPE_ENEMY_HPP
