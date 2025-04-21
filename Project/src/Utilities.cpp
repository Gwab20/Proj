#include "Utilities.h"
#include <iostream>
#include <windows.h>
#include <limits>

void Utilities::clearScreen() {
    system("cls");
}

void Utilities::exitGame() {
    exit(0);
}

void Utilities::setTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int Utilities::getValidatedInput(int min, int max) {
    int input;
    while (!(std::cin >> input) || input < min || input > max) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Try again: ";
    }
    return input;
}