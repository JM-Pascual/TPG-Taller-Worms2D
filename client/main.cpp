#include <iostream>

#include <spdlog/spdlog.h>

#include "../common/const.h"
#include "../common/liberror.h"
#include "../common/logger.h"

#include "client.h"

#define HOSTNAME argv[1]
#define SERVNAME argv[2]

#define LOGNAME "client"
#define LOGFILE "logs/client.txt"

int main(int argc, char* argv[]) try {

    if (argc != 3) {
        std::cerr << "Bad program call. Expected " << argv[0]
                  << " <ip/hostname server> <port/servicename>\n";
        return ERROR_;
    }
    // Cuando haya multiples clientes se podria cambiar la inicializacion del log a cuando se le
    // pasa la id al cliente para que no se interfieran multiples logs en un archivo
    Logger l(LOGNAME, LOGFILE);
    Client client(HOSTNAME, SERVNAME);
    client.run();
    return SUCCESS_;

} catch (const LibError& e) {
    spdlog::get("client")->error("{:s}", e.what());
    spdlog::dump_backtrace();
    return ERROR_;

} catch (const std::exception& e) {
    spdlog::get("client")->error("{:s}", e.what());
    spdlog::dump_backtrace();
    return ERROR_;

} catch (...) {
    spdlog::get("client")->error("Error desconocido");
    spdlog::dump_backtrace();
    return ERROR_;
}
