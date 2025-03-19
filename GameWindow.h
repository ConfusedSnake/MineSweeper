#pragma once

#include "AnimationWindow.h"
#include "widgets/Button.h"


class GameWindow : public TDT4102::AnimationWindow
{
    private:
    
    static constexpr int pad = 10;
    static constexpr int btnSize = 100;

    public:

    GameWindow(TDT4102::Point position, int width, int height, const std::string& title);

    TDT4102::Button butt;

};