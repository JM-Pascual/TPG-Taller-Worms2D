#ifndef TEXTURESSINGLETON_H
#define TEXTURESSINGLETON_H

#include <SDL2pp/SDL2pp.hh>
#include <memory>
#include <unordered_map>

#include "Window.h"
#include "../common/const.h"

class TexturesPool {
private:
    void load_worm_textures();
    void load_level_textures();
    void load_water_textures();
    void load_weapon_textures();

    std::unordered_map<Actors, std::shared_ptr<SDL2pp::Texture>> textures;
    std::shared_ptr<SDL2pp::Renderer>& renderer;
public:
    explicit TexturesPool(std::shared_ptr<SDL2pp::Renderer>& game_renderer);

    std::shared_ptr<SDL2pp::Texture>& get_texture(Actors actor_to_fetch);
};


#endif  // TEXTURESSINGLETON_H
