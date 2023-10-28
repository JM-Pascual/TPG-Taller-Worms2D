#ifndef CLIENT_PARSER_H
#define CLIENT_PARSER_H

#include <memory>

#include "../common/const.h"

class Dto;

namespace ClientSide {
class Parser {
public:
    static std::unique_ptr<Dto> makeGStateDto(const Commands& c, ClientSide::Protocol& protocol);
};
}  // namespace ClientSide


#endif
