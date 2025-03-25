#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"

class Keybinds : public TDT4102::AnimationWindow{

    public:

    bool up();
    bool upClicked();
    bool down();
    bool downClicked();
    bool left();
    bool leftClicked();
    bool right();
    bool rightClicked();

};