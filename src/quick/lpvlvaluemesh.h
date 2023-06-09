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
#include <QtCore/QSizeF>
#include <QtQuick/QQuickItem>
#include <vector>

using std::vector;

namespace LPVL
{
    class LPVL_EXPORT ValueMesh : public QQuickItem
    {
        public:
            struct ValueDiscrete
            {
                ValueDiscrete(float x, float y, float value);
                ValueDiscrete();
                float x; // top left
                float y; // top left
                float value;
            };

        private:
            Q_OBJECT
            Q_PROPERTY(QSizeF rectSize READ rectSize WRITE setRectSize NOTIFY rectSizeChanged)
            Q_PROPERTY(vector<ValueDiscrete> data READ data WRITE setData NOTIFY dataChanged)

        public:
            ValueMesh(QQuickItem* parent = nullptr);

            QSizeF rectSize() const; void setRectSize(const QSizeF&);
            vector<ValueDiscrete> data() const; void setData(const vector<ValueDiscrete>&);

            signals:
                void rectSizeChanged();
                void dataChanged();

        protected:
            QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*) override;

        private:

        private:
            QSizeF m_rectSize;
            vector<ValueDiscrete> m_data;
    };
} // LPVL
