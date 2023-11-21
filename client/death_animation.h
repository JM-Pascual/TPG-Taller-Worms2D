#ifndef DEATHANIMATION_H
#define DEATHANIMATION_H

#include <SDL2pp/SDL2pp.hh>

#include "TexturesPool.h"

class DeathAnimation {
private:
    /** SDL texture of the raw death image. */
    std::shared_ptr<SDL2pp::Texture> &worm_death_texture;
    /** SDL texture of the raw tombstone image. */
    std::shared_ptr<SDL2pp::Texture> &worm_tombstone_texture;
    /** Current animation frame. */
    unsigned int currentFrame;
    /** Delay between frames. */
    unsigned int delay;
    /** Whether the animation should loop or not. */
    bool loop_animation;
    /** Counter for the animation. */
    unsigned int counter;
public:
    explicit DeathAnimation(TexturesPool& pool, unsigned int delay = 0);

    void update(bool iddle = false);

    void render(SDL2pp::Renderer &renderer, SDL2pp::Rect dest);

    ~DeathAnimation() = default;
};

#endif  // DEATHANIMATION_H
