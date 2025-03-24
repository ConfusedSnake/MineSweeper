#include "GameWindow.h"

GameWindow::GameWindow(TDT4102::Point position, int width, int height, const std::string& title): 
    AnimationWindow{position.x, position.y, width, height, title},
    resetButton{TDT4102::Point {100, 650}, 100, 30, "Reset"}
{
    std::map<int, std::string> numPic{
        {-1, "Tall/bomb.png"},
        {0, "Tall/nothing.png"},
        {1, "Tall/one.png"}, 
        {2, "Tall/two.png"}, 
        {3, "Tall/three.png"}, 
        {4, "Tall/four.png"}, 
        {5, "Tall/five.png"}, 
        {6, "Tall/six.png"}, 
        {7, "Tall/seven.png"},
        {8, "Tall/eight.png"},
        {9, "Tall/flag.png"},
        {10, "gameArt/lightDirt.png"},
        {11, "gameArt/darkDirt.png"},
        {12, "gameArt/lightGrass.png"}
    };

    playerFieldVec.reserve(H);
    for (int i = 0; i < H; i++) {
        playerFieldVec.push_back(std::make_unique<std::vector<int>>(W, 0));
    }

    std:cout << field;

    for (const auto& [key, filename] : numPic) {
        images[key] = std::make_shared<TDT4102::Image>(filename);
    }

    //drawGrid(*this, field);
    //drawPlayerGrid(*this, playerFieldVec);
    resetButton.setCallback(std::bind(&GameWindow::callbackButton, this));
    add(resetButton);
}

void GameWindow::run() {
    while (!should_close()) {

        if(!field){
            drawPlayerGrid(*this, playerFieldVec);
            if (mouseClickedLeft() && clickX() != -1 && clickY() != -1) {
                field = std::make_unique<Field>(W, H, clickX(), clickY());
                tileClick(*field, playerFieldVec, dead);
                drawGrid(*this);
                drawPlayerGrid(*this, playerFieldVec);
            }
        } else {
            drawGrid(*this);
            if (!dead){
                drawPlayerGrid(*this, playerFieldVec);
            }
        
            if (mouseClickedLeft() && clickX() != -1 && clickY() != -1) { 
                tileClick(*field, playerFieldVec, dead);
            }
            else if (mouseClickedRight() && clickX() != -1 && clickY() != -1){
                flagRightClick(*field, playerFieldVec);
            }
        }

        draw_text(TDT4102::Point {200, 650}, to_string(bombCount) , TDT4102::Color::red, 45);
        next_frame();
    }
}


void GameWindow::drawGrid(AnimationWindow& win) {
    if (!field) return;

    TDT4102::Color color = TDT4102::Color::grey;

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {

            auto& imagePtr = images.count((*field->getField()[y])[x]) 
                ? images.at((*field->getField()[y])[x]) 
                : images.at(0);

            if ((*field->getField()[y])[x] == -1) {
                color = TDT4102::Color::red;
            } else if((*playerFieldVec[y])[x] == 1){
                color = TDT4102::Color::silver;
            }

            //win.draw_rectangle(TDT4102::Point{x * cellSize, y * cellSize}, cellSize-2, cellSize-2, color);
            win.draw_image(TDT4102::Point{x * cellSize, y * cellSize}, *images.at(10), cellSize, cellSize);
            win.draw_image(TDT4102::Point{x * cellSize, y * cellSize}, *imagePtr);
            //win.draw_text(TDT4102::Point {200, 650}, to_string(bombCount) , TDT4102::Color::red, 40);
        }
    }
}

