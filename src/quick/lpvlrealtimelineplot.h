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

#include "LPVL/LinePlot"

class QTimer;
namespace LPVL
{
    class LPVL_EXPORT RealtimeLinePlot : public LinePlot
    {
        Q_OBJECT
        Q_PROPERTY(float interval READ interval WRITE setInterval NOTIFY intervalChanged)
        Q_PROPERTY(int seconds READ seconds WRITE setSeconds NOTIFY secondsChanged)
        Q_PROPERTY(float from READ from WRITE setFrom NOTIFY fromChanged)
        Q_PROPERTY(float to READ to WRITE setTo NOTIFY toChanged)

        public:
            RealtimeLinePlot(QQuickItem* parent = nullptr);
            Q_INVOKABLE void append(float f);

            float interval() const; void setInterval(float);
            int seconds() const; void setSeconds(int);
            float from() const; void setFrom(float);
            float to() const; void setTo(float);

            signals:
                void intervalChanged();
                void secondsChanged();
                void fromChanged();
                void toChanged();

        private:
            private slots:
                void tick();

        private:
            QTimer* timer;
            float st = 0;
            vector<float> vec;
            int so;

            float m_interval = 1.0; // s
            int m_seconds = 30;
            float m_from = 0;
            float m_to = 0;
    };
} // LPVL
