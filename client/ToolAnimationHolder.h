#ifndef TOOLANIMATIONHOLDER_H
#define TOOLANIMATIONHOLDER_H

#include <SDL2pp/SDL2pp.hh>
#include <unordered_map>

#include "SpecialToolAnimation.h"
#include "TexturesPool.h"

class ToolAnimationHolder {
private:
    /** Current weapon/tool. */
    WeaponsAndTools currently_equipped_item;
    /** Map of SDL actors_textures of the tool animations. */
    std::unordered_map<WeaponsAndTools, std::shared_ptr<SpecialToolAnimation>> tool_animations;

    void load_all_draw_animations(TexturesPool& pool);
public:
    explicit ToolAnimationHolder(TexturesPool& pool);

    void update(std::shared_ptr<WormStateG> &worm_state);

    void render(SDL2pp::Renderer& renderer, Camera& camera, int non_squared_width,
                int non_squared_height, SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL,
                double angle = 0.0);
};


#endif  // TOOLANIMATIONHOLDER_H
