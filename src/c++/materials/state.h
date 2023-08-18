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

#include <QtGui/QColor>

struct State
{
  int compare(const State*) const;
  QColor color;
};

inline int State::compare(const State* other) const
{
  if(color.rgba() == other->color.rgba())
    return 0;
  if(color.rgba() < other->color.rgba())
    return -1;
  return 1;
}