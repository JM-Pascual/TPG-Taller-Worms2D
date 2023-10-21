#include "client.h"

Client::Client(const char* hostname, const char* servname):
        recv(&this->protocol), send(&this->protocol), protocol(hostname, servname) {
    recv.start();
    send.start();
}

Client::~Client() {
    protocol.close();
    recv.join();
    send.kill();
    send.join();
}

void Client::run() {
    char command;
    while (std::cin >> command) {
        if (command == 'a') {
            send.queueUp(5);
        } else if (command == 'q') {
            break;
        }
    }
}
