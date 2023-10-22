#include "creceiver.h"

#include "cprotocol.h"

ClientSide::Receiver::Receiver(ClientSide::Protocol& protocol, Queue<uint8_t>& game_state_queue):
        Thread(), protocol(protocol), queue(game_state_queue) {}

void ClientSide::Receiver::run() {

    do {
        uint8_t x;
        protocol.recv(&x, 1);
        queue.push(x);
    } while (_keep_running);
}
