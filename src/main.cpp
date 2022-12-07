#include <iostream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>
#include "redis/redis.hh"
#include "redis-msg/redis-msg.hh"
#include "redis/redis.hh"
#include "uid.h"
#include "app.hh"

using namespace std;
using json = nlohmann::json;

void test_handler1(string topic, string msg)
{
    log_debug("message [{}]: {}", topic, msg);
}

void test_handler2(string topic, string msg)
{
    log_debug("message [{}]: {}", topic, msg);
}

void test_wildcard_handler(string topic, string msg)
{
    log_debug("message [{}]: {}", topic, msg);
}

auto main() -> int
{
    app_env_init();
    app_log_init();

    /* test redis */
    auto ok = Redis_Init();
    if (ok)
    {
        Redis_Subscribe("test/redisbus1", test_handler1);
        Redis_Subscribe("test/redisbus2", test_handler2);
        Redis_Subscribe("*/data", test_wildcard_handler);
        Redis_Start();

        Redis_Client()
            ->command("set", "abc", 321);

        while (true)
        {
            log_info("Hello {}! {}", "world", 234);
            Redis_Publish("test/redisbus3", "123");
            std::this_thread::sleep_for(3s);
        }
    }
    else
    {
        exit(EXIT_FAILURE);
    }

    return 0;
}
