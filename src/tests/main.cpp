#include <dtz/chrono.hpp>
#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
  dtz::initialize();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
