#pragma once
#include <dtz/chrono.hpp>
#include <functional>
#include <string>
#include <utility>
#include <vector>

using namespace dtz::literals;

template <typename Rep, typename Period>
struct format_duration_data {};

// ====================================================================================================================
// nanoseconds
// ====================================================================================================================

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
    { "-00:00:00.000000001", duration{ -1 } },
    { "-00:00:00.000001000", duration{ -1us } },
    { "-00:00:00.001000000", duration{ -1ms } },
    { "-00:00:01.000000000", duration{ -1s } },
    { "-00:01:00.000000000", duration{ -1min } },
    { "-01:00:00.000000000", duration{ -1h } },
    { "-24:00:00.000000000", duration{ -dtz::days{ 1 } } },
  };
};

template <>
struct format_duration_data<float, dtz::nanoseconds::period> {
  using duration = dtz::duration<float, dtz::nanoseconds::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "00:00:00.000000000", duration{ 0.1f } },
    { "00:00:00.000000000", duration{ 0.9f } },
    { "00:00:00.000000001", duration{ 1.0f } },
    { "00:00:00.000000002", duration{ 2.9f } },
    { "-00:00:00.000000000", duration{ -0.1f } },
    { "-00:00:00.000000000", duration{ -0.9f } },
    { "-00:00:00.000000001", duration{ -1.0f } },
    { "-00:00:00.000000002", duration{ -2.9f } },
  };
};

template <>
struct format_duration_data<double, dtz::nanoseconds::period> {
  using duration = dtz::duration<double, dtz::nanoseconds::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "00:00:00.000000000", duration{ 0.1 } },
    { "00:00:00.000000000", duration{ 0.9 } },
    { "00:00:00.000000001", duration{ 1.0 } },
    { "00:00:00.000000002", duration{ 2.9 } },
    { "-00:00:00.000000000", duration{ -0.1 } },
    { "-00:00:00.000000001", duration{ -1.0 } },
    { "-00:00:00.000000000", duration{ -0.9 } },
    { "-00:00:00.000000002", duration{ -2.9 } },
  };
};

// ====================================================================================================================
// microseconds
// ====================================================================================================================

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
    { "-00:00:00.000001", duration{ -1 } },
    { "-00:00:00.001000", duration{ -1ms } },
    { "-00:00:01.000000", duration{ -1s } },
    { "-00:01:00.000000", duration{ -1min } },
    { "-01:00:00.000000", duration{ -1h } },
    { "-24:00:00.000000", duration{ -dtz::days{ 1 } } },
  };
};

template <>
struct format_duration_data<float, dtz::microseconds::period> {
  using duration = dtz::duration<float, dtz::microseconds::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "00:00:00.000000100", duration{ 0.1f } },
    { "00:00:00.000000900", duration{ 0.9f } },
    { "00:00:00.000001000", duration{ 1.0f } },
    { "00:00:00.000002900", duration{ 2.9f } },
    { "-00:00:00.000000100", duration{ -0.1f } },
    { "-00:00:00.000000900", duration{ -0.9f } },
    { "-00:00:00.000001000", duration{ -1.0f } },
    { "-00:00:00.000002900", duration{ -2.9f } },
  };
};

template <>
struct format_duration_data<double, dtz::microseconds::period> {
  using duration = dtz::duration<double, dtz::microseconds::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

// ====================================================================================================================
// milliseconds
// ====================================================================================================================

template <>
struct format_duration_data<dtz::milliseconds::rep, dtz::milliseconds::period> {
  using duration = dtz::duration<dtz::milliseconds::rep, dtz::milliseconds::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "00:00:00.001", duration{ 1 } },
    { "00:00:01.000", duration{ 1s } },
    { "00:01:00.000", duration{ 1min } },
    { "01:00:00.000", duration{ 1h } },
    { "24:00:00.000", duration{ dtz::days{ 1 } } },
    { "-00:00:00.001", duration{ -1 } },
    { "-00:00:01.000", duration{ -1s } },
    { "-00:01:00.000", duration{ -1min } },
    { "-01:00:00.000", duration{ -1h } },
    { "-24:00:00.000", duration{ -dtz::days{ 1 } } },
  };
};

