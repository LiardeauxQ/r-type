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

class SFMLEventProducer : public IEventProducer {
public:
    SFMLEventProducer(sf::RenderWindow& window, shared_ptr<deque<sf::Event>>);
    ~SFMLEventProducer() final = default;

    void pollEvents() final;
private:
    sf::RenderWindow& m_window;
    shared_ptr<deque<sf::Event>> m_events;
};

#endif //R_TYPE_SFMLEVENTPRODUCER_HPP
