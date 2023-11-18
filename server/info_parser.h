#ifndef INFO_PARSER_H
#define INFO_PARSER_H

#include <list>
#include <map>
#include <memory>
#include <mutex>

#include <stdint.h>

class Player;
class States;
class Projectile;
class GameInfoL;


class InfoParser {
private:
    std::mutex& m_game;
    std::map<uint8_t, std::unique_ptr<Player>>& players;
    std::map<uint8_t, std::shared_ptr<Projectile>>& projectiles;

public:
    InfoParser(std::mutex& m_game, std::map<uint8_t, std::unique_ptr<Player>>& players,
               std::map<uint8_t, std::shared_ptr<Projectile>>& projectiles):
            m_game(m_game), players(players), projectiles(projectiles) {}

    void makeLobbyState(std::list<std::shared_ptr<States>>& states);

    void makeGameState(std::list<std::shared_ptr<States>>& states);
};


#endif
