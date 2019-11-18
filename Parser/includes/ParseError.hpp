//
// Created by Quentin Liardeaux on 11/18/19.
//

#ifndef R_TYPE_PARSEERROR_HPP
#define R_TYPE_PARSEERROR_HPP

#include <exception>
#include <string>

using namespace std;

class ParseError: public exception {
public:
    ParseError(string const &msg) : m_msg(msg) {}
    ~ParseError() noexcept = default;

    virtual const char *what() const noexcept { return m_msg.c_str(); }
private:
    string m_msg;
};

#endif //R_TYPE_PARSEERROR_HPP
