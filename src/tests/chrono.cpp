#include <dtz/chrono.hpp>
#include <gtest/gtest.h>

using namespace dtz::literals;

namespace date {

[[nodiscard]] inline constexpr bool operator<=(const weekday& lhs, const weekday& rhs) noexcept {
  return lhs.iso_encoding() <= rhs.iso_encoding();
}

[[nodiscard]] inline constexpr bool operator>=(const weekday& lhs, const weekday& rhs) noexcept {
  return lhs.iso_encoding() >= rhs.iso_encoding();
}

[[nodiscard]] inline constexpr bool operator<(const weekday& lhs, const weekday& rhs) noexcept {
  return lhs.iso_encoding() < rhs.iso_encoding();
}

[[nodiscard]] inline constexpr bool operator>(const weekday& lhs, const weekday& rhs) noexcept {
  return lhs.iso_encoding() > rhs.iso_encoding();
}

template <dtz::HHMMSS LHS, dtz::HHMMSS RHS>
[[nodiscard]] inline constexpr bool operator==(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() == rhs.to_duration();
}

template <dtz::HHMMSS LHS, dtz::HHMMSS RHS>
[[nodiscard]] inline constexpr bool operator<=(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() <= rhs.to_duration();
}

template <dtz::HHMMSS LHS, dtz::HHMMSS RHS>
[[nodiscard]] inline constexpr bool operator>=(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() >= rhs.to_duration();
}

template <dtz::HHMMSS LHS, dtz::HHMMSS RHS>
[[nodiscard]] inline constexpr bool operator<(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() < rhs.to_duration();
}

template <dtz::HHMMSS LHS, dtz::HHMMSS RHS>
[[nodiscard]] inline constexpr bool operator>(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() > rhs.to_duration();
}

template <dtz::ZonedTime ZonedTime, dtz::Duration FromDuration>
[[nodiscard]] inline constexpr auto operator+(const ZonedTime& zt, const FromDuration& d) noexcept {
  using ToDuration = std::common_type_t<FromDuration, typename dtz::is_zoned_time<ZonedTime>::duration>;
  return dtz::zoned_time<ToDuration>{ zt.get_time_zone(), dtz::cast<ToDuration>(zt.get_sys_time() + d) };
}

template <dtz::ZonedTime ZonedTime, dtz::Duration FromDuration>
[[nodiscard]] inline constexpr auto operator-(const ZonedTime& zt, const FromDuration& d) noexcept {
  return operator+(zt, -d);
}

}  // namespace date

