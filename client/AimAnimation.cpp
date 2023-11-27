#include "AimAnimation.h"

#include <algorithm>
#include <memory>

void AimAnimation::load_all_aim_textures(TexturesPool& pool) {
    weapon_aim_textures.insert(
            {WeaponsAndTools::BAZOOKA, (pool.get_aim_texture(WeaponAiming::WORM_AIM_BAZOOKA))});

    weapon_aim_textures.insert(
            {WeaponsAndTools::MORTAR, (pool.get_aim_texture(WeaponAiming::WORM_AIM_MORTAR))});

    weapon_aim_textures.insert(
            {WeaponsAndTools::DYNAMITE, (pool.get_aim_texture(WeaponAiming::WORM_AIM_DYNAMITE))});

    weapon_aim_textures.insert({WeaponsAndTools::GREEN_GRENADE,
                                (pool.get_aim_texture(WeaponAiming::WORM_AIM_GREEN_GRENADE))});

    weapon_aim_textures.insert({WeaponsAndTools::RED_GRENADE,
                                (pool.get_aim_texture(WeaponAiming::WORM_AIM_RED_GRENADE))});

    weapon_aim_textures.insert(
            {WeaponsAndTools::BANANA, (pool.get_aim_texture(WeaponAiming::WORM_AIM_BANANA))});

    weapon_aim_textures.insert({WeaponsAndTools::AIR_STRIKE,
                                (pool.get_aim_texture(WeaponAiming::WORM_AIM_AIR_STRIKE))});

    weapon_aim_textures.insert({WeaponsAndTools::TELEPORT,
                                (pool.get_aim_texture(WeaponAiming::WORM_AIM_TELEPORT))});
}

AimAnimation::AimAnimation(TexturesPool& pool):
        crosshair_texture(pool.get_actor_texture(Actors::CROSSHAIR)),
        power_charge_animation(std::make_unique<Animation>(
                pool.get_actor_texture(Actors::POWER_CHARGE_BAR), 6, 2, false)),
        current_inclination(0) {
    this->load_all_aim_textures(pool);
}

void AimAnimation::render(WeaponsAndTools current_weapon, SDL2pp::Renderer& renderer,
                          SDL2pp::Rect dest, SDL_RendererFlip flipType, double angle) {

    if (current_weapon != WeaponsAndTools::DYNAMITE &&
        current_weapon != WeaponsAndTools::AIR_STRIKE &&
        current_weapon != WeaponsAndTools::TELEPORT) {
        renderer.Copy((*weapon_aim_textures.at(current_weapon)),
                      SDL2pp::Rect(0,
                                   std::min((16 * 60 - (60) * int(-1 * ((this->current_inclination /
                                                                         (M_PI / 32))))),
                                            1860),
                                   35, 60),
                      dest,
                      angle,            // don't rotate
                      SDL2pp::NullOpt,  // rotation center - not needed
                      flipType);

        if (flipType == SDL_FLIP_HORIZONTAL) {
            renderer.Copy(
                    (*crosshair_texture),
                    SDL2pp::Rect(0,
                                 std::min((16 * 60 - (60) * int(-1 * ((this->current_inclination /
                                                                       (M_PI / 32))))),
                                          1860),
                                 35, 60),
                    // SDL2pp::Rect (dest.x * (1 + (cos(current_inclination)*0.35)), (dest.y * (1 -
                    // (sin(current_inclination))*0.35)), 35, 60),
                    SDL2pp::Rect((dest.x + (40 * cos(current_inclination))),
                                 (dest.y - 40 * sin(current_inclination)), 35, 60),
                    angle,            // don't rotate
                    SDL2pp::NullOpt,  // rotation center - not needed
                    flipType);
        } else {
            renderer.Copy(
                    (*crosshair_texture),
                    SDL2pp::Rect(0,
                                 std::min((16 * 60 - (60) * int(-1 * ((this->current_inclination /
                                                                       (M_PI / 32))))),
                                          1860),
                                 35, 60),
                    // SDL2pp::Rect (dest.x * (1 - cos(current_inclination)*0.35), dest.y * (1 -
                    // sin(current_inclination)*0.35), 35, 60),
                    SDL2pp::Rect((dest.x - (40 * cos(current_inclination))),
                                 (dest.y - 40 * sin(current_inclination)), 35, 60),
                    angle,            // don't rotate
                    SDL2pp::NullOpt,  // rotation center - not needed
                    flipType);
        }

        power_charge_animation->render(renderer, SDL2pp::Rect(dest.x, dest.y - 35, 35, 60), 0, 0);

    } else {
        renderer.Copy((*weapon_aim_textures.at(current_weapon)), SDL2pp::Rect(0, 0, 35, 60), dest,
                      angle,            // don't rotate
                      SDL2pp::NullOpt,  // rotation center - not needed
                      flipType);
    }
}

void AimAnimation::update(float new_inclination_degrees, bool charging_power) {
    current_inclination = new_inclination_degrees;
    power_charge_animation->update(!charging_power);
}
