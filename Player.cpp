#include "Player.h"

Player::Player(){
    playerPositionVec.reserve(H);
    for (int i = 0; i < H; i++) {
        playerPositionVec.push_back(std::make_unique<std::vector<int>>(W, 0));
    }
    (*playerPositionVec[playerY])[playerX] = 1;
}

void Player::movement(){
    if (key.leftClicked()){
        facingWest = true;
        facingEast = false;
        facingNorth = false;
        facingSouth = false;
    }
    else if (key.leftClicked() && facingWest){
        try
        {
            (*playerPositionVec[playerY])[playerX] = 0;
            playerX--;
            (*playerPositionVec[playerY])[playerX] = 1;
        }
        catch(const std::exception& e)
        {
            std::cout << "Out of range" << "\n";
            std::cerr << e.what() << '\n';
        }
    }
    if (key.rightClicked()){
        facingEast = true;
        facingWest = false;
        facingNorth = false;
        facingSouth = false;
    }
    else if (key.rightClicked() && facingEast){
        try
        {
            (*playerPositionVec[playerY])[playerX] = 0;
            playerX++;
            (*playerPositionVec[playerY])[playerX] = 1;
        }
        catch(const std::exception& e)
        {
            std::cout << "Out of range" << "\n";
            std::cerr << e.what() << '\n';
        }
    }
    if (key.upClicked()){
        facingNorth = true;
        facingWest = false;
        facingEast = false;
        facingSouth = false;
    }
    else if (key.upClicked() && facingNorth){
        try
        {
            (*playerPositionVec[playerY])[playerX] = 0;
            playerY--;
            (*playerPositionVec[playerY])[playerX] = 1;
        }
        catch(const std::exception& e)
        {
            std::cout << "Out of range" << "\n";
            std::cerr << e.what() << '\n';
        }
    }
    if (key.downClicked()){
        facingSouth = true;
        facingWest = false;
        facingEast = false;
        facingNorth = false;
    }
    else if (key.downClicked() && facingSouth){
        try
        {
            (*playerPositionVec[playerY])[playerX] = 0;
            playerY++;
            (*playerPositionVec[playerY])[playerX] = 1;
        }
        catch(const std::exception& e)
        {
            std::cout << "Out of range" << "\n";
            std::cerr << e.what() << '\n';
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    for (const auto& row : player.getPlayer()) {
        for (int val : *row) {
            os << val << " ";
        }
        os << std::endl;
    }
    return os;
}