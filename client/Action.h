#ifndef ACTION_H
#define ACTION_H

#include "../common/const.h"

namespace ClientSide {
class Protocol;
}

// ------------------------------- ACTION INTERFACE --------------------------

class Action {
public:
    const Actions c;

    explicit Action(const Actions c): c(c) {}

    virtual void send(ClientSide::Protocol& protocol) = 0;

    virtual ~Action() = default;
};

class NullAction: public Action {
public:
    NullAction();

    void send(ClientSide::Protocol& protocol) override;

    ~NullAction() = default;
};

// ------------------------------- GAME ACTIONS --------------------------

class StartMoving: public Action {
private:
    const MoveDir direction;

public:
    explicit StartMoving(MoveDir facing_right);

    void send(ClientSide::Protocol& protocol) override;

    ~StartMoving() override = default;
};

class StopMoving: public Action {
public:
    StopMoving();

    void send(ClientSide::Protocol& protocol) override;

    ~StopMoving() override = default;
};

// ----------------------------------- LOBBY ACTIONS -------------------------

class CreateGame: public Action {
public:
    CreateGame(): Action(Actions::CREATE) {}

    void send(ClientSide::Protocol& protocol) override;

    ~CreateGame() override = default;
};

class JoinGame: public Action {
public:
    JoinGame(): Action(Actions::JOIN) {}

    void send(ClientSide::Protocol& protocol) override;

    ~JoinGame() override = default;
};

#endif
