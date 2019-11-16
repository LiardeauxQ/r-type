//
// Created by Quentin Liardeaux on 11/15/19.
//

#ifndef R_TYPE_FRAME_HPP
#define R_TYPE_FRAME_HPP

template <typename T>
class Frame {
public:
    Frame(T x, T y, T width, T height);
    ~Frame() = default;

    T m_x;
    T m_y;
    T m_width;
    T m_height;
};

#endif //R_TYPE_FRAME_HPP
