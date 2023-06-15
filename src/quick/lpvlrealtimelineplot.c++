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

#include "lpvlrealtimelineplot.h"
#include <QtCore/QTimer>
#include <QtQuick/QSGGeometryNode>
#include <QtQuick/QSGFlatColorMaterial>
#include <stdexcept>

#include "LPVL/GLGeometry"

namespace LPVL
{
    LPVL_REGISTER_QML(RealtimeLinePlot, "LPVLRealtimeLinePlot", "LPVL.Charts")

    RealtimeLinePlot::RealtimeLinePlot(QQuickItem* parent)
        : LinePlot(parent)
        , timer(new QTimer(this))
    {
        setFlags(ItemHasContents);
        connect(timer, &QTimer::timeout, this, &RealtimeLinePlot::tick);

        vec.resize(seconds() / interval());
        timer->start(interval() * 1'000);
    }

    void RealtimeLinePlot::append(float f) { st = f; }

    float RealtimeLinePlot::interval() const { return m_interval; }
    void RealtimeLinePlot::setInterval(float o) {
        if (qFuzzyCompare(m_interval, o))
            return;

        if(o <= 0)
            throw std::invalid_argument("Interval must be greater than 0.");

        m_interval = o;
        emit intervalChanged();

        vec.clear();
        so = seconds() / interval();
    }

    int RealtimeLinePlot::seconds() const { return m_seconds; }
    void RealtimeLinePlot::setSeconds(int o) {
        if (m_seconds == o)
            return;

        if(o <= 0)
            throw std::invalid_argument("Seconds must be greater than 0.");

        m_seconds = o;
        emit secondsChanged();

        vec.clear();
        this->update();
    }

    void RealtimeLinePlot::tick()
    {
        so = seconds() / interval();
        if(vec.size() >= so and vec.size() > 0)
            vec.erase(vec.begin());
        vec.push_back(st);
        st = 0;

        if(from() == 0 and to() == 0)
            this->set(vec);
        else
            this->set(vec, to(), from());
    }

    float RealtimeLinePlot::from() const { return m_from; }
    void RealtimeLinePlot::setFrom(float o) {
        if (qFuzzyCompare(m_from, o))
            return;
        m_from = o;
        emit fromChanged();
    }

    float RealtimeLinePlot::to() const { return m_to; }
    void RealtimeLinePlot::setTo(float o) {
        if (qFuzzyCompare(m_to, o))
            return;
        m_to = o;
        emit toChanged();
    }
} // LPVL
