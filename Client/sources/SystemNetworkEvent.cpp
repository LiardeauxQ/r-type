//
// Created by alex on 11/26/19.
//

#include "SystemNetworkEvent.hpp"
#include <TcpListener.hpp>

ecs::EntityRequest SystemNetworkEvent::getDependencies() const
{
    return ecs::EntityRequest({}, {});
}

void SystemNetworkEvent::operator()(any entities, shared_ptr<ecs::StateData<string>> data)
{
    auto& listener = data->world.fetchResource<TcpListener>("listener");
    auto optStream = listener.acceptNonBlocking();

    cout << "Network: " << this_thread::get_id() << endl;
    if (optStream) {
        auto stream = optStream.value();
        stream.setNonBlocking();
        // data->world.createEntity().with<Client>(stream);
    }
}
