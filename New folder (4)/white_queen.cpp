/* #include <iostream>
#include <thread>
#include <string>
#ifdef _WIN32
#include <windows.h>
#pragma comment(lib, "winmm.lib")
#else
#include <cstdlib>
#endif

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void playBackgroundMusic() {
#ifdef _WIN32
    PlaySound(TEXT("white_queen.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
#else
    thread([](){
        system("aplay white_queen.wav 2>/dev/null || "
               "afplay white_queen.wav 2>/dev/null || "
               "mpg123 white_queen.mp3 2>/dev/null");
    }).detach();
#endif
}

void displayTitleScreen() {
    clearScreen();
    
    // Corrected ASCII art without backslash warnings
    cout << R"(
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
    
}

int main() {
    playBackgroundMusic();
    displayTitleScreen();
    
    cout << "\nPress Enter to begin your adventure...";
    cin.ignore();
    
#ifdef _WIN32
    PlaySound(NULL, NULL, 0);
#endif
    
    return 0;
} */

#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

// Enable ANSI escape codes, UTF-8, and prepare for music
void initConsole() {
    // Console setup
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    system("mode con cols=80 lines=30");
    
    // Start background music (looped)
    PlaySound(TEXT("white_queen.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}

void displayTitle() {
    // Clear screen
    cout << "\033[2J\033[H";

    // Title with Unicode box drawing
    cout << R"(
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
  ║  ╚██████╝ ╚████╔╝ ███████╗███████╗██║ ╚████║║
  ║   ╚════██   ╚═══╝  ╚══════╝╚══════╝╚═╝  ╚═══╝║
  ║                                              ║
  ║              A s   i t   B e g a n           ║
  ║                                              ║
  ║           ┌──────────────────────┐           ║
  ║           │       New Game       │           ║
  ║           │       Load Game      │           ║
  ║           │       Exit           │           ║
  ║           └──────────────────────┘           ║
  ╚══════════════════════════════════════════════╝
)" << endl;

    cout << "\nPress any key to continue...";
}

int main() {
    initConsole();
    displayTitle();
    
    _getch(); // Wait for key press
    
    // Clean up music before exiting
    PlaySound(NULL, NULL, 0);
    return 0;
}