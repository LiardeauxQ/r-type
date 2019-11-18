//
// Created by Quentin Liardeaux on 11/14/19.
//

#ifndef R_TYPE_PARSEJSONSPRITE_HPP
#define R_TYPE_PARSEJSONSPRITE_HPP

#include "ParseSprite.hpp"
#include "SpriteFile.hpp"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

class ParseJSONSprite {
public:
    static vector<shared_ptr<SpriteFile>> parse(string const &filename);
private:
    struct Parser {
        Parser(string const &filename);
        ~Parser() = default;

        rapidjson::Value &getSpritesFrom(string const &filename);
        void addSpriteFile(rapidjson::Value const &value);

        vector<shared_ptr<SpriteFile>> m_spriteFiles;
    };
};

#endif //R_TYPE_PARSEJSONSPRITE_HPP
