#pragma once
#include "std_lib_facilities.h"
#include "Input.h"

class Player{
    private:
    int W = 30;
    int H = 16;
    int playerX = 0;
    int playerY = 0;
    char playerDirection = 'R';

    std::chrono::steady_clock::time_point lastMoveTime;
    const std::chrono::milliseconds moveDelay = std::chrono::milliseconds(200); // 200 ms delay

    public:

    Player();

    bool canMove();
    
    int getPlayerY(){
        return playerY;
    }
    int getPlayerX(){
        return playerX;
    }

    void moveLeft(AnimationWindow& win);
    void moveRight(AnimationWindow& win);
    void moveUp(AnimationWindow& win);
    void moveDown(AnimationWindow& win);

};
