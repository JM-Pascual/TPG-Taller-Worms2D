#include "lobby_client.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../common/const.h"
#include "../common/socket.h"

#include "game_browser.h"

LobbyClient::LobbyClient(Socket&& skt, GameBrowser& lobby, const uint8_t id):
        protocol(std::move(skt)), lobby(lobby), id(id) {}

void LobbyClient::run() {
    /*
        Esto es experimental, en la realidad tendria que enviarse un comando para mostrar los juegos
        en proceso. No enviarse todos de una cuando se conecta
    */
    std::vector<std::string> info;
    lobby.infoGames(info);

    std::string welcome("Games disponibles: ");
    protocol.send(welcome.data(), welcome.length());

    for (auto s: info) {
        protocol.send(&s, s.length());
    }

    Commands c;
    protocol.recvCommand(c);
    /*
        Faltaria un recv del comando (join/create) y decirle al lobby que lo asigne a esa sala
    */
}
