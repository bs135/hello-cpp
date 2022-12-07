#include <iostream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>
#include "redis/redis.hh"
#include "redis-msg/redis-msg.hh"
#include "redis/redis.hh"
#include "utils.h"
#include "app.h"
#include "app_test.hh"

using namespace std;
using json = nlohmann::json;

auto main() -> int
{
    app_env_init();
    app_log_init();
    app_redis_init();

    return 0;
}
