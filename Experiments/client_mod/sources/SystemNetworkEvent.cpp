//
// Created by alex on 11/26/19.
//

#include "SystemNetworkEvent.hpp"
#include <TcpListener.hpp>

ecs::EntityRequest SystemNetworkEvent::getDependencies() const
{
    return ecs::EntityRequest({}, {});
}

any SystemNetworkEvent::operator()(any entities, shared_ptr<ecs::StateData<string>> data)
{
    auto& listener = data->world.fetchResource<TcpListener>("listener");
    auto optStream = listener.acceptNonBlocking();

    if (optStream) {
        auto stream = optStream.value();
        cout << "new connection." << endl;
        stream.setNonBlocking();
        data->world.writeResource("Client", stream);
        // data->world.createEntity().with<Client>(stream);
    }
}

Box<IFactorizable<String>> SystemNetworkEvent::copy() const
{
    return static_unique_pointer_cast<IFactorizable<String>>(std::make_unique<SystemNetworkEvent>());
}

String SystemNetworkEvent::getKey() const
{
    return String("base::SystemNetworkEvent");
}
