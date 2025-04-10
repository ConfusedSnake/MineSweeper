#include "GameWindow.h"



GameWindow::GameWindow(TDT4102::Point position, int width, int height, const std::string& title): 
    AnimationWindow{position.x, position.y, width, height, title},
    resetButton{TDT4102::Point {xOffset, yOffset - cellSize}, 100, 30, "Reset"}
{

    // ==================== Pictures on field ==================== //
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

    for (const auto& [key, filename] : numPic) {
        images[key] = std::make_unique<TDT4102::Image>(filename);
    }

    // ==================== Pictures not on field ==================== //
    std::map<std::string, std::string> imageMap {
        {"backgroundTop", "background3.png"},
        {"upDark", "arrowKeys/upDark.png"},
        {"upLight", "arrowKeys/upLight.png"},
        {"downDark", "arrowKeys/downDark.png"},
        {"downLight", "arrowKeys/downLight.png"},
        {"leftDark", "arrowKeys/leftDark.png"},
        {"leftLight", "arrowKeys/leftLight.png"},
        {"rightDark", "arrowKeys/rightDark.png"},
        {"rightLight", "arrowKeys/rightLight.png"},
        {"groundLight","Tall/groundLight.png"},
        {"groundDark","Tall/groundDark.png"}
    };

    for (const auto& [key, filename] : imageMap) {
        pictures[key] = std::make_unique<TDT4102::Image>(filename);
    }

    // ============================================================ //

    playerFieldVec.reserve(H);
    for (int i = 0; i < H; i++) {
        playerFieldVec.push_back(std::make_unique<std::vector<int>>(W, 0));
    }

    resetButton.setCallback(std::bind(&GameWindow::callbackButton, this));
    add(resetButton);
}

