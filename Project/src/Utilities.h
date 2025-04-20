#pragma once
#include <windows.h>
#include <conio.h>  // For _kbhit(), _getch()

namespace term {
    void clear();
    void setColor(int color);
    void moveCursor(int x, int y);
    int getKey();  // Non-blocking input
}