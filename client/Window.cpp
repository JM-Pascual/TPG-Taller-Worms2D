#include "Window.h"

#include "TexturesPool.h"
#include "camera.h"

Window::Window(const int& width, const int& height):
        game_window(std::make_shared<SDL2pp::Window>("Worms2D", SDL_WINDOWPOS_UNDEFINED,
                                                     SDL_WINDOWPOS_UNDEFINED, width, height,
                                                     SDL_WINDOW_RESIZABLE)),
        game_renderer(
                std::make_shared<SDL2pp::Renderer>((*game_window), -1, SDL_RENDERER_SOFTWARE)) {}

std::shared_ptr<SDL2pp::Renderer>& Window::get_renderer() { return game_renderer; }

void Window::render_stage_texture(const std::shared_ptr<SDL2pp::Texture>& texture,
                                  SDL2pp::Rect destination) {

    game_renderer->Copy((*texture), SDL2pp::NullOpt, destination);
}

void Window::clear_textures() { game_renderer->Clear(); }

void Window::present_textures() { game_renderer->Present(); }

void Window::render_stage(TexturesPool& pool, Camera& camera) {
    int vcenter = (game_renderer->GetOutputHeight() / 2);

    render_stage_texture(
            pool.get_level_texture(LevelActors::GRADIENT),
            SDL2pp::Rect(0, 0, game_renderer->GetOutputWidth(), game_renderer->GetOutputHeight()));

    render_stage_texture(pool.get_level_texture(LevelActors::BACKGROUND),
                         SDL2pp::Rect(0, vcenter - 160, game_renderer->GetOutputWidth(), 200));

    for (int i = 0; i < 19; i++) {
        render_stage_texture(pool.get_level_texture(LevelActors::LONG_BAR),
                             camera.calcRect(0 + i * 70, vcenter + 40, 70, 20));
    }
}
