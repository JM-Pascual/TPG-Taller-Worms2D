#ifndef CLIENT_PARSER_H
#define CLIENT_PARSER_H

#include <map>
#include <memory>
#include <vector>

#include "../common/const.h"
#include "../common/queue.h"

class States;

namespace ClientSide {

class Parser {

public:
    static void filterStates(Queue<std::shared_ptr<States>>& game_states,
                             Queue<std::shared_ptr<States>>& lobby_states,
                             std::shared_ptr<States> state);
};
}  // namespace ClientSide

#endif
