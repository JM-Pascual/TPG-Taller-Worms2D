#include "TexturesPool.h"

TexturesPool::TexturesPool(std::shared_ptr<SDL2pp::Renderer>& game_renderer) :
        renderer(game_renderer) {
    load_level_textures();
    load_water_textures();
    load_worm_textures();
    load_weapon_textures();
    load_projectile_textures();
    load_effect_textures();
}

void TexturesPool::load_general_worm_textures() {
    /// Loads all the body actors_textures and enables alpha blending
    actors_textures.insert({Actors::WORM, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/worms/worm-left.png")
                                                                                                 .SetColorKey(true, 0x000000))});
    actors_textures[Actors::WORM]->SetBlendMode(SDL_BLENDMODE_BLEND);

    actors_textures.insert({Actors::JUMPING_WORM, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/worms/worm-jump-up.png")
                                                                                                         .SetColorKey(true, 0x000000))});
    actors_textures[Actors::JUMPING_WORM]->SetBlendMode(SDL_BLENDMODE_BLEND);

    actors_textures.insert({Actors::BACKFLIP_WORM, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/worms/worm-backflip.png")
                                                                                                          .SetColorKey(true, 0x000000))});
    actors_textures[Actors::BACKFLIP_WORM]->SetBlendMode(SDL_BLENDMODE_BLEND);
}

void TexturesPool::load_draw_textures() {
    /// Loads all the weapon draw actors_textures and enables alpha blending (If neccesary)
    draw_textures.insert({WeaponsDraw::WORM_DRAW_BAZOOKA,
                          std::make_shared<SDL2pp::Texture>((*renderer),
                                                            SDL2pp::Surface(
                                                                    DATA_PATH
                                                                    "/worms/worm-bazooka-draw.png"))});

    draw_textures.insert({WeaponsDraw::WORM_DRAW_DYNAMITE,
                          std::make_shared<SDL2pp::Texture>((*renderer),
                                                            SDL2pp::Surface(
                                                                    DATA_PATH
                                                                    "/worms/worm-dynamite-draw.png")
                                                                    .SetColorKey(true, 0x000000))});
    draw_textures[WeaponsDraw::WORM_DRAW_DYNAMITE]->SetBlendMode(SDL_BLENDMODE_BLEND);

    draw_textures.insert({WeaponsDraw::WORM_DRAW_GREEN_GRENADE,
                          std::make_shared<SDL2pp::Texture>((*renderer),
                                                            SDL2pp::Surface(
                                                                    DATA_PATH
                                                                    "/worms/worm-ggrenade-draw.png")
                                                                    .SetColorKey(true, 0x000000))});
    draw_textures[WeaponsDraw::WORM_DRAW_GREEN_GRENADE]->SetBlendMode(SDL_BLENDMODE_BLEND);

    draw_textures.insert({WeaponsDraw::WORM_DRAW_BANANA,
                          std::make_shared<SDL2pp::Texture>((*renderer),
                                                            SDL2pp::Surface(
                                                                    DATA_PATH
                                                                    "/worms/worm-banana-draw.png")
                                                                    .SetColorKey(true, 0x000000))});
    draw_textures[WeaponsDraw::WORM_DRAW_BANANA]->SetBlendMode(SDL_BLENDMODE_BLEND);
}

