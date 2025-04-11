#include "GameWindow.h"
#include "menu.h"

void GameWindow::drawMainMenu(){
    // Menu Background
    draw_image(TDT4102::Point {0,0}, *pictures.at("menuBackground"));
    draw_image(TDT4102::Point {720 - 225, 450 - 275},
    *pictures.at("optionsBackground"));
    
    // No Mans Land
    draw_image(TDT4102::Point {720 - 450, 10},
    *pictures.at("noMansLand"));


    // Main Menu
    draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 250},
    *pictures.at("mainMenu"));

    // Start Button
    if (mouseOnTopMenuButton() && leftClick(*this)){
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 2*optionButtonHeight - optionButtonPad/2 -optionButtonPad}, 
        *pictures.at("newGameDark")); 
    } else{
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 2*optionButtonHeight - optionButtonPad/2 -optionButtonPad}, 
        *pictures.at("newGame")); }
    
    // Load Button
    if (mouseOnTopMiddleMenuButton() && leftClick(*this)){
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, 
        *pictures.at("loadGameDark"));
    } else{ 
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2},
        *pictures.at("loadGame")); }
    
    // Controls Button
    if (mouseOnBottomMiddleMenuButton() && leftClick(*this)){
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, 
        *pictures.at("controlsDark"));
    } else {
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, 
        *pictures.at("controls")); }

    // Quit Button
    if (mouseOnBottomMenuButton() && leftClick(*this)){
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2 + optionButtonPad + optionButtonHeight}, 
        *pictures.at("quitDark"));
    } else {
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2 + optionButtonPad + optionButtonHeight}, 
        *pictures.at("quit")); }
}

void GameWindow::drawPauseMenu(){
    // Menu Background
    draw_image(TDT4102::Point {0,0}, *pictures.at("menuBackground"));
    draw_image(TDT4102::Point {720 - 225, 450 - 275},
    *pictures.at("optionsBackground"));
    
    // Paused
    draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 250},
    *pictures.at("paused"));

    // Resume Button
    if (mouseOnTopMenuButton() && leftClick(*this)){
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 2*optionButtonHeight - optionButtonPad/2 -optionButtonPad}, *pictures.at("resumeDark"));
    }
    else{
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 2*optionButtonHeight - optionButtonPad/2 -optionButtonPad}, *pictures.at("resume"));
    }

    // Save Button
    if (mouseOnTopMiddleMenuButton() && leftClick(*this)){
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, *pictures.at("saveGameDark"));
    }
    else{
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, *pictures.at("saveGame"));
    }
    // Controls Button
    if (mouseOnBottomMiddleMenuButton() && leftClick(*this)){
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, *pictures.at("controlsDark"));
    }
    else {
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, *pictures.at("controls"));
    }

    // Exit Button
    if (mouseOnBottomMenuButton() && leftClick(*this)){
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2 + optionButtonPad + optionButtonHeight}, *pictures.at("exitDark"));
    }
    else {
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2 + optionButtonPad + optionButtonHeight}, *pictures.at("exit"));
    }
}

void GameWindow::drawPauseMenuButton(){
    draw_image(TDT4102::Point {10, 10 + yMove}, *pictures.at("options"), 60, 60);
}

void GameWindow::drawYouWin(){
    // Menu background
    //draw_image(TDT4102::Point {0,0}, *pictures.at("menuBackground"));
    draw_image(TDT4102::Point {720 - 225, 450 - 275},
    *pictures.at("optionsBackground"));

    // You Win!

    draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 250}, *pictures.at("youWin"));

    // Time spent

    draw_image(TDT4102::Point {720 - 150, 450 - 170}, *pictures.at("timeSpent"), 200, 47);
    draw_text(TDT4102::Point {720 + 40, 450 - 165}, to_string(static_cast<int>(frozenTimer + savedTimer)) + "s", TDT4102::Color::red, 30, Font::courier_bold);

   // New Game Button
    if (mouseOnTopMiddleMenuButton() && leftClick(*this)){
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, *pictures.at("newGameDark"));
    }
    else{
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, *pictures.at("newGame"));
    }

    // Exit Button

    if (mouseOnBottomMiddleMenuButton() && leftClick(*this)){
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, *pictures.at("exitDark"));
    }
    else {
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, *pictures.at("exit"));
    }
}

void GameWindow::drawYouDied(){
    // Menu background
    //draw_image(TDT4102::Point {0,0}, *pictures.at("menuBackground"));
    draw_image(TDT4102::Point {720 - 225, 450 - 275},
    *pictures.at("optionsBackground"));

    // You Died

    draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 250}, *pictures.at("youDied"));

    // Time spent

    draw_image(TDT4102::Point {720 - 150, 450 - 170}, *pictures.at("timeSpent"), 200, 47);
    draw_text(TDT4102::Point {720 + 40, 450 - 165}, to_string(static_cast<int>(frozenTimer + savedTimer)) + "s", TDT4102::Color::red, 30, Font::courier_bold);

   // New Game Button
    if (mouseOnTopMiddleMenuButton() && leftClick(*this)){
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, *pictures.at("newGameDark"));
    }
    else{
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, *pictures.at("newGame"));
    }

    // Exit Button

    if (mouseOnBottomMiddleMenuButton() && leftClick(*this)){
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, *pictures.at("exitDark"));
    }
    else {
        draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, *pictures.at("exit"));
    }
}