#if 1
TEST(dtz, concepts) {
  // Clock
  static_assert(dtz::Clock<dtz::system_clock>);
  static_assert(dtz::Clock<dtz::steady_clock>);
  static_assert(dtz::Clock<dtz::high_resolution_clock>);
  static_assert(dtz::Clock<dtz::utc_clock>);
  static_assert(dtz::Clock<dtz::tai_clock>);
  static_assert(dtz::Clock<dtz::gps_clock>);

  // !Clock
  static_assert(!dtz::Clock<dtz::local_t>);

  // Local
  static_assert(dtz::Local<dtz::local_t>);

  // !Local
  static_assert(!dtz::Local<dtz::system_clock>);
  static_assert(!dtz::Local<dtz::steady_clock>);
  static_assert(!dtz::Local<dtz::high_resolution_clock>);
  static_assert(!dtz::Local<dtz::utc_clock>);
  static_assert(!dtz::Local<dtz::tai_clock>);
  static_assert(!dtz::Local<dtz::gps_clock>);

  // ClockOrLocal
  static_assert(dtz::ClockOrLocal<dtz::system_clock>);
  static_assert(dtz::ClockOrLocal<dtz::steady_clock>);
  static_assert(dtz::ClockOrLocal<dtz::high_resolution_clock>);
  static_assert(dtz::ClockOrLocal<dtz::utc_clock>);
  static_assert(dtz::ClockOrLocal<dtz::tai_clock>);
  static_assert(dtz::ClockOrLocal<dtz::gps_clock>);
  static_assert(dtz::ClockOrLocal<dtz::local_t>);

  // Duration
  static_assert(dtz::Duration<dtz::nanoseconds>);
  static_assert(dtz::Duration<dtz::microseconds>);
  static_assert(dtz::Duration<dtz::milliseconds>);
  static_assert(dtz::Duration<dtz::seconds>);
  static_assert(dtz::Duration<dtz::minutes>);
  static_assert(dtz::Duration<dtz::hours>);
  static_assert(dtz::Duration<dtz::days>);
  static_assert(dtz::Duration<dtz::weeks>);
  static_assert(dtz::Duration<dtz::months>);
  static_assert(dtz::Duration<dtz::years>);

  // !Duration
  static_assert(!dtz::Duration<dtz::sys_time<dtz::seconds>>);
  static_assert(!dtz::Duration<dtz::sys_days>);
  static_assert(!dtz::Duration<dtz::utc_time<dtz::seconds>>);
  static_assert(!dtz::Duration<dtz::tai_time<dtz::seconds>>);
  static_assert(!dtz::Duration<dtz::gps_time<dtz::seconds>>);

  // TimePoint
  static_assert(dtz::TimePoint<dtz::sys_time<dtz::seconds>>);
  static_assert(dtz::TimePoint<dtz::sys_days>);
  static_assert(dtz::TimePoint<dtz::utc_time<dtz::seconds>>);
  static_assert(dtz::TimePoint<dtz::tai_time<dtz::seconds>>);
  static_assert(dtz::TimePoint<dtz::gps_time<dtz::seconds>>);

  // !TimePoint
  static_assert(!dtz::TimePoint<dtz::nanoseconds>);
  static_assert(!dtz::TimePoint<dtz::microseconds>);
  static_assert(!dtz::TimePoint<dtz::milliseconds>);
  static_assert(!dtz::TimePoint<dtz::seconds>);
  static_assert(!dtz::TimePoint<dtz::minutes>);
  static_assert(!dtz::TimePoint<dtz::hours>);
  static_assert(!dtz::TimePoint<dtz::days>);
  static_assert(!dtz::TimePoint<dtz::weeks>);
  static_assert(!dtz::TimePoint<dtz::months>);
  static_assert(!dtz::TimePoint<dtz::years>);
  static_assert(!dtz::TimePoint<dtz::local_time<dtz::seconds>>);
  static_assert(!dtz::TimePoint<dtz::local_days>);
  static_assert(!dtz::TimePoint<dtz::zoned_time<dtz::seconds>>);

  // LocalTime
  static_assert(dtz::LocalTime<dtz::local_time<dtz::seconds>>);
  static_assert(dtz::LocalTime<dtz::local_days>);

  // !LocalTime
  static_assert(!dtz::LocalTime<dtz::sys_time<dtz::seconds>>);
  static_assert(!dtz::LocalTime<dtz::sys_days>);
  static_assert(!dtz::LocalTime<dtz::utc_time<dtz::seconds>>);
  static_assert(!dtz::LocalTime<dtz::tai_time<dtz::seconds>>);
  static_assert(!dtz::LocalTime<dtz::gps_time<dtz::seconds>>);
  static_assert(!dtz::LocalTime<dtz::zoned_time<dtz::seconds>>);

  // TimePointOrLocalTime
  static_assert(dtz::TimePointOrLocalTime<dtz::sys_time<dtz::seconds>>);
  static_assert(dtz::TimePointOrLocalTime<dtz::sys_days>);
  static_assert(dtz::TimePointOrLocalTime<dtz::utc_time<dtz::seconds>>);
  static_assert(dtz::TimePointOrLocalTime<dtz::tai_time<dtz::seconds>>);
  static_assert(dtz::TimePointOrLocalTime<dtz::gps_time<dtz::seconds>>);
  static_assert(dtz::TimePointOrLocalTime<dtz::local_time<dtz::seconds>>);
  static_assert(dtz::TimePointOrLocalTime<dtz::local_days>);

  // TimeZone
  static_assert(dtz::TimeZone<dtz::time_zone>);

  // !TimeZone
  static_assert(!dtz::TimeZone<dtz::time_zone*>);
  static_assert(!dtz::TimeZone<const dtz::time_zone*>);
  static_assert(!dtz::TimeZone<dtz::time_zone* const>);
  static_assert(!dtz::TimeZone<const dtz::time_zone* const>);

  // TimeZonePtr
  static_assert(dtz::TimeZonePtr<dtz::time_zone*>);
  static_assert(dtz::TimeZonePtr<const dtz::time_zone*>);
  static_assert(dtz::TimeZonePtr<dtz::time_zone* const>);
  static_assert(dtz::TimeZonePtr<const dtz::time_zone* const>);

  // !TimeZonePtr
  static_assert(!dtz::TimeZonePtr<dtz::time_zone>);

  // ZonedTime
  static_assert(dtz::ZonedTime<dtz::zoned_time<dtz::seconds>>);

  // !ZonedTime
  static_assert(!dtz::ZonedTime<dtz::sys_time<dtz::seconds>>);
  static_assert(!dtz::ZonedTime<dtz::sys_days>);
  static_assert(!dtz::ZonedTime<dtz::utc_time<dtz::seconds>>);
  static_assert(!dtz::ZonedTime<dtz::tai_time<dtz::seconds>>);
  static_assert(!dtz::ZonedTime<dtz::gps_time<dtz::seconds>>);
  static_assert(!dtz::ZonedTime<dtz::local_time<dtz::seconds>>);
  static_assert(!dtz::ZonedTime<dtz::local_days>);
}

