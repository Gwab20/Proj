// AudioManager.h
#pragma once
#include <string>

class AudioManager {
public:
    static void playMusic(const std::string& path);
    static void stopMusic();
};