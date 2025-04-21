#pragma once
#include <string>

enum class State { TITLE, DIALOGUE, BATTLE, EXIT };

class GameState {
public:
    GameState();
    void update();
    void render();
    void switchState(State newState);
    
private:
    State currentState;
};