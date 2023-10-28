#include "ssender.h"

#include "sprotocol.h"

ServerSide::Sender::Sender(ServerSide::Protocol& protocol, Queue<uint8_t>& game_states):
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

void ServerSide::Sender::send(uint8_t o) { this->protocol.send(&o, 1); }

void ServerSide::Sender::kill() {
    this->_is_alive = false;
    this->closeQueue();
}

void ServerSide::Sender::closeQueue() { game_states.close(); }
