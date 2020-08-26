#include "format.hpp"
#include <dtz/format.hpp>
#include <gtest/gtest.h>

template <dtz::Duration Duration>
void format_duration_test() {
  for (const auto& e : format_duration_data<typename Duration::rep, typename Duration::period>::value) {
    EXPECT_EQ(e.first, fmt::format("{}", e.second));
  }
  for (const auto& e : format_duration_data<float, typename Duration::period>::value) {
    EXPECT_EQ(e.first, fmt::format("{}", e.second));
  }
  for (const auto& e : format_duration_data<double, typename Duration::period>::value) {
    EXPECT_EQ(e.first, fmt::format("{}", e.second));
  }
}

TEST(dtz, format_duration) {
  format_duration_test<dtz::nanoseconds>();
  format_duration_test<dtz::microseconds>();
  format_duration_test<dtz::milliseconds>();
  format_duration_test<dtz::seconds>();
  format_duration_test<dtz::minutes>();
  format_duration_test<dtz::hours>();
  format_duration_test<dtz::days>();
  format_duration_test<dtz::weeks>();
  format_duration_test<dtz::months>();
  format_duration_test<dtz::years>();
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
