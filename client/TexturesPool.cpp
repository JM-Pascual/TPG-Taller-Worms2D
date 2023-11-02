#include "TexturesPool.h"

TexturesPool::TexturesPool(std::shared_ptr<SDL2pp::Renderer>& game_renderer) :
        renderer(game_renderer) {
    load_level_textures();
    load_water_textures();
    load_worm_texture();
}

void TexturesPool::load_worm_texture() {
    /// Loads all the worm textures and enables alpha blending
    textures.insert({Actors::WORM, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/worms/worm-left.png")
                                                                                                                 .SetColorKey(true, 0x000000))});
    textures[Actors::WORM]->SetBlendMode(SDL_BLENDMODE_BLEND);
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
    textures.insert({Actors::WATER, std::make_shared<SDL2pp::Texture>((*renderer), SDL2pp::Surface(DATA_PATH "/blue-water-sprites/blue_concat3.bmp")
                                                                                           .SetColorKey(true, 0x000000))});
    textures[Actors::WATER]->SetBlendMode(SDL_BLENDMODE_BLEND);
}

std::shared_ptr<SDL2pp::Texture>& TexturesPool::get_texture(Actors actor_to_fetch) {
    return (textures[actor_to_fetch]);
}