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
#include "LPVL/ChartBase"
#include "LPVL/Point2D"
#include <vector>

using std::vector;

namespace LPVL
{
    class LPVL_EXPORT XYPlot : public ChartBase
    {
        Q_OBJECT
        Q_PROPERTY(bool fill READ fill WRITE setFill NOTIFY fillChanged)

        public:
            XYPlot(QQuickItem* parent = nullptr);
            ~XYPlot();

            Q_INVOKABLE void set(const vector<LPVL::Point2D>& vec);
            Q_INVOKABLE void clear();

            bool fill() const; void setFill(bool);

            signals:
                void fillChanged();

        protected:
            QSGNode* updatePaintNode(QSGNode* old_node, UpdatePaintNodeData*) override;

        private:
            void calculate_bounds(bool skip = false);

        private:
            vector<Point2D> v;
            bool m_fill;

            float x_max, x_min, y_max, y_min;
    };
} // LPVL
