//
// Created by alex on 11/21/19.
//

#include "DrawSystem.hpp"

ecs::EntityRequest DrawSystem::getDependencies() const
{
    return ecs::EntityRequest({}, {});
}

void DrawSystem::operator()(any entities, shared_ptr<ecs::StateData<string>> data)
{
    auto window = data->world.fetchResource<sf::RenderWindow *>("window");

    if (window->setActive(true)) {
        auto sprite = data->world.fetchResource<sf::Sprite *>("shipSprite");
        window->clear();
        window->draw(*sprite);
        window->display();
        window->setActive(false);
    }
}
