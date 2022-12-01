#include "redis-bus.hh"
// #include <sw/redis++/async_redis++.h>

/**
 * @brief Construct a new Redis Bus:: Redis Bus object
 *
 */
// RedisBus::RedisBus()
// {
//     // RedisBus(REDIS_HOST_TEST, REDIS_PORT_DEFAULT, REDIS_DB_DEFAULT, REDIS_PASS_DEFAULT);
//     //  _opts.host = REDIS_HOST_TEST;
//     //  std::cout << "Test " << _opts.host << std::endl;
//     //  _opts.port = REDIS_PORT_DEFAULT;
//     //  _opts.db = REDIS_DB_DEFAULT;
//     //  _opts.password = REDIS_PASS_DEFAULT;
// }

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
    std::cout << "TestAAA " << _opts.host << std::endl;
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
        std::cout << "Test11 " << _opts.host << std::endl;
        _redis_client = new Redis(_opts);
        std::cout << "Test22 " << _opts.host << std::endl;
        if (_redis_client != nullptr)
            std::cout << "Connected to server " << _opts.host << std::endl;
    }
    catch (const Error &e)
    {
        std::cout << "Cannot connect to server " << std::endl;
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
void RedisBus::Subscribe(string topic)
{
    auto sub = _redis_client->subscriber();
    sub.subscribe(topic);
    std::cout << "Sub OK " << std::endl;

    sub.on_message([](std::string channel, std::string msg)
                   { std::cout << channel << ": " << msg << std::endl; });
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