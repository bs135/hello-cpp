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
        /* Check source of command type is a string */
        if (payload["source"].is_string())
        {
            log_debug("source : {}", payload["source"].get<string>());
        }
        else
        {
            log_debug("source is not a string");
            return false;
        }
        /* Check dest of command type is a string */
        if (payload["dest"].is_string())
        {
            log_debug("dest : {}", payload["dest"].get<string>());
        }
        else
        {
            log_debug("dest is not a string");
            return false;
        }
        log_debug("checksum : {}", payload["checksum"].get<string>());
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
 * @param message
 */
void RedisMsg::RedisMsg_Parser(string message)
{
    json payload = json::parse(message);
    msgtype = payload["msgtype"].get<string>();
    cmd = payload["cmd"].get<string>();

    time = payload["time"].get<uint32_t>();
    msgid = payload["msgid"].get<string>();
    source = payload["source"].get<string>();
    dest = payload["dest"].get<string>();
    checksum = payload["checksum"].get<string>();
}

/**
 * @brief
 *
 * @param topic
 * @param message
 * @return uint8_t
 */
json RedisMsg::RedisMsg_BuildResponseMessage(string message)
{
    json payload;
    return payload;
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
    /* Check the message is valid*/
    if (redismsg.RedisMsg_MessageIsValidated(message) == true)
    {
        /* Parse data*/
        redismsg.RedisMsg_Parser(message);
    }
}
