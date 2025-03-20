#include "GameWindow.h"

GameWindow::GameWindow(TDT4102::Point position, int width, int height, const std::string& title, const Field& field): 
    AnimationWindow{position.x, position.y, width, height, title}
{
    playerFieldVec.reserve(field.getH());
    for (int i = 0; i < field.getH(); i++) {
        playerFieldVec.push_back(std::make_unique<std::vector<int>>(field.getW(), 0));
    }


    drawGrid(*this, field);
    drawPlayerGrid(*this, field, playerFieldVec);
    
    while (!should_close()) {
        if (rightClick()) { 
            tileClick(field, playerFieldVec);
            drawGrid(*this, field); 
            drawPlayerGrid(*this, field, playerFieldVec);  
            next_frame(); 
        }
    }
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

void GameWindow::drawPlayerGrid(AnimationWindow& win, const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec) {
    for (int y = 0; y < field.getH(); y++) {
        for (int x = 0; x < field.getW(); x++) {
            if ((*playerFieldVec[y])[x] == 1) {
                continue;
            } else {
                win.draw_rectangle(TDT4102::Point{x * cellSize, y * cellSize}, cellSize - 2, cellSize - 2, TDT4102::Color::grey);
            }
        }
    }
}


bool GameWindow::leftClick(){
    return TDT4102::AnimationWindow::is_left_mouse_button_down();
}

bool GameWindow::rightClick(){
    return TDT4102::AnimationWindow::is_right_mouse_button_down();
}

TDT4102::Point GameWindow::coordinates(){
    return TDT4102::AnimationWindow::get_mouse_coordinates();
}

int GameWindow::clickY(const Field& field){
    int yIndex = coordinates().y / cellSize;
    if (coordinates().y < cellSize * field.getH()){
        return yIndex;
    }
    return -1;
}

int GameWindow::clickX(const Field& field){
    int xIndex = coordinates().x / cellSize;
    if (coordinates().x < cellSize * field.getW()){
        return xIndex;
    }
    return -1;
}

void GameWindow::tileClick(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec){
    if ((clickX(field) != -1 ) && clickY(field) != -1){
        if ((*playerFieldVec[clickY(field)])[clickX(field)] == 0){
            (*playerFieldVec[clickY(field)])[clickX(field)] = 1;
        }   
    }

}

