#include "format.hpp"
#include <dtz/format.hpp>
#include <gtest/gtest.h>

template <dtz::Duration Duration>
bool format_duration_test() {
  bool success = true;
  for (const auto& e : format_duration_data<typename Duration::rep, typename Duration::period>::value) {
    const auto str = fmt::format("{}", e.second);
    success &= e.first == str;
    EXPECT_EQ(e.first, str);
  }
  return success;
}

TEST(dtz, format_duration) {
  EXPECT_TRUE(format_duration_test<dtz::nanoseconds>());
  EXPECT_TRUE(format_duration_test<dtz::microseconds>());
  EXPECT_TRUE(format_duration_test<dtz::milliseconds>());
  EXPECT_TRUE(format_duration_test<dtz::seconds>());
  EXPECT_TRUE(format_duration_test<dtz::minutes>());
  EXPECT_TRUE(format_duration_test<dtz::hours>());
  EXPECT_TRUE(format_duration_test<dtz::days>());
  EXPECT_TRUE(format_duration_test<dtz::weeks>());
  EXPECT_TRUE(format_duration_test<dtz::months>());
  EXPECT_TRUE(format_duration_test<dtz::years>());

  EXPECT_EQ("00:00:00.000000500", fmt::format("{}", dtz::fpmicroseconds<float>{ 0.5f }));
  EXPECT_EQ("00:00:00.001500", fmt::format("{}", dtz::fpmilliseconds<float>{ 1.5f }));
  EXPECT_EQ("00:00:02.500", fmt::format("{}", dtz::fpseconds<float>{ 2.5f }));
  EXPECT_EQ("00:03:30", fmt::format("{}", dtz::fpminutes<float>{ 3.5f }));
  EXPECT_EQ("04:30", fmt::format("{}", dtz::fphours<float>{ 4.5f }));
  EXPECT_EQ("36:00", fmt::format("{}", dtz::fpdays<float>{ 1.5f }));
  EXPECT_EQ("24:00", fmt::format("{}", dtz::fpweeks<float>{ 1.0f / 7 }));
}

template <dtz::Duration Duration>
bool format_time_point_test() {
  bool success = true;
  for (const auto& e : format_time_point_data<Duration>::value) {
    const auto str = fmt::format("{}", e.second);
    success &= e.first == str;
    EXPECT_EQ(e.first, str);
  }
  return success;
}

TEST(dtz, format_time_point) {
  EXPECT_TRUE(format_time_point_test<dtz::nanoseconds>());
  EXPECT_TRUE(format_time_point_test<dtz::microseconds>());
  EXPECT_TRUE(format_time_point_test<dtz::milliseconds>());
  EXPECT_TRUE(format_time_point_test<dtz::seconds>());
  EXPECT_TRUE(format_time_point_test<dtz::minutes>());
  EXPECT_TRUE(format_time_point_test<dtz::hours>());
  EXPECT_TRUE(format_time_point_test<dtz::days>());
  EXPECT_TRUE(format_time_point_test<dtz::weeks>());
  EXPECT_TRUE(format_time_point_test<dtz::fpmonths<float>>());
  EXPECT_TRUE(format_time_point_test<dtz::fpyears<float>>());
}
