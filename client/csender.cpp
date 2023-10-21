#include "csender.h"

#include "cprotocol.h"

ClientSide::Sender::Sender(Protocol* protocol): Thread(), protocol(protocol) {}

void ClientSide::Sender::run() {
    do {
        try {
            this->send(queue.pop());

        } catch (const ClosedQueue& e) {
            break;
        }
    } while (this->_keep_running);
}

void ClientSide::Sender::send(uint8_t o) { this->protocol->send(&o, 1); }

void ClientSide::Sender::queueUp(uint8_t o) { queue.push(o); }

void ClientSide::Sender::kill() {
    this->_is_alive = false;
    this->closeQueue();
}

void ClientSide::Sender::closeQueue() { queue.close(); }
