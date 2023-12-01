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
    explicit LevelActor(float x, float y, Camera& camera): position(x, y), camera(camera) {}

    virtual inline void change_position(float x, float y) {
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
    explicit ShortBar(float x, float y, float inclination_degrees, TexturesPool& pool,
                      Camera& camera):
            LevelActor(x, y, camera),
            texture(pool.get_level_texture(TerrainActors::BAR)),
            inclination(inclination_degrees) {}

    inline void render(const std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect render_rect = camera.calcRect(position.x, position.y, 70, 20);
        game_renderer->Copy((*texture), SDL2pp::NullOpt, render_rect, inclination);
    }

    inline void update() override {}
};

// ----------------------- LONG BAR ----------------------

class LongBar: public LevelActor {
private:
    std::shared_ptr<SDL2pp::Texture>& texture;
    float inclination;

public:
    explicit LongBar(float x, float y, float inclination_degrees, TexturesPool& pool,
                     Camera& camera):
            LevelActor(x, y, camera),
            texture(pool.get_level_texture(TerrainActors::LONG_BAR)),
            inclination(inclination_degrees) {}

    inline void render(const std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect render_rect = camera.calcRect(position.x, position.y, 140, 20);
        game_renderer->Copy((*texture), SDL2pp::NullOpt, render_rect, inclination);
    }

    inline void update() override {}
};

// ----------------------- WATER ----------------------

class Water: public LevelActor {
private:
    Animation waves_animation;

public:
    explicit Water(float x, float y, TexturesPool& pool, Camera& camera):
            LevelActor(x, y, camera),
            waves_animation(Animation(pool.get_level_texture(TerrainActors::WATER), 11, 3)) {}

    inline void update() override { waves_animation.update(); }

    inline void render(const std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        waves_animation.render((*game_renderer), camera.calcRect(0, 600, 1280, 40), 1240, 0);
    }
};

// ----------------------- ATTACK JET ----------------------

class AttackJet: public LevelActor {
private:
    std::shared_ptr<SDL2pp::Texture>& on_air_texture;
    bool currently_flying;

public:
    explicit AttackJet(float x, float y, TexturesPool& pool, Camera& camera):
            LevelActor(x, y, camera),
            on_air_texture(pool.get_level_texture(TerrainActors::AIR_JET)),
            currently_flying(false) {}

    inline void update() override {
        position.x -= 15;

        if (position.x < -40) {
            currently_flying = false;
        }
    }

    inline void change_position(float x, float y) override {
        if (currently_flying) {
            return;
        }
        position.x = (x - 5);
        position.y = (y + 10);
        currently_flying = true;
    }

    inline void render(const std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        if (position.x <= -40) {
            return;
        } else {
            SDL2pp::Rect render_rect = camera.calcRect(position.x, position.y, 140, 140);
            game_renderer->Copy((*on_air_texture), SDL2pp::NullOpt, render_rect);
        }
    }
};

// ----------------------- WIND ----------------------

class Wind: public LevelActor {
private:
    std::shared_ptr<SDL2pp::Texture>& left_wind;
    std::shared_ptr<SDL2pp::Texture>& right_wind;
    float current_strenght;
public:
    explicit Wind(float x, float y, TexturesPool& pool, Camera& camera):
            LevelActor(x, y, camera),
            left_wind(pool.get_actor_texture(Actors::WIND_LEFT)),
            right_wind(pool.get_actor_texture(Actors::WIND_RIGHT)),
            current_strenght(0) {}

    inline void update() override {
        //The Wind animation is static due to not finding the complete texture
    }

    inline void update_strenght(float new_wind_strenght) {
        current_strenght = new_wind_strenght;
    }

    inline void render(const std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        if (current_strenght < 0.0f){
            game_renderer->Copy((*left_wind),
                                SDL_Rect{0, 0, (int)(96 * abs((current_strenght/4))), 13},
                                SDL_Rect{int(position.x), int(position.y),
                                         (int)(96 * abs((current_strenght/4))), 20});
        } else {
            game_renderer->Copy((*right_wind),
                                SDL_Rect{0, 0, (int)(96 * (current_strenght/4)), 13},
                                SDL_Rect{int(position.x), int(position.y),
                                         (int)(96 * (current_strenght/4)), 20});
        }
    }
};

#endif  // LEVELACTORS_H
