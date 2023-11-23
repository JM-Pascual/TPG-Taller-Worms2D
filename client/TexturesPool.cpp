#include "TexturesPool.h"

template <typename EnumType>
void TexturesPool::load_texture_into_map(
        const std::string& filePath,
        std::unordered_map<EnumType, std::shared_ptr<SDL2pp::Texture>>& textureMap,
        EnumType texture_enum, bool with_alpha_blending) {

    if (with_alpha_blending){
        textureMap.insert({texture_enum, std::make_shared<SDL2pp::Texture>(
                                                 (*renderer), SDL2pp::Surface(filePath)
                                                                      .SetColorKey(true, 0x000000))});
        textureMap[texture_enum]->SetBlendMode(SDL_BLENDMODE_BLEND);
    } else {
        textureMap.insert({texture_enum, std::make_shared<SDL2pp::Texture>((*renderer),
                                                                           SDL2pp::Surface(filePath))});
    }
}

void TexturesPool::load_general_worm_textures() {
    /// Loads all the body actors_textures and enables alpha blending
    load_texture_into_map(DATA_PATH "/worms/worm-left.png", actors_textures, Actors::WORM);
    load_texture_into_map(DATA_PATH "/worms/worm-jump-up.png", actors_textures, Actors::JUMPING_WORM);
    load_texture_into_map(DATA_PATH "/worms/worm-backflip.png", actors_textures, Actors::BACKFLIP_WORM);
    load_texture_into_map(DATA_PATH "/worms/worm-death.png", actors_textures, Actors::DYING_WORM);
}

void TexturesPool::load_draw_textures() {
    /// Loads all the weapon draw actors_textures and enables alpha blending (If neccesary)
    load_texture_into_map(DATA_PATH "/worms/worm-bazooka-draw.png", draw_textures, WeaponsDraw::WORM_DRAW_BAZOOKA, false);
    load_texture_into_map(DATA_PATH "/worms/worm-dynamite-draw.png", draw_textures, WeaponsDraw::WORM_DRAW_DYNAMITE);
    load_texture_into_map(DATA_PATH "/worms/worm-ggrenade-draw.png", draw_textures, WeaponsDraw::WORM_DRAW_GREEN_GRENADE);
    load_texture_into_map(DATA_PATH "/worms/worm-banana-draw.png", draw_textures, WeaponsDraw::WORM_DRAW_BANANA);
    load_texture_into_map(DATA_PATH "/worms/worm-mortar-draw.png", draw_textures, WeaponsDraw::WORM_DRAW_MORTAR);
}

void TexturesPool::load_aiming_textures() {
    /// Loads all the worm weapon holding actors_textures and enables alpha blending (If neccesary)
    load_texture_into_map(DATA_PATH "/worms/worm-bazooka-aim.png", aim_textures, WeaponAiming::WORM_AIM_BAZOOKA);
    load_texture_into_map(DATA_PATH "/worms/worm-dynamite-aim.png", aim_textures, WeaponAiming::WORM_AIM_DYNAMITE);
    load_texture_into_map(DATA_PATH "/worms/worm-ggrenade-aim.png", aim_textures, WeaponAiming::WORM_AIM_GREEN_GRENADE);
    load_texture_into_map(DATA_PATH "/worms/worm-banana-aim.png", aim_textures, WeaponAiming::WORM_AIM_BANANA);
    load_texture_into_map(DATA_PATH "/worms/worm-mortar-aim.png", aim_textures, WeaponAiming::WORM_AIM_MORTAR);
}

void TexturesPool::load_projectile_textures() {
    /// Loads all the projectile textures and enables alpha blending (If neccesary)
    load_texture_into_map(DATA_PATH "/weapons/bazooka-missile.png", projectile_textures, Projectiles::BAZOOKA_PROYECTILE, false);
    load_texture_into_map(DATA_PATH "/weapons/mortar-missile.png", projectile_textures, Projectiles::MORTAR_PROYECTILE, false);
    load_texture_into_map(DATA_PATH "/weapons/mortar-fragment.png", projectile_textures, Projectiles::MORTAR_FRAGMENT);
    load_texture_into_map(DATA_PATH "/weapons/green-grenade-projectile.png", projectile_textures, Projectiles::GREEN_GRENADE_PROYECTILE);
    load_texture_into_map(DATA_PATH "/weapons/spinning-banana.png", projectile_textures, Projectiles::BANANA_PROYECTILE);
    load_texture_into_map(DATA_PATH "/weapons/dynamite-projectile.png", projectile_textures, Projectiles::DYNAMITE_PROYECTILE);
}

