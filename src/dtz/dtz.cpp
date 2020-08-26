#include <dtz.hpp>
#include <atomic>
#include <filesystem>
#include <cstdio>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#endif

namespace dtz {

const char* error::name() const noexcept {
  return "dtz error";
}

std::string error::message(int ev) const {
  switch (static_cast<errc>(ev)) {
  case errc::invalid_format:
    return "invalid format";
  case errc::invalid_year_format:
    return "invalid year format";
  case errc::invalid_month_format:
    return "invalid month format";
  case errc::invalid_day_format:
    return "invalid day format";
  case errc::invalid_hours_format:
    return "invalid hours format";
  case errc::invalid_minutes_format:
    return "invalid minutes format";
  case errc::invalid_seconds_format:
    return "invalid seconds format";
  case errc::invalid_subseconds_format:
    return "invalid subseconds format";
  }
  return "unknown error value: " + std::to_string(ev);
}

const error error_instance;

const error& error_category() noexcept {
  return error_instance;
}

#ifdef _WIN32

void initialize(std::error_code& ec) noexcept {
  ec.clear();
  std::string executable;
  DWORD size = 0;
  DWORD code = 0;
  do {
    executable.resize(executable.size() + MAX_PATH);
    size = GetModuleFileName(nullptr, executable.data(), static_cast<DWORD>(executable.size()));
    code = GetLastError();
  } while (code == ERROR_INSUFFICIENT_BUFFER);
  if (code) {
    ec = std::error_code{ static_cast<int>(code), std::system_category() };
    return;
  }
  executable.resize(size);
  const auto path = std::filesystem::path(executable).parent_path();
  auto tzdata = path / "tzdata";
  if (!std::filesystem::is_directory(tzdata)) {
    tzdata = path.parent_path() / "tzdata";
  }
  if (!std::filesystem::is_directory(tzdata)) {
    tzdata = path.parent_path() / "share" / "tzdata";
  }
  if (!std::filesystem::is_directory(tzdata)) {
    ec = std::make_error_code(std::errc::no_such_file_or_directory);
    return;
  }
  date::set_install(std::filesystem::canonical(tzdata).string());
}

void initialize() {
  std::error_code ec;
  initialize(ec);
  if (ec) {
    throw std::system_error(ec, "Could not load time zone database.");
  }
}

#else

void initialize(std::error_code& ec) noexcept {
  ec.clear();
}

void initialize() {
}

#endif

}  // namespace dtz
