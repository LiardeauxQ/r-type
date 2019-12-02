//
// Created by alex on 11/26/19.
//

#include "GraphicBundle.hpp"

void GraphicBundle::load(ecs::World& m_world, EventHandler& handler)
{
    m_world.writeResource<sf::RenderWindow *>("window", new sf::RenderWindow(sf::VideoMode(1920, 1080), m_windowName));

    auto eventQueue = make_shared<deque<sf::Event>>();
    auto& window = m_world.fetchResource<sf::RenderWindow *>("window");
    window->setFramerateLimit(30);
    window->setActive(false);
    handler.addProducer(unique_ptr<IEventProducer>(new SFMLEventProducer(*window, eventQueue)));
    m_world.writeResource<shared_ptr<deque<sf::Event>>>("sfEvents", eventQueue);
}

GraphicBundle::GraphicBundle(string windowName)
    : m_windowName { move(windowName) }
{
}
