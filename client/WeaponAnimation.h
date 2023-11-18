#ifndef WEAPONHOLDANIMATION_H
#define WEAPONHOLDANIMATION_H

#include <SDL2pp/SDL2pp.hh>
#include <unordered_map>

#include "Animation.h"
#include "TexturesPool.h"

class WeaponAnimation {
private:
    /** Current weapon. */
    WeaponsAndTools current_weapon;
    /** Map of SDL actors_textures of the weapon draw animations. */
    std::unordered_map<WeaponsAndTools, std::shared_ptr<Animation>> weapon_draw_animations;
    /** Animation of the power charge */
    std::unique_ptr<Animation> power_charge_animation;
    /** SDL texture of the crosshair animation. */
    std::shared_ptr<SDL2pp::Texture>& crosshair_texture;
    /** Map of SDL actors_textures weapon aiming actors_textures. */
    std::unordered_map<WeaponsAndTools, std::shared_ptr<SDL2pp::Texture>&> weapon_aim_textures;
    /** Reference to the texture holder */
    TexturesPool& pool;
    /** Indicates if the weapon was already animated thw draw. */
    unsigned int weapon_drawn_frames_counter;
    /** Current worm inclination. */
    float current_inclination;

    void update_weapon(WeaponsAndTools equipped_weapon);

    void load_all_aim_textures();

    void load_all_draw_animations();
public:
    explicit WeaponAnimation(TexturesPool& pool);

    void update(float new_inclination_degrees, bool charging_power,
                WeaponsAndTools equipped_weapon, bool weapon_currently_stored);

    void render(SDL2pp::Renderer &renderer, SDL2pp::Rect dest,
                SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL,
                double angle = 0.0);
};


#endif  // WEAPONHOLDANIMATION_H