void GameWindow::drawMainMenu(AnimationWindow& win){
    // Menu Background and Text
    win.draw_rectangle(TDT4102::Point {720 - menuButtonWidth/2 - 50, 450 - menuButtonHeight/2 - menuButtonPad - menuButtonHeight - 150}, 100 + menuButtonWidth, 200 + 3*menuButtonHeight + 2*menuButtonPad);
    win.draw_text(TDT4102::Point {720 - 110, 450 - menuButtonHeight/2 - menuButtonPad - menuButtonHeight - 100}, "Main Menu", TDT4102::Color::red, 45, Font::courier_bold);

    // Points right side
    TDT4102::Point rightUpper = {720 - menuButtonWidth/2 + menuButtonWidth, 450 - 2*menuButtonHeight - menuButtonPad/2 -menuButtonPad};
    TDT4102::Point rightLower = {720 - menuButtonWidth/2 + menuButtonWidth, 450 - menuButtonHeight - menuButtonPad/2 -menuButtonPad};
    TDT4102::Point rightOuter = {720 - menuButtonWidth/2 + menuButtonWidth + menuTriangleHeight, 450 - static_cast<int>(1.5*menuButtonHeight) - menuButtonPad/2 -menuButtonPad};

    // Points left side
    TDT4102::Point leftUpper = {720 - menuButtonWidth/2, 450 - 2*menuButtonHeight - menuButtonPad/2 -menuButtonPad};
    TDT4102::Point leftLower = {720 - menuButtonWidth/2, 450 - menuButtonHeight - menuButtonPad/2 -menuButtonPad};
    TDT4102::Point leftOuter = {720 - menuButtonWidth/2 - menuTriangleHeight, 450 - static_cast<int>(1.5*menuButtonHeight) - menuButtonPad/2 -menuButtonPad};

    // Start Button
    if (mouseOnTopMenuButton() && leftClick(*this)){
        TopMenuColor = color;
    }
    else{
        TopMenuColor = menuButtonColor;
    }
    win.draw_rectangle(TDT4102::Point {720 - menuButtonWidth/2, 450 - 2*menuButtonHeight - menuButtonPad/2 -menuButtonPad}, menuButtonWidth, menuButtonHeight, TopMenuColor);
    win.draw_triangle(rightUpper, rightOuter, rightLower, TopMenuColor);
    win.draw_triangle(leftUpper, leftLower, leftOuter, TopMenuColor);
    win.draw_text(TDT4102::Point {720 - 88, 450 - 2*menuButtonHeight - menuButtonPad/2 -menuButtonPad + 9}, "New Game", TDT4102::Color::red, 45, Font::courier_bold);

    // Load Button
    if (mouseOnTopMiddleMenuButton() && leftClick(*this)){
        TopMiddleMenuColor = color;
    }
    else{
        TopMiddleMenuColor = menuButtonColor;
    }
    win.draw_rectangle(TDT4102::Point {720 - menuButtonWidth/2, 450 - menuButtonHeight - menuButtonPad/2}, menuButtonWidth, menuButtonHeight, TopMiddleMenuColor);
    win.draw_triangle(TDT4102::Point {rightUpper.x, rightUpper.y + menuButtonHeight + menuButtonPad}, 
    TDT4102::Point {rightOuter.x, rightOuter.y + menuButtonHeight + menuButtonPad}, TDT4102::Point {rightLower.x,
    rightLower.y + menuButtonHeight + menuButtonPad}, TopMiddleMenuColor);
    win.draw_triangle(TDT4102::Point {leftUpper.x, leftUpper.y + menuButtonHeight + menuButtonPad}, 
    TDT4102::Point {leftLower.x, leftLower.y + menuButtonHeight + menuButtonPad}, TDT4102::Point {leftOuter.x,
    leftOuter.y + menuButtonHeight + menuButtonPad}, TopMiddleMenuColor);
    win.draw_text(TDT4102::Point {720 - 110, 450 - menuButtonHeight - menuButtonPad/2 + 9}, "Load Game", TDT4102::Color::red, 45, Font::courier_bold);


    // Controls Button
    if (mouseOnBottomMiddleMenuButton() && leftClick(*this)){
        BottomMiddleMenuColor = color;
    }
    else {
        BottomMiddleMenuColor = menuButtonColor;
    }
    win.draw_rectangle(TDT4102::Point {720 - menuButtonWidth/2, 450 + menuButtonPad/2}, menuButtonWidth, menuButtonHeight, BottomMiddleMenuColor);
    win.draw_triangle(TDT4102::Point {rightUpper.x, rightUpper.y + 2*(menuButtonHeight + menuButtonPad),}, 
    TDT4102::Point {rightOuter.x, rightOuter.y + 2*(menuButtonHeight + menuButtonPad)}, TDT4102::Point {rightLower.x,
    rightLower.y + 2*(menuButtonHeight + menuButtonPad)}, BottomMiddleMenuColor);
    win.draw_triangle(TDT4102::Point {leftUpper.x, leftUpper.y + 2*(menuButtonHeight + menuButtonPad)}, 
    TDT4102::Point {leftLower.x, leftLower.y + 2*(menuButtonHeight + menuButtonPad)}, TDT4102::Point {leftOuter.x,
    leftOuter.y + 2*(menuButtonHeight + menuButtonPad)}, BottomMiddleMenuColor);
    win.draw_text(TDT4102::Point {720 - 98, 450 + menuButtonPad/2 + 9}, "Controls", TDT4102::Color::red, 45, Font::courier_bold);

    // Exit Button
    if (mouseOnBottomMenuButton() && leftClick(*this)){
        BottomMenuColor = color;
    }
    else {
        BottomMenuColor = menuButtonColor;
    }
    win.draw_rectangle(TDT4102::Point {720 - menuButtonWidth/2, 450 + menuButtonPad/2 + menuButtonPad + menuButtonHeight}, menuButtonWidth, menuButtonHeight, BottomMenuColor);
    win.draw_triangle(TDT4102::Point {rightUpper.x, rightUpper.y + 3*(menuButtonHeight + menuButtonPad),}, 
    TDT4102::Point {rightOuter.x, rightOuter.y + 3*(menuButtonHeight + menuButtonPad)}, TDT4102::Point {rightLower.x,
    rightLower.y + 3*(menuButtonHeight + menuButtonPad)}, BottomMenuColor);
    win.draw_triangle(TDT4102::Point {leftUpper.x, leftUpper.y + 3*(menuButtonHeight + menuButtonPad)}, 
    TDT4102::Point {leftLower.x, leftLower.y + 3*(menuButtonHeight + menuButtonPad)}, TDT4102::Point {leftOuter.x,
    leftOuter.y + 3*(menuButtonHeight + menuButtonPad)}, BottomMenuColor);
    win.draw_text(TDT4102::Point {720 - 50, 450 + menuButtonPad/2 + menuButtonPad + menuButtonHeight + 9}, "Exit", TDT4102::Color::red, 45, Font::courier_bold);
}