void TexturesPool::load_effect_textures() {
    load_texture_into_map(DATA_PATH "/weapons/bazooka-explosion.png", effect_textures, Effects::NORMAL_EXPLOSION);
    load_texture_into_map(DATA_PATH "/weapons/mortar-fragment-explosion.png", effect_textures, Effects::FRAGMENT_EXPLOSION);
}

void TexturesPool::load_combat_textures() {
    load_texture_into_map(DATA_PATH "/weapons/crosshair.png", actors_textures, Actors::CROSSHAIR);
    load_texture_into_map(DATA_PATH "/miscellaneous/font-background.png", actors_textures, Actors::STATE_SIGN);
    load_texture_into_map(DATA_PATH "/weapons/loading-shot.png", actors_textures, Actors::POWER_CHARGE_BAR);
}

void TexturesPool::load_worm_textures() {
    this->load_general_worm_textures();
    this->load_draw_textures();
    this->load_aiming_textures();
}

void TexturesPool::load_level_textures() {
    /// Loads all the level actors_textures and enables alpha blending
    load_texture_into_map(DATA_PATH "/stage/gradient.bmp", level_actors_textures, LevelActors::GRADIENT, false);
    load_texture_into_map(DATA_PATH "/stage/background.png", level_actors_textures, LevelActors::BACKGROUND);
    load_texture_into_map(DATA_PATH "/stage/bridge.png", level_actors_textures, LevelActors::LONG_BAR);
    load_texture_into_map(DATA_PATH "/blue-water-sprites/blue_water.png", level_actors_textures, LevelActors::WATER);
}

void TexturesPool::load_tombstones_textures() {
    /// Loads all the tombstones textures and enables alpha blending (If neccesary)
    load_texture_into_map(DATA_PATH "/miscellaneous/tombstone1.png", tombstones_textures, Tombstones::TOMBSTONE_1);
    load_texture_into_map(DATA_PATH "/miscellaneous/tombstone2.png", tombstones_textures, Tombstones::TOMBSTONE_2);
    load_texture_into_map(DATA_PATH "/miscellaneous/tombstone3.png", tombstones_textures, Tombstones::TOMBSTONE_3);
    load_texture_into_map(DATA_PATH "/miscellaneous/tombstone4.png", tombstones_textures, Tombstones::TOMBSTONE_4);
    load_texture_into_map(DATA_PATH "/miscellaneous/tombstone5.png", tombstones_textures, Tombstones::TOMBSTONE_5);
    load_texture_into_map(DATA_PATH "/miscellaneous/tombstone6.png", tombstones_textures, Tombstones::TOMBSTONE_6);
}

TexturesPool::TexturesPool(std::shared_ptr<SDL2pp::Renderer>& game_renderer) :
        renderer(game_renderer) {
    load_level_textures();
    load_worm_textures();
    load_combat_textures();
    load_projectile_textures();
    load_effect_textures();
    load_tombstones_textures();
}

std::shared_ptr<SDL2pp::Texture>& TexturesPool::get_actor_texture(Actors actor_to_fetch) {
    return (actors_textures[actor_to_fetch]);
}

std::shared_ptr<SDL2pp::Texture>& TexturesPool::get_level_texture(
        LevelActors level_actor_to_fetch) {
    return (level_actors_textures[level_actor_to_fetch]);
}

std::shared_ptr<SDL2pp::Texture>& TexturesPool::get_aim_texture(WeaponAiming aim_texture_to_fetch) {
    return (aim_textures[aim_texture_to_fetch]);
}

std::shared_ptr<SDL2pp::Texture>& TexturesPool::get_draw_texture(WeaponsDraw draw_texture_to_fetch) {
    return (draw_textures[draw_texture_to_fetch]);
}

std::shared_ptr<SDL2pp::Texture>& TexturesPool::get_projectile_texture(
        Projectiles projectile_texture_to_fetch) {
    return (projectile_textures[projectile_texture_to_fetch]);
}

std::shared_ptr<SDL2pp::Texture>& TexturesPool::get_effect_texture(
        Effects effect_texture_to_fetch) {
    return (effect_textures[effect_texture_to_fetch]);
}

std::shared_ptr<SDL2pp::Texture>& TexturesPool::get_tombstone_texture(
        Tombstones tombstone_texture_to_fetch) {
    return (tombstones_textures[tombstone_texture_to_fetch]);
}

