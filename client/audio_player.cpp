#include "audio_player.h"

#include <list>
#include <utility>

#include <spdlog/spdlog.h>

#define CHUNKSIZE 4096

#define CHANNEL -1

// Max volume = MIX_MAX_VOLUME == 128
#define MUSIC_VOLUME 25

AudioPlayer::AudioPlayer(): background_music(nullptr) {
    Mix_Init(MIX_INIT_MP3);

    if (Mix_OpenAudio(22050, AUDIO_S16SYS, MIX_DEFAULT_CHANNELS, CHUNKSIZE) == -1) {
        spdlog::get("client")->error("Error al intentar cargar el dispositivo de audio");
    }

    background_music = Mix_LoadMUS("client/resources/sounds/background/oriental.mp3");
    if (not background_music) {
        spdlog::get("client")->error("Error al intentar cargar la musica ambiente");
    }

    std::list<std::pair<std::string, std::string>> key_filepath;
    key_filepath.push_back({"test", "client/resources/sounds/laugh.mp3"});

    for (const auto& key_path: key_filepath) {
        Mix_Chunk* chunk = Mix_LoadWAV(key_path.second.data());

        if (chunk) {
            chunks.insert({key_path.first, chunk});
            Mix_VolumeChunk(chunk, 100);
            continue;
        }

        spdlog::get("client")->error("Error al intentar cargar el sonido {:s}: {:s}",
                                     key_path.first, key_path.second);
    }

    Mix_VolumeMusic(MUSIC_VOLUME);
    if (Mix_PlayMusic(background_music, -1) == -1) {
        spdlog::get("client")->error("Error al intentar reproducir la musica ambiente");
    }
}

void AudioPlayer::playAudio(const std::string& key) {
    if (chunks.count(key) == 1) {
        return;
    }

    int channel = Mix_PlayChannel(1, chunks.at(key), -1);
    if (channel == -1) {
        spdlog::get("client")->error("Error al intentar reproducir el audio {:s}", key);
        return;
    }

    while (Mix_Playing(channel) != 0) {
        SDL_Delay(200);  // wait 200 milliseconds
    }
}


AudioPlayer::~AudioPlayer() {
    for (auto& [key, chunk]: chunks) {
        if (chunk) {
            Mix_FreeChunk(chunk);
        }
    }

    if (background_music) {
        Mix_FreeMusic(background_music);
    }

    Mix_CloseAudio();
    Mix_Quit();
}