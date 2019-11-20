//
// Created by alex on 11/19/19.
//

#ifndef R_TYPE_MAINMENUSTATE_HPP
#define R_TYPE_MAINMENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include "AbstactState.hpp"

class MainMenuState: public ecs::AbstractState<string> {
public:
    MainMenuState() = default;
    ~MainMenuState() override = default;

    void onStart(ecs::StateData<string>& data) override;
    void onStop(ecs::StateData<string>& data) override;
    void onPause(ecs::StateData<string>& data) override;
    void onResume(ecs::StateData<string>& data) override;
    ecs::Transition<string> update(ecs::StateData<string>& data) override;
    ecs::Transition<string> handleEvent(ecs::StateData<string>& data) override;
    ecs::Transition<string> fixedUpdate(ecs::StateData<string>& data) override;
    void shadowUpdate(ecs::StateData<string>& data) override;
    void shadowFixedUpdate(ecs::StateData<string>& data) override;
};

#endif //R_TYPE_MAINMENUSTATE_HPP