void TexturesPool::load_aiming_textures() {
    /// Loads all the worm weapon holding actors_textures and enables alpha blending (If neccesary)
    aim_textures.insert({WeaponAiming::WORM_AIM_BAZOOKA,
                          std::make_shared<SDL2pp::Texture>((*renderer),
                                                            SDL2pp::Surface(
                                                                    DATA_PATH
                                                                    "/worms/worm-bazooka-aim.png"))});
    aim_textures[WeaponAiming::WORM_AIM_BAZOOKA]->SetBlendMode(SDL_BLENDMODE_BLEND);

    aim_textures.insert({WeaponAiming::WORM_AIM_DYNAMITE,
                          std::make_shared<SDL2pp::Texture>((*renderer),
                                                            SDL2pp::Surface(
                                                                    DATA_PATH
                                                                    "/worms/worm-dynamite-aim.png")
                                                                   .SetColorKey(true, 0x000000))});
    aim_textures[WeaponAiming::WORM_AIM_DYNAMITE]->SetBlendMode(SDL_BLENDMODE_BLEND);

    aim_textures.insert({WeaponAiming::WORM_AIM_GREEN_GRENADE,
                         std::make_shared<SDL2pp::Texture>((*renderer),
                                                           SDL2pp::Surface(
                                                                   DATA_PATH
                                                                   "/worms/worm-ggrenade-aim.png")
                                                                   .SetColorKey(true, 0x000000))});
    aim_textures[WeaponAiming::WORM_AIM_GREEN_GRENADE]->SetBlendMode(SDL_BLENDMODE_BLEND);

    aim_textures.insert({WeaponAiming::WORM_AIM_BANANA,
                         std::make_shared<SDL2pp::Texture>((*renderer),
                                                           SDL2pp::Surface(
                                                                   DATA_PATH
                                                                   "/worms/worm-banana-aim.png")
                                                                   .SetColorKey(true, 0x000000))});
    aim_textures[WeaponAiming::WORM_AIM_BANANA]->SetBlendMode(SDL_BLENDMODE_BLEND);
}

void TexturesPool::load_projectile_textures() {
    projectile_textures.insert({Projectiles::BAZOOKA_PROYECTILE,
                                std::make_shared<SDL2pp::Texture>((*renderer),
                                                                  SDL2pp::Surface(
                                                                          DATA_PATH "/weapons/bazooka-missile.png")
                                                                          .SetColorKey(true, 0x000000))});

    projectile_textures.insert({Projectiles::GREEN_GRENADE_PROYECTILE,
                                std::make_shared<SDL2pp::Texture>((*renderer),
                                                                  SDL2pp::Surface(
                                                                          DATA_PATH "/weapons/green-grenade-proyectile.png")
                                                                          .SetColorKey(true, 0x000000))});
    projectile_textures[Projectiles::GREEN_GRENADE_PROYECTILE]->SetBlendMode(SDL_BLENDMODE_BLEND);

    projectile_textures.insert({Projectiles::BANANA_PROYECTILE,
                                std::make_shared<SDL2pp::Texture>((*renderer),
                                                                  SDL2pp::Surface(
                                                                          DATA_PATH "/weapons/spinning-banana.png")
                                                                          .SetColorKey(true, 0x000000))});
    projectile_textures[Projectiles::BANANA_PROYECTILE]->SetBlendMode(SDL_BLENDMODE_BLEND);

    projectile_textures.insert({Projectiles::DYNAMITE_PROYECTILE,
                                std::make_shared<SDL2pp::Texture>((*renderer),
                                                                  SDL2pp::Surface(
                                                                          DATA_PATH "/weapons/dynamite-proyectile.png")
                                                                          .SetColorKey(true, 0x000000))});
    projectile_textures[Projectiles::DYNAMITE_PROYECTILE]->SetBlendMode(SDL_BLENDMODE_BLEND);
}

void TexturesPool::load_effect_textures() {
    effect_textures.insert({Effects::NORMAL_EXPLOSION,
                            std::make_shared<SDL2pp::Texture>((*renderer),
                                                              SDL2pp::Surface(DATA_PATH "/weapons/bazooka-explosion.png")
                                                                                                              .SetColorKey(true, 0x000000))});

    effect_textures[Effects::NORMAL_EXPLOSION]->SetBlendMode(SDL_BLENDMODE_BLEND);
}

void TexturesPool::load_worm_textures() {
    this->load_general_worm_textures();
    this->load_draw_textures();
    this->load_aiming_textures();
}

