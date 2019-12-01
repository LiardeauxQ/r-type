//
// Created by alex on 11/26/19.
//

#ifndef R_TYPE_BUNDLE_HPP
#define R_TYPE_BUNDLE_HPP

#include "World.hpp"
#include "EventHandler.hpp"
#include "IEntityComponentStorage.hpp"

namespace ecs {

class Bundle {
public:
    virtual ~Bundle() = default;

    //virtual void configure(const string& path);

    virtual void load(World& m_world, EventHandler& handler) = 0;

    string m_name;
};

}

#endif //R_TYPE_BUNDLE_HPP