TEST(dtz, make_zoned) {
  const auto loc_zone = dtz::locate_zone("Europe/Berlin");
  ASSERT_TRUE(loc_zone);

  const auto utc_zone = dtz::locate_zone("UTC");
  ASSERT_TRUE(utc_zone);

  const auto ymd = dtz::year{ 2018 } / dtz::month{ 3 } / dtz::day{ 25 };
  const auto hms = 2h + 30min + 1s + 2ms;

  const auto loc_days = dtz::local_days{ ymd };
  const auto sys_days = dtz::sys_days{ ymd };

  const auto loc_time_point = loc_days + hms;
  const auto sys_time_point = sys_days + hms;

  // template <typename Zone, SafeZonedLocalTime FromSafeZonedLocalTime>
  // auto make_zoned(Zone&& zone, const FromSafeZonedLocalTime& tp)
  {
    const auto zon_days = dtz::make_zoned(loc_zone, loc_days + 0h);

    const auto zon_loc_time_point = zon_days.get_local_time();
    const auto zon_loc_days = dtz::time_point_cast<dtz::days>(zon_loc_time_point);

    EXPECT_EQ(zon_loc_days, loc_days);
    EXPECT_EQ(zon_loc_time_point - zon_loc_days, 0s);
  }

  // template <typename Zone, UnsafeZonedLocalTime FromUnsafeZonedLocalTime>
  // auto make_zoned(Zone&& zone, const FromUnsafeZonedLocalTime& tp, choose choose)
  {
    const auto zon_days = dtz::make_zoned(loc_zone, loc_time_point, dtz::choose::earliest);

    const auto zon_loc_time_point = zon_days.get_local_time();
    const auto zon_loc_days = dtz::time_point_cast<dtz::days>(zon_loc_time_point);

    EXPECT_EQ(zon_loc_days, loc_days);
    EXPECT_EQ(zon_loc_time_point - zon_loc_days, 3h + 0ms);
  }

  // template <typename Zone, TimePoint FromTimePoint>
  // auto make_zoned(Zone&& zone, const FromTimePoint& tp)
  {
    const auto zon_days = dtz::make_zoned(loc_zone, sys_time_point);

    const auto zon_loc_time_point = zon_days.get_local_time();
    const auto zon_loc_days = dtz::time_point_cast<dtz::days>(zon_loc_time_point);

    EXPECT_EQ(zon_loc_days, loc_days);
    EXPECT_EQ(zon_loc_time_point - zon_loc_days, hms + 2h);
  }
}

