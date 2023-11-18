#include "player_action.h"

#include "Game.h"
#include "game_browser.h"
#include "sprotocol.h"
#include "turn_handler.h"

// ----------------------- COMMAND ----------------------

// ----------------------- NULL_COMMAND ----------------------

void NullCommand::execute(Game& game, const uint8_t& turn_id, TurnHandler& turn_handler) {}

void NullCommand::execute() {}

// ----------------------- START MOVING ----------------------

StartMoving::StartMoving(ServerSide::Protocol& protocol, const uint8_t& id): PlayerAction(id) {
    protocol.recvDirection(this->direction);
}

void StartMoving::execute(Game& game, const uint8_t& turn_id, TurnHandler& turn_handler) {
    if (turn_id != this->id) {
        return;
    }

    game.player_start_moving(direction, id);
}

// ----------------------- STOP MOVING ----------------------

StopMoving::StopMoving(const uint8_t& id): PlayerAction(id) {}

void StopMoving::execute(Game& game, const uint8_t& turn_id, TurnHandler& turn_handler) {
    if (turn_id != this->id) {
        return;
    }

    game.player_stop_moving(id);
}


// ----------------------- JUMP ----------------------

Jump::Jump(ServerSide::Protocol& protocol, const uint8_t& id): PlayerAction(id) {
    protocol.recvJumpDir(this->direction);
}

void Jump::execute(Game& game, const uint8_t& turn_id, TurnHandler& turn_handler) {
    if (turn_id != this->id) {
        return;
    }

    game.player_jump(direction, id);
}

// ---------------------------- ADSAngle ------------------

ADSAngle::ADSAngle(ServerSide::Protocol& protocol, const uint8_t& id): PlayerAction(id) {
    protocol.recvADSAngleDir(this->direction);
}

void ADSAngle::execute(Game& game, const uint8_t& turn_id, TurnHandler& turn_handler) {
    if (turn_id != this->id) {
        return;
    }

    if (turn_handler.player_used_stop_action()) {
        return;
    }

    game.player_start_aiming(direction, id);
}

// -------------------------- STOP ADS ---------------

StopADSAngle::StopADSAngle(const uint8_t& id): PlayerAction(id) {}

void StopADSAngle::execute(Game& game, const uint8_t& turn_id, TurnHandler& turn_handler) {
    if (turn_id != this->id) {
        return;
    }

    if (turn_handler.player_used_stop_action()) {
        return;
    }

    game.player_stop_aiming(id);
}

// ---------------------------- FIRE POWER ------------------

FirePower::FirePower(const uint8_t& id): PlayerAction(id) {}

void FirePower::execute(Game& game, const uint8_t& turn_id, TurnHandler& turn_handler) {
    if (turn_id != this->id) {
        return;
    }

    if (turn_handler.player_used_stop_action()) {
        return;
    }

    game.player_start_charging(id);
}

// ---------------------------- SHOOT ------------------

Shoot::Shoot(const uint8_t& id): PlayerAction(id) {}

void Shoot::execute(Game& game, const uint8_t& turn_id, TurnHandler& turn_handler) {
    if (turn_id != this->id) {
        return;
    }

    if (turn_handler.player_used_stop_action()) {
        return;
    }

    game.player_shoot(id);

    turn_handler.use_stop_action();
}

// ---------------------------- DELAY ------------------

Delay::Delay(ServerSide::Protocol& protocol, const uint8_t& id): PlayerAction(id) {
    protocol.recvDelay(this->amount);
}

void Delay::execute(Game& game, const uint8_t& turn_id, TurnHandler& turn_handler) {
    if (turn_id != this->id) {
        return;
    }

    if (turn_handler.player_used_stop_action()) {
        return;
    }
}

// ---------------------------- CHANGE GADGET ------------------

ChangeGadget::ChangeGadget(ServerSide::Protocol& protocol, const uint8_t& id): PlayerAction(id) {
    protocol.recvGadget(this->gadget);
}

void ChangeGadget::execute(Game& game, const uint8_t& turn_id, TurnHandler& turn_handler) {
    if (turn_id != this->id) {
        return;
    }

    if (turn_handler.player_used_stop_action()) {
        return;
    }

    game.player_change_gadget(gadget, id);
}

// ----------------------- JOIN ----------------------

Join::Join(GameBrowser& gb, uint8_t& id_to_join, const uint8_t& id,
           Queue<std::shared_ptr<States>>& state_queue):
        gb(gb), game_id(id_to_join), id(id), state_queue(state_queue) {}

void Join::execute() { gb.join_game(game_id, id, state_queue); }

// ----------------------- CREATE ----------------------

Create::Create(GameBrowser& gb, uint8_t& id_to_create, const uint8_t& id,
               Queue<std::shared_ptr<States>>& state_queue, ServerSide::Protocol& protocol):
        Join(gb, id_to_create, id, state_queue) {
    protocol.recvString64(desc);
    protocol.recvString64(map);
    gb.create_game(desc, map, id_to_create);
}

// -------------------- SHOW GAMES -----------------

void ShowGames::execute() {
    gb.infoGames(info);
    state_queue.push(std::make_shared<GamesCountL>(info.size()));

    for (const auto& i: info) {
        state_queue.push(i);
    }
}

// -------------------- EXIT GAME ----------------------

void ExitGame::execute() { gb.removePlayer(player_id, game_id); }

// ----------------------- READY --------------------

void Ready::execute() { gb.set_player_ready(id, id_game); }
