/**
 * @file app.hh
 * @author bs
 * @brief
 * @version 0.1
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#ifndef APP_APP_H
#define APP_APP_H

#include <climits>
#include <string>
#include "env.h"
#include "log.h"
#include "app_test.hh"

#define APP_NAME "hello-cpp"

#define APP_ENV_PATH "/etc/hello/env/"

#define APP_LOG_PATH_DEFAULT "/etc/hello/log/"
#define APP_LOG_LEVEL_DEFAULT LOG_DEBUG

inline void app_env_init()
{
    std::filesystem::path dir(APP_ENV_PATH);
    std::filesystem::path file(std::string(APP_NAME) + ".env");
    std::filesystem::path path = dir / file;
    // std::cout << "app env path: " << path << std::endl;
    env_init(path.string().c_str());
}

inline void app_log_init()
{
    // !IMPORTANT: make sure the env is loaded before getting

    int level = env_get_int("LOG_LEVEL", APP_LOG_LEVEL_DEFAULT);
    if (level < LOG_TRACE || level > LOG_OFF)
        level = APP_LOG_LEVEL_DEFAULT;
    std::string path = env_get("LOG_PATH", APP_LOG_PATH_DEFAULT);
    if (!std::filesystem::is_directory(path) || !std::filesystem::exists(path))
    {
        try
        {
            std::filesystem::create_directory(path);
        }
        catch (...)
        {
            path = "";
        }
    }
    // std::cout << "app log path: " << path << std::endl;
    log_init(level, APP_NAME, path);
}

inline void app_redis_init()
{
    auto ok = Redis_Init();
    if (ok)
    {
        Redis_Subscribe("test/redisbus1", test_handler1);
        Redis_Subscribe("test/redisbus2", test_handler2);
        Redis_Subscribe("*/data", test_wildcard_handler);
        Redis_Start();

        Redis_Client()
            ->command("set", "abc", 321);

        while (true)
        {
            log_info("Hello {}! {}", "world", 234);
            Redis_Publish("test/redisbus3", "123");
            std::this_thread::sleep_for(3s);
        }
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

#endif