TEST(dtz, cast) {
  const auto ymd = dtz::year{ 1971 } / dtz::month{ 1 } / dtz::day{ 1 };
  const auto loc = dtz::local_days{ ymd };
  const auto sys = dtz::sys_days{ ymd };
  const auto utc = dtz::utc_clock::from_sys(sys);
  const auto tai = dtz::tai_clock::from_utc(utc);
  const auto gps = dtz::gps_clock::from_utc(utc);

  // template <Duration ToDuration, Duration FromDuration>
  // auto cast(const FromDuration& d)
  static_assert(std::is_same_v<decltype(dtz::cast<dtz::milliseconds>(90s)), dtz::milliseconds>);
  EXPECT_EQ(dtz::cast<dtz::milliseconds>(90s), 90000ms);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::seconds>(90s)), dtz::seconds>);
  EXPECT_EQ(dtz::cast<dtz::seconds>(90s), 90000ms);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::minutes>(90s)), dtz::minutes>);
  EXPECT_EQ(dtz::cast<dtz::minutes>(90s), 60000ms);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::minutes>(-90s)), dtz::minutes>);
  EXPECT_EQ(dtz::cast<dtz::minutes>(-90s), -60000ms);

  // template <Duration ToDuration, TimePointOrLocalTime FromTimePointOrLocalTime>
  // auto cast(const FromTimePointOrLocalTime& tp)
  static_assert(std::is_same_v<decltype(dtz::cast<dtz::milliseconds>(loc + 90s)), dtz::local_time<dtz::milliseconds>>);
  EXPECT_EQ(dtz::cast<dtz::milliseconds>(loc + 90s), loc + 90000ms);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::milliseconds>(sys + 90s)), dtz::sys_time<dtz::milliseconds>>);
  EXPECT_EQ(dtz::cast<dtz::milliseconds>(sys + 90s), sys + 90000ms);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::seconds>(loc + 90s)), dtz::local_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::seconds>(loc + 90s), loc + 90000ms);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::seconds>(sys + 90s)), dtz::sys_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::seconds>(sys + 90s), sys + 90000ms);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::minutes>(loc + 90s)), dtz::local_time<dtz::minutes>>);
  EXPECT_EQ(dtz::cast<dtz::minutes>(loc + 90s), loc + 60000ms);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::minutes>(sys + 90s)), dtz::sys_time<dtz::minutes>>);
  EXPECT_EQ(dtz::cast<dtz::minutes>(sys + 90s), sys + 60000ms);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::hours>(sys + 90s)), dtz::sys_time<dtz::hours>>);
  EXPECT_EQ(dtz::cast<dtz::hours>(sys + 90s), sys);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::days>(sys + 90s)), dtz::sys_time<dtz::days>>);
  EXPECT_EQ(dtz::cast<dtz::days>(sys + 90s), dtz::sys_days{ sys });

  // template <ValidZonedTimeDuration ToValidZonedTimeDuration, ZonedTime FromZonedTime>
  // auto cast(const FromZonedTime& zt)
  const auto zon = dtz::make_zoned(dtz::locate_zone("Europe/Berlin"), loc + 90s, dtz::choose::earliest);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::milliseconds>(zon)), dtz::zoned_time<dtz::milliseconds>>);
  {
    const auto zon_time_point = dtz::cast<dtz::milliseconds>(zon);
    const auto zon_loc_time_point = zon_time_point.get_local_time();
    const auto zon_loc_days = dtz::cast<dtz::days>(zon_loc_time_point);
    EXPECT_EQ(zon_loc_days, loc);
    EXPECT_EQ(zon_loc_time_point - zon_loc_days, 90000ms);
  }

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::seconds>(zon)), dtz::zoned_time<dtz::seconds>>);
  {
    const auto zon_time_point = dtz::cast<dtz::seconds>(zon);
    const auto zon_loc_time_point = zon_time_point.get_local_time();
    const auto zon_loc_days = dtz::cast<dtz::days>(zon_loc_time_point);
    EXPECT_EQ(zon_loc_days, loc);
    EXPECT_EQ(zon_loc_time_point - zon_loc_days, 90000ms);
  }

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::minutes>(zon)), dtz::zoned_time<dtz::minutes>>);
  {
    const auto zon_time_point = dtz::cast<dtz::minutes>(zon);
    const auto zon_loc_time_point = zon_time_point.get_local_time();
    const auto zon_loc_days = dtz::cast<dtz::days>(zon_loc_time_point);
    EXPECT_EQ(zon_loc_days, loc);
    EXPECT_EQ(zon_loc_time_point - zon_loc_days, 60000ms);
  }

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::hours>(zon)), dtz::zoned_time<dtz::hours>>);
  {
    const auto zon_time_point = dtz::cast<dtz::hours>(zon);
    const auto zon_loc_time_point = zon_time_point.get_local_time();
    const auto zon_loc_days = dtz::cast<dtz::days>(zon_loc_time_point);
    EXPECT_EQ(zon_loc_days, loc);
    EXPECT_EQ(zon_loc_time_point - zon_loc_days, 0ms);
  }

  // template <ClockOrLocal ToClockOrLocal, TimePointOrLocalTime FromTimePointOrLocalTime>
  // auto cast(const FromTimePointOrLocalTime& tp)
  static_assert(std::is_same_v<decltype(dtz::cast<dtz::system_clock>(loc + 90s)), dtz::sys_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::system_clock>(loc + 90s), sys + 90s);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::system_clock>(sys + 90s)), dtz::sys_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::system_clock>(sys + 90s), sys + 90s);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::utc_clock>(loc + 90s)), dtz::utc_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::utc_clock>(loc + 90s), utc + 90s);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::utc_clock>(sys + 90s)), dtz::utc_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::utc_clock>(sys + 90s), utc + 90s);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::tai_clock>(loc + 90s)), dtz::tai_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::tai_clock>(loc + 90s), tai + 80s);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::tai_clock>(sys + 90s)), dtz::tai_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::tai_clock>(sys + 90s), tai + 90s);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::gps_clock>(loc + 90s)), dtz::gps_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::gps_clock>(loc + 90s), gps + 99s);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::gps_clock>(sys + 90s)), dtz::gps_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::gps_clock>(sys + 90s), gps + 90s);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::local_t>(loc + 90s)), dtz::local_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::local_t>(loc + 90s), loc + 90s);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::local_t>(sys + 90s)), dtz::local_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::local_t>(sys + 90s), loc + 90s);

  // template <Local ToLocal, ZonedTime FromZonedTime>
  // auto cast(const FromZonedTime& tp)
  static_assert(std::is_same_v<decltype(dtz::cast<dtz::local_t>(zon)), dtz::local_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::local_t>(zon), loc + 90s);

  // template <Clock ToClock, ZonedTime FromZonedTime>
  // auto cast(const FromZonedTime& tp)
  static_assert(std::is_same_v<decltype(dtz::cast<dtz::system_clock>(zon)), dtz::sys_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::system_clock>(zon), sys + 90s - 1h);

  // template <Duration ToDuration, Duration FromDuration>
  // auto cast(const hh_mm_ss<FromDuration>& hms)
  constexpr auto hms = dtz::hh_mm_ss<dtz::seconds>{ 1h + 1min + 1s };

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::milliseconds>(hms)), dtz::milliseconds>);
  EXPECT_EQ(dtz::cast<dtz::milliseconds>(hms), 1h + 1min + 1s + 0ms);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::seconds>(hms)), dtz::seconds>);
  EXPECT_EQ(dtz::cast<dtz::seconds>(hms), 1h + 1min + 1s);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::minutes>(hms)), dtz::minutes>);
  EXPECT_EQ(dtz::cast<dtz::minutes>(hms), 1h + 1min);

  // template <Duration ToDuration>
  // auto cast(const year_month_day& ymd)
  static_assert(std::is_same_v<decltype(dtz::cast<dtz::milliseconds>(ymd)), dtz::local_time<dtz::milliseconds>>);
  EXPECT_EQ(dtz::cast<dtz::milliseconds>(ymd), dtz::local_days{ ymd } + 0ms);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::seconds>(ymd)), dtz::local_time<dtz::seconds>>);
  EXPECT_EQ(dtz::cast<dtz::seconds>(ymd), dtz::local_days{ ymd } + 0s);

  static_assert(std::is_same_v<decltype(dtz::cast<dtz::minutes>(ymd)), dtz::local_time<dtz::minutes>>);
  EXPECT_EQ(dtz::cast<dtz::minutes>(ymd), dtz::local_days{ ymd } + 0min);
}

