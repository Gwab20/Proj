#pragma once
#include <windows.h>

class AudioManager {
public:
    static void playBeep(int freq, int duration);  // Uses Beep()
    static void playSound(const char* path);       // Uses PlaySoundW()
    
};