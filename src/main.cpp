#include <iostream>
#include <string>
#include <ctime>
#include <unistd.h>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

auto main() -> int
{
  std::chrono::seconds interval(3);

  json j = json::parse(R"(
    {
      "pi": 3.141,
      "bar": true
    }
  )");

  while (1)
  {
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", now);
    std::cout << buf << '\n';

    std::cout << "Hello world!" << '\n';
    std::cout << "pi : " << j["pi"] << '\n';
    std::cout << "bar: " << j["bar"] << '\n';
    std::cout << "=====\n"
              << std::flush;

    std::this_thread::sleep_for(interval);
  }
  return 0;
}
