#include <iostream>
#include "redis-bus.hh"
#include <sw/redis++/redis++.h>
// #include <sw/redis++/async_redis++.h>

using namespace sw::redis;

/**
 * @brief Construct a new Redis Bus:: Redis Bus object
 *
 */
RedisBus::RedisBus()
{
    RedisBus(REDIS_HOST_DEFAULT, REDIS_PORT_DEFAULT, REDIS_DB_DEFAULT, REDIS_PASS_DEFAULT);
}

/**
 * @brief Construct a new Redis Bus:: Redis Bus object
 *
 * @param host
 * @param port
 * @param db
 * @param pass
 */
RedisBus::RedisBus(std::string host, int port, int db, std::string pass)
{
    _host = host;
    _port = port;
    _db = db;
    _pass = pass;
}

/**
 * @brief Destroy the Redis Bus:: Redis Bus object
 *
 */
RedisBus::~RedisBus()
{
}

void RedisBus::Connect()
{
    ConnectionOptions opts;
    opts.host = "192.168.1.24"; //_host;
    opts.port = 6379;           //_port;
    // opts.socket_timeout = std::chrono::milliseconds(100);

    auto _redis = Redis(opts);

    auto _sub = _redis.subscriber();

    _sub.on_message([](std::string channel, std::string msg)
                    { std::cout << channel << ": " << msg << std::endl; });

    _sub.on_pmessage([](std::string pattern, std::string channel, std::string msg)
                     { std::cout << pattern << ":" << channel << ": " << msg << std::endl; });

    _sub.subscribe("test/hello");
    _sub.subscribe({"test/adc2", "test/adc3"});

    _sub.psubscribe("test/gpio/*");

    while (true)
    {
        try
        {
            _sub.consume();
        }
        catch (const Error &err)
        {
            std::cout << "Error: " << err.what() << std::endl;
        }
    }
}

void RedisBus::Loop()
{
}