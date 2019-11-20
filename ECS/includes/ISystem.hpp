//
// Created by nwmqpa on 11/20/19
//

#pragma once

#include <any>
#include "Definitions.hpp"
#include "EntityRequest.hpp"

namespace ecs {

    class ISystem {

        public:
            virtual ~ISystem() = default;
            virtual EntityRequest getDependencies() const = 0;
            virtual void operator()(std::any entities) = 0;

    };

}
