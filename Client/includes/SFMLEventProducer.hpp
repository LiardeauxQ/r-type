//
// Created by Quentin Liardeaux on 11/19/19.
//

#ifndef R_TYPE_SFMLEVENTPRODUCER_HPP
#define R_TYPE_SFMLEVENTPRODUCER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "EventHandler.hpp"

using namespace std;

class SFMLEventProducer : public AbstractEventProducer {
public:
    SFMLEventProducer(sf::RenderWindow& window);
    ~SFMLEventProducer() = default;

    vector<ecs::Event> fetchEvents() final;
private:
    sf::RenderWindow& m_window;
};

#endif //R_TYPE_SFMLEVENTPRODUCER_HPP
