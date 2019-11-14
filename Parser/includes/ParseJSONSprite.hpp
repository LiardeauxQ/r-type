//
// Created by Quentin Liardeaux on 11/14/19.
//

#ifndef R_TYPE_PARSEJSONSPRITE_HPP
#define R_TYPE_PARSEJSONSPRITE_HPP

#include "ParseSprite.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class ParseJSONSprite: public ParseSprite {
public:
    ParseJSONSprite(string const &filename);
    ~ParseJSONSprite() {}
private:
    rapidjson::Document m_document;
};


#endif //R_TYPE_PARSEJSONSPRITE_HPP
