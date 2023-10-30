#include "ssender.h"

#include "sprotocol.h"

ServerSide::Sender::Sender(ServerSide::Protocol& protocol,
                           Queue<std::shared_ptr<GameState>>& game_states):
        protocol(protocol), game_states(game_states) {}

void ServerSide::Sender::run() {
    do {
        try {
            this->protocol.sendGameState(game_states.pop());

        } catch (const ClosedQueue& e) {
            break;
        }
    } while (this->_keep_running);
}


void ServerSide::Sender::kill() {
    this->_is_alive = false;
    this->closeQueue();
}

void ServerSide::Sender::closeQueue() { game_states.close(); }
