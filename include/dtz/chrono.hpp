#pragma once
#include <date/date.h>
#include <date/tz.h>
#include <chrono>
#include <string_view>
#include <type_traits>

namespace dtz {

// clang-format off

// ====================================================================================================================
// Clock
// ====================================================================================================================

using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::high_resolution_clock;

using date::utc_clock;
using date::tai_clock;
using date::gps_clock;


using date::is_clock;

template <typename T>
inline constexpr bool is_clock_v = is_clock<T>::value;

template <typename T>
concept Clock = is_clock_v<T>;


// ====================================================================================================================
// Local
// ====================================================================================================================

using date::local_t;


template <typename T>
struct is_local : std::false_type {};

template <>
struct is_local<local_t> : std::true_type {};

template <typename T>
inline constexpr bool is_local_v = is_local<T>::value;

template <typename T>
concept Local = is_local_v<T>;


// ====================================================================================================================
// ClockOrLocal
// ====================================================================================================================

template <typename T>
concept ClockOrLocal = (Clock<T> || Local<T>);


// ====================================================================================================================
// Duration
// ====================================================================================================================

using std::chrono::duration;

using std::chrono::nanoseconds;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::minutes;
using std::chrono::hours;

using date::days;
using date::weeks;
using date::months;
using date::years;

using std::chrono::duration_values;
using std::chrono::treat_as_floating_point;


template <typename T>
struct is_duration : std::false_type {};

template <typename Rep, typename Period>
struct is_duration<duration<Rep, Period>> : std::true_type {};

template <typename T>
inline constexpr bool is_duration_v = is_duration<T>::value;

template <typename T>
concept Duration = is_duration_v<T>;


// ====================================================================================================================
// TimePoint
// ====================================================================================================================

using std::chrono::time_point;

using date::sys_time;
using date::sys_days;

using date::utc_time;
using date::tai_time;
using date::gps_time;


template <typename T>
struct is_time_point : std::false_type {};

template <Clock Clock, Duration Duration>
struct is_time_point<time_point<Clock, Duration>> : std::true_type {};

template <typename T>
inline constexpr bool is_time_point_v = is_time_point<T>::value;

template <typename T>
concept TimePoint = is_time_point_v<T>;


// ====================================================================================================================
// LocalTime
// ====================================================================================================================

using date::local_time;
using date::local_days;


template <typename T>
struct is_local_time : std::false_type {};

template <Local Local, Duration Duration>
struct is_local_time<time_point<Local, Duration>> : std::true_type {};

template <typename T>
inline constexpr bool is_local_time_v = is_local_time<T>::value;

template <typename T>
concept LocalTime = is_local_time_v<T>;


// ====================================================================================================================
// TimePointOrLocalTime
// ====================================================================================================================

template <typename T>
concept TimePointOrLocalTime = (TimePoint<T> || LocalTime<T>);


// ====================================================================================================================
// TimeZone
// ====================================================================================================================

using date::time_zone;


template <typename T>
struct is_time_zone : std::false_type {};

template <>
struct is_time_zone<time_zone> : std::true_type {};

template <typename T>
inline constexpr bool is_time_zone_v = is_time_zone<T>::value;

template <typename T>
concept TimeZone = is_time_zone_v<T>;


template <typename T>
struct is_time_zone_ptr {
  static constexpr bool value = std::is_pointer_v<T> && is_time_zone_v<std::remove_cv_t<std::remove_pointer_t<T>>>;
};

template <typename T>
inline constexpr bool is_time_zone_ptr_v = is_time_zone_ptr<T>::value;

template <typename T>
concept TimeZonePtr = is_time_zone_ptr_v<T>;


// ====================================================================================================================
// TimeZone Database
// ====================================================================================================================

using date::tzdb;
using date::tzdb_list;

using date::get_tzdb;
using date::get_tzdb_list;

#ifdef _WIN32
using date::reload_tzdb;
#else
inline const tzdb& reload_tzdb() {
  return get_tzdb();
}
#endif

using date::locate_zone;
using date::current_zone;

using date::sys_info;
using date::local_info;
using date::leap_second;


// ====================================================================================================================
// ZonedTime
// ====================================================================================================================

using date::zoned_time;

using date::zoned_traits;

using date::ambiguous_local_time;
using date::nonexistent_local_time;
using date::choose;


template <typename T>
struct is_zoned_time : std::false_type {};

template <Duration Duration, TimeZonePtr TimeZonePtr>
struct is_zoned_time<zoned_time<Duration, TimeZonePtr>> {
  using duration = Duration;
  static constexpr bool value = std::ratio_less_v<typename duration::period, days::period>;
};

template <typename T>
inline constexpr bool is_zoned_time_v = is_zoned_time<T>::value;

template <typename T>
concept ZonedTime = is_zoned_time_v<T>;


template <typename T>
concept SafeZonedLocalTime = (LocalTime<T> &&
  std::ratio_less_v<typename T::period, days::period> &&
  std::ratio_greater_equal_v<typename T::duration::period, hours::period>);

template <typename T>
concept UnsafeZonedLocalTime = (LocalTime<T> &&
  std::ratio_less_v<typename T::duration::period, hours::period>);

template <typename T>
concept ValidZonedTimeDuration = ZonedTime<zoned_time<T>>;


template <SafeZonedLocalTime FromSafeZonedLocalTime>
[[nodiscard]] inline constexpr auto make_zoned(const time_zone* zone, const FromSafeZonedLocalTime& zt) noexcept {
  return zoned_time<typename FromSafeZonedLocalTime::duration>{ zone, zt, choose::earliest };
}

template <SafeZonedLocalTime FromSafeZonedLocalTime>
[[nodiscard]] inline constexpr auto make_zoned(std::string_view zone, const FromSafeZonedLocalTime& zt) {
  return dtz::make_zoned(locate_zone(zone), zt);
}

template <UnsafeZonedLocalTime FromUnsafeZonedLocalTime>
[[nodiscard]] inline constexpr auto make_zoned(const time_zone* zone, const FromUnsafeZonedLocalTime& zt, choose choose) noexcept {
  return zoned_time<typename FromUnsafeZonedLocalTime::duration>{ zone, zt, choose };
}

template <UnsafeZonedLocalTime FromUnsafeZonedLocalTime>
[[nodiscard]] inline constexpr auto make_zoned(std::string_view zone, const FromUnsafeZonedLocalTime& zt, choose choose) {
  return dtz::make_zoned(locate_zone(zone), zt, choose);
}

template <Clock FromClock, ValidZonedTimeDuration FromValidZonedTimeDuration>
[[nodiscard]] inline constexpr auto make_zoned(const time_zone* zone, const time_point<FromClock, FromValidZonedTimeDuration>& tp) noexcept {
  return zoned_time<FromValidZonedTimeDuration>{ zone, tp };
}

template <Clock FromClock, ValidZonedTimeDuration FromValidZonedTimeDuration>
[[nodiscard]] inline constexpr auto make_zoned(std::string_view zone, const time_point<FromClock, FromValidZonedTimeDuration>& tp) {
  return dtz::make_zoned(locate_zone(zone), tp);
}


// ====================================================================================================================
// TimeOfDay
// ====================================================================================================================

using date::time_of_day;

template <typename T>
struct is_time_of_day : std::false_type {};

template <Duration Duration>
struct is_time_of_day<time_of_day<Duration>> {
  static constexpr bool value = std::ratio_less_v<typename Duration::period, days::period>;
};

template <typename T>
inline constexpr bool is_time_of_day_v = is_time_of_day<T>::value;

template <typename T>
concept TimeOfDay = is_time_of_day_v<T>;

template <typename T>
concept ValidTimeOfDayDuration = TimeOfDay<time_of_day<T>>;


// ====================================================================================================================
// Units
// ====================================================================================================================

using date::is_am;
using date::is_pm;
using date::make12;
using date::make24;

using date::day;
using date::month;
using date::year;
using date::weekday;
using date::weekday_indexed;
using date::weekday_last;
using date::month_day;
using date::month_day_last;
using date::month_weekday;
using date::month_weekday_last;
using date::year_month;
using date::year_month_day;
using date::year_month_day_last;
using date::year_month_weekday;
using date::year_month_weekday_last;

using date::last_spec;
using date::last;

using date::jan;
using date::feb;
using date::mar;
using date::apr;
using date::may;
using date::jun;
using date::jul;
using date::aug;
using date::sep;
using date::oct;
using date::nov;
using date::dec;

using date::sun;
using date::mon;
using date::tue;
using date::wed;
using date::thu;
using date::fri;
using date::sat;


// ====================================================================================================================
// Conversion
// ====================================================================================================================

using std::chrono::duration_cast;
using std::chrono::time_point_cast;

using date::clock_time_conversion;
using date::clock_cast;

using std::chrono::abs;
using std::chrono::ceil;
using std::chrono::floor;
using std::chrono::round;


template <Duration ToDuration, Duration FromDuration>
[[nodiscard]] inline constexpr auto cast(const FromDuration& d) {
  return duration_cast<ToDuration>(d);
}

template <Duration ToDuration, TimePointOrLocalTime FromTimePointOrLocalTime>
[[nodiscard]] inline constexpr auto cast(const FromTimePointOrLocalTime& tp) {
  return time_point_cast<ToDuration>(tp);
}

template <ValidZonedTimeDuration ToValidZonedTimeDuration, ZonedTime FromZonedTime>
[[nodiscard]] inline constexpr auto cast(const FromZonedTime& zt) {
  return zoned_time<ToValidZonedTimeDuration>{ zt.get_time_zone(), cast<ToValidZonedTimeDuration>(zt.get_sys_time()) };
}

template <ClockOrLocal ToClockOrLocal, TimePointOrLocalTime FromTimePointOrLocalTime>
[[nodiscard]] inline constexpr auto cast(const FromTimePointOrLocalTime& tp) {
  return clock_cast<ToClockOrLocal>(tp);
}

template <Local ToLocal, ZonedTime FromZonedTime>
[[nodiscard]] inline constexpr auto cast(const FromZonedTime& zt) {
  return zt.get_local_time();
}

template <Clock ToClock, ZonedTime FromZonedTime>
[[nodiscard]] inline constexpr auto cast(const FromZonedTime& zt) {
  return cast<ToClock>(zt.get_sys_time());
}

template <Duration ToDuration, Duration FromDuration>
[[nodiscard]] inline constexpr auto cast(const time_of_day<FromDuration>& tod) {
  return cast<ToDuration>(tod.to_duration());
}

template <Duration ToDuration>
[[nodiscard]] inline constexpr auto cast(const year_month_day& ymd) {
  return cast<ToDuration>(local_days{ ymd });
}


template <LocalTime FromLocalTime>
[[nodiscard]] inline constexpr auto ymd(const FromLocalTime& tp) {
  return year_month_day{ floor<days>(tp) };
}

template <TimePoint FromTimePoint>
[[nodiscard]] inline constexpr auto ymd(const FromTimePoint& tp) {
  return year_month_day{ floor<days>(cast<local_t>(tp)) };
}

template <ZonedTime FromZonedTime>
[[nodiscard]] inline constexpr auto ymd(const FromZonedTime& zt) {
  return year_month_day{ floor<days>(cast<local_t>(zt)) };
}


template <ValidTimeOfDayDuration FromValidTimeOfDayDuration>
[[nodiscard]] inline constexpr auto tod(const FromValidTimeOfDayDuration& d) {
  return time_of_day<FromValidTimeOfDayDuration>{ d };
}

template <ClockOrLocal FromClockOrLocal, ValidTimeOfDayDuration FromValidTimeOfDayDuration>
[[nodiscard]] inline constexpr auto tod(const time_point<FromClockOrLocal, FromValidTimeOfDayDuration>& tp) {
  return time_of_day<FromValidTimeOfDayDuration>{ tp - cast<days>(tp) };
}

template <ValidTimeOfDayDuration FromValidTimeOfDayDuration>
[[nodiscard]] inline constexpr auto tod(const zoned_time<FromValidTimeOfDayDuration>& zt) {
  return tod(cast<FromValidTimeOfDayDuration>(cast<local_t>(zt)));
}


// ====================================================================================================================
// Now
// ====================================================================================================================

[[nodiscard]] inline auto now() noexcept(noexcept(system_clock::now())) {
  return system_clock::now();
}

template <Clock Clock>
[[nodiscard]] inline auto now() noexcept(noexcept(Clock::now())) {
  return Clock::now();
}

template <Duration Duration>
[[nodiscard]] inline constexpr auto now() {
  return cast<Duration>(now());
}

[[nodiscard]] inline auto now(const time_zone* zone) noexcept(noexcept(date::make_zoned(zone, now()))) {
  return date::make_zoned(zone, now());
}

[[nodiscard]] inline auto now(std::string_view zone) {
  return date::make_zoned(locate_zone(zone), now());
}

template <ValidZonedTimeDuration Duration>
[[nodiscard]] inline constexpr auto now(const time_zone* zone) noexcept(noexcept(date::make_zoned(zone, now<Duration>()))) {
  return zoned_time<Duration>{ zone, now<Duration>() };
}

template <ValidZonedTimeDuration Duration>
[[nodiscard]] inline constexpr auto now(std::string_view zone) {
  return zoned_time<Duration>{ locate_zone(zone), now<Duration>() };
}


// clang-format on

// ====================================================================================================================
// Initialize
// ====================================================================================================================

bool initialize() noexcept;

inline static bool initialized = []() {
  return initialize();
}();

namespace literals {

using namespace std::chrono_literals;
using namespace date::literals;

}  // namespace literals
}  // namespace dtz

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

