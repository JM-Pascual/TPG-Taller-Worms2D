#include <iostream>

#include "../common/const.h"
#include "../common/liberror.h"
#include "../common/logger.h"

#include "server.h"

#define SERVNAME argv[1]

#define LOGNAME "server"
#define LOGFILE "logs/server.txt"


int main(int argc, char* argv[]) try {

    if (argc != 2) {
        std::cerr << "Bad program call. Expected " << argv[0] << " <port/servicename>\n";
        return ERROR_;
    }

    Logger l(LOGNAME, LOGFILE);
    Server sv(SERVNAME);
    sv.run();
    return SUCCESS_;

} catch (const LibError& e) {
    std::cerr << e.what();
    return ERROR_;

} catch (const std::exception& e) {
    std::cerr << e.what();
    return ERROR_;

} catch (...) {
    std::cerr << "Error desconocido";
    return ERROR_;
}
