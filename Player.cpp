#include "Player.h"

Player::Player(){
    lastMoveTime = std::chrono::steady_clock::now();
}

bool Player::canMove() {
    auto now = std::chrono::steady_clock::now();
    if (now - lastMoveTime >= moveDelay) {
        lastMoveTime = now;
        return true;
    }
    return false;
}

void Player::moveLeft(AnimationWindow& win){
    if (!canMove()) return;
    playerDirection = 'L';
    if (playerX == 0){
        std::cout << "Out of range";
    } else {
        playerX--;
    }
}

void Player::moveRight(AnimationWindow& win){ 
    if (!canMove()) return;
    playerDirection = 'R';
    if (playerX == (W-1)){
        std::cout << "Out of range";
    } else {
        playerX++;
    }
}

void Player::moveUp(AnimationWindow& win){
    if (!canMove()) return;
    playerDirection = 'U';
    if (playerY == 0){
        std::cout << "Out of range";
    } else {
        playerY--;
    }
}

void Player::moveDown(AnimationWindow& win){
    if (!canMove()) return;
    playerDirection = 'D';
    if (playerY == (H-1)){
        std::cout << "Out of range";
    } else {
        playerY++;
    }
}