cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
  hello-cpp
  VERSION 0.1.0
  DESCRIPTION "Short description"
  HOMEPAGE_URL "https://example.com/"
  LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----
find_package(nlohmann_json REQUIRED)

# ---- Declare executable ----
add_executable(hello-cpp_exe source/main.cpp)
add_executable(hello-cpp::exe ALIAS hello-cpp_exe)

set_property(TARGET hello-cpp_exe PROPERTY OUTPUT_NAME hello-cpp)

target_compile_features(hello-cpp_exe PRIVATE cxx_std_17)

target_link_libraries(hello-cpp_exe PRIVATE nlohmann_json::nlohmann_json)

# ---- Install rules ----
if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----
if(NOT hello-cpp_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
    AUTHOR_WARNING
    "Developer mode is intended for developers of hello-cpp"
  )
endif()

include(cmake/dev-mode.cmake)
