#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

#include "../common/const.h"

class TexturesPool;
class Camera;

class Window {
private:
    std::shared_ptr<SDL2pp::Window> game_window;
    std::shared_ptr<SDL2pp::Renderer> game_renderer;

    void render_stage_texture(const std::shared_ptr<SDL2pp::Texture>& texture,
                              SDL2pp::Rect destination);

public:
    Window(const int& width, const int& height);

    std::shared_ptr<SDL2pp::Renderer>& get_renderer();

    /// Clears the actors_textures in screen calling the SDL2pp::Renderer::Clear method
    void clear_textures();

    /// Presents the actors_textures in screen calling the SDL2pp::Renderer::Present method
    void present_textures();

    void render_stage(TexturesPool& pool, Camera& camera);

    ~Window() = default;

    friend class TexturesPool;
};


#endif  // WINDOW_H
