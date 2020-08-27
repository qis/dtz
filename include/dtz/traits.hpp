#pragma once
#include "chrono.hpp"
#include <array>

namespace dtz {

template <typename Rep, typename LHS, typename RHS>
concept FormatDuration = std::ratio_less_v<LHS, RHS> || (std::is_floating_point_v<Rep> && std::ratio_less_equal_v<LHS, RHS>);

template <typename T>
struct traits {
  static constexpr std::size_t buffer_size = 0;
};

template <Duration Duration>
struct traits<Duration> {
  // 24 | -0000:00:00.000000000
  static constexpr std::size_t buffer_size = 24;
};

template <LocalTime LocalTime>
struct traits<LocalTime> {
  // clang-format off
  // 29 | 0000-00-00 00:00:00.000000000
  // 26 | 0000-00-00 00:00:00.000000
  // 23 | 0000-00-00 00:00:00.000
  // 19 | 0000-00-00 00:00:00
  // 16 | 0000-00-00 00:00
  static constexpr std::size_t buffer_size =
    std::ratio_less_equal_v<typename LocalTime::period, nanoseconds::period> ? 29 :
    std::ratio_less_equal_v<typename LocalTime::period, microseconds::period> ? 26 :
    std::ratio_less_equal_v<typename LocalTime::period, milliseconds::period> ? 23 :
    std::ratio_less_equal_v<typename LocalTime::period, seconds::period> ? 19 : 16;
  // clang-format on
};

template <TimePoint TimePoint>
struct traits<TimePoint> : traits<local_time<typename TimePoint::duration>> {};

template <ZonedTime ZonedTime>
struct traits<ZonedTime> : traits<local_time<typename is_zoned_time<ZonedTime>::duration>> {};

template <Duration Duration>
struct traits<hh_mm_ss<Duration>> {
  // clang-format off
  // 18 | 00:00:00.000000000
  // 15 | 00:00:00.000000
  // 12 | 00:00:00.000
  //  8 | 00:00:00
  //  5 | 00:00
  static constexpr std::size_t buffer_size =
    std::ratio_less_equal_v<typename Duration::period, nanoseconds::period> ? 18 :
    std::ratio_less_equal_v<typename Duration::period, microseconds::period> ? 15 :
    std::ratio_less_equal_v<typename Duration::period, milliseconds::period> ? 12 :
    std::ratio_less_equal_v<typename Duration::period, seconds::period> ? 8 : 5;
  // clang-format on
};

template <>
struct traits<day> {
  //  2 | 00
  static constexpr std::size_t buffer_size = 2;
};

template <>
struct traits<month> {
  //  3 | Jan
  static constexpr std::size_t buffer_size = 3;
  static constexpr std::array<const char*, 12> names = {
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec",
  };
};

template <>
struct traits<year> {
  //  4 | 0000
  static constexpr std::size_t buffer_size = 4;
};

template <>
struct traits<weekday> {
  //  3 | Sun
  static constexpr std::size_t buffer_size = 3;
  static constexpr std::array<const char*, 7> names = {
    "Sun",
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat",
  };
};

template <>
struct traits<weekday_indexed> {
  //  6 | Sun[1]
  static constexpr std::size_t buffer_size = 6;
};

template <>
struct traits<weekday_last> {
  //  9 | Sun[last]
  static constexpr std::size_t buffer_size = 9;
};

template <>
struct traits<month_day> {
  //  6 | Jan/01
  static constexpr std::size_t buffer_size = 6;
};

template <>
struct traits<month_day_last> {
  //  8 | Jan/last
  static constexpr std::size_t buffer_size = 8;
};

template <>
struct traits<month_weekday> {
  // 10 | Jan/Sun[1]
  static constexpr std::size_t buffer_size = 10;
};

template <>
struct traits<month_weekday_last> {
  // 13 | Jan/Sun[last]
  static constexpr std::size_t buffer_size = 13;
};

template <>
struct traits<year_month> {
  //  7 | 0000-00
  static constexpr std::size_t buffer_size = 7;
};

template <>
struct traits<year_month_day> {
  // 10 | 0000-00-00
  static constexpr std::size_t buffer_size = 10;
};

template <>
struct traits<year_month_day_last> {
  // 12 | 0000-00/last
  static constexpr std::size_t buffer_size = 12;
};

template <>
struct traits<year_month_weekday> {
  // 14 | 2019-02/Tue[1]
  static constexpr std::size_t buffer_size = 14;
};

template <>
struct traits<year_month_weekday_last> {
  // 17 | 2019-02/Tue[last]
  static constexpr std::size_t buffer_size = 17;
};

template <typename T>
concept Format = traits<T>::buffer_size > 0;

}  // namespace dtz
