# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(hello-cppTests LANGUAGES CXX)

# ---- Tests ----
add_executable(hello-cpp_test src/hello-cpp_test.cpp)
target_link_libraries(hello-cpp_test PRIVATE hello-cpp_lib)
target_compile_features(hello-cpp_test PRIVATE cxx_std_17)

add_test(NAME hello-cpp_test COMMAND hello-cpp_test)

# ---- End-of-file commands ----
add_folders(Test)
