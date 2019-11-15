//
// Created by alex on 11/12/19.
//

#ifndef R_TYPE_ABSTRACTMIDDLEWARE_HPP
#define R_TYPE_ABSTRACTMIDDLEWARE_HPP

#include <unordered_map>

using namespace std;

class AbstractMiddleware {
    virtual void *operator()(void *data, size_t size);

    getParameter(const string& name, uint32_t value);
    setParameter(const string& name, uint32_t value);
private:
    map<string, uint32_t> parameters;
};

#endif //R_TYPE_ABSTRACTMIDDLEWARE_HPP
