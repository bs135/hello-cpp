#include <iostream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>
#include "redis/redis.hh"
#include "app.hh"

using namespace std;
using json = nlohmann::json;

void test_handler1(string msg)
{
  log_debug("message [1]: {}", msg);
}

void test_handler2(string msg)
{
  log_debug("message [2]: {}", msg);
}

auto main() -> int
{
  app_env_init();
  app_log_init();

  /* test redis */
  Redis_Init();
  Redis_Subscribe("test/redisbus1", test_handler1);
  Redis_Subscribe("test/redisbus2", test_handler2);
  Redis_Start();

  Redis_Client()
      ->command("set", "abc", 321);

  while (true)
  {
    log_info("Hello {}! {}", "world", 234);
    Redis_Publish("test/redisbus3", "123");
    std::this_thread::sleep_for(3s);
  }

  return 0;
}
