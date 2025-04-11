#include "GameWindow.h"

GameWindow::GameWindow(TDT4102::Point position, int width, int height, const std::string& title): 
    AnimationWindow{position.x, position.y, width, height, title},
    resetButton{TDT4102::Point {xOffset, 20}, 100, 30, "Reset"}
{

    // ==================== Pictures on field ==================== //
    std::map<int, std::string> numPic{
        {-1, "Art/Tall/bomb.png"},
        {0, "Art/Tall/nothing.png"},
        {1, "Art/Tall/one.png"}, 
        {2, "Art/Tall/two.png"}, 
        {3, "Art/Tall/three.png"}, 
        {4, "Art/Tall/four.png"}, 
        {5, "Art/Tall/five.png"}, 
        {6, "Art/Tall/six.png"}, 
        {7, "Art/Tall/seven.png"},
        {8, "Art/Tall/eight.png"},
        {9, "Art/Tall/flag.png"}
    };

    for (const auto& [key, filename] : numPic) {
        images[key] = std::make_unique<TDT4102::Image>(filename);
    }

    // ==================== Pictures not on field ==================== //
    std::map<std::string, std::string> imageMap {
        {"backgroundTop", "Art/Background/background3.png"},
        {"upDark", "Art/arrowKeys/upDark.png"},
        {"upLight", "Art/arrowKeys/upLight.png"},
        {"downDark", "Art/arrowKeys/downDark.png"},
        {"downLight", "Art/arrowKeys/downLight.png"},
        {"leftDark", "Art/arrowKeys/leftDark.png"},
        {"leftLight", "Art/arrowKeys/leftLight.png"},
        {"rightDark", "Art/arrowKeys/rightDark.png"},
        {"rightLight", "Art/arrowKeys/rightLight.png"},
        {"spaceLight", "Art/arrowKeys/spaceLight.png"},
        {"spaceDark", "Art/arrowKeys/spaceDark.png"},
        {"bombCount", "Art/arrowKeys/bombCount.png"},

        {"groundLight","Art/Tall/groundLight.png"},
        {"groundDark","Art/Tall/groundDark.png"},
        {"dirt","Art/Tall/dirt.png"},
        {"grassBot","Art/Tall/grassBot.png"},
        {"grassRight","Art/Tall/grassRight.png"},
        {"grassLeft","Art/Tall/grassLeft.png"},
        {"grassTop","Art/Tall/grassTop.png"},

        {"playerDown", "Art/Character/PlayerDown.png"},
        {"playerRight", "Art/Character/PlayerRight.png"},
        {"playerUp", "Art/Character/PlayerUp.png"},
        {"playerLeft", "Art/Character/PlayerLeft.png"},

        {"controls", "Art/MenuArt/Controls.png"},
        {"quit", "Art/MenuArt/Quit.png"},
        {"resume", "Art/MenuArt/Resume.png"},
        {"saveGame", "Art/MenuArt/SaveGame.png"},
        {"loadGame", "Art/MenuArt/LoadGame.png"},
        {"newGame", "Art/MenuArt/newGame.png"},
        {"exit", "Art/MenuArt/Exit.png"},
        {"back", "Art/MenuArt/Back.png"},
        {"controlsDark", "Art/MenuArt/ControlsDark.png"},
        {"quitDark", "Art/MenuArt/QuitDark.png"},
        {"resumeDark", "Art/MenuArt/ResumeDark.png"},
        {"saveGameDark", "Art/MenuArt/SaveGameDark.png"},
        {"loadGameDark", "Art/MenuArt/LoadGameDark.png"},
        {"newGameDark", "Art/MenuArt/newGameDark.png"},
        {"exitDark", "Art/MenuArt/ExitDark.png"},
        {"backDark", "Art/MenuArt/BackDark.png"},

        {"paused", "Art/MenuArt/Paused.png"},
        {"youDied", "Art/MenuArt/YouDied.png"},
        {"youWin", "Art/MenuArt/YouWin.png"},
        {"timeSpent", "Art/MenuArt/TimeSpent.png"},
        {"optionsBackground", "Art/MenuArt/OptionsBackground.png"},
        {"menuBackground", "Art/MenuArt/MenuBackground.png"},
        {"controlsMenu", "Art/MenuArt/ControlsMenu.png"},
        {"options", "Art/MenuArt/Options.png"},
        {"mainMenu", "Art/MenuArt/mainMenu.png"},
        {"noMansLand", "Art/MenuArt/NoMansLand.png"}


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


// ==================== Functions that runs the game ==================== //
void GameWindow::run() {
    std::filesystem::path fileName{"myFile.txt"};
    std::ifstream inputStream{fileName};
    bool started = false;
    reset();
 
    while (!should_close()) {
        
        menuClicks();
        resetButton.setVisible(false);
        if(controls){
            drawControls();
        } else if(mainMenuOpen){
            drawMainMenu();
            t.start();
        } else if(pauseMenuOpen){
            t.start();
            drawPauseMenu();
        } else{
            if(player->getPlayerX() == (W-1)){
                yMove = 0;
                youWin = true;
                drawGame(false);
                drawYouWin();
            }
            else if (dead){
                yMove = 0;
                drawGame(false);
                youDied = true;
                drawYouDied();
                
                if (!std::filesystem::is_empty("myFile.txt")){
                    std::ofstream file("myFile.txt", std::ios::trunc);
                }

            } else {
                frozenTimer = t.stop();
                drawGame(true);
                if(!spaceBar(*this)){
                    move();
                }
                if(spaceBar(*this)){
                    flagSpaceMode();
                }
            }

            if (keyRClicked(*this)){
                reset();
            }
        }
        
    next_frame();
    }
}

void GameWindow::move(){
    if (up(*this)){
        if(player->getPlayerY() != 0 && (*playerFieldVec[player->getPlayerY()-1])[player->getPlayerX()] != -1){
            player->moveUp();
            tileClick();
        }
        
    } else if (down(*this)){
        if(player->getPlayerY() != (H-1) && (*playerFieldVec[player->getPlayerY()+1])[player->getPlayerX()] != -1){
            player->moveDown();
            tileClick();
        }
        
    } else if (left(*this)){
        if(player->getPlayerX() != 0 &&(*playerFieldVec[player->getPlayerY()])[player->getPlayerX()-1] != -1){
            player->moveLeft();
            tileClick();
        }
        
    } else if (right(*this)){
        if(player->getPlayerX() != (W-1) && (*playerFieldVec[player->getPlayerY()])[player->getPlayerX()+1] != -1){
            player->moveRight();
            tileClick();
        }
        
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


void GameWindow::tileClick(){
    int x = player->getPlayerX();
    int y = player->getPlayerY();

    if((*field->getField()[y])[x] == -1){
        dead = true;
    }

    if (x != -1 && y != -1 && (*playerFieldVec[y])[x] == 0) {
        openUp(x, y);
    }
}

void GameWindow::openUp(int x, int y){
    if ((*playerFieldVec[y])[x] == 1) {
        return; 
    }

    (*playerFieldVec[y])[x] = 1;

    if ((*field->getField()[y])[x] == 0){
        for (int dy = -1; dy <= 1; ++dy) { 
            for (int dx = -1; dx <= 1; ++dx) { 
                if (dy == 0 && dx== 0){
                    continue;
                }

                int newY = y + dy;
                int newX = x + dx;

                if (newY >= 0 && newY < (field->getH()) && newX >= 0 && newX < (field->getW())) {
                    if (((*field->getField()[newY])[newX] == 0) && ((*playerFieldVec[newY])[newX] == 0)) {
                        openUp(newX, newY);
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

void GameWindow::flagSpace(){
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

void GameWindow::flagRightClick(){
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

void GameWindow::clearSave(){
    std::ofstream file("myFile.txt", std::ios::trunc);
    if (file.is_open()) {
        std::cout << "Filen ble clearet!\n";
        file.close();
    } else {
        std::cerr << "Kunne ikke åpne filen.\n";
    }
}

void GameWindow::reset(){
    playerFieldVec.clear();
    playerFieldVec.reserve(H);
    for (int i = 0; i < H; i++) {
        playerFieldVec.push_back(std::make_unique<std::vector<int>>(W, 0));
    }
    //field.reset();
    //player.reset();
    field = std::make_unique<Field>(W, H, 0, 0, false);
    player = std::make_unique<Player>();
    tileClick();

    dead = false;
    bombCount = 99;
    savedTimer = 0;
    t.start();
}

void GameWindow::saveGame(){
    clearSave();
    std::filesystem::path fileName{"myFile.txt"};
    std::ofstream outputStream{fileName};
    std::string line;

    outputStream << to_string(player->getPlayerX()) << " " << to_string(player->getPlayerY()) << std::endl;
    outputStream << to_string(savedTimer) << std::endl;
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

