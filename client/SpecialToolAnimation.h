#ifndef SPECIALTOOLANIMATION_H
#define SPECIALTOOLANIMATION_H

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "common/States.h"

#include "camera.h"

class SdlTexture;
class Area;

class SpecialToolAnimation {
protected:
    /** SDL texture of the raw image. */
    std::shared_ptr<SDL2pp::Texture> &texture;
    /** Total number of frames in the sprite. */
    unsigned int numFrames;
    /** Size of the sprite (height and width). */
    unsigned int size;
    /** Current animation frame. */
    unsigned int currentFrame;
    /** Delay between frames. */
    unsigned int delay;
    /** Counter for the animation. */
    unsigned int counter;
    /** Bool that defines if a game state currently_animating_tool the tool. */
    bool currently_animating_tool;
public:
    SpecialToolAnimation(std::shared_ptr<SDL2pp::Texture> &texture,
                         unsigned int frames_in_texture, unsigned int delay_in_animation,
                         bool loop) : texture(texture), numFrames(frames_in_texture),
            size(this->texture->GetHeight() / numFrames),
            currentFrame(0), delay(delay_in_animation),
            counter(0),
            currently_animating_tool(false) {
        assert(this->numFrames > 0);
        assert(this->size > 0);
    }

    virtual void update_tool_animation(std::shared_ptr<WormStateG>& worm_state) = 0;

    virtual void render(SDL2pp::Renderer& renderer, Camera& camera, int non_squared_width,
                        int non_squared_height, SDL_RendererFlip flipType, double angle) = 0;

    bool animation_ongoing(){
        return currently_animating_tool;
    }

};

class TeleportAnimation : public SpecialToolAnimation {
private:
    b2Vec2 initial_position;
    b2Vec2 teleport_position;
public:
    TeleportAnimation(std::shared_ptr<SDL2pp::Texture> &texture,
                      unsigned int frames_in_texture, unsigned int delay_in_animation, bool loop) :
            SpecialToolAnimation(texture, frames_in_texture, delay_in_animation, loop),
            initial_position(0,0), teleport_position(0,0){}

    void update_tool_animation(std::shared_ptr<WormStateG> &worm_state) override {
        if (!currently_animating_tool && worm_state->using_tool){
            currently_animating_tool = true;
            teleport_position = worm_state->pos;
        } else if (!currently_animating_tool){
            initial_position = worm_state->pos;
            this->currentFrame = 0;
        } else {
            counter++;
            teleport_position = worm_state->pos;
            if (counter < delay) {
                return;
            } else {
                if (currentFrame < numFrames-1) {
                    this->currentFrame++;
                } else {
                    currently_animating_tool = false;
                    return; //Last frame, end of animation
                }
                counter = 0;
            }
        }
    }

    void render(SDL2pp::Renderer& renderer, Camera& camera, int non_squared_width,
                int non_squared_height, SDL_RendererFlip flipType, double angle) override {

        //Copiamos la textura del worm saliendo
        //Copio al derecho la textura, desde que sale hasta que llega
        SDL2pp::Rect render_rect_initial = camera.calcRect(initial_position.x, initial_position.y, 60, 60);
        renderer.Copy(
                (*texture),
                SDL2pp::Rect(0, (this->size) * this->currentFrame,
                             (this->size + non_squared_width), (this->size + non_squared_height)),
                render_rect_initial,
                angle,
                SDL2pp::NullOpt,
                flipType
        );

        //Copiamos la textura del worm llegando
        //Copio al revés la textura, desde que llega a que sale
        SDL2pp::Rect render_rect_end = camera.calcRect(teleport_position.x, teleport_position.y, 60, 60);
        renderer.Copy(
                (*texture),
                SDL2pp::Rect(0, ((this->size) * numFrames) - ((this->size) * this->currentFrame),
                             (this->size + non_squared_width), (this->size + non_squared_height)),
                render_rect_end,
                angle,
                SDL2pp::NullOpt,
                flipType
        );
    }

    virtual ~TeleportAnimation() = default;
};

#endif  // SPECIALTOOLANIMATION_H
