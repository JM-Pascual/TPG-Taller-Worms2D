#ifndef COMMAND_DTO
#define COMMAND_DTO

#include "../common/const.h"

namespace ClientSide {
class Protocol;
}

class Action {
public:
    const Commands c;

    explicit Action(const Commands c): c(c) {}

    virtual void send(ClientSide::Protocol& protocol) = 0;

    virtual ~Action() = default;
};

// ------------------------------- GAME COMMANDS --------------------------

class StartMoving: public Action {
public:
    const bool is_walking;
    const bool facing_right;

    explicit StartMoving(bool is_walking, bool facing_right):
            Action(Commands::MOVE), is_walking(is_walking), facing_right(facing_right) {}

    void send(ClientSide::Protocol& protocol) override {
        protocol.sendUint8(c);
        protocol.sendBool(is_walking);
        protocol.sendBool(facing_right);
    }

    ~StartMoving() = default;
};

// ----------------------------------- LOBBY COMMANDS -------------------------

class CreateGame: public Action {
public:
    CreateGame() :
            Action(Commands::CREATE) {}

    void send(ClientSide::Protocol& protocol) override;

    ~CreateGame() = default;
};

#endif
