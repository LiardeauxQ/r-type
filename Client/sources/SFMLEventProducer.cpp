//
// Created by Quentin Liardeaux on 11/19/19.
//

#include "includes/SFMLEventProducer.hpp"

SFMLEvent::SFMLEvent(sf::Event const &event)
    : Event("sfml", sf::Event(event)) {

}

SFMLEventProducer::SFMLEventProducer(shared_ptr<sf::RenderWindow> window)
    : m_window(move(window)) {

}

vector<unique_ptr<ecs::Event>> SFMLEventProducer::fetchEvents() {
    vector<unique_ptr<ecs::Event>> events;
    sf::Event event;

    while (m_window->pollEvent(event))
        events.push_back(make_unique<SFMLEvent>(event));
    return events;
}