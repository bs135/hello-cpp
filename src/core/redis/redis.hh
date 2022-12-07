/**
 * @file redis.hh
 * @author bs
 * @brief
 * @version 0.1
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#ifndef CORE_REDIS_HH
#define CORE_REDIS_HH

#include <iostream>
#include <string>
#include <map>
#include <sw/redis++/redis++.h>
// #include <sw/redis++/async_redis++.h>
#include "log.h"

using namespace sw::redis;
using namespace std;

#define REDIS_HOST_DEFAULT "127.0.0.1" // localhost
#define REDIS_PORT_DEFAULT 6379
#define REDIS_DB_DEFAULT 0
#define REDIS_PASS_DEFAULT ""

using RedisMsgHandler = function<void(string payload)>;

using RedisPMsgHandler = function<void(string pattern,
                                       string topic,
                                       string payload)>;

void Redis_Publish(string topic, string payload);
void Redis_Subscribe(string topic, RedisMsgHandler handler);

bool Redis_Init();
void Redis_StartLoop();
Redis *Redis_Client();
void Redis_Start();

#endif