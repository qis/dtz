#include <dtz.hpp>
#include <iostream>

using namespace dtz::literals;

namespace date {

template <dtz::Duration Duration>
[[nodiscard]] inline constexpr auto operator+(const year_month_day& ymd, const hh_mm_ss<Duration>& hms) noexcept {
  return local_days{ ymd } + duration_cast<Duration>(hms.to_duration());
}

template <dtz::Duration Duration>
[[nodiscard]] inline constexpr auto operator-(const year_month_day& ymd, const hh_mm_ss<Duration>& hms) noexcept {
  return local_days{ ymd } - duration_cast<Duration>(hms.to_duration());
}

}  // namespace date

int main(int argc, char* argv[]) {
  constexpr auto max = std::numeric_limits<dtz::microseconds::rep>::max();  // 9223372036854775807

  //fmt::print("yy: {}\n", dtz::cast<dtz::years>(dtz::microseconds{ max }).count());

  fmt::print("{}\n", dtz::cast<dtz::fpyears<float>>(dtz::local_days{ 2020_y / 6 / 15 }));

  /*
  const auto dur = dtz::microseconds{ 1 };
  const auto str = fmt::format("{}", dur);
  fmt::print("ok: {}\n", dtz::parse<dtz::microseconds>(str) == dur);

  const auto tod = 1h + 30min + 30s + 500ms;
  const auto ltp = dtz::cast<dtz::duration<double, dtz::years::period>>(dtz::local_days{ 2020_y / 8 / 26 } + tod);
  fmt::print("{}\n", ltp);
  */
}
