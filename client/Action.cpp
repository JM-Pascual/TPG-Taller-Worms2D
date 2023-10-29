#include "Action.h"

// ------------------------------- GAME COMMANDS --------------------------

//PLAYER START MOVING
StartMoving::StartMoving(MoveDir direction) :
        Action(Actions::START_MOVING), direction(direction) {}

void StartMoving::send(ClientSide::Protocol& protocol) {
    protocol.send(&c, sizeof(uint8_t));
    protocol.send(&direction, sizeof(direction));
}

// ------------------------------- LOBBY COMMANDS --------------------------

// CREATE GAME
void CreateGame::send(ClientSide::Protocol& protocol) {
    protocol.send(&c, sizeof(uint8_t));
}

// JOIN GAME
void JoinGame::send(ClientSide::Protocol& protocol) {
    protocol.send(&c, sizeof(uint8_t));
}
