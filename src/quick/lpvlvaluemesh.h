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
                float x; // top left, normalized
                float y; // top left, normalized
                float value; // normalized
            };

        private:
            Q_OBJECT
            Q_PROPERTY(QSizeF rectSize READ rectSize WRITE setRectSize NOTIFY rectSizeChanged)
            Q_PROPERTY(vector<ValueDiscrete> data READ data WRITE setData NOTIFY dataChanged)
            Q_PROPERTY(QString minColor READ minColor WRITE setMinColor NOTIFY minColorChanged)
            Q_PROPERTY(QString maxColor READ maxColor WRITE setMaxColor NOTIFY maxColorChanged)

        public:
            ValueMesh(QQuickItem* parent = nullptr);

            QSizeF rectSize() const; void setRectSize(const QSizeF&);
            vector<ValueDiscrete> data() const; void setData(const vector<ValueDiscrete>&);

            QString minColor() const; void setMinColor(const QString&);
            QString maxColor() const; void setMaxColor(const QString&);

            signals:
                void rectSizeChanged();
                void dataChanged();
                void minColorChanged();
                void maxColorChanged();

        protected:
            QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*) override;

        private:
            void updateDeltas() noexcept;

        private:
            struct GradientDelta
            {
                int dr = 0;
                int dg = 0;
                int db = 0;
            } delta;

            QSizeF m_rectSize;
            vector<ValueDiscrete> m_data;
            QString m_minColor;
            QString m_maxColor;
            QColor min;
            QColor max;
    };
} // LPVL
