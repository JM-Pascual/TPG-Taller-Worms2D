/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <SDL2pp/SDL2pp.hh>

#define DRAW_FACTOR (60)

class SdlTexture;
class Area;

class Animation {
private:
    /** SDL texture of the raw image. */
    std::shared_ptr<SDL2pp::Texture> &texture;
    /** Total number of frames in the sprite. */
    unsigned int numFrames;
    /** Size of the sprite (height and width). */
    unsigned int size;
    /** Time elapsed (msecs from SDL2pp::GetTickRate()). */
    unsigned int elapsed;
    /** Current animation frame. */
    unsigned int currentFrame;
    /** Delay between frames. */
    unsigned int delay;
public:
    explicit Animation(std::shared_ptr<SDL2pp::Texture> &texture,
                       unsigned int frames_in_texture, unsigned int delay_in_animation = 0);

    void update(unsigned int dt, bool iddle = false);

    void render(SDL2pp::Renderer &renderer, SDL2pp::Rect dest,
                int non_squared_width = 0, int non_squared_height = 0,
                SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL,
                double angle = 0.0);

    ~Animation() = default;
};

#endif  // ANIMATION_H_
