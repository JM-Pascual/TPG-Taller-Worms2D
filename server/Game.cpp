#include "Game.h"

#include <spdlog/spdlog.h>


    Game::Game(): gravity(X_GRAVITY,Y_GRAVITY), world(std::make_unique<b2World>(gravity)),player(world){
    create_battlefield();
}

std::shared_ptr<GameState> Game::get_game_state() const {
    return std::make_shared<GameState>(player.worm->GetPosition().x * PPM, player.worm->GetPosition().y * PPM,player.worm->GetLinearVelocity().x != 0,
                                       player.facing_right);
}

void Game::add_client_queue(Queue<std::shared_ptr<GameState>>& client_game_state) {
    std::lock_guard<std::mutex> lock(m);
    broadcast_list.push_back(&client_game_state);
}

void Game::broadcast_game_state() {
    update_physics();
    std::shared_ptr<GameState> gs = get_game_state();

    std::lock_guard<std::mutex> lock(m);
    for (auto& client_game_state_queue: broadcast_list) {
        try {
            client_game_state_queue->push(gs);

        } catch (const ClosedQueue& e) {
            continue;
        }
    }
}

void Game::remove_closed_clients() {
    std::lock_guard<std::mutex> lock(m);
    broadcast_list.erase(
            std::remove_if(broadcast_list.begin(), broadcast_list.end(),
                           [](Queue<std::shared_ptr<GameState>>* q) { return q->is_closed(); }),
            broadcast_list.end());
}

bool Game::is_playing() {
    std::lock_guard<std::mutex> lock(m);
    return (!broadcast_list.empty());
}

void Game::player_start_moving(const MoveDir& direction) {
    player.facing_right = (bool)direction;
    player.is_moving = true;
    // ToDo Incremento temporal de la velocidad, cuando haya físicas hay que pulirlo

    b2Vec2 vel = player.worm->GetLinearVelocity();
    vel.x = 0.2f* (std::pow(-1, 1 - player.facing_right) / TICK_RATE)* 200;
    player.worm->SetLinearVelocity(vel); // Esto tengo que ver si esta bien, se ve cuando lo corra
}

void Game::player_stop_moving() {
    player.is_moving = false;
    b2Vec2 vel = player.worm->GetLinearVelocity();
    vel.x = 0;
    player.worm->SetLinearVelocity(vel);
}

void Game::create_battlefield() {

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f/PPM, -10.0f/PPM);

    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox((100.0f/PPM) /2, (20.0f/PPM) /2);
    groundBody->CreateFixture(&groundBox, 0.0f);

    //------------------------------ VIGA ----------------------------------------
    //En este caso las dimensiones de las vigas ya estan definidas por enunciado --> 3m/6m x 0.8m

    b2BodyDef vigaBodyDef;
    vigaBodyDef.position.Set(640/PPM, 340/PPM);
    b2Body* vigaBody = world->CreateBody(&vigaBodyDef);

    b2PolygonShape vigaBox;
    vigaBox.SetAsBox((1280.0f/PPM)/2, (0.8/PPM)/2);
    vigaBody->CreateFixture(&vigaBox, 0.0f);
}

void Game::step() {
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    world->Step(timeStep, velocityIterations, positionIterations);
}

void Game::update_physics() {
    if(player.is_moving){
        b2Vec2 vel = player.worm->GetLinearVelocity();
        vel.x = 0.2f* (std::pow(-1, 1 - player.facing_right) / TICK_RATE)* 200;
        player.worm->SetLinearVelocity(vel);
    }

}





