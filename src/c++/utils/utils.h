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

#include <QtQuick/QSGGeometry>
#include <QtQuick/QSGGeometryNode>

namespace LPVL::utils
{
  enum CreationMode
  {
    GeometryAndMaterial,
    OnlyGeometry,
    OnlyMaterial,
    EmptyNode
  };

  QSGGeometryNode* createSimpleGeometryNode(const QColor& color, unsigned int drawing_mode, CreationMode mode = GeometryAndMaterial, float line_width = 1);

  QSGGeometry::Point2D fromTexturedPoint2D(const QSGGeometry::TexturedPoint2D&);
  QSGGeometry::TexturedPoint2D fromPoint2D(const QSGGeometry::Point2D&, float u, float v);
  QSGGeometry::TexturedPoint2D fromPoint2DBounded(const QSGGeometry::Point2D&, double width, double height);
} // LPVL::utils
