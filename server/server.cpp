#include "server.h"

Server::Server(char* servname): acceptor(servname) { acceptor.start(); }

void Server::run() {
    char command;
    while (std::cin >> command) {
        if (command == 'q') {
            break;
        }
    }
}

Server::~Server() {
    acceptor.kill();
    acceptor.join();
}
