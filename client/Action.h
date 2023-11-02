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

// ################################ MOVEMENT #################################

class StartMoving: public Action {
private:
    const Direction direction;

public:
    explicit StartMoving(Direction facing_right);

    void send(ClientSide::Protocol& protocol) override;

    ~StartMoving() override = default;
};

class StopMoving: public Action {
public:
    StopMoving();

    void send(ClientSide::Protocol& protocol) override;

    ~StopMoving() override = default;
};

class Jump: public Action {
private:
    const JumpDir direction;

public:
    explicit Jump(JumpDir dir);

    void send(ClientSide::Protocol& protocol) override;

    ~Jump() = default;
};

// #################################### OFFENSIVE ACTIONS #################################

class ADSAngle: public Action {
private:
    const ADSAngleDir direction;

public:
    explicit ADSAngle(ADSAngleDir dir);

    void send(ClientSide::Protocol& protocol) override;

    ~ADSAngle() = default;
};

class StopADSAngle: public Action {
public:
    StopADSAngle();

    void send(ClientSide::Protocol& protocol) override;

    ~StopADSAngle() = default;
};

class ADSDir: public Action {
private:
    const Direction direction;

public:
    explicit ADSDir(Direction dir);

    void send(ClientSide::Protocol& protocol) override;

    ~ADSDir() = default;
};

class FirePower: public Action {
public:
    FirePower();

    void send(ClientSide::Protocol& protocol) override;

    ~FirePower() = default;
};

class Shoot: public Action {
public:
    Shoot();

    void send(ClientSide::Protocol& protocol) override;

    ~Shoot() = default;
};

class Delay: public Action {
private:
    const DelayAmount amount;

public:
    explicit Delay(DelayAmount amount);

    void send(ClientSide::Protocol& protocol) override;

    ~Delay() = default;
};

class ChangeGadget: public Action {
private:
    const WeaponsAndTools gadget;

public:
    explicit ChangeGadget(WeaponsAndTools gadget);

    void send(ClientSide::Protocol& protocol) override;

    ~ChangeGadget() = default;
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
