#ifndef CLIENT_LOGGER_H
#define CLIENT_LOGGER_H

#include <string>

class Logger {
private:
public:
    /*
        Configura al logger global de nombre log_name a dumpear los logs en logfile
    */
    explicit Logger(const std::string& log_name, const std::string& logfile);

    ~Logger();
};

#endif
