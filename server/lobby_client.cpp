#include "lobby_client.h"

#include <string>
#include <utility>
#include <vector>

#include <spdlog/spdlog.h>

#include "../common/const.h"
#include "../common/liberror.h"
#include "../common/socket.h"

#include "command.h"
#include "lobby.h"
#include "sparser.h"

LobbyClient::LobbyClient(Socket&& skt, Lobby& lobby, const uint8_t id):
        protocol(std::move(skt)), lobby(lobby), killed(false), id(id) {}

void LobbyClient::run() {
    /*
        Esto es experimental, en la realidad tendria que enviarse un comando para mostrar los juegos
        en proceso. No enviarse todos de una cuando se conecta.
        Osea se toca un boton en qt -> se envia un comando para mostrar todos los juegos activos.
    */
    try {
        std::vector<std::string> info;
        lobby.infoGames(info);

        std::string welcome("Games disponibles: ");
        protocol.send(welcome.data(), welcome.length());

        for (auto s: info) {
            protocol.send(s.data(), s.length());
        }

        Commands c;
        protocol.recvCommand(c);
        ServerSide::Parser parser;

        auto command = parser.makeLobbyCommand(c, protocol, id, lobby);
        command->execute();

    } catch (const LibError& e) {
        if (not killed) {
            spdlog::get("server")->error("Ocurrio un error en el socket del cliente {:u}", id);
        }
    }
}

void LobbyClient::kill() {
    killed = true;
    spdlog::get("server")->debug("Cerrando el socket del cliente {:u}", id);
    protocol.close();
}
