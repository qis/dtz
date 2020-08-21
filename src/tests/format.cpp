#include <dtz/format.hpp>
#include <gtest/gtest.h>

using namespace dtz::literals;

TEST(dtz, format_duration) {
  EXPECT_EQ("00:00:00.000000001", fmt::format("{}", dtz::nanoseconds{ 1ns }));
  EXPECT_EQ("00:00:00.000001000", fmt::format("{}", dtz::nanoseconds{ 1us }));
  EXPECT_EQ("00:00:00.001000000", fmt::format("{}", dtz::nanoseconds{ 1ms }));
  EXPECT_EQ("00:00:01.000000000", fmt::format("{}", dtz::nanoseconds{ 1s }));
  EXPECT_EQ("00:01:00.000000000", fmt::format("{}", dtz::nanoseconds{ 1min }));
  EXPECT_EQ("01:00:00.000000000", fmt::format("{}", dtz::nanoseconds{ 1h }));
  EXPECT_EQ("24:00:00.000000000", fmt::format("{}", dtz::nanoseconds{ dtz::days{ 1 } }));

  EXPECT_EQ("00:00:00.000001", fmt::format("{}", dtz::microseconds{ 1us }));
  EXPECT_EQ("00:00:00.001000", fmt::format("{}", dtz::microseconds{ 1ms }));
  EXPECT_EQ("00:00:01.000000", fmt::format("{}", dtz::microseconds{ 1s }));
  EXPECT_EQ("00:01:00.000000", fmt::format("{}", dtz::microseconds{ 1min }));
  EXPECT_EQ("01:00:00.000000", fmt::format("{}", dtz::microseconds{ 1h }));
  EXPECT_EQ("24:00:00.000000", fmt::format("{}", dtz::microseconds{ dtz::days{ 1 } }));

  EXPECT_EQ("00:00:00.001", fmt::format("{}", dtz::milliseconds{ 1ms }));
  EXPECT_EQ("00:00:01.000", fmt::format("{}", dtz::milliseconds{ 1s }));
  EXPECT_EQ("00:01:00.000", fmt::format("{}", dtz::milliseconds{ 1min }));
  EXPECT_EQ("01:00:00.000", fmt::format("{}", dtz::milliseconds{ 1h }));
  EXPECT_EQ("24:00:00.000", fmt::format("{}", dtz::milliseconds{ dtz::days{ 1 } }));

  EXPECT_EQ("00:00:01", fmt::format("{}", dtz::seconds{ 1s }));
  EXPECT_EQ("00:01:00", fmt::format("{}", dtz::seconds{ 1min }));
  EXPECT_EQ("01:00:00", fmt::format("{}", dtz::seconds{ 1h }));
  EXPECT_EQ("24:00:00", fmt::format("{}", dtz::seconds{ dtz::days{ 1 } }));

  EXPECT_EQ("00:01", fmt::format("{}", dtz::minutes{ 1min }));
  EXPECT_EQ("01:00", fmt::format("{}", dtz::minutes{ 1h }));
  EXPECT_EQ("24:00", fmt::format("{}", dtz::minutes{ dtz::days{ 1 } }));

  EXPECT_EQ("01:00", fmt::format("{}", dtz::hours{ 1h }));
  EXPECT_EQ("24:00", fmt::format("{}", dtz::hours{ dtz::days{ 1 } }));

  EXPECT_EQ("24:00", fmt::format("{}", dtz::days{ 1 }));
}

template <dtz::ClockOrLocal ClockOrLocal, dtz::Duration Duration>
auto mtp(const dtz::year_month_day& ymd, const Duration& duration) {
  return dtz::cast<ClockOrLocal>(dtz::local_days{ ymd }) + duration;
}

template <dtz::Duration Duration>
auto mtp(const dtz::time_zone* zone, const dtz::year_month_day& ymd, const Duration& duration) {
  return dtz::make_zoned(zone, dtz::sys_days{ ymd } + duration);
}

template <dtz::Duration Duration>
auto mtp(std::string_view zone, const dtz::year_month_day& ymd, const Duration& duration) {
  return dtz::make_zoned(zone, dtz::sys_days{ ymd } + duration);
}

TEST(dtz, format_time_point) {
  const auto ymd = dtz::year{ 1971 } / dtz::month{ 1 } / dtz::day{ 1 };

  const auto tmp0 = mtp<dtz::local_t>(ymd, 1h);
  const auto tmp1 = mtp<dtz::system_clock>(ymd, 1h);
  const auto tmp2 = mtp<dtz::utc_clock>(ymd, 1h);
  const auto tmp3 = mtp<dtz::tai_clock>(ymd, 1h);
  const auto tmp4 = mtp<dtz::gps_clock>(ymd, 1h);
  const auto tmp5 = mtp("Europe/Berlin", ymd, 1h);
  
  //const auto sys = dtz::sys_days{ ymd };
  //const auto utc = dtz::utc_clock::from_sys(sys);
  //const auto tai = dtz::tai_clock::from_utc(utc);
  //const auto gps = dtz::gps_clock::from_utc(utc);
  //const auto zon = dtz::make_zoned("Europe/Berlin", sys + 0h);
  //const auto loc = zon.get_local_time;
  
}
