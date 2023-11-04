#include "Action.h"

#include "cprotocol.h"

// -------------------------- NULL ACTION ------------------------
NullAction::NullAction(): Action(Actions::NULL_) {}

void NullAction::send(ClientSide::Protocol& protocol) {}

// ------------------------------- GAME COMMANDS --------------------------

// ################################ MOVEMENT ###############################

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~ START MOVING ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
StartMoving::StartMoving(Direction direction):
        Action(Actions::START_MOVING), direction(direction) {}

void StartMoving::send(ClientSide::Protocol& protocol) {
    protocol.send(&c, sizeof(uint8_t));
    protocol.send(&direction, sizeof(bool));
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ STOP MOVING ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

StopMoving::StopMoving(): Action(Actions::STOP_MOVING) {}

void StopMoving::send(ClientSide::Protocol& protocol) { protocol.send(&c, sizeof(uint8_t)); }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JUMP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Jump::Jump(JumpDir dir): Action(Actions::JUMP), direction(dir) {}

void Jump::send(ClientSide::Protocol& protocol) {
    protocol.send(&c, sizeof(uint8_t));
    protocol.send(&direction, sizeof(bool));
}

// ################################# OFFENSIVE ACTIONS ###############################pragma
// endregion

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ADSAngle ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ADSAngle::ADSAngle(ADSAngleDir dir): Action(Actions::ADS_ANGLE), direction(dir) {}

void ADSAngle::send(ClientSide::Protocol& protocol) {
    protocol.send(&c, sizeof(uint8_t));
    protocol.send(&direction, sizeof(bool));
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ STOP ADS ~~~~~~~~~~~~~~~~~~~~~~~~~~

StopADSAngle::StopADSAngle(): Action(Actions::STOP_ADS_ANGLE) {}

void StopADSAngle::send(ClientSide::Protocol& protocol) { protocol.send(&c, sizeof(uint8_t)); }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FirePower ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

FirePower::FirePower(): Action(Actions::FIRE_POWER) {}

void FirePower::send(ClientSide::Protocol& protocol) { protocol.send(&c, sizeof(uint8_t)); }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Shoot ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Shoot::Shoot(): Action(Actions::SHOOT) {}

void Shoot::send(ClientSide::Protocol& protocol) { protocol.send(&c, sizeof(uint8_t)); }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Delay ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Delay::Delay(DelayAmount amount): Action(Actions::DELAY), amount(amount) {}

void Delay::send(ClientSide::Protocol& protocol) {
    protocol.send(&c, sizeof(uint8_t));
    protocol.send(&amount, sizeof(uint8_t));
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ChangeGadget ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ChangeGadget::ChangeGadget(WeaponsAndTools gadget):
        Action(Actions::CHANGE_WEAPON_OR_TOOL), gadget(gadget) {}

void ChangeGadget::send(ClientSide::Protocol& protocol) {
    protocol.send(&c, sizeof(uint8_t));
    protocol.send(&gadget, sizeof(uint8_t));
}

// ------------------------------- LOBBY COMMANDS --------------------------

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CREATE GAME ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CreateGame::send(ClientSide::Protocol& protocol) { protocol.send(&c, sizeof(uint8_t)); }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ JOIN GAME ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void JoinGame::send(ClientSide::Protocol& protocol) {
    protocol.send(&c, sizeof(uint8_t));
    protocol.send(&game_id, sizeof(uint8_t));
}

void Ready::send(ClientSide::Protocol& protocol) { protocol.send(&c, sizeof(uint8_t)); }
