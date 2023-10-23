#include "ssender.h"

#include "sprotocol.h"

ServerSide::Sender::Sender(ServerSide::Protocol& protocol, std::unique_ptr<Game>& game):
        protocol(protocol), game(game) {}

void ServerSide::Sender::run() {
    do {
        try {
            this->send(queue.pop());

        } catch (const ClosedQueue& e) {
            break;
        }
    } while (this->_keep_running);
}

void ServerSide::Sender::send(uint8_t o) { this->protocol.send(&o, 1); }

void ServerSide::Sender::queueUp(uint8_t o) { queue.push(o); }

void ServerSide::Sender::kill() {
    this->_is_alive = false;
    this->closeQueue();
}

void ServerSide::Sender::closeQueue() { queue.close(); }
