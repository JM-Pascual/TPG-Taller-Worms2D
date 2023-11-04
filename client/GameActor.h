#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common/GameState.h"
#include "../common/const.h"
#include "../common/vector2d.h"

#include "Animation.h"
#include "TexturesPool.h"

// ----------------------- ACTOR INTERFACE ----------------------

class GameActor {
protected:
    Vector2D position;

public:
    GameActor(const float& x, const float& y): position(x, y) {}
    virtual void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) = 0;
    virtual void update(const std::shared_ptr<GameState>& actor_state, unsigned int ms) = 0;
    virtual ~GameActor() = default;
};

// ----------------------- WORM ----------------------

class Worm: public GameActor {
private:
    bool is_walking;
    bool facing_right;
    Animation worm_animation;

public:
    Worm(const std::shared_ptr<GameState>& initial_state, float ms, TexturesPool& pool):
            GameActor(std::dynamic_pointer_cast<PlayerState>(initial_state)->pos.x,
                      std::dynamic_pointer_cast<PlayerState>(initial_state)->pos.y),
            is_walking(std::dynamic_pointer_cast<PlayerState>(initial_state)->is_walking),
            facing_right(std::dynamic_pointer_cast<PlayerState>(initial_state)->facing_right),
            worm_animation(pool.get_texture(Actors::WORM), 15) {}

    void update(const std::shared_ptr<GameState>& actor_state, unsigned int ms) override {
        position = std::dynamic_pointer_cast<PlayerState>(actor_state)->pos;
        is_walking = std::dynamic_pointer_cast<PlayerState>(actor_state)->is_walking;
        facing_right = std::dynamic_pointer_cast<PlayerState>(actor_state)->facing_right;
        worm_animation.update(ms, !is_walking);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        worm_animation.render((*game_renderer), SDL2pp::Rect(position.x, position.y, 32, 60), 0, 0,
                              facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }

    ~Worm() override = default;
};

#endif  // GAMEENTITY_H
