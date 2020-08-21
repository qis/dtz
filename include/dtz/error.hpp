#pragma once
#include <string>
#include <system_error>

namespace dtz {

enum class errc {
  invalid_format = 1,
  invalid_year_format,
  invalid_month_format,
  invalid_day_format,
  invalid_hours_format,
  invalid_minutes_format,
  invalid_seconds_format,
  invalid_subseconds_format,
};

class error : public std::error_category {
public:
  const char* name() const noexcept override;
  std::string message(int ev) const override;
};

const error& error_category() noexcept;

}  // namespace dtz

namespace std {

template <>
struct is_error_code_enum<dtz::errc> : true_type {};

inline error_code make_error_code(dtz::errc ev) noexcept {
  return { static_cast<int>(ev), dtz::error_category() };
}

}  // namespace std
