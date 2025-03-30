#include "std_lib_facilities.h"
#include "GameWindow.h"
#include "mineField.h"
#include "Timer.h"
#include "Player.h"

int main() {
    TDT4102::Point p = {0,0};
    GameWindow game = GameWindow(p, 1440, 1080, "WINDOW");
    game.run();
    game.wait_for_close();
    if(!game.dead){
        game.saveGame();
    }
}
