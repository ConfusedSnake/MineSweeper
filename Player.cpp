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
    playerX--;
}

void Player::moveRight(AnimationWindow& win){ 
    if (!canMove()) return;
    playerDirection = 'R';
    playerX++;
}

void Player::moveUp(AnimationWindow& win){
    if (!canMove()) return;
    playerDirection = 'U';
    playerY--;
}

void Player::moveDown(AnimationWindow& win){
    if (!canMove()) return;
    playerDirection = 'D';
    playerY++;
}