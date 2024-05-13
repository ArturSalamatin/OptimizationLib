# https://rknuus.github.io/agility-and-quality/blog/2020/04/15/up-and-google-testing-in-minutes
# https://matgomes.com/integrate-google-test-into-cmake/

cmake_minimum_required(VERSION 3.14.0)

# fetch google test from github
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# create a variable called target_name and set it to the string "test"
set (target_name test)
project(${target_name})

macro(add_google_test name)

set(TEST_EXECUTABLE ${name})
set(TEST_NAME ${name})
add_executable(${TEST_EXECUTABLE} ${TEST_EXECUTABLE}.cpp)
target_include_directories(${TEST_EXECUTABLE} PUBLIC "${PROJECT_SOURCE_DIR}/..")
target_link_libraries(${TEST_EXECUTABLE}
    gtest_main
) 
add_test(NAME ${TEST_NAME} COMMAND ${TEST_EXECUTABLE})

  # let the preprocessor know about the system name
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_definitions(${name} PUBLIC "IS_LINUX")
  endif()
  if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  target_compile_definitions(${name} PUBLIC "IS_MACOS")
  endif()
  if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_definitions(${name} PUBLIC "IS_WINDOWS")
  endif()

endmacro()


add_google_test(foo_test)
add_google_test(point_test)

