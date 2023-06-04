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

namespace LPVL
{
    class LPVL_EXPORT ChartBase : public QQuickItem
    {
        Q_OBJECT
        Q_PROPERTY(QString backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
        Q_PROPERTY(QString foregroundColor READ foregroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged)
        Q_PROPERTY(QString plottingColor READ plottingColor WRITE setPlottingColor NOTIFY plottingColorChanged)
        Q_PROPERTY(bool drawBackground READ drawBackground WRITE setDrawBackground NOTIFY drawBackgroundChanged)

        public:
            ChartBase(QQuickItem* parent = nullptr);
            virtual ~ChartBase() = default;

            Q_INVOKABLE void forceUpdate() noexcept;

            QString backgroundColor() const; void setBackgroundColor(const QString&);
            QString foregroundColor() const; void setForegroundColor(const QString&);
            QString plottingColor() const; void setPlottingColor(const QString&);
            bool drawBackground() const; void setDrawBackground(bool);

            signals:
                void backgroundColorChanged();
                void foregroundColorChanged();
                void plottingColorChanged();
                void drawBackgroundChanged();

        private:
            QString m_backgroundColor = "black";
            QString m_foregroundColor = "white";
            QString m_plottingColor = "blue";
            bool m_drawBackground = true;
    };
} // LPVL
