//
// Created by Quentin Liardeaux on 11/14/19.
//

#include "ParseSprite.hpp"

ParseSprite::ParseSprite(string const &filename)
    : m_filename(filename)
{
    ifstream file(m_filename);

    file.seekg(0, std::ios::end);
    m_data.reserve(static_cast<unsigned long>(file.tellg()));
    file.seekg(0, std::ios::beg);
    m_data.assign((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
}
