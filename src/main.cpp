#include <iostream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>
#include "redis-bus/redis-bus.hh"

#include "app.h"

using namespace std;
using json = nlohmann::json;

void test_handler(string topic, string msg)
{
  log_debug("message_on {}: {}", topic, msg);
}

auto main() -> int
{
  app_env_init();
  app_log_init();

  /* test redis */
  auto redisbus = RedisBus();
  redisbus.Connect();
  redisbus.Subscribe("test/redisbus", test_handler);

  /* test loop */
  std::chrono::seconds interval(10);
  while (1)
  {
    log_info("Hello {}! {}", "world", 234);
    // std::cout << std::flush;

    std::this_thread::sleep_for(interval);
  }

  return 0;
}
