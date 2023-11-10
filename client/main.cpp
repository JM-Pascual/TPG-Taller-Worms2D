#include <QApplication>
#include <iostream>

#include <spdlog/spdlog.h>

#include "../common/const.h"
#include "../common/liberror.h"
#include "../common/logger.h"

#include "client.h"
#include "mainwindow.h"

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

    Logger l(LOGNAME, LOGFILE);
    QApplication a(argc, argv);
    MainWindow w(HOSTNAME, SERVNAME);
    w.show();

    QCoreApplication::quit();
    return a.exec();

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
