//
// Created by Quentin Liardeaux on 11/14/19.
//

#ifndef R_TYPE_PARSEDENTITY_HPP
#define R_TYPE_PARSEDENTITY_HPP

#include <string>
#include <fstream>

using namespace std;

class ParseSprite {
public:
    ParseSprite(string const &filename);
    ~ParseSprite() = default;

    string const &getData() { return m_data; }
private:
    string m_filename;
    string m_data;
};

#endif //R_TYPE_PARSEDENTITY_HPP
