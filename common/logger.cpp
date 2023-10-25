#include "logger.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

Logger::Logger(const std::string& logfile) {
    auto logger = spdlog::basic_logger_mt("client", logfile);
    spdlog::set_default_logger(logger);
    spdlog::flush_on(spdlog::level::info);

    // spdlog::enable_backtrace(10);
}

Logger::~Logger() { spdlog::dump_backtrace(); }
