#include "GameWindow.h"

GameWindow::GameWindow(TDT4102::Point position, int width, int height, const std::string& title): 
    AnimationWindow{position.x, position.y, width, height, title},
    resetButton{TDT4102::Point {xOffset, yOffset - cellSize}, 100, 30, "Reset"}
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
        {9, "Tall/flag.png"}
    };

    std::map<std::string, std::string> imageMap {
        {"backgroundTop", "background3.png"},
        {"upDark", "arrowKeys/upDark.png"},
        {"upLight", "arrowKeys/upLight.png"},
        {"downDark", "arrowKeys/downDark.png"},
        {"downLight", "arrowKeys/downLight.png"},
        {"leftDark", "arrowKeys/leftDark.png"},
        {"leftLight", "arrowKeys/leftLight.png"},
        {"rightDark", "arrowKeys/rightDark.png"},
        {"rightLight", "arrowKeys/rightLight.png"}
    };

    playerFieldVec.reserve(H);
    for (int i = 0; i < H; i++) {
        playerFieldVec.push_back(std::make_unique<std::vector<int>>(W, 0));
    }
    std:cout << field;

    for (const auto& [key, filename] : numPic) {
        images[key] = std::make_unique<TDT4102::Image>(filename);
    }

    for (const auto& [key, filename] : imageMap) {
        pictures[key] = std::make_unique<TDT4102::Image>(filename);
    }


    resetButton.setCallback(std::bind(&GameWindow::callbackButton, this));
    add(resetButton);
}

void GameWindow::run() {
    while (!should_close()) {

        draw_image(TDT4102::Point{0,0}, *pictures.at("backgroundTop"));
        if(!field || !player){
            drawPlayerGrid(*this, playerFieldVec);
            draw_text(TDT4102::Point {720, xOffset-22}, to_string(static_cast<int>(0)) , TDT4102::Color::red, 45, Font::courier_bold);
            if ((mouseClickedLeft(*this) && clickX() != -1 && clickY() != -1)||(up(*this) || down(*this) || left(*this) || right(*this))) {
                field = std::make_unique<Field>(W, H, 0, 0);
                player = std::make_unique<Player>();

                tileClick(*field, playerFieldVec, dead);
                drawGrid(*this);
                drawPlayerGrid(*this, playerFieldVec);
                drawPlayer(*this);
                t.start();
            }
        } else {
            drawGrid(*this);
            if (!dead){
                drawPlayerGrid(*this, playerFieldVec);
                drawPlayer(*this);
                draw_text(TDT4102::Point {720, xOffset-22}, to_string(static_cast<int>(t.stop())) , TDT4102::Color::red, 45, Font::courier_bold);
                frozenTimer = t.stop();

                if(!spaceBar(*this)){
                    move();
                }
            }
            else {
                draw_text(TDT4102::Point {720, xOffset-22}, to_string(static_cast<int>(frozenTimer)) , TDT4102::Color::red, 45, Font::courier_bold);
            }

            if (mouseClickedLeft(*this) && clickX() != -1 && clickY() != -1 && (*playerFieldVec[clickY()])[clickX()] != -1) { 
                tileClick(*field, playerFieldVec, dead);
            }

            if (mouseClickedRight(*this) && clickX() != -1 && clickY() != -1){
                flagRightClick(*field, playerFieldVec);
            }

            if(spaceBar(*this)){
                flagSpaceMode();
            }

            if (keyRClicked(*this)){
                reset();
            }

            /*if (spaceBarClicked(*this)){
                flagSpace(*field, playerFieldVec);
            }*/
        }
        
        
        drawArrows(*this);
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
            } else {
                color = TDT4102::Color::grey;
            }

            win.draw_rectangle(TDT4102::Point{x * cellSize + xOffset, y * cellSize + yOffset}, cellSize-2, cellSize-2, color);
            win.draw_image(TDT4102::Point{x * cellSize + xOffset, y * cellSize + yOffset}, *imagePtr);
            //win.draw_text(TDT4102::Point {200, 650}, to_string(bombCount) , TDT4102::Color::red, 40);
        }
    }
}

