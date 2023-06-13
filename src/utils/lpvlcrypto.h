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

class QString;

namespace LPVL
{
    LPVL_EXPORT uint16_t crc16(char* data, int size) noexcept;
    LPVL_EXPORT uint16_t crc16_ccitt(const char* data, int size) noexcept;
    LPVL_EXPORT char* str_data(const QString& str) noexcept;
}



