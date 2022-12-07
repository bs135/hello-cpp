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

#include <string>
#include <mutex>
#include "env.h"
#include "log.h"
#include "redis.hh"

static mutex msgMux;
Redis *redis_client;
map<string, RedisMsgHandler> handlers;

/**
 * @brief Internal method to handle Redis messages
 *
 * @param topic
 * @param payload
 */
void _message_handler(string topic, string payload)
{
    msgMux.lock();
    try
    {
        if (handlers.count(topic) > 0)
        {
            thread t(handlers[topic], topic, payload);
            t.detach();
        }
        {
            log_debug("No handler for [{}]: {}", topic, payload);
        }
    }
    catch (const exception &e)
    {
        log_error("Message header error: {}", e.what());
    }
    msgMux.unlock();
}

void _pattern_message_handler(string pattern, string topic, string payload)
{
    msgMux.lock();
    try
    {
        if (handlers.count(pattern) > 0)
        {
            thread t(handlers[pattern], topic, payload);
            t.detach();
        }
        else
        {
            log_warn("No handler for [{}][{}]: {}", pattern, topic, payload);
        }
    }
    catch (const exception &e)
    {
        log_error("PMessage header error: {}", e.what());
    }
    msgMux.unlock();
}

/**
 * @brief Publish a message to Redis topic
 *
 * @param topic
 * @param payload
 */
void Redis_Publish(string topic, string payload)
{
    auto r = redis_client->publish(topic, payload);
}

/**
 * @brief Subscribe to a Redis topic. Actually, this method will add the topic to list first and subscribe in StartLoop() later.
 *
 * @param topic
 * @param handler
 */
void Redis_Subscribe(string topic, RedisMsgHandler handler)
{
    handlers[topic] = handler;
}

/**
 * @brief Initialize and Connect to Redis server.
 *
 * @return true
 * @return false
 */
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

/**
 * @brief Start and loop to watching for consuming data from Redis
 *
 */
void _start_loop()
{
    auto _subscriber = redis_client->subscriber();
    _subscriber.on_message(_message_handler);
    _subscriber.on_pmessage(_pattern_message_handler);

    for (const auto &[topic, handler] : handlers)
    {
        if (topic.find('*') == std::string::npos)
        {
            _subscriber.subscribe(topic);
            log_info("Subscribe OK: {}", topic);
        }
        else
        {
            _subscriber.psubscribe(topic);
            log_info("PSubscribe OK: {}", topic);
        }
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

/**
 * @brief Start Redis client process. This method must be called after Init() and Subscribe()
 *
 */
void Redis_Start()
{
    try
    {
        thread redis_worker(
            []()
            {
                _start_loop();
                log_warn("Redis worker is stoped!");
            });
        redis_worker.detach();
    }
    catch (const exception &e)
    {
        log_error("Redis start failed: {}", e.what());
    }
}

/**
 * @brief Return Redis Client instance for other usages
 *
 * @return Redis*
 */
Redis *Redis_Client()
{
    return redis_client;
}
