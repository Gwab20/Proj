// AudioManager.cpp
#include "AudioManager.h"
#include <windows.h>
#include <mmsystem.h>  // Required header
#pragma comment(lib, "winmm.lib")  // Directly link the library

void AudioManager::playMusic(const std::string& path) {
    PlaySoundA(path.c_str(), NULL, SND_ASYNC | SND_LOOP);
}

void AudioManager::stopMusic() {
    PlaySoundA(nullptr, nullptr, 0);
}