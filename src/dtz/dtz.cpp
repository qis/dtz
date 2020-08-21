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

namespace {

[[noreturn]] void exit(const char* message, std::error_code ec) {
  std::fprintf(stderr, "%s: %s (%d)\n", message, ec.message().data(), ec.value());
  std::exit(ec.value());
}

enum class initialize_state {
  none = 0,
  initializing,
  failure,
  success,
};

std::atomic<initialize_state> g_initialize_state = initialize_state::none;

}  // namespace

bool initialize() noexcept {
  initialize_state state = initialize_state::none;
  if (!g_initialize_state.compare_exchange_strong(state, initialize_state::initializing)) {
    return state == initialize_state::success;
  }

  std::string executable;
  DWORD size = 0;
  DWORD code = 0;
  do {
    executable.resize(executable.size() + MAX_PATH);
    size = GetModuleFileName(nullptr, executable.data(), static_cast<DWORD>(executable.size()));
    code = GetLastError();
  } while (code == ERROR_INSUFFICIENT_BUFFER);
  if (code) {
    const auto ec = std::error_code{ static_cast<int>(code), std::system_category() };
    g_initialize_state.store(initialize_state::failure);
    exit("Could not locate executable", ec);
    return false;
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
    const auto ec = std::make_error_code(std::errc::no_such_file_or_directory);
    g_initialize_state.store(initialize_state::failure);
    exit("Could not locate tzdata directory", ec);
    return false;
  }
  date::set_install(std::filesystem::canonical(tzdata).string());
  if (!g_initialize_state.compare_exchange_strong(state, initialize_state::success)) {
    return state == initialize_state::success;
  }
  return true;
}
#else

bool initialize() noexcept {
  return true;
}

#endif

}  // namespace dtz
