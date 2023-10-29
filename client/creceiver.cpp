#include "creceiver.h"

#include "../common/dto.h"

#include "cparser.h"
#include "cprotocol.h"

ClientSide::Receiver::Receiver(ClientSide::Protocol& protocol,
                               Queue<std::unique_ptr<Dto>>& game_state_queue):
        Thread(), protocol(protocol), game_stateQ(game_state_queue) {}

void ClientSide::Receiver::run() {

    Actions c;

    do {
        protocol.recvCommand(c);
        game_stateQ.push(ClientSide::Parser::makeGStateDto(c, protocol));
    } while (_keep_running);
}
