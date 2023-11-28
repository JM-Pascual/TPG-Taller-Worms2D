#include "text_printer.h"

TextPrinter::TextPrinter(unsigned int font_size, std::shared_ptr<SDL2pp::Texture>& font_background) :
        font(FONT_PATH "/kartooni.regular.ttf", font_size),
        background(font_background),
        font_size(font_size){}

void TextPrinter::  print_text(SDL2pp::Renderer& renderer, const std::string& text,
                             int x, int y, int x_offset, int y_offset, bool with_background) {
    if (with_background){
        renderer.Copy((*background),
                      SDL2pp::NullOpt,
                      SDL2pp::Rect(x, y-y_offset, background->GetWidth(), background->GetHeight()));
    }
    SDL2pp::Texture text_texture(renderer,
                                 font.RenderText_Solid(text, SDL_Color{221, 15, 15, 255}));

    SDL2pp::Rect text_rect(x+(x_offset/2), y-((y_offset*5)/8),
                           text_texture.GetWidth(), text_texture.GetHeight());

    renderer.Copy(text_texture, SDL2pp::NullOpt, text_rect);
}