void GameWindow::drawPlayerGrid(AnimationWindow& win, const std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec) {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if ((*playerFieldVec[y])[x] == 0) {
                win.draw_rectangle(TDT4102::Point{x * cellSize + xOffset, y * cellSize + yOffset}, cellSize - 2, cellSize - 2, TDT4102::Color::grey);
            }
            else if ((*playerFieldVec[y])[x] == -1){
                win.draw_rectangle(TDT4102::Point{x * cellSize + xOffset, y * cellSize + yOffset}, cellSize - 2, cellSize - 2, TDT4102::Color::grey);
                win.draw_image(TDT4102::Point{x * cellSize + xOffset, y * cellSize + yOffset}, *images.at(9));
            }
        }
    }
}

void GameWindow::drawPlayer(AnimationWindow& win){
    int x = player->getPlayerX();
    int y = player->getPlayerY();

    win.draw_circle(TDT4102::Point{x * cellSize + cellSize/2 + xOffset, y * cellSize + cellSize/2 + yOffset}, 10, TDT4102::Color::black);
}



void GameWindow::move(){
    if (up(*this)){
        if(player->getPlayerY() != 0 && (*playerFieldVec[player->getPlayerY()-1])[player->getPlayerX()] != -1){
            player->moveUp(*this);
            tileClick(*field, playerFieldVec, dead);
        }
        
    } else if (down(*this)){
        if(player->getPlayerY() != (H-1) && (*playerFieldVec[player->getPlayerY()+1])[player->getPlayerX()] != -1){
            player->moveDown(*this);
            tileClick(*field, playerFieldVec, dead);
        }
        
    } else if (left(*this)){
        if(player->getPlayerX() != 0 &&(*playerFieldVec[player->getPlayerY()])[player->getPlayerX()-1] != -1){
            player->moveLeft(*this);
            tileClick(*field, playerFieldVec, dead);
        }
        
    } else if (right(*this)){
        if(player->getPlayerX() != (W-1) && (*playerFieldVec[player->getPlayerY()])[player->getPlayerX()+1] != -1){
            player->moveRight(*this);
            tileClick(*field, playerFieldVec, dead);
        }
        
    }
}

void GameWindow::drawArrows(AnimationWindow& win){
    if (!up(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - 2* cellSize - 2, xOffset - 20}, *pictures.at("upLight"));
    }
    else if (up(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - 2* cellSize - 2, xOffset - 20}, *pictures.at("upDark"));
    }
    if (!down(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - 2* cellSize - 2, xOffset + cellSize - 18}, *pictures.at("downLight"));
    }
    else if (down(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - 2* cellSize - 2, xOffset + cellSize - 18}, *pictures.at("downDark"));
    }
    if (!left(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - 3* cellSize - 4, xOffset + cellSize - 18}, *pictures.at("leftLight"));
    }
    else if (left(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - 3* cellSize - 4, xOffset + cellSize - 18}, *pictures.at("leftDark")); 
    }
    if (!right(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - cellSize, xOffset + cellSize - 18}, *pictures.at("rightLight"));
    }
    else if (right(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - cellSize, xOffset + cellSize - 18}, *pictures.at("rightDark"));
    }
    // win.draw_image(TDT4102::Point{1440 - xOffset - 2* cellSize - 2, xOffset - 20}, UPIMAGE);
    // win.draw_image(TDT4102::Point{1440 - xOffset - 2* cellSize - 2, xOffset + cellSize - 18}, DOWNIMAGE);
    // win.draw_image(TDT4102::Point{1440 - xOffset - 3* cellSize - 4, xOffset + cellSize - 18}, LEFTIMAGE);
    // win.draw_image(TDT4102::Point{1440 - xOffset - cellSize, xOffset + cellSize - 18}, RIGHTIMAGE);
    draw_text(TDT4102::Point {200, 650}, to_string(bombCount) , TDT4102::Color::red, 45);
}



TDT4102::Point GameWindow::coordinates(){
    return TDT4102::AnimationWindow::get_mouse_coordinates();
}

int GameWindow::clickY(){
    int yIndex = coordinates().y / cellSize;
    if (coordinates().y < cellSize * H + yOffset && coordinates().y > yOffset){
        return yIndex;
    }
    return -1;
}

int GameWindow::clickX(){
    int xIndex = coordinates().x / cellSize;
    if (coordinates().x < cellSize * W + xOffset && coordinates().x > xOffset){
        return xIndex;
    }
    return -1;
}


