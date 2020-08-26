#include <dtz.hpp>

using namespace dtz::literals;

int main() {
  dtz::initialize();

  const auto ltp0 = dtz::local_days{ 2020_y / 8 / 26 } + 11h + 20min;
  const auto ztp0 = dtz::make_zoned("Europe/Berlin", ltp0, dtz::choose::latest);

  const auto ltp1 = dtz::local_days{ 2020_y / 8 / 26 } + 12h + 50min;
  const auto ztp1 = dtz::make_zoned("Europe/Berlin", ltp1, dtz::choose::latest);

  const auto diff = dtz::cast<dtz::system_clock>(ztp1) - dtz::cast<dtz::system_clock>(ztp0);

  const auto next = dtz::cast<dtz::local_t>(ztp0) + 1h + 30min;
  const auto ztp2 = dtz::make_zoned(ztp0.get_time_zone(), next, dtz::choose::latest);

  //fmt::print("ymd: {}\n", ymd);
  //fmt::print("tod: {}\n", tod);
  //fmt::print("ltp: {}\n", ltp);
  //fmt::print("ztp: {}\n", ztp);
  //fmt::print("ztp system_clock: {}\n", dtz::cast<dtz::system_clock>(ztp));
  //fmt::print("ztp local_t: {}\n", dtz::cast<dtz::local_t>(ztp));

  //
  //const auto tod = dtz::hh_mm_ss{ 23h + 59min + 59s + 0ms };
  //const auto ltp = date::local_days{ ymd } + 23h + 59min + 59s + 0ms;
  //const auto utp = date::utc_clock::from_local(ltp) + 1s;
  //
  //const auto utp_local = date::clock_cast<date::local_t>(utp);
  //const auto utp_local_days = std::chrono::time_point_cast<date::days>(utp_local);
  //const auto hms = date::hh_mm_ss{ utp_local - utp_local_days };
  //
  //std::cout << hms.seconds().count() << '.' << hms.subseconds().count() << std::endl;
}
