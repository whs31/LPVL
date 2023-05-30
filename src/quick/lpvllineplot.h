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
#include <QtQuick/QQuickItem>
#include <vector>

using std::vector;

namespace LPVL
{
    class LPVL_EXPORT LinePlot : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY(QString backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
        Q_PROPERTY(QString foregroundColor READ foregroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged)
        Q_PROPERTY(QString plottingColor READ plottingColor WRITE setPlottingColor NOTIFY plottingColorChanged)
        Q_PROPERTY(bool drawBackground READ drawBackground WRITE setDrawBackground NOTIFY drawBackgroundChanged)
        Q_PROPERTY(bool drawAxes READ drawAxes WRITE setDrawAxes NOTIFY drawAxesChanged)
        Q_PROPERTY(bool fill READ fill WRITE setFill NOTIFY fillChanged)

        public:
            LinePlot(QQuickItem* parent = nullptr);
            virtual ~LinePlot();

            Q_INVOKABLE void set(const vector<float>& vec, float max = 0, float min = 0);
            Q_INVOKABLE void clear();

            QString backgroundColor() const; void setBackgroundColor(const QString&);
            QString foregroundColor() const; void setForegroundColor(const QString&);
            QString plottingColor() const; void setPlottingColor(const QString&);

            bool drawBackground() const; void setDrawBackground(bool);
            bool drawAxes() const; void setDrawAxes(bool);
            bool fill() const; void setFill(bool);

            signals:
                void backgroundColorChanged();
                void foregroundColorChanged();
                void plottingColorChanged();
                void drawBackgroundChanged();
                void drawAxesChanged();
                void fillChanged();

        protected:
            QSGNode* updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*) override;

        private:
            void calculate_bounds(bool skip = false);

        private:
            vector<float> v;
            QString m_backgroundColor;
            QString m_foregroundColor;
            QString m_plottingColor;
            bool m_drawBackground = true;
            bool m_drawAxes = true;
            bool m_fill = true;

            float x_size, y_max, y_min;
    };
} // LPVL
