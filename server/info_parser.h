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

    /*
        @param states: todo

        @brief
     */
    void makeLobbyState(std::list<std::shared_ptr<States>>& states);

    /*
        @param states:
        @param id_of_active_player:

        @brief
     */
    void makeGameState(std::list<std::shared_ptr<States>>& states,
                       const uint8_t& id_of_active_player);

    /*
        @param states:
        @param map_name:

        @brief
     */
    void makeLevelState(std::list<std::shared_ptr<States>>& states, const std::string& map_name);
};


#endif
