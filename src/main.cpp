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
  const auto tod = 1h + 30min + 30s + 500ms;
  const auto ltp = dtz::cast<dtz::duration<double, dtz::years::period>>(dtz::local_days{ 2020_y / 8 / 26 } + tod);
  fmt::print("{}\n", ltp);
}