void GameWindow::drawControls(){
    // Background
    draw_image(TDT4102::Point {0,0}, *pictures.at("menuBackground"));
    draw_image(TDT4102::Point {720 - 225, 450 - 275},
    *pictures.at("controlsMenu"));
    
    // Button
    if (mouseOnBackButton() && leftClick(*this)){
        draw_image(TDT4102::Point {10,10}, *pictures.at("backDark"));
    }
    else{
        draw_image(TDT4102::Point {10,10}, *pictures.at("back"));
    }
}

bool GameWindow::mouseOnTopMenuButton(){
    if ((coordinates().x >= 720 - optionButtonWidth/2) && (coordinates().x <= 720 + optionButtonWidth/2) &&
    (coordinates().y >= 450 - 2*optionButtonHeight - optionButtonPad/2 -optionButtonPad)
    && (coordinates().y <= 450 - optionButtonHeight - optionButtonPad/2 -optionButtonPad)){
        return true;
    }
    return false;
}
    
bool GameWindow::mouseOnTopMiddleMenuButton(){
    if ((coordinates().x >= 720 - optionButtonWidth/2) && (coordinates().x <= 720 + optionButtonWidth/2) &&
    (coordinates().y >= 450 - optionButtonHeight - optionButtonPad/2) &&
    (coordinates().y <= 450 - optionButtonPad)){
        return true;
    }
    return false;
}

bool GameWindow::mouseOnBottomMiddleMenuButton(){
    if ((coordinates().x >= 720 - optionButtonWidth/2) && (coordinates().x <= 720 + optionButtonWidth/2) &&
    (coordinates().y >= 450 + optionButtonPad/2) &&
    (coordinates().y <= 450 + optionButtonPad/2 + optionButtonHeight)){
        return true;
    }
    return false;
}
    
bool GameWindow::mouseOnBottomMenuButton(){
    if ((coordinates().x >= 720 - optionButtonWidth/2) && (coordinates().x <= 720 + optionButtonWidth/2) &&
    (coordinates().y >= 450 + optionButtonPad/2 + optionButtonPad + optionButtonHeight) &&
    (coordinates().y <= 450 + optionButtonPad/2 + optionButtonPad + 2*optionButtonHeight)){
        return true;
    }
    return false;
}

bool GameWindow::mouseOnBackButton(){
    if ((coordinates().x >= 10) && (coordinates().x <= 200 + 10) &&
    (coordinates().y >= 10) &&
    (coordinates().y <= 200 + 10)){
        return true;
    }
    return false;
}

bool GameWindow::mouseOnOptionsButton(){
    if ((coordinates().x >= 17) && (coordinates().x <= 63) &&
    (coordinates().y >= 17) &&
    (coordinates().y <= 63)){
        return true;
    }
    return false;
}

void GameWindow::menuClicks(){
    // Toggle Pause Menu med ESC
    if (ESCclicked(*this) && !controls && !mainMenuOpen){
        pauseMenuOpen = !pauseMenuOpen;
        if (pauseMenuOpen) {
            savedTimer += frozenTimer;
        }
    }


    // Top button : New Game / Resume
    if (mouseOnTopMenuButton() && mouseClickedLeft(*this) && !controls){
        if (mainMenuOpen){
            reset();
            mainMenuOpen = false;
        }
        else if (pauseMenuOpen){
            pauseMenuOpen = false;
        }
    }

    // Top-Middle button : LoadGame / SaveGame
    if (mouseOnTopMiddleMenuButton() && mouseClickedLeft(*this) && !controls){
        if (mainMenuOpen){
            try
            {
                loadGame();
                mainMenuOpen = false;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else if (pauseMenuOpen){
            saveGame();
        }
        else if (youDied || youWin){
            reset();
            youDied = false;
            youWin = false;
        }
    }

    // Bottom-Middle button : Controls / Exit
    if (mouseOnBottomMiddleMenuButton() && mouseClickedLeft(*this) && !controls){
        // insert controls pic
        if (mainMenuOpen || pauseMenuOpen){
            controls = true;
        }
        else if(youDied || youWin){
            mainMenuOpen = true;
            youDied = false;
            youWin = false;
        }
    }

    // // Bottom button : Exit / Quit
    if (mouseOnBottomMenuButton() && mouseClickedLeft(*this) && !controls){
        if (mainMenuOpen){
            close();
        }
        else if (pauseMenuOpen){
            pauseMenuOpen = false;
            mainMenuOpen = true;
        }
    }

    // Back Button
    if (controls && mouseOnBackButton() && mouseClickedLeft(*this) && (mainMenuOpen || pauseMenuOpen)){
        controls = false;
    }

    // Options Button
    if (mouseOnOptionsButton() && mouseClickedLeft(*this) && !controls && !mainMenuOpen && !pauseMenuOpen){
        pauseMenuOpen = true;
        savedTimer += frozenTimer;
    }
}
