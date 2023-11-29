#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <map>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "../common/const.h"


class AudioPlayer {
private:
    std::map<SoundEffects, Mix_Chunk*> effects;
    Mix_Music* background_music;

    void load_effects();
public:
    AudioPlayer();

    void play_background_music();

    void playAudio(SoundEffects key);

    ~AudioPlayer();
};

#endif
