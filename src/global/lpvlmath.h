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

#include "LPVL/Global"

namespace LPVL
{
    LPVL_EXPORT double log(double base, double value) noexcept;

    LPVL_EXPORT double deg2rad(double degrees) noexcept;
    LPVL_EXPORT double rad2deg(double radians) noexcept;

    LPVL_EXPORT double NaN() noexcept;
    LPVL_EXPORT bool isNaN(double other) noexcept;
}
