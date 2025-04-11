#include "GameWindow.h"
#include "menu.h"

void GameWindow::drawMainMenu(AnimationWindow& win){
    // Menu Background and Text
    win.draw_image(TDT4102::Point {0,0}, *pictures.at("menuBackground"));
    win.draw_image(TDT4102::Point {720 - 225, 450 - 275},
    *pictures.at("optionsBackground"));
    
    //SKAL VÆRE NAVNET PÅ SPILLET
    win.draw_image(TDT4102::Point {720 - 150, 450 - 250},
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

    // Exit Button
    if (mouseOnBottomMenuButton() && leftClick(*this)){
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2 + optionButtonPad + optionButtonHeight}, 
        *pictures.at("quitDark"));
    } else {
        win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2 + optionButtonPad + optionButtonHeight}, 
        *pictures.at("quit")); }
}

void GameWindow::drawPauseMenu(AnimationWindow& win){
    // Menu background and Text
    win.draw_image(TDT4102::Point {0,0}, *pictures.at("menuBackground"));
    win.draw_image(TDT4102::Point {720 - optionButtonWidth/2 - 50, 450 - optionButtonHeight/2 - optionButtonPad - optionButtonHeight - 150},
    *pictures.at("optionsBackground"));

    // Paused
    win.draw_image(TDT4102::Point {720 - 150, 450 - 250},
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

    // Quit Button
    if (mouseOnBottomMenuButton() && leftClick(*this)){
        bottomOptionColor = color;
    }
    else {
        bottomOptionColor = menuButtonColor;
    }
    win.draw_image(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2 + optionButtonPad + optionButtonHeight}, *pictures.at("exit"));

}

void GameWindow::drawPauseMenuButton(AnimationWindow& win){

}

