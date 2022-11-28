#include <fstream>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

auto main() -> int
{
  std::cout << "Hello world! 123" << '\n';

  json j = json::parse(R"(
    {
      "pi": 3.141,
      "happy": true
    }
  )");

  std::cout << j["pi"] << '\n';
  std::cout << j["happy"] << '\n';

  return 0;
}
