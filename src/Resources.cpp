#include "Resources.h"
#include <iostream>
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file) {
    auto it = imageTable.find(file);
    if (it != imageTable.end())
        return it->second;

    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (!texture) {
        std::cerr << "Erro ao carregar imagem: " << file << " - " << SDL_GetError() << std::endl;
        return nullptr;
    }

    imageTable[file] = texture;
    return texture;
}

void Resources::ClearImages() {
    for (auto& pair : imageTable) {
        SDL_DestroyTexture(pair.second);
    }
    imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file) {
    auto it = musicTable.find(file);
    if (it != musicTable.end())
        return it->second;

    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if (!music) {
        std::cerr << "Erro ao carregar música: " << file << " - " << Mix_GetError() << std::endl;
        return nullptr;
    }

    musicTable[file] = music;
    return music;
}

void Resources::ClearMusics() {
    for (auto& pair : musicTable) {
        Mix_FreeMusic(pair.second);
    }
    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file) {
    auto it = soundTable.find(file);
    if (it != soundTable.end())
        return it->second;

    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
    if (!chunk) {
        std::cerr << "Erro ao carregar som: " << file << " - " << Mix_GetError() << std::endl;
        return nullptr;
    }

    soundTable[file] = chunk;
    return chunk;
}

void Resources::ClearSounds() {
    for (auto& pair : soundTable) {
        Mix_FreeChunk(pair.second);
    }
    soundTable.clear();
}
