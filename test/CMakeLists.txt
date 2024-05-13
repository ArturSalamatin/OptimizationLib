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
# add_library(GTest::GTest INTERFACE IMPORTED)
# target_link_libraries(GTest::GTest INTERFACE gtest_main)


# create a variable called target_name and set it to the string "test"
set (target_name test)
project(${target_name})



# set(TEST_EXECUTABLE foo_test)
# set(TEST_NAME foo_gtest)
# add_executable(${TEST_EXECUTABLE} ${TEST_EXECUTABLE}.cpp)
# target_include_directories(${TEST_EXECUTABLE} PUBLIC "${PROJECT_SOURCE_DIR}/..")
# target_link_libraries(${TEST_EXECUTABLE}
#   PRIVATE 
#       GTest::GTest
# ) 
# add_test(NAME ${TEST_NAME} COMMAND ${TEST_EXECUTABLE})



set(TEST_EXECUTABLE point_test)
set(TEST_NAME point_gtest)
add_executable(${TEST_EXECUTABLE} ${TEST_EXECUTABLE}.cpp)
target_include_directories(${TEST_EXECUTABLE} PUBLIC "${PROJECT_SOURCE_DIR}/..")
target_link_libraries(${TEST_EXECUTABLE}
  # PRIVATE 
      # GTest::GTest
      gtest_main
) 
add_test(NAME ${TEST_NAME} COMMAND ${TEST_EXECUTABLE})
