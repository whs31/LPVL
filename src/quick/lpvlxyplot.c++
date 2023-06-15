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
    , dx(0)
    , dy(0)
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
    QSGGeometry* geometry = nullptr;
    QSGGeometryNode* node = static_cast<QSGGeometryNode*>(old_node);
    if(node == nullptr)
    {
        node = new QSGGeometryNode;

        QSGFlatColorMaterial* material = new QSGFlatColorMaterial;

        node->setMaterial(material);

        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0, 0, QSGGeometry::UnsignedIntType);
        geometry->setDrawingMode(QSGGeometry::DrawTriangles);
        node->setGeometry(geometry);
        node->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);
    }

    QSGFlatColorMaterial* material = static_cast<QSGFlatColorMaterial*>(node->material());
    material->setColor(plottingColor());

    geometry = node->geometry();

    vector<VertexC> gl;

    LPVL_UNIMPLEMENTED

    geometry->allocate(gl.size());
    for(size_t i = 0; i < gl.size(); i++)
        geometry->vertexDataAsPoint2D()[i].set(gl.at(i).x, gl.at(i).y);

    node->markDirty(QSGNode::DirtyGeometry);
    return node;
}

void XYPlot::calculate_bounds()
{
    x_min = 0;
    x_max = 0;
    y_min = 0;
    y_max = 0;
    dx = 0;
    dy = 0;

    for(const auto& p : v)
    {
        if(p.x() > x_max)
            x_max = p.x();
        if(p.x() < x_min)
            x_min = p.x();
        if(p.y() > y_max)
            y_max = p.y();
        if(p.y() < y_min)
            y_min = p.y();
    }

    dx = width() / abs(x_max - x_min);
    dy = height() / abs(y_max - y_min);
}

} // LPVL
