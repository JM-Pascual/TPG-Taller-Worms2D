#include "ssender.h"

#include "sprotocol.h"

ServerSide::Sender::Sender(ServerSide::Protocol& protocol,
                           Queue<std::shared_ptr<GameState>>& game_states):
        protocol(protocol), game_states(game_states) {}

void ServerSide::Sender::run() {
    do {
        try {
            this->send(game_states.pop());

        } catch (const ClosedQueue& e) {
            break;
        }
    } while (this->_keep_running);
}

void ServerSide::Sender::send(std::shared_ptr<GameState> state) {
    this->protocol.send_game_state(state);
    // ToDo Este método tiene que hacer 3 sends, uno para cada atributo del dto
    // Se podría hacer un método send game state que justamente reciba el dto y lo serialice
}

void ServerSide::Sender::kill() {
    this->_is_alive = false;
    this->closeQueue();
}

void ServerSide::Sender::closeQueue() { game_states.close(); }
