//
// Created by Quentin Liardeaux on 11/14/19.
//

#ifndef R_TYPE_SPRITEFILE_HPP
#define R_TYPE_SPRITEFILE_HPP

#include <string>
#include <vector>
#include <memory>

#include "SpriteChild.hpp"

using namespace std;

class SpriteFile {
public:
    SpriteFile(string const &filename);
    ~SpriteFile() = default;
private:
    string m_filename;
    vector<unique_ptr<SpriteChild>> childs;
};

#endif //R_TYPE_SPRITEFILE_HPP
