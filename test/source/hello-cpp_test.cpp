#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "hello-cpp" ? 0 : 1;
}
