#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common/WormGameState.h"
#include "../common/const.h"
#include "box2d/b2_math.h"

#include "Animation.h"
#include "TexturesPool.h"

// ----------------------- ACTOR INTERFACE ----------------------

class GameActor {
protected:
    b2Vec2 position;
public:
    GameActor(const float& x, const float& y) : position(x, y) {}
    virtual void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) = 0;
    virtual void update(const std::shared_ptr<WormGameState>& actor_state, unsigned int ms) = 0;
    virtual ~GameActor() = default;
};

// ----------------------- WORM ----------------------

class Worm: public GameActor {
private:
    bool is_walking;
    bool facing_right;
    Animation worm_animation;
public:
    Worm(const std::shared_ptr<WormGameState>& initial_state, float ms, TexturesPool& pool) :
            GameActor(initial_state->player_position.x, initial_state->player_position.y),
            is_walking(initial_state->is_walking), facing_right(initial_state->facing_right),
            worm_animation(pool.get_texture(Actors::WORM), 15) {}

    void update(const std::shared_ptr<WormGameState>& actor_state, unsigned int ms) override {
        position = actor_state->player_position;
        is_walking = actor_state->is_walking;
        facing_right = actor_state->facing_right;
        worm_animation.update(ms, !is_walking);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        worm_animation.render((*game_renderer),
                              SDL2pp::Rect(position.x, position.y, 32, 60), 0, 0,
                              facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }

    ~Worm() override = default;
};

#endif  // GAMEENTITY_H
