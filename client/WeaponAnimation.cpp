#include "WeaponAnimation.h"

void WeaponAnimation::load_all_draw_animations() {
    weapon_draw_animations.insert({
            WeaponsAndTools::BAZOOKA, std::make_unique<Animation>(
                                              pool.get_draw_texture(WeaponsDraw::WORM_DRAW_BAZOOKA)
                                                      , 7, 2, false)});
    weapon_draw_animations.insert({
            WeaponsAndTools::DYNAMITE, std::make_unique<Animation>(
                                               pool.get_draw_texture(WeaponsDraw::WORM_DRAW_DYNAMITE)
                                                       , 7, 2, false)});
}

void WeaponAnimation::load_all_aim_textures() {
    weapon_aim_textures.insert({WeaponsAndTools::BAZOOKA,
                                (pool.get_aim_texture(WeaponAiming::WORM_AIM_BAZOOKA))});

    weapon_aim_textures.insert({WeaponsAndTools::BAZOOKA,
                                (pool.get_aim_texture(WeaponAiming::WORM_AIM_DYNAMITE))});
}

WeaponAnimation::WeaponAnimation(TexturesPool& pool) :
        current_weapon(WeaponsAndTools::BAZOOKA),
        power_charge_animation(std::make_unique<Animation>(
                pool.get_actor_texture(Actors::POWER_CHARGE_BAR), 6, 2, false)),
        crosshair_texture(pool.get_actor_texture(Actors::CROSSHAIR)),
        pool(pool), weapon_drawn_frames_counter(0), current_inclination(0) {

    this->load_all_aim_textures();
    this->load_all_draw_animations();

}

void WeaponAnimation::update_weapon(WeaponsAndTools equipped_weapon) {
    current_weapon = equipped_weapon;
}

void WeaponAnimation::update(float new_inclination_degrees, bool charging_power,
                             WeaponsAndTools equipped_weapon, bool weapon_currently_stored) {
    if (weapon_currently_stored){
        weapon_drawn_frames_counter = 0;
    }
    update_weapon(equipped_weapon);
    weapon_draw_animations[current_weapon]->update(weapon_currently_stored);
    power_charge_animation->update(!charging_power);
    current_inclination = new_inclination_degrees;
}

void WeaponAnimation::render(SDL2pp::Renderer& renderer, SDL2pp::Rect dest,
                                 SDL_RendererFlip flipType, double angle) {

    if (weapon_drawn_frames_counter < 14 /* 7*2 */){
        weapon_draw_animations[current_weapon]->render(renderer, dest, 0, 0, flipType);
        weapon_drawn_frames_counter++;
    } else {
            renderer.Copy(
                    (*weapon_aim_textures.at(current_weapon)),
                    SDL2pp::Rect(0,
                             std::min((16*60 - (60) * int(-1*((this->current_inclination /
                                                                   (M_PI/32))))), 1860), 35, 60),
                    dest,
                    angle,                // don't rotate
                    SDL2pp::NullOpt,    // rotation center - not needed
                    flipType
            );

            if (flipType == SDL_FLIP_HORIZONTAL){
                renderer.Copy(
                        (*crosshair_texture),
                        SDL2pp::Rect(0,
                                     std::min((16*60 - (60) * int(-1*((this->current_inclination /
                                                                           (M_PI/32))))), 1860),
                                     35, 60),
                        //SDL2pp::Rect (dest.x * (1 + (cos(current_inclination)*0.35)), (dest.y * (1 - (sin(current_inclination))*0.35)), 35, 60),
                        SDL2pp::Rect((dest.x + (40*cos(current_inclination))),
                                     (dest.y - 40*sin(current_inclination)), 35, 60),
                        angle,                // don't rotate
                        SDL2pp::NullOpt,    // rotation center - not needed
                        flipType
                );
            } else {
                renderer.Copy(
                        (*crosshair_texture),
                        SDL2pp::Rect(0,
                                     std::min((16*60 - (60) * int(-1*((this->current_inclination /
                                                                           (M_PI/32))))), 1860),
                                     35, 60),
                        //SDL2pp::Rect (dest.x * (1 - cos(current_inclination)*0.35), dest.y * (1 - sin(current_inclination)*0.35), 35, 60),
                        SDL2pp::Rect((dest.x - (40*cos(current_inclination))),
                                     (dest.y - 40*sin(current_inclination)), 35, 60),
                        angle,                // don't rotate
                        SDL2pp::NullOpt,    // rotation center - not needed
                        flipType
                );
            }

            power_charge_animation->render(renderer, SDL2pp::Rect(dest.x, dest.y -35, 35, 60),0, 0);
    }
}
