#pragma once
#include "std_lib_facilities.h"
#include "Keybinds.h"

class Player {
    private:

    Keybinds key;

    int W = 30;
    int H = 16;
    int playerX = 0;
    int playerY = 7;

    
    bool facingEast = true;
    bool facingWest = false;
    bool facingNorth = false;
    bool facingSouth = false;

    std::vector<std::unique_ptr<std::vector<int>>> playerPositionVec;

    public:
    
    Player();
    void movement();

    const std::vector<std::unique_ptr<std::vector<int>>>& getPlayer() const {
       return playerPositionVec;
    }
};
std::ostream& operator<<(std::ostream& os, const Player& player);
