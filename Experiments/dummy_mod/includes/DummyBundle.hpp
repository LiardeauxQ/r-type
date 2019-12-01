//
// Created by alex on 11/26/19.
//

#pragma once

#include "Bundle.hpp"

class DummyBundle : public ecs::Bundle {
public:
    DummyBundle() = default;
    ~DummyBundle() override = default;
    void load(ecs::World& m_world, EventHandler& handler) final;

};

