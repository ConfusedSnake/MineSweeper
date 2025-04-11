#pragma once
#include "AnimationWindow.h"
#include "widgets/Button.h"
#include "mineField.h"
#include "std_lib_facilities.h"
#include "Timer.h"
#include "Player.h"
#include <vector>
#include <fstream>

class GameWindow : public TDT4102::AnimationWindow
{
    private:
    const int W = 31;
    const int H = 16;

    const int xOffset = 90;
    const int yOffset = 180;
    int yMove = 0;

    int viewXdirec = 8;
    int viewYdirec = 5;

    static constexpr int cellSize = 90;
    static constexpr int arrowSize = 45;

    TDT4102::Button resetButton;


    TDT4102::Color topOptionColor;
    TDT4102::Color topMiddleOptionColor;
    TDT4102::Color bottomMiddleOptionColor;
    TDT4102::Color bottomOptionColor;

    TDT4102::Color menuButtonColor = TDT4102::Color::dark_gray;

    std::unique_ptr<Field> field;
    Timer t;
    std::unique_ptr<Player> player;   
    std::vector<std::unique_ptr<std::vector<int>>> playerFieldVec; 

    int bombCount = 99;
    double frozenTimer;
    int savedTimer = 0;
    bool mainMenuOpen = true;
    bool pauseMenuOpen = false;
    bool youWin = false;
    bool youDied = false;
    bool controls = false;
    
    public:
    bool dead = false;

    
    TDT4102::Color color = TDT4102::Color::grey;
    std::map<int, std::unique_ptr<TDT4102::Image>> images;
    std::map<std::string, std::unique_ptr<TDT4102::Image>> pictures;

    GameWindow(TDT4102::Point position, int width, int height, const std::string& title);
    void drawMainMenu(AnimationWindow& win);
    void drawPauseMenu(AnimationWindow& win);
    void drawPauseMenuButton(AnimationWindow& win);
    void drawYouWin(AnimationWindow& win);
    void drawYouDied(AnimationWindow& win);
    void drawControls(AnimationWindow& win);
    void drawMenus(AnimationWindow& win);

    bool mouseOnTopMenuButton();
    bool mouseOnTopMiddleMenuButton();
    bool mouseOnBottomMiddleMenuButton();
    bool mouseOnBottomMenuButton();
    bool mouseOnBackButton();
    bool mouseOnOptionsButton();

    void menuClicks();

    void run();
    void runSaved();

    void drawGrid(AnimationWindow& win);
    void drawPlayerGrid(AnimationWindow& win, const std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec);
    void drawPlayer(AnimationWindow& win);
    void drawArrows(AnimationWindow& win);
    void drawGame(bool dField, bool dPlayerField, bool dPlayer, bool dBackground, AnimationWindow& win);

    TDT4102::Point coordinates();
    int clickY();
    int clickX();
    
    void tileClick(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec, bool& dead);
    void openUp(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec, int x, int y);

    void flagRightClick(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec);
    void flagSpace(const Field& field, std::vector<std::unique_ptr<std::vector<int>>>& playerFieldVec);

    void callbackButton();
    void resetCallback(int& resetCount);
    void reset();

    void move();
    void flagSpaceMode();

    void saveGame();
    void loadGame();
};



