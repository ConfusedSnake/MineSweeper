#include "Player.h"

Player::Player(){
    playerX = 0;
    playerY = 0;
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

void Player::moveLeft(){
    if (!canMove()) return;
    playerDirection = 'L';
    playerX--;
}

void Player::moveRight(){ 
    if (!canMove()) return;
    playerDirection = 'R';
    playerX++;
}

void Player::moveUp(){
    if (!canMove()) return;
    playerDirection = 'U';
    playerY--;
}

void Player::moveDown(){
    if (!canMove()) return;
    playerDirection = 'D';
    playerY++;
}