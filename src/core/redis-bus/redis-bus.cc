#include "env.h"
#include "log.h"
#include "redis-bus.hh"
// #include <sw/redis++/async_redis++.h>

/**
 * @brief Construct a new Redis Bus:: Redis Bus object
 *
 */
RedisBus::RedisBus()
{
    // !IMPORTANT: make sure the env is loaded

    _opts.host = env_get("REDIS_HOST", REDIS_HOST_DEFAULT);
    _opts.port = env_get_int("REDIS_PORT", REDIS_PORT_DEFAULT);
    _opts.db = env_get_int("REDIS_DB", REDIS_DB_DEFAULT);
    _opts.password = env_get("REDIS_PASS", REDIS_PASS_DEFAULT);

    // new (this) RedisBus(REDIS_HOST_DEFAULT, REDIS_PORT_DEFAULT, REDIS_DB_DEFAULT, REDIS_PASS_DEFAULT);
}

/**
 * @brief Construct a new Redis Bus:: Redis Bus object
 *
 * @param host
 * @param port
 * @param db
 * @param pass
 */
RedisBus::RedisBus(string host, int port, int db, string pass)
{
    _opts.host = host;
    _opts.port = port;
    _opts.db = db;
    _opts.password = pass;
}

/**
 * @brief Destroy the Redis Bus:: Redis Bus object
 *
 */
RedisBus::~RedisBus()
{
}

/**
 * @brief
 *
 */
void RedisBus::Connect()
{
    try
    {
        _redis_client = new Redis(_opts);
        if (_redis_client != nullptr)
            log_debug("Connected to server {}", _opts.host);
    }
    catch (const Error &e)
    {
        log_error("Cannot connect to server {}", _opts.host);
    }
}

/**
 * @brief
 *
 * @param topic     Channel want to publish the the message
 * @param message   The message want to publish to the topic
 */
void RedisBus::Publish(string topic, string message)
{
}

/**
 * @brief
 *
 * @param topic     Channel want to publish the the message
 * @param handler   Callback function
 */
// template <typename MsgCb>
void RedisBus::Subscribe(string topic, MsgHandler handler)
{
    auto sub = _redis_client->subscriber();
    sub.subscribe(topic);
    log_info("Subscribe OK: {}", topic);

    sub.on_message(handler);

    while (true)
    {
        try
        {
            sub.consume();
        }
        catch (const Error &err)
        {
            std::cout << "Error: " << err.what() << std::endl;
        }
    }
}

/**
 * @brief
 *
 */
void RedisBus::Loop()
{
}