template <>
struct format_duration_data<float, dtz::milliseconds::period> {
  using duration = dtz::duration<float, dtz::milliseconds::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

template <>
struct format_duration_data<double, dtz::milliseconds::period> {
  using duration = dtz::duration<double, dtz::milliseconds::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

// ====================================================================================================================
// seconds
// ====================================================================================================================

template <>
struct format_duration_data<dtz::seconds::rep, dtz::seconds::period> {
  using duration = dtz::duration<dtz::seconds::rep, dtz::seconds::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "00:00:01", duration{ 1 } },
    { "00:01:00", duration{ 1min } },
    { "01:00:00", duration{ 1h } },
    { "24:00:00", duration{ dtz::days{ 1 } } },
    { "-00:00:01", duration{ -1 } },
    { "-00:01:00", duration{ -1min } },
    { "-01:00:00", duration{ -1h } },
    { "-24:00:00", duration{ -dtz::days{ 1 } } },
  };
};

template <>
struct format_duration_data<float, dtz::seconds::period> {
  using duration = dtz::duration<float, dtz::seconds::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

template <>
struct format_duration_data<double, dtz::seconds::period> {
  using duration = dtz::duration<double, dtz::seconds::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

// ====================================================================================================================
// minutes
// ====================================================================================================================

template <>
struct format_duration_data<dtz::minutes::rep, dtz::minutes::period> {
  using duration = dtz::duration<dtz::minutes::rep, dtz::minutes::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "00:01", duration{ 1 } },
    { "01:00", duration{ 1h } },
    { "24:00", duration{ dtz::days{ 1 } } },
    { "-00:01", duration{ -1 } },
    { "-01:00", duration{ -1h } },
    { "-24:00", duration{ -dtz::days{ 1 } } },
  };
};

template <>
struct format_duration_data<float, dtz::minutes::period> {
  using duration = dtz::duration<float, dtz::minutes::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

template <>
struct format_duration_data<double, dtz::minutes::period> {
  using duration = dtz::duration<double, dtz::minutes::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

// ====================================================================================================================
// hours
// ====================================================================================================================

template <>
struct format_duration_data<dtz::hours::rep, dtz::hours::period> {
  using duration = dtz::duration<dtz::hours::rep, dtz::hours::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "01:00", duration{ 1 } },
    { "24:00", duration{ dtz::days{ 1 } } },
    { "-01:00", duration{ -1 } },
    { "-24:00", duration{ -dtz::days{ 1 } } },
  };
};

template <>
struct format_duration_data<float, dtz::hours::period> {
  using duration = dtz::duration<float, dtz::hours::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

template <>
struct format_duration_data<double, dtz::hours::period> {
  using duration = dtz::duration<double, dtz::hours::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

// ====================================================================================================================
// days
// ====================================================================================================================

template <>
struct format_duration_data<dtz::days::rep, dtz::days::period> {
  using duration = dtz::duration<dtz::days::rep, dtz::days::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {
    { "24:00", duration{ 1 } },
    { "120:00", duration{ 5 } },
    { "-24:00", duration{ -1 } },
    { "-120:00", duration{ -5 } },
  };
};

template <>
struct format_duration_data<float, dtz::days::period> {
  using duration = dtz::duration<float, dtz::days::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

template <>
struct format_duration_data<double, dtz::days::period> {
  using duration = dtz::duration<double, dtz::days::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

// ====================================================================================================================
// weeks
// ====================================================================================================================

template <>
struct format_duration_data<dtz::weeks::rep, dtz::weeks::period> {
  using duration = dtz::duration<dtz::weeks::rep, dtz::weeks::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

template <>
struct format_duration_data<float, dtz::weeks::period> {
  using duration = dtz::duration<float, dtz::weeks::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

template <>
struct format_duration_data<double, dtz::weeks::period> {
  using duration = dtz::duration<double, dtz::weeks::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

// ====================================================================================================================
// months
// ====================================================================================================================

template <>
struct format_duration_data<dtz::months::rep, dtz::months::period> {
  using duration = dtz::duration<dtz::months::rep, dtz::months::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

template <>
struct format_duration_data<float, dtz::months::period> {
  using duration = dtz::duration<float, dtz::months::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

template <>
struct format_duration_data<double, dtz::months::period> {
  using duration = dtz::duration<double, dtz::months::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

// ====================================================================================================================
// years
// ====================================================================================================================

template <>
struct format_duration_data<dtz::years::rep, dtz::years::period> {
  using duration = dtz::duration<dtz::years::rep, dtz::years::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

template <>
struct format_duration_data<float, dtz::years::period> {
  using duration = dtz::duration<float, dtz::years::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};

template <>
struct format_duration_data<double, dtz::years::period> {
  using duration = dtz::duration<double, dtz::years::period>;
  static inline const std::vector<std::pair<std::string, duration>> value = {};
};
