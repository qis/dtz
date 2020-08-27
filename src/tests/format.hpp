#pragma once
#include <dtz/chrono.hpp>
#include <functional>
#include <string>
#include <utility>
#include <vector>

using namespace dtz::literals;

// ====================================================================================================================
// Duration
// ====================================================================================================================

template <typename Rep, typename Period>
struct format_duration_data {};

template <>
struct format_duration_data<dtz::nanoseconds::rep, dtz::nanoseconds::period> {
  using duration = dtz::duration<dtz::nanoseconds::rep, dtz::nanoseconds::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "00:00:00.000000001", duration{ 1 } },
    { "00:00:00.000001000", duration{ 1us } },
    { "00:00:00.001000000", duration{ 1ms } },
    { "00:00:01.000000000", duration{ 1s } },
    { "00:01:00.000000000", duration{ 1min } },
    { "01:00:00.000000000", duration{ 1h } },
    { "24:00:00.000000000", duration{ dtz::days{ 1 } } },
    { "168:00:00.000000000", duration{ dtz::weeks{ 1 } } },
    { "730:29:06.000000000", dtz::cast<duration>(dtz::months{ 1 }) },
    { "8765:49:12.000000000", dtz::cast<duration>(dtz::years{ 1 }) },
    { "-00:00:00.000000001", duration{ -1 } },
    { "-00:00:00.000001000", duration{ -1us } },
    { "-00:00:00.001000000", duration{ -1ms } },
    { "-00:00:01.000000000", duration{ -1s } },
    { "-00:01:00.000000000", duration{ -1min } },
    { "-01:00:00.000000000", duration{ -1h } },
    { "-24:00:00.000000000", duration{ -dtz::days{ 1 } } },
    { "-168:00:00.000000000", duration{ dtz::weeks{ -1 } } },
    { "-730:29:06.000000000", dtz::cast<duration>(dtz::months{ -1 }) },
    { "-8765:49:12.000000000", dtz::cast<duration>(dtz::years{ -1 }) },
  };
};

template <>
struct format_duration_data<dtz::microseconds::rep, dtz::microseconds::period> {
  using duration = dtz::duration<dtz::microseconds::rep, dtz::microseconds::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "00:00:00.000001", duration{ 1 } },
    { "00:00:00.001000", duration{ 1ms } },
    { "00:00:01.000000", duration{ 1s } },
    { "00:01:00.000000", duration{ 1min } },
    { "01:00:00.000000", duration{ 1h } },
    { "24:00:00.000000", duration{ dtz::days{ 1 } } },
    { "168:00:00.000000", duration{ dtz::weeks{ 1 } } },
    { "730:29:06.000000", dtz::cast<duration>(dtz::months{ 1 }) },
    { "8765:49:12.000000", dtz::cast<duration>(dtz::years{ 1 }) },
    { "-00:00:00.000001", duration{ -1 } },
    { "-00:00:00.001000", duration{ -1ms } },
    { "-00:00:01.000000", duration{ -1s } },
    { "-00:01:00.000000", duration{ -1min } },
    { "-01:00:00.000000", duration{ -1h } },
    { "-24:00:00.000000", duration{ -dtz::days{ 1 } } },
    { "-168:00:00.000000", duration{ dtz::weeks{ -1 } } },
    { "-730:29:06.000000", dtz::cast<duration>(dtz::months{ -1 }) },
    { "-8765:49:12.000000", dtz::cast<duration>(dtz::years{ -1 }) },
  };
};

template <>
struct format_duration_data<dtz::milliseconds::rep, dtz::milliseconds::period> {
  using duration = dtz::duration<dtz::milliseconds::rep, dtz::milliseconds::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "00:00:00.001", duration{ 1 } },
    { "00:00:01.000", duration{ 1s } },
    { "00:01:00.000", duration{ 1min } },
    { "01:00:00.000", duration{ 1h } },
    { "24:00:00.000", duration{ dtz::days{ 1 } } },
    { "168:00:00.000", duration{ dtz::weeks{ 1 } } },
    { "730:29:06.000", dtz::cast<duration>(dtz::months{ 1 }) },
    { "8765:49:12.000", dtz::cast<duration>(dtz::years{ 1 }) },
    { "-00:00:00.001", duration{ -1 } },
    { "-00:00:01.000", duration{ -1s } },
    { "-00:01:00.000", duration{ -1min } },
    { "-01:00:00.000", duration{ -1h } },
    { "-24:00:00.000", duration{ -dtz::days{ 1 } } },
    { "-168:00:00.000", duration{ dtz::weeks{ -1 } } },
    { "-730:29:06.000", dtz::cast<duration>(dtz::months{ -1 }) },
    { "-8765:49:12.000", dtz::cast<duration>(dtz::years{ -1 }) },
  };
};

