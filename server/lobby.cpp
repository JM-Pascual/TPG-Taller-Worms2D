#include "lobby.h"

#include <algorithm>

#include "sclient.h"

void Lobby::notifyAllClients(const uint8_t& dto) {
    for (ServerSide::Client* client: clients) {
        client->sendChat(dto);
    }
}

void Lobby::pushClient(ServerSide::Client* c) {
    std::lock_guard<std::mutex> lock(m);
    clients.push_back(c);
}

bool Lobby::deleteDeaths() {
    std::unique_lock<std::mutex> lock(m_clean);
    can_delete.wait(lock);
    std::lock_guard<std::mutex> l(m);

    size_t prev_size = clients.size();

    auto end = std::remove_if(clients.begin(), clients.end(), [](ServerSide::Client* c) {
        if (!c->isAlive()) {
            delete c;
            return true;
        }
        return false;
    });

    clients.erase(end, clients.end());

    return (prev_size > clients.size());
}

void Lobby::killAll() {
    for (ServerSide::Client* c: clients) {
        c->kill();
    }
}

void Lobby::notifyClean() { can_delete.notify_all(); }

Lobby::~Lobby() {
    std::lock_guard<std::mutex> lock(m);
    for (ServerSide::Client* client: clients) {
        delete client;
    }
}
