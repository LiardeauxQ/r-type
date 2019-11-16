//
// Created by Quentin Liardeaux on 11/15/19.
//

#include "Frame.hpp"

template<typename T>
Frame<T>::Frame(T x, T y, T width, T height)
    : m_x(x)
    , m_y(y)
    , m_width(width)
    , m_height(height)
{}