template <>
struct format_duration_data<dtz::seconds::rep, dtz::seconds::period> {
  using duration = dtz::duration<dtz::seconds::rep, dtz::seconds::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "00:00:01", duration{ 1 } },
    { "00:01:00", duration{ 1min } },
    { "01:00:00", duration{ 1h } },
    { "24:00:00", duration{ dtz::days{ 1 } } },
    { "168:00:00", duration{ dtz::weeks{ 1 } } },
    { "730:29:06", dtz::cast<duration>(dtz::months{ 1 }) },
    { "8765:49:12", dtz::cast<duration>(dtz::years{ 1 }) },
    { "-00:00:01", duration{ -1 } },
    { "-00:01:00", duration{ -1min } },
    { "-01:00:00", duration{ -1h } },
    { "-24:00:00", duration{ -dtz::days{ 1 } } },
    { "-168:00:00", duration{ dtz::weeks{ -1 } } },
    { "-730:29:06", dtz::cast<duration>(dtz::months{ -1 }) },
    { "-8765:49:12", dtz::cast<duration>(dtz::years{ -1 }) },
  };
};

template <>
struct format_duration_data<dtz::minutes::rep, dtz::minutes::period> {
  using duration = dtz::duration<dtz::minutes::rep, dtz::minutes::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "00:01", duration{ 1 } },
    { "01:00", duration{ 1h } },
    { "24:00", duration{ dtz::days{ 1 } } },
    { "168:00", duration{ dtz::weeks{ 1 } } },
    { "730:29", dtz::cast<duration>(dtz::months{ 1 }) },
    { "8765:49", dtz::cast<duration>(dtz::years{ 1 }) },
    { "-00:01", duration{ -1 } },
    { "-01:00", duration{ -1h } },
    { "-24:00", duration{ -dtz::days{ 1 } } },
    { "-168:00", duration{ dtz::weeks{ -1 } } },
    { "-730:29", dtz::cast<duration>(dtz::months{ -1 }) },
    { "-8765:49", dtz::cast<duration>(dtz::years{ -1 }) },
  };
};

template <>
struct format_duration_data<dtz::hours::rep, dtz::hours::period> {
  using duration = dtz::duration<dtz::hours::rep, dtz::hours::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "01:00", duration{ 1 } },
    { "24:00", duration{ dtz::days{ 1 } } },
    { "168:00", duration{ dtz::weeks{ 1 } } },
    { "730:00", dtz::cast<duration>(dtz::months{ 1 }) },
    { "8765:00", dtz::cast<duration>(dtz::years{ 1 }) },
    { "-01:00", duration{ -1 } },
    { "-24:00", duration{ -dtz::days{ 1 } } },
    { "-168:00", duration{ dtz::weeks{ -1 } } },
    { "-730:00", dtz::cast<duration>(dtz::months{ -1 }) },
    { "-8765:00", dtz::cast<duration>(dtz::years{ -1 }) },
  };
};

template <>
struct format_duration_data<dtz::days::rep, dtz::days::period> {
  using duration = dtz::duration<dtz::days::rep, dtz::days::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "24:00", duration{ 1 } },
    { "168:00", duration{ dtz::weeks{ 1 } } },
    { "720:00", dtz::cast<duration>(dtz::months{ 1 }) },
    { "8760:00", dtz::cast<duration>(dtz::years{ 1 }) },
    { "-24:00", duration{ -1 } },
    { "-168:00", duration{ dtz::weeks{ -1 } } },
    { "-720:00", dtz::cast<duration>(dtz::months{ -1 }) },
    { "-8760:00", dtz::cast<duration>(dtz::years{ -1 }) },
  };
};

template <>
struct format_duration_data<dtz::weeks::rep, dtz::weeks::period> {
  using duration = dtz::duration<dtz::weeks::rep, dtz::weeks::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "168:00", duration{ 1 } },
    { "672:00", dtz::cast<duration>(dtz::months{ 1 }) },
    { "8736:00", dtz::cast<duration>(dtz::years{ 1 }) },
    { "-168:00", duration{ -1 } },
    { "-672:00", dtz::cast<duration>(dtz::months{ -1 }) },
    { "-8736:00", dtz::cast<duration>(dtz::years{ -1 }) },
  };
};

