#pragma once
#include "chrono.hpp"
#include "error.hpp"
#include <charconv>
#include <string>
#include <system_error>

namespace dtz {

template <Duration Duration>
[[nodiscard]] inline Duration parse(std::string_view str, std::error_code& ec) noexcept {
  using Period = typename Duration::period;

  const char* beg = str.data();
  const char* const end = beg + str.size();

  // Parse negative sign.
  bool negative = false;
  if (*beg == '-') {
    negative = true;
    ++beg;
  }

  // Parse hours.
  hours::rep hv;  // NOLINT: Will be set by from_chars or not used on error.
  if (const auto [cur, err] = std::from_chars(beg, end, hv); err != std::errc{} || cur == end || *cur != ':') {
    ec = std::make_error_code(errc::invalid_hours_format);
    return {};
  } else {
    beg = cur + 1;
  }

  // Use absolute hours to initialize result.
  auto result = cast<Duration>(hours{ hv });

  // Get remaining string length.
  const auto size = end - beg;

  if constexpr (std::ratio_less_v<Period, hours::period>) {
    if (size > 1) {
      // Parse minutes.
      minutes::rep mv;  // NOLINT: Will be set by from_chars or not used on error.
      if (const auto [cur, err] = std::from_chars(beg, beg + 2, mv); err != std::errc{} || cur != beg + 2 || mv < 0 || mv > 59)
      {
        ec = std::make_error_code(errc::invalid_minutes_format);
        return {};
      } else {
        result += minutes{ mv };
        if (cur == end) {
          return negative ? -result : result;
        }
        if (*cur != ':') {
          ec = std::make_error_code(errc::invalid_format);
          return {};
        }
        beg = cur + 1;
      }

      if constexpr (std::ratio_less_v<Period, minutes::period>) {
        if (size > 4) {
          // Parse seconds.
          seconds::rep sv;  // NOLINT: Will be set by from_chars or not used on error.
          if (const auto [cur, err] = std::from_chars(beg, beg + 2, sv);
              err != std::errc{} || cur != beg + 2 || sv < 0 || sv > 59)
          {
            ec = std::make_error_code(errc::invalid_seconds_format);
            return {};
          } else {
            result += seconds{ sv };
            if (cur == end) {
              return negative ? -result : result;
            }
            if (*cur != '.') {
              ec = std::make_error_code(errc::invalid_format);
              return {};
            }
            beg = cur + 1;
          }

          if constexpr (std::ratio_less_v<Period, seconds::period>) {
            if (size > 6) {
              // Parse subseconds.
              int subseconds;  // NOLINT: Will be set by from_chars or not used on error.
              if (const auto [cur, err] = std::from_chars(beg, end, subseconds); err != std::errc{} || subseconds < 0) {
                ec = std::make_error_code(err);
                return {};
              } else if (cur != end) {
                ec = std::make_error_code(errc::invalid_subseconds_format);
                return {};
              }
              switch (size) {
              case 9:
                result += cast<Duration>(milliseconds{ subseconds });
                break;
              case 12:
                result += cast<Duration>(microseconds{ subseconds });
                break;
              case 15:
                result += cast<Duration>(nanoseconds{ subseconds });
                break;
              default:
                ec = std::make_error_code(errc::invalid_subseconds_format);
                return {};
              }
            }
          }
        }
      }
    }
  }

  return negative ? -result : result;
}

template <Duration Duration>
[[nodiscard]] inline Duration parse(std::string_view str) {
  std::error_code ec;
  const auto result = parse<Duration>(str, ec);
  if (ec) {
    throw std::system_error(ec, "could not parse duration");
  }
  return result;
}

template <TimePointOrLocalTime TimePointOrLocalTime>
[[nodiscard]] inline TimePointOrLocalTime parse(std::string_view str, std::error_code& ec) noexcept {
  // TODO: Allow 0000, 0000-00 and 0000-00-00 formats.
  // TODO: Use time_of_day instead of duration.
  using Duration = typename TimePointOrLocalTime::duration;
  using Period = typename TimePointOrLocalTime::period;

  const char* beg = str.data();
  const char* const end = beg + str.size();

  // Parse year.
  int iy;  // NOLINT: Will be set by from_chars or not used on error.
  if (const auto [cur, err] = std::from_chars(beg, end, iy); err != std::errc{} || cur == end || *cur != '-') {
    ec = std::make_error_code(errc::invalid_year_format);
    return {};
  } else {
    beg = cur + 1;
  }

  // Get remaining string length.
  const auto size = end - beg;

  if (size < 11) {
    ec = std::make_error_code(errc::invalid_format);
    return {};
  }

  // Parse month.
  unsigned um;  // NOLINT: Will be set by from_chars or not used on error.
  if (const auto [cur, err] = std::from_chars(beg, beg + 2, um);
      err != std::errc{} || cur != beg + 2 || *cur != '-' || um < 1 || um > 12)
  {
    ec = std::make_error_code(errc::invalid_month_format);
    return {};
  } else {
    beg = cur + 1;
  }

  // Parse day.
  unsigned ud;  // NOLINT: Will be set by from_chars or not used on error.
  if (const auto [cur, err] = std::from_chars(beg, beg + 2, ud);
      err != std::errc{} || cur != beg + 2 || *cur != ' ' || ud < 1 || ud > 31)
  {
    ec = std::make_error_code(errc::invalid_day_format);
    return {};
  } else {
    beg = cur + 1;
  }

  const auto ymd = year{ iy } / month{ um } / day{ ud };
  Duration duration{};

  if constexpr (std::ratio_less_v<Period, days::period>) {
    // Parse hours.
    hours::rep hv;  // NOLINT: Will be set by from_chars or not used on error.
    if (const auto [cur, err] = std::from_chars(beg, beg + 2, hv);
        err != std::errc{} || cur != beg + 2 || *cur != ':' || hv < 0 || hv > 23)
    {
      ec = std::make_error_code(errc::invalid_hours_format);
      return {};
    } else {
      beg = cur + 1;
    }
    duration += hours{ hv };
  }

  if constexpr (std::ratio_less_v<Period, hours::period>) {
    // Parse minutes.
    minutes::rep mv;  // NOLINT: Will be set by from_chars or not used on error.
    if (const auto [cur, err] = std::from_chars(beg, beg + 2, mv); err != std::errc{} || cur != beg + 2 || mv < 0 || mv > 59)
    {
      ec = std::make_error_code(errc::invalid_minutes_format);
      return {};
    } else {
      duration += minutes{ mv };
      if (cur == end) {
        return cast<TimePointOrLocalTime>(local_days{ ymd }) + duration;
      }
      if (*cur != ':') {
        ec = std::make_error_code(errc::invalid_format);
        return {};
      }
      beg = cur + 1;
    }
  }

  if constexpr (std::ratio_less_v<Period, minutes::period>) {
    if (size > 11) {
      // Parse seconds.
      seconds::rep sv;  // NOLINT: Will be set by from_chars or not used on error.
      if (const auto [cur, err] = std::from_chars(beg, beg + 2, sv); err != std::errc{} || cur != beg + 2 || sv < 0 || sv > 60)
      {
        ec = std::make_error_code(errc::invalid_seconds_format);
        return {};
      } else {
        duration += seconds{ sv };
        if (cur == end) {
          return cast<TimePointOrLocalTime>(local_days{ ymd }) + duration;
        }
        if (*cur != '.') {
          ec = std::make_error_code(errc::invalid_format);
          return {};
        }
        beg = cur + 1;
      }

      if constexpr (std::ratio_less_v<Period, seconds::period>) {
        if (size > 14) {
          // Parse subseconds.
          int subseconds;  // NOLINT: Will be set by from_chars or not used on error.
          if (const auto [cur, err] = std::from_chars(beg, end, subseconds); err != std::errc{} || subseconds < 0) {
            ec = std::make_error_code(err);
            return {};
          } else if (cur != end) {
            ec = std::make_error_code(errc::invalid_subseconds_format);
            return {};
          }
          switch (size) {
          case 18:
            duration += cast<Duration>(milliseconds{ subseconds });
            break;
          case 21:
            duration += cast<Duration>(microseconds{ subseconds });
            break;
          case 24:
            duration += cast<Duration>(nanoseconds{ subseconds });
            break;
          default:
            ec = std::make_error_code(errc::invalid_subseconds_format);
            return {};
          }
        }
      }
    }
  }

  return cast<TimePointOrLocalTime>(local_days{ ymd }) + duration;
}

template <TimePointOrLocalTime TimePointOrLocalTime>
[[nodiscard]] inline TimePointOrLocalTime parse(std::string_view str) {
  std::error_code ec;
  const auto result = parse<TimePointOrLocalTime>(str, ec);
  if (ec) {
    throw std::system_error(ec, "could not parse time point");
  }
  return result;
}

#if 0
namespace literals {
namespace internal {

template <std::size_t SIZE>
inline constexpr auto zero() {
  if constexpr (SIZE == 4) {
    return years{ 0 };
  } else if constexpr (SIZE == 7) {
    return months{ 0 };
  } else if constexpr (SIZE == 10) {
    return days{ 0 };
  } else if constexpr (SIZE == 13) {
    return hours{ 0 };
  } else if constexpr (SIZE == 16) {
    return minutes{ 0 };
  } else if constexpr (SIZE == 19) {
    return seconds{ 0 };
  } else if constexpr (SIZE == 23) {
    return milliseconds{ 0 };
  } else if constexpr (SIZE == 26) {
    return microseconds{ 0 };
  } else if constexpr (SIZE == 29) {
    return nanoseconds{ 0 };
  } else {
    static_assert(false, "invalid time point length");
  }
}

template <std::size_t SIZE>
struct parse_traits {
  using type = decltype(zero<SIZE>());
};

}  // namespace internal

inline auto operator""_h(const char* str, std::size_t size) {
  return parse<hours>({ str, size });
}

inline auto operator""_min(const char* str, std::size_t size) {
  return parse<minutes>({ str, size });
}

inline auto operator""_s(const char* str, std::size_t size) {
  return parse<seconds>({ str, size });
}

inline auto operator""_ms(const char* str, std::size_t size) {
  return parse<milliseconds>({ str, size });
}

inline auto operator""_us(const char* str, std::size_t size) {
  return parse<microseconds>({ str, size });
}

inline auto operator""_ns(const char* str, std::size_t size) {
  return parse<nanoseconds>({ str, size });
}

}  // namespace literals

template <std::size_t SIZE>
inline constexpr auto du(const char(&str)[SIZE]) {
  return parse<seconds>(str);
}

template <std::size_t SIZE>
inline constexpr auto lt(const char (&str)[SIZE]) {
  return parse<local_time<internal::parse_traits<SIZE - 1>::type>>(str);
}

template <std::size_t SIZE>
inline constexpr auto st(const char(&str)[SIZE]) {
  return parse<sys_time<internal::parse_traits<SIZE - 1>::type>>(str);
}

template <std::size_t SIZE>
inline constexpr auto ut(const char(&str)[SIZE]) {
  return parse<utc_time<internal::parse_traits<SIZE - 1>::type>>(str);
}


// GCC Only
template <std::size_t N>
struct static_string {
  static_assert(N != 0);

  inline constexpr static_string(const char(&arr)[N]) {
    for (std::size_t i = 0; i < N; ++i) {
      value[i] = arr[i];
    }
  }

  char value[N]{};
  static constexpr std::size_t size = N;
};

template <std::size_t N>
static_string(const char(&)[N])->static_string<N>;

template <static_string>
struct S {};

template struct S<"Hello">;

template <static_string str>
inline constexpr std::size_t operator""_size() {
  return decltype(str)::size;
}

std::size_t test() {
  return "Hello"_size;
}

#endif

}  // namespace dtz
