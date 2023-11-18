#ifndef AIMANIMATION_H
#define AIMANIMATION_H

#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "common/const.h"
#include "Animation.h"
#include "TexturesPool.h"


class AimAnimation {
private:
    /** SDL texture of the crosshair animation. */
    std::shared_ptr<SDL2pp::Texture>& crosshair_texture;
    /** Map of SDL actors_textures weapon aiming actors_textures. */
    std::unordered_map<WeaponsAndTools, std::shared_ptr<SDL2pp::Texture>&> weapon_aim_textures;
    /** Animation of the power charge */
    std::unique_ptr<Animation> power_charge_animation;
    /** Current aim inclination. */
    float current_inclination;

    void load_all_aim_textures(TexturesPool& pool);
public:
    explicit AimAnimation(TexturesPool& pool);

    void update(float new_inclination_degrees, bool charging_power);

    void render(WeaponsAndTools current_weapon, SDL2pp::Renderer &renderer, SDL2pp::Rect dest,
                SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL, double angle = 0.0);
};


#endif  // AIMANIMATION_H
