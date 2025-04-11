#include "GameWindow.h"
#include "menu.h"

void GameWindow::drawMainMenu(AnimationWindow& win){
    // Menu Background
    win.draw_image(TDT4102::Point {0,0}, *pictures.at("menuBackground"));
    win.draw_image(TDT4102::Point {720 - 225, 450 - 275},
    *pictures.at("optionsBackground"));
    
    //SKAL VÆRE NAVNET PÅ SPILLET
    win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 250},
    *pictures.at("paused"));

    // Start Button
    if (mouseOnTopMenuButton() && leftClick(*this)){
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 2*optionButtonHeight - optionButtonPad/2 -optionButtonPad}, 
        *pictures.at("newGameDark")); 
    } else{
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 2*optionButtonHeight - optionButtonPad/2 -optionButtonPad}, 
        *pictures.at("newGame")); }
    
    // Load Button
    if (mouseOnTopMiddleMenuButton() && leftClick(*this)){
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, 
        *pictures.at("loadGameDark"));
    } else{ 
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2},
        *pictures.at("loadGame")); }
    
    // Controls Button
    if (mouseOnBottomMiddleMenuButton() && leftClick(*this)){
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, 
        *pictures.at("controlsDark"));
    } else {
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, 
        *pictures.at("controls")); }

    // Quit Button
    if (mouseOnBottomMenuButton() && leftClick(*this)){
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2 + optionButtonPad + optionButtonHeight}, 
        *pictures.at("quitDark"));
    } else {
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2 + optionButtonPad + optionButtonHeight}, 
        *pictures.at("quit")); }
}

void GameWindow::drawPauseMenu(AnimationWindow& win){
    // Menu Background
    win.draw_image(TDT4102::Point {0,0}, *pictures.at("menuBackground"));
    win.draw_image(TDT4102::Point {720 - 225, 450 - 275},
    *pictures.at("optionsBackground"));
    
    // Paused
    win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 250},
    *pictures.at("paused"));

    // Resume Button
    if (mouseOnTopMenuButton() && leftClick(*this)){
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 2*optionButtonHeight - optionButtonPad/2 -optionButtonPad}, *pictures.at("resumeDark"));
    }
    else{
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 2*optionButtonHeight - optionButtonPad/2 -optionButtonPad}, *pictures.at("resume"));
    }

    // Save Button
    if (mouseOnTopMiddleMenuButton() && leftClick(*this)){
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, *pictures.at("saveGameDark"));
    }
    else{
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, *pictures.at("saveGame"));
    }
    // Controls Button
    if (mouseOnBottomMiddleMenuButton() && leftClick(*this)){
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, *pictures.at("controlsDark"));
    }
    else {
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, *pictures.at("controls"));
    }

    // Exit Button
    if (mouseOnBottomMenuButton() && leftClick(*this)){
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2 + optionButtonPad + optionButtonHeight}, *pictures.at("exitDark"));
    }
    else {
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2 + optionButtonPad + optionButtonHeight}, *pictures.at("exit"));
    }
}

void GameWindow::drawPauseMenuButton(AnimationWindow& win){
    draw_image(TDT4102::Point {10, 10}, *pictures.at("options"), 60, 60);
}

void GameWindow::drawYouWin(AnimationWindow& win){
    // Menu background
    win.draw_image(TDT4102::Point {0,0}, *pictures.at("menuBackground"));
    win.draw_image(TDT4102::Point {720 - 225, 450 - 275},
    *pictures.at("optionsBackground"));

    // You Win!

    win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 250}, *pictures.at("youWin"));

    // Time spent

    win.draw_image(TDT4102::Point {720 - 150, 450 - 170}, *pictures.at("timeSpent"), 200, 47);
    win.draw_text(TDT4102::Point {720 + 40, 450 - 165}, to_string(static_cast<int>(frozenTimer + savedTimer)) + "s", TDT4102::Color::red, 30, Font::courier_bold);

   // New Game Button
    if (mouseOnTopMiddleMenuButton() && leftClick(*this)){
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, *pictures.at("newGameDark"));
    }
    else{
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, *pictures.at("newGame"));
    }

    // Exit Button

    if (mouseOnBottomMiddleMenuButton() && leftClick(*this)){
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, *pictures.at("exitDark"));
    }
    else {
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, *pictures.at("exit"));
    }
}

