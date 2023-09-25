/* ---------------------------------------------------------------------
 * LPVL - Linear Algebra, Plotting and Visualisation Library
 * Copyright (C) 2023 whs31.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero Public License version 3 as
 * published by the Free Software Foundation.
 * http://www.gnu.org/licenses.
 *
 * github.com/whs31/lpvl
 * ---------------------------------------------------------------------- */

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
    template<class T> inline constexpr T euler = enable_if_floating<T>(2.71828182845904523536028747135266249L);
    template<class T> inline constexpr T sqrt2 = enable_if_floating<T>(1.41421356237309504880168872420969807L);
    template<class T> inline constexpr T sqrt3 = enable_if_floating<T>(1.73205080756887729352744634150587236L);
    template<class T> inline constexpr T sqrt5 = enable_if_floating<T>(2.23606797749978969640917366873127623L);
    template<class T> inline constexpr T phi = enable_if_floating<T>(1.61803398874989484820458683436563811L);

    constexpr inline double π = pi<double>;
    constexpr inline double e = euler<double>;
    constexpr inline double φ = phi<double>;
  }

  constexpr inline double log(double base, double value) noexcept { return (std::log(value) / std::log(base)); }

  constexpr inline double deg2rad(double degrees) noexcept { return degrees * (Numbers::pi<double> / 180); }
  constexpr inline double rad2deg(double radians) noexcept { return radians * (180 / Numbers::pi<double>); }

  constexpr inline double NaN() noexcept { return std::numeric_limits<double>::quiet_NaN(); };
  constexpr inline bool isNaN(double other) noexcept { return std::isnan(other); };

  constexpr bool compare(double x, double y) { return (std::abs(x - y) * 1000000000000. <= std::min(std::abs(x), std::abs(y))); }
  constexpr bool compare(float x, float y) { return (std::abs(x - y) * 100000.f <= std::min(std::abs(x), std::abs(y))); }
}