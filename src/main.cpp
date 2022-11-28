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

  while (1)
  {
    spdlog::info("Hello {0}! {1}", "world", 123);
    float pi = j["pi"];
    bool bar = j["bar"];
    string foo = j["foo"];
    spdlog::info("pi = {0}, bar = {1}, foo = {1}", pi, bar, foo);
    // std::cout << "=====\n"
    //           << std::flush;

    std::this_thread::sleep_for(interval);
  }
  return 0;
}
