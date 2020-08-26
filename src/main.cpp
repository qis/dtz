#include <dtz.hpp>

using namespace dtz::literals;

int main() {
  dtz::initialize();

  const auto ymd = 2020_y / 8 / 26;
  const auto tod = dtz::hh_mm_ss{ 0h + 20min };

  const auto ltp = dtz::local_days{ ymd } + dtz::to_duration(tod);
  const auto ztp = dtz::make_zoned("Europe/Berlin", ltp, dtz::choose::latest);
  const auto stp = dtz::cast<dtz::system_clock>(ztp);

  fmt::print("ymd: {}\n", ymd);
  fmt::print("tod: {}\n", tod);
  fmt::print("ltp: {}\n", ltp);
  fmt::print("ztp: {}\n", ztp);
  fmt::print("stp: {}\n", stp);
  fmt::print("\n");

  fmt::print("stp ymd: {}, stp tod: {}\n", dtz::ymd(stp), dtz::hms(stp));
  fmt::print("ltp ymd: {}, ltp tod: {}\n", dtz::ymd(ltp), dtz::hms(ltp));

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
