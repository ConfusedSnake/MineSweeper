#include "GameWindow.h"
#include "drawGame.h"


void GameWindow::drawGame(bool dPlayerField) {
    try {
        if (player->getPlayerY() == (viewYdirec - 1)) {
            resetButton.setVisible(false);
            yMove = -cellSize;
        } else if (player->getPlayerY() >= viewYdirec) {
            yMove = -2 * cellSize;
        } else {
            yMove = 0;
            resetButton.setVisible(true);
        }

        if (player->getPlayerX() < 9) {
            draw_image(TDT4102::Point{0, yMove}, *pictures.at("backgroundTop"), 1440, cellSize * 2);
        } else if (player->getPlayerX() > (W - 8)) {
            draw_image(TDT4102::Point{-((W - 8) - 8) * cellSize / 6, yMove}, *pictures.at("backgroundTop"), 1440, cellSize * 2);
            draw_image(TDT4102::Point{1440 - ((W - 8) - 8) * cellSize / 6, yMove}, *pictures.at("backgroundTop"), 1440, cellSize * 2);
        } else {
            draw_image(TDT4102::Point{-(player->getPlayerX() - 8) * cellSize / 6, yMove}, *pictures.at("backgroundTop"), 1440, cellSize * 2);
            draw_image(TDT4102::Point{1440 - (player->getPlayerX() - 8) * cellSize / 6, yMove}, *pictures.at("backgroundTop"), 1440, cellSize * 2);
        }

        drawGrid();
        if (dPlayerField) {
            drawPlayerGrid();
        }
        drawArrows();
        drawBombCount();
        drawPauseMenuButton();
        draw_text(TDT4102::Point{697, xOffset - 22 + yMove}, to_string(static_cast<int>(frozenTimer + savedTimer)), TDT4102::Color::red, 45, Font::courier_bold);
        drawPlayer();
    } catch (const std::exception& e) {
        std::cerr << "Error in drawGame: " << e.what() << std::endl;
    }
}

void GameWindow::drawGrid() {
    try {
        if (!field) return;

        int topy;
        int topx;
        int boty;
        int botx;

        boty = player->getPlayerY() - viewYdirec;
        topy = player->getPlayerY() + viewYdirec;
        botx = player->getPlayerX() - viewXdirec;
        topx = player->getPlayerX() + viewXdirec;

        if (player->getPlayerX() < viewXdirec) {
            botx = 0;
            topx = viewXdirec * 2;
        }
        if (player->getPlayerY() < viewYdirec) {
            boty = 0;
            topy = viewYdirec * 2;
        }
        if (player->getPlayerX() > (W - viewXdirec - 1)) {
            botx = W - (viewXdirec * 2);
            topx = W;
        }
        if (player->getPlayerY() > (H - viewYdirec - 1)) {
            boty = H - (viewYdirec * 2);
            topy = H;
        }

        TDT4102::Color color = TDT4102::Color::grey;

        for (int y = boty; y < topy; y++) {
            for (int x = botx; x < topx; x++) {
                auto& imagePtr = images.count((*field->getField()[y])[x])
                                      ? images.at((*field->getField()[y])[x])
                                      : images.at(0);

                draw_image(TDT4102::Point{(x - botx) * cellSize, (y - boty) * cellSize + yOffset + yMove}, *pictures.at("dirt"));

                if (!dead || player->getPlayerX() == (W - 1)) {
                    if (y == 0) {
                        if ((*playerFieldVec[y])[x] != 1) {
                            draw_image(TDT4102::Point{x * cellSize, 90 + yMove}, *pictures.at("grassBot"));
                        }
                    }

                    if (y != (H - 2) && (*playerFieldVec[y])[x] == 1 && (*playerFieldVec[y + 1])[x] != 1) {
                        draw_image(TDT4102::Point{(x - botx) * cellSize, (y - boty) * cellSize + yOffset + yMove}, *pictures.at("grassBot"));
                    }
                    if (y != (0) && (*playerFieldVec[y])[x] == 1 && (*playerFieldVec[y - 1])[x] != 1) {
                        draw_image(TDT4102::Point{(x - botx) * cellSize, (y - boty) * cellSize + yOffset + yMove}, *pictures.at("grassTop"));
                    }
                    if (x != (W - 1) && (*playerFieldVec[y])[x] == 1 && (*playerFieldVec[y])[x + 1] != 1) {
                        draw_image(TDT4102::Point{(x - botx) * cellSize, (y - boty) * cellSize + yOffset + yMove}, *pictures.at("grassRight"));
                    }
                    if (x != (0) && (*playerFieldVec[y])[x] == 1 && (*playerFieldVec[y])[x - 1] != 1) {
                        draw_image(TDT4102::Point{(x - botx) * cellSize, (y - boty) * cellSize + yOffset + yMove}, *pictures.at("grassLeft"));
                    }
                }

                if ((*field->getField()[y])[x] == -1) {
                    draw_image(TDT4102::Point{(x - botx) * cellSize, (y - boty) * cellSize + yOffset + yMove}, *imagePtr, cellSize, cellSize);
                } else {
                    draw_image(TDT4102::Point{(x - botx) * cellSize, (y - boty) * cellSize + yOffset + yMove}, *imagePtr);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in drawGrid: " << e.what() << std::endl;
    }
}


void GameWindow::drawPlayerGrid() {
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
                    draw_image(TDT4102::Point{(x-botx) * cellSize, (y-boty) * cellSize + yOffset + yMove}, *pictures.at("groundLight"));
                } else{
                    draw_image(TDT4102::Point{(x-botx) * cellSize, (y-boty) * cellSize + yOffset + yMove}, *pictures.at("groundDark"));
                }
                if ((*playerFieldVec[y])[x] == -1){
                    draw_image(TDT4102::Point{(x-botx) * cellSize, (y-boty) * cellSize + yOffset + yMove - 20}, *images.at(9), cellSize, cellSize);
                }
            }
        }
    }
}