TEST(dtz, ymd) {
  const auto ymd = dtz::year{ 1971 } / dtz::month{ 1 } / dtz::day{ 1 };
  const auto loc = dtz::local_days{ ymd };
  const auto sys = dtz::sys_days{ ymd };
  const auto zon = dtz::make_zoned(dtz::locate_zone("Europe/Berlin"), loc + 90s, dtz::choose::earliest);

  // template <LocalTime FromLocalTime>
  // auto ymd(const FromLocalTime& tp)
  static_assert(std::is_same_v<decltype(dtz::ymd(loc)), dtz::year_month_day>);
  EXPECT_EQ(dtz::ymd(loc), ymd);

  // template <TimePoint FromTimePoint>
  // auto ymd(const FromTimePoint& tp)
  static_assert(std::is_same_v<decltype(dtz::ymd(sys)), dtz::year_month_day>);
  EXPECT_EQ(dtz::ymd(sys), ymd);
}

TEST(dtz, hms) {
  const auto ymd = dtz::year{ 1971 } / dtz::month{ 1 } / dtz::day{ 1 };
  const auto loc = dtz::local_days{ ymd };
  const auto sys = dtz::sys_days{ ymd };
  const auto utc = dtz::utc_clock::from_sys(sys);
  const auto tai = dtz::tai_clock::from_utc(utc);
  const auto gps = dtz::gps_clock::from_utc(utc);
  const auto zon = dtz::make_zoned(dtz::locate_zone("Europe/Berlin"), loc + 0h);

  // template <ValidHHMMSSDuration FromValidHHMMSSDuration>
  // auto hms(const FromValidHHMMSSDuration& d)
  static_assert(std::is_same_v<decltype(dtz::hms(90ms)), dtz::hh_mm_ss<dtz::milliseconds>>);
  static_assert(std::is_same_v<decltype(dtz::hms(90s)), dtz::hh_mm_ss<dtz::seconds>>);
  static_assert(std::is_same_v<decltype(dtz::hms(90min)), dtz::hh_mm_ss<dtz::minutes>>);
  static_assert(std::is_same_v<decltype(dtz::hms(90h)), dtz::hh_mm_ss<dtz::hours>>);

  EXPECT_EQ(dtz::hms(1h + 1min + 1s + 1ms).hours(), 1h);
  EXPECT_EQ(dtz::hms(1h + 1min + 1s + 1ms).minutes(), 1min);
  EXPECT_EQ(dtz::hms(1h + 1min + 1s + 1ms).seconds(), 1s);
  EXPECT_EQ(dtz::hms(1h + 1min + 1s + 1ms).subseconds(), 1ms);

  EXPECT_EQ(dtz::hms(1h + 1min + 1s).hours(), 1h);
  EXPECT_EQ(dtz::hms(1h + 1min + 1s).minutes(), 1min);
  EXPECT_EQ(dtz::hms(1h + 1min + 1s).seconds(), 1s);
  EXPECT_EQ(dtz::hms(1h + 1min + 1s).subseconds(), 0ms);

  EXPECT_EQ(dtz::hms(1h + 1min).hours(), 1h);
  EXPECT_EQ(dtz::hms(1h + 1min).minutes(), 1min);
  EXPECT_EQ(dtz::hms(1h + 1min).seconds(), 0s);
  EXPECT_EQ(dtz::hms(1h + 1min).subseconds(), 0ms);

  EXPECT_EQ(dtz::hms(1h).hours(), 1h);
  EXPECT_EQ(dtz::hms(1h).minutes(), 0min);
  EXPECT_EQ(dtz::hms(1h).seconds(), 0s);
  EXPECT_EQ(dtz::hms(1h).subseconds(), 0ms);

  EXPECT_EQ(dtz::hms(-(1h + 1min + 1s + 1ms)).hours(), 1h);
  EXPECT_EQ(dtz::hms(-(1h + 1min + 1s + 1ms)).minutes(), 1min);
  EXPECT_EQ(dtz::hms(-(1h + 1min + 1s + 1ms)).seconds(), 1s);
  EXPECT_EQ(dtz::hms(-(1h + 1min + 1s + 1ms)).subseconds(), 1ms);

  EXPECT_EQ(dtz::hms(25h + 61min + 61s + 1001ms).hours(), 26h);
  EXPECT_EQ(dtz::hms(25h + 61min + 61s + 1001ms).minutes(), 2min);
  EXPECT_EQ(dtz::hms(25h + 61min + 61s + 1001ms).seconds(), 2s);
  EXPECT_EQ(dtz::hms(25h + 61min + 61s + 1001ms).subseconds(), 1ms);

  // template <ClockOrLocal FromClockOrLocal, ValidHHMMSSDuration FromValidHHMMSSDuration>
  // auto hms(const time_point<FromClockOrLocal, FromValidHHMMSSDuration>& tp)
  static_assert(std::is_same_v<decltype(dtz::hms(loc + 90ms)), dtz::hh_mm_ss<dtz::milliseconds>>);
  static_assert(std::is_same_v<decltype(dtz::hms(loc + 90s)), dtz::hh_mm_ss<dtz::seconds>>);
  static_assert(std::is_same_v<decltype(dtz::hms(loc + 90min)), dtz::hh_mm_ss<dtz::minutes>>);
  static_assert(std::is_same_v<decltype(dtz::hms(loc + 90h)), dtz::hh_mm_ss<dtz::hours>>);

  EXPECT_EQ(dtz::hms(loc + 1h + 1min + 1s + 1ms).hours(), 1h);
  EXPECT_EQ(dtz::hms(loc + 1h + 1min + 1s + 1ms).minutes(), 1min);
  EXPECT_EQ(dtz::hms(loc + 1h + 1min + 1s + 1ms).seconds(), 1s);
  EXPECT_EQ(dtz::hms(loc + 1h + 1min + 1s + 1ms).subseconds(), 1ms);

  static_assert(std::is_same_v<decltype(dtz::hms(sys + 90ms)), dtz::hh_mm_ss<dtz::milliseconds>>);
  static_assert(std::is_same_v<decltype(dtz::hms(sys + 90s)), dtz::hh_mm_ss<dtz::seconds>>);
  static_assert(std::is_same_v<decltype(dtz::hms(sys + 90min)), dtz::hh_mm_ss<dtz::minutes>>);
  static_assert(std::is_same_v<decltype(dtz::hms(sys + 90h)), dtz::hh_mm_ss<dtz::hours>>);

  EXPECT_EQ(dtz::hms(sys + 1h + 1min + 1s + 1ms).hours(), 1h);
  EXPECT_EQ(dtz::hms(sys + 1h + 1min + 1s + 1ms).minutes(), 1min);
  EXPECT_EQ(dtz::hms(sys + 1h + 1min + 1s + 1ms).seconds(), 1s);
  EXPECT_EQ(dtz::hms(sys + 1h + 1min + 1s + 1ms).subseconds(), 1ms);

  static_assert(std::is_same_v<decltype(dtz::hms(utc + 90ms)), dtz::hh_mm_ss<dtz::milliseconds>>);
  static_assert(std::is_same_v<decltype(dtz::hms(utc + 90s)), dtz::hh_mm_ss<dtz::seconds>>);

  EXPECT_EQ(dtz::hms(utc + 1h + 1min + 1s + 1ms).hours(), 1h);
  EXPECT_EQ(dtz::hms(utc + 1h + 1min + 1s + 1ms).minutes(), 1min);
  EXPECT_EQ(dtz::hms(utc + 1h + 1min + 1s + 1ms).seconds(), 1s);
  EXPECT_EQ(dtz::hms(utc + 1h + 1min + 1s + 1ms).subseconds(), 1ms);

  static_assert(std::is_same_v<decltype(dtz::hms(tai + 90ms)), dtz::hh_mm_ss<dtz::milliseconds>>);
  static_assert(std::is_same_v<decltype(dtz::hms(tai + 90s)), dtz::hh_mm_ss<dtz::seconds>>);

  EXPECT_EQ(dtz::hms(tai + 1h + 1min + 1s + 1ms).hours(), 1h);
  EXPECT_EQ(dtz::hms(tai + 1h + 1min + 1s + 1ms).minutes(), 1min);
  EXPECT_EQ(dtz::hms(tai + 1h + 1min + 1s + 1ms).seconds(), 11s);
  EXPECT_EQ(dtz::hms(tai + 1h + 1min + 1s + 1ms).subseconds(), 1ms);

  static_assert(std::is_same_v<decltype(dtz::hms(gps + 90ms)), dtz::hh_mm_ss<dtz::milliseconds>>);
  static_assert(std::is_same_v<decltype(dtz::hms(gps + 90s)), dtz::hh_mm_ss<dtz::seconds>>);

  EXPECT_EQ(dtz::hms(gps + 1h + 1min + 1s + 1ms).hours(), 22h);
  EXPECT_EQ(dtz::hms(gps + 1h + 1min + 1s + 1ms).minutes(), 59min);
  EXPECT_EQ(dtz::hms(gps + 1h + 1min + 1s + 1ms).seconds(), 7s);
  EXPECT_EQ(dtz::hms(gps + 1h + 1min + 1s + 1ms).subseconds(), 999ms);

  // template <ValidHHMMSSDuration FromValidHHMMSSDuration>
  // auto hms(const zoned_time<FromValidHHMMSSDuration>& zt)
  static_assert(std::is_same_v<decltype(dtz::hms(zon + 90ms)), dtz::hh_mm_ss<dtz::milliseconds>>);
  static_assert(std::is_same_v<decltype(dtz::hms(zon + 90s)), dtz::hh_mm_ss<dtz::seconds>>);
  static_assert(std::is_same_v<decltype(dtz::hms(zon + 90min)), dtz::hh_mm_ss<dtz::minutes>>);
  static_assert(std::is_same_v<decltype(dtz::hms(zon + 90h)), dtz::hh_mm_ss<dtz::hours>>);

  EXPECT_EQ(dtz::hms(zon + 1h + 1min + 1s + 1ms).hours(), 1h);
  EXPECT_EQ(dtz::hms(zon + 1h + 1min + 1s + 1ms).minutes(), 1min);
  EXPECT_EQ(dtz::hms(zon + 1h + 1min + 1s + 1ms).seconds(), 1s);
  EXPECT_EQ(dtz::hms(zon + 1h + 1min + 1s + 1ms).subseconds(), 1ms);
}

