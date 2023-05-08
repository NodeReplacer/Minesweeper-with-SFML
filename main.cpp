#include <iostream>
#include "Game.h"

int main() {
    Game game;
    
    if (game.IsRunning()) {
        game.update();
        game.render();
    }
}
