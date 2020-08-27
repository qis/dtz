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
  const auto v = dtz::parse<dtz::months>("730:00");
  fmt::print("{} != {}\n", v, dtz::cast<dtz::months>(dtz::months{ 1 }));
}