TEST(dtz, now) {
  const auto zone = dtz::locate_zone("UTC");
  ASSERT_TRUE(zone);

  // auto now()
  static_assert(std::is_same_v<decltype(dtz::now()), dtz::system_clock::time_point>);

  // template <Clock Clock>
  // auto now()
  static_assert(std::is_same_v<decltype(dtz::now<dtz::system_clock>()), dtz::system_clock::time_point>);
  static_assert(std::is_same_v<decltype(dtz::now<dtz::utc_clock>()), dtz::utc_clock::time_point>);
  static_assert(std::is_same_v<decltype(dtz::now<dtz::tai_clock>()), dtz::tai_clock::time_point>);
  static_assert(std::is_same_v<decltype(dtz::now<dtz::gps_clock>()), dtz::gps_clock::time_point>);

  // template <Duration Duration>
  // auto now()
  static_assert(std::is_same_v<decltype(dtz::now<dtz::milliseconds>()), dtz::sys_time<dtz::milliseconds>>);
  static_assert(std::is_same_v<decltype(dtz::now<dtz::seconds>()), dtz::sys_time<dtz::seconds>>);
  static_assert(std::is_same_v<decltype(dtz::now<dtz::minutes>()), dtz::sys_time<dtz::minutes>>);
  static_assert(std::is_same_v<decltype(dtz::now<dtz::hours>()), dtz::sys_time<dtz::hours>>);
  static_assert(std::is_same_v<decltype(dtz::now<dtz::days>()), dtz::sys_time<dtz::days>>);

  // auto now(const time_zone* zone)
  static_assert(std::is_same_v<decltype(dtz::now(zone)), dtz::zoned_time<dtz::system_clock::duration>>);

  // auto now(std::string_view zone)
  static_assert(std::is_same_v<decltype(dtz::now("Europe/Berlin")), dtz::zoned_time<dtz::system_clock::duration>>);

  // template <Duration Duration>
  // auto now(const time_zone* zone)
  static_assert(std::is_same_v<decltype(dtz::now<dtz::milliseconds>(zone)), dtz::zoned_time<dtz::milliseconds>>);
  static_assert(std::is_same_v<decltype(dtz::now<dtz::seconds>(zone)), dtz::zoned_time<dtz::seconds>>);
  static_assert(std::is_same_v<decltype(dtz::now<dtz::minutes>(zone)), dtz::zoned_time<dtz::minutes>>);
  static_assert(std::is_same_v<decltype(dtz::now<dtz::hours>(zone)), dtz::zoned_time<dtz::hours>>);

  // template <Duration Duration>
  // auto now(std::string_view zone)
  static_assert(std::is_same_v<decltype(dtz::now<dtz::milliseconds>("Europe/Berlin")), dtz::zoned_time<dtz::milliseconds>>);
  static_assert(std::is_same_v<decltype(dtz::now<dtz::seconds>("Europe/Berlin")), dtz::zoned_time<dtz::seconds>>);
  static_assert(std::is_same_v<decltype(dtz::now<dtz::minutes>("Europe/Berlin")), dtz::zoned_time<dtz::minutes>>);
  static_assert(std::is_same_v<decltype(dtz::now<dtz::hours>("Europe/Berlin")), dtz::zoned_time<dtz::hours>>);
}