void GameWindow::drawYouDied(AnimationWindow& win){
    // Menu background
    win.draw_image(TDT4102::Point {0,0}, *pictures.at("menuBackground"));
    win.draw_image(TDT4102::Point {720 - 225, 450 - 275},
    *pictures.at("optionsBackground"));

    // You Died

    win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - 250}, *pictures.at("youDied"));

    // Time spent

    win.draw_image(TDT4102::Point {720 - 150, 450 - 170}, *pictures.at("timeSpent"), 200, 47);
    win.draw_text(TDT4102::Point {720 + 40, 450 - 165}, to_string(static_cast<int>(frozenTimer + savedTimer)) + "s", TDT4102::Color::red, 30, Font::courier_bold);

   // New Game Button
    if (mouseOnTopMiddleMenuButton() && leftClick(*this)){
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, *pictures.at("newGameDark"));
    }
    else{
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, *pictures.at("newGame"));
    }

    // Exit Button

    if (mouseOnBottomMiddleMenuButton() && leftClick(*this)){
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, *pictures.at("exitDark"));
    }
    else {
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, *pictures.at("exit"));
    }
}

void GameWindow::drawControls(AnimationWindow& win){
    // Background
    win.draw_image(TDT4102::Point {0,0}, *pictures.at("menuBackground"));
    win.draw_image(TDT4102::Point {720 - 225, 450 - 275},
    *pictures.at("optionsBackground"));
    
    // Button
    if (mouseOnBackButton() && leftClick(*this)){
        win.draw_image(TDT4102::Point {10,10}, *pictures.at("backDark"));
    }
    else{
        win.draw_image(TDT4102::Point {10,10}, *pictures.at("back"));
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
    // Top button
    if (mouseOnTopMenuButton() && mouseClickedLeft(*this)){
        if (mainMenuOpen){
            reset();
        }
        else if (pauseMenuOpen){
            pauseMenuOpen = false;
        }
    }

    // Top-Middle button
    if (mouseOnTopMiddleMenuButton() && mouseClickedLeft(*this)){
        if (mainMenuOpen){
            try
            {
                loadGame();
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
        }
    }

    // Bottom-Middle button
    if (mouseOnBottomMiddleMenuButton() && mouseClickedLeft(*this)){
        // insert controls pic
        if (mainMenuOpen || pauseMenuOpen){
            controls = true;
        }
        else if(youDied || youWin){
            mainMenuOpen = true;
        }
    }

    // // Bottom button
    if (mouseOnBottomMenuButton() && mouseClickedLeft(*this)){
        if (mainMenuOpen){
            close();
        }
        else if (pauseMenuOpen){
            pauseMenuOpen = false;
            mainMenuOpen = true;
        }
    }

    // Back Button

    if (mouseOnBackButton() && mouseClickedLeft(*this) && controls && !mainMenuOpen && !pauseMenuOpen){
        controls = false;
        pauseMenuOpen = true;
    }

    // Options Button

    if (mouseOnOptionsButton() && mouseClickedLeft(*this) && !controls && !mainMenuOpen){
        pauseMenuOpen = true;
    }


}

void GameWindow::drawMenus(AnimationWindow& win){
    if (mainMenuOpen){
        drawMainMenu(*this);
    }

    else if (pauseMenuOpen){
        drawPauseMenu(*this);
    }

    else if (controls){
        drawControls(*this);
    }
    
    else if (youDied){
        drawYouDied(*this);
    }
    
    else if (youWin){
        drawYouWin(*this);
    }

    if (!mainMenuOpen && !pauseMenuOpen && !controls && !youWin && !youDied){
        drawPauseMenuButton(*this);
        resetButton.setVisible(true);
    }
    else{
        resetButton.setVisible(false);
    }
}