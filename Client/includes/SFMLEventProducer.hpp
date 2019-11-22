//
// Created by Quentin Liardeaux on 11/19/19.
//

#ifndef R_TYPE_SFMLEVENTPRODUCER_HPP
#define R_TYPE_SFMLEVENTPRODUCER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "AbstractEvent.hpp"
#include "Event.hpp"

using namespace std;

class SFMLEventProducer : public AbstractEventProducer {
public:
    SFMLEventProducer(shared_ptr<sf::RenderWindow> window);
    ~SFMLEventProducer() = default;

    vector<ecs::Event> fetchEvents() final;
private:
    shared_ptr<sf::RenderWindow> m_window;
};

#endif //R_TYPE_SFMLEVENTPRODUCER_HPP
