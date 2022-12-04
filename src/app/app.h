#pragma once

#ifndef APP_APP_H
#define APP_APP_H

#include <limits.h>
#include "env.h"
#include "log.h"

#define APP_NAME "hello-cpp"

#define APP_ENV_PATH "/etc/hello/env/"

#define APP_LOG_PATH_DEFAULT "/etc/hello/log/"
#define APP_LOG_LEVEL_DEFAULT LOG_DEBUG

#ifdef __cplusplus
extern "C"
{
#endif

    inline void app_env_init()
    {
        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s%s.env", APP_ENV_PATH, APP_NAME);
        // printf("path=%s\n", path);
        env_init(path);
    }

    inline void app_log_init()
    {
        // !IMPORTANT: make sure the env is loaded

        int level = env_get_int("LOG_LEVEL", APP_LOG_LEVEL_DEFAULT);
        if (level < LOG_TRACE || level > LOG_OFF)
            level = APP_LOG_LEVEL_DEFAULT;
        const char *path = env_get("LOG_PATH", APP_LOG_PATH_DEFAULT);
        log_init(level, APP_NAME, path);
    }

#ifdef __cplusplus
}
#endif

#endif
