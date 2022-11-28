#include <iostream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

using namespace std;

using json = nlohmann::json;

auto main() -> int
{
  std::chrono::seconds interval(3);

  json j = json::parse(R"(
    {
      "pi": 3.141,
      "bar": true,
      "foo": "test"
    }
  )");

  spdlog::set_level(spdlog::level::debug); // Set global log level to debug

  while (1)
  {
    spdlog::info("Hello {}! {}", "world", 123);
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
