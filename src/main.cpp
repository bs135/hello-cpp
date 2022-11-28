#include <iostream>
#include <string>
#include <ctime>
#include <unistd.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

auto main() -> int
{
  json j = json::parse(R"(
    {
      "pi": 3.141,
      "foo": true
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
    std::cout << "foo: " << j["foo"] << '\n';
    sleep(1);
  }
  return 0;
}
