#include "GameWindow.h"

GameWindow::GameWindow(TDT4102::Point position, int width, int height, const std::string& title): 
    AnimationWindow{position.x, position.y, width, height, title},
    butt{TDT4102::Point{position.x + 100 ,200},btnSize,btnSize,std::string("MORENDIN")}

{
    int a = 0;
    add(butt);
}
