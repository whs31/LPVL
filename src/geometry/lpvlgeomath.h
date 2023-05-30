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

class QGeoCoordinate;
class QPointF;

namespace LPVL
{
    namespace Private
    {
        LPVL_EXPORT double mqi_zoom_level(double latitude, float meters_per_pixel = 1) noexcept;
        LPVL_EXPORT QPointF geo2webmercator(const QGeoCoordinate& geo, uint8_t zoom = 19) noexcept;
    }
} // LPVL