void GameWindow::drawPauseMenu(AnimationWindow& win){
    // Menu background and Text
    win.draw_rectangle(TDT4102::Point {720 - menuButtonWidth/2 - 50, 450 - menuButtonHeight/2 - menuButtonPad - menuButtonHeight - 150}, 100 + menuButtonWidth, 200 + 3*menuButtonHeight + 2*menuButtonPad);
    win.draw_text(TDT4102::Point {720 - 80, 450 - menuButtonHeight/2 - menuButtonPad - menuButtonHeight - 100}, "Paused", TDT4102::Color::red, 45, Font::courier_bold);

    // Points right side
    TDT4102::Point rightUpper = {720 - menuButtonWidth/2 + menuButtonWidth, 450 - 2*menuButtonHeight - menuButtonPad/2 -menuButtonPad};
    TDT4102::Point rightLower = {720 - menuButtonWidth/2 + menuButtonWidth, 450 - menuButtonHeight - menuButtonPad/2 -menuButtonPad};
    TDT4102::Point rightOuter = {720 - menuButtonWidth/2 + menuButtonWidth + menuTriangleHeight, 450 - static_cast<int>(1.5*menuButtonHeight) - menuButtonPad/2 -menuButtonPad};

    // Points left side
    TDT4102::Point leftUpper = {720 - menuButtonWidth/2, 450 - 2*menuButtonHeight - menuButtonPad/2 -menuButtonPad};
    TDT4102::Point leftLower = {720 - menuButtonWidth/2, 450 - menuButtonHeight - menuButtonPad/2 -menuButtonPad};
    TDT4102::Point leftOuter = {720 - menuButtonWidth/2 - menuTriangleHeight, 450 - static_cast<int>(1.5*menuButtonHeight) - menuButtonPad/2 -menuButtonPad};

    // Resume Button
    if (mouseOnTopMenuButton() && leftClick(*this)){
        TopMenuColor = color;
    }
    else{
        TopMenuColor = menuButtonColor;
    }
    win.draw_rectangle(TDT4102::Point {720 - menuButtonWidth/2, 450 - 2*menuButtonHeight - menuButtonPad/2 -menuButtonPad}, menuButtonWidth, menuButtonHeight, TopMenuColor);
    win.draw_triangle(rightUpper, rightOuter, rightLower, TopMenuColor);
    win.draw_triangle(leftUpper, leftLower, leftOuter, TopMenuColor);
    win.draw_text(TDT4102::Point {720 - 80, 450 - 2*menuButtonHeight - menuButtonPad/2 -menuButtonPad + 9}, "Resume", TDT4102::Color::red, 45, Font::courier_bold);

    // Save Button
    if (mouseOnTopMiddleMenuButton() && leftClick(*this)){
        TopMiddleMenuColor = color;
    }
    else{
        TopMiddleMenuColor = menuButtonColor;
    }
    win.draw_rectangle(TDT4102::Point {720 - menuButtonWidth/2, 450 - menuButtonHeight - menuButtonPad/2}, menuButtonWidth, menuButtonHeight, TopMiddleMenuColor);
    win.draw_triangle(TDT4102::Point {rightUpper.x, rightUpper.y + menuButtonHeight + menuButtonPad}, 
    TDT4102::Point {rightOuter.x, rightOuter.y + menuButtonHeight + menuButtonPad}, TDT4102::Point {rightLower.x,
    rightLower.y + menuButtonHeight + menuButtonPad}, TopMiddleMenuColor);
    win.draw_triangle(TDT4102::Point {leftUpper.x, leftUpper.y + menuButtonHeight + menuButtonPad}, 
    TDT4102::Point {leftLower.x, leftLower.y + menuButtonHeight + menuButtonPad}, TDT4102::Point {leftOuter.x,
    leftOuter.y + menuButtonHeight + menuButtonPad}, TopMiddleMenuColor);
    win.draw_text(TDT4102::Point {720 - 110, 450 - menuButtonHeight - menuButtonPad/2 + 9}, "Save Game", TDT4102::Color::red, 45, Font::courier_bold);

    // Controls Button
    if (mouseOnBottomMiddleMenuButton() && leftClick(*this)){
        BottomMiddleMenuColor = color;
    }
    else {
        BottomMiddleMenuColor = menuButtonColor;
    }
    win.draw_rectangle(TDT4102::Point {720 - menuButtonWidth/2, 450 + menuButtonPad/2}, menuButtonWidth, menuButtonHeight, BottomMiddleMenuColor);
    win.draw_triangle(TDT4102::Point {rightUpper.x, rightUpper.y + 2*(menuButtonHeight + menuButtonPad),}, 
    TDT4102::Point {rightOuter.x, rightOuter.y + 2*(menuButtonHeight + menuButtonPad)}, TDT4102::Point {rightLower.x,
    rightLower.y + 2*(menuButtonHeight + menuButtonPad)}, BottomMiddleMenuColor);
    win.draw_triangle(TDT4102::Point {leftUpper.x, leftUpper.y + 2*(menuButtonHeight + menuButtonPad)}, 
    TDT4102::Point {leftLower.x, leftLower.y + 2*(menuButtonHeight + menuButtonPad)}, TDT4102::Point {leftOuter.x,
    leftOuter.y + 2*(menuButtonHeight + menuButtonPad)}, BottomMiddleMenuColor);
    win.draw_text(TDT4102::Point {720 - 98, 450 + menuButtonPad/2 + 9}, "Controls", TDT4102::Color::red, 45, Font::courier_bold);

    // Quit Button
    if (mouseOnBottomMenuButton() && leftClick(*this)){
        BottomMenuColor = color;
    }
    else {
        BottomMenuColor = menuButtonColor;
    }
    win.draw_rectangle(TDT4102::Point {720 - menuButtonWidth/2, 450 + menuButtonPad/2 + menuButtonPad + menuButtonHeight}, menuButtonWidth, menuButtonHeight, BottomMenuColor);
    win.draw_triangle(TDT4102::Point {rightUpper.x, rightUpper.y + 3*(menuButtonHeight + menuButtonPad),}, 
    TDT4102::Point {rightOuter.x, rightOuter.y + 3*(menuButtonHeight + menuButtonPad)}, TDT4102::Point {rightLower.x,
    rightLower.y + 3*(menuButtonHeight + menuButtonPad)}, BottomMenuColor);
    win.draw_triangle(TDT4102::Point {leftUpper.x, leftUpper.y + 3*(menuButtonHeight + menuButtonPad)}, 
    TDT4102::Point {leftLower.x, leftLower.y + 3*(menuButtonHeight + menuButtonPad)}, TDT4102::Point {leftOuter.x,
    leftOuter.y + 3*(menuButtonHeight + menuButtonPad)}, BottomMenuColor);
    win.draw_text(TDT4102::Point {720 - 50, 450 + menuButtonPad/2 + menuButtonPad + menuButtonHeight + 9}, "Quit", TDT4102::Color::red, 45, Font::courier_bold);
}

