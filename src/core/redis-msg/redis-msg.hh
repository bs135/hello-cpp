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
#include <uuid/uuid.h>

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
    json msgReceive;
    json msgRequest;
    json msgResponse;

public:
    RedisMsg();
    ~RedisMsg();
    bool RedisMsg_MessageIsValidated(string message);
    /* API GET json message inside payload */
    string RedisMsg_GetMessageType();
    string RedisMsg_GetCommand();
    time_t RedisMsg_GetTime();
    string RedisMsg_GetMessageID();
    string RedisMsg_GetMessageSource();
    string RedisMsg_GetMessageDest();
    string RedisMsg_GetMessageChecksum();
    json RedisMsg_GetReceivcePayload();
    /* API SET value to create payload */
    json RedisMsg_BuildRequestMessage(string reqCommand, json reqParam);
    json RedisMsg_BuildResponseMessage(string respCommand, json respParam);
};

void RedisMsg_Receivce_Handler(string topic, string message);

#endif