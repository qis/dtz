#pragma once
#include "traits.hpp"
#include <fmt/format.h>

namespace dtz {

template <std::size_t SIZE, Duration Duration>
inline auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const Duration& duration) {
  using Period = typename Duration::period;
  if (duration < Duration{ 0 }) {
    constexpr const char* minus = "-";
    out.append(minus, minus + 1);
  }
  const auto d = abs(duration);
  const auto h = cast<hours>(d);
  if constexpr (std::ratio_less_equal_v<Period, minutes::period>) {
    const auto m = duration_cast<minutes>(d - h);
    if constexpr (std::ratio_less_equal_v<Period, seconds::period>) {
      const auto s = duration_cast<seconds>(d - h - m);
      if constexpr (std::ratio_less_equal_v<Period, nanoseconds::period>) {
        const auto ns = duration_cast<nanoseconds>(d - h - m - s);
        return fmt::format_to(out, "{:02}:{:02}:{:02}.{:09}", h.count(), m.count(), s.count(), ns.count());
      } else if constexpr (std::ratio_less_equal_v<Period, microseconds::period>) {
        const auto us = duration_cast<microseconds>(d - h - m - s);
        return fmt::format_to(out, "{:02}:{:02}:{:02}.{:06}", h.count(), m.count(), s.count(), us.count());
      } else if constexpr (std::ratio_less_equal_v<Period, milliseconds::period>) {
        const auto ms = duration_cast<milliseconds>(d - h - m - s);
        return fmt::format_to(out, "{:02}:{:02}:{:02}.{:03}", h.count(), m.count(), s.count(), ms.count());
      } else {
        return fmt::format_to(out, "{:02}:{:02}:{:02}", h.count(), m.count(), s.count());
      }
    } else {
      return fmt::format_to(out, "{:02}:{:02}", h.count(), m.count());
    }
  } else {
    return fmt::format_to(out, "{:02}:00", h.count());
  }
}

template <std::size_t SIZE, LocalTime LocalTime>
inline auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const LocalTime& tp) {
  using Duration = typename LocalTime::duration;
  using Period = typename LocalTime::period;
  const auto tpd = cast<days>(tp);
  const auto ymd = year_month_day{ tpd };
  const auto iy = static_cast<int>(ymd.year());
  const auto um = static_cast<unsigned int>(ymd.month());
  const auto ud = static_cast<unsigned int>(ymd.day());
  if constexpr (std::ratio_less_equal_v<Period, hours::period>) {
    const auto sec = cast<seconds>(tpd);
    const auto tod = time_of_day<Duration>{ cast<Duration>(tp - sec) }.to_duration();
    const auto h = cast<hours>(tod);
    if constexpr (std::ratio_less_equal_v<Period, minutes::period>) {
      const auto m = cast<minutes>(tod - h);
      if constexpr (std::ratio_less_equal_v<Period, seconds::period>) {
        const auto s = cast<seconds>(tod - h - m);
        if constexpr (std::ratio_less_equal_v<Period, nanoseconds::period>) {
          const auto ns = cast<nanoseconds>(tod - h - m - s);
          constexpr auto format = "{}-{:02}-{:02} {:02}:{:02}:{:02}.{:09}";
          return fmt::format_to(out, format, iy, um, ud, h.count(), m.count(), s.count(), ns.count());
        } else if constexpr (std::ratio_less_equal_v<Period, microseconds::period>) {
          const auto us = cast<microseconds>(tod - h - m - s);
          constexpr auto format = "{}-{:02}-{:02} {:02}:{:02}:{:02}.{:06}";
          return fmt::format_to(out, format, iy, um, ud, h.count(), m.count(), s.count(), us.count());
        } else if constexpr (std::ratio_less_equal_v<Period, milliseconds::period>) {
          const auto ms = cast<milliseconds>(tod - h - m - s);
          constexpr auto format = "{}-{:02}-{:02} {:02}:{:02}:{:02}.{:03}";
          return fmt::format_to(out, format, iy, um, ud, h.count(), m.count(), s.count(), ms.count());
        } else {
          constexpr auto format = "{}-{:02}-{:02} {:02}:{:02}:{:02}";
          return fmt::format_to(out, format, iy, um, ud, h.count(), m.count(), s.count());
        }
      } else {
        constexpr auto format = "{}-{:02}-{:02} {:02}:{:02}";
        return fmt::format_to(out, format, iy, um, ud, h.count(), m.count());
      }
    } else {
      constexpr auto format = "{}-{:02}-{:02} {:02}:00";
      return fmt::format_to(out, format, iy, um, ud, h.count());
    }
  } else {
    return fmt::format_to(out, "{}-{:02}-{:02}", iy, um, ud);
  }
}

