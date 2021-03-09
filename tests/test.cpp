#include "gtest/gtest.h"
#include "valid.hpp"
#include "print_test.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
