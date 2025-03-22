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
    TDT4102::Image numImage;

    public:
    
    std::map<int, TDT4102::Image> images;
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

    GameWindow(TDT4102::Point position, int width, int height, const std::string& title);

    void run();

    void drawGrid(AnimationWindow& win, const Field& Field);
    void drawPlayerGrid(AnimationWindow& win, const Field& Field, const std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec);

    TDT4102::Point coordinates();
    int clickY(const Field& field);
    int clickX(const Field& field);
    
    bool mouseClickedLeft();
    bool mouseClickedRight();
    bool leftClick();
    bool rightClick();

    void tileClick(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec);
    void openUp(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec, int x, int y);
    void bombClick(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec);
};



