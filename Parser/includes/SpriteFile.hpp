//
// Created by Quentin Liardeaux on 11/14/19.
//

#ifndef R_TYPE_SPRITEFILE_HPP
#define R_TYPE_SPRITEFILE_HPP

#include <string>
#include <vector>
#include <memory>
#include <tuple>

#include "SpriteChild.hpp"
#include "ParseError.hpp"
#include "RapidJsonErrorHandler.hpp"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

using namespace std;

class SpriteFile {
public:
    SpriteFile(rapidjson::Value const &sprite);
    ~SpriteFile() = default;

    [[nodiscard]] const string &getFilename() const { return m_filename; }
    [[nodiscard]] const string &getName() const { return m_name; }
    shared_ptr<SpriteChild> getChildWithPosition(SpritePosition pos);
private:
    void fetchSprite(rapidjson::Value const &sprite);
    void addChild(rapidjson::Value const &movements, char const *namePos, SpritePosition pos);

    string m_filename;
    string m_name;
    vector<shared_ptr<SpriteChild>> m_childs;
};

#endif //R_TYPE_SPRITEFILE_HPP
