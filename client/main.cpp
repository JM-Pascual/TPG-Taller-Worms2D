#include <iostream>

#include "../common/const.h"
#include "../common/liberror.h"

#include "client.h"

#define HOSTNAME argv[1]
#define SERVNAME argv[2]


int main(int argc, char* argv[]) try {

    if (argc != 3) {
        std::cerr << "Bad program call. Expected " << argv[0]
                  << " <ip/hostname server> <port/servicename>\n";
        return ERROR;
    }

    Client client(HOSTNAME, SERVNAME);
    client.run();
    return SUCCESS;

} catch (const LibError& e) {
    std::cerr << e.what();
    return ERROR;

} catch (const std::exception& e) {
    std::cerr << e.what();
    return ERROR;

} catch (...) {
    std::cerr << "Error desconocido";
    return ERROR;
}
