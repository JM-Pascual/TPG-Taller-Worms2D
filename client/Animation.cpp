/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#include <SDL2pp/SDL2pp.hh>
#include <cassert>

#include "Animation.h"

Animation::Animation(std::shared_ptr<SDL2pp::Texture> &texture,
                     unsigned int frames_in_texture, unsigned int delay_in_animation,
                     bool loop) :
                                                  texture(texture), numFrames(frames_in_texture),
                                                  size(this->texture->GetHeight() / numFrames), elapsed(0.0f),
                                                  currentFrame(0), delay(delay_in_animation),
                                                  loop_animation(loop), counter(0) {
    assert(this->numFrames > 0);
    assert(this->size > 0);

}

void Animation::update(bool iddle) {
    if (iddle) {
        this->currentFrame = 0;
    } else{
        counter++;
        if (counter < delay) {
            return;
        } else {
            if (currentFrame < numFrames-1) {
                this->currentFrame++;
            } else if (loop_animation) {
                this->currentFrame = 0;
            } else {
                return; //Stuck in the last frame
            }
            counter = 0;
        }
    }
}

/**
 * @brief Renders the animation in the given coordinates.
 *
 * @param renderer Renderer.
 * @param x X coordinate.
 * @param y Y corrdinate.
 */
void Animation::render(SDL2pp::Renderer& renderer, SDL2pp::Rect dest, int non_squared_width,
                       int non_squared_height, SDL_RendererFlip flipType, double angle) {
    renderer.Copy(
            (*texture),
            SDL2pp::Rect(0, (this->size) * this->currentFrame,
                         (this->size + non_squared_width), (this->size + non_squared_height)),
            dest,
            angle,                // don't rotate
            SDL2pp::NullOpt,    // rotation center - not needed
            flipType
    );
}
