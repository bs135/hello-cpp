/**
 * @file cvt.h
 * @author bs
 * @brief
 * @version 0.1
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#ifndef UTILS_UTILS_H
#define UTILS_UTILS_H

#include <string>
#include <algorithm>
#include <vector>
#include <chrono>
#include <uuid/uuid.h>

/**
 * @brief Generate a random uuid string
 *
 * @return std::string
 */
inline std::string uuid_gen()
{
    uuid_t uid;
    char uid_str[UUID_STR_LEN];
    uuid_generate(uid);
    uuid_unparse(uid, uid_str);
    return uid_str;
}

/**
 * @brief Convert a string to bool
 *
 * @param str
 * @return true
 * @return false
 */
inline bool stob(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    // std::istringstream is(str);
    // bool b;
    // is >> std::boolalpha >> b;
    // return b;

    std::vector<std::string> tab{"true", "t", "yes", "y", "1"};
    return std::find(tab.begin(), tab.end(), str) != tab.end();
}

/**
 * @brief Get epoch timestamp in milliseconds
 *
 * @return uint64_t
 */
inline uint64_t time_epoch_ms()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

/**
 * @brief Get epoch timestamp in seconds
 *
 * @return uint64_t
 */
inline uint64_t time_epoch_s()
{
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

#endif
