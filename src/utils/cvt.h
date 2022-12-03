#pragma once

#ifndef UTILS_CVT_H
#define UTILS_CVT_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

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
