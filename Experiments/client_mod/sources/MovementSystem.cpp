//
// Created by alex on 11/21/19.
//

#include "MovementSystem.hpp"

ecs::EntityRequest MovementSystem::getDependencies() const
{
    return ecs::EntityRequest({}, {});
}

any MovementSystem::operator()(any entities, shared_ptr<ecs::StateData<string>> data)
{
    auto s = data->world.fetchResource<sf::Sprite *>("shipSprite");
    auto pos = s->getPosition();
    s->move(static_cast<float>(data->delta) * 10, 0);
    cout << "Movement: " << this_thread::get_id() << endl;
}

Box<IFactorizable<String>> MovementSystem::copy() const
{
    return static_unique_pointer_cast<IFactorizable<String>>(std::make_unique<MovementSystem>());
}

String MovementSystem::getKey() const
{
    return String("base::MovementSystem");
}