template <std::size_t SIZE, TimePoint TimePoint>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const TimePoint& tp) {
  return format_to(out, cast<local_t>(tp));
}

template <std::size_t SIZE, ZonedTime ZonedTime>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const ZonedTime& tp) {
  return format_to(out, cast<local_t>(tp));
}

template <std::size_t SIZE, Duration Duration>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const time_of_day<Duration>& tod) {
  return format_to(out, cast<Duration>(tod));
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const day& d) {
  return fmt::format_to(out, "{:02}", static_cast<unsigned>(d));
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const month& m) {
  const auto s = traits<month>::names[static_cast<unsigned>(m) - 1];
  out.append(s, s + traits<month>::buffer_size);
  return out.end();
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const year& y) {
  return fmt::format_to(out, "{}", static_cast<int>(y));
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const weekday& wd) {
  const auto s = traits<weekday>::names[wd.c_encoding()];
  out.append(s, s + traits<weekday>::buffer_size);
  return out.end();
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const weekday_indexed& wdi) {
  format_to(out, wdi.weekday());
  return fmt::format_to(out, "[{}]", wdi.index());
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const weekday_last& wdl) {
  constexpr const char* s = "[last]";
  format_to(out, wdl.weekday());
  out.append(s, s + 6);
  return out.end();
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const month_day& md) {
  format_to(out, md.month());
  return fmt::format_to(out, "/{:02}", static_cast<unsigned>(md.day()));
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const month_day_last& mdl) {
  constexpr const char* s = "/last";
  format_to(out, mdl.month());
  out.append(s, s + 5);
  return out.end();
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const month_weekday& mwd) {
  constexpr const char* s = "/";
  format_to(out, mwd.month());
  out.append(s, s + 1);
  return format_to(out, mwd.weekday_indexed());
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const month_weekday_last& mwdl) {
  constexpr const char* s = "/";
  format_to(out, mwdl.month());
  out.append(s, s + 1);
  return format_to(out, mwdl.weekday_last());
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const year_month& ym) {
  const auto iy = static_cast<int>(ym.year());
  const auto um = static_cast<unsigned int>(ym.month());
  return fmt::format_to(out, "{}-{:02}", iy, um);
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const year_month_day& ymd) {
  const auto iy = static_cast<int>(ymd.year());
  const auto um = static_cast<unsigned int>(ymd.month());
  const auto ud = static_cast<unsigned int>(ymd.day());
  return fmt::format_to(out, "{}-{:02}-{:02}", iy, um, ud);
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const year_month_day_last& ymdl) {
  constexpr const char* s = "/last";
  format_to(out, ymdl.year() / ymdl.month());
  out.append(s, s + 5);
  return out.end();
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const year_month_weekday& ymwd) {
  constexpr const char* s = "/";
  format_to(out, ymwd.year() / ymwd.month());
  out.append(s, s + 1);
  format_to(out, ymwd.weekday_indexed());
  return out.end();
}

template <std::size_t SIZE>
inline constexpr auto format_to(fmt::basic_memory_buffer<char, SIZE>& out, const year_month_weekday_last& ymwdl) {
  constexpr const char* s = "/";
  format_to(out, ymwdl.year() / ymwdl.month());
  out.append(s, s + 1);
  format_to(out, ymwdl.weekday_last());
  return out.end();
}

}  // namespace dtz

template <dtz::Format Format>
struct fmt::formatter<Format> : fmt::formatter<std::string_view> {
  template <typename FormatContext>
  auto format(const Format& value, FormatContext& context) {
    fmt::basic_memory_buffer<char, dtz::traits<Format>::buffer_size> out;
    dtz::format_to(out, value);
    return fmt::formatter<std::string_view>::format({ out.data(), out.size() }, context);
  }
};
