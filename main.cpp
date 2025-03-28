#include "std_lib_facilities.h"
#include "GameWindow.h"
#include "mineField.h"
#include "Timer.h"
#include "Player.h"

int main() {
    
    TDT4102::Point p = {300,100};
    GameWindow game = GameWindow(p, 1000, 1000, "WINDOW");
    game.run();
    game.wait_for_close();
    game.saveGame();
}
