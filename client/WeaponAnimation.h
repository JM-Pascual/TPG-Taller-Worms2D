#ifndef WEAPONHOLDANIMATION_H
#define WEAPONHOLDANIMATION_H

#include <SDL2pp/SDL2pp.hh>
#include <unordered_map>

#include "Animation.h"
#include "AimAnimation.h"
#include "TexturesPool.h"

class WeaponAnimation {
private:
    /** Current weapon. */
    WeaponsAndTools current_weapon;
    /** Map of SDL actors_textures of the weapon draw animations. */
    std::unordered_map<WeaponsAndTools, std::shared_ptr<Animation>> weapon_draw_animations;
    /** Weapons aim animations*/
    AimAnimation aim_animations;
    /** Indicates if the weapon was already animated thw draw. */
    unsigned int weapon_drawn_frames_counter;

    void update_weapon(WeaponsAndTools equipped_weapon);

    void load_all_draw_animations(TexturesPool& pool);
public:
    explicit WeaponAnimation(TexturesPool& pool);

    void update(float new_inclination_degrees, bool charging_power,
                WeaponsAndTools equipped_weapon, bool weapon_currently_stored);

    void render(SDL2pp::Renderer &renderer, SDL2pp::Rect dest,
                SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL,
                double angle = 0.0);
};


#endif  // WEAPONHOLDANIMATION_H
