cmake_minimum_required(VERSION 3.14)

project(
  hello-cpp
  VERSION 0.1.0
  DESCRIPTION "Short description"
  HOMEPAGE_URL "https://example.com/"
  LANGUAGES CXX
)

# ---- import library ----
find_package(nlohmann_json REQUIRED)

# ---- executable ----
add_executable(hello-cpp src/main.cpp)

set_property(TARGET hello-cpp PROPERTY OUTPUT_NAME hello-cpp)

target_compile_features(hello-cpp PRIVATE cxx_std_17)

target_link_libraries(hello-cpp nlohmann_json::nlohmann_json)

# ---- build library ----
# add_subdirectory(./lib/spdlog)

# set_property(TARGET spdlog PROPERTY IMPORTED_LOCATION ./lib/libspdlog.a)
# target_link_libraries(hello-cpp spdlog)
target_include_directories(hello-cpp PRIVATE ./lib/)

# ---- vendor ----
# add_subdirectory(./lib/cpp-dotenv)
# target_link_libraries(hello-cpp cpp_dotenv)
