#ifndef TEXT_PRINTER_H
#define TEXT_PRINTER_H

#include <SDL2pp/SDL2pp.hh>

#include "TexturesPool.h"

class TextPrinter {
private:
    SDL2pp::Font font;
    std::shared_ptr<SDL2pp::Texture>& background;
    unsigned int font_size;

    static SDL_Color interpret_team_colour(TeamColours team);
public:

    explicit TextPrinter(unsigned int font_size, std::shared_ptr<SDL2pp::Texture>& font_background);

    void print_text(SDL2pp::Renderer& renderer, const std::string& text,
                    int x, int y, int in_line_adjustment = 0, int x_offset = 0, int y_offset = 0,
                    bool with_background = false);

    void print_team_text(SDL2pp::Renderer& renderer, const std::string& text, TeamColours team,
                    int x, int y, int in_line_adjustment = 0, int x_offset = 0, int y_offset = 0,
                    bool with_background = false);

    ~TextPrinter() = default;
};



#endif  // TEXT_PRINTER_H
