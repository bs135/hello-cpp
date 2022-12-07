#pragma once

#ifndef UTILS_UID_H
#define UTILS_UID_H

#include <string>
#include "libuuidpp/libuuidpp.hpp"

inline std::string uid_gen()
{
    auto random_uid = libuuidpp::uuid::random();
    auto uidString = random_uid.string(libuuidpp::uuid::formatting::lowercase);
    return uidString;
}

#endif
