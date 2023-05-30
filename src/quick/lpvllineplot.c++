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

#include "lpvllineplot.h"
#include <QtQuick/QSGGeometryNode>
#include <QtQuick/QSGFlatColorMaterial>
#include "LPVL/GLGeometry"

namespace LPVL
{
    LPVL_REGISTER_QML(LinePlot, "LPVLLinePlot", "LPVL.Charts");

    LinePlot::LinePlot(QQuickItem* parent)
        : QQuickItem(parent)
    {
        setFlags(ItemHasContents);
    }

    LinePlot::~LinePlot() {}

    void LinePlot::set(const vector<float>& vec, float max, float min)
    {
        if(v == vec)
            return;

        v = vec;
        y_max = max;
        y_min = min;
        this->calculate_bounds((max != 0 or min != 0));
        this->update();
    }

    void LinePlot::clear()
    {
        v.clear();
        y_max = 0;
        y_min = 0;
        this->update();
    }

    QSGNode *LinePlot::updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*)
    {
        QSGGeometry* geometry = nullptr;
        QSGGeometry* plot_geometry = nullptr;
        QSGGeometry* outline_geometry = nullptr;
        QSGGeometry* axis_geometry = nullptr;
        QSGGeometryNode* plot_node = nullptr;
        QSGGeometryNode* node = static_cast<QSGGeometryNode*>(old_node);

        if(node == nullptr)
        {
            node = new QSGGeometryNode;

            QSGFlatColorMaterial* material = new QSGFlatColorMaterial;
            material->setColor(QColor(plottingColor()));
            geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0, 0, QSGGeometry::UnsignedIntType);

            node->setMaterial(material);
            node->setGeometry(geometry);
            node->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);
        }

        node->removeAllChildNodes();

        if(drawBackground())
            node->appendChildNode(scenegraph::createBackgroundNode(backgroundColor(), width(), height()));

        axis_geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0, 0, QSGGeometry::UnsignedIntType);
        axis_geometry->setDrawingMode(QSGGeometry::DrawLines);
        axis_geometry->setLineWidth(2);
        QSGGeometryNode* axis_node = new QSGGeometryNode;
        axis_node->setMaterial(scenegraph::createFlatTransparentMaterial(foregroundColor(), .3));
        axis_node->setGeometry(axis_geometry);
        axis_node->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);
        node->appendChildNode(axis_node);

        float dx = width() / (x_size - 1);
        float dy = height() / (y_max - y_min);

        if(fill())
        {
            plot_node = new QSGGeometryNode;
            plot_node->setMaterial(scenegraph::createFlatTransparentMaterial(plottingColor(), .4));
            plot_node->setGeometry(scenegraph::createSimpleGraphNode(v, dx, dy, width(), height()));
            plot_node->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);
            node->appendChildNode(plot_node);
        }

        QSGGeometryNode* outline_node = new QSGGeometryNode;
        outline_node->setMaterial(scenegraph::createFlatTransparentMaterial(plottingColor()));
        outline_node->setGeometry(scenegraph::createLineStripNode(v, dx, dy, width(), height(), 3));
        outline_node->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);
        node->appendChildNode(outline_node);

        if(drawAxes())
        {
            vector<Vertex> gla;
            float ox_dx = width() / 5;
            float x = ox_dx;
            while(x < width())
            {
                gla.push_back(Vertex(x, 0));
                gla.push_back(Vertex(x, height()));
                x += ox_dx;
            }

            float oy_dy = height() / 4;
            float y = oy_dy;
            while(y < height())
            {
                gla.push_back(Vertex(0, y));
                gla.push_back(Vertex(width(), y));
                y += oy_dy;
            }

            axis_geometry->allocate(gla.size());
            for(size_t i = 0; i < gla.size(); ++i)
                axis_geometry->vertexDataAsPoint2D()[i].set(gla[i].x, gla[i].y);
        }

        node->markDirty(QSGNode::DirtyGeometry);
        return node;
    }

    QString LinePlot::backgroundColor() const { return m_backgroundColor; }
    void LinePlot::setBackgroundColor(const QString& o) {
        if (m_backgroundColor == o)
            return;
        m_backgroundColor = o;
        emit backgroundColorChanged();
    }

    QString LinePlot::foregroundColor() const { return m_foregroundColor; }
    void LinePlot::setForegroundColor(const QString& o) {
        if (m_foregroundColor == o)
            return;
        m_foregroundColor = o;
        emit foregroundColorChanged();
    }

    QString LinePlot::plottingColor() const { return m_plottingColor; }
    void LinePlot::setPlottingColor(const QString& o) {
        if (m_plottingColor == o)
            return;
        m_plottingColor = o;
        emit plottingColorChanged();
    }

    void LinePlot::calculate_bounds(bool skip)
    {
        x_size = v.size();
        if(not skip)
        {
            const auto [min, max] = std::minmax_element(v.begin(), v.end());
            y_max = (float)*max;
            y_min = (float)*min;
        }
    }

    bool LinePlot::drawBackground() const { return m_drawBackground; }
    void LinePlot::setDrawBackground(bool o) {
        if (m_drawBackground == o)
            return;
        m_drawBackground = o;
        emit drawBackgroundChanged();
    }

    bool LinePlot::drawAxes() const { return m_drawAxes; }
    void LinePlot::setDrawAxes(bool o) {
        if (m_drawAxes == o)
            return;
        m_drawAxes = o;
        emit drawAxesChanged();
    }

    bool LinePlot::fill() const { return m_fill; }
    void LinePlot::setFill(bool o) {
        if (m_fill == o)
            return;
        m_fill = o;
        emit fillChanged();
    }
} // LPVL
