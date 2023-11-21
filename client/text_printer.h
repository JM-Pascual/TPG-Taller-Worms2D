#ifndef TEXT_PRINTER_H
#define TEXT_PRINTER_H

#include <SDL2pp/SDL2pp.hh>

class TextPrinter {
private:
    SDL2pp::Font font;
public:
    explicit TextPrinter(size_t font_size);

    void print_text(SDL2pp::Renderer& renderer, const std::string& text, int x, int y);

    ~TextPrinter() = default;
};



#endif  // TEXT_PRINTER_H