void GameWindow::tileClick(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec, bool& dead){
    int x = player->getPlayerX();
    int y = player->getPlayerY();

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
void GameWindow::flagSpaceMode(){

    int x = player->getPlayerX();
    int y = player->getPlayerY();
    char direction = player->getDirection();
    int dx = 0;
    int dy = 0;

    if (keyUp(*this)){
        dy = -1;
        if(y == 0){
            return;
        }

        if ((*playerFieldVec[y+dy])[x+dx] == 0){
        (*playerFieldVec[y+dy])[x+dx] = -1;
        bombCount--;
        }
        else if ((*playerFieldVec[y+dy])[x+dx] == -1){
            (*playerFieldVec[y+dy])[x+dx] = 0;
            bombCount++;
        }

    } else if (keyDown(*this)){
        dy = 1;
        if(y == (H-1)){
            return;
        }

        if ((*playerFieldVec[y+dy])[x+dx] == 0){
        (*playerFieldVec[y+dy])[x+dx] = -1;
        bombCount--;
        }
        else if ((*playerFieldVec[y+dy])[x+dx] == -1){
            (*playerFieldVec[y+dy])[x+dx] = 0;
            bombCount++;
        }
        
    } else if (keyLeft(*this)){
        dx=-1;
        if(x == 0){
            return;
        }

        if ((*playerFieldVec[y+dy])[x+dx] == 0){
        (*playerFieldVec[y+dy])[x+dx] = -1;
        bombCount--;
        }
        else if ((*playerFieldVec[y+dy])[x+dx] == -1){
            (*playerFieldVec[y+dy])[x+dx] = 0;
            bombCount++;
        }
        
    } else if (keyRight(*this)){
        dx=1;
        if(x == (W-1)){
            return;
        }

        if ((*playerFieldVec[y+dy])[x+dx] == 0){
        (*playerFieldVec[y+dy])[x+dx] = -1;
        bombCount--;
        }
        else if ((*playerFieldVec[y+dy])[x+dx] == -1){
            (*playerFieldVec[y+dy])[x+dx] = 0;
            bombCount++;
        }
    }
}


void GameWindow::flagSpace(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec){
    int x = player->getPlayerX();
    int y = player->getPlayerY();
    char direction = player->getDirection();
    int dx = 0;
    int dy = 0;

    if (direction == 'L' && x!=0)
    {
        dx = -1;
        if(x == 0){
            return;
        }
    } else if(direction == 'R' && x!=(W-1)){
        dx = 1;
        if(x == (W-1)){
            return;
        }
    } else if(direction == 'U' && y!=0){
        dy=-1;
        if(y == 0){
            return;
        }
    } else if(direction == 'D' && y!=(H-1)){
        dy=+1;
        if(y == (H-1)){
            return;
        }
    }

    if ((*playerFieldVec[y+dy])[x+dx] == 0){
        (*playerFieldVec[y+dy])[x+dx] = -1;
        bombCount--;
    }
    else if ((*playerFieldVec[y+dy])[x+dx] == -1){
        (*playerFieldVec[y+dy])[x+dx] = 0;
        bombCount++;
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
    bombCount = 70;
}

void GameWindow::saveGame(){
    std::filesystem::path fileName{"myFile.txt"};
    std::ofstream outputStream{fileName};
    std::string line;

    outputStream << to_string(player->getPlayerX()) << " " << to_string(player->getPlayerY()) << std::endl;
    outputStream << to_string(static_cast<int>(frozenTimer)) << std::endl;
    outputStream << to_string(bombCount) << std::endl;

    outputStream << to_string(W) << std::endl;
    outputStream << to_string(H) << std::endl;
    for (int y = 0; y < H; y++){
        line = "";
        for (int x = 0; x < W; x++){
            line += to_string((*field->getField()[y])[x]) + " ";
        }
        outputStream << line << endl;
    }
    outputStream << to_string(W) << std::endl;
    outputStream << to_string(H) << std::endl;

    for (int y = 0; y < H; y++){
        line = "";
        for (int x = 0; x < W; x++){
            line += to_string((*playerFieldVec[y])[x]) + " ";
        }
        outputStream << line << endl;
    }
}