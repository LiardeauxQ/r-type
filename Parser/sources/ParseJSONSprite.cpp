//
// Created by Quentin Liardeaux on 11/14/19.
//

#include "ParseJSONSprite.hpp"

ParseJSONSprite::ParseJSONSprite(string const &filename)
    : ParseSprite(filename)
{
    m_document = rapidjson::Document();
    m_document.Parse(m_data.c_str());
}