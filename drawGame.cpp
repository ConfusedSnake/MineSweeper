#include "GameWindow.h"
#include "drawGame.h"


void GameWindow::drawGrid(AnimationWindow& win) {
    if (!field) return;
    int topy;
    int topx;
    int boty;
    int botx;

    boty = player->getPlayerY()-viewYdirec;
    topy = player->getPlayerY()+viewYdirec;
    botx = player->getPlayerX()-viewXdirec;
    topx = player->getPlayerX()+viewXdirec;

    if(player->getPlayerX() < viewXdirec ){
        botx = 0;
        topx = viewXdirec*2;
    }
    if(player->getPlayerY() < viewYdirec){
        boty = 0;
        topy = viewYdirec*2;
    }
    if(player->getPlayerX() > (W-viewXdirec-1)){
        botx = W-(viewXdirec*2);
        topx = W;
    }
    if(player->getPlayerY() > (H-viewYdirec-1)){
        boty = H-(viewYdirec*2);
        topy = H;
    } 
    
    TDT4102::Color color = TDT4102::Color::grey;


    for (int y = boty; y < topy; y++) {
        for (int x = botx; x < topx; x++) {
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

            if(y != (H-2) && (*playerFieldVec[y])[x] == 1 && (*playerFieldVec[y+1])[x] == 0){
                win.draw_image(TDT4102::Point{(x-botx) * cellSize, (y-boty) * cellSize + yOffset + yMove}, *pictures.at("dirtGrass"));
            } else {
                win.draw_image(TDT4102::Point{(x-botx) * cellSize, (y-boty) * cellSize + yOffset + yMove}, *pictures.at("dirt"));
            }
            //win.draw_rectangle(TDT4102::Point{(x-botx) * cellSize, (y-boty) * cellSize + yOffset + yMove}, cellSize-2, cellSize-2, color);
            win.draw_image(TDT4102::Point{(x-botx) * cellSize, (y-boty) * cellSize + yOffset + yMove}, *imagePtr);
        }
    }
}

void GameWindow::drawPlayerGrid(AnimationWindow& win, const std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec) {
    int topy;
    int topx;
    int boty;
    int botx;

    boty = player->getPlayerY()-viewYdirec;
    topy = player->getPlayerY()+viewYdirec;
    botx = player->getPlayerX()-viewXdirec;
    topx = player->getPlayerX()+viewXdirec;

    if(player->getPlayerX() < viewXdirec ){
        botx = 0;
        topx = viewXdirec*2;
    }
    if(player->getPlayerY() < viewYdirec ){
        boty = 0;
        topy = viewYdirec*2;
    }
    if(player->getPlayerX() > (W-viewXdirec-1)){
        botx = W-(viewXdirec*2);
        topx = W;
    }
    if(player->getPlayerY() > (H-viewYdirec-1)){
        boty = H-(viewYdirec*2);
        topy = H;
    } 

    for (int y = boty; y < topy; y++) {
        for (int x = botx; x < topx; x++) {
            if ((*playerFieldVec[y])[x] != 1){
                if(y%2==0){
                    win.draw_image(TDT4102::Point{(x-botx) * cellSize, (y-boty) * cellSize + yOffset + yMove}, *pictures.at("groundLight"));
                } else{
                    win.draw_image(TDT4102::Point{(x-botx) * cellSize, (y-boty) * cellSize + yOffset + yMove}, *pictures.at("groundDark"));
                }
                if ((*playerFieldVec[y])[x] == -1){
                    win.draw_image(TDT4102::Point{(x-botx) * cellSize, (y-boty) * cellSize + yOffset + yMove}, *images.at(9), cellSize, cellSize);
                }
            }
        }
    }
}

void GameWindow::drawPlayer(AnimationWindow& win){
    int x = player->getPlayerX();
    int y = player->getPlayerY();

    int xpos = viewXdirec;
    int ypos = viewYdirec;
    if(x < viewXdirec){
        xpos = x;
    }
    if(y < viewYdirec){
        ypos = y;
    }
    if(x > (W-viewXdirec)){
        xpos = ((viewXdirec*2)-(W-x));    
    } 
    if (y > (H-viewYdirec)){
        ypos = ((viewYdirec*2)-(H-y));
    }

    if(player->getDirection() == 'D'){
        win.draw_image(TDT4102::Point{xpos * cellSize, ypos * cellSize - cellSize/2 + yOffset + yMove},  *pictures.at("playerDown"), 
        cellSize, cellSize);
    } else if(player->getDirection() == 'U'){
        win.draw_image(TDT4102::Point{xpos * cellSize, ypos * cellSize - cellSize/2 + yOffset + yMove},  *pictures.at("playerUp"), 
        cellSize, cellSize);
    } else if(player->getDirection() == 'R'){
        win.draw_image(TDT4102::Point{xpos * cellSize, ypos * cellSize - cellSize/2 + yOffset + yMove},  *pictures.at("playerRight"), 
        cellSize, cellSize);
    } else{
        win.draw_image(TDT4102::Point{xpos * cellSize, ypos * cellSize - cellSize/2 + yOffset + yMove},  *pictures.at("playerLeft"), 
        cellSize, cellSize);
    } 
    //win.draw_circle(TDT4102::Point{xpos * cellSize + cellSize/2, ypos * cellSize + cellSize/2 + yOffset + yMove}, 10, TDT4102::Color::black);
    
}

void GameWindow::drawArrows(AnimationWindow& win){
    if (!up(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - 2* arrowSize - 2, 40 + yMove}, *pictures.at("upLight"));
    }
    else if (up(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - 2* arrowSize - 2, 40 + yMove}, *pictures.at("upDark"));
    }
    if (!down(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - 2* arrowSize - 2, 42 + arrowSize + yMove}, *pictures.at("downLight"));
    }
    else if (down(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - 2* arrowSize - 2, 42 + arrowSize + yMove}, *pictures.at("downDark"));
    }
    if (!left(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - 3* arrowSize - 4, 42 + arrowSize + yMove}, *pictures.at("leftLight"));
    }
    else if (left(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - 3* arrowSize - 4, 42 + arrowSize + yMove}, *pictures.at("leftDark")); 
    }
    if (!right(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - arrowSize, 42 + arrowSize + yMove}, *pictures.at("rightLight"));
    }
    else if (right(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - arrowSize, 42 + arrowSize + yMove}, *pictures.at("rightDark"));
    }
    if (!spaceBar(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - 6*arrowSize - 6, 42 + arrowSize + yMove}, *pictures.at("spaceLight"));
    }
    else if (spaceBar(*this)){
        win.draw_image(TDT4102::Point{1440 - xOffset - 6*arrowSize - 6, 42 + arrowSize + yMove}, *pictures.at("spaceDark"));
    }
}
