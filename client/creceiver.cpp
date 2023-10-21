#include "creceiver.h"

ClientSide::Receiver::Receiver(Protocol* protocol): Thread(), protocol(protocol) {}

void ClientSide::Receiver::run() {}