void GameWindow::drawYouWin(AnimationWindow& win){
    // Menu background and Text
    win.draw_rectangle(TDT4102::Point {720 - optionButtonWidth/2 - 50, 450 - optionButtonHeight/2 - optionButtonPad - optionButtonHeight - 150}, 100 + optionButtonWidth, 200 + 3*optionButtonHeight + 2*optionButtonPad);
    win.draw_text(TDT4102::Point {720 - 117, 450 - optionButtonHeight/2 - optionButtonPad - optionButtonHeight - 100}, "YOU WIN!", TDT4102::Color::red, 60, Font::courier_bold);
    win.draw_text(TDT4102::Point {720 - 115, 450 - optionButtonHeight/2 - optionButtonPad - optionButtonHeight - 25}, "Time spent: " + to_string(static_cast<int>(frozenTimer + savedTimer)) + "s", TDT4102::Color::red, 30, Font::courier_bold);

    // Points right side
    TDT4102::Point rightUpper = {720 - optionButtonWidth/2 + optionButtonWidth, 450 - 2*optionButtonHeight - optionButtonPad/2 -optionButtonPad};
    TDT4102::Point rightLower = {720 - optionButtonWidth/2 + optionButtonWidth, 450 - optionButtonHeight - optionButtonPad/2 -optionButtonPad};
    TDT4102::Point rightOuter = {720 - optionButtonWidth/2 + optionButtonWidth + optionTriangleHeight, 450 - static_cast<int>(1.5*optionButtonHeight) - optionButtonPad/2 -optionButtonPad};

    // Points left side
    TDT4102::Point leftUpper = {720 - optionButtonWidth/2, 450 - 2*optionButtonHeight - optionButtonPad/2 -optionButtonPad};
    TDT4102::Point leftLower = {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2 -optionButtonPad};
    TDT4102::Point leftOuter = {720 - optionButtonWidth/2 - optionTriangleHeight, 450 - static_cast<int>(1.5*optionButtonHeight) - optionButtonPad/2 -optionButtonPad};

   // New Game Button
    if (mouseOnTopMiddleMenuButton() && leftClick(*this)){
        topMiddleOptionColor = color;
    }
    else{
        topMiddleOptionColor = menuButtonColor;
    }
    win.draw_rectangle(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, optionButtonWidth, optionButtonHeight, topMiddleOptionColor);
    win.draw_triangle(TDT4102::Point {rightUpper.x, rightUpper.y + optionButtonHeight + optionButtonPad}, 
    TDT4102::Point {rightOuter.x, rightOuter.y + optionButtonHeight + optionButtonPad}, TDT4102::Point {rightLower.x,
    rightLower.y + optionButtonHeight + optionButtonPad}, topMiddleOptionColor);
    win.draw_triangle(TDT4102::Point {leftUpper.x, leftUpper.y + optionButtonHeight + optionButtonPad}, 
    TDT4102::Point {leftLower.x, leftLower.y + optionButtonHeight + optionButtonPad}, TDT4102::Point {leftOuter.x,
    leftOuter.y + optionButtonHeight + optionButtonPad}, topMiddleOptionColor);
    win.draw_text(TDT4102::Point {720 - 88, 450 - optionButtonHeight - optionButtonPad/2 + 9}, "New Game", TDT4102::Color::red, 45, Font::courier_bold);

    // Main Menu Button
    if (mouseOnBottomMiddleMenuButton() && leftClick(*this)){
        bottomMiddleOptionColor = color;
    }
    else {
        bottomMiddleOptionColor = menuButtonColor;
    }
    win.draw_rectangle(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, optionButtonWidth, optionButtonHeight, bottomMiddleOptionColor);
    win.draw_triangle(TDT4102::Point {rightUpper.x, rightUpper.y + 2*(optionButtonHeight + optionButtonPad),}, 
    TDT4102::Point {rightOuter.x, rightOuter.y + 2*(optionButtonHeight + optionButtonPad)}, TDT4102::Point {rightLower.x,
    rightLower.y + 2*(optionButtonHeight + optionButtonPad)}, bottomMiddleOptionColor);
    win.draw_triangle(TDT4102::Point {leftUpper.x, leftUpper.y + 2*(optionButtonHeight + optionButtonPad)}, 
    TDT4102::Point {leftLower.x, leftLower.y + 2*(optionButtonHeight + optionButtonPad)}, TDT4102::Point {leftOuter.x,
    leftOuter.y + 2*(optionButtonHeight + optionButtonPad)}, bottomMiddleOptionColor);
    win.draw_text(TDT4102::Point {720 - 110, 450 + optionButtonPad/2 + 9}, "Main Menu", TDT4102::Color::red, 45, Font::courier_bold);
}

