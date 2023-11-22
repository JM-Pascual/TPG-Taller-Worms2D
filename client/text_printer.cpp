#include "text_printer.h"

TextPrinter::TextPrinter(unsigned int font_size, TexturesPool& pool) :
        font(FONT_PATH "/Mefika-Font.ttf", font_size),
        state_sign(pool.get_actor_texture(Actors::STATE_SIGN)),
        font_size(font_size){}

void TextPrinter::print_text(SDL2pp::Renderer& renderer, const std::string& text,
                             int x, int y, bool with_border) {
    if (with_border){
        renderer.Copy((*state_sign),
                      SDL2pp::NullOpt,
                      SDL2pp::Rect(x-10, y-12, 40, 45));
    }
    SDL2pp::Texture text_texture(renderer,
                                 font.RenderText_Solid(text, SDL_Color{255, 255, 255, 255}));

    SDL2pp::Rect text_rect(x, y,
                           text_texture.GetWidth(), text_texture.GetHeight());

    renderer.Copy(text_texture, SDL2pp::NullOpt, text_rect);
}
