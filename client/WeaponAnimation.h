#ifndef WEAPONHOLDANIMATION_H
#define WEAPONHOLDANIMATION_H

#include <SDL2pp/SDL2pp.hh>

#include "Animation.h"
#include "TexturesPool.h"

class WeaponAnimation {
private:
    /** Current weapon. */
    WeaponsAndTools current_weapon;
    /** SDL texture of the current weapon draw animation. */
    std::unique_ptr<Animation> current_weapon_draw_animation;
    /** SDL texture of the crosshair animation. */
    std::shared_ptr<SDL2pp::Texture>& crosshair_texture;
    /** SDL texture of the current weapon aiming animation. */
    std::shared_ptr<SDL2pp::Texture>& current_weapon_texture;
    /** Reference to the texture holder */
    TexturesPool& pool;
    /** Indicates if the weapon was already animated thw draw. */
    unsigned int weapon_drawn_frames_counter;
    /** Current worm inclination. */
    float current_inclination;

    void change_weapon_texture(WeaponsAndTools new_weapon);
public:
    explicit WeaponAnimation(TexturesPool& pool);

    void update(float new_inclination_degrees,
                WeaponsAndTools equipped_weapon, bool weapon_currently_stored);

    void render(SDL2pp::Renderer &renderer, SDL2pp::Rect dest,
                SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL,
                double angle = 0.0);
};


#endif  // WEAPONHOLDANIMATION_H
