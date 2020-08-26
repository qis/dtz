# DateTimeZone
C++20 convenience library for `std::chrono` with `std::format` support.

## Installation
This library is meant to be installed as vcpkg ports overlay.

```sh
git clone https://github.com/qis/dtz
vcpkg install --overlay-ports=dtz dtz
```

## Customization
The standard does not implement operators that have several coflicting but valid meanings.

<details>
<summary><b><code>dtz::weekday</code> comparison</b></summary>

The day of the week can start with 

To enable comparison of `dtz::weekday`, the operators must be implemented in the `date` namespace:

```cpp
namespace date {

[[nodiscard]] inline constexpr bool operator<=(const weekday& lhs, const weekday& rhs) noexcept {
  return lhs.iso_encoding() <= rhs.iso_encoding();
}

[[nodiscard]] inline constexpr bool operator>=(const weekday& lhs, const weekday& rhs) noexcept {
  return lhs.iso_encoding() >= rhs.iso_encoding();
}

[[nodiscard]] inline constexpr bool operator<(const weekday& lhs, const weekday& rhs) noexcept {
  return lhs.iso_encoding() < rhs.iso_encoding();
}

[[nodiscard]] inline constexpr bool operator>(const weekday& lhs, const weekday& rhs) noexcept {
  return lhs.iso_encoding() > rhs.iso_encoding();
}

}  // namespace date
```

</details>

<details>
<summary><b><code>dtz::time_of_day</code> comparison</b></summary>

To enable comparison of `dtz::time_of_day`, the operators must be implemented in the `date` namespace:

```cpp
namespace date {

template <dtz::HHMMSS LHS, dtz::HHMMSS RHS>
[[nodiscard]] inline constexpr bool operator==(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() == rhs.to_duration();
}

template <dtz::HHMMSS LHS, dtz::HHMMSS RHS>
[[nodiscard]] inline constexpr bool operator<=(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() <= rhs.to_duration();
}

template <dtz::HHMMSS LHS, dtz::HHMMSS RHS>
[[nodiscard]] inline constexpr bool operator>=(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() >= rhs.to_duration();
}

template <dtz::HHMMSS LHS, dtz::HHMMSS RHS>
[[nodiscard]] inline constexpr bool operator<(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() < rhs.to_duration();
}

template <dtz::HHMMSS LHS, dtz::HHMMSS RHS>
[[nodiscard]] inline constexpr bool operator>(const LHS& lhs, const RHS& rhs) noexcept {
  return lhs.to_duration() > rhs.to_duration();
}

}  // namespace date
```

</details>

<details>
<summary><b><code>dtz::year_month_day</code> and <code>dtz::hh_mm_ss</code> addition</b></summary>

To enable comparison of `dtz::time_of_day`, the operators must be implemented in the `date` namespace:

```cpp
namespace date {

template <dtz::Duration Duration>
[[nodiscard]] inline constexpr auto operator+(const year_month_day& ymd, const hh_mm_ss<Duration>& hms) noexcept {
  return local_days{ ymd } + duration_cast<Duration>(hms.to_duration());
}

}  // namespace date
```

</details>
