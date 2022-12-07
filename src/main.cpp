#include <iostream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>
#include "redis-bus/redis-bus.hh"
#include "redis-msg/redis-msg.hh"
#include "uid.h"
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

  redisbus.Subscribe("test/redisbus", RedisMsg_Receivce_Handler);

  /* test loop */
  std::chrono::seconds interval(1000);
  while (1)
  {
    log_info("Hello {}! {}", "world", 234);
    // std::cout << std::flush;
    auto uidRandomString = uid_gen();
    log_info("UID = : {}", uidRandomString);
    std::this_thread::sleep_for(3s);
  }

  return 0;
}
