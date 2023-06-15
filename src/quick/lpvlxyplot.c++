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

#include "lpvlxyplot.h"
#include <QtQuick/QSGGeometryNode>
#include <QtQuick/QSGFlatColorMaterial>
#include "LPVL/GLGeometry"

namespace LPVL
{

LPVL_REGISTER_QML(XYPlot, "LPVLXYPlot", "LPVL.Charts")

XYPlot::XYPlot(QQuickItem* parent)
    : ChartBase(parent)
    , m_fill(true)
    , x_min(0)
    , x_max(0)
    , y_min(0)
    , y_max(0)
{
    setFlags(ItemHasContents);
}

XYPlot::~XYPlot() {}

void XYPlot::set(const vector<Point2D>& vec)
{
    if(v == vec)
        return;

    v = vec;
    this->calculate_bounds();
    this->update();
}

void XYPlot::clear()
{
    v.clear();
    y_max = 0;
    y_min = 0;
    this->update();
}

bool XYPlot::fill() const { return m_fill; }
void XYPlot::setFill(bool b) {
    if (m_fill == b)
        return;
    m_fill = b;
    emit fillChanged();
}

QSGNode *XYPlot::updatePaintNode(QSGNode *old_node, UpdatePaintNodeData *)
{

}

void XYPlot::calculate_bounds(bool skip)
{

}

} // LPVL