void GameWindow::drawPlayerGrid(AnimationWindow& win, const std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec) {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if ((*playerFieldVec[y])[x] == 0) {
                //win.draw_rectangle(TDT4102::Point{x * cellSize, y * cellSize}, cellSize - 2, cellSize - 2, TDT4102::Color::grey);
                win.draw_image(TDT4102::Point{x * cellSize, y * cellSize}, *images.at(12), cellSize, cellSize);
            }
            else if ((*playerFieldVec[y])[x] == -1){
                //win.draw_rectangle(TDT4102::Point{x * cellSize, y * cellSize}, cellSize - 2, cellSize - 2, TDT4102::Color::grey);
                win.draw_image(TDT4102::Point{x * cellSize, y * cellSize}, *images.at(12), cellSize, cellSize);
                win.draw_image(TDT4102::Point{x * cellSize, y * cellSize}, *images.at(9));
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

bool GameWindow::mouseClickedLeft() {
    static bool isButtonPressed = false;

    if (leftClick()) {
        if (!isButtonPressed) {
            isButtonPressed = true; 
            return false; 
        }
    } else {
        if (isButtonPressed) {
            isButtonPressed = false; 
            return true;
        }
    }

    return false; 
}

bool GameWindow::mouseClickedRight() {
    static bool isButtonPressed = false;

    if (rightClick()) {
        if (!isButtonPressed) {
            isButtonPressed = true;  
            return false;  
        }
    } else {
        if (isButtonPressed) {
            isButtonPressed = false;  
            return true; 
        }
    }

    return false; 
}


TDT4102::Point GameWindow::coordinates(){
    return TDT4102::AnimationWindow::get_mouse_coordinates();
}

int GameWindow::clickY(){
    int yIndex = coordinates().y / cellSize;
    if (coordinates().y < cellSize * H){
        return yIndex;
    }
    return -1;
}

int GameWindow::clickX(){
    int xIndex = coordinates().x / cellSize;
    if (coordinates().x < cellSize * W){
        return xIndex;
    }
    return -1;
}


void GameWindow::tileClick(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec, bool& dead){
    int x = clickX();
    int y = clickY();

    if((*field.getField()[y])[x] == -1){
        dead = true;
    }

    if (x != -1 && y != -1 && (*playerFieldVec[y])[x] == 0) {
        openUp(field, playerFieldVec, x, y);
    }


}

void GameWindow::openUp(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec, int x, int y){
    if ((*playerFieldVec[y])[x] == 1) {
        return; 
    }

    (*playerFieldVec[y])[x] = 1;

    if ((*field.getField()[y])[x] == 0){
        for (int dy = -1; dy <= 1; ++dy) { 
            for (int dx = -1; dx <= 1; ++dx) { 
                if (dy == 0 && dx== 0){
                    continue;
                }

                int newY = y + dy;
                int newX = x + dx;

                if (newY >= 0 && newY < (field.getH()) && newX >= 0 && newX < (field.getW())) {
                    if (((*field.getField()[newY])[newX] == 0) && ((*playerFieldVec[newY])[newX] == 0)) {
                        openUp(field, playerFieldVec, newX, newY);
                    }
                    (*playerFieldVec[newY])[newX] = 1; 

                }
            }
        } 
    }
    
}


void GameWindow::flagRightClick(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec){
    int x = clickX();
    int y = clickY();

    if (x != -1 && y != -1 && (*playerFieldVec[y])[x] == 0){
        (*playerFieldVec[y])[x] = -1;
        bombCount--;
    }
    else if (x != -1 && y != -1 && (*playerFieldVec[y])[x] == -1){
        (*playerFieldVec[y])[x] = 0;
        bombCount++;
    }
}


void GameWindow::callbackButton(){
    std::cout << "Reset button pressed\n";
    this->reset();
}

void GameWindow::reset(){
    playerFieldVec.clear();
    playerFieldVec.reserve(H);
    for (int i = 0; i < H; i++) {
        playerFieldVec.push_back(std::make_unique<std::vector<int>>(W, 0));
    }
    field.reset();

    dead = false;
    bombCount = 99;
}

void GameWindow::deathFreeze(){
    bool reset = false;
    while (!reset){
        if (true){
            reset = true;

        }
    }
}
