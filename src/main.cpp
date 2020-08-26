#include <dtz.hpp>
#include <iostream>

using namespace date::literals;
using namespace std::chrono_literals;

int main() {
  dtz::initialize();

  const auto ltp = date::local_days{ 2016_y / 12 / 31 } + 23h + 59min + 59s + 0ms;
  const auto utp = date::utc_clock::from_local(ltp) + 1s;

  const auto utp_local = date::clock_cast<date::local_t>(utp);
  const auto utp_local_days = std::chrono::time_point_cast<date::days>(utp_local);
  const auto hms = date::hh_mm_ss{ utp_local - utp_local_days };

  std::cout << hms.seconds().count() << '.' << hms.subseconds().count() << std::endl;
}
