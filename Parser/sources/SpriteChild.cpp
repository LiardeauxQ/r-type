//
// Created by Quentin Liardeaux on 11/14/19.
//

#include "includes/SpriteChild.hpp"

#include <iostream>

SpriteChild::SpriteChild(SpritePosition position)
    : m_position(position)
    , m_frames() {}

void SpriteChild::addAnimation(Frame<int> frame) {
    m_frames.push_back(frame);
}

shared_ptr<SpriteChild> SpriteChild::fromJSONDocument(rapidjson::Value const &animation,
        SpritePosition position) {
    auto child = make_shared<SpriteChild>(position);

    if (!animation.IsArray())
        throw ParseError("Invalid data to parse");

    for (rapidjson::SizeType i = 0 ; i < animation.Size() ; i++)
        child->addAnimation(createFrameFromRapidJsonValue(animation[i]));
    return child;
}

Frame<int> SpriteChild::createFrameFromRapidJsonValue(rapidjson::Value const &value) {
    int x = value["x"].GetInt();
    int y = value["y"].GetInt();
    int width = value["width"].GetInt();
    int height = value["height"].GetInt();

    return Frame<int>(x, y, width, height);
}

const Frame<int> &SpriteChild::getFrameForAnimationAtPos(size_t pos) const {
    return m_frames.at(pos);
}