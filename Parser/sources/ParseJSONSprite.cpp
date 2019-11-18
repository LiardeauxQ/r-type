//
// Created by Quentin Liardeaux on 11/14/19.
//

#include "ParseJSONSprite.hpp"

#include <iostream>

vector<shared_ptr<SpriteFile>> ParseJSONSprite::parse(string const &filename) {
    Parser parser(filename);

    return parser.m_spriteFiles;
}

ParseJSONSprite::Parser::Parser(string const &filename)
    : m_spriteFiles() {
    rapidjson::Value &sprites = getSpritesFrom(filename);

    if (!sprites.IsArray())
        throw ParseError("Invalid data");
    for (rapidjson::SizeType i = 0 ; i < sprites.Size() ; i++) {
        addSpriteFile(sprites[i]);
    }
}

rapidjson::Value &ParseJSONSprite::Parser::getSpritesFrom(string const &filename) {
    rapidjson::Document document = rapidjson::Document();

    document.Parse(ParseSprite(filename).getData().c_str());
    if (document.HasParseError() || !document.HasMember("sprites"))
        throw ParseError("Invalid file");
    return document["sprites"];
}

void ParseJSONSprite::Parser::addSpriteFile(rapidjson::Value const &value) {
    try {
        m_spriteFiles.push_back(make_shared<SpriteFile>(value));
    } catch (ParseError &e) {}
}

