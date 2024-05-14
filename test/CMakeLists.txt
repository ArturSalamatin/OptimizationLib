# https://rknuus.github.io/agility-and-quality/blog/2020/04/15/up-and-google-testing-in-minutes
# https://matgomes.com/integrate-google-test-into-cmake/
# https://google.github.io/googletest/primer.html
# https://www.youtube.com/watch?v=Lp1ifh9TuFI&t=755s
# https://www.youtube.com/watch?v=jyQcCWWcIQU
cmake_minimum_required(VERSION 3.14.0)

# fetch google test from github
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
if(MSVC)
  # hack for windows compilation
  # or for compilation with MSVC
  # if MinGW -- may not be required...
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
FetchContent_MakeAvailable(googletest)

# create a variable called target_name and set it to the string "test"
set (target_name test)
project(${target_name})

macro(add_google_test name)

  set(TEST_EXECUTABLE ${name})
  set(TEST_NAME ${name})
  add_executable(
    ${TEST_NAME}  
      ${TEST_EXECUTABLE}.cpp
  )
  target_include_directories(
    ${TEST_NAME} PRIVATE 
      "${PROJECT_SOURCE_DIR}/.."
  )
  target_link_libraries(
    ${TEST_NAME} PRIVATE
      gtest_main
  ) 

  # let the preprocessor know about the system name
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(${TEST_NAME} PUBLIC "IS_LINUX")
  endif()
  if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(${TEST_NAME} PUBLIC "IS_MACOS")
  endif()
  if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(${TEST_NAME} PUBLIC "IS_WINDOWS")
  endif()

  # compiler-specific options
  if(MSVC AND MSVC_VERSION GREATER 1400)
    target_compile_options(
      ${TEST_NAME} PRIVATE 
      /MP)
  else()
    target_compile_options(
      ${TEST_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
  endif()

  # adding the test, finally
  add_test(
    NAME ${TEST_NAME} 
    COMMAND ${TEST_EXECUTABLE})

endmacro()


# add_google_test(foo_test)
add_google_test(point_test)
add_google_test(fixture_demo)

