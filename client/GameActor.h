#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common/GameState.h"
#include "../common/const.h"
#include "box2d/b2_math.h"

#include "Animation.h"
#include "TexturesPool.h"

// ----------------------- ACTOR INTERFACE ----------------------

class GameActor {
protected:
    b2Vec2 position;
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
    bool is_jumping;
    bool is_backflipping;
    bool facing_right;
    Animation walking;
    Animation jumping;
    Animation backflipping;
public:
    Worm(const std::shared_ptr<GameState>& initial_state, TexturesPool& pool):
            GameActor(std::dynamic_pointer_cast<PlayerState>(initial_state)->pos.x,
                      std::dynamic_pointer_cast<PlayerState>(initial_state)->pos.y),
            is_walking(std::dynamic_pointer_cast<PlayerState>(initial_state)->is_walking),
            is_jumping(std::dynamic_pointer_cast<PlayerState>(initial_state)->is_jumping),
            is_backflipping(std::dynamic_pointer_cast<PlayerState>(initial_state)->is_backflipping),
            facing_right(std::dynamic_pointer_cast<PlayerState>(initial_state)->facing_right),
            walking(pool.get_texture(Actors::WORM), 15),
            jumping(pool.get_texture(Actors::JUMPING_WORM), 10, 80),
            backflipping(pool.get_texture(Actors::BACKFLIP_WORM), 22, 60){}

    void update(const std::shared_ptr<GameState>& actor_state, unsigned int ms) override {
        position = std::dynamic_pointer_cast<PlayerState>(actor_state)->pos;
        is_walking = std::dynamic_pointer_cast<PlayerState>(actor_state)->is_walking;
        is_jumping = std::dynamic_pointer_cast<PlayerState>(actor_state)->is_jumping;
        is_backflipping = std::dynamic_pointer_cast<PlayerState>(actor_state)->is_backflipping;
        facing_right = std::dynamic_pointer_cast<PlayerState>(actor_state)->facing_right;
        walking.update(ms, !is_walking);
        jumping.update(ms);
        backflipping.update(ms);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        if (is_jumping) {
            jumping.render((*game_renderer), SDL2pp::Rect(position.x, position.y, 32, 60), 0, 0,
                           facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        } else if (is_backflipping){
            backflipping.render((*game_renderer), SDL2pp::Rect(position.x, position.y, 32, 60), 0, 0,
                           facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        } else {
            walking.render((*game_renderer), SDL2pp::Rect(position.x, position.y, 32, 60), 0, 0,
                           facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        }
    }

    ~Worm() override = default;
};

#endif  // GAMEENTITY_H
