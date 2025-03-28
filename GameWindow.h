#pragma once
#include "AnimationWindow.h"
#include "widgets/Button.h"
#include "mineField.h"
#include "std_lib_facilities.h"
#include "Timer.h"
#include "Player.h"
#include <vector>

class GameWindow : public TDT4102::AnimationWindow
{
    private:
    const int W = 30;
    const int H = 16;

    static constexpr int cellSize = 40;
    TDT4102::Image numImage;
    TDT4102::Button resetButton;

    std::unique_ptr<Field> field;
    Timer t;
    std::unique_ptr<Player> player;    

    int bombCount = 70;
    int resetCount = 0;
    bool dead = false;
    double frozenTimer;
    
    public:
    std::vector<std::unique_ptr<std::vector<int>>> playerFieldVec;
    TDT4102::Color color = TDT4102::Color::grey;
    std::map<int, std::shared_ptr<TDT4102::Image>> images;

    GameWindow(TDT4102::Point position, int width, int height, const std::string& title);
    void run();

    void drawGrid(AnimationWindow& win);
    void drawPlayerGrid(AnimationWindow& win, const std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec);
    void drawPlayer(AnimationWindow& win);
    void drawArrows();

    TDT4102::Point coordinates();
    int clickY();
    int clickX();
    
    void tileClick(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec, bool& dead);
    void openUp(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec, int x, int y);

    void flagRightClick(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec);
    void flagSpace(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec);

    void deathFreeze();
    void callbackButton();
    void resetCallback(int& resetCount);
    void reset();

    void move();
    void flagSpaceMode();
};



