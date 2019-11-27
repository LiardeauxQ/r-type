//
// Created by Quentin Liardeaux on 11/19/19.
//

#include "SFMLEventProducer.hpp"

#include <utility>

SFMLEventProducer::SFMLEventProducer(sf::RenderWindow& window, shared_ptr<deque<sf::Event>> queue)
    : m_window(window)
    , m_events(move(queue))
{
}

void SFMLEventProducer::pollEvents()
{
    sf::Event event;

    while (m_window.pollEvent(event))
        m_events->emplace_back(event);
}
