//
// Created by alex on 11/19/19.
//

#ifndef R_TYPE_MAINMENUSTATE_HPP
#define R_TYPE_MAINMENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include "AbstactState.hpp"

class MainMenuState: public AbstractState {
public:
    MainMenuState() = default;
    ~MainMenuState() override = default;

    void onStart() override;
    void onStop() override;
    void onPause() override;
    void onResume() override;
    Transition update() override;
    Transition handleEvent() override;

private:
    Transition fixedUpdate() override;
    void shadowUpdate() override;
    void shadowFixedUpdate() override;
};

#endif //R_TYPE_MAINMENUSTATE_HPP
