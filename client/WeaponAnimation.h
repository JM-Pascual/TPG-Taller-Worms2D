#ifndef WEAPONHOLDANIMATION_H
#define WEAPONHOLDANIMATION_H

#include <SDL2pp/SDL2pp.hh>

#include "TexturesPool.h"

class SdlTexture;
class Area;

class WeaponAnimation {
private:
    /** Current weapon. */
    WeaponsAndTools current_weapon;
    /** SDL texture of the raw image. */
    std::shared_ptr<SDL2pp::Texture>& current_weapon_texture;
    /** Reference to the texture holder */
    TexturesPool& pool;
    /** Current worm inclination. */
    float current_inclination;

    void change_weapon_texture(WeaponsAndTools new_weapon);
public:
    explicit WeaponAnimation(TexturesPool& pool);

    void update(float new_inclination_degrees, WeaponsAndTools equipped_weapon);

    void render(SDL2pp::Renderer &renderer, SDL2pp::Rect dest,
                SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL,
                double angle = 0.0);
};


#endif  // WEAPONHOLDANIMATION_H
