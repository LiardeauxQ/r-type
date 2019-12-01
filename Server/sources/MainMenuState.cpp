//
// Created by alex on 11/19/19.
//

#include "MainMenuState.hpp"
#include <TcpListener.hpp>

void MainMenuState::onStart(ecs::StateData<string>& data)
{
    data.world.writeResource<TcpListener>("listener", 1234);

    auto& listener = data.world.fetchResource<TcpListener>("listener");
    listener.setNonBlocking();
    listener.listen();
}

void MainMenuState::onStop(ecs::StateData<string>& data)
{
    cout << "Stopping Main Menu" << endl;
}

void MainMenuState::onPause(ecs::StateData<string>& data)
{
    cout << "Pausing Main Menu" << endl;
}

void MainMenuState::onResume(ecs::StateData<string>& data)
{
    cout << "Resuming Main Menu" << endl;
}

ecs::Transition<string, ecs::Event> MainMenuState::update(ecs::StateData<string>& data)
{
    m_dispatcher->dispatch(make_shared<ecs::StateData<string>>(data));
    return ecs::Transition<string, ecs::Event>();
}

ecs::Transition<string, ecs::Event> MainMenuState::handleEvent(ecs::StateData<string>& data, ecs::Event event)
{
    if (event.isOfType("sfml")) {
    }
    return ecs::Transition<string, ecs::Event>();
}

ecs::Transition<string, ecs::Event> MainMenuState::fixedUpdate(ecs::StateData<string>& data)
{
    cout << "Fixed update." << endl;
    return ecs::Transition<string, ecs::Event>();
}

void MainMenuState::shadowUpdate(ecs::StateData<string>& data)
{

}

void MainMenuState::shadowFixedUpdate(ecs::StateData<string>& data)
{
    cout << "Shadow fixed update." << endl;
}

MainMenuState::MainMenuState(unique_ptr<ecs::Dispatcher<ecs::StateData<string>, ecs::Error>> dispatcher)
    : AbstractState(move(dispatcher))
{
}

MainMenuState::MainMenuState()
    : AbstractState()
{
}

String MainMenuState::getKey() const
{
    return String("base::MainMenuState");
}

Box<IFactorizable<String>> MainMenuState::copy() const {
    std::cout << m_dispatcher->getSystemNames().at(0) << std::endl;
    return static_unique_pointer_cast<IFactorizable<String>>(
        std::make_unique<MainMenuState>(
            m_dispatcher->copy()
        )
    );
}
