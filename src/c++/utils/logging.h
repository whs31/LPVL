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

#include <QtCore/QtGlobal>

#define scope_info LPVL::Internal::parseScopeInfo(Q_FUNC_INFO)

namespace LPVL::Internal
{
  inline const char* parseScopeInfo(const char* x) noexcept
  {
    const regex rx(".* ([^\\s]*)\\(");
    QRegExp r(".* ([^\\s]*)\\(");
    r.lastIndexIn(x);
    auto s = r.capturedTexts().back();
    return s.toLocal8Bit().data();
  }
} // LPVL::Internal