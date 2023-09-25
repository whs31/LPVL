#pragma once

#include <limits>
#include <cmath>
#include <type_traits>

template<typename T>
using enable_if_floating = std::enable_if_t<std::is_floating_point_v<T>, T>;

namespace LPVL
{
  namespace Numbers
  {
    template<class T> inline constexpr T pi = enable_if_floating<T>(3.141592653589793238462643383279502884L);
  }

  double log(double base, double value) noexcept { return (std::log(value) / std::log(base)); }

  double deg2rad(double degrees) noexcept { return degrees * (M_PI / 180); }
  double rad2deg(double radians) noexcept { return radians * (180 / M_PI); }

  double NaN() noexcept;
  bool isNaN(double other) noexcept;

  constexpr bool compare(double x, double y) { return (std::abs(x - y) * 1000000000000. <= std::min(std::abs(x), std::abs(y))); }
  constexpr bool compare(float x, float y) { return (std::abs(x - y) * 100000.f <= std::min(std::abs(x), std::abs(y))); }
}