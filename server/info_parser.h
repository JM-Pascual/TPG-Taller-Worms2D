#ifndef INFO_PARSER_H
#define INFO_PARSER_H

#include <list>
#include <memory>

class States;
class Game;


class InfoParser {
private:
    Game& game;
    /*
        Lock necesario unicamente para la parte del lobby
    */

public:
    explicit inline InfoParser(Game& game): game(game) {}

    void makeLobbyState(std::list<std::shared_ptr<States>>& states);

    void makeGameState(std::list<std::shared_ptr<States>>& states, uint8_t id_of_active_player);

    void makeLevelState(std::list<std::shared_ptr<States>>& states);
};


#endif
