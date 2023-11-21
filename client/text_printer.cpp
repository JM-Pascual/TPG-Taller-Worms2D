#include "text_printer.h"

TextPrinter::TextPrinter(size_t font_size) :
        font(FONT_PATH "/Mefika-Font.ttf", font_size){}

void TextPrinter::print_text(SDL2pp::Renderer& renderer, const std::string& text, int x, int y) {
    SDL2pp::Texture text_texture(renderer,
                                 font.RenderText_Solid(text, SDL_Color{255, 255, 255, 255}));

    SDL2pp::Rect text_rect(x, y,
                           text_texture.GetWidth(), text_texture.GetHeight());

    renderer.Copy(text_texture, SDL2pp::NullOpt, text_rect);
}
