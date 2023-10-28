#include "cparser.h"

#include "../common/dto.h"

std::unique_ptr<Dto> ClientSide::Parser::makeGStateDto(const Commands& c,
                                                       ClientSide::Protocol& protocol) {
    switch (c) {
        case Commands::MOVE:
            return std::make_unique<MoveDto>(protocol);

        default:
            return std::make_unique<NullDto>(protocol);
    }
}
