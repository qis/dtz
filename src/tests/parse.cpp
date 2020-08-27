#include "data.hpp"
#include <dtz/format.hpp>
#include <dtz/parse.hpp>
#include <gtest/gtest.h>

template <dtz::Duration Duration>
bool parse_duration_test(const std::string& s, const Duration& d) {
  const auto v = dtz::parse<Duration>(s);
  EXPECT_EQ(s, dtz::format(v));
  return v == d;
}

template <dtz::Duration Duration>
bool parse_duration_test() {
  bool success = true;
  for (const auto& e : format_duration_data<typename Duration::rep, typename Duration::period>::value) {
    success &= parse_duration_test(e.first, e.second);
  }
  return success;
}

TEST(dtz, parse_duration) {
  EXPECT_TRUE(parse_duration_test<dtz::nanoseconds>());
  EXPECT_TRUE(parse_duration_test<dtz::microseconds>());
  EXPECT_TRUE(parse_duration_test<dtz::milliseconds>());
  EXPECT_TRUE(parse_duration_test<dtz::seconds>());
  EXPECT_TRUE(parse_duration_test<dtz::minutes>());
  EXPECT_TRUE(parse_duration_test<dtz::hours>());
  EXPECT_TRUE(parse_duration_test<dtz::days>());

  // TODO: Change format to allow more precision.
  //EXPECT_TRUE(parse_duration_test<dtz::weeks>());
  //EXPECT_TRUE(parse_duration_test<dtz::months>());
  //EXPECT_TRUE(parse_duration_test<dtz::years>());

  // TODO: Relaxed comparison during testing.
  //EXPECT_TRUE(parse_duration_test("00:00:00.000000500", dtz::fpmicroseconds<float>{ 0.5f }));
  //EXPECT_TRUE(parse_duration_test("00:00:00.001500", dtz::fpmilliseconds<float>{ 1.5f }));
  //EXPECT_TRUE(parse_duration_test("00:00:02.500", dtz::fpseconds<float>{ 2.5f }));
  //EXPECT_TRUE(parse_duration_test("00:03:30", dtz::fpminutes<float>{ 3.5f }));
  //EXPECT_TRUE(parse_duration_test("04:30", dtz::fphours<float>{ 4.5f }));
  //EXPECT_TRUE(parse_duration_test("36:00", dtz::fpdays<float>{ 1.5f }));
  //EXPECT_TRUE(parse_duration_test("24:00", dtz::fpweeks<float>{ 1.0f / 7 }));
}
