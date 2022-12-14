/**
 * @file env.h
 * @author bs
 * @brief
 * @version 0.1
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#ifndef UTILS_ENV_H
#define UTILS_ENV_H

#include <stdlib.h>
#include "dotenv/dotenv.h"
#include "utils.h"

#ifdef __cplusplus
extern "C"
{
#endif

    inline void env_init(const char *path)
    {
        env_load(path, false);
    }

    inline const char *env_get(const char *name, const char *def)
    {
        char *val = getenv(name);
        if (val == NULL || val[0] == '\0')
            return def;
        return val;
    }

    inline int env_get_int(const char *name, int def)
    {
        char *val = getenv(name);
        if (val == NULL || val[0] == '\0')
            return def;
        return atoi(val);
    }

    inline bool env_get_bool(const char *name)
    {
        char *val = getenv(name);
        if (val == NULL || val[0] == '\0')
            return false;

        return stob(val);
    }

#ifdef __cplusplus
}
#endif

#endif
