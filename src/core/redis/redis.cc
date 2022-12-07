/**
 * @file redis.cc
 * @author bs
 * @brief
 * @version 0.1
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "env.h"
#include "log.h"
#include "redis.hh"

Redis *redis_client;
map<string, RedisMsgHandler> handlers;

void _message_handler(string topic, string payload)
{
    log_debug("on_message [{}]: {}", topic, payload);
    if (handlers.count(topic) > 0)
    {
        thread t(handlers[topic], payload);
        t.detach();
    }
}

void Redis_Publish(string topic, string payload)
{
    auto r = redis_client->publish(topic, payload);
}

void Redis_Subscribe(string topic, RedisMsgHandler handler)
{
    handlers[topic] = handler;
}

bool Redis_Init()
{
    // !IMPORTANT: make sure the env is loaded before getting

    ConnectionOptions _opts;
    _opts.host = env_get("REDIS_HOST", REDIS_HOST_DEFAULT);
    _opts.port = env_get_int("REDIS_PORT", REDIS_PORT_DEFAULT);
    _opts.db = env_get_int("REDIS_DB", REDIS_DB_DEFAULT);
    _opts.password = env_get("REDIS_PASS", REDIS_PASS_DEFAULT);

    try
    {
        redis_client = new Redis(_opts);
        if (redis_client == nullptr)
        {
            log_fatal("Redis instance [{}:{}] created failed.", _opts.host, _opts.port);
            return false;
        }

        auto ping = redis_client->ping();
        log_info("Redis ping successful. Response: {}", ping);
        return true;
    }
    catch (const Error &e)
    {
        log_error("Cannot connect to Redis server [{}:{}]: {}", _opts.host, _opts.port, e.what());
        return false;
    }
}

void Redis_StartLoop()
{
    auto _subscriber = redis_client->subscriber();
    _subscriber.on_message(_message_handler);

    for (const auto &[topic, handler] : handlers)
    {
        _subscriber.subscribe(topic);
        log_info("Subscribe OK: {}", topic);
    }

    while (true)
    {
        try
        {
            _subscriber.consume();
        }
        catch (const Error &err)
        {
            log_error("Redis consume error: {}", err.what());
        }
    }
}

void Redis_Start()
{
    thread redis_worker([]()
                        { Redis_StartLoop(); });
    redis_worker.detach();
}

Redis *Redis_Client()
{
    return redis_client;
}
