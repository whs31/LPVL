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
{
    this->setFlag(ItemHasContents);
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

QSGNode *ValueMesh::updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*)
{
    QSGGeometry* geometry = nullptr;
    QSGGeometryNode* node = static_cast<QSGGeometryNode*>(old_node);

    if(node == nullptr)
    {
        node = new QSGGeometryNode;

        QSGVertexColorMaterial* material = new QSGVertexColorMaterial;
        material->setFlag(QSGMaterial::Blending);

        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), 0, 0, QSGGeometry::UnsignedIntType);

        node->setMaterial(material);
        node->setGeometry(geometry);
        node->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);
    }

    return node;
}


} // LPVL
