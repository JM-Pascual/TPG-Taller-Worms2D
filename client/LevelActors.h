#ifndef LEVELACTORS_H
#define LEVELACTORS_H

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common/States.h"
#include "../common/const.h"

#include "Animation.h"
#include "TexturesPool.h"
#include "camera.h"

class LevelActor {
protected:
    b2Vec2 position;
    Camera& camera;

public:
    LevelActor(float x, float y, Camera& camera) : position(x, y), camera(camera) {}

    virtual void change_position(float x, float y) {
        position.x = x;
        position.y = y;
    }
    virtual void render(const std::shared_ptr<SDL2pp::Renderer>& game_renderer) = 0;
    virtual void update() = 0;
    virtual ~LevelActor() = default;
};


// ----------------------- SHORT BAR ----------------------

class ShortBar: public LevelActor {
private:
    std::shared_ptr<SDL2pp::Texture>& texture;
    float inclination;

public:
    ShortBar(float x, float y, float inclination_degrees, TexturesPool& pool, Camera& camera) :
            LevelActor(x, y, camera),
            texture(pool.get_level_texture(TerrainActors::BAR)),
            inclination(inclination_degrees) {}

    void render(const std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect render_rect = camera.calcRect(position.x, position.y, 70, 20);
        game_renderer->Copy((*texture), SDL2pp::NullOpt, render_rect, inclination);
    }

    void update() override {}
};

// ----------------------- LONG BAR ----------------------

class LongBar: public LevelActor {
private:
    std::shared_ptr<SDL2pp::Texture>& texture;
    float inclination;

public:
    LongBar(float x, float y, float inclination_degrees, TexturesPool& pool, Camera& camera) :
            LevelActor(x, y, camera),
            texture(pool.get_level_texture(TerrainActors::LONG_BAR)),
            inclination(inclination_degrees) {}

    void render(const std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect render_rect = camera.calcRect(position.x, position.y, 140, 20);
        game_renderer->Copy((*texture), SDL2pp::NullOpt, render_rect, inclination);
    }

    void update() override {}
};

// ----------------------- WATER ----------------------

class Water: public LevelActor {
private:
    Animation waves_animation;

public:
    Water(float x, float y, TexturesPool& pool, Camera& camera) :
            LevelActor(x, y, camera),
            waves_animation(Animation(pool.get_level_texture(TerrainActors::WATER), 11, 3)) {}

    void update() override { waves_animation.update(); }

    void render(const std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        waves_animation.render((*game_renderer), camera.calcRect(0, 600, 1280, 40), 1240, 0);
    }
};

// ----------------------- ATTACK JET ----------------------

class AttackJet: public LevelActor {
private:
    std::shared_ptr<SDL2pp::Texture>& on_air_texture;
    bool currently_flying;
public:
    AttackJet(float x, float y, TexturesPool& pool, Camera& camera) :
            LevelActor(x, y, camera),
            on_air_texture(pool.get_level_texture(TerrainActors::AIR_JET)),
            currently_flying(false){}

    void update() override {
        position.x -= 15;

        if (position.x < -40) {
            currently_flying = false;
        }
    }

    void change_position(float x, float y) override{
        if (currently_flying){
            return;
        }
        position.x = (x-5);
        position.y = (y+10);
        currently_flying = true;
    }

    void render(const std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        if (position.x <= -40) {
            return;
        } else {
            SDL2pp::Rect render_rect = camera.calcRect(position.x, position.y, 140, 140);
            game_renderer->Copy((*on_air_texture), SDL2pp::NullOpt, render_rect);
        }
    }
};

// ----------------------- CRATE INTERFACE ----------------------

class Crate: public GameActor {
protected:
    Animation falling;
    Animation on_floor;

    bool still_falling;
    bool was_opened;

public:
    Crate(std::shared_ptr<CrateState>& initial_state, TexturesPool& pool, Camera& camera):
            GameActor(initial_state->pos.x, initial_state->pos.y, camera),
            falling(pool.get_level_texture(TerrainActors::CRATE_FALLING), 27, 2, true),
            on_floor(pool.get_level_texture(TerrainActors::CRATE), 15, 1, false),
            still_falling(true),
            was_opened(false) {}

