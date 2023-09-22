#pragma once

#include <limits>
#include <cmath>

namespace LPVL
{
  double log(double base, double value) noexcept { return (std::log(value) / std::log(base)); }

  double deg2rad(double degrees) noexcept { return degrees * (M_PI / 180); }
  double rad2deg(double radians) noexcept { return radians * (180 / M_PI); }

  double NaN() noexcept;
  bool isNaN(double other) noexcept;

  constexpr bool compare(double x, double y) { return (std::abs(x - y) * 1000000000000. <= std::min(std::abs(x), std::abs(y))); }
  constexpr bool compare(float x, float y) { return (std::abs(x - y) * 100000.f <= std::min(std::abs(x), std::abs(y))); }
}