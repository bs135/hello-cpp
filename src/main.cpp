#include <iostream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>
#include "spdlog/spdlog.h"
#include "dotenv/dotenv.h"
#include "hello/hello.hh"
#include "redis-bus/redis-bus.hh"

using namespace std;

using json = nlohmann::json;

auto main() -> int
{
  env_load(".", false);
  char *redis_host = getenv("REDIS_HOST");
  spdlog::info("REDIS_HOST: {}", redis_host);
  char *redis_port = getenv("REDIS_PORT");
  spdlog::info("REDIS_PORT: {}", redis_port);

  Date *date = new Date(1, 2, 3);
  int d = date->getDay();
  int m = date->getMonth();
  int y = date->getYear();
  spdlog::info("getSum: {}-{}-{}", m, d, y);

  std::chrono::seconds interval(10);

  json j = json::parse(R"(
    {
      "pi": 3.141,
      "bar": true,
      "foo": "test"
    }
  )");

  spdlog::set_level(spdlog::level::debug); // Set global log level to debug

  auto redisbus = RedisBus();
  redisbus.Connect();

  while (1)
  {
    spdlog::info("Hello {}! {}", "world", 234);
    float pi = j["pi"];
    bool bar = j["bar"];
    string foo = j["foo"];
    spdlog::debug("pi = {0}, foo = {2}, bar = {1}", pi, bar, foo);
    // std::cout << "=====\n"
    //           << std::flush;

    std::this_thread::sleep_for(interval);
  }

  return 0;
}
