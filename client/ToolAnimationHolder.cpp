#include "ToolAnimationHolder.h"

ToolAnimationHolder::ToolAnimationHolder(TexturesPool& pool) :
        currently_equipped_item(WeaponsAndTools::BAZOOKA) {
    load_all_draw_animations(pool);
}

void ToolAnimationHolder::load_all_draw_animations(TexturesPool& pool) {
    tool_animations.insert({
            WeaponsAndTools::TELEPORT, std::make_unique<TeleportAnimation>(
                                             pool.get_tool_usage_texture(ToolUsage::TELEPORT_USE)
                                                     , 48, 2, false)});
}

void ToolAnimationHolder::update(std::shared_ptr<WormStateG>& worm_state) {
    currently_equipped_item = worm_state->weapon;

    if (tool_animations.count(currently_equipped_item) != 0){
        tool_animations.at(currently_equipped_item)->update_tool_animation(worm_state);
    }
}

void ToolAnimationHolder::render(SDL2pp::Renderer& renderer, Camera& camera, int non_squared_width,
                                 int non_squared_height, SDL_RendererFlip flipType, double angle) {

    tool_animations.at(currently_equipped_item)->render(renderer, camera, non_squared_width,
                                             non_squared_height, flipType, angle);
}
