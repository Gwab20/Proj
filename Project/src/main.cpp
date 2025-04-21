#include "GameState.h"
#include <windows.h>

int main() {
    GameState game;
    while (true) {
        game.update();
        game.render();
        Sleep(16); // ~60 FPS
    }
    return 0;
}