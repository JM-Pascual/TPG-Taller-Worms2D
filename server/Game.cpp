#include "Game.h"

#include <spdlog/spdlog.h>

    Game::Game():player(battlefield){
}

std::shared_ptr<PlayerState> Game::get_game_state() const {
    return std::make_shared<PlayerState>(player.worm->GetPosition().x, player.worm->GetPosition().y, player.worm->GetLinearVelocity().x != 0,
                                           player.facing_right);
}

//std::shared_ptr<BattlefieldGameState> Game::get_battlefield() const {
    //return std::make_shared<BattlefieldGameState>(battlefield.bar->GetPosition().x,battlefield.bar->GetPosition().x,battlefield.bar->GetTransform().);
//}


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
    vel.x = 0.2f* (std::pow(-1, 1 - player.facing_right) / TICK_RATE)* 400;
    player.worm->SetLinearVelocity(vel); // Esto tengo que ver si esta bien, se ve cuando lo corra
}

void Game::player_stop_moving() {
    player.is_moving = false;
    b2Vec2 vel = player.worm->GetLinearVelocity();
    vel.x = 0;
    player.worm->SetLinearVelocity(vel);
}

void Game::step() {
    battlefield.step();
}

void Game::update_physics() {

    b2Vec2 vel = player.worm->GetLinearVelocity();
    vel.x = player.is_moving * (0.2f* (std::pow(-1, 1 - player.facing_right) / TICK_RATE)* 400); // Agregar comentario
    player.worm->SetLinearVelocity(vel);
}







