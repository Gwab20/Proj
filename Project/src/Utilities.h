#pragma once
#include <string>

class Utilities {
public:
    static void clearScreen();
    static void exitGame();
    static void setTextColor(int color);
    static int getValidatedInput(int min, int max);
};