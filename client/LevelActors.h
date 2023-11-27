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

#endif  // LEVELACTORS_H
