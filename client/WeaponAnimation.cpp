#include "WeaponAnimation.h"

WeaponAnimation::WeaponAnimation(TexturesPool& pool) :
        current_weapon(WeaponsAndTools::BAZOOKA),
        current_weapon_draw_animation(std::make_unique<Animation>(pool.get_texture(
                                                                          Actors::WORM_DRAW_BAZOOKA
                                                                          ), 7, 2, false)),
        crosshair_texture(pool.get_texture(Actors::CROSSHAIR)),
        current_weapon_texture(pool.get_texture(Actors::WORM_HOLDING_BAZOOKA)),
        pool(pool), weapon_drawn_frames_counter(0), current_inclination(0) {}

void WeaponAnimation::change_weapon_texture(WeaponsAndTools equipped_weapon) {
    if (equipped_weapon == current_weapon) return;

    switch (equipped_weapon) {
        case(WeaponsAndTools::BAZOOKA): {
            current_weapon_texture = pool.get_texture(Actors::WORM_HOLDING_BAZOOKA);
            current_weapon_draw_animation = std::make_unique<Animation>(
                    pool.get_texture(Actors::WORM_DRAW_BAZOOKA), 7, 2, false);
            current_weapon = WeaponsAndTools::BAZOOKA;
            break;
        }
        default: {
                break;
        }
    }
}

void WeaponAnimation::update(float new_inclination_degrees,
                             WeaponsAndTools equipped_weapon, bool weapon_currently_stored) {
    if (weapon_currently_stored){
        weapon_drawn_frames_counter = 0;
    }
    current_weapon_draw_animation->update(weapon_currently_stored);

    current_inclination = new_inclination_degrees;
    change_weapon_texture(equipped_weapon);
}

void WeaponAnimation::render(SDL2pp::Renderer& renderer, SDL2pp::Rect dest,
                                 SDL_RendererFlip flipType, double angle) {

    if (weapon_drawn_frames_counter < 14 /*7*2*/){
        current_weapon_draw_animation->render(renderer, dest, 0, 0, flipType);
        weapon_drawn_frames_counter++;
    } else {
            renderer.Copy(
                    (*current_weapon_texture),
                    SDL2pp::Rect(0, (16*60 - (60) * int(-1*((this->current_inclination / (M_PI/32))))), 35, 60),
                    dest,
                    angle,                // don't rotate
                    SDL2pp::NullOpt,    // rotation center - not needed
                    flipType
            );

            if (flipType == SDL_FLIP_HORIZONTAL){
                renderer.Copy(
                        (*crosshair_texture),
                        SDL2pp::Rect(0, (16*60 - (60) * int(-1*((this->current_inclination / (M_PI/32))))), 35, 60),
                        //SDL2pp::Rect (dest.x * (1 + (cos(current_inclination)*0.35)), (dest.y * (1 - (sin(current_inclination))*0.35)), 35, 60),
                        SDL2pp::Rect((dest.x + (40*cos(current_inclination))), (dest.y - 40*sin(current_inclination)), 35, 60),
                        angle,                // don't rotate
                        SDL2pp::NullOpt,    // rotation center - not needed
                        flipType
                );
            } else {
                renderer.Copy(
                        (*crosshair_texture),
                        SDL2pp::Rect(0, (16*60 - (60) * int(-1*((this->current_inclination / (M_PI/32))))), 35, 60),
                        //SDL2pp::Rect (dest.x * (1 - cos(current_inclination)*0.35), dest.y * (1 - sin(current_inclination)*0.35), 35, 60),
                        SDL2pp::Rect((dest.x - (40*cos(current_inclination))), (dest.y - 40*sin(current_inclination)), 35, 60),
                        angle,                // don't rotate
                        SDL2pp::NullOpt,    // rotation center - not needed
                        flipType
                );
            }
    }
}
