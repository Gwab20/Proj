#include "TitleScreen.h"
#include "Utilities.h"
#include <windows.h>
#include <iostream>

void TitleScreen::render() {
    Utilities::clearScreen();
    Utilities::setTextColor(11);
    
    std::cout << R"(
  ╔══════════════════════════════════════════════╗
  ║     ██╗    ██╗██╗  ██╗██╗████████╗███████╗   ║ 
  ║     ██║    ██║██║  ██║██║╚══██╔══╝██╔════╝   ║
  ║     ██║ █╗ ██║███████║██║   ██║   █████╗     ║
  ║     ██║███╗██║██╔══██║██║   ██║   ██╔══╝     ║
  ║     ╚███╔███╔╝██║  ██║██║   ██║   ███████╗   ║
  ║      ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝   ╚═╝   ╚══════╝   ║
  ║                                              ║
  ║   ██████╗ ██╗   ██╗███████╗███████╗███╗   ██╗║
  ║  ██╔═══██╗██║   ██║██╔════╝██╔════╝████╗  ██║║
  ║  ██║   ██║██║   ██║█████╗  █████╗  ██╔██╗ ██║║
  ║  ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══╝  ██║╚██╗██║║
  ║  ╚██████╔╝ ╚████╔╝ ███████╗███████╗██║ ╚████║║
  ║   ╚═════╝   ╚═══╝  ╚══════╝╚══════╝╚═╝  ╚═══╝║
  ║                                              ║
  ║              A s   i t   B e g a n           ║
  ║                                              ║
  ║           ┌──────────────────────┐           ║
  ║           │       New Game       │           ║
  ║           │       Load Game      │           ║
  ║           │       Exit           │           ║
  ║           └──────────────────────┘           ║
  ╚══════════════════════════════════════════════╝
    )" << "\n";

    Utilities::setTextColor(14);
    std::cout << "\n           [ ↑ ↓ Select | Enter Confirm ]\n";
}

bool TitleScreen::handleInput() {
    static int selected = 0;
    
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        selected = (selected - 1 + 3) % 3;
        Sleep(150);
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        selected = (selected + 1) % 3;
        Sleep(150);
    }
    return !(GetAsyncKeyState(VK_RETURN) & 0x8000 && selected == 2);
}