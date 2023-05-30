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

#include "lpvlmath.h"

#include <QtCore/QDebug>
#include <limits>
#include <cmath>

namespace LPVL
{

    double log(double base, double value) noexcept { return (std::log(value) / std::log(base)); }
    double deg2rad(double degrees) noexcept { return degrees * (M_PI / 180); }
    double rad2deg(double radians) noexcept { return radians * (180 / M_PI); }

    double NaN() noexcept { return std::numeric_limits<double>::quiet_NaN(); }
    bool isNaN(double other) noexcept { return std::isnan(other); }

} // LPVL
