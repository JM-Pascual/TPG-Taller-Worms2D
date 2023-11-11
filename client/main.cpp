#include <spdlog/spdlog.h>

#include "../common/const.h"
#include "../common/liberror.h"

#include "game.h"

#define LOGNAME "client"
#define LOGFILE "logs/client.txt"

int main(int argc, char* argv[]) try {

    if (argc != 3) {
        std::cerr << "Bad program call. Expected " << argv[0]
                  << " <ip/hostname server> <port/servicename>\n";
        return ERROR_;
    }
    Logger l(LOGNAME, LOGFILE);
    Game game(argc, argv);
    return game.run();

} catch (const LibError& e) {
    spdlog::get("client")->error("{:s}", e.what());
    spdlog::dump_backtrace();
    QCoreApplication::quit();
    return ERROR_;

} catch (const std::exception& e) {
    spdlog::get("client")->error("{:s}", e.what());
    spdlog::dump_backtrace();
    QCoreApplication::quit();
    return ERROR_;

} catch (...) {
    spdlog::get("client")->error("Error desconocido");
    spdlog::dump_backtrace();
    QCoreApplication::quit();
    return ERROR_;
}
