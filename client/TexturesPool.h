#ifndef TEXTURESPOOL_H
#define TEXTURESPOOL_H

#include <memory>
#include <string>
#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "../common/const.h"

#include "Window.h"

class TexturesPool {
private:
    void load_worm_textures();
    void load_aiming_textures();
    void load_draw_textures();
    void load_general_worm_textures();
    void load_general_textures();
    void load_combat_textures();
    void load_projectile_textures();
    void load_tool_use_textures();
    void load_effect_textures();
    void load_weapon_miniature_textures();
    void load_tombstones_textures();

    template <typename EnumType>
    void load_texture_into_map(
            const std::string& filePath,
            std::unordered_map<EnumType, std::shared_ptr<SDL2pp::Texture>>& textureMap,
            const EnumType& texture_enum, const bool& with_alpha_blending = true);

    std::unordered_map<Actors, std::shared_ptr<SDL2pp::Texture>> actors_textures;
    std::unordered_map<TerrainActors, std::shared_ptr<SDL2pp::Texture>> level_actors_textures;
    std::unordered_map<WeaponAiming, std::shared_ptr<SDL2pp::Texture>> aim_textures;
    std::unordered_map<WeaponsDraw, std::shared_ptr<SDL2pp::Texture>> draw_textures;
    std::unordered_map<Projectiles, std::shared_ptr<SDL2pp::Texture>> projectile_textures;
    std::unordered_map<ToolUsage, std::shared_ptr<SDL2pp::Texture>> tool_usage_textures;
    std::unordered_map<VisualEffects, std::shared_ptr<SDL2pp::Texture>> effect_textures;
    std::unordered_map<WeaponsAndTools, std::shared_ptr<SDL2pp::Texture>> miniature_weapons;
    std::unordered_map<Tombstones, std::shared_ptr<SDL2pp::Texture>> tombstones_textures;

    std::shared_ptr<SDL2pp::Renderer>& renderer;

public:
    explicit TexturesPool(std::shared_ptr<SDL2pp::Renderer>& game_renderer);

    void load_level_textures(const std::string& level_name);
    std::shared_ptr<SDL2pp::Texture>& get_actor_texture(const Actors& actor_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_level_texture(const TerrainActors& level_actor_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_draw_texture(const WeaponsDraw& draw_texture_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_aim_texture(const WeaponAiming& aim_texture_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_projectile_texture(
            const Projectiles& aim_texture_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_tool_usage_texture(
            const ToolUsage& tool_use_texture_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_effect_texture(const VisualEffects& aim_texture_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_tombstone_texture(
            const Tombstones& tombstone_texture_to_fetch);
    std::shared_ptr<SDL2pp::Texture>& get_weapon_miniature(WeaponsAndTools weapon_to_fetch);
};


#endif  // TEXTURESPOOL_H
