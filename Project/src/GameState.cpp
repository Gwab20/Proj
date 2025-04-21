#include "GameState.h"
#include "TitleScreen.h"
#include "AudioManager.h"
#include "Utilities.h"
#include <iostream>
#include <windows.h>

GameState::GameState() : currentState(State::TITLE) {
    AudioManager::playMusic("assets/audio/music/title.wav");
}

void GameState::update() {
    switch(currentState) {
        case State::TITLE:
            if (!TitleScreen::handleInput()) {
                currentState = State::EXIT;
            } else {
                currentState = State::DIALOGUE;
                AudioManager::stopMusic();
            }
            break;

        case State::DIALOGUE:
            if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                currentState = State::BATTLE;
            }
            break;

        case State::BATTLE:
            if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                currentState = State::DIALOGUE;
            }
            break;

        case State::EXIT:
            Utilities::exitGame();
            break;
    }
}

void GameState::render() {
    switch(currentState) {
        case State::TITLE:
            TitleScreen::render();
            break;

        case State::DIALOGUE:
            Utilities::clearScreen();
            Utilities::setTextColor(15);
            std::cout << "[DIALOGUE PLACEHOLDER - PRESS ENTER TO CONTINUE]\n";
            break;

        case State::BATTLE:
            Utilities::clearScreen();
            Utilities::setTextColor(12);
            std::cout << "[BATTLE PLACEHOLDER - PRESS ENTER TO FINISH]\n";
            break;

        case State::EXIT:
            break;
    }
}

void GameState::switchState(State newState) {
    currentState = newState;
    Utilities::clearScreen();
}