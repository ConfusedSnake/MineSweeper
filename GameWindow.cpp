#include "GameWindow.h"

GameWindow::GameWindow(TDT4102::Point position, int width, int height, const std::string& title, const Field& field): 
    AnimationWindow{position.x, position.y, width, height, title}
{
    drawGrid(*this, field);
}

void GameWindow::drawGrid(AnimationWindow& win, const Field& Field){
    for (int y = 0; y < Field.getH(); y++){
        for (int x = 0; x < Field.getW(); x++){

            TDT4102::Color color = TDT4102::Color::grey;
            TDT4102::Image numImage(numPic.at((*field.getField()[y])[x]));
            
            if ((*field.getField()[y])[x] == -1){
                color = TDT4102::Color::red;
                win.draw_rectangle(TDT4102::Point{x * cellSize, y * cellSize}, cellSize-2, cellSize-2, color);
            } else{
                color = TDT4102::Color::grey;
            }
            win.draw_rectangle(TDT4102::Point{x * cellSize, y * cellSize}, cellSize-2, cellSize-2, color);
            win.draw_image(TDT4102::Point{x * cellSize, y * cellSize}, numImage);
        }
    }
}

GameWindow::~GameWindow() {

}