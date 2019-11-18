//
// Created by Quentin Liardeaux on 11/14/19.
//

#include "SpriteFile.hpp"

#include <iostream>

static const vector<tuple<string, SpritePosition>> idMovements = {
        make_tuple("right", SpritePosition::RIGHT),
        make_tuple("left", SpritePosition::LEFT),
        make_tuple("bottom", SpritePosition::BOTTOM),
        make_tuple("top", SpritePosition::TOP),
        make_tuple("jump_left", SpritePosition::JUMP_LEFT),
        make_tuple("jump_right", SpritePosition::JUMP_RIGHT),
        make_tuple("fire_left", SpritePosition::FIRE_LEFT),
        make_tuple("fire_right", SpritePosition::FIRE_RIGHT),
};

SpriteFile::SpriteFile(rapidjson::Value const &sprite) {
    fetchSprite(sprite);
}

void SpriteFile::fetchSprite(rapidjson::Value const &sprite) {
    const rapidjson::Value &name = RapidJsonErrorHandler::getValidValue(sprite, "name");
    const rapidjson::Value &filename = RapidJsonErrorHandler::getValidValue(sprite, "filename");
    const rapidjson::Value &movements = RapidJsonErrorHandler::getValidValue(sprite, "movements");

    m_filename = filename.GetString();
    m_name = name.GetString();
    for (const auto & idMovement : idMovements)
        addChild(movements, get<0>(idMovement).c_str(), get<1>(idMovement));
}

void SpriteFile::addChild(rapidjson::Value const &movements, char const *namePos, SpritePosition pos) {
    if (!movements.HasMember(namePos))
        throw ParseError("Invalid name member");
    m_childs.push_back(SpriteChild::fromJSONDocument(movements[namePos], pos));
}

shared_ptr<SpriteChild> SpriteFile::getChildWithPosition(SpritePosition pos) {
    for (auto child : m_childs) {
        if (child->getPosition() == pos)
            return child;
    }
    throw ParseError("No position for this sprite");
}
