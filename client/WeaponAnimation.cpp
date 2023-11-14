#include "WeaponAnimation.h"

WeaponAnimation::WeaponAnimation(TexturesPool& pool) :
        current_weapon(WeaponsAndTools::BAZOOKA),
        current_weapon_texture(pool.get_texture(Actors::WORM_HOLDING_BAZOOKA)),
        pool(pool), current_inclination(0) {}

void WeaponAnimation::change_weapon_texture(WeaponsAndTools equipped_weapon) {
    if (equipped_weapon == current_weapon) return;

    switch (equipped_weapon) {
        case(WeaponsAndTools::BAZOOKA): {
            current_weapon_texture = pool.get_texture(Actors::WORM_HOLDING_BAZOOKA);
            current_weapon = WeaponsAndTools::BAZOOKA;
            break;
        }
        default: {
                break;
        }
    }
}

void WeaponAnimation::update(float new_inclination_degrees, WeaponsAndTools equipped_weapon) {
    current_inclination = new_inclination_degrees;
    change_weapon_texture(equipped_weapon);
}

void WeaponAnimation::render(SDL2pp::Renderer& renderer, SDL2pp::Rect dest,
                                 SDL_RendererFlip flipType, double angle) {

    renderer.Copy(
            (*current_weapon_texture),
            SDL2pp::Rect(0, (16*60 - (60) * int(-1*((this->current_inclination / (M_PI/32))))), 35, 60),
            dest,
            angle,                // don't rotate
            SDL2pp::NullOpt,    // rotation center - not needed
            flipType
    );
}
