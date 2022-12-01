cmake_minimum_required(VERSION 3.14)

set(PN hello-cpp)

project(
  ${PN}
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
add_executable(${PN} ${ALL_SRC})
set_property(TARGET ${PN} PROPERTY OUTPUT_NAME ${PN})
target_compile_features(${PN} PRIVATE cxx_std_17)

# ---- import library ----
find_package(nlohmann_json REQUIRED)
target_link_libraries(${PN} nlohmann_json::nlohmann_json)

# find_package(hiredis REQUIRED)
target_link_libraries(${PN} hiredis)

# find_package(redis++ REQUIRED)
target_link_libraries(${PN} redis++)

# add_library(redis++::redis++ UNKNOWN IMPORTED)

# set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
# set(THREADS_PREFER_PTHREAD_FLAG TRUE)
# find_package(Threads REQUIRED)
# target_link_libraries(${PN} Threads::Threads)

# ---- include ----
# add_subdirectory(./lib/spdlog)

# set_property(TARGET spdlog PROPERTY IMPORTED_LOCATION ./lib/libspdlog.a)
# target_link_libraries(${PN} spdlog)
target_include_directories(${PN} PRIVATE src/app/)
target_include_directories(${PN} PRIVATE src/core/)
target_include_directories(${PN} PRIVATE src/lib/)
target_include_directories(${PN} PRIVATE src/utils/)

# target_include_directories(${PN} PRIVATE extlib/dotenv/src/)

# ---- vendor ----
# add_subdirectory(extlib/cpp-dotenv)
# target_link_libraries(${PN} cpp_dotenv)
# add_subdirectory(extlib/dotenv)
# target_link_libraries(${PN} dotenv)
