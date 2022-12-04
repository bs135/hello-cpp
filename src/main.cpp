#include <iostream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>
#include "hello/hello.hh"
#include "redis-bus/redis-bus.hh"

#include "env.h"
#include "log.h"

using namespace std;

using json = nlohmann::json;

auto main() -> int
{
  log_init(LOG_DEBUG, "hello-cpp", "log");

  log_trace("test log {}", "TRACE");
  log_debug("test log {}", "DEBUG");
  log_info("test log {}", "INFO");
  log_warn("test log {}", "WARN");
  log_error("test log {}", "ERROR");
  log_fatal("test log {}", "FATAL");

  env_init(".");
  string redis_host = env_get("REDIS_HOST", "localhost");
  log_info("REDIS_HOST: {}", redis_host);
  int redis_port = env_get_int("REDIS_PORT", 1234);
  log_info("REDIS_PORT: {}", redis_port);
  int redis_db = env_get_int("REDIS_DB", 1);
  log_info("REDIS_DB: {}", redis_db);

  bool test_bool = env_get_bool("TEST_BOOL");
  log_info("TEST_BOOL: {}", test_bool);

  Date *date = new Date(1, 2, 3);
  int d = date->getDay();
  int m = date->getMonth();
  int y = date->getYear();
  log_info("getSum: {}-{}-{}", m, d, y);

  std::chrono::seconds interval(10);

  json j = json::parse(R"(
    {
      "pi": 3.141,
      "bar": true,
      "foo": "test"
    }
  )");

  auto redisbus = RedisBus();
  redisbus.Connect();
  redisbus.Subscribe("TestRedisBus");
  while (1)
  {
    log_info("Hello {}! {}", "world", 234);
    float pi = j["pi"];
    bool bar = j["bar"];
    string foo = j["foo"];
    log_debug("pi = {0}, foo = {2}, bar = {1}", pi, bar, foo);
    // std::cout << "=====\n"
    //           << std::flush;

    std::this_thread::sleep_for(interval);
  }

  return 0;
}
