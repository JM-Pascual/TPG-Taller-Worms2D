#ifndef TEXT_PRINTER_H
#define TEXT_PRINTER_H

#include <SDL2pp/SDL2pp.hh>

#include "TexturesPool.h"

class TextPrinter {
private:
    SDL2pp::Font font;
    std::shared_ptr<SDL2pp::Texture>& state_sign;
    unsigned int font_size;
public:

    explicit TextPrinter(unsigned int font_size, TexturesPool& pool);

    void print_text(SDL2pp::Renderer& renderer, const std::string& text,
                    int x, int y, bool with_border = false);

    ~TextPrinter() = default;
};



#endif  // TEXT_PRINTER_H