bool GameWindow::mouseOnTopMenuButton(){
    if ((coordinates().x >= 720 - menuButtonWidth/2) && (coordinates().x <= 720 + menuButtonWidth/2) &&
    (coordinates().y >= 450 - 2*menuButtonHeight - menuButtonPad/2 -menuButtonPad)
    && (coordinates().y <= 450 - menuButtonHeight - menuButtonPad/2 -menuButtonPad)){
        return true;
    }
    return false;
}
    
bool GameWindow::mouseOnTopMiddleMenuButton(){
    if ((coordinates().x >= 720 - menuButtonWidth/2) && (coordinates().x <= 720 + menuButtonWidth/2) &&
    (coordinates().y >= 450 - menuButtonHeight - menuButtonPad/2) &&
    (coordinates().y <= 450 - menuButtonPad)){
        return true;
    }
    return false;
}

bool GameWindow::mouseOnBottomMiddleMenuButton(){
    if ((coordinates().x >= 720 - menuButtonWidth/2) && (coordinates().x <= 720 + menuButtonWidth/2) &&
    (coordinates().y >= 450 + menuButtonPad/2) &&
    (coordinates().y <= 450 + menuButtonPad/2 + menuButtonHeight)){
        return true;
    }
    return false;
}
    
bool GameWindow::mouseOnBottomMenuButton(){
    if ((coordinates().x >= 720 - menuButtonWidth/2) && (coordinates().x <= 720 + menuButtonWidth/2) &&
    (coordinates().y >= 450 + menuButtonPad/2 + menuButtonPad + menuButtonHeight) &&
    (coordinates().y <= 450 + menuButtonPad/2 + menuButtonPad + 2*menuButtonHeight)){
        return true;
    }
    return false;
}

