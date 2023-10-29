#include "cparser.h"

#include "../common/dto.h"

std::unique_ptr<Dto> ClientSide::Parser::makeGStateDto(const Actions& c,
                                                       ClientSide::Protocol& protocol) {
    switch (c) {
        case Actions::START_MOVING:
            return std::make_unique<MoveDto>(protocol);

        default:
            return std::make_unique<NullDto>(protocol);
    }
}
