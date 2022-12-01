#pragma once

#ifndef CORE_REDIS_MSG_H
#define CORE_REDIS_MSG_H

#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

/**
 * @brief
 *
 */
class RedisBusMsg
{
private:
    json payload;

public:
    RedisBusMsg();
    ~RedisBusMsg();
}

#endif