template <>
struct format_duration_data<dtz::months::rep, dtz::months::period> {
  using duration = dtz::duration<dtz::months::rep, dtz::months::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "730:00", duration{ 1 } },
    { "8765:00", duration{ dtz::years{ 1 } } },
    { "-730:00", duration{ -1 } },
    { "-8765:00", duration{ dtz::years{ -1 } } },
  };
};

template <>
struct format_duration_data<dtz::years::rep, dtz::years::period> {
  using duration = dtz::duration<dtz::years::rep, dtz::years::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "8765:00", duration{ 1 } },
    { "-8765:00", duration{ -1 } },
  };
};

// ====================================================================================================================
// TimePoint
// ====================================================================================================================

template <dtz::Duration Duration>
struct format_time_point_data {};

template <>
struct format_time_point_data<dtz::nanoseconds> {
  using time_point = dtz::local_time<dtz::nanoseconds>;
  static inline const std::vector<std::pair<std::string, time_point>> value = {
    { "2020-01-01 01:01:02.003004005", dtz::local_days{ 2020_y / 1 / 1 } + 1h + 1min + 2s + 3ms + 4us + 5ns },
  };
};

template <>
struct format_time_point_data<dtz::microseconds> {
  using time_point = dtz::local_time<dtz::microseconds>;
  static inline const std::vector<std::pair<std::string, time_point>> value = {
    { "2020-01-01 01:01:02.003004", dtz::local_days{ 2020_y / 1 / 1 } + 1h + 1min + 2s + 3ms + 4us },
    { "-0001-01-01 01:01:02.003004", dtz::local_days{ (2020_y / 1 / 1) - dtz::years{ 2021 } } + 1h + 1min + 2s + 3ms + 4us },
  };
};

template <>
struct format_time_point_data<dtz::milliseconds> {
  using time_point = dtz::local_time<dtz::milliseconds>;
  static inline const std::vector<std::pair<std::string, time_point>> value = {
    { "2020-01-01 01:01:02.003", dtz::local_days{ 2020_y / 1 / 1 } + 1h + 1min + 2s + 3ms },
    { "-0001-01-01 01:01:02.003", dtz::local_days{ (2020_y / 1 / 1) - dtz::years{ 2021 } } + 1h + 1min + 2s + 3ms },
  };
};

template <>
struct format_time_point_data<dtz::seconds> {
  using time_point = dtz::local_time<dtz::seconds>;
  static inline const std::vector<std::pair<std::string, time_point>> value = {
    { "2020-01-01 01:01:02", dtz::local_days{ 2020_y / 1 / 1 } + 1h + 1min + 2s },
    { "-0001-01-01 01:01:02", dtz::local_days{ (2020_y / 1 / 1) - dtz::years{ 2021 } } + 1h + 1min + 2s },
  };
};

template <>
struct format_time_point_data<dtz::minutes> {
  using time_point = dtz::local_time<dtz::minutes>;
  static inline const std::vector<std::pair<std::string, time_point>> value = {
    { "2020-01-01 01:01", dtz::local_days{ 2020_y / 1 / 1 } + 1h + 1min },
    { "-0001-01-01 01:01", dtz::local_days{ (2020_y / 1 / 1) - dtz::years{ 2021 } } + 1h + 1min },
  };
};

template <>
struct format_time_point_data<dtz::hours> {
  using time_point = dtz::local_time<dtz::hours>;
  static inline const std::vector<std::pair<std::string, time_point>> value = {
    { "2020-01-01 01:00", dtz::local_days{ 2020_y / 1 / 1 } + 1h },
    { "-0001-01-01 01:00", dtz::local_days{ (2020_y / 1 / 1) - dtz::years{ 2021 } } + 1h },
  };
};

template <>
struct format_time_point_data<dtz::days> {
  using time_point = dtz::local_time<dtz::days>;
  static inline const std::vector<std::pair<std::string, time_point>> value = {
    { "2020-01-01", dtz::local_days{ 2020_y / 1 / 1 } },
    { "-0001-01-01", dtz::local_days{ (2020_y / 1 / 1) - dtz::years{ 2021 } } },
  };
};

template <>
struct format_time_point_data<dtz::weeks> {
  using time_point = dtz::local_time<dtz::weeks>;
  static inline const std::vector<std::pair<std::string, time_point>> value = {
    { "2019-12-26", dtz::cast<dtz::weeks>(dtz::local_days{ 2020_y / 1 / 1 }) },
    { "-0001-01-07", dtz::cast<dtz::weeks>(dtz::local_days{ (2020_y / 1 / 1) - dtz::years{ 2021 } }) },
  };
};
