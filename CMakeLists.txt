cmake_minimum_required(VERSION 3.14)

project(
  hello-cpp
  VERSION 0.1.0
  DESCRIPTION "Short description"
  HOMEPAGE_URL "https://example.com/"
  LANGUAGES C CXX
)

# ---- executable ----
file(GLOB_RECURSE ALL_SRC
  "src/**.cpp"
  "src/**.cc"
  "src/**.c"
)

add_executable(hello-cpp ${ALL_SRC})
set_property(TARGET hello-cpp PROPERTY OUTPUT_NAME hello-cpp)
target_compile_features(hello-cpp PRIVATE cxx_std_17)

# ---- import library ----
find_package(nlohmann_json REQUIRED)
target_link_libraries(hello-cpp nlohmann_json::nlohmann_json)

# ---- build library ----
# add_subdirectory(./lib/spdlog)

# set_property(TARGET spdlog PROPERTY IMPORTED_LOCATION ./lib/libspdlog.a)
# target_link_libraries(hello-cpp spdlog)
target_include_directories(hello-cpp PRIVATE src/utils/)
target_include_directories(hello-cpp PRIVATE src/app/)
target_include_directories(hello-cpp PRIVATE src/lib/)

# target_include_directories(hello-cpp PRIVATE extlib/dotenv/src/)

# ---- vendor ----
# add_subdirectory(extlib/cpp-dotenv)
# target_link_libraries(hello-cpp cpp_dotenv)
# add_subdirectory(extlib/dotenv)
# target_link_libraries(hello-cpp dotenv)
