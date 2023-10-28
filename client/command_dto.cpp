#include "command_dto.h"

CommandDto::CommandDto(const Commands c): c(c) {}

MoveDto::MoveDto(const bool is_walking, const bool facing_right):
        CommandDto(Commands::MOVE), is_walking(is_walking), facing_right(facing_right) {}

void MoveDto::send(ClientSide::Protocol& protocol) {}

CreateDto::CreateDto(): CommandDto(Commands::CREATE) {}

void CreateDto::send(ClientSide::Protocol& protocol) {}