void GameWindow::drawPlayer(){
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
        draw_image(TDT4102::Point{xpos * cellSize, ypos * cellSize - cellSize/2 + yOffset + yMove},  *pictures.at("playerDown"), 
        cellSize, cellSize);
    } else if(player->getDirection() == 'U'){
        draw_image(TDT4102::Point{xpos * cellSize, ypos * cellSize - cellSize/2 + yOffset + yMove},  *pictures.at("playerUp"), 
        cellSize, cellSize);
    } else if(player->getDirection() == 'R'){
        draw_image(TDT4102::Point{xpos * cellSize, ypos * cellSize - cellSize/2 + yOffset + yMove},  *pictures.at("playerRight"), 
        cellSize, cellSize);
    } else{
        draw_image(TDT4102::Point{xpos * cellSize, ypos * cellSize - cellSize/2 + yOffset + yMove},  *pictures.at("playerLeft"), 
        cellSize, cellSize);
    } 
    //draw_circle(TDT4102::Point{xpos * cellSize + cellSize/2, ypos * cellSize + cellSize/2 + yOffset + yMove}, 10, TDT4102::Color::black);
    
}

void GameWindow::drawArrows(){
    if (!up(*this)){
        draw_image(TDT4102::Point{1440 - xOffset - 2* arrowSize - 2, 40 + yMove}, *pictures.at("upLight"));
    }
    else if (up(*this)){
        draw_image(TDT4102::Point{1440 - xOffset - 2* arrowSize - 2, 40 + yMove}, *pictures.at("upDark"));
    }
    if (!down(*this)){
        draw_image(TDT4102::Point{1440 - xOffset - 2* arrowSize - 2, 42 + arrowSize + yMove}, *pictures.at("downLight"));
    }
    else if (down(*this)){
        draw_image(TDT4102::Point{1440 - xOffset - 2* arrowSize - 2, 42 + arrowSize + yMove}, *pictures.at("downDark"));
    }
    if (!left(*this)){
        draw_image(TDT4102::Point{1440 - xOffset - 3* arrowSize - 4, 42 + arrowSize + yMove}, *pictures.at("leftLight"));
    }
    else if (left(*this)){
        draw_image(TDT4102::Point{1440 - xOffset - 3* arrowSize - 4, 42 + arrowSize + yMove}, *pictures.at("leftDark")); 
    }
    if (!right(*this)){
        draw_image(TDT4102::Point{1440 - xOffset - arrowSize, 42 + arrowSize + yMove}, *pictures.at("rightLight"));
    }
    else if (right(*this)){
        draw_image(TDT4102::Point{1440 - xOffset - arrowSize, 42 + arrowSize + yMove}, *pictures.at("rightDark"));
    }
    if (!spaceBar(*this)){
        draw_image(TDT4102::Point{1440 - xOffset - 6*arrowSize - 6, 42 + arrowSize + yMove}, *pictures.at("spaceLight"));
    }
    else if (spaceBar(*this)){
        draw_image(TDT4102::Point{1440 - xOffset - 6*arrowSize - 6, 42 + arrowSize + yMove}, *pictures.at("spaceDark"));
    }
}

void GameWindow::drawBombCount(){
    draw_image(TDT4102::Point{1440 - xOffset - 6*arrowSize - 6, 40 + yMove}, *pictures.at("bombCount"));
    draw_text(TDT4102::Point{1440 - xOffset - 5*arrowSize - 10, 43 + yMove}, to_string(bombCount) , TDT4102::Color::black, 30, Font::courier_bold);
}
