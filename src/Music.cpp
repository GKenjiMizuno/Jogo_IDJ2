#include "Music.h"
#include <iostream>

Music::Music() : music(nullptr) {}

Music::Music(std::string file) : music(nullptr) {
    Open(file);
}

Music::~Music() {
    Stop();
    if (music) Mix_FreeMusic(music);
}

void Music::Open(std::string file) {
    if (music) Mix_FreeMusic(music);
    music = Mix_LoadMUS(file.c_str());
    if (!music)
        std::cerr << "Erro ao carregar música: " << Mix_GetError() << std::endl;
}

void Music::Play(int times) {
    if (music)
        Mix_PlayMusic(music, times);
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

bool Music::IsOpen() {
    return music != nullptr;
}
