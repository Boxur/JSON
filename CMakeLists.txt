cmake_minimum_required(VERSION 3.14)

project("json")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

option(MYLIB_BUILD_TESTS "Build tests" ${PROJECT_IS_TOP_LEVEL})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_library(json
  src/json.cpp
)
target_include_directories(json PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(MYLIB_BUILD_TESTS)
  add_executable(tests
    src/tests/json.cpp
  )
  include(FetchContent)

  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/f840327b0f76408eafde2440af3b2f0a70662ea6.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  FetchContent_MakeAvailable(googletest)

  enable_testing()

  target_link_libraries(tests json GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(tests)
endif()
