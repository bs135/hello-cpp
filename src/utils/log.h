#pragma once

#ifndef UTILS_LOG_H
#define UTILS_LOG_H

#include <iostream>
#include <string>
#include <filesystem>

/***********************************
 * customize spdlog
 ***********************************/

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#define LOG_LEVEL_NAME_TRACE spdlog::string_view_t("TRACE", 5)
#define LOG_LEVEL_NAME_DEBUG spdlog::string_view_t("DEBUG", 5)
#define LOG_LEVEL_NAME_INFO spdlog::string_view_t("INFO", 4)
#define LOG_LEVEL_NAME_WARN spdlog::string_view_t("WARN", 4)
#define LOG_LEVEL_NAME_ERROR spdlog::string_view_t("ERROR", 5)
#define LOG_LEVEL_NAME_FATAL spdlog::string_view_t("FATAL", 5)
#define LOG_LEVEL_NAME_OFF spdlog::string_view_t("OFF", 3)

#define SPDLOG_LEVEL_NAMES        \
    {                             \
        LOG_LEVEL_NAME_TRACE,     \
            LOG_LEVEL_NAME_DEBUG, \
            LOG_LEVEL_NAME_INFO,  \
            LOG_LEVEL_NAME_WARN,  \
            LOG_LEVEL_NAME_ERROR, \
            LOG_LEVEL_NAME_FATAL, \
            LOG_LEVEL_NAME_OFF    \
    }

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

/***********************************
 * wrapper
 ***********************************/

enum
{
    LOG_TRACE, // 0
    LOG_DEBUG, // 1
    LOG_INFO,  // 2
    LOG_WARN,  // 3
    LOG_ERROR, // 4
    LOG_FATAL, // 5 == CRITICAL
    LOG_OFF    // 6
};

#define log_trace SPDLOG_TRACE
#define log_debug SPDLOG_DEBUG
#define log_info SPDLOG_INFO
#define log_warn SPDLOG_WARN
#define log_error SPDLOG_ERROR
#define log_fatal SPDLOG_CRITICAL

/***********************************
 * default
 ***********************************/

#define LOG_MAX_FILE_SIZE 1024 * 1024 * 10
#define LOG_MAX_FILE_COUNT 10
#define LOG_FLUSH_INTERVAL_SECOND 1
#define LOG_FILE_EXT ".log"

inline void log_init(int level, std::string tag, std::string path)
{
    // refs: https://spdlog.docsforge.com/v1.x/3.custom-formatting/#pattern-flags

    std::vector<spdlog::sink_ptr> sinks;

    // File sink
    std::filesystem::path filepath(path);
    std::filesystem::path filename(tag + LOG_FILE_EXT);
    std::filesystem::path logfile = filepath / filename;
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logfile.u8string(), LOG_MAX_FILE_SIZE, LOG_MAX_FILE_COUNT);
    file_sink->set_pattern("%Y-%m-%d %T.%e %-5l [%t] %n %@,%!(): %v");
    file_sink->set_level(spdlog::level::level_enum(level));
    sinks.push_back(file_sink);

    // Console sink
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_pattern("%Y-%m-%d %T.%e %^%-5l%$ [%t] %n %s:%#,%!(): %v");
    console_sink->set_level(spdlog::level::level_enum(level));
    sinks.push_back(console_sink);

    // merge all sinks logger
    auto logger = std::make_shared<spdlog::logger>(tag, begin(sinks), end(sinks));
    logger->set_level(spdlog::level::level_enum(level));
    spdlog::register_logger(logger);
    spdlog::set_default_logger(logger);
    spdlog::flush_every(std::chrono::seconds(LOG_FLUSH_INTERVAL_SECOND));
}

inline void log_final()
{
    // flush all log entries
    spdlog::shutdown();
}

#endif
