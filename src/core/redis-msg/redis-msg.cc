#include "redis-msg.hh"

/**
 * @brief Construct a new Redis Bus Msg:: Redis Bus Msg object
 *
 */
RedisMsg::RedisMsg()
{
}

/**
 * @brief Destroy the Redis Bus Msg:: Redis Bus Msg object
 *
 */
RedisMsg::~RedisMsg()
{
}

/**
 * @brief
 *
 * @param message
 * @return true
 * @return false
 */
bool RedisMsg::RedisMsg_MessageIsValidated(string message)
{
    try
    {
        json payload = json::parse(message);
        log_debug("Message Valid");
        /* Todo : Check data inside json message is valid or not */
        /* Check message type is a string */
        if (payload["msgtype"].is_string())
        {
            log_debug("msgtype : {}", payload["msgtype"].get<string>());
        }
        else
        {
            log_debug("msgtype is not string");
            return false;
        }
        /* Check command type is a string */
        if (payload["cmd"].is_string())
        {
            log_debug("cmd : {}", payload["cmd"].get<string>());
        }
        else
        {
            log_debug("cmd is not string");
            return false;
        }
        /* Check parameter type is an object */
        if (payload["params"].is_object())
        {
            string s_temp = payload["params"].dump();
            log_debug("params : {}", s_temp);
            // json j_temp = json::parse(s_temp);
        }
        else
        {
            log_debug("params is not an object");
            return false;
        }
        /* Check time type is an integer value */
        if (payload["time"].is_number_integer())
        {
            log_debug("time : {}", payload["time"].get<uint32_t>());
        }
        else
        {
            log_debug("time value is not an integer");
            return false;
        }
        /* Check messsage id type is a string */
        if (payload["msgid"].is_string())
        {
            log_debug("msgid : {}", payload["msgid"].get<string>());
        }
        else
        {
            log_debug("Message ID is not a string");
            return false;
        }
        // /* Check source of command type is a string */
        // if (payload["source"].is_string())
        // {
        //     log_debug("source : {}", payload["source"].get<string>());
        // }
        // else
        // {
        //     log_debug("source is not a string");
        //     return false;
        // }
        // /* Check dest of command type is a string */
        // if (payload["dest"].is_string())
        // {
        //     log_debug("dest : {}", payload["dest"].get<string>());
        // }
        // else
        // {
        //     log_debug("dest is not a string");
        //     return false;
        // }
        log_debug("checksum : {}", payload["checksum"].get<string>());
        /* All value is valid, copy to msgReceive */
        RedisMsg::msgReceive = payload;
        return true;
    }
    catch (const Error &e)
    {
        log_debug("Message is invalid json format");
        return false;
    }
    return false;
}

/**
 * @brief
 *
 * @param reqCommand
 * @param reqParam
 * @return json
 */
json RedisMsg::RedisMsg_BuildRequestMessage(string reqCommand, json reqParam)
{
    json reqPayload;
    time_t current_epoch_time;
    time_t current_time;
    uuid_t reqMsgID;
    char msgid_temp[UUID_STR_LEN];
    reqPayload["msgtype"] = "request";
    reqPayload["cmd"] = reqCommand;
    reqPayload["params"] = reqParam;
    /* Get current time with epoch format */
    time(&current_time);
    current_epoch_time = mktime(localtime(&current_time));
    reqPayload["time"] = current_epoch_time;
    /* Generate message id with UUID format */
    uuid_generate(reqMsgID);
    uuid_unparse(reqMsgID, msgid_temp);
    reqPayload["msgid"] = msgid_temp;
    /* Todo : Calculate Checksum */
    reqPayload["checksum"] = "dummy_checksum";
    return reqPayload;
}

/**
 * @brief
 *
 * @param respCommand
 * @param respParam
 * @return json
 */
json RedisMsg::RedisMsg_BuildResponseMessage(string respCommand, json respParam)
{
    json respPayload;
    time_t current_epoch_time;
    time_t current_time;
    uuid_t reqMsgID;
    char msgid_temp[UUID_STR_LEN];
    respPayload["msgtype"] = "response";
    respPayload["cmd"] = respCommand;
    log_debug("Response MsgID {}", respPayload["cmd"]);
    respPayload["params"] = respParam;
    log_debug("Response Param {}", respPayload["params"].dump());
    /* Get current time with epoch format */
    time(&current_time);
    current_epoch_time = mktime(localtime(&current_time));
    respPayload["time"] = current_epoch_time;
    respPayload["msgid"] = msgReceive["msgid"];
    log_debug("Response MsgID {}", respPayload["msgid"]);
    /* Todo : Calculate Checksum */
    respPayload["checksum"] = "dummy_checksum";
    return respPayload;
}

string RedisMsg::RedisMsg_GetCommand()
{
    return msgReceive["cmd"];
}
/**
 * @brief
 *
 * @param topic
 * @param message
 */
void RedisMsg_Receivce_Handler(string topic, string message)
{
    log_debug("message_on {}: {}", topic, message);
    /* Create new RedisMessage Object */
    auto redismsg = RedisMsg();
    json respTemp;
    /* Check the message is valid*/
    if (redismsg.RedisMsg_MessageIsValidated(message) == true)
    {
        json _respParam = "{\"status\" : true, \"message\" :\"update success\"}"_json;
        string minifyJsonString = _respParam.dump();
        log_debug("minifyJsonString : {}", minifyJsonString);
        json minifyJson = json::parse(minifyJsonString);
        respTemp = redismsg.RedisMsg_BuildResponseMessage(redismsg.RedisMsg_GetCommand(),
                                                          minifyJson);
        /* Todo : Application use data for itself service */
    }
}
