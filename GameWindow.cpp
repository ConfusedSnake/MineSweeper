#include "GameWindow.h"

GameWindow::GameWindow(TDT4102::Point position, int width, int height, const std::string& title): 
    AnimationWindow{position.x, position.y, width, height, title}
{
    createButtons(16,30);
}

void GameWindow::createButtons(int rows, int columns){
    int spacing = 10;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            int xpos = x * (btnSize + spacing);
            int ypos = y * (btnSize + spacing);
            auto btn = new TDT4102::Button{TDT4102::Point{xpos, ypos}, btnSize, btnSize, "Knapp"};
            buttons.push_back(btn);
            add(*btn);
            }
        }
    }

GameWindow::~GameWindow() {
    for (auto btn : buttons) {
        delete btn;
    }
}