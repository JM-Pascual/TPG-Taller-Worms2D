#include "Window.h"

#include "TexturesPool.h"
#include "camera.h"

Window::Window(const int& width, const int& height):
        game_window(std::make_shared<SDL2pp::Window>("Worms2D", SDL_WINDOWPOS_UNDEFINED,
                                                     SDL_WINDOWPOS_UNDEFINED, width, height,
                                                     SDL_WINDOW_RESIZABLE)),
        game_renderer(
                std::make_shared<SDL2pp::Renderer>((*game_window), -1, SDL_RENDERER_SOFTWARE)) {}

void Window::load_background_textures(TexturesPool& pool) {
    background_textures.insert({TerrainActors::GRADIENT, pool.get_level_texture(TerrainActors::GRADIENT)});
    background_textures.insert({TerrainActors::BACKGROUND, pool.get_level_texture(TerrainActors::BACKGROUND)});
}

std::shared_ptr<SDL2pp::Renderer>& Window::get_renderer() { return game_renderer; }

void Window::render_stage_texture(const std::shared_ptr<SDL2pp::Texture>& texture,
                                  SDL2pp::Rect destination) {

    game_renderer->Copy((*texture), SDL2pp::NullOpt, destination);
}

void Window::clear_textures() { game_renderer->Clear(); }

void Window::present_textures() { game_renderer->Present(); }

void Window::render_background(TexturesPool& pool) {
    int vcenter = (game_renderer->GetOutputHeight() / 2);

    if (background_textures.empty()) {
        load_background_textures(pool);
    }

    render_stage_texture(
            background_textures.at(TerrainActors::GRADIENT),
            SDL2pp::Rect(0, 0, game_renderer->GetOutputWidth(), game_renderer->GetOutputHeight()));

    render_stage_texture(
            background_textures.at(TerrainActors::BACKGROUND),
            SDL2pp::Rect(0, vcenter - 160, game_renderer->GetOutputWidth(), 200));
}
