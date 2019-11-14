//
// Created by nwmqpa on 12/11/2019
//

#pragma once

#include "Definitions.hpp"

template<typename T>
class IFactorizable {
    public:
        virtual ~IFactorizable() = default;
        virtual Box<IFactorizable> copy() const = 0;
        virtual T getKey() const = 0;
};
