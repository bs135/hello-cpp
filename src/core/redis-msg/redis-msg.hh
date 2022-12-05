#pragma once

#ifndef CORE_REDIS_MSG_H
#define CORE_REDIS_MSG_H

#include <iostream>
#include "env.h"
#include "log.h"
#include <string>
#include <ctime>
#include <nlohmann/json.hpp>
#include <sw/redis++/redis++.h>
using namespace std;
using namespace sw::redis;

using json = nlohmann::json;

/**
 * @brief
 *
 */
class RedisMsg
{
private:
    string msgtype;
    string cmd;
    json params = json::object();
    time_t time;
    string msgid;
    string source;
    string dest;
    string checksum;

public:
    RedisMsg();
    ~RedisMsg();
    bool RedisMsg_MessageIsValidated(string message);
    void RedisMsg_Parser(string message);
    string RedisMsg_GetMessageType();
    string RedisMsg_GetCommand();
    time_t RedisMsg_GetTime();
    string RedisMsg_GetMessageID();
    string RedisMsg_GetMessageSource();
    string RedisMsg_GetMessageDest();
    string RedisMsg_GetMessageChecksum();

    json RedisMsg_BuildResponseMessage(string message);
};

void RedisMsg_Receivce_Handler(string topic, string message);

#endif