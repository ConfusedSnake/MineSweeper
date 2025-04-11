#pragma once
#include "std_lib_facilities.h"
#include "Input.h"

class Player{
    private:
    int playerX;
    int playerY;
    char playerDirection = 'R';

    std::chrono::steady_clock::time_point lastMoveTime;
    const std::chrono::milliseconds moveDelay = std::chrono::milliseconds(200);

    public:
    
    Player();

    bool canMove();

    char getDirection(){
        return playerDirection;
    }
    
    int getPlayerY(){
        return playerY;
    }
    int getPlayerX(){
        return playerX;
    }

    void changePlayerY(int positionY){
        playerY = positionY;
    }

    void changePlayerX(int positionX){
        playerX = positionX;
    }

    void changeDirection(char direc){
        playerDirection = direc;
    }

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
};
