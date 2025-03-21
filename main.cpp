#include "std_lib_facilities.h"
#include "GameWindow.h"
#include "mineField.h"

int main() {
    Field field;
    std::cout << field;


    TDT4102::Point p = {300,100};

    GameWindow game = GameWindow(p, 1000, 1000, "WINDOW", field);

    while (!game.should_close()) {
        if (game.leftClick()) { 
            game.tileClick(field, game.playerFieldVec);
            game.drawGrid(game, field); 
            game.drawPlayerGrid(game, field, game.playerFieldVec);  
            game.next_frame(); 
        }
    }
    game.wait_for_close();
}
