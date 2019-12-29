//
// Created by Quentin Liardeaux on 12/29/19.
//

#include "Bullet.hpp"

void Bullet::update(float elapsedTime) {
    move(Direction::RIGHT, elapsedTime);
}