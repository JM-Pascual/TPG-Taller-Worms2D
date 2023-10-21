#include <iostream>

#include "../common/const.h"
#include "../common/liberror.h"

#include "server.h"

#define SERVNAME argv[1]


int main(int argc, char* argv[]) try {

    if (argc != 2) {
        std::cerr << "Bad program call. Expected " << argv[0] << " <port/servicename>\n";
        return ERROR;
    }

    Server sv(SERVNAME);
    sv.run();
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