template <dtz::TimeOfDay LHS, dtz::TimeOfDay RHS>
[[nodiscard]] inline constexpr bool operator==(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() == rhs.to_duration();
}

template <dtz::TimeOfDay LHS, dtz::TimeOfDay RHS>
[[nodiscard]] inline constexpr bool operator<=(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() <= rhs.to_duration();
}

template <dtz::TimeOfDay LHS, dtz::TimeOfDay RHS>
[[nodiscard]] inline constexpr bool operator>=(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() >= rhs.to_duration();
}

template <dtz::TimeOfDay LHS, dtz::TimeOfDay RHS>
[[nodiscard]] inline constexpr bool operator<(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() < rhs.to_duration();
}

template <dtz::TimeOfDay LHS, dtz::TimeOfDay RHS>
[[nodiscard]] inline constexpr bool operator>(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() > rhs.to_duration();
}

template <dtz::ZonedTime ZonedTime, dtz::Duration FromDuration>
[[nodiscard]] inline constexpr auto operator+(const ZonedTime& zt, const FromDuration& d) noexcept {
  using ToDuration = std::common_type_t<FromDuration, typename dtz::is_zoned_time<ZonedTime>::duration>;
  return dtz::zoned_time<ToDuration>{ zt.get_time_zone(), dtz::cast<ToDuration>(zt.get_sys_time() + d) };
}

}  // namespace date