//
// Created by Quentin Liardeaux on 11/19/19.
//

#include "includes/SFMLEventProducer.hpp"

SFMLEventProducer::SFMLEventProducer(sf::RenderWindow& window)
    : m_window(window)
{

}

vector<ecs::Event> SFMLEventProducer::fetchEvents()
{
    vector<ecs::Event> events;
    sf::Event event;

    while (m_window.pollEvent(event))
        events.emplace_back("sfml", event);
    return events;
}
