//
// Created by Quentin Liardeaux on 11/18/19.
//

#ifndef R_TYPE_RAPIDJSONERRORHANDLER_HPP
#define R_TYPE_RAPIDJSONERRORHANDLER_HPP

#include <string>

#include "ParseError.hpp"

#include "rapidjson/document.h"

class RapidJsonErrorHandler {
public:
    static const rapidjson::Value &getValidValue(rapidjson::Value const &value, const string &id);
};

#endif //R_TYPE_RAPIDJSONERRORHANDLER_HPP
