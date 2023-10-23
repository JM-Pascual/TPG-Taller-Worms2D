#include "command.h"

#include "sprotocol.h"

Command::Command(uint8_t id): client_id(id) {}

Move::Move(uint8_t id, ServerSide::Protocol& protocol): Command(id) {
    protocol.recvMoveDir(this->direction);
}

void Move::execute(uint8_t& x) { x += 2 * (uint8_t)direction - 1; }

// Jump::Jump(uint8_t id): Command(id) {}

// Damage::Damage(uint8_t id): Command(id) {}
