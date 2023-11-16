#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <map>
#include <string>

#include <SDL2pp/SDL2pp.hh>


class AudioPlayer {
private:
    std::map<std::string, Mix_Chunk*> chunks;
    Mix_Music* background_music;

public:
    AudioPlayer();

    void playAudio(const std::string& key);

    ~AudioPlayer();
};

#endif