void TexturesPool::load_weapon_textures() {
    actors_textures.insert({Actors::CROSSHAIR, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/weapons/crosshair.png")
                                                                                               .SetColorKey(true, 0x000000))});

    actors_textures[Actors::CROSSHAIR]->SetBlendMode(SDL_BLENDMODE_BLEND);

    actors_textures.insert({Actors::POWER_CHARGE_BAR, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/weapons/loading-shot.png")
                                                                                                       .SetColorKey(true, 0x000000))});

    actors_textures[Actors::POWER_CHARGE_BAR]->SetBlendMode(SDL_BLENDMODE_BLEND);
}

void TexturesPool::load_level_textures() {
    /// Loads all the level actors_textures and enables alpha blending

    actors_textures.insert({Actors::GRADIENT, std::make_shared<SDL2pp::Texture>((*renderer),SDL2pp::Surface(DATA_PATH "/stage/gradient.bmp")
                                                                                                  .SetColorKey(true, 0x000000))});

    actors_textures.insert({Actors::BACKGROUND, std::make_shared<SDL2pp::Texture>((*renderer),SDL2pp::Surface(DATA_PATH "/stage/background.png")
                                                                                                       .SetColorKey(true, 0x000000))});
    actors_textures[Actors::BACKGROUND]->SetBlendMode(SDL_BLENDMODE_BLEND);

    actors_textures.insert({Actors::BRIDGE, std::make_shared<SDL2pp::Texture>((*renderer),SDL2pp::Surface(DATA_PATH "/stage/bridge.png")
                                                                                                .SetColorKey(true, 0x000000))});
    actors_textures[Actors::BRIDGE]->SetBlendMode(SDL_BLENDMODE_BLEND);
}

void TexturesPool::load_tombstones_textures() {
    tombstones_textures.insert({Tombstones::TOMBSTONE_1, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/miscellaneous/tombstone1.png")
                                                                                                       .SetColorKey(true, 0x000000))});
    tombstones_textures[Tombstones::TOMBSTONE_1]->SetBlendMode(SDL_BLENDMODE_BLEND);

    tombstones_textures.insert({Tombstones::TOMBSTONE_2, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/miscellaneous/tombstone2.png")
                                                                                                       .SetColorKey(true, 0x000000))});
    tombstones_textures[Tombstones::TOMBSTONE_2]->SetBlendMode(SDL_BLENDMODE_BLEND);

    tombstones_textures.insert({Tombstones::TOMBSTONE_3, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/miscellaneous/tombstone3.png")
                                                                                                       .SetColorKey(true, 0x000000))});
    tombstones_textures[Tombstones::TOMBSTONE_3]->SetBlendMode(SDL_BLENDMODE_BLEND);

    tombstones_textures.insert({Tombstones::TOMBSTONE_4, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/miscellaneous/tombstone4.png")
                                                                                                       .SetColorKey(true, 0x000000))});
    tombstones_textures[Tombstones::TOMBSTONE_4]->SetBlendMode(SDL_BLENDMODE_BLEND);

    tombstones_textures.insert({Tombstones::TOMBSTONE_5, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/miscellaneous/tombstone5.png")
                                                                                                       .SetColorKey(true, 0x000000))});
    tombstones_textures[Tombstones::TOMBSTONE_5]->SetBlendMode(SDL_BLENDMODE_BLEND);

    tombstones_textures.insert({Tombstones::TOMBSTONE_6, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/miscellaneous/tombstone6.png")
                                                                                                       .SetColorKey(true, 0x000000))});
    tombstones_textures[Tombstones::TOMBSTONE_6]->SetBlendMode(SDL_BLENDMODE_BLEND);

}

void TexturesPool::load_water_textures(){
    /// Loads all the water actors_textures and enables alpha blending
    actors_textures.insert({Actors::WATER, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/blue-water-sprites/blue_water.png")
                                                                                           .SetColorKey(true, 0x000000))});
    actors_textures[Actors::WATER]->SetBlendMode(SDL_BLENDMODE_BLEND);
}

std::shared_ptr<SDL2pp::Texture>& TexturesPool::get_actor_texture(Actors actor_to_fetch) {
    return (actors_textures[actor_to_fetch]);
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