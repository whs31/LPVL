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

#include "lpvlvaluemesh.h"
#include <QtQuick/QSGGeometryNode>
#include <QtQuick/QSGVertexColorMaterial>
#include <LPVL/GLGeometry>

namespace LPVL
{

LPVL_REGISTER_QML(ValueMesh, "LPVLValueMesh", "LPVL.Charts");

ValueMesh::ValueDiscrete::ValueDiscrete(float x, float y, float value)
    : x(x)
    , y(y)
    , value(value)
{}

ValueMesh::ValueDiscrete::ValueDiscrete()
    : x(0)
    , y(0)
    , value(0)
{}


ValueMesh::ValueMesh(QQuickItem* parent)
    : QQuickItem(parent)
    , m_rectSize(QSizeF())
    , m_minColor("#ed8796")
    , m_maxColor("#a6da95")
    , min(m_minColor)
    , max(m_maxColor)
{
    this->setFlag(ItemHasContents);
    this->updateDeltas();
}

QSizeF ValueMesh::rectSize() const { return m_rectSize; }
void ValueMesh::setRectSize(const QSizeF& sz) {
    if (m_rectSize == sz)
        return;
    m_rectSize = sz;
    emit rectSizeChanged();

    this->update();
}

vector<ValueMesh::ValueDiscrete> ValueMesh::data() const { return m_data; }
void ValueMesh::setData(const vector<ValueMesh::ValueDiscrete>& dt) {
    m_data = dt;
    emit dataChanged();

    this->update();
}

QSGNode* ValueMesh::updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*)
{
    QSGGeometry* geometry = nullptr;
    QSGGeometryNode* node = static_cast<QSGGeometryNode*>(old_node);

    if(node == nullptr)
    {
        node = new QSGGeometryNode;

        QSGVertexColorMaterial* material = new QSGVertexColorMaterial;
        material->setFlag(QSGMaterial::Blending);

        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), 0, 0, QSGGeometry::UnsignedIntType);
        geometry->setDrawingMode(QSGGeometry::DrawTriangles);

        node->setMaterial(material);
        node->setGeometry(geometry);
        node->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);
    }

    geometry = node->geometry();

    if(data().empty() or rectSize().isEmpty())
        return node;

    vector<VertexC> gl;
    for(const auto& discrete : data())
    {
        uint8_t r = static_cast<uint8_t>(min.red() + delta.dr * discrete.value);
        uint8_t g = static_cast<uint8_t>(min.green() + delta.dg * discrete.value);
        uint8_t b = static_cast<uint8_t>(min.blue() + delta.db * discrete.value);
        gl.push_back({static_cast<float>(discrete.x * width()),
                      static_cast<float>(discrete.y * height()),
                      r, g, b, 255});
        gl.push_back({static_cast<float>((discrete.x + rectSize().width()) * width()),
                      static_cast<float>(discrete.y * height()),
                      r, g, b, 255});
        gl.push_back({static_cast<float>((discrete.x + rectSize().width()) * width()),
                      static_cast<float>((discrete.y + rectSize().height()) * height()),
                      r, g, b, 255});
        gl.push_back({static_cast<float>(discrete.x * width()),
                      static_cast<float>(discrete.y * height()),
                      r, g, b, 255});
        gl.push_back({static_cast<float>(discrete.x * width()),
                      static_cast<float>((discrete.y + rectSize().height()) * height()),
                      r, g, b, 255});
        gl.push_back({static_cast<float>((discrete.x + rectSize().width()) * width()),
                      static_cast<float>((discrete.y + rectSize().height()) * height()),
                      r, g, b, 255});
    }

    geometry->allocate(gl.size());
    for(size_t i = 0; i < gl.size(); i++)
        geometry->vertexDataAsColoredPoint2D()[i].set(gl.at(i).x, gl.at(i).y,
                                                      gl.at(i).r, gl.at(i).g,
                                                      gl.at(i).b, gl.at(i).a);

    node->markDirty(QSGNode::DirtyGeometry);

    return node;
}

void ValueMesh::updateDeltas() noexcept
{
    min = QColor(minColor());
    max = QColor(maxColor());

    delta.dr = max.red() - min.red();
    delta.dg = max.green() - min.green();
    delta.db = max.blue() - min.blue();

    qDebug() << delta.dr << delta.dg << delta.db;

    this->update();
}

QString ValueMesh::minColor() const { return m_minColor; }
void ValueMesh::setMinColor(const QString &c) {
    if (m_minColor == c)
        return;
    m_minColor = c;
    emit minColorChanged();

    this->updateDeltas();
}

QString ValueMesh::maxColor() const { return m_maxColor; }
void ValueMesh::setMaxColor(const QString &c) {
    if (m_maxColor == c)
        return;
    m_maxColor = c;
    emit maxColorChanged();

    this->updateDeltas();
}

} // LPVL
