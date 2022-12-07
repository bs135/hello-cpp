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

#ifndef UTILS_CVT_H
#define UTILS_CVT_H

#include <string>
#include <algorithm>
#include <vector>

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

#endif
