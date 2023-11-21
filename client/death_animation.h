#ifndef DEATHANIMATION_H
#define DEATHANIMATION_H

#include <SDL2pp/SDL2pp.hh>

#include "TexturesPool.h"
#include "Animation.h"

class DeathAnimation {
private:
    /** Animation of the death of the worm. */
    Animation worm_death_animation;
    /** Animation of the tombstone of the worm. */
    Animation worm_tombstone_animation;
    /** Animation of the explosion. */
    Animation explosion;
    /** Current animation frame. */
    unsigned int currentFrame;
    /** Delay between frames. */
    unsigned int delay;
    /** Counter for the animation. */
    unsigned int counter;

    std::shared_ptr<SDL2pp::Texture>& search_random_tomstone(TexturesPool& pool);
public:
    explicit DeathAnimation(TexturesPool& pool, unsigned int delay = 0);

    void update(bool iddle = false);

    void render(SDL2pp::Renderer &renderer, SDL2pp::Rect dest);

    ~DeathAnimation() = default;
};

#endif  // DEATHANIMATION_H
