#include "Keybinds.h"

bool Keybinds::up(){
    return TDT4102::AnimationWindow::is_key_down(KeyboardKey::UP);
}

bool Keybinds::upClicked() {
    static bool isButtonPressed = false;

    if (up()) {
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

bool Keybinds::down(){
    return TDT4102::AnimationWindow::is_key_down(KeyboardKey::DOWN);
}

bool Keybinds::downClicked() {
    static bool isButtonPressed = false;

    if (down()) {
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

bool Keybinds::left(){
    return TDT4102::AnimationWindow::is_key_down(KeyboardKey::LEFT);
}

bool Keybinds::leftClicked() {
    static bool isButtonPressed = false;

    if (left()) {
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

bool Keybinds::right(){
    return TDT4102::AnimationWindow::is_key_down(KeyboardKey::RIGHT);
}

bool Keybinds::rightClicked() {
    static bool isButtonPressed = false;

    if (right()) {
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