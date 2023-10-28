#ifndef COMMAND_DTO
#define COMMAND_DTO

#include "../common/const.h"

namespace ClientSide {
class Protocol;
}

class CommandDto {
public:
    const Commands c;

    explicit CommandDto(const Commands c);

    virtual void send(ClientSide::Protocol& protocol) = 0;

    virtual ~CommandDto() = default;
};

// ------------------------------- GAME COMMANDS --------------------------

class MoveDto: public CommandDto {
public:
    const bool is_walking;
    const bool facing_right;

    explicit MoveDto(const bool is_walking, const bool facing_right);

    void send(ClientSide::Protocol& protocol) override;

    ~MoveDto() = default;
};

// ----------------------------------- LOBBY COMMANDS -------------------------

class CreateDto: public CommandDto {
public:
    CreateDto();

    void send(ClientSide::Protocol& protocol) override;

    ~CreateDto() = default;
};

#endif
