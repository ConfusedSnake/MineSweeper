#include "GameWindow.h"

GameWindow::GameWindow(TDT4102::Point position, int width, int height, const std::string& title): 
    AnimationWindow{position.x, position.y, width, height, title}
{
    playerFieldVec.reserve(field.getH());
    for (int i = 0; i < field.getH(); i++) {
        playerFieldVec.push_back(std::make_unique<std::vector<int>>(field.getW(), 0));
    }

    std:cout << field;

    for (const auto& [key, filename] : numPic) {
        images[key] = TDT4102::Image(filename);
    }

    drawGrid(*this, field);
    drawPlayerGrid(*this, field, playerFieldVec);
}

void GameWindow::run(){
    while (!should_close()) {
        drawGrid(*this, field);
        drawPlayerGrid(*this, field, playerFieldVec);

        if (mouseClicked()) { 
            tileClick(field, playerFieldVec);
        }
        else if (rightClick()){
            bombClick(field, playerFieldVec);
        }
        next_frame();
    }
}

void GameWindow::drawGrid(AnimationWindow& win, const Field& Field){
    TDT4102::Color color = TDT4102::Color::grey;

    for (int y = 0; y < Field.getH(); y++){
        for (int x = 0; x < Field.getW(); x++){
            if (images.count((*fieldData[y])[x])) {
                numImage = images.at((*fieldData[y])[x]);
            } else {
                numImage = images.at(0);
            }

            
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
            if ((*playerFieldVec[y])[x] == 0) {
                win.draw_rectangle(TDT4102::Point{x * cellSize, y * cellSize}, cellSize - 2, cellSize - 2, TDT4102::Color::grey);
            }
            else if ((*playerFieldVec[y])[x] == -1){
                win.draw_rectangle(TDT4102::Point{x * cellSize, y * cellSize}, cellSize - 2, cellSize - 2, TDT4102::Color::green);
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
    int x = clickX(field);
    int y = clickY(field);

    if (x != -1 && y != -1 && (*playerFieldVec[y])[x] == 0) {
        openUp(field, playerFieldVec, x, y);
    }

}

void GameWindow::openUp(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec, int x, int y){
    if ((*playerFieldVec[y])[x] == 1) {
        return; 
    }

    (*playerFieldVec[y])[x] = 1;

    if ((*fieldData[y])[x] == 0){
        for (int dy = -1; dy <= 1; ++dy) { 
            for (int dx = -1; dx <= 1; ++dx) { 
                if (dy == 0 && dx== 0){
                    continue;
                }

                int newY = y + dy;
                int newX = x + dx;

                if (newY >= 0 && newY < (field.getH()) && newX >= 0 && newX < (field.getW())) {
                    if (((*fieldData[newY])[newX] == 0) && ((*playerFieldVec[newY])[newX] == 0)) {
                        openUp(field, playerFieldVec, newX, newY);
                    }
                    (*playerFieldVec[newY])[newX] = 1; 

                }
            }
        } 
    }
    
}

bool GameWindow::mouseClicked() {
    static bool isButtonPressed = false;

    if (leftClick()) {
        if (!isButtonPressed) {
            isButtonPressed = true;  // Museknappen er trykket ned
            return false;  // Returner false til du slipper knappen
        }
    } else {
        if (isButtonPressed) {
            isButtonPressed = false;  // Museknappen er sluppet
            return true;  // Returner true når knappen er sluppet
        }
    }

    return false;  // Ingen endring i museknappens tilstand
}

void GameWindow::bombClick(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec){
    int x = clickX(field);
    int y = clickY(field);

    if (x != -1 && y != -1 && (*playerFieldVec[y])[x] == 0){
        (*playerFieldVec[y])[x] = -1;
    }
    else if (x != -1 && y != -1 && (*playerFieldVec[y])[x] == -1){
        (*playerFieldVec[y])[x] = 0;
    }
}
