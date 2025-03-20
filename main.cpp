#include "std_lib_facilities.h"
#include "GameWindow.h"
#include "mineField.h"

int main() {
    Field field;
    std::cout << field;


    TDT4102::Point p = {300,100};

    GameWindow game = GameWindow(p, 1000, 1000, "WINDOW", field);
    game.wait_for_close();
}
