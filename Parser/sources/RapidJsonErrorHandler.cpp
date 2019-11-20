//
// Created by Quentin Liardeaux on 11/18/19.
//

#include "RapidJsonErrorHandler.hpp"

const rapidjson::Value &RapidJsonErrorHandler::getValidValue(
        rapidjson::Value const &value, const string &id) {
    if (!value.HasMember(id.c_str()))
        throw ParseError("Member has not been found");
    return value[id.c_str()];
}