//
// Created by Quentin Liardeaux on 11/14/19.
//

#ifndef R_TYPE_SPRITECHILD_HPP
#define R_TYPE_SPRITECHILD_HPP

#include <vector>
#include <memory>
#include <string>

#include "rapidjson/document.h"

#include "ParseError.hpp"
#include "Frame.hpp"

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
    SpriteChild(SpritePosition position);
    ~SpriteChild() = default;

    void addAnimation(Frame<int> frame);
    static shared_ptr<SpriteChild> fromJSONDocument(rapidjson::Value const &value, SpritePosition position);
    [[nodiscard]] const SpritePosition &getPosition() const { return m_position; }
    [[nodiscard]] const Frame<int> &getFrameForAnimationAtPos(size_t pos) const;
private:
    static Frame<int> createFrameFromRapidJsonValue(rapidjson::Value const &value);

    SpritePosition m_position;
    vector<Frame<int>> m_frames;
};

#endif //R_TYPE_SPRITECHILD_HPP
