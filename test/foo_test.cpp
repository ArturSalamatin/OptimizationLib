#include <gtest/gtest.h>

// Fatal assetion
// ASSERT_** (EQ, NE, GE, ...)

// Non-fatal assertion
// EXPECT_** (EQ, NE, GE, ...)


// assertion for C-strings
// ASSERT/EXPECT_STR**


// assertion for throws
// ASSERT/EXPECT_THROW - whether throws or not

// Test Suite == Foo
// Test Case  == Bar
TEST(Foo, Bar) {
  // Arrange
  // Set up, initialize test

  // Act
  // Execution of a method
  // Save result

  //Assert
  // Verify assertion
  ASSERT_EQ(0, 0);
}