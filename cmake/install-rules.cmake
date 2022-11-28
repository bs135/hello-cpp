install(
    TARGETS hello-cpp_exe
    RUNTIME COMPONENT hello-cpp_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
