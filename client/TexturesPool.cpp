#include "TexturesPool.h"

TexturesPool::TexturesPool(std::shared_ptr<SDL2pp::Renderer>& game_renderer) :
        renderer(game_renderer) {
    load_level_textures();
    load_water_textures();
    load_worm_textures();
    load_weapon_textures();
}

void TexturesPool::load_worm_textures() {
    /// Loads all the body textures and enables alpha blending
    textures.insert({Actors::WORM, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/worms/worm-left.png")
                                                                                                                 .SetColorKey(true, 0x000000))});
    textures[Actors::WORM]->SetBlendMode(SDL_BLENDMODE_BLEND);

    textures.insert({Actors::JUMPING_WORM, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/worms/worm-jump-up.png")
                                                                                          .SetColorKey(true, 0x000000))});
    textures[Actors::JUMPING_WORM]->SetBlendMode(SDL_BLENDMODE_BLEND);

    textures.insert({Actors::BACKFLIP_WORM, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/worms/worm-backflip.png")
                                                                                                  .SetColorKey(true, 0x000000))});
    textures[Actors::BACKFLIP_WORM]->SetBlendMode(SDL_BLENDMODE_BLEND);

    /// Loads all the worm weapon holding textures and enables alpha blending (If neccesary)
    textures.insert({Actors::WORM_DRAW_BAZOOKA, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/worms/worm-bazooka-draw.png"))});
    textures.insert({Actors::WORM_HOLDING_BAZOOKA, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/worms/worm-bazooka-straight.png"))});
}

void TexturesPool::load_weapon_textures() {
    textures.insert({Actors::CROSSHAIR, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/weapons/crosshair.png")
                                                                                               .SetColorKey(true, 0x000000))});

    textures[Actors::CROSSHAIR]->SetBlendMode(SDL_BLENDMODE_BLEND);

    textures.insert({Actors::POWER_CHARGE_BAR, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/weapons/loading-shot.png")
                                                                                                       .SetColorKey(true, 0x000000))});

    textures[Actors::POWER_CHARGE_BAR]->SetBlendMode(SDL_BLENDMODE_BLEND);

    textures.insert({Actors::BAZOOKA_PROYECTILE, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/weapons/bazooka-missile2.png"))});

    textures.insert({Actors::BAZOOKA_EXPLOSION, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/weapons/bazooka-explosion.png")
                                                                                                        .SetColorKey(true, 0x000000))});

    textures[Actors::BAZOOKA_EXPLOSION]->SetBlendMode(SDL_BLENDMODE_BLEND);
}

void TexturesPool::load_level_textures() {
    /// Loads all the level textures and enables alpha blending

    textures.insert({Actors::GRADIENT, std::make_shared<SDL2pp::Texture>((*renderer),SDL2pp::Surface(DATA_PATH "/stage/gradient.bmp")
                                                                                                  .SetColorKey(true, 0x000000))});

    textures.insert({Actors::BACKGROUND, std::make_shared<SDL2pp::Texture>((*renderer),SDL2pp::Surface(DATA_PATH "/stage/background.png")
                                                                                                       .SetColorKey(true, 0x000000))});
    textures[Actors::BACKGROUND]->SetBlendMode(SDL_BLENDMODE_BLEND);

    textures.insert({Actors::BRIDGE, std::make_shared<SDL2pp::Texture>((*renderer),SDL2pp::Surface(DATA_PATH "/stage/bridge.png")
                                                                                                .SetColorKey(true, 0x000000))});
    textures[Actors::BRIDGE]->SetBlendMode(SDL_BLENDMODE_BLEND);
}

void TexturesPool::load_water_textures(){
    /// Loads all the water textures and enables alpha blending
    textures.insert({Actors::WATER, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/blue-water-sprites/blue_water.png")
                                                                                           .SetColorKey(true, 0x000000))});
    textures[Actors::WATER]->SetBlendMode(SDL_BLENDMODE_BLEND);
}
std::shared_ptr<SDL2pp::Texture>& TexturesPool::get_texture(Actors actor_to_fetch) {
    return (textures[actor_to_fetch]);
}
