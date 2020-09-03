#include <gtest/gtest.h>
#include <dtz/chrono.hpp>

int main(int argc, char* argv[])
{
  dtz::initialize();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
