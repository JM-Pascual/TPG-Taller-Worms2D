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
    void load_combat_textures();
    void load_projectile_textures();
    void load_effect_textures();
    void load_tombstones_textures();

    template <typename EnumType>
    void load_texture_into_map(const std::string& filePath,
                            std::unordered_map<EnumType, std::shared_ptr<SDL2pp::Texture>>& textureMap,
                            EnumType texture_enum, bool with_alpha_blending = true);

    std::unordered_map<Actors, std::shared_ptr<SDL2pp::Texture>> actors_textures;
    std::unordered_map<LevelActors, std::shared_ptr<SDL2pp::Texture>> level_actors_textures;
    std::unordered_map<WeaponAiming, std::shared_ptr<SDL2pp::Texture>> aim_textures;
    std::unordered_map<WeaponsDraw, std::shared_ptr<SDL2pp::Texture>> draw_textures;
    std::unordered_map<Projectiles, std::shared_ptr<SDL2pp::Texture>> projectile_textures;
    std::unordered_map<Effects, std::shared_ptr<SDL2pp::Texture>> effect_textures;
    std::unordered_map<Tombstones, std::shared_ptr<SDL2pp::Texture>> tombstones_textures;

    std::shared_ptr<SDL2pp::Renderer>& renderer;
public:
    explicit TexturesPool(std::shared_ptr<SDL2pp::Renderer>& game_renderer);

    std::shared_ptr<SDL2pp::Texture>& get_actor_texture(Actors actor_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_level_texture(LevelActors level_actor_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_draw_texture(WeaponsDraw draw_texture_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_aim_texture(WeaponAiming aim_texture_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_projectile_texture(Projectiles aim_texture_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_effect_texture(Effects aim_texture_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_tombstone_texture(Tombstones tombstone_texture_to_fetch);
};


#endif  // TEXTURESPOOL_H
