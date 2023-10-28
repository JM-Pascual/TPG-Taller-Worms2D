#include "dto.h"

#include "../client/cprotocol.h"

Dto::Dto(const Commands c): c(c) {}

// --------------------------------------- MOVE DTO --------------------------------------

MoveDto::MoveDto(const float& x, const float& y, const bool& is_walking, const bool& facing_right):
        Dto(Commands::MOVE), pos(x, y), is_walking(is_walking), facing_right(facing_right) {}

MoveDto::MoveDto(ClientSide::Protocol& protocol):
        Dto(Commands::MOVE),
        pos(protocol.recvFloat(), protocol.recvFloat()),
        is_walking(protocol.recvBool()),
        facing_right(protocol.recvBool()) {}
