#include "Action.h"

#include "cprotocol.h"

// -------------------------- NULL ACTION ------------------------
NullAction::NullAction(): Action(Actions::NULL_) {}

void NullAction::send(ClientSide::Protocol& protocol) {}

// ------------------------------- GAME COMMANDS --------------------------

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ START MOVING ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
StartMoving::StartMoving(MoveDir direction): Action(Actions::START_MOVING), direction(direction) {}

void StartMoving::send(ClientSide::Protocol& protocol) {
    protocol.send(&c, sizeof(uint8_t));
    protocol.send(&direction, sizeof(bool));
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ STOP MOVING ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

StopMoving::StopMoving(): Action(Actions::STOP_MOVING) {}

void StopMoving::send(ClientSide::Protocol& protocol) { protocol.send(&c, sizeof(uint8_t)); }


// ------------------------------- LOBBY COMMANDS --------------------------

// CREATE GAME
void CreateGame::send(ClientSide::Protocol& protocol) { protocol.send(&c, sizeof(uint8_t)); }

// JOIN GAME
void JoinGame::send(ClientSide::Protocol& protocol) { protocol.send(&c, sizeof(uint8_t)); }
