//
// Created by alex on 11/26/19.
//

#ifndef R_TYPE_GRAPHICBUNDLE_HPP
#define R_TYPE_GRAPHICBUNDLE_HPP

#include "Bundle.hpp"
#include <SFML/Graphics.hpp>
#include "SFMLEventProducer.hpp"

class GraphicBundle : public ecs::Bundle {
public:
    explicit GraphicBundle(string windowName);
    virtual ~GraphicBundle() = default;
    void load(ecs::World& m_world, EventHandler& handler) final;

private:
    string m_windowName;
};

#endif //R_TYPE_GRAPHICBUNDLE_HPP
