//
// Created by Quentin Liardeaux on 11/19/19.
//

#ifndef R_TYPE_SFMLEVENTPRODUCER_HPP
#define R_TYPE_SFMLEVENTPRODUCER_HPP

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Event.hpp"
#include "AbstractEvent.hpp"

using namespace std;

class SFMLEvent: public ecs::AbstractEvent {
public:
    SFMLEvent(sf::Event const &event);
    ~SFMLEvent() = default;
};

class SFMLEventProducer: public AbstractEventProducer {
public:
    SFMLEventProducer(shared_ptr<sf::RenderWindow> window);
    ~SFMLEventProducer() = default;

    vector<unique_ptr<ecs::AbstractEvent>> fetchEvents() final;
private:
    shared_ptr<sf::RenderWindow> m_window;
};

#endif //R_TYPE_SFMLEVENTPRODUCER_HPP
