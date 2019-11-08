//
// Created by alex on 11/8/19.
//

#ifndef CPP_RTYPE_2019_DEFINITIONS_HPP
#define CPP_RTYPE_2019_DEFINITIONS_HPP

#include <memory>

template<typename  T>
using Box = std::unique_ptr<T>;

template<typename  T>
using Rc = std::shared_ptr<T>;

#endif //CPP_RTYPE_2019_DEFINITIONS_HPP