TEST(dtz, weekday_operators) {
  static_assert(dtz::mon < dtz::tue);
  static_assert(dtz::tue < dtz::wed);
  static_assert(dtz::wed < dtz::thu);
  static_assert(dtz::thu < dtz::fri);
  static_assert(dtz::fri < dtz::sat);
  static_assert(dtz::sat < dtz::sun);

  static_assert(dtz::tue > dtz::mon);
  static_assert(dtz::wed > dtz::tue);
  static_assert(dtz::thu > dtz::wed);
  static_assert(dtz::fri > dtz::thu);
  static_assert(dtz::sat > dtz::fri);
  static_assert(dtz::sun > dtz::sat);

  static_assert(dtz::mon <= dtz::tue);
  static_assert(dtz::tue <= dtz::wed);
  static_assert(dtz::wed <= dtz::thu);
  static_assert(dtz::thu <= dtz::fri);
  static_assert(dtz::fri <= dtz::sat);
  static_assert(dtz::sat <= dtz::sun);

  static_assert(dtz::tue >= dtz::mon);
  static_assert(dtz::wed >= dtz::tue);
  static_assert(dtz::thu >= dtz::wed);
  static_assert(dtz::fri >= dtz::thu);
  static_assert(dtz::sat >= dtz::fri);
  static_assert(dtz::sun >= dtz::sat);
}

