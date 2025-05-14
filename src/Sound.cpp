#include "Sound.h"
#include <iostream>

Sound::Sound() : chunk(nullptr), channel(-1) {}

Sound::Sound(std::string file) : chunk(nullptr), channel(-1) {
    Open(file);
}

Sound::~Sound() {
    if (chunk) {
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
    }
}

void Sound::Open(std::string file) {
    if (chunk) {
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
    }
    chunk = Mix_LoadWAV(file.c_str());
    if (!chunk)
        std::cerr << "Erro ao carregar som: " << Mix_GetError() << std::endl;
}

void Sound::Play(int times) {
    if (chunk)
        channel = Mix_PlayChannel(-1, chunk, times - 1);
}

void Sound::Stop() {
    if (chunk)
        Mix_HaltChannel(channel);
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}
