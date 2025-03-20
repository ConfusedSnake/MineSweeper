#pragma once
#include "AnimationWindow.h"
#include "widgets/Button.h"
#include "mineField.h"
#include "std_lib_facilities.h"

#include <vector>


class GameWindow : public TDT4102::AnimationWindow
{
    private:
    static constexpr int cellSize = 30;
    Field field;

    std::vector<std::unique_ptr<std::vector<int>>> playerFieldVec;
    public:

    std::map<int, std::string> numPic{
        {-1, "Tall/bomb.png"},
        {0, "Tall/nothing.png"},
        {1, "Tall/one.png"}, 
        {2, "Tall/two.png"}, 
        {3, "Tall/three.png"}, 
        {4, "Tall/four.png"}, 
        {5, "Tall/five.png"}, 
        {6, "Tall/six.png"}, 
        {7, "Tall/seven.png"},
        {8, "Tall/eight.png"}
    };


    GameWindow(TDT4102::Point position, int width, int height, const std::string& title, const Field& field);
    void drawGrid(AnimationWindow& win, const Field& Field);
    void drawPlayerGrid(AnimationWindow& win, const Field& Field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec);
    bool leftClick();
    bool rightClick();
    TDT4102::Point coordinates();
    int clickY(const Field& field);
    int clickX(const Field& field);
    void tileClick(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec);
    void bombClick();
};

