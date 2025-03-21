#include "std_lib_facilities.h"
#include "GameWindow.h"
#include "mineField.h"

int main() {
    
    TDT4102::Point p = {300,100};
    GameWindow game = GameWindow(p, 1000, 1000, "WINDOW");
    game.wait_for_close();

    /*while (!game.should_close()) {
        if (game.leftClick()) { 
            game.tileClick(field, game.playerFieldVec);
            game.drawGrid(game, field); 
            game.drawPlayerGrid(game, field, game.playerFieldVec);  
            game.next_frame(); 
        }
    }*/
    
}
