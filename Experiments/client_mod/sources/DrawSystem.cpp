//
// Created by alex on 11/21/19.
//

#include "DrawSystem.hpp"

ecs::EntityRequest DrawSystem::getDependencies() const
{
    return ecs::EntityRequest({}, {});
}

any DrawSystem::operator()(any entities, shared_ptr<ecs::StateData<string>> data)
{
    auto window = data->world.fetchResource<sf::RenderWindow *>("window");
    auto& sfmlEventQueue = data->world.fetchResource<shared_ptr<deque<sf::Event>>>("sfEvents");
    auto& transitionQueue = data->world.fetchResource<deque<ecs::Transition<string, ecs::Event>> *>("transitionQueue");

    while (!sfmlEventQueue->empty()) {
        auto& event = sfmlEventQueue->back();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            transitionQueue->emplace_back(ecs::TransitionName::POP, nullptr);
        sfmlEventQueue->pop_back();
    }
    if (window->setActive(true)) {
        auto sprite = data->world.fetchResource<sf::Sprite *>("shipSprite");
        window->clear();
        window->draw(*sprite);
        window->display();
        window->setActive(false);
    }
}

Box<IFactorizable<String>> DrawSystem::copy() const
{
    return static_unique_pointer_cast<IFactorizable<String>>(std::make_unique<DrawSystem>());
}

String DrawSystem::getKey() const
{
    return String("base::DrawSystem");
}
