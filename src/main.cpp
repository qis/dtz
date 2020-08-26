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
  //using namespace std::chrono_literals;
  //using namespace date::literals;
  //
  //const auto ltp = date::local_days{ 2020_y / 8 / 26 - date::years{ 2021 } } + 6h + 0ms;
  //std::cout << ltp << std::endl;  // -0001-08-26 06:00:00.000
  //
  //const auto ymd = date::year_month_day{ std::chrono::floor<date::days>(ltp) };
  //std::cout << ymd << std::endl;  // -0001-08-26
  //
  //const auto hms = date::hh_mm_ss{ ltp - std::chrono::floor<date::days>(ltp) };
  //std::cout << hms << std::endl;  // 06:00:00.000

  const auto ztp = dtz::now("Europe/Berlin");
  const auto ltp = dtz::cast<dtz::local_t>(ztp);
  const auto ymd = dtz::ymd(ltp) - dtz::years{ 2021 };
  const auto hms = dtz::hms(ltp);
  fmt::print("{}\n", ymd + hms);

  //const auto ymd = dtz::ymd(stp) - dtz::years{ 2021 };
  //const auto ltp = ymd + dtz::hms(stp);

  //fmt::memory_buffer buffer;
  //dtz::format_to(buffer, ltp);
  //fmt::print("\"{}\"\n", std::string_view{ buffer.data(), buffer.size() });
}