TEST(dtz, hh_mm_ss_operators) {
  static_assert(dtz::hms(1h) < dtz::hms(1h + 1ns));
  static_assert(dtz::hms(1h + 1ns) > dtz::hms(1h));

  static_assert(dtz::hms(1h) <= dtz::hms(1h + 1ns));
  static_assert(dtz::hms(1h + 1ns) >= dtz::hms(1h));

  static_assert(dtz::hms(1h) == dtz::hms(60min));
  static_assert(dtz::hms(1h) == dtz::hms(60min));
}

TEST(dtz, zoned_time_operators) {
  {
    const auto ymd = dtz::year{ 2018 } / dtz::month{ 3 } / dtz::day{ 25 };
    const auto hms = 1h + 30min;
    const auto zon = dtz::make_zoned("Europe/Berlin", dtz::local_days{ ymd } + hms, dtz::choose::earliest);
    EXPECT_EQ(zon.get_local_time() - dtz::make_zoned("UTC", zon.get_sys_time()).get_local_time(), 1h);
    EXPECT_EQ(dtz::hms(zon + 1h).to_duration(), 3h + 30min);
    EXPECT_EQ(dtz::hms((zon + 1h) - 1h).to_duration(), 1h + 30min);
  }
  {
    const auto ymd = dtz::year{ 2018 } / dtz::month{ 10 } / dtz::day{ 28 };
    const auto hms = 1h + 30min;
    const auto zon = dtz::make_zoned("Europe/Berlin", dtz::local_days{ ymd } + hms, dtz::choose::earliest);
    ASSERT_EQ(zon, dtz::make_zoned("Europe/Berlin", dtz::local_days{ ymd } + hms, dtz::choose::latest));
    EXPECT_EQ(zon.get_local_time() - dtz::make_zoned("UTC", zon.get_sys_time()).get_local_time(), 2h);
    EXPECT_EQ(dtz::hms(zon + 1h).to_duration(), 2h + 30min);
    EXPECT_EQ(dtz::hms(zon + 2h).to_duration(), 2h + 30min);
    EXPECT_EQ(dtz::hms((zon + 1h) - 1h).to_duration(), 1h + 30min);
    EXPECT_EQ(dtz::hms((zon + 2h) - 2h).to_duration(), 1h + 30min);
  }
}
#endif
