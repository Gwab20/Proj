#include <iostream>
#include <string>
#include <vector>
#include <conio.h> // For _getch() on Windows
#include <windows.h> // For Windows console functions
#include <algorithm> // For std::min

using namespace std;

// ANSI color codes (Windows may need SetConsoleMode)
const string COLOR_RESET = "\033[0m";
const string COLOR_RED = "\033[31m";
const string COLOR_GREEN = "\033[32m";
const string COLOR_BLUE = "\033[34m";
const string COLOR_YELLOW = "\033[33m";
const string COLOR_CYAN = "\033[36m";

// Clear screen function (platform specific)
void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

// Character sprite class
class CharacterSprite {
public:
    vector<string> art;
    string name;
    string color;

    CharacterSprite(vector<string> a, string n, string c) : art(a), name(n), color(c) {}

    void display(int x, int y) {
        for (size_t i = 0; i < art.size(); ++i) {
            cout << "\033[" << (y + i) << ";" << x << "H" << color << art[i] << COLOR_RESET;
        }
    }
};

// Text box class with ASCII borders
class TextBox {
private:
    int width;
    int height;
    int x;
    int y;

public:
    TextBox(int w, int h, int posX, int posY) : width(w), height(h), x(posX), y(posY) {}

    void draw() {
        // Top border
        cout << "\033[" << y << ";" << x << "H" << "+" << string(width - 2, '-') << "+";

        // Side borders
        for (int i = 1; i < height - 1; ++i) {
            cout << "\033[" << (y + i) << ";" << x << "H" << "|" << string(width - 2, ' ') << "|";
        }

        // Bottom border
        cout << "\033[" << (y + height - 1) << ";" << x << "H" << "+" << string(width - 2, '-') << "+";
    }

    void printText(const string& text) {
        int currentLine = 1;
        int currentPos = 0;
        cout << "\033[" << (y + currentLine) << ";" << (x + 2) << "H";

        for (char c : text) {
            if (c == '\n' || currentPos >= width - 4) {
                currentLine++;
                currentPos = 0;
                if (currentLine >= height - 1) break;
                cout << "\033[" << (y + currentLine) << ";" << (x + 2) << "H";
            }
            cout << c;
            currentPos++;
        }
    }
};

// Simple RPG character class
class RPGCharacter {
public:
    string name;
    int hp;
    int maxHp;
    int attack;

    RPGCharacter(string n, int mh, int atk) : name(n), maxHp(mh), hp(mh), attack(atk) {}

    void displayStatus(int x, int y) {
        cout << "\033[" << y << ";" << x << "H" << name << ": ";

        // Health bar
        float percent = static_cast<float>(hp) / maxHp;
        int bars = static_cast<int>(20 * percent);

        cout << "[";
        for (int i = 0; i < 20; i++) {
            if (i < bars) {
                if (percent > 0.6) cout << COLOR_GREEN << "=";
                else if (percent > 0.3) cout << COLOR_YELLOW << "=";
                else cout << COLOR_RED << "=";
            } else {
                cout << " ";
            }
        }
        cout << COLOR_RESET << "] " << hp << "/" << maxHp;
    }
};

int main() {
    // Set up console for ANSI codes on Windows
    #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    #endif

    // Create character sprites
    vector<string> heroArt = {
        "  O ",
        " /|\\",
        " / \\"
    };

    vector<string> enemyArt = {
        " ( ) ",
        " ) ( ",
        "|   |"
    };

    CharacterSprite hero(heroArt, "Hero", COLOR_BLUE);
    CharacterSprite enemy(enemyArt, "Goblin", COLOR_RED);

    // Create RPG characters
    RPGCharacter player("Hero", 100, 15);
    RPGCharacter goblin("Goblin", 60, 10);

    // Create text box
    TextBox textBox(60, 10, 5, 15);

    // Game state
    bool inCombat = true;
    int turn = 0;

    while (inCombat) {
        clearScreen();

        // Display scene
        cout << "=== DRAGON REALM ADVENTURE ===" << endl;

        // Display sprites
        hero.display(10, 3);
        enemy.display(50, 3);

        // Display status
        player.displayStatus(5, 8);
        goblin.displayStatus(45, 8);

        // Draw text box
        textBox.draw();

        if (turn % 2 == 0) {
            // Player turn
            textBox.printText("What will you do?\n1. Attack\n2. Defend\n3. Use Item");

            cout << "\033[" << (15 + 9) << ";" << 5 << "H" << "> ";

            char choice = _getch();

            switch (choice) {
                case '1': {
                    int damage = player.attack;
                    goblin.hp -= damage;
                    string msg = "You attack the " + goblin.name + " for " + to_string(damage) + " damage!";
                    textBox.printText(msg);
                    break;
                }
                case '2':
                    textBox.printText("You raise your guard!\n(Defense increased next turn)");
                    break;
                case '3':
                    textBox.printText("You use a healing herb!\nHP + 20");
                    player.hp = min(player.hp + 20, player.maxHp);
                    break;
                default:
                    textBox.printText("Invalid choice!");
                    turn--; // Repeat turn
                    break;
            }
        } else {
            // Enemy turn
            int damage = goblin.attack;
            player.hp -= damage;
            string msg = goblin.name + " attacks you for " + to_string(damage) + " damage!";
            textBox.printText(msg);
        }

       

 
        // Check win/lose conditions
        if (goblin.hp <= 0) {
            textBox.printText("You defeated the " + goblin.name + "!\nPress any key to continue...");
            inCombat = false;
        } else if (player.hp <= 0) {
            textBox.printText("You were defeated...\nGame Over");
            inCombat = false;
        }

        _getch(); // Wait for key press
        turn++;
    }

    return 0;
}
