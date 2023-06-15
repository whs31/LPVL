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

#include "lpvlglnodegeometry.h"
#include "lpvlglvertex.h"

#include <cmath>
#include <QtGui/QColor>
#include <QtQuick/QSGGeometry>
#include <QtQuick/QSGFlatColorMaterial>
#include <QtQuick/QSGGeometryNode>
#include <LPVL/Math>

namespace LPVL
{
namespace scenegraph
{

QSGGeometry* createLineStripNode(const vector<float> &v, float dx, float dy, float w, float h, float line_width)
{
    auto ret = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0, 0, QSGGeometry::UnsignedIntType);
    ret->setDrawingMode(QSGGeometry::DrawLineStrip);
    ret->setLineWidth(line_width);

    vector<Vertex> gl;
    for(size_t i = 0; i < v.size(); ++i)
        gl.push_back(Vertex(i * dx, h - v[i] * dy));

    ret->allocate(gl.size());
    for(size_t i = 0; i < gl.size(); ++i)
        ret->vertexDataAsPoint2D()[i].set(gl[i].x, gl[i].y);

    return ret;
}

QSGGeometry* createSimpleGraphNode(const vector<float> &v, float dx, float dy, float w, float h)
{
    auto ret = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0, 0, QSGGeometry::UnsignedIntType);
    ret->setDrawingMode(QSGGeometry::DrawTriangleStrip);

    vector<Vertex> gl;
    for(size_t i = 0; i < v.size(); ++i) {
        gl.push_back(Vertex(i * dx, h - v[i] * dy));
        gl.push_back(Vertex(i * dx, h));
    }

    ret->allocate(gl.size());
    for(size_t i = 0; i < gl.size(); ++i)
        ret->vertexDataAsPoint2D()[i].set(gl[i].x, gl[i].y);

    return ret;
}

QSGFlatColorMaterial* createFlatTransparentMaterial(const QString& col, float alpha)
{
    auto ret = new QSGFlatColorMaterial;
    QColor c(col);
    if(alpha != 1)
        c.setAlphaF(alpha);
    ret->setColor(c);

    return ret;
}

QSGGeometryNode* createBackgroundNode(const QString &col, float w, float h)
{
    QSGGeometry* g = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0, 0, QSGGeometry::UnsignedIntType);
    g->setDrawingMode(QSGGeometry::DrawTriangles);
    QSGGeometryNode* ret = new QSGGeometryNode;
    ret->setMaterial(createFlatTransparentMaterial(col));
    ret->setGeometry(g);
    ret->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);

    g->allocate(6);
    g->vertexDataAsPoint2D()[0].set(0, 0);
    g->vertexDataAsPoint2D()[1].set(w, 0);
    g->vertexDataAsPoint2D()[2].set(w, h);
    g->vertexDataAsPoint2D()[3].set(w, h);
    g->vertexDataAsPoint2D()[4].set(0, h);
    g->vertexDataAsPoint2D()[5].set(0, 0);

    return ret;
}

QSGGeometryNode *createLineStripNode(const vector<float> &v, float dx, float dy, float w, float h, const QString &col, float alpha, float line_width)
{
    auto ret = new QSGGeometryNode;
    ret->setMaterial(scenegraph::createFlatTransparentMaterial(col, alpha));
    ret->setGeometry(scenegraph::createLineStripNode(v, dx, dy, w, h, line_width));
    ret->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);

    return ret;
}

QSGGeometryNode *createGraphNode(const vector<float> &v, float dx, float dy, float w, float h, const QString &col, float alpha)
{
    auto ret = new QSGGeometryNode;
    ret->setMaterial(scenegraph::createFlatTransparentMaterial(col, alpha));
    ret->setGeometry(scenegraph::createSimpleGraphNode(v, dx, dy, w, h));
    ret->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);

    return ret;
}

} // scenegraph

Boundaries calc::boundArray(const vector<Point2D> &vec) noexcept
{
    Boundaries ret;
    for(const auto& p : vec)
    {
        if(p.x() > ret.xmax)
            ret.xmax = p.x();
        if(p.x() < ret.xmin)
            ret.xmin = p.x();
        if(p.y() > ret.ymax)
            ret.ymax = p.y();
        if(p.y() < ret.ymin)
            ret.ymin = p.y();
    }

    return ret;
}

CoordDelta calc::deltaBound(float w, float h, const Boundaries &bounds) noexcept
{
    CoordDelta ret;
    ret.dx = w / abs(bounds.xmax - bounds.xmin);
    ret.dy = h / abs(bounds.ymax - bounds.ymin);
    return ret;
}

constexpr static const double MAP_SCALE_CONST = 156543.03392;

float internal::mqi_zoom_ratio(double lat, float m_to_px_ratio) noexcept
{
    if(not m_to_px_ratio)
        return LPVL::log(2, MAP_SCALE_CONST * cos(lat * M_PI / 180));
    return LPVL::log(2, MAP_SCALE_CONST * cos(lat * M_PI / 180) / m_to_px_ratio);
}

} // LPVL