void GameWindow::drawYouDied(AnimationWindow& win){
    // Menu background and Text
    win.draw_rectangle(TDT4102::Point {720 - optionButtonWidth/2 - 50, 450 - optionButtonHeight/2 - optionButtonPad - optionButtonHeight - 150}, 100 + optionButtonWidth, 200 + 3*optionButtonHeight + 2*optionButtonPad);
    win.draw_text(TDT4102::Point {720 - 135, 450 - optionButtonHeight/2 - optionButtonPad - optionButtonHeight - 100}, "You died.", TDT4102::Color::red, 60, Font::courier_bold);
    win.draw_text(TDT4102::Point {720 - 115, 450 - optionButtonHeight/2 - optionButtonPad - optionButtonHeight - 25}, "Time spent: " + to_string(static_cast<int>(frozenTimer + savedTimer)) + "s", TDT4102::Color::red, 30, Font::courier_bold);
    // Points right side
    TDT4102::Point rightUpper = {720 - optionButtonWidth/2 + optionButtonWidth, 450 - 2*optionButtonHeight - optionButtonPad/2 -optionButtonPad};
    TDT4102::Point rightLower = {720 - optionButtonWidth/2 + optionButtonWidth, 450 - optionButtonHeight - optionButtonPad/2 -optionButtonPad};
    TDT4102::Point rightOuter = {720 - optionButtonWidth/2 + optionButtonWidth + optionTriangleHeight, 450 - static_cast<int>(1.5*optionButtonHeight) - optionButtonPad/2 -optionButtonPad};

    // Points left side
    TDT4102::Point leftUpper = {720 - optionButtonWidth/2, 450 - 2*optionButtonHeight - optionButtonPad/2 -optionButtonPad};
    TDT4102::Point leftLower = {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2 -optionButtonPad};
    TDT4102::Point leftOuter = {720 - optionButtonWidth/2 - optionTriangleHeight, 450 - static_cast<int>(1.5*optionButtonHeight) - optionButtonPad/2 -optionButtonPad};

   // New Game Button
    if (mouseOnTopMiddleMenuButton() && leftClick(*this)){
        topMiddleOptionColor = color;
    }
    else{
        topMiddleOptionColor = menuButtonColor;
    }
    win.draw_rectangle(TDT4102::Point {720 - optionButtonWidth/2, 450 - optionButtonHeight - optionButtonPad/2}, optionButtonWidth, optionButtonHeight, topMiddleOptionColor);
    win.draw_triangle(TDT4102::Point {rightUpper.x, rightUpper.y + optionButtonHeight + optionButtonPad}, 
    TDT4102::Point {rightOuter.x, rightOuter.y + optionButtonHeight + optionButtonPad}, TDT4102::Point {rightLower.x,
    rightLower.y + optionButtonHeight + optionButtonPad}, topMiddleOptionColor);
    win.draw_triangle(TDT4102::Point {leftUpper.x, leftUpper.y + optionButtonHeight + optionButtonPad}, 
    TDT4102::Point {leftLower.x, leftLower.y + optionButtonHeight + optionButtonPad}, TDT4102::Point {leftOuter.x,
    leftOuter.y + optionButtonHeight + optionButtonPad}, topMiddleOptionColor);
    win.draw_text(TDT4102::Point {720 - 88, 450 - optionButtonHeight - optionButtonPad/2 + 9}, "New Game", TDT4102::Color::red, 45, Font::courier_bold);

    // Main Menu Button
    if (mouseOnBottomMiddleMenuButton() && leftClick(*this)){
        bottomMiddleOptionColor = color;
    }
    else {
        bottomMiddleOptionColor = menuButtonColor;
    }
    win.draw_rectangle(TDT4102::Point {720 - optionButtonWidth/2, 450 + optionButtonPad/2}, optionButtonWidth, optionButtonHeight, bottomMiddleOptionColor);
    win.draw_triangle(TDT4102::Point {rightUpper.x, rightUpper.y + 2*(optionButtonHeight + optionButtonPad),}, 
    TDT4102::Point {rightOuter.x, rightOuter.y + 2*(optionButtonHeight + optionButtonPad)}, TDT4102::Point {rightLower.x,
    rightLower.y + 2*(optionButtonHeight + optionButtonPad)}, bottomMiddleOptionColor);
    win.draw_triangle(TDT4102::Point {leftUpper.x, leftUpper.y + 2*(optionButtonHeight + optionButtonPad)}, 
    TDT4102::Point {leftLower.x, leftLower.y + 2*(optionButtonHeight + optionButtonPad)}, TDT4102::Point {leftOuter.x,
    leftOuter.y + 2*(optionButtonHeight + optionButtonPad)}, bottomMiddleOptionColor);
    win.draw_text(TDT4102::Point {720 - 110, 450 + optionButtonPad/2 + 9}, "Main Menu", TDT4102::Color::red, 45, Font::courier_bold);
}

void GameWindow::drawControls(AnimationWindow& win){
    win.draw_rectangle({0,0}, 1440, 900, TDT4102::Color::navy);
    win.draw_rectangle({20,20}, 90, 45, TDT4102::Color::dark_gray);
    win.draw_text({20,20}, "Back", TDT4102::Color::red, 35, Font::courier_bold);
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
            loadGame();
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
}