void GameWindow::menuClicks(){
    // Top button
    if (mouseOnTopMenuButton() && mouseClickedLeft(*this)){
        if (mainMenuOpen){
            mainMenuOpen = false;
        }
        else if (pauseMenuOpen){
            pauseMenuOpen = false;
        }
    }

    // Top-Middle button
    if (mouseOnTopMiddleMenuButton() && mouseClickedLeft(*this)){
        if (mainMenuOpen){
            loadGame();
        }
        else if (pauseMenuOpen){
            saveGame();
        }
    }

    // Bottom-Middle button
    if (mouseOnBottomMiddleMenuButton() && mouseClickedLeft(*this)){
    }

    // // Bottom button
    if (mouseOnBottomMenuButton() && mouseClickedLeft(*this)){
        if (mainMenuOpen){
            loadGame();
        }
        else if (pauseMenuOpen){
            saveGame();
        }
    }
}

// ==================== Functions that runs the game ==================== //
void GameWindow::run() {
    std::filesystem::path fileName{"myFile.txt"};
    std::ifstream inputStream{fileName};

    while (!should_close()) {
        // ==================== Before first click ==================== //
        if(!field || !player){
            draw_image(TDT4102::Point{0,0}, *pictures.at("backgroundTop"));
            draw_text(TDT4102::Point {676, xOffset-22}, to_string(0) , TDT4102::Color::red, 45, Font::courier_bold);
            if ((mouseClickedLeft(*this) && clickX() != -1 && clickY() != -1)||(up(*this) || down(*this) || left(*this) || right(*this))) {
                
                // Creating game, either load og new game
                try{ 
                    loadGame();
                } catch(const exception& e) {
                    std::cout << e.what() << std::endl;
                    field = std::make_unique<Field>(W, H, 0, 0, false);
                    player = std::make_unique<Player>();
                    tileClick(*field, playerFieldVec, dead);
                } 
                
                drawGame(true, true, true, true, *this);
                t.start();
            }
        
        // ==================== After first click ==================== //
        } else {

            // Drawing top background, moving when player moves


            // =======================================================


            if (!dead){
                drawGame(true, true, true, true, *this);
                frozenTimer = t.stop();
                draw_text(TDT4102::Point {676, xOffset-22 + yMove}, to_string(static_cast<int>(frozenTimer + savedTimer)) , TDT4102::Color::red, 45, Font::courier_bold);
                menuClicks();
                if(!spaceBar(*this)){
                    move();
                }

                if(spaceBar(*this)){
                    flagSpaceMode();
                }
            }
            else {
                yMove = 0;
                drawGame(true, false, true, true, *this);
                draw_text(TDT4102::Point {676, xOffset-22}, to_string(static_cast<int>(frozenTimer + savedTimer)) , TDT4102::Color::red, 45, Font::courier_bold);
                if (!std::filesystem::is_empty("myFile.txt")){
                    std::ofstream file("myFile.txt", std::ios::trunc);
                }
            }

            if (keyRClicked(*this)){
                    reset();
                }
        }
        
        drawPauseMenu(*this);
        drawArrows(*this);
        draw_text(TDT4102::Point {200, 650 + yMove}, to_string(bombCount) , TDT4102::Color::red, 45);
        next_frame();
    }
}

