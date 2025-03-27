#include "Input.h"

bool up(TDT4102::AnimationWindow& win){
    return win.is_key_down(KeyboardKey::UP);
}

bool upClicked(TDT4102::AnimationWindow& win) {
    static bool isButtonPressed = false;

    if (up(win)) {
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

bool down(TDT4102::AnimationWindow& win){
    return win.is_key_down(KeyboardKey::DOWN);
}

bool downClicked(TDT4102::AnimationWindow& win) {
    static bool isButtonPressed = false;

    if (down(win)) {
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

bool left(TDT4102::AnimationWindow& win){
    return win.is_key_down(KeyboardKey::LEFT);
}

bool leftClicked(TDT4102::AnimationWindow& win) {
    static bool isButtonPressed = false;

    if (left(win)) {
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

bool right(TDT4102::AnimationWindow& win){
    return win.is_key_down(KeyboardKey::RIGHT);
}

bool rightClicked(TDT4102::AnimationWindow& win) {
    static bool isButtonPressed = false;

    if (right(win)) {
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


bool leftClick(TDT4102::AnimationWindow& win){
    return win.is_left_mouse_button_down();
}

bool rightClick(TDT4102::AnimationWindow& win){
    return win.is_right_mouse_button_down();
}

bool mouseClickedLeft(TDT4102::AnimationWindow& win) {
    static bool isButtonPressed = false;

    if (leftClick(win)) {
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

bool mouseClickedRight(TDT4102::AnimationWindow& win) {
    static bool isButtonPressed = false;

    if (rightClick(win)) {
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
