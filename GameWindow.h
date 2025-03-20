#pragma once
#include "AnimationWindow.h"
#include "widgets/Button.h"
#include "mineField.h"


class GameWindow : public TDT4102::AnimationWindow
{
    private:
    static constexpr int cellSize = 30;
    Field field;
    
    public:

    GameWindow(TDT4102::Point position, int width, int height, const std::string& title, const Field& field);
    void drawGrid(AnimationWindow& win, const Field& Field);
    ~GameWindow();

};