    void print_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                     TextPrinter& state_printer) override {}
};

// ----------------------- TRAP CRATE ----------------------

class TrapCrate: public Crate {
private:
    Animation opening;

public:
    TrapCrate(std::shared_ptr<CrateState>& initial_state, TexturesPool& pool, Camera& camera):
            Crate(initial_state, pool, camera),
            opening(pool.get_effect_texture(Effects::NORMAL_EXPLOSION), 8, 3, false) {}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<CrateState>(actor_state);
        position = state->pos;
        still_falling = state->falling;
        was_opened = state->was_opened;
        falling.update(!still_falling);
        on_floor.update(still_falling);
        opening.update(!was_opened);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        if (still_falling) {
            SDL2pp::Rect rect_falling = camera.calcRect(position.x, position.y, 70, 74);
            falling.render((*game_renderer), rect_falling, 0, 0, SDL_FLIP_NONE);
        } else if (was_opened) {
            SDL2pp::Rect rect_floor = camera.calcRect(position.x, position.y, 60, 60);
            opening.render((*game_renderer), rect_floor, 0, 0, SDL_FLIP_NONE);
        } else {
            SDL2pp::Rect rect_floor = camera.calcRect(position.x, position.y, 60, 60);
            on_floor.render((*game_renderer), rect_floor, 0, 0, SDL_FLIP_NONE);
        }
    }
};

class HealCrate: public Crate {
private:
    Animation opening;

public:
    HealCrate(std::shared_ptr<CrateState>& initial_state, TexturesPool& pool, Camera& camera):
            Crate(initial_state, pool, camera),
            opening(pool.get_effect_texture(Effects::CRATE_HEAL), 13, 2, false) {}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<CrateState>(actor_state);
        position = state->pos;
        still_falling = state->falling;
        was_opened = state->was_opened;
        falling.update(!still_falling);
        on_floor.update(still_falling);
        opening.update(!was_opened);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        if (still_falling) {
            SDL2pp::Rect rect_falling = camera.calcRect(position.x, position.y, 70, 74);
            falling.render((*game_renderer), rect_falling, 0, 0, SDL_FLIP_NONE);
        } else if (was_opened) {
            SDL2pp::Rect rect_floor = camera.calcRect(position.x, (position.y - 30), 60, 60);
            opening.render((*game_renderer), rect_floor, 0, 0, SDL_FLIP_NONE);
        } else {
            SDL2pp::Rect rect_floor = camera.calcRect(position.x, position.y, 60, 60);
            on_floor.render((*game_renderer), rect_floor, 0, 0, SDL_FLIP_NONE);
        }
    }
};

class AmmoCrate: public Crate {
private:
    Animation opening;

public:
    AmmoCrate(std::shared_ptr<CrateState>& initial_state, TexturesPool& pool, Camera& camera):
            Crate(initial_state, pool, camera),
            opening(pool.get_effect_texture(Effects::CRATE_AMMO), 21, 2, false) {}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<CrateState>(actor_state);
        position = state->pos;
        still_falling = state->falling;
        was_opened = state->was_opened;
        falling.update(!still_falling);
        on_floor.update(still_falling);
        opening.update(!was_opened);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        if (still_falling) {
            SDL2pp::Rect rect_falling = camera.calcRect(position.x, position.y, 70, 74);
            falling.render((*game_renderer), rect_falling, 0, 0, SDL_FLIP_NONE);
        } else if (was_opened) {
            SDL2pp::Rect rect_floor = camera.calcRect(position.x, (position.y - 30), 60, 60);
            opening.render((*game_renderer), rect_floor, 0, 0, SDL_FLIP_NONE);
        } else {
            SDL2pp::Rect rect_floor = camera.calcRect(position.x, position.y, 60, 60);
            on_floor.render((*game_renderer), rect_floor, 0, 0, SDL_FLIP_NONE);
        }
    }
};

#endif  // LEVELACTORS_H