void GameWindow::drawGame(bool dField, bool dPlayerField, bool dPlayer, bool dBackground, AnimationWindow& win){
    if(player->getPlayerY() == (viewYdirec-1)){
        yMove = -cellSize;
    } else if(player->getPlayerY() >= viewYdirec){
        yMove = -2*cellSize;
    } else{
        yMove = 0;
    }

    if(dField){
        drawGrid(win);
    }
    if(dPlayerField){
        drawPlayerGrid(win, playerFieldVec);
    }
    if(dPlayer){
        drawPlayer(win);
    }

    if(dBackground){
        if(player->getPlayerX() < 9){
            draw_image(TDT4102::Point{0,yMove}, *pictures.at("backgroundTop"), 1440, cellSize*2);
        } else if(player->getPlayerX() > (W-8)){
            draw_image(TDT4102::Point{-((W-8)-8)*cellSize/6,yMove}, *pictures.at("backgroundTop"), 1440, cellSize*2);
            draw_image(TDT4102::Point{1440-((W-8)-8)*cellSize/6,yMove}, *pictures.at("backgroundTop"), 1440, cellSize*2);
        }else {
            draw_image(TDT4102::Point{-(player->getPlayerX()-8)*cellSize/6,yMove}, *pictures.at("backgroundTop"), 1440, cellSize*2);
            draw_image(TDT4102::Point{1440-(player->getPlayerX()-8)*cellSize/6,yMove}, *pictures.at("backgroundTop"), 1440, cellSize*2);
        }
    }
}

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

            win.draw_rectangle(TDT4102::Point{(x-botx) * cellSize, (y-boty) * cellSize + yOffset + yMove}, cellSize-2, cellSize-2, color);
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

    win.draw_circle(TDT4102::Point{xpos * cellSize + cellSize/2, ypos * cellSize + cellSize/2 + yOffset + yMove}, 10, TDT4102::Color::black);
    
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
    std::ofstream file("myFile.txt", std::ios::trunc);
    if (file.is_open()) {
        std::cout << "Filen ble clearet!\n";
        file.close();
    } else {
        std::cerr << "Kunne ikke åpne filen.\n";
    }

    playerFieldVec.clear();
    playerFieldVec.reserve(H);
    for (int i = 0; i < H; i++) {
        playerFieldVec.push_back(std::make_unique<std::vector<int>>(W, 0));
    }
    field.reset();

    dead = false;
    bombCount = 70;
    savedTimer = 0;
}

void GameWindow::saveGame(){
    std::filesystem::path fileName{"myFile.txt"};
    std::ofstream outputStream{fileName};
    std::string line;

    outputStream << to_string(player->getPlayerX()) << " " << to_string(player->getPlayerY()) << std::endl;
    outputStream << to_string(static_cast<int>(frozenTimer) + savedTimer) << std::endl;
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

void GameWindow::loadGame(){
    std::cout << "Loading..." << std::endl;
    std::filesystem::path fileName{"myFile.txt"};
    std::cout << "Path complete" << std::endl;
    std::ifstream inputStream{fileName};
    std::cout << "Inputstream open" << std::endl;
    std::string nextWord;
    std::string line;

    if (!inputStream) {
        std::cout << "Could not open file" << std::endl;
    }
    else {
        
        player = std::make_unique<Player>();
        inputStream >> nextWord;
        player->changePlayerX(std::stoi(nextWord));
        std::cout << player->getPlayerX() << std::endl;

        inputStream >> nextWord;
        player->changePlayerY(std::stoi(nextWord));
        std::cout << player->getPlayerY() << std::endl;

        inputStream >> nextWord;
        savedTimer = std::stoi(nextWord);
        std::cout << savedTimer << std::endl;

        inputStream >> nextWord;
        bombCount = std::stoi(nextWord);
        std::cout << bombCount << std::endl;

        inputStream >> nextWord;
        int x = std::stoi(nextWord);
        std::cout << x << std::endl;

        inputStream >> nextWord;
        int y = std::stoi(nextWord);
        std::cout << y << std::endl;

        //std::unique_ptr<std::vector<int>> ptr = std::make_unique<std::vector<int>>(H);
        //field.reset();
        //playerFieldVec.clear();
        //playerFieldVec.reserve(H);

        field = std::make_unique<Field>(x,y,0,0,true);
        for (int n = 0; n < y; n++){
            for (int i = 0; i < x; i++){
                inputStream >> nextWord;
                field->changeFieldVec(n, i, std::stoi(nextWord));
            }
        }

        std::cout << *field << std::endl;

        inputStream >> nextWord;
        x = std::stoi(nextWord);
        std::cout << x << std::endl;

        inputStream >> nextWord;
        y = std::stoi(nextWord);
        std::cout << y << std::endl;

        for (int n = 0; n < y; n++){
            for (int i = 0; i < x; i++){
                inputStream >> nextWord;
                playerFieldVec.at(n)->at(i) = std::stoi(nextWord);
                //ptr->push_back(std::stoi(nextWord));
            }
            //playerFieldVec.push_back(std::move(ptr));
        }
    }
}