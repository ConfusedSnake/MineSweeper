#pragma once

#include "AnimationWindow.h"
#include "widgets/Button.h"


class GameWindow : public TDT4102::AnimationWindow
{
    private:
    static constexpr int pad = 10;
    static constexpr int btnSize = 30;
    std::vector<TDT4102::Button*> buttons;
    
    public:

    GameWindow(TDT4102::Point position, int width, int height, const std::string& title);
    void createButtons(int rows, int columns);
    ~GameWindow();

};