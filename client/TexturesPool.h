#ifndef TEXTURESPOOL_H
#define TEXTURESPOOL_H

#include <SDL2pp/SDL2pp.hh>
#include <memory>
#include <unordered_map>

#include "Window.h"
#include "../common/const.h"

class TexturesPool {
private:
    void load_worm_textures();
    void load_aiming_textures();
    void load_draw_textures();
    void load_general_worm_textures();
    void load_level_textures();
    void load_water_textures();
    void load_weapon_textures();

    std::unordered_map<Actors, std::shared_ptr<SDL2pp::Texture>> actors_textures;
    std::unordered_map<WeaponAiming, std::shared_ptr<SDL2pp::Texture>> aim_textures;
    std::unordered_map<WeaponsDraw, std::shared_ptr<SDL2pp::Texture>> draw_textures;

    std::shared_ptr<SDL2pp::Renderer>& renderer;
public:
    explicit TexturesPool(std::shared_ptr<SDL2pp::Renderer>& game_renderer);

    std::shared_ptr<SDL2pp::Texture>& get_actor_texture(Actors actor_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_draw_texture(WeaponsDraw draw_texture_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_aim_texture(WeaponAiming aim_texture_to_fetch);
};


#endif  // TEXTURESPOOL